#!/usr/bin/env python3
"""Preserve installed Eggy hopping, death release and child animation evidence.

This is evidence extraction, not a claim of a finished Eggy port. Other types
share this function; only explicitly reviewed branches apply to 29.2.0.
"""
import argparse
import hashlib
import json
import struct
from pathlib import Path
import capstone
import pefile

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/eggy/source'
EXE = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--check', action='store_true')
    parser.add_argument('--extend', action='store_true', help='Extend this unfrozen research manifest with base movement evidence')
    args = parser.parse_args()
    raw = EXE.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == SHA
    pe = pefile.PE(data=raw)
    read = lambda a, n: pe.get_data(a - pe.OPTIONAL_HEADER.ImageBase, n)
    u32 = lambda a: struct.unpack('<I', read(a, 4))[0]
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    dispatch = {}
    for entity_type in [29, 34, 54]:
        index = read(0x69abc0 + entity_type - 10, 1)[0]
        case = u32(0x69a7f8 + 4 * index)
        assert case == 0x69a19f
        assert list(md.disasm(read(case + 2, 5), case + 2))[0].op_str == '0x514450'
        dispatch[str(entity_type)] = dict(index=index, case=hex(case), controller='0x514450')
    constants = {}
    for name, address, expected in [
        ('random_u32_scale', 0xb6a19c, 2**-32),
        ('trite_controlled_bonus', 0xb6ab20, 120),
        ('trite_random_bonus_a', 0xb6aa60, 50),
        ('trite_random_bonus_b', 0xb6aab4, 70),
        ('range_bonus_scale', 0xb6a690, 1.3),
        ('range_base', 0xb6ab34, 130),
        ('egg_rag_variant_range_scale', 0xb6a50c, .7),
        ('target_overshoot_divisor', 0xb6aba8, 200),
        ('wander_distance_base', 0xb6aaf0, 95),
        ('far_target_impulse_scale', 0xb6a274, .05),
        ('outside_jump_direction_scale', 0xb6a2cc, .1),
        ('target_arrival_distance', 0xb6a974, 10),
        ('stuck_speed_threshold', 0xb6a53c, .75),
        ('hop_retention', 0xb6a50c, .7),
        ('native_grid_spacing', 0xb6aa3c, 40),
        ('creep_visual_scale', 0xb6a560, .8),
        ('child_short_frame', 0xb6a8cc, 4),
        ('child_medium_frame_short_minimum', 0xb6a8f4, 5),
        ('child_long_frame', 0xb6a910, 6),
        ('child_long_random_range', 0xb6a864, 3),
        ('child_medium_minimum', 0xb6a940, 8),
    ]:
        value = struct.unpack('<f', read(address, 4))[0]
        assert abs(value - expected) < max(abs(expected) * 1e-6, 1e-12)
        constants[name] = dict(address=hex(address), value=value)
    strings = {}
    for address, expected in [(0xb3fd8c, 'Idle'), (0xb405cc, 'Hop'),
                              (0xb40338, 'Jump'), (0xb4034c, 'Land'),
                              (0xb43120, 'Die'), (0xb43124, 'HopShort'), (0xb43110, 'HopLong')]:
        value = read(address, 64).split(b'\0')[0].decode()
        assert value == expected
        strings[hex(address)] = value
    result = dict(baseline='Installed Repentance 1.7.9b', executable_sha256=SHA,
        scope='Shared controller, ordinary target helper, native grid mapping, normal entity-time/friction integration and animation event masks.',
        dispatch=dispatch, constants=constants, strings=strings, windows=[])
    if not args.check:
        assert not (OUT / 'manifest.json').exists() or args.extend
        assert not (OUT.parent / 'checkpoint.json').exists(), 'Do not rewrite a frozen checkpoint'
        OUT.mkdir(parents=True, exist_ok=True)
    for name, start, end in [('controller', 0x514450, 0x516dda),
                             ('normal_target_helper', 0x695a30, 0x695c2e),
                             ('entity_defaults', 0x681aa7, 0x681b4e),
                             ('entity_movement', 0x686406, 0x686497),
                             ('event_masks', 0x405e90, 0x405fcb),
                             ('current_event_wrapper', 0x4060f0, 0x40610f),
                             ('clamp_wrapper', 0x427710, 0x42773e),
                             ('grid_index', 0x7ce950, 0x7ce9bc),
                             ('grid_position', 0x7cebc0, 0x7cec06)]:
        blob = read(start, end - start)
        text = '\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'
                         for i in md.disasm(blob, start)) + '\n'
        path = OUT / (name + '.asm')
        if args.check:
            assert path.read_text() == text
        else:
            assert not path.exists() or path.read_text() == text, 'Existing evidence differs'
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
