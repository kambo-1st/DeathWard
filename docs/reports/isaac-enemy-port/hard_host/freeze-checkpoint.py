"""Freeze this regular-enemy slice once, after evidence and history checks."""
import datetime
import hashlib
import json
import subprocess
import xml.etree.ElementTree as ET
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
BASE = 'docs/reports/isaac-enemy-port/hard_host/'
OUT = ROOT / BASE
PREVIOUS = 'docs/reports/isaac-enemy-port/hosts/checkpoint.json'


def load(path):
    return json.loads((ROOT / path).read_text())


def save(path, value):
    (ROOT / path).write_text(json.dumps(value, indent=2, ensure_ascii=False) + '\n')


def sha(path):
    h = hashlib.sha256()
    with (ROOT / path).open('rb') as stream:
        for chunk in iter(lambda: stream.read(4 * 1024 * 1024), b''):
            h.update(chunk)
    return h.hexdigest()


def passed(case):
    return all(case.find(tag) is None for tag in ['failure', 'error', 'skipped'])


assert not (OUT / 'checkpoint.json').exists(), 'Already frozen'
cases = ET.parse(OUT / 'native.xml').getroot().findall('.//testcase')
assert len(cases) == 77
assert {c.attrib['name'] for c in cases if not passed(c)} == {'crackle_discrete_fire_jets'}
corrections = ET.parse(OUT / 'crackle-corrected.xml').getroot().findall('.//testcase')
assert len(corrections) == 1 and corrections[0].attrib['name'] == 'crackle_discrete_fire_jets' and passed(corrections[0])
passing = sorted({c.attrib['name'] for c in cases + corrections if passed(c)})
assert len(passing) == 77
assert 'PASS Hard Host' in (OUT / 'native-targeted.txt').read_text()
web = load(BASE + 'web-final/results.json')
assert len(web['checks']) == 3 and not web['errors']
assert {r['case'] for r in web['checks']} == {'near', 'far', 'resident'}
assert all('PASS ' + r['case'] in (OUT / 'browser-final.txt').read_text() for r in web['checks'])
visual = load(BASE + 'visual-review.json')
assert len(visual['final_images']) == 11 and all(r['inspected'] for r in visual['final_images'])
captures = load(BASE + 'native-captures.json')
assert len(captures) == 4 and all(r['exit_code'] == 0 for r in captures)
fingerprint = (OUT / 'mechanics-final.txt').read_text().split('fingerprint ')[1].split()[0]
assert fingerprint == '8f59a76434a3149b'
assert 'direct_pool_id_count=71' in (OUT / 'pool-audit.txt').read_text()
history = load(BASE + 'historical-integrity.json')['files']
assert len(history) == 6347
for path, digest in history.items():
    assert sha(path) == digest, path
subprocess.run(['python3', 'scripts/isaac-reference/analyze-hard-host.py', '--check'],
               cwd=ROOT, check=True, capture_output=True)

native = dict(passed=77, failed=0, report=BASE + 'native.xml', passing_suites=passing,
    corrected_reports=[BASE + 'crackle-corrected.xml'], behavior=BASE + 'native-targeted.txt',
    corrections='Full run passed76/77. The Crackle witness search expands from30 to256 seeds; actual seed61/floor1/room4 passes. Pool additions changed weighted draws; no Crackle runtime or weight changes. Initial Hard Host pit fixture changed visible floor strips but not collision cells; the corrected fixture and full suite pass.')
browser = dict(cases=3, report=BASE + 'web-final/results.json', scope=web['scope'], errors=[],
    build=BASE + 'build-wasm-fixed.txt',
    corrections='Initial WASM build rejected unparenthesized object literals in EM_ASM probes. Parenthesized literals compile; final production build and all3cases pass.')
