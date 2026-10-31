#!/usr/bin/env python3
"""Preserve installed type16 controllers, death payloads and Troll Bomb inputs."""
import argparse, hashlib, json, struct
from pathlib import Path
import capstone, pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/mulligans/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def main():
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--check',action='store_true');args=ap.parse_args()
    raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==SHA
    pe=pefile.PE(data=raw);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    assert read(0xb51a60,17)==b'CollidesWithGrid\x00'
    assert read(0x641420,7)==bytes.fromhex('8a8188010000c3')
    assert struct.unpack('<4I',read(0xb48ce8,16))==(0x67aa80,0x67aba0,0x686060,0x67ae90)
    constants={}
    for key,a,want in [('normal_speed',0xb6a928,7),('hard_speed',0xb6a974,10),('overkill',0xb6aeb8,-10),
        ('contact_period',0xb6a8f4,5),('contact_squared_range',0xb6ace4,1600),('walk_retention',0xb6a560,.8),
        ('chase_retention',0xb6a5a4,.9),('diagonal_axis',0xb6a524,2**-.5),('bomb_base_radius',0xb6aac4,75),
        ('double_player_damage_threshold',0xb6aad8,85)]:
        v=struct.unpack('<f',read(a,4))[0];assert abs(v-want)<1e-6;constants[key]={'address':hex(a),'value':v}
    windows=[('type16_dispatch',0x699790,0x69979c),('controller',0x4f9a70,0x4fa1db),
        ('grid_collision_lua_binding',0x805473,0x805482),('grid_collision_getter',0x641420,0x641427),
        ('source_interval',0x6847e0,0x684852),('cardinal_diagonal_modes',0x6a269d,0x6a2ac0),
        ('bomb_initialization',0x67aba0,0x67ae83),('bomb_appearance_timer',0x67afe6,0x67b053),
        ('bomb_animation_count',0x67b481,0x67b4e4),('bomb_explosion_call',0x67ccfa,0x67cda0),
        ('bomb_explosion_radius',0x6d26e0,0x6d2752),('bomb_radius_application',0x6d28fa,0x6d294e),
        ('blast_player_damage',0x6d205b,0x6d20c4)]
    data={'baseline':'Installed Repentance1.7.9b','executable_sha256':SHA,'constants':constants,
        'findings':[
            'Type16 dispatches4f9a70. Variants0/1 use the same EvadeTarget and MoveRandomly primitives reviewed for Hive, then.8friction. Variant2 uses FindGridPath with speed1.2, marker0,direct-pathtrue, then.9friction.',
            'Variants0/1 test Entity+188 and RNG%300==0 on ready updates, then playExplode and enterstate5. This is CollidesWithGrid: the installed Lua registration binds that exact name to getter641420which returns byte+188. It is not a fixed-age or arbitrary nearby-player trigger.',
            'State5 multiplies friction by.8 and waits for animation completion. Extracted30FPS Explode lasts29frames with no trigger events. Completion calls BombDamage with40damage,60radius,lineChecktrue,sourceactor,flags4anddamageSourcefalse; emits mode6cardinal shots and Kill. Normal shot speed7; hardmode10.',
            'Mulliboom checks source interval5 with offset0; target squared distance<1600callsKill. This is a40-unit proximity trigger, not a literal radius-sum collision despite the wiki contact shorthand. No explosion windup for variant2. Dead processing always calls the same40/60BombDamage and visual effects.',
            'Mulligoon dead processing always emits mode7diagonal shots and spawns type4variant3Troll Bomb with itself as producer. Voluntary detonation already emitted the cardinal mode6and immediate40/60blast, yielding eight total shots plus the delayed bomb.',
            'Mulligan death requiresHP>-10. Count=max(0,4-signedWordNPC+bc6); no room-population denominator. Each child independently selects RNG%11:0..6Fly13,7Pooter14,8..10AttackFly18. Offset is randomangle*U*6without the Hive minimum2. Children do not receive live-spit contact-expiry flags. Nonzero+bc6counter lifecycle remains unverified.',
            'RTTI Entity_Bomb@IsaacRepentance vtableb48ce8maps Init67aba0/Update67ae90. Init sets damage100 and count45; variants3/4/8/18add independent RNG%30. Normal radius starts75 for damage100. Generic blast damage below85passes player damage1; above/equal85passes2, unless special damage flags override it.',
            'Troll count45..74is initialized source data, not yet proof of wall-clock fuse: Update uses animation count and extends a state-dependent appearance timer. Local seconds=(45+RNG%30)/30is an explicit provisional interpretation; full animation/fuse, pushing/kicking/status/item parity remains pending.',
            'Shared pathfinding gaps from the Hive review remain. Local retained payload capacity, sourceHPx3.2and physical3D projectile/blast treatment are explicit adaptations, not native engine equivalence.'
        ],'windows':[]}
    if not args.check:assert not (OUT/'manifest.json').exists();OUT.mkdir(parents=True,exist_ok=True)
    for name,a,b in windows:
        raw=read(a,b-a);text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(raw,a))+'\n';p=OUT/(name+'.asm')
        if args.check:assert p.read_text()==text
        else:p.write_text(text)
        data['windows'].append({'path':str(p.relative_to(ROOT)),'start':hex(a),'end':hex(b),'raw_sha256':hashlib.sha256(raw).hexdigest(),'sha256':hashlib.sha256(p.read_bytes()).hexdigest()})
    data['records']=json.loads((OUT.parent/'records.json').read_text())
    if args.check:assert json.loads((OUT/'manifest.json').read_text())==data
    else:(OUT/'manifest.json').write_text(json.dumps(data,indent=2)+'\n')
    print(json.dumps({'result':'pass','mode':'checked' if args.check else 'preserved','windows':len(windows)}))
if __name__=='__main__':main()
