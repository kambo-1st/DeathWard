#!/usr/bin/env python3
"""Preserve installed Prey and Small Leech controllers, metadata and launch evidence."""
import argparse,hashlib,json,struct
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2];OUT=ROOT/'docs/reports/isaac-enemy-port/prey/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def main():
 ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--check',action='store_true');args=ap.parse_args()
 data=EXE.read_bytes();assert hashlib.sha256(data).hexdigest()==SHA
 pe=pefile.PE(data=data);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 constants={}
 for name,a,want in [('wet_acceleration',0xb6a228,.016),('wet_acceleration_cap',0xb6a3f8,.35),('wet_retention',0xb6a5e8,.96),
  ('dry_retention',0xb6a50c,.7),('dry_impulse_minimum',0xb6a7b0,2),('dry_impulse_span',0xb6a7b0,2),('speed_cap',0xb6a974,10),
  ('wall_bounce',0xb6ae28,-.6),('wall_margin_x',0xb6a974,10),('wall_margin_top',0xb6a9c8,20),('wall_margin_bottom',0xb6a8cc,4),
  ('source_overkill',0xb6aee4,-20),('death_launch_initial_height',0xb6aeb8,-10),('death_launch_planar_multiplier',0xb6a264,.04)]:
  v=struct.unpack('<f',read(a,4))[0];assert abs(v-want)<1e-6;constants[name]={'address':hex(a),'value':v}
 dispatch={}
 for id,want in [(810,0x699fbf),(817,0x699fef)]:
  index=read(0x69abc0+id-10,1)[0];address=struct.unpack('<I',read(0x69a7f8+4*index,4))[0];assert address==want
  dispatch[str(id)]={'index':index,'address':hex(address)}
 assert read(0xb4034c,5)==b'Land\0'
 windows=[('dispatch_small_leech',0x699fbf,0x699fcb),('dispatch_prey',0x699fef,0x699ffb),
  ('small_leech_controller',0x548fc0,0x549d41),('leech_launch',0x549d70,0x549f48),
  ('prey_live_child',0x4fa868,0x4fa8cb),('population_death_count',0x4faccb,0x4fada7),('prey_death_launch',0x4fb036,0x4fb127)]
 result={'baseline':'Installed Repentance1.7.9b','executable_sha256':SHA,'dispatch':dispatch,'constants':constants,'windows':[],
 'findings':[
 'Type810 dispatches548fc0; type817 shares Hive controller4fa1e0. Positive room field+7134 chooses wet behavior and grid collision6(no pits); dry uses5(ground), except thrown state6 uses3(walls).',
 'Ordinary wet Small Leech normalizes the current target delta, increases internal acceleration by.016/update capped.35, adds that force and applies.96retention. It has no alignment acquisition or wall-stop attack state. Source speed cap is10 after friction. Source edge response reverses the offending velocity axis by-.6 within X10/top20/bottom4room margins.',
 'Ordinary dry Small Leech applies.7retention while idle and has a1/2chance per ready update to launch a short hop. Impulse is normalized target direction times2+2*U. State7 coasts until Land has occurred, then.7retention, returning to state3after animation completion. Metadata establishes Hop10/Land6,30FPS. Source hop is sprite animation, not an airborne entity-height state.',
 'The native wet controller also contains owner-orbit, status/fear/confusion and subtype1branches; only exact XML810.0.0 normal hostile behavior is in this slice. Knockback is not disabled by this controller.',
 'Prey uses shared evasion/cooldown/population/HeadAttack18/Shoot4rules. Its Shoot emits type810variant0subtype0without the Hive AttackFly contact-expiry flag. Live children have full sourceHP5.',
 'Prey death requiresHP>-20. The shared ceil(4/(1+.2*room population))count is reduced by1and clamped to minimum1; native signedNPC+bc6then subtracts. Ordinary zero counter gives3alone,2with2others,1with5others. The wiki2..3description omits crowd suppression.',
 'Death selects a free nearby point with source radius80and wet-room permission, adds a random direction times10and calls549d70with initial height-10. The helper emits a Small Leech at the parent, state6, initial vertical velocity-8and planar velocity.04*(target-origin). State6integrates gravity+.7perupdate, sets grid collision3and entity collision0, and restores grid6/entity4/ready3on landing. This thrown birth is distinct from ordinary sprite hops and live spitting.',
 'Prey,Small Leech XML, room-library habitats and animation metadata are preserved separately. Canyon wet-room mapping, HPx3.2 and world geometry/visual conversion are DeathWard adaptations, not native engine equivalence.'
 ]}
 if not args.check:assert not (OUT/'manifest.json').exists();OUT.mkdir(parents=True,exist_ok=True)
 for name,a,b in windows:
  raw=read(a,b-a);text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(raw,a))+'\n';path=OUT/(name+'.asm')
  if args.check:assert path.read_text()==text
  else:path.write_text(text)
  result['windows'].append({'path':str(path.relative_to(ROOT)),'start':hex(a),'end':hex(b),'raw_sha256':hashlib.sha256(raw).hexdigest(),'sha256':hashlib.sha256(path.read_bytes()).hexdigest()})
 result['records']=json.loads((OUT.parent/'records.json').read_text())
 if args.check:assert json.loads((OUT/'manifest.json').read_text())==result
 else:(OUT/'manifest.json').write_text(json.dumps(result,indent=2)+'\n')
 print(json.dumps({'result':'pass','windows':len(windows)}))
if __name__=='__main__':main()
