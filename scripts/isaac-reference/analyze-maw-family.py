#!/usr/bin/env python3
"""Pin installed Maw/Eternal Fly controllers and their shared helpers."""
import argparse, hashlib, json, struct
from pathlib import Path
import capstone, pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/maw_family/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==SHA
 pe=pefile.PE(data=raw);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);dispatch={};constants={}
 for ident,case,target in [(26,0x6999e0,0x4feb40),(96,0x699914,0x4f8860)]:
  index=read(0x69abc0+ident-10,1)[0];assert struct.unpack('<I',read(0x69a7f8+4*index,4))[0]==case
  ins=list(md.disasm(read(case,12),case));assert ins[1].mnemonic=='call' and ins[1].op_str==hex(target)
  dispatch[str(ident)]={'index':index,'case':hex(case),'controller':hex(target)}
 for name,address,value in [('range',0xb6aba8,200),('pursuit',0xb6a2f0,.13),('retention',0xb6a5c4,.93),('shot_speed',0xb6a928,7),('red_multiplier',0xb6a864,3)]:
  actual=struct.unpack('<f',read(address,4))[0];assert abs(actual-value)<1e-5
  constants[name]={'address':hex(address),'value':actual}
 windows=[('maw',0x4feb40,0x4ff1f7),('eternal_fly',0x4f8860,0x4f8e28),('acquisition',0x6a15a0,0x6a174c),('cadence',0x684790,0x6847db),('projectile_params',0x430d70,0x430e90),('fire_projectiles',0x6a1a20,0x6a3420),('homing',0x6348ac,0x634ab9),('released_fly_regeneration',0x4f58ec,0x4f592f),('homing_binding',0x80421b,0x804225),('homing_getter',0x5ef0e0,0x5ef0e8),('vector_helpers',0x962380,0x962ce7)]
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
