#!/usr/bin/env python3
"""Execute bounded Frowning activation gates and animation helpers from 1.7.9b.

The caller supplies animation update cadence and direct-path results. This is
not execution of the full NPC scheduler, native navigation, or visual layers.
"""
import argparse
import csv
import hashlib
import importlib.util
import io
import json
import struct
import xml.etree.ElementTree as ET
from pathlib import Path

import capstone
import pefile
from unicorn.x86_const import (UC_X86_REG_ECX, UC_X86_REG_EDI,
                               UC_X86_REG_ESP, UC_X86_REG_FPCW,
                               UC_X86_REG_MXCSR)

spec = importlib.util.spec_from_file_location(
    'motion', Path(__file__).with_name('analyze-player-motion.py'))
M = importlib.util.module_from_spec(spec)
spec.loader.exec_module(M)
OUT = M.ROOT / 'docs/reports/isaac-first-floor-parity/frowning-activation'
RUNTIME = Path('/mnt/c/Windows/SysWOW64/ucrtbase.dll')
RUNTIME_SHA = 'e4f8f92eef00ff6a0c6d418af756a59d5a4b818d0d1de0d96cc193b4d6759432'
ANIMATION = M.ROOT / 'docs/reports/isaac-enemy-port/gaper/animations/010.000_Frowning Gaper.anm2'
WINDOWS = [
    ('initialize-head', 0x4f6fd2, 0x4f6ffc),
    ('select-force', 0x4f7e45, 0x4f7f0c),
    ('wake-gate', 0x4f80ed, 0x4f812f),
    ('set-overlay', 0x405bb0, 0x405c69),
    ('set-animation', 0x403740, 0x403814),
    ('set-frame', 0x403c00, 0x403ce5),
    ('play-overlay', 0x405a00, 0x405a77),
    ('overlay-frame', 0x405d10, 0x405d21),
    ('advance-animation', 0x403d60, 0x403e21),
    ('update-sprite', 0x403e30, 0x403e50),
]


