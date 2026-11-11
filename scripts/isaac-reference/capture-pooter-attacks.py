#!/usr/bin/env python3
"""Bounded unmodified Repentance Pooter shot, interval, cooldown and flight execution.

Animation cadence, target eligibility, actor initialization and collision masks
are supplied boundaries. This is not a whole NPC-wrapper or RNG replay.
"""
import argparse,csv,hashlib,importlib.util,io,json,struct
from pathlib import Path
import capstone,pefile
from unicorn.x86_const import *
spec=importlib.util.spec_from_file_location('motion',Path(__file__).with_name('analyze-player-motion.py'))
M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)
OUT=M.ROOT/'docs/reports/isaac-first-floor-parity/d06-pooter-shots'
def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--check',action='store_true');args=parser.parse_args()
    raw=M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==M.SHA;pe=pefile.PE(data=raw)
    def word(n,a,v):n.u.mem_write(a,struct.pack('<I',v&0xffffffff))
    def setup(n):
        for reg,v in [(UC_X86_REG_EDI,n.PLAYER),(UC_X86_REG_ESI,n.PLAYER),(UC_X86_REG_EBP,n.ebp),(UC_X86_REG_ESP,n.STACK+0x6000)]:n.u.reg_write(reg,v)
    def save(name,b):
        path=OUT/name
        if args.check:assert path.read_bytes()==b,name
        else:path.write_bytes(b)
    def csvfile(name,header,rows):
        stream=io.StringIO(newline='');w=csv.writer(stream,lineterminator='\n');w.writerow(header);w.writerows(rows);save(name,stream.getvalue().encode())
    OUT.mkdir(parents=True,exist_ok=True)
    rows=[]
    for dx,dy in [(1,0),(0,1),(3,4),(-4,3)]:
        n=M.NativeMotion(pe);setup(n);sp=n.STACK+0x6000;p=n.PLAYER
        n.write_float(sp+0x34,dx);n.write_float(sp+0x38,dy)
        n.run(0x4f5cfe,0x4f5d15)
        vx=n.read_float(sp+0x34);vy=n.read_float(sp+0x38)
        rows.append([dx,dy,vx,vy])
    csvfile('native-shot-velocity.csv',['target_dx','target_dy','vx','vy'],rows)
    n=M.NativeMotion(pe);setup(n);p=n.PLAYER
    n.run(0x62f1ef,0x62f1f9)
    array=p+0x9000;word(n,array,p);word(n,n.ebp-0x4c,array)
    n.u.reg_write(UC_X86_REG_ESI,0);n.u.reg_write(UC_X86_REG_EDX,1)
    n.run(0x6a3090,0x6a30b2)
    initial=[n.read_float(p+off) for off in (0x360,0x364,0x368)]
    assert initial[0]==-23 and initial[1]==-3 and abs(initial[2]-.1)<1e-6
    for off,v in [(0x294,320),(0x298,280),(0x2b8,7),(0x2c0,1),(0x2c4,1),(0x2f4,1)]:n.write_float(p+off,v)
    flight=[]
    for k in range(1,100):
        setup(n);n.run(0x636567,0x6365d5)
        setup(n);n.run(0x686406,0x686497)
        setup(n);n.run(0x636de5,0x636e0f)
        dead=n.u.mem_read(p+0x16b,1)[0]
        flight.append([k,n.read_float(p+0x294),n.read_float(p+0x360),n.read_float(p+0x364),dead])
        if dead:break
    assert flight[-1][-1]==1
    csvfile('native-flight.csv',['update','x','height','falling_speed','dead'],flight)
    cooldown=[]
    for old in range(36):
        n=M.NativeMotion(pe);setup(n);p=n.PLAYER;word(n,p+0xaf0,old)
        for off,v in [(0x2c4,1),(0xb00,.2),(0xb04,.1),(0x2fc,2),(0x2f8,1)]:n.write_float(p+off,v)
        n.run(0x4f5d59,0x4f5dc5)
        cooldown.append([old,struct.unpack('<i',n.u.mem_read(p+0xaf0,4))[0],n.read_float(p+0x2c4),n.read_float(p+0xb00)])
    csvfile('native-cooldown.csv',['old','remaining','friction','wander_x'],cooldown)
    n=M.NativeMotion(pe);setup(n);word(n,n.PLAYER+0x2c,0);n.run(0x4f5b57,0x4f5b78)
    assert struct.unpack('<I',n.u.mem_read(n.PLAYER+0xaf0,4))[0]==35
    gates=[]
    for entity in range(7):
        n=M.NativeMotion(pe);setup(n);game=n.PLAYER+0x9000;n.u.reg_write(UC_X86_REG_ESI,game)
        # Global frame is at +0x1a30dc; use separately mapped game storage.
        game=0x4000000;n.u.mem_map(game,0x200000);n.u.reg_write(UC_X86_REG_ESI,game)
        word(n,n.ebp+8,7);word(n,n.ebp+12,entity)
        for frame in range(1,71):
            word(n,game+0x1a30dc,frame);n.run(0x6847b9,0x6847cb)
            gates.append([entity,frame,n.u.reg_read(UC_X86_REG_EAX)&255])
    csvfile('native-interval.csv',['entity','frame','due'],gates)
    animation=M.ROOT/'docs/reports/isaac-enemy-port/fly_pooter/animations/manifest.json'
    meta=json.loads(animation.read_text());attack=next(a for a in meta['files'][0]['animations'] if a['attributes']['Name']=='Attack')
    assert attack['attributes']['FrameNum']=='14' and attack['triggers'][0]['AtFrame']=='6'
    windows=[];md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    for name,start,end in [('shot_speed',0x4f5cfe,0x4f5d15),('cooldown',0x4f5d59,0x4f5dc5),('flight',0x636567,0x6365d5),('landing',0x636de5,0x636e0f),('mode0',0x6a3090,0x6a30b2),('interval',0x6847b9,0x6847cb)]:
        blob=pe.get_data(start-0x400000,end-start);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,start))+'\n').encode());windows.append(dict(name=name,sha256=hashlib.sha256(blob).hexdigest()))
    manifest=dict(exe_sha256=M.SHA,initial_height=initial[0],initial_falling_speed=initial[1],falling_acceleration=initial[2],flight_updates=len(flight),shot_vectors=len(rows),cooldown_cases=len(cooldown),interval_cases=len(gates),attack_frames=14,shoot_frame=6,cooldown_frames=35,animation_metadata_sha256=hashlib.sha256(animation.read_bytes()).hexdigest(),windows=windows,supplied_boundaries=['resolved target delta; Normal difficulty branch selected','initialized projectile, unit friction/time; no collision flags','ordinary one-update cooldown age advance','global frame and entity index; interval helper eligibility preconditions supplied','animation cadence from preserved ANM2 metadata; full NPC animation scheduler not executed'],full_native_acceptance=False)
    save('native-manifest.json',(json.dumps(manifest,indent=2)+'\n').encode());print(json.dumps(dict(passed=True,check=args.check,flight_updates=len(flight),interval_cases=len(gates),cooldown_cases=len(cooldown))))
if __name__=='__main__':main()
