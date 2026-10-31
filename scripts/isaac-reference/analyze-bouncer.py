#!/usr/bin/env python3
"""Pin Repentance1.7.9b Bouncer's controller, reflection and projectile rules."""
import argparse, hashlib, json, struct
from pathlib import Path
import capstone, pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/bouncer/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 sha=lambda data:hashlib.sha256(data).hexdigest()
 def save(path,data):
  if args.check or path.exists():assert path.read_bytes()==data,path
  else:path.parent.mkdir(parents=True,exist_ok=True);path.write_bytes(data)
 raw=EXE.read_bytes();assert sha(raw)==SHA
 pe=pefile.PE(data=raw,fast_load=True);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 index=read(0x69abc0+822-10,1)[0];case=struct.unpack('<I',read(0x69a7f8+index*4,4))[0]
 assert index==157 and case==0x69a127
 assert any(i.mnemonic=='call' and i.op_str=='0x4efe40' for i in md.disasm(read(case,12),case))
 manifest=dict(baseline='Installed Repentance1.7.9b',executable_sha256=SHA,dispatch=dict(type=822,index=index,case=hex(case),controller='0x4efe40'),windows=[],constants={},states={},shared_evidence=[])
 for name,a,b,complete in [
  ('controller',0x4efe40,0x4f0868,True),
  ('reflection',0x64dff6,0x64e10d,False),
  ('explosive-tear-gate',0x64dd2a,0x64dd88,False),
  ('contact-kill',0x6a43a5,0x6a43d0,False),
  ('pair-rng',0x7a7d50,0x7a7da8,True),
  ('extended-acceleration',0x635ea6,0x635f3a,False),
  ('linear-interpolation',0x962380,0x96238d,True),
  ('minimum-helper',0x407e80,0x407e8d,True),
  ('projectile-common-update',0x6302e0,0x6302e7,False),
  ('common-age-increment',0x6860e7,0x686116,False),
  ('shockwave-helper',0x6d6570,0x6d6c5b,True),
  ('blood-effect-callback',0x4efb00,0x4efe35,True),
  ('target-selection',0x695680,0x695a26,True),
 ]:
  blob=read(a,b-a);ins=list(md.disasm(blob,a));assert ins and ins[-1].address+ins[-1].size==b,name
  if complete:assert ins[-1].mnemonic=='ret',name
  data=('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in ins)+'\n').encode();path=OUT/(name+'.asm');save(path,data)
  manifest['windows'].append(dict(name=name,start=hex(a),end_exclusive=hex(b),complete_function=complete,instructions=len(ins),raw_sha256=sha(blob),path=str(path.relative_to(ROOT)),sha256=sha(data)))
 for state in range(17):
  i=read(0x4f087c+state,1)[0];manifest['states'][str(state)]=hex(struct.unpack('<I',read(0x4f0868+i*4,4))[0])
 for name,a,want in [('timer_min',0xb6a910,6),('timer_range',0xb6a8cc,4),('timer_decrement',0xb6a25c,1/30),('damage_timer_divisor',0xb6a8a0,3.5),('evade_friction',0xb6a560,.8),('inflating_friction',0xb6a4c4,.6),('inflated_radius_factor',0xb6a6f0,1.5),('cloud_spawn_offset',0xb6a8f4,5),('cloud_max_planar_speed',0xb6a9ac,15),('cloud_height_base',0xb6aee8,-22),('cloud_height_range',0xb6a940,8),('cloud_falling_accel_base',0xb6addc,-.06),('cloud_falling_accel_range',0xb6a24c,.03),('cloud_scale_range',0xb6a66c,1.2),('ramp_frames',0xb6a9c8,20),('cluster_speed',0xb6a928,7),('cluster_falling_accel',0xb6a3c4,.32),('cluster_fall_range_base',0xb6aa0c,30)]:
  value=struct.unpack('<f',read(a,4))[0];assert abs(value-want)<1e-5,name;manifest['constants'][name]=dict(address=hex(a),value=value)
 shifts=struct.unpack('<3I',read(0xa08c44,12));assert shifts==(5,9,7)
 manifest['reflection_rng']=dict(seed='uint32(tear.InitSeed + target.InitSeed)',shifts=list(shifts),algorithm='x ^= x>>5; x ^= x<<9; x ^= x>>7; unsigned32 modulo5 ==0',incoming_condition='dot(tearVelocity, normalized(tearPosition-targetPosition)) <0',explosive_mask=[hex(n) for n in struct.unpack('<4I',read(0xbc4ca0,16))],ludovico_mask=[hex(n) for n in struct.unpack('<4I',read(0xbc4ce0,16))])
 for relative in ['docs/reports/isaac-enemy-port/bouncer/animations/manifest.json','docs/reports/isaac-enemy-port/nest/source/evade_pathfinder.asm','docs/reports/isaac-enemy-port/long_legs/source/chase_pathfinder.asm','docs/reports/isaac-enemy-port/chubber/source/tear_collision.asm','docs/reports/isaac-enemy-port/chubber/source/npc_collision.asm','docs/reports/isaac-enemy-port/hardy/source/aimed_cluster.asm','docs/reports/isaac-enemy-port/hardy/source/fire_projectiles.asm','docs/reports/isaac-enemy-port/hardy/source/projectile_params.asm','docs/reports/isaac-enemy-port/spitties/source/projectile_init.asm','docs/reports/isaac-enemy-port/gurgle_lobs/source/flight_integrator.asm','reference/isaac-repentance-1.7.9b/loose/resources/scripts/enums.lua']:
  manifest['shared_evidence'].append(dict(path=relative,sha256=sha((ROOT/relative).read_bytes())))
 manifest['claims']=[
  'State0 starts HeadAppear and paused body walk, sets state3, clears the post-inflation chase latch and samples timer U[6,10). First update only initializes.',
  'State3 uses the shared EvadeTarget pathfinder and .8 friction. Timer decrements1/30 per update while positive, additionally max(0,timer-queuedDamage/3.5). Inflation requires age>30, proximity memoryAA0>0, timer<=0, and RNG%20==0; no direct low-HP percentage test.',
  'HeadInflate has21 source frames and Inflate event at7. That event changes state8 to16 and multiplies collision size by1.5. State16 can already reflect/explode before the animation finishes. .6 friction while waiting; after animation completion a latch enables ground chase speed.9 with path marker900 and direct path enabled.',
  'Inflated head animation playback direction alternates +/-1; this is not the reflection lottery. Reflection tests state16 and deterministic pair seed modulo5. It reflects the existing incoming tear radially and returns without ordinary damage; allegiance/ownership and piercing are not changed in this branch. Explosive non-Ludovico tears bypass it.',
  'NPC contact handler kills state16 on collision with a player or its tracked target. Normal forms remain contact-damaging but are not consumed.',
  'Early death (state!=16) emits FireProjectiles mode7: four diagonal shots, planar speed10. Init/default falling properties remain distinct from the large cloud.',
  'Inflated death emits12 FireBossProjectiles with zero target and trajectory0: random directions, speed7, fallingSpeed5-U*24, fallingAccel.32, size.9+.4*(RNG&1)+U*.05.',
  'Inflated death additionally emits22 direct projectiles: random radial offset5, speedU*15, height-22-U*8, fallingSpeed0, fallingAccel-.06-U*.03, size.6+U*1.2. Flags highword0x20 means ACCELERATE_EX (bit37), not ordinary DECELERATE.',
  'ACCELERATE_EX applies lerp(1,.9,min(elapsedSourceAge/20,1)). Common entity update increments age and translates before this multiplier; first age is1. Flight separately uses .9 falling retention and (.1+fallingAccel). Direct cloud shots also invoke one native Update immediately after creation; deferred DeathWard admission must explicitly account for or document this timing difference.',
  'Inflated death calls shockwave helper6d6570 with native radius120 and both booleansfalse. It pushes nearby eligible entities; direct10damage branch is gated on a player source and does not apply to a normal hostile Bouncer. This is not an unconditional damaging bomb explosion or rock-destruction call.',
  'Callback4efb00 creates type1000 effect variant2 subtype3 (blood effects), not additional hostile projectiles. Sound/shake/gore are separate from the34 hostile projectiles.',
 ]
 manifest['scope']='Source-backed implementation contract; Bouncer controller remains unimplemented at this research checkpoint. Existing native primitives and 3D conversions require scoped validation; no original-game live execution claimed.'
 manifest['preflight_note']='Preserved *-preflight.asm files are exploratory and may include tables or following functions. Only bounded manifest windows are authoritative.'
 ref=json.loads((ROOT/'docs/research/isaac-mechanics-reference.json').read_text());record=next(r for r in ref['records'] if r.get('key')=='822.0.0')
 save(OUT/'record.json',(json.dumps(record,indent=2)+'\n').encode())
 a=ref['articles']['Mulligan'];wiki={k:a[k] for k in ['title','revision_url','revision','timestamp','license','attribution']};wiki['sections']=[s for s in a['sections'] if s['heading']=='Bouncer'];wiki['retrieval']='Preserved pinned research article; no fresh retrieval claimed.'
 save(OUT/'wiki-source.json',(json.dumps(wiki,indent=2)+'\n').encode())
 save(OUT/'manifest.json',(json.dumps(manifest,indent=2)+'\n').encode())
 print(json.dumps(dict(pass_=True,check=args.check,windows=len(manifest['windows']),constants=len(manifest['constants']),animation_files=1)))
if __name__=='__main__':main()
