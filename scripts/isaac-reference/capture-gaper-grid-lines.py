#!/usr/bin/env python3
"""Execute pinned ordinary grid collision lookup and CheckLine mode0.

Masks/entity collision fields are supplied. This does not execute generation
of grid costs from native room props, special statuses or the full pathfinder.
"""
import argparse,csv,hashlib,importlib.util,io,json,struct
from pathlib import Path
import capstone,pefile
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_ECX,UC_X86_REG_EIP,UC_X86_REG_ESP
spec=importlib.util.spec_from_file_location('routing',Path(__file__).with_name('capture-gaper-scheduler-routing.py'));R=importlib.util.module_from_spec(spec);spec.loader.exec_module(R)
M=R.M
OUT=M.ROOT/'docs/reports/isaac-first-floor-parity/gaper-grid-lines'
COSTS=[0,1,900,949,950,999,1000,2999,3000,3999,4000]
def main():
 ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--check',action='store_true');a=ap.parse_args();raw=M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==M.SHA;pe=pefile.PE(data=raw)
 g=R.Grid(pe,{});n=g.n;u=n.u;p=n.PLAYER;sp=n.STACK+0xd000;g.word(g.ROOM+4,g.ROOM+0x9000)
 def call(address,args):
  u.mem_write(sp,struct.pack('<'+'I'*(len(args)+1),n.STOP,*args));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,g.ROOM);u.emu_start(address,n.STOP,count=1000000);assert u.reg_read(UC_X86_REG_EIP)==n.STOP;return u.reg_read(UC_X86_REG_EAX)&255
 masks=[];index=4*15+7
 for cost in COSTS:
  for collision in [-1,0,1,3,4]:
   g.word(g.ROOM+0x76c+4*index,cost);g.word(g.ROOM+0x24+4*index,0 if collision<0 else p+0x1000);g.word(p+0x103c,max(collision,0));result=call(0x7aeec0,[index]);expected=collision if collision>=0 else 1 if 3000<=cost<=3999 else 3 if cost>=1000 else 0;assert result==expected;masks.append([cost,collision,result])
 g.word(g.ROOM+0x24+4*index,0)
 rows=[]
 layouts=['open','central-cover','sealed','upper-gap','lower-gap','cost1','cost900','cost950']
 pairs=[(120,280,520,280),(520,280,120,280),(120,160,520,160),(120,400,520,400),(120,160,520,400),(120,400,520,160),(320,280,320,280)]
 # Probe both sides of a native cell edge, where the four +/-5 offsets matter.
 pairs += [(x,160,x,400) for x in [294,295,296,299,300,304,305,306,340,345,346]]
 for layout in layouts:
  for i in range(448):
   c,r=i%15,i//15;cost=0 if 1<=c<=13 and 1<=r<=7 else 1000
   if c==7 and ((layout=='central-cover' and 2<=r<=6) or layout=='sealed' or(layout=='upper-gap' and r>=2)or(layout=='lower-gap' and r<=6)):cost=1000
   if i==index and layout.startswith('cost'):cost=int(layout[4:])
   g.word(g.ROOM+0x76c+4*i,cost)
  for threshold in [0,900]:
   for x,y,tx,ty in pairs:
    for address,value in [(p+0x100,x),(p+0x104,y),(p+0x108,tx),(p+0x10c,ty)]:n.write_float(address,value)
    result=call(0x7af4b0,[p+0x100,p+0x108,0,threshold,0,0,0]);rows.append([layout,threshold,x,y,tx,ty,result])
 OUT.mkdir(parents=True,exist_ok=True)
 def save(name,data):
  path=OUT/name
  if a.check:assert path.read_bytes()==data,name
  else:path.write_bytes(data)
 for name,header,data in [('native-masks.csv',['cost','object_collision','native_collision'],masks),('native-lines.csv',['layout','threshold','from_x','from_y','to_x','to_y','clear'],rows)]:
  stream=io.StringIO(newline='');w=csv.writer(stream,lineterminator='\n');w.writerow(header);w.writerows(data);save(name,stream.getvalue().encode())
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
 for name,start,end in [('collision-lookup',0x7aeec0,0x7aef29),('check-line',0x7af4b0,0x7afa37),('caller-options',0x7a3d8b,0x7a3dfc)]:
  blob=pe.get_data(start-0x400000,end-start);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip()for i in md.disasm(blob,start))+'\n').encode());windows.append(dict(name=name,sha256=hashlib.sha256(blob).hexdigest(),executed=name!='caller-options'))
 manifest=dict(exe_sha256=M.SHA,mask_cases=len(masks),line_cases=len(rows),windows=windows,method='original unpatched collision lookup and complete mode0 CheckLine with native sqrt and cookie checks; no helper hooks',supplied_boundaries=['normal room dimensions15x9 and supplied0/1000 or experimental positive costs','optional synthetic grid-object collision field, no native object construction','mode0 with thresholds0/900; no ignored solids or special room config','native mask generation, cache/status/full pathfinder and continuous collision excluded'],full_native_acceptance=False)
 save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode());print(json.dumps(dict(passed=True,check=a.check,mask_cases=len(masks),line_cases=len(rows))))
if __name__=='__main__':main()
