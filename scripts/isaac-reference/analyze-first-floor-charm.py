#!/usr/bin/env python3
"""Preserve installed 1.7.9b Charm contracts; this is not runtime acceptance."""
import argparse
import hashlib
import json
import struct
from pathlib import Path

import capstone
import pefile

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/first-floor-batch1/charm/source'
EXE = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
BASELINE = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'

# Every endpoint is an instruction boundary. Full small functions are retained
# where a short excerpt would omit a relevant return or alternate branch.
WINDOWS = [
    ('add_charmed', 0x685510, 0x6857c2),
    ('lua_registration', 0x8053dd, 0x8053e7),
    ('expiry', 0x686815, 0x686882),
    ('get_player_target', 0x695680, 0x695a26),
    ('target_candidates', 0x6d90b0, 0x6d92a3),
    ('can_target', 0x681840, 0x68187a),
    ('source_poll', 0x684790, 0x6847db),
    ('can_shut_doors', 0x68f550, 0x68f56f),
    ('projectile_owner_flags', 0x6a179a, 0x6a17dd),
    ('projectile_collision', 0x6375e0, 0x6385dc),
    ('npc_friendly_contact_gate', 0x6a4e1e, 0x6a4e71),
    ('npc_contact_damage', 0x6a606f, 0x6a6200),
    ('contact_cache_reset', 0x6a02d5, 0x6a02f2),
    ('contact_cache_clear', 0x4d1fd0, 0x4d2040),
    ('contact_log', 0x68f440, 0x68f457),
    ('contact_log_thunk', 0x9ec394, 0x9ec39a),
    ('entity_ref', 0x4229a0, 0x422abb),
    ('player_damage_friendly_gate', 0x73cb0d, 0x73cb4e),
]

FINDINGS = [
    dict(id='duration', evidence=['add_charmed', 'lua_registration', 'expiry'],
         contract='The registered AddCharmed function is 685510. Positive adjusted duration assigns max(old timer21c, new duration), without the additive120/150-frame status cap. It sets CHARM0x100. Expiry decrements21c, clears CHARM and clears cached target31c. Existing FRIENDLY0x20000000 makes application return immediately.'),
    dict(id='permanent', evidence=['add_charmed', 'can_shut_doors'],
         contract='Negative adjusted duration sets CHARM|FRIENDLY0x20000100 and zeroes timer21c; it does not use abs(duration). Eligible NPCs are registered in the room persistent entity collection. CanShutDoors tests the ordinary door predicate and excludes FRIENDLY, not temporary CHARM. Transfer serialization and floor lifetime still need separate review.'),
    dict(id='targeting', evidence=['get_player_target', 'target_candidates', 'can_target', 'source_poll'],
         contract='For ordinary CHARM actors, GetPlayerTarget polls every15 global updates staggered by entity index, or whenever cached target31c is null. It searches within5000 native units. Candidate selection excludes self/common-parent bodies, very recent births (age<=1), dead/removed or unsuitable collision classes, FRIENDLY and NO_TARGET, plus explicit type exceptions. It minimizes planar distance squared plus160000 for a CHARM candidate; another temporarily charmed NPC is penalized, not categorically excluded. No LOS test occurs in this selector. Without a candidate it uses the existing player/decoy/retaliation fallback, ultimately the first player. Source poll684790 itself respects Freeze and the global stopping condition; do not replace it with an unconditional timer.'),
    dict(id='projectile_flags', evidence=['projectile_owner_flags', 'projectile_collision'],
         contract='Factory6a179a maps owner CHARM to HIT_ENEMIES0x80 and independently maps FRIENDLY to CANT_HIT_PLAYER0x80000000. Projectile6378a0 skips the player for CANT_HIT_PLAYER. The NPC branch skips FRIENDLY targets when CANT_HIT_PLAYER is set; HIT_ENEMIES permits ordinary NPC targets. The parent identity check63800b prevents hitting the shooter. Other native special types/flags have additional branches.'),
    dict(id='projectile_npc_damage', evidence=['projectile_collision'],
         contract='For ordinary projectile variants,63848c loads projectile CollisionDamage2e0 and adds5 native HP before NPC TakeDamage, with damage flags0 and countdown30. Variant8 has a separate fixed35-HP branch. This is distinct from player damage. Do not reuse DeathWard player-target shot damage or convert an NPC shot into a player AttackSpec. Exact factory defaults, unit conversion, owner-death ancestry lifetime and companion incoming scaling remain integration work.'),
    dict(id='contact', evidence=['npc_contact_damage', 'contact_cache_reset', 'contact_cache_clear', 'contact_log', 'contact_log_thunk'],
         contract='Ordinary active NPC contact can damage when CHARM differs, or when the other body is the cached target31c/retaliation targete88. Positive source contact damage is required. A per-source entity set deduplicates hits and is cleared by the staggered3-update source poll. Damage is ln((sourceMaxHP+110)/100)*33 in native HP. For a FRIENDLY recipient it becomes min(damage*.25,3.5). The native log wrapper resolves to _libm_sse2_log_precise. Existing DeathWard companion damage/cadence must not be assumed to implement this formula.'),
    dict(id='player_contact', evidence=['npc_friendly_contact_gate', 'entity_ref', 'player_damage_friendly_gate'],
         contract='The reviewed NPC collision gate exempts FRIENDLY bodies from player/familiar contact. EntityRef snapshots CHARM as bit1 and FRIENDLY as bit2. Player TakeDamage73cb34 rejects bit2, not bit1. These paths do not establish blanket player safety for temporary CHARM. Ordinary player collision, item-specific protection and producer attribution require integration tests; static inspection here is not an Isaac gameplay recording.'),
]


