#!/usr/bin/env python3
"""Bounded installed ordinary Attack Fly pursuit and recorded room414 evidence."""
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
OUT=M.ROOT/'docs/reports/isaac-first-floor-parity/d14a5-mixed-flies/source'

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
    raw=M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==M.SHA
    pe=pefile.PE(data=raw);n=M.NativeMotion(pe);u=n.u;numeric=NM.NativeMath(n,pe)
    p=n.PLAYER;sp=n.STACK+0x6000
    def word(at,v):u.mem_write(at,struct.pack('<I',v&0xffffffff))
    def setup():
        n.reset();u.mem_write(sp,bytes(0x1000))
        for reg,value in [(UC_X86_REG_ESI,p),(UC_X86_REG_EDI,18),(UC_X86_REG_ESP,sp),(UC_X86_REG_EBP,n.ebp)]:u.reg_write(reg,value)
        for off,value in [(0x28,18),(0xe6c,-1)]:word(p+off,value)
        for off in (0x2c0,0x2c4,0x2f4):n.write_float(p+off,1)
    def save(name,data):
        path=OUT/name
        if args.check:assert path.read_bytes()==data,name
        else:path.parent.mkdir(parents=True,exist_ok=True);path.write_bytes(data)
    def csvfile(name,header,rows):
        buf=io.StringIO();w=csv.writer(buf,lineterminator='\n');w.writerow(header);w.writerows(rows);save(name,buf.getvalue().encode())
    pursuit=[]
    for dx in (-200,-40,-25,-20,0,20,25,40,200):
        for dy in (-160,-50,-20,0,20,50,160):
            setup();n.write_float(p+0x28c,dx);n.write_float(p+0x290,dy)
            n.run(0x4f67db,0x4f6a3a)
            pursuit.append([dx,dy,n.read_float(p+0x2b8),n.read_float(p+0x2bc)])
    csvfile('native-pursuit.csv',['dx','dy','vx','vy'],pursuit)
    rooms,stb=R.read_stb(R.SOURCE/'rooms/01.basement.stb')
    room=next(r for r in rooms if (r['type'],r['variant'],r['subtype'])==(1,414,0))
    save('room.json',(json.dumps(dict(source=stb,room=room),indent=2)+'\n').encode())
    save('manifest.json',(json.dumps(dict(executable_sha256=M.SHA,pursuit_cases=len(pursuit),numeric=numeric.manifest(),scope='Original ordinary type18 pursuit with supplied deltas and a due force tick, no parent or status. Existing shared target3/force2/jitter4/retention3 cadence evidence is in isaac-enemy-port/attack_fly/source. World actor allocation, RNG order, collision and complete scheduler wrappers remain unverified.',full_native_acceptance=False),indent=2)+'\n').encode())
    print('PASS',len(pursuit),'native ordinary Attack Fly force cases; source414')
if __name__=='__main__':main()
