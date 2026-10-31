#!/usr/bin/env python3
"""Pin installed Rock Spider/Hardy controllers and animation metadata, without game art."""
import argparse,hashlib,importlib.util,json,struct,xml.etree.ElementTree as ET,zlib
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/rock-spiders'
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
 for t,index_expected,case_expected,controller in [(33,19,0x699cd7,0x6a7ae0),(818,154,0x69a0af,0x4e7250),(826,161,0x69a10f,0x4ee860)]:
  index=read(0x69abc0+t-10,1)[0];case=struct.unpack('<I',read(0x69a7f8+4*index,4))[0]
  assert index==index_expected and case==case_expected
  assert any(i.mnemonic=='call' and i.op_str==hex(controller) for i in md.disasm(read(case,12),case))
  dispatch.append({'type':t,'index':index,'case':hex(case),'controller':hex(controller)})
 constants={}
 for name,a,value in [('move_retention',0xb6a4c4,.6),('normal_force',0xb6a864,3),('tinted_force',0xb6a8f8,5.1),('coal_force_multiplier',0xb6a754,1.8),('singe_coal_force_multiplier',0xb6a70c,1.6),('bounce',0xb6ae08,-.3),('landing_retention',0xb6a560,.8),('gravity',0xb6a480,.5),('wake_speed',0xb6a7b0,2),('wake_vertical',0xb6a4c4,.6),('air_entity_collision',0xb6af28,-50),('air_grid_collision',0xb6ae88,-4),('hot_coal_impulse',0xb6ae44,-1),('coal_death_threshold',0xb6a6f0,1.5),('wander_distance',0xb6a9c8,20),('chase_spread',0xb6aa0c,30),('hardy_move_retention',0xb6a5d8,.95),('hardy_force',0xb6a50c,.7)]:
  actual=struct.unpack('<f',read(a,4))[0];assert abs(actual-value)<1e-5,(name,actual)
  constants[name]={'address':hex(a),'value':actual}
 strings={hex(a):read(a,64).split(b'\0')[0].decode() for a in [0xb42a58,0xb40360,0xb41264,0xb3fd8c,0xb40c58,0xb42ae8]}
 states={}
 for name,index,table in [('rock_spider',0x4e82c4,0x4e82b0),('hardy',0x4efae8,0x4efad0)]:
  states[name]={str(i):hex(struct.unpack('<I',read(table+4*read(index+i,1)[0],4))[0]) for i in range(17)}
 manifest={'baseline':'Installed Repentance1.7.9b','executable_sha256':EXE_SHA,'dispatch':dispatch,
  'constants':constants,'strings':strings,'states':states,'windows':[]}
 for name,a,b in [('rock_spider_controller',0x4e7250,0x4e82af),('hardy_controller',0x4ee860,0x4efacf),('rock_projectile_factory',0x4e70a0,0x4e7250),('fireplace_coal_dispatch',0x6a7ae0,0x6a7b92)]:
  blob=read(a,b-a);instructions=list(md.disasm(blob,a));assert instructions[-1].address+instructions[-1].size==b
  data=('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in instructions)+'\n').encode()
  path=OUT/'source'/(name+'.asm');save(path,data)
  manifest['windows'].append({'path':str(path.relative_to(ROOT)),'start':hex(a),'end':hex(b),'raw_sha256':sha(blob),'sha256':sha(data)})
 save(OUT/'source/manifest.json',(json.dumps(manifest,indent=2)+'\n').encode())
 spec=importlib.util.spec_from_file_location('archive_helpers',ROOT/'scripts/isaac-reference/extract-hornfel-animations.py')
 helper=importlib.util.module_from_spec(spec);spec.loader.exec_module(helper)
 pinned=json.loads((ROOT/'reference/isaac-repentance-1.7.9b/manifests/source-manifest.json').read_text())
 names=[f'818.{v:03d}_{name} {i}.anm2' for v,name in [(0,'rock spider'),(1,'tinted rock spider'),(2,'coal spider')] for i in range(1,4)]+[f'818.002_coal {i}.anm2' for i in range(1,4)]+['826.000_hardy.anm2'];remaining=set(names);files=[];sources=[]
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
