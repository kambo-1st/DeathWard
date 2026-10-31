#!/usr/bin/env python3
"""Preserve baseline cart attachment and track-junction evidence, read-only."""
import hashlib,json,re,struct
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2]
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SOURCE=ROOT/'reference/isaac-mechanics-study/code/TeamREPENTOGON__REPENTOGON/348e5d0ea277760fc87af420d88e2c7909c9167e/libzhl/functions/EntityNPC.zhl'
OUT=ROOT/'docs/reports/isaac-enemy-port/hornfel_controller/native'
BASELINE='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def main():
 data=EXE.read_bytes();assert hashlib.sha256(data).hexdigest()==BASELINE
 pe=pefile.PE(data=data);base=pe.OPTIONAL_HEADER.ImageBase;source=SOURCE.read_text();anchors={}
 for name in ['MinecartUpdateChild','MinecartBreak','SetMinecartPosVel']:
  sig=re.search(r'"([0-9a-f?]+)":\s*[^;\n]*Entity_NPC::'+name+r'\(',source)[1]
  pattern=b''.join(b'.' if x=='??' else re.escape(bytes.fromhex(x)) for x in re.findall('..',sig))
  hits=list(re.finditer(pattern,data,re.S));assert len(hits)==1,(name,len(hits))
  anchors[name]={'address':hex(base+pe.get_rva_from_offset(hits[0].start())),'signature':sig}
 windows=[('cart_movement',0x4bb2b0,0x4bb867),('cart_frame',0x4bb870,0x4bba36),
 ('cart_ai_candidate',0x4bba40,0x4bc03c),('cart_break',0x4bc040,0x4bc1e0),
 ('cart_position_velocity',0x4bc1e0,0x4bc29a),('cart_attach',0x4bc2d0,0x4bc373),
 ('rail_projection',0x939120,0x9395a1)]
 decoder=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);decoder.detail=True;OUT.mkdir(parents=True,exist_ok=True);records=[]
 for name,start,end in windows:
  raw=pe.get_data(start-base,end-start);lines=['; Repentance1.7.9b bounded native evidence. Candidate names are interpretations, not exported symbols.']
  for i in decoder.disasm(raw,start):
   notes=[]
   for o in i.operands:
    if o.type==capstone.x86.X86_OP_MEM and not o.mem.base and not o.mem.index and base<=o.mem.disp<0xc00000:
     value=pe.get_data(o.mem.disp-base,4)
     if len(value)==4:notes.append(f'f32={struct.unpack("<f",value)[0]:.9g}')
   lines.append(f'{i.address:08x} {i.mnemonic} {i.op_str}'+(' ; '+', '.join(notes) if notes else ''))
  path=OUT/(name+'.asm');path.write_text('\n'.join(lines)+'\n')
  records.append({'name':name,'start':hex(start),'end_exclusive':hex(end),'raw_sha256':hashlib.sha256(raw).hexdigest(),'artifact':str(path.relative_to(ROOT)),'artifact_sha256':hashlib.sha256(path.read_bytes()).hexdigest()})
 geometry=[]
 for variant in range(11):
  raw=pe.get_data(0xbc76f0-base+variant*68,68);count=struct.unpack('<i',raw[:4])[0]
  geometry.append({'variant':variant,'count':count,'points':list(struct.iter_unpack('<ff',raw[4:]))[:count]})
 report={'baseline':'Repentance1.7.9b','exe_sha256':BASELINE,'signature_source':str(SOURCE.relative_to(ROOT)),'signature_sha256':hashlib.sha256(SOURCE.read_bytes()).hexdigest(),'anchors':anchors,'windows':records,'rail_table_address':'0xbc76f0','rail_table_stride':68,'rail_cell_native_units':40,'rail_geometry':geometry,
 'findings':[
 {'claim':'MinecartUpdateChild clears prior rider/cart references and binds both directions; cart child offset0x318 and rider cart offset0x32c.','evidence':'0x4bc2d7-0x4bc365'},
 {'claim':'SetMinecartPosVel updates position, current grid index, velocity and stored rail direction.','evidence':'0x4bc1fb-0x4bc28e'},
 {'claim':'Movement projects onto rail geometry through0x939120. It samples movement in bounded substeps, queries the current tile and reverses the returned direction when the helper endpoint flag is set.','evidence':'0x4bb550-0x4bb665'},
 {'claim':'Variants7/8/9/10 are endpoint segments. At along>=1 and positive incoming dot tangent, the helper sets its endpoint flag. This supports reversal when approached into the cap.','evidence':'0x9391c7-0x9391df;0x939504-0x93953c'},
 {'claim':'Vertical cap9 starts at(0,13) and ends at(0,-4);10 starts at(0,-13) and ends at(0,4). Their inward ports are south and north respectively.','evidence':'rail table at0xbc76f0'},
 {'claim':'The projection scores candidate segments using distance and an incoming-direction term. Straight crossing traversal is supported for centered cardinal entry, but arbitrary off-track/collision approach behavior is not claimed by a compiled route.','evidence':'0x93938b-0x9394d1;crossing tablevariant6'}],
 'limitations':['Only three API signatures uniquely identify names; other function names follow local call/prologue context.','The runtime curved physical path remains a declared3D adaptation; it is not a reimplementation of every native projection/collision detail.','Door scheduling, bomb fuse/tick semantics, passengers and all boss attack states are not resolved by this cart excerpt.']}
 (OUT/'manifest.json').write_text(json.dumps(report,indent=2)+'\n');print('Verified3 cart signatures; preserved7 windows and11 rail tile geometries')
if __name__=='__main__':main()
