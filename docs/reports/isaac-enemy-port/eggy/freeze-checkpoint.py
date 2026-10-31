"""Freeze Eggy evidence once, preserving all previous checkpoints and failures."""
import datetime
import gzip
import hashlib
import json
import subprocess
import xml.etree.ElementTree as ET
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
BASE = 'docs/reports/isaac-enemy-port/eggy/'
OUT = ROOT / BASE
PREVIOUS = 'docs/reports/isaac-enemy-port/trite/checkpoint.json'


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
initial = ET.parse(OUT / 'native-final.xml').getroot().findall('.//testcase')
assert len(initial) == 80
assert {c.attrib['name'] for c in initial if not passed(c)} == {'prey_and_small_leech', 'monster_behaviors'}
passing = {c.attrib['name'] for c in initial if passed(c)}
corrections = {'prey-corrected.xml': 'prey_and_small_leech', 'monster-corrected.xml': 'monster_behaviors'}
for report, name in corrections.items():
    cases = ET.parse(OUT / report).getroot().findall('.//testcase')
    assert len(cases) == 1 and cases[0].attrib['name'] == name and passed(cases[0])
    passing.add(name)
assert len(passing) == 80
assert 'PASS Eggy' in (OUT / 'native-navigation.txt').read_text()
assert 'PASS Trite' in (OUT / 'trite-navigation.txt').read_text()
web = load(BASE + 'web-navigation/results.json')
assert len(web['checks']) == 5 and not web['errors']
assert {r['case'] for r in web['checks']} == {'isolated', 'cover', 'death', 'blast', 'resident'}
assert all(r['pass'] for r in web['checks'])
assert all('PASS ' + r['case'] in (OUT / 'browser-navigation.txt').read_text() for r in web['checks'])
visual = load(BASE + 'visual-review.json')
assert len(visual['final_images']) == 12 and all(r['inspected'] for r in visual['final_images'])
captures = load(BASE + 'native-final-captures.json')
assert len(captures) == 4 and all(r['exit_code'] == 0 for r in captures)
fingerprint = (OUT / 'mechanics-final.txt').read_text().split('fingerprint ')[1].split()[0]
assert fingerprint == '74a0ff8b3a6d27d2'
current = subprocess.check_output(['build/deathward_check_mechanics'], cwd=ROOT, text=True)
assert 'fingerprint ' + fingerprint in current
assert 'direct_pool_id_count=74' in (OUT / 'pool-audit.txt').read_text()
history = load(BASE + 'historical-integrity.json')['files']
assert len(history) == 6554
for path, digest in history.items():
    assert sha(path) == digest, path
subprocess.run(['python3', 'scripts/isaac-reference/analyze-eggy.py', '--check'],
               cwd=ROOT, check=True, capture_output=True)
for name in ['index.js', 'index.wasm', 'index.data']:
    path = ROOT / 'build-web' / name
    assert gzip.decompress(path.with_suffix(path.suffix + '.gz').read_bytes()) == path.read_bytes()

native = dict(passed=80, failed=0, report=BASE + 'native-final.xml', passing_suites=sorted(passing),
    correction_reports=[BASE + n for n in corrections], behavior=BASE + 'native-navigation.txt',
    shared_controller_regression=BASE + 'trite-navigation.txt',
    corrections='The completed full run passed78/80. Adding Eggy changed weighted choices; the older Prey witness search examined only the first band1 floor in256seeds. A bounded0..1023 search across all configured Flooded band1 floors finds Prey at seed242/floor3/room7 and Small Leech at seed5/floor2/room3. Spawn rules and all assertions remain unchanged.The legacy monster_behaviors assertion expected five instant Eggy children; it now requires a harmless husk,14releases before Die70 and14living dedicated Swarms after body removal.80distinct suites pass across the full run and these two corrected reruns, not a fresh full80/80 run. An earlier full run was interrupted after the runtime navigation fix made it stale; its partial native.txt log is retained.')
browser = dict(cases=5, report=BASE + 'web-navigation/results.json', scope=web['scope'], errors=[],
    build=BASE + 'build-wasm-navigation.txt', compression=BASE + 'web-compression-final.txt')
