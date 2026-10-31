"""Freeze this partial regular-enemy slice once; preserve all earlier evidence."""
import datetime, hashlib, json, subprocess, xml.etree.ElementTree as ET
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
BASE = 'docs/reports/isaac-enemy-port/hosts/'
OUT = ROOT / BASE
PREVIOUS = 'docs/reports/isaac-enemy-port/maw_family/checkpoint.json'

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
assert len(cases) == 76
assert {c.attrib['name'] for c in cases if not passed(c)} == {'maw_family', 'boom_flies'}
corrections = []
for file, name in [('maw-corrected.xml', 'maw_family'), ('boom-corrected-2.xml', 'boom_flies')]:
    correction = ET.parse(OUT / file).getroot().findall('.//testcase')
    assert len(correction) == 1 and correction[0].attrib['name'] == name and passed(correction[0])
    corrections += correction
passing = sorted({c.attrib['name'] for c in cases + corrections if passed(c)})
assert len(passing) == 76
assert 'PASS Hosts:' in (OUT / 'native-targeted.txt').read_text()
web = load(BASE + 'web-clean/results.json')
assert len(web['checks']) == 10 and not web['errors']
assert all('PASS ' + r['case'] in (OUT / 'browser-clean.txt').read_text() for r in web['checks'])
assert len(load(BASE + 'native-accepted-captures.json')) == 13
visual = load(BASE + 'visual-review.json')
assert len(visual['final_images']) == 28 and all(r['inspected'] for r in visual['final_images'])
fingerprint = (OUT / 'mechanics-final.txt').read_text().split('fingerprint ')[1].split()[0]
assert fingerprint == 'f76820643f7192cc'
assert 'direct_pool_id_count=70' in (OUT / 'pool-audit.txt').read_text()
history = load(BASE + 'historical-integrity.json')['files']
assert len(history) == 6162
for path, digest in history.items():
    assert sha(path) == digest, path
subprocess.run(['python3', 'scripts/isaac-reference/analyze-hosts.py', '--check'], cwd=ROOT, check=True, capture_output=True)

native = dict(passed=76, failed=0, report=BASE + 'native.xml', passing_suites=passing,
    corrected_reports=[BASE + 'maw-corrected.xml', BASE + 'boom-corrected-2.xml'],
    behavior=BASE + 'native-targeted.txt',
    corrections='Full run passed74/76. Maw fixture now uses each expedition actual first band1 floor; Bone Fly retains earlier seed candidates and adds an independently verified seed93/floor3/room3. Both corrected suites pass. First Bone retry was terminated with143 and is retained without claiming a pass. Initial Host fixture used an out-of-range fixed floor and was corrected to use the generated expedition plan.')
browser = dict(cases=10, report=BASE + 'web-clean/results.json', scope=web['scope'], errors=[],
    build=BASE + 'build-wasm-clean.txt', startup_diagnostic=BASE + 'browser-diagnostic.txt')
remaining = [
    'Hard Host27.3 is source-reviewed only: legacy HP/generic AI remain unverified; aimed physical rock shockwave, cover destruction and nearby knockback need implementation. Mushroom300 has a separate controller.',
    'Native status/champion/friendly/control branches, subtype99/Bracelet transformations and grimace interactions remain open.',
    'Poison/booger/spike/crush distinctions, source projectile height/fall/lifetime, native grid and RNG parity remain open.',
    'Native replacement probabilities and exact alternate-stage placement remain open; local pools use documented authored weights/costs.',
    'Full combat readability, balance and controlled Linux/WASM performance acceptance remain open; no complete port is claimed.'
]
adaptations = [
    'Source30Hz, distance x.1, velocity x3, HP x3.2; established local hostile damage10.',
    'Collision-aware3D movement/local path solver, physical combat-plane shots with five-second lifetime, whole-volley capacity retry, stun cancels/closes the cast.',
    'Original procedural skull/stem, unarmored red flesh, walking legs and floating body; no source artwork imported.',
    'Authored ordinary specialist pools: first four from band1, Floast band3, cap1 each; not on the opening floor.'
]
review = dict(scope='Partial normal-hostile Host27.0, Red Host27.1, Mobile Host204, Flesh Mobile Host247 and Floast859; Hard Host27.3 research only.',
    source=BASE + 'source-review.md', adaptations=adaptations, remaining=remaining,
    native=native, browser=browser, visual=visual, complete=False)
