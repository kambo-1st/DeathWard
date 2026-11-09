#!/usr/bin/env python3
"""Bounded native NPC scheduling blocks and obstructed grid search.

Executes original instructions. Full NPC wrapper, mask generation, route cache,
collision and live NPC timing are outside this fixture.
"""
import argparse
import csv
import hashlib
import importlib.util
import io
import json
import struct
from pathlib import Path

import capstone
import pefile
from unicorn.x86_const import (UC_X86_REG_EBP, UC_X86_REG_EBX, UC_X86_REG_ECX,
    UC_X86_REG_EDI, UC_X86_REG_EDX, UC_X86_REG_EIP, UC_X86_REG_ESI,
    UC_X86_REG_ESP, UC_X86_REG_XMM1, UC_X86_REG_XMM2)

spec = importlib.util.spec_from_file_location('activation',
    Path(__file__).with_name('capture-frowning-activation.py'))
A = importlib.util.module_from_spec(spec)
spec.loader.exec_module(A)
M = A.M
OUT = M.ROOT / 'docs/reports/isaac-first-floor-parity/gaper-scheduler-routing'
WINDOWS = [
    ('ordinary-early-bypass', 0x69b5a0, 0x69b5d5, True),
    ('early-special-base', 0x69b6aa, 0x69b6f7, False),
    ('ready-state-bypass', 0x69be56, 0x69be64, True),
    ('ordinary-ai-call', 0x69ce88, 0x69ce99, False),
    ('late-base-call', 0x69f887, 0x69f8ae, False),
    ('base-animation', 0x6860e7, 0x68618c, True),
    ('grid-search', 0x7a4383, 0x7a451e, True),
    ('grid-choice-steering', 0x7a4570, 0x7a47f5, True),
    ('queue-pop', 0x7a7aa0, 0x7a7bb0, True),
    ('queue-push', 0x7a7bb0, 0x7a7c30, True),
]


def scheduler(pe, runtime):
    f = A.Fixture(pe, runtime, 20)
    n, u, p = f.n, f.n.u, f.p
    # Normal healthy state takes the branch around the EARLY base call.
    u.reg_write(UC_X86_REG_EBP, n.ebp)
    f.word(p + 0xab4, 4)
    f.block(0x69b5a0, 0x69b756)
    u.reg_write(UC_X86_REG_ECX, 4)
    f.block(0x69be56, 0x69cda8)
    rows = []
    for name, scale, flags in [('ordinary', 1, 0), ('half-time-scale', .5, 0),
                               ('sprite-suppressed', 1, 1)]:
        f = A.Fixture(pe, runtime, 20)
        n, u, p = f.n, f.n.u, f.p
        for k in range(24):
            before = f.frame()
            force = f.ai_gates(True)
            after_ai = f.frame()
            n.write_float(p + 0x2f4, scale)
            u.reg_write(UC_X86_REG_EDX, 0)
            u.reg_write(UC_X86_REG_ESI, flags)
            f.block(0x6860e7, 0x68618c)
            after_base = f.frame()
            if name == 'ordinary':
                assert int(before) == min(k, 19)
                assert abs(force - (.6 if k == 0 else .72)) < 1e-6
                assert int(after_base) == min(k + 1, 19)
            elif name == 'half-time-scale':
                assert after_ai == 0 and after_base == .5
            else:
                assert after_base == 0
            assert n.read_float(p + 0x140) == 1  # playback speed restored
            assert n.read_float(p + 0x2fc) == (k + 1) * scale
            rows.append([name, k, scale, flags, before, force, after_ai,
                         after_base, f.playing()])
    return rows


