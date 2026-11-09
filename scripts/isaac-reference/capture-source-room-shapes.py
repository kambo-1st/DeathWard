#!/usr/bin/env python3
"""Read the pinned native room rectangles and chapter STB shape dimensions.
No gameplay/process writes. Table presence is not floor-I eligibility/frequency.
"""
import collections, hashlib, json, struct
from pathlib import Path
import pefile
ROOT=Path(__file__).resolve().parents[2]
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==SHA
pe=pefile.PE(data=raw)
shapes=[]
for shape in range(1,13):
 raw_rects=pe.get_data(0xbc5d60+32*shape-0x400000,32)
 values=struct.unpack('<8i',raw_rects);rects=[values[:4],values[4:]]
 cells={(x,z) for l,t,r,b in rects for x in range(l,r+1) for z in range(t,b+1)}
 shapes.append(dict(shape=shape,rectangles=rects,interior_cells=len(cells),
                    width=max(x for x,z in cells)-min(x for x,z in cells)+1,
                    height=max(z for x,z in cells)-min(z for x,z in cells)+1,
                    table_bytes_sha256=hashlib.sha256(raw_rects).hexdigest()))
libraries=[]
for path in sorted((ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3/rooms').glob('0[123].*.stb')):
 blob=path.read_bytes();offset=8;counts=collections.Counter();positive=collections.Counter()
 assert blob[:4]==b'STB1'
 def take(fmt):
  global offset
  v=struct.unpack_from(fmt,blob,offset);offset+=struct.calcsize(fmt);return v
 for _ in range(struct.unpack_from('<I',blob,4)[0]):
  kind,var,sub,difficulty,n=take('<IIIBH');offset+=n
  weight,width,height,shape,doors,stacks=take('<fBBBBH');offset+=5*doors
  for _ in range(stacks):
   x,y,entries=take('<hhB');offset+=10*entries
  counts[(shape,width,height)]+=1
  if weight>0:positive[(shape,width,height)]+=1
 assert offset==len(blob)
 libraries.append(dict(file=str(path.relative_to(ROOT)),sha256=hashlib.sha256(blob).hexdigest(),
    templates=[dict(shape=s,width=w,height=h,count=n,positive_weight=positive[(s,w,h)]) for (s,w,h),n in sorted(counts.items())]))
out=ROOT/'docs/reports/isaac-first-floor-parity/d02-room-scale/source-shapes.json'
out.write_text(json.dumps(dict(executable_sha256=SHA,table_address='0xbc5d60',
    table_consumer='Native L-room rectangle helper 0x7da8e0 (also called by clamp 0x7cec10)',
    native_cell=40,world_tile=2,shapes=shapes,libraries=libraries,
    limits=['Static native geometry and stored templates; not live traversal of all shapes.',
            'STB dimensions include narrow-room padding; native rectangle masks specify actual floor.',
            'Template presence does not establish floor-I eligibility, weights, door slots or map-generation rules.']),indent=2)+'\n')
print('PASS pinned executable hash, 12 native masks, three complete chapter libraries')
