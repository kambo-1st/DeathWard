#!/usr/bin/env python3
"""Bounded installed shop price/category calls; GetCard is supplied as Temperance only."""
import csv,hashlib,importlib.util,io,json,struct
from pathlib import Path
spec=importlib.util.spec_from_file_location('heart',Path(__file__).with_name('capture-shop-heart.py'))
H=importlib.util.module_from_spec(spec);spec.loader.exec_module(H)
A=H.A;raw=A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==A.M.SHA
f=A.NativeAwards(H.pefile.PE(data=raw),raw);u=f.u;n=f.n
f.write(f.ROOM+8,2);f.write(f.ROOM+4,f.ROOM+0x1000)
rows=[]
for seed in (1,42,12345,0x7fffffff,0xffffffff):
 f.write(f.ROOM+0x1058,seed)
 for slot in range(6):
  sp=n.STACK+0x9000;u.mem_write(sp,struct.pack('<4I',n.STOP,300,15,slot));u.reg_write(H.UC_X86_REG_ESP,sp);u.reg_write(H.UC_X86_REG_ECX,f.ROOM);f.run(0x7d0950)
  price=u.reg_read(H.UC_X86_REG_EAX);assert price==5;rows.append([seed,300,15,slot,price])
# Only the category dispatch is under test, not the unrestricted card pool.
u.mem_write(0x701da0,b'\xb8\x0f\0\0\0\xc2\x14\0')
resolved=[]
for slot in range(6):
 u.mem_write(f.ROOM+0x1094+slot*2,struct.pack('<h',6));variant_out,subtype_out=f.HEAP+0x300000,f.HEAP+0x300004
 sp=n.STACK+0x9000;u.mem_write(sp,struct.pack('<5I',n.STOP,slot,variant_out,subtype_out,12345));u.reg_write(H.UC_X86_REG_ESP,sp);u.reg_write(H.UC_X86_REG_ECX,f.ROOM);u.emu_start(0x7d04a0,0x7d063e,count=200000)
 variant,subtype=f.integer(variant_out),u.reg_read(H.UC_X86_REG_EAX);assert (variant,subtype)==(300,15);resolved.append(dict(slot=slot,category=6,variant=variant,subtype=subtype))
root=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d14a9-temperance/source';out=io.StringIO();w=csv.writer(out);w.writerow(['seed','variant','subtype','slot','price']);w.writerows(rows);(root/'native-card-prices.csv').write_text(out.getvalue())
(root/'native-card-shop.json').write_text(json.dumps(dict(exe_sha256=A.M.SHA,prices=30,category_cases=resolved,scope='Original pricing and category6 dispatch through the GetCard return. Stops before later subtype wrappers. Host returns15 from GetCard; full pool, sale, factory, placement and contact wrappers are not verified.'),indent=2)+'\n')
print('PASS 30 native card prices / six category6 dispatches with supplied Temperance pool')
