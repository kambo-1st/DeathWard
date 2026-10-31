#!/usr/bin/env python3
"""Preserve installed Chubber collision/controller evidence, without artwork."""
import argparse
import hashlib
import json
import struct
from pathlib import Path
import capstone
import pefile

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/chubber/source'
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
              'scope': 'Chubber supplementary evidence; prior Vis checkpoints remain untouched.',
              'windows': [], 'flags': {}, 'vtables': {}}
    for name, start, end in [
        ('returning_controller', 0x519980, 0x519da4),
        ('parent_controller', 0x519dd0, 0x51af94),
        ('npc_collision', 0x6a3970, 0x6a648b),
        ('tear_collision', 0x64dcd0, 0x6500d0),
        ('piercing_obstruction_check', 0x6846e0, 0x684733),
        ('enemy_check', 0x68cf40, 0x68cfa3),
        ('base_damage_window', 0x684bb0, 0x685bff),
    ]:
        blob = read(start, end - start)
        instructions = list(dis.disasm(blob, start))
        assert instructions and instructions[-1].address + instructions[-1].size == end, name
        text = ('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in instructions) + '\n').encode()
        path = OUT / (name + '.asm')
        save(path, text)
        result['windows'].append({'path': str(path.relative_to(ROOT)), 'start': hex(start), 'end': hex(end),
                                  'raw_sha256': sha(blob), 'sha256': sha(text)})
    for name, address, value in [('piercing', 0xbc4be0, 2), ('spectral', 0xbc4cc0, 1)]:
        actual = int.from_bytes(read(address, 16), 'little')
        assert actual == value
        result['flags'][name] = {'address': hex(address), 'value': actual}
    for name, address in [('npc', 0xb49398), ('tear', 0xb46a88)]:
        result['vtables'][name] = {'address': hex(address), 'entries': {
            hex(offset): hex(struct.unpack('<I', read(address+offset, 4))[0])
            for offset in (8, 12, 0x20, 0x24, 0x28, 0x58)}}
    enums = ROOT / 'reference/isaac-repentance-1.7.9b/loose/resources/scripts/enums.lua'
    text = enums.read_text()
    assert 'TEAR_PIERCING = TEARFLAG(1)' in text and 'TEAR_SPECTRAL = TEARFLAG(0)' in text
    result['flag_enum_source'] = {'path': str(enums.relative_to(ROOT)), 'sha256': sha(enums.read_bytes())}
    save(OUT / 'manifest.json', (json.dumps(result, indent=2) + '\n').encode())
    print(json.dumps({'pass': True, 'windows': len(result['windows']), 'check': args.check}))


if __name__ == '__main__':
    main()
