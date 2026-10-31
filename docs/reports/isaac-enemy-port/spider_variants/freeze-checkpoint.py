"""Freeze this validated regular-enemy slice once, never rewriting older evidence."""
import datetime
import hashlib
import json
import subprocess
import xml.etree.ElementTree as ET
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
BASE = 'docs/reports/isaac-enemy-port/spider_variants/'
OUT = ROOT / BASE
PREVIOUS = 'docs/reports/isaac-enemy-port/spiders/checkpoint.json'

def load(p): return json.loads((ROOT / p).read_text())
def save(p, value): (ROOT / p).write_text(json.dumps(value, indent=2, ensure_ascii=False) + '\n')
def sha(p):
    h = hashlib.sha256()
    with (ROOT / p).open('rb') as stream:
        for chunk in iter(lambda: stream.read(4 * 1024 * 1024), b''): h.update(chunk)
    return h.hexdigest()

assert not (OUT / 'checkpoint.json').exists(), 'Checkpoint already frozen'
initial = ET.parse(OUT / 'native.xml').getroot().findall('.//testcase')
corrected = ET.parse(OUT / 'native-corrected.xml').getroot().findall('.//testcase')
def passed(case): return case.find('failure') is None and case.find('skipped') is None and case.find('error') is None
assert len(initial) == 72 and sum(passed(c) for c in initial) == 69
assert len(corrected) == 3 and all(passed(c) for c in corrected)
assert {c.attrib['name'] for c in initial if not passed(c)} == {c.attrib['name'] for c in corrected}
passing = sorted({c.attrib['name'] for c in initial + corrected if passed(c)})
assert len(passing) == 72
assert 'PASS Strider and Swarm Spider' in (OUT / 'behavior-third.txt').read_text()
(OUT / 'behavior-final.txt').write_bytes((OUT / 'behavior-third.txt').read_bytes())
native = dict(covered_suites=72, passed=72, failed=0,
    initial_full_run=dict(report=BASE+'native.xml', passed=69, failed=[c.attrib['name'] for c in initial if not passed(c)]),
    corrected_runs=[BASE+'native-corrected.xml'], passing_suites=passing,
    scope='72 unique native suites pass across the full run and three focused reruns. Corrections cover legal replacement phases, source-equal Spider/Swarm colliders and flying offspring collision masks. Runtime simulation code did not change after the full run; only a debug cover placement and Strider leg rendering changed. Original failures are preserved.',
    behavior=BASE+'behavior-final.txt',
    behavior_scope='Strider Row6/20frames, forces, current-target tracking, glide, solid/deep-water collision; all Swarm hop events/launch ranges/weights/commitment/friction, pit collision and peer overlap; fireplace-specific immunity and ordinary Flame/Burning/contact/stun; wet direct and retained Big Spider death children; strict immutable config; real seeded placement.')
save(BASE+'native-results.json', native)
web = load(BASE+'web-final/results.json')
assert len(web['checks']) == 8 and not web['errors']
assert all('PASS '+case['case'] in (OUT/'browser-final.txt').read_text() for case in web['checks'])
fingerprint = (OUT/'mechanics.txt').read_text().split('fingerprint ')[1].split()[0]
assert fingerprint == '834662978ecb9391'
assert load(BASE+'pool-audit.json')['counts'] == {'direct':53, 'enabled':57}
subprocess.run(['python3','scripts/isaac-reference/analyze-spider-variants.py','--check'], cwd=ROOT, check=True, capture_output=True)
history = load(BASE+'historical-integrity.json')['files']
assert len(history) == 5721
for p, h in history.items(): assert sha(p) == h, p
old = load(PREVIOUS)
source = load(BASE+'source-review.json')
visual = load(BASE+'visual-review.json')
runtime = ['assets/mechanics/spider_variants.mechanics','assets/mechanics/monsters.mechanics',
    'src/combat/SpiderVariants.cpp','src/combat/Monsters.cpp','src/combat/Simulation.hpp',
    'src/combat/MonsterMovement.cpp','src/combat/FireReactions.cpp','src/combat/EnvironmentActors.cpp',
    'src/content/Mechanics.hpp','src/content/Mechanics.cpp','src/content/EncounterVariants.cpp',
    'src/render/MonsterVisuals.hpp','src/main.cpp','tests/spider_variant_tests.cpp',
    'tests/resident_enemies_tests.cpp','tests/pacing_tests.cpp','tests/floor_progression_tests.cpp',
    'tests/monster_tests.cpp','web/spider-variant-test.cjs','CMakeLists.txt','README.md']
