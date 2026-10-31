#!/usr/bin/env python3
"""Pin ordinary Gaper path/animation helpers from installed Repentance1.7.9b."""
import argparse,hashlib,json,struct
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/gaper/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def sha(data):return hashlib.sha256(data).hexdigest()
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=EXE.read_bytes();assert sha(raw)==SHA;pe=pefile.PE(data=raw,fast_load=True)
 read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 def save(path,data):
  if args.check or path.exists():assert path.read_bytes()==data,path
  else:path.parent.mkdir(parents=True,exist_ok=True);path.write_bytes(data)
 windows=[]
 for name,start,end in [('grid-path',0x7a3650,0x7a4813),('grid-line',0x7af4b0,0x7afa37),
  ('walk-selector',0x6980a0,0x698323),('overlay-play',0x405a00,0x405a76),('overlay-frame',0x405d10,0x405d20)]:
  blob=read(start,end-start);ops=list(md.disasm(blob,start));assert ops[-1].address+ops[-1].size==end and ops[-1].mnemonic=='ret',name
  listing=('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in ops)+'\n').encode();path=OUT/f'{name}.asm';save(path,listing)
  windows.append({'path':str(path.relative_to(ROOT)),'start':hex(start),'end_exclusive':hex(end),'raw_sha256':sha(blob),'sha256':sha(listing)})
 constants={}
 for name,address,value in [('path-retention',0xb6a50c,.7),('blocked-retention',0xb6a588,.85),
  ('arrived-retention',0xb6a480,.5),('distance-gain',0xb6a2cc,.1),('maximum-gain',0xb6a7b0,2),('arrival-distance',0xb6a614,1)]:
  actual,=struct.unpack('<f',read(address,4));assert abs(actual-value)<1e-6
  constants[name]={'address':hex(address),'value':actual}
 assert read(0xb41e78,5)==b'Head\0'
 # +a90 is a pathfinder member: NPC+364+72c, written by ordinary grid-line check.
 assert read(0x7a3df6,6)==bytes.fromhex('88832c070000')
 forces={name:struct.unpack('<f',struct.pack('<I',bits))[0] for name,bits in
  [('frowning-closed',0x3f19999a),('frowning-open',0x3f3851ec),('ordinary',0x3efef9db),('flaming',0x3f0c3c9f)]}
 data={'baseline':'Installed Repentance1.7.9b','executable_sha256':SHA,'windows':windows,'constants':constants,'forces':forces,
  'findings':['4f7f93..4f7fd7: targetPosition helper(output,0), then FindGridPath(targetPosition,force,900,true).900 is PathMarker, not a range or attack timer.',
   'Normal moving path applies .7 retention and normalized impulse force*min(sourceDistance*.1,2). Arrived distance<=1 applies.5; absent/zero route applies.85.',
   'Frowning starts with Head overlay frame0 paused. After direct-path flag+a90, PlayOverlay(Head,true) starts it. Force increases only once overlay frame>0, independent of later obstruction.',
   'NPC+a90 equals pathfinder+72c. Ordinary path writes grid-line result at7a3df6; direct collision3/control exceptions set true. DeathWard will adapt native cell tests to physical ground navigation.',
   'Walk-selector threshold.1 is a speed threshold, not animation rate. Below it vertical walk is held at frame0; above it22-frame loops play at source30FPS. Frowning Head has20 nonlooping frames; ordinary Head1; Flaming Head12looping.'],
  'limits':['Native grid marker/cell routing and status/control/champion branches are not exact DeathWard geometry equivalents.','Stored wiki Gaper revision270042 section5 establishes Flaming fire vulnerability and no ordinary-to-Flaming fire conversion. Full global native damage dispatch has not been pinned here.']}
 save(OUT/'movement-manifest.json',(json.dumps(data,indent=2)+'\n').encode());print(json.dumps({'pass':True,'check':args.check,'windows':len(windows)}))
if __name__=='__main__':main()
