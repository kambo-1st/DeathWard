#!/usr/bin/env python3
"""Preserve pinned 1.7.9b Shrink duration, size transition and player collision."""
import argparse
import hashlib
import json
import struct
from pathlib import Path
import capstone
import pefile
ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/first-floor-batch1/shrink/source'
EXE = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
BASELINE = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--check',action='store_true');args=parser.parse_args()
    raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==BASELINE
    pe=pefile.PE(data=raw);md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    windows=[('add_shrink',0x68cfb0,0x68d160),('remove_shrink',0x68d260,0x68d2ea),
             ('scale_and_expiry',0x6868f5,0x68694d),('set_size',0x6843a0,0x68451d),
             ('shrunken_player_collision',0x6a4df2,0x6a4e1e),('collision_death',0x6a4d73,0x6a4d85),
             ('visual_scale',0x697d3f,0x697d76),('lua_registration',0x8053ab,0x8053b5)]
    result=dict(baseline='Installed Repentance 1.7.9b',executable_sha256=BASELINE,windows=[],constants=[],referenced_evidence=[],
      api_reference='https://wofsauge.github.io/IsaacDocs/rep/Entity.html#addshrink', findings=[
        'AddShrink68cfb0 rejects bosses and common status immunity, routes linked parents, and uses shared source-duration modifier685020. Cohort scope is ordinary types10/11/12, not linked/boss/item integration.',
        'Timer234 positive duration adds then caps150; negative duration keeps max(old,abs(duration)). Zero is rejected. Reapplying a positive duration can shorten a longer negative-duration application. Entity low flag1000000 marks Shrink.',
        'On first activation, target visual scale310 becomes float bits3eaa7efa (.333). Current scale30c is not reset. SetSize receives configuration radius multiplied by CURRENT scale, not target scale. Active reapplication skips SetSize. Removal restores configuration radius immediately and target visual scale1.',
        'Base update6868f5 approaches target: scale += (target-scale)*5*(1/30), then decrements Shrink duration and removes at zero. This update is not gated by ordinary Freeze or Slow. Collision size2c8 is separate from visual scale30c; inspected ordinary base update does not continually resize the hitbox. A first application at scale1 therefore retains ordinary collision radius; reactivation during visual recovery samples that intermediate scale.',
        'NPC sprite-scale assignment697d3f uses current30c. Shrink does not imply damage amplification or a lower maxHP in these reviewed paths.',
        'Ordinary NPC collision6a4df2 tests Shrink, other entity type1(player), and non-boss; then calls virtual+24 directly at6a4d73 before ordinary player-contact damage. This is a direct death path, not the unrelated DAMAGE_CRUSH amount35 or80 seen elsewhere.',
        'Existing pinned Fear evidence contains shared Fear|Shrink1000800 evasion and Horf acquisition gates, and Confusion|Fear|Shrink1000a00 Gusher shot gate. Moving cohort members flee; stationary Horf keeps passive motion. Committed Horf attacks and selected Gusher payloads are retained.'
      ],adaptations=[
        'shrink_effect ID cap targetScale approach opts in only10.0.0,10.1.0,11.0.0,11.1.0,12.0.0. Durations and interpolation use the retained30Hz source phase; modal/inactive-room storage pauses both without catch-up.',
        '3D visual scaling is anchored at the ground, applies to the complete procedural model and its shadow/occlusion pass, and keeps the unshrunk render radius separate from collision radius. Visual scale snaps only within1e-6 of target.',
        'The current cohort uses the same physical body radius through its Gaper-to-headless morph. Native first-activation collision sampling and immediate restoration are retained; generic actor resize/champion integration remains open.',
        'Player contact uses DeathWard swept sphere and line-of-sight/physical cover. Stunned/frozen or capacity-waiting bodies can still be squashed. A queued execution uses the existing damage/death pipeline, suppresses headless morph, and pays one normal kill. Local damage/kill item hooks and player attribution are an explicit adaptation of the native direct Die call.',
        'Under full event capacity, one squash intent per actor is retained and its AI stops until admission. It never hurts the player or silently loses the kill. Already emitted projectiles keep their existing lifetime. No new player item or input binding is added.',
        'Ordinary projectile origin remains the existing collision/actor center. Scaling arbitrary shot offsets, all other status types, champions, source item duration modifiers and full cohort acceptance are not certified by this slice.'
      ])
    if not args.check:
        assert not (OUT/'manifest.json').exists(),'Do not overwrite preserved evidence'
        OUT.mkdir(parents=True,exist_ok=True)
    for name,start,end in windows:
        data=pe.get_data(start-pe.OPTIONAL_HEADER.ImageBase,end-start)
        ins=list(md.disasm(data,start))
        assert sum(i.size for i in ins)==len(data),(name,hex(start+sum(i.size for i in ins)),hex(end))
        text=''.join(f'{i.address:08x} {i.mnemonic} {i.op_str}\n' for i in ins)
        path=OUT/(name+'.asm')
        if args.check:assert path.read_text()==text
        else:path.write_text(text)
        result['windows'].append(dict(path=str(path.relative_to(ROOT)),start=hex(start),end=hex(end),raw_sha256=hashlib.sha256(data).hexdigest(),sha256=hashlib.sha256(path.read_bytes()).hexdigest()))
    for name,address in [('transition_gain',0xb6a8f4),('source_dt',0xb6a25c)]:
        data=pe.get_data(address-pe.OPTIONAL_HEADER.ImageBase,4)
        result['constants'].append(dict(name=name,address=hex(address),bytes=data.hex(),value=struct.unpack('<f',data)[0]))
    for relative in ['first-floor-batch1/statuses/source/manifest.json','headless/source/controller.asm','gaper/source/morph.asm','gaper/source/base-config.asm']:
        path=ROOT/'docs/reports/isaac-enemy-port'/relative
        result['referenced_evidence'].append(dict(path=str(path.relative_to(ROOT)),sha256=hashlib.sha256(path.read_bytes()).hexdigest()))
    path=OUT/'manifest.json'
    if args.check:assert json.loads(path.read_text())==result
    else:path.write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps(dict(result='pass',mode='check' if args.check else 'preserved',windows=len(windows))))
if __name__=='__main__':main()
