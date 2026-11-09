#!/usr/bin/env python3
"""Execute native Frowning AI gates then the ordinary base-animation interval.

Healthy status, direct-path results and entity timeScale are supplied. Wrapper
branch order is pinned by the scheduler checkpoint; full wrapper is not run.
"""
import argparse,csv,hashlib,importlib.util,io,json
from pathlib import Path
import pefile
from unicorn.x86_const import UC_X86_REG_EDX,UC_X86_REG_ESI
s=importlib.util.spec_from_file_location('routing',Path(__file__).with_name('capture-gaper-scheduler-routing.py'));R=importlib.util.module_from_spec(s);s.loader.exec_module(R);A=R.A;M=R.M
OUT=M.ROOT/'docs/reports/isaac-first-floor-parity/frowning-phase-review'
CASES=[('never-clear',lambda k:False,1),('clear-at-start',lambda k:True,1),('clear-after-three',lambda k:k>=3,1),('single-clear-pulse',lambda k:k==3,1),('half-speed-always-clear',lambda k:True,.5),('half-speed-single-pulse',lambda k:k==3,.5)]
def main():
 ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('--check',action='store_true');a=ap.parse_args();raw=M.EXE.read_bytes();rt=A.RUNTIME.read_bytes();assert hashlib.sha256(raw).hexdigest()==M.SHA;assert hashlib.sha256(rt).hexdigest()==A.RUNTIME_SHA;pe=pefile.PE(data=raw);runtime=pefile.PE(data=rt);rows=[]
 for name,route,scale in CASES:
  f=A.Fixture(pe,runtime,20)
  for k in range(48):
   before=f.frame();force=f.ai_gates(route(k));after=f.frame();f.n.write_float(f.p+0x2f4,scale);f.n.u.reg_write(UC_X86_REG_EDX,0);f.n.u.reg_write(UC_X86_REG_ESI,0);f.block(0x6860e7,0x68618c)
   rows.append([name,k,int(route(k)),scale,before,force,after,f.frame(),f.playing()])
 OUT.mkdir(parents=True,exist_ok=True)
 def save(name,data):
  p=OUT/name
  if a.check:assert p.read_bytes()==data,name
  else:p.write_bytes(data)
 stream=io.StringIO(newline='');w=csv.writer(stream,lineterminator='\n');w.writerow(['case','update','direct_path','time_scale','frame_before_ai','force','frame_after_ai','frame_after_base','playing']);w.writerows(rows);save('native-phases.csv',stream.getvalue().encode())
 manifest=dict(exe_sha256=M.SHA,runtime_sha256=A.RUNTIME_SHA,cases=6,evaluations=len(rows),method='original initialization/AI gates and actual ordinary base-animation interval, with real UCRT helpers; no patches or helper stubs',supplied_boundaries=['direct-path flag','entity timeScale1 or.5; not native Slow status acceptance','minimal20-frame Head metadata without visual layers','ordinary AI-then-base order from scoped wrapper evidence; intervening wrapper logic excluded'],full_native_acceptance=False);save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode());print(json.dumps(dict(passed=True,check=a.check,cases=6,evaluations=len(rows))))
if __name__=='__main__':main()
