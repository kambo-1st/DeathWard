#!/usr/bin/env python3
"""Execute pinned room-clear award and ordinary pickup subtype selection.

Numeric/RNG/game-query routines execute original instructions. The pickup
fixture supplies only CRT allocation/copy operations; no world spawning occurs.
"""
import argparse
import csv
import hashlib
import importlib.util
import io
import json
import struct
from pathlib import Path
import capstone
import pefile
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_READ, UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_EDX, UC_X86_REG_EIP, UC_X86_REG_ESP

SPEC=importlib.util.spec_from_file_location('motion',Path(__file__).with_name('analyze-player-motion.py'))
M=importlib.util.module_from_spec(SPEC);SPEC.loader.exec_module(M)
OUT=M.ROOT/'docs/reports/isaac-first-floor-parity/room-awards'
GATES={'rotten':0x1e7,'scared':0x194,'half_soul':0x6d,'bone':0x1d3,'golden_heart':0x12c,
       'sticky_nickel':0x13c,'lucky_penny':0x13e,'golden_penny':0x2b1,'charged_key':0x199,'golden_bomb':0x12e}


class NativeAwards:
    GAME=0x4000000;MANAGER=0x5000000;ITEMS=0x6000000;ROOM=0x4500000;HEAP=0x7000000
    def __init__(self,pe,raw):
        self.n=M.NativeMotion(pe);self.u=self.n.u;p=self.n.PLAYER
        for a,size in [(self.GAME,0x400000),(self.MANAGER,0x100000),(self.ITEMS,0x100000),(self.ROOM,0x10000),(self.HEAP,0x400000),(0,0x1000)]:self.u.mem_map(a,size)
        self.write(0xbfd65c,self.GAME);self.write(0xbfd680,self.MANAGER)
        self.u.mem_write(self.MANAGER+0x15,b'\x01')
        self.write(self.MANAGER+0x29e84,self.ITEMS);self.write(self.MANAGER+0x29e88,self.ITEMS+4096)
        for i in range(1024):self.write(self.ITEMS+i*4,self.ITEMS+0x10000+i*0x200)
        sentinel=self.ITEMS+0xf0000
        for offset in (0,4,8):self.write(sentinel+offset,sentinel)
        self.u.mem_write(sentinel+0xc,b'\x01\x01');self.write(self.GAME+0x1bb58,sentinel)
        self.write(p+0x28,1);self.write(p+0x1290,6);self.write(p+0x1294,6)
        self.write(p+0x15f0,self.ITEMS+0xf1000);self.write(p+0x1670,self.ITEMS+0xf3000)
        players=self.n.STACK+0x500;self.write(players,p)
        self.write(self.GAME+0x1ba50,players);self.write(self.GAME+0x1ba54,players+4)
        self.write(self.GAME+0x18190,self.ROOM);self.write(self.ROOM+8,1)
        self.heap_cursor=self.HEAP;self.allocations={};self.import_counts={};self.endpoints={}
        imports={i.address:i.name.decode() for e in pe.DIRECTORY_ENTRY_IMPORT for i in e.imports if i.name}
        for address,name in imports.items():
            if name not in ('malloc','free','memcpy','memmove','memset'):continue
            needle=b'\xff\x25'+struct.pack('<I',address);start=0
            while True:
                pos=raw.find(needle,start)
                if pos<0:break
                start=pos+1;va=pe.OPTIONAL_HEADER.ImageBase+pe.get_rva_from_offset(pos)
                self.endpoints[va]=name
                self.u.hook_add(UC_HOOK_CODE,self.memory_import,begin=va,end=va)
        self.u.hook_add(UC_HOOK_MEM_READ|UC_HOOK_MEM_WRITE,self.low_guard,begin=0,end=0xffff)

    def write(self,address,value):self.u.mem_write(address,struct.pack('<I',value&0xffffffff))
    def integer(self,address):return struct.unpack('<I',self.u.mem_read(address,4))[0]
    def low_guard(self,uc,access,address,size,value,data):
        pc=uc.reg_read(UC_X86_REG_EIP)
        if address!=0 or uc.mem_read(pc,1)!=b'\x64':raise RuntimeError(f'unexpected low-memory access {address:#x} at {pc:#x}')
    def memory_import(self,uc,address,size,data):
        name=self.endpoints[address];self.import_counts[name]=self.import_counts.get(name,0)+1
        sp=uc.reg_read(UC_X86_REG_ESP);ret,arg=struct.unpack('<2I',uc.mem_read(sp,8))
        if name=='malloc':
            assert 0<arg<=0x100000
            result=self.heap_cursor;self.heap_cursor+=(arg+15)&~15
            assert self.heap_cursor<self.HEAP+0x400000
            self.allocations[result]=arg;uc.reg_write(UC_X86_REG_EAX,result)
        elif name=='free':
            if arg:assert self.allocations.pop(arg,None) is not None,hex(arg)
        else:
            dest,source,length=struct.unpack('<3I',uc.mem_read(sp+4,12));assert length<=0x100000
            if length:uc.mem_write(dest,bytes([source&255])*length if name=='memset' else bytes(uc.mem_read(source,length)))
            uc.reg_write(UC_X86_REG_EAX,dest)
        uc.reg_write(UC_X86_REG_ESP,sp+4);uc.reg_write(UC_X86_REG_EIP,ret)
    def run(self,start):
        self.u.emu_start(start,self.n.STOP,count=200000)
        assert self.u.reg_read(UC_X86_REG_EIP)==self.n.STOP,hex(self.u.reg_read(UC_X86_REG_EIP))
    def award(self,seed,luck,prevent_none=False):
        rng=self.n.STACK+0x400;sp=self.n.STACK+0x9000
        self.u.mem_write(rng,struct.pack('<4I',seed,5,9,7));self.n.write_float(self.n.PLAYER+0x14b0,luck)
        self.u.mem_write(sp,struct.pack('<3I',self.n.STOP,rng,int(prevent_none)))
        self.u.reg_write(UC_X86_REG_ESP,sp);self.run(0x7b82b0)
        return self.u.reg_read(UC_X86_REG_EAX),self.integer(rng)
    def pickup(self,seed,variant,gates=False):
        for offset in GATES.values():self.u.mem_write(self.MANAGER+offset,bytes([int(gates)]))
        vp=self.n.STACK+0x600;st=vp+4;sp=self.n.STACK+0x9000
        self.write(vp,variant);self.write(st,0)
        self.u.mem_write(sp,struct.pack('<4I',self.n.STOP,st,1,0))
        self.u.reg_write(UC_X86_REG_ESP,sp);self.u.reg_write(UC_X86_REG_ECX,seed);self.u.reg_write(UC_X86_REG_EDX,vp)
        self.run(0x6b48b0)
        assert self.integer(0xc038f8)==0 and not self.allocations
        return self.integer(vp),self.integer(st)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--check',action='store_true');args=parser.parse_args()
    raw=M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==M.SHA
    pe=pefile.PE(data=raw);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
    fixture=NativeAwards(pe,raw);OUT.mkdir(parents=True,exist_ok=True)
    def save(name,blob):
        p=OUT/name
        if args.check:assert p.read_bytes()==blob,name
        else:p.write_bytes(blob)
    def table(name,fields,rows):
        buf=io.StringIO(newline='');w=csv.writer(buf,lineterminator='\n');w.writerow(fields);w.writerows(rows);save(name,buf.getvalue().encode())
    seeds=[(i*0x9e3779b9)&0xffffffff for i in range(1,129)]+[1,42,0x7fffffff,0x80000000,0xfffffffe,0xffffffff]
    # Supply first RNG words around each native branch boundary. Only input
    # seeds are constructed here; expected choices/state still execute natively.
    def undo(value,shift,left=False):
        result=value
        for _ in range(32):result=(value^((result<<shift) if left else (result>>shift)))&0xffffffff
        return result
    coefficient=struct.unpack('<f',read(0xb6a198,4))[0]
    for threshold in (.22,.30,.45,.50,.60,.80,.95):
        target=struct.unpack('<f',struct.pack('<f',threshold))[0]
        word=int(target/coefficient)
        for offset in (-1024,-256,-1,0,1,256,1024):
            value=(word+offset)&0xffffffff
            seed=undo(undo(undo(value,7),9,True),5)
            assert seed
            seeds.append(seed)
    seeds=list(dict.fromkeys(seeds))
    awards=[]
    for luck in (-3,0,1,5,10,20):
        for prevent in (False,True):
            for seed in seeds:
                variant,after=fixture.award(seed,luck,prevent);awards.append([seed,luck,int(prevent),variant,after])
    table('native-awards.csv',['seed','luck','prevent_none','variant','rng_after_selector'],awards)
    print(f'Native room-award selector: {len(awards)} cases',flush=True)
    pickups=[]
    for variant in (10,20,30,40):
        for gates in (False,True):
            for seed in [(i*0x9e3779b9)&0xffffffff for i in range(1,513)]+[1,42,0x7fffffff,0x80000000,0xfffffffe,0xffffffff]:
                result,subtype=fixture.pickup(seed,variant,gates);pickups.append([seed,variant,int(gates),result,subtype])
        print(f'Native pickup {variant}: captured',flush=True)
    table('native-pickups.csv',['seed','variant','represented_gates_enabled','result_variant','subtype'],pickups)
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
    for name,a,b in [('award_selector',0x7b82b0,0x7b8b0a),('award_spawn',0x7b8b10,0x7baf7a),('pickup_resolver',0x6b48b0,0x6b6a7c),('weighted_picker',0x489420,0x4895b8),('clear_callsite',0x7c31a7,0x7c31e2),('natural_clear_callsite',0x7ae343,0x7ae39d),('lua_award_binding',0x808d12,0x808d1c)]:
        blob=read(a,b-a);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(blob,a))+'\n').encode());windows.append({'name':name,'start':hex(a),'end_exclusive':hex(b),'raw_sha256':hashlib.sha256(blob).hexdigest()})
    manifest={'baseline':'Installed Repentance 1.7.9b','executable_sha256':M.SHA,'award_cases':len(awards),'pickup_cases':len(pickups),'windows':windows,
              'award_scope':'Whole native selector, one empty-inventory ordinary Isaac; supplied nonzero room RNG seed, shifts5/9/7, Luck input and prevent-none flag. No RNG/numeric/game-query helpers substituted.',
              'pickup_scope':'Whole native variant/subtype resolver for supplied heart/coin/key/bomb variants and pickup seed, input subtype0 and caller flags1/0, supplied ordinary room type1. Other game fields are synthetic zero defaults except the explicitly initialized fixture fields. Represented achievement bytes are toggled explicitly; this does not prove a complete native floor, fresh-save or fully unlocked profile.',
              'represented_achievement_bytes':{name:hex(offset) for name,offset in GATES.items()},
              'memory_import_boundaries':{'endpoints':{hex(a):name for a,name in sorted(fixture.endpoints.items())},'calls':fixture.import_counts,'scope':'Only malloc/free/memcpy/memmove/memset are hosted. All native RNG, weighted outcome, subtype branches and game queries run original instructions. Low-memory accesses are rejected except actual FS:[0] exception bookkeeping.'},
              'award_variants_seen':sorted({r[3] for r in awards}),
              'pickup_outputs_seen':{str(v):sorted({r[4] for r in pickups if r[1]==v}) for v in (10,20,30,40)},
              'capture_claims_gameplay_acceptance':False,
              'remaining':['source room seed mapping and full award-spawn modifiers/placement','card/pill/trinket/chest/sack contents and interaction rules','pickup physical creation, timers, motion and collision','complete unlock profiles and reachable item/trinket modifiers','production generation and matched native full-floor acceptance']}
    save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode());print(f'Native cases complete: {len(awards)} awards, {len(pickups)} pickups; gameplay acceptance remains open.')


if __name__=='__main__':main()