browser = dict(cases=8, report=BASE+'web-final/results.json', errors=[], scope=web['scope'])
save(BASE+'implementation-review.json', dict(scope=source['scope'], mechanics_fingerprint=fingerprint,
    native=native, browser=browser, visual=visual, adaptations=source['adaptations'], remaining=source['remaining'],
    complete=False, historical_artifacts_preserved=len(history)))

status = load('docs/research/isaac-enemy-port-status.json')
save(BASE+'status-before.json', status)
records = load(BASE+'records.json')
for ident in ['814.0.0','884.0.0']:
    r = next(r for r in status['records'] if r['id'] == ident)
    strider = ident == '814.0.0'
    r.update(review='reviewed', disposition='ordinary', implementation='in_progress')
    r['runtime'] = list(dict.fromkeys(r['runtime'] + runtime))
    r['evidence'].append(dict(source=BASE+'source-review.json', supports='Installed dispatch and distinct controllers, Strider facing helper, checked constants, source XML/habitats and animation event metadata; pinned Spider revision268921. Adaptations, failed fixtures and unfinished branches are explicit.'))
    r['contract'] = dict(
        movement=('30Hz ready-check1/4, chase1/2 if LOS, otherwise wander1/3. Walk20frames, Row6 adds source6..9 impulse, retention.95. GridNOPITS crosses deep water but blocks solid scenery.' if strider else
            '30Hz short/medium/long hop controller. Jump/Land events2/8,3/9,4/14 in10/12/18frame animations. Launch5..6,8..10,10..13 source units, spread45/20/10degrees. Ground retention.7; no airborne damping; ground grid collision throughout.'),
        targeting=('Chase direction follows current player every update; wander keeps its sampled direction. Facing follows20%wrapped angular error; impulse uses actual current direction.' if strider else
            'Commit launch before animation. Near<100 always turn sideways/back; otherwise turn chance1/4 or1/20 beyond200. Hop weights5/3/0 near,2/3/2 middle,2/3/9 far. No midair homing.'),
        attacks='Contact damage10 before existing1.25multiplier; no projectile attack.',
        vulnerability=('SourceHP6.5+stage0 ->20.8local. Normal gunfire/flame damage and physical enemy-body separation.' if strider else
            'SourceHP4.5+.2stage, scaled3.2;15.04local at opening stage. Player-objects collision excludes peer-body separation and fireplace contact. Player Flame/Burning, gunfire and bombs remain effective.')+' Source radius13 maps to collider.4.',
        phases=('Initialize ready, select stroke, Row impulse, animation completion, glide throughout. Source thrown state6 omitted.' if strider else
            'Initialize ready, select/commit hop, Jump/airborne/Land,1/4early finish after Land or animation end. Jump no-physics-knockback flag is not mistaken for flight. Full knockback parity remains open.'),
        offspring='None for this exact installed tuple. '+('Receives all85.0.0births in wet band1, including retained Big Spider death children, preserving health/impulse/capacity.' if strider else
            'Existing Eggy29.2death produces884.0.0children. Nonzero subtype group expansion is outside this installed0tuple slice.'),
        completion='Living threats and retained pending births keep rooms sealed; defeating the remaining threats permits completion.',
        source_numbers={k:records[ident]['xml'].get(k) for k in ['baseHP','stageHP','collisionDamage','collisionRadius','friction']},
        adaptations='; '.join(source['adaptations']), unknowns='; '.join(source['remaining']))
    r['parents'] = list(dict.fromkeys(r['parents'] + (['94.0.0'] if strider else ['29.2.0'])))
    r['placement'] = [dict(kind='all_birth_replacement' if strider else 'weighted_basic',
        bands=[1] if strider else [0,1,2], approved=True, evidence=BASE+'source-review.json',
        note='Wet band1Spider85replacement on encounter plans and direct/queued children.' if strider else
            'Pursuit groups of4, weight1, cost2, max8. Early/middle source habitats mapped to local bands.')]
    r['unresolved'] = source['remaining']
    r.setdefault('implementation_notes',[]).append('Regular-enemy priority: source-derived normal hostile controller, external config, source-aware collision and real seeded residents. Still in progress; registry presence and partial validation are not six-gate completion.')
    for gate, path, scope in [
        ('behavior',BASE+'behavior-final.txt',native['behavior_scope']),
        ('reachability',BASE+'behavior-final.txt','Production Strider seed2/floor2/room4 and Swarm seed0/floor0/room2; zero-based.'),
        ('visual_linux',BASE+('native-strider-final.png' if strider else 'native-swarm-group-final.png'),visual['result']),
        ('visual_wasm',BASE+'web-final/results.json',browser['scope'])]:
        r['validation'][gate].append(dict(path=path,result='partial_pass',scope=scope))
for parent, child in [('94.0.0','814.0.0'),('29.2.0','884.0.0')]:
    r = next(r for r in status['records'] if r['id'] == parent)
    r['children'] = list(dict.fromkeys(r['children'] + [child]))
