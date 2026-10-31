#!/usr/bin/env python3
"""Preserve installed Tainted Hopper29.3.0 movement and four-ring evidence."""
import argparse
import hashlib
import json
import struct
from pathlib import Path
import capstone
import pefile

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/tainted_hopper/source'
EXE = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    raw = EXE.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == SHA
    pe = pefile.PE(data=raw)
    read = lambda a, n: pe.get_data(a - pe.OPTIONAL_HEADER.ImageBase, n)
    u32 = lambda a: struct.unpack('<I', read(a, 4))[0]
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    index = read(0x69abc0 + 29 - 10, 1)[0]
    case = u32(0x69a7f8 + 4 * index)
    assert case == 0x69a19f
    assert list(md.disasm(read(case + 2, 5), case + 2))[0].op_str == '0x514450'
    tables = {}
    for name, address, expected in [
        ('land_ring_stage', 0x516ddc, [0x515f58, 0x515f77, 0x515f83, 0x515f99]),
        ('projectile_modes', 0x6a33ec, [0x6a1a83, 0x6a1afb, 0x6a1c91, 0x6a1ead, 0x6a2099,
                                     0x6a2360, 0x6a269d, 0x6a286f, 0x6a2a49, 0x6a2e74])]:
        actual = [u32(address + i * 4) for i in range(len(expected))]
        assert actual == expected
        tables[name] = dict(address=hex(address), cases=list(map(hex, actual)))
    strings = {}
    for address, expected in [(0xb3fd8c, 'Idle'), (0xb40218, 'Idle2'), (0xb405cc, 'Hop'),
                              (0xb430f0, 'Hop2'), (0xb40338, 'Jump'), (0xb4034c, 'Land')]:
        value = read(address, 64).split(b'\0')[0].decode()
        assert value == expected
        strings[hex(address)] = value
    constants = {}
    for name, address, expected in [
        ('target_range', 0xb6ab34, 130), ('wander', 0xb6aaf0, 95),
        ('far_force', 0xb6a274, .05), ('ground_factor', 0xb6a2cc, .1),
        ('retention', 0xb6a50c, .7), ('arrival', 0xb6a974, 10),
        ('near_force_range', 0xb6aa0c, 30), ('stuck_speed', 0xb6a53c, .75),
        ('grid_spacing', 0xb6aa3c, 40), ('ring_radians', 0xb6a914, 6.28318530718),
        ('ring_count_rounding', 0xb6a480, .5)]:
        value = struct.unpack('<f', read(address, 4))[0]
        assert abs(value - expected) < max(abs(expected) * 1e-6, 1e-12), (name, value)
        constants[name] = dict(address=hex(address), value=value)
    result = dict(baseline='Installed Repentance1.7.9b', executable_sha256=SHA,
        scope='Tainted Hopper normal branch, shared destination motion, current/accumulated event queries, four-stage projectile modes and landing effect. Not a complete behavior or armor port.',
        dispatch=dict(index=index, case=hex(case), controller='0x514450'),
        tables=tables, strings=strings, constants=constants, windows=[])
    if not args.check:
        assert not (OUT / 'manifest.json').exists()
        assert not (OUT.parent / 'checkpoint.json').exists()
        OUT.mkdir(parents=True, exist_ok=True)
    for name, start, end in [
        ('controller', 0x514450, 0x516dda), ('normal_target_helper', 0x695a30, 0x695c2e),
        ('entity_defaults', 0x681aa7, 0x681b4e), ('entity_movement', 0x686406, 0x686497),
        ('event_masks', 0x405e90, 0x405fcb), ('current_event_wrapper', 0x4060f0, 0x40610f),
        ('clamp_wrapper', 0x427710, 0x42773e), ('grid_index', 0x7ce950, 0x7ce9bc),
        ('grid_position', 0x7cebc0, 0x7cec06), ('projectile_params', 0x430d70, 0x430ec0),
        ('fire_projectiles', 0x6a1a20, 0x6a3420), ('landing_effect', 0x68d7b0, 0x68d821)]:
        blob = read(start, end - start)
        text = '\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'
                         for i in md.disasm(blob, start)) + '\n'
        path = OUT / (name + '.asm')
        if args.check:
            assert path.read_text() == text
        else:
            assert not path.exists()
            path.write_text(text)
        result['windows'].append(dict(path=str(path.relative_to(ROOT)), start=hex(start), end=hex(end),
            raw_sha256=hashlib.sha256(blob).hexdigest(), sha256=hashlib.sha256(path.read_bytes()).hexdigest()))
    if args.check:
        assert json.loads((OUT / 'manifest.json').read_text()) == result
    else:
        (OUT / 'manifest.json').write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(dict(result='pass', windows=len(result['windows']))))


if __name__ == '__main__':
    main()
