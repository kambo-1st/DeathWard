#!/usr/bin/env python3
"""Preserve parent movement constants and shared evade evidence from pinned build."""
import argparse,hashlib,json,struct
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/rotten-gaper/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def sha(data):return hashlib.sha256(data).hexdigest()
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=EXE.read_bytes();assert sha(raw)==SHA;pe=pefile.PE(data=raw,fast_load=True)
 read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
 def save(path,data):
  if args.check or path.exists():assert path.read_bytes()==data,path
  else:path.parent.mkdir(parents=True,exist_ok=True);path.write_bytes(data)
 constants={}
 for name,a,want in [('visible_evade_range',0xb6abec,250),('hidden_evade_range',0xb6ab7c,170),
   ('escape_impulse',0xb6a6f0,1.5),('candidate_center',0xb6aa0c,30),('candidate_extra_radius',0xb6ac80,450),
   ('candidate_divisor',0xb6a864,3),('candidate_attempts',0xb6a928,7),('candidate_pressure_scale',0xb6a3b0,.3),
   ('candidate_slack_step',0xb6a974,10),('candidate_target_distance_squared',0xb6ad60,40000),
   ('orbit_radius',0xb6aa8c,60),('brood_player_distance_squared',0xb6ad28,6400),('evade_retention',0xb6a560,.8),
   ('orbit_near',0xb6aad4,80),('orbit_span',0xb6aafc,100),('orbit_gain',0xb6a38c,.25),
   ('orbit_minimum',0xb6a53c,.75),('orbit_retention',0xb6a5a4,.9),('orbit_turn_span',0xb6aa3c,40),
   ('orbit_turn_halfspan',0xb6a9c8,20),('diagonal_bias',0xb6a480,.5)]:
  value=struct.unpack('<f',read(a,4))[0];assert abs(value-want)<1e-5,(name,value,want)
  constants[name]={'address':hex(a),'value':value}
 constants['evade_path_force']={'instruction':'7a5165 immediate0x3f8a1cac','value':struct.unpack('<f',struct.pack('<I',0x3f8a1cac))[0]}
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 a,b=0x7a4830,0x7a51d1;blob=read(a,b-a);ops=list(md.disasm(blob,a))
 assert ops[-1].address+ops[-1].size==b and ops[-1].mnemonic=='ret'
 listing=('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in ops)+'\n').encode()
 save(OUT/'parent-evade.asm',listing)
 records=json.loads((OUT/'records.json').read_text())
 data={'baseline':'Installed Repentance1.7.9b','executable_sha256':SHA,'constants':constants,
  'evade':{'start':hex(a),'end_exclusive':hex(b),'raw_sha256':sha(blob),'listing_sha256':sha(listing),'path':str((OUT/'parent-evade.asm').relative_to(ROOT))},
  'room_templates':{r['key']:r['room_library_presence'] for r in records if r['key'].startswith('10.3.')},
  'source_interpretation':[
   'Brood only acquires different-subtype Rotten neighbor within60 when player distance>80. Retention30..44source frames.',
   'Evade uses globalFrame+entityIndex modulo14, visible250/hidden170, three sticky checks; otherwise wander.',
   'Native evade candidate search has tile-cache pressure, visibility and distance scoring. DeathWard uses physical body clearance and irregular room routes; exact grid-cache parity remains open.',
   'Parent multiplies resulting evade friction by.8; direct orbit multiplies by.9. Neither value is a fixed walking speed.',
   'Brood chance is1/8 only aftercounter>60; reset before owner-cap6; child spawns at parent position with zero velocity.',
   'Default subtype0 chooses uniformly1..5; state0 does not run the active movement branch in the same update.'
  ],'limits':['Native status/charm/control branches not yet ported.','Exact native PRNG, collision mass and tile-cache behavior not claimed.','Stored template presence is not spawn probability.']}
 save(OUT/'parent-movement.json',(json.dumps(data,indent=2)+'\n').encode())
 print(json.dumps({'pass':True,'check':args.check,'constants':len(constants),'helper_instructions':len(ops)}))
if __name__=='__main__':main()
