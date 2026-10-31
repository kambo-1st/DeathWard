"""Freeze this validated slice once; preserve every earlier report artifact."""
import datetime, hashlib, json, subprocess, xml.etree.ElementTree as ET
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
BASE = 'docs/reports/isaac-enemy-port/hive/'
OUT = ROOT / BASE
PREVIOUS = 'docs/reports/isaac-enemy-port/tainted_pooter/checkpoint.json'
def load(p): return json.loads((ROOT/p).read_text())
def save(p, v): (ROOT/p).write_text(json.dumps(v, indent=2, ensure_ascii=False)+'\n')
def sha(p):
    h = hashlib.sha256()
    with (ROOT/p).open('rb') as f:
        for block in iter(lambda: f.read(4*1024*1024), b''): h.update(block)
    return h.hexdigest()

assert not (OUT/'checkpoint.json').exists()
initial = ET.parse(OUT/'native.xml').getroot()
retry = ET.parse(OUT/'native-floor-retry.xml').getroot()
assert initial.attrib['tests'] == '67' and initial.attrib['failures'] == '1'
assert [t.attrib['name'] for t in initial if t.find('failure') is not None] == ['floor_progression']
assert retry.attrib['tests'] == '1' and retry.attrib['failures'] == '0'
assert retry[0].attrib['name'] == 'floor_progression'
assert 'PASS Hive/Drowned evaders' in (OUT/'behavior-final.txt').read_text()
coverage = {t.attrib['name']: {'result': 'fail' if t.find('failure') is not None else 'pass', 'report': BASE+'native.xml'} for t in initial}
coverage['floor_progression'] = {'result': 'pass', 'report': BASE+'native-floor-retry.xml'}
assert len(coverage) == 67 and all(v['result'] == 'pass' for v in coverage.values())
save(BASE+'native-coverage.json', {'covered_suites': 67, 'passed': 67, 'failed': 0, 'suites': coverage,
    'note': 'Initial full run66/67; only floor_progression failed. The expanded fallback seed search then passed unchanged production mechanics. No failed original report was overwritten.'})
web = load(BASE+'web/results.json')
assert len(web['checks']) == 8 and not web['errors']
assert {c['case'] for c in web['checks']} == {'hive-live','drowned-live','hive-death','drowned-death','hive-overkill','drowned-overkill','natural-hive','natural-drowned'}
fingerprint = (OUT/'mechanics.txt').read_text().split('fingerprint ')[1].split()[0]
assert fingerprint == 'b6d232227ffffd87'
assert load(BASE+'pool-audit.json')['counts'] == {'direct': 44, 'enabled': 46}
subprocess.run(['python3','scripts/isaac-reference/analyze-hive.py','--check'], cwd=ROOT, check=True, capture_output=True)
history = load(BASE+'historical-integrity.json')['files']
for path, digest in history.items(): assert sha(path) == digest, path
old, source = load(PREVIOUS), load(BASE+'source-review.json')
native = {'covered_suites': 67, 'passed': 67, 'failed': 0, 'report': BASE+'native-coverage.json',
    'initial_report': BASE+'native.xml', 'retry_report': BASE+'native-floor-retry.xml', 'behavior': BASE+'behavior-final.txt',
    'scope': 'Full67-suite run passed66; only the bounded rare-replacement seed sample failed after pool expansion. Raising its fallback ceiling128to512 while retaining the32-seed broad sweep and all assertions passed the focused rerun. Production mechanics and chances were unchanged.',
    'tests': 'Source-scaled health, harmless contact, proximity/Shoot4/Attack18/cooldown ordering, room-wide population delay, child policy/halfHP, atomic Shoot under capacity pressure, placement retry after parent removal, independent7:3:1death draws, population-sensitive count, inclusive scaled overkill, reserved births and room completion, flee/wander, invalid config and immutable reloads, conditional odds and actual seeded residents.'}
