#!/usr/bin/env python3
"""Pin installed Guts-family controller and animation metadata, without game art."""
import argparse,hashlib,importlib.util,json,struct,xml.etree.ElementTree as ET,zlib
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/guts'
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
 for t in [40,862]:
  index=read(0x69abc0+t-10,1)[0];case=struct.unpack('<I',read(0x69a7f8+4*index,4))[0]
  assert index==24 and case==0x69a26b
  assert any(i.mnemonic=='call' and i.op_str=='0x5031b0' for i in md.disasm(read(case,12),case))
  dispatch.append({'type':t,'index':index,'case':hex(case),'controller':'0x5031b0'})
 constants={}
 for name,a,value in [('grid',0xb6aa3c,40),('damping',0xb6a4c4,.6),('force',0xb6a864,3),
  ('scarred_force',0xb6a87c,3.3),('slog_force',0xb6a81c,2.45),('arrival',0xb6a974,10),
  ('stuck_distance',0xb6a7b0,2),('stuck_seconds',0xb6a38c,.25),('cross_axis_pull',0xb6a434,.4),
  ('prediction_frames',0xb6a8f4,5),('charge_brake',0xb6a2cc,.1),('recovery_acceleration',0xb6a274,.05)]:
  actual=struct.unpack('<f',read(a,4))[0];assert abs(actual-value)<1e-5,(name,actual)
  constants[name]={'address':hex(a),'value':actual}
 directions=list(struct.unpack('<8i',read(0xb42db0,32)));assert directions==[0,1,1,0,0,-1,-1,0]
 strings={}
 for a,wanted in [(0xb41458,'Roll'),(0xb40520,'ChargeStart'),(0xb414b8,'ChargeLoop'),(0xb42f18,'HitVert'),(0xb42f48,'HitHori')]:
  actual=read(a,64).split(b'\0')[0].decode();assert actual==wanted;strings[hex(a)]=actual
 manifest={'baseline':'Installed Repentance1.7.9b','executable_sha256':EXE_SHA,'dispatch':dispatch,
  'constants':constants,'directions':directions,'strings':strings,'windows':[]}
 for name,a,b in [('controller',0x5031b0,0x5054da),('grid_test',0x502e00,0x502e97),
  ('alignment',0x502ea0,0x503074),('target_filter',0x503080,0x50319a)]:
  blob=read(a,b-a);instructions=list(md.disasm(blob,a));assert instructions[-1].address+instructions[-1].size==b
  data=('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in instructions)+'\n').encode()
  path=OUT/'source'/(name+'.asm');save(path,data)
  manifest['windows'].append({'path':str(path.relative_to(ROOT)),'start':hex(a),'end':hex(b),'raw_sha256':sha(blob),'sha256':sha(data)})
 save(OUT/'source/manifest.json',(json.dumps(manifest,indent=2)+'\n').encode())
 spec=importlib.util.spec_from_file_location('archive_helpers',ROOT/'scripts/isaac-reference/extract-hornfel-animations.py')
 helper=importlib.util.module_from_spec(spec);spec.loader.exec_module(helper)
 pinned=json.loads((ROOT/'reference/isaac-repentance-1.7.9b/manifests/source-manifest.json').read_text())
 names=['040.000_Guts.anm2','040.001_Scarred Guts.anm2','040.002_Slog.anm2'];remaining=set(names);files=[];sources=[]
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
