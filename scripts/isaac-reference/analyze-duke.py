#!/usr/bin/env python3
"""Execute original ordinary Duke AI with explicit external spawn/graphics boundaries."""
import argparse,csv,hashlib,importlib.util,io,json,struct
from pathlib import Path
import pefile,capstone,xml.etree.ElementTree as ET
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import *
def module(name,file):
    spec=importlib.util.spec_from_file_location(name,Path(__file__).with_name(file));m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
A=module('awards','analyze-room-awards.py');NM=module('native_math','native_math.py')
OUT=A.M.ROOT/'docs/reports/isaac-first-floor-parity/duke'
class NativeDuke:
    def __init__(self,pe,raw):
        self.f=f=A.NativeAwards(pe,raw);self.n=n=f.n;self.u=u=f.u;self.boss=n.PLAYER+0x4000;self.sp=n.STACK+0x9000
        self.math=NM.NativeMath(f,pe,('floor',))
        path=Path('/mnt/c/Windows/SysWOW64/vcruntime140.dll');data=path.read_bytes();self.rtti_sha=hashlib.sha256(data).hexdigest();assert self.rtti_sha=='2fa6efc053203460a23d3a25158f227d895d2dadc63acc1a372da97c3a4281c3'
        dll=pefile.PE(data=data);dll.relocate_image(0x11000000);u.mem_map(0x11000000,(dll.OPTIONAL_HEADER.SizeOfImage+4095)&~4095);u.mem_write(0x11000000,dll.get_memory_mapped_image())
        export=next(e for e in dll.DIRECTORY_ENTRY_EXPORT.symbols if e.name==b'__RTDynamicCast');f.write(0xa06464,0x11000000+export.address)
        self.effect_update=struct.unpack('<I',pe.get_data(0xb459fc-pe.OPTIONAL_HEADER.ImageBase,4))[0]
        u.mem_map(0x12000000,0x1000);f.write(0xa064c0,0x12000000)
        self.endpoints={0x12000000:self.os_clock,0x422e20:self.spawn,0x888de0:self.audio,self.effect_update:self.graphics,0x68a380:self.color}
        for address in self.endpoints:u.hook_add(UC_HOOK_CODE,self.endpoint,begin=address,end=address)
        self.metadata=json.loads((OUT/'animations/manifest.json').read_text())['files'][0]
        self.frame=0;self.births=[];self.sounds=[];self.next_actor=f.HEAP+0x280000;self.effects=0
    def call(self,address,this,args=()):
        self.u.mem_write(self.sp,struct.pack('<'+'I'*(1+len(args)),self.n.STOP,*args));self.u.reg_write(UC_X86_REG_ESP,self.sp);self.u.reg_write(UC_X86_REG_ECX,this);self.f.run(address)
    def endpoint(self,u,address,size,data):
        sp=u.reg_read(UC_X86_REG_ESP);ret=self.f.integer(sp);pop,result=self.endpoints[address](sp)
        if result is not None:u.reg_write(UC_X86_REG_EAX,result)
        u.reg_write(UC_X86_REG_ESP,sp+pop);u.reg_write(UC_X86_REG_EIP,ret)
    def os_clock(self,sp):return 4,0
    def refs(self,at):
        sentinel=at+0xe00
        for off in (0,4,8):self.f.write(sentinel+off,sentinel)
        self.u.mem_write(sentinel+0xc,b'\x01\x01');self.f.write(at+0x324,sentinel);self.f.write(at+0x328,0)
    def spawn(self,sp):
        f,n,u=self.f,self.n,self.u
        kind,var,pos,vel,parent,subtype,seed=struct.unpack('<7I',u.mem_read(sp+4,28));at=self.next_actor;self.next_actor+=0x1000
        assert at<f.HEAP+0x400000
        u.mem_write(at,bytes(0x1000));self.refs(at);f.write(at,0xb459f0 if kind==1000 else 0xb49398)
        for off,value in [(0x20,(at-f.HEAP)//0x1000),(0x28,kind),(0x2c,var),(0x30,subtype),(0x320,parent),(0x344,seed)]:f.write(at+off,value)
        for off,value in [(0x2c0,1),(0x2c4,1),(0x2f4,1),(0x30c,1),(0xb88,1),(0x2d8,5),(0x2dc,5),(0x2c8,17)]:n.write_float(at+off,value)
        u.mem_write(at+0x294,bytes(u.mem_read(pos,8)));u.mem_write(at+0x2b8,bytes(u.mem_read(vel,8)))
        if kind!=1000:
            count=f.integer(f.ROOM+0x1264);f.write(f.HEAP+0x240000+count*4,at);f.write(f.ROOM+0x1264,count+1);f.write(f.ROOM+0x12c0,f.integer(f.ROOM+0x12c0)+1)
            if kind==13:n.write_float(at+0x2d8,3);n.write_float(at+0x2dc,3)
        self.births.append([self.frame,kind,var,subtype,seed,n.read_float(at+0x294),n.read_float(at+0x298),parent,at])
        return 32,at
    def audio(self,sp):self.sounds.append([self.frame,self.f.integer(sp+4)]);return 28,None
    def graphics(self,sp):self.effects+=1;return 4,None
    def color(self,sp):return 24,None
    def string(self,at,value):
        data=value.encode();assert len(data)<16;self.u.mem_write(at,data+b'\0'*(16-len(data)));self.f.write(at+0x10,len(data));self.f.write(at+0x14,15)
    def setup(self,seed=42,state=4,frame=0,total=1,owned=0,velocity=(0,0)):
        f,n,u=self.f,self.n,self.u;b=self.boss
        f.heap_cursor=f.HEAP;f.allocations.clear();u.mem_write(f.ROOM+0x1218,bytes(0x200))
        u.mem_write(b,bytes(0x1000));self.refs(b);f.write(b,0xb49398);f.write(b+0x20,77);f.write(b+0x28,67);f.write(b+0xab4,state);f.write(b+0x360,frame);f.write(b+0x180,4);f.write(b+0x344,seed)
        for off,value in [(0x294,320),(0x298,280),(0x2b8,velocity[0]),(0x2bc,velocity[1]),(0x2c0,1),(0x2c4,1),(0x2f4,1),(0x30c,1),(0x2c8,35),(0x2d4,30)]:n.write_float(b+off,value)
        for off,value in [(0x14,0),(0x18,0),(0x1c,640),(0x20,560)]:n.write_float(f.ROOM+off,value)
        cache=f.ROOM+0x4000
        for off in (0,4,8):f.write(cache+off,cache)
        u.mem_write(cache+0xc,b'\x01\x01');f.write(f.ROOM+0x1218+0xe0,cache)
        f.write(f.ROOM+4,f.ROOM+0x1000);f.write(f.ROOM+0x1010,f.ROOM+0x2000);f.write(f.ROOM+0x2048,1);f.write(f.ROOM+0x12c0,total);f.write(f.ROOM+0x12c4,0)
        # Supply the native cohort list by parent index; the original collection helper executes.
        cohort=f.HEAP+0x240000;storage=cohort+0x1000;f.write(f.ROOM+0x125c,cohort);f.write(f.ROOM+0x1264,owned)
        f.write(f.ROOM+0x128c,storage);f.write(f.ROOM+0x1290,128);f.write(f.ROOM+0x129c,storage+0x1000);f.write(f.ROOM+0x12a0,4096);f.write(f.ROOM+0x12a4,0)
        for i in range(owned):
            at=f.HEAP+0x250000+i*0x1000;f.write(cohort+i*4,at);u.mem_write(at,bytes(0x1000));self.refs(at);f.write(at,0xb49398);f.write(at+0x28,18);f.write(at+0xbcc,77);f.write(at+0x314,b)
            for off,value in [(0x294,320+10*(i+1)),(0x298,280),(0x2b8,2),(0x2bc,-1),(0x2c0,1),(0x2c4,1),(0x2f4,1)]:n.write_float(at+off,value)
            self.call(0x4bae70,b,(at+0x314,))
        # Original sprite metadata path, without artwork layers.
        animations=f.HEAP+0x200000;u.mem_write(animations,bytes(0x20000));sprite=b+0x3c;f.write(b+0x6c,sprite);f.write(sprite+0x74,animations);f.write(sprite+0x78,len(self.metadata['animations']));n.write_float(sprite+0x104,1)
        for i,a in enumerate(self.metadata['animations']):
            ptr=animations+i*0x13c;self.string(ptr,a['attributes']['Name']);f.write(ptr+0x30,int(a['attributes']['FrameNum']));u.mem_write(ptr+0x34,bytes([int(a['attributes']['Loop']=='true')]))
        self.frame=0;self.births=[];self.sounds=[];self.next_actor=f.HEAP+0x280000;self.effects=0
        u.reg_write(UC_X86_REG_ECX,seed);u.mem_write(self.sp,struct.pack('<I',n.STOP));u.reg_write(UC_X86_REG_ESP,self.sp);f.run(0x6c3d50)
    def step(self,physics=False):
        self.f.write(self.f.ROOM+0x12a4,0);self.frame+=1;self.f.write(self.f.GAME+0x1a30dc,self.frame);self.call(0x45dd40,self.boss)
        f,n,b=self.f,self.n,self.boss
        if physics:
            self.u.reg_write(UC_X86_REG_EDI,b);self.n.run(0x686406,0x686497)
        return [self.frame,f.integer(b+0xab4),f.integer(b+0x360),n.read_float(b+0x294),n.read_float(b+0x298),n.read_float(b+0x2b8),n.read_float(b+0x2bc),n.read_float(b+0x2c4),f.integer(0xbc5304),len(self.births),len(self.sounds)]
    def counts(self):
        f=self.f;count=f.integer(f.ROOM+0x1264);owned=0
        for i in range(count):
            at=f.integer(f.HEAP+0x240000+i*4)
            owned+=int(f.integer(at+0xbcc)==77)
        return f.integer(f.ROOM+0x12c0),owned
    def peek(self):
        state=bytes(self.u.mem_read(0xbffe10,624*4));index=self.f.integer(0xbc5304)
        self.call(0x6c3d90,0);word=self.u.reg_read(UC_X86_REG_EAX)
        self.u.mem_write(0xbffe10,state);self.f.write(0xbc5304,index);return word

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--probe',action='store_true');ap.add_argument('--check',action='store_true');args=ap.parse_args()
    raw=A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==A.M.SHA
    pe=pefile.PE(data=raw);m=NativeDuke(pe,raw)
    if args.probe:
        m.setup()
        for i in range(3):print(m.step(physics=True))
        return
    OUT.mkdir(parents=True,exist_ok=True)
    def save(name,data):
        p=OUT/name
        if args.check:assert p.read_bytes()==data,name
        else:p.write_bytes(data)
    def table(name,fields,rows):
        s=io.StringIO(newline='');w=csv.writer(s,lineterminator='\n');w.writerow(fields);w.writerows(rows);save(name,s.getvalue().encode())
    rows=[];births=[];sounds=[];releases=[];case=0
    def capture(physics,dead):
        f,n,b=m.f,m.n,m.boss;start=len(m.births);sound_start=len(m.sounds);total,owned=m.counts()
        inputs=[f.integer(b+0xab4),f.integer(b+0x360),total,owned,n.read_float(b+0x294),n.read_float(b+0x298),n.read_float(b+0x2b8),n.read_float(b+0x2bc),int(dead),int(physics)]
        cohort=[]
        if inputs[0]==8 and inputs[1]==17:
            for i in range(f.integer(f.ROOM+0x1264)):
                at=f.integer(f.HEAP+0x240000+i*4)
                if f.integer(at+0xbcc)==77:
                    cohort.append((at,[n.read_float(at+off) for off in (0x294,0x298,0x2b8,0x2bc,0x2c4,0x2f4)]))
        try:result=m.step(physics=physics)
        except Exception as error:raise RuntimeError(f'Duke case {case} inputs {inputs}') from error
        rows.append([case,f.integer(b+0x344),*inputs,*result[1:8],m.peek(),len(m.sounds)-sound_start])
        for at,values in cohort:
            releases.append([case,m.frame,*values,n.read_float(at+0x2b8),n.read_float(at+0x2bc),int(f.integer(at+0x314)==0),int(f.integer(at+0xbcc)==0xffffffff)])
        for event in m.sounds[sound_start:]:sounds.append([case,*event])
        for event in m.births[start:]:
            if event[1]==1000:continue
            at=event[8]
            births.append([case,m.frame,*event[1:7],int(event[7]==b),int(f.integer(at+0x314)==b),int(f.integer(at+0xbcc)==77),m.u.mem_read(at+0x16c,1)[0],n.read_float(at+0x2d8),n.read_float(at+0x2dc),n.read_float(at+0xb88)])
    contexts=[(1,0),(5,3),(9,0),(9,5),(12,8),(0,0)]
    for seed in (1,42,5489):
        for total,owned in contexts:
            for state,frame in [(0,0),(4,0),(4,39),(13,19),(13,20),(13,39),(14,17),(14,18),(14,39),(8,16),(8,17),(8,39)]:
                for velocity in [(0,0),(2,-.2),(-3,.1)]:
                    for dead in (False,True):
                        m.setup(seed,state,frame,total,owned,velocity);m.u.mem_write(m.boss+0x16b,bytes([dead]));capture(bool(case%2),dead);case+=1
    for seed in range(1,129):
        for total,owned in contexts:
            m.setup(seed,4,0,total,owned);capture(True,False);case+=1
    matrix_cases=case
    for seed in (1,42,5489):
        for owned in (0,5):
            m.setup(seed,0,0,1+owned,owned)
            for tick in range(180):capture(True,False)
            case+=1
    table('native-states.csv',['case','init_seed','before_state','before_frame','total','owned','before_x','before_z','before_vx','before_vz','dead','physics','after_state','after_frame','after_x','after_z','after_vx','after_vz','after_friction','next_mt_word','sound_requests'],rows)
    table('native-births.csv',['case','tick','type','variant','subtype','init_seed','x','z','spawner_is_boss','parent_is_boss','cohort','contact_expiry','hp','max_hp','visual_scale'],births)
    table('native-sounds.csv',['case','tick','sound_id'],sounds)
    table('native-releases.csv',['case','tick','x','z','before_vx','before_vz','friction','time_scale','after_vx','after_vz','parent_cleared','cohort_cleared'],releases)
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
    for name,start,end in [('controller',0x45dd40,0x45f5a8),('cohort',0x6a6f60,0x6a70a0),('npc_order',0x69b66e,0x69b6f7),('child_pursuit',0x4f68ef,0x4f6a3a),('child_edge',0x4f6d93,0x4f6e2e),('effect_dispatch',0x5be281,0x5be2b8),('tiny_fly_effect33',0x5d8968,0x5d93f2)]:
        blob=pe.get_data(start-pe.OPTIONAL_HEADER.ImageBase,end-start);save(name+'.asm',(''.join(f'{i.address:08x} {i.mnemonic} {i.op_str}\n' for i in md.disasm(blob,start))).encode());windows.append({'name':name,'start':hex(start),'end_exclusive':hex(end),'sha256':hashlib.sha256(blob).hexdigest()})
    xml=A.M.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3/entities2.xml'
    entities=ET.parse(xml).getroot()
    source_entity=next(e.attrib for e in entities.iter('entity') if e.get('id')=='67' and e.get('variant')=='0')
    tiny=next(e.attrib for e in entities.iter('entity') if e.get('id')=='1000' and e.get('variant')=='33')
    assert tiny['collisionDamage']=='0' and tiny['collisionMass']=='0' and tiny['collisionRadius']=='0'
    assert struct.unpack('<I',pe.get_data(0x5e9214+32*4-pe.OPTIONAL_HEADER.ImageBase,4))[0]==0x5d8968
    manifest={'source_entity':source_entity,'tiny_fly_effect33':tiny,'entity_xml_sha256':hashlib.sha256(xml.read_bytes()).hexdigest(),'executable_sha256' :A.M.SHA,'matrix_cases':matrix_cases,'sequence_cases':6,'states':len(rows),'npc_births':len(births),'cohort_release_intents':len(releases),'math':m.math.manifest(),'vcruntime_sha256':m.rtti_sha,'vcruntime_mapping':'0x11000000 with ordinary PE base relocation; __RTDynamicCast import resolved to original export','external_boundaries':{'Spawn422e20':'Records complete request and provides typed NPC/effect body with documented XML-like base fields and weak-reference tree; NPC list/counter registration is fixture world input, not full Spawn acceptance.','Audio888de0':'Records request, no audio device.','EffectUpdate':hex(m.effect_update),'Color68a380':'Graphics endpoint only; no color layers hosted.','timeGetTime':'WINMM.dll import0xa064c0; OS profiling clock returns0; no game clock replaced.'},'windows':windows,'scope':'Whole original ordinary67.0.0 AI function, original rectangle room clamp, original cohort collection/weak references and runtime type checks, original sprite animation selection, original MT and UCRT numeric exports. Optional bounded base-physics block runs after AI, matching the preserved normal NPC call order. Synthetic rectangular room, supplied ordinary cohort/room population, no items/status/mods; cosmetic query lists empty. Offspring AI/Spawn allocation, full NPC update/sprite advancement, real room geometry/flags/cosmetic population and global call order remain open.','full_acceptance':False}
    save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode());print(f'Captured {len(rows)} Duke AI states and {len(births)} NPC birth intents; full acceptance remains open.')
if __name__=='__main__':main()
