#!/usr/bin/env python3
"""Bounded installed Full Fly pursuit, recoil and mode-9 death-burst evidence."""
import argparse, csv, hashlib, importlib.util, io, json, struct
from pathlib import Path
import capstone, pefile
from unicorn.x86_const import *

def module(name, file):
    spec=importlib.util.spec_from_file_location(name,Path(__file__).with_name(file))
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
M=module('motion','analyze-player-motion.py')
NM=module('numeric','native_math.py')
R=module('rooms','audit-live-floor.py')
OUT=M.ROOT/'docs/reports/isaac-first-floor-parity/d14a2-full-fly/source'

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
    raw=M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==M.SHA
    pe=pefile.PE(data=raw);n=M.NativeMotion(pe);u=n.u;numeric=NM.NativeMath(n,pe)
    p=n.PLAYER;sp=n.STACK+0x6000
    def word(at,v):u.mem_write(at,struct.pack('<I',v&0xffffffff))
    def setup():
        n.reset();u.mem_write(sp,bytes(0x1000))
        for reg,value in [(UC_X86_REG_ESI,p),(UC_X86_REG_EDI,249),(UC_X86_REG_ESP,sp),(UC_X86_REG_EBP,n.ebp)]:u.reg_write(reg,value)
        for off,value in [(0x28,249),(0xe6c,-1)]:word(p+off,value)
        for off in (0x2c0,0x2c4,0x2f4):n.write_float(p+off,1)
    def save(name,data):
        path=OUT/name
        if args.check:assert path.read_bytes()==data,name
        else:path.parent.mkdir(parents=True,exist_ok=True);path.write_bytes(data)
    def csvfile(name,header,rows):
        buf=io.StringIO();w=csv.writer(buf,lineterminator='\n');w.writerow(header);w.writerows(rows);save(name,buf.getvalue().encode())
    pursuit=[]
    for skatole in (0,1):
        for dx in (-200,-40,-20,0,20,40,200):
            for dy in (-160,-20,0,20,160):
                setup();u.mem_write(sp+0xb,bytes([skatole]));n.write_float(p+0x28c,dx);n.write_float(p+0x290,dy)
                n.run(0x4f67db,0x4f6a3a)
                pursuit.append([dx,dy,skatole,n.read_float(p+0x2b8),n.read_float(p+0x2bc)])
    csvfile('native-pursuit.csv',['dx','dy','skatole','vx','vy'],pursuit)
    recoil=[]
    for x,y in [(0,0),(.5,.5),(1,0),(1.01,0),(2,-3),(-4,2)]:
        setup();n.write_float(p+0xb08,x);n.write_float(p+0xb0c,y)
        n.run(0x4f6ae2,0x4f6b62)
        recoil.append([x,y,n.read_float(p+0x2b8),n.read_float(p+0x2bc),n.read_float(p+0xb08),n.read_float(p+0xb0c)])
    csvfile('native-recoil.csv',['x','y','vx','vy','next_x','next_y'],recoil)
    # Original radial mode takes (speed,count), not a two-axis shot velocity.
    # Execute its initialization and each trigonometric velocity calculation;
    # skip world allocation, RNG, flags/filters and actor registration explicitly.
    setup();params=p+0x2000;vector=p+0x3000;args_at=p+0x4000
    u.reg_write(UC_X86_REG_EBX,args_at);word(args_at+0xc,vector);word(args_at+0x14,params)
    n.write_float(vector,8);n.write_float(vector+4,6)
    n.run(0x6a2e74,0x6a2ec0)
    count=struct.unpack('<I',u.mem_read(n.ebp-0x20,4))[0];assert count==6
    step=n.read_float(n.ebp-0x2c);angle=0;shots=[]
    for i in range(count):
        n.xmm(UC_X86_REG_XMM1,angle);n.xmm(UC_X86_REG_XMM2,step)
        n.run(0x6a2ec0,0x6a2ef0)
        angle=n.read_float(n.ebp-0x24)
        shots.append([i,n.read_float(n.ebp-0x18),struct.unpack('<f',struct.pack('<I',u.reg_read(UC_X86_REG_XMM0)&0xffffffff))[0]*8])
    csvfile('native-burst.csv',['index','vx','vy'],shots)
    rooms,stb=R.read_stb(R.SOURCE/'rooms/01.basement.stb')
    room=next(r for r in rooms if (r['type'],r['variant'],r['subtype'])==(1,704,0))
    save('room.json',(json.dumps(dict(source=stb,room=room),indent=2)+'\n').encode())
    windows=[];md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    for name,start,end in [('shared-update',0x4f4e30,0x4f6ed0),('mode9',0x6a2e74,0x6a301f),('params',0x430d70,0x430ef9)]:
        data=pe.get_data(start-0x400000,end-start)
        save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(data,start))+'\n').encode())
        windows.append(dict(name=name,start=hex(start),end=hex(end),sha256=hashlib.sha256(data).hexdigest()))
    constants={}
    for name,address in [('recoil_angle',0xb6ae6c),('recoil_spread',0xb6a6f0)]:constants[name]=struct.unpack('<f',pe.get_data(address-0x400000,4))[0]
    save('manifest.json',(json.dumps(dict(executable_sha256=M.SHA,pursuit_cases=len(pursuit),recoil_cases=len(recoil),burst_cases=len(shots),constants=constants,windows=windows,numeric=numeric.manifest(),scope='Original ordinary pursuit with supplied target/cadence, optional Skatole; original recoil application with supplied impulse; original mode9 six velocity calculations. World actor allocation, global RNG order, collision-normal generation, complete status/animation/scheduler wrappers remain unverified.',full_native_acceptance=False),indent=2)+'\n').encode())
    print('PASS',len(pursuit),'pursuit,',len(recoil),'recoil,',len(shots),'burst cases; source704')
if __name__=='__main__':main()
