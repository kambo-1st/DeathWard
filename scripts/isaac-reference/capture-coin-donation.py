#!/usr/bin/env python3
"""Execute bounded Repentance coin-deposit and withdrawal arithmetic; host presentation/profile endpoints."""
import argparse,csv,hashlib,importlib.util,io,json,struct
from pathlib import Path
import pefile,capstone
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import *
spec=importlib.util.spec_from_file_location('awards',Path(__file__).with_name('analyze-room-awards.py'));A=importlib.util.module_from_spec(spec);spec.loader.exec_module(A)
def main():
 p=argparse.ArgumentParser();p.add_argument('--check',action='store_true');args=p.parse_args()
 raw=A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==A.M.SHA
 pe=pefile.PE(data=raw);f=A.NativeAwards(pe,raw);u,n=f.u,f.n;b=n.ebp;actor=f.HEAP+0x10000;player=actor+0x10000
 out=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d14a14-coin-donation/source';out.mkdir(parents=True,exist_ok=True);state={}
 def save(name,data):
  if args.check:assert (out/name).read_bytes()==data,name
  else:(out/name).write_bytes(data)
 def csvfile(name,head,rows):
  buf=io.StringIO();w=csv.writer(buf,lineterminator='\n');w.writerow(head);w.writerows(rows);save(name,buf.getvalue().encode())
 def ret(clean=0,value=0):
  sp=u.reg_read(UC_X86_REG_ESP);to=f.integer(sp);u.reg_write(UC_X86_REG_ESP,sp+4+clean);u.reg_write(UC_X86_REG_EAX,value);u.reg_write(UC_X86_REG_EIP,to)
 def host(u,at,size,data):
  sp=u.reg_read(UC_X86_REG_ESP)
  if at==0x419b50:ret(4,actor+0x3c)
  elif at==0x405e90:ret(value=1)
  elif at==0x41c4a0:ret(value=f.MANAGER+0x14)
  elif at==0x41e720:ret(4,f.integer(f.MANAGER+0x31c))
  elif at==0x884e40:
   assert f.integer(sp+4)==20
   amount=struct.unpack('<i',u.mem_read(sp+8,4))[0];f.write(f.MANAGER+0x31c,f.integer(f.MANAGER+0x31c)+amount);ret(8)
  elif at==0x776b60:state['luck']+=1;ret(4)
  elif at in (0x405850,0x405950,0x4054f0,0x73b950):ret(8)
  elif at==0x884c80:ret(4)
  elif at==0x8b1480:ret(16)
  elif at==0x639170:ret(value=0xb468f8)
  elif at==0x6c3d90:ret(value=42)
  elif at==0x422e20:ret(28,actor+0x2000)
  elif at==0x63dbb9:
   # Overflow throwing/placement loop is outside this numeric harness.
   for _ in range(15):
    v=f.integer(actor+0x334);v^=v>>4;v^=(v<<3)&0xffffffff;v^=v>>17;f.write(actor+0x334,v)
   u.reg_write(UC_X86_REG_EIP,0x63dcba)
 for at in [0x419b50,0x405e90,0x41c4a0,0x41e720,0x884e40,0x776b60,0x405850,0x405950,0x4054f0,0x73b950,0x884c80,0x8b1480,0x639170,0x6c3d90,0x422e20,0x63dbb9]:u.hook_add(UC_HOOK_CODE,host,begin=at,end=at)
 deposits=[];withdraw=[]
 for i in range(256):
  seed=((i+1)*0x9e3779b9)&0xffffffff
  for bank,run,held in [(0,0,0),(17,10,60),(998,25,120),(999,666,150),(1248,99,200)]:
   state['luck']=0;f.write(f.MANAGER+0x31c,bank);f.write(f.GAME+0x1c318c,run);f.write(f.GAME+0x1c3168,0);f.write(f.GAME+0x1c316c,0)
   f.write(actor+0x360,2);u.mem_write(actor+0x376,struct.pack('<H',held));u.mem_write(actor+0x334,struct.pack('<4I',seed,4,3,17))
   f.write(b-0xa0,player);f.write(b-0xb8,actor)
   for reg,value in [(UC_X86_REG_EBP,b),(UC_X86_REG_ESP,b-0x2000),(UC_X86_REG_EDI,actor),(UC_X86_REG_EBX,actor+0x334)]:u.reg_write(reg,value)
   u.emu_start(0x63d880,0x63e3fe,count=100000)
   assert u.reg_read(UC_X86_REG_EIP)==0x63e3fe
   deposits.append([seed,bank,run,held,f.integer(f.MANAGER+0x31c),f.integer(f.GAME+0x1c318c),state['luck'],f.integer(actor+0x360),struct.unpack('<H',u.mem_read(actor+0x36a,2))[0],f.integer(f.GAME+0x1c3168),f.integer(actor+0x334)])
  for bank in [0,1,2,7,14,999,1000,1007]:
   f.write(f.MANAGER+0x31c,bank);f.write(actor+0x360,1);u.mem_write(actor+0x334,struct.pack('<4I',seed,4,3,17))
   for reg,value in [(UC_X86_REG_EBP,b),(UC_X86_REG_ESP,b-0x2000),(UC_X86_REG_EBX,actor)]:u.reg_write(reg,value)
   u.emu_start(0x6400e6,0x640151,count=10000)
   after=f.integer(f.MANAGER+0x31c);withdraw.append([seed,bank,bank-after,max(0,bank-after-1),after,f.integer(actor+0x334)])
 csvfile('native-deposits.csv',['seed','bank','run','held','bank_after','run_after','luck','state','cooldown','flags','rng_after'],deposits)
 csvfile('native-withdrawals.csv',['seed','bank','withdrawn','coins','bank_after','rng_after'],withdraw)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
 for name,start,end in [('deposit',0x63d880,0x63dda2),('withdraw',0x640070,0x640586),('jam-immunity',0x64087e,0x64088d),('counters',0x6d6c80,0x6d6ca0),('bank-store',0x884e40,0x884e87),('luck-store',0x776b60,0x776b7f),('contact-animation',0x63eff8,0x63f04b),('held-counter',0x63e6b9,0x63e6e1)]:
  blob=pe.get_data(start-0x400000,end-start);save(name+'.asm',('\n'.join(f'{x.address:08x} {x.mnemonic} {x.op_str}'.rstrip() for x in md.disasm(blob,start))+'\n').encode());windows.append(dict(name=name,start=hex(start),end=hex(end),sha256=hashlib.sha256(blob).hexdigest()))
 save('manifest.json',(json.dumps(dict(executable_sha256=A.M.SHA,deposit_cases=len(deposits),withdrawal_cases=len(withdraw),windows=windows,scope='Original deposit counter arithmetic, normal RNG luck/jam decisions, held cooldown and overflow flag; original withdrawal count arithmetic. Bank/profile/achievement/visual endpoints hosted; bank-store assembly pinned separately. Overflow throwing loop hosted with 15 child seed draws; physical pickup factories, animation scheduling, contact counters and prior RNG history not fully executed. Ordinary Karma absent. Full native equivalence remains open.'),indent=2)+'\n').encode());print('PASS',len(deposits),'deposits;',len(withdraw),'withdrawals')
if __name__=='__main__':main()
