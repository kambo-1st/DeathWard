#!/usr/bin/env python3
"""Preserve installed 1.7.9b fear/confusion evidence for the five-enemy cohort."""
import argparse
import hashlib
import json
from pathlib import Path
import capstone
import pefile

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/first-floor-batch1/statuses/source'
EXE = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
BASELINE = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    raw = EXE.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == BASELINE
    pe = pefile.PE(data=raw)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    windows = [('add_confusion', 0x6857d0, 0x68598a),
               ('add_fear', 0x685ae0, 0x685c9d),
               ('expire_timers', 0x686882, 0x6868f5),
               ('invalidate_target_cache', 0x680df0, 0x680e31)]
    result = dict(baseline='Installed Repentance 1.7.9b', executable_sha256=BASELINE,
                  windows=[], referenced_evidence=[], findings=[
        'AddConfusion=6857d0 and AddFear=685ae0 are bound by Entity API registration at8053d3/8053bf. Both reject NO_STATUS_EFFECTS and use source-adjusted duration. This cohort does not implement player item duration multipliers or boss immunity cooldowns.',
        'Ordinary positive duration adds to the remaining counter with cap0x78=120 source updates, four seconds at30Hz. Confusion takes max(old,cappedSum); Fear assigns cappedSum. Negative duration means max(old,-duration), not permanent.',
        'Common update decrements220(confusion)/228(fear) and clears flag200/800 at zero. Status acquisition invalidates cached path targets through680df0 on first activation.',
        'Horf shared acquisition6a15a0 rejects confusion200 and fear/shrink1000800. Its committed Shoot callback does not repeat that check.',
        'Gaper fear/shrink branch calls EvadeTarget7a4830 then applies friction*.8. Ordinary pursuit uses695a30, whose confusion branch caches a random point and refreshes every15 global updates.',
        'Confused target radius is uniform1*uniform2*240native units, with a separate random angle and room/radius clamping. Fear branch takes precedence over confused targeting.',
        'Headless shooting tests1000a00(confusion|fear|shrink); the suppressed path still decrements its timer below zero. Fear movement uses EvadeTarget; base friction*.75 precedes its force, and*.8 follows when NPC+aa0(pathfinder+73c)evade memory is positive.',
        'Morph and resolved base/NPC configuration contain no writes clearing flags160/164 or timers220/228. Gaper decapitation keeps the same entity and these timers. Rendering/path initialization does not create a fresh entity.'
    ], adaptations=[
        'Only10.0.0,10.1.0,11.0.0,11.1.0,12.0.0 opt into timed Fear and Confusion. Shrink, Charm, Freeze, Slow, damaging statuses, bosses/champions and player item application remain separate open work.',
        'Durations use active-room30Hz time. Inactive residents and modal game pauses retain their state; no off-room catch-up. Status decrements after each local controller step. Cached target refresh uses retained actor source phase instead of native global frame.',
        'Fear reuses the existing grounded EvadeTarget adaptation with actual canyon navigation,16candidate bound and source force/friction. Confused destinations are clamped to room bounds and shortened along the same ray if they land on blocked floor.',
        'Capacity-delayed payloads already selected before status application are retained. Fear/confusion block new attacks, not already-selected queue work. Negative countdown saturates at-18000 to bound stored integers.',
        'applyEnemyStatus is a reusable simulation API; --enemy-status supplies native smoke-test access without adding player items or changing the starting build. Positive duration caps and motion values are external mechanics content.',
        'Original-style body tints and small overhead marks are DeathWard readability cues, not copied Isaac artwork.'
    ])
    if not args.check:
        assert not (OUT / 'manifest.json').exists(), 'Do not overwrite preserved evidence'
        OUT.mkdir(parents=True, exist_ok=True)
    for name, start, end in windows:
        data = pe.get_data(start - pe.OPTIONAL_HEADER.ImageBase, end-start)
        instructions = list(md.disasm(data, start))
        assert sum(i.size for i in instructions) == len(data), name
        text = ''.join(f'{i.address:08x} {i.mnemonic} {i.op_str}\n' for i in instructions)
        if name == 'add_confusion':
            assert 'mov ecx, 0x78' in text and 'cmovl edx, ecx' in text
        if name == 'add_fear':
            assert 'mov edi, 0x78' in text and 'neg ebx' in text
        if name == 'expire_timers':
            assert 'and esi, 0xfffffdff' in text and 'and ecx, 0xfffff7ff' in text
        path = OUT / (name + '.asm')
        if args.check:
            assert path.read_text() == text
        else:
            path.write_text(text)
        result['windows'].append(dict(path=str(path.relative_to(ROOT)), start=hex(start), end=hex(end),
                                      raw_sha256=hashlib.sha256(data).hexdigest(), sha256=hashlib.sha256(path.read_bytes()).hexdigest()))
    for relative in ['horf_fly/source/shared_acquisition.asm', 'headless/source/controller.asm',
                     'gaper/source/controller.asm', 'gaper/source/morph.asm', 'gaper/source/base-config.asm',
                     'gaper/source/npc-config.asm', 'rotten-gaper/source/parent-evade.asm', 'faceless/source/target_position.asm']:
        path = ROOT / 'docs/reports/isaac-enemy-port' / relative
        result['referenced_evidence'].append(dict(path=str(path.relative_to(ROOT)), sha256=hashlib.sha256(path.read_bytes()).hexdigest()))
    path = OUT / 'manifest.json'
    if args.check:
        assert json.loads(path.read_text()) == result
    else:
        path.write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(dict(result='pass', mode='check' if args.check else 'preserved', windows=len(windows))))


if __name__ == '__main__':
    main()
