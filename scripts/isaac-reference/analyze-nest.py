#!/usr/bin/env python3
"""Preserve installed Nest evasion, cooldown, live-spider contact expiry and death choice."""
import argparse,hashlib,json,struct
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2];OUT=ROOT/'docs/reports/isaac-enemy-port/nest/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--check',action='store_true');args=p.parse_args()
 raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==SHA
 pe=pefile.PE(data=raw);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n);md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 assert struct.unpack('<I',read(0xb49398+0x24,4))[0]==0x695560
 assert struct.unpack('<I',read(0xb49398+0x58,4))[0]==0x6a3970
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
   'Type205 uses shared controller4fa1e0. State0 at4fa261 becomes4, clears attack timer and returns without movement or attack. State4 uses target-team/evasion helpers and .8 friction; no Drowned .95 multiplier and no Holy/Tainted movement during attack.',
   'Shared ordinary evasion: 14-frame staggered proximity checks, visible250/hidden170 range and3 sticky checks. Path force1.079*min(distance*.1,2), path friction.7; wander40 distance,.5 impulse,.9 friction. Native grid caches, diagonal bias and status branches are not equivalent to local terrain navigation.',
   'Common room population gate at4fa9d5: timer<=one update and population>=uniform4..8 adds uniform20..69. Cooldown decreases while evading. Attack requires distance<300 and clear sight; failed range retries3, blocked sight7.',
   'Nest-specific4fab84..4fabd9: timer75 plus55+(RNG%20), therefore130..149 source updates for ordinary hostile AI. Controlled-player branch uses no random addition and is outside this port slice.',
   'HeadAttack18 source frames and Shoot at4 are pinned by installed Nest animation metadata (30FPS). Live branch4fa8cb..4fa930 spawns85.0.0 at parent with zero velocity, sets NPC byte16c=1 and clears APPEAR bit4. Player collision6a5552 checks byte16c and invokes virtual Kill; NPC vtable dispatch is verified.',
   'Death at4facd8 requires post-hitHP>-20. Type205 branch4fad6a..4fad76 forces count1 instead of the common ceil population formula. The native signed word+bc6 is then subtracted: only its ordinary zero-initialized case is established here.',
   'Death4fb127..4fb16e chooses RNG&1: zero=>type94 variant0 Big Spider, one=>type29 variant1 Trite. Both are at parent position with zero velocity and APPEAR cleared. No live-child contact flag is set, and it must not propagate through later Big Spider death children.',
   'XML sourceHP20, stageHP0, collisionDamage0. Source room-template counts establish presence only. Local stage bands/weights, radius and HP/world conversion are DeathWard adaptations.',
   'Pinned wiki revision271647 Nest section confirms the live/death-child distinction and overkill. It also records a Burning Basement Flaming Hopper bug; exact native initialization/replacement branch remains unverified and is not silently claimed as implemented.'
  ],'windows':[]}
 windows=[('shared_controller',0x4fa1e0,0x4fb1c5),('target_team',0x6aeb40,0x6aebcc),('room_enemy_count',0x6ad7a0,0x6ad86d),
  ('evade_pathfinder',0x7a4830,0x7a51d1),('wander_pathfinder',0x7a6180,0x7a64a7),('grid_path_final_force',0x7a46bc,0x7a47f5),('player_collision',0x6a5129,0x6a5562),('kill',0x695560,0x6955f5)]
 if not args.check:OUT.mkdir(parents=True,exist_ok=True)
 for name,a,b in windows:
  raw=read(a,b-a);text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(raw,a))+'\n';path=OUT/(name+'.asm')
  if args.check or path.exists():assert path.read_text()==text
  else:path.write_text(text)
  data['windows'].append({'path':str(path.relative_to(ROOT)),'start':hex(a),'end':hex(b),'raw_sha256':hashlib.sha256(raw).hexdigest(),'sha256':hashlib.sha256(path.read_bytes()).hexdigest()})
 records=json.loads((ROOT/'docs/research/isaac-mechanics-reference.json').read_text())['records']
 data['records']={r['key']:{k:r[k] for k in ['xml','room_library_presence']} for r in records if r.get('key') in ['205.0.0']}
 if args.check or (OUT/'manifest.json').exists():assert json.loads((OUT/'manifest.json').read_text())==data
 else:(OUT/'manifest.json').write_text(json.dumps(data,indent=2)+'\n')
 print(json.dumps({'result':'pass','mode':'checked' if args.check else 'preserved','windows':len(windows)}))
if __name__=='__main__':main()
