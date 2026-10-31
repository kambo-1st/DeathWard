#!/usr/bin/env python3
"""Pin Mushroom's normal controller, cross patterns and shared shot postpass."""
import argparse,hashlib,json,struct
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/mushroom/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==SHA
 pe=pefile.PE(data=raw);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
 u32=lambda a:struct.unpack('<I',read(a,4))[0]
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 i=read(0x69abc0+300-10,1)[0];assert i==121 and u32(0x69a7f8+4*i)==0x699d97
 assert list(md.disasm(read(0x699d99,5),0x699d99))[0].op_str=='0x52fcb0'
 assert u32(0x6a33ec+6*4)==0x6a269d and u32(0x6a33ec+7*4)==0x6a286f
 constants={}
 for name,a,value in [('closed_damage_scale',0xb6a38c,.25),('diagonal_component',0xb6a524,.70710677)]:
  v=struct.unpack('<f',read(a,4))[0];assert abs(v-value)<1e-6;constants[name]=dict(address=hex(a),value=v)
 states={str(s):hex(u32(0x53017c+4*read(0x53018c+s-3,1)[0])) for s in [3,8,9,16]}
 assert states=={'3':'0x52fd93','8':'0x52fe6e','9':'0x52fe6e','16':'0x530034'}
 windows=[('controller',0x52fcb0,0x53017c),('cardinal',0x6a269d,0x6a286f),
          ('diagonal',0x6a286f,0x6a2a49),('postpass',0x6a301c,0x6a3159)]
 result=dict(baseline='Installed Repentance1.7.9b',executable_sha256=SHA,
  dispatch=dict(index=i,case='0x699d97',controller='0x52fcb0'),states=states,constants=constants,windows=[])
 if not args.check:assert not (OUT/'manifest.json').exists();OUT.mkdir(parents=True,exist_ok=True)
 for name,a,b in windows:
  blob=read(a,b-a);txt='\n'.join(f'{x.address:08x} {x.mnemonic} {x.op_str}' for x in md.disasm(blob,a))+'\n';p=OUT/(name+'.asm')
  if args.check:assert p.read_text()==txt
  else:p.write_text(txt)
  result['windows'].append(dict(path=str(p.relative_to(ROOT)),start=hex(a),end=hex(b),raw_sha256=hashlib.sha256(blob).hexdigest(),sha256=hashlib.sha256(p.read_bytes()).hexdigest()))
 if args.check:assert json.loads((OUT/'manifest.json').read_text())==result
 else:(OUT/'manifest.json').write_text(json.dumps(result,indent=2)+'\n')
 print(json.dumps(dict(result='pass',windows=len(windows))))
if __name__=='__main__':main()
