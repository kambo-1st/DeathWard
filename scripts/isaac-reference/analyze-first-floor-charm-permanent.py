#!/usr/bin/env python3
"""Preserve confirmed permanent-Charm contracts; lifecycle tracing remains open."""
import argparse
import hashlib
import json
from pathlib import Path

import capstone
import pefile

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/first-floor-batch1/charm/source-permanent'
EXE = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
BASELINE = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    sha = lambda data: hashlib.sha256(data).hexdigest()
    raw = EXE.read_bytes()
    assert sha(raw) == BASELINE
    pe = pefile.PE(data=raw)
    base = pe.OPTIONAL_HEADER.ImageBase
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    result = dict(
        executable_sha256=BASELINE,
        status='source_review_in_progress',
        runtime_implemented=False,
        scope=['10.0.0', '10.1.0', '11.0.0', '11.1.0', '12.0.0'],
        windows=[], strings=[], references=[],
        findings=[
            'AddCharmed685510 first checks FRIENDLY and returns without changing an already-friendly actor. Its negative-duration branch sets CHARM|FRIENDLY and clears the temporary counter. Positive reapplication must not turn a permanent ally back into a timed hostile.',
            'Negative conversion checks boss status and active-enemy eligibility before calling416340 on Room+1218. These five ordinary identities pass the reviewed type filter; the dead-state byte16b is rejected when include-dead is false.',
            '416340 is confirmed as persistent registration by its referenced diagnostic string. It removes the actor from the list at+20 using412500, then deduplicates/appends it to the persistent list at+34/count+3c. Registration is capacity-limited; persistence is not implied by the FRIENDLY bit alone.',
            '684b00 is a source-affiliation immunity predicate used at the entry of TakeDamage684bb0. A FRIENDLY NPC rejects player/familiar sources, sources spawned by player/familiar, source type8, EntityRef FRIENDLY bit2 and effect variants accepted by5ed040. Temporary CHARM alone does not enter this immunity branch.',
            'The preserved target-affiliation predicate rejects the player fallback as an attack target for permanent FRIENDLY NPCs, although the position resolver may still return the player. Horf acquisition therefore needs an affiliation check separate from position resolution.',
            'Previously preserved contact logic caps damage received by a FRIENDLY target at min(raw*.25,3.5) native HP. This is contact-specific evidence; it does not establish a blanket incoming-damage reduction for all attacks.'
        ],
        implementation_consequences=[
            'Represent permanent conversion independently of a positive countdown; keep CHARM active for target/projectile policies and FRIENDLY active for room/player/source-affiliation rules.',
            'Do not route converted ordinary enemies through room-limited familiar profiles or their generic invulnerability fallback.',
            'Keep projectile faction snapshots and contact recipient reduction distinct; preserve player immunity even after projectile owners leave or die.',
            'Implement explicit follower retention/transfer only after tracing registry consumption; preserve source-specific attack acquisition and mortality.'
        ],
        unresolved=[
            'Trace persistent-list consumption during ordinary room and floor transitions, removal, capacity and placement. Registration alone does not prove exact transfer or save semantics.',
            'Resolve applicable effect-source classification5ed040 and permanent-ally damage/death hooks beyond the entry immunity check.',
            'Integrate and test conversion, positive reapplication, player/NPC attacks, contact caps, Horf fallback suppression, room completion and follower lifecycle for the same five.',
            'No permanent runtime implementation, new enemy, completed record, player item or WASM validation is claimed by this source checkpoint.'
        ],
    )
    if not args.check:
        assert not (OUT / 'manifest.json').exists()
        OUT.mkdir(parents=True, exist_ok=True)
    for name, start, end in [
        ('friendly_source_immunity', 0x684b00, 0x684bae),
        ('active_enemy_predicate', 0x68cf40, 0x68cfa3),
        ('persistent_registration', 0x416340, 0x4163b7),
        ('entity_list_remove', 0x412500, 0x41257f),
    ]:
        data = pe.get_data(start-base, end-start)
        ins = list(md.disasm(data, start))
        assert sum(i.size for i in ins) == len(data)
        body = ''.join(f'{i.address:08x} {i.mnemonic} {i.op_str}\n' for i in ins)
        path = OUT / (name+'.asm')
        if args.check:
            assert path.read_text() == body
        else:
            path.write_text(body)
        result['windows'].append(dict(path=str(path.relative_to(ROOT)), start=hex(start), end=hex(end),
                                      raw_sha256=sha(data), sha256=sha(body.encode())))
    address = 0xb3f568
    data = pe.get_data(address-base, 180).split(b'\0')[0]
    assert data == b"[warn] Can't add more persistent entities, persistent list is full!\n"
    result['strings'].append(dict(address=hex(address), text=data.decode(), sha256=sha(data)))
    for relative in [
        'docs/reports/isaac-enemy-port/first-floor-batch1/charm/source/add_charmed.asm',
        'docs/reports/isaac-enemy-port/first-floor-batch1/charm/source/npc_contact_damage.asm',
        'docs/reports/isaac-enemy-port/first-floor-batch1/charm/source-runtime/target_affiliation.asm',
    ]:
        result['references'].append(dict(path=relative, sha256=sha((ROOT/relative).read_bytes())))
    path = OUT / 'manifest.json'
    if args.check:
        assert json.loads(path.read_text()) == result
    else:
        path.write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps(dict(result='pass', windows=len(result['windows']),
                          mode='check' if args.check else 'preserved', permanent_runtime=False)))


if __name__ == '__main__':
    main()