browser = {'cases': 8, 'report': BASE+'web/results.json', 'errors': [],
    'scope': 'Production Original-style Hive/Drowned live movement/spawning, death count and identity/health, overkill suppression, real seed9floor0Hive and seed66floor2Drowned residents. Native tests supply exact timing and retained-contact-policy checks.',
    'note': 'Initial Drowned death hit57.6left a positive float remainder against18*3.2health. The scripted normal-death hit was corrected to58without a runtime change. Initial test/log/results and numeric explanation are preserved.'}
visual = {'result': 'Inspected Original low-poly Hive and Drowned bodies, offspring, ground contact/shadows and real resident room placement in native/browser captures. Natural Drowned eventually moves behind the top-right HUD in the later browser framing; no all-angle readability or controlled performance acceptance is claimed.',
    'linux': [BASE+'native-hive.png', BASE+'native-drowned-resident.png'],
    'wasm': [BASE+'web/hive-live.png', BASE+'web/drowned-live.png', BASE+'web/natural-drowned.png']}
runtime = ['assets/mechanics/evaders.mechanics','assets/mechanics/monsters.mechanics','assets/mechanics/deaths.mechanics',
    'src/combat/Evaders.cpp','src/combat/Monsters.cpp','src/combat/Simulation.hpp','src/content/Mechanics.hpp',
    'src/content/Mechanics.cpp','src/content/EncounterVariants.cpp','tests/evader_tests.cpp','tests/monster_tests.cpp',
    'tests/buzz_fly_tests.cpp','tests/floor_progression_tests.cpp','web/hive-test.cjs','CMakeLists.txt','README.md']
save(BASE+'implementation-review.json', {'scope': source['scope'], 'mechanics_fingerprint': fingerprint,
    'changes': ['Replace generic Hive/Drowned fleeing/spawning with reusable source-based proximity, attack-event and population-sensitive controller.',
        'Independent population-scaled death draws, source mixture, half-health Drowned offspring and consistently scaled overkill.',
        'Retain delayed offspring requests and captured contact policy until legal placement/capacity, including after summoner removal.',
        'Enable sparse bands0..2Hive and conditional Flooded Drowned placement; preserve player, visuals and expedition structure.'],
    'adaptations': source['adaptations'], 'native': native, 'browser': browser, 'visual': visual, 'remaining': source['remaining']})
status = load('docs/research/isaac-enemy-port-status.json')
for ident in ['22.0.0','22.1.0']:
    r = next(r for r in status['records'] if r['id'] == ident)
    drowned = ident == '22.1.0'
    r['implementation'] = 'in_progress'
    r['runtime'] = list(dict.fromkeys(r['runtime']+runtime))
    r['evidence'].append({'source': BASE+'source-review.json', 'supports': 'Installed shared controller, global population helper, source path forces and unresolved path details, independent death mixture/count, scaled health/overkill, extracted30HzHeadAttack18/Shoot4 and pinned Flooded substitution.'})
    r['contract'].update(
        movement='30Hz ground evader: proximity14, visible25/hidden17, three sticky checks; random wandering otherwise. Retention'+('.76' if drowned else '.8')+'. Source forces adapted to physical canyon pathfinding; exact grid cache/initial impulse/diagonal bias pending.',
        targeting='Player proximity drives fleeing. Live spawning uses all hostile room threats plus reserved births; random threshold4..8 adds20..69retry frames. No owner-specific population cap.',
        attacks='HeadAttack18/Shoot4; cooldown75ticks set on acquisition, advances while evading, check-before-decrement. Range30/sight required; retry3/7. Spits '+('half-health Drowned Charger23.1(35.2HP).' if drowned else 'Attack Fly18.0with contact expiry and.9pursuit retention.'),
        vulnerability=('18x3.2=57.6' if drowned else '20x3.2=64')+'HP; stageHP0, normally vulnerable and harmless body contact. Radius.7is local geometry.',
        phases='Ready evade/wander and coasting18-frame attack. No self-detonation or health phases for these variants.',
        offspring='Death countceil(4/(1+.2*population)), '+('capped by uniform1or2; each child is23.1with halfHP35.2.' if drowned else 'independent Fly13/Attack18/Pooter14draws weighted7:3:1. Death Attack Flies remain persistent.')+' Post-hitHP<=-64suppresses births, converting source-20by3.2. Nonzero nativeNPC+bc6counter semantics pending.',
        completion='Parent counts as one threat. Live Shoot waits at frame4under active-body saturation; retained births retry capacity/placement, keep the room sealed and retain contact policy after parent removal. Existing generation<=4bound/reset/debug cleanup remains.',
        adaptations='; '.join(source['adaptations']), unknowns='; '.join(source['remaining']))
    r['placement'] = [{'kind': 'conditional_replacement' if drowned else 'weighted_specialist', 'bands': [1] if drowned else [0,1,2],
        'approved': True, 'evidence': BASE+'source-review.json',
        'note': '50%Hive replacement only in Flooded band1; actual seed66floor2room1.' if drowned else 'Pursuit weight1/cost3/max1; actual seed9floor0room1, seed11floor2room2 and seed1floor4room3. Placement approval is not complete parity.'}]
    r['unresolved'] = source['remaining']
    r.setdefault('implementation_notes', []).append('Hive checkpoint supersedes earlier generic-controller, owner-specific cap and provisional mixture/timing notes for22.0/22.1only. Both remain in progress with explicit source-path/status/counter and six-gate work outstanding.')
    for gate, path, scope in [
        ('behavior', BASE+'behavior-final.txt', native['tests']),
        ('reachability', BASE+'behavior-final.txt', 'Production seeded room witnesses and Flooded-only50%replacement; all three approved Hive bands. Local weights/cost/cap remain balance policy.'),
        ('visual_linux', BASE+('native-drowned-resident.png' if drowned else 'native-hive.png'), visual['result']),
        ('visual_wasm', BASE+'web/results.json', browser['scope'])]:
        r['validation'][gate].append({'path': path, 'result': 'partial_pass', 'scope': scope})
