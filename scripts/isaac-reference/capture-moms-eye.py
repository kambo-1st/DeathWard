#!/usr/bin/env python3
"""Pinned ordinary Mom's Eye gate and backward-vector arithmetic.
Executes real inventory queries/SSE with a supplied global RNG word. Does not
instantiate a native tear or claim global RNG/full weapon-wrapper equivalence.
"""
import argparse,csv,hashlib,importlib.util,io,json,struct,xml.etree.ElementTree as ET
from pathlib import Path
import capstone,pefile
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import *
sp=importlib.util.spec_from_file_location('awards',Path(__file__).with_name('analyze-room-awards.py'))
A=importlib.util.module_from_spec(sp);sp.loader.exec_module(A)
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==A.M.SHA
 pe=pefile.PE(data=raw);f=A.NativeAwards(pe,raw);u=f.u;n=f.n;b=n.ebp;out=f.HEAP+0x1000
 directory=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d14a7-moms-eye/source';directory.mkdir(parents=True,exist_ok=True)
 def save(name,data):
  p=directory/name
  if args.check:assert p.read_bytes()==data,name
  else:p.write_bytes(data)
 def table(name,columns,rows):
  s=io.StringIO();w=csv.writer(s,lineterminator='\n');w.writerow(columns);w.writerows(rows);save(name,s.getvalue().encode())
 word=0;draws=0
 def rng(uc,addr,size,data):
  nonlocal draws
  draws+=1;sp=uc.reg_read(UC_X86_REG_ESP);ret=f.integer(sp);uc.reg_write(UC_X86_REG_EAX,word);uc.reg_write(UC_X86_REG_ESP,sp+4);uc.reg_write(UC_X86_REG_EIP,ret)
 u.hook_add(UC_HOOK_CODE,rng,begin=0x6c3d90,end=0x6c3d90)
 rows=[]
 for copies in (0,1,2,5):
  for luck in (-10,-5,-4,-1,0,.5,1,2,4,4.999,5,6,20):
   threshold=struct.unpack('<f',struct.pack('<f',struct.unpack('<f',struct.pack('<f',luck*.10000000149011612))[0]+.5))[0]
   boundary=max(0,min(0xffffffff,int(threshold*2**32)))
   words=list(dict.fromkeys([0,1,0x40000000,0x7fffffff,0x80000000,0xffffff00,0xffffffff]+[max(0,min(0xffffffff,boundary+k)) for k in (-512,-128,-1,0,1,128,512)]))
   for word in words:
    draws=0;f.write(f.ITEMS+0xf1000+55*4,copies);n.write_float(n.PLAYER+0x14b0,luck);u.mem_write(out,bytes(64));u.mem_write(b-0x1000,bytes(128));f.write(b+12,1)
    for reg,val in [(UC_X86_REG_EBP,b),(UC_X86_REG_ESP,b-0x1000),(UC_X86_REG_EDI,n.PLAYER),(UC_X86_REG_EBX,out)]:u.reg_write(reg,val)
    u.emu_start(0x74ad55,0x74ae4d,count=50000);assert u.reg_read(UC_X86_REG_EIP)==0x74ae4d
    backward,sideways=bytes(u.mem_read(out+0x1d,2));unit=struct.unpack('<f',struct.pack('<f',word))[0]*2**-32
    assert backward==int(copies>0 and unit<threshold) and sideways==0 and draws==int(copies>0),(copies,luck,word,backward,threshold,unit)
    rows.append([copies,luck,word,backward,draws])
 vectors=[]
 for x,y in [(1,0),(-1,0),(0,1),(0,-1),(.70710677,.70710677),(-.70710677,.70710677),(.70710677,-.70710677),(-.70710677,-.70710677)]:
  for speed in (.5,1,2):
   u.reg_write(UC_X86_REG_EBP,b);n.write_float(b-0xc8,x);n.write_float(b-0xb8,y);n.write_float(b-0x104,speed)
   u.emu_start(0x95af4d,0x95af94,count=1000);vx=n.read_float(b-0xbc);vy=n.read_float(b-0xfc)
   assert abs(vx+x*speed)<1e-6 and abs(vy+y*speed)<1e-6;vectors.append([x,y,speed,vx,vy])
 table('native-gate.csv',['copies','luck','rng_word','backward','draws'],rows)
 table('native-vector.csv',['aim_x','aim_y','speed','backward_x','backward_y'],vectors)
 windows=[];md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 for name,start,end in [('ordinary-inventory-and-gate',0x74ad55,0x74ae4d),('ordinary-weapon-config-call',0x959e6f,0x959e9f),('rear-vector-queue',0x95a6f7,0x95a85a),('rear-tear-request',0x95af34,0x95b085)]:
  blob=pe.get_data(start-0x400000,end-start);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,start))+'\n').encode());windows.append(dict(name=name,start=hex(start),end=hex(end),sha256=hashlib.sha256(blob).hexdigest()))
 source=A.M.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3'
 item=next(e for e in ET.parse(source/'items.xml').getroot() if e.tag=='passive' and e.get('id')=='55')
 pool=next(e for p in ET.parse(source/'itempools.xml').getroot() if p.get('Name')=='treasure' for e in p if e.get('Id')=='55')
 assert not item.get('achievement') and pool.get('Weight')=='1'
 manifest=dict(version='Repentance1.7.9b',executable_sha256=A.M.SHA,item=dict(item.attrib),treasure_pool_entry=dict(pool.attrib),gate_cases=len(rows),vector_cases=len(vectors),windows=windows,formula='float32(0.5 + float32(0.1 * Luck)) > float32(uint32 RNG) * 2^-32; one Boolean ownership check and one RNG draw, copies do not stack',scope='Ordinary weapon1 branch with other items/effects absent. Original HasCollectible helpers execute; only global RNG call supplies a chosen word. Backward vector arithmetic executes separately for eight supplied directions. Caller/tear-request assembly preserved; full native tear factory, modifiers, weapon wrappers, global RNG order and physics remain unaccepted.',full_native_acceptance=False)
 save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode());print('PASS',len(rows),'native inventory/Luck gate cases and',len(vectors),'backward vectors')
if __name__=='__main__':main()