status['next_work'] = [
    'USER PRIORITY: regular enemies and required offspring first; additional boss/Hornfel work deferred.',
    'Strider814 and SwarmSpider884 now have distinct source-based normal hostile controllers, valid seeded placement, wet birth replacement and source-aware collision. Continue regular roster and ordinary-enemy acceptance gaps.',
    'Remaining regular spider-family variants and spawners need separate controller review; do not infer behavior from common art. Native status/item/thrown branches and full six-gate acceptance remain open.']
status['priority_override']['current_focus'] = ['Regular enemies and their required offspring','Continue regular roster and close ordinary-enemy acceptance gaps before more boss work']
status['latest_source_review'] = BASE+'source-review.json'
status['checkpoint'].update(mechanics_fingerprint=fingerprint, report=BASE+'checkpoint.json', native_tests=72,
    runtime_definitions=169, reviewed_records=142, partial_implementations=100, direct_pool_ids=53, enabled_pool_ids=57,
    wasm_final_build_cases=8,
    note='Strider/Swarm regular-enemy slice: source-based rowing and weighted hops, wet all-birth replacement, collision and fireplace contact fix.72unique native suites pass across full run and three fixture-correction reruns;8WASM cases pass;Original captures inspected. Native special branches and full six-gate acceptance remain open;zero complete ports.')
save('docs/research/isaac-enemy-port-status.json',status)
checked = json.loads(subprocess.check_output(['python3','scripts/isaac-reference/track-enemies.py','--check','--csv'],cwd=ROOT,text=True))
assert checked['reviewed']==142 and checked['complete']==0 and checked['implementations']['in_progress']==100
assert checked['implementations']['missing']==470 and checked['implementations']['existing_unverified']==71
save(BASE+'checklist-final.json',checked)
save('docs/research/isaac-enemy-port-validation.json',checked)
p=ROOT/'docs/isaac_monsters.md'
text=p.read_text();marker='Current implementation checkpoint:\n';assert marker in text
text=text.replace(marker,marker+'''
The [Strider and Swarm Spider checkpoint](reports/isaac-enemy-port/spider_variants/checkpoint.json)
adds distinct source-based regular-enemy controllers for 814.0.0 and 884.0.0.
Strider rows over deep water and replaces Spider births on wet band-1 floors,
including Big Spider children. Swarm uses three distance-weighted hop patterns,
source-equal collision radius and fireplace-specific contact immunity. Both
appear in actual seeded rooms. A real fireplace contact-delay bug was also fixed.
Fingerprint `834662978ecb9391`: **169 definitions, 142 reviewed, 100 in progress,
71 existing-unverified, 470 missing, 12 excluded; zero complete ports**.
The direct pool has 53 identities, 57 including conditional replacements.
**72 unique native suites pass** across the full run and three fixture-correction
reruns; **eight final-build WASM cases pass**. Original captures were inspected.
Native special branches, broader readability, balance and controlled performance
acceptance remain open. Regular enemies and offspring remain the priority.

''',1);p.write_text(text)

sourcepaths=set(old['source_sha256'])|{'scripts/isaac-reference/analyze-spider-variants.py',BASE+'source-review.json',BASE+'extract-metadata.py',BASE+'records.json',BASE+'wiki-source.json'}
sourcepaths|={str(p.relative_to(ROOT)) for folder in ['source','animations'] for p in (OUT/folder).rglob('*') if p.is_file()}
buildpaths=set(old['build_sha256'])|{'build/deathward_spider_variant_tests','build/deathward_pacing_tests','build/deathward_floor_progression_tests','build/deathward_monster_tests'}
save(BASE+'checkpoint.json',dict(status='Partial regular Strider/Swarm Spider port; full goal active; regular enemies prioritized.',
    created_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(), mechanics_fingerprint=fingerprint,
    runtime_definitions=169, item_definitions=13, enemy_bomb_profiles=6, checklist=checked, native=native, browser=browser,
    visual=visual, remaining=source['remaining'],implementation_review=BASE+'implementation-review.json',previous_checkpoint=PREVIOUS,
    runtime_sha256={p:sha(p) for p in sorted(set(old['runtime_sha256'])|set(runtime))},
    build_sha256={p:sha(p) for p in sorted(buildpaths)},source_sha256={p:sha(p) for p in sorted(sourcepaths)},
    artifacts_sha256={str(p.relative_to(ROOT)):sha(str(p.relative_to(ROOT))) for p in OUT.rglob('*') if p.is_file() and p.name!='checkpoint.json'}))
print(json.dumps(dict(checkpoint=BASE+'checkpoint.json',native_unique_pass=72,wasm_pass=8,historical_unchanged=len(history),complete=0)))
