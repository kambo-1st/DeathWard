#!/usr/bin/env python3
"""Golden key admitted collection, ordinary key spending and conditional floor flags.
Original installed x86 instructions; supplied ordinary player fields. Earlier
collision callbacks/physics and complete floor callers remain outside scope.
"""
import argparse,csv,hashlib,importlib.util,io,json,struct
from pathlib import Path
import pefile
from unicorn.x86_const import *
spec=importlib.util.spec_from_file_location('awards',Path(__file__).with_name('analyze-room-awards.py'))
A=importlib.util.module_from_spec(spec);spec.loader.exec_module(A)
OUT=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d14a19-golden-keys/source'
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==A.M.SHA
 f=A.NativeAwards(pefile.PE(data=raw),raw);n=f.n;u=f.u;p=n.PLAYER;pickup=p+0x5000;sp=n.STACK+0xd000
 def save(name,data):
  file=OUT/name
  if args.check:assert file.read_bytes()==data,name
  else:file.parent.mkdir(parents=True,exist_ok=True);file.write_bytes(data)
 def csvfile(name,header,rows):
  text=io.StringIO();w=csv.writer(text,lineterminator='\n');w.writerow(header);w.writerows(rows);save(name,text.getvalue().encode())
 collection=[];spends=[];floors=[]
 for count in [0,1,2,5,98,99]:
  for golden in [0,1]:
   f.write(p+0x12ac,count);u.mem_write(p+0x12b0,bytes([golden]));f.write(pickup+0x2c,30);f.write(pickup+0x30,2)
   u.mem_write(n.ebp-0x6d,b'\0');u.reg_write(UC_X86_REG_EBP,n.ebp);u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ESI,pickup);u.reg_write(UC_X86_REG_EDI,p)
   n.run(0x6bf367,0x6c02a5)
   result=[count,golden,f.integer(p+0x12ac),u.mem_read(p+0x12b0,1)[0],u.mem_read(n.ebp-0x6d,1)[0]]
   assert result==[count,golden,count,1,1];collection.append(result)
   f.write(p+0x12ac,count);u.mem_write(p+0x12b0,bytes([golden]));u.mem_write(sp,struct.pack('<I',n.STOP));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,p)
   f.run(0x726070);ok=u.reg_read(UC_X86_REG_EAX)&255;after=f.integer(p+0x12ac)
   assert ok==int(golden or count>0) and after==count-int(not golden and count>0)
   spends.append([count,golden,after,ok])
 for arg in [0,1]:
  for key in [0,1]:
   for bomb in [0,1]:
    u.mem_write(p+0x12b0,bytes([key,bomb]));f.write(p+0x12ac,7);f.write(p+0x12a8,9);u.mem_write(n.ebp+8,bytes([arg]));u.reg_write(UC_X86_REG_EBP,n.ebp);u.reg_write(UC_X86_REG_EBX,p);u.reg_write(UC_X86_REG_ESI,pickup)
    n.run(0x76ae77,0x76ae92);result=[arg,key,bomb,*u.mem_read(p+0x12b0,2),f.integer(p+0x12ac),f.integer(p+0x12a8)]
    assert result==[arg,key,bomb,key if arg else 0,bomb if arg else 0,7,9];floors.append(result)
 csvfile('native-collection.csv',['initial_keys','initial_golden','keys','golden','collected'],collection)
 csvfile('native-spending.csv',['initial_keys','golden','keys','success'],spends)
 csvfile('native-floor-flags.csv',['argument','initial_key','initial_bomb','golden_key','golden_bomb','keys','bombs'],floors)
 save('manifest.json',(json.dumps({'executable_sha256':A.M.SHA,'collection_cases':len(collection),'spending_cases':len(spends),'conditional_floor_cases':len(floors),'windows':{'collection':['0x6bf367','0x6c02a5 (branch exit)'],'use_key':['0x726070','native return'],'conditional_floor_flags':['0x76ae77','0x76ae92']},'scope':__doc__,'duplicate_golden_and_99_cap':'Admitted key branch consumes and sets flag; previous ordinary collision gates remain a world adaptation.','full_native_acceptance':False},indent=2)+'\n').encode())
 print('PASS12 native golden-key collections,12 key-use cases and8 conditional floor cases')
if __name__=='__main__':main()
