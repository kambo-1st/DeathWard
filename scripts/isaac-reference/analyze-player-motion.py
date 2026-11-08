#!/usr/bin/env python3
"""Execute bounded 1.7.9b player-motion code in an isolated CPU emulator.

No game process, imports, filesystem callbacks or patched instructions are used.
This establishes per-invocation ordinary motion, not whole-game timing/geometry.
Requires pefile, capstone, unicorn==2.1.4 (see the evidence README).
"""
import argparse
import csv
import hashlib
import io
import json
import struct
from pathlib import Path
import capstone
import pefile
from unicorn import Uc, UC_ARCH_X86, UC_MODE_32
from unicorn.x86_const import (UC_X86_REG_EDI, UC_X86_REG_ESI, UC_X86_REG_EBP,
    UC_X86_REG_ESP, UC_X86_REG_EIP, UC_X86_REG_ECX, UC_X86_REG_XMM5, UC_X86_REG_XMM6)

ROOT=Path(__file__).resolve().parents[2]
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
OUT=ROOT/'docs/reports/isaac-first-floor-parity/player-motion'
WINDOWS=[('input_normalization',0x74211c,0x74215c),('speed_and_direction',0x742369,0x7423fb),
    ('ordinary_velocity',0x742453,0x742830),('no_additional_friction_item',0x742830,0x7428ee),
    ('sqrt_helper',0x4228c0,0x4228df),('empty_item_query',0x88b600,0x88b631),
    ('normalize',0x9624f0,0x96254c),('resize',0x962860,0x9628c7),
    ('inheritance',0x76ff80,0x7701d4),('slippery_timer',0x74d378,0x74d3aa)]

