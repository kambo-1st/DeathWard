"""Freeze once after final evidence passes; older evidence remains immutable."""
import datetime
import hashlib
import json
import subprocess
import xml.etree.ElementTree as ET
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
BASE = 'docs/reports/isaac-enemy-port/mushroom/'
OUT = ROOT / BASE
PREVIOUS = 'docs/reports/isaac-enemy-port/hard_host/checkpoint.json'


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
cases = ET.parse(OUT / 'native-final.xml').getroot().findall('.//testcase')
assert len(cases) == 78 and all(passed(c) for c in cases)
passing = sorted(c.attrib['name'] for c in cases)
assert 'PASS Mushroom' in (OUT / 'native-targeted.txt').read_text()
web = load(BASE + 'web-placement/results.json')
assert len(web['checks']) == 3 and not web['errors']
assert {r['case'] for r in web['checks']} == {'isolated', 'closed-hit', 'resident'}
assert all('PASS ' + r['case'] in (OUT / 'browser-placement.txt').read_text() for r in web['checks'])
visual = load(BASE + 'visual-review.json')
assert len(visual['final_images']) == 11 and all(r['inspected'] for r in visual['final_images'])
captures = load(BASE + 'native-final-captures.json')
assert len(captures) == 4 and all(r['exit_code'] == 0 for r in captures)
fingerprint = (OUT / 'mechanics-final.txt').read_text().split('fingerprint ')[1].split()[0]
assert fingerprint == '6cb687923a293a80'
assert 'direct_pool_id_count=72' in (OUT / 'pool-audit.txt').read_text()
history = load(BASE + 'historical-integrity.json')['files']
assert len(history) == 6401
for path, digest in history.items():
    assert sha(path) == digest, path
subprocess.run(['python3', 'scripts/isaac-reference/analyze-mushroom.py', '--check'],
               cwd=ROOT, check=True, capture_output=True)

native = dict(passed=78, failed=0, report=BASE + 'native-final.xml', passing_suites=passing,
    initial_report=BASE + 'native.xml', behavior=BASE + 'native-targeted.txt',
    corrections='Initial full run77/78: unchanged expedition_pacing exposed a solid Grimace blocking the room center in Classic seed0/Canyon/room1. Generic placement now reserves the actual statue footprint and checks entry/center/objective/door connectivity, matching the progression spawner. Final full78/78pass; no test weakened.')
browser = dict(cases=3, report=BASE + 'web-placement/results.json', scope=web['scope'], errors=[],
    build=BASE + 'build-wasm-placement.txt',
    corrections='Initial behavior cases passed but inherited single aimed warning ray misrepresented the fixed-axis cross. Suppressed it for Mushroom. Final browser run follows rendering and statue placement fixes; compressed assets refreshed.')
remaining = [
    'Petrification and its loss of closed resistance, champions and controlled/friendly native branches remain open.',
    'Exact native RNG and damage-queue/update ordering, projectile vertical physics and special item/status interactions remain open.',
    'Source20% Host/Red Host replacement and unlock conditions remain open; direct band1 specialist weight2/cost3/cap1 is an adaptation.',
    'Full combat readability, balance and controlled Linux/WASM performance acceptance remain open; no complete port is claimed.'
]
adaptations = [
    'Source30Hz, distance x.1, velocity x3, HP x3.2; source23HP becomes73.6, source7 shot speed becomes21. Authored radius.7 and base10 hostile contact/projectile damage.',
    'Physical combat-plane projectiles have authored5second lifetime and ordinary wall collision; original cap/stem art has no imported source artwork.',
    'Whole four-shot cross waits under projectile/event capacity pressure without rerolling its orientation; local stun pauses the cycle and room suspension preserves it.',
    'Anchored body restoration prevents local separation/impulses from causing drift. Native grid/entity physics and ordering are not asserted identical.',
    'Direct seeded Caves-analogue band1 specialist placement is authored; Mine, tutorial, hubs, expedition length and player defaults stay unchanged.'
]
review = dict(scope='Partial normal-hostile Mushroom300.0 closed resistance, source-frame cycle and cardinal/diagonal physical cross.',
    source=BASE + 'source-review.md', adaptations=adaptations, remaining=remaining,
    native=native, browser=browser, visual=visual, complete=False)
