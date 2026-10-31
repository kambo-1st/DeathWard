#!/usr/bin/env python3
"""Preserve bounded installed1.7.9b Crackle FIRE_WAVE and Fire Jet evidence."""
import argparse,hashlib,json,struct
from pathlib import Path
from urllib.request import urlopen
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/crackle/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
BASELINE='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
URL='https://wofsauge.github.io/IsaacDocs/rep/enums/GridCollisionClass.html'
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--check',action='store_true');args=p.parse_args()
 data=EXE.read_bytes();assert hashlib.sha256(data).hexdigest()==BASELINE
 pe=pefile.PE(data=data);base=pe.OPTIONAL_HEADER.ImageBase;read=lambda a,n:pe.get_data(a-base,n)
 u32=lambda a:struct.unpack('<I',read(a,4))[0]
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 # Installed RTTI is independent of the nonmatching later-source Update signature.
 rtti=b'.?AVEntity_Effect@IsaacRepentance@@\0';assert read(0xbeaaf4,len(rtti))==rtti
 locator=u32(0xb459ec);assert u32(locator+12)==0xbeaaec
 assert u32(0xb459fc)==0x5bdf00
 assert u32(0x5e9214+4*(148-1))==0x5c2176 and u32(0x5e9214+4*(147-1))==0x5c1fdc
 bindings=[]
 for name,string,registration,function in [('GetGridCollisionAtPos',0xb53ef0,0x809000,0x7aee40),('GetClampedPosition',0xb54110,0x808eca,0x427710),('FrameCount',0xb51b64,0x8052f7,0x682200)]:
  # FrameCount's string address is recovered from the registration, not assumed.
  if name=='FrameCount':string=u32(registration+6)
  raw=b'\x68'+struct.pack('<I',function)+b'\x68'+struct.pack('<I',string)
  assert read(registration,10)==raw and read(string,len(name)+1)==name.encode()+b'\0'
  bindings.append({'name':name,'registration':hex(registration),'function':hex(function)})
 constants=[]
 for name,address,value in [('step',0xb6aa0c,30),('scale_per_frame',0xb6a248,.03),('stop_scale',0xb6a350,.2),('cardinal_rotation',0xb6aae4,90),('damage_radius',0xb6a9c8,20)]:
  found=struct.unpack('<f',read(address,4))[0];assert abs(found-value)<1e-6;constants.append({'name':name,'address':hex(address),'value':found})
 windows=[('projectile_fire_wave_impact',0x63334c,0x633433),('effect_dispatch',0x5be281,0x5be2b8),
  ('wave_init',0x5bab67,0x5bab9d),('wave_propagation',0x5c2176,0x5c244d),('jet_pulses_and_lifetime',0x5c1fdc,0x5c2176),
  ('radial_damage_factions',0x6d1280,0x6d1446),('frame_count',0x682200,0x682212),('rotation_setter',0x427510,0x427524),
  ('sprite_scale_setter',0x427330,0x42734b),('clamped_position_wrapper',0x427710,0x42773e)]
 if not args.check:
  assert not (OUT/'manifest.json').exists();OUT.mkdir(parents=True,exist_ok=True)
  with urlopen(URL,timeout=30) as response:(OUT/'grid-collision.html').write_bytes(response.read())
 html=(OUT/'grid-collision.html').read_text();assert 'COLLISION_PIT' in html and 'COLLISION_OBJECT' in html
 result={'baseline':'Repentance1.7.9b','executable_sha256':BASELINE,'effect_rtti':{'descriptor':'0xbeaaec','locator':hex(locator),'vtable':'0xb459f0','update':'0x5bdf00'},
  'bindings':bindings,'constants':constants,'enum_reference':{'url':URL,'path':str((OUT/'grid-collision.html').relative_to(ROOT)),'sha256':hashlib.sha256((OUT/'grid-collision.html').read_bytes()).hexdigest()},
  'findings':[
   'FIRE_WAVE bit35 spawns four1000.148 effects at impact with rotations0/90/180/270, original spawner and projectile parent. Friendly flags are propagated. This is distinct from EXPLODE.',
   'The invisible generator advances30native units on even FrameCount, rejects room-clamped positions and grid collision>1; grid class1 is pit. Each accepted point spawns1000.147 Fire Jet.',
   'Jet SpriteScale is1-.03*generatorFrameCount. Generator removes itself after emitting a jet with scale<.2: frame28. Local first-after-spawn scheduling uses ages2..28 (14jets); whether native age0 participates in the spawn frame remains unverified.',
   'Fire Jet damages only at its ages2 and4; source radius20, collisionDamage10 and FIRE damage flag2. It disappears when Idle animation finishes. Extracted Idle metadata is20frames at30FPS.',
   'The radial helper receives original EntityRef; hostile jet allows NPC damage and one player half-heart (damage10 is below the30threshold). Friendly source suppresses player damage. Damage call carries countdown30; exact NPC countdown arbitration remains open.',
   'SpriteScale changes appearance only in this branch; the explicit radius20 damage call is not scaled. Native shared movement/status and source ordering remain separate acceptance work.'
  ],'windows':[]}
 for name,start,end in windows:
  raw=read(start,end-start);text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(raw,start))+'\n';path=OUT/(name+'.asm')
  if args.check:assert path.read_text()==text
  else:path.write_text(text)
  result['windows'].append({'path':str(path.relative_to(ROOT)),'start':hex(start),'end':hex(end),'raw_sha256':hashlib.sha256(raw).hexdigest(),'sha256':hashlib.sha256(path.read_bytes()).hexdigest()})
 if args.check:assert json.loads((OUT/'manifest.json').read_text())==result
 else:(OUT/'manifest.json').write_text(json.dumps(result,indent=2)+'\n')
 print(json.dumps({'result':'pass','mode':'check' if args.check else 'preserved','windows':len(windows)}))
if __name__=='__main__':main()