class NativeMotion:
    PLAYER=0x2000000
    STACK=0x3000000
    STOP=0x300f000
    def __init__(self,pe):
        self.u=Uc(UC_ARCH_X86,UC_MODE_32);base=pe.OPTIONAL_HEADER.ImageBase
        self.u.mem_map(base,(pe.OPTIONAL_HEADER.SizeOfImage+4095)&~4095)
        self.u.mem_write(base,pe.get_memory_mapped_image())
        self.u.mem_map(self.PLAYER,0x10000);self.u.mem_map(self.STACK,0x10000)
        self.ebp=self.STACK+0x8000
        self.reset()
    def reset(self):self.u.mem_write(self.PLAYER,bytes(0x10000))
    def write_float(self,address,value):self.u.mem_write(address,struct.pack('<f',value))
    def read_float(self,address):return struct.unpack('<f',self.u.mem_read(address,4))[0]
    def xmm(self,reg,value):self.u.reg_write(reg,struct.unpack('<I',struct.pack('<f',value))[0])
    def run(self,start,end):
        self.u.emu_start(start,end,count=10000)
        assert self.u.reg_read(UC_X86_REG_EIP)==end,hex(self.u.reg_read(UC_X86_REG_EIP))
    def step(self,x,y,speed=1):
        p=self.PLAYER;u=self.u;b=self.ebp
        previous=(self.read_float(p+0x2b8),self.read_float(p+0x2bc))
        self.write_float(p+0x14ac,speed)
        self.write_float(p+0x1594,previous[0]);self.write_float(p+0x1598,previous[1])
        u.reg_write(UC_X86_REG_EDI,p);u.reg_write(UC_X86_REG_ESI,p+0x1450)
        u.reg_write(UC_X86_REG_EBP,b);u.reg_write(UC_X86_REG_ESP,b-0x100)
        for offset,value in [(-0x60,x),(-0x50,y),(-0x44,x),(-0x40,y)]:self.write_float(b+offset,value)
        self.run(0x74211c,0x74215c)
        x=self.read_float(b-0x60);y=self.read_float(b-0x50)
        self.xmm(UC_X86_REG_XMM5,x);self.xmm(UC_X86_REG_XMM6,y)
        self.run(0x742369,0x7423fb)
        # The omitted interval only updates a presentation-facing angle.
        # Execute the native physics and empty item query, including real sqrt.
        self.run(0x742453,0x7428ee)
        return previous,(self.read_float(p+0x2b8),self.read_float(p+0x2bc))
    def inheritance(self,velocity,direction):
        p=self.PLAYER;u=self.u;sp=self.STACK+0x9000
        self.write_float(p+0x1594,velocity[0]);self.write_float(p+0x1598,velocity[1])
        output=self.STACK+0x100;vector=self.STACK+0x200
        self.write_float(vector,direction[0]);self.write_float(vector+4,direction[1])
        # true selects the ordinary formula without item/character overrides.
        u.mem_write(sp,struct.pack('<4I',self.STOP,output,vector,1))
        u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,p)
        self.run(0x76ff80,self.STOP)
        return self.read_float(output),self.read_float(output+4)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--check',action='store_true');args=parser.parse_args()
    raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==SHA
    pe=pefile.PE(data=raw);base=pe.OPTIONAL_HEADER.ImageBase;native=NativeMotion(pe)
    out=OUT;out.mkdir(parents=True,exist_ok=True)
    def save(name,data):
        path=out/name
        if args.check:assert path.read_bytes()==data,name
        else:path.write_bytes(data)
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
    for name,start,end in WINDOWS:
        blob=pe.get_data(start-base,end-start)
        listing=('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(blob,start))+'\n').encode()
        save(name+'.asm',listing)
        windows.append({'name':name,'start':hex(start),'end_exclusive':hex(end),'raw_sha256':hashlib.sha256(blob).hexdigest(),'listing_sha256':hashlib.sha256(listing).hexdigest()})
    cases=[('press_release',1,[(1,0)]*45+[(0,0)]*45),
        ('diagonal',1,[(1,1)]*45+[(0,0)]*30),
        ('reverse',1,[(1,0)]*30+[(-1,0)]*30+[(0,0)]*30),
        ('corner',1,[(1,0)]*30+[(0,1)]*30+[(-1,0)]*30+[(0,0)]*20),
        ('analog',1,[(.3,.4)]*45+[(0,0)]*30),
        ('speed_0_8',.8,[(1,0)]*45+[(0,0)]*30),
        ('speed_2',2,[(1,0)]*45+[(0,0)]*30)]
    rows=[]
    for name,speed,inputs in cases:
        native.reset()
        for frame,(x,y) in enumerate(inputs):
            previous,velocity=native.step(x,y,speed)
            inherited=native.inheritance(previous,(1,0))
            rows.append([name,frame,speed,x,y,*previous,*velocity,*inherited])
    text=io.StringIO(newline='');writer=csv.writer(text,lineterminator='\n')
    writer.writerow(['case','invocation','speed_stat','input_x','input_y','previous_vx','previous_vy','native_vx','native_vy','inherit_right_vx','inherit_right_vy']);writer.writerows(rows)
    save('native-traces.csv',text.getvalue().encode())
    inheritance=[]
    for velocity in [(4,0),(-4,0),(0,4),(2,3),(-2,-3),(0,0)]:
        for direction in [(1,0),(0,1),(-1,0),(0,-1),(1,1),(0,0)]:
            result=native.inheritance(velocity,direction)
            inheritance.append({'velocity':velocity,'direction':direction,'inherited':result})
    manifest={'version':'Repentance 1.7.9b','exe_sha256':SHA,'emulator':'Unicorn 2.1.4','method':'Native x86/SSE blocks, native sqrt/vector/item-query helpers, zeroed empty collectible effects; no instruction patches, import hooks or game process','scope':'ordinary grounded player motion per invocation and ordinary movement inheritance; NOT whole-game or collision/timing acceptance','omitted':'control/character/item/status branches before normalized input, presentation-only angle update, post-motion item actions, collision/world integration and global scheduling','windows':windows,'trace_rows':len(rows),'cases':len(cases),'inheritance_cases':inheritance,'clock_scope':'Native invocations have no assigned wall-clock duration in these fixtures. Establish scheduler cadence before claiming real-time movement equivalence.','spatial_scope':'Native coordinates only; the DW unit conversion is a separate adaptation.'}
    save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode())
    print(json.dumps({'pass':True,'check':args.check,'trace_rows':len(rows),'cases':len(cases),'native_helpers_stubbed':0,'scope':manifest['scope']}))

if __name__=='__main__':main()
