#!/usr/bin/env python3
"""Bounded native Spider burst/idle and Pooter ordinary wandering execution.

Spider destinations and Pooter random draws are supplied. No whole-controller
RNG, acquisition, collision, live scheduler or attack acceptance is claimed.
"""
import argparse,csv,ctypes,hashlib,importlib.util,io,json,math,struct
from pathlib import Path
import pefile,capstone,xml.etree.ElementTree as ET
from unicorn.x86_const import *
s=importlib.util.spec_from_file_location('motion',Path(__file__).with_name('analyze-player-motion.py'));M=importlib.util.module_from_spec(s);s.loader.exec_module(M)
OUT=M.ROOT/'docs/reports/isaac-first-floor-parity/spider-pooter-movement'
def f(x):return struct.unpack('<f',struct.pack('<f',x))[0]
lib=ctypes.CDLL('libm.so.6')
for name in ['cosf','sinf']:getattr(lib,name).argtypes=[ctypes.c_float];getattr(lib,name).restype=ctypes.c_float
class Draws:
 def __init__(self):self.state=123456
 def next(self):
  mask=(1<<64)-1;self.state=(self.state+0x9e3779b97f4a7c15)&mask;z=self.state;z=((z^(z>>30))*0xbf58476d1ce4e5b9)&mask;z=((z^(z>>27))*0x94d049bb133111eb)&mask;return z^(z>>31)
 def bounded(self,n):
  threshold=((1<<64)-n)%n
  while True:
   z=self.next()
   if z>=threshold:return z%n
 def angle(self):return f(f(f(2*f(math.pi))*f(self.next()>>40))/16777216)