def sha(data):
    return hashlib.sha256(data).hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    raw = EXE.read_bytes()
    assert sha(raw) == BASELINE, 'Installed executable does not match the reviewed baseline'
    pe = pefile.PE(data=raw)
    base = pe.OPTIONAL_HEADER.ImageBase
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    result = dict(
        baseline='Installed Repentance 1.7.9b', executable_sha256=BASELINE,
        scope=['10.0.0', '10.1.0', '11.0.0', '11.1.0', '12.0.0'],
        status='source_review_only', runtime_implemented=False,
        windows=[], constants=[], imports=[], referenced_evidence=[], findings=FINDINGS,
        supplementary_api=[
            dict(url='https://wofsauge.github.io/IsaacDocs/rep/Entity.html#addcharmed',
                 note='Documents duration in frames and -1 permanent room-following. Current API documentation is supplementary; installed binary defines this baseline. Its general friendly wording is not a substitute for collision/flag review.'),
            dict(url='https://wofsauge.github.io/IsaacDocs/rep/enums/ProjectileFlags.html',
                 note='Names HIT_ENEMIES as1<<7 and CANT_HIT_PLAYER as1<<31; independently checked in native factory and collision paths.')],
        open_work=[
            'Implement temporary Charm and permanent conversion as distinct states for these five only. No new roster entries or blanket friendly toggle.',
            'Review permanent room/floor transfer, restoration/removal and native retaliation ownership before claiming full Charm support.',
            'Resolve target-aware Gaper pursuit, Horf acquisition/Shoot aim, Fear/Shrink evasion and Confusion precedence. Headless wandering must remain wandering.',
            'Preserve shot affiliation when emitted/selected, native NPC projectile damage and parent exclusions. Keep player item builds out of NPC projectiles.',
            'Review NPC damage/retaliation and implement source contact cadence with bounded queue admission, correct HP conversion and recipient scaling.',
            'Test expiry/reapplication, Freeze/Slow, null/dead targets, morphs, room clear/storage/transfer, projectile lifetime and simultaneous status changes at30/60/120Hz.',
            'Validate external configuration, native Original-style cues, mixed-room readability, balance and rendered performance. WASM remains skipped.'
        ])
    if not args.check:
        assert not (OUT / 'manifest.json').exists(), 'Do not overwrite preserved source evidence'
        OUT.mkdir(parents=True, exist_ok=True)
    texts = {}
    for name, start, end in WINDOWS:
        data = pe.get_data(start - base, end - start)
        instructions = list(md.disasm(data, start))
        assert sum(i.size for i in instructions) == len(data), (name, 'incomplete instruction window')
        body = ''.join(f'{i.address:08x} {i.mnemonic} {i.op_str}\n' for i in instructions)
        texts[name] = body
        path = OUT / (name + '.asm')
        if args.check:
            assert path.read_text() == body, path
        else:
            path.write_text(body)
        result['windows'].append(dict(name=name, path=str(path.relative_to(ROOT)), start=hex(start), end=hex(end),
                                      raw_sha256=sha(data), sha256=sha(body.encode())))
    # Verify the API binding and the distinct flags in the preserved windows.
    assert 'push 0x685510' in texts['lua_registration']
    assert 'or edx, 0x20000100' in texts['add_charmed']
    assert 'cmovl ecx, ebx' in texts['add_charmed']
    assert 'or dword ptr [esi + 0x388], 0x80\n' in texts['projectile_owner_flags']
    assert 'or dword ptr [esi + 0x388], 0x80000000\n' in texts['projectile_owner_flags']
    assert 'addss xmm0, dword ptr [0xb6a8f4]' in texts['projectile_collision']
    for name, address, expected in [
        ('target_range', 0xb6ad20, 5000), ('charmed_target_squared_penalty', 0xb6ad88, 160000),
        ('contact_hp_offset', 0xb6ab10, 110), ('contact_hp_divisor', 0xb6aafc, 100),
        ('contact_log_gain', 0xb6aa1c, 33), ('friendly_contact_scale', 0xb6a38c, .25),
        ('friendly_contact_cap', 0xb6a8a0, 3.5), ('ordinary_projectile_npc_bonus', 0xb6a8f4, 5),
    ]:
        data = pe.get_data(address - base, 4)
        value = struct.unpack('<f', data)[0]
        assert value == expected, (name, value)
        result['constants'].append(dict(name=name, address=hex(address), bytes=data.hex(), value=value))
    for module in pe.DIRECTORY_ENTRY_IMPORT:
        for imported in module.imports:
            if imported.address == 0xa06548:
                assert imported.name == b'_libm_sse2_log_precise'
                result['imports'].append(dict(address=hex(imported.address), name=imported.name.decode(), dll=module.dll.decode()))
    assert len(result['imports']) == 1
    for relative in ['first-floor-batch1/statuses/source/manifest.json', 'first-floor-batch1/shrink/source/manifest.json',
                     'headless/source/controller.asm', 'chubber/source/npc_collision.asm']:
        path = ROOT / 'docs/reports/isaac-enemy-port' / relative
        result['referenced_evidence'].append(dict(path=str(path.relative_to(ROOT)), sha256=sha(path.read_bytes())))
    path = OUT / 'manifest.json'
    if args.check:
        assert json.loads(path.read_text()) == result
    else:
        path.write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(dict(result='pass', mode='check' if args.check else 'preserved', windows=len(WINDOWS),
                          runtime_implemented=False, newly_completed_records=0)))


if __name__ == '__main__':
    main()
