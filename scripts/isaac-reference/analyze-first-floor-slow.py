#!/usr/bin/env python3
"""Preserve installed 1.7.9b Slow clocks, force/friction and projectile inheritance."""
import argparse
import hashlib
import json
import struct
from pathlib import Path
import capstone
import pefile

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/first-floor-batch1/slow/source'
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
    windows = [('add_slowing', 0x685400, 0x685508), ('expire_slow', 0x6867cb, 0x68680f),
               ('npc_time_scale', 0x690ad0, 0x690cb7), ('projectile_time_scale', 0x62f440, 0x62f5d3),
               ('inherit_projectile_flag', 0x6a1750, 0x6a179a), ('factory_owner_flags', 0x6a38f1, 0x6a3907),
               ('rational_retention', 0x65c960, 0x65c98a), ('add_velocity', 0x422b60, 0x422bcf),
               ('base_velocity', 0x686406, 0x686492), ('animation_clock', 0x6860e7, 0x68618c),
               ('horf_cooldown', 0x500fdd, 0x501006), ('gusher_cooldown', 0x4f93e9, 0x4f9403)]
    result = dict(baseline='Installed Repentance 1.7.9b', executable_sha256=BASELINE,
                  windows=[], constants=[], referenced_evidence=[], findings=[
        'AddSlowing685400 adds positive duration to218 without the120 cap used by Freeze/Fear/Confusion. Negative duration assigns2, including shortening an existing duration. Zero does not add status. Low Entity flag80 indicates Slow. Shared update decrements218 once per source update and clears80 at zero.',
        'AddSlowing stores caller strength at304, but ordinary NPC time-scale690ad0 does not read it. After room modifiers it tests low flag80 and multiplies by b6a480=.5. The selected normal expedition profile does not simulate unrelated global stopwatch/room/item modes.',
        'Native sprite playback and float FrameCount are scaled, while AI/global acquisition polls still run each real30Hz update. Horf/Gusher integer cooldowns subtract trunc(currentFrameCount)-trunc(previousFrameCount); a due Gusher may fire on an AI update with zero logical-frame increment.',
        'AddVelocity422b60 multiplies force by timeScale and divides by accumulated friction. Base Entity movement transforms retention q into q/(q+t-q*t), multiplies stored velocity by that value and multiplies displacement by t. Helper65c960 uses this same rational formula, not exponentiation.',
        'For an existing normal controller result q*old+impulse, the slowed carried velocity is (q*old+impulse*t)/(q+t-q*t), with displacement multiplied separately by t. Family friction order, path-arrival friction and combined fear friction all matter.',
        'Projectile factory6a38f1 passes owner flags to6a1750. Owner low flag80 adds projectile SLOWED1<<24 at388. Projectile time-scale62f440 tests that retained flag and applies.5 independently of the owner thereafter.',
        'Vertical projectile update636567 uses65c960 to adjust.9 falling-speed retention, multiplies both gravity terms by t and then advances height by fallingSpeed*t. Ordinary Horf/Gusher speeds and damage are otherwise unchanged. Earlier projectiles do not gain SLOWED retroactively.',
        'Freeze skips AI and animation but still advances scaled base FrameCount. Consequently logical cooldown fraction may advance while frozen even though the cooldown itself is held; the sprite fraction remains held.'
    ], adaptations=[
        'Only10.0.0,10.1.0,11.0.0,11.1.0,12.0.0 opt into Slow. slow_effect ID actorScale shotScale negativeRefresh exposes separate tuning values; defaults.5/.5/2 match this baseline. These scales are not a claim that native AddSlowing strength304 controls ordinary NPC speed.',
        'Existing fixed-source-step controllers retain independent real AI ticks, logical cooldown fractions and animation fractions. Global staggered polls use retained local source phase in inactive rooms. Modal pauses stop simulation; room storage retains durations without catch-up.',
        'Continuous3D integration uses the established recurrence interpolation between exact30Hz endpoints. Stored body/projectile velocity remains unscaled, while actual displacement includes time scale. Physical canyon cover, body steering and damage conversion remain unchanged.',
        'Positive applications saturate only atINT_MAX to avoid signed overflow; individual API durations remain bounded to18000 source frames. This is not a120-frame cap. Negative duration assigns the externally configured refresh count.',
        'Queued Gusher shots capture slowed projectile state at selection and keep it across capacity retry. Horf captures it when its Shoot payload is admitted. Already emitted shots retain independent time scale after owner removal or death.',
        'The local projectile lifetime budget consumes logical time; source airborne trajectories still determine ground impact. Tested Slow projectile support is the ordinary Horf/Gusher lob path, not an assertion of unrelated accelerated/homing/splitting projectile parity.',
        'Ochre body treatment and a small hourglass marker are original DeathWard cues. Freeze visually takes precedence. Tint lasts for the status duration instead of reproducing the native caller-color stacking API. No player item or ordinary input binding is added.',
        'Boss immunity cooldowns, linked-entity propagation, item duration/source modifiers and other Slow sources remain open. Headless cosmetic trail remains the existing bounded10-real-tick adaptation.'
    ])
    if not args.check:
        assert not (OUT / 'manifest.json').exists(), 'Do not overwrite preserved evidence'
        OUT.mkdir(parents=True, exist_ok=True)
    for name, start, end in windows:
        data = pe.get_data(start-pe.OPTIONAL_HEADER.ImageBase, end-start)
        instructions = list(md.disasm(data, start))
        assert sum(i.size for i in instructions) == len(data), (name, hex(start+sum(i.size for i in instructions)), hex(end))
        text = ''.join(f'{i.address:08x} {i.mnemonic} {i.op_str}\n' for i in instructions)
        if name == 'add_slowing':
            assert 'add dword ptr [esi + 0x218], edx' in text and 'mov dword ptr [esi + 0x218], 2' in text
        if name == 'inherit_projectile_flag':
            assert 'and eax, 0x80' in text and 'or dword ptr [esi + 0x388], 0x1000000' in text
        if name == 'rational_retention':
            assert 'subss xmm1, xmm0' in text and 'divss xmm2, xmm1' in text
        path = OUT / (name+'.asm')
        if args.check:
            assert path.read_text() == text
        else:
            path.write_text(text)
        result['windows'].append(dict(path=str(path.relative_to(ROOT)), start=hex(start), end=hex(end),
            raw_sha256=hashlib.sha256(data).hexdigest(), sha256=hashlib.sha256(path.read_bytes()).hexdigest()))
    for name, address in [('slow_time_scale', 0xb6a480), ('falling_retention', 0xb6a5a4)]:
        data = pe.get_data(address-pe.OPTIONAL_HEADER.ImageBase, 4)
        result['constants'].append(dict(name=name,address=hex(address),bytes=data.hex(),value=struct.unpack('<f',data)[0]))
    for relative in ['first-floor-batch1/source/flight_integrator.asm', 'first-floor-batch1/source/mode0_defaults.asm',
                     'gaper/source/grid-path.asm', 'headless/source/controller.asm',
                     'horf_fly/source/horf_acquisition_and_delay.asm', 'horf_fly/source/shared_acquisition.asm',
                     'gaper/source/morph.asm', 'gaper/source/base-config.asm', 'gaper/source/npc-config.asm']:
        path = ROOT / 'docs/reports/isaac-enemy-port' / relative
        result['referenced_evidence'].append(dict(path=str(path.relative_to(ROOT)),sha256=hashlib.sha256(path.read_bytes()).hexdigest()))
    path = OUT/'manifest.json'
    if args.check:
        assert json.loads(path.read_text()) == result
    else:
        path.write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps(dict(result='pass',mode='check' if args.check else 'preserved',windows=len(windows))))


if __name__ == '__main__':
    main()
