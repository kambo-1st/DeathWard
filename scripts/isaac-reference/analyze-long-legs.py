#!/usr/bin/env python3
"""Preserve installed Long Legs/Sack controllers and supporting numeric evidence."""
import argparse, hashlib, json, struct
from pathlib import Path
import capstone, pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/long_legs/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==SHA
 pe=pefile.PE(data=raw);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 dispatch={}
 for ident,case,target in [(206,0x699bd8,0x51edf0),(207,0x699bd8,0x51edf0),(30,0x6999ec,0x5054e0)]:
  i=read(0x69abc0+ident-10,1)[0];assert struct.unpack('<I',read(0x69a7f8+4*i,4))[0]==case
  ins=list(md.disasm(read(case,12),case));assert ins[1].mnemonic=='call' and ins[1].op_str==hex(target)
  dispatch[str(ident)]={'case':hex(case),'controller':hex(target),'index':i}
 constants={}
 for name,a,value in [('sack_initial_HP',0xb6a928,7),('sack_friction',0xb6a560,.8),('sack_near',0xb6abd0,230),('sack_aim',0xb6abec,250),('sack_regen_gain',0xb6a670,1.2),('sack_growth',0xb6a234,.02),('black_champion_growth',0xb6a214,.01),('spider_throw_delta',0xb6a264,.04),('diagonal_normalize',0xb6a524,.70710678)]:
  actual=struct.unpack('<f',read(a,4))[0];assert abs(actual-value)<1e-5;(constants.update({name:{'address':hex(a),'value':actual}}))
 strings={hex(a):read(a,24).split(b'\0')[0].decode() for a in [0xb432bc,0xb432a8,0xb40510,0xb400ac,0xb41e70,0xb41e80]}
 assert list(strings.values())==['Lay Egg','Lay','Attack','Shoot','Shrink','Shake']
 windows=[('long_legs_dispatch',0x699bd8,0x699be4),('sack_dispatch',0x6999ec,0x6999f8),
  ('long_legs_controller',0x51edf0,0x51f504),('sack_controller',0x5054e0,0x50612d),
  ('random_unit_vector',0x659290,0x6592ef),('chase_pathfinder',0x7a3650,0x7a4813),
  ('evade_pathfinder',0x7a4830,0x7a51d1),('diagonal_shots',0x6a286f,0x6a2a49),
  ('eight_way_shots',0x6a2a49,0x6a2ff1),('projectile_falling_application',0x6a3059,0x6a31b8),
  ('projectile_initial_fall',0x62f1ef,0x62f2d0)]
 data={'baseline':'Installed Repentance1.7.9b','executable_sha256':SHA,'dispatch':dispatch,'constants':constants,'strings':strings,'windows':[]}
 if not args.check:assert not (OUT/'manifest.json').exists();OUT.mkdir(parents=True,exist_ok=True)
 for name,a,b in windows:
  blob=read(a,b-a);text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(blob,a))+'\n';p=OUT/(name+'.asm')
  if args.check:assert p.read_text()==text
  else:p.write_text(text)
  data['windows'].append({'path':str(p.relative_to(ROOT)),'start':hex(a),'end':hex(b),'raw_sha256':hashlib.sha256(blob).hexdigest(),'sha256':hashlib.sha256(p.read_bytes()).hexdigest()})
 if args.check:assert json.loads((OUT/'manifest.json').read_text())==data
 else:(OUT/'manifest.json').write_text(json.dumps(data,indent=2)+'\n')
 print(json.dumps({'result':'pass','windows':len(windows)}))
if __name__=='__main__':main()