status['next_work'] = ['USER PRIORITY: regular enemies and required dependencies first; further boss/Hornfel expansion deferred.',
    'Hive22.0/Drowned22.1 now have source-based evasion/spawning, population-sensitive offspring and natural placement. Continue remaining ordinary Mulligan/Hive-family records and dependencies.',
    'Resolve explicit native path/status/counter gaps and full six-gate acceptance; all653records remain tracked and no placeholder counts as complete. Keep Tainted Pooter outside ordinary pools until its dedicated route exists.']
status['priority_override']['current_focus'] = ['Regular enemies and required dependencies', 'Remaining Mulligan/Hive-family records and the rest of the regular roster before further bosses']
status['latest_source_review'] = BASE+'source-review.json'
status['checkpoint'].update(mechanics_fingerprint=fingerprint, report=BASE+'checkpoint.json', native_tests=67,
    partial_implementations=92, direct_pool_ids=44, enabled_pool_ids=46, wasm_final_build_cases=8,
    note='Hive/Drowned source-based evader and population-sensitive retained offspring; sparse natural placement.67native suites covered after one seed-sample correction,8WASM cases pass. Original captures inspected. Source-path/status/counter and complete acceptance remain pending; zero complete ports.')
save('docs/research/isaac-enemy-port-status.json', status)
checked = json.loads(subprocess.check_output(['python3','scripts/isaac-reference/track-enemies.py','--check','--csv'], cwd=ROOT, text=True))
assert checked['reviewed'] == 136 and checked['complete'] == 0 and checked['implementations']['in_progress'] == 92
save(BASE+'checklist-final.json', checked)
save('docs/research/isaac-enemy-port-validation.json', checked)
p = ROOT/'docs/isaac_monsters.md'
text = p.read_text(); marker = 'Current implementation checkpoint:\n'; assert marker in text
text = text.replace(marker, '''Current implementation checkpoint:

The [Hive/Drowned Hive checkpoint](reports/isaac-enemy-port/hive/checkpoint.json)
replaces generic spawning with source-based evasion, Attack18/Shoot4/cooldown75,
room-wide population delay and independent death offspring. Health is 64/57.6;
Drowned children have half health. Reserved births retry placement and keep
their contact policy after the parent disappears. Hive now has sparse pursuit
placement in bands 0–2; Flooded band 1 can replace it with Drowned Hive.

Fingerprint `b6d232227ffffd87`: **163 monster definitions, 13 item definitions,
136 reviewed, 92 in progress, 73 existing unverified, 476 missing, 12 excluded,
zero complete**. **67 native suites are covered** after correcting a rare-event
seed sample; **eight WASM cases pass**. Original Linux/browser views were
inspected. There are **44 directly weighted pool identities, 46 including
conditional I. Blob and Drowned Hive**. Native path/status/counter details and
full acceptance remain pending. Regular enemies remain first; further boss work
stays deferred. See the [readable report](reports/isaac-enemy-port/hive/README.md).

The preceding Tainted Pooter checkpoint:
''', 1)
p.write_text(text)
p = OUT/'README.md'; text = p.read_text()
marker = 'Final validation and immutable hashes are recorded here after the current\nnative regression and browser checks finish.'
assert marker in text
text = text.replace(marker, '''All **67 native suites have passing coverage** in the
[coverage manifest](native-coverage.json). The initial [full run](native.xml)
passed 66/67: the old 128-seed fallback missed a Hopper substitution after the
pool expanded. Keeping the 32-seed broad sweep and all assertions, the expanded
512-seed ceiling passed the [focused rerun](native-floor-retry.xml). Spawn chances
and runtime mechanics were unchanged. The [full retry output](floor-retry-full.txt)
finds the Hopper substitution at seed 140, floor 0, room 2, and verifies 46
enabled identities across 341 floors. The [focused Hive behavior log](behavior-final.txt)
also passes, including placement retry after the parent disappears.

All **eight WASM cases pass** without browser/GL errors in the
[browser report](web/results.json). The initial scripted Drowned death hit left
a tiny positive rounding remainder; the test now uses 58 damage. Its
[numeric explanation](browser-test-correction.json), original test/log/results
are retained. This required no runtime change.

[Native Hive](native-hive.png), [native Drowned resident](native-drowned-resident.png),
[browser Hive](web/hive-live.png), [browser Drowned](web/drowned-live.png) and
[browser Drowned resident](web/natural-drowned.png) were inspected. The later
browser resident framing lets the fleeing body pass behind the HUD, so this
does not close all-angle readability. Displayed FPS is not a benchmark.

The [checkpoint](checkpoint.json) freezes runtime, builds, source and evidence.
All '''+f'{len(history):,}'+''' previously recorded report artifacts remain unchanged.''')
p.write_text(text)
sourcepaths = set(old['source_sha256']) | {'scripts/isaac-reference/analyze-hive.py', BASE+'source-review.json', BASE+'extract-metadata.py', BASE+'wiki-source.json', BASE+'mulligan-wiki.wikitext'}
sourcepaths |= {str(p.relative_to(ROOT)) for folder in ['source','animations'] for p in (OUT/folder).rglob('*') if p.is_file()}
save(BASE+'checkpoint.json', {'status': 'Partial regular Hive/Drowned port; full goal active; regular enemies prioritized.',
    'created_utc': datetime.datetime.now(datetime.timezone.utc).isoformat(), 'mechanics_fingerprint': fingerprint,
    'runtime_definitions': 163, 'item_definitions': 13, 'enemy_bomb_profiles': 5, 'checklist': checked,
    'native': native, 'browser': browser, 'visual': visual, 'remaining': source['remaining'],
    'implementation_review': BASE+'implementation-review.json', 'previous_checkpoint': PREVIOUS,
    'runtime_sha256': {p: sha(p) for p in sorted(set(old['runtime_sha256'])|set(runtime))},
    'build_sha256': {p: sha(p) for p in old['build_sha256']},
    'source_sha256': {p: sha(p) for p in sorted(sourcepaths)},
    'artifacts_sha256': {str(p.relative_to(ROOT)): sha(str(p.relative_to(ROOT))) for p in OUT.rglob('*') if p.is_file() and p.name != 'checkpoint.json'}})
print(json.dumps({'checkpoint': BASE+'checkpoint.json', 'native_pass': 67, 'wasm_pass': 8, 'historical_unchanged': len(history), 'complete': 0}))
