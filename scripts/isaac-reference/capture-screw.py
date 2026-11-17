#!/usr/bin/env python3
"""Pinned Screw count/tear contribution, ordinary curve and shot-speed cache block.

Ordinary player fixture, other modifiers off except supplied Onion contribution
and optional held Whip Worm. Not a whole cache scheduler or pool acceptance.
"""
import argparse,csv,hashlib,importlib.util,io,json,struct,xml.etree.ElementTree as ET
from pathlib import Path
spec=importlib.util.spec_from_file_location('heart',Path(__file__).with_name('capture-shop-heart.py'))
H=importlib.util.module_from_spec(spec);spec.loader.exec_module(H)
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 A=H.A;raw=A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==A.M.SHA
 pe=H.pefile.PE(data=raw);f=A.NativeAwards(pe,raw);u=f.u;n=f.n;b=n.ebp
 out=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d14a1-screw-reward/source'
 if not args.check:out.mkdir(parents=True,exist_ok=True)
 def save(name,data):
  if args.check:assert (out/name).read_bytes()==data,name
  else:(out/name).write_bytes(data)
 def table(name,columns,rows):
  s=io.StringIO();w=csv.writer(s,lineterminator='\n');w.writerow(columns);w.writerows(rows);save(name,s.getvalue().encode())
 def frame():
  u.reg_write(H.UC_X86_REG_EBP,b);u.reg_write(H.UC_X86_REG_ESP,b-0x1000);f.write(b-0x428,n.PLAYER)
 def block(start,end):
  u.emu_start(start,end,count=500000);assert u.reg_read(H.UC_X86_REG_EIP)==end
 tears=[];shots=[]
 for base in (-8,-2,-1,-.7,-.5,-.2,0,.3,1,2,4,8):
  for onion in (0,1,2,5):
   for copies in (0,1,2,5,8):
    f.write(f.ITEMS+0xf1000+255*4,copies);frame();u.reg_write(H.UC_X86_REG_EDI,n.PLAYER)
    u.reg_write(H.UC_X86_REG_EAX,0);u.reg_write(H.UC_X86_REG_ESI,0);n.write_float(b-0x42c,.7*onion)
    block(0x72fbcd,0x72fc21);contribution=n.read_float(b-0x42c)
    assert abs(contribution-(.7*onion+.5*copies))<.000001
    total=struct.unpack('<f',struct.pack('<f',base+contribution))[0]
    frame();u.reg_write(H.UC_X86_REG_EDI,n.PLAYER);n.write_float(b-0x448,total);n.xmm(H.UC_X86_REG_XMM1,total);n.xmm(H.UC_X86_REG_XMM0,1)
    block(0x73006a,0x730143)
    rate=struct.unpack('<f',struct.pack('<I',u.reg_read(H.UC_X86_REG_XMM1)&0xffffffff))[0]
    tears.append([base,onion,copies,contribution,total,n.read_float(b-0x448),rate])
 for copies in (0,1,2,5,8,20):
  for held in (0,27,39):
   f.write(f.ITEMS+0xf1000+255*4,copies);f.write(n.PLAYER+0x15e8,held);frame()
   f.write(b-0x440,n.PLAYER+0x1450);n.write_float(b-0x43c,1);u.mem_write(b-0x441,b'\x01');u.reg_write(H.UC_X86_REG_EAX,n.PLAYER)
   block(0x732646,0x732c33);speed=n.read_float(n.PLAYER+0x13ac)
   assert abs(speed-(1+.2*copies+(.5 if held==27 else 0)))<.000001,(copies,held,speed)
   shots.append([copies,held,speed])
 table('native-tears.csv',['base_tear_stat','onion_copies','screw_copies','contribution','total_tear_stat','delay','tears_per_second'],tears)
 table('native-shot-speed.csv',['screw_copies','held_trinket','shot_speed'],shots)
 source=A.M.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3'
 item=next(e for e in ET.parse(source/'items.xml').getroot() if e.tag=='passive' and e.get('id')=='255')
 pool=next(e for p in ET.parse(source/'itempools.xml').getroot() if p.get('Name')=='boss' for e in p if e.get('Id')=='255')
 assert item.get('cache')=='firedelay shotspeed' and not item.get('achievement') and pool.get('Weight')=='1'
 windows=[];md=H.capstone.Cs(H.capstone.CS_ARCH_X86,H.capstone.CS_MODE_32)
 for name,start,end in [('screw-tear-contribution',0x72fbcd,0x72fc21),('ordinary-tear-curve',0x73006a,0x730143),('screw-shot-contribution',0x7327d2,0x732818),('shot-speed-cache-block',0x732646,0x732c33)]:
  blob=pe.get_data(start-0x400000,end-start);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,start))+'\n').encode());windows.append(dict(name=name,start=hex(start),end=hex(end),sha256=hashlib.sha256(blob).hexdigest()))
 save('manifest.json',(json.dumps(dict(version='Repentance1.7.9b',executable_sha256=A.M.SHA,item=dict(item.attrib),boss_pool_entry=dict(pool.attrib),tear_cases=len(tears),shot_cases=len(shots),windows=windows,xml_sha256={x:hashlib.sha256((source/x).read_bytes()).hexdigest() for x in ('items.xml','itempools.xml')},scope='Original inventory count query and +0.5 raw tear-stat contribution; supplied base/Onion contribution into original ordinary curve. Complete ordinary shot-speed cache block with real count query and optional Whip Worm: +0.2 per copy. Neutral cache-effect multiplier local is explicitly1; callbacks/full cache order, other characters/modifiers, pool RNG and physical actors remain unaccepted.',full_native_acceptance=False),indent=2)+'\n').encode())
 print(f'PASS {len(tears)} native tear cases and {len(shots)} shot-speed/Whip cases; source boss-pool eligibility')
if __name__=='__main__':main()
