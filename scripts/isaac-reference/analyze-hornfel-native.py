#!/usr/bin/env python3
"""Preserve bounded, addressable evidence from the verified local 1.7.9b binary.

This is disassembly with explicitly scoped interpretation, not recovered source.
No installed game files are changed. Requires pefile and capstone.
"""
import hashlib
import json
import re
import struct
from pathlib import Path
import capstone
import pefile

ROOT = Path(__file__).resolve().parents[2]
EXE = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
CODE = ROOT / 'reference/isaac-mechanics-study/code/TeamREPENTOGON__REPENTOGON/348e5d0ea277760fc87af420d88e2c7909c9167e'
OUT = ROOT / 'docs/reports/isaac-enemy-port/hornfel/native'
BASELINE = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'


def main():
    data = EXE.read_bytes()
    assert hashlib.sha256(data).hexdigest() == BASELINE, 'Executable is not the preserved 1.7.9b baseline'
    pe = pefile.PE(data=data)
    base = pe.OPTIONAL_HEADER.ImageBase
    anchors = {}
    unmatched = {}
    methods = [('EntityNPC', 'Entity_NPC', name) for name in
               ['Hornfel_UpdateAI', 'Hornfel_UpdateFrame', 'GetPlayerTarget', 'FireProjectiles', 'PlaySound']]
    methods += [('Game', 'Game', 'Spawn'), ('WeightedOutcomePicker', 'WeightedOutcomePicker', 'PickOutcome')]
    for file, owner, name in methods:
        signature_path = CODE / f'libzhl/functions/{file}.zhl'
        source = signature_path.read_text()
        match = re.search(r'"([0-9a-f?]+)":\s*[^;\n]*' + owner + '::' + name + r'\(', source)
        assert match, name
        signature = match.group(1)
        pattern = b''.join(b'.' if pair == '??' else re.escape(bytes.fromhex(pair)) for pair in re.findall('..', signature))
        hits = list(re.finditer(pattern, data, re.S))
        if len(hits) != 1:
            assert not name.startswith('Hornfel_'), (name, len(hits))
            unmatched[name] = {'matches': len(hits), 'signature': signature}
            continue
        address = base + pe.get_rva_from_offset(hits[0].start())
        anchors[name] = {'va': hex(address), 'signature': signature, 'file_offset': hits[0].start(),
                         'declaration': owner + '::' + name, 'source': str(signature_path.relative_to(ROOT)),
                         'source_sha256': hashlib.sha256(signature_path.read_bytes()).hexdigest()}
    assert anchors['Hornfel_UpdateAI']['va'] == '0x4a6280'
    assert anchors['Hornfel_UpdateFrame']['va'] == '0x4a8000'
    labels = {int(v['va'], 16): k for k, v in anchors.items()}
    windows = [
        ('helper_4a4dc0', 0x4a4dc0, 0x4a4e6f),
        ('helper_4a4e70', 0x4a4e70, 0x4a5113),
        ('helper_4a5120', 0x4a5120, 0x4a5a04),
        ('helper_4a5a10', 0x4a5a10, 0x4a5c40),
        ('helper_4a5c40', 0x4a5c40, 0x4a6080),
        ('helper_4a6080', 0x4a6080, 0x4a6280),
        ('hornfel_update_ai', 0x4a6280, 0x4a7fb3),
        ('hornfel_update_frame', 0x4a8000, 0x4a8142),
        ('spawn_wrapper', 0x422e20, 0x422e48),
        ('spawn_target_prefix', 0x6d0ca0, 0x6d0d20),
        ('lua_health_properties', 0x8054c3, 0x8054e1),
        ('entity_get_hit_points', 0x412220, 0x412227),
        ('entity_set_hit_points', 0x427350, 0x427364),
        ('entity_get_max_hit_points', 0x412210, 0x412217),
        ('entity_set_max_hit_points', 0x427370, 0x427384),
    ]
    OUT.mkdir(parents=True, exist_ok=True)
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True
    records = []
    for name, start, end in windows:
        raw = pe.get_data(start - base, end - start)
        lines = ['; Installed Repentance 1.7.9b. Address-bounded linear decode; helper names are unresolved.',
                 '; Literal float/string comments describe bytes, not inferred native field meanings.']
        calls = set()
        for instruction in decoder.disasm(raw, start):
            notes = []
            for operand in instruction.operands:
                if operand.type == capstone.x86.X86_OP_IMM:
                    address = operand.imm
                    if instruction.mnemonic == 'call':
                        calls.add(hex(address))
                        if address in labels:
                            notes.append(labels[address])
                    if base <= address < base + pe.OPTIONAL_HEADER.SizeOfImage:
                        value = pe.get_data(address - base, 100).split(b'\0', 1)[0]
                        if len(value) >= 3 and all(32 <= byte < 127 for byte in value):
                            notes.append('string=' + repr(value.decode('ascii')))
                if operand.type == capstone.x86.X86_OP_MEM and not operand.mem.base and not operand.mem.index and operand.mem.disp >= base:
                    value = pe.get_data(operand.mem.disp - base, 4)
                    if len(value) == 4:
                        notes.append(f'[{operand.mem.disp:#x}] f32={struct.unpack("<f", value)[0]:.9g}')
            lines.append(f'{instruction.address:08x} {instruction.mnemonic} {instruction.op_str}' + (' ; ' + '; '.join(notes) if notes else ''))
        path = OUT / (name + '.asm')
        path.write_text('\n'.join(lines) + '\n')
        records.append({'name': name, 'start': hex(start), 'end_exclusive': hex(end),
                        'raw_sha256': hashlib.sha256(raw).hexdigest(), 'artifact': str(path.relative_to(ROOT)),
                        'artifact_sha256': hashlib.sha256(path.read_bytes()).hexdigest(), 'calls': sorted(calls)})
    table = struct.unpack('<17I', pe.get_data(0x4a7fb4 - base, 68))
    report = {'baseline': 'Repentance 1.7.9b', 'exe': str(EXE), 'exe_sha256': BASELINE,
              'image_base': hex(base), 'signature_source': str((CODE / 'libzhl/functions/EntityNPC.zhl').relative_to(ROOT)),
              'anchors': anchors, 'unmatched_optional_signatures': unmatched,
              'windows': records, 'ai_state_jump_table_va': '0x4a7fb4',
              'ai_states': {str(n): hex(address) for n, address in enumerate(table)},
              'caveats': ['The matched signatures identify methods, not the field offsets in newer API headers.',
                          'Installed state offset is 0xab4 and the cart reference is 0x32c in these methods; newer saved headers use 0xb64 and 0x3d4.',
                          'Helper windows are call-target/prologue-bounded candidates; semantic names need separate review. spawn_target_prefix is deliberately not a full function.',
                          'Timing values are native ticks or animation frames, not directly DeathWard seconds.',
                          'AI jump table is stored separately and is not decoded as executable instructions.']}
    (OUT / 'manifest.json').write_text(json.dumps(report, indent=2) + '\n')
    print(f'Verified {len(anchors)} unique method signatures; preserved {len(records)} code windows and 17 state entries')


if __name__ == '__main__':
    main()
