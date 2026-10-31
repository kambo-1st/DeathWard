#!/usr/bin/env python3
"""Pin Gusher/Pacer controller evidence; shared-type branches need separate review."""
import argparse
import hashlib
import json
import struct
from pathlib import Path
import capstone
import pefile

ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/headless'
INSTALL=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth')
EXE_SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def sha(data):return hashlib.sha256(data).hexdigest()
def main():
    parser=argparse.ArgumentParser();parser.add_argument('--check',action='store_true');args=parser.parse_args()
    def save(path,data):
        if args.check or path.exists():assert path.read_bytes()==data,path
        else:path.parent.mkdir(parents=True,exist_ok=True);path.write_bytes(data)
    raw=(INSTALL/'isaac-ng.exe').read_bytes();assert sha(raw)==EXE_SHA
    pe=pefile.PE(data=raw,fast_load=True);read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
    decoder=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    index=read(0x69abc0+11-10,1)[0];case,=struct.unpack('<I',read(0x69a7f8+4*index,4))
    assert case==0x699cfb
    assert any(i.mnemonic=='call' and i.op_str=='0x4f8e40' for i in decoder.disasm(read(case,12),case))
    start,end=0x4f8e40,0x4f9a6e
    blob=read(start,end-start);instructions=list(decoder.disasm(blob,start))
    assert instructions[-1].address+instructions[-1].size==end
    assert any(i.address==0x4f9a51 and i.mnemonic=='ret' for i in instructions)
    assert instructions[-1].mnemonic=='jmp' and instructions[-1].op_str=='0x4f9a34'
    # The final branch after RET is reached from an earlier conditional jump.
    # Cutting at the first RET would lose live shared-controller code.
    text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in instructions)+'\n'
    path=OUT/'source/controller.asm';save(path,text.encode())
    manifest={'baseline':'Installed Repentance1.7.9b','executable_sha256':EXE_SHA,
        'dispatch':{'type':11,'index':index,'case':hex(case),'controller':hex(start)},
        'window':{'start':hex(start),'end_exclusive':hex(end),'raw_sha256':sha(blob),'path':str(path.relative_to(ROOT)),'sha256':sha(text.encode())},
        'scope':'Source-only preflight. Includes shared types210,211,238,280; those branches are not automatically Gusher/Pacer behavior.',
        'constants':{},'strings':{}}
    for name,address,expected in [('projectile_speed',0xb6a8f4,5),('retention_before_random_walk',0xb6a53c,.75),
                                 ('cosmetic_period',0xb6a974,10),('blood_scale_min',0xb6a350,.2),('blood_scale_range',0xb6a3b0,.3)]:
        value,=struct.unpack('<f',read(address,4));assert abs(value-expected)<1e-6
        manifest['constants'][name]={'address':hex(address),'value':value}
    for address in [0xb41240,0xb42efc]:manifest['strings'][hex(address)]=read(address,64).split(b'\0')[0].decode()
    save(OUT/'source/manifest.json',(json.dumps(manifest,indent=2)+'\n').encode())
    ref=json.loads((ROOT/'docs/research/isaac-mechanics-reference.json').read_text())
    records=[r for r in ref['records'] if r.get('key','').startswith('11.')]
    assert {r['key'] for r in records}=={'11.0.0','11.1.0'}
    save(OUT/'source/records.json',(json.dumps(records,indent=2)+'\n').encode())
    print(json.dumps({'pass':True,'check':args.check,'instructions':len(instructions),'scope':'source only; runtime unchanged'}))
if __name__=='__main__':main()
