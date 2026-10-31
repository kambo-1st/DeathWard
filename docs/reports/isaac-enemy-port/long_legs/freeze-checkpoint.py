"""Freeze this regular-enemy checkpoint once, retaining earlier evidence."""
import datetime
import hashlib
import json
import subprocess
import xml.etree.ElementTree as ET
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
BASE = 'docs/reports/isaac-enemy-port/long_legs/'
OUT = ROOT / BASE
PREVIOUS = 'docs/reports/isaac-enemy-port/spider_variants/checkpoint.json'

def load(p): return json.loads((ROOT / p).read_text())
def save(p, value): (ROOT / p).write_text(json.dumps(value, indent=2, ensure_ascii=False) + '\n')
def sha(p):
    h = hashlib.sha256()
    with (ROOT / p).open('rb') as stream:
        for chunk in iter(lambda: stream.read(4 * 1024 * 1024), b''): h.update(chunk)
    return h.hexdigest()
def passed(case): return all(case.find(tag) is None for tag in ['failure','skipped','error'])

assert not (OUT/'checkpoint.json').exists(), 'Checkpoint already frozen'
initial = ET.parse(OUT/'native.xml').getroot().findall('.//testcase')
corrected_reports=['hive-corrected.xml','mulligan-corrected.xml']
corrected=[c for report in corrected_reports for c in ET.parse(OUT/report).getroot().findall('.//testcase')]
assert len(initial) == 73
assert {c.attrib['name'] for c in initial if not passed(c)} == {'hive_evaders','mulligan_family'}
assert len(corrected) == 2 and all(passed(c) for c in corrected)
assert {c.attrib['name'] for c in corrected} == {'hive_evaders','mulligan_family'}
passing = sorted({c.attrib['name'] for c in initial+corrected if passed(c)})
assert len(passing) == 73
assert 'PASS Long Legs and Sack' in (OUT/'behavior-second.txt').read_text()
(OUT/'behavior-final.txt').write_bytes((OUT/'behavior-second.txt').read_bytes())
native = dict(covered_suites=73, passed=73, failed=0, passing_suites=passing,
    initial_full_run=dict(report=BASE+'native.xml', passed=71, failed=['hive_evaders','mulligan_family']),
    corrected_runs=[BASE+p for p in corrected_reports],
    scope='73 unique native suites pass across the full run and two corrected reachability fixtures. New specialists changed seeded selections; the unchanged first100seeds no longer contained Drowned Hive. Independent production search found seed245/floor1/room7. Mulligan/Mulligoon now use seeds7and21. Tests retain original samples plus actual new witnesses. Runtime/build content unchanged after the full build; only the two fixtures were rebuilt.',
    behavior=BASE+'behavior-final.txt',
    behavior_scope='Long Legs45frame attacks, Lay26/Shoot22, exact8way/4diagonal volleys and physical arc fields, retained atomic volleys, Baby twins/opposite impulses/global population gating, Small Baby Sack/white creep, source Sack current/maxHP and regenerative recurrence/damage reset/noncontact, thrown Spider landing/controller reset, movement around cover/retreat, strict immutable config and four actual seeded parent witnesses.')
