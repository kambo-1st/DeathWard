#!/usr/bin/env python3
"""Bounded original Sad Onion contribution and ordinary fire-delay curve."""
import argparse,csv,hashlib,importlib.util,io,json,struct,xml.etree.ElementTree as ET
from pathlib import Path
import capstone,pefile
from unicorn.x86_const import *
spec=importlib.util.spec_from_file_location('motion',Path(__file__).with_name('analyze-player-motion.py'))
M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)
OUT=M.ROOT/'docs/reports/isaac-first-floor-parity/d11a-treasure-upgrade/source'
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==M.SHA
 pe=pefile.PE(data=raw);n=M.NativeMotion(pe);u=n.u;b=n.ebp
 source=M.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3'
 item=next(e for e in ET.parse(source/'items.xml').getroot() if e.tag=='passive' and e.get('id')=='1')
 pool=next(e for p in ET.parse(source/'itempools.xml').getroot() if p.get('Name')=='treasure' for e in p if e.get('Id')=='1')
 assert item.get('cache')=='firedelay' and not item.get('achievement') and pool.get('Weight')=='1'
 OUT.mkdir(parents=True,exist_ok=True)
 def save(name,blob):
  p=OUT/name
  if args.check:assert p.read_bytes()==blob,name
  else:p.write_bytes(blob)
 windows=[('sad-onion-query',0x72f97a,0x72f9bb),('tear-stat-weight',0x72fb55,0x72fb7c),('ordinary-delay-curve',0x73006a,0x730143),('sqrt',0x4228f0,0x42291e)]
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);evidence=[]
 for name,start,end in windows:
  blob=pe.get_data(start-0x400000,end-start);listing='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,start))+'\n';save(name+'.asm',listing.encode());evidence.append(dict(name=name,start=hex(start),end=hex(end),sha256=hashlib.sha256(blob).hexdigest()))
 rows=[]
 for base in [-8,-2,-1,-.7,-.5,-.2,0,.3,1,2,4,8]:
  for copies in [0,1,2,3,8]:
   n.reset();u.reg_write(UC_X86_REG_EBP,b);u.reg_write(UC_X86_REG_ESP,b-0x1000);u.reg_write(UC_X86_REG_EDI,n.PLAYER)
   # Execute the owned-count contribution, supplying only the query's result.
   # Other item-count terms are zero. No query/factory/global cache acceptance.
   u.reg_write(UC_X86_REG_EAX,copies);n.write_float(b-0x42c,0);n.run(0x72f9a4,0x72f9bb)
   n.run(0x72fb6c,0x72fb7c);contribution=n.read_float(b-0x42c)
   bonus=struct.unpack('<f',struct.pack('<f',base+contribution))[0]
   n.write_float(b-0x448,bonus);n.xmm(UC_X86_REG_XMM1,bonus);n.xmm(UC_X86_REG_XMM0,1);u.mem_write(b-0x428,struct.pack('<I',n.PLAYER))
   n.run(0x73006a,0x730143)
   rate=struct.unpack('<f',struct.pack('<I',u.reg_read(UC_X86_REG_XMM1)&0xffffffff))[0]
   rows.append([base,copies,contribution,bonus,n.read_float(b-0x448),rate])
 out=io.StringIO();w=csv.writer(out,lineterminator='\n');w.writerow(['base_tear_stat','copies','item_contribution','total_tear_stat','delay','tears_per_second']);w.writerows(rows);save('native-tears.csv',out.getvalue().encode())
 manifest=dict(executable_sha256=M.SHA,version='Repentance 1.7.9b',item=dict(item.attrib),treasure_pool_entry=dict(pool.attrib),xml_sha256={name:hashlib.sha256((source/name).read_bytes()).hexdigest() for name in ['items.xml','itempools.xml']},windows=evidence,cases=len(rows),scope='Original SSE contribution and ordinary rate curve including original min/max/sqrt helpers. Supplied owned-count result and base tear stat; ordinary character, no other modifiers. Full inventory query/cache order, item interactions, pool RNG and pickup factory/animation are not accepted.',full_native_acceptance=False)
 save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode());print('PASS',len(rows),'original contribution/delay/rate cases and eligible treasure XML')
if __name__=='__main__':main()
