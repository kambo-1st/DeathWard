#!/usr/bin/env python3
"""Bounded timed-effect arithmetic from the pinned installed executable.

Supplied ordinary player/item definitions and a preallocated effect vector.
Costume removal is intercepted; no full input/world/scheduler acceptance claim.
"""
import argparse, csv, hashlib, importlib.util, io, json, struct
from pathlib import Path
import xml.etree.ElementTree as ET
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import *
spec=importlib.util.spec_from_file_location('health',Path(__file__).with_name('analyze-player-health.py'))
H=importlib.util.module_from_spec(spec);spec.loader.exec_module(H)

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
    raw=H.MOTION.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==H.MOTION.SHA
    pe=H.pefile.PE(data=raw);f=H.NativeHealth(pe);n=f.native;u=f.u
    out=H.MOTION.ROOT/'docs/reports/isaac-first-floor-parity/pw-a02-book-of-shadows/source'
    if not args.check:out.mkdir(parents=True,exist_ok=True)
    def save(name,data):
        if args.check:assert (out/name).read_bytes()==data,name
        else:(out/name).write_bytes(data)
    def integer(a):return struct.unpack('<I',u.mem_read(a,4))[0]
    def call(a,ecx,*values):
        sp=n.STACK+0x9000;u.mem_write(sp,struct.pack('<'+'I'*(len(values)+1),n.STOP,*values))
        u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,ecx)
        u.emu_start(a,n.STOP,count=100000);assert u.reg_read(UC_X86_REG_EIP)==n.STOP
        return u.reg_read(UC_X86_REG_EAX)
    def effects(uc,address,size,data):
        if address==0x9ec358: # External CRT memmove import; overlap-safe semantics.
            sp=uc.reg_read(UC_X86_REG_ESP);ret,dst,src,size=struct.unpack('<4I',uc.mem_read(sp,16))
            if size:uc.mem_write(dst,bytes(uc.mem_read(src,size)))
            uc.reg_write(UC_X86_REG_EAX,dst);uc.reg_write(UC_X86_REG_ESP,sp+4);uc.reg_write(UC_X86_REG_EIP,ret)
        elif address==0x75a130: # RemoveCostume side effect after actual vector erase.
            sp=uc.reg_read(UC_X86_REG_ESP);uc.reg_write(UC_X86_REG_EIP,integer(sp));uc.reg_write(UC_X86_REG_ESP,sp+12)
    u.hook_add(UC_HOOK_CODE,effects)
    definition=f.ITEMS+0x10000+58*0x200;entry=f.ITEMS+0xe0000;temp=entry+0x100;owner=n.PLAYER+0x1450
    f.write(definition,3);f.write(definition+4,58);f.write(definition+0x78,300);f.write(definition+0x74,3)
    f.write(owner+4,entry);f.write(owner+8,entry);f.write(owner+12,entry+120);f.write(owner+20,n.PLAYER)
    call(0x427600,temp,definition);assert integer(temp+8)==300
    call(0x88b1c0,owner,temp,0,1);assert integer(entry+8)==300 and integer(entry+4)==1
    rows=[]
    for tick in range(301):
        present=call(0x88b570,owner,58)&255
        rows.append([tick,integer(entry+8) if present else 0,present])
        assert bool(present)==(tick<300)
        if tick<300:call(0x88b6f0,owner)
    stream=io.StringIO();w=csv.writer(stream,lineterminator='\n');w.writerow(['effect_tick','remaining','protected_effect_present']);w.writerows(rows);save('native-timer.csv',stream.getvalue().encode())
    call(0x88b1c0,owner,temp,0,1)
    for _ in range(90):call(0x88b6f0,owner)
    call(0x88b1c0,owner,temp,0,1)
    assert integer(entry+8)==510 and integer(entry+4)==2
    charge=[];f.write(n.PLAYER+0x14c4,58)
    for before in range(4):
        for amount in (1,2,3):
            f.write(n.PLAYER+0x14c8,before);sp=n.STACK+0x9000
            u.mem_write(sp,struct.pack('<6I',n.STOP,amount,0,0,0,0));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,n.PLAYER)
            u.emu_start(0x758030,0x758135,count=100000)
            after=integer(n.PLAYER+0x14c8);assert after==min(3,before+amount);charge.append([before,amount,after])
    stream=io.StringIO();w=csv.writer(stream,lineterminator='\n');w.writerow(['charge','award','next_charge']);w.writerows(charge);save('native-charge.csv',stream.getvalue().encode())
    source=H.MOTION.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3'
    item=next(x for x in ET.parse(source/'items.xml').getroot() if x.tag=='active' and x.get('id')=='58')
    pool=next(x for x in ET.parse(source/'itempools.xml').getroot() if x.get('Name')=='treasure');treasure=next(x for x in pool if x.get('Id')=='58')
    assert item.get('cooldown')=='300' and item.get('maxcharges')=='3' and treasure.get('Weight')=='1'
    windows=[];md=H.capstone.Cs(3,4)
    for name,a,z in [('effect-constructor',0x427600,0x42761b),('use-effect-caller',0x5b229c,0x5b22eb),('effect-add',0x88b1c0,0x88b264),('effect-update',0x88b6f0,0x88b7b5),('player-update-caller',0x74dd43,0x74dd6a),('damage-protection-gate',0x786a60,0x786ab6),('charge-capacity',0x757d80,0x757e40),('charge-update',0x758030,0x758149)]:
        blob=pe.get_data(a-0x400000,z-a);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,a))+'\n').encode());windows.append(dict(name=name,start=hex(a),end=hex(z),sha256=hashlib.sha256(blob).hexdigest()))
    manifest=dict(executable_sha256=H.MOTION.SHA,item=item.attrib,treasure=treasure.attrib,timer_states=len(rows),charge_cases=len(charge),repeat={'after_ticks':90,'remaining_before':210,'remaining_after':510},windows=windows,
        scope='Executed native effect constructor, first/repeated AddTemporaryEffect, all 300 Update ticks including erase, HasCollectibleEffect and primary recharge. Native generic use caller and damage-protection branch are disassembled, not full wrappers executed. Preallocated effect vector; CRT memmove emulated; native costume removal endpoint intercepted. DW uses 30 effect updates/second as its explicit active-gameplay adapter; full source scheduler, transitions, special damage bypass flags, modifiers/co-op/pocket slots and item-pool/factory acceptance remain open.',full_native_acceptance=False)
    save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode());print('PASS 301 effect states, additive reuse, 12 charge cases')
if __name__=='__main__':main()