save(BASE+'native-results.json',native)
web = load(BASE+'web/results.json')
assert len(web['checks']) == 10 and not web['errors']
assert all('PASS '+case['case'] in (OUT/'browser.txt').read_text() for case in web['checks'])
browser = dict(cases=10, report=BASE+'web/results.json', errors=[], scope=web['scope'])
fingerprint = (OUT/'mechanics.txt').read_text().split('fingerprint ')[1].split()[0]
assert fingerprint == '64bd7ece6bf04647'
assert load(BASE+'pool-audit.json')['counts'] == {'direct':57,'enabled':61}
subprocess.run(['python3','scripts/isaac-reference/analyze-long-legs.py','--check'],cwd=ROOT,check=True,capture_output=True)
history = load(BASE+'historical-integrity.json')['files']
assert len(history) == 5816
for p,h in history.items(): assert sha(p) == h,p
old = load(PREVIOUS)
source = load(BASE+'source-review.json')
visual = load(BASE+'visual-review.json')
runtime = ['assets/mechanics/long_legs.mechanics','assets/mechanics/monsters.mechanics',
    'src/combat/LongLegs.cpp','src/combat/Monsters.cpp','src/combat/Simulation.hpp',
    'src/combat/Spiders.cpp','src/combat/SpiderVariants.cpp','src/combat/Swimmers.cpp',
    'src/content/Mechanics.hpp','src/content/Mechanics.cpp','src/content/EncounterVariants.cpp',
    'src/render/MonsterVisuals.hpp','src/main.cpp','tests/long_legs_tests.cpp',
    'tests/resident_enemies_tests.cpp','tests/evader_tests.cpp','tests/mulligan_tests.cpp','web/long-legs-test.cjs','CMakeLists.txt','README.md']
save(BASE+'implementation-review.json',dict(scope=source['scope'],mechanics_fingerprint=fingerprint,
    native=native,browser=browser,visual=visual,adaptations=source['adaptations'],remaining=source['remaining'],
    complete=False,historical_artifacts_preserved=len(history)))

status = load('docs/research/isaac-enemy-port-status.json')
save(BASE+'status-before.json',status)
records = load(BASE+'records.json')
ids = ['206.0.0','206.1.0','207.0.0','207.1.0','30.2.0']
children = {'206.0.0':['85.0.0','814.0.0'],'206.1.0':['30.2.0'],
    '207.0.0':[],'207.1.0':[],'30.2.0':['85.0.0','814.0.0']}
bands = {'206.0.0':[0,1,2],'206.1.0':[0,1],'207.0.0':[0,1,3],'207.1.0':[0,1,2,3]}
images = {'206.0.0':'native-natural-baby.png','206.1.0':'native-natural-small-baby.png',
    '207.0.0':'native-natural-crazy.png','207.1.0':'native-natural-small-crazy.png','30.2.0':'native-sack.png'}
