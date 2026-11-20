#!/usr/bin/env python3
"""Pin ordinary donation achievement thresholds, source shop levels and stock-slot coordinates."""
import argparse,csv,hashlib,importlib.util,io,json,struct,xml.etree.ElementTree as ET
from pathlib import Path
import pefile,capstone
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import *
spec=importlib.util.spec_from_file_location('a',Path(__file__).with_name('analyze-room-awards.py'));A=importlib.util.module_from_spec(spec);spec.loader.exec_module(A)
spec=importlib.util.spec_from_file_location('rooms',Path(__file__).with_name('audit-live-floor.py'));R=importlib.util.module_from_spec(spec);spec.loader.exec_module(R)
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==A.M.SHA
 pe=pefile.PE(data=raw);f=A.NativeAwards(pe,raw);u,n=f.u,f.n
 out=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d14a15-donation-milestones/source';out.mkdir(parents=True,exist_ok=True)
 def save(name,data):
  if args.check:assert (out/name).read_bytes()==data,name
  else:(out/name).write_bytes(data)
 def csvfile(name,head,rows):
  b=io.StringIO();w=csv.writer(b,lineterminator='\n');w.writerow(head);w.writerows(rows);save(name,b.getvalue().encode())
 calls=[]
 def unlock(u,address,size,data):
  sp=u.reg_read(UC_X86_REG_ESP);calls.append(f.integer(sp+4));u.reg_write(UC_X86_REG_EIP,f.integer(sp));u.reg_write(UC_X86_REG_ESP,sp+8)
 u.hook_add(UC_HOOK_CODE,unlock,begin=0x884c80,end=0x884c80)
 ids=[134,151,135,152,136,153,137,154,59,138];thresholds=[10,20,50,100,150,200,400,600,900,999];rows=[]
 for bank in sorted({0,1,1000,*[v+d for v in thresholds for d in [-1,0,1]]}):
  calls.clear();u.reg_write(UC_X86_REG_EBP,n.ebp);u.reg_write(UC_X86_REG_ESP,n.ebp-0x1000);f.write(n.ebp-0x80,bank);f.write(n.ebp-0x90,f.MANAGER+0x14)
  u.emu_start(0x63da85,0x63db69,count=10000);mask=sum(1<<ids.index(i) for i in calls)
  rows.append([bank,mask]);assert mask==sum(1<<i for i,v in enumerate(thresholds) if bank>=v)
 csvfile('native-milestones.csv',['credited_display_bank','unlocked_mask'],rows)
 levels=[]
 for mask in range(16):
  u.mem_write(f.MANAGER+0xe3,bytes((mask>>i)&1 for i in range(4)));f.write(f.MANAGER+8,0);f.write(f.GAME+0x243624,0)
  u.reg_write(UC_X86_REG_EDI,f.ROOM);u.reg_write(UC_X86_REG_ESP,n.ebp-0x1000);u.emu_start(0x7b1717,0x7b1834,count=10000)
  levels.append([mask,f.integer(f.ROOM+0x6f5c)]);assert levels[-1][1]==1+mask.bit_length()
 csvfile('native-shop-level.csv',['upgrade_bits','native_level'],levels)
 rooms,meta=R.read_stb(R.SOURCE/'rooms/00.special rooms.stb');selected=[next(r for r in rooms if(r['type'],r['variant'],r['subtype'])==(2,i,i)) for i in range(5)]
 csvfile('source-stock-slots.csv',['upgrade_level','ordinal','x','y'],[[i,n,s['x'],s['y']] for i,r in enumerate(selected) for n,s in enumerate(r['slots']) if s['choices'][0]['type']==5 and s['choices'][0]['variant']==150])
 assert [sum(s['choices'][0]['type']==5 for s in r['slots']) for r in selected]==[2,3,4,5,6]
 xml=R.SOURCE/'achievements.xml';ach=ET.parse(xml).getroot();achievements=[dict(next(e for e in ach if e.get('id')==str(i)).attrib) for i in ids]
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
 for name,start,end in [('milestone-gates',0x63da85,0x63db69),('shop-level',0x7b1717,0x7b1834)]:
  blob=pe.get_data(start-0x400000,end-start);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,start))+'\n').encode());windows.append(dict(name=name,start=hex(start),end=hex(end),sha256=hashlib.sha256(blob).hexdigest()))
 save('manifest.json',(json.dumps(dict(executable_sha256=A.M.SHA,thresholds=thresholds,achievement_ids=ids,achievements=achievements,achievement_xml_sha256=hashlib.sha256(xml.read_bytes()).hexdigest(),rooms_source=meta,layouts=selected,windows=windows,scope='Original milestone calls and ordinary normal room level stores, supplied achievement bytes, profile special cases off. Default 2.variant.subtype0-4 STB stock coordinates; not full room allocation or pool equivalence.'),indent=2)+'\n').encode());print('PASS',len(rows),'native milestone gates;16 native shop levels;default stock counts2/3/4/5/6')
if __name__=='__main__':main()
