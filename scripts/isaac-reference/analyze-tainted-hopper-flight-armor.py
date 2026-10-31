#!/usr/bin/env python3
"""Pin bounded installed flight evidence and the still-unimplemented armor path."""
import argparse
import hashlib
import json
import struct
from pathlib import Path
import capstone
import pefile

ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/tainted_hopper/flight-armor-source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
parser=argparse.ArgumentParser();parser.add_argument('--check',action='store_true');args=parser.parse_args()
raw=EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==SHA
pe=pefile.PE(data=raw);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
result=dict(baseline='Installed Repentance1.7.9b',executable_sha256=SHA,constants={},windows=[],
    scope='Physical ring flight plus verified NPC adaptive-history formula. Armor implementation, initial-protection and large-hit claims are NOT certified.')
for name,address,expected in [('flight_retention',0xb6a5a4,.9),('flight_base_accel',0xb6a2cc,.1),
    ('random_fall_width',0xb6a350,.2),('random_fall_center',0xb6a480,.5),
    ('armor_floor',0xb6a2b4,.09),('armor_correction',0xb6a330,.18),('fps',0xb6aa0c,30)]:
    value=struct.unpack('<f',read(address,4))[0];assert abs(value-expected)<1e-6
    result['constants'][name]=dict(address=hex(address),value=value)
assert abs(struct.unpack('<f',struct.pack('<I',0xbd8f5c29))[0]+.07)<1e-6
if not args.check:
    assert not (OUT/'manifest.json').exists();OUT.mkdir(parents=True,exist_ok=True)
for name,start,end in [('ring_fall_modifier',0x515f20,0x515f4c),
    ('projectile_defaults',0x62f1ef,0x62f2d0),('projectile_modifiers',0x6a3059,0x6a3372),
    ('flight_integrator',0x636567,0x6365d5),('time_scale_retention',0x65c960,0x65c98a),
    ('npc_armor_defaults',0x68fbfc,0x68fc1a),('npc_armor_config',0x692a10,0x692a90),
    ('npc_armor_update_call',0x69b66e,0x69b691),('npc_adaptive_armor',0x6adfd0,0x6ae315)]:
    blob=read(start,end-start);instructions=list(md.disasm(blob,start))
    text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in instructions)+'\n'
    path=OUT/(name+'.asm')
    if args.check:assert path.read_text()==text
    else:assert not path.exists();path.write_text(text)
    result['windows'].append(dict(path=str(path.relative_to(ROOT)),start=hex(start),end=hex(end),
        raw_sha256=hashlib.sha256(blob).hexdigest(),sha256=hashlib.sha256(path.read_bytes()).hexdigest()))
if args.check:assert json.loads((OUT/'manifest.json').read_text())==result
else:(OUT/'manifest.json').write_text(json.dumps(result,indent=2)+'\n')
print(json.dumps(dict(result='pass',windows=len(result['windows']))))