for ident in ids:
    r = next(r for r in status['records'] if r['id']==ident)
    sack = ident=='30.2.0';baby=ident.startswith('206');small=ident.split('.')[1]=='1'
    r.update(review='reviewed',disposition='ordinary',implementation='in_progress')
    r['runtime'] = list(dict.fromkeys(r['runtime']+runtime))
    r['evidence'].append(dict(source=BASE+'source-review.json',supports='Installed1.7.9b dispatch/controllers, evasion/path/shot helpers, numeric fields and initialization; extracted animation durations/events; exact XML/habitats and pinned attributed wiki. Corrections, local adaptations and remaining uncertainties explicit.'))
    r['contract'] = dict(
        movement=('Stationary; no ordinary movement. Health-based visual growth.' if sack else
            'EvadeTarget-derived retreat/wander, source30Hz force1.079 and ready friction assignment.8; local physical pathfinding.' if baby else
            'FindGridPath-derived pursuit, source30Hz force.65 and ready friction assignment.8; both variants share movement force. Small animation stride is slower.'),
        targeting=('At fullHP,1/50attack check, extra1/4beyond230source distance. Shoot only when roomcount<8 and random(count)==0; otherwise shake. Near player uses midpoint/scatter aim; far uses local scatter.' if sack else
            'Sticky proximity evasion:14staggered frames, visible250/hidden170source range, countdown3. Laying requires roomcount<6. Chance1/200small or1/100normal plus doubled chance when not fleeing.' if baby else
            'Current player pursuit; direct clear route approximates native pathfinder CheckLine flag for1/50attack check. Volleys use fixed world axes/diagonals rather than aiming at player.'),
        attacks=('Shoot24frames/Shoot12 throws Spider; Shake26has no child. No contact damage.' if sack else
            'LayEgg45frames/Lay26. Small lays Sack and slowing white creep; normal lays Spider, with1/20opposite-moving twin. Contact10.' if baby else
            'Attack45frames/Shoot22: eight directions normal, four diagonals small. Shared source speed8..10, falling modifiers10/-10/.5 translated to local arcs. Contact10.'),
        vulnerability=('Source currentHP7/max20, scaled3.2. Regeneration adds prior growth*1.2; growth=(growth+.02)*.64. Damage resets growth and interrupts attack below fullHP. Lethal damage prevents regeneration.' if sack else
            'Source baseHP12small/16normal +4stage, scaled3.2: opening51.2/64. Normal gunfire/bombs/status integration; collider source13 maps to.4.'),
        phases=('Growth, fullHP ready, Shake or Shoot, airborne child, recovery. Normal-mode initialization only; hard/champion/status cases remain open.' if sack else
            'Initialize, ready movement,45frame attack with.5momentum retention, single event at26Baby/22Crazy, recovery. Payload retained at event if capacity unavailable.'),
        offspring=('Spider85.0.0; wet-band replacement814.0.0. Source thrown state6has height-10/up-8/gravity+.7, horizontal delta*.04, entity-collision-zero during flight; legal landing switches to correct ground controller.' if sack else
            'Small produces30.2.0Sack with partly grown currentHP, unchanged maxHP, and white slowing creep. Overlapping Sacks replace without death rewards.' if baby and small else
            'Normal produces85.0.0Spider or wet814.0.0Strider, opposite randomunit impulses for twins. Children survive parent death.' if baby else
            'None for these exact Crazy variants.'),
        completion='Living threats and retained pending children keep room sealed. Final threat death permits completion. Parent death does not erase independently living children.',
        source_numbers={k:records[ident]['xml'].get(k) for k in ['baseHP','stageHP','collisionDamage','collisionRadius','friction']},
        adaptations='; '.join(source['adaptations']),unknowns='; '.join(source['remaining']))
    r['children'] = list(dict.fromkeys(r['children']+children[ident]))
    if sack:r['parents'] = list(dict.fromkeys(r['parents']+['206.1.0']))
    r['placement'] = [dict(kind='required_offspring' if sack else 'weighted_specialist',
        bands=[0,1] if sack else bands[ident],approved=True,evidence=BASE+'source-review.json',
        note='Required Small Baby offspring; no direct ordinary pool slot.' if sack else
            'Sparse specialist max1, weight1; source habitat bands mapped to expedition progression. Real opening-floor witnesses recorded.')]
    r['unresolved']=source['remaining']
    r.setdefault('implementation_notes',[]).append('Regular-enemy priority: distinct source-derived normal hostile controller, external values, valid children and seeded parents. Partial acceptance; no completed-port claim.')
    for gate,path,scope in [
        ('behavior',BASE+'behavior-final.txt',native['behavior_scope']),
        ('reachability',BASE+'web/results.json','Actual production seeded parent rooms; Small Baby lays Sack, Sack lays Spider. Wet substitutions additionally verified by native fixture.'),
        ('visual_linux',BASE+images[ident],visual['result']),
        ('visual_wasm',BASE+'web/results.json',browser['scope'])]:
        r['validation'][gate].append(dict(path=path,result='partial_pass',scope=scope))
for parent,kids in children.items():
    for child in kids:
        r=next(r for r in status['records'] if r['id']==child)
        r['parents']=list(dict.fromkeys(r['parents']+[parent]))
status['next_work']=[
    'USER PRIORITY: regular enemies and required offspring before additional bosses/Hornfel work.',
    'Four Baby/Crazy Long Legs variants and Sack now have source-based normal hostile controllers and partial Linux/WASM validation. Continue the regular roster and close ordinary-enemy acceptance gaps.',
    'Native special statuses/items, exact grid/RNG parity, detailed white-creep values and full readability/balance/performance acceptance remain open. Registry presence does not count as completion.']
