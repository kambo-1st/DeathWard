#!/usr/bin/env python3
"""Preserve Faceless helper evidence and the shared zero-vector normalization rule."""
import argparse
import hashlib
import json
import struct
from pathlib import Path

import capstone
import pefile

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/faceless/source'
INSTALL = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth')
EXE_SHA = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'


def sha(data):
    return hashlib.sha256(data).hexdigest()


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()

    def save(path, data):
        if args.check or path.exists():
            assert path.read_bytes() == data, path
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)

    raw = (INSTALL / 'isaac-ng.exe').read_bytes()
    assert sha(raw) == EXE_SHA
    pe = pefile.PE(data=raw, fast_load=True)
    read = lambda address, count: pe.get_data(address - pe.OPTIONAL_HEADER.ImageBase, count)
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    manifest = {
        'baseline': 'Installed Repentance 1.7.9b',
        'executable_sha256': EXE_SHA,
        'scope': 'Evidence only; helper extraction does not imply implementation or full status/control parity.',
        'windows': [],
    }
    windows = [
        ('eligible_target', 0x695620, 0x695674, True),
        ('target_position', 0x695a30, 0x695ec6, True),
        ('random_walk', 0x7a6180, 0x7a64a9, True),
        ('random_walk_special_gate', 0x7a35d0, 0x7a3641, True),
        ('radial_mode9', 0x6a2e74, 0x6a301c, False),
        ('blood_splat', 0x68d7b0, 0x68d821, True),
        ('normalize_vector', 0x962560, 0x9625d5, True),
    ]
    for name, start, end, whole_function in windows:
        blob = read(start, end - start)
        instructions = list(decoder.disasm(blob, start))
        assert instructions[0].address == start
        assert instructions[-1].address + instructions[-1].size == end
        if whole_function:
            assert instructions[-1].mnemonic == 'ret'
        else:
            assert instructions[-1].mnemonic == 'jmp' and instructions[-1].op_str == '0x6a301f'
        text = '\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in instructions) + '\n'
        path = OUT / (name + '.asm')
        save(path, text.encode())
        manifest['windows'].append({
            'path': str(path.relative_to(ROOT)), 'start': hex(start), 'end_exclusive': hex(end),
            'whole_function': whole_function, 'raw_sha256': sha(blob), 'sha256': sha(text.encode()),
        })
    dispatch = struct.unpack('<10I', read(0x6a33ec, 40))
    assert dispatch[9] == 0x6a2e74
    manifest['projectile_mode_table'] = {
        'address': '0x6a33ec', 'targets': list(map(hex, dispatch)),
        'raw_sha256': sha(read(0x6a33ec, 40)),
    }
    manifest['float_constants'] = {}
    for name, address, expected in [
        ('zero', 0xb6a18c, 0), ('one', 0xb6a614, 1),
        ('attack_base', 0xb6a210, .008), ('damage_chance', 0xb6a2ac, .08),
        ('damage_decay', 0xb6a2dc, .11), ('passive_retention', 0xb6a560, .8),
        ('shot_damage_accumulator_cost', 0xb6a928, 7), ('alert_distance', 0xb6aad4, 80),
        ('unresolved_status_multiplier', 0xb6a4dc, .65),
        ('wander_radius', 0xb6aa3c, 40), ('wander_arrival', 0xb6a864, 3),
        ('wander_force', 0xb6a480, .5), ('wander_stuck_speed_squared', 0xb6a2cc, .1),
        ('path_retention', 0xb6a50c, .7), ('overkill_boundary', 0xb6aef8, -25),
        ('full_circle', 0xb6a914, 6.283185307179586),
    ]:
        value, = struct.unpack('<f', read(address, 4))
        assert abs(value - expected) < 1e-5, (name, value, expected)
        manifest['float_constants'][name] = {'address': hex(address), 'value': value}
    manifest['shared_evidence'] = []
    for relative in [
        'docs/reports/isaac-enemy-port/hardy/source/fire_projectiles.asm',
        'docs/reports/isaac-enemy-port/adult-leech/source/projectile_params.asm',
        'docs/reports/isaac-enemy-port/adult-leech/source/falling_pathfinder.asm',
        'reference/isaac-repentance-1.7.9b/loose/resources/scripts/enums.lua',
        'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3/entities2.xml',
    ]:
        manifest['shared_evidence'].append({'path': relative, 'sha256': sha((ROOT / relative).read_bytes())})
    save(OUT / 'helpers-manifest.json', (json.dumps(manifest, indent=2) + '\n').encode())
    print(json.dumps({'pass': True, 'windows': len(windows), 'check': args.check}))


if __name__ == '__main__':
    main()