save(BASE + 'implementation-review.json', review)
runtime = ['assets/mechanics/hosts.mechanics', 'assets/mechanics/monsters.mechanics', 'src/combat/Hosts.cpp',
    'src/combat/Monsters.cpp', 'src/combat/Simulation.hpp', 'src/combat/Simulation.cpp', 'src/combat/Enemies.cpp',
    'src/content/Mechanics.hpp', 'src/content/Mechanics.cpp', 'src/content/EncounterVariants.cpp',
    'src/render/MonsterVisuals.hpp', 'src/main.cpp', 'tests/host_tests.cpp', 'tests/monster_tests.cpp',
    'tests/maw_family_tests.cpp', 'tests/boom_fly_tests.cpp', 'web/host-test.cjs', 'CMakeLists.txt']
status = load('docs/research/isaac-enemy-port-status.json')
save(BASE + 'status-before.json', status)
ids = ['27.0.0', '27.1.0', '204.0.0', '247.0.0', '859.0.0']
names = ['host', 'red-host', 'mobile-host', 'flesh-mobile-host', 'floast']
for ident, name in zip(ids, names):
    r = next(r for r in status['records'] if r['id'] == ident)
    mobile = ident in ['204.0.0', '247.0.0']
    floating = ident == '859.0.0'
    red = ident in ['27.1.0', '247.0.0']
    r.update(review='reviewed', disposition='ordinary', implementation='in_progress')
    r['runtime'] = list(dict.fromkeys(r['runtime'] + runtime))
    r['evidence'].append(dict(source=BASE + 'source-review.md', supports='Pinned native controllers/helpers/projectile postpass and bindings; six animation/event records, exact source XML/habitats and archived wiki; explicit remaining branches.'))
    r['contract'] = dict(
        movement='Signed diagonal per-axis acceleration.55, retention.9 even during attacks; reflected blocked axis.' if floating else 'Ground pursuit maximum net impulse.8, retention.56; tapers within2world units; attack retention.5; local obstacle-aware path solver.' if mobile else 'Stationary grounded body; zero contact damage.',
        targeting='Strict240source-unit range, line of sight, global/entity seven-frame acquisition gate; live aim at Shoot24.' + (' Additionally1/3 idle roll; cooldown70 counts attack frames then accepted idle rolls.' if mobile else ' Cooldown7 counts idle seven-frame checks, frozen during the cast.'),
        attacks=('Five' if red else 'Three') + ' physical aimed shots at source event24. Native unequal forward/side spread coefficients, common mode postpass and VelocityMulti retained. ' + ('Final center speed25.2 with no inheritance.' if floating else 'Final center speed25.2 with .4 parent velocity.' if mobile else 'Final center speed26.964 with .428 parent velocity.'),
        vulnerability='Always damageable; no closed-skull armor.' if red else 'Damageable only between Open and Close. Burning bypasses armor; direct Flame and explosion do not. Blocked idle damage sums per update, source HP rounded then halved, delay cap10 with seven-frame decay.',
        phases='Ready; closed preparation; exposed attack; closed recovery. Source frames ' + ('10/24/54/63.' if floating else '10/24/53/61.' if mobile else '9/24/55/61.') + ' Animation/cooldown/delay state survives room suspension; death cancels cast.',
        offspring='None for these normal variants; subtype transformations not implemented.',
        completion='Ordinary room threat. Actual death resolves it; whole pending volleys survive capacity pressure until fired or actor death.',
        adaptations='; '.join(adaptations), unknowns='; '.join(remaining[1:]))
    r['placement'] = [dict(kind='weighted_specialist', bands=[3] if floating else [1,2,3], approved=True,
        evidence=BASE + 'source-review.md', note='Source Utero/Corpse habitats.' if floating else 'Source Caves onward. Authored weights/costs and cap1; native replacement probabilities not certified.')]
    r['unresolved'] = remaining[1:]
    for gate, path, scope in [
        ('behavior', 'native-targeted.txt', 'Normal armor/event/delay/burn/direct damage, contact, three/five-shot physical velocities, movement, capacity, lifecycle and immutable config; not all native branches.'),
        ('reachability', 'web-clean/results.json', 'Five concrete production resident witnesses, acquired from real seeded floor pools.'),
        ('visual_linux', 'native-grounded-' + name + '.png', visual['scope']),
        ('visual_wasm', 'web-clean/' + name + '.png', visual['scope'])]:
        r['validation'][gate].append(dict(path=BASE + path, result='partial_pass', scope=scope))
hard = next(r for r in status['records'] if r['id'] == '27.3.0')
assert hard['implementation'] == 'existing_unverified'
hard.update(review='reviewed', disposition='ordinary')
hard['evidence'].append(dict(source=BASE + 'source-review.md', supports='Native shared Host controller includes variant3 slam/aimed rock shockwave and close-range knockback; animation metadata open10/close54/end71. Source XML15HP. Research only; no faithful implementation or validation claimed.'))
hard['contract'] = dict(movement='Stationary Host variant.', targeting='Shared Host acquisition; aimed shockwave on slam.',
    attacks='Physical rock shockwave rather than a regular projectile spread; destroys breakable obstacles and knocks back nearby targets. Implementation pending.',
    vulnerability='Source15HP; armored outside open window, shared Host damage-delay behavior. Legacy local HP remains unverified.',
    phases='Source animation open10, slam/close54, end71; source-reviewed only.', offspring='No required ordinary offspring identified.',
    completion='Expected ordinary room threat; local faithful death/completion behavior not certified.',
    adaptations='No new runtime adaptation approved in this slice; previous generic definition retained.', unknowns=remaining[0])
