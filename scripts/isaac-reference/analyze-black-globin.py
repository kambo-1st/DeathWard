#!/usr/bin/env python3
"""Pin complete installed Black Globin controllers, including out-of-order tails."""
import argparse
import hashlib
import json
import struct
from pathlib import Path
import capstone
import pefile

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/black-globin/source'
INSTALL = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth')
EXE_SHA = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--check', action='store_true')
    args = ap.parse_args()
    sha = lambda data: hashlib.sha256(data).hexdigest()
    raw = (INSTALL / 'isaac-ng.exe').read_bytes()
    assert sha(raw) == EXE_SHA
    pe = pefile.PE(data=raw, fast_load=True)
    read = lambda address, length: pe.get_data(address - pe.OPTIONAL_HEADER.ImageBase, length)
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

    def save(path, data):
        if args.check or path.exists():
            assert path.read_bytes() == data, path
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)

    manifest = {'baseline': 'Installed Repentance 1.7.9b', 'executable_sha256': EXE_SHA,
                'scope': 'Ordinary hostile subtype zero; shared controllers do not imply shared behavior.',
                'dispatch': [], 'windows': [], 'constants': {}}
    for type_id, wanted_index, controller in [(278, 11, 0x4fc330), (279, 18, 0x500140), (280, 1, 0x4f8e40)]:
        index = read(0x69abc0 + type_id - 10, 1)[0]
        case, = struct.unpack('<I', read(0x69a7f8 + index * 4, 4))
        assert index == wanted_index
        assert any(i.mnemonic == 'call' and i.op_str == hex(controller)
                   for i in decoder.disasm(read(case, 20), case))
        manifest['dispatch'].append({'type': type_id, 'index': index, 'case': hex(case), 'controller': hex(controller)})
    for name, start, end in [('parent', 0x4fc330, 0x4fd0b5),
                             ('head-complete', 0x500140, 0x500f98),
                             ('body-complete', 0x4f8e40, 0x4f9a6e),
                             ('throw-spider', 0x6994f0, 0x69972c)]:
        blob = read(start, end - start)
        instructions = list(decoder.disasm(blob, start))
        assert instructions[-1].address + instructions[-1].size == end
        data = ('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in instructions) + '\n').encode()
        path = OUT / f'{name}.asm'
        save(path, data)
        manifest['windows'].append({'name': name, 'start': hex(start), 'end_exclusive': hex(end),
                                    'instructions': len(instructions), 'raw_sha256': sha(blob),
                                    'path': str(path.relative_to(ROOT)), 'sha256': sha(data)})
    for name, address, expected in [('strict_damage_threshold', 0xb6a8f4, 5),
                                    ('target_fraction_and_body_friction', 0xb6a53c, .75),
                                    ('parent_path_force', 0xb6a4c4, .6),
                                    ('dense_creep_interval', 0xb6a98c, 12),
                                    ('sparse_creep_interval', 0xb6a9e8, 24),
                                    ('extra_creep_speed_squared', 0xb6a95c, 9)]:
        value, = struct.unpack('<f', read(address, 4))
        assert abs(value - expected) < 1e-5
        manifest['constants'][name] = {'address': hex(address), 'value': value}
    assert read(0xb42efc, 32).split(b'\0')[0] == b'Spiders'
    manifest['body_overlay'] = {'address': '0xb42efc', 'animation': 'Spiders', 'frames': 8}
    manifest['claims'] = [
        {'window': 'parent', 'address': '0x4fc57a..0x4fc62e',
         'meaning': 'Poll last emitted HP minus current HP; strictly greater than 5 emits once and updates baseline. Throw toward 75% of player delta from height -30.'},
        {'window': 'parent', 'address': '0x4fcbce..0x4fd097',
         'meaning': 'Death releases independent body280 at origin and head279 at free position within40; no goo, overkill suppression or separate forced spider.'},
        {'window': 'head-complete', 'address': '0x5003b7..0x500407',
         'meaning': 'Type279 pursues using .5 path force and grid cost900; bypasses ordinary Brain cardinal wandering/charge.'},
        {'window': 'head-complete', 'address': '0x500dcd..0x500f98',
         'meaning': 'Common red-creep trail uses12/24 interval at room count5, extra halfway emission at speed squared>9.'},
        {'window': 'body-complete', 'address': '0x4f982f..0x4f9a6e',
         'meaning': 'Initial20..39 cooldown, requires room count<5; ThrowSpider zero target selects nearby free position. Reload90 or180, not uniform. Final tail after RET decrements cooldown.'},
    ]
    manifest['preflight_correction'] = 'head.asm and body.asm are incomplete historical first-return windows. Use head-complete.asm and body-complete.asm.'
    save(OUT / 'manifest.json', (json.dumps(manifest, indent=2) + '\n').encode())
    print(json.dumps({'pass': True, 'check': args.check, 'windows': len(manifest['windows']), 'scope': 'source evidence; not runtime acceptance'}))

if __name__ == '__main__':
    main()
