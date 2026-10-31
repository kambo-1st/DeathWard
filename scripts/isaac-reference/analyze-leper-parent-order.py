#!/usr/bin/env python3
"""Pin the shared damage/update evidence needed for Leper's form changes."""
import argparse
import hashlib
import json
from pathlib import Path
import capstone
import pefile

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/leper-parent/source'
EXE = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
SHA = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    sha = lambda data: hashlib.sha256(data).hexdigest()
    raw = EXE.read_bytes()
    assert sha(raw) == SHA
    pe = pefile.PE(data=raw, fast_load=True)
    read = lambda address, length: pe.get_data(address-pe.OPTIONAL_HEADER.ImageBase, length)
    decoder = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

    def save(path, data):
        if args.check or path.exists():
            assert path.read_bytes() == data, path
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)

    manifest = {'baseline': 'Installed Repentance 1.7.9b', 'executable_sha256': SHA,
                'windows': [], 'shared_evidence': []}
    for name, start, end, complete in [
        ('npc-take-damage', 0x6ac370, 0x6acafd, True),
        ('default-extra-ai-flags', 0x68fba0, 0x68fc46, False),
        ('ordinary-ai-call', 0x69cda8, 0x69ce99, False),
        ('queued-damage-reset', 0x68701d, 0x687038, False),
        ('headless-state-entry', 0x4f8e40, 0x4f9008, False),
    ]:
        blob = read(start, end-start)
        instructions = list(decoder.disasm(blob, start))
        assert instructions and instructions[-1].address+instructions[-1].size == end, name
        if name == 'npc-take-damage':
            assert not any(i.mnemonic.startswith('mov') and i.op_str.startswith('dword ptr [edi + 0x2d8],') for i in instructions)
            assert any(i.mnemonic == 'call' and i.op_str == '0x684bb0' for i in instructions)
        data = ('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in instructions)+'\n').encode()
        path = OUT/(name+'.asm');save(path, data)
        manifest['windows'].append({'name': name, 'start': hex(start), 'end_exclusive': hex(end),
                                    'complete_function': complete, 'instructions': len(instructions),
                                    'raw_sha256': sha(blob), 'path': str(path.relative_to(ROOT)), 'sha256': sha(data)})
    for relative in ['docs/reports/isaac-enemy-port/leper/source/manifest.json',
                     'docs/reports/isaac-enemy-port/leper/animations/manifest.json',
                     'docs/reports/isaac-enemy-port/gaper/source/morph.asm',
                     'docs/reports/isaac-enemy-port/gaper/source/base-config.asm',
                     'docs/reports/isaac-enemy-port/gaper/source/npc-config.asm',
                     'docs/reports/isaac-enemy-port/adult-leech/source/direct_damage.asm',
                     'docs/reports/isaac-enemy-port/black-globin/source/body-complete.asm',
                     'docs/reports/isaac-enemy-port/nest/source/evade_pathfinder.asm']:
        manifest['shared_evidence'].append({'path': relative, 'sha256': sha((ROOT/relative).read_bytes())})
    manifest['claims'] = [
        'NPC TakeDamage forwards to684bb0. The complete forwarder has no direct current-HP write; base TakeDamage queues hits and accumulates14.',
        'Ordinary NPC AI runs at69ce94 before the shared update at69f8a9. The reset sets extra-AI flags to zero; Leper does not opt into extra callbacks.',
        'Parent534c8b predicts currentHP minus queued damage; all loop thresholds use the same maxHP. Only after loop534ff2 calls Morph.',
        'Morph reloads subtype maxHP via config and clamps currentHP before the common queued subtraction at686e81. Queue and pending-damage14 are cleared at68701d.',
        'The common subtraction stops after a lethal ordinary hit; leftover parent hits must not be applied to a same-entity Gusher.',
        'Headless controller only special-cases State0; no State4 guard exists in its complete controller. Inherited State16 does not freeze a morphed Gusher.',
        'Evade AA0 equals pathfinder base364 plus73c. It is the proximity memory: interval14, near resets3, far decrements; chase lottery requires memory<=0.',
    ]
    # Explicit algebra fixtures derived from the instructions above. These are
    # reference calculations, not execution of the original native game.
    def batch(stage, hp, max_hp, hits):
        predicted = hp-sum(hits)
        old = stage
        while stage < 3 and predicted <= (3-stage)*max_hp/(4-stage):
            stage += 1
        if stage != old:
            max_hp = 60-stage*15
            hp = min(hp, max_hp)
        applied = 0
        for amount in hits:
            hp -= amount;applied += 1
            if hp <= 0:
                break
        return dict(stage=stage, hp=hp, max_hp=max_hp, shed=stage-old, hits_applied=applied)
    cases = []
    for hits, expected in [([14], (0,46,0)), ([15], (1,30,1)), ([20], (2,10,2)), ([10,10], (2,10,2)), ([20,20], (3,-5,3))]:
        result = batch(0,60,60,hits)
        assert (result['stage'],result['hp'],result['shed']) == expected
        cases.append({'input': {'stage': 0, 'hp': 60, 'max_hp': 60, 'queued_hits': hits}, 'result': result})
    manifest['reference_calculations'] = cases
    manifest['scope'] = 'Normal hostile non-champion path. Static source analysis plus explicit algebra; no claim of original-game live execution or status/control parity.'
    save(OUT/'manifest.json', (json.dumps(manifest,indent=2)+'\n').encode())
    print(json.dumps({'pass': True, 'check': args.check, 'windows': len(manifest['windows']), 'reference_cases': len(cases)}))


if __name__ == '__main__':
    main()
