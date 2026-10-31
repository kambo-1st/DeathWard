#!/usr/bin/env python3
"""Preserve exact installed Boil/Gut/Sack and walking-family evidence."""
import argparse, hashlib, json, struct
from pathlib import Path
import capstone, pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/boils/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==SHA
 pe=pefile.PE(data=raw);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 dispatch={}
 for ident,case,target in [(30,0x6999ec,0x5054e0),(88,0x699a28,0x5099c0)]:
  index=read(0x69abc0+ident-10,1)[0];assert struct.unpack('<I',read(0x69a7f8+4*index,4))[0]==case
  ins=list(md.disasm(read(case,12),case));assert ins[1].mnemonic=='call' and ins[1].op_str==hex(target)
  dispatch[str(ident)]={'index':index,'case':hex(case),'controller':hex(target)}
 constants={}
 for name,address,value in [('walking_friction',0xb6a53c,.75),('stationary_friction_and_regen',0xb6a560,.8),
  ('initial_HP_and_shot_speed',0xb6a928,7),('wander_reach',0xb6aa3c,40),('wander_arrival',0xb6a864,3),
  ('wander_force',0xb6a480,.5),('near_distance',0xb6abd0,230),('aim_distance',0xb6abec,250),
  ('aim_jitter',0xb6a9c8,20),('shot_scatter',0xb6a8a0,3.5),('trajectory_bias',0xb6a3c4,.32),
  ('falling_base',0xb6a8f4,5),('fall_random_and_walking_throw_height',0xb6aa0c,30),
  ('gut_velocity',0xb6a4a0,.55),('gut_targeted_multiplier',0xb6a4c4,.6),('gut_accel_modifier',0xb6a3b0,.3),
  ('gut_fall_multiplier',0xb6a50c,.7),('gut_fall_subtract',0xb6a994,13),
  ('stationary_throw_height',0xb6a974,10),('throw_planar',0xb6a264,.04),
  ('shot_scale_jitter',0xb6a274,.05),('shot_scale_step',0xb6a434,.4)]:
  actual=struct.unpack('<f',read(address,4))[0];assert abs(actual-value)<1e-5
  constants[name]={'address':hex(address),'value':actual}
 windows=[('stationary_dispatch',0x6999ec,0x6999f8),('walking_dispatch',0x699a28,0x699a34),
  ('stationary_controller',0x5054e0,0x50612d),('walking_controller',0x5099c0,0x50a447),
  ('random_walk_helper',0x7a6180,0x7a64a9),('boss_projectile_helper',0x6a3420,0x6a3970),
  ('projectile_initial',0x62f1ef,0x62f2d0),('flight_integrator',0x636567,0x6365d5),
  ('explosive_projectile_blast',0x631ca4,0x631d44)]
 result={'baseline':'Installed Repentance1.7.9b','executable_sha256':SHA,'dispatch':dispatch,'constants':constants,
  'named_helper_binding':'docs/reports/isaac-enemy-port/gurgle_mortality/source/manifest.json',
  'note':'FireBossProjectiles binding independently established there; full bounded helper and both controllers preserved here. No source sprite artwork copied into runtime.', 'windows':[]}
 if not args.check:assert not (OUT/'manifest.json').exists();OUT.mkdir(parents=True,exist_ok=True)
 for name,a,b in windows:
  blob=read(a,b-a);text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(blob,a))+'\n';p=OUT/(name+'.asm')
  if args.check:assert p.read_text()==text
  else:p.write_text(text)
  result['windows'].append({'path':str(p.relative_to(ROOT)),'start':hex(a),'end':hex(b),'raw_sha256':hashlib.sha256(blob).hexdigest(),'sha256':hashlib.sha256(p.read_bytes()).hexdigest()})
 if args.check:assert json.loads((OUT/'manifest.json').read_text())==result
 else:(OUT/'manifest.json').write_text(json.dumps(result,indent=2)+'\n')
 print(json.dumps({'result':'pass','windows':len(windows)}))
if __name__=='__main__':main()