class Fixture:
    def __init__(self, pe, runtime, frames):
        self.n = M.NativeMotion(pe)
        n = self.n
        u = n.u
        self.p = n.PLAYER
        self.sp = n.STACK + 0xe000
        self.sprite = self.p + 0x3c
        base = runtime.OPTIONAL_HEADER.ImageBase
        u.mem_map(base, (runtime.OPTIONAL_HEADER.SizeOfImage + 4095) & ~4095)
        u.mem_write(base, runtime.get_memory_mapped_image())
        u.reg_write(UC_X86_REG_FPCW, 0x27f)
        u.reg_write(UC_X86_REG_MXCSR, 0x1f80)
        for iat, name in [(0xa06524, b'floor'), (0xa06550, b'nextafterf')]:
            export = next(e for e in runtime.DIRECTORY_ENTRY_EXPORT.symbols
                          if e.name == name)
            assert export.forwarder is None
            self.word(iat, base + export.address)
        # Minimal Head animation metadata, with visual layers omitted explicitly.
        anim = self.p + 0x8000
        self.word(self.p + 0x28, 10)
        self.word(self.sprite + 0x74, anim)
        self.word(self.sprite + 0x78, 1)
        u.mem_write(anim, b'Head\0')
        for offset, value in [(0x10, 4), (0x14, 15), (0x30, frames)]:
            self.word(anim + offset, value)
        self.word(self.sprite + 0x50, self.sprite)
        n.write_float(self.sprite + 0x104, 1)
        u.mem_write(self.sprite + 0x109, b'\1')
        self.block(0x4f6fd2, 0x4f6ffc)
        assert self.frame() == 0 and not self.playing()

    def word(self, address, value):
        self.n.u.mem_write(address, struct.pack('<I', value))

    def block(self, start, end):
        u = self.n.u
        u.reg_write(UC_X86_REG_EDI, self.p)
        u.reg_write(UC_X86_REG_ESP, self.sp)
        self.n.run(start, end)

    def frame(self):
        return self.n.read_float(self.sprite + 0x60)

    def playing(self):
        return self.n.u.mem_read(self.sprite + 0x64, 1)[0]

    def advance(self, speed):
        self.n.write_float(self.sprite + 0x104, speed)
        self.word(self.sp, self.n.STOP)
        self.n.u.reg_write(UC_X86_REG_ESP, self.sp)
        self.n.u.reg_write(UC_X86_REG_ECX, self.sprite)
        self.n.run(0x403e30, self.n.STOP)

    def ai_gates(self, clear):
        self.n.u.mem_write(self.p + 0xa90, bytes([clear]))
        self.block(0x4f7e45, 0x4f7f0c)
        force = self.n.read_float(self.p + 0xb84)
        self.block(0x4f80ed, 0x4f812f)
        return force


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--check', action='store_true')
    args = ap.parse_args()
    raw = M.EXE.read_bytes()
    rt = RUNTIME.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == M.SHA
    assert hashlib.sha256(rt).hexdigest() == RUNTIME_SHA
    pe, runtime = pefile.PE(data=raw), pefile.PE(data=rt)
    root = ET.parse(ANIMATION).getroot()
    head = next(e for e in root.iter('Animation') if e.get('Name') == 'Head')
    frames = int(head.get('FrameNum'))
    assert frames == 20 and head.get('Loop') == 'false'
    assert not list(head.iter('Trigger'))
    OUT.mkdir(parents=True, exist_ok=True)

    def save(name, value):
        p = OUT / name
        if args.check:
            assert p.read_bytes() == value, name
        else:
            p.write_bytes(value)

    rows = []
    cases = [
        ('never-clear', lambda k: False, 1),
        ('clear-at-start', lambda k: True, 1),
        ('clear-after-three', lambda k: k >= 3, 1),
        ('single-clear-pulse', lambda k: k == 3, 1),
        ('half-speed-always-clear', lambda k: True, .5),
        ('half-speed-single-pulse', lambda k: k == 3, .5),
    ]
    for name, route, speed in cases:
        f = Fixture(pe, runtime, frames)
        for k in range(48):
            before = f.frame()
            clear = route(k)
            force = f.ai_gates(clear)
            after = f.frame()
            assert abs(force - (.72 if int(before) > 0 else .6)) < 1e-6
            if name == 'never-clear':
                assert before == 0 and not f.playing()
            if name == 'half-speed-always-clear':
                assert before == (0 if k == 0 else .5) and after == 0
            if name == 'single-clear-pulse' and k > 3:
                assert int(before) == min(19, k - 3)
            rows.append([name, k, int(clear), speed, before, force, after, f.playing()])
            f.advance(speed)
        if name in ['clear-at-start', 'clear-after-three', 'single-clear-pulse',
                    'half-speed-single-pulse']:
            assert int(f.frame()) == 19 and not f.playing()
    text = io.StringIO(newline='')
    w = csv.writer(text, lineterminator='\n')
    w.writerow(['case', 'supplied_update', 'supplied_direct_path',
                'supplied_animation_step', 'frame_before_ai', 'force',
                'frame_after_wake_gate', 'playing_after_gate'])
    w.writerows(rows)
    save('native-activation.csv', text.getvalue().encode())
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    windows = []
    for name, start, end in WINDOWS:
        blob = pe.get_data(start - 0x400000, end - start)
        listing = '\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip()
                            for i in md.disasm(blob, start)) + '\n'
        save(name + '.asm', listing.encode())
        windows.append(dict(name=name, start=hex(start), end=hex(end),
                            raw_sha256=hashlib.sha256(blob).hexdigest()))
    manifest = dict(
        exe_sha256=M.SHA, runtime_sha256=RUNTIME_SHA,
        animation_sha256=hashlib.sha256(ANIMATION.read_bytes()).hexdigest(),
        cases=len(cases), samples=len(rows), windows=windows,
        method='Original x86 instructions, real mapped UCRT floor/nextafterf; '
               'IAT binding only, no patched code or helper stubs',
        supplied_boundaries=[
            'minimal Head animation metadata:20 nonlooping frames, no events; visual layers omitted',
            'healthy type10 variant0, default sprite speed1 or experimental.5',
            'direct-path flag supplied, not calculated by native FindGridPath',
            'one explicit Sprite.Update AFTER each AI gate evaluation; this cadence/order is supplied',
            'UCRT initial data without DLL initialization; masked FPU0x27f and MXCSR0x1f80'],
        verified=['initial Head frame0 is stopped',
                  'force selection reads integer overlay frame before wake gate',
                  'clear path starts/restarts Head if integer frame<=0',
                  'Head continues without a direct path once playing and stops at frame19',
                  'repeated clear path with supplied.5 animation step restarts frame0 each evaluation'],
        not_verified=['whole NPC animation scheduling and live activation timing',
                      'native terrain/grid navigation', 'full status/Slow behavior',
                      'render layers, collision and complete enemy acceptance'],
        gameplay_changes=False)
    save('manifest.json', (json.dumps(manifest, indent=2) + '\n').encode())
    print(json.dumps(dict(passed=True, check=args.check, cases=len(cases), samples=len(rows),
                         full_scheduler_verified=False, gameplay_changes=False)))


if __name__ == '__main__':
    main()
