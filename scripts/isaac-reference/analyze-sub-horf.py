#!/usr/bin/env python3
"""Preserve bounded native ordinary Sub Horf movement/cadence evidence."""
import argparse,hashlib,json,struct
from pathlib import Path
import capstone,pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/sub-horf/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--check',action='store_true');args=p.parse_args()
raw=EXE.read_bytes();digest=hashlib.sha256(raw).hexdigest()
assert digest=='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
pe=pefile.PE(data=raw);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
slot=read(0x69abc0+812-10,1)[0];case=struct.unpack('<I',read(0x69a7f8+4*slot,4))[0]
assert case==0x69a007
ins={i.address:(i.mnemonic,i.op_str) for i in md.disasm(read(case,12),case)}
assert ins[0x69a009]==('call','0x54d470')
constants=[]
for name,address,expected in [('normal_interval_numerator',0xb6a9c8,20),('tainted_interval_numerator_not_ported',0xb6a8f4,5),('body_friction',0xb6a5f8,.97),('shot_speed',0xb6a974,10),('movement_threshold',0xb6a214,.01),('max_native_hit_speed',0xb6a940,8)]:
 value=struct.unpack('<f',read(address,4))[0];assert abs(value-expected)<1e-6
 constants.append(dict(name=name,address=hex(address),value=value))
start,end=0x54d470,0x54de41;data=read(start,end-start)
text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(data,start))+'\n'
OUT.mkdir(parents=True,exist_ok=True);path=OUT/'native-update.asm'
result=dict(executable_sha256=digest,baseline='Repentance1.7.9b',function_start=hex(start),function_end=hex(end),raw_sha256=hashlib.sha256(data).hexdigest(),constants=constants,
 observations=['Ordinary812.0 dispatches to shared SubHorf update0x54d470; variant1 has separate pursuit and cadence branches, and is not enabled by this port.',
 'Ordinary rotation at0x54db50 is driven by planar velocity length, adds twice native speed to I1, reverses sign for negative X velocity and wraps degrees.',
 'Ordinary shot test at0x54dc44 requires speed>.01 and counterB10>2*max(1,int(20/speed)). It emits in the previously computed facing direction with planar native speed10, then resets the counter.',
 'Final update multiplies friction by.97. Native knockback initialization has further special source/status handling; local projectile/explosion impulse strengths36/60 are deliberate DeathWard tuning.',
 'Source XML14HP,0stageHP,mass3 are preserved; DeathWard HP conversion3.2 yields44.8 before the global regular multiplier.',
 'One final-death shot is supported by the supplied Horf wiki prose. Its exact native death angle/vertical packet was not recovered here. The local shot uses current facing and the standing-target3Darc conversion.'],
 limits=['Static native evidence, not a controlled Isaac replay.','The shared function includes Tainted/controlled-source branches that are preserved as context but not implemented by this ordinary812.0 port.','3Darc, local hit strengths, bounded shot admission and status policies remain explicit adaptations.'])
if args.check:
 assert path.read_text()==text
 assert json.loads((OUT/'manifest.json').read_text())==result
else:
 path.write_text(text);(OUT/'manifest.json').write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps(dict(result='pass',check=args.check,constants=len(constants),native_function='0x54d470')))