save(BASE + 'implementation-review.json', review)
runtime = ['assets/mechanics/mushrooms.mechanics', 'src/content/Mechanics.hpp',
    'src/content/Mechanics.cpp', 'src/content/EncounterVariants.cpp', 'src/combat/Simulation.hpp',
    'src/combat/Mushrooms.cpp', 'src/combat/Monsters.cpp', 'src/combat/Enemies.cpp',
    'src/combat/Encounters.cpp', 'src/render/Renderer.cpp', 'src/render/MonsterVisuals.hpp',
    'src/main.cpp', 'tests/mushroom_tests.cpp', 'web/mushroom-test.cjs', 'CMakeLists.txt']
status = load('docs/research/isaac-enemy-port-status.json')
save(BASE + 'status-before.json', status)
r = next(r for r in status['records'] if r['id'] == '300.0.0')
assert r['implementation'] == 'missing' and r['review'] == 'pending'
r.update(review='reviewed', disposition='ordinary', implementation='in_progress')
r['runtime'] = list(dict.fromkeys(r['runtime'] + runtime))
r['evidence'].append(dict(source=BASE + 'source-review.md',
    supports='Pinned installed type300 controller, state dispatch, damage multiplier, FireProjectiles modes6/7 and common postpass; ANM2 events and source habitat records. Explicit adaptations and unimplemented branches.'))
r['contract'] = dict(
    movement='Stationary at saved initial position; local contact10 active even while closed. No pursuit or ranged target acquisition.',
    targeting='Normal hostile cycle has no range or sight requirement. Random cardinal or diagonal world-axis burst, not aimed at target.',
    attacks='Reveal Shoot3 produces four shots. Cardinal axes or all sign combinations of diagonal .707106769; speed21, base10damage, local5second lifetime. Ordinary walls stop shots. Whole cross retained under queue/capacity pressure.',
    vulnerability='23sourceHP becomes73.6. InitialHide/Blocking take25% damage, including Burning/Crush/explosions. Reveal/Revealed/Hide take full damage. Retracting is not armored until Hide finishes.',
    phases='Initial Hide6 once; blocked30*(1..5)frames; Reveal6 with Shoot3; exposed30*(1..3); Hide6, then blocked.30Hz. Orientation chosen once per cast. Local stun pauses; death cancels unemitted burst.',
    offspring='No normal NPC offspring or special death spawn in the reviewed controller.',
    completion='Ordinary threat resolves on actual death; leaving/re-entering retains phase/timer/orientation. Emitted projectiles follow ordinary lifecycle.',
    adaptations='; '.join(adaptations), unknowns='; '.join(remaining))
r['placement'] = [dict(kind='weighted_specialist', bands=[1], approved=True,
    evidence=BASE + 'source-review.md', note='Positive-weight Caves/Catacombs/Flooded Caves habitats. Authored weight2/cost3/cap1; natural Rourke seed1/floor2/room5. Does not implement Host replacement/unlock parity.')]
r['unresolved'] = remaining
for gate, path, scope in [
    ('behavior', 'native-targeted.txt', 'Source-frame normal cycle/resistance/cross, contact/terrain, lifecycle, limits, external config and placement. Special branches remain open.'),
    ('reachability', 'web-placement/results.json', 'Actual seeded ordinary resident, Rourke seed1/floor2/room5; dedicated phases and shots observed.'),
    ('visual_linux', 'native-final-burst.png', visual['scope']),
    ('visual_wasm', 'web-placement/isolated-burst.png', visual['scope'])]:
    r['validation'][gate].append(dict(path=BASE + path, result='partial_pass', scope=scope))
