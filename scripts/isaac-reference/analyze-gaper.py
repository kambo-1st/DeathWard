#!/usr/bin/env python3
"""Pin Gaper controller evidence; Rotten Gaper dispatch and shared types need separate review."""
import argparse
import hashlib
import json
import struct
from pathlib import Path
import capstone
import pefile

ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/gaper'
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
    index=read(0x69abc0+10-10,1)[0];case,=struct.unpack('<I',read(0x69a7f8+4*index,4))
    assert case==0x699ffb
    assert any(i.mnemonic=='call' and i.op_str=='0x4f6ee0' for i in decoder.disasm(read(case,12),case))
    start,end=0x4f6ee0,0x4f8668
    blob=read(start,end-start);instructions=list(decoder.disasm(blob,start))
    assert instructions[-1].address+instructions[-1].size==end
    assert instructions[-1].mnemonic=='ret'
    text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in instructions)+'\n'
    path=OUT/'source/controller.asm';save(path,text.encode())
    manifest={'baseline':'Installed Repentance1.7.9b','executable_sha256':EXE_SHA,
        'dispatch':{'type':10,'index':index,'case':hex(case),'controller':hex(start)},
        'window':{'start':hex(start),'end_exclusive':hex(end),'raw_sha256':sha(blob),'path':str(path.relative_to(ROOT)),'sha256':sha(text.encode())},
        'scope':'Source-only preflight. Type10 variant3 delegates to4c70e0. Other shared-type branches are not automatically ordinary Gaper behavior.',
        'constants':{},'strings':{}}
    value,=struct.unpack('<f',read(0xb6aef8,4));assert value==-25
    manifest['constants']['overkill']={'address':'0xb6aef8','value':value}
    save(OUT/'source/manifest.json',(json.dumps(manifest,indent=2)+'\n').encode())
    ref=json.loads((ROOT/'docs/research/isaac-mechanics-reference.json').read_text())
    records=[r for r in ref['records'] if r.get('key','').startswith('10.')]
    assert {r['key'] for r in records} >= {'10.0.0','10.1.0','10.2.0','10.3.0'}
    save(OUT/'source/records.json',(json.dumps(records,indent=2)+'\n').encode())
    # Resolve both virtual Morph calls from Entity_NPC's actual RTTI/vtable.
    # Neither is an AI-state initializer: +5c is appearance, +60 reloads NPC
    # configuration/animation through the base and sprite helpers pinned here.
    col=struct.unpack('<5I',read(0xb6d958,20));assert col==(0,0,0,0xbeab70,0xb6d920)
    assert read(0xbeab78,64).split(b'\0')[0]==b'.?AVEntity_NPC@IsaacRepentance@@'
    assert struct.unpack('<I',read(0xb49394,4))[0]==0xb6d958
    assert struct.unpack('<I',read(0xb49398+0x5c,4))[0]==0x697e30
    assert struct.unpack('<I',read(0xb49398+0x60,4))[0]==0x692960
    windows=[]
    for name,start,end in [('morph',0x697c60,0x697e21),('npc-appearance',0x697e30,0x698093),
            ('npc-config',0x692960,0x692f73),('base-config',0x681ea0,0x682190),
            ('npc-sprite',0x692080,0x692954)]:
        blob=read(start,end-start);ops=list(decoder.disasm(blob,start))
        assert ops[-1].address+ops[-1].size==end and ops[-1].mnemonic=='ret',name
        assert not any('0xab4]' in i.op_str or '0xaf0]' in i.op_str for i in ops),name
        listing='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in ops)+'\n'
        path=OUT/f'source/{name}.asm';save(path,listing.encode())
        windows.append({'name':name,'start':hex(start),'end_exclusive':hex(end),'raw_sha256':sha(blob),
            'path':str(path.relative_to(ROOT)),'sha256':sha(listing.encode())})
    evidence={'baseline':'Installed Repentance1.7.9b','executable_sha256':EXE_SHA,
        'rtti':{'type_descriptor':'0xbeab70','complete_object_locator':'0xb6d958','vtable':'0xb49398',
            'plus_5c':'0x697e30','plus_60':'0x692960'},'windows':windows,
        'finding':'Morph and the resolved configuration/sprite helpers do not reset AI State+ab4 or ProjectileCooldown+af0. The Gaper caller retains State4 and explicitly writes20+RNG%20 after morph; headless spawn initialization must not redraw it.',
        'limits':'Ordinary non-champion path. Champion/status helpers and mod callbacks are not claimed as ported; DeathWard retains its seeded PRNG rather than reproducing Isaac RNG streams.'}
    save(OUT/'source/morph-initialization.json',(json.dumps(evidence,indent=2)+'\n').encode())
    print(json.dumps({'pass':True,'check':args.check,'instructions':len(instructions),'scope':'source verification only; does not certify runtime parity'}))
if __name__=='__main__':main()
