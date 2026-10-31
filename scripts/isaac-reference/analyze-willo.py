#!/usr/bin/env python3
"""Preserve installed Willo orbit/attack and Mullighoul shared-controller evidence."""
import argparse,hashlib,json,struct
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2];OUT=ROOT/'docs/reports/isaac-enemy-port/mullighoul/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def main():
 ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==SHA
 pe=pefile.PE(data=raw);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 constants={}
 for name,a,want in [('tracking_gain',0xb6a480,.5),('angular_factor',0xb6a260,.035),('ellipse_z',0xb6a580,.84),
  ('angular_pi',0xb6a874,3.141592653589793),('ring_spacing',0xb6a914,6.283185307179586),('settle_squared',0xb6ac60,400),
  ('velocity_cap_and_shot_speed',0xb6a974,10),('settle_range',0xb6a9c8,20),('ownerless_falling_modifier',0xb6a8cc,4),
  ('overkill',0xb6aee4,-20),('population_scale',0xb6a350,.2),('projectile_retention',0xb6a5a4,.9)]:
  value=struct.unpack('<f',read(a,4))[0];assert abs(value-want)<1e-6,(name,value);constants[name]={'address':hex(a),'value':value}
 dispatch={}
 for id,want in [(808,0x699f8f),(817,0x699fef)]:
  i=read(0x69abc0+id-10,1)[0];a=struct.unpack('<I',read(0x69a7f8+4*i,4))[0];assert a==want;dispatch[str(id)]={'index':i,'address':hex(a)}
 for a,s in [(0xb43580,b'Warn\0'),(0xb400ac,b'Shoot\0'),(0xb40510,b'Attack\0')]:assert read(a,len(s))==s
 states={str(i):hex(struct.unpack('<I',read(0x546480+4*i,4))[0]) for i in range(14)}
 windows=[('willo_dispatch',0x699f8f,0x699f9b),('mullighoul_dispatch',0x699fef,0x699ffb),
  ('regroup',0x544b70,0x544dbc),('orbit_target',0x544dc0,0x544eba),('orbit_center',0x544ec0,0x544ff6),
  ('orbit_tracking',0x545000,0x54521d),('attack_events',0x545220,0x5454fe),('willo_controller',0x545510,0x54647e),
  ('boss_special_spawn_helper',0x5464c0,0x546691),('mullighoul_hover',0x4fa226,0x4fa27a),
  ('mullighoul_live_child',0x4fa868,0x4fa8cb),('mullighoul_death_count',0x4faccb,0x4fada7),
  ('mullighoul_death_child',0x4fb036,0x4fb068),('mullighoul_child_admission',0x4fb157,0x4fb175),
  ('projectile_falling_application',0x6a3059,0x6a31b8)]
 result={'baseline':'Installed Repentance1.7.9b','executable_sha256':SHA,'dispatch':dispatch,'states':states,'constants':constants,
 'findings':[
 'Type808 dispatch545510. Init radius120, multiplier1, initial40counter and regroup544b70. XML6HP/stage0/contact0/gridnone. Ordinary subtype0 is separate from Min-Min special emergence/dive helpers.',
 'Regroup selects living subtype0Willos with the same Parent pointer; takes minimumexisting angle offset and reassigns2pi*n/count. Attackstate8 copies its offset to b0c so regrouping cannot move its committed attack slot. Ordinary Mullighoul spawning sets SpawnerEntity but no Parent, so Willos join the ownerless cohort.',
 'Orbit center is Parent position when present, otherwise mean eligible player positions. Target is center+(cos(theta)*radius,sin(theta)*radius*.84), theta=offset-(globalFrame+halfFrame+optionalAheadFrames)*.5*pi*.035. Single-player ordinary case uses current player center.',
 'Tracking takes twice player velocity divided by friction as carry, adds a .5correction from predicted body to orbit target, caps that correction at10sourceunits, and adds the carry. Native collisionNONE allows orbit through grid solids and outside room.',
 'Ready state3 makes a1/9random check. Ordinary subtype0 additionally requires no projectile cooldown, nonnegative entity height, squared target-point error<=400, room-position validity and absence of fear/confusion/shrink flags0x1000a00. Any living subtype0Willo in state8 or9 blocks another attack. Successful acquisition enters8 and copies current orbit slot.',
 'State8 playsAttack, runs the shared event helper and continues orbit tracking. ANM2Attack36/30FPS hasWarn6andShoot24. Completion returns3. No fixed extra cooldown is set by this controller. Special states9/10/6/7/13 have distinct boss/underwater behavior; they are preserved but not claimed implemented.',
 'Shoot aims toward target position plus one target velocity, normalized*10. FireProjectiles mode0 uses BulletFlags0x2000=NO_WALL_COLLIDE per installed enums.lua. Ownerless subtype0adds4to FallingSpeedModifier. Common mode0defaults are fallingSpeed-3/fallingAccel.1; ordinary shot therefore starts atheight-23, fallingSpeed1, and uses .9falling retention plus base.1and authored.1 acceleration.',
 'Mullighoul817variant1 init sets height-6 and gridcollision6(no pits); it does not gain rocks/walls-free flight. Shared Hive18frameHeadAttack/Shoot4spits808.0.0 without disposable-contact flag. InstalledHP14 contradicts wiki infobox13; XML is baseline.',
 'The native817death adjustment is shared by variants0and1: max(1,ceil(4/(1+.2*roompopulation))-1),then subtract signedNPC+bc6 and clamp0. Normal zero-counter result3alone/2with2others/1with5others; no random1..2cap. HP<=-20suppresses. Variant1creates Willos directly; variant0uses thrown Small Leech helper.',
 'Existing inherited source reviews preserve shared evasion and common projectile integration. Physical3D scales, fire damage intervals, safe birth capacity and local habitat weights remain explicit DeathWard adaptations; full native status/item/boss-spawn behavior is not certified.'
 ],'windows':[],'records':json.loads((OUT.parent/'records.json').read_text()),
 'dependencies':['docs/reports/isaac-enemy-port/hive/source/manifest.json','docs/reports/isaac-enemy-port/gurgle_lobs/source/manifest.json','docs/reports/isaac-enemy-port/tainted_pooter/source/manifest.json'],
 'projectile_enum_source':'reference/isaac-repentance-1.7.9b/loose/resources/scripts/enums.lua'}
 if not args.check:assert not (OUT/'manifest.json').exists();OUT.mkdir(parents=True,exist_ok=True)
 for name,a,b in windows:
  blob=read(a,b-a);text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(blob,a))+'\n';p=OUT/(name+'.asm')
  if args.check:assert p.read_text()==text
  else:p.write_text(text)
  result['windows'].append({'path':str(p.relative_to(ROOT)),'start':hex(a),'end':hex(b),'raw_sha256':hashlib.sha256(blob).hexdigest(),'sha256':hashlib.sha256(p.read_bytes()).hexdigest()})
 if args.check:assert json.loads((OUT/'manifest.json').read_text())==result
 else:(OUT/'manifest.json').write_text(json.dumps(result,indent=2)+'\n')
 print(json.dumps({'result':'pass','windows':len(windows)}))
if __name__=='__main__':main()