status['next_work'] = ['USER PRIORITY: regular enemies and required offspring before further bosses.',
    'Continue Hopper/Trite/Eggy/Tainted Hopper and Leaper families; replace generic variant behavior from source evidence.',
    'Close full behavior/placement/visual/balance/performance acceptance gaps, including previously ported regular families.', *remaining]
status['latest_source_review'] = BASE + 'source-review.md'
status['checkpoint'].update(mechanics_fingerprint=fingerprint, report=BASE + 'checkpoint.json', native_tests=78,
    runtime_definitions=177, reviewed_records=163, partial_implementations=121,
    direct_pool_ids=72, enabled_pool_ids=76, wasm_final_build_cases=3,
    note='Partial normal Mushroom port.78/78native suites and3productionWASM cases pass;11images inspected. Fixed Classic statue route blockage without weakening test. Regular-enemy priority;zero complete ports;full six-gate acceptance open.')
save('docs/research/isaac-enemy-port-status.json', status)
checked = json.loads(subprocess.check_output(['python3', 'scripts/isaac-reference/track-enemies.py', '--check', '--csv'], cwd=ROOT, text=True))
assert checked['reviewed'] == 163 and checked['complete'] == 0
assert checked['implementations'] == dict(in_progress=121, existing_unverified=58, missing=462, excluded=12)
save(BASE + 'checklist-final.json', checked)
save('docs/research/isaac-enemy-port-validation.json', checked)
p = ROOT / 'docs/isaac_monsters.md'
text = p.read_text()
marker = 'Current implementation checkpoint:\n'
assert marker in text
p.write_text(text.replace(marker, marker + '''
The [Mushroom checkpoint](reports/isaac-enemy-port/mushroom/checkpoint.json)
adds Mushroom's closed resistance, timed reveal and four-shot cardinal/diagonal
cross to ordinary Caves-equivalent encounters. Fingerprint `6cb687923a293a80`:
**177 definitions, 163 reviewed, 121 in progress, 58 existing-unverified,
462 missing, 12 excluded; zero complete ports**. There are 72 direct ordinary
pool identities, 76 including replacements. **78/78 native suites and three
production WASM cases pass**, with eleven inspected images. The
[report](reports/isaac-enemy-port/mushroom/README.md) preserves sources, adaptations
and the Classic statue-route regression and fix. Regular enemies and required
offspring remain first; full six-gate acceptance is open. Earlier checkpoints
below describe historical states.

''', 1))
old = load(PREVIOUS)
sources = set(old['source_sha256']) | {'scripts/isaac-reference/analyze-mushroom.py',
    BASE + 'source-review.md', BASE + 'record.json', BASE + 'extract-metadata.py'}
sources |= {str(p.relative_to(ROOT)) for directory in ['source', 'animations']
            for p in (OUT / directory).rglob('*') if p.is_file()}
builds = set(old['build_sha256']) | {'build/deathward_mushroom_tests'}
save(BASE + 'checkpoint.json', dict(status='Partial regular Mushroom port; full goal active.',
    created_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(), mechanics_fingerprint=fingerprint,
    runtime_definitions=177, item_definitions=13, enemy_bomb_profiles=6, checklist=checked,
    native=native, browser=browser, visual=visual, remaining=remaining, previous_checkpoint=PREVIOUS,
    implementation_review=BASE + 'implementation-review.json', historical_artifacts_preserved=len(history),
    runtime_sha256={p: sha(p) for p in sorted(set(old['runtime_sha256']) | set(runtime))},
    build_sha256={p: sha(p) for p in sorted(builds)}, source_sha256={p: sha(p) for p in sorted(sources)},
    artifacts_sha256={str(p.relative_to(ROOT)): sha(str(p.relative_to(ROOT))) for p in OUT.rglob('*') if p.is_file() and p.name != 'checkpoint.json'}))
print(json.dumps(dict(checkpoint=BASE + 'checkpoint.json', native_pass=78, wasm_pass=3,
    historical_unchanged=len(history), complete=0)))
