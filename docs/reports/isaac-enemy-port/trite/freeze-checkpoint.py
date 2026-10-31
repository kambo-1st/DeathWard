"""Freeze the Trite slice once; retain previous evidence and initial failures."""
import datetime
import gzip
import hashlib
import json
import subprocess
import xml.etree.ElementTree as ET
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
BASE = 'docs/reports/isaac-enemy-port/trite/'
OUT = ROOT / BASE
PREVIOUS = 'docs/reports/isaac-enemy-port/mushroom/checkpoint.json'


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
initial = ET.parse(OUT / 'native.xml').getroot().findall('.//testcase')
assert len(initial) == 79
assert {c.attrib['name'] for c in initial if not passed(c)} == {'hive_evaders', 'mulligan_family'}
passing = {c.attrib['name'] for c in initial if passed(c)}
corrections = {'hive-final.xml': 'hive_evaders', 'mulligan-corrected.xml': 'mulligan_family'}
for report, name in corrections.items():
    cases = ET.parse(OUT / report).getroot().findall('.//testcase')
    assert len(cases) == 1 and cases[0].attrib['name'] == name and passed(cases[0])
    passing.add(name)
assert len(passing) == 79
assert 'PASS Trite' in (OUT / 'native-targeted.txt').read_text()
web = load(BASE + 'web-final/results.json')
assert len(web['checks']) == 4 and not web['errors']
assert {r['case'] for r in web['checks']} == {'isolated', 'cover', 'river', 'resident'}
assert all('PASS ' + r['case'] in (OUT / 'browser-final.txt').read_text() for r in web['checks'])
visual = load(BASE + 'visual-review.json')
assert len(visual['final_images']) == 11 and all(r['inspected'] for r in visual['final_images'])
captures = load(BASE + 'native-captures.json')
assert len(captures) == 6 and all(r['exit_code'] == 0 for r in captures)
fingerprint = (OUT / 'mechanics-final.txt').read_text().split('fingerprint ')[1].split()[0]
assert fingerprint == 'd16f1a8e6aa61d3f'
assert 'direct_pool_id_count=73' in (OUT / 'pool-audit.txt').read_text()
history = load(BASE + 'historical-integrity.json')['files']
assert len(history) == 6481
for path, digest in history.items():
    assert sha(path) == digest, path
subprocess.run(['python3', 'scripts/isaac-reference/analyze-trite.py', '--check'],
               cwd=ROOT, check=True, capture_output=True)
for name in ['index.js', 'index.wasm', 'index.data']:
    path = ROOT / 'build-web' / name
    assert gzip.decompress(path.with_suffix(path.suffix + '.gz').read_bytes()) == path.read_bytes()

native = dict(passed=79, failed=0, report=BASE + 'native.xml', passing_suites=sorted(passing),
    correction_reports=[BASE + n for n in corrections], behavior=BASE + 'native-targeted.txt',
    corrections='Initial full run77/79. Weighted-pool addition invalidated old fixed seed witnesses for Mulligoon and Drowned Hive. Bounded production searches preserve spawn rules and assertions; both corrected suites pass. An intermediate Hive filter incorrectly read an unconfigured profile; final uses production configureFloor. Evidence is79 distinct passing suites across the full run and targeted reruns, not a fresh full79/79 run.')
browser = dict(cases=4, report=BASE + 'web-final/results.json', scope=web['scope'], errors=[],
    build=BASE + 'build-wasm.txt', compression=BASE + 'web-compression.txt')
remaining = [
    'Native special-status/champion/control branches and exact RNG/update ordering remain open.',
    'Native grid/collision parity and unusual geometry require further acceptance; real3D elevation and safe landing are adaptations.',
    'Source Hopper replacement probability/unlock/context rules remain open; direct bands0-2 specialist weight2/cost2/cap2 is authored.',
    'Full mixed-room balance, all-angle combat readability and controlled Linux/WASM performance remain open; no complete port claimed.'
]
adaptations = [
    'Source30Hz within60Hz simulation; distance x.1, velocity x3, HP x3.2; source10HP becomes32. Radius.5, height1.6 and base10contact authored.',
    'Four-unit destination grid anchored within generated room bounds, radius-aware clamping and legal-floor checks replace source fixed-coordinate grid.',
    'Same-force trajectory prediction rejects unsafe landings; flight sweeps cross cover/water while walls block. Actual height affects collision/aiming. Closing geometry restores last legal ground without a swept corrective attack.',
    'Stun cancels grounded preparation or permits airborne motion to safe ground before waiting. Room suspension retains complete runtime. Friendly contact uses local adapter, not native charm certification.',
    'Original procedural orange spider retained; preparation ring replaces misleading aimed ray. No source artwork imported.',
    'Seeded direct ordinary bands0-2 placement is authored; Mine roster, tutorial, hubs, expedition length and player defaults unchanged.'
]
review = dict(scope='Partial normal-hostile Trite29.1 destination law, source-frame inertia and physical hopping.',
    source=BASE + 'source-review.md', adaptations=adaptations, remaining=remaining,
    native=native, browser=browser, visual=visual, complete=False)
