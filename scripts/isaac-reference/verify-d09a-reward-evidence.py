#!/usr/bin/env python3
"""Verify preserved source evidence for the bounded D09a reward/heart consumer."""
import csv, hashlib, json
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
base=ROOT/'docs/reports/isaac-first-floor-parity'
prior=json.loads((base/'room-awards/validation.json').read_text())
files={}
for name in ('native-awards.csv','native-pickups.csv','award_selector.asm','award_spawn.asm','pickup_resolver.asm'):
 path=base/'room-awards'/name;relative=str(path.relative_to(ROOT));actual=hashlib.sha256(path.read_bytes()).hexdigest()
 assert actual==prior['sha256'][relative],name
 files[relative]=actual
manifest=json.loads((base/'room-awards/manifest.json').read_text())
assert manifest['executable_sha256']=='04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
with (base/'heart-pickups/native-red-quantities.csv').open() as f:
 quantities={int(r['subtype']):int(r['red_halves']) for r in csv.DictReader(f)}
assert quantities=={1:2,2:1,5:4,9:2}
result=dict(executable_sha256=manifest['executable_sha256'],target='Repentance 1.7.9b, ordinary Isaac, Normal, no reward-modifying items/trinkets',
 preserved_evidence_sha256=files,source_red_quantities=quantities,enabled_subtypes=[1,2,5],native_selector_cases=2196,native_heart_resolver_cases=1036,
 production_rare_heart_gates=dict(rotten=False,scared=False,halfSoul=False,bone=False,goldenHeart=False),
 gate_scope='Explicit represented reference inputs; not certification of a complete fresh-save or unlocked profile.',
 seed_adapter='Independent SplitMix64 of DW floor seed xor 0x4845415254415744 xor ((room index+1)*0x9e3779b97f4a7c15), low 32 bits, zero maps to 1.',
 pickup_seed='Next native 5/9/7 xorshift after ordinary selector; extra draw visible at 7b903a..7b9064.',
 placement='Room center, then nearest reachable legal DW floor cell; source placement and actor birth/physics are not accepted.',
 recovery_archive_sha256='42171909a523f0659e7899e9993ac6183f9fa04c942fd5d6d5c0c51719637be0',
 limits=['Live native floor/descriptor seed mapping and full spawn wrapper unaccepted.','Only ordinary opening-floor red-heart clear rewards enabled.','Other family/subtype decisions are retained as unsupported, not rerolled or converted.','Full appearance timing, collision/physics, modifier/unlock profile and complete reward/economy parity remain open.'])
(base/'d09a-red-heart-rewards/source-evidence.json').write_text(json.dumps(result,indent=2)+'\n')
print('PASS pinned reward matrices/disassembly and red quantities; 2196 selector + 1036 heart resolver cases retained')
