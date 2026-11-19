#!/usr/bin/env python3
"""Execute the pinned ordinary shopkeeper drop selector with supplied item eligibility."""
from pathlib import Path
import argparse,importlib.util,hashlib,json,struct,csv,io
import pefile,capstone
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import *
spec=importlib.util.spec_from_file_location('awards',Path(__file__).with_name('analyze-room-awards.py'));A=importlib.util.module_from_spec(spec);spec.loader.exec_module(A)
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==A.M.SHA;pe=pefile.PE(data=raw);f=A.NativeAwards(pe,raw);n=f.n;u=f.u;b=n.ebp;actor=f.HEAP+0x10000;frame=b+0x1000
 out=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d14a11-shopkeeper/source';out.mkdir(parents=True,exist_ok=True)
 rows=[];spawns=[];available=set()
 def hook(u,a,size,data):
  if a==0x698d8a:u.emu_stop();return
  sp=u.reg_read(UC_X86_REG_ESP);ret=f.integer(sp);val=0
  if a==0x701bd0:val=int(f.integer(sp+4) in available);cleanup=12
  else:
   v=struct.unpack('<5I',u.mem_read(sp+4,20));spawns.append(v);cleanup=20
  u.reg_write(UC_X86_REG_EAX,val);u.reg_write(UC_X86_REG_ESP,sp+4+cleanup);u.reg_write(UC_X86_REG_EIP,ret)
 for a in [0x698d8a,0x701bd0,0x68f5d0]:u.hook_add(UC_HOOK_CODE,hook,begin=a,end=a)
 # Execute the source entity initialization slice; it seeds DropRNG from InitSeed.
 for seed in [1,6,42,12345,0x80000000,0xffffffff]:
  u.reg_write(UC_X86_REG_EBP,b);u.reg_write(UC_X86_REG_ESP,b-0x2000);u.reg_write(UC_X86_REG_ECX,actor)
  for offset,value in [(8,17),(12,1),(16,4),(20,seed)]:f.write(b+offset,value)
  u.emu_start(0x6819e6,0x681a26,count=1000);assert struct.unpack('<4I',u.mem_read(actor+0x334,16))==(seed,4,3,17)
 for mask in [0,1,3,7]:
  available={item for bit,item in enumerate([64,429,521]) if mask&(1<<bit)};u.mem_write(f.MANAGER+0x1b8,bytes([int(521 in available)]))
  for seed in [((i+1)*0x9e3779b9)&0xffffffff for i in range(1024)]+[1,6,20,42,12345,0xffffffff]:
   spawns.clear();u.reg_write(UC_X86_REG_EBP,b);u.reg_write(UC_X86_REG_EBX,frame);u.reg_write(UC_X86_REG_ESI,actor);u.reg_write(UC_X86_REG_ESP,b-0x2000);f.write(b-0x40,actor);u.mem_write(frame+12,b'\x01');f.write(actor+0x2c,1);u.mem_write(actor+0x334,struct.pack('<4I',seed,4,3,17))
   u.emu_start(0x698988,0x698d8a,count=100000);assert u.reg_read(UC_X86_REG_EIP)==0x698d8a
   assert len(spawns)<=2
   for v in spawns:assert (v[0],v[1],v[2]) in [(5,100,64),(5,100,429),(5,100,521),(5,20,0),(85,0,0)]
   padded=spawns+[(0,0,0,0,0)]*(2-len(spawns));rows.append([seed,mask,len(spawns),*[v for s in padded for v in s[:4]],f.integer(actor+0x334)])
 def save(name,data):
  p=out/name
  if args.check:assert p.read_bytes()==data,name
  else:p.write_bytes(data)
 buf=io.StringIO();w=csv.writer(buf,lineterminator='\n');w.writerow(['seed','eligible_mask','count','type0','variant0','subtype0','seed0','type1','variant1','subtype1','seed1','after_seed']);w.writerows(rows);save('native-drops.csv',buf.getvalue().encode())
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
 for name,a,z in [('entity-drop-rng-init',0x6819e6,0x681a26),('ordinary-drops',0x698988,0x698b6d),('drop-tail',0x698d72,0x698d98),('keeper-controller',0x698fb0,0x6994cd),('vulnerable-query',0x684630,0x6846da)]:
  blob=pe.get_data(a-0x400000,z-a);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,a))+'\n').encode());windows.append(dict(name=name,start=hex(a),end=hex(z),sha256=hashlib.sha256(blob).hexdigest()))
 manifest=dict(baseline='Repentance1.7.9b',executable_sha256=A.M.SHA,cases=len(rows),windows=windows,scope='Original ordinary variant1 numeric/RNG/drop decisions and seed requests. Item availability is supplied; collection append is observed. Six original entity-initialization slices verify DropRNG=InitSeed and shift tuple4/3/17. DW descriptor seed and factory order remain adaptations. Full damage/factory/spider trajectory/physics/keeper scheduler/unlocks/global RNG are not accepted.',production_eligible_items=[64],unimplemented_rare_items=[429,521],full_native_acceptance=False)
 save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode());print('PASS',len(rows),'native ordinary keeper outcomes with four eligibility profiles')
if __name__=='__main__':main()
