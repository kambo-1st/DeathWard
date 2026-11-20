#!/usr/bin/env python3
"""Ordinary battery collection/charge arithmetic, stock identity and price from pinned 1.7.9b."""
import argparse,csv,hashlib,importlib.util,io,json,struct
from pathlib import Path
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import *
spec=importlib.util.spec_from_file_location('health',Path(__file__).with_name('analyze-player-health.py'));H=importlib.util.module_from_spec(spec);spec.loader.exec_module(H)
spec=importlib.util.spec_from_file_location('awards',Path(__file__).with_name('analyze-room-awards.py'));A=importlib.util.module_from_spec(spec);spec.loader.exec_module(A)
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args();raw=H.MOTION.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==H.MOTION.SHA
 pe=H.pefile.PE(data=raw);f=H.NativeHealth(pe);n=f.native;u=f.u;out=H.MOTION.ROOT/'docs/reports/isaac-first-floor-parity/d14a16-shop-batteries/source';out.mkdir(parents=True,exist_ok=True)
 def save(name,data):
  if args.check:assert (out/name).read_bytes()==data,name
  else:(out/name).write_bytes(data)
 def table(name,header,rows):
  s=io.StringIO();w=csv.writer(s,lineterminator='\n');w.writerow(header);w.writerows(rows);save(name,s.getvalue().encode())
 def hook(u,a,size,data):
  if a==0x758357:u.reg_write(UC_X86_REG_EIP,0x75825d) # Charge HUD/audio only; preserve original arithmetic/return.
  if a in (0x6c0db8,0x6c1f4c):u.emu_stop() # Before achievement/collection visuals or rejected pickup tail.
 u.hook_add(UC_HOOK_CODE,hook);rows=[]
 for item,capacity in [(0,0),(45,4),(58,3),(135,0)]:
  for before in range(capacity+1):
   f.reset();definition=f.ITEMS+0x10000+item*0x200;f.write(definition+0x74,capacity);f.write(definition+0xac,0)
   f.write(n.PLAYER+0x14c4,item);f.write(n.PLAYER+0x14c8,before)
   pickup=f.ITEMS+0xe0000;f.write(pickup+0x30,1);sp=n.STACK+0x9000;b=n.ebp
   u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_EBP,b);u.reg_write(UC_X86_REG_EDI,n.PLAYER);u.reg_write(UC_X86_REG_ESI,pickup);u.mem_write(b-0x6d,b'\0')
   u.emu_start(0x6c0cfe,n.STOP,count=200000);pc=u.reg_read(UC_X86_REG_EIP);assert pc in (0x6c0db8,0x6c1f4c),hex(pc)
   after=struct.unpack('<I',u.mem_read(n.PLAYER+0x14c8,4))[0];accepted=int(pc==0x6c0db8);assert after==min(capacity,before+6) and accepted==int(before<capacity),(item,before,after,accepted)
   rows.append([item,capacity,before,after,accepted])
 table('native-charge.csv',['item','capacity','before','after','accepted'],rows)
 # Original primary-charge API at other supplied room-charge capacities; battery amount is6.
 charges=[]
 for capacity in (1,2,3,4,6,12):
  for before in range(capacity+1):
   for amount in (1,2,6,12):
    f.reset();f.write(f.ITEMS+0x10000+45*0x200+0x74,capacity);f.write(n.PLAYER+0x14c4,45);f.write(n.PLAYER+0x14c8,before)
    sp=n.STACK+0x9000;u.mem_write(sp,struct.pack('<6I',n.STOP,amount,0,1,0,0));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,n.PLAYER)
    u.emu_start(0x758030,n.STOP,count=200000);assert u.reg_read(UC_X86_REG_EIP)==n.STOP
    after=struct.unpack('<I',u.mem_read(n.PLAYER+0x14c8,4))[0];changed=u.reg_read(UC_X86_REG_EAX);assert after==min(capacity,before+amount) and changed==after-before
    charges.append([capacity,before,amount,after,changed])
 table('native-capacity.csv',['capacity','before','amount','after','changed'],charges)
 g=A.NativeAwards(pe,raw);u=g.u;n=g.n;g.write(g.ROOM+8,2);g.write(g.ROOM+4,g.ROOM+0x1000);prices=[]
 for seed in (1,42,12345,0x7fffffff,0xffffffff):
  g.write(g.ROOM+0x1058,seed)
  for slot in range(6):
   sp=n.STACK+0x9000;u.mem_write(sp,struct.pack('<4I',n.STOP,90,1,slot));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,g.ROOM);g.run(0x7d0950);price=u.reg_read(UC_X86_REG_EAX);assert price==5;prices.append([seed,slot,price])
 table('native-prices.csv',['seed','slot','price'],prices)
 # Shop category5 resolver; no unrelated item/variant factory is replaced.
 resolves=[]
 for slot in range(6):
  u.mem_write(g.ROOM+0x1094+slot*2,struct.pack('<h',5));vo,so=g.HEAP+0x300000,g.HEAP+0x300004
  sp=n.STACK+0x9000;u.mem_write(sp,struct.pack('<5I',n.STOP,slot,vo,so,12345));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,g.ROOM);g.run(0x7d04a0)
  variant,subtype=g.integer(vo),g.integer(so);assert (variant,subtype)==(90,1),(variant,subtype);resolves.append([slot,5,variant,subtype])
 table('native-stock.csv',['slot','category','variant','subtype'],resolves)
 windows=[];md=H.capstone.Cs(3,4)
 for name,a,z in [('battery-collection',0x6c0cf5,0x6c0dd7),('add-charge',0x758030,0x7583ca)]:
  blob=pe.get_data(a-0x400000,z-a);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,a))+'\n').encode());windows.append(dict(name=name,start=hex(a),end=hex(z),sha256=hashlib.sha256(blob).hexdigest()))
 save('manifest.json',(json.dumps(dict(executable_sha256=H.MOTION.SHA,collection_cases=len(rows),capacity_cases=len(charges),price_cases=len(prices),stock_cases=len(resolves),windows=windows,scope='Original ordinary battery collection branch and AddActiveCharge with supplied empty-inventory primary active state; HUD/audio skipped after charge write, stop before achievement/collect visual or rejection tail. Original ordinary stock category and price routines. No Battery passive, alternate slots, timed/item-specific capacities, full native contact/factory/shop payment scheduler/physics or profile acceptance.'),indent=2)+'\n').encode());print('PASS',len(rows),'collection',len(charges),'capacity',len(prices),'price',len(resolves),'stock cases')
if __name__=='__main__':main()
