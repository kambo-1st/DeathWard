#!/usr/bin/env python3
"""Pinned ordinary blood-machine blast gates and destruction drop instructions."""
import argparse, csv, hashlib, importlib.util, io, json, struct
from pathlib import Path
import capstone, pefile
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import *

spec = importlib.util.spec_from_file_location('awards', Path(__file__).with_name('analyze-room-awards.py'))
A = importlib.util.module_from_spec(spec); spec.loader.exec_module(A)

def main():
    parser=argparse.ArgumentParser(); parser.add_argument('--check',action='store_true'); args=parser.parse_args()
    raw=A.M.EXE.read_bytes(); assert hashlib.sha256(raw).hexdigest()==A.M.SHA
    pe=pefile.PE(data=raw); f=A.NativeAwards(pe,raw); n=f.n; u=f.u; b=n.ebp
    actor=f.HEAP+0x10000; spawned=[]; reached=[]
    out=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d14a12-blood-machine-explosions/source'; out.mkdir(parents=True,exist_ok=True)
    def save(name,data):
        path=out/name
        if args.check: assert path.read_bytes()==data,name
        else:path.write_bytes(data)
    def csvfile(name,columns,rows):
        buf=io.StringIO(); w=csv.writer(buf,lineterminator='\n');w.writerow(columns);w.writerows(rows);save(name,buf.getvalue().encode())
    def hook(u,address,size,data):
        if address in [0x6400b8,0x640916,0x63f92d]:
            reached.append(address);u.emu_stop();return
        sp=u.reg_read(UC_X86_REG_ESP);ret=f.integer(sp)
        if address==0x6c3450:
            result=u.reg_read(UC_X86_REG_ECX);u.mem_write(result,struct.pack('<2f',0,0));cleanup=0
        else:
            values=struct.unpack('<7I',u.mem_read(sp+4,28));spawned.append(values);result=actor+0x1000;cleanup=28
        u.reg_write(UC_X86_REG_EAX,result);u.reg_write(UC_X86_REG_ESP,sp+4+cleanup);u.reg_write(UC_X86_REG_EIP,ret)
    for address in [0x6400b8,0x640916,0x63f92d,0x6c3450,0x422e20]:
        u.hook_add(UC_HOOK_CODE,hook,begin=address,end=address)
    gates=[]
    for state in [0,1,2,3,4,5]:
        for flags in [0,4,32,36,0x1000004]:
            for damage in [0,1,100]:
                reached.clear();sp=n.STACK+0x7000
                f.write(actor+0x2c,2);f.write(actor+0x360,state)
                u.mem_write(sp,struct.pack('<If4I',n.STOP,float(damage),flags,0,actor+0x2000,0))
                u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,actor)
                u.emu_start(0x640070,n.STOP,count=10000)
                assert reached and reached[-1] in [0x6400b8,0x640916]
                gates.append([state,flags,damage,int(reached[-1]==0x640916),f.integer(actor+0x360)])
    csvfile('native-blast-gates.csv',['state','damage_flags','damage','accepted','after_state'],gates)
    rows=[]
    for seed in [((i+1)*0x9e3779b9)&0xffffffff for i in range(1024)]+[1,6,20,42,12345,0xffffffff]:
        spawned.clear();reached.clear()
        u.reg_write(UC_X86_REG_EBP,b);u.reg_write(UC_X86_REG_ESP,b-0x2000)
        u.reg_write(UC_X86_REG_EBX,actor);u.reg_write(UC_X86_REG_EAX,2)
        f.write(b-0x48,0);f.write(b-0x4c,actor) # Daemon's Tail absent; retained actor.
        u.mem_write(actor+0x334,struct.pack('<4I',seed,4,3,17))
        u.emu_start(0x63f841,0x63f92d,count=100000)
        assert u.reg_read(UC_X86_REG_EIP)==0x63f92d and 1<=len(spawned)<=8
        assert all(v[0]==5 and v[1] in [10,20] and v[5]==0 for v in spawned)
        pairs=[value for v in spawned for value in [v[1],v[6]]]+[0]*(16-2*len(spawned))
        rows.append([seed,len(spawned),*pairs,f.integer(actor+0x334)])
    csvfile('native-blast-drops.csv',['seed','count',*[name for i in range(8) for name in [f'variant{i}',f'seed{i}']],'after_seed'],rows)
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
    for name,start,end in [('damage-gate',0x640070,0x6400d9),('damage-state',0x64087e,0x640916),('damage-tail',0x640df4,0x640f0b),('destroy-setup',0x63f660,0x63f6c3),('blood-drops',0x63f841,0x63f93e)]:
        blob=pe.get_data(start-0x400000,end-start)
        save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,start))+'\n').encode())
        windows.append({'name':name,'start':hex(start),'end':hex(end),'sha256':hashlib.sha256(blob).hexdigest()})
    manifest={'baseline':'Installed Repentance1.7.9b','executable_sha256':A.M.SHA,'gate_cases':len(gates),'drop_cases':len(rows),'windows':windows,'rng_shifts':[4,3,17],'scope':'Ordinary blood machine variant2. Original explosion-flag/state gates stop before visual spawning; original destruction selector executes with absent Daemons Tail and hosted position/factory calls. Output variants and per-pickup init seeds are observed. Full native damage wrapper, visual effects, thrown pickup arrival, RNG streams after DW donation cycles, profile and scheduler are not accepted.','full_native_acceptance':False}
    save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode());print('PASS',len(gates),'blast gates,',len(rows),'native destruction outcomes')

if __name__=='__main__':main()
