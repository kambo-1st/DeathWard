#!/usr/bin/env python3
"""Reproduce the installed Leper evidence, including the flesh controller tail."""
import argparse
import hashlib
import json
import struct
from pathlib import Path
import capstone
import pefile

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/leper/source'
EXE = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    sha = lambda data: hashlib.sha256(data).hexdigest()
    raw = EXE.read_bytes()
    assert sha(raw) == SHA
    pe = pefile.PE(data=raw, fast_load=True)
    read = lambda address, length: pe.get_data(address-pe.OPTIONAL_HEADER.ImageBase, length)
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

    def save(path, data):
        if args.check or path.exists():
            assert path.read_bytes() == data, path
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)

    index = read(0x69abc0+310-10, 1)[0]
    case, = struct.unpack('<I', read(0x69a7f8+index*4, 4))
    assert index == 127 and case == 0x699edb
    assert any(i.mnemonic == 'call' and i.op_str == '0x5346d0' for i in decoder.disasm(read(case, 20), case))
    manifest = {'baseline': 'Installed Repentance 1.7.9b', 'executable_sha256': SHA,
                'dispatch': {'type': 310, 'index': index, 'case': hex(case), 'parent': '0x5346d0', 'variant1': '0x5351f0'},
                'windows': [], 'constants': {}}
    for name, start, end, complete in [
        ('parent', 0x5346d0, 0x5351ea, True),
        ('flesh', 0x5351f0, 0x5358df, True),
        ('damage-reaction', 0x68b970, 0x68c801, True),
        ('normal-ai-call', 0x69ce57, 0x69ce99, False),
        ('base-update-call', 0x69f855, 0x69f919, False),
        ('friction-integration', 0x686406, 0x686497, False),
        ('queued-damage-subtraction', 0x686d98, 0x686eb6, False),
    ]:
        blob = read(start, end-start)
        instructions = list(decoder.disasm(blob, start))
        assert instructions and instructions[-1].address+instructions[-1].size == end, name
        data = ('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in instructions)+'\n').encode()
        path = OUT / (name+'.asm')
        save(path, data)
        manifest['windows'].append({'name': name, 'start': hex(start), 'end_exclusive': hex(end),
                                    'complete_function': complete, 'instructions': len(instructions),
                                    'raw_sha256': sha(blob), 'path': str(path.relative_to(ROOT)), 'sha256': sha(data)})
    for name, address, expected in [('flesh_retention', 0xb6a5d8, .95), ('flesh_force', 0xb6a304, .15),
                                    ('prediction_distance_factor', 0xb6a2cc, .1), ('shot_speed', 0xb6a974, 10),
                                    ('parent_overkill', 0xb6aef8, -25), ('blood_minimum', 0xb6a434, .4)]:
        value, = struct.unpack('<f', read(address, 4))
        assert abs(value-expected) < 1e-5
        manifest['constants'][name] = {'address': hex(address), 'value': value}
    manifest['claims'] = [
        {'at': '535231..5353c1;686406..686497', 'meaning': 'Flesh multiplies friction by .95, directly adds .15*(unit target + 2*random unit), then common integration applies friction to the resulting velocity.'},
        {'at': '5353c6..535509', 'meaning': 'InitSeed chooses six Idle shapes and flip. State0 becomes4 and sets kill-on-player-contact byte16c.'},
        {'at': '53555a..535745', 'meaning': 'Six-tick effect111 emissions are cosmetic, not hostile shots.'},
        {'at': '535764..5358cc', 'meaning': 'Dead flesh fires mode0 once: target position plus target velocity times .1*native distance; normalized planar speed10. Writes at params+2c..54 are color fields, not falling modifiers.'},
        {'at': '534c8b..535010', 'meaning': 'Parent predicts HP minus pending damage. Loop uses (3-subtype)*maxHP/(4-subtype), increments subtype, emits flesh; only after the loop invokes Morph. The reaction helper68b970 is not a config reset.'},
    ]
    manifest['shared_evidence'] = []
    for relative in ['docs/reports/isaac-enemy-port/nest/source/player_collision.asm',
                     'docs/reports/isaac-enemy-port/nest/source/kill.asm',
                     'docs/reports/isaac-enemy-port/tainted_pooter/source/projectile_params_defaults.asm',
                     'docs/reports/isaac-enemy-port/tainted_pooter/source/params_physics_and_damage.asm',
                     'docs/reports/isaac-enemy-port/gaper/source/morph.asm']:
        manifest['shared_evidence'].append({'path': relative, 'sha256': sha((ROOT/relative).read_bytes())})
    manifest['preflight_corrections'] = [
        'controller-preflight also contains unrelated function5358e0; use the bounded parent/flesh functions.',
        'configuration-preflight is a partial damage reaction helper, not NPC configuration.',
        'damage-apply-preflight starts misaligned in a special damage branch; it is not evidence of general damage order.',
        'Parent multiple-hit/update/morph ordering still requires a runtime contract before implementation.'
    ]
    save(OUT/'manifest.json', (json.dumps(manifest, indent=2)+'\n').encode())
    print(json.dumps({'pass': True, 'check': args.check, 'windows': len(manifest['windows'])}))


if __name__ == '__main__':
    main()
