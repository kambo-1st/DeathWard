#!/usr/bin/env python3
"""Preserve installed Super Pooter pair and Skatole branch evidence without artwork."""
import argparse, hashlib, json, math, struct
from pathlib import Path
import capstone, pefile

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/super_pooter/source'
EXE = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    raw = EXE.read_bytes(); assert hashlib.sha256(raw).hexdigest() == SHA
    pe = pefile.PE(data=raw); read = lambda a,n: pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
    md = capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    assert struct.unpack('<I',read(0x6a33ec+4,4))[0] == 0x6a1afb
    side, forward = [struct.unpack('<f',read(a,4))[0] for a in (0xb6a39c,0xb6a5ec)]
    assert abs(side-.276)<1e-6 and abs(forward-.961)<1e-6
    data = {
        'baseline':'Installed Repentance 1.7.9b', 'executable_sha256':SHA,
        'previous_shared_controller':'docs/reports/isaac-enemy-port/fly_pooter/source/manifest.json',
        'pair':{'mode':1,'forward':forward,'side':side,'half_angle_degrees':math.degrees(math.atan2(side,forward)),
                'speed_multiplier':math.hypot(side,forward),'default_spread':1},
        'findings':[
            'Shared Pooter Shoot chooses FireProjectiles mode1 for variant1, mode0 for ordinary. Normal speed7; hard Super speed8. Source range200/check7/delay35 and Attack14/Shoot6 match ordinary Pooter.',
            'Mode1 emits two vectors: (forward*x - side*Spread*y, forward*y + side*Spread*x) and its opposite-side partner. Constructor initializes Spread at+28 to1. The approximate .961/.276 coefficients are not renormalized in this branch.',
            'Shared update queries collectible9 with its final boolean argument true. For non-friendly actors it sets a local suppression flag; the complete Pooter attack/cooldown-damping branch is skipped while set. Attack animation recovery is earlier and is not skipped.',
            'The same item branch morphs Attack Fly18 into Fly13; other shared-fly branches also consume the flag. Only ordinary/Super Pooter attack suppression is implemented in this slice. This is not a complete Skatole item port.',
            'Local adaptation maps the planar pair to horizontal aim plus physical vertical aiming. The .961/.276 planar coefficients and resulting slight speed loss are preserved; vertical velocity retains the common aimed pitch.',
            'Installed room templates place Super Pooter in Basement/Cellar/Burning Basement, Caves variants, Necropolis and Utero. Local sparse crossfire roles cover bands0–3; source random replacement probability is separate pending work.'
        ],'windows':[]}
    if not args.check:
        assert not (OUT/'manifest.json').exists(); OUT.mkdir(parents=True,exist_ok=True)
    for name,start,end in [
        ('pair_dispatch',0x6a1a6d,0x6a1a83),('pair_vectors',0x6a1afb,0x6a1c91),
        ('params_spread_default',0x430d70,0x430dc5),('skatole_flag_and_attack_fly_morph',0x4f4ff6,0x4f503f),
        ('pooter_attack',0x4f5b1e,0x4f5dc5),('pooter_recovery',0x4f5a1d,0x4f5a5b)]:
        blob=read(start,end-start)
        text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(blob,start))+'\n'
        path=OUT/(name+'.asm')
        if args.check: assert path.read_text()==text
        else: path.write_text(text)
        data['windows'].append({'path':str(path.relative_to(ROOT)),'start':hex(start),'end':hex(end),
            'raw_sha256':hashlib.sha256(blob).hexdigest(),'sha256':hashlib.sha256(path.read_bytes()).hexdigest()})
    records=json.loads((ROOT/'docs/research/isaac-mechanics-reference.json').read_text())['records']
    record=next(r for r in records if r.get('key')=='14.1.0')
    data['xml']=record['xml']; data['room_library_presence']=record['room_library_presence']
    if args.check: assert json.loads((OUT/'manifest.json').read_text())==data
    else: (OUT/'manifest.json').write_text(json.dumps(data,indent=2)+'\n')
    print(json.dumps({'result':'pass','mode':'check' if args.check else 'preserved','windows':len(data['windows']),'pair':data['pair']}))

if __name__=='__main__': main()
