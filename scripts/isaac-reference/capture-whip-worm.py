#!/usr/bin/env python3
"""Installed Whip Worm query/cache contribution and bounded trinket factory."""
import argparse,csv,hashlib,importlib.util,io,json,struct,xml.etree.ElementTree as ET
from pathlib import Path
import capstone,pefile
from unicorn.x86_const import *
spec=importlib.util.spec_from_file_location('awards',Path(__file__).with_name('analyze-room-awards.py'))
A=importlib.util.module_from_spec(spec);spec.loader.exec_module(A);M=A.M
OUT=M.ROOT/'docs/reports/isaac-first-floor-parity/pw-t02-whip-worm/source'
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==M.SHA
 pe=pefile.PE(data=raw);f=A.NativeAwards(pe,raw);u=f.u;n=f.n;b=n.ebp
 source=M.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3/items.xml'
 item=next(e for e in ET.parse(source).getroot() if e.tag=='trinket' and e.get('id')=='27')
 assert item.get('cache')=='shotspeed' and not item.get('achievement')
 OUT.mkdir(parents=True,exist_ok=True)
 def save(name,blob):
  p=OUT/name
  if args.check:assert p.read_bytes()==blob,name
  else:p.write_bytes(blob)
 def frame(held):
  u.reg_write(UC_X86_REG_EBP,b);u.reg_write(UC_X86_REG_ESP,b-0x1000)
  f.write(b-0x428,n.PLAYER);f.write(n.PLAYER+0x15e8,held)
  f.write(b-0x440,n.PLAYER+0x1450);u.mem_write(b-0x441,b'\x01')
  u.reg_write(UC_X86_REG_ESI,n.PLAYER+0x1450);u.reg_write(UC_X86_REG_EDI,n.PLAYER+0x13ac)
 def block(start,end):
  u.emu_start(start,end,count=500000);assert u.reg_read(UC_X86_REG_EIP)==end
 rows=[]
 for base in [.1,.6,.9,1,1.5,2,2.5,3]:
  for held in [0,27,39]:
   frame(held);n.write_float(n.PLAYER+0x13ac,base);n.write_float(b-0x43c,1)
   block(0x732b12,0x732c33);before=n.read_float(n.PLAYER+0x13ac)
   assert abs(before-(base+(.5 if held==27 else 0)))<.000001
   u.reg_write(UC_X86_REG_EDI,n.PLAYER);block(0x732cd0,0x732ce8);after=n.read_float(n.PLAYER+0x13ac)
   assert abs(after-max(.6,before))<.000001
   rows.append([base,held,before,after])
 whole=[]
 for held in [0,27,39]:
  frame(held);u.reg_write(UC_X86_REG_EAX,n.PLAYER)
  block(0x732646,0x732c33);speed=n.read_float(n.PLAYER+0x13ac)
  assert speed==(1.5 if held==27 else 1);whole.append(dict(held=held,shot_speed=speed))
 out=io.StringIO();w=csv.writer(out,lineterminator='\n');w.writerow(['base','held','before_global_floor','after_global_floor']);w.writerows(rows);save('native-shot-speed.csv',out.getvalue().encode())
 save('native-cache.json',(json.dumps(whole,indent=2)+'\n').encode())
 factories=[]
 for pool in [[27],[39],[27,39]]:
  for seed in [1,2,7,39,69,12345,1416295006,0xffffffff]:
   g=A.NativeAwards(pe,raw);p=g.GAME+0x1a5cc;v=g.HEAP+0x300000;defs=v+0x1000;d=defs+0x1000;callbacks=d+0x1000
   for addr,val in [(p+0x798,len(pool)),(p+0x78c,v),(p+0x790,v+8*len(pool)),(g.MANAGER+0x29e90,defs),(g.MANAGER+0x29e94,defs+200*4),(0xbfd674,callbacks),(callbacks,callbacks+0x100)]:g.write(addr,val)
   for i,id in enumerate(pool):
    g.write(defs+id*4,d+i*16);g.write(d+i*16,2);g.write(d+i*16+4,id);g.u.mem_write(v+i*8,struct.pack('<I4B',id,1,1,0,0))
   g.u.mem_write(p+0x664,struct.pack('<4I',seed,5,9,7))
   variant,subtype=g.pickup(seed,350)
   state=seed^(seed>>5);state^=(state<<9)&0xffffffff;state^=state>>7
   assert variant==350 and subtype==pool[state%len(pool)] and g.integer(p+0x798)==len(pool)-1
   factories.append(dict(pool=pool,seed=seed,subtype=subtype,remaining=g.integer(p+0x798)))
 save('native-factory.json',(json.dumps(factories,indent=2)+'\n').encode())
 out=io.StringIO();w=csv.writer(out,lineterminator='\n');w.writerow(['seed','subtype']);w.writerows([r['seed'],r['subtype']] for r in factories if r['pool']==[27,39]);save('native-pair.csv',out.getvalue().encode())
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
 for name,start,end in [('whip-query-contribution',0x732b12,0x732b40),('global-shot-speed-floor',0x732cd0,0x732ce8),('ordinary-shot-speed-cache',0x732646,0x732c33)]:
  blob=pe.get_data(start-0x400000,end-start);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,start))+'\n').encode());windows.append(dict(name=name,start=hex(start),end=hex(end),sha256=hashlib.sha256(blob).hexdigest()))
 save('manifest.json',(json.dumps(dict(executable_sha256=M.SHA,version='Repentance 1.7.9b',item=dict(item.attrib),xml_sha256=hashlib.sha256(source.read_bytes()).hexdigest(),windows=windows,arithmetic_cases=len(rows),whole_cache_cases=len(whole),factory_cases=len(factories),scope='Original held-slot queries and Whip contribution, ordinary shot-speed cache before mod callback, and final global minimum. Other modifiers empty. Native pickup factory with supplied fresh enabled pools [27], [39], [27,39] and supplied pool RNG seeds; no complete pool/depletion/refill/seed-stream acceptance. Existing custom Shot Speed below native minimum remains a DW testing override. Golden/swallowed/Moms Box, character/status/mod callbacks, complete cache scheduler and actor physics unaccepted.',full_native_acceptance=False),indent=2)+'\n').encode())
 print('PASS',len(rows),'native Whip arithmetic;',len(whole),'whole ordinary cache;',len(factories),'bounded factory cases')
if __name__=='__main__':main()
