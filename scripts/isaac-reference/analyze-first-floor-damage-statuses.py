#!/usr/bin/env python3
"""Preserve installed 1.7.9b ordinary Poison/Burn application and ticking."""
import argparse
import hashlib
import json
import struct
from pathlib import Path
import capstone
import pefile
ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/first-floor-batch1/damage-statuses/source'
EXE = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
BASELINE = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--check',action='store_true');args=parser.parse_args()
    raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==BASELINE
    pe=pefile.PE(data=raw);base=pe.OPTIONAL_HEADER.ImageBase;md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    windows=[('api_binding',0x8053b5,0x805405),('add_poison',0x6851c0,0x6853f2),('add_burn',0x685ca0,0x685e1a),
        ('source_duration',0x685020,0x68507d),('poison_expiry',0x68678d,0x6867cb),('burn_expiry',0x68694d,0x686982),
        ('periodic_damage',0x687038,0x687201),('empty_entity_ref',0x427290,0x4272f0),('initial_damage',0x681c5f,0x681c73)]
    result=dict(baseline='Installed Repentance 1.7.9b',executable_sha256=BASELINE,windows=[],constants=[],findings=[
        'Entity API registration binds AddPoison to6851c0 and AddBurn to685ca0. Ordinary timers214/22c use positive additive cap120 and negative max(old,abs(duration)). Reapplying positive duration can shorten an extended effect. No-status and boss-immunity/linked routing branches are visible but outside this cohort.',
        'Both applications keep max(oldDamage,newDamage). Fresh native fields278/27c start at2 and expiry resets them to2. Nonpositive supplied damage uses the source ancestor player Damage when available, otherwise2. The caller source is not stored by these native application functions.',
        'New Poison resets238; new Burn resets23c. Active reapplications do not reset those tick phases. Duration decrements and clears the status before the periodic-damage branch. Active phase starts0; oldPhase%20==1 deals damage, then phase increments. Thus hits occur on real updates2,22,42,62,82,102; duration must exceed the hit update.',
        'The periodic branch runs for ordinary NPC types10..999 and is not gated by Freeze or Slow. Poison and Burn have independent duration, phase and damage fields and can both tick on one update.',
        'Both periodic damage calls use DAMAGE_POISON_BURN0x8000, an empty EntityRef constructed by427290, and countdown30. They are not physical flame-contact damage. The existing DeathWard Burning channel is the corresponding shared damage kind.',
        'Duration helper685020 checks a source-player effect78 and multiplies input duration by twice its count. That item-source duration modifier is preserved as evidence but not implemented by this slice.'
    ],adaptations=[
        'Only10.0.0,10.1.0,11.0.0,11.1.0,12.0.0 opt in. damage_status ID poison|burn cap period firstTick minimumDamage exposes120/20/2/6.4; source2HP times existing enemyHP scale3.2 gives6.4. API explicit power is already in DeathWard HP units.',
        'A nonpositive API power snapshots the current resolved player build damage for Player/Ally producers, otherwise the configured floor. No new item is added. Native arbitrary source-ancestor traversal and effect78 duration multiplication remain pending item-system integration.',
        'DeathWard retains explicit producer attribution for item hooks and diagnostics instead of replacing it with native empty EntityRef. The stronger application owns that snapshot; reapplication with weaker/equal power preserves it. Each periodic tick starts an independent bounded event chain; ownership survives producer removal.',
        'Damage enters the existing event pipeline and resolves at the end of the physics step. Same-entity lethal morph, ordinary rewards, fire reactions and room completion use the existing damage path. This does not claim native intra-step callback ordering on unusually long steps.',
        'Queue backpressure retains at most one selected tick per effect and pauses only that effect clock until admission. Selected power/source/position survive reapplication. This is a local bounded-queue policy; ordinary cadence has no delay. Explicit removal stops future ticks but does not cancel already selected damage.',
        'Modal and inactive-room suspension retain durations/phases. Green bubbles and small side flames are original DeathWard cues; Freeze retains body-tint priority while damage-effect side cues continue. No source sprites or full native color-stack API are copied.',
        'Other enemies, linked entities, boss status cooldowns, bleeding, charm/shrink and item-source duration interfaces remain separate work. Player100HP/24damage, expedition structure, Mine and hubs remain unchanged.'
    ],api_reference=dict(url='https://wofsauge.github.io/IsaacDocs/rep/Entity.html#addpoison',
        consulted='2026-10-28',summary='Public API documentation independently describes duration3 for the first hit and20-frame intervals. Installed1.7.9b disassembly above is the baseline authority; later Repentance+ overloads are not applied.'))
    if not args.check:
        assert not (OUT/'manifest.json').exists(),'Do not overwrite preserved evidence';OUT.mkdir(parents=True,exist_ok=True)
    for name,start,end in windows:
        data=pe.get_data(start-base,end-start);instructions=list(md.disasm(data,start))
        assert sum(i.size for i in instructions)==len(data),(name,hex(start+sum(i.size for i in instructions)))
        text=''.join(f'{i.address:08x} {i.mnemonic} {i.op_str}\n' for i in instructions)
        path=OUT/(name+'.asm')
        if args.check:assert path.read_text()==text
        else:path.write_text(text)
        result['windows'].append(dict(path=str(path.relative_to(ROOT)),start=hex(start),end=hex(end),raw_sha256=hashlib.sha256(data).hexdigest(),sha256=hashlib.sha256(path.read_bytes()).hexdigest()))
    data=pe.get_data(0xb6a7b0-base,4);result['constants'].append(dict(name='fallback_damage',address='0xb6a7b0',bytes=data.hex(),value=struct.unpack('<f',data)[0]))
    path=OUT/'manifest.json'
    if args.check:assert json.loads(path.read_text())==result
    else:path.write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps(dict(result='pass',mode='check' if args.check else 'preserved',windows=len(windows))))
if __name__=='__main__':main()