remaining = [
    'Native special-status/champion/control branches, Bursting Sack, unidentified release-suppression field and exact RNG/update ordering remain open.',
    'Native white-creep radius/slow semantics and grid marker900 remain unmeasured; friendly/charm behavior including the shared Tar harmsPlayer policy is not certified.',
    'Source fixed-grid/collision parity differs from arbitrary3D terrain; safe landing and blocked-snap fallback are explicit local adaptations.',
    'Ordinary generation-zero retained births are tested; the shared generation-depth limit above four remains local policy, not source parity.',
    'Native direct-pool probability/unlock/context parity, full mixed-room balance, all-angle readability and controlled Linux/WASM performance remain open; no complete port claimed.'
]
adaptations = [
    'Source30Hz within60Hz simulation; distance x.1, velocity x3, HP x3.2. Health(20+2*sourceStageMultiplier)*3.2; local base10contact.',
    'Shared physical target-hop controller predicts safe ground landings, crosses cover/water at actual height and blocks walls. A blocked snapped target falls back to the radius-clamped unsnapped candidate, fixing natural seed8/floor4/room10.',
    'White slow-only Tar patch: authored radius1.28, source-derived5second lifetime, local speed3.2/6 and.3second residual slow. Land restart can be suppressed when its local3D ground point is unsafe.',
    'Lethal ordinary hostile damage anchors an invulnerable non-contacting husk on legal ground. One kill/loot event resolves at Die70; husk and retained offspring hold room completion. Execution/friendly paths are not native-parity claims.',
    'Fourteen mandatory884.0.0 births retain source launch-kind/frame/momentum metadata through capacity delays and parent removal. Child placement can relocate from invalid terrain; source fixed-grid placement is not duplicated.',
    'Original procedural pale spotted spider, dark legs and lowered death body; dying HP bar hidden. No source artwork imported.',
    'Bands1-3 pursuit specialist weight1/cost4/cap1 is authored from habitat evidence. Mine roster, tutorial, hubs, expedition length and player defaults preserved.'
]
review = dict(scope='Partial normal-hostile Eggy29.2 hopping, white creep and timed Swarm Spider death sequence.',
    source=BASE + 'source-review.md', adaptations=adaptations, remaining=remaining,
    native=native, browser=browser, visual=visual, complete=False)
save(BASE + 'implementation-review.json', review)
old = load(PREVIOUS)
runtime = sorted({p for p, h in old['runtime_sha256'].items() if sha(p) != h} | {
    'assets/mechanics/eggies.mechanics', 'src/combat/Eggies.cpp',
    'tests/eggy_tests.cpp', 'web/eggy-test.cjs', 'tests/prey_tests.cpp'})
status = load('docs/research/isaac-enemy-port-status.json')
save(BASE + 'status-before.json', status)
r = next(r for r in status['records'] if r['id'] == '29.2.0')
assert r['implementation'] == 'existing_unverified' and r['review'] == 'pending'
r.update(review='reviewed', disposition='ordinary', implementation='in_progress')
r['runtime'] = list(dict.fromkeys(r['runtime'] + runtime))
r['evidence'].append(dict(source=BASE + 'source-review.md',
    supports='Installed29.2 shared-controller branch, current versus accumulated event query, normal zero-status14-child formula, child launch fields and Die/Hop animation metadata. Native source rules separated from3D/death/creep adapters.'))
r['contract'] = dict(
    movement='Source shared destination inertia .7*(velocity+force), zero random bonus, normal target/wander selection. Physical safe cover/water hopping with walls; blocked snapped target falls back to unsnapped legal candidate.',
    targeting='Strict91native-unit acquisition, candidate target with no Trite overshoot; wander95; clamp/grid and local predicted-safe landing. No velocity prediction or ordinary sight requirement.',
    attacks='Contact base10 and white slow-only creep on Land17; no ranged shots. Creep5sec, authored radius1.28/local Tar strength. One-in-three Land restart skips preparation on next legal hop.',
    vulnerability='Source(20+2*stageMultiplier)HP x3.2. Ordinary body damageable; lethal damage beginsHP.1 harmless invulnerable husk. Repeated ordinary hits do not restart death; shots pass through.',
    phases='Source30Hz, idle8, Hop26/Jump4/Land17; one-in-three restart atJump4. Die70 with release counter beginningJump7; position anchored. Local stun and suspension preserve death progress.',
    offspring='14Swarm Spiders884.0.0 at Die frames8,11,13,14,17,19,20,21,25,31,36,37,51,66. Independent scatter/direction, hop weights3:2:1, source speed bands, first frames4/5/6. Required births retained under capacity with launch metadata.',
    completion='Husk and pending children hold clear; one parent kill/loot at Die70;14real children continue as threats. Re-entry freezes/resumes clock and pending births. General depth-limit parity remains open.',
    adaptations='; '.join(adaptations), unknowns='; '.join(remaining))
r['placement'] = [dict(kind='weighted_specialist', bands=[1, 2, 3], approved=True,
    evidence=BASE + 'source-review.md', note='Sparse pursuit specialist from Necropolis/Utero and rare Catacombs/Corpse habitat; authored weight1/cost4/cap1. Natural Rourke seed8/floor4/room10.')]
