#!/usr/bin/env python3
"""Pinned ordinary key spending and bounded ordinary-door admission.

Supplied ordinary player/door fields; no source arithmetic is replaced.
The door block stops before animation/geometry callbacks. Lock generation,
special doors, golden resources and item effects are outside this delivery.
"""
import argparse,csv,hashlib,importlib.util,io,json,struct
from pathlib import Path
import capstone,pefile
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import *

spec=importlib.util.spec_from_file_location('awards',Path(__file__).with_name('analyze-room-awards.py'))
A=importlib.util.module_from_spec(spec);spec.loader.exec_module(A)
OUT=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d10c-keyed-doors/source'

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--check',action='store_true');args=ap.parse_args()
    raw=A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==A.M.SHA
    pe=pefile.PE(data=raw);f=A.NativeAwards(pe,raw);n=f.n;u=f.u;p=n.PLAYER;door=p+0x5000
    sp=n.STACK+0xd000;counts=(-1,0,1,2,3,5,98,99);spends=[];doors=[]
    def signed(value):return value if value<0x80000000 else value-0x100000000
    for count in counts:
        f.write(p+0x12ac,count);u.mem_write(p+0x12b0,b'\0')
        u.mem_write(sp,struct.pack('<I',n.STOP));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,p)
        f.run(0x726070)
        after=signed(f.integer(p+0x12ac));ok=u.reg_read(UC_X86_REG_EAX)&255
        assert after==count-int(count>0) and ok==int(count>0)
        spends.append([count,after,ok])
    def stop(uc,address,size,data):uc.emu_stop()
    hooks=[u.hook_add(UC_HOOK_CODE,stop,begin=a,end=a) for a in (0x6e124c,0x6e13a4)]
    for state,substate in [(1,0),(1,2),(8,2)]:
        for count in counts:
            u.mem_write(door,bytes(0x400));f.write(door+8,state);f.write(door+0xc,substate);f.write(door+0x15c,4)
            f.write(p+0x12ac,count);u.mem_write(p+0x12b0,b'\0');f.write(n.ebp+0xc,0)
            for reg,val in [(UC_X86_REG_ESP,sp),(UC_X86_REG_EBP,n.ebp),(UC_X86_REG_ESI,p),(UC_X86_REG_EDI,door)]:u.reg_write(reg,val)
            u.emu_start(0x6e112e,n.STOP,count=200000)
            pc=u.reg_read(UC_X86_REG_EIP);assert pc in (0x6e124c,0x6e13a4)
            admitted=int(pc==0x6e124c);after=signed(f.integer(p+0x12ac))
            assert admitted==int(state==1 and substate!=2 and count>0)
            assert after==count-admitted
            doors.append([state,substate,count,after,admitted])
    for hook in hooks:u.hook_del(hook)
    OUT.mkdir(parents=True,exist_ok=True)
    def save(name,data):
        path=OUT/name
        if args.check:assert path.read_bytes()==data,name
        else:path.write_bytes(data)
    for name,header,rows in [('native-spend.csv',['before','after','spent'],spends),('native-doors.csv',['state','substate','before','after','admitted'],doors)]:
        buf=io.StringIO(newline='');w=csv.writer(buf,lineterminator='\n');w.writerow(header);w.writerows(rows);save(name,buf.getvalue().encode())
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
    for name,start,end,scope in [('use-key',0x726070,0x726181,'complete ordinary helper'),('door-admission',0x6e112e,0x6e124c,'bounded admitted ordinary branch'),('door-context',0x6e0bc0,0x6e13ac,'static full caller context')]:
        blob=pe.get_data(start-0x400000,end-start)
        save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,start))+'\n').encode())
        windows.append(dict(name=name,start=hex(start),end=hex(end),sha256=hashlib.sha256(blob).hexdigest(),scope=scope))
    save('manifest.json',(json.dumps(dict(executable_sha256=A.M.SHA,spend_cases=len(spends),door_cases=len(doors),windows=windows,
        method='Original x86 code and native key/bookkeeping/trinket-count helpers; memory imports hosted by existing ordinary empty-inventory fixture. Stop hooks only at branch boundaries.',
        scope='Ordinary finite keys, golden flag off, force off, no item overrides; door kind1/subtype4, no special flags. No animation/collision/factory or source floor-lock policy acceptance.',
        full_native_acceptance=False),indent=2)+'\n').encode())
    print(f'PASS {len(spends)} native key-spend cases and {len(doors)} bounded door-admission cases.')

if __name__=='__main__':main()
