#!/usr/bin/env python3
"""Bounded original Brother Bobby following, firing gates and tear birth arithmetic.
No installed executable/process modifications. Host supplies actor state/parent/input.
"""
import argparse,csv,hashlib,importlib.util,io,json,struct,xml.etree.ElementTree as ET
from pathlib import Path
spec=importlib.util.spec_from_file_location('heart',Path(__file__).with_name('capture-shop-heart.py'))
H=importlib.util.module_from_spec(spec);spec.loader.exec_module(H)
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=H.A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==H.A.M.SHA
 pe=H.pefile.PE(data=raw);f=H.A.NativeAwards(pe,raw);n=f.n;u=f.u;b=n.ebp;fam=f.HEAP+0x300000
 out=H.A.M.ROOT/'docs/reports/isaac-first-floor-parity/pw-f01-brother-bobby/source'
 if not args.check:out.mkdir(parents=True,exist_ok=True)
 def save(name,data):
  if args.check:assert (out/name).read_bytes()==data,name
  else:(out/name).write_bytes(data)
 def table(name,header,rows):
  s=io.StringIO();w=csv.writer(s,lineterminator='\n');w.writerow(header);w.writerows(rows);save(name,s.getvalue().encode())
 def reg(r,v):u.reg_write(r,v)
 def block(a,z):
  u.emu_start(a,z,count=500000);assert u.reg_read(H.UC_X86_REG_EIP)==z
 def frame():reg(H.UC_X86_REG_EBP,b);reg(H.UC_X86_REG_ESP,n.STACK+0x9000)
 rows=[]
 for case,goals in [('straight',[(150,0)]*90),('corner',[(150,0)]*40+[(0,150)]*40),('reverse',[(150,0)]*35+[(-150,0)]*35),('diagonal',[(100,100)]*70),('threshold',[(0,0),(19.99,0),(20,0),(20.01,0),(0,0)])]:
  u.mem_write(fam,bytes(0x10000));n.write_float(fam+0x2f4,1);n.write_float(fam+0x2c0,1)
  for step,(x,z) in enumerate(goals):
   before=[n.read_float(fam+a) for a in (0x294,0x298,0x2b8,0x2bc)]
   frame();reg(H.UC_X86_REG_ESI,fam);n.write_float(fam+0x2c4,1);n.write_float(b-0x1c,x);n.write_float(b-0x18,z);n.write_float(b-0x24,20)
   block(0x5f4dc1,0x5f4e97);reg(H.UC_X86_REG_EDI,fam);block(0x686406,0x686497)
   after=[n.read_float(fam+a) for a in (0x294,0x298,0x2b8,0x2bc)];rows.append([case,step,*before,x,z,*after])
 table('native-follow.csv',['case','step','x','z','vx','vz','parent_x','parent_z','next_x','next_z','next_vx','next_vz'],rows)
 u.mem_write(fam,bytes(0x10000));f.write(fam+0x360,n.PLAYER);f.write(fam+0x288,fam+0x2000);f.write(fam+0x28,3);f.write(fam+0x2c,1)
 cadence=[]
 for tick in range(80):
  frame();reg(H.UC_X86_REG_ESI,fam);reg(H.UC_X86_REG_ECX,n.PLAYER);block(0x5f6350,0x5f63b3)
  delay=u.reg_read(H.UC_X86_REG_EDI);assert delay==16
  held=tick<25 or tick>=50;remaining=f.integer(fam+0xc9c);fired=held and remaining==0
  if fired:reg(H.UC_X86_REG_EDI,delay);block(0x5f6648,0x5f6658)
  cadence.append([tick,int(held),int(fired),f.integer(fam+0xc9c),delay])
 table('native-cadence.csv',['tick','held','fired','remaining','interval'],cadence)
 births=[]
 for damage in (3.5,20):
  n.write_float(n.PLAYER+0x13b8,damage)
  for vx,vz in [(0,0),(2,0),(-2,0),(-12,0),(0,2),(1,1)]:
   n.write_float(n.PLAYER+0x2b8,vx);n.write_float(n.PLAYER+0x2bc,vz)
   for dx,dz in [(1,0),(0,1),(-1,0),(0,-1)]:
    sp=n.STACK+0x9000;v=fam+0x3000;n.write_float(v,dx);n.write_float(v+4,dz)
    u.mem_write(sp,struct.pack('<3I',n.STOP,v,0));reg(H.UC_X86_REG_ESP,sp);reg(H.UC_X86_REG_ECX,fam)
    # Original entry through all ordinary modifier queries, stop before factory.
    block(0x618860,0x619a1e);sp=u.reg_read(H.UC_X86_REG_ESP)
    vals=[n.read_float(sp+a) for a in (0x24,0x28,0x30,0x3c,0x50,0x54)]
    assert vals[0]==3.5 and vals[2:4]==[0,0];births.append([damage,vx,vz,dx,dz,*vals])
 table('native-birth.csv',['player_damage','player_vx','player_vz','aim_x','aim_z','damage','scale','falling_acceleration','falling_speed_base','tear_vx','tear_vz'],births)
 source=H.A.M.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3'
 item=next(x for x in ET.parse(source/'items.xml').getroot() if x.get('id')=='8' and x.tag=='familiar')
 entity=next(x for x in ET.parse(source/'entities2.xml').getroot() if x.get('id')=='3' and x.get('variant')=='1')
 pool=next(x for x in ET.parse(source/'itempools.xml').getroot() if x.get('Name')=='treasure');entry=next(x for x in pool if x.get('Id')=='8');assert entry.get('Weight')=='1'
 md=H.capstone.Cs(3,4);windows=[]
 for name,a,z in [('dispatch',0x6009b4,0x6009c7),('ordinary-follow-tail',0x5f4d7c,0x5f4eab),('free-physics',0x686406,0x686497),('cadence',0x5f6350,0x5f63d6),('shoot-gate',0x5f6486,0x5f64cb),('shoot-reset',0x5f6648,0x5f6662),('tear-velocity',0x618860,0x618b44),('tear-baseline',0x618b60,0x618bf5),('tear-factory-boundary',0x619a1e,0x619b4c)]:
  blob=pe.get_data(a-0x400000,z-a);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,a))+'\n').encode());windows.append(dict(name=name,start=hex(a),end=hex(z),sha256=hashlib.sha256(blob).hexdigest()))
 save('manifest.json',(json.dumps(dict(executable_sha256=H.A.M.SHA,item=item.attrib,entity=entity.attrib,treasure=entry.attrib,follow_states=len(rows),cadence_states=len(cadence),birth_cases=len(births),windows=windows,scope='Supplied parent follow tail + original free physics. Original ordinary cooldown decrement/variant interval/reset, supplied held-input admission. Entire original familiar tear routine to first factory boundary with actual empty-inventory queries and ordinary owner. Factory/initial tear height, native actor scheduler, parent-chain construction, inventory cache reconstruction, item synergies and live physical acceptance not certified. DW 30Hz boundary/space/eight-way aim and physical collisions are explicit adapters.',full_native_acceptance=False),indent=2)+'\n').encode())
 print('PASS',len(rows),'follow,',len(cadence),'cadence,',len(births),'ordinary birth cases')
if __name__=='__main__':main()
