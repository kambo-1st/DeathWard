#!/usr/bin/env python3
"""Pin installed Knight-family controllers and animation metadata, without game art."""
import argparse,hashlib,importlib.util,json,struct,xml.etree.ElementTree as ET,zlib
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/knights'
INSTALL=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth')
EXE_SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def sha(data):return hashlib.sha256(data).hexdigest()
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 def save(path,data):
  if args.check or path.exists():assert path.read_bytes()==data,path
  else:path.parent.mkdir(parents=True,exist_ok=True);path.write_bytes(data)
 raw=(INSTALL/'isaac-ng.exe').read_bytes();assert sha(raw)==EXE_SHA
 pe=pefile.PE(data=raw);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 dispatch=[]
 for t,index_expected,case_expected,controller in [(41,25,0x699d07,0x5014f0),(840,16,0x69a19f,0x514450)]:
  index=read(0x69abc0+t-10,1)[0];case=struct.unpack('<I',read(0x69a7f8+4*index,4))[0]
  assert index==index_expected and case==case_expected
  assert any(i.mnemonic=='call' and i.op_str==hex(controller) for i in md.disasm(read(case,12),case))
  dispatch.append({'type':t,'index':index,'case':hex(case),'controller':hex(controller)})
 constants={}
 for name,a,value in [('grid',0xb6aa3c,40),('retention',0xb6a560,.8),('brainless_retention',0xb6a594,.88),
  ('walk_force',0xb6a53c,.75),('selfless_walk_force',0xb6a680,1.25),('loose_walk_force',0xb6a4c4,.6),
  ('black_walk_force',0xb6a4e0,.66),('charge_force',0xb6a614,1),('selfless_charge_multiplier',0xb6a710,1.65),
  ('black_initial_charge',0xb6a50c,.7),('black_charge_acceleration',0xb6a290,.07),('black_charge_max',0xb6a8cc,4),
  ('prediction_max_frames',0xb6a9b0,16),('charge_range',0xb6aba8,200),('alignment_tolerance',0xb6a9c8,20),
  ('charge_cross_pull',0xb6a2cc,.1),('impact_min_speed',0xb6a940,8),('impact_alignment',0xb6a5a4,.9),
  ('pon_spawn_offset',0xb6a974,10),('impact_lift_speed',0xb6a8f4,5),('impact_gravity',0xb6a64c,1.1)]:
  actual=struct.unpack('<f',read(a,4))[0];assert abs(actual-value)<1e-5,(name,actual)
  constants[name]={'address':hex(a),'value':actual}
 strings={}
 for a,wanted in [(0xb406e4,'Up'),(0xb406f0,'Down'),(0xb42f28,'Hori')]:
  actual=read(a,64).split(b'\0')[0].decode();assert actual==wanted;strings[hex(a)]=actual
 manifest={'baseline':'Installed Repentance1.7.9b','executable_sha256':EXE_SHA,'dispatch':dispatch,
  'constants':constants,'strings':strings,'windows':[]}
 for name,a,b in [('knight_controller',0x5014f0,0x502de7),('pon_shared_hopper',0x514450,0x516dda),
  ('mask_damage_direction',0x6aa830,0x6aabd9),('grid_wander',0x7a51e0,0x7a617d),
  ('black_tear_reflection',0x6a3a39,0x6a3da4),('tear_collision',0x64dcd0,0x6500d0)]:
  blob=read(a,b-a);instructions=list(md.disasm(blob,a));assert instructions[-1].address+instructions[-1].size==b
  data=('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in instructions)+'\n').encode()
  path=OUT/'source'/(name+'.asm');save(path,data)
  manifest['windows'].append({'path':str(path.relative_to(ROOT)),'start':hex(a),'end':hex(b),'raw_sha256':sha(blob),'sha256':sha(data)})
 save(OUT/'source/manifest.json',(json.dumps(manifest,indent=2)+'\n').encode())
 spec=importlib.util.spec_from_file_location('archive_helpers',ROOT/'scripts/isaac-reference/extract-hornfel-animations.py')
 helper=importlib.util.module_from_spec(spec);spec.loader.exec_module(helper)
 pinned=json.loads((ROOT/'reference/isaac-repentance-1.7.9b/manifests/source-manifest.json').read_text())
 names=['041.000_Knight.anm2','041.001_Selfless Knight.anm2','041.002_loose knight.anm2','041.003_empty knight.anm2','041.004_black knight.anm2','840.000_pon.anm2'];remaining=set(names);files=[];sources=[]
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
 print(json.dumps({'pass':True,'windows':len(manifest['windows']),'animations':len(files),'check':args.check}))
if __name__=='__main__':main()
