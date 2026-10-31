#!/usr/bin/env python3
"""Pin installed Host-family controllers and their shared helpers."""
import argparse, hashlib, json, struct
from pathlib import Path
import capstone, pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/hosts/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==SHA
 pe=pefile.PE(data=raw);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);dispatch={};constants={}
 for ident,case,target in [(27,0x69a2bf,0x4ff200),(859,0x69a2bf,0x4ff200),(204,0x699be4,0x51f510),(247,0x699be4,0x51f510)]:
  index=read(0x69abc0+ident-10,1)[0];assert struct.unpack('<I',read(0x69a7f8+4*index,4))[0]==case
  ins=list(md.disasm(read(case,12),case));assert ins[1].mnemonic=='call' and ins[1].op_str==hex(target)
  dispatch[str(ident)]={'index':index,'case':hex(case),'controller':hex(target)}
 for name,address,value in [('range',0xb6abe4,240),('range_squared',0xb6ad68,57600),('float_force',0xb6a4a0,.55),('float_retention',0xb6a5a4,.9),('shot_speed',0xb6a928,7),('walk_idle_friction',0xb6a560,.8),('walk_attack_friction',0xb6a480,.5),('path_friction',0xb6a50c,.7),('path_gain',0xb6a2cc,.1),('path_cap',0xb6a7b0,2),('spread2_forward',0xb6a5ec,.961),('spread2_side',0xb6a39c,.276),('spread5_inner_forward',0xb6a600,.978),('spread5_inner_side',0xb6a360,.208),('spread5_outer_forward',0xb6a5b0,.914),('spread5_outer_side',0xb6a43c,.407)]:
  actual=struct.unpack('<f',read(address,4))[0];assert abs(actual-value)<1e-5
  constants[name]={'address':hex(address),'value':actual}
 windows=[('host',0x4ff200,0x500132),('mobile_host',0x51f510,0x52002d),('grid_path',0x7a3650,0x7a4813),('acquisition',0x6a15a0,0x6a174c),('cadence',0x684790,0x6847db),('age_cadence',0x6847e0,0x684852),('projectile_params',0x430d70,0x430ec0),('fire_projectiles',0x6a1a20,0x6a3420)]
 result={'baseline':'Installed Repentance 1.7.9b','executable_sha256':SHA,'dispatch':dispatch,'constants':constants,'windows':[]}
 if not args.check:assert not (OUT/'manifest.json').exists();OUT.mkdir(parents=True,exist_ok=True)
 for name,a,b in windows:
  blob=read(a,b-a);txt='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(blob,a))+'\n';p=OUT/(name+'.asm')
  if args.check:assert p.read_text()==txt
  else:p.write_text(txt)
  result['windows'].append({'path':str(p.relative_to(ROOT)),'start':hex(a),'end':hex(b),'raw_sha256':hashlib.sha256(blob).hexdigest(),'sha256':hashlib.sha256(p.read_bytes()).hexdigest()})
 if args.check:assert json.loads((OUT/'manifest.json').read_text())==result
 else:(OUT/'manifest.json').write_text(json.dumps(result,indent=2)+'\n')
 print(json.dumps({'result':'pass','windows':len(windows)}))
if __name__=='__main__':main()
