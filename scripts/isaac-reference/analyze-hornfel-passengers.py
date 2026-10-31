#!/usr/bin/env python3
"""Preserve/check Hornfel's installed 1.7.9b passenger-controller evidence.

This is bounded disassembly, not recovered source or an executed-game trace.
Generation refuses to replace an existing report. --check never writes files.
"""
import argparse
import hashlib
import json
import re
import struct
from pathlib import Path

import capstone
import pefile

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/hornfel_passenger_review/native'
EXE = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
BASELINE = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
DECL = ROOT / ('reference/isaac-mechanics-study/code/TeamREPENTOGON__REPENTOGON/'
               '348e5d0ea277760fc87af420d88e2c7909c9167e/libzhl/functions/EntityEffect.zhl')
WINDOWS = [
    ('effect_constructor', 0x5b7820, 0x5b7882),
    ('effect_dispatch', 0x5be281, 0x5be2b8),
    ('effect_152_case', 0x5c3090, 0x5c30a0),
    ('effect_timer_epilogue', 0x5e9122, 0x5e9168),
    ('effect_timer_api', 0x806fe1, 0x806ff9),
    ('passenger_controller', 0x4a9240, 0x4a9678),
    ('room_clear_cleanup', 0x4a48b0, 0x4a4be5),
    ('door_picker', 0x4a8150, 0x4a8335),
    ('door_entry_direction', 0x4a8340, 0x4a8495),
    ('door_reservation', 0x4a8710, 0x4a8795),
    ('spawn_carrier', 0x68eff0, 0x68f0c1),
    ('cart_ai', 0x4bba40, 0x4bc03c),
    ('cart_break', 0x4bc040, 0x4bc1d2),
    ('cart_attachment', 0x4bc2d0, 0x4bc373),
    ('alive_boss_count', 0x448020, 0x448036),
    ('room_clear_getter', 0x427700, 0x427709),
    ('spawner_type_getter', 0x422ac0, 0x422ac4),
    ('fireplace_ai_preflight', 0x6a7ae0, 0x6a8a39),
    ('movable_tnt_ai_preflight', 0x6acb80, 0x6ad715),
]
PASSENGERS = [(823, 0x69a0eb, 0x4eae80), (820, 0x69a0d3, 0x4e94a0),
              (827, 0x69a0bb, 0x4e82e0), (227, 0x699d4f, 0x525830),
              (87, 0x699a1c, 0x508ef0), (33, 0x699cd7, 0x6a7ae0),
              (292, 0x699df7, 0x6acb80)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    check = parser.parse_args().check
    data = EXE.read_bytes()
    assert hashlib.sha256(data).hexdigest() == BASELINE
    pe = pefile.PE(data=data)
    base = pe.OPTIONAL_HEADER.ImageBase
    read = lambda address, size: pe.get_data(address - base, size)
    u32 = lambda address: struct.unpack('<I', read(address, 4))[0]
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

    # A newer declaration names the constructor only after an exact unique match.
    sig = re.search(r'"([0-9a-f?]+)":\s*[^;\n]*Entity_Effect::constructor\(', DECL.read_text())[1]
    pattern = b''.join(b'.' if v == '??' else re.escape(bytes.fromhex(v))
                       for v in re.findall('..', sig))
    hits = list(re.finditer(pattern, data, re.S))
    assert len(hits) == 1
    assert base + pe.get_rva_from_offset(hits[0].start()) == 0x5b7820
    assert read(0x5b782f, 6) == bytes.fromhex('c706f059b400')
    assert u32(0xb459f0 + 12) == 0x5bdf00
    assert u32(0x5e9214 + 4 * (152 - 1)) == 0x5c3090
    case = list(decoder.disasm(read(0x5c3090, 16), 0x5c3090))
    assert (case[1].mnemonic, case[1].op_str) == ('call', '0x4a9240')

    table = []
    for address in (0xb6b0f0, 0xb6b0d0, 0xb6b090):
        table.extend(struct.iter_unpack('<II', read(address, 16)))
    # Seventh pair is constructed with immediate instructions on the stack.
    assert read(0x4a9342, 8) == bytes.fromhex('c744246c24010000')
    assert read(0x4a9356, 8) == bytes.fromhex('c744247000000000')
    table.append((292, 0))
    assert table == [(kind, 0) for kind, _, _ in PASSENGERS]
    manifest = {'baseline': 'Repentance 1.7.9b', 'exe_sha256': BASELINE,
                'constructor_signature': sig,
                'declaration': str(DECL.relative_to(ROOT)),
                'declaration_sha256': hashlib.sha256(DECL.read_bytes()).hexdigest(),
                'effect_vtable': '0xb459f0', 'effect_update': '0x5bdf00',
                'variant_table': '0x5e9214', 'effect_152_case': '0x5c3090',
                'controller': '0x4a9240',
                'payload_table': [{'id': f'{kind}.{variant}.0', 'index': index}
                                  for index, (kind, variant) in enumerate(table)],
                'dispatch': {}, 'api_anchors': {}, 'windows': []}
    windows = list(WINDOWS)
    for kind, expected, ai in PASSENGERS:
        index = read(0x69abc0 + kind - 10, 1)[0]
        address = u32(0x69a7f8 + 4 * index)
        assert address == expected
        case = list(decoder.disasm(read(address, 12), address))
        assert (case[1].mnemonic, case[1].op_str) == ('call', hex(ai))
        manifest['dispatch'][str(kind)] = {'index': index, 'case': hex(address), 'ai': hex(ai)}
        windows.append((f'npc_{kind}_case', address, address + 12))

    for name, address, function in [('IsClear', 0xb5406c, 0x427700),
                                     ('GetAliveBossesCount', 0xb54264, 0x448020),
                                     ('SpawnerType', 0xb50f10, 0x422ac0),
                                     ('Remove', 0xb50174, 0x860511),
                                     ('Kill', 0xb51910, 0x8604fd)]:
        assert read(address, len(name) + 1) == name.encode() + b'\0'
        assert data.count(b'\x68' + struct.pack('<I', function)
                          + b'\x68' + struct.pack('<I', address)) == 1
        manifest['api_anchors'][name] = {'name': hex(address), 'function': hex(function)}
    # Independently bind the virtual offsets used by quiet cart/room cleanup.
    assert read(0x860511, 5) == bytes.fromhex('8b01ff6028')
    assert read(0x8604fd, 5) == bytes.fromhex('8b01ff6024')
    manifest['virtual_dispatch'] = {'Remove': {'slot': 40, 'bytes': '8b01ff6028'},
                                    'Kill': {'slot': 36, 'bytes': '8b01ff6024'}}
    for name, address, field, registration in [('Timeout', 0xb53004, 0x3ac, 0x806fed),
                                               ('LifeSpan', 0xb530c0, 0x3b0, 0x806fe1)]:
        assert read(address, len(name) + 1) == name.encode() + b'\0'
        assert read(registration, 12) == b'\x6a\x01\x68' + struct.pack('<I', field) + b'\x68' + struct.pack('<I', address)
        manifest['api_anchors'][name] = {'name': hex(address), 'field': hex(field), 'registration': hex(registration)}
    assert struct.unpack('<f', read(0xb6ad0c, 4))[0] == 3600

    if not check:
        assert not OUT.exists(), 'Refusing to overwrite preserved source evidence'
        OUT.mkdir(parents=True)
    for name, start, end in windows:
        raw = read(start, end - start)
        text = '; Installed-binary disassembly; field interpretations require the source review.\n'
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
    path = OUT / 'manifest.json'
    if check:
        assert json.loads(path.read_text()) == manifest
    else:
        path.write_text(json.dumps(manifest, indent=2) + '\n')
    print(f'PASS: effect152 dispatch, seven passenger identities/AI targets, seven API anchors, {len(windows)} native windows')


if __name__ == '__main__':
    main()
