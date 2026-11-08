#!/usr/bin/env python3
"""Check installed native grid-coordinate and room-clamp arithmetic against a live room snapshot.

The live snapshot is collected separately with VM_READ only. This fixture supplies
that room's stored fields; it does not execute full room generation/initialization.
"""
import argparse,csv,hashlib,importlib.util,io,json,struct
from pathlib import Path
import capstone,pefile
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EBP,UC_X86_REG_ESP,UC_X86_REG_XMM1,UC_X86_REG_XMM2,UC_X86_REG_XMM3
spec=importlib.util.spec_from_file_location('motion',Path(__file__).with_name('analyze-player-motion.py'));M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)
OUT=M.ROOT/'docs/reports/isaac-first-floor-parity/room-scale-timing'
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');a=ap.parse_args()
 raw=M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==M.SHA
 pe=pefile.PE(data=raw);n=M.NativeMotion(pe);u=n.u;snapshot=json.loads((OUT/'live-room-snapshot.json').read_text());assert snapshot['shape']==1
 width,height=snapshot['grid_width'],snapshot['grid_height'];assert (width,height)==(15,9)
 stride=struct.unpack('<f',pe.get_data(0xb6aa3c-0x400000,4))[0];origin_y=struct.unpack('<f',pe.get_data(0xb6ab20-0x400000,4))[0];assert stride==40 and origin_y==120
 def save(name,data):
  p=OUT/name
  if a.check:assert p.read_bytes()==data,name
  else:p.write_bytes(data)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
 for name,start,end in [('grid-position',0x7a4687,0x7a46b5),('room-clamp',0x7cec10,0x7cef13)]:
  blob=pe.get_data(start-0x400000,end-start);listing='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(blob,start))+'\n';save(name+'.asm',listing.encode());windows.append({'name':name,'start':hex(start),'end':hex(end),'raw_sha256':hashlib.sha256(blob).hexdigest()})
 def xmm(reg):return struct.unpack('<f',struct.pack('<I',u.reg_read(reg)&0xffffffff))[0]
 grid=[]
 for index in range(width*height):
  u.reg_write(UC_X86_REG_EAX,index);u.reg_write(UC_X86_REG_EBP,n.ebp);n.write_float(n.ebp-0x60,0);u.mem_write(n.ebp-0x60,struct.pack('<i',width));n.run(0x7a4687,0x7a46b5)
  x,y=xmm(UC_X86_REG_XMM2),xmm(UC_X86_REG_XMM1);assert x==40+40*(index%width) and y==120+40*(index//width);grid.append([index,index%width,index//width,x,y])
 room=n.PLAYER+0x4000;desc=n.PLAYER+0x6000;data=n.PLAYER+0x7000
 u.mem_write(room+4,struct.pack('<I',desc));u.mem_write(desc+0x10,struct.pack('<I',data));u.mem_write(data+0x48,struct.pack('<I',1))
 for offset,key in [(0x14,'left'),(0x18,'top'),(0x1c,'right'),(0x20,'bottom')]:n.write_float(room+offset,snapshot[key])
 points=[(-100,-100),(0,0),(60,140),(320,280),(580,420),(1000,1000),(40,500)];clamps=[]
 for margin in [0,10.5]:
  for x,y in points:
   sp=n.STACK+0x9000;out=n.STACK+0x200;at=n.STACK+0x300
   u.mem_write(sp,struct.pack('<IIIfff',n.STOP,out,at,margin,margin,margin));n.write_float(at,x);n.write_float(at+4,y);n.xmm(UC_X86_REG_XMM3,margin);u.reg_write(UC_X86_REG_ECX,room);u.reg_write(UC_X86_REG_ESP,sp);n.run(0x7cec10,n.STOP)
   actual=(n.read_float(out),n.read_float(out+4));expected=(max(snapshot['left']+margin,min(snapshot['right']-margin,x)),max(snapshot['top']+margin,min(snapshot['bottom']-margin,y)));assert actual==expected,(actual,expected);clamps.append([margin,x,y,*actual])
 def table(name,header,rows):
  text=io.StringIO(newline='');w=csv.writer(text,lineterminator='\n');w.writerow(header);w.writerows(rows);save(name,text.getvalue().encode())
 table('native-grid.csv',['index','column','row','native_x','native_y'],grid);table('native-clamp.csv',['margin','input_x','input_y','output_x','output_y'],clamps)
 interior=[r for r in grid if 1<=r[1]<width-1 and 1<=r[2]<height-1];bounds=[min(r[3] for r in interior)-20,min(r[4] for r in interior)-20,max(r[3] for r in interior)+20,max(r[4] for r in interior)+20];observed=[snapshot[k] for k in ['left','top','right','bottom']];assert bounds==observed
 manifest={'exe_sha256':M.SHA,'live_snapshot_sha256':hashlib.sha256((OUT/'live-room-snapshot.json').read_bytes()).hexdigest(),'shape':1,'grid_width':width,'grid_height':height,'cell_spacing':stride,'grid_origin':[40,origin_y],'stored_interior_bounds':observed,'interior_size':[bounds[2]-bounds[0],bounds[3]-bounds[1]],'interior_cells':[width-2,height-2],'grid_positions_executed':len(grid),'clamp_cases_executed':len(clamps),'windows':windows,'method':'Original native grid path coordinate arithmetic and full ordinary room clamp; real live room fields supplied from read-only snapshot; no stubbed helpers or patched instructions','not_verified':['Full room generation and all room shapes','Player/entity wall radius and corner collision','Active gameplay elapsed movement timing','DeathWard spatial rollout']}
 save('geometry-manifest.json',(json.dumps(manifest,indent=2)+'\n').encode());print(json.dumps({'pass':True,'check':a.check,'interior_size':manifest['interior_size'],'grid_positions':len(grid),'clamp_cases':len(clamps)}))
if __name__=='__main__':main()
