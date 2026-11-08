#!/usr/bin/env python3
"""Execute bounded 1.7.9b blue-fly arithmetic, not complete familiar AI."""
import argparse,csv,hashlib,importlib.util,io,json,struct
from pathlib import Path
import capstone,pefile
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EBP,UC_X86_REG_EBX,UC_X86_REG_ECX,UC_X86_REG_EDI,UC_X86_REG_ESI,UC_X86_REG_ESP,UC_X86_REG_EIP,UC_X86_REG_XMM0,UC_X86_REG_XMM1,UC_X86_REG_XMM2,UC_X86_REG_XMM3

SPEC=importlib.util.spec_from_file_location('health',Path(__file__).with_name('analyze-player-health.py'))
H=importlib.util.module_from_spec(SPEC);SPEC.loader.exec_module(H)
OUT=H.MOTION.ROOT/'docs/reports/isaac-first-floor-parity/blue-fly'
XML=H.MOTION.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3/entities2.xml'


def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--check',action='store_true');args=p.parse_args()
    raw=H.MOTION.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==H.MOTION.SHA
    pe=pefile.PE(data=raw);h=H.NativeHealth(pe);n=h.native;u=h.u;fly=0x7000000
    u.mem_map(fly,0x10000);OUT.mkdir(parents=True,exist_ok=True)
    sp=n.STACK+0x9000;b=n.ebp
    def reg(r,v):u.reg_write(r,v)
    def f(offset,value):n.write_float(fly+offset,value)
    def r(offset):return n.read_float(fly+offset)
    def save(name,data):
        path=OUT/name
        if args.check:assert path.read_bytes()==data,name
        else:path.write_bytes(data)
    def table(name,header,rows):
        stream=io.StringIO(newline='');writer=csv.writer(stream,lineterminator='\n');writer.writerow(header);writer.writerows(rows);save(name,stream.getvalue().encode())
    rows=[]
    plans=[('straight',[(150,0)]*90),('corner',[(150,0)]*40+[(0,150)]*40),
           ('reverse',[(150,0)]*35+[(-150,0)]*35),('diagonal',[(100,100)]*70),
           ('zero',[(0,0)]*4),('threshold',[(.099,0),(.1,0),(-.1,0),(0,0)])]
    for name,goals in plans:
        u.mem_write(fly,bytes(0x10000));f(0x2f4,1);f(0x2c0,1)
        for step,(gx,gz) in enumerate(goals):
            before=[r(o) for o in [0x294,0x298,0x2b8,0x2bc]]
            f(0x28c,gx);f(0x290,gz);f(0x2c4,1)
            reg(UC_X86_REG_ESI,fly);reg(UC_X86_REG_ESP,sp)
            h.run(0x5f7539,0x5f75ed)
            reg(UC_X86_REG_EDI,fly)
            h.run(0x686406,0x686497)
            after=[r(o) for o in [0x294,0x298,0x2b8,0x2bc]]
            rows.append([name,step,*before,gx,gz,*after])
    table('native-motion.csv',['case','step','x','z','vx','vz','goal_x','goal_z','next_x','next_z','next_vx','next_vz'],rows)
    angles=[]
    for phase in [0,1.2,-6.1]:
        for frame in [0,1,5,30,180,300]:
            for parity in [0,1]:
                f(0xcb0,phase);f(0xcbc,.045);h.write(h.GAME+0x1a30dc,frame);h.write(h.MANAGER+0x4a264,parity)
                reg(UC_X86_REG_EBX,fly);reg(UC_X86_REG_ECX,h.GAME);reg(UC_X86_REG_ESP,sp)
                h.run(0x5f50aa,0x5f510b)
                value=struct.unpack('<f',struct.pack('<I',u.reg_read(UC_X86_REG_XMM0)&0xffffffff))[0]
                angles.append([phase,frame,parity,value])
    table('native-orbit-angle.csv',['phase','global_frame','parity','native_fmod_input'],angles)
    scores=[]
    for distance in [0,100,200,250]:
        for owner in [0,100,200,450]:
            for hp in [1,20,400,800]:
                f(0x2d8,hp);u.mem_write(sp,bytes(0x100));h.write(sp+0x14,0)
                n.write_float(sp+0x30,owner);u.mem_write(sp+0x2c,b'\x01');u.mem_write(sp+0x4c,b'\x01');h.write(b+0x10,0)
                reg(UC_X86_REG_EDI,fly);reg(UC_X86_REG_ESP,sp);reg(UC_X86_REG_EBP,b)
                n.xmm(UC_X86_REG_XMM0,distance);n.xmm(UC_X86_REG_XMM1,0);n.xmm(UC_X86_REG_XMM3,0)
                h.run(0x5f6d7a,0x5f6de0)
                value=struct.unpack('<f',struct.pack('<I',u.reg_read(UC_X86_REG_XMM2)&0xffffffff))[0]
                scores.append([distance,owner,hp,value])
    table('native-target-score.csv',['fly_distance','owner_distance','hp','native_score'],scores)
    damage=[]
    for value in [.1,3.5,5.25,12,40]:
        h.write(fly+0x360,h.player);n.write_float(h.player+0x14c0,value)
        reg(UC_X86_REG_EDI,fly);reg(UC_X86_REG_EBP,b)
        h.run(0x5f0cfd,0x5f0d1e);damage.append([value,r(0x2e0)])
    table('native-damage.csv',['player_damage','initialized_fly_damage'],damage)
    kills=[]
    def kill_boundary(uc,address,size,data):
        if address==0x6089ea:uc.emu_stop()  # Before native NPC Kill/world effects.
    u.hook_add(UC_HOOK_CODE,kill_boundary)
    for kind in [10,13,14,18,25,80,222,256,281,296,868]:
        for variant in [0,2]:
            h.write(fly+0x28,kind);h.write(fly+0x2c,variant);reg(UC_X86_REG_ESI,fly)
            u.emu_start(0x6089cf,0x608b00,count=200)
            at=u.reg_read(UC_X86_REG_EIP);assert at in [0x6089ea,0x608b00]
            kills.append([kind,variant,int(at==0x6089ea)])
    table('native-instakill.csv',['type','variant','native_direct_kill_branch'],kills)
    import xml.etree.ElementTree as ET
    entity=next(x.attrib for x in ET.parse(XML).getroot() if x.get('id')=='3' and x.get('variant')=='43')
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
    for name,start,end in [('ordinary_ai',0x5f7340,0x5f75f3),('motion',0x5f7539,0x5f75ed),
                           ('physics',0x686406,0x686497),('orbit_angle',0x5f50aa,0x5f510b),
                           ('orbit_position',0x5f521e,0x5f5274),('target_score',0x5f6d7a,0x5f6de0),
                           ('target_filters',0x5f6b47,0x5f6e50),('initial_damage',0x5f0ced,0x5f0d1e),
                           ('contact_damage',0x608b14,0x608b94),('special_kill_branch',0x6089cf,0x608b00),
                           ('npc_kill',0x695560,0x6955f5),('lua_kill_remove_binding',0x8604fd,0x860516),
                           ('ordinary_consumption',0x6089f1,0x608a40)]:
        blob=pe.get_data(start-pe.OPTIONAL_HEADER.ImageBase,end-start)
        listing=''.join(f'{i.address:08x} {i.mnemonic} {i.op_str}\n' for i in md.disasm(blob,start)).encode();save(name+'.asm',listing)
        windows.append({'name':name,'start':hex(start),'end_exclusive':hex(end),'raw_sha256':hashlib.sha256(blob).hexdigest(),'listing_sha256':hashlib.sha256(listing).hexdigest()})
    manifest={'version':'Repentance 1.7.9b','exe_sha256':H.MOTION.SHA,'native_motion_states':len(rows),'native_motion_cases':len(plans),'native_orbit_angles':len(angles),'native_target_scores':len(scores),'native_damage_cases':len(damage),'native_special_kill_branches':len(kills),
              'method':'Bounded original x86/SSE with native sqrt and native ordinary physics. Numeric helpers execute unmodified. Special-kill branch fixture stops before NPC Kill/world effects.',
              'scope':'Steering with supplied goals, timeScale1/base friction1, native free-motion endpoint; orbit angle before external fmod/cos/sin; target score with supplied distances/HP/ordinary flags; spawn damage before item modifiers.',
              'xml_sha256':hashlib.sha256(XML.read_bytes()).hexdigest(),'source_entity':entity,
              'static_findings':['Blue-fly Update dispatch calls0x5f7340. Ordinary target radius200, RNG modulo3 poll then IsFrame(13,InitSeed), target flags13.',
                                 'No-target orbit group1 uses radii35/30, ordinary angular rate.045, group angle offset.5; target acquisition removes the fly from that orbit group.',
                                 'Ordinary entity contact queues stored collision damage and removes the fly; special NPC kills, subtype behavior and item modifiers exist separately.',
                                 'Collision radius13 and friction1 are XML attributes. Init variant43 takes grid collision class0; XML alone does not prove AI.'],
              'not_executed':['world target enumeration/filtering','orbit membership initialization and imported trigonometry','whole blue-fly update ordering/physics/collision','spawn/removal and room callbacks','global RNG','item/cache-refresh modifiers','live timing or full acceptance'],'windows':windows}
    save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode())
    print(f'Captured/checked native blue-fly kernels: {len(rows)} motion, {len(angles)} angle, {len(scores)} score, {len(damage)} damage cases; full acceptance remains open.')


if __name__=='__main__':main()
