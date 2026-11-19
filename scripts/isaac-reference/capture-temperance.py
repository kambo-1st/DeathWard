#!/usr/bin/env python3
"""Bounded installed normal-mode Temperance, machine, IV Bag and Blood Bag evidence."""
import argparse,csv,hashlib,importlib.util,io,json,struct,xml.etree.ElementTree as ET
from pathlib import Path
import pefile,capstone
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import *
spec=importlib.util.spec_from_file_location('awards',Path(__file__).with_name('analyze-room-awards.py'));A=importlib.util.module_from_spec(spec);spec.loader.exec_module(A)
def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==A.M.SHA;pe=pefile.PE(data=raw)
 out=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d14a9-temperance/source';out.mkdir(parents=True,exist_ok=True)
 def save(name,data):
  p=out/name
  if args.check:assert p.read_bytes()==data,name
  else:p.write_bytes(data)
 def csvfile(name,cols,rows):
  buf=io.StringIO();w=csv.writer(buf,lineterminator='\n');w.writerow(cols);w.writerows(rows);save(name,buf.getvalue().encode())
 f=A.NativeAwards(pe,raw);n=f.n;u=f.u;b=n.ebp;rng=f.HEAP+0x3000;machine=f.HEAP+0x4000;unlocked=eligible=True
 stop=[0x63b5c8,0x63b778,0x63b462,0x63b892,0x5a36ff,0x77cb3f,0x63ea6a,0x63ee90]
 spawns=[];damage=[]
 hosted={0x427900,0x701d40,0x700ad0,0x41c4a0,0x884da0,0x68d750,0x4023f0,0x7cf240,0x422e20,0x4122a0,0x300e000}
 def host(u,a,size,data):
  if a in stop:u.emu_stop();return
  sp=u.reg_read(UC_X86_REG_ESP);ret=f.integer(sp);val=0;count=0
  if a==0x427900:val=f.ITEMS+0x10000;count=8 if f.integer(sp+4)==135 else 4
  elif a==0x701d40:val=0 # Child's Heart absent from current supported trinket pool.
  elif a==0x700ad0:val=int(eligible)
  elif a==0x41c4a0:val=f.ITEMS+0x10000;count=4
  elif a==0x884da0:val=int(unlocked)
  elif a==0x68d750:count=16
  elif a==0x4023f0:val=f.ROOM
  elif a==0x7cf240:
   val=f.integer(sp+4);u.mem_write(val,struct.pack('<2f',100.,200.));count=20
  elif a==0x422e20:
   v=struct.unpack('<7I',u.mem_read(sp+4,28));spawns.append(v);val=machine;count=28
  elif a==0x4122a0:count=8
  elif a==0x300e000:
   v=struct.unpack('<5I',u.mem_read(sp+4,20));damage.append(v);count=20;val=1
  u.reg_write(UC_X86_REG_EAX,val);u.reg_write(UC_X86_REG_ESP,sp+4+count);u.reg_write(UC_X86_REG_EIP,ret)
 # n.STOP area already mapped; controlled virtual TakeDamage endpoint.
 for addr in stop+list(hosted):u.hook_add(UC_HOOK_CODE,host,begin=addr,end=addr)
 def setup(seed):
  u.reg_write(UC_X86_REG_EBP,b);u.reg_write(UC_X86_REG_ESP,b-0x2000);u.reg_write(UC_X86_REG_EBX,rng);u.reg_write(UC_X86_REG_EDI,machine);u.reg_write(UC_X86_REG_ESI,n.PLAYER)
  u.mem_write(rng,struct.pack('<4I',seed,1,11,6));f.write(b-0xa0,n.PLAYER)
 rows=[]
 for unlocked in [False,True]:
  for eligible in [False,True]:
   for seed in [(i*0x9e3779b9)&0xffffffff for i in range(1,257)]+[20,42,1,0xffffffff]:
    setup(seed);u.emu_start(0x63b435,0x63b892,count=100000);end=u.reg_read(UC_X86_REG_EIP)
    assert end in (0x63b5c8,0x63b778)
    item=u.reg_read(UC_X86_REG_ESI) if end==0x63b5c8 else 0;coins=f.integer(b-0xa0) if not item else 0
    rows.append([seed,int(unlocked),int(eligible),item,coins,f.integer(rng)])
 csvfile('native-machine.csv',['seed','blood_bag_unlocked','iv_bag_available','item','coin_actors','after_seed'],rows)
 iv=[]
 for seed in range(1,257):
  setup(seed);f.write(b-0x588,n.PLAYER);u.mem_write(n.PLAYER+0x334,struct.pack('<4I',seed,1,11,6));u.emu_start(0x5a35d6,0x5a36ff,count=100000)
  assert u.reg_read(UC_X86_REG_EIP)==0x5a36ff;iv.append([seed,u.reg_read(UC_X86_REG_EDI),f.integer(n.PLAYER+0x334)])
 csvfile('native-iv-coins.csv',['seed','coin_actors','after_seed'],iv)
 cards=[]
 for seed in [1,42,12345,0xffffffff]:
  setup(seed);spawns.clear();u.reg_write(UC_X86_REG_EDI,n.PLAYER);u.reg_write(UC_X86_REG_ESI,rng);u.emu_start(0x777b99,0x77cb3f,count=100000)
  assert len(spawns)==1 and spawns[0][:2]==(6,2) and spawns[0][5]==0
  cards.append(dict(seed=seed,spawn_type=6,spawn_variant=2,spawn_subtype=0,spawn_seed=spawns[0][6],next_seed=f.integer(rng)))
 save('native-card.json',(json.dumps(cards,indent=2)+'\n').encode())
 # Original contact gate requests one half-heart with RED_HEARTS flag32 and supplied cooldown30.
 gates=[];vt=f.HEAP+0x9000;f.write(n.PLAYER,vt);f.write(vt+0x20,0x300e000);f.write(machine+0x28,6);f.write(machine+0x2c,2)
 for hurt in [0,1,14,15,30,60]:
  setup(1);damage.clear();f.write(n.PLAYER+0x1308,hurt);u.reg_write(UC_X86_REG_EBX,n.PLAYER);u.emu_start(0x63e957,0x63ea6a,count=100000)
  if damage:
   v=damage[0];assert struct.unpack('<f',struct.pack('<I',v[0]))[0]==1 and v[1]==32 and v[4]==30
  gates.append([hurt,int(bool(damage)),f.integer(n.PLAYER+0x1308)])
 csvfile('native-contact.csv',['hurt_counter','requests_damage','after_hurt_counter'],gates)
 f.write(n.PLAYER+0x15fc,f.HEAP+0xa000);f.write(n.PLAYER+0x1600,f.HEAP+0xa000+200)
 blood=[]
 for copies in [0,1,2,5,8]:
  setup(1);f.write(f.ITEMS+0xf1000+119*4,copies);f.write(b-0x428,n.PLAYER);f.write(b-0x440,n.PLAYER+0x1450);n.write_float(b-0x43c,1);u.mem_write(b-0x441,b'\0');n.write_float(n.PLAYER+0x1864,1);u.reg_write(UC_X86_REG_EDI,n.PLAYER);u.reg_write(UC_X86_REG_ESI,n.PLAYER+0x1450);u.reg_write(UC_X86_REG_EAX,n.PLAYER)
  u.emu_start(0x73394d,0x7340c9,count=500000);speed=n.read_float(n.PLAYER+0x14ac);assert abs(speed-(1+.3*copies))<.00001;blood.append([copies,speed])
 csvfile('native-blood-bag-speed.csv',['copies','speed_before_final_caps'],blood)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
 for name,a,z in [('card',0x777b99,0x777bfe),('card-spawn',0x777a93,0x777aab),('contact-payment',0x63e928,0x63ea6a),('payment-state',0x63ee09,0x63ee8d),('payout',0x63b411,0x63b892),('cooldown',0x639fae,0x639fd2),('prize-admission',0x63aa21,0x63ab31),('prize-finish',0x63e3fe,0x63e448),('iv-bag',0x5a355b,0x5a3762),('blood-bag-speed',0x733a6f,0x733b26)]:
  blob=pe.get_data(a-0x400000,z-a);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,a))+'\n').encode());windows.append(dict(name=name,start=hex(a),end=hex(z),sha256=hashlib.sha256(blob).hexdigest()))
 xml=A.M.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3'
 items=[dict(x.attrib) for x in ET.parse(xml/'items.xml').getroot() if x.tag in ['passive','active'] and x.get('id') in ['119','135']]
 card=next(dict(x.attrib) for x in ET.parse(xml/'pocketitems.xml').getroot() if x.get('id')=='15')
 manifest=dict(baseline='Installed Repentance1.7.9b',executable_sha256=A.M.SHA,card=card,items=items,cases=dict(machine=len(rows),iv_coins=len(iv),card=len(cards),contact=len(gates),blood_bag_speed=len(blood)),windows=windows,scope="Normal ordinary Isaac; original RNG/selection with supplied unlock/pool inputs; Child's Heart pool absent. Original card spawn and damage request slices with hosted world/factory/virtual damage. Not full native use/damage/factory/scheduler/global-RNG/character/synergy acceptance.",full_native_acceptance=False)
 save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode());print('PASS',manifest['cases'])
if __name__=='__main__':main()
