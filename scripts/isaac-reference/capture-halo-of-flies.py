#!/usr/bin/env python3
"""Bounded original 1.7.9b Halo cache, orbit and contact decisions; supplied actors."""
import argparse,csv,hashlib,importlib.util,io,json,struct,xml.etree.ElementTree as ET
from pathlib import Path
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import *
spec=importlib.util.spec_from_file_location('bobby',Path(__file__).with_name('capture-brother-bobby.py'))
B=importlib.util.module_from_spec(spec);spec.loader.exec_module(B);H=B.H

def main():
 ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
 raw=H.A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==H.A.M.SHA
 pe=H.pefile.PE(data=raw);f=H.A.NativeAwards(pe,raw);n=f.n;u=f.u;b=n.ebp;fam=f.HEAP+0x300000;actor=fam+0x10000
 out=H.A.M.ROOT/'docs/reports/isaac-first-floor-parity/pw-f02-halo-of-flies/source'
 if not args.check:out.mkdir(parents=True,exist_ok=True)
 def save(name,data):
  if args.check:assert (out/name).read_bytes()==data,name
  else:(out/name).write_bytes(data)
 def table(name,header,rows):
  s=io.StringIO();w=csv.writer(s,lineterminator='\n');w.writerow(header);w.writerows(rows);save(name,s.getvalue().encode())
 def reg(r,v):u.reg_write(r,v)
 def frame():reg(UC_X86_REG_EBP,b);reg(UC_X86_REG_ESP,n.STACK+0x9000)
 def block(a,z):u.emu_start(a,z,count=500000);assert u.reg_read(UC_X86_REG_EIP)==z
 # Exact ordinary cache arithmetic. Other effect counts supplied zero.
 counts=[]
 for copies in range(9):
  frame();reg(UC_X86_REG_EAX,copies);reg(UC_X86_REG_ECX,0);reg(UC_X86_REG_ESI,n.PLAYER);f.write(b-0x4ec,10)
  block(0x738828,0x738833);reg(UC_X86_REG_EDI,0);block(0x73883a,0x73884d)
  counts.append([copies,f.integer(u.reg_read(UC_X86_REG_EAX))])
 table('native-count.csv',['copies','count'],counts)
 slot=pe.get_data(0x5f20dc-0x400000+3,1)[0];target=struct.unpack('<I',pe.get_data(0x5f20b0-0x400000+slot*4,4))[0];assert target==0x5f0747
 frame();reg(UC_X86_REG_EDI,fam);block(target,0x5f07ec);assert f.integer(fam+0xcc0)==0
 group=struct.unpack('<5f',pe.get_data(0xbc4530-0x400000,20));assert group[:2]==(25,20)
 angles=[]
 for phase in [0,1.2,3.1415927410125732]:
  for tick in [0,1,5,30,180,300]:
   for parity in [0,1]:
    n.write_float(fam+0xcb0,phase);n.write_float(fam+0xcbc,group[2]);f.write(f.GAME+0x1a30dc,tick);f.write(f.MANAGER+0x4a264,parity)
    frame();reg(UC_X86_REG_EBX,fam);reg(UC_X86_REG_ECX,f.GAME);block(0x5f50aa,0x5f510b)
    value=struct.unpack('<f',struct.pack('<I',u.reg_read(UC_X86_REG_XMM0)&0xffffffff))[0];angles.append([phase,tick,parity,value])
 table('native-orbit.csv',['phase','frame','parity','angle_input'],angles)
 # The original admitted-contact tail marks hostile projectile removal and retains Halo.
 shots=[]
 for variant in [1,33]:
  for kind in [2,9]:
   for flags in [0,0x80000000]:
    u.mem_write(fam,bytes(0x10000));u.mem_write(actor,bytes(0x10000));f.write(fam+0x2c,variant);f.write(actor+0x28,kind);f.write(actor+0x388,flags)
    frame();reg(UC_X86_REG_EDI,fam);reg(UC_X86_REG_ESI,actor)
    def stop(uc,address,size,data):
     if address in (0x609cf4,0x609cf8):uc.emu_stop()
    hook=u.hook_add(UC_HOOK_CODE,stop);u.emu_start(0x6098ca,0x609d36,count=2000);u.hook_del(hook)
    assert u.reg_read(UC_X86_REG_EIP) in (0x609cf4,0x609cf8)
    shots.append([variant,kind,flags,u.mem_read(actor+0x16b,1)[0],u.mem_read(fam+0x16b,1)[0]])
 table('native-shot-contact.csv',['familiar_variant','actor_type','projectile_flags','remove_projectile','remove_familiar'],shots)
 kills=[]
 for kind in [10,13,14,18,25,80,222,256,281,296,868]:
  for variant in [0,2]:
   f.write(actor+0x28,kind);f.write(actor+0x2c,variant);f.write(fam+0x2c,33)
   frame();reg(UC_X86_REG_ESI,actor);reg(UC_X86_REG_EDI,fam);reg(UC_X86_REG_EAX,33)
   def stop(uc,address,size,data):
    if address in (0x6089ea,0x6092f0):uc.emu_stop()
   hook=u.hook_add(UC_HOOK_CODE,stop);u.emu_start(0x6089cf,0x608b64,count=200);u.hook_del(hook)
   at=u.reg_read(UC_X86_REG_EIP);assert at in (0x6089ea,0x6092f0);kills.append([kind,variant,int(at==0x6089ea)])
 table('native-npc-contact.csv',['type','variant','direct_kill'],kills)
 md=H.capstone.Cs(3,4);windows=[]
 for name,a,z in [('count',0x73880b,0x73888e),('group',0x5f072a,0x5f07ec),('formation',0x5f0b99,0x5f0ce4),('orbit-angle',0x5f50aa,0x5f510b),('orbit-position',0x5f521e,0x5f5274),('orbital-ai',0x5ff758,0x5ff7a1),('blocker',0x5efae0,0x5efb67),('projectile-gates',0x6098ca,0x609900),('projectile-removal',0x609a35,0x609b22),('npc-contact',0x6089cf,0x608b64)]:
  blob=pe.get_data(a-0x400000,z-a);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,a))+'\n').encode());windows.append(dict(name=name,start=hex(a),end=hex(z),sha256=hashlib.sha256(blob).hexdigest()))
 source=H.A.M.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3'
 item=next(x.attrib for x in ET.parse(source/'items.xml').getroot() if x.get('id')=='10' and x.tag=='familiar')
 entity=next(x.attrib for x in ET.parse(source/'entities2.xml').getroot() if x.get('id')=='3' and x.get('variant')=='33')
 pool=next(x for x in ET.parse(source/'itempools.xml').getroot() if x.get('Name')=='treasure');entry=next(x.attrib for x in pool if x.get('Id')=='10')
 save('manifest.json',(json.dumps(dict(executable_sha256=H.A.M.SHA,item=item,entity=entity,treasure=entry,orbit_group=0,group_values=group,count_cases=len(counts),orbit_cases=len(angles),projectile_cases=len(shots),npc_cases=len(kills),windows=windows,scope='Supplied ordinary copy count/zero other orbital effects; original init group dispatch, orbit angle before host fmod/trig, projectile contact tail and NPC kill admission. Contact broadphase, full inventory cache/factory/scheduler, synergies and special projectile death effects are not certified. Group0 source radii25/20, speed.045 and angle offset1.5; evenly spaced formation. Halo bypasses ordinary contact damage, retaining special fly-enemy kills.',full_native_acceptance=False),indent=2)+'\n').encode())
 print('PASS',len(counts),'cache counts,',len(angles),'angles,',len(shots),'shot contacts,',len(kills),'NPC contacts')
if __name__=='__main__':main()
