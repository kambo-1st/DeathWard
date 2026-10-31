#!/usr/bin/env python3
"""Preserve installed Attack Fly pursuit, morph and live-Hive contact evidence."""
import argparse, hashlib, json, struct
from pathlib import Path
import capstone, pefile

ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/attack_fly/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--check',action='store_true');args=parser.parse_args()
    raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==SHA
    pe=pefile.PE(data=raw);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    assert struct.unpack('<I',read(0xb49398+0x24,4))[0]==0x695560
    assert struct.unpack('<I',read(0xb49398+0x58,4))[0]==0x6a3970
    constants={}
    for name,address,expected in [('deadzone',0xb6a9ec,25),('axis_scale',0xb6a480,.5),('gain',0xb6a2ac,.08),
        ('force_cap',0xb6a670,1.2),('contact_friction',0xb6a5a4,.9),('parent_scale',0xb6a350,.2)]:
        value=struct.unpack('<f',read(address,4))[0];assert abs(value-expected)<1e-6
        constants[name]={'address':hex(address),'value':value}
    data={'baseline':'Installed Repentance 1.7.9b','executable_sha256':SHA,'constants':constants,
        'findings':[
            'Type18 dispatches to shared update4f4e30. Target cache refreshes on global third frames; the ordinary target helper returns the player target position. The source force scheduler is every two entity-time frames.',
            'Ordinary pursuit uses target minus position with second axis multiplied by.5, then normalizes. Native deadzone25, gain.08 and cap1.2. The special214/249/819 doubling is not applied to18. Parent-linked variants have an additional.2 scale and tether branch; a summoner is not necessarily a Parent.',
            'Existing shared fourth-frame jitter and third-frame friction apply. Actor byte16c adds.9 friction during pursuit. SpawnerType67 skips ordinary edge bias.',
            'Live Hive22 spawn4fa8cb..4fa930 sets child18 byte16c=1. Player collision6a5552 invokes virtual Kill when this byte is set. NPC vtableb49398 resolves Kill695560 and HandleCollision6a3970. Hive death offspring do not pass through this live-spawn branch.',
            'Collectible9 morphs a non-friendly18 into13. Native Morph clamps current HP to the new maximum; unlike dung morph, this caller does not explicitly restore full HP. The examined Morph/config-load code does not clear byte16c. A fly-tag collision branch also suppresses contact damage when collectible9 is owned.',
            'Boss-child source preflight is retained only: Gurdy36 live children set byte16c and subtract2 from current HP; Duke/Husk67 share a controller with parent-linked children and source-specific size/HP changes. No boss-child parity is claimed by this ordinary-enemy slice.'
        ],'windows':[]}
    if not args.check:assert not (OUT/'manifest.json').exists();OUT.mkdir(parents=True,exist_ok=True)
    windows=[('dispatch',0x69a0c7,0x69a0ce),('initialization',0x4f4e30,0x4f4f03),
        ('skatole_morph',0x4f4ff6,0x4f503f),('target_period',0x4f6162,0x4f61b5),
        ('target_cache',0x4f64f5,0x4f651a),('ordinary_target',0x695bf3,0x695c2d),
        ('pursuit_force',0x4f67c1,0x4f6a3a),('shared_jitter_and_edge',0x4f6d0e,0x4f6ee0),
        ('hive_live_spawn',0x4fa8cb,0x4fa930),('player_collision',0x6a5129,0x6a5562),
        ('kill',0x695560,0x6955f5),('morph',0x697c60,0x697e21),
        ('load_npc_config',0x692960,0x692f73),('load_entity_config',0x681ea0,0x682190),
        ('gurdy_child_preflight',0x46b791,0x46b7d0),('duke_husk_child_preflight',0x45e9a1,0x45ead8)]
    for name,start,end in windows:
        blob=read(start,end-start)
        text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(blob,start))+'\n'
        path=OUT/(name+'.asm')
        if args.check:assert path.read_text()==text
        else:path.write_text(text)
        data['windows'].append({'path':str(path.relative_to(ROOT)),'start':hex(start),'end':hex(end),
            'raw_sha256':hashlib.sha256(blob).hexdigest(),'sha256':hashlib.sha256(path.read_bytes()).hexdigest()})
    record=next(r for r in json.loads((ROOT/'docs/research/isaac-mechanics-reference.json').read_text())['records'] if r.get('key')=='18.0.0')
    data['xml']=record['xml'];data['room_library_presence']=record['room_library_presence']
    if args.check:assert json.loads((OUT/'manifest.json').read_text())==data
    else:(OUT/'manifest.json').write_text(json.dumps(data,indent=2)+'\n')
    print(json.dumps({'result':'pass','mode':'checked' if args.check else 'preserved','windows':len(windows),'constants':constants}))

if __name__=='__main__':main()
