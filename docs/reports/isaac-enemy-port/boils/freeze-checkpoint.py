"""Freeze this regular-enemy checkpoint once; earlier evidence stays immutable."""
import datetime
import hashlib
import json
import subprocess
import xml.etree.ElementTree as ET
from pathlib import Path
ROOT=Path(__file__).resolve().parents[4]
BASE='docs/reports/isaac-enemy-port/boils/'
OUT=ROOT/BASE
PREVIOUS='docs/reports/isaac-enemy-port/long_legs/checkpoint.json'
def load(p): return json.loads((ROOT/p).read_text())
def save(p,v): (ROOT/p).write_text(json.dumps(v,indent=2,ensure_ascii=False)+'\n')
def sha(p):
    h=hashlib.sha256()
    with (ROOT/p).open('rb') as stream:
        for chunk in iter(lambda:stream.read(4*1024*1024),b''): h.update(chunk)
    return h.hexdigest()
def passed(c): return all(c.find(tag) is None for tag in ['failure','skipped','error'])
assert not (OUT/'checkpoint.json').exists(), 'Checkpoint already frozen'
initial=ET.parse(OUT/'native.xml').getroot().findall('.//testcase')
corrected_paths=sorted(OUT.glob('*-corrected.xml'))
corrected=[c for path in corrected_paths for c in ET.parse(path).getroot().findall('.//testcase')]
assert len(initial)==74 and all(passed(c) for c in corrected)
failed={c.attrib['name'] for c in initial if not passed(c)}
assert failed=={c.attrib['name'] for c in corrected}, 'Every original failure needs a recorded, passing correction'
passing=sorted({c.attrib['name'] for c in initial+corrected if passed(c)})
assert len(passing)==74
assert 'PASS Boil family' in (OUT/'behavior-second.txt').read_text()
(OUT/'behavior-final.txt').write_bytes((OUT/'behavior-second.txt').read_bytes())
native=dict(covered_suites=74,passed=74,failed=0,passing_suites=passing,
    initial_full_run=dict(report=BASE+'native.xml',passed=74-len(failed),failed=sorted(failed)),
    corrected_runs=[str(p.relative_to(ROOT)) for p in corrected_paths],
    behavior=BASE+'behavior-final.txt',
    behavior_scope='Source regenerative recurrence and damage reset; Shoot24/event12; blood and explosive lobs checked against independent 30Hz recurrence; exact impact and immunity exceptions; pending whole volleys/impacts and room completion; wandering/collision/contact; Spider/Strider throw height, stun and independent landing; strict immutable configuration; all six actual seeded residents.')
if failed:
    native['correction_review']=BASE+'native-corrections.json'
    assert (OUT/'native-corrections.json').exists()
web=load(BASE+'web/results.json')
assert len(web['checks'])==13 and not web['errors']
assert all('PASS '+case['case'] in (OUT/'browser.txt').read_text() for case in web['checks'])
browser=dict(cases=13,report=BASE+'web/results.json',errors=[],scope=web['scope'])
fingerprint=(OUT/'mechanics-final.txt').read_text().split('fingerprint ')[1].split()[0]
assert fingerprint=='bb632c6e46f99362'
assert load(BASE+'pool-audit.json')['counts']=={'direct':62,'enabled':66}
subprocess.run(['python3','scripts/isaac-reference/analyze-boils.py','--check'],cwd=ROOT,check=True,capture_output=True)
history=load(BASE+'historical-integrity.json')['files'];assert len(history)==5924
for path,digest in history.items(): assert sha(path)==digest,path
old=load(PREVIOUS);source=load(BASE+'source-review.json');visual=load(BASE+'visual-review.json')
assert len(load(BASE+'native-captures.json'))==12
runtime=['assets/mechanics/boils.mechanics','assets/mechanics/long_legs.mechanics','assets/mechanics/monsters.mechanics','assets/mechanics/encounters.mechanics',
    'src/combat/Boils.cpp','src/combat/LongLegs.cpp','src/combat/Monsters.cpp','src/combat/Simulation.hpp','src/combat/Swimmers.cpp',
    'src/content/Mechanics.hpp','src/content/Mechanics.cpp','src/content/EncounterVariants.cpp','src/render/MonsterVisuals.hpp','src/main.cpp',
    'tests/boil_tests.cpp','tests/evader_tests.cpp','tests/mulligan_tests.cpp','tests/resident_enemies_tests.cpp','web/boil-test.cjs','CMakeLists.txt','README.md']
save(BASE+'native-results.json',native)
save(BASE+'implementation-review.json',dict(scope=source['scope'],mechanics_fingerprint=fingerprint,native=native,browser=browser,visual=visual,
    adaptations=source['adaptations'],remaining=source['remaining'],complete=False,historical_artifacts_preserved=len(history)))