hard['unresolved'] = [remaining[0], *remaining[1:]]
status['next_work'] = ['USER PRIORITY: regular enemies and required offspring before further bosses.',
    'Implement Hard Host physical shockwave/terrain interaction and review Mushroom; continue ordinary roster and six-gate acceptance gaps.', *remaining]
status['latest_source_review'] = BASE + 'source-review.md'
status['checkpoint'].update(mechanics_fingerprint=fingerprint, report=BASE + 'checkpoint.json', native_tests=76,
    runtime_definitions=176, reviewed_records=162, partial_implementations=119, direct_pool_ids=70, enabled_pool_ids=74,
    wasm_final_build_cases=10, note='Five partial source-derived regular Host variants; Hard Host research only.76native suites/10productionWASM cases pass;zero complete ports;full six-gate acceptance remains open.')
save('docs/research/isaac-enemy-port-status.json', status)
checked = json.loads(subprocess.check_output(['python3', 'scripts/isaac-reference/track-enemies.py', '--check', '--csv'], cwd=ROOT, text=True))
assert checked['reviewed'] == 162 and checked['complete'] == 0
assert checked['implementations'] == dict(in_progress=119, existing_unverified=59, missing=463, excluded=12)
save(BASE + 'checklist-final.json', checked)
save('docs/research/isaac-enemy-port-validation.json', checked)
p = ROOT / 'docs/isaac_monsters.md'
text = p.read_text()
marker = 'Current implementation checkpoint:\n'
assert marker in text
text = text.replace(marker, marker + '''
The [Host-family checkpoint](reports/isaac-enemy-port/hosts/checkpoint.json)
adds source-derived normal-state Host, Red Host, Mobile Host, Flesh Mobile Host
and Floast controllers. Hard Host is researched but retains unverified legacy
behavior. Fingerprint `f76820643f7192cc`: **176 definitions, 162 reviewed,
119 in progress, 59 existing-unverified, 463 missing, 12 excluded; zero complete
ports**. There are 70 direct ordinary pool identities, 74 including replacements.
**76 native suites and 10 production WASM cases pass.** The
[report](reports/isaac-enemy-port/hosts/README.md) records sources, adaptations,
test corrections and 28 inspected Original-style images. Regular enemies and
required offspring remain the priority; balance/performance and full parity
acceptance are still open.

''', 1)
p.write_text(text)
old = load(PREVIOUS)
sources = set(old['source_sha256']) | {'scripts/isaac-reference/analyze-hosts.py', BASE + 'source-review.md',
    BASE + 'records.json', BASE + 'reviewed-records.json', BASE + 'extract-metadata.py', BASE + 'host-wiki-source.json',
    BASE + 'DamageFlag.md', BASE + 'documentation-source.json'}
sources |= {str(p.relative_to(ROOT)) for folder in ['source', 'animations'] for p in (OUT / folder).rglob('*') if p.is_file()}
builds = set(old['build_sha256']) | {'build/deathward_host_tests', 'build/deathward_maw_family_tests', 'build/deathward_boom_fly_tests', 'build/deathward_monster_tests'}
save(BASE + 'checkpoint.json', dict(status='Partial regular Host-family port; full goal active.',
    created_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(), mechanics_fingerprint=fingerprint,
    runtime_definitions=176, item_definitions=13, enemy_bomb_profiles=6, checklist=checked,
    native=native, browser=browser, visual=visual, remaining=remaining, previous_checkpoint=PREVIOUS,
    implementation_review=BASE + 'implementation-review.json', historical_artifacts_preserved=len(history),
    runtime_sha256={p: sha(p) for p in sorted(set(old['runtime_sha256']) | set(runtime))},
    build_sha256={p: sha(p) for p in sorted(builds)}, source_sha256={p: sha(p) for p in sorted(sources)},
    artifacts_sha256={str(p.relative_to(ROOT)): sha(str(p.relative_to(ROOT))) for p in OUT.rglob('*') if p.is_file() and p.name != 'checkpoint.json'}))
print(json.dumps(dict(checkpoint=BASE + 'checkpoint.json', native_pass=76, wasm_pass=10, historical_unchanged=len(history), complete=0)))
