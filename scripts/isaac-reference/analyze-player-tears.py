#!/usr/bin/env python3
"""Execute pinned ordinary tear birth/flight arithmetic; no full-game acceptance."""
import argparse,csv,hashlib,importlib.util,io,json,struct
from pathlib import Path
import capstone,pefile
from unicorn.x86_const import UC_X86_REG_EAX,UC_X86_REG_EDI,UC_X86_REG_ESI,UC_X86_REG_EBP,UC_X86_REG_ESP,UC_X86_REG_EFLAGS
spec=importlib.util.spec_from_file_location('native_motion',Path(__file__).with_name('analyze-player-motion.py'))
module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
ROOT=module.ROOT;OUT=ROOT/'docs/reports/isaac-first-floor-parity/player-tears'
WINDOWS=[('cache_defaults',0x732d05,0x732d33),('birth_jitter',0x757908,0x75795b),
 ('birth_acceleration_range',0x75799f,0x7579d9),('ordinary_flight',0x64d5eb,0x64d64f),
 ('floor_predicate',0x64ab3a,0x64ab4b),('ordinary_death',0x64ac55,0x64ac6c),
 ('time_scale_retention',0x65c960,0x65c98a),('height_render_only',0x6500f0,0x650144),
 ('weapon_velocity',0x95a2a8,0x95a32c)]

def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--check',action='store_true');a=p.parse_args()
 raw=module.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==module.SHA
 pe=pefile.PE(data=raw);native=module.NativeMotion(pe);u=native.u;body=native.PLAYER;player=body+0x4000;b=native.ebp
 OUT.mkdir(parents=True,exist_ok=True)
 def save(name,data):
  f=OUT/name
  if a.check:assert f.read_bytes()==data,name
  else:f.write_bytes(data)
 md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
 for name,start,end in WINDOWS:
  blob=pe.get_data(start-pe.OPTIONAL_HEADER.ImageBase,end-start)
  listing=('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(blob,start))+'\n').encode();save(name+'.asm',listing)
  windows.append({'name':name,'start':hex(start),'end_exclusive':hex(end),'raw_sha256':hashlib.sha256(blob).hexdigest(),'listing_sha256':hashlib.sha256(listing).hexdigest()})
 rows=[];births=[]
 for raw_rng in [0,1,65536,16777216,2147483647,4294967295]:
  native.reset();u.reg_write(UC_X86_REG_EDI,player);u.reg_write(UC_X86_REG_ESI,body)
  u.reg_write(UC_X86_REG_ESP,b-0x2000);u.reg_write(UC_X86_REG_EAX,raw_rng)
  native.write_float(player+0x13c0,0)
  # Start just after the RNG call, fixing its result to exercise conversion.
  native.run(0x75790d,0x75795b)
  initial=native.read_float(body+0x364);births.append({'raw_rng':raw_rng,'initial_falling_speed':initial})
  native.write_float(body+0x360,-23.75);native.write_float(body+0x368,0);native.write_float(body+0x2f4,1)
  for frame in range(60):
   before=native.read_float(body+0x360);speed_before=native.read_float(body+0x364)
   u.reg_write(UC_X86_REG_EDI,body);native.run(0x64ab3a,0x64ab49)
   # Native 'ja' predicate for finite ordinary height > -5. Native flag-0
   # continuation reaches 64ac55 and the source death call (preserved above).
   grounded=(u.reg_read(UC_X86_REG_EFLAGS)&0x41)==0
   assert grounded==(before>-5)
   if grounded:
    rows.append([raw_rng,frame,before,speed_before,before,speed_before,1]);break
   u.reg_write(UC_X86_REG_EBP,b);u.reg_write(UC_X86_REG_ESP,b-0x2000)
   native.run(0x64d5eb,0x64d64a)
   # SetHeight's first store is exact; omit its rendering/global-room callback.
   after=native.read_float(u.reg_read(UC_X86_REG_ESP));native.write_float(body+0x360,after)
   rows.append([raw_rng,frame,before,speed_before,after,native.read_float(body+0x364),0])
 output=io.StringIO();w=csv.writer(output,lineterminator='\n');w.writerow(['raw_rng','invocation','height_before','falling_before','height_after','falling_after','grounded_before_flight']);w.writerows(rows);save('native-flight.csv',output.getvalue().encode())
 m={'version':'Repentance 1.7.9b','exe_sha256':module.SHA,'method':'Unicorn 2.1.4 executing original x86/SSE; fixed raw RNG results; no instruction patches or native helper stubs','scope':'ordinary zero-flag birth jitter and flight arithmetic, base cached height/range and floor boundary; NOT whole-game timing, birth ordering, collision, item/flag or RNG-stream acceptance','windows':windows,'births':births,'trace_rows':len(rows),'source_base_cache':{'tear_height':-23.75,'falling_speed_stat':0,'falling_acceleration':0,'tear_range':260},'source_base_launch':'Weapon_Tears multiplies its direction by 10 native coordinate units before inheritance and shot-speed scaling; default shot speed is 1','omitted':'SetHeight room/render callbacks after its exact first logical store; ordinary flag eligibility is inspected source, not an emulated full collision/death lifecycle'}
 save('manifest.json',(json.dumps(m,indent=2)+'\n').encode());print(json.dumps({'pass':True,'check':a.check,'cases':len(births),'rows':len(rows),'source_sha256':module.SHA}))
if __name__=='__main__':main()
