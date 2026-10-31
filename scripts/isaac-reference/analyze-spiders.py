#!/usr/bin/env python3
"""Preserve the installed ordinary Spider/Big Spider controller and split evidence."""
import argparse,hashlib,json,struct
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2];OUT=ROOT/'docs/reports/isaac-enemy-port/spiders/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==SHA
 pe=pefile.PE(data=raw);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 constants={}
 for name,a,want in [('force',0xb6a910,6),('range_minimum_and_span',0xb6aafc,100),('wander_span',0xb6aa3c,40),('wander_minimum',0xb6aab4,70),('retention',0xb6a4c4,.6),('arrival',0xb6a9a0,14),('stuck_speed',0xb6a864,3),('prediction_and_death_split',0xb6a974,10),('overkill',0xb6aee4,-20),('gap_trim',0xb6a2cc,.1)]:
  value=struct.unpack('<f',read(a,4))[0];assert abs(value-want)<1e-6,(name,value);constants[name]={'address':hex(a),'value':value}
 for id in [85,94]:
  i=read(0x69abc0+id-10,1)[0];assert i==57 and struct.unpack('<I',read(0x69a7f8+4*i,4))[0]==0x699f0b
 assert read(0xb3fd8c,5)==b'Idle\0' and read(0xb41264,5)==b'Walk\0'
 windows=[('shared_dispatch',0x699f0b,0x699f17),('shared_controller',0x5175b0,0x5185d7),
  ('ordinary_target',0x695bf3,0x695c30),('room_clamp',0x7cec10,0x7cef13)]
 result={'baseline':'Installed Repentance 1.7.9b','executable_sha256':SHA,'dispatch':{'85':{'index':57,'address':'0x699f0b','controller':'0x5175b0'},'94':{'index':57,'address':'0x699f0b','controller':'0x5175b0'}},'constants':constants,'windows':[],
 'findings':[
 'Types85 and94 share controller5175b0. Initial state0 becomes4 and resets counter+360 to0. Ordinary ready movement uses Idle while no target, Walk while a target exists; source animation metadata is30FPS Idle4/Walk5 loops. No attack projectile event exists.',
 'The idle counter increments by entity-time integer delta. Selection requires its previous value>13: with normal delta1, the first selection occurs on the15th ready update. Moving decrements the same counter. Ordinary state6 is thrown-airborne behavior, separate from this ground controller.',
 'Normal target helper695a30 returns the target entity position. Passed60 affects fear/shrink branches, not ordinary lead. Ordinary chase selection compares target distance against100+100*U and checks line of sight (unless gridcollision3). It then adds target velocity*10 and clamps the destination to room bounds using body-size margins. Native+e88 can override the range condition.',
 'If chase selection fails, choose a random direction and distance70+40*U. Clamp with source left60/top70/right40/bottom60 margins. Destination grid must be clear, then line check mode0 must pass. If it fails,1/20chance tests mode1 between10%-trimmed endpoints. Accepted wandering destination sets counter15. Exact source grid/line semantics are separate from physical3D sweeps.',
 'Ordinary movement adds normalized destination delta*6 divided by current friction. End-of-controller multiplies friction by0.6. Stop/clear target if within14sourceunits, or if speed<3 and the decremented counter is negative. The last impulse is still applied on that stopping update. There is no continuous homing or A* pursuit in this ordinary branch.',
 'Type94 death with post-hitHP>-20 creates exactly two type85variant0subtype0 children. Perpendicular to the player-target delta, each is offset by10sourceunits on opposite sides and gets the same outward10unit velocity. Degenerate target delta uses a random unit direction. Both children have APPEAR bit4 cleared. Overkill at or below-20 suppresses both.',
 'Controller also implements other spider types, Bursting Sack(item377) neutral handling, player control, special thrown state6 and status-aware target helper. Those are not inferred from the ordinary85/94 branch. Baseline XML HP6.5/20, stage0 and contact1 are preserved.'
 ],'records':json.loads((OUT.parent/'records.json').read_text())}
 if not args.check:assert not (OUT/'manifest.json').exists();OUT.mkdir(parents=True,exist_ok=True)
 for name,a,b in windows:
  blob=read(a,b-a);s='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(blob,a))+'\n';p=OUT/(name+'.asm')
  if args.check:assert p.read_text()==s
  else:p.write_text(s)
  result['windows'].append({'path':str(p.relative_to(ROOT)),'start':hex(a),'end':hex(b),'raw_sha256':hashlib.sha256(blob).hexdigest(),'sha256':hashlib.sha256(p.read_bytes()).hexdigest()})
 if args.check:assert json.loads((OUT/'manifest.json').read_text())==result
 else:(OUT/'manifest.json').write_text(json.dumps(result,indent=2)+'\n')
 print(json.dumps({'result':'pass','windows':len(windows)}))
if __name__=='__main__':main()
