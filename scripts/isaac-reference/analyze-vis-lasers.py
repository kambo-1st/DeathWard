#!/usr/bin/env python3
"""Pin supplementary Vis laser evidence; never replace the earlier frozen review."""
import argparse
import hashlib
import json
import struct
import xml.etree.ElementTree as ET
from pathlib import Path
import capstone
import pefile

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/vis/laser-source'
EXE = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
EXPECTED = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    sha = lambda data: hashlib.sha256(data).hexdigest()
    raw = EXE.read_bytes()
    assert sha(raw) == EXPECTED
    pe = pefile.PE(data=raw)
    read = lambda address, size: pe.get_data(address - pe.OPTIONAL_HEADER.ImageBase, size)
    dis = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

    def save(path, data):
        if args.check or path.exists():
            assert path.read_bytes() == data, path
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)

    result = {'baseline': 'Installed Repentance 1.7.9b', 'executable_sha256': EXPECTED,
              'scope': 'Supplemental instruction windows; original Vis source/animations remain frozen.',
              'windows': [], 'constants': {}}
    for name, start, end in [
        ('spawn', 0x8c7550, 0x8c765f),
        ('target_eligibility', 0x8c5a90, 0x8c5be9),
        ('update', 0x8cc300, 0x8d0a99),
        ('damage_driver', 0x8cbe80, 0x8cc11a),
        ('apply_damage', 0x8d6600, 0x8d688f),
        ('interval', 0x6847e0, 0x684852),
        ('base_movement_window', 0x686060, 0x68694d),
        ('base_damage_window', 0x684bb0, 0x685bff),
    ]:
        blob = read(start, end - start)
        instructions = list(dis.disasm(blob, start))
        # End windows only on instruction boundaries, never silently truncate.
        assert instructions and instructions[-1].address + instructions[-1].size == end, name
        text = ('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in instructions) + '\n').encode()
        path = OUT / (name + '.asm')
        save(path, text)
        result['windows'].append({'path': str(path.relative_to(ROOT)), 'start': hex(start), 'end': hex(end),
                                  'raw_sha256': sha(blob), 'sha256': sha(text)})
    for name, address, expected in [('hit_interval', 0xb6a7b0, 2), ('fade_scale', 0xb6a5a0, .895)]:
        actual, = struct.unpack('<f', read(address, 4))
        assert abs(actual - expected) < 1e-6
        result['constants'][name] = {'address': hex(address), 'value': actual}
    result['variant1_timeout_uses_fade'] = read(0x8c5968, 1)[0] == 0
    assert result['variant1_timeout_uses_fade']
    xml = ROOT / 'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3/entities2.xml'
    laser = next(e for e in ET.parse(xml).getroot() if e.get('id') == '7' and e.get('variant') == '1'
                 and e.get('subtype', '0') == '0')
    assert laser.get('collisionDamage') == '11' and laser.get('collisionRadius') == '16'
    result['laser_xml'] = {'path': str(xml.relative_to(ROOT)), 'sha256': sha(xml.read_bytes()),
                           'id': '7.1.0', 'collisionDamage': 11, 'collisionRadius': 16}
    save(OUT / 'manifest.json', (json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({'pass': True, 'windows': len(result['windows']), 'check': args.check}))


if __name__ == '__main__':
    main()
