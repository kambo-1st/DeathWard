#!/usr/bin/env python3
"""Bounded ordinary Yum Heart arithmetic from the installed read-only executable.
Supplied player/slot/descriptor state; no native world or actor-wrapper claim.
"""
import argparse, csv, hashlib, importlib.util, io, json, struct
from pathlib import Path
import xml.etree.ElementTree as ET
from unicorn.x86_const import *
spec=importlib.util.spec_from_file_location('health',Path(__file__).with_name('analyze-player-health.py'))
H=importlib.util.module_from_spec(spec);spec.loader.exec_module(H)

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
    raw=H.MOTION.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==H.MOTION.SHA
    pe=H.pefile.PE(data=raw);f=H.NativeHealth(pe);n=f.native;u=f.u
    out=H.MOTION.ROOT/'docs/reports/isaac-first-floor-parity/pw-a01-yum-heart/source'
    if not args.check:out.mkdir(parents=True,exist_ok=True)
    def save(name,data):
        if args.check:assert (out/name).read_bytes()==data,name
        else:(out/name).write_bytes(data)
    def table(name,header,rows):
        s=io.StringIO();w=csv.writer(s,lineterminator='\n');w.writerow(header);w.writerows(rows);save(name,s.getvalue().encode())
    def block(a,z):
        u.emu_start(a,z,count=100000);assert u.reg_read(UC_X86_REG_EIP)==z
    heals=[]
    for capacity in (0,2,6,12):
        for bone in (0,1):
            for hp in range(capacity+2*bone+1):
                if hp==0 and capacity==0 and bone==0: soul=2
                else:soul=0
                f.reset()
                for key,value in [('max_red',capacity),('red',hp),('bone',bone),('soul',soul)]:f.write(n.PLAYER+H.FIELDS[key],value)
                u.reg_write(UC_X86_REG_ESP,n.STACK+0x9000);u.reg_write(UC_X86_REG_EAX,n.PLAYER);u.reg_write(UC_X86_REG_ESI,n.PLAYER)
                # Actual owner-vs-other amount branch and full original AddHearts.
                block(0x5a287c,0x5a288e)
                after=f.snapshot();assert after['red']==min(hp+2,capacity+2*bone)
                heals.append([capacity,bone,hp,soul,after['red'],after['soul']])
    table('native-healing.csv',['capacity','bone','red','soul','next_red','next_soul'],heals)
    discharges=[]
    for hp in range(7):
        f.reset();f.write(n.PLAYER+0x1294,hp);f.write(n.PLAYER+0x14c4,45);f.write(n.PLAYER+0x14c8,4)
        f.write(f.ITEMS+0x10000+45*0x200+0x74,4)
        sp=n.STACK+0x9000;u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_EBP,n.ebp)
        u.reg_write(UC_X86_REG_EBX,sp+0x200);f.write(sp+0x208,0);f.write(sp+0x20c,0);u.reg_write(UC_X86_REG_ECX,n.PLAYER)
        # Bypass SEH prologue only; original admission/modifier queries and SetActiveCharge.
        block(0x771551,0x771788)
        charge=struct.unpack('<I',u.mem_read(n.PLAYER+0x14c8,4))[0];assert charge==0
        discharges.append([hp,4,charge])
    table('native-discharge.csv',['red','charge','next_charge'],discharges)
    f.reset();f.write(n.PLAYER+0x14c4,45);definition=f.ITEMS+0x10000+45*0x200
    f.write(definition+0x74,4)
    charges=[]
    for current in range(5):
        for amount in (1,2,4):
            f.write(n.PLAYER+0x14c8,current)
            sp=n.STACK+0x9000;u.mem_write(sp,struct.pack('<6I',n.STOP,amount,0,0,0,0))
            u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,n.PLAYER)
            # Original item lookup/capacity query and clamped primary-charge write.
            # Stop before battery/visual/sound side effects.
            block(0x758030,0x758135)
            after=struct.unpack('<I',u.mem_read(n.PLAYER+0x14c8,4))[0]
            assert after==min(4,current+amount);charges.append([current,amount,after])
    table('native-charge.csv',['charge','award','next_charge'],charges)
    room=f.ITEMS+0xe0000;descriptor=room+0x100;layout=room+0x200
    f.write(f.GAME+0x18190,room);f.write(room+4,descriptor);f.write(descriptor+0x10,layout)
    shapes=[]
    for kind in (1,17):
        for shape in range(1,13):
            f.write(room+8,kind);f.write(layout+0x48,shape)
            u.reg_write(UC_X86_REG_EBP,n.ebp);u.reg_write(UC_X86_REG_ESP,n.STACK+0x9000)
            block(0x76e226,0x76e271);award=u.reg_read(UC_X86_REG_ESI)
            assert award==(2 if kind!=17 and shape in (8,9,10,11,12) else 1);shapes.append([kind,shape,award])
    table('native-room-charge.csv',['room_type','shape','ordinary_award'],shapes)
    source=H.MOTION.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3'
    item=next(x for x in ET.parse(source/'items.xml').getroot() if x.tag=='active' and x.get('id')=='45')
    pool=next(x for x in ET.parse(source/'itempools.xml').getroot() if x.get('Name')=='treasure');entry=next(x for x in pool if x.get('Id')=='45')
    assert item.get('maxcharges')=='4' and entry.get('Weight')=='1'
    windows=[];md=H.capstone.Cs(3,4)
    for name,a,z in [('yum-effect',0x5a2818,0x5a28a5),('result-default',0x5a1360,0x5a1430),('use-discharge-caller',0x7599f2,0x759ad0),('charge-capacity',0x757d80,0x757e40),('charge-arithmetic',0x758030,0x758149),('clear-charge',0x76e140,0x76e4a6),('discharge',0x771510,0x772000)]:
        blob=pe.get_data(a-0x400000,z-a);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,a))+'\n').encode());windows.append(dict(name=name,start=hex(a),end=hex(z),sha256=hashlib.sha256(blob).hexdigest()))
    manifest=dict(executable_sha256=H.MOTION.SHA,item=item.attrib,treasure=entry.attrib,healing_cases=len(heals),charge_cases=len(charges),discharge_cases=len(discharges),room_charge_cases=len(shapes),windows=windows,
      scope='Executed owner amount branch plus original AddHearts and ordinary discharge through original SetActiveCharge (SEH prologue bypassed); supplied slot primary-charge arithmetic and room-shape award branch. Ordinary Yum effect leaves default discharge=true even with full health; primary caller invokes discharge on this result. Full use/input/animation/co-op/room-clear scheduler, modifiers, battery/pocket slots and factory acceptance are not certified. DeathWard uses one charge per first hostile-room clear with its retained canyon shapes; no area multiplier inferred from dynamic size. Regeneration ledger is an explicit testing policy.',full_native_acceptance=False)
    save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode())
    print('PASS',len(heals),'healing,',len(charges),'charge,',len(shapes),'room-charge cases')
if __name__=='__main__':main()
