#!/usr/bin/env python3
"""Preserve installed ordinary Pooter, shared fly force and normal dung evidence."""
import argparse, hashlib, json, struct
from pathlib import Path
import capstone, pefile

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/fly_pooter/source'
EXE = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
BASELINE = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    raw = EXE.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == BASELINE
    pe = pefile.PE(data=raw);base = pe.OPTIONAL_HEADER.ImageBase
    read = lambda address, count: pe.get_data(address-base, count)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    u32 = lambda address: struct.unpack('<I', read(address, 4))[0]
    case = u32(0x69a7f8+4*read(0x69abc0+14-10, 1)[0])
    dispatch = list(md.disasm(read(case, 12), case))
    assert dispatch[1].mnemonic == 'call' and dispatch[1].op_str == '0x4f4e30'
    assert u32(0xb49fb4+0x10) == 0x6e6400
    assert u32(0xb49fb4+0x18) == 0x6e69b0
    constants = []
    for name,address,value in [('cooldown_friction',0xb6a560,.8),('wander_cooldown',0xb6a50c,.7),
        ('ordinary_speed',0xb6a928,7),('hard_speed',0xb6a974,10),('super_hard_speed',0xb6a940,8),
        ('range',0xb6aba8,200),('edge_top',0xb6abd0,230),('edge_bottom',0xb6ac6c,420),
        ('edge_right',0xb6ac94,540),('edge_left',0xb6aad4,80)]:
        found = struct.unpack('<f', read(address,4))[0]
        assert abs(found-value)<1e-6
        constants.append({'name':name,'address':hex(address),'float32':found})
    windows = [
        ('pooter_attack',0x4f5b1e,0x4f5dc5),('pooter_recovery',0x4f5a1d,0x4f5a5b),
        ('hard_mode_predicate',0x6af030,0x6af04e),('add_velocity',0x422b60,0x422bcf),
        ('normal_dung_damage',0x6e646a,0x6e64d8),('dung_damage_state',0x6e6596,0x6e65e8),
        ('entity_config_default',0x66cc09,0x66cc30),('npc_clear_flag_load',0x692a34,0x692a55),
        ('npc_can_shut_doors',0x68f550,0x68f56f)
    ]
    result = {
        'baseline':'Installed Repentance 1.7.9b','executable_sha256':BASELINE,
        'shared_fly_preflight':'docs/reports/isaac-enemy-port/horf_fly/source/manifest.json',
        'api_binding_evidence':'docs/reports/isaac-enemy-port/horf_fly/source/api-bindings.json',
        'pooter_dispatch':{'case':hex(case),'function':'0x4f4e30'},
        'dung_vtable':'0xb49fb4','dung_hurt':'0x6e6400','constants':constants,
        'findings':[
            'Ordinary Pooter uses the shared fly update. Acquisition calls the same strict range200, interval7, non-predictive helper as Horf. On acquisition delay35 is set; variant2 uses63. Shoot fetches the current target, firing mode0 for ordinary Pooter.',
            'Normal shot speed is7native/frame. Predicate6af030 explicitly checks game modes1/3; hard ordinary speed10 and Super Pooter speed8 are separate from normal mode. Only ordinary normal-mode Pooter is implemented in this batch.',
            'Preserved Pooter animation is14frames at30FPS, Shoot6. While its source delay is positive, friction is multiplied by.8 and wandering vector by.7 each update. Recovery returns the actor to flying state after Attack finishes.',
            'AddVelocity at422b60 adds vector*timeScale/currentFriction before the shared movement update. The existing Fly preflight supplies the1/5player impulse, fourth-frame jitter and third-frame wander/friction. Exact common movement-update ordering and time-dilation/knockback parity remain unaccepted.',
            'Entity config constructor sets shutDoors at+58 totrue; NPC initialization copies it to+b8c. CanShutDoors reads this flag unless friendly. Fly XML has no override and its shared AI has no observed clear-flag rewrite, supporting normal room-threat participation.',
            'Normal dung Hurt starts from supplied integer damage, adds one with probability1/3, and for variant0 independently adds another with probability1/3. It increases grid state by250times that result, capped at1000. Thus Hurt1 removes1,2or3of four ordinary damage steps; it need not destroy a fresh pile.',
            'Fly transformation checks grid type14 without checking damage state. It calls Hurt1 but does not branch on that return before Morph14.0 and restoring maxHP. A destroyed dung remnant can still permit the transformation while the grid remains present.',
            'Local3D adaptations: independent seeded dung placement, low-poly mesh, four health steps, no dung loot/item/special variants yet; bombs destroy the pile and regular projectiles request Hurt1. Exact native projectile-to-grid damage conversion remains separate work.'
        ],'windows':[]
    }
    if not args.check:
        assert not (OUT/'manifest.json').exists()
        OUT.mkdir(parents=True,exist_ok=True)
    for name,start,end in windows:
        data = read(start,end-start)
        text = '\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(data,start))+'\n'
        path = OUT/(name+'.asm')
        if args.check:assert path.read_text()==text
        else:path.write_text(text)
        result['windows'].append({'path':str(path.relative_to(ROOT)),'start':hex(start),'end':hex(end),
            'raw_sha256':hashlib.sha256(data).hexdigest(),'sha256':hashlib.sha256(path.read_bytes()).hexdigest()})
    if args.check:assert json.loads((OUT/'manifest.json').read_text())==result
    else:(OUT/'manifest.json').write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps({'result':'pass','mode':'check' if args.check else 'preserved','windows':len(windows)}))

if __name__=='__main__':main()
