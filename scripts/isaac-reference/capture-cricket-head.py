#!/usr/bin/env python3
"""Original Cricket contribution, ordinary curve, presence gate and tear parameters."""
import argparse,csv,hashlib,importlib.util,io,json,struct,xml.etree.ElementTree as ET
from pathlib import Path
spec=importlib.util.spec_from_file_location('heart',Path(__file__).with_name('capture-shop-heart.py'))
H=importlib.util.module_from_spec(spec);spec.loader.exec_module(H)
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 A=H.A;raw=A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==A.M.SHA
 pe=H.pefile.PE(data=raw);f=A.NativeAwards(pe,raw);u=f.u;n=f.n;b=n.ebp
 out=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d11b-treasure-variety/source'
 if not args.check:out.mkdir(parents=True,exist_ok=True)
 def save(name,blob):
  if args.check:assert (out/name).read_bytes()==blob,name
  else:(out/name).write_bytes(blob)
 def table(name,columns,rows):
  s=io.StringIO();w=csv.writer(s,lineterminator='\n');w.writerow(columns);w.writerows(rows);save(name,s.getvalue().encode())
 def frame():
  u.reg_write(H.UC_X86_REG_EBP,b);u.reg_write(H.UC_X86_REG_ESP,b-0x1000);f.write(b-0x428,n.PLAYER)
 def block(start,end):
  u.emu_start(start,end,count=500000);assert u.reg_read(H.UC_X86_REG_EIP)==end
 def tear(damage,copies):
  f.write(f.ITEMS+0xf1000+16,copies);n.write_float(n.PLAYER+0x13b8,damage);n.write_float(n.PLAYER+0x13bc,-23.75);n.write_float(n.PLAYER+0x13c4,260);n.write_float(n.PLAYER+0x13ac,1)
  target=f.HEAP+300000;sp=n.STACK+0x9000;u.mem_write(sp,struct.pack('<6I',n.STOP,target,1,0x3f800000,0xffffffff,0));u.reg_write(H.UC_X86_REG_ESP,sp);u.reg_write(H.UC_X86_REG_ECX,n.PLAYER);f.run(0x7836a0)
  return bytes(u.mem_read(target,0x68))
 rows=[];params=[];speeds=[]
 for base in (-.8,-.5,0,.3,1,2,4,8):
  for copies in (0,1,2,5):
   f.write(f.ITEMS+0xf1000+16,copies);frame();u.reg_write(H.UC_X86_REG_EDI,n.PLAYER);u.reg_write(H.UC_X86_REG_EAX,0);u.reg_write(H.UC_X86_REG_ESI,0);n.write_float(b-0x42c,0)
   block(0x731524,0x73155d);contribution=n.read_float(b-0x42c);assert contribution==.5*copies
   # Bridge the ordinary raw stat into its curve, with other contributions off.
   frame();u.reg_write(H.UC_X86_REG_EDI,n.PLAYER);n.write_float(n.PLAYER+0x13b8,base+contribution);block(0x731b25,0x731b82)
   before=n.read_float(n.PLAYER+0x13b8);frame();u.reg_write(H.UC_X86_REG_ESI,n.PLAYER+0x13b8);u.reg_write(H.UC_X86_REG_EDI,n.PLAYER+0x1450);f.write(b-0x438,b-0x800);n.write_float(b-0x800,1)
   block(0x7322ad,0x73232e);damage=n.read_float(n.PLAYER+0x13b8)
   rows.append([base,copies,contribution,before,damage]);actual=tear(damage,copies)
   # Entire ordinary tear-parameter routine, real inventory queries: equal
   # cached damage gives identical records with/without Cricket, not extra speed.
   assert actual==tear(damage,0)
   vals=struct.unpack_from('<6f',actual,0x48);params.append([base,copies,*vals])
 for copies in (0,1,2,5):
  f.write(f.ITEMS+0xf1000+16,copies);frame();f.write(b-0x440,n.PLAYER+0x1450);u.mem_write(b-0x441,b'\x01');u.reg_write(H.UC_X86_REG_EAX,n.PLAYER)
  block(0x732646,0x732c33);speed=n.read_float(n.PLAYER+0x13ac);assert speed==1;speeds.append([copies,speed])
 table('native-damage.csv',['raw_base','copies','contribution','before_multiplier','damage'],rows)
 table('native-tears.csv',['raw_base','copies','damage','scale','height','velocity_multiplier','knockback','falling_acceleration'],params)
 table('native-shot-speed.csv',['copies','shot_speed'],speeds)
 source=A.M.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3';items=ET.parse(source/'items.xml').getroot();pool=next(x for x in ET.parse(source/'itempools.xml').getroot() if x.get('Name')=='treasure')
 records=[]
 for id in ('1','4'):
  item=next(x for x in items if x.get('id')==id and x.tag=='passive');entry=next(x for x in pool if x.get('Id')==id);assert not item.get('achievement') and entry.get('Weight')=='1';records.append(dict(item=dict(item.attrib),pool=dict(entry.attrib)))
 md=H.capstone.Cs(H.capstone.CS_ARCH_X86,H.capstone.CS_MODE_32);windows=[]
 for name,a,z in [('cricket-contribution',0x731524,0x73155d),('contribution-store',0x731769,0x73178d),('damage-curve',0x731b25,0x731b82),('presence-multiplier',0x7322ad,0x73232e),('tear-scale',0x7862a7,0x786315)]:
  blob=pe.get_data(a-0x400000,z-a);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,a))+'\n').encode());windows.append(dict(name=name,start=hex(a),end=hex(z),sha256=hashlib.sha256(blob).hexdigest()))
 manifest=dict(version='Repentance 1.7.9b',executable_sha256=A.M.SHA,items=records,windows=windows,damage_cases=len(rows),whole_tear_comparisons=len(params),shot_speed_cases=len(speeds),xml_sha256={x:hashlib.sha256((source/x).read_bytes()).hexdigest() for x in ('items.xml','itempools.xml')},scope='Original inventory query/contribution, ordinary raw-damage curve and original presence multiplier with supplied intermediate raw cache. Whole GetTearHitParams (0x7836a0) under ordinary player fixture: same damage gives identical 104-byte output with/without item. Shot-speed cache block with other modifiers off stops before callback. Full cache ordering, other damage items/characters, native RNG, actors/physical contact and full pool are unaccepted. Relative DW size and inverse accepted-base damage are explicit adapters.',full_native_acceptance=False)
 save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode());print('PASS',len(rows),'damage,',len(params),'whole tear comparisons,',len(speeds),'shot-speed cases')
if __name__=='__main__':main()
