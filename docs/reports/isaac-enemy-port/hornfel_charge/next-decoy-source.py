"""Read-only bounded evidence for the next Hornfel decoy increment.

Run from the repository root with pefile/capstone installed. Output is separate
from all previous immutable reports. This does not implement a decoy.
"""
from pathlib import Path
import hashlib
import json
import re
import struct

import capstone
import pefile

ROOT = Path.cwd()
OUT = Path(__file__).resolve().parent / 'next-decoy-native'
EXE = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
CODE = ROOT / 'reference/isaac-mechanics-study/code/TeamREPENTOGON__REPENTOGON/348e5d0ea277760fc87af420d88e2c7909c9167e/libzhl/functions'
BASELINE = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'


def sha(data):
    return hashlib.sha256(data).hexdigest()


def main():
    assert not OUT.exists(), 'Do not overwrite preserved evidence'
    data = EXE.read_bytes()
    assert sha(data) == BASELINE
    pe = pefile.PE(data=data)
    base = pe.OPTIONAL_HEADER.ImageBase
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

    def matches(pattern):
        raw = b''.join(b'.' if p == '??' else re.escape(bytes.fromhex(p)) for p in re.findall('..', pattern))
        return [base + pe.get_rva_from_offset(m.start()) for m in re.finditer(raw, data, re.S)]

    entity = (CODE / 'Entity.zhl').read_text()
    pattern = re.search(r'"([0-9a-f?]+)":\s*bool TakeDamage\(', entity)[1]
    assert matches(pattern) == [0x684bb0]
    assert matches('568bf1817e??62030000') == [0x68ff80]
    assert pe.get_data(0x8604e9-base, 5) == bytes.fromhex('8b01ff6020')
    table = struct.unpack('<12I', pe.get_data(0xb49398-base, 48))
    assert table[8] == 0x6ac370 and table[10] == 0x68ff80
    assert pe.get_data(0x805653-base, 10) == bytes.fromhex('68e9048600682819b500')
    assert pe.get_data(0x80a081-base, 10) == bytes.fromhex('6850176d0068444eb500')
    assert pe.get_data(0xb51928-base, 11) == b'TakeDamage\0'
    assert pe.get_data(0xb54e44-base, 11) == b'BombDamage\0'
    game = (CODE / 'Game.zhl').read_text()
    bomb_pattern = re.search(r'"([0-9a-f?]+)":\s*[^;\n]*Game::BombDamage\(', game)[1]
    # The newer prologue does not match; the installed name/function pairing does.
    assert matches(bomb_pattern) == []

    OUT.mkdir()
    windows = [
        ('take_damage_registration', 0x805653, 0x80565d),
        ('take_damage_virtual_thunk', 0x8604e9, 0x8604ee),
        ('npc_remove_prefix', 0x68ff80, 0x68ffb0),
        ('npc_take_damage_forwarding', 0x6ac370, 0x6ac39f),
        ('base_take_damage', 0x684bb0, 0x685009),
        ('decoy_damage_queue', 0x4a65d0, 0x4a66da),
        ('decoy_destruction', 0x4a7af8, 0x4a7c82),
        ('bomb_damage_registration', 0x80a081, 0x80a08b),
    ]
    saved = []
    for name, start, end in windows:
        raw = pe.get_data(start-base, end-start)
        text = '; Repentance1.7.9b bounded native evidence; names are interpretive.\n'
        text += '\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in decoder.disasm(raw, start)) + '\n'
        path = OUT / (name+'.asm')
        path.write_text(text)
        saved.append({'path': str(path.relative_to(ROOT)), 'start': hex(start), 'end_exclusive': hex(end), 'raw_sha256': sha(raw)})
    report = {
        'status': 'source review for next increment; no decoy runtime implementation',
        'baseline': 'Repentance1.7.9b', 'exe_sha256': BASELINE,
        'anchors': {
            'base_take_damage_unique_signature': {'address': '0x684bb0', 'pattern': pattern},
            'npc_remove_unique_signature': {'address': '0x68ff80', 'pattern': '568bf1817e??62030000'},
            'npc_vtable': {'address': '0xb49398', 'take_damage_slot': '0x20', 'take_damage': '0x6ac370', 'remove_slot': '0x28', 'remove': '0x68ff80', 'entries': [hex(n) for n in table]},
            'native_take_damage_api': {'registration': '0x805653', 'thunk': '0x8604e9', 'name': '0xb51928'},
            'native_bomb_damage_api': {'registration': '0x80a081', 'function': '0x6d1750', 'name': '0xb54e44', 'newer_prologue_matches': 0},
        },
        'findings': [
            'Native TakeDamage API thunk dispatches virtual slot0x20. Independently matched NPC Remove identifies the NPC table; its TakeDamage forwards all damage/flags/source/countdown arguments to uniquely matched base TakeDamage0x684bb0.',
            'Base TakeDamage queues a record at actor+8, adds accepted damage to float actor+0x14 and ORs low/high64-bit input damage flags into actor+0x18/+0x1c. This verifies that the decoy branch examines accumulated accepted damage and flags, not raw HP or an unrelated field.',
            'Decoy checks positive accumulated damage, then flag bit4. Pinned API enum names bit4 DAMAGE_EXPLOSION. Otherwise each positive queued amount<=10 subtracts1, or2 on RNG%3==0; amount>10 subtracts2, or3 on that outcome. Queue records stride0x38. Final HP<1.5 sets death, clamping values<1 to1.',
            'Decoy destruction invokes native BombDamage before its six Troll Bomb spawns. At the call: position=decoy position, damage110, radius75, lineCheck=false, source=null, tear flags allzero, damage flags0x1004, damageSource=false. Pinned enum maps0x1004 to EXPLOSION|TNT. The direct blast must not be omitted or replaced by the six later fuses.',
        ],
        'limits': [
            'DamageFlag names come from the pinned public API header; this binary has no matching literal enum-name strings. Numeric flag transport is independently verified in installed code.',
            'Base TakeDamage performs gating, callbacks and other damage scaling before queuing. This is not a complete damage-system reconstruction.',
            'The damage>10 test requires an explicit DeathWard-to-source damage conversion. Player defaults must remain unchanged.',
            'The direct110damage/75radius are native units. Source-specific blast masks, damage conversion and six-bomb launch/fuse physics still need runtime design and tests.',
            'Decoy selection, rail ownership, removal/completion and capacity handling remain unfinished. No enemy completion count changes.'
        ],
        'windows': saved,
        'source_sha256': {str(p.relative_to(ROOT)): sha(p.read_bytes()) for p in [CODE/'Entity.zhl',CODE/'EntityNPC.zhl',CODE/'Game.zhl',CODE/'Global.zhl']},
    }
    (OUT/'review.json').write_text(json.dumps(report, indent=2)+'\n')
    print('Preserved eight bounded decoy/damage windows; fields and direct blast identified. No runtime completion claim.')


if __name__ == '__main__':
    main()
