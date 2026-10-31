#!/usr/bin/env python3
"""Preserve bounded installed Horf evidence and ordinary-Fly implementation preflight."""
import argparse,hashlib,json,struct
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/horf_fly/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
BASELINE='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--check',action='store_true');args=parser.parse_args()
    raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==BASELINE
    pe=pefile.PE(data=raw);base=pe.OPTIONAL_HEADER.ImageBase;read=lambda a,n:pe.get_data(a-base,n)
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);u32=lambda a:struct.unpack('<I',read(a,4))[0]
    dispatch=[]
    for kind,target in [(12,0x500fa0),(248,0x500fa0),(13,0x4f4e30)]:
        case=u32(0x69a7f8+4*read(0x69abc0+kind-10,1)[0]);ins=list(md.disasm(read(case,12),case))
        assert (ins[1].mnemonic,ins[1].op_str)==('call',hex(target));dispatch.append({'type':kind,'case':hex(case),'function':hex(target)})
    constants=[]
    for name,address,value in [('horf_range',0xb6aba8,200),('horf_normal_speed',0xb6a928,7),('horf_hard_speed',0xb6a974,10),
        ('horf_friction',0xb6a50c,.7),('fly_jitter',0xb6a4c4,.6),('fly_jitter_retention',0xb6a434,.4),('fly_dung_search',0xb6abe4,240),('fly_edge_bias',0xb6a278,.06)]:
        found=struct.unpack('<f',read(address,4))[0];assert abs(found-value)<1e-6
        constants.append({'name':name,'address':hex(address),'float32':found})
    for address,name in [(0xb40510,'Attack'),(0xb400ac,'Shoot'),(0xb41e80,'Shake')]:assert read(address,len(name)+1)==name.encode()+b'\0'
    windows=[('horf_acquisition_and_delay',0x500fbf,0x501125),('horf_current_aim_and_speed',0x501125,0x50124e),
        ('horf_projectile_flags_and_fire',0x501369,0x5013ec),('horf_animation_recovery',0x50145c,0x5014ee),
        ('shared_acquisition',0x6a15a0,0x6a174c),('shared_interval',0x684790,0x6847db),
        ('fly_dung_transform',0x4f5ab2,0x4f5b1e),('fly_dung_search',0x4f6383,0x4f651a),
        ('fly_ordinary_target_reset',0x4f651a,0x4f6553),('fly_player_drift',0x4f6bb9,0x4f6d0e),
        ('fly_buzz_and_edge_forces',0x4f6d0e,0x4f6e78)]
    result={'baseline':'Repentance1.7.9b','executable_sha256':BASELINE,'dispatch':dispatch,'constants':constants,
        'horf_findings':[
            'Shared Horf12/PsychicHorf248 update calls acquisition with range200, prediction false, interval7. Shared helper checks target validity, status flags, strict distance<range, source global-frame+entity-index modulo7, and projectile-line collision.',
            'On acquisition, source Attack is requested and delay is28updates in Normal/Greed or14 in Hard/Greedier. Normal shot speed7native/frame; hard speed10. Delay begins before Shoot, not after animation recovery.',
            'At Shoot, ordinary non-controlled Horf fetches the current GetPlayerTarget position. PsychicHorf adds HOMING flag1; this script does not certify the shared homing integrator.',
            'Preserved archive metadata:20-frame Attack at30FPS, Shoot4. Source idle overlay returns toShake after attack completion. Source also damps friction by.7 each update.',
            'DeathWard normal-mode implementation uses20world range,21world/sec shot,32HP, local damage10 and fixed5second3D projectile lifetime. Source spawn/animation-update ordering, status/controlled-target quirks, hard-mode replay details and projectile vertical lifetime remain separate validation work.'
        ],'fly_preflight':[
            'Ordinary type13 uses shared fly AI, not a stationary controller. It has source collisionDamage0 and3HP, with wall-only grid collision.',
            'At every active update, rng%1000==0 can transform a Fly currently over grid type14(dung) into14.0Pooter; it calls grid virtual slot0x10 with1 and restores maxHP. The named Destroy thunk uses slot0x14, so destroying the dung must not be assumed. This is a stochastic check, not a deterministic dwell-time timer.',
            'Ordinary Fly/Pooter target-position is reset to zero except a specific boss-spawner subtype path. While targetless and uncontrolled, a1/5random check adds unit(player-position) *.7*timeScale to velocity.',
            'Globalframe%4==1 adds random unit*.6 to the wander vector, then multiplies it by.4. Globalframe%3==2 adds twice the wander vector through the shared velocity helper and applies friction*.6. Source room-edge constants need mapping to generated3D room boundaries.',
            'Dung search and Dip-target branches precede ordinary target reset. Do not infer a lasting dung homing target from those branches in isolation.',
            'Fly implementation, exact shared velocity/friction integration, room-clear field initialization, dung props, source ordering and item/status/faction exceptions remain unfinished. Preserving this preflight is not a completed Fly port.'
        ],'windows':[]}
    if not args.check:assert not (OUT/'manifest.json').exists();OUT.mkdir(parents=True,exist_ok=True)
    for name,start,end in windows:
        data=read(start,end-start);text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(data,start))+'\n';path=OUT/(name+'.asm')
        if args.check:assert path.read_text()==text
        else:path.write_text(text)
        result['windows'].append({'path':str(path.relative_to(ROOT)),'start':hex(start),'end':hex(end),'raw_sha256':hashlib.sha256(data).hexdigest(),'sha256':hashlib.sha256(path.read_bytes()).hexdigest()})
    if args.check:assert json.loads((OUT/'manifest.json').read_text())==result
    else:(OUT/'manifest.json').write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps({'result':'pass','mode':'check' if args.check else 'preserved','windows':len(windows)}))
if __name__=='__main__':main()