class Grid:
    ROOM, GAME, QUEUE = 0x5000000, 0x4000000, 0x6000000

    def __init__(self, pe, costs):
        self.n = M.NativeMotion(pe)
        n, u = self.n, self.n.u
        self.finder = n.PLAYER + 0x8000
        for address, size in [(self.ROOM, 0x10000), (self.GAME, 0x200000),
                              (self.QUEUE, 0x10000)]:
            u.mem_map(address, size)
        self.word(0xbfd65c, self.GAME)
        self.word(self.GAME + 0x18190, self.ROOM)
        self.word(self.ROOM + 0xc, 15)
        self.word(self.ROOM + 0x10, 9)
        self.word(self.finder, n.PLAYER)
        self.costs = costs

    def word(self, address, value):
        self.n.u.mem_write(address, struct.pack('<I', value & 0xffffffff))

    def search(self, start, goal):
        n, u, b, f = self.n, self.n.u, self.n.ebp, self.finder
        self.word(f + 0x20, start)
        for i in range(448):
            value = self.costs.get(i, 1000)
            self.word(self.ROOM + 0x76c + i * 4, value)
            self.word(f + 0x2c + i * 4, value)
        # Preallocated scratch vector prevents heap/OS dependencies. Native
        # queue push/pop still execute unmodified; no helper is intercepted.
        for offset, value in [(-0x28, self.ROOM), (-0x44, goal),
                              (-0x58, f), (-0x8c, self.QUEUE),
                              (-0x88, self.QUEUE), (-0x84, self.QUEUE + 0x10000)]:
            self.word(b + offset, value)
        u.mem_write(b - 0x23, b'\0')
        u.reg_write(UC_X86_REG_EBP, b)
        u.reg_write(UC_X86_REG_ESP, b - 0x500)
        u.reg_write(UC_X86_REG_EBX, f)
        u.emu_start(0x7a4383, 0x7a451e, count=1000000)
        assert u.reg_read(UC_X86_REG_EIP) == 0x7a451e
        found = bool(u.mem_read(f + 0x72d, 1)[0])
        # Stop before scratch deallocation; select native gradient neighbor.
        x, y = 40 + 40 * (start % 15), 120 + 40 * (start // 15)
        for offset, value in [(0x294, x), (0x298, y), (0x2c4, 1),
                              (0x2f4, 1), (0x2b8, 0), (0x2bc, 0)]:
            n.write_float(n.PLAYER + offset, value)
        for offset, value in [(-0x78, x), (-0x74, y), (-0x50, 1),
                              (-0x54, 0), (-0x68, 0), (0xc, .6)]:
            n.write_float(b + offset, value)
        u.reg_write(UC_X86_REG_EBX, f)
        n.run(0x7a4570, 0x7a47f5)
        selected = struct.unpack('<I', u.mem_read(b - 0x3c, 4))[0] if found else -1
        waypoint = [40 + 40 * (selected % 15), 120 + 40 * (selected // 15)] if found else [0, 0]
        assert u.reg_read(UC_X86_REG_ESP) == b - 0x500
        return found, selected, waypoint, n.read_float(n.PLAYER + 0x2c4)


def navigation(pe):
    floor = {r * 15 + c: 0 for r in range(1, 8) for c in range(1, 14)}
    cases = []
    for name, cells in [
        ('open', []), ('central-cover', [(7, r) for r in range(2, 7)]),
        ('sealed', [(7, r) for r in range(1, 8)]),
        ('upper-gap', [(7, r) for r in range(2, 8)]),
        ('lower-gap', [(7, r) for r in range(1, 7)]),
        ('reopened', []),
    ]:
        costs = dict(floor)
        for c, r in cells:
            costs[r * 15 + c] = 1000
        cases.append((name, costs))
    rows = []
    for name, costs in cases:
        g = Grid(pe, costs)
        start, goal = 4 * 15 + 2, 4 * 15 + 12
        visited = set()
        for k in range(100):
            # The omitted direct-target branch takes over near the goal. Do
            # not force a grid-only search to represent native final arrival.
            if abs(start % 15 - goal % 15) + abs(start // 15 - goal // 15) == 1:
                break
            assert start not in visited, (name, start, 'route cycle')
            visited.add(start)
            found, selected, waypoint, friction = g.search(start, goal)
            rows.append([name, k, start, goal, int(found), selected, *waypoint, friction])
            if name == 'sealed':
                assert not found and abs(friction - .85) < 1e-6
                break
            assert found and costs.get(selected, 1000) < 950
            assert abs(start % 15 - selected % 15) + abs(start // 15 - selected // 15) == 1, (name, k, start, selected)
            if k == 0:
                if name in ['central-cover', 'upper-gap']:
                    assert selected == start - 15
                if name == 'lower-gap':
                    assert selected == start + 1  # equal gradients choose right before down
            if selected == goal:
                break
            start = selected
        else:
            raise AssertionError((name, 'goal not reached'))
    return rows


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--check', action='store_true')
    args = ap.parse_args()
    raw, rt = M.EXE.read_bytes(), A.RUNTIME.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == M.SHA
    assert hashlib.sha256(rt).hexdigest() == A.RUNTIME_SHA
    pe, runtime = pefile.PE(data=raw), pefile.PE(data=rt)
    timing, routes = scheduler(pe, runtime), navigation(pe)
    OUT.mkdir(parents=True, exist_ok=True)

    def save(name, data):
        p = OUT / name
        if args.check:
            assert p.read_bytes() == data, name
        else:
            p.write_bytes(data)

    for name, header, rows in [
        ('native-animation.csv', ['case', 'update', 'time_scale', 'no_sprite_update',
         'frame_before_ai', 'force', 'frame_after_ai', 'frame_after_base', 'playing'], timing),
        ('native-routes.csv', ['case', 'decision', 'start_index', 'goal_index',
         'found', 'selected_index', 'waypoint_x', 'waypoint_y', 'outgoing_friction'], routes)]:
        stream = io.StringIO(newline='')
        writer = csv.writer(stream, lineterminator='\n')
        writer.writerow(header)
        writer.writerows(rows)
        save(name, stream.getvalue().encode())
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    windows = []
    for name, start, end, executed in WINDOWS:
        blob = pe.get_data(start - 0x400000, end - start)
        listing = '\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip()
                            for i in md.disasm(blob, start)) + '\n'
        save(name + '.asm', listing.encode())
        windows.append(dict(name=name, start=hex(start), end=hex(end),
                            executed=executed, raw_sha256=hashlib.sha256(blob).hexdigest()))
    manifest = dict(exe_sha256=M.SHA, runtime_sha256=A.RUNTIME_SHA,
        animation_evaluations=len(timing), route_decisions=len(routes), route_cases=6,
        windows=windows, gameplay_changes=False,
        method='unpatched native activation/base-animation blocks and grid flood/gradient search; native queue helpers execute in preallocated scratch storage',
        supplied_boundaries=['ordinary healthy state4; timeScale1,.5 or sprite suppression flag',
            'AI-gate then base-animation sequence follows scoped wrapper branch evidence; intervening wrapper logic is not executed',
            '15x9 room dimensions, interior13x7, grid costs0/1000 and target/start cell indices',
            'fresh search per grid decision; scratch vector capacity preallocated; allocation/deallocation excluded',
            'NPC footprint expansion, native grid mask generation, direct-line/cache/RNG setup excluded',
            'grid-only approaches stop one cell from target; direct final arrival is excluded',
            'no collision, continuous position integration or live NPC timing'],
        full_native_acceptance=False)
    save('manifest.json', (json.dumps(manifest, indent=2) + '\n').encode())
    print(json.dumps(dict(passed=True, check=args.check, animation_evaluations=len(timing),
                          route_cases=6, route_decisions=len(routes), gameplay_changes=False)))


if __name__ == '__main__':
    main()
