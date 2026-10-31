#!/usr/bin/env python3
"""Preserve installed Mr. Maw body/head/neck source and animation metadata without runtime art."""
import argparse,hashlib,importlib.util,json,struct,xml.etree.ElementTree as ET,zlib
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/mr-maw'
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
 for t in [35]:
  i=read(0x69abc0+t-10,1)[0];case=struct.unpack('<I',read(0x69a7f8+4*i,4))[0]
  assert i==20 and case==0x6999f8
  instructions=list(md.disasm(read(case,20),case));assert any(x.mnemonic=='call' and x.op_str=='0x506130' for x in instructions)
  dispatch.append({'type':t,'index':i,'case':hex(case),'controller':'0x506130'})
 constants={}
 for name,a,value in [('normal_pursuit',0xb6a4c4,.6),('red_pursuit',0xb6a560,.8),
  ('body_throw_retention',0xb6a50c,.7),('head_prediction',0xb6a864,3),('range_squared',0xb6ad48,16900),
  ('launch_speed',0xb6a9a0,14),('return_distance',0xb6a8f4,5),('timer_minimum',0xb6af0c,-30),
  ('spring_timer_divisor',0xb6aa4c,45),('spring_base',0xb6a6c8,1.4),('spring_subtract',0xb6a50c,.7),
  ('head_retention_base',0xb6a5a4,.9),('head_retention_timer_scale',0xb6a1e4,.0028),
  ('neck_last_slot',0xb6a928,7),('neck_fraction',0xb6a2ec,.125),('neck_center',0xb6a8cc,4),
  ('neck_sag_span',0xb6aafc,100),('neck_sag_height',0xb6a9b0,16),('neck_y_offset',0xb6aa14,31)]:
  actual=struct.unpack('<f',read(a,4))[0];assert abs(actual-value)<1e-5
  constants[name]={'address':hex(a),'value':actual}
 strings={}
 for a,wanted in [(0xb42f30,'MrMawBodyHori'),(0xb42f50,'MrMawBodyVert')]:
  actual=read(a,64).split(b'\0')[0].decode();assert actual==wanted;strings[hex(a)]=actual
 manifest={'baseline':'Installed Repentance1.7.9b','executable_sha256':EXE_SHA,'dispatch':dispatch,'constants':constants,'strings':strings,'windows':[]}
 for name,a,b in [('controller',0x506130,0x507258),('morph',0x697c60,0x697e21),
  ('pathfinder',0x7a3650,0x7a482c),('pursuit_target',0x695a30,0x695dfb),
  ('path_force',0x7a7610,0x7a7a00),('base_movement',0x686406,0x68649a),
  ('global_interval',0x684790,0x6847db)]:
  blob=read(a,b-a);data=('\n'.join(f'{x.address:08x} {x.mnemonic} {x.op_str}' for x in md.disasm(blob,a))+'\n').encode()
  path=OUT/'source'/(name+'.asm');save(path,data)
  manifest['windows'].append({'path':str(path.relative_to(ROOT)),'start':hex(a),'end':hex(b),'raw_sha256':sha(blob),'sha256':sha(data)})
 save(OUT/'source/manifest.json',(json.dumps(manifest,indent=2)+'\n').encode())
 spec=importlib.util.spec_from_file_location('archive_helpers',ROOT/'scripts/isaac-reference/extract-hornfel-animations.py')
 helper=importlib.util.module_from_spec(spec);spec.loader.exec_module(helper)
 pinned=json.loads((ROOT/'reference/isaac-repentance-1.7.9b/manifests/source-manifest.json').read_text())
 names=['035.000_Mr. Maw Body.anm2','035.001_Mr. Maw Head.anm2','035.002_Mr. Red Maw Body.anm2','035.003_Mr. Red Maw Head.anm2','035.010_Mr. Maw Neck.anm2'];remaining=set(names);files=[];sources=[]
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
