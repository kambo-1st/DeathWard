#!/usr/bin/env python3
"""Installed Cancer cache arithmetic and ordinary trinket factory, bounded fixtures."""
import argparse,csv,hashlib,importlib.util,io,json,struct,xml.etree.ElementTree as ET
from pathlib import Path
import capstone,pefile
from unicorn.x86_const import *
spec=importlib.util.spec_from_file_location('awards',Path(__file__).with_name('analyze-room-awards.py'))
A=importlib.util.module_from_spec(spec);spec.loader.exec_module(A);M=A.M
OUT=M.ROOT/'docs/reports/isaac-first-floor-parity/pw-t01-cancer/source'
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==M.SHA
 pe=pefile.PE(data=raw);n=M.NativeMotion(pe);u=n.u;b=n.ebp
 source=M.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3/items.xml'
 item=next(e for e in ET.parse(source).getroot() if e.tag=='trinket' and e.get('id')=='39')
 assert item.get('cache')=='firedelay' and not item.get('achievement')
 OUT.mkdir(parents=True,exist_ok=True)
 def save(name,blob):
  p=OUT/name
  if args.check:assert p.read_bytes()==blob,name
  else:p.write_bytes(blob)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
 for name,start,end in [('cancer-query-contribution',0x73030e,0x730371),('post-curve-addition',0x73043c,0x730454),('ordinary-final-delay',0x730c0e,0x730c38),('trinket-pool',0x701880,0x701bc8),('trinket-factory',0x6b62bf,0x6b6314)]:
  blob=pe.get_data(start-0x400000,end-start)
  save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,start))+'\n').encode())
  windows.append(dict(name=name,start=hex(start),end=hex(end),sha256=hashlib.sha256(blob).hexdigest()))
 rows=[]
 for base in [-2,-1,-.7,-.3,0,.3,1,2,4,8]:
  for copies in [0,1,3]:
   for held in [0,1]:
    n.reset();u.reg_write(UC_X86_REG_EBP,b);u.reg_write(UC_X86_REG_ESP,b-0x1000)
    # Native Sad Onion weighted contribution followed by native ordinary cap/curve.
    u.reg_write(UC_X86_REG_EAX,copies);n.write_float(b-0x42c,0);n.run(0x72f9a4,0x72f9bb);n.run(0x72fb6c,0x72fb7c)
    rawStat=base+n.read_float(b-0x42c);n.write_float(b-0x448,rawStat);n.xmm(UC_X86_REG_XMM1,rawStat);n.xmm(UC_X86_REG_XMM0,1)
    u.mem_write(b-0x428,struct.pack('<I',n.PLAYER));n.run(0x73006a,0x730143)
    ordinary=struct.unpack('<f',struct.pack('<I',u.reg_read(UC_X86_REG_XMM1)&0xffffffff))[0]
    u.reg_write(UC_X86_REG_EAX,held);n.write_float(b-0x450,0);n.write_float(b-0x458,0);n.run(0x730352,0x730371)
    bonus=n.read_float(b-0x450);n.write_float(b-0x42c,bonus);n.write_float(b-0x434,ordinary);n.xmm(UC_X86_REG_XMM0,0);n.run(0x73043c,0x730454)
    rate=n.read_float(b-0x434);n.xmm(UC_X86_REG_XMM1,rate);n.write_float(n.PLAYER+0x1868,1);n.run(0x730c0e,0x730c38)
    rows.append([base,copies,held,ordinary,bonus,rate,n.read_float(b-0x448)])
 out=io.StringIO();w=csv.writer(out,lineterminator='\n');w.writerow(['base_tear_stat','onion_copies','held','ordinary_rate','cancer_bonus','rate','delay']);w.writerows(rows);save('native-tears.csv',out.getvalue().encode())
 factories=[]
 for seed in [1,2,7,39,69,12345,0xdeadbeef,0xffffffff]:
  f=A.NativeAwards(pe,raw);p=f.GAME+0x1a5cc;v=f.HEAP+0x300000;defs=v+0x1000;d=defs+0x1000;callbacks=d+0x1000
  for addr,val in [(p+0x798,1),(p+0x78c,v),(p+0x790,v+8),(f.MANAGER+0x29e90,defs),(f.MANAGER+0x29e94,defs+200*4),(defs+39*4,d),(d,2),(d+4,39),(0xbfd674,callbacks),(callbacks,callbacks+0x100)]:f.write(addr,val)
  f.u.mem_write(v,struct.pack('<I4B',39,1,1,0,0));f.u.mem_write(p+0x664,struct.pack('<4I',seed,5,9,7))
  variant,subtype=f.pickup(seed,350);remaining=f.integer(p+0x798);available=f.u.mem_read(v+4,1)[0]
  assert (variant,subtype,remaining,available)==(350,39,0,0)
  factories.append(dict(seed=seed,variant=variant,subtype=subtype,remaining=remaining,available=available))
 save('native-factory.json',(json.dumps(factories,indent=2)+'\n').encode())
 save('manifest.json',(json.dumps(dict(executable_sha256=M.SHA,version='Repentance 1.7.9b',item=dict(item.attrib),xml_sha256=hashlib.sha256(source.read_bytes()).hexdigest(),windows=windows,arithmetic_cases=len(rows),factory_cases=len(factories),scope='Original SSE ordinary curve, Cancer contribution and addition/final delay, with supplied ordinary base stat, owned Onion count and Cancer effective multiplier. Other cache contributions zero; multiplier one. Original numeric pickup wrapper with a supplied one-entry enabled/available Cancer pool, no mod callbacks/golden unlocks. No full pool population/refill/native seed stream, swallowed/golden/Moms Box, inventory/cache scheduler, physics or full actor acceptance.',full_native_acceptance=False),indent=2)+'\n').encode())
 print('PASS',len(rows),'native Cancer/Onion rate cases;',len(factories),'original trinket factory/eligibility cases')
if __name__=='__main__':main()
