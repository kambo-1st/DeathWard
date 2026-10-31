#!/usr/bin/env python3
"""Preserve installed Repentance 1.7.9b ordinary Freeze and related clock evidence."""
import argparse
import hashlib
import json
import struct
from pathlib import Path
import capstone
import pefile

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/first-floor-batch1/freeze/source'
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
    windows = [('add_freeze', 0x685080, 0x6851b3),
               ('expire_freeze', 0x686757, 0x68678d),
               ('animation_gate', 0x6860e7, 0x68618c),
               ('is_frozen', 0x69b0b0, 0x69b0d6),
               ('ai_gate', 0x69cda8, 0x69ce99),
               ('freeze_friction', 0x69eb35, 0x69eb90),
               ('velocity_retention', 0x686406, 0x686492),
               ('half_step_motion', 0x68827a, 0x6882f1),
               ('player_contact', 0x6a5129, 0x6a5327),
               # Preserve evidence for the next Slow implementation, not a
               # claim that this change also implements Slow.
               ('add_slowing_research', 0x685400, 0x685508),
               ('npc_slow_clock_research', 0x690c21, 0x690c39)]
    result = dict(baseline='Installed Repentance 1.7.9b', executable_sha256=BASELINE,
                  windows=[], constants=[], referenced_evidence=[], findings=[
        'Entity AddFreeze binding calls685080. Ordinary positive duration adds to210 and caps120; negative duration keeps max(old,abs(duration)). Positive reapplication can shorten an extended duration to120. Zero does not apply. Low Entity flag20 marks Freeze.',
        'Common expiration decrements210 at30Hz and clears20 at zero. Base float FrameCount2fc advances even while frozen, but the animation gate skips sprite updates. Native interpolation and local capture60Hz are distinct from the source30Hz clock.',
        'Ordinary NPC AI gate69cdc2 invokes69b0b0 and jumps past699730 when frozen. Committed attack frames and controller-owned cooldowns therefore hold; freeze is not an attack cancel. Special states/flag exceptions exist outside this five-enemy cohort.',
        'Freeze skips ordinary family movement AI and multiplies friction2c4 by b6a214=.01. Base update multiplies carried velocity by friction and advances position. External momentum remains possible. At normal timeScale1 the recurrence is vNext=.01*v, positionNext=position+vNext/30 after conversion.',
        'Player contact branch6a5129 retains NPC collision damage and ordinary player damage dispatch; this branch has no Freeze gate for types10/11/12. Freeze does not grant invulnerability, a damage multiplier, an ice corpse or a room-clear exemption.',
        'Same-entity Gaper Morph/config helpers do not clear flags160/164 or timers210. Ordinary headless transformations therefore retain Freeze; final death remains the normal mortality path.'
    ], adaptations=[
        'Only10.0.0,10.1.0,11.0.0,11.1.0,12.0.0 opt into freeze_effect. Boss immunity240, linked-entity propagation, player item duration modifiers, Midas and Ice remain separate open work.',
        'Fractional motion uses the existing exact30Hz recurrence interpolation for DeathWard3D and physical canyon collision. The source.01 endpoint is preserved at30/60/120Hz. Swept player contact is retained. Normal crowd collision can still move the body.',
        'Local frozen body animation and gait amplitude are held; source polling ticks continue. Fear/confusion durations continue independently. Local controller state, including DeathWard stun, waits until thaw. Inactive rooms and modal pauses preserve durations and pose without catch-up.',
        'A capacity-delayed shot is held until thaw, not discarded. Its selected projectile stays intact, while retry movement uses the damped body velocity. A shot already emitted into the world continues moving normally.',
        'A pale blue material tint and static six-spoke overhead mark are original DeathWard readability cues, not copied artwork. No player perk or input binding is introduced; API and isolated capture CLI expose the status.'
    ], next_slow_research=[
        '685400 adds positive duration to218 without120cap. Negative application stores2, not abs(duration); zero still writes strength304. These rules differ from Freeze/Fear/Confusion.',
        'Ordinary NPC clock690c21 tests low flag80 and multiplies time scale by.5; this path does not read strength304. Current API prose alone is insufficient to infer arbitrary NPC slowdown strength.',
        'Base velocity686406 transforms retention q to q/(q+t-q*t) when timeScale t differs from1. Slow also affects movement and force, so simply halving controller dt would not reproduce this recurrence. Complete Slow implementation and validation remain open.'
    ])
    if not args.check:
        assert not (OUT / 'manifest.json').exists(), 'Do not overwrite preserved evidence'
        OUT.mkdir(parents=True, exist_ok=True)
    for name, start, end in windows:
        data = pe.get_data(start - pe.OPTIONAL_HEADER.ImageBase, end-start)
        instructions = list(md.disasm(data, start))
        assert sum(i.size for i in instructions) == len(data), (name, hex(start + sum(i.size for i in instructions)), hex(end))
        text = ''.join(f'{i.address:08x} {i.mnemonic} {i.op_str}\n' for i in instructions)
        if name == 'add_freeze':
            assert 'mov ecx, 0x78' in text and 'or edi, 0x20' in text
        if name == 'expire_freeze':
            assert 'and edx, 0xffffffdf' in text
        if name == 'freeze_friction':
            assert 'mulss xmm0, dword ptr [0xb6a214]' in text
        path = OUT / (name + '.asm')
        if args.check:
            assert path.read_text() == text
        else:
            path.write_text(text)
        result['windows'].append(dict(path=str(path.relative_to(ROOT)), start=hex(start), end=hex(end),
                                      raw_sha256=hashlib.sha256(data).hexdigest(), sha256=hashlib.sha256(path.read_bytes()).hexdigest()))
    for name, address in [('freeze_retention', 0xb6a214), ('slow_time_scale', 0xb6a480)]:
        data = pe.get_data(address-pe.OPTIONAL_HEADER.ImageBase, 4)
        result['constants'].append(dict(name=name, address=hex(address), bytes=data.hex(), value=struct.unpack('<f', data)[0]))
    for relative in ['gaper/source/morph.asm', 'gaper/source/base-config.asm', 'gaper/source/npc-config.asm',
                     'headless/source/controller.asm', 'horf_fly/source/horf_current_aim_and_speed.asm', 'chubber/source/npc_collision.asm']:
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
