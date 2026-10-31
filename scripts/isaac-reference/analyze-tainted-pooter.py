#!/usr/bin/env python3
"""Preserve installed Tainted Pooter volley and backward impact-splitting evidence."""
import argparse, hashlib, json, struct
from pathlib import Path
import capstone, pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/tainted_pooter/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--check',action='store_true');args=parser.parse_args()
    raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==SHA
    pe=pefile.PE(data=raw);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    vtable={name:{'offset':hex(offset),'address':hex(expected)} for name,offset,expected in [
        ('Update',0x0c,0x62f6f0),('Kill',0x24,0x6848b0),('Remove',0x28,0x6848f0),('HandleCollision',0x58,0x6375e0)]}
    for name,v in vtable.items():assert struct.unpack('<I',read(0xb46790+int(v['offset'],16),4))[0]==int(v['address'],16)
    constants={}
    for name,address,expected in [('inner_forward',0xb6a60c,.99),('inner_side',0xb6a2f8,.139),('outer_forward',0xb6a5b0,.914),
        ('outer_side',0xb6a43c,.407),('outer_scale',0xb6a5a4,.9),('back_split_angle',0xb6a9e8,24),('sight_range',0xb6aba8,200)]:
        value=struct.unpack('<f',read(address,4))[0];assert abs(value-expected)<1e-6
        constants[name]={'address':hex(address),'value':value}
    assert struct.unpack('<I',read(0x6a33ec+4*4,4))[0]==0x6a2099
    data={'baseline':'Installed Repentance 1.7.9b','executable_sha256':SHA,'projectile_vtable':{'address':'0xb46790','type_descriptor':'0xbeabf4','entries':vtable},'constants':constants,
        'findings':[
            'Shared type14 attack excludes the Skatole-suppressed branch. Variant2 chooses delay63 rather than35, acquires through the shared seven-frame/sight helper, and aims again at Shoot.',
            'Variant2 ProjectileParams: Scale1.4, FallingSpeedModifier1, FallingAccelModifier-.15, Spread1.2, BulletFlags bit54 BACKSPLIT, internal byte+98=1. Aim is resized to7; FireProjectiles mode4. Stack pushes shift the apparent local offsets; constructor and application confirm fields.',
            'Mode4 dispatch6a33ec[4] points to6a2099. Inner velocity coefficients are forward.99 and side+/-.139*Spread. Outer coefficients are .914 and +/-.407*Spread, both multiplied by.9. The vectors are not normalized afterward. Final outer shot joins6a2023.',
            'Internal ProjectileParams byte+98 skips the default mode-specific falling/velocity adjustment. Parameter application adds falling modifiers and applies the scale. Exact native height curves are preserved as evidence but not ported in this slice.',
            'Projectile vtable b46790 resolves Update62f6f0 and collision6375e0. Update631c84 enters dead processing on byte16b; entity flag0x20 takes an early Remove path. Collision637945 also sets dead byte16b on player impact.',
            'BACKSPLIT branch63371e normalizes and negates original velocity, rotates by +/-24 degrees, scales child velocity to10, and adds that velocity to impact position as spawn offset. Both children are projectile type9 variant0; owner pointer and spawner type/variant are retained. Child falling acceleration is-.04. BACKSPLIT is cleared, preventing recursion. No scale override is applied to the children.',
            'The wiki describes wall/obstacle splitting; installed ordinary player collision also reaches the dead-processing branch. Local safety TTL and explicit cancellation do not count as physical impacts.',
            'Installed XML source HP75, contact0. The extracted DLC animation metadata is30FPS: Attack14 with Shoot6, Fly2loop, Appear25. Source Ascent placement remains dedicated, not ordinary floor pools.'
        ],'windows':[]}
    if not args.check:assert not (OUT/'manifest.json').exists();OUT.mkdir(parents=True,exist_ok=True)
    windows=[('pooter_attack',0x4f5b1e,0x4f5dc5),('projectile_params_defaults',0x430d70,0x430ef9),
        ('mode4_volley',0x6a2023,0x6a2360),('params_physics_and_damage',0x6a3059,0x6a31f2),
        ('projectile_init',0x62f1b0,0x62f340),('projectile_dead_gate',0x631c84,0x631cd5),
        ('back_split',0x63371e,0x633859),('player_collision_dead_flag',0x6375e0,0x637985),
        ('falling_acceleration_setter',0x436b90,0x436ba0),('vector_normalize',0x962560,0x962600),
        ('vector_negate',0x962b20,0x962b50),('vector_scale',0x962b50,0x962b80)]
    for name,start,end in windows:
        blob=read(start,end-start);text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(blob,start))+'\n'
        path=OUT/(name+'.asm')
        if args.check:assert path.read_text()==text
        else:path.write_text(text)
        data['windows'].append({'path':str(path.relative_to(ROOT)),'start':hex(start),'end':hex(end),
            'raw_sha256':hashlib.sha256(blob).hexdigest(),'sha256':hashlib.sha256(path.read_bytes()).hexdigest()})
    record=next(r for r in json.loads((ROOT/'docs/research/isaac-mechanics-reference.json').read_text())['records'] if r.get('key')=='14.2.0')
    data['xml']=record['xml'];data['room_library_presence']=record['room_library_presence']
    if args.check:assert json.loads((OUT/'manifest.json').read_text())==data
    else:(OUT/'manifest.json').write_text(json.dumps(data,indent=2)+'\n')
    print(json.dumps({'result':'pass','mode':'checked' if args.check else 'preserved','windows':len(windows),'constants':constants}))
if __name__=='__main__':main()