r['unresolved'] = remaining
for gate, path, scope in [
    ('behavior', 'native-navigation.txt', 'Normal hopping, creep, measured death cadence and child launch, damage collision, retained births, suspension, stun and external snapshots. Native special branches remain open.'),
    ('reachability', 'web-navigation/results.json', 'Natural Rourke seed8/floor4/room10 with physical hops and creep after fixing blocked-grid-target stall.'),
    ('visual_linux', 'native-final-release.png', visual['scope']),
    ('visual_wasm', 'web-navigation/resident-resident.png', visual['scope'])]:
    r['validation'][gate].append(dict(path=BASE + path, result='partial_pass', scope=scope))
status['next_work'] = ['USER PRIORITY: regular enemies and required offspring before further bosses.',
    'Continue Tainted Hopper and Leaper variants; improve normal/Flaming Hopper source fidelity.',
    'Close full behavior/placement/visual/balance/performance gaps for regular families.', *remaining]
status['latest_source_review'] = BASE + 'source-review.md'
status['checkpoint'].update(mechanics_fingerprint=fingerprint, report=BASE + 'checkpoint.json', native_tests=80,
    runtime_definitions=177, reviewed_records=165, partial_implementations=123,
    direct_pool_ids=74, enabled_pool_ids=78, wasm_final_build_cases=5,
    note='Partial normal Eggy port.80unique native suites pass across full run and two corrected reruns;5productionWASM cases pass;12accepted images. Regular-enemy priority;zero complete ports;full six-gate acceptance open.')
save('docs/research/isaac-enemy-port-status.json', status)
checked = json.loads(subprocess.check_output(['python3', 'scripts/isaac-reference/track-enemies.py', '--check', '--csv'], cwd=ROOT, text=True))
assert checked['reviewed'] == 165 and checked['complete'] == 0
assert checked['implementations'] == dict(in_progress=123, existing_unverified=56, missing=462, excluded=12)
save(BASE + 'checklist-final.json', checked)
save('docs/research/isaac-enemy-port-validation.json', checked)
p = ROOT / 'docs/isaac_monsters.md'
text = p.read_text()
marker = 'Current implementation checkpoint:\n'
assert marker in text
p.write_text(text.replace(marker, marker + '''
The [Eggy checkpoint](reports/isaac-enemy-port/eggy/checkpoint.json) adds
source-derived hopping, white slowing creep and a timed fourteen-Swarm death
sequence to ordinary encounters. Fingerprint `74a0ff8b3a6d27d2`:
**177 definitions, 165 reviewed, 123 in progress, 56 existing-unverified,
462 missing, 12 excluded; zero complete ports**. There are74 direct ordinary
pool identities,78 including replacements. **80 distinct native suites pass**
across the full run and two corrected regressions; five production WASM
cases pass and twelve accepted images were inspected. The
[report](reports/isaac-enemy-port/eggy/README.md) preserves initial failures,
the real generated-room navigation fix, sources and adaptations. Regular enemies
and required offspring remain first; full six-gate acceptance is open.
Earlier checkpoints below are historical.

''', 1))
sources = set(old['source_sha256']) | {'scripts/isaac-reference/analyze-eggy.py',
    BASE + 'source-review.md', BASE + 'record.json', BASE + 'wiki-source.json', BASE + 'extract-metadata.py'}
sources |= {str(p.relative_to(ROOT)) for directory in ['source', 'animations']
            for p in (OUT / directory).rglob('*') if p.is_file()}
builds = set(old['build_sha256']) | {'build/deathward_eggy_tests', 'build/deathward_prey_tests'}
save(BASE + 'checkpoint.json', dict(status='Partial regular Eggy port; full goal active.',
    created_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(), mechanics_fingerprint=fingerprint,
    runtime_definitions=177, item_definitions=13, enemy_bomb_profiles=6, checklist=checked,
    native=native, browser=browser, visual=visual, remaining=remaining, previous_checkpoint=PREVIOUS,
    implementation_review=BASE + 'implementation-review.json', historical_artifacts_preserved=len(history),
    runtime_sha256={p: sha(p) for p in sorted(set(old['runtime_sha256']) | set(runtime))},
    build_sha256={p: sha(p) for p in sorted(builds)}, source_sha256={p: sha(p) for p in sorted(sources)},
    artifacts_sha256={str(p.relative_to(ROOT)): sha(str(p.relative_to(ROOT))) for p in OUT.rglob('*') if p.is_file() and p.name != 'checkpoint.json'}))
print(json.dumps(dict(checkpoint=BASE + 'checkpoint.json', native_pass=80, wasm_pass=5,
    historical_unchanged=len(history), complete=0)))
