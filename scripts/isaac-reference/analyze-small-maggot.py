#!/usr/bin/env python3
"""Pin Small Maggot constants/helpers against the installed 1.7.9b executable."""
import argparse, hashlib, json, struct
from pathlib import Path
import capstone, pefile

ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/rotten-gaper/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
    digest=lambda b:hashlib.sha256(b).hexdigest()
    raw=EXE.read_bytes();assert digest(raw)==SHA
    pe=pefile.PE(data=raw,fast_load=True)
    read=lambda a,n:pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase,n)
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    def save(p,b):
        if args.check or p.exists():assert p.read_bytes()==b,p
        else:p.parent.mkdir(parents=True,exist_ok=True);p.write_bytes(b)
    d={'baseline':'Installed Repentance 1.7.9b','executable_sha256':SHA,'constants':{},'helpers':[],
       'scope':'Normal Small Maggot853.0.0 ground behavior. Shared thrown, variant10, special room and status branches require their own validation.'}
    for name,a,want in [('retention',0xb6a560,.8),('normal_force_multiplier',0xb6a614,1),
                       ('targeted_force_multiplier',0xb6a7b0,2),('lookahead',0xb6a910,6),
                       ('obstacle_turn_max',0xb6aae4,90),('obstacle_turn_range',0xb6ab88,180),
                       ('curve_range',0xb6a8cc,4),('force_minimum',0xb6a304,.15),
                       ('force_range',0xb6a3b0,.3),('alert_range',0xb6aad4,80)]:
        v,=struct.unpack('<f',read(a,4));assert abs(v-want)<1e-6
        d['constants'][name]={'address':hex(a),'value':v}
    d['animation_table']={'address':'0x4c50a0','targets':[hex(x) for x in struct.unpack('<4I',read(0x4c50a0,16))]}
    assert d['animation_table']['targets']==['0x4c4dc9','0x4c4e3c','0x4c4eae','0x4c4f20']
    d['strings']={hex(a):read(a,64).split(b'\0')[0].decode() for a in
                  [0xb42410,0xb42418,0xb423f4,0xb42404,0xb42438,0xb4244c,0xb4034c]}
    for name,a,b in [('small-maggot-global-interval',0x684790,0x6847db),
                     ('small-maggot-player-undetectable',0x786be0,0x786c39),
                     ('small-maggot-target',0x695680,0x695a26),
                     ('small-maggot-base-movement',0x686406,0x686497)]:
        blob=read(a,b-a);ops=list(md.disasm(blob,a))
        assert ops[-1].address+ops[-1].size==b
        text=('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in ops)+'\n').encode()
        p=OUT/(name+'.asm');save(p,text)
        d['helpers'].append({'start':hex(a),'end_exclusive':hex(b),'raw_sha256':digest(blob),'path':str(p.relative_to(ROOT)),'sha256':digest(text)})
    save(OUT/'small-maggot-details.json',(json.dumps(d,indent=2)+'\n').encode())
    print(json.dumps({'pass':True,'check':args.check,'helpers':len(d['helpers']),'constants':len(d['constants'])}))
if __name__=='__main__':main()
