#!/usr/bin/env python3
"""Pinned ordinary shop grab-bag identity, price and complete numeric contents branch."""
import argparse,csv,hashlib,importlib.util,io,json,struct
from pathlib import Path
import capstone,pefile
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import *
spec=importlib.util.spec_from_file_location('awards',Path(__file__).with_name('analyze-room-awards.py'));A=importlib.util.module_from_spec(spec);spec.loader.exec_module(A)
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==A.M.SHA
 pe=pefile.PE(data=raw);f=A.NativeAwards(pe,raw);u,n=f.u,f.n;b=n.ebp;actor=f.HEAP+0x300000;rng=actor+0x334
 out=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d14a17-shop-grab-bags/source';out.mkdir(parents=True,exist_ok=True)
 def save(name,data):
  if args.check:assert (out/name).read_bytes()==data,name
  else:(out/name).write_bytes(data)
 def table(name,head,rows):
  s=io.StringIO();w=csv.writer(s,lineterminator='\n');w.writerow(head);w.writerows(rows);save(name,s.getvalue().encode())
 spawns=[]
 def append(u,addr,size,data):
  sp=u.reg_read(UC_X86_REG_ESP);spawns.append(struct.unpack('<5I',u.mem_read(sp+4,20)))
  u.reg_write(UC_X86_REG_EAX,0);u.reg_write(UC_X86_REG_EIP,f.integer(sp));u.reg_write(UC_X86_REG_ESP,sp+24)
 u.hook_add(UC_HOOK_CODE,append,begin=0x68f5d0,end=0x68f5d0)
 rows=[]
 seeds=[1,2,7,15,42,12345,0x7fffffff,0xffffffff]+[(i*0x9e3779b9)&0xffffffff for i in range(1,513)]
 for seed in seeds:
  f.heap_cursor=f.HEAP;f.allocations.clear();spawns.clear()
  u.reg_write(UC_X86_REG_EBP,b);u.reg_write(UC_X86_REG_ESP,b-0x2000);u.reg_write(UC_X86_REG_ESI,rng);u.reg_write(UC_X86_REG_EDI,69)
  f.write(b-0xa4,actor);f.write(actor+0x30,1);u.mem_write(rng,struct.pack('<4I',seed,4,3,17))
  u.emu_start(0x6b3179,0x6b3650,count=200000);assert u.reg_read(UC_X86_REG_EIP)==0x6b3650
  assert len(spawns) in (2,3) and all(t==5 and v in (20,30,40,90,300) and sub==0 for t,v,sub,_,_ in spawns)
  padded=spawns+[(0,0,0,0,0)]*(3-len(spawns));rows.append([seed,len(spawns),*[x for p in padded for x in p[1:4]],f.integer(rng)])
 table('native-contents.csv',['seed','count','variant0','subtype0','seed0','variant1','subtype1','seed1','variant2','subtype2','seed2','after_seed'],rows)
 # Actual category7 resolution and ordinary price; no pool calls are replaced.
 f.write(f.ROOM+8,2);f.write(f.ROOM+4,f.ROOM+0x1000);resolved=[];prices=[]
 for seed in seeds[:8]:
  f.write(f.ROOM+0x1058,seed)
  for slot in range(6):
   u.mem_write(f.ROOM+0x1094+slot*2,struct.pack('<h',7));vo,so=actor+0x1000,actor+0x1004;sp=n.STACK+0x9000
   u.mem_write(sp,struct.pack('<5I',n.STOP,slot,vo,so,seed));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,f.ROOM);f.run(0x7d04a0)
   assert (f.integer(vo),f.integer(so))==(69,1);resolved.append([seed,slot,7,69,1])
   u.mem_write(sp,struct.pack('<4I',n.STOP,69,1,slot));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,f.ROOM);f.run(0x7d0950)
   price=u.reg_read(UC_X86_REG_EAX);assert price==7;prices.append([seed,slot,price])
 table('native-stock.csv',['seed','slot','category','variant','subtype'],resolved);table('native-prices.csv',['seed','slot','price'],prices)
 md=capstone.Cs(3,4);windows=[]
 for name,a,z in [('contents',0x6b3179,0x6b3673),('collection',0x6c1b65,0x6c1dba),('stock-bag',0x7d0649,0x7d0669),('stock-trinket',0x7d0766,0x7d0784),('ordinary-price',0x7d0d19,0x7d0d33)]:
  blob=pe.get_data(a-0x400000,z-a);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,a))+'\n').encode());windows.append(dict(name=name,start=hex(a),end=hex(z),sha256=hashlib.sha256(blob).hexdigest()))
 save('manifest.json',(json.dumps(dict(executable_sha256=A.M.SHA,contents_cases=len(rows),stock_cases=len(resolved),price_cases=len(prices),category7='Grab Bag5.69.1',category11='Trinket5.350',weights={'40':15,'30':20,'20':15,'90':4,'300':4},windows=windows,scope='Original ordinary subtype1 bag branch, native vector/weighted selection/RNG and all ordered spawn requests; append only is observed instead of creating entities. Supplied initial DropRNG4/3/17; descriptor mapping, downstream subtype/card pool, native actors/payment/physics/scheduler and special sacks are separate.'),indent=2)+'\n').encode());print('PASS',len(rows),'native contents,',len(resolved),'stock,',len(prices),'prices')
if __name__=='__main__':main()