remaining = [
    'Native special status/champion/control branches, item transformations and all special grid/NPC immunity exceptions remain open.',
    'Native RNG sequence, age-zero generator ordering, source grid parity and full crush knockback/mass physics remain open.',
    'Source player friction/control/flying exceptions are not fully reproduced; local grounded horizontal collision and normal controls remain active during the hop.',
    'Exact alternate-stage placement and replacement probabilities remain open; authored band1 specialist weight1/cost4/cap1 is an adaptation.',
    'Full combat readability, balance and controlled Linux/WASM performance acceptance remain open; no complete port is claimed.'
]
adaptations = [
    'Source30Hz, distance x.1, velocity x3, HP x3.2. Rock pulse10sourceHP becomes32NPC damage; player base10 uses the established hostile damage scale.',
    'Swept3D ground tracing prevents thin-prop tunnelling. Cracks/dung/cache entrances break and powder barrels can ignite; local ore/resource gates and structural cache sides remain protected.',
    'Per-wave seeded RNG and whole-pulse/cast retry under capacity pressure; emitted generator survives owner death/room clear but clears on room change.',
    'Physical hop with upward27world/sec and gravity99world/sec2; horizontal impulse9 with authored .8 retention and grounded collision.',
    'Original stone-cap body, exposed stem, rock crests and particles; no source artwork imported. Authored Mines/Ashpit analogue placement in band1.'
]
review = dict(scope='Partial normal-hostile Hard Host27.3 physical slam, crush wave, terrain and player hop.',
    source=BASE + 'source-review.md', adaptations=adaptations, remaining=remaining,
    native=native, browser=browser, visual=visual, complete=False)
save(BASE + 'implementation-review.json', review)
runtime = ['assets/mechanics/hosts.mechanics', 'assets/mechanics/monsters.mechanics',
    'src/content/Mechanics.hpp', 'src/content/Mechanics.cpp', 'src/combat/Simulation.hpp',
    'src/combat/Simulation.cpp', 'src/combat/Hosts.cpp', 'src/combat/Destruction.cpp',
    'src/combat/Enemies.cpp', 'src/combat/FireReactions.cpp', 'src/render/Renderer.cpp',
    'src/render/MonsterVisuals.hpp', 'src/main.cpp', 'tests/hard_host_tests.cpp',
    'tests/crackle_tests.cpp', 'web/hard-host-test.cjs', 'CMakeLists.txt']
status = load('docs/research/isaac-enemy-port-status.json')
save(BASE + 'status-before.json', status)
r = next(r for r in status['records'] if r['id'] == '27.3.0')
assert r['implementation'] == 'existing_unverified'
r.update(review='reviewed', disposition='ordinary', implementation='in_progress')
r['runtime'] = list(dict.fromkeys(r['runtime'] + runtime))
r['evidence'].append(dict(source=BASE + 'source-review.md',
    supports='Pinned effect72 dispatcher/init/update, CRUSH terrain/damage helper, Player vtable launch binding and hop recurrence, extending prior Host identity/animation review. Explicit local adaptations and unimplemented branches.'))
r['contract'] = dict(
    movement='Stationary grounded body; source contact1 becomes local base10.',
    targeting='Shared Host strict24world-unit range and sight acquisition on global/entity seven-frame checks. Live target aim on Close54. Nearby player launch uses strict12world-unit radius without sight check.',
    attacks='Close54 spawns original-owner rock generator2units forward. Steps3units every2sourceframes; straight through6 then independent heading jitter up to75degrees, ramp20frames;240frame lifetime. Pulse radius2,32NPC damage,10base player damage, CRUSH channel with no entity sight check. No bullet volley. Eligible terrain destruction and nearby physical hop.',
    vulnerability='15sourceHP becomes48localHP. Closed armor, shared cumulative hit-delay and Burning bypass. Damageable between Open10 and Close54; source contact damage retained.',
    phases='Closed preparation, exposed attack, Close54 slam, closed recovery through end71. Idle cooldown7 checks. Whole slam/pulse waits under capacity pressure. Death/stun cancels unemitted attacks.',
    offspring='No NPC offspring. Original-owner1000.72/subtype2 effect represented by physical RockWaveRuntime, independently surviving owner death.',
    completion='Ordinary room threat resolves on actual death. Emitted wave survives owner death/room clear and stops on terrain, pit, room bounds, lifetime or room change. Player hop lands exactly and clears on transition.',
    adaptations='; '.join(adaptations), unknowns='; '.join(remaining))
r['placement'] = [dict(kind='weighted_specialist', bands=[1], approved=True,
    evidence=BASE + 'source-review.md', note='Mines/Ashpit source habitats; authored weight1/cost4/cap1, natural seed1/floor2/room3. Does not modify Mine roster.')]
