#!/usr/bin/env python3
"""Original ordinary shop/treasure lock decision, supplied stage/type/mode.
Stops at the lock assignment or the unlocked continuation before world/animation.
"""
import argparse,csv,hashlib,importlib.util,io,json,struct,itertools
from pathlib import Path
import capstone,pefile
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import *
spec=importlib.util.spec_from_file_location('awards',Path(__file__).with_name('analyze-room-awards.py'))
A=importlib.util.module_from_spec(spec);spec.loader.exec_module(A)
OUT=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d10d-room-locks/source'
def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--check',action='store_true');args=ap.parse_args()
    raw=A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==A.M.SHA
    pe=pefile.PE(data=raw);f=A.NativeAwards(pe,raw);u=f.u;n=f.n;door=n.PLAYER+0x5000;rows=[]
    def stop(uc,address,size,data):uc.emu_stop()
    for a in (0x6e1864,0x6e1a5f):u.hook_add(UC_HOOK_CODE,stop,begin=a,end=a)
    for stage,stage_type,mode,origin,target in itertools.product(range(1,9),range(6),(0,1),(1,2,4),(1,2,4)):
            u.mem_write(door,bytes(0x400));f.write(door+0x158,origin);f.write(door+0x15c,target);f.write(door+0x27c,85)
            f.write(f.GAME,stage);f.write(f.GAME+4,stage_type);f.write(f.GAME+0x243624,mode);f.write(f.GAME+0x1c319c,0)
            f.write(n.ebp+8,origin);f.write(n.ebp+12,target);u.mem_write(n.ebp-1,b'\0');f.write(n.PLAYER+0x130c,0)
            for reg,value in [(UC_X86_REG_EBP,n.ebp),(UC_X86_REG_ESP,n.ebp-0x1000),(UC_X86_REG_ESI,door),(UC_X86_REG_EDI,f.GAME),(UC_X86_REG_ECX,85)]:u.reg_write(reg,value)
            u.emu_start(0x6e194c,n.STOP,count=10000)
            pc=u.reg_read(UC_X86_REG_EIP);assert pc in (0x6e1864,0x6e1a5f),hex(pc)
            locked=int(pc==0x6e1864);assert locked==int(target in (2,4) and (stage!=1 or stage_type in (4,5)))
            if locked:assert f.integer(door+8)==1
            rows.append([stage,stage_type,mode,origin,target,locked])
    OUT.mkdir(parents=True,exist_ok=True)
    def save(name,data):
        path=OUT/name
        if args.check:assert path.read_bytes()==data,name
        else:path.write_bytes(data)
    buf=io.StringIO(newline='');w=csv.writer(buf,lineterminator='\n');w.writerow(['stage','stage_type','mode','from_room_type','to_room_type','locked']);w.writerows(rows);save('native-locks.csv',buf.getvalue().encode())
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
    for name,start,end in [('ordinary-lock-policy',0x6e1947,0x6e1a69),('stage-type',0x718ae0,0x718af3),('greed-mode',0x6cba40,0x6cba56),('player-type-query',0x5ef580,0x5ef5b4)]:
        blob=pe.get_data(start-0x400000,end-start);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,start))+'\n').encode());windows.append(dict(name=name,start=hex(start),end=hex(end),sha256=hashlib.sha256(blob).hexdigest()))
    save('manifest.json',(json.dumps(dict(executable_sha256=A.M.SHA,cases=len(rows),windows=windows,method='Original decision instructions and helper calls; supplied ordinary room metadata/Normal-Hard mode/stage/type. Stop hooks only at decision boundaries.',scope='Ordinary Isaac, no special challenge, red/secret connections, previously opened state, Greed, item overrides or world/animation callbacks. Types4/5 are contrast cases; DW enables only its ordinary mapped stage family.',full_native_acceptance=False),indent=2)+'\n').encode())
    print(f'PASS {len(rows)} native ordinary lock decisions; both shop and treasure are free at ordinary stage1.')
if __name__=='__main__':main()
