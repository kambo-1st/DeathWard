#!/usr/bin/env python3
"""Read-only extraction of one pinned ordinary Basement formation; no process writes."""
import hashlib, json, struct
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
path=ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3/rooms/01.basement.stb'
data=path.read_bytes()
sha='524406fcb10c6275995292c0bd024cfc43d3d30c32b233e55d4d514573d963b0'
assert hashlib.sha256(data).hexdigest()==sha
magic,count=struct.unpack_from('<4sI',data);assert magic==b'STB1'
offset=8;selected=[]
def take(fmt):
 global offset
 result=struct.unpack_from(fmt,data,offset);offset+=struct.calcsize(fmt);return result
for index in range(count):
 kind,variant,subtype,difficulty,n=take('<IIIBH');name=data[offset:offset+n].decode();offset+=n
 weight,width,height,shape,door_count,stack_count=take('<fBBBBH')
 doors=[dict(zip(('x','y','enabled'),take('<hh?'))) for _ in range(door_count)]
 spawns=[]
 for _ in range(stack_count):
  x,y,entries=take('<hhB')
  spawns.append(dict(x=x,y=y,entries=[dict(zip(('type','variant','subtype','weight'),take('<HHHf'))) for _ in range(entries)]))
 if (kind,variant,subtype)==(1,47,0):
  selected.append(dict(index=index,type=kind,variant=variant,subtype=subtype,name=name,difficulty=difficulty,weight=weight,width=width,height=height,shape=shape,doors=doors,spawns=spawns))
assert offset==len(data) and len(selected)==1
room=selected[0]
assert (room['difficulty'],room['weight'],room['width'],room['height'],room['shape'])==(1,1,13,7,1)
assert [(s['x'],s['y']) for s in room['spawns']]==[(5,3),(7,3)]
assert all(s['entries']==[dict(type=10,variant=1,subtype=0,weight=1)] for s in room['spawns'])
assert all(d['enabled'] for d in room['doors']) and len(room['doors'])==4
out=ROOT/'docs/reports/isaac-first-floor-parity/d08-source-room/source-template.json'
out.write_text(json.dumps(dict(source='The Binding of Isaac: Repentance 1.7.9b',file=str(path.relative_to(ROOT)),sha256=sha,parsed_templates=count,fully_consumed_bytes=len(data),room=room,
 evidence='Positive-weight, difficulty-1, standard normal-room entry in the installed Basement library; no extra cover, props, pickups or hazards in the spawn stacks.',
 limits=['Not evidence of native random floor selection frequency, unlock filters or a live seed capture.',
 'Four allowed door slots are capabilities; actual connected doors depend on the floor graph.',
 'DW guarantees this formation in one opening-floor room; that selection policy, custom canyon shape/scale, NPC RNG and current rewards are adaptations.']),indent=2)+'\n')
print(f'PASS pinned STB: {count} templates, {len(data)} bytes; normal 1.47.0, 13x7, two ordinary Gapers, empty cover')
