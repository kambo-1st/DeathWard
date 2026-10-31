#!/usr/bin/env python3
"""Preserve installed Spitty family source and animation metadata without runtime art."""
import argparse,hashlib,importlib.util,json,struct,xml.etree.ElementTree as ET,zlib
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/spitties'
INSTALL=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth')
EXE_SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def sha(data):return hashlib.sha256(data).hexdigest()
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 if not args.check:assert not (OUT/'source/manifest.json').exists() and not (OUT/'checkpoint.json').exists()
 def save(path,data):
  if args.check:assert path.read_bytes()==data,path
  else:path.parent.mkdir(parents=True,exist_ok=True);assert not path.exists();path.write_bytes(data)
 raw=(INSTALL/'isaac-ng.exe').read_bytes();assert sha(raw)==EXE_SHA
 pe=pefile.PE(data=raw);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 dispatch=[]
 for t in [31,243]:
  i=read(0x69abc0+t-10,1)[0];case=struct.unpack('<I',read(0x69a7f8+4*i,4))[0]
  assert i==9 and case==0x699968
  instructions=list(md.disasm(read(case,20),case));assert any(x.mnemonic=='call' and x.op_str=='0x51afa0' for x in instructions)
  dispatch.append({'type':t,'index':i,'case':hex(case),'controller':'0x51afa0'})
 constants={}
 for name,a,value in [('walk_force',0xb6a534,.72),('retention',0xb6a588,.85),
  ('vertical_axis_retention',0xb6a5f0,.9647058248519897),('shot_speed',0xb6a940,8),
  ('stream_speed',0xb6a9bc,18),('burst_lob_parameter',0xb6a974,10),('burst_speed',0xb6a928,7),
  ('burst_accel_base',0xb6a3c4,.32),('stream_accel_step',0xb6a1fc,.005),('stream_accel_offset',0xb6a2ac,.08),
  ('stream_decel_step',0xb6a248,.03),('stream_size',0xb6a730,1.7),('stream_size_step',0xb6a2cc,.1),
  ('radians',0xb6a230,.0174532925199433),('orbit_drift',0xb6a480,.5),('pi',0xb6a874,3.141592653589793),
  ('two_pi',0xb6a914,6.283185307179586),('grid_spacing',0xb6aa3c,40),('arrival',0xb6a8f4,5),
  ('stuck_speed',0xb6a4c4,.6),('blocked_speed',0xb6a864,3)]:
  actual=struct.unpack('<f',read(a,4))[0];assert abs(actual-value)<1e-5
  constants[name]={'address':hex(a),'value':actual}
 strings={}
 for a,wanted in [(0xb400ac,'Shoot'),(0xb425a8,'Move Hori'),(0xb425a0,'Move Up'),(0xb425c4,'Move Down'),
  (0xb43214,'Attack Hori'),(0xb42574,'Attack Up'),(0xb42540,'Attack Down'),(0xb43250,'Move Vert')]:
  actual=read(a,64).split(b'\0')[0].decode();assert actual==wanted;strings[hex(a)]=actual
 manifest={'baseline':'Installed Repentance1.7.9b','executable_sha256':EXE_SHA,'dispatch':dispatch,'constants':constants,'strings':strings,'windows':[]}
 for name,a,b in [('controller',0x51afa0,0x51ddf3),('axis_random_walk',0x7a51e0,0x7a617d),
  ('boss_projectiles',0x6a3420,0x6a3970),('orbit',0x634eb5,0x6351e1),('acceleration',0x635d8d,0x635e50),
  ('projectile_init',0x62f1b0,0x62f300),('projectile_update_entry',0x62f6f0,0x62f81b),('projectile_params',0x430d70,0x430ef9),
  ('vector_helpers',0x9624e0,0x962cf0),('base_movement',0x686406,0x68649a),
  ('fire_projectiles',0x6a1a20,0x6a33ec)]:
  blob=read(a,b-a);data=('\n'.join(f'{x.address:08x} {x.mnemonic} {x.op_str}' for x in md.disasm(blob,a))+'\n').encode()
  path=OUT/'source'/(name+'.asm');save(path,data)
  manifest['windows'].append({'path':str(path.relative_to(ROOT)),'start':hex(a),'end':hex(b),'raw_sha256':sha(blob),'sha256':sha(data)})
 save(OUT/'source/manifest.json',(json.dumps(manifest,indent=2)+'\n').encode())
 spec=importlib.util.spec_from_file_location('archive_helpers',ROOT/'scripts/isaac-reference/extract-hornfel-animations.py')
 helper=importlib.util.module_from_spec(spec);spec.loader.exec_module(helper)
 pinned=json.loads((ROOT/'reference/isaac-repentance-1.7.9b/manifests/source-manifest.json').read_text())
 names=['031.000_spity.anm2','031.001_ultra spitty.anm2','243.000_conjoined spitty.anm2'];remaining=set(names);files=[];sources=[]
 for archive in ['repentance.a','afterbirthp.a','afterbirth.a']:
  wanted={helper.namehash(prefix+name):(prefix+name,name) for prefix in ['resources-dlc3/gfx/','resources/gfx/'] for name in remaining}
  relative='resources/packed/'+archive
  with (INSTALL/relative).open('rb') as f:
   header=f.read(14);assert header[:8]==b'ARCH000\x02';index,count=struct.unpack_from('<IH',header,8)
   f.seek(index);entries=[struct.unpack('<5I',f.read(20)) for _ in range(count)]
   matches=[(entry,wanted[entry[:2]]) for entry in entries if entry[:2] in wanted]
   if not matches:continue
   f.seek(0);actual=sha(f.read());expected=next(x['sha256'] for x in pinned if x['path']==relative);assert actual==expected
   sources.append({'archive':relative,'sha256':actual,'previously_pinned':True})
   for (_,_,position,length,crc),(source,name) in matches:
    f.seek(position);data=bytearray()
    while True:
     flags,=struct.unpack('<I',f.read(4));size=flags&0x7fffffff
     assert 0<size<=2048 and not(size==1024 and not flags>>31)
     inflater=zlib.decompressobj(-15);data.extend(inflater.decompress(f.read(size)))
     assert not inflater.unused_data and not inflater.unconsumed_tail
     if flags>>31:break
    assert len(data)==length and helper.checksum(data)==crc
    path=OUT/'animations'/name;save(path,data);xml=ET.fromstring(data)
    files.append({'source':source,'archive':relative,'path':str(path.relative_to(ROOT)),'sha256':sha(data),'checksum':hex(crc),
     'info':dict(xml.find('Info').attrib),'events':[dict(e.attrib) for e in xml.findall('./Content/Events/Event')],
     'animations':[{'attributes':dict(a.attrib),'triggers':[dict(t.attrib) for t in a.findall('./Triggers/Trigger')]} for a in xml.findall('./Animations/Animation')]})
    remaining.remove(name)
  if not remaining:break
 assert not remaining,remaining
 save(OUT/'animations/manifest.json',(json.dumps({'baseline':'Installed1.7.9b','scope':'Highest available DLC override before base metadata; source animation files only, no artwork imported.','sources':sources,'files':files},indent=2)+'\n').encode())
 print(json.dumps({'pass':True,'source_windows':len(manifest['windows']),'animations':len(files)}))
if __name__=='__main__':main()
