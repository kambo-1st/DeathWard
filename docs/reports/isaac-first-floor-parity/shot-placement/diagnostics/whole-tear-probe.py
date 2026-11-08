import importlib.util,pefile,struct
from collections import deque
from unicorn import UC_HOOK_CODE,UC_HOOK_MEM_INVALID
from unicorn.x86_const import *
s=importlib.util.spec_from_file_location('sp','scripts/isaac-reference/analyze-shot-placement.py');sp=importlib.util.module_from_spec(s);s.loader.exec_module(sp)
raw=sp.A.M.EXE.read_bytes();x=sp.NativePlacement(pefile.PE(data=raw),raw);f,n,u,p,t=x.f,x.n,x.u,x.p,x.t
x.reset(pos=(100,50));f.write(f.ROOM+4,f.ROOM+0x1000);f.write(f.ROOM+0x1010,f.ROOM+0x2000);f.write(f.ROOM+0x2048,1)
for off,val in [(0x14,0),(0x18,0),(0x1c,640),(0x20,560)]:n.write_float(f.ROOM+off,val)
f.write(t,0xb46a88);f.write(t+0x28,2);f.write(t+0x314,p);f.write(t+0x320,p);f.write(p,0xb4d4f0);u.mem_write(t+0x16a,b'\1')
for off,val in [(0x294,100),(0x298,50),(0x2b8,10),(0x2bc,0),(0x2c0,1),(0x2c4,1),(0x2f4,1),(0x2e0,3.5),(0x2c8,7),(0x360,-23.75),(0x364,.1),(0x370,1),(0x374,1),(0x770,260)]:n.write_float(t+off,val)
for actor,at in [(p,p+0x8000),(t,p+0x9000)]:
 for off in [0,4,8]:f.write(at+off,at)
 u.mem_write(at+0xc,b'\1\1');f.write(actor+0x324,at)
def assertion(uc,pc,size,data):
 if pc!=0x95e330:return
 ss=uc.reg_read(UC_X86_REG_ESP);values=struct.unpack('<4I',uc.mem_read(ss,16));print('ASSERT',list(map(hex,values)))
 for ptr in values[1:]:
  if 0x400000<=ptr<0xc90000:
   text=bytes(uc.mem_read(ptr,200)).split(b'\0')[0];print('TEXT',repr(text))
 raise RuntimeError('native diagnostic boundary reached; no skipped assertions')
u.hook_add(UC_HOOK_CODE,assertion,begin=0x95e330,end=0x95e330)
def formatter(uc,pc,size,data):
 ss=uc.reg_read(UC_X86_REG_ESP);values=struct.unpack('<4I',uc.mem_read(ss,16));print('FORMAT_CALL',list(map(hex,values)), 'ECX',hex(uc.reg_read(UC_X86_REG_ECX)),'EDX',hex(uc.reg_read(UC_X86_REG_EDX)))
 for ptr in [uc.reg_read(UC_X86_REG_ECX),uc.reg_read(UC_X86_REG_EDX),*values[1:]]:
  if 0x400000<=ptr<0xc90000:print('FORMAT_TEXT',repr(bytes(uc.mem_read(ptr,160)).split(b'\0')[0]))
 raise RuntimeError('unresolved formatting boundary observed; original actor not accepted')
u.hook_add(UC_HOOK_CODE,formatter,begin=0x411f70,end=0x411f70)
recent=deque(maxlen=25);u.hook_add(UC_HOOK_CODE,lambda uc,a,size,data:recent.append(hex(a)))
def bad(uc,access,address,size,value,data):print('MEM',hex(uc.reg_read(UC_X86_REG_EIP)),hex(address));return False
u.hook_add(UC_HOOK_MEM_INVALID,bad)
try:x.call(0x642990,t);print('PASS',[(hex(o),n.read_float(t+o)) for o in [0x294,0x298,0x360,0x364]],'imports',f.import_counts)
except Exception as e:print(type(e).__name__,e,'EIP',hex(u.reg_read(UC_X86_REG_EIP)),'recent',list(recent))