r['unresolved'] = remaining
for gate, path, scope in [
    ('behavior', 'native-targeted.txt', 'Normal armor/events/contact, crush wave/damage/terrain, hop recurrence/landing, capacity/lifecycle/config. Special branches remain open.'),
    ('reachability', 'web-final/results.json', 'Actual ordinary seeded resident from Rourke seed1/floor2/room3; dedicated runtime, wave and hop observed.'),
    ('visual_linux', 'native-slam-hop.png', visual['scope']),
    ('visual_wasm', 'web-final/near-wave.png', visual['scope'])]:
    r['validation'][gate].append(dict(path=BASE + path, result='partial_pass', scope=scope))
status['next_work'] = ['USER PRIORITY: regular enemies and required offspring before further bosses.',
    'Review Mushroom and continue the ordinary roster, then close behavior/placement/visual/balance/performance acceptance gaps.', *remaining]
status['latest_source_review'] = BASE + 'source-review.md'
status['checkpoint'].update(mechanics_fingerprint=fingerprint, report=BASE + 'checkpoint.json', native_tests=77,
    runtime_definitions=176, reviewed_records=162, partial_implementations=120,
    direct_pool_ids=71, enabled_pool_ids=75, wasm_final_build_cases=3,
    note='Partial Hard Host physical slam/crush-wave/hop port.77unique native suites and3productionWASM cases pass;11images inspected. Regular-enemy priority;zero complete ports;full six-gate acceptance remains open.')
save('docs/research/isaac-enemy-port-status.json', status)
checked = json.loads(subprocess.check_output(['python3', 'scripts/isaac-reference/track-enemies.py', '--check', '--csv'], cwd=ROOT, text=True))
assert checked['reviewed'] == 162 and checked['complete'] == 0
assert checked['implementations'] == dict(in_progress=120, existing_unverified=58, missing=463, excluded=12)
save(BASE + 'checklist-final.json', checked)
save('docs/research/isaac-enemy-port-validation.json', checked)
p = ROOT / 'docs/isaac_monsters.md'
text = p.read_text()
marker = 'Current implementation checkpoint:\n'
assert marker in text
p.write_text(text.replace(marker, marker + '''
The [Hard Host checkpoint](reports/isaac-enemy-port/hard_host/checkpoint.json)
replaces Hard Host's generic bullet attack with its armored slam, physical crush
wave, eligible terrain destruction and nearby player hop. Fingerprint
`8f59a76434a3149b`: **176 definitions, 162 reviewed, 120 in progress,
58 existing-unverified, 463 missing, 12 excluded; zero complete ports**.
There are 71 direct ordinary pool identities, 75 including replacements.
**77 unique native suites and three production WASM cases pass**, with 11 images
inspected. The [report](reports/isaac-enemy-port/hard_host/README.md) preserves
sources, adaptations, initial failures and corrected results. Regular enemies
and required offspring remain the priority; full fidelity and six-gate acceptance
are still open. Earlier checkpoints below describe their historical states.

''', 1))
old = load(PREVIOUS)
sources = set(old['source_sha256']) | {'scripts/isaac-reference/analyze-hard-host.py', BASE + 'source-review.md'}
sources |= {str(p.relative_to(ROOT)) for p in (OUT / 'source').rglob('*') if p.is_file()}
builds = set(old['build_sha256']) | {'build/deathward_hard_host_tests', 'build/deathward_crackle_tests'}
save(BASE + 'checkpoint.json', dict(status='Partial regular Hard Host port; full goal active.',
    created_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(), mechanics_fingerprint=fingerprint,
    runtime_definitions=176, item_definitions=13, enemy_bomb_profiles=6, checklist=checked,
    native=native, browser=browser, visual=visual, remaining=remaining, previous_checkpoint=PREVIOUS,
    implementation_review=BASE + 'implementation-review.json', historical_artifacts_preserved=len(history),
    runtime_sha256={p: sha(p) for p in sorted(set(old['runtime_sha256']) | set(runtime))},
    build_sha256={p: sha(p) for p in sorted(builds)}, source_sha256={p: sha(p) for p in sorted(sources)},
    artifacts_sha256={str(p.relative_to(ROOT)): sha(str(p.relative_to(ROOT))) for p in OUT.rglob('*') if p.is_file() and p.name != 'checkpoint.json'}))
print(json.dumps(dict(checkpoint=BASE + 'checkpoint.json', native_pass=77, wasm_pass=3,
    historical_unchanged=len(history), complete=0)))
