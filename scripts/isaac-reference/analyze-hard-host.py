#!/usr/bin/env python3
"""Pin Hard Host's slam, rock-wave generator, crush pulse and player hop."""
import argparse,hashlib,json,struct
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/hard_host/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');a=ap.parse_args()
 raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==SHA
 pe=pefile.PE(data=raw);read=lambda address,n:pe.get_data(address-pe.OPTIONAL_HEADER.ImageBase,n)
 u32=lambda address:struct.unpack('<I',read(address,4))[0]
 assert u32(0x5e9214+4*71)==0x5dfb35
 assert u32(0xb4d4f0+0x50)==0x794280
 constants={}
 for name,address,value in [('spawn_offset',0xb6a9c8,20),('slam_range',0xb6ab20,120),('push',0xb6a864,3),('step_distance',0xb6aa0c,30),('angle_span',0xb6ab58,150),('pulse_damage',0xb6a974,10),('hop_gravity',0xb6a64c,1.1)]:
  v=struct.unpack('<f',read(address,4))[0];assert abs(v-value)<1e-5;constants[name]=dict(address=hex(address),value=v)
 windows=[('slam',0x4ff944,0x4ffd40),('wave_init',0x5b8f80,0x5b8fba),
  ('wave_update',0x5dfb35,0x5e05be),('crush_pulse',0x6d1750,0x6d26e0),
  ('player_launch',0x794280,0x79433f),('player_hop',0x74c275,0x74c3ef)]
 result=dict(baseline='Installed Repentance1.7.9b',executable_sha256=SHA,
  bindings={'effect72_dispatch':'0x5dfb35','player_vtable':'0xb4d4f0','launch_virtual_50':'0x794280'},constants=constants,windows=[])
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 if not a.check:assert not (OUT/'manifest.json').exists();OUT.mkdir(parents=True,exist_ok=True)
 for name,start,end in windows:
  blob=read(start,end-start);text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(blob,start))+'\n';p=OUT/(name+'.asm')
  if a.check:assert p.read_text()==text
  else:p.write_text(text)
  result['windows'].append(dict(path=str(p.relative_to(ROOT)),start=hex(start),end=hex(end),raw_sha256=hashlib.sha256(blob).hexdigest(),sha256=hashlib.sha256(p.read_bytes()).hexdigest()))
 if a.check:assert json.loads((OUT/'manifest.json').read_text())==result
 else:(OUT/'manifest.json').write_text(json.dumps(result,indent=2)+'\n')
 print(json.dumps(dict(result='pass',windows=len(windows))))
if __name__=='__main__':main()
