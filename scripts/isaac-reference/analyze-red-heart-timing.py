#!/usr/bin/env python3
"""Execute installed red-heart appearance gates and appearance/collection frame timelines."""
import argparse,csv,hashlib,importlib.util,io,json,struct
from pathlib import Path
import capstone,pefile
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import *
def module(name,file):
    spec=importlib.util.spec_from_file_location(name,Path(__file__).with_name(file));m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
M=module('motion','analyze-player-motion.py');NM=module('native_math','native_math.py')
OUT=M.ROOT/'docs/reports/isaac-first-floor-parity/d09a-heart-timing'

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--check',action='store_true');args=parser.parse_args()
    raw=M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==M.SHA
    pe=pefile.PE(data=raw);n=M.NativeMotion(pe);u=n.u;math=NM.NativeMath(n,pe,('floor',));p=n.PLAYER;b=n.ebp
    class Access:
        def write(self,address,value):u.mem_write(address,struct.pack('<I',value&0xffffffff))
        def integer(self,address):return struct.unpack('<I',u.mem_read(address,4))[0]
        def run(self,start):n.run(start,n.STOP)
    f=Access()
    sprite=p+0x3c;layer=p+0x6c;animation=n.STACK+0x2000;events=n.STACK+0x3000;trigger=n.STACK+0x4000
    OUT.mkdir(parents=True,exist_ok=True)
    def save(name,data):
        q=OUT/name
        if args.check:assert q.read_bytes()==data,name
        else:q.write_bytes(data)
    def table(name,fields,rows):
        s=io.StringIO(newline='');w=csv.writer(s,lineterminator='\n');w.writerow(fields);w.writerows(rows);save(name,s.getvalue().encode())
    def string(at,value):
        blob=value.encode();assert len(blob)<16
        u.mem_write(at,blob+b'\0'*(16-len(blob)));f.write(at+0x10,len(blob));f.write(at+0x14,15)
    def setup(name,length,drop,playing=True,mask=0,collision=0):
        u.mem_write(p,bytes(0x1000));u.mem_write(animation,bytes(0x100));u.mem_write(b-0x1000,bytes(0x1100))
        f.write(p+0x2c,10);f.write(p+0x30,1);f.write(p+0x180,collision)
        f.write(layer,sprite);f.write(layer+4,animation);n.write_float(sprite+0x104,1)
        u.mem_write(layer+0x14,bytes([int(playing)]));f.write(layer+0x18,mask)
        f.write(sprite+0x8c,events);f.write(sprite+0x90,1);string(events,'DropSound')
        string(animation,name);f.write(animation+0x30,length);f.write(animation+0x28,trigger);f.write(animation+0x2c,int(drop>=0))
        f.write(trigger,0);f.write(trigger+4,max(drop,0));self_state['sound']=self_state['idle']=0
    self_state={'sound':0,'idle':0}
    def presentation(uc,address,size,data):
        sp=uc.reg_read(UC_X86_REG_ESP);ret=f.integer(sp)
        if address==0x6be0a0:
            self_state['sound']+=1;uc.reg_write(UC_X86_REG_ESP,sp+4)
        else:
            name=f.integer(sp+4);assert bytes(uc.mem_read(name,5))==b'Idle\0'
            self_state['idle']+=1;string(animation,'Idle');f.write(animation+0x30,30)
            u.mem_write(animation+0x34,b'\x01');f.write(animation+0x2c,0)
            n.write_float(layer+0x10,0);u.mem_write(layer+0x14,b'\x01');f.write(layer+0x18,0)
            uc.reg_write(UC_X86_REG_ESP,sp+12)
        uc.reg_write(UC_X86_REG_EIP,ret)
    for address in (0x6be0a0,0x4054f0):u.hook_add(UC_HOOK_CODE,presentation,begin=address,end=address)
    def gate():
        for reg,value in ((UC_X86_REG_EDI,p),(UC_X86_REG_EBP,b),(UC_X86_REG_ESP,b-0x1000)):u.reg_write(reg,value)
        n.run(0x6bb8c5,0x6bba3b)
    gates=[]
    for name in ('Appear','AppearFast','Reappear','Idle','Other'):
        for playing in (0,1):
            for event in (0,1):
                for collision in (0,4):
                    setup(name,33,23,playing,event,collision);gate()
                    gates.append([name,playing,event,collision,f.integer(p+0x180),self_state['sound'],self_state['idle']])
    table('native-appearance-gates.csv',['animation','playing','drop_event','initial_collision','after_collision','sound_calls','idle_calls'],gates)
    metadata=OUT/'animations/manifest.json'
    m=json.loads(metadata.read_text());timelines=[]
    for asset in m['files']:
        for anim in asset['animations']:
            name=anim['attributes']['Name']
            if name not in ('Appear','AppearFast','Reappear'):continue
            length=int(anim['attributes']['FrameNum']);drop=next((int(t['AtFrame']) for t in anim['triggers'] if t['EventId']=='0'),-1)
            for speed in (.25,.5,1,1.05,4):
                setup(name,length,drop);n.write_float(sprite+0x104,speed)
                for tick in range(141):
                    if tick:
                        sp=n.STACK+0x9000;f.write(sp,n.STOP);u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,layer);f.run(0x403d60);gate()
                    timelines.append([Path(asset['path']).name,name,length,drop,speed,tick,n.read_float(layer+0x10),u.mem_read(layer+0x14,1)[0],f.integer(layer+0x18),f.integer(p+0x180),self_state['sound'],self_state['idle']])
    table('native-appearance-timelines.csv',['asset','animation','length','drop_frame','speed','tick','frame','playing','event_mask','collision','sound_calls','idle_calls'],timelines)
    collection=[]
    # Supply the consumed flag written by the native collection tail. Execute
    # the cleanup decision, stopping at the virtual Remove endpoint.
    def removal():
        f.write(p,n.STACK+0x6000);f.write(n.STACK+0x6028,n.STOP)
        u.mem_write(b-0x8e,b'\x01')
        for reg,value in ((UC_X86_REG_EDI,p),(UC_X86_REG_EBP,b),(UC_X86_REG_ESP,b-0x1000)):u.reg_write(reg,value)
        hook=u.hook_add(UC_HOOK_CODE,lambda uc,a,size,data:uc.emu_stop(),begin=0x6bb8c5,end=0x6bb8c5)
        try:u.emu_start(0x6bb8a1,n.STOP,count=100)
        finally:u.hook_del(hook)
        pc=u.reg_read(UC_X86_REG_EIP);assert pc in (n.STOP,0x6bb8c5),hex(pc)
        return int(pc==n.STOP)

    for asset in m['files']:
        length=int(next(a for a in asset['animations'] if a['attributes']['Name']=='Collect')['attributes']['FrameNum'])
        setup('Collect',length,-1)
        for tick in range(16):
            if tick:
                sp=n.STACK+0x9000;f.write(sp,n.STOP);u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,layer);f.run(0x403d60)
            collection.append([Path(asset['path']).name,length,tick,n.read_float(layer+0x10),u.mem_read(layer+0x14,1)[0],removal()])
    table('native-collection-timelines.csv',['asset','length','tick','frame','playing','remove_called'],collection)
    windows=[]
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    for name,start,end in [('appearance_gate',0x6bb8c5,0x6bba3b),('layer_update',0x403d60,0x403e21),('pickup_initial_counter',0x6b706a,0x6b7074),('pickup_initial_appearance',0x6b7bf2,0x6b7c11),('pickup_collection_tail',0x6c25a2,0x6c25d6),('pickup_update_order',0x6bb274,0x6bb48a),('pickup_animation_cleanup',0x6bb8a1,0x6bb8c5)]:
        data=pe.get_data(start-pe.OPTIONAL_HEADER.ImageBase,end-start)
        save(name+'.asm', ''.join(f'{i.address:08x} {i.mnemonic} {i.op_str}\n' for i in md.disasm(data,start)).encode())
        windows.append({'name':name,'start':hex(start),'end_exclusive':hex(end),'sha256':hashlib.sha256(data).hexdigest()})
    manifest={'executable_sha256':M.SHA,'native_math':math.manifest(),'gate_cases':len(gates),'timeline_states':len(timelines),'collection_states':len(collection),'animation_metadata_sha256':hashlib.sha256(metadata.read_bytes()).hexdigest(),'windows':windows,
      'scope':'Original native layer frame/event advance and pickup appearance collision gate for variant10 with parsed installed full/half/double-heart metadata. Sound endpoint and Play(Idle) state reset hosted. Supplied initial Appear/collision state and frame invocation; Collect frames and cleanup gate execute with supplied consumed flag and virtual Remove endpoint. Complete factory, room scheduler and physical/health eligibility not executed.',
      'full_acceptance':False}
    save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode())
    print(f'Captured {len(gates)} gates and {len(timelines)} native red-heart frame/event states.')

if __name__=='__main__':main()
