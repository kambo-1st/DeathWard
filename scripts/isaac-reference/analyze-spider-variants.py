#!/usr/bin/env python3
"""Preserve installed Strider/Swarm Spider dispatch, controllers and constants."""
import argparse,hashlib,json,struct
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2];OUT=ROOT/'docs/reports/isaac-enemy-port/spider_variants/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==SHA
 pe=pefile.PE(data=raw);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 dispatch={}
 for ident,index,case,target in [(814,151,0x699fcb,0x54a0c0),(884,202,0x699f2f,0x53d4c0)]:
  assert read(0x69abc0+ident-10,1)[0]==index and struct.unpack('<I',read(0x69a7f8+4*index,4))[0]==case
  ins=list(md.disasm(read(case,12),case));assert ins[1].mnemonic=='call' and ins[1].op_str==hex(target)
  dispatch[str(ident)]={'index':index,'address':hex(case),'controller':hex(target)}
 constants={}
 for name,a,want in [('ground_retention',0xb6a50c,.7),('strider_retention',0xb6a5d8,.95),('strider_force',0xb6a910,6),('strider_force_span',0xb6a864,3),('strider_turn',0xb6a350,.2),('strider_height',0xb6aeac,-8),('near_range',0xb6aafc,100),('far_range',0xb6aba8,200),('short_speed',0xb6a8f4,5),('medium_speed',0xb6a940,8),('long_speed',0xb6a974,10),('short_spread',0xb6aa4c,45),('medium_spread',0xb6a9c8,20)]:
  value=struct.unpack('<f',read(a,4))[0];assert abs(value-want)<1e-6;constants[name]={'address':hex(a),'value':value}
 strings={hex(a):read(a,30).split(b'\0')[0].decode() for a in [0xb43610,0xb40338,0xb4034c,0xb43110,0xb405cc,0xb43124]}
 assert list(strings.values())==['Row','Jump','Land','HopLong','Hop','HopShort']
 states=[hex(x) for x in struct.unpack('<7I',read(0x54a77c,28))]
 windows=[('strider_dispatch',0x699fcb,0x699fd7),('swarm_dispatch',0x699f2f,0x699f3b),('strider_controller',0x54a0c0,0x54a77a),('strider_facing',0x549f50,0x54a0b1),('swarm_controller',0x53d4c0,0x53e272)]
 result={'baseline':'Installed Repentance 1.7.9b','executable_sha256':SHA,'dispatch':dispatch,'constants':constants,'strings':strings,'strider_states':states,'windows':[],
 'findings':[
  'Strider init: grid collision6 NOPITS, height-8, angle90, ready state3. Idle1/4check; then1/2chance of chase if CheckLine mode3 to current target passes; otherwise1/3chance random unit wander. No normal acquisition distance limit. Player control/confusion paths are separate.',
  'Strider state4 preserves walk animation frame while facing changes. Stored zero direction means aim at current target each update; nonzero direction means wander. Angle follows20%of wrapped angular error each source update. Row event adds6+3*U velocity along current direction; end controller friction retention0.95. Walk20frames with Row6; returns ready when animation ends. State6 handles thrown arrival and is not ordinary rowing.',
  'Swarm init sets ready3 and ENTCOLL_PLAYEROBJECTS2. Native enum says player/tears/familiars, excluding ordinary enemy-body collision. Nonzero subtype expands into extra same-type actors scattered +/-20source units and then clears subtype; only installed884.0.0 is covered here.',
  'Swarm ready gets player target (normal helper). Zero distance does nothing. Direction turns if rng modulo4 is0, or modulo20 when distance>200; distance<100 always turns. A turn is half reverse180degrees, half randomly+90/-90degrees. Otherwise direction points toward target.',
  'Swarm weighted hop choices short/medium/long: distance<100 weights5/3/0;100..200 weights2/3/2;>200 weights2/3/9. Short speed5+U, spread+/-45degrees; medium8+2U,+/-20; long10+3U,+/-10. Selected launch vector is committed before the animation.',
  'Swarm Jump assigns committed velocity and sets FLAG_NO_PHYSICS_KNOCKBACK bit30; Land clears it. While not carrying that flag, friction retention0.7. Native controller changes no grid collision or physical world height during ordinary hops; sprite carries visual hop. After Land,1/4chance ends animation early per update, otherwise wait for its end.',
  'Animation metadata at30FPS: HopShort10/Jump2/Land8; Hop12/Jump3/Land9; HopLong18/Jump4/Land14. Jump also emits source sound258 with randomized pitch1.8..2.0. Item377Bursting Sack loads inert visuals and changes target selection; not ordinary hostile behavior.',
  'Installed XML StriderHP6.5/stage0 and SwarmHP4.5/stage.2, contact1, radius13. Pinned Spider wiki establishes Strider replacement of all Spider spawns in Downpour/Dross, and Swarm immunity to fireplace damage. Current web fetch403; pinned revision268921 retained. Local fireplace exception is scoped to source actor contact, not arbitrary Flame/Burning damage.'
 ]}
 if not args.check:assert not (OUT/'manifest.json').exists();OUT.mkdir(parents=True,exist_ok=True)
 for name,a,b in windows:
  blob=read(a,b-a);text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(blob,a))+'\n';path=OUT/(name+'.asm')
  if args.check:assert path.read_text()==text
  else:path.write_text(text)
  result['windows'].append({'path':str(path.relative_to(ROOT)),'start':hex(a),'end':hex(b),'raw_sha256':hashlib.sha256(blob).hexdigest(),'sha256':hashlib.sha256(path.read_bytes()).hexdigest()})
 if args.check:assert json.loads((OUT/'manifest.json').read_text())==result
 else:(OUT/'manifest.json').write_text(json.dumps(result,indent=2)+'\n')
 print(json.dumps({'result':'pass','windows':len(windows)}))
if __name__=='__main__':main()
