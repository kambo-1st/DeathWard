#!/usr/bin/env python3
"""Pinned basic-shop stock coordinates, original ordinary pricing and red eligibility.
No installed game/process writes. Full stock RNG/discount/collection wrapper omitted.
"""
import argparse,csv,hashlib,importlib.util,io,json,struct
from pathlib import Path
import pefile,capstone
from unicorn.x86_const import *
spec=importlib.util.spec_from_file_location('awards',Path(__file__).with_name('analyze-room-awards.py'))
A=importlib.util.module_from_spec(spec);spec.loader.exec_module(A)
OUT=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d12a-shop-heart/source'
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==A.M.SHA
 pe=pefile.PE(data=raw);f=A.NativeAwards(pe,raw);u=f.u;n=f.n
 path=A.M.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3/rooms/00.special rooms.stb';blob=path.read_bytes();offset=8;selected=None
 def take(fmt):
  nonlocal offset
  v=struct.unpack_from(fmt,blob,offset);offset+=struct.calcsize(fmt);return v
 assert blob[:4]==b'STB1'
 for _ in range(struct.unpack_from('<I',blob,4)[0]):
  kind,variant,subtype,difficulty,length=take('<IIIBH');name=blob[offset:offset+length].decode();offset+=length
  weight,width,height,shape,doors,count=take('<fBBBBH');door_rows=[take('<hh?') for _ in range(doors)];slots=[]
  for ordinal in range(count):
   x,y,choices=take('<hhB');slots.append(dict(ordinal=ordinal,x=x,y=y,choices=[dict(zip(('type','variant','subtype','weight'),take('<HHHf'))) for _ in range(choices)]))
  if (kind,variant,subtype)==(2,0,0):selected=dict(type=kind,variant=variant,subtype=subtype,name=name,difficulty=difficulty,weight=weight,width=width,height=height,shape=shape,doors=door_rows,slots=slots)
 assert offset==len(blob) and selected
 assert [(s['x'],s['y']) for s in selected['slots'] if s['choices']==[dict(type=5,variant=150,subtype=0,weight=1.)]]==[(5,4),(7,4)]
 OUT.mkdir(parents=True,exist_ok=True)
 def save(name,data):
  p=OUT/name
  if args.check:assert p.read_bytes()==data,name
  else:p.write_bytes(data)
 def table(name,columns,rows):
  out=io.StringIO();w=csv.writer(out,lineterminator='\n');w.writerow(columns);w.writerows(rows);save(name,out.getvalue().encode())
 f.write(f.ROOM+8,2);f.write(f.ROOM+4,f.ROOM+0x1000)
 prices=[]
 for seed in [1,42,12345,0x7fffffff,0xffffffff]:
  f.write(f.ROOM+0x1058,seed)
  for subtype in (1,2):
   for slot in range(6):
    sp=n.STACK+0x9000;u.mem_write(sp,struct.pack('<4I',n.STOP,10,subtype,slot));u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,f.ROOM);f.run(0x7d0950)
    result=u.reg_read(UC_X86_REG_EAX);assert result==3;prices.append([seed,10,subtype,slot,result])
 eligible=[]
 for capacity in [0,2,6,12,24]:
  for hp in range(capacity+1):
   f.write(n.PLAYER+0x1290,capacity);f.write(n.PLAYER+0x1294,hp)
   sp=n.STACK+0x9000;f.write(sp,n.STOP);u.reg_write(UC_X86_REG_ESP,sp);u.reg_write(UC_X86_REG_ECX,n.PLAYER);f.run(0x786d30)
   result=u.reg_read(UC_X86_REG_EAX)&255;assert result==int(hp<capacity);eligible.append([capacity,hp,result])
 table('native-prices.csv',['room_seed','variant','subtype','shop_slot','ordinary_price'],prices)
 table('native-red-admission.csv',['red_capacity','red_health','can_collect'],eligible)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
 for name,a,b in [('ordinary-price',0x7d0950,0x7d0c31),('red-admission',0x786d30,0x786d80),('red-capacity',0x6b1b40,0x6b1b7a),('red-amount',0x6bfa0c,0x6bfa74),('coin-affordability',0x6be82e,0x6be861)]:
  data=pe.get_data(a-0x400000,b-a);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(data,a))+'\n').encode());windows.append(dict(name=name,start=hex(a),end=hex(b),sha256=hashlib.sha256(data).hexdigest()))
 manifest=dict(version='Repentance 1.7.9b',executable_sha256=A.M.SHA,room_file=str(path.relative_to(A.M.ROOT)),room_sha256=hashlib.sha256(blob).hexdigest(),layout=selected,price_cases=len(prices),admission_cases=len(eligible),windows=windows,scope='Whole original ordinary Room pricing function, supplied shop/descriptor/empty inventory and default ordinary character. Red-admission helper executes original capacity/type helpers. Basic shop STB decoded completely. D12a implements only the red-heart stock slot at (7,4); pinning this outcome is a bounded override, not native generic-shop-item150 resolution or shop-level selection. Other stock, machines, source rocks/shopkeeper, sales/discounts/Restock/characters/full actor physics are not enabled or accepted.',full_native_acceptance=False)
 save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode());print(f'PASS {len(prices)} native ordinary prices, {len(eligible)} red-admission cases and basic-shop STB stock positions')
if __name__=='__main__':main()
