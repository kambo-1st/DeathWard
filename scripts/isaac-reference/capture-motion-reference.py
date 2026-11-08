#!/usr/bin/env python3
"""Execute original bounded player/NPC movement arithmetic, never patch game code.

NPC targets/path outcomes are supplied. Native navigation, AI selection and live
scheduler behavior are NOT exercised. Outputs distinguish outgoing velocity from
next-invocation realized velocity, which consumes current friction.
"""
import argparse,csv,hashlib,importlib.util,io,json,struct
from pathlib import Path
import pefile,capstone
from unicorn.x86_const import UC_X86_REG_EDI,UC_X86_REG_EBX,UC_X86_REG_EBP,UC_X86_REG_ESP,UC_X86_REG_XMM1,UC_X86_REG_XMM2,UC_X86_REG_XMM5
spec=importlib.util.spec_from_file_location('motion',Path(__file__).with_name('analyze-player-motion.py'))
M=importlib.util.module_from_spec(spec);spec.loader.exec_module(M)
OUT=M.ROOT/'docs/reports/isaac-first-floor-parity/native-motion-reference'
WINDOWS=[('base-speed-init',0x722b66,0x722b70),('base',0x686406,0x686497),('gaper-moving',0x7a4704,0x7a47dd),('gaper-arrived',0x7a47dd,0x7a47f5),('gaper-blocked',0x7a46db,0x7a46f5),('spider-impulse',0x518508,0x518578),('spider-retention',0x5183a5,0x5183cd)]
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');a=ap.parse_args()
 raw=M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==M.SHA
 pe=pefile.PE(data=raw);md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);OUT.mkdir(parents=True,exist_ok=True)
 def save(name,data):
  p=OUT/name
  if a.check:assert p.read_bytes()==data,name
  else:p.write_bytes(data)
 windows=[]
 for name,start,end in WINDOWS:
  blob=pe.get_data(start-pe.OPTIONAL_HEADER.ImageBase,end-start)
  listing='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(blob,start))+'\n'
  save(name+'.asm',listing.encode());windows.append({'name':name,'start':hex(start),'end':hex(end),'sha256':hashlib.sha256(blob).hexdigest()})
 baseline=M.NativeMotion(pe);baseline.u.reg_write(UC_X86_REG_EDI,baseline.PLAYER)
 baseline.run(0x722b66,0x722b70);base_speed=baseline.read_float(baseline.PLAYER+0x14ac);assert base_speed==1
 rows=[]
 cases=[('player-press-release','player',[(1,0)]*180+[(0,0)]*120,1),('player-diagonal','player',[(1,1)]*90+[(0,0)]*60,1),('player-reverse','player',[(1,0)]*90+[(-1,0)]*90+[(0,0)]*60,1),('player-corner','player',[(1,0)]*90+[(0,1)]*90+[(0,0)]*60,1),('player-analog','player',[(.3,.4)]*90+[(0,0)]*60,1),('player-speed-08','player',[(1,0)]*90+[(0,0)]*60,.8),('player-speed-2','player',[(1,0)]*90+[(0,0)]*60,2)]
 for label,force in [('gaper-normal',.49799999594688416),('gaper-awake',.7200000286102295)]:
  cases.append((label,'gaper',[(100,0)]*120+[(0,0)]*30+[(None,None)]*30,force))
 cases.append(('spider-burst-pause','spider',[(0,0)]*16+[(100,0)]*12+[(0,0)]*30+[(-100,0)]*12+[(0,0)]*30,6))
 for case,kind,inputs,parameter in cases:
  n=M.NativeMotion(pe);p=n.PLAYER;b=n.ebp;u=n.u;pathfinder=p+0x8000
  u.mem_write(pathfinder,struct.pack('<I',p));n.write_float(p+0x2c0,1);n.write_float(p+0x2c4,1);n.write_float(p+0x2f4,1)
  for tick,(x,y) in enumerate(inputs):
   u.reg_write(UC_X86_REG_EDI,p);u.reg_write(UC_X86_REG_ESP,b-0x100);u.reg_write(UC_X86_REG_EBP,b)
   n.run(0x686406,0x686497)
   realized=[n.read_float(p+o) for o in [0x2b8,0x2bc]]
   if kind=='player':n.step(x,y,parameter);mode='input'
   elif kind=='gaper':
    u.reg_write(UC_X86_REG_EBX,pathfinder);n.write_float(b-0x50,1);n.write_float(b+0xc,parameter)
    if x is None:n.run(0x7a46db,0x7a46f5);mode='blocked'
    else:
     # Moving window expects delta.y in xmm1 and saved delta.x on stack.
     n.write_float(b-0x54,x);n.xmm(UC_X86_REG_XMM1,y);n.xmm(UC_X86_REG_XMM2,x)
     n.run(0x7a4704,0x7a47f5);mode='moving' if x*x+y*y>1 else 'arrived'
   else:
    n.xmm(UC_X86_REG_XMM5,0)
    if x or y:
     n.write_float(b-0x58,x);n.write_float(b-0x54,y);n.write_float(b-0x3c,parameter)
     n.run(0x518508,0x518578);mode='target'
    else:mode='idle'
    n.run(0x5183a5,0x5183cd)
   rows.append([case,kind,tick,parameter,x if x is not None else 0,y if y is not None else 0,mode,*[n.read_float(p+o) for o in [0x294,0x298,0x2b8,0x2bc,0x2c4]],*realized])
 text=io.StringIO(newline='');w=csv.writer(text,lineterminator='\n');w.writerow(['case','kind','invocation','parameter','input_x','input_y','mode','x','y','outgoing_vx','outgoing_vy','friction','realized_vx','realized_vy']);w.writerows(rows)
 save('native-traces.csv',text.getvalue().encode())
 manifest={'exe_sha256':M.SHA,'base_speed_cache_write':{'address':'0x722b66','field':'Player+0x14ac','executed_value':base_speed,'scope':'original baseline initialization write, not full character/item cache recomputation'},'rows':len(rows),'cases':len(cases),'windows':windows,'method':'original mapped x86/SSE and native sqrt/vector helpers; no instruction patches or stubbed helpers','scope':'bounded ordinary physics and steering arithmetic; targets/path results supplied','not_verified':['complete Player/NPC update reachability','Spider idle/target/RNG/stop controller','Pooter controller','navigation/collision','complete live scheduling and wall-clock','source room/world geometry'],'player_clock':'ordinary target dispatch60/s from earlier bounded routing evidence; not a live measurement','npc_clock':'ordinary target dispatch30/s from earlier bounded routing evidence; not a live measurement'}
 save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode());print(json.dumps({'pass':True,'check':a.check,'rows':len(rows),'cases':len(cases)}))
if __name__=='__main__':main()
