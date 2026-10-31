#!/usr/bin/env python3
"""Pin additional native evidence used by the first-five temporary Charm slice."""
import argparse
import hashlib
import json
from pathlib import Path
import capstone
import pefile

ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/first-floor-batch1/charm/source-runtime'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
BASELINE='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--check',action='store_true');args=parser.parse_args()
    raw=EXE.read_bytes();sha=lambda data:hashlib.sha256(data).hexdigest();assert sha(raw)==BASELINE
    pe=pefile.PE(data=raw);md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    result=dict(executable_sha256=BASELINE,scope=['10.0.0','10.1.0','11.0.0','11.1.0','12.0.0'],windows=[],references=[],findings=[
        'Projectile constructor62f270 writes CollisionDamage2e0=float1. Combined with the ordinary NPC collision+5 branch already preserved, native6HP maps to19.2 DeathWard enemy HP at3.2 scale. Player-target damage remains the existing local10HP, before the existing player damage multiplier.',
        'First temporary Charm calls680df0, which clears two cached vector pairs368/36c and370/374; it does not grant FRIENDLY or zero the actual velocity2b8/2bc.',
        'NPC damage retaliation6ac3e0 is gated by item0x187 (391, Betrayal in preserved items.xml). Do not invent unconditional retaliation as part of ordinary Charm. The helper6909f0 prefers nearer targets and stores duration150 from this call, but full item production remains separate work.',
        'Native target-affiliation predicate6aeb40 immediately permits a temporary CHARM actor (CHARM without FRIENDLY), including player fallback. The retained shared acquisition path calls this predicate. Permanent conversion has a different branch and is explicitly unsupported by this runtime slice.'
    ],adaptations=[
        'Positive temporary Charm only. Negative permanent conversion returns false and CLI rejects it; permanent followers and persistence remain unfinished, not simulated by abs(duration).',
        'The existing 3D actor representation maps candidate collision/visibility exclusions to existing room-hazard, buried, teleport, thrown and returning-body states. Isaac-specific room flag7185 and external decoy/item targeting remain unported.',
        'Gaper pursuit, Horf acquisition/current Shoot aim and Fear/Shrink evasion use the resolved target. Headless random movement remains unchanged. Confusion retains its own random target/suppression rules.',
        'Temporary shots retain NPC flight and player damage, with independent enemy-hit flag and enemy-target damage. Selected Gusher payloads retain policy through capacity retry; already emitted projectiles retain policy after owner expiry/death.',
        'Physical NPC contact is sampled on the real30Hz clock with swept relative 3D spheres and terrain sight. The per-source touched set follows staggered3-update cache cycles, held by Freeze. Queue saturation retains one selected hit per source; selected damage is not recalculated on retry.',
        'The core game uses fixed simulation steps. A caller passing a whole long physics step receives one swept contact sample, not a reconstructed inter-actor simulation of every missing native frame. Long-step contact equivalence is not claimed.',
        'Existing hostile damage/death event attribution and local loot/item hooks remain in use. Native generic friendly/companion incoming damage is not claimed by this temporary-only slice.',
        'Pink body tint, a small heart marker and pink NPC projectiles are original procedural presentation. No Isaac sprites, new player item, roster expansion or WASM checks are introduced.'
    ])
    if not args.check:
        assert not (OUT/'manifest.json').exists();OUT.mkdir(parents=True,exist_ok=True)
    for name,start,end in [('projectile_default_damage',0x62f249,0x62f27a),('first_charm_vectors',0x680df0,0x680e31),
                           ('retaliation_item_gate',0x6ac3e0,0x6ac4b5),('retaliation_target',0x6909f0,0x690ac6),
                           ('target_affiliation',0x6aeb40,0x6aebce)]:
        data=pe.get_data(start-pe.OPTIONAL_HEADER.ImageBase,end-start);ins=list(md.disasm(data,start));assert sum(i.size for i in ins)==len(data)
        body=''.join(f'{i.address:08x} {i.mnemonic} {i.op_str}\n' for i in ins);path=OUT/(name+'.asm')
        if args.check:assert path.read_text()==body
        else:path.write_text(body)
        result['windows'].append(dict(path=str(path.relative_to(ROOT)),start=hex(start),end=hex(end),raw_sha256=sha(data),sha256=sha(body.encode())))
    for relative in ['docs/reports/isaac-enemy-port/first-floor-batch1/charm/source/manifest.json',
                     'docs/reports/isaac-enemy-port/horf_fly/source/shared_acquisition.asm',
                     'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3/items.xml']:
        path=ROOT/relative;result['references'].append(dict(path=relative,sha256=sha(path.read_bytes())))
    path=OUT/'manifest.json'
    if args.check:assert json.loads(path.read_text())==result
    else:path.write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps(dict(result='pass',windows=len(result['windows']),mode='check' if args.check else 'preserved')))

if __name__=='__main__':main()
