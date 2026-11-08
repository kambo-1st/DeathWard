#!/usr/bin/env python3
"""Execute pinned native player damage rounding, ordinary hurt counter and tick.

This is not whole TakeDamage, item/flag acceptance or live scheduler calibration.
No native calls or instructions in the executed windows are replaced.
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
from unicorn.x86_const import UC_X86_REG_EDI, UC_X86_REG_EBP, UC_X86_REG_ESP, UC_X86_REG_XMM0

SPEC = importlib.util.spec_from_file_location('motion', Path(__file__).with_name('analyze-player-motion.py'))
M = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(M)
OUT = M.ROOT / 'docs/reports/isaac-first-floor-parity/player-hurt'
WINDOWS = [('round_damage', 0x73d701, 0x73d719),
           ('ordinary_counter', 0x740cfe, 0x740d4b),
           ('counter_tick', 0x74ff9e, 0x74ffaf),
           ('integer_min', 0x417c60, 0x417c6a),
           ('damage_counter_guard', 0x73d963, 0x73d98a),
           ('early_counter_override', 0x7415d6, 0x741614)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    raw = M.EXE.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == M.SHA
    pe = pefile.PE(data=raw)
    n = M.NativeMotion(pe)
    u, p, b = n.u, n.PLAYER, n.ebp
    OUT.mkdir(parents=True, exist_ok=True)

    def save(name, blob):
        path = OUT / name
        if args.check:
            assert path.read_bytes() == blob, name
        else:
            path.write_bytes(blob)

    def integer(address):
        return struct.unpack('<i', u.mem_read(address, 4))[0]

    def write(address, value):
        u.mem_write(address, struct.pack('<i', value))

    def setup():
        n.reset()
        u.mem_write(b-0x1000, bytes(0x1100))
        u.reg_write(UC_X86_REG_EDI, p)
        u.reg_write(UC_X86_REG_EBP, b)
        u.reg_write(UC_X86_REG_ESP, b-0x1000)

    def table(name, fields, rows):
        buf = io.StringIO(newline='')
        w = csv.writer(buf, lineterminator='\n')
        w.writerow(fields)
        w.writerows(rows)
        save(name, buf.getvalue().encode())

    rows = []
    for amount in [0, .01, .1, .25, .49, .49999, .5, .50001, .75, .99,
                   1, 1.25, 1.49, 1.49999, 1.5, 1.50001, 1.99, 2, 2.49,
                   2.5, 3, 4, 6, 12]:
        setup()
        n.xmm(UC_X86_REG_XMM0, amount)
        n.run(0x73d701, 0x73d719)
        original, health = integer(b-0x130), integer(b-0x100)
        n.run(0x740cfe, 0x740d4b)
        rows.append([amount, original, health, integer(p+0x1308)])
    table('native-counter.csv', ['damage_half_hearts', 'original_rounded', 'health_before_modifiers', 'hurt_counter'], rows)
    ticks = []
    for initial, count in [(-1, 2), (0, 2), (1, 3), (60, 63), (120, 123)]:
        setup()
        write(p+0x1308, initial)
        for frame in range(count):
            before = integer(p+0x1308)
            n.run(0x74ff9e, 0x74ffaf)
            ticks.append([initial, frame, before, integer(p+0x1308)])
    table('native-tick.csv', ['initial', 'invocation', 'before', 'after'], ticks)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    windows = []
    for name, start, end in WINDOWS:
        blob = pe.get_data(start-pe.OPTIONAL_HEADER.ImageBase, end-start)
        save(name+'.asm', ('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(blob, start))+'\n').encode())
        windows.append({'name': name, 'start': hex(start), 'end_exclusive': hex(end), 'sha256': hashlib.sha256(blob).hexdigest(), 'executed': name in ('round_damage', 'ordinary_counter', 'counter_tick', 'integer_min')})
    manifest = {'target': 'Repentance 1.7.9b', 'exe_sha256': M.SHA,
                'counter_cases': len(rows), 'tick_states': len(ticks), 'windows': windows,
                'scope': 'Original damage rounding, bounded ordinary post-health counter assignment and isolated positive-counter decrement. Real integer-min helper executes. Supplied original amount; no health modifiers or world effects in these windows.',
                'remaining': ['whole damage entry and flags', 'item and special-state counter overrides', 'damage reduction original-versus-final amount integration', 'live callback frequency and scheduler/wall-clock calibration', 'complete collision ordering']}
    save('manifest.json', (json.dumps(manifest, indent=2)+'\n').encode())
    print(f'Native player hurt checked: {len(rows)} damage/counter cases, {len(ticks)} tick states; live timing and full TakeDamage remain open.')


if __name__ == '__main__':
    main()
