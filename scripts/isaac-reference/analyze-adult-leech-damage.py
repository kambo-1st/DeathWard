#!/usr/bin/env python3
"""Preserve the distinct collision, radial-damage and direct-damage routes."""
import argparse,hashlib,json
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/adult-leech/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
def sha(data):return hashlib.sha256(data).hexdigest()
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=EXE.read_bytes();assert sha(raw)=='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
 pe=pefile.PE(data=raw);md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 def save(path,data):
  if args.check or path.exists():assert path.read_bytes()==data,path
  else:path.write_bytes(data)
 manifest={'executable_sha256':sha(raw),'windows':[],
  'finding':'Radial collection skips EntityCollisionClass zero at 6d1356. General scripted TakeDamage registers pending damage without that blanket guard; the IsVulnerableEnemy call near 684bfb belongs to a special protection/effect route, not an unconditional rejection.'}
 for name,a,b in [('radial_damage',0x6d1280,0x6d1446),('vulnerable_query',0x684630,0x6846dc),
  ('direct_damage',0x684bb0,0x68500b),('npc_damage_forward',0x6ac370,0x6ac3b8)]:
  blob=pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,b-a);ins=list(md.disasm(blob,a));assert ins[-1].address+ins[-1].size==b,(name,hex(ins[-1].address))
  data=('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in ins)+'\n').encode();path=OUT/(name+'.asm');save(path,data)
  manifest['windows'].append({'path':str(path.relative_to(ROOT)),'start':hex(a),'end':hex(b),'raw_sha256':sha(blob),'sha256':sha(data)})
 save(OUT/'damage-manifest.json',(json.dumps(manifest,indent=2)+'\n').encode())
 print(json.dumps({'pass':True,'windows':len(manifest['windows']),'check':args.check}))
if __name__=='__main__':main()
