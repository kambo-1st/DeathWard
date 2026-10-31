#!/usr/bin/env python3
"""Reproduce installed1.7.9b Hardy controller/helper evidence; no imported art."""
import argparse,hashlib,json,struct
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/hardy'
INSTALL=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
def sha(data):return hashlib.sha256(data).hexdigest()
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 def save(path,data):
  if args.check or path.exists():assert path.read_bytes()==data,path
  else:path.parent.mkdir(parents=True,exist_ok=True);path.write_bytes(data)
 raw=INSTALL.read_bytes();assert sha(raw)=='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
 pe=pefile.PE(data=raw);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 assert read(0x69abc0+826-10,1)[0]==161
 assert struct.unpack('<I',read(0x69a7f8+161*4,4))[0]==0x69a10f
 assert struct.unpack('<I',read(0x6a33ec+8*4,4))[0]==0x6a2a49
 manifest={'baseline':'Repentance1.7.9b','executable_sha256':sha(raw),'dispatch':{'type':826,'case':'0x69a10f','controller':'0x4ee860'},'ring_mode8':'0x6a2a49','windows':[],'constants':{}}
 windows=[('controller',0x4ee860,0x4efacf),('aimed_cluster',0x6a3420,0x6a395a),('fire_projectiles',0x6a1a20,0x6a33ec),('projectile_params',0x430d70,0x430ef9),('burst_flag_gate',0x632d79,0x632d99),('burst_four_children',0x63315b,0x63334c),('thrown_rock_actor',0x4e70a0,0x4e7250),('vector_length',0x962a00,0x962a2c),('vector_scale',0x962bb0,0x962bd6),('vector_negate',0x962b20,0x962b4a),('vector_construct',0x9624e0,0x9624ec),('vector_subtract',0x962ac0,0x962ae8),('random_unit',0x659290,0x6592ef),('set_height',0x4424c0,0x4424d4),('set_falling_speed',0x436b70,0x436b84),('set_size',0x4424e0,0x4424f4)]
 for name,a,b in windows:
  blob=read(a,b-a);instructions=list(md.disasm(blob,a));assert instructions[-1].address+instructions[-1].size==b,(name,hex(instructions[-1].address))
  data=('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in instructions)+'\n').encode();path=OUT/'source'/(name+'.asm');save(path,data)
  manifest['windows'].append({'path':str(path.relative_to(ROOT)),'start':hex(a),'end':hex(b),'raw_sha256':sha(blob),'sha256':sha(data)})
 for name,a,v in [('retention',0xb6a5d8,.95),('idle_retention',0xb6a480,.5),('force',0xb6a50c,.7),('launch',0xb6a9c8,20),('slow_speed',0xb6a95c,9),('stop_speed',0xb6a614,1),('hit_brake',0xb6a4c4,.6),('slow_brake',0xb6a560,.8),('shock_range',0xb6aae4,90),('blast_multiplier',0xb6a820,2.5),('child_height',0xb6aeb8,-10),('child_spread',0xb6ab20,120),('third_shot_size',0xb6a670,1.2),('cluster_gravity',0xb6a3c4,.32),('cluster_speed',0xb6a928,7),('cluster_scatter',0xb6a8a0,3.5),('cluster_falling_base',0xb6a8f4,5),('size_low',0xb6a5a4,.9),('size_choice',0xb6a434,.4),('size_jitter',0xb6a274,.05),('burst_falling_width',0xb6a350,.2),('burst_falling_subtract',0xb6a27c,.06)]:
  value=struct.unpack('<f',read(a,4))[0];assert abs(value-v)<1e-5;manifest['constants'][name]={'address':hex(a),'value':value}
 ref=json.loads((ROOT/'docs/research/isaac-mechanics-reference.json').read_text());record=next(r for r in ref['records'] if r.get('key')=='826.0.0')
 save(OUT/'source/record.json',(json.dumps(record,indent=2)+'\n').encode())
 article=ref['articles']['Squirt'];selected={k:article[k] for k in ['title','url','revision_url','revision','timestamp','license','attribution']};selected['section']=next(s for s in article['sections'] if s['heading']=='Hardy')
 save(OUT/'source/wiki.json',(json.dumps(selected,indent=2)+'\n').encode())
 save(OUT/'source/manifest.json',(json.dumps(manifest,indent=2)+'\n').encode())
 print(json.dumps({'pass':True,'windows':len(windows),'constants':len(manifest['constants']),'check':args.check}))
if __name__=='__main__':main()
