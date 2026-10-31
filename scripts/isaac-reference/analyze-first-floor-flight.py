#!/usr/bin/env python3
"""Preserve and verify installed Horf/Gusher projectile evidence for batch one."""
import argparse
import hashlib
import json
import struct
from pathlib import Path

import capstone
import pefile

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/first-floor-batch1/source'
EXE = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
BASELINE = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    raw = EXE.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == BASELINE
    pe = pefile.PE(data=raw)
    read = lambda a, n: pe.get_data(a - pe.OPTIONAL_HEADER.ImageBase, n)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    constants = []
    for name, address, value in [('body_retention', 0xb6a50c, .7),
                                 ('flight_retention', 0xb6a5a4, .9),
                                 ('common_acceleration', 0xb6a2cc, .1)]:
        actual = struct.unpack('<f', read(address, 4))[0]
        assert abs(actual - value) < 1e-6
        constants.append(dict(name=name, address=hex(address), value=actual))
    windows = [('horf_controller', 0x500fa0, 0x5014ee),
               ('projectile_parameters', 0x430d70, 0x430ef9),
               ('mode0_defaults', 0x6a3059, 0x6a30b8),
               ('parameter_addition', 0x6a3159, 0x6a31b8),
               ('gusher_parameters', 0x4f92df, 0x4f93c4),
               ('initial_height', 0x62f1ef, 0x62f1f9),
               ('flight_integrator', 0x636567, 0x6365d5)]
    result = dict(baseline='Installed Repentance 1.7.9b', executable_sha256=BASELINE,
                  constants=constants, windows=[], findings=[
        'Ordinary Horf initializes ProjectileParams and calls FireProjectiles mode0 without falling modifiers. The distinct Psychic Horf branch only adds its own flags/color.',
        'Mode0 overwrites fallingSpeed with -3 and fallingAccel with .1. The parameter pass then adds the caller modifiers. Initial height is -23.',
        'Gusher sets fallingSpeedModifier=-5 and fallingAccelModifier=.3: initial speed=-8 and acceleration field=.4.',
        'The shared flight update also adds common acceleration .1. At source timeScale1 the recurrence is v=.9*v+.1+fallingAccel; height+=v. Thus Horf adds .2 per update and Gusher adds .5.',
        'The previous Gusher world gravity18 used only the .4 field. At vertical scale .05 and30Hz it must be(.1+.4)*.05*900=22.5.',
        'Horf applies friction*.7 each update despite having no pursuit movement. DeathWard retains incoming horizontal momentum with .7 damping; fractional-step interpolation and physical canyon collision remain explicit adaptations.'
    ], adaptations=[
        'Horf horizontal scale.1 gives speed21. Vertical scale.03 gives launch height.69, upward speed2.7 and gravity5.4. This narrower arc keeps ordinary aimed shots within the existing standing-player combat silhouette; it does not change the player hitbox.',
        'Gusher retains vertical scale.05, launch height1.15 and upward speed12; gravity22.5 now includes the shared base acceleration.',
        'Swept spheres collide with actual3D scenery and ground. Native collision-height thresholds and sprite layering are not reproduced. Existing local shot radius.22 and lifetime caps are retained.',
        'Passive Horf damping consumes external velocity but does not invent a new hit impulse. Exact native mass/knockback production remains part of the shared acceptance work.'
    ])
    if not args.check:
        assert not (OUT / 'manifest.json').exists(), 'Do not overwrite preserved source evidence'
        OUT.mkdir(parents=True, exist_ok=True)
    for name, start, end in windows:
        data = read(start, end - start)
        instructions = list(md.disasm(data, start))
        assert sum(i.size for i in instructions) == len(data), name
        if name == 'mode0_defaults':
            assert any(i.op_str == 'dword ptr [eax + 0x364], 0xc0400000' for i in instructions)
            assert any(i.op_str == 'dword ptr [eax + 0x368], 0x3dcccccd' for i in instructions)
        if name == 'gusher_parameters':
            assert any(i.op_str == 'dword ptr [ebp - 0x10c], 0x3e99999a' for i in instructions)
            assert any(i.op_str == 'dword ptr [ebp - 0x110], 0xc0a00000' for i in instructions)
        if name == 'initial_height':
            assert instructions[0].op_str == 'dword ptr [esi + 0x360], 0xc1b80000'
        text = ''.join(f'{i.address:08x} {i.mnemonic} {i.op_str}\n' for i in instructions)
        path = OUT / (name + '.asm')
        if args.check:
            assert path.read_text() == text, path
        else:
            path.write_text(text)
        result['windows'].append(dict(path=str(path.relative_to(ROOT)), start=hex(start), end=hex(end),
                                      raw_sha256=hashlib.sha256(data).hexdigest(),
                                      sha256=hashlib.sha256(path.read_bytes()).hexdigest()))
    manifest = OUT / 'manifest.json'
    if args.check:
        assert json.loads(manifest.read_text()) == result
    else:
        manifest.write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(dict(result='pass', mode='check' if args.check else 'preserved', windows=len(windows))))


if __name__ == '__main__':
    main()
