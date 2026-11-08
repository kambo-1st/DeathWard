#!/usr/bin/env python3
"""Execute pinned ordinary NPC Midas/Freeze application and timer blocks.

Original helpers and the NPC virtual metadata query execute. SetColor is the
only intercepted method. No live AI, linked-body or world-drop acceptance.
Dependencies: pefile, capstone, unicorn==2.1.4; see player-health/README.md.
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
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_EDX, UC_X86_REG_EDI, UC_X86_REG_ESI, UC_X86_REG_ESP, UC_X86_REG_EIP

SPEC=importlib.util.spec_from_file_location('health',Path(__file__).with_name('analyze-player-health.py'))
HEALTH=importlib.util.module_from_spec(SPEC);SPEC.loader.exec_module(HEALTH)
OUT=HEALTH.MOTION.ROOT/'docs/reports/isaac-first-floor-parity/midas-freeze'
WINDOWS=[('apply_midas',0x685990,0x685ad3),('apply_ordinary_freeze',0x685080,0x6851b3),
         ('status_immunity',0x684b00,0x684bae),('source_duration',0x685020,0x68507b),
         ('freeze_timer',0x686757,0x68678d),('midas_timer',0x6869dc,0x686a13),
         ('control_cooldown',0x686d68,0x686d79),('golden_heart_reset',0x78c740,0x78c76a),
         ('midas_death_drop',0x69e7f8,0x69e8d0),('bounded_rng',0x659230,0x659248),
         ('npc_metadata_query',0x68f570,0x68f577),('frozen_ai_predicate',0x69b0b0,0x69b0d6)]


class NativeMidas:
    NPC=0x7000000
    REF=0x7010000
    def __init__(self,pe):
        self.h=HEALTH.NativeHealth(pe);self.u=self.h.u;self.n=self.h.native
        self.u.mem_map(self.NPC,0x11000)
        self.h.write(self.REF,1);self.h.write(self.REF+0x24,self.h.player)
        self.color_calls=0
        self.u.hook_add(UC_HOOK_CODE,self.color_boundary)

    def color_boundary(self,uc,address,size,data):
        if address==0x68a380:
            self.color_calls+=1
            sp=uc.reg_read(UC_X86_REG_ESP)
            ret=struct.unpack('<I',uc.mem_read(sp,4))[0]
            uc.reg_write(UC_X86_REG_ESP,sp+24);uc.reg_write(UC_X86_REG_EIP,ret)

    def reset(self,kind=10,boss=False,flags=0,freeze=0,midas=0,cooldown=0):
        self.u.mem_write(self.NPC,bytes(0x10000));self.color_calls=0
        for offset,value in [(0,0xb49398),(0x28,kind),(0x160,flags),(0x210,freeze),(0x224,midas),(0x230,cooldown)]:
            self.h.write(self.NPC+offset,value)
        self.u.mem_write(self.NPC+0xb8d,bytes([int(boss)]))

    def snapshot(self):
        return [struct.unpack('<I',self.u.mem_read(self.NPC+offset,4))[0]
                for offset in [0x160,0x210,0x224,0x230,0x2c]]

    def apply(self,operation,duration):
        self.color_calls=0
        if operation=='golden':
            self.u.reg_write(UC_X86_REG_ESI,self.NPC)
            self.u.reg_write(UC_X86_REG_ECX,self.NPC)
            self.u.reg_write(UC_X86_REG_ESP,self.n.STACK+0x9000)
            self.h.run(0x78c740,0x78c74f)
        sp=self.n.STACK+0x9000
        self.u.mem_write(sp,struct.pack('<3I',self.n.STOP,self.REF,duration&0xffffffff))
        self.u.reg_write(UC_X86_REG_ESP,sp);self.u.reg_write(UC_X86_REG_ECX,self.NPC)
        self.h.run(0x685080 if operation=='ordinary' else 0x685990,self.n.STOP)

    def tick(self):
        self.color_calls=0
        self.u.reg_write(UC_X86_REG_EDI,self.NPC)
        self.u.reg_write(UC_X86_REG_ESP,self.n.STACK+0x9000)
        low=struct.unpack('<I',self.u.mem_read(self.NPC+0x160,4))[0]
        self.u.reg_write(UC_X86_REG_ESI,low);self.u.reg_write(UC_X86_REG_ECX,0)
        self.h.run(0x686757,0x68678d)
        low=struct.unpack('<I',self.u.mem_read(self.NPC+0x160,4))[0]
        self.u.reg_write(UC_X86_REG_ECX,low);self.u.reg_write(UC_X86_REG_EDX,0)
        self.h.run(0x6869dc,0x686a13)
        self.h.run(0x686d68,0x686d79)


def cases():
    yield 'ordinary',{},[('midas',180)]+[('tick',0)]*181
    yield 'one_frame',{},[('midas',1),('tick',0),('tick',0)]
    yield 'non_positive',{},[('midas',0),('midas',-90)]
    yield 'refuse_extension',{},[('midas',30),('midas',180)]+[('tick',0)]*31
    yield 'ordinary_shortens_ai_hold',{},[('midas',180),('ordinary',1)]+[('tick',0)]*181
    yield 'midas_overwrites_ordinary',{},[('ordinary',-300),('midas',180)]+[('tick',0)]*181
    yield 'boss_cooldown',{'boss':True},[('midas',180),('midas',180)]+[('tick',0)]*241
    yield 'golden_bypasses_cooldown',{'boss':True,'cooldown':120},[('midas',180),('golden',180),('golden',180)]+[('tick',0)]*241
    yield 'immune',{'flags':0x20000000,'cooldown':120},[('midas',180),('golden',180)]
    yield 'dead',{'flags':1},[('midas',180)]
    yield 'active_marker',{'flags':0x400,'midas':10},[('midas',180),('golden',180)]
    yield 'special_type_245',{'kind':245},[('midas',180)]
    yield 'pooter_body',{'kind':14},[('midas',180)]+[('tick',0)]*3


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--check',action='store_true');args=parser.parse_args()
    raw=HEALTH.MOTION.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==HEALTH.MOTION.SHA
    pe=pefile.PE(data=raw);native=NativeMidas(pe);OUT.mkdir(parents=True,exist_ok=True)
    def save(name,data):
        path=OUT/name
        if args.check:assert path.read_bytes()==data,name
        else:path.write_bytes(data)
    rows=[]
    for name,initial,operations in cases():
        native.reset(**initial);kind=initial.get('kind',10);boss=int(initial.get('boss',False))
        rows.append([name,-1,'initial',0,kind,boss,*native.snapshot(),0])
        for step,(operation,amount) in enumerate(operations):
            if operation=='tick':native.tick()
            else:native.apply(operation,amount)
            rows.append([name,step,operation,amount,kind,boss,*native.snapshot(),native.color_calls])
    text=io.StringIO(newline='');writer=csv.writer(text,lineterminator='\n')
    writer.writerow(['case','step','operation','amount','type','boss_metadata','flags','freeze','midas','cooldown','variant','color_calls']);writer.writerows(rows)
    save('native-midas.csv',text.getvalue().encode())
    rng_rows=[]
    for raw_rng in [0,1,2,3,4,5,6,7,8,0xfffffffe,0xffffffff]:
        sp=native.n.STACK+0x9000;native.u.mem_write(sp,struct.pack('<2I',0,native.n.STOP))
        native.u.reg_write(UC_X86_REG_ESP,sp);native.u.reg_write(UC_X86_REG_ESI,3);native.u.reg_write(UC_X86_REG_EAX,raw_rng)
        native.h.run(0x659240,native.n.STOP)
        native.h.run(0x69e867,0x69e86a)
        rng_rows.append([raw_rng,native.u.reg_read(UC_X86_REG_ESI)])
    text=io.StringIO(newline='');writer=csv.writer(text,lineterminator='\n');writer.writerow(['raw_rng','ordinary_isaac_death_coins']);writer.writerows(rng_rows)
    save('native-death-coins.csv',text.getvalue().encode())
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
    for name,start,end in WINDOWS:
        blob=pe.get_data(start-pe.OPTIONAL_HEADER.ImageBase,end-start)
        listing=''.join(f'{i.address:08x} {i.mnemonic} {i.op_str}\n' for i in md.disasm(blob,start)).encode()
        save(name+'.asm',listing)
        windows.append({'name':name,'start':hex(start),'end_exclusive':hex(end),'raw_sha256':hashlib.sha256(blob).hexdigest(),'listing_sha256':hashlib.sha256(listing).hexdigest()})
    manifest={'version':'Repentance 1.7.9b','exe_sha256':HEALTH.MOTION.SHA,'rows':len(rows),'cases':len({r[0] for r in rows}),
              'method':'Native AddMidas/AddFreeze, native immunity/duration/metadata/unlinked-propagation helpers; native bounded timer blocks. SetColor(0x68a380) alone is intercepted with native five-argument cleanup.',
              'fixture':'Synthetic unlinked NPC, original NPC vtable, type/boss metadata/raw flags specified by case; empty-inventory ordinary player EntityRef. Metadata is supplied fixture data, not acceptance of any boss controller.',
              'golden_scope':'Native cooldown-reset block then AddMidas; query selection/world burst is outside this trace.',
              'death_coin_scope':'Original modulo-helper tail and ordinary Isaac +1 block with supplied raw RNG. Global RNG/nearest-player query/spawn physics excluded; Keeper branch excluded.',
              'unverified':['live scheduling/physics','all actor immunity initialization','linked propagation/controllers','type245 gameplay morph','Midas damage propagation','world drop physics and RNG stream','item duration modifiers','full actor acceptance'],
              'windows':windows}
    save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode())
    print(f'{"Checked" if args.check else "Captured"} {len(rows)} native control states, {manifest["cases"]} cases, {len(rng_rows)} supplied-RNG coin cases; full acceptance remains open.')


if __name__=='__main__':main()
