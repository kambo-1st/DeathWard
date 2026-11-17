#!/usr/bin/env python3
"""Pinned ordinary fireplace/poop drop selectors and three complete room records."""
import argparse,csv,hashlib,importlib.util,io,json,struct
from pathlib import Path
import pefile,capstone
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import *
spec=importlib.util.spec_from_file_location('awards',Path(__file__).with_name('analyze-room-awards.py'));A=importlib.util.module_from_spec(spec);spec.loader.exec_module(A)
spec=importlib.util.spec_from_file_location('audit',Path(__file__).with_name('audit-live-floor.py'));R=importlib.util.module_from_spec(spec);spec.loader.exec_module(R)
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args();raw=A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==A.M.SHA
 pe=pefile.PE(data=raw);f=A.NativeAwards(pe,raw);u=f.u;n=f.n;b=n.ebp;out=A.M.ROOT/'docs/reports/isaac-first-floor-parity/ordinary-room-props/source'
 if not args.check:out.mkdir(parents=True,exist_ok=True)
 def save(name,data):
  if args.check:assert (out/name).read_bytes()==data,name
  else:(out/name).write_bytes(data)
 result=None
 def stop(u,pc,size,data):
  nonlocal result
  sp=u.reg_read(UC_X86_REG_ESP)
  if pc==0x6a79e8:result=(f.integer(sp+4),f.integer(sp+12))
  elif pc==0x6e82c1:result=(f.integer(sp+4),f.integer(sp+24))
  else:result=(0,0)
  u.emu_stop()
 for pc in (0x6a79e8,0x6a79f0,0x6e82c1,0x6e8374):u.hook_add(UC_HOOK_CODE,stop,begin=pc,end=pc)
 rows=[]
 for kind in ('fire','poop'):
  for seed in [(i*0x9e3779b9)&0xffffffff for i in range(1,513)]:
   u.mem_write(b-0x1000,b'\0'*0x1200);u.reg_write(UC_X86_REG_EBP,b);u.reg_write(UC_X86_REG_ESP,b-0x1000);result=None
   f.write(f.GAME+0x1ad58,f.MANAGER)
   if kind=='fire':
    rng=n.STACK+0x300;u.mem_write(rng,struct.pack('<4I',seed,1,11,6));u.reg_write(UC_X86_REG_ESI,rng);start=0x6a78a8
   else:
    for offset,value in [(-0x28,1),(-0x24,5),(-0x30,16),(-0x18,1),(-0xc,n.PLAYER)]:f.write(b+offset,value)
    u.reg_write(UC_X86_REG_EDI,seed);u.reg_write(UC_X86_REG_ESI,1);start=0x6e7f7e
   u.emu_start(start,n.STOP,count=100000);assert result is not None,hex(u.reg_read(UC_X86_REG_EIP))
   variant,pickup_seed=result
   subtype=0
   if variant:resolved,subtype=f.pickup(pickup_seed,variant,False);assert resolved==variant
   rows.append([kind,seed,variant,pickup_seed,subtype])
 buf=io.StringIO();w=csv.writer(buf,lineterminator='\n');w.writerow(['kind','seed','variant','pickup_seed','subtype']);w.writerows(rows);save('native-drops.csv',buf.getvalue().encode())
 rooms,stb=R.read_stb(R.SOURCE/'rooms/01.basement.stb');selected=[r for r in rooms if r['type']==1 and r['variant'] in (26,52,633) and r['subtype']==0];assert len(selected)==3
 save('rooms.json',(json.dumps(dict(source=stb,rooms=selected),indent=2)+'\n').encode())
 windows=[];md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 for name,start,end in [('fire-drops',0x6a7839,0x6a79f0),('poop-drops',0x6e7f7e,0x6e8374),('fire-hit-loss',0x6a8134,0x6a822e),('poop-hit-loss',0x6e646a,0x6e64d8)]:
  data=pe.get_data(start-0x400000,end-start);windows.append(dict(name=name,start=hex(start),end=hex(end),sha256=hashlib.sha256(data).hexdigest()));save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(data,start))+'\n').encode())
 save('manifest.json',(json.dumps(dict(executable_sha256=A.M.SHA,drop_cases=len(rows),windows=windows,scope='Original ordinary Normal-mode drop branch and pickup subtype resolver; no held drop modifiers or rare unlocks. Fire supplied drop RNG1/11/6, poop grid RNG1/5/16. Stops before world spawning; full native constructor/global seed mapping, special variants and modifier wrappers remain open.',full_native_acceptance=False),indent=2)+'\n').encode());print('PASS',len(rows),'native ordinary fire/poop drop cases; three complete source rooms')
if __name__=='__main__':main()
