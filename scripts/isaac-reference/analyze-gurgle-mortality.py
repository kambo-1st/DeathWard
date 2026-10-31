#!/usr/bin/env python3
"""Preserve/verify bounded installed1.7.9b Gurgle-family mortality evidence."""
import argparse, hashlib, json, re, struct
from pathlib import Path
import capstone, pefile

ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/gurgle_mortality/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
BASELINE='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
DECL=ROOT/'reference/isaac-mechanics-study/code/TeamREPENTOGON__REPENTOGON/348e5d0ea277760fc87af420d88e2c7909c9167e/libzhl/functions'

def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--check',action='store_true');args=p.parse_args()
    data=EXE.read_bytes();assert hashlib.sha256(data).hexdigest()==BASELINE
    pe=pefile.PE(data=data);base=pe.OPTIONAL_HEADER.ImageBase
    read=lambda a,n:pe.get_data(a-base,n)
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    u32=lambda a:struct.unpack('<I',read(a,4))[0]
    f32=lambda a:struct.unpack('<f',read(a,4))[0]
    signatures=[]
    for filename,method,address in [('EntityRef.zhl','EntityRef::constructor',0x4229a0),('EntityNPC.zhl','Entity_NPC::Morph',0x697c60)]:
        sig=re.search(r'"([0-9a-f?]+)":\s*[^;\n]*'+re.escape(method)+r'\(', (DECL/filename).read_text())[1]
        pattern=b''.join(b'.' if x=='??' else re.escape(bytes.fromhex(x)) for x in re.findall('..',sig))
        matches=list(re.finditer(pattern,data,re.S))
        assert len(matches)==1 and base+pe.get_rva_from_offset(matches[0].start())==address
        signatures.append({'declaration':str((DECL/filename).relative_to(ROOT)),'method':method,'signature':sig,'address':hex(address)})
    for kind,target in [(87,0x508ef0),(238,0x4f8e40)]:
        case=u32(0x69a7f8+4*read(0x69abc0+kind-10,1)[0]);ins=list(md.disasm(read(case,12),case))
        assert (ins[1].mnemonic,ins[1].op_str)==('call',hex(target))
    assert f32(0xb6aef8)==-25
    assert read(0x50902e,3)==bytes.fromhex('83fa0f') # rng%100 <15
    assert read(0x509037,4)==bytes.fromhex('837f2c00') # variant0 only
    assert read(0x509047,5)==bytes.fromhex('68ee000000') # target238
    assert read(0x5090ae,3)==bytes.fromhex('83e106') and read(0x4f8fce,3)==bytes.fromhex('83e104')
    bindings=[]
    for name,string,registration,function in [
        ('FireBossProjectiles',0xb53500,0x8076a6,0x6a3420),
        ('FindGridPath',0xb511d0,0x8044c2,0x7a3650),
        ('EvadeTarget',0xb511c4,0x8044a4,0x7a4830)]:
        raw=b'\x68'+struct.pack('<I',function)+b'\x68'+struct.pack('<I',string)
        assert read(string,len(name)+1)==name.encode()+b'\0' and read(registration,10)==raw and data.count(raw)==1
        bindings.append({'name':name,'registration':hex(registration),'function':hex(function),'bytes':raw.hex()})
    # Independent installed RTTI locates projectile virtual methods. Later-source
    # constructor/update signatures DO NOT match this build and are not evidence.
    rtti=b'.?AVEntity_Projectile@IsaacRepentance@@\0'
    assert read(0xbeabfc,len(rtti))==rtti
    locator=u32(0xb4678c);assert u32(locator+12)==0xbeabf4
    assert u32(0xb46794)==0x62f1b0 and u32(0xb4679c)==0x62f6f0
    windows=[('gurgle_mortality',0x509002,0x5090ee),('splasher_immunity',0x4f8f99,0x4f9008),
             ('entity_ref',0x4229a0,0x422abb),('gurgle_acquisition',0x509479,0x509581),
             ('gurgle_shot',0x5096c5,0x509725),('gurgle_ballistic_modifiers',0x50987f,0x5098ee),
             ('splasher_shot',0x4f9194,0x4f9408),('projectile_defaults',0x62f1ef,0x62f2d0),
             ('ordinary_shot_defaults',0x6a3059,0x6a30c2),('ordinary_shot_modifiers',0x6a3170,0x6a31c1),
             ('boss_shot_trajectory',0x6a3466,0x6a3494),('boss_shot_velocity',0x6a35e8,0x6a3655),
             ('boss_shot_falling',0x6a36b7,0x6a3718),('explosive_projectile_blast',0x631ca4,0x631d44)]
    result={'baseline':'Repentance1.7.9b','executable_sha256':BASELINE,'scope':'Ordinary Gurgle87.0, Crackle87.1 and Splasher238.0 damage/death slice, plus bounded attack preflight. No runtime attack/placement approval.',
      'signatures':signatures,'named_bindings':bindings,
      'projectile_rtti':{'descriptor':'0xbeabf4','locator':hex(locator),'vtable':'0xb46790','init':'0x62f1b0','update':'0x62f6f0'},
      'findings':['Gurgle: dead flag, residualHP strictly>-25, rng%100<15, variant0; Morph238.0.0/champion-1, clearDead and restore maxHP;20..39update delay.',
        'Damage entry source starts+0x10: EntityRef Type/SpawnerType/Flags at+0/+8/+0x20. EntityRef constructor independently verifies NPC fields and maps FLAG_FRIENDLY0x20000000 to bit2.',
        'Gurgle/Crackle filter FIRE|EXPLOSION; Splasher EXPLOSION only. Exempt source friendly, direct type1, spawner1/3, and DAMAGE_TNT0x1000. These are not blanket player bomb immunities.',
        'Source projectile EXPLODE bit2 invokes named BombDamage with50damage,60radius,lineCheck=true and producer pointer if available.',
        'Projectile default height-23. FireProjectiles mode0 overrides falling speed-3,accel.1; Splasher adds-5/.3 =>-8/.4 before common flight update. Gurgle uses FireBossProjectiles count1/trajectory10 then velocity*.55,accel-.6,speed*.7-3. Common flight integration remains unresolved.'],
      'windows':[]}
    if not args.check:assert not (OUT/'manifest.json').exists();OUT.mkdir(parents=True,exist_ok=True)
    for name,start,end in windows:
        raw=read(start,end-start);text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(raw,start))+'\n';path=OUT/(name+'.asm')
        if args.check:assert path.read_text()==text
        else:path.write_text(text)
        result['windows'].append({'path':str(path.relative_to(ROOT)),'start':hex(start),'end':hex(end),'raw_sha256':hashlib.sha256(raw).hexdigest(),'sha256':hashlib.sha256(path.read_bytes()).hexdigest()})
    if args.check:assert json.loads((OUT/'manifest.json').read_text())==result
    else:(OUT/'manifest.json').write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps({'result':'pass','mode':'check' if args.check else 'preserved','windows':len(windows),'scope':'mortality; attack preflight only'}))
if __name__=='__main__':main()
