#!/usr/bin/env python3
"""Preserve bounded Hornfel charge evidence without changing installed files.

This is an evidence checkpoint, not recovered game source or a gameplay port.
Existing reports are immutable: --check verifies one, otherwise create a new one.
Requires the reference study's pefile/capstone environment.
"""
import argparse
import hashlib
import json
import re
import struct
from datetime import datetime, timezone
from pathlib import Path
from urllib.request import urlopen

import capstone
import pefile

ROOT = Path(__file__).resolve().parents[2]
EXE = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
BASELINE = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
CODE = ROOT / 'reference/isaac-mechanics-study/code/TeamREPENTOGON__REPENTOGON/348e5d0ea277760fc87af420d88e2c7909c9167e'
OUT = ROOT / 'docs/reports/isaac-enemy-port/hornfel_charge_review'
API = 'https://wofsauge.github.io/IsaacDocs/rep/enums/ProjectileFlags.html'


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def relative(path):
    return str(path.relative_to(ROOT))


def check():
    report = json.loads((OUT / 'checkpoint.json').read_text())
    verified = 0
    for kind in ['sources_sha256', 'artifacts_sha256']:
        for name, digest in report[kind].items():
            assert sha(ROOT / name) == digest, name
            verified += 1
    assert sha(EXE) == BASELINE, 'Installed binary changed from baseline'
    print(f'PASS Hornfel charge review: {verified} source/artifact hashes and installed binary; no runtime completion claim')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    if args.check:
        check()
        return
    assert not OUT.exists(), f'Refusing to overwrite immutable report: {OUT}'
    data = EXE.read_bytes()
    assert hashlib.sha256(data).hexdigest() == BASELINE
    pe = pefile.PE(data=data)
    base = pe.OPTIONAL_HEADER.ImageBase
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    decoder.detail = True

    signatures = CODE / 'libzhl/functions/EntityNPC.zhl'
    params = CODE / 'libzhl/functions/ProjectileParams.zhl'
    sig = re.search(r'"([0-9a-f?]+)":\s*[^;\n]*Entity_NPC::FireBossProjectiles\(', signatures.read_text())[1]
    pattern = b''.join(b'.' if pair == '??' else re.escape(bytes.fromhex(pair)) for pair in re.findall('..', sig))
    hits = list(re.finditer(pattern, data, re.S))
    # This newer REPENTOGON prologue does NOT match installed1.7.9b. Use the
    # installed native API registration's adjacent function/name pointers instead.
    method_name = b'FireBossProjectiles\0'
    name_offset = data.index(method_name)
    name_address = base + pe.get_rva_from_offset(name_offset)
    registration = b'\x68' + struct.pack('<I', 0x6a3420) + b'\x68' + struct.pack('<I', name_address)
    registrations = [m.start() for m in re.finditer(re.escape(registration), data)]
    assert len(registrations) == 1
    registration_address = base + pe.get_rva_from_offset(registrations[0])
    fire_address = struct.unpack('<I', data[registrations[0]+1:registrations[0]+5])[0]
    assert fire_address == 0x6a3420
    assert 'uint64_t BulletFlags : 0x58' in params.read_text()
    assert 'Scale : 0x14' in params.read_text()

    prior = ROOT / 'docs/reports/isaac-enemy-port/hornfel_controller/checkpoint.json'
    historical = json.loads(prior.read_text())
    for name, digest in historical['artifacts_sha256'].items():
        assert sha(ROOT / name) == digest, f'Historical artifact changed: {name}'

    # Keep the exact enum evidence used for the bit name. Mechanics are anchored
    # to the installed binary; a current documentation page alone is insufficient.
    with urlopen(API, timeout=30) as response:
        api_data = response.read()
    api_text = api_data.decode('utf-8')
    assert 'FIRE_WAVE' in api_text
    stripped = re.sub('<[^>]+>', ' ', api_text).replace('&lt;', '<')
    assert re.search(r'1\s*<<\s*35\s+FIRE_WAVE\b', stripped)

    OUT.mkdir(parents=True)
    (OUT / 'native').mkdir()
    (OUT / 'sources').mkdir()
    (OUT / 'sources/projectile-flags.html').write_bytes(api_data)
    windows = [
        ('periodic_predicate', 0x684790, 0x6847db),
        ('scaled_counter_crossing', 0x6847e0, 0x684852),
        ('room_inset_predicate', 0x7cf0a0, 0x7cf158),
        ('random_unit_vector', 0x659290, 0x6592ef),
        ('projectile_params_flags_init', 0x430d70, 0x430e44),
        ('fire_boss_projectiles_prefix', 0x6a3420, 0x6a3480),
        ('native_api_registration', registration_address, registration_address+10),
    ]
    records = []
    for name, start, end in windows:
        raw = pe.get_data(start-base, end-start)
        lines = ['; Repentance 1.7.9b bounded evidence. Interpretive names are not exported symbols.']
        for instruction in decoder.disasm(raw, start):
            notes = []
            for operand in instruction.operands:
                if operand.type == capstone.x86.X86_OP_MEM and not operand.mem.base and not operand.mem.index:
                    address = operand.mem.disp
                    if base <= address < base + pe.OPTIONAL_HEADER.SizeOfImage:
                        literal = pe.get_data(address-base, 4)
                        if len(literal) == 4:
                            notes.append(f'f32={struct.unpack("<f", literal)[0]:.9g}')
            lines.append(f'{instruction.address:08x} {instruction.mnemonic} {instruction.op_str}' +
                         (' ; ' + ', '.join(notes) if notes else ''))
        target = OUT / 'native' / (name+'.asm')
        target.write_text('\n'.join(lines)+'\n')
        records.append({'name': name, 'start': hex(start), 'end_exclusive': hex(end),
                        'raw_sha256': hashlib.sha256(raw).hexdigest(), 'artifact': relative(target)})

    evidence = ROOT / 'docs/reports/isaac-enemy-port/hornfel/native'
    animation_path = ROOT / 'docs/reports/isaac-enemy-port/hornfel/animations/manifest.json'
    animation_data = json.loads(animation_path.read_text())
    animation = next(a for f in animation_data['files'] for a in f['animations'] if a['attributes']['Name'] == 'ChargeFinish')
    assert animation['attributes'] == {'Name': 'ChargeFinish', 'FrameNum': '87', 'Loop': 'false'}
    assert animation['triggers'] == [{'EventId': '2', 'AtFrame': '22'}, {'EventId': '1', 'AtFrame': '46'}]
    source_files = [Path(__file__).resolve(), signatures, params, animation_path, prior,
                    evidence/'helper_4a5120.asm', evidence/'helper_4a5a10.asm',
                    evidence/'hornfel_update_ai.asm', evidence/'hornfel_update_frame.asm',
                    ROOT/'docs/reports/isaac-enemy-port/hornfel_controller/native/cart_ai_candidate.asm']
    findings = [
        {'topic': 'Selection', 'addresses': ['0x4a5695-0x4a572c'],
         'contract': 'After earlier decoy selection fails, state6 and zero byte0xaf2 allow a random low-three-bit-zero test (1/8 for uniform RNG). Entry must have a nonnull paired door different from itself. Select state10, set cart parameter0xb08 to0.1, retain entry door, set byte0xaf2=100 and repeat byte0xaf6=RNG%3+6.',
         'limits': 'This is a conditional selection probability, not an unconditional per-pass probability. Prior decoy selection and paired-route eligibility matter.'},
        {'topic': 'Charge movement', 'addresses': ['0x4a67d9-0x4a67fd', '0x4bbd98-0x4bbe17'],
         'contract': 'State10 adds0.08 to cart parameter0xb08, capped at30. Cart AI adds normalized rail direction times1.3 times this parameter to velocity and sets rider friction0.8.',
         'limits': '0xb08 is not direct world speed. Full movement order, integration and the separate native movement cap must inform conversion. Existing DeathWard constant12 world-units/second is a declared adaptation.'},
        {'topic': 'Repeated traversal', 'addresses': ['0x4a5a3a-0x4a5b30', '0x4a800c-0x4a8043'],
         'contract': 'State10 keeps both paired doors requested open. At exit, positive repeat byte teleports cart to stored entry through SetMinecartPosVel, decrements byte, and copies cart position to actor. No ordinary outside wait. Counter6-8 represents repeats after the initial pass:7-9 fast traversals if uninterrupted.',
         'limits': 'Do not sweep collision across the teleport chord. Rail endcap routes that return to the same door fail the native paired-door condition.'},
        {'topic': 'Charge bomb cadence', 'addresses': ['0x4a6803-0x4a6835', '0x684790-0x6847db'],
         'contract': 'Periodic helper uses (global field0x1a30dc + actor field0x20) modulo15; returns false when actor flag0x4000 or helper0x6d0380 is active. Bomb spawn also requires room-inset predicate with margin20 native units.',
         'limits': 'Do not label actor field0x20 as animation time, or equate15 to an unconditional elapsed-time timer without identifying the clock and suppression conditions.'},
        {'topic': 'Charge bomb placement', 'addresses': ['0x4a6835-0x4a68fa', '0x659290-0x6592ef', '0x7cf10a-0x7cf158'],
         'contract': 'Candidate target is current actor position plus a random unit vector times U[0,1). A subsequent room helper adjusts the target. Spawn entity4 variant0 and call existing Hornfel bomb launch helper0x4a6080.',
         'limits': 'Charge bombs are scattered around the rail position, not the ordinary attack aimed at the player. Exact target-adjustment helper0x7cf240 semantics remain to verify.'},
        {'topic': 'Counter decay', 'addresses': ['0x4a7a83-0x4a7ad9', '0x6847e0-0x684852'],
         'contract': 'Counter bytes0xaf0..0xaf3 decrement only when helper returns nonzero. With offset0 and divisor3, helper returns trunc(actor[0x2fc]/3)-trunc(actor[0x2f8]/3), subject to the same suppression gates.',
         'limits': 'The earlier150/30=5seconds mine-cooldown interpretation is not established. Both100 charge and150 mine counters use this crossing helper; field semantics must be identified before claiming exact elapsed seconds.'},
        {'topic': 'Recovery entry', 'addresses': ['0x4a5a64-0x4a5ac7', '0x4a5163-0x4a5279', '0x4a5731-0x4a5744'],
         'contract': 'Exhausted repeat byte changes to hidden state7, timer1, cart parameter capped at6. Helper reuses retained entry, restores visibility/collision and enters state11.',
         'limits': 'Recovery is another traversal from the original entry. It must not start in the middle of the room or choose a new random rail.'},
        {'topic': 'Recovery animation and speed', 'addresses': ['0x4a68ff-0x4a6b07', '0x4a80db-0x4a80e2'],
         'contract': 'ChargeFinish has87 animation frames at30FPS, Sound22 and Shoot46. Before the Shoot event has occurred, subtract0.75 from cart parameter with floor0.8. Afterward add0.1 with cap1.2. State11 has no animation-finished transition in this dispatch: ordinary room exit resolves it.',
         'limits': 'An87-frame animation is not a fixed87-frame recovery state. Do not count the recovery traversal among the initial fast traversals.'},
        {'topic': 'Recovery projectile', 'addresses': ['0x4a6924-0x4a6a60', '0x6a3420'],
         'contract': 'Shoot constructs ProjectileParams at ebp-0xe8; Scale at+0x14 is2. It ORs8 into high flags word+0x5c (bit35 FIRE_WAVE). FireBossProjectiles, identified by installed native API function/name registration, receives count1, predicted target and trajectoryModifier10. Prediction is target position + target velocity *0.1*distance. Returned fields0x368-=0.6,0x370=2,0x364=0.7*old-3.',
         'limits': 'The third FireBossProjectiles argument is a trajectory modifier per the matched API declaration, not proven shot speed10. Returned projectile fields need native accessor verification before labeling their meanings. Exact cardinal-fire aftermath timing/damage/propagation is separate work.'},
    ]
    review = {'status': 'source_review_only_not_runtime_implementation', 'baseline': 'Repentance1.7.9b',
              'exe_sha256': BASELINE,
              'native_api_registration': {'method': 'FireBossProjectiles', 'address': hex(fire_address),
                                          'name_address': hex(name_address), 'registration_address': hex(registration_address)},
              'newer_signature': {'pattern': sig, 'matches': len(hits),
                                  'note': 'No signature match in baseline; native registration establishes identity instead.'},
              'windows': records, 'animation': animation, 'findings': findings,
              'api_evidence': {'url': API, 'snapshot': relative(OUT/'sources/projectile-flags.html'),
                               'claim': 'FIRE_WAVE=1<<35; native high-word OR8 and parameter layout independently establish the bit.'},
              'next_implementation': [
                  'Verify native clock fields and suppression gates, then choose and document DeathWard timing conversion.',
                  'Implement external charge selection and retained-route repeat/recovery states with explicit acceleration/friction adaptation.',
                  'Add reusable ballistic impact and cardinal fire-wave support with capacity, cover, pit, room-lifetime and ownership rules.',
                  'Test exact repeat count, no teleport-chord hits, original recovery entry, event46 one-shot emission, exit-based recovery and mid-charge dismount.',
                  'Use actual seeded arenas for Linux/WASM visual, starting-kit balance and rendered performance checks.'],
              'unchanged_gaps': ['Decoys', 'passengers', 'Fly Bomb escort ownership', 'source-specific rewards', 'full six-gate acceptance']}
    (OUT/'source-review.json').write_text(json.dumps(review, indent=2)+'\n')
    checkpoint = {'status': 'review_progress_no_runtime_changes', 'previous_turn': 'progress: partial Hornfel controller/arenas',
                  'this_turn': 'progress: charge selection, repeat, recovery, bomb cadence/placement and parameter-contract review',
                  'created_utc': datetime.now(timezone.utc).isoformat(), 'previous_checkpoint': relative(prior),
                  'runtime_checkpoint_unchanged': historical['mechanics_fingerprint'],
                  'source_review': relative(OUT/'source-review.json'), 'source_findings': len(findings),
                  'historical_artifacts_verified': len(historical['artifacts_sha256']),
                  'checklist_unchanged': historical['checklist'],
                  'sources_sha256': {relative(p): sha(p) for p in source_files},
                  'artifacts_sha256': {relative(p): sha(p) for p in sorted(OUT.rglob('*')) if p.is_file()},
                  'validation': 'Hashes, installed native API registration and animation assertions; existing runtime tests are not rerun or newly claimed.',
                  'goal_status': 'active; no records newly complete'}
    (OUT/'checkpoint.json').write_text(json.dumps(checkpoint, indent=2)+'\n')
    check()


if __name__ == '__main__':
    main()
