#!/usr/bin/env python3
"""Preserve/verify bounded escort evidence from the installed 1.7.9b executable.

This is disassembly, not recovered source. --check never modifies artifacts.
Generation refuses to replace an existing report.
"""
import argparse
import hashlib
import json
import struct
from pathlib import Path
import capstone
import pefile

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/hornfel_escorts/native'
EXE = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
BASELINE = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
WINDOWS = [
    ('npc_ai_dispatch', 0x699730, 0x699784),
    ('fly_dispatch_case', 0x69a0c7, 0x69a0d3),
    ('hornfel_dispatch_case', 0x69a31f, 0x69a32b),
    ('shared_fly_ai', 0x4f4e30, 0x4f6ed0),
    ('hornfel_entry', 0x4a5120, 0x4a5a04),
    ('hornfel_exit', 0x4a5a10, 0x4a5c40),
    ('global_frame_gate', 0x684790, 0x6847d9),
    ('elapsed_frame_gate', 0x6847e0, 0x684852),
    ('add_velocity', 0x422b60, 0x422bcf),
    ('hp_getter', 0x412220, 0x412227),
    ('parent_getter', 0x422c10, 0x422c17),
]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    check = parser.parse_args().check
    data = EXE.read_bytes()
    assert hashlib.sha256(data).hexdigest() == BASELINE
    pe = pefile.PE(data=data)
    base = pe.OPTIONAL_HEADER.ImageBase
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    dispatch = {}
    for kind, expected in [(819, 0x69a0c7), (906, 0x69a31f)]:
        index = pe.get_data(0x69abc0 + kind - 10 - base, 1)[0]
        target = struct.unpack('<I', pe.get_data(0x69a7f8 + 4 * index - base, 4))[0]
        assert target == expected
        dispatch[str(kind)] = {'index': index, 'case': hex(target)}
    manifest = {'baseline': 'Repentance 1.7.9b', 'exe_sha256': BASELINE,
                'dispatch': dispatch, 'windows': []}
    if not check:
        assert not OUT.exists(), 'Refusing to overwrite preserved native evidence'
        OUT.mkdir(parents=True)
    for name, start, end in WINDOWS:
        raw = pe.get_data(start - base, end - start)
        text = '; Bounded installed-binary disassembly; field names require separate verification.\n'
        text += '\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip()
                          for i in decoder.disasm(raw, start)) + '\n'
        path = OUT / (name + '.asm')
        if check:
            assert path.read_text() == text, name
        else:
            path.write_text(text)
        manifest['windows'].append({'path': str(path.relative_to(ROOT)), 'start': hex(start),
                                    'end_exclusive': hex(end), 'raw_sha256': hashlib.sha256(raw).hexdigest(),
                                    'artifact_sha256': hashlib.sha256(text.encode()).hexdigest()})
    for name, address, getter, setter in [('HitPoints', 0xb519e4, 0x412220, 0x427350),
                                          ('Parent', 0xb51b84, 0x422c10, 0x6818e0)]:
        assert pe.get_data(address - base, len(name) + 1) == name.encode() + b'\0'
        assert data.count(b'\x68' + struct.pack('<I', setter) + b'\x68' + struct.pack('<I', getter)
                          + b'\x68' + struct.pack('<I', address)) == 1
    path = OUT / 'manifest.json'
    if check:
        assert json.loads(path.read_text()) == manifest
    else:
        path.write_text(json.dumps(manifest, indent=2) + '\n')
    print('PASS: 819/906 dispatch, HP/Parent API pairings, and', len(WINDOWS), 'escort code windows')


if __name__ == '__main__':
    main()