status=load('docs/research/isaac-enemy-port-status.json');save(BASE+'status-before.json',status)
records=load(BASE+'records.json')
ids=['30.0.0','30.1.0','30.2.0','88.0.0','88.1.0','88.2.0']
names=['boil','gut','sack','walking-boil','walking-gut','walking-sack']
bands={0:[1,2,3],1:[1,2],2:[0,1,2]}
for ident,name in zip(ids,names):
    r=next(r for r in status['records'] if r['id']==ident)
    walking=ident.startswith('88.');variant=int(ident.split('.')[1]);spider=variant==2
    r.update(review='reviewed',disposition='ordinary',implementation='in_progress')
    r['runtime']=list(dict.fromkeys(r['runtime']+runtime))
    r['evidence'].append(dict(source=BASE+'source-review.json',supports='Installed 1.7.9b stationary/walking controllers, WalkRandom and FireBossProjectiles helpers, shared projectile integration/explosive impact; nine preserved code windows, six ANM2 records, exact XML and room habitats. Wiki revision and local adaptations retained.'))
    r['contract']=dict(
        movement=('WalkRandom-derived wandering: source radius40/arrival3/force.5/friction.75, coasting during attacks; clear legal destinations and local physical collision.' if walking else 'Stationary; health-based growth and no contact damage.'),
        targeting='Ready source30Hz chance1/50; beyond230 units extra1/4. Shoot uses current player within250-20U, random direction/local scatter beyond that. '+('Spider births additionally require total room population<8 and successful1/count roll.' if spider else 'Blood/Gut shots have no population gate.'),
        attacks=('Shoot24/event12 throws independent Spider; walking initial height-30, stationary-10. A rejected stationary Sack shakes26frames; walking Sack keeps moving.' if spider else
            'Shoot24/event12 fires one explosive Gut lob: source velocity multiplier.55, targeted additional.6+U, height-23, initial fall speed-16.5..-33.3, acceleration1.02. Physical impact preserves producer identity.' if variant==1 else
            'Shoot24/event12 fires3/4 scattered blood projectiles: source speed7, targeted jitter0..3.5, height-23, initial fall speed-5..-29, acceleration1.32. Whole volley retained if capacity unavailable.'),
        vulnerability=('Source max20HP, starts full, no regeneration and ordinary damage does not interrupt shooting. Contact10 local damage.' if walking else
            'Source initial7/max20HP. Heal prior growth*1.2; growth=(growth+.02)*'+('.64' if spider else '.8')+'. Damage resets growth and interrupts attacks below fullHP. Lethal damage cannot regrow. No contact damage.')+' All six block hostile/environment EXPLOSION damage but allow player, ally/familiar and TNT explosions; ordinary fire/gunfire still hurt.',
        phases=('Initialize full; wander, attack coasting, event12 and recovery24.' if walking else 'Initialize partly grown; regenerate to full, ready, Shoot24/event12 or Sack Shake26, recovery. Damage returns to growth.'),
        offspring=('Spider85.0.0 or wet all-birth replacement Strider814.0.0. Thrown collision disabled until legal landing; shared stun timer advances; child survives parent death and retains room completion.' if spider else 'None for this exact family member; Gut explosion remains independently pending after producer death.'),
        completion='Living threats, pending offspring and retained explosive impacts keep the room sealed; final resolution permits completion.',
        source_numbers={k:records[ident]['xml'].get(k) for k in ['baseHP','stageHP','collisionDamage','collisionRadius','friction']},
        adaptations='; '.join(source['adaptations']),unknowns='; '.join(source['remaining']))
    kids=['85.0.0','814.0.0'] if spider else []
    r['children']=list(dict.fromkeys(r['children']+kids))
    r['placement']=[dict(kind='weighted_specialist',bands=bands[variant],approved=True,evidence=BASE+'source-review.json',note='Positive source room-template habitats mapped to local stage bands. Sparse cap1. Local weights/costs; native replacement percentages remain unverified.')]
    if ident=='30.2.0':
        r['parents']=list(dict.fromkeys(r['parents']+['206.1.0']))
        r['placement'].append(dict(kind='required_offspring',bands=[0,1],approved=True,evidence=PREVIOUS,note='Small Baby Long Legs retains its Sack child.'))
    r['unresolved']=source['remaining']
    r.setdefault('implementation_notes',[]).append('Regular-enemy priority: source-derived Boil family replaces generic placeholders; shared Sack integration and external values, all six seeded witnesses. Partial acceptance, not a completed port.')
    for gate,path,scope in [
        ('behavior',BASE+'behavior-final.txt',native['behavior_scope']),
        ('reachability',BASE+'web/results.json','All six identities verified in production seeded rooms on Linux and WASM. Spider/Strider children independently exercised.'),
        ('visual_linux',BASE+'native-'+name+'.png',visual['result']),
        ('visual_wasm',BASE+'web/'+name+'.png',browser['scope'])]:
        r['validation'][gate].append(dict(path=path,result='partial_pass',scope=scope))
    for child in kids:
        other=next(r for r in status['records'] if r['id']==child)
        other['parents']=list(dict.fromkeys(other['parents']+[ident]))
