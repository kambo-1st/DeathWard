#!/usr/bin/env python3
"""Pin the separate Rotten Gaper controller; extraction is not runtime parity."""
import argparse,hashlib,json,struct
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/rotten-gaper/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def sha(data):return hashlib.sha256(data).hexdigest()
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=EXE.read_bytes();assert sha(raw)==SHA;pe=pefile.PE(data=raw,fast_load=True)
 read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 def save(path,data):
  if args.check or path.exists():assert path.read_bytes()==data,path
  else:path.parent.mkdir(parents=True,exist_ok=True);path.write_bytes(data)
 start,end=0x4c70e0,0x4c7ebd
 blob=read(start,end-start);ops=list(md.disasm(blob,start));assert ops[-1].address+ops[-1].size==end and ops[-1].mnemonic=='ret'
 assert read(end,3)==b'\xcc'*3
 listing=('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in ops)+'\n').encode();path=OUT/'controller.asm';save(path,listing)
 source=json.loads((ROOT/'docs/research/isaac-mechanics-reference.json').read_text())
 records=[r for r in source['records'] if r.get('key','').startswith('10.3.') or r.get('key')=='853.0.0']
 assert len(records)==7
 save(OUT/'records.json',(json.dumps(records,indent=2,ensure_ascii=False)+'\n').encode())
 # The initialization has a six-float table on its stack: four packed values,
 # followed by .9 and1.9. Meanings and subtype indexing are reviewed separately.
 values=list(struct.unpack('<4f',read(0xb6bcd0,16)))+[struct.unpack('<f',struct.pack('<I',x))[0] for x in [0x3f666666,0x3ff33333]]
 data={'baseline':'Installed Repentance1.7.9b','executable_sha256':SHA,'controller':{'start':hex(start),'end_exclusive':hex(end),'raw_sha256':sha(blob),'path':str(path.relative_to(ROOT)),'sha256':sha(listing),'instructions':len(ops)},
  'dispatch':'Ordinary Gaper controller4f6ee0 delegates type10 variant3 at4f6f2f to this separate controller.',
  'stack_constants':{'packed_address':'0xb6bcd0','values':values,'interpretation':'Pending subtype/control-flow review; do not assume every number is a speed.'},
  'records':[r['key'] for r in records],
  'scope':'Source-only extraction. No new runtime, placement or completion credit. All six parent subtypes and Small Maggot dependency require reviewed behavior.'}
 save(OUT/'manifest.json',(json.dumps(data,indent=2)+'\n').encode())
 childStart,childEnd=0x4c3fd0,0x4c509d
 childBlob=read(childStart,childEnd-childStart);childOps=list(md.disasm(childBlob,childStart))
 assert childOps[-1].address+childOps[-1].size==childEnd and childOps[-1].mnemonic=='ret'
 childText=('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in childOps)+'\n').encode()
 save(OUT/'small-maggot-controller.asm',childText)
 childIndex=read(0x69abc0+853-10,1)[0];childCase,=struct.unpack('<I',read(0x69a7f8+4*childIndex,4))
 assert childCase==0x69a253 and any(i.mnemonic=='call' and i.op_str=='0x4c3fd0' for i in md.disasm(read(childCase,12),childCase))
 helper={'baseline':'Installed Repentance1.7.9b','executable_sha256':SHA,'dispatch':{'type':853,'case':hex(childCase),'controller':hex(childStart)},
  'window':{'start':hex(childStart),'end_exclusive':hex(childEnd),'raw_sha256':sha(childBlob),'sha256':sha(childText),'path':str((OUT/'small-maggot-controller.asm').relative_to(ROOT))},
  'scope':'Shared controller, not every branch is853.0.0. Child behavior and external jump-table data require review.',
  'existing_shared_evidence':['docs/reports/isaac-enemy-port/danny/source/owned_children.asm','docs/reports/isaac-enemy-port/long_legs/source/evade_pathfinder.asm']}
 save(OUT/'small-maggot-manifest.json',(json.dumps(helper,indent=2)+'\n').encode())
 extra={'baseline':'Installed Repentance1.7.9b','executable_sha256':SHA,'helpers':[],
  'finding':'Orbit resize and normalization preserve a vector below native epsilon, including zero; no invented fallback tangent. Brood target retention expires before reacquisition, and its owner cap is checked after a successful chance resets the spawn counter.'}
 for name,a,b in [('orbit-resize',0x9628d0,0x962933),('orbit-normalize',0x962560,0x9625d5)]:
  rawHelper=read(a,b-a);ins=list(md.disasm(rawHelper,a));assert ins[-1].address+ins[-1].size==b and ins[-1].mnemonic=='ret'
  listingHelper=('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in ins)+'\n').encode()
  pathHelper=OUT/(name+'.asm');save(pathHelper,listingHelper)
  extra['helpers'].append({'start':hex(a),'end_exclusive':hex(b),'raw_sha256':sha(rawHelper),'path':str(pathHelper.relative_to(ROOT)),'sha256':sha(listingHelper)})
 extra['epsilon']={'address':'0xb6a18c','value':struct.unpack('<f',read(0xb6a18c,4))[0]}
 save(OUT/'parent-helpers.json',(json.dumps(extra,indent=2)+'\n').encode())
 print(json.dumps({'pass':True,'check':args.check,'instructions':len(ops),'records':len(records),'stack_constants':values,'child_instructions':len(childOps)}))
if __name__=='__main__':main()