save(BASE + 'implementation-review.json', review)
runtime = ['assets/mechanics/trites.mechanics', 'assets/mechanics/monsters.mechanics',
    'src/content/Mechanics.hpp', 'src/content/Mechanics.cpp', 'src/content/EncounterVariants.cpp',
    'src/combat/Simulation.hpp', 'src/combat/TargetHops.cpp', 'src/combat/Monsters.cpp',
    'src/combat/MonsterMovement.cpp', 'src/render/Renderer.cpp', 'src/main.cpp',
    'tests/trite_tests.cpp', 'tests/evader_tests.cpp', 'tests/mulligan_tests.cpp',
    'web/trite-test.cjs', 'CMakeLists.txt']
status = load('docs/research/isaac-enemy-port-status.json')
save(BASE + 'status-before.json', status)
r = next(r for r in status['records'] if r['id'] == '29.1.0')
assert r['implementation'] == 'existing_unverified' and r['review'] == 'pending'
r.update(review='reviewed', disposition='ordinary', implementation='in_progress')
r['runtime'] = list(dict.fromkeys(r['runtime'] + runtime))
r['evidence'].append(dict(source=BASE + 'source-review.md',
    supports='Installed shared controller variant29.1 branch, target helper, base friction/time integration, event masks, grid helpers and ANM2 metadata; exact source/destination law separated from3D adaptations.'))
r['contract'] = dict(
    movement='Destination-based inertia: .7*(velocity+force); far force.05*delta, grounded delta factor.1; near normalized direction. Source units converted; physical cover/water flight and blocked walls.',
    targeting='Every normal frame b=50*U+70*V. Strict range130+1.3*b. Near candidate target+(target-self)*b/200; far random95+b. Clamp/snap, then commit. No ordinary velocity prediction or sight requirement.',
    attacks='Contact10 only, using actual3D swept body. No normal shots. Air collision beginsJump4 and persists untilHop26, including afterLand18.',
    vulnerability='Source10HP/stage0 converted to32. Ordinary damageable body; no special armor added. Real elevation affects attack intersections.',
    phases='Source30Hz, idle threshold15; Hop26/Jump4/Land18. After Hop release at distance<10 or1/10 if speed<.75 orcounter>30; last steering impulse still applied. Local stun handling explicit.',
    offspring='No ordinary projectile/death-child branch. Existing parents spawning29.1 also receive dedicated controller.',
    completion='One ordinary room threat resolves on actual death. Re-entry retains destination/momentum/frame/position. No pending offspring or death hop.',
    adaptations='; '.join(adaptations), unknowns='; '.join(remaining))
r['placement'] = [dict(kind='weighted_specialist', bands=[0, 1, 2], approved=True,
    evidence=BASE + 'source-review.md', note='Cellar/Caves/Necropolis habitat analogues; authored weight2/cost2/cap2. Natural Rourke seed0/floor1/room2. Source replacement parity remains open.')]
r['unresolved'] = remaining
for gate, path, scope in [
    ('behavior', 'native-targeted.txt', 'Normal timing/selection/numeric inertia, real terrain, lifecycle, contact, external config and isolated default-kit kill. Native special branches remain open.'),
    ('reachability', 'web-final/results.json', 'Actual ordinary seeded resident Rourke seed0/floor1/room2 with dedicated hopping.'),
    ('visual_linux', 'native-air.png', visual['scope']),
    ('visual_wasm', 'web-final/river-river.png', visual['scope']),
    ('balance', 'native-targeted.txt', 'Isolated starting100HP/default-damage kit kills Trite in1.11667sec with100HP remaining. Not mixed-room balance acceptance.')]:
    r['validation'][gate].append(dict(path=BASE + path, result='partial_pass', scope=scope))
