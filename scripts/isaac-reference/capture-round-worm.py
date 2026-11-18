#!/usr/bin/env python3
"""Pin ordinary Round Worm arithmetic, phase gates, room and animation metadata.

Executes original bounded code. Supplied animation state/targets are not a live
NPC scheduler, native room collision, global RNG or complete actor acceptance.
"""
import argparse, csv, hashlib, importlib.util, io, json, struct, zlib
import xml.etree.ElementTree as ET
from pathlib import Path
import capstone, pefile
from unicorn.x86_const import *

def module(name, file):
    spec=importlib.util.spec_from_file_location(name,Path(__file__).with_name(file))
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m

M=module('motion','analyze-player-motion.py')
NM=module('math','native_math.py')
R=module('rooms','audit-live-floor.py')
H=module('archives','extract-hornfel-animations.py')
OUT=M.ROOT/'docs/reports/isaac-first-floor-parity/d14a3-round-worm/source'

def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
    raw=M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==M.SHA
    pe=pefile.PE(data=raw);read=lambda at,size:pe.get_data(at-0x400000,size)
    n=M.NativeMotion(pe);u=n.u;numeric=NM.NativeMath(n,pe);p=n.PLAYER;sp=n.STACK+0x6000
    def word(at,value):u.mem_write(at,struct.pack('<I',value&0xffffffff))
    def integer(at):return struct.unpack('<I',u.mem_read(at,4))[0]
    def setup():
        n.reset();u.mem_write(sp,bytes(0x1000))
        for reg,value in [(UC_X86_REG_EDI,p),(UC_X86_REG_ESI,p),(UC_X86_REG_ESP,sp),(UC_X86_REG_EBP,n.ebp)]:u.reg_write(reg,value)
        word(p+0x28,244);word(p+0xe6c,-1);n.write_float(p+0x2d8,10)
    def save(name,data):
        path=OUT/name
        if args.check:assert path.read_bytes()==data,name
        else:path.parent.mkdir(parents=True,exist_ok=True);path.write_bytes(data)
    def csvfile(name,header,rows):
        buf=io.StringIO();w=csv.writer(buf,lineterminator='\n');w.writerow(header);w.writerows(rows);save(name,buf.getvalue().encode())
    shots=[]
    for dx in (-300,-30,0,30,300):
        for dy in (-200,-10,0,10,200):
            if dx==dy==0:continue
            setup();n.write_float(sp+0x34,dx);n.write_float(sp+0x38,dy)
            n.run(0x52c95b,0x52c995)
            shots.append([dx,dy,n.read_float(sp+0x18),n.read_float(sp+0x1c)])
    csvfile('native-shots.csv',['dx','dy','vx','vy'],shots)
    prediction=[]
    for vx,vy in [(0,0),(1,0),(-4,3),(2,-2),(.3,.4)]:
        setup();n.write_float(p+0x2b8,vx);n.write_float(p+0x2bc,vy)
        n.run(0x52c41b,0x52c473)
        prediction.append([vx,vy,n.read_float(sp+0x24),n.read_float(sp+0x20)])
    csvfile('native-prediction.csv',['vx','vy','lead_x','lead_y'],prediction)
    relocation=[]
    for radius in (0,99,100,100.01,200,999.99,1000,1001):
        for draw in (0,1,2,3):
            setup();u.reg_write(UC_X86_REG_EAX,draw)
            n.xmm(UC_X86_REG_XMM1,radius*radius);n.xmm(UC_X86_REG_XMM2,123);n.xmm(UC_X86_REG_XMM3,234)
            n.run(0x52c000,0x52c03a)
            relocation.append([radius,draw,int(n.read_float(p+0x294)==123)])
    csvfile('native-relocation.csv',['radius','rng_word','accepted'],relocation)
    phases=[]
    for pending in (0,5,9.9,10,11):
        setup();word(p+0xab4,6);word(p+0x180,4);u.mem_write(p+0x169,b'\x01');n.write_float(p+0x14,pending)
        n.run(0x52bc6d,0x52cfb5)
        phases.append(['dig_in_finished',pending,0,integer(p+0xab4),integer(p+0x180),u.mem_read(p+0x169,1)[0]])
    for playing in (0,1):
        setup();word(p+0xab4,8);word(p+0x180,4);word(p+0x70,p+0x1000);u.mem_write(p+0x80,bytes([playing]));u.mem_write(p+0x169,b'\x01')
        n.run(0x52cf83,0x52cfb5)
        phases.append(['dig_out',0,playing,integer(p+0xab4),integer(p+0x180),u.mem_read(p+0x169,1)[0]])
    csvfile('native-phases.csv',['case','pending_damage','playing','state','collision','visible'],phases)
    rooms,stb=R.read_stb(R.SOURCE/'rooms/01.basement.stb')
    room=next(x for x in rooms if (x['type'],x['variant'],x['subtype'])==(1,505,0))
    save('room.json',(json.dumps(dict(source=stb,room=room),indent=2)+'\n').encode())
    xml=ET.parse(R.SOURCE/'entities2.xml').getroot()
    entity=next(x.attrib for x in xml if x.get('id')=='244' and x.get('variant','0')=='0')
    windows=[];md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    for name,a,b in [('controller',0x52b370,0x52d034),('dispatch',0x699d1f,0x699d2b)]:
        data=read(a,b-a);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(data,a))+'\n').encode())
        windows.append(dict(name=name,start=hex(a),end=hex(b),sha256=hashlib.sha256(data).hexdigest()))
    constants={hex(a):struct.unpack('<f',read(a,4))[0] for a in (0xb6a974,0xb6a940,0xb6abec,0xb6aa8c,0xb6ad38,0xb6ada0)}
    # Metadata only: no original sprite texture is imported.
    name='244.000_Round Worm.anm2'
    pinned=json.loads((M.ROOT/'reference/isaac-repentance-1.7.9b/manifests/source-manifest.json').read_text())
    for archive in ('repentance.a','afterbirthp.a','afterbirth.a','rebirth.a'):
        path=H.INSTALL/'resources/packed'/archive
        if not path.exists():continue
        wanted={H.namehash(prefix+name):prefix+name for prefix in ('resources-dlc3/gfx/','resources/gfx/')}
        with path.open('rb') as f:
            head=f.read(14);index,count=struct.unpack_from('<IH',head,8);f.seek(index)
            entries=[struct.unpack('<5I',f.read(20)) for _ in range(count)];matches=[e for e in entries if e[:2] in wanted]
            if not matches:continue
            f.seek(0);digest=hashlib.sha256(f.read()).hexdigest()
            assert digest==next(x['sha256'] for x in pinned if x['path']=='resources/packed/'+archive)
            a,b,pos,length,crc=matches[0];f.seek(pos);data=bytearray()
            while True:
                flag,=struct.unpack('<I',f.read(4));data.extend(zlib.decompressobj(-15).decompress(f.read(flag&0x7fffffff)))
                if flag>>31:break
            assert len(data)==length and H.checksum(data)==crc
            save(name,bytes(data));xml=ET.fromstring(data)
            animation=dict(archive=archive,archive_sha256=digest,source=wanted[(a,b)],sha256=hashlib.sha256(data).hexdigest(),events=[x.attrib for x in xml.findall('./Content/Events/Event')],animations=[dict(attributes=x.attrib,triggers=[t.attrib for t in x.findall('./Triggers/Trigger')]) for x in xml.findall('./Animations/Animation')])
            save('animation-manifest.json',(json.dumps(animation,indent=2)+'\n').encode());break
    else:raise RuntimeError('Round Worm animation missing')
    save('manifest.json',(json.dumps(dict(executable_sha256=M.SHA,entity=entity,constants=constants,windows=windows,numeric=numeric.manifest(),native_cases=len(shots)+len(prediction)+len(relocation)+len(phases),scope='Ordinary 244.0.0 only. Original shot normalization/speed, ten-native-player-step lead, relocation range/parity and supplied animation-end transitions. DW physical placement, random stream, animation scheduler and whole actor remain explicit acceptance gaps.',full_native_acceptance=False),indent=2)+'\n').encode())
    print('PASS',len(shots)+len(prediction)+len(relocation)+len(phases),'native cases; source505 and Round Worm animation metadata')
if __name__=='__main__':main()
