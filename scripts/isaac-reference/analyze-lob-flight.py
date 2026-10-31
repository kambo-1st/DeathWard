#!/usr/bin/env python3
"""Preserve bounded installed1.7.9b flight evidence for ordinary Gurgle/Splasher."""
import argparse, hashlib, json, struct
from pathlib import Path
import capstone, pefile

ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/gurgle_lobs/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
BASELINE='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--check',action='store_true');args=parser.parse_args()
    raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==BASELINE
    pe=pefile.PE(data=raw);base=pe.OPTIONAL_HEADER.ImageBase
    read=lambda address,count:pe.get_data(address-base,count)
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    constants=[]
    for name,address,value in [('retention',0xb6a5a4,.9),('base_accel',0xb6a2cc,.1),('ground_threshold',0xb6ae98,-5),('collision_height',0xb6af28,-50),('unit_time',0xb6a614,1)]:
        found=struct.unpack('<f',read(address,4))[0];assert abs(found-value)<1e-6
        constants.append({'name':name,'address':hex(address),'float32':found})
    windows=[('flight_integrator',0x636567,0x6365d5),('time_scale_retention',0x65c960,0x65c98a),('floor_and_collision_death',0x636de5,0x636e0f)]
    result={'baseline':'Repentance1.7.9b','executable_sha256':BASELINE,'constants':constants,
      'dependencies':['docs/reports/isaac-enemy-port/gurgle_mortality/source/manifest.json','docs/reports/isaac-enemy-port/gurgle_review/animations'],
      'findings':[
        'At ordinary timeScale1: fallingSpeed=.9*fallingSpeed+.1+fallingAccel; height+=fallingSpeed. Projectile flight is damped, not conventional constant-gravity ballistic motion.',
        'Native time-scale helper returns q/(q+t-q*t), with exact q at t=1. DeathWard fractional-tick interpolation is deliberately separate; its full30Hz endpoints match the ordinary source recurrence.',
        'Gurgle FireBossProjectiles trajectory10 followed by source modifiers gives horizontal3.85 + uniform-radial jitter0..1.925, fallingSpeed-6.5..-23.3 and fallingAccel.72.',
        'Splasher mode0 defaults plus modifiers give horizontal5, fallingSpeed-8, fallingAccel.4. Both start at height-23.',
        'Projectile EXPLODE payload remains source50damage/60radius with line check, documented in the preceding mortality source windows.',
        'DeathWard horizontal scaling.1 and vertical scaling.05 are explicit3D adaptations. Geometry uses swept spheres and the actual floor, rather than source grid collision flags and height thresholds.'
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