status['next_work']=[
    'USER PRIORITY: regular enemies and required offspring before additional bosses/Hornfel work.',
    'Boil/Gut/Sack and all three walking variants now use source-derived normal hostile controllers with partial Linux/WASM validation. Continue regular roster and ordinary-enemy acceptance gaps.',
    'Native replacement rates, hard mode/champions/status/control branches, exact grid/RNG parity, broad combat readability, balance and controlled performance remain open. Registry presence is not completion.']
status['priority_override']['current_focus']=['Regular enemies and required offspring','Continue regular roster and ordinary-enemy acceptance before more bosses']
status['latest_source_review']=BASE+'source-review.json'
status['checkpoint'].update(mechanics_fingerprint=fingerprint,report=BASE+'checkpoint.json',native_tests=74,runtime_definitions=173,reviewed_records=152,partial_implementations=110,direct_pool_ids=62,enabled_pool_ids=66,wasm_final_build_cases=13,
    note='Boil family regular-enemy slice: five generic rows replaced, Sack integrated; stationary regeneration, walking motion, physical blood/Gut shots, independent thrown children, source-aware immunity and stage pools.74unique native suites and13WASM cases pass. Full six-gate acceptance remains open;zero complete ports.')
save('docs/research/isaac-enemy-port-status.json',status)
checked=json.loads(subprocess.check_output(['python3','scripts/isaac-reference/track-enemies.py','--check','--csv'],cwd=ROOT,text=True))
assert checked['reviewed']==152 and checked['complete']==0 and checked['implementations']['in_progress']==110
assert checked['implementations']['missing']==466 and checked['implementations']['existing_unverified']==65
save(BASE+'checklist-final.json',checked);save('docs/research/isaac-enemy-port-validation.json',checked)
p=ROOT/'docs/isaac_monsters.md';text=p.read_text();marker='Current implementation checkpoint:\n';assert marker in text
text=text.replace(marker,marker+'''
The [Boil family checkpoint](reports/isaac-enemy-port/boils/checkpoint.json)
replaces generic Boil 30.0, Gut 30.1 and Walking Boil/Gut/Sack 88.0/88.1/88.2
behavior and extends Sack 30.2. Stationary bodies regenerate; walkers wander
without healing. Blood volleys, explosive Gut lobs and independently thrown
Spider/Strider offspring use source animation events, physical trajectories
and source-aware damage rules. All six occur in appropriate seeded stage pools.
Fingerprint `bb632c6e46f99362`: **173 definitions, 152 reviewed, 110 in progress,
65 existing-unverified, 466 missing, 12 excluded; zero complete ports**.
The direct ordinary pool has 62 identities, 66 including replacements.
**74 unique native suites and 13 WASM cases pass.** Original-style Linux/WASM
captures were inspected. Hard/champion/control branches, native substitutions,
full readability, balance and controlled performance remain open.
Regular enemies and required offspring remain the priority.

''',1);p.write_text(text)
sourcepaths=set(old['source_sha256'])|{'scripts/isaac-reference/analyze-boils.py',BASE+'source-review.json',BASE+'extract-metadata.py',BASE+'records.json',BASE+'wiki-source.json'}
sourcepaths|={str(p.relative_to(ROOT)) for folder in ['source','animations'] for p in (OUT/folder).rglob('*') if p.is_file()}
buildpaths=set(old['build_sha256'])|{'build/deathward_boil_tests'}
save(BASE+'checkpoint.json',dict(status='Partial regular Boil family port; full goal active; regular enemies prioritized.',created_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),
    mechanics_fingerprint=fingerprint,runtime_definitions=173,item_definitions=13,enemy_bomb_profiles=6,checklist=checked,native=native,browser=browser,visual=visual,remaining=source['remaining'],implementation_review=BASE+'implementation-review.json',previous_checkpoint=PREVIOUS,
    runtime_sha256={p:sha(p) for p in sorted(set(old['runtime_sha256'])|set(runtime))},build_sha256={p:sha(p) for p in sorted(buildpaths)},source_sha256={p:sha(p) for p in sorted(sourcepaths)},
    artifacts_sha256={str(p.relative_to(ROOT)):sha(str(p.relative_to(ROOT))) for p in OUT.rglob('*') if p.is_file() and p.name!='checkpoint.json'}))
print(json.dumps(dict(checkpoint=BASE+'checkpoint.json',native_unique_pass=74,wasm_pass=13,historical_unchanged=len(history),complete=0)))
