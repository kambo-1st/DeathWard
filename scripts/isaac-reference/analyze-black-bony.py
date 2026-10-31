#!/usr/bin/env python3
"""Verify/preserve installed1.7.9b Black Bony evidence; never replace a report."""
import argparse, hashlib, json, re, struct
from pathlib import Path
import capstone, pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/black_bony/source'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
BASELINE='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--check',action='store_true');args=p.parse_args()
    data=EXE.read_bytes();assert hashlib.sha256(data).hexdigest()==BASELINE
    pe=pefile.PE(data=data);base=pe.OPTIONAL_HEADER.ImageBase
    read=lambda a,n:pe.get_data(a-base,n)
    u32=lambda a:struct.unpack('<I',read(a,4))[0]
    decoder=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    idx=read(0x69abc0+277-10,1)[0];case=u32(0x69a7f8+4*idx)
    dis=list(decoder.disasm(read(case,12),case));assert (dis[1].mnemonic,dis[1].op_str)==('call','0x525830')
    assert read(0xb54e44,11)==b'BombDamage\0'
    binding=bytes.fromhex('6850176d0068444eb500');assert data.count(binding)==1
    assert read(0x80a081,len(binding))==binding
    # Installed named IsPlaying signature verifies pointer+flag offsets, without
    # trusting later-edition structure offsets alone.
    decl=ROOT/'reference/isaac-mechanics-study/code/TeamREPENTOGON__REPENTOGON/348e5d0ea277760fc87af420d88e2c7909c9167e/libzhl/functions/ANM2.zhl'
    sig=re.search(r'"([0-9a-f?]+)":\s*[^;\n]*ANM2::IsPlaying\(',decl.read_text())[1]
    pattern=b''.join(b'.' if v=='??' else re.escape(bytes.fromhex(v)) for v in re.findall('..',sig))
    hits=list(re.finditer(pattern,data,re.S));assert len(hits)==1 and base+pe.get_rva_from_offset(hits[0].start())==0x405640
    assert read(0x405643,3)==bytes.fromhex('8b4134') and read(0x40564a,4)==bytes.fromhex('80794400')
    assert read(0x5265c3,4)==bytes.fromhex('837f7000') and read(0x5265c9,7)==bytes.fromhex('80bf8000000000')
    assert read(0x5265e3,7)==bytes.fromhex('83bf6003000002')
    assert struct.unpack('<4f',read(0xb6c1b0,16))==(.4000000059604645,)*3+(1.,)
    assert read(0x52683c,8)==bytes.fromhex('c744240400007042') # radius60
    assert read(0x526844,7)==bytes.fromhex('c7042400002042') # damage40
    source='docs/reports/isaac-enemy-port/bony_review/animations/manifest.json'
    metadata=json.loads((ROOT/source).read_text());black=next(x for x in metadata['files'] if '277.000' in x['source'])
    assert hashlib.sha256((ROOT/black['path']).read_bytes()).hexdigest()==black['sha256']
    assert black['info']['Fps']=='30'
    for a in black['animations']:
        if a['attributes']['Name'].startswith('Attack'):
            assert a['attributes']['FrameNum']=='13' and a['triggers']==[{'EventId':'0','AtFrame':'4'}]
    windows=[('dispatch',case,case+12),('playing',0x405640,0x405695),('repeat_gate',0x5265c3,0x52668a),
             ('death_blast',0x52680e,0x526887),('bomb_api_binding',0x80a081,0x80a090)]
    manifest={'baseline':'Repentance1.7.9b','executable_sha256':BASELINE,'tuple':'277.0.0','ai':'0x525830',
      'animation_manifest':source,'animation_sha256':black['sha256'],'is_playing_signature':sig,
      'bomb_damage_binding':{'name':'0xb54e44','function':'0x6d1750','registration':'0x80a081','bytes':binding.hex()},
      'findings':['Repeat gate checks animation pointer and playing flag, not the Shoot event. Counter starts0 and repeats while<2: three complete13-frame animations.',
        'Each Shoot event aims at the current player target, retaining ordinary speed10 and bone variant1; black projectile color multiplier.4, body.3.',
        'Death calls named BombDamage with40damage/60radius/lineCheck=true/sourceNPC. Local128damage/radius6/player20 are explicit world/damage conversions.'],
      'windows':[]}
    if not args.check:assert not (OUT/'manifest.json').exists();OUT.mkdir(parents=True,exist_ok=True)
    for name,start,end in windows:
        raw=read(start,end-start);text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in decoder.disasm(raw,start))+'\n'
        path=OUT/(name+'.asm')
        if args.check:assert path.read_text()==text
        else:path.write_text(text)
        manifest['windows'].append({'path':str(path.relative_to(ROOT)),'start':hex(start),'end':hex(end),'sha256':hashlib.sha256(path.read_bytes()).hexdigest(),'raw_sha256':hashlib.sha256(raw).hexdigest()})
    if args.check:assert json.loads((OUT/'manifest.json').read_text())==manifest
    else:(OUT/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
    print(json.dumps({'result':'pass','tuple':'277.0.0','windows':len(windows),'mode':'check' if args.check else 'preserved'}))
if __name__=='__main__':main()