status['next_work'] = ['USER PRIORITY: regular enemies and required offspring before further bosses.',
    'Continue Eggy with required Swarm offspring, Tainted Hopper and Leaper variants; improve normal/Flaming Hopper source fidelity.',
    'Close full behavior/placement/visual/balance/performance gaps for regular families.', *remaining]
status['latest_source_review'] = BASE + 'source-review.md'
status['checkpoint'].update(mechanics_fingerprint=fingerprint, report=BASE + 'checkpoint.json', native_tests=79,
    runtime_definitions=177, reviewed_records=164, partial_implementations=122,
    direct_pool_ids=73, enabled_pool_ids=77, wasm_final_build_cases=4,
    note='Partial normal Trite port.79unique native suites pass across full run and two corrected witness reruns;4productionWASM cases pass;11accepted images. Regular-enemy priority;zero complete ports;full six-gate acceptance open.')
save('docs/research/isaac-enemy-port-status.json', status)
checked = json.loads(subprocess.check_output(['python3', 'scripts/isaac-reference/track-enemies.py', '--check', '--csv'], cwd=ROOT, text=True))
assert checked['reviewed'] == 164 and checked['complete'] == 0
assert checked['implementations'] == dict(in_progress=122, existing_unverified=57, missing=462, excluded=12)
save(BASE + 'checklist-final.json', checked)
save('docs/research/isaac-enemy-port-validation.json', checked)
p = ROOT / 'docs/isaac_monsters.md'
text = p.read_text()
marker = 'Current implementation checkpoint:\n'
assert marker in text
p.write_text(text.replace(marker, marker + '''
The [Trite checkpoint](reports/isaac-enemy-port/trite/checkpoint.json) adds
dedicated destination hopping, source-frame inertia and physical cover/water
traversal to ordinary encounters. Fingerprint `d16f1a8e6aa61d3f`:
**177 definitions, 164 reviewed, 122 in progress, 57 existing-unverified,
462 missing, 12 excluded; zero complete ports**. There are 73 direct ordinary
pool identities, 77 including replacements. **79 distinct native suites pass**
across the full run and two corrected witness searches; four production WASM
cases pass and eleven accepted images were inspected. The
[report](reports/isaac-enemy-port/trite/README.md) preserves initial failures,
sources and adaptations. Regular enemies and required offspring remain first;
full six-gate acceptance is open. Earlier checkpoints below are historical.

''', 1))
old = load(PREVIOUS)
sources = set(old['source_sha256']) | {'scripts/isaac-reference/analyze-trite.py',
    BASE + 'source-review.md', BASE + 'record.json', BASE + 'wiki-source.json', BASE + 'extract-metadata.py'}
sources |= {str(p.relative_to(ROOT)) for directory in ['source', 'animations']
            for p in (OUT / directory).rglob('*') if p.is_file()}
builds = set(old['build_sha256']) | {'build/deathward_trite_tests', 'build/deathward_evader_tests', 'build/deathward_mulligan_tests'}
save(BASE + 'checkpoint.json', dict(status='Partial regular Trite port; full goal active.',
    created_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(), mechanics_fingerprint=fingerprint,
    runtime_definitions=177, item_definitions=13, enemy_bomb_profiles=6, checklist=checked,
    native=native, browser=browser, visual=visual, remaining=remaining, previous_checkpoint=PREVIOUS,
    implementation_review=BASE + 'implementation-review.json', historical_artifacts_preserved=len(history),
    runtime_sha256={p: sha(p) for p in sorted(set(old['runtime_sha256']) | set(runtime))},
    build_sha256={p: sha(p) for p in sorted(builds)}, source_sha256={p: sha(p) for p in sorted(sources)},
    artifacts_sha256={str(p.relative_to(ROOT)): sha(str(p.relative_to(ROOT))) for p in OUT.rglob('*') if p.is_file() and p.name != 'checkpoint.json'}))
print(json.dumps(dict(checkpoint=BASE + 'checkpoint.json', native_pass=79, wasm_pass=4,
    historical_unchanged=len(history), complete=0)))
