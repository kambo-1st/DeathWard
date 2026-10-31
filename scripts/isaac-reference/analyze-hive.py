#!/usr/bin/env python3
"""Preserve installed Hive/Drowned Hive update, evasion, child count and death selection."""
import argparse,hashlib,json,struct
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2];OUT=ROOT/'docs/reports/isaac-enemy-port/hive/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--check',action='store_true');args=p.parse_args()
 raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==SHA
 pe=pefile.PE(data=raw);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n);md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 constants={}
 for name,a,expected in [('walk_retention',0xb6a560,.8),('drowned_retention_multiplier',0xb6a5d8,.95),('sight_flee_range',0xb6abec,250),
  ('hidden_flee_range',0xb6ab7c,170),('attack_range',0xb6ac14,300),('attack_delay',0xb6aac4,75),('overkill',0xb6aee4,-20),
  ('death_budget',0xb6a8cc,4),('population_scale',0xb6a350,.2),('death_radius_max',0xb6a910,6),('death_radius_min',0xb6a7b0,2),
  ('wander_distance',0xb6aa3c,40),('wander_force',0xb6a480,.5),('path_friction',0xb6a50c,.7),('wander_friction',0xb6a5a4,.9),
  ('evade_initial_impulse',0xb6a6f0,1.5),('evade_origin_distance',0xb6aa0c,30),('evade_scatter_distance',0xb6ac80,450)]:
  v=struct.unpack('<f',read(a,4))[0];assert abs(v-expected)<1e-6;constants[name]={'address':hex(a),'value':v}
 assert read(0x9ec3ac,6)==b'\xff\x25\x1c\x65\xa0\x00'
 assert next(s.name for dll in pe.DIRECTORY_ENTRY_IMPORT for s in dll.imports if s.address==0xa0651c)==b'ceil'
 data={'baseline':'Installed Repentance1.7.9b','executable_sha256':SHA,'constants':constants,
  'findings':[
   'Shared controller4fa1e0 covers Hive22, Nest205 and Prey817; this slice configures only22.0/22.1. Ordinary hostile targets pass the target-team helper and call EvadeTarget7a4830. Far bodies fall back to MoveRandomly7a6180.',
   'EvadeTarget proximity checks every14 staggered frames: visible distance250 or blocked distance170 sets evade countdown3; far checks decrement it. It uses random destination candidates, then physical source grid pathfinding. State4 movement adds.8friction; Drowned adds another.95.',
   'Source random movement target is40units away, clears at distance3 or collision, and adds normalized.5impulse with.9friction outside evasion. FindGridPath uses speed1.079, impulse min(distance*.1,2)*speed and.7friction. Source evasion also uses diagonal-axis bias, initial1.5impulse, adaptive grid-search retries/cache and status logic; local terrain navigation is an explicit adaptation, not full grid equivalence.',
   'Live attack count6ad7a0 uses room alive-enemy counts for ordinary hostile owners, not summoner-specific children. At timer<=oneupdate, population >= random integer4..8 adds random20..69frames. Timer decrements while evade countdown is positive. Distance>=300 retries after3; blocked sight retries after7; successful attack sets75frames and HeadAttack.',
   'HeadAttack metadata is18frames with Shoot at4 for both22.0/22.1. Native state8 coasts for these variants rather than calling evasion. Hive spits18.0 and latches child byte16c contact expiry; Drowned spits23.1 and halves both current/max health. Holy/Tainted branches remain separate follow-up.',
   'Death requires HP>-20. Count is ceil(4/(1+.2*room enemy count)); native thunk9ec3ac resolves imported ceil, not floor. Drowned caps this by a uniform1or2. A signed native word atNPC+bc6 is subtracted afterward; its nonzero lifecycle semantics remain unverified, so this slice models the ordinary zero-initialized case.',
   'Ordinary Hive makes an independent RNG%11 choice for every death child:0..6type13,7type14,8..10type18. Positions use random angle and max(2,U*6)radius. Drowned overrides identity23.1 and halves childHP. Death children do not receive the live-spit contact-expiry flag.',
   'The source range/floors/weights are distinct from3D adaptation: retained birthplace retries and pending-birth population accounting prevent dropped children or premature room completion under local capacity/placement pressure.'
  ],'windows':[]}
 windows=[('shared_controller',0x4fa1e0,0x4fb1c5),('target_team',0x6aeb40,0x6aebcc),('room_enemy_count',0x6ad7a0,0x6ad86d),
  ('evade_pathfinder',0x7a4830,0x7a51d0),('wander_pathfinder',0x7a6180,0x7a64a7),('grid_path_final_force',0x7a46bc,0x7a47f5)]
 if not args.check:assert not (OUT/'manifest.json').exists();OUT.mkdir(parents=True,exist_ok=True)
 for name,a,b in windows:
  raw=read(a,b-a);text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(raw,a))+'\n';path=OUT/(name+'.asm')
  if args.check:assert path.read_text()==text
  else:path.write_text(text)
  data['windows'].append({'path':str(path.relative_to(ROOT)),'start':hex(a),'end':hex(b),'raw_sha256':hashlib.sha256(raw).hexdigest(),'sha256':hashlib.sha256(path.read_bytes()).hexdigest()})
 records=json.loads((ROOT/'docs/research/isaac-mechanics-reference.json').read_text())['records']
 data['records']={r['key']:{k:r[k] for k in ['xml','room_library_presence']} for r in records if r.get('key') in ['22.0.0','22.1.0']}
 if args.check:assert json.loads((OUT/'manifest.json').read_text())==data
 else:(OUT/'manifest.json').write_text(json.dumps(data,indent=2)+'\n')
 print(json.dumps({'result':'pass','mode':'checked' if args.check else 'preserved','windows':len(windows)}))
if __name__=='__main__':main()
