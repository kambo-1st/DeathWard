#!/usr/bin/env python3
"""Execute pinned native Gaper physics/steering and alternate interpolation.

Routes and target positions are supplied; this does not execute full native
FindGridPath, animation initialization, status logic or entity/terrain collision.
Main phase0 defines time0; each subsequent sample advances1/60 nominal second.
"""
import argparse,csv,hashlib,importlib.util,io,json,struct,xml.etree.ElementTree as ET
from pathlib import Path
import capstone,pefile
from unicorn.x86_const import UC_X86_REG_EDI,UC_X86_REG_EDX,UC_X86_REG_EBX,UC_X86_REG_EBP,UC_X86_REG_ESP,UC_X86_REG_XMM1,UC_X86_REG_XMM2
spec=importlib.util.spec_from_file_location('motion',Path(__file__).with_name('analyze-player-motion.py'));M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)
OUT=M.ROOT/'docs/reports/isaac-first-floor-parity/gaper-trajectories'
CASES=[('ordinary-long',1,90,(0,0)),('ordinary-short',1,90,(0,0)),('ordinary-near-arrival',1,60,(2,0)),('ordinary-zero-arrival',1,60,(2,0)),('ordinary-turn',1,90,(0,0)),('ordinary-reverse',1,90,(0,0)),('ordinary-moving-target',1,90,(0,0)),('ordinary-blocked',1,60,(2,0)),('frowning-open-route',0,90,(0,0)),('frowning-awake-turn',0,90,(0,0))]
def target(name,k):
 if name=='ordinary-short':return (350,300)
 if name=='ordinary-near-arrival':return (322.5,280)
 if name=='ordinary-zero-arrival':return (322,280)
 if name.endswith('turn'):return (560,280) if k<30 else (320,400) if k<60 else (80,280)
 if name=='ordinary-reverse':return (560,280) if k<30 else (80,280)
 if name=='ordinary-moving-target':return (400+k*.5,300+k*.5)
 return (560,280)
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');a=ap.parse_args();raw=M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==M.SHA;pe=pefile.PE(data=raw);OUT.mkdir(parents=True,exist_ok=True)
 def save(name,data):
  p=OUT/name
  if a.check:assert p.read_bytes()==data,name
  else:p.write_bytes(data)
 windows=[('npc-base-call',0x69b6c9,0x69b6f7,False),('npc-ai-call',0x69b7be,0x69b7c5,False),('gaper-dispatch',0x699ffb,0x69a002,False),('physics',0x686406,0x686497,True),('interpolation',0x68827a,0x6882f1,True),('restore',0x8b02e2,0x8b0301,True),('force-normal',0x4f7edf,0x4f7ee9,True),('force-closed',0x4f7e48,0x4f7e52,True),('force-awake',0x4f7ed3,0x4f7edd,True),('direct-target',0x7a3dfc,0x7a3f08,True),('pursuit',0x7a46c1,0x7a47f5,True),('blocked',0x7a46db,0x7a46f5,True)]
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);evidence=[]
 for name,start,end,executed in windows:
  blob=pe.get_data(start-0x400000,end-start);listing='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,start))+'\n';save(name+'.asm',listing.encode());evidence.append({'name':name,'start':hex(start),'end':hex(end),'raw_sha256':hashlib.sha256(blob).hexdigest(),'executed':executed})
 rows=[]
 for name,variant,frames,initial in CASES:
  n=M.NativeMotion(pe);p=n.PLAYER;b=n.ebp;u=n.u;finder=p+0x8000;u.mem_write(finder,struct.pack('<I',p));u.mem_write(p+0x28,struct.pack('<I',10));u.mem_write(p+0x2c,struct.pack('<I',variant))
  for off,value in [(0x294,320),(0x298,280),(0x2b8,initial[0]),(0x2bc,initial[1]),(0x2c0,1),(0x2c4,1),(0x2f4,1)]:n.write_float(p+off,value)
  last=None
  def setup():u.reg_write(UC_X86_REG_EDI,p);u.reg_write(UC_X86_REG_ESP,b-0x100);u.reg_write(UC_X86_REG_EBP,b)
  def steer(k):
   setup();lo,hi=(0x4f7edf,0x4f7ee9) if variant else ((0x4f7e48,0x4f7e52) if k==0 and name=='frowning-open-route' else (0x4f7ed3,0x4f7edd));n.run(lo,hi);force=n.read_float(p+0xb84)
   tx,ty=target(name,k);u.reg_write(UC_X86_REG_EBX,finder);n.write_float(b-0x50,1);n.write_float(b+0xc,force)
   n.write_float(b-0x74,n.read_float(p+0x298));n.write_float(b-0x78,n.read_float(p+0x294))
   if name=='ordinary-blocked':
    n.xmm(UC_X86_REG_XMM2,0);n.xmm(UC_X86_REG_XMM1,0);n.run(0x7a46c1,0x7a47f5);route='blocked'
   else:
    # Execute the native direct-target selection with a supplied clear-line
    # result. Its true-option threshold is750, covering these room targets.
    target_ptr=p+0x9000;n.write_float(target_ptr,tx);n.write_float(target_ptr+4,ty)
    u.mem_write(finder+0x72c,b'\1');u.mem_write(b-0x3c,struct.pack('<I',target_ptr));u.mem_write(b+0x14,b'\1');u.mem_write(b-0x22,b'\0')
    for offset,value in [(-0x70,n.read_float(p+0x294)),(-0x5c,n.read_float(p+0x298)),(-0x2c,0),(-0x38,0)]:n.write_float(b+offset,value)
    n.run(0x7a3dfc,0x7a47f5);route='valid'
   return tx,ty,route,force
  def record(sample,k,phase,goal):
   nonlocal last
   x,y=n.read_float(p+0x294),n.read_float(p+0x298);dx,dy=(0,0) if last is None else ((x-last[0])*2,(y-last[1])*2);last=(x,y)
   rows.append([name,variant,sample,k,phase,*goal,x,y,n.read_float(p+0x2b8),n.read_float(p+0x2bc),n.read_float(p+0x2c4),dx,dy,*seed])
  setup();n.run(0x686406,0x686497);seed=(n.read_float(p+0x2b8),n.read_float(p+0x2bc));goal=steer(0);record(0,0,'main',goal)
  for k in range(frames):
   setup();n.run(0x68827a,0x6882f1);record(2*k+1,k,'interpolation',goal)
   # Original Manager restores saved main position before next physics update.
   u.reg_write(UC_X86_REG_EDX,p);n.run(0x8b02e2,0x8b0301)
   setup();n.run(0x686406,0x686497);goal=steer(k+1);record(2*k+2,k+1,'main',goal)
 text=io.StringIO(newline='');w=csv.writer(text,lineterminator='\n');w.writerow(['case','variant','sample','npc_frame','phase','target_x','target_y','route','force','x','y','outgoing_vx','outgoing_vy','friction','visible_interval_vx','visible_interval_vy','seed_realized_vx','seed_realized_vy']);w.writerows(rows);save('native-trajectories.csv',text.getvalue().encode())
 xml=M.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3/entities2.xml';bodies=[dict(e.attrib) for e in ET.parse(xml).getroot() if e.get('id')=='10' and e.get('variant','0') in ['0','1']];assert len(bodies)==2 and all(e.get('friction')=='1' for e in bodies)
 manifest={'exe_sha256':M.SHA,'source_xml_sha256':hashlib.sha256(xml.read_bytes()).hexdigest(),'source_bodies':bodies,'samples':len(rows),'cases':[{'name':name,'variant':v,'frames':f,'initial_velocity_before_first_physics':vel} for name,v,f,vel in CASES],'windows':evidence,'method':'original unpatched native physics, force writes, direct-target selection/route steering, alternate interpolation and Manager restoration; native sqrt executes; no helper hooks','time_origin':'first main physics/AI update is time0; interpolation and next main samples then alternate at nominal1/60','supplied_boundaries':['unobstructed target coordinates or absent route; direct-line result supplied true, native750 threshold and target selection executed','normal status/timeScale1/baseFriction1','closed then awake force schedule for frowning-open-route; pre-awake state for awake-turn'],'not_verified':['Full native FindGridPath/terrain grid','Frowning overlay/initialization scheduling','Complete NPC update reachability and live NPC wall-clock','Collision, status/champion branches, damage/lifecycle']};save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode());print(json.dumps({'pass':True,'check':a.check,'cases':len(CASES),'samples':len(rows)}))
if __name__=='__main__':main()