status['priority_override']['current_focus']=['Regular enemies and required offspring','Continue regular roster and ordinary-enemy acceptance before more bosses']
status['latest_source_review']=BASE+'source-review.json'
status['checkpoint'].update(mechanics_fingerprint=fingerprint,report=BASE+'checkpoint.json',native_tests=73,
    runtime_definitions=173,reviewed_records=147,partial_implementations=105,direct_pool_ids=57,enabled_pool_ids=61,
    wasm_final_build_cases=10,
    note='Long Legs/Sack regular-enemy slice: four parent variants, source event attacks, Sack growth and thrown Spider/Strider integration.73unique native suites pass across full run and two expanded witness fixtures;10WASM cases pass;12usableOriginal captures inspected. Full six-gate acceptance remains open;zero complete ports.')
save('docs/research/isaac-enemy-port-status.json',status)
checked=json.loads(subprocess.check_output(['python3','scripts/isaac-reference/track-enemies.py','--check','--csv'],cwd=ROOT,text=True))
assert checked['reviewed']==147 and checked['complete']==0 and checked['implementations']['in_progress']==105
assert checked['implementations']['missing']==466 and checked['implementations']['existing_unverified']==70
save(BASE+'checklist-final.json',checked)
save('docs/research/isaac-enemy-port-validation.json',checked)
p=ROOT/'docs/isaac_monsters.md';text=p.read_text();marker='Current implementation checkpoint:\n';assert marker in text
text=text.replace(marker,marker+'''
The [Long Legs and Sack checkpoint](reports/isaac-enemy-port/long_legs/checkpoint.json)
adds source-based controllers for Baby/Small Baby Long Legs 206.0/206.1,
Crazy/Small Crazy Long Legs 207.0/207.1, and Sack 30.2. Babies flee and lay
independent children; Crazy variants chase and fire eight-way/diagonal volleys.
Sacks regenerate from 7/20 source HP and throw spiders. The four parents enter
sparse seeded stage pools; Small Baby supplies Sacks. Values are external.
Fingerprint `64bd7ece6bf04647`: **173 definitions, 147 reviewed, 105 in progress,
70 existing-unverified, 466 missing, 12 excluded; zero complete ports**.
The direct ordinary pool has 57 identities, 61 including replacements.
**73 unique native suites pass** across the full run and two seeded witness
corrections; **ten WASM cases pass**. Twelve usable Original-style captures were
inspected. Native special cases, broader readability, balance and controlled
performance acceptance remain open. Regular enemies remain the priority.

''',1);p.write_text(text)
sourcepaths=set(old['source_sha256'])|{'scripts/isaac-reference/analyze-long-legs.py',BASE+'source-review.json',BASE+'extract-metadata.py',BASE+'records.json',BASE+'wiki-source.json'}
sourcepaths|={str(p.relative_to(ROOT)) for folder in ['source','animations'] for p in (OUT/folder).rglob('*') if p.is_file()}
buildpaths=set(old['build_sha256'])|{'build/deathward_long_legs_tests','build/deathward_evader_tests','build/deathward_mulligan_tests'}
save(BASE+'checkpoint.json',dict(status='Partial regular Long Legs/Sack port; full goal active; regular enemies prioritized.',
    created_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),mechanics_fingerprint=fingerprint,
    runtime_definitions=173,item_definitions=13,enemy_bomb_profiles=6,checklist=checked,native=native,browser=browser,
    visual=visual,remaining=source['remaining'],implementation_review=BASE+'implementation-review.json',previous_checkpoint=PREVIOUS,
    runtime_sha256={p:sha(p) for p in sorted(set(old['runtime_sha256'])|set(runtime))},
    build_sha256={p:sha(p) for p in sorted(buildpaths)},source_sha256={p:sha(p) for p in sorted(sourcepaths)},
    artifacts_sha256={str(p.relative_to(ROOT)):sha(str(p.relative_to(ROOT))) for p in OUT.rglob('*') if p.is_file() and p.name!='checkpoint.json'}))
print(json.dumps(dict(checkpoint=BASE+'checkpoint.json',native_unique_pass=73,wasm_pass=10,historical_unchanged=len(history),complete=0)))
