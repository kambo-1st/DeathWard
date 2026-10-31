#!/usr/bin/env python3
"""Preserve installed ordinary Brain source and animation metadata without runtime art."""
import argparse,hashlib,importlib.util,json,struct,xml.etree.ElementTree as ET,zlib
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/brain'
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
 for t in [32]:
  i=read(0x69abc0+t-10,1)[0];case=struct.unpack('<I',read(0x69a7f8+4*i,4))[0]
  assert i==18 and case==0x699e4b
  instructions=list(md.disasm(read(case,20),case));assert any(x.mnemonic=='call' and x.op_str=='0x500140' for x in instructions)
  dispatch.append({'type':t,'index':i,'case':hex(case),'controller':'0x500140'})
 constants={}
 for name,a,value in [('walk_force_immediate',0x5008f5,.75),('x_retention',0xb6a588,.85),
  ('z_retention_and_charge_friction',0xb6a560,.8),('grid_spacing',0xb6aa3c,40),
  ('charge_alignment',0xb6a9c8,20),('charge_range',0xb6aba8,200),('target_prediction',0xb6a9b0,16),
  ('charge_grid_correction',0xb6a2cc,.1),('charge_grid_old',0xb6a5a4,.9),
  ('creep_sparse_interval',0xb6a9e8,24),('creep_dense_interval',0xb6a98c,12),
  ('extra_creep_speed_squared',0xb6a95c,9),('creep_base_radius',0xb6a9c8,20),
  ('creep_damage',0xb6a614,1),('creep_fade_scale',0xb6a604,.98),('arrival',0xb6a8f4,5),('stuck_speed',0xb6a4c4,.6)]:
  actual=struct.unpack('<f',read(a,4))[0];assert abs(actual-value)<1e-5
  constants[name]={'address':hex(a),'value':actual}
 strings={}
 for a,wanted in [(0xb41264,'Walk')]:
  actual=read(a,64).split(b'\0')[0].decode();assert actual==wanted;strings[hex(a)]=actual
 manifest={'baseline':'Installed Repentance1.7.9b','executable_sha256':EXE_SHA,'dispatch':dispatch,'constants':constants,'strings':strings,'windows':[]}
 assert struct.unpack('<I',read(0x5e9214+4*(22-1),4))[0]==0x5d17fc
 for name,a,b in [('controller',0x500140,0x500f98),('axis_random_walk',0x7a51e0,0x7a617d),
  ('base_movement',0x686406,0x68649a),('global_interval',0x684790,0x6847db),
  ('actor_interval',0x6847e0,0x684852),('alive_enemy_count',0x6ad7a0,0x6ad86d),
  ('effect_init',0x5b79c0,0x5bbf98),('creep_update',0x5d17fc,0x5d32ec),
  ('effect_timer_epilogue',0x5e9122,0x5e9168),('grid_position',0x7a6e20,0x7a6e9e)]:
  blob=read(a,b-a);data=('\n'.join(f'{x.address:08x} {x.mnemonic} {x.op_str}' for x in md.disasm(blob,a))+'\n').encode()
  path=OUT/'source'/(name+'.asm');save(path,data)
  manifest['windows'].append({'path':str(path.relative_to(ROOT)),'start':hex(a),'end':hex(b),'raw_sha256':sha(blob),'sha256':sha(data)})
 save(OUT/'source/manifest.json',(json.dumps(manifest,indent=2)+'\n').encode())
 spec=importlib.util.spec_from_file_location('archive_helpers',ROOT/'scripts/isaac-reference/extract-hornfel-animations.py')
 helper=importlib.util.module_from_spec(spec);spec.loader.exec_module(helper)
 pinned=json.loads((ROOT/'reference/isaac-repentance-1.7.9b/manifests/source-manifest.json').read_text())
 names=['032.000_Brain.anm2'];remaining=set(names);files=[];sources=[]
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
