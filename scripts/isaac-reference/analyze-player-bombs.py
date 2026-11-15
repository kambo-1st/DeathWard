#!/usr/bin/env python3
"""Execute bounded installed 1.7.9b inventory-bomb calculations.

This is not a whole-actor or live-clock capture. No calculation is hosted.
"""
import argparse,csv,hashlib,importlib.util,io,json,struct,xml.etree.ElementTree as ET
from pathlib import Path
import capstone,pefile
from unicorn.x86_const import *

spec=importlib.util.spec_from_file_location('awards',Path(__file__).with_name('analyze-room-awards.py'))
A=importlib.util.module_from_spec(spec);spec.loader.exec_module(A)
OUT=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d10a-dynamite/source'

def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--check',action='store_true');args=ap.parse_args()
    raw=A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==A.M.SHA
    pe=pefile.PE(data=raw);f=A.NativeAwards(pe,raw);n=f.n;u=f.u;p=n.PLAYER;b=n.ebp;sp=b-0x1000
    OUT.mkdir(parents=True,exist_ok=True)
    def save(name,data):
        path=OUT/name
        if args.check:assert path.read_bytes()==data,name
        else:path.write_bytes(data)
    def table(name,fields,rows):
        buf=io.StringIO(newline='');w=csv.writer(buf,lineterminator='\n');w.writerow(fields);w.writerows(rows);save(name,buf.getvalue().encode())
    def reset():
        u.mem_write(p,bytes(0x1000));u.mem_write(sp,bytes(0x1100))
        for reg,value in ((UC_X86_REG_EDI,p),(UC_X86_REG_EBP,b),(UC_X86_REG_ESP,sp)):u.reg_write(reg,value)
    initialization=[]
    for variant in (0,3,4,8,18,15,17,20):
        for seed in (1,42,1234567,0x7fffffff,0x80000000,0xffffffff):
            reset();u.reg_write(UC_X86_REG_ECX,p)
            for offset,value in ((8,4),(12,variant),(16,0),(20,seed)):f.write(b+offset,value)
            n.run(0x6819e6,0x681a26)
            n.run(0x67abbd,0x67ad37)
            initialization.append([variant,seed,f.integer(p+0x360),n.read_float(p+0x368),n.read_float(p+0x39c),f.integer(p+0x334),f.integer(p+0x338),f.integer(p+0x33c),f.integer(p+0x340)])
    table('native-initialization.csv',['variant','seed','countdown','damage','radius_multiplier','rng_after','shift_a','shift_b','shift_c'],initialization)
    fuse=[]
    for countdown in range(-2,80):
        reset();f.write(p+0x360,countdown);f.write(p+0x2c,0)
        # Both branch destinations stop before flags, items, or world effects.
        u.emu_start(0x67caf0,0x67cb58,count=1000) if countdown>0 else n.run(0x67caf0,0x67cca9)
        assert u.reg_read(UC_X86_REG_EIP)==(0x67cb58 if countdown>0 else 0x67cca9)
        after=f.integer(p+0x360);after=after if after<0x80000000 else after-0x100000000
        fuse.append([countdown,after,int(countdown<=0)])
    table('native-countdown.csv',['before','after','entered_explosion'],fuse)
    inherited=[]
    for vx,vz in ((0,0),(1,-2),(-4,3),(.001,0),(12,-16),(50,50)):
        reset();n.write_float(p+0x2b8,vx);n.write_float(p+0x2bc,vz)
        n.run(0x74a213,0x74a252)
        inherited.append([vx,vz,n.read_float(sp+0x20),n.read_float(sp+0x24)])
    table('native-inheritance.csv',['player_x','player_z','bomb_x','bomb_z'],inherited)
    motion=[]
    for row in inherited:
        reset()
        for offset,value in ((0x294,0),(0x298,0),(0x2b8,row[2]),(0x2bc,row[3]),(0x2c0,1),(0x2c4,1),(0x2f4,1)):n.write_float(p+offset,value)
        for tick in range(1,13):
            n.run(0x686406,0x686497)
            motion.append([row[0],row[1],tick,n.read_float(p+0x294),n.read_float(p+0x298),n.read_float(p+0x2b8),n.read_float(p+0x2bc)])
    table('native-free-motion.csv',['player_x','player_z','tick','position_x','position_z','velocity_x','velocity_z'],motion)
    reset();u.reg_write(UC_X86_REG_EAX,0);u.reg_write(UC_X86_REG_ESI,1)
    n.run(0x74a14a,0x74a166);cooldown=f.integer(p+0x1544);assert cooldown==30
    radii=[]
    for damage in (0,20,84.999,85,100,139.999,140,140.001,174.999,175,185,300):
        reset();n.write_float(b+0xc,damage);u.reg_write(UC_X86_REG_ECX,f.GAME)
        n.run(0x6d26fa,0x6d2752)
        stack=u.reg_read(UC_X86_REG_ESP);radii.append([n.read_float(b+0xc),n.read_float(stack+0x14)])
    table('native-base-radius.csv',['damage','radius'],radii)
    incoming=[]
    for damage in (0,20,84.999,85,100,185,300):
        for flags in (4,0x40000004,0x10000004):
            reset();u.reg_write(UC_X86_REG_EBX,sp+0x200);n.write_float(sp+0x20c,damage);f.write(sp+0x22c,flags)
            # Caller only admits positive blast damage before this block.
            n.xmm(UC_X86_REG_XMM0,damage);n.run(0x6d2075,0x6d20aa)
            amount=struct.unpack('<f',struct.pack('<I',u.reg_read(UC_X86_REG_XMM0)&0xffffffff))[0]
            incoming.append([damage,flags,amount])
    table('native-player-amount.csv',['blast_damage','damage_flags','half_hearts'],incoming)
    windows=[];md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    for name,start,end in [('entity_seed_initialization',0x6819e6,0x681a26),('initialization',0x67abbd,0x67ad37),('countdown',0x67caf0,0x67cb58),('inventory_placement',0x74a12f,0x74a7cd),('explosion_call',0x67cca9,0x67cda0),('explosion_radius',0x6d26e0,0x6d2752),('radius_application',0x6d28bb,0x6d294e),('incoming_player_amount',0x6d205b,0x6d20c4),('base_physics',0x686406,0x686497)]:
        blob=pe.get_data(start-pe.OPTIONAL_HEADER.ImageBase,end-start)
        save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(blob,start))+'\n').encode())
        windows.append({'name':name,'start':hex(start),'end_exclusive':hex(end),'sha256':hashlib.sha256(blob).hexdigest()})
    xml=A.M.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3/entities2.xml'
    entity=next(e.attrib for e in ET.parse(xml).getroot().iter('entity') if e.get('id')=='4' and e.get('variant')=='0')
    assert entity['friction']=='1' and entity['collisionRadius']=='16' and entity['collisionMass']=='6'
    manifest={'executable_sha256':A.M.SHA,'initialization_cases':len(initialization),'countdown_cases':len(fuse),'inheritance_cases':len(inherited),'free_motion_states':len(motion),'radius_cases':len(radii),'incoming_player_cases':len(incoming),'ordinary_placement_cooldown':cooldown,'entity_xml_sha256':hashlib.sha256(xml.read_bytes()).hexdigest(),'ordinary_entity':entity,'windows':windows,'scope':'Original bounded calculations; supplied variant, nonzero InitSeed, velocity, damage and flags. Actual Entity::Init copies InitSeed and initializes shifts4/3/17 before bomb initialization. No game calculation hooks, patched instructions or substituted RNG/math. Initialization excludes other constructor/configuration/visual setup. Free motion executes base physics with friction1/timeScale1 after inherited velocity. Countdown excludes modifiers/freeze/remote detonation. Radius captures the base threshold before flag/radius multipliers; incoming amount excludes recipient eligibility, earlier flags and TakeDamage. Inventory placement disassembly distinguishes ordinary bombs from FireBomb weapon API. Native scheduler, collision impulses/grid, global spawn seed selection, item/character modifiers and full actor acceptance remain open.','full_acceptance':False}
    save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode())
    print(f'Captured {len(initialization)} initializations, {len(fuse)} countdown cases, {len(inherited)} inherited velocities, {len(radii)} radii and {len(incoming)} incoming amounts; actor acceptance remains open.')

if __name__=='__main__':main()