def main():
 ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--check',action='store_true');a=ap.parse_args();raw=M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==M.SHA;pe=pefile.PE(data=raw);rows=[];gates=[];pooters=[]
 def setup(n):
  n.u.reg_write(UC_X86_REG_EDI,n.PLAYER);n.u.reg_write(UC_X86_REG_ESI,n.PLAYER);n.u.reg_write(UC_X86_REG_EBP,n.ebp);n.u.reg_write(UC_X86_REG_ESP,n.STACK+0x6000)
 def word(n,address,value):n.u.mem_write(address,struct.pack('<I',value&0xffffffff))
 for counter in range(16):
  n=M.NativeMotion(pe);setup(n);word(n,n.PLAYER+0x360,counter);word(n,n.ebp-0x44,1);n.run(0x517db0,0x517dca if counter>13 else 0x5183b5);gates.append([counter,struct.unpack('<i',n.u.mem_read(n.PLAYER+0x360,4))[0],int(n.u.reg_read(UC_X86_REG_EIP)==0x517dca)])
 for name,target,velocity,counter in [('idle',None,2,0),('burst-far',(500,280),0,20),('burst-arrival',(330,280),0,20),('burst-stuck',(500,280),0,0)]:
  n=M.NativeMotion(pe);p=n.PLAYER;b=n.ebp
  for off,value in [(0x294,320),(0x298,280),(0x2b8,velocity),(0x2c0,1),(0x2c4,1),(0x2f4,1),(0x28c,target[0]if target else 0),(0x290,target[1]if target else 0)]:n.write_float(p+off,value)
  word(n,p+0x360,counter)
  for k in range(12):
   setup(n);word(n,b-0x44,1)
   if n.read_float(p+0x28c)!=0 or n.read_float(p+0x290)!=0:
    n.run(0x518267,0x518270);n.write_float(b-0x3c,6);n.run(0x51845f,0x5183cd)
   else:n.run(0x517db0,0x5183cd)
   setup(n);n.run(0x686406,0x686497)
   rows.append([name,k,velocity,counter,int(n.read_float(p+0x28c)!=0 or n.read_float(p+0x290)!=0),struct.unpack('<i',n.u.mem_read(p+0x360,4))[0],*[n.read_float(p+off)for off in [0x294,0x298,0x2b8,0x2bc]]])
 for name,x,y,cooldown in [('centre',320,280,0),('top',320,160,0),('bottom',320,410,0),('left',70,280,0),('right',570,280,0),('cooldown',320,280,35)]:
  n=M.NativeMotion(pe);p=n.PLAYER;u=n.u;game=0x4000000;u.mem_map(game,0x200000);word(n,0xbfd65c,game);draws=Draws()
  for off,value in [(0x294,x),(0x298,y),(0x2b8,-4 if name=='right' else 2),(0x2bc,-2 if name=='bottom' else 1),(0x2c0,1),(0x2c4,1),(0x2f4,1),(0xb00,.2),(0xb04,.1)]:n.write_float(p+off,value)
  for k in range(1,25):
   setup(n);u.reg_write(UC_X86_REG_EDI,game);word(n,game+0x1a30dc,k)
   if cooldown:
    word(n,p+0xaf0,cooldown);u.reg_write(UC_X86_REG_EDX,cooldown);n.write_float(p+0x2fc,k);n.write_float(p+0x2f8,k-1);n.run(0x4f5d63,0x4f5dc5);cooldown-=1
   pursuit=draws.bounded(5)==0
   if pursuit:
    target=p+0x9000;n.write_float(target+0x294,1000);n.write_float(target+0x298,280);u.reg_write(UC_X86_REG_EAX,target);n.run(0x4f6c8b,0x4f6d0e)
   if k%4==1:
    angle=draws.angle();vector=p+0x9100;n.write_float(vector,lib.cosf(angle));n.write_float(vector+4,-lib.sinf(angle));u.reg_write(UC_X86_REG_EAX,vector);n.run(0x4f6d37,0x4f6e78)
   else:u.reg_write(UC_X86_REG_ECX,k);n.run(0x4f6d89,0x4f6e78)
   setup(n);n.run(0x686406,0x686497)
   pooters.append([name,k,x,y,35 if name=='cooldown'else 0,int(pursuit),str(draws.state),*[n.read_float(p+off)for off in [0x294,0x298,0x2b8,0x2bc,0xb00,0xb04]]])
 OUT.mkdir(parents=True,exist_ok=True)
 def save(name,data):
  p=OUT/name
  if a.check:assert p.read_bytes()==data,name
  else:p.write_bytes(data)
 for name,header,data in [('spider-gates.csv',['old_counter','new_counter','selection_due'],gates),('spider-native.csv',['case','update','initial_vx','initial_counter','target_ready','counter','x','y','vx','vy'],rows),('pooter-native.csv',['case','update','initial_x','initial_y','initial_cooldown','pursuit','draw_state','x','y','vx','vy','wander_x','wander_y'],pooters)]:
  stream=io.StringIO(newline='');w=csv.writer(stream,lineterminator='\n');w.writerow(header);w.writerows(data);save(name,stream.getvalue().encode())
 windows=[];md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 for name,start,end in [('spider-idle',0x517db0,0x517dca),('spider-counter',0x518267,0x518270),('spider-stop-impulse',0x51845f,0x518578),('spider-retention',0x5183a5,0x5183cd),('pooter-cooldown',0x4f5d63,0x4f5dc5),('pooter-pursuit',0x4f6c8b,0x4f6d0e),('pooter-wander',0x4f6d37,0x4f6e78)]:
  blob=pe.get_data(start-0x400000,end-start);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip()for i in md.disasm(blob,start))+'\n').encode());windows.append(dict(name=name,sha256=hashlib.sha256(blob).hexdigest()))
 xml=M.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3/entities2.xml';bodies=[dict(e.attrib)for e in ET.parse(xml).getroot()if e.get('id')in['14','85']and e.get('variant','0')=='0'];assert len(bodies)==2 and all(e.get('friction')=='1'for e in bodies)
 manifest=dict(exe_sha256=M.SHA,source_xml_sha256=hashlib.sha256(xml.read_bytes()).hexdigest(),source_bodies=bodies,spider_idle_gates=len(gates),spider_update_states=len(rows),pooter_update_states=len(pooters),windows=windows,method='original native counter/stop/impulse, pursuit, cooldown, wander/edge, velocity helper and base physics instructions; no patched code or helper stubs',supplied_boundaries=['Spider initialized state, destination, starting counter/momentum; acquisition RNG/line/clamp excluded','Pooter normal state, target1000/280, wander.2/.1, velocity2/1 except right -4/1 and bottom2/-2; cooldown0/35','Pooter random outcomes/directions generated with DW SplitMix64 seed123456; native RNG distribution/replay NOT verified','source global frame1..24 supplied; fourth-frame jitter path entered after supplied random direction; third-frame cadence executes','AI then base physics state comparisons; no continuous terrain/entity collision or live NPC cadence','Pooter attacks/morphs/items/statuses/champions excluded'],full_native_acceptance=False);save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode());print(json.dumps(dict(passed=True,check=a.check,spider_states=len(rows),spider_gates=len(gates),pooter_states=len(pooters))))
if __name__=='__main__':main()
