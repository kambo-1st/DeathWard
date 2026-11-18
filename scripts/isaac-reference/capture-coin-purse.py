#!/usr/bin/env python3
"""Bounded installed 1.7.9b purse requests, ordinary pill colors and stat/health blocks."""
import argparse,csv,hashlib,importlib.util,io,json,struct,xml.etree.ElementTree as ET
from pathlib import Path
import pefile,capstone
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import *
def module(name,file):
 s=importlib.util.spec_from_file_location(name,Path(__file__).with_name(file));m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
A=module('awards','analyze-room-awards.py');H=module('health','analyze-player-health.py')
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==A.M.SHA
 pe=pefile.PE(data=raw);f=A.NativeAwards(pe,raw);n=f.n;u=f.u;b=n.ebp
 out=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d14a8-coin-purse/source';out.mkdir(parents=True,exist_ok=True)
 def save(name,data):
  p=out/name
  if args.check:assert p.read_bytes()==data,name
  else:p.write_bytes(data)
 def table(name,cols,rows):
  s=io.StringIO();w=csv.writer(s,lineterminator='\n');w.writerow(cols);w.writerows(rows);save(name,s.getvalue().encode())
 def no_callback(u,a,size,data):
  sp=u.reg_read(UC_X86_REG_ESP);ret=f.integer(sp);u.reg_write(UC_X86_REG_EAX,0);u.reg_write(UC_X86_REG_ESP,sp+12);u.reg_write(UC_X86_REG_EIP,ret)
 u.hook_add(UC_HOOK_CODE,no_callback,begin=0x802790,end=0x802790)
 colors=[]
 for seed in [(i*0x9e3779b9)&0xffffffff for i in range(1,513)]+[1,42,0xffffffff]:
  sp=n.STACK+0x9000;u.mem_write(sp,struct.pack('<2I',n.STOP,seed));u.reg_write(UC_X86_REG_ESP,sp);f.run(0x702590)
  value=seed;value^=value>>2;value^=(value<<7)&0xffffffff;value^=value>>9
  color=u.reg_read(UC_X86_REG_EAX);assert color==value%13+1;colors.append([seed,color])
 table('native-colors.csv',['seed','color'],colors)
 spawn=[];rng=f.HEAP+0x1000
 def host(u,a,size,data):
  sp=u.reg_read(UC_X86_REG_ESP);ret=f.integer(sp)
  if a==0x7cf240:
   result=f.integer(sp+4);u.mem_write(result,struct.pack('<2f',100.,200.));retbytes=20
  else:
   values=struct.unpack('<7I',u.mem_read(sp+4,28));spawn.append(values);result=f.HEAP+0x10000+len(spawn)*0x1000;retbytes=28
  u.reg_write(UC_X86_REG_EAX,result);u.reg_write(UC_X86_REG_ESP,sp+4+retbytes);u.reg_write(UC_X86_REG_EIP,ret)
 for addr in [0x7cf240,0x422e20]:u.hook_add(UC_HOOK_CODE,host,begin=addr,end=addr)
 purse=[]
 for seed in [1,42,12345,0xffffffff]:
  for fresh in [0,1]:
   spawn.clear();u.mem_write(rng,struct.pack('<4I',seed,1,11,6));u.reg_write(UC_X86_REG_EBP,b);u.reg_write(UC_X86_REG_ESP,b-0x1000);u.reg_write(UC_X86_REG_ESI,n.PLAYER);u.reg_write(UC_X86_REG_EDI,rng);u.mem_write(b+0x10,bytes([fresh]));u.emu_start(0x72bb2b,0x72e057,count=10000)
   assert len(spawn)==4*fresh and all(s[0:2]==(5,70) and s[5]==0 for s in spawn)
   purse.append(dict(seed=seed,new_pickup=bool(fresh),spawn_seeds=[s[6] for s in spawn],ordinals=[f.integer(f.HEAP+0x10000+(i+1)*0x1000+0x4a0) for i in range(len(spawn))]))
 save('native-purse.json',(json.dumps(purse,indent=2)+'\n').encode())
 counts=f.HEAP+0x2000;f.write(n.PLAYER+0x15fc,counts);f.write(n.PLAYER+0x1600,counts+50*4)
 def frame():
  u.reg_write(UC_X86_REG_EBP,b);u.reg_write(UC_X86_REG_ESP,b-0x1000);u.reg_write(UC_X86_REG_EDI,n.PLAYER);u.reg_write(UC_X86_REG_ESI,n.PLAYER+0x1450);u.reg_write(UC_X86_REG_EAX,n.PLAYER)
  f.write(b-0x428,n.PLAYER);f.write(b-0x440,n.PLAYER+0x1450);n.write_float(b-0x43c,1);u.mem_write(b-0x441,b'\0');n.write_float(n.PLAYER+0x1864,1)
 def block(start,end):
  u.emu_start(start,end,count=500000);assert u.reg_read(UC_X86_REG_EIP)==end
 stats=[]
 for effect in [11,12,13,14,15,16,17,18,47,48]:
  for count in [0,1,2,5]:
   u.mem_write(counts,bytes(200));f.write(counts+effect*4,count);frame();block(0x732d05,0x7338be);ran=n.read_float(n.PLAYER+0x13c8)
   frame();block(0x73394d,0x7340c9);speed=n.read_float(n.PLAYER+0x14ac)
   frame();block(0x732646,0x732c33);shot=n.read_float(n.PLAYER+0x13ac)
   frame();block(0x72f8d8,0x72f922);tear=n.read_float(b-0x438)
   frame();block(0x739bd1,0x739c09);luck=n.read_float(b-0x42c)
   assert abs(ran-(260+(50 if effect==12 else -40 if effect==11 else 0)*count))<.001
   assert abs(speed-(1+(.15 if effect==14 else -.12 if effect==13 else 0)*count))<.00001
   assert abs(shot-(1+(.15 if effect==48 else -.15 if effect==47 else 0)*count))<.00001
   assert abs(tear-((.5 if effect==16 else -.4 if effect==15 else 0)*count))<.00001
   assert luck==(1 if effect==18 else -1 if effect==17 else 0)*count
   stats.append([effect,count,speed,tear,ran/40,shot,luck])
 table('native-stats.csv',['effect','count','speed','raw_tears','range_tiles','shot_speed','luck'],stats)
 health=H.NativeHealth(pe);hn=health.native;hu=health.u;hb=hn.ebp;hp=health.player;rows=[]
 for cap in [2,4,6,12,24]:
  for red in [0,cap//2,cap]:
   for effect,start,end in [(2,0x788353,0x788365),(5,0x78842f,0x788365),(6,0x788507,0x78851e),(7,0x788448,0x78845c)]:
    health.reset();health.write(hp+0x1290,cap);health.write(hp+0x1294,red)
    sp=hn.STACK+0x9000;hu.mem_write(sp,struct.pack('<2I',hn.STOP,6));hu.reg_write(UC_X86_REG_ESP,sp);hu.reg_write(UC_X86_REG_ECX,hp);health.run(0x7876f0,hn.STOP);safe=hu.reg_read(UC_X86_REG_EAX)&255
    if effect==6 and not safe:start,end=0x788448,0x78845c
    hu.reg_write(UC_X86_REG_EBP,hb);hu.reg_write(UC_X86_REG_ESP,hb-0x1000);hu.reg_write(UC_X86_REG_EDI,hp);hu.reg_write(UC_X86_REG_EDX,0);hu.mem_write(hb-0x144,b'\0');health.run(start,end)
    result=health.snapshot();rows.append([effect,cap,red,result['max_red'],result['red'],result['soul'],int(effect==6 and not safe)])
 table('native-health.csv',['effect','capacity','red','after_capacity','after_red','after_soul','converted_up'],rows)
 windows=[];md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 for name,start,end in [('purse-dispatch',0x72b944,0x72b995),('purse-requests',0x72bb2b,0x72bbda),('pill-color',0x702590,0x702704),('low-health-conversion',0x702888,0x7028b5),('health-down-safety',0x7876f0,0x78778f),('health-effects',0x788353,0x78851e),('tears-counter',0x72f8d8,0x72f922),('range-counter',0x732e47,0x732e93),('speed-counter',0x7339e7,0x733a33),('luck-counter',0x739bd1,0x739c09),('use-identification',0x7878c5,0x7878cd),('use-counter',0x787f26,0x787f47)]:
  blob=pe.get_data(start-0x400000,end-start);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,start))+'\n').encode());windows.append(dict(name=name,start=hex(start),end=hex(end),sha256=hashlib.sha256(blob).hexdigest()))
 source=A.M.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3'
 item=next(x for x in ET.parse(source/'items.xml').getroot() if x.tag=='passive' and x.get('id')=='195');pool=next(x for p in ET.parse(source/'itempools.xml').getroot() if p.get('Name')=='shop' for x in p if x.get('Id')=='195')
 manifest=dict(version='Repentance1.7.9b',executable_sha256=A.M.SHA,item=dict(item.attrib),shop_entry=dict(pool.attrib),color_cases=len(colors),purse_cases=len(purse),stat_cases=len(stats),health_cases=len(rows),windows=windows,scope='Purse new-pickup gate/count/seed requests with world position and actor factories hosted; original color RNG with gold/horse gates off and absent mod callback; original stat-cache slices with supplied counters and other modifiers absent, before final cache callbacks/caps; original ordinary health APIs and low-capacity Health Down gate. Not native pool generation, full use wrapper, pickup factory, actors, scheduler or RNG order.',full_native_acceptance=False)
 save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode());print('PASS',len(colors),'colors,',len(purse),'purse gates,',len(stats),'stat cases,',len(rows),'health cases')
if __name__=='__main__':main()
