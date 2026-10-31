import hashlib,json,struct,zlib,importlib.util
from pathlib import Path
import xml.etree.ElementTree as ET
spec=importlib.util.spec_from_file_location('method','scripts/isaac-reference/extract-hornfel-animations.py');m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
OUT=Path('docs/reports/isaac-enemy-port/mulligans/animations');OUT.mkdir(parents=True,exist_ok=True)
assert not (OUT/'manifest.json').exists()
wanted={m.namehash(n):n for n in ['resources/gfx/016.000_Mulligan.anm2', 'resources/gfx/016.001_Mulligoon.anm2', 'resources/gfx/016.002_Mulliboom.anm2']};records=[];sources=[]
manifest=json.loads((m.REFERENCE/'manifests/source-manifest.json').read_text())
for name in ['repentance','afterbirthp','afterbirth','animations']:
 if not wanted:break
 archive='resources/packed/'+name+'.a';expected=next((r for r in manifest if r['path']==archive),None)
 with (m.INSTALL/archive).open('rb') as f:
  header=f.read(14);assert header[:8]==b'ARCH000\x02';index,count=struct.unpack_from('<IH',header,8);f.seek(index)
  entries=[struct.unpack('<5I',f.read(20)) for _ in range(count)];found=[e for e in entries if e[:2] in wanted]
  if not found:continue
  f.seek(0);hasher=hashlib.sha256()
  for chunk in iter(lambda:f.read(1024*1024),b''):hasher.update(chunk)
  assert expected is None or hasher.hexdigest()==expected['sha256'];sources.append({'archive':archive,'sha256':hasher.hexdigest(),'previously_pinned':expected is not None})
  for a,b,position,length,crc in found:
   source=wanted.pop((a,b));f.seek(position);data=bytearray()
   while True:
    flags,=struct.unpack('<I',f.read(4));size=flags&0x7fffffff;assert 0<size<=2048
    inflater=zlib.decompressobj(-15);data.extend(inflater.decompress(f.read(size)));assert not inflater.unused_data and not inflater.unconsumed_tail
    if flags>>31:break
   assert len(data)==length and m.checksum(data)==crc
   p=OUT/Path(source).name;assert not p.exists() or p.read_bytes()==data;p.write_bytes(data);xml=ET.fromstring(data)
   records.append({'source':source,'archive':archive,'path':str(p),'sha256':hashlib.sha256(data).hexdigest(),'checksum':hex(crc),'info':dict(xml.find('Info').attrib),'events':[dict(e.attrib) for e in xml.findall('./Content/Events/Event')],'animations':[{'attributes':dict(a.attrib),'triggers':[dict(t.attrib) for t in a.findall('./Triggers/Trigger')]} for a in xml.findall('./Animations/Animation')]})
assert not wanted,wanted
(OUT/'manifest.json').write_text(json.dumps({'baseline':'Installed1.7.9b','scope':'Animation/event metadata only; no sprite artwork imported. DLC override searched before base animation archive.','sources':sources,'files':records},indent=2)+'\n')
print(json.dumps(records,indent=2))
