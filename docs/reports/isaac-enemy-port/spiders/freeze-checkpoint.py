"""Freeze validated Spider/Big Spider work once, preserving prior evidence."""
import datetime, hashlib, json, subprocess
from pathlib import Path
ROOT=Path(__file__).resolve().parents[4]
BASE='docs/reports/isaac-enemy-port/spiders/'
OUT=ROOT/BASE
PREVIOUS='docs/reports/isaac-enemy-port/mullighoul/checkpoint.json'
def load(p):return json.loads((ROOT/p).read_text())
def save(p,v):(ROOT/p).write_text(json.dumps(v,indent=2,ensure_ascii=False)+'\n')
def sha(p):
 h=hashlib.sha256()
 with (ROOT/p).open('rb') as f:
  for b in iter(lambda:f.read(4*1024*1024),b''):h.update(b)
 return h.hexdigest()
assert not (OUT/'checkpoint.json').exists(), 'Checkpoint already frozen'
native=load(BASE+'native-results.json')
assert native['covered_suites']==native['passed']==71 and native['failed']==0
assert 'PASS Spider and Big Spider' in (OUT/'behavior-second.txt').read_text()
(OUT/'behavior-final.txt').write_bytes((OUT/'behavior-second.txt').read_bytes())
web=load(BASE+'web/results.json');assert len(web['checks'])==8 and not web['errors']
fingerprint=(OUT/'mechanics.txt').read_text().split('fingerprint ')[1].split()[0]
assert fingerprint=='aed14fc9bf892f8c'
assert load(BASE+'pool-audit.json')['counts']=={'direct':52,'enabled':55}
subprocess.run(['python3','scripts/isaac-reference/analyze-spiders.py','--check'],cwd=ROOT,check=True,capture_output=True)
history=load(BASE+'historical-integrity.json')['files']
for p,h in history.items():assert sha(p)==h,p
assert len(history)==5646
old=load(PREVIOUS);source=load(BASE+'source-review.json');visual=load(BASE+'visual-review.json')
runtime=['assets/mechanics/spiders.mechanics','assets/mechanics/monsters.mechanics','src/combat/Spiders.cpp',
 'src/combat/Monsters.cpp','src/combat/Simulation.hpp','src/content/Mechanics.hpp','src/content/Mechanics.cpp',
 'src/content/EncounterVariants.cpp','src/render/MonsterVisuals.hpp','src/main.cpp','tests/spider_tests.cpp',
 'tests/mulligan_tests.cpp','tests/resident_enemies_tests.cpp','web/spider-test.cjs','CMakeLists.txt','README.md']
native.update(report=BASE+'native-results.json',behavior=BASE+'behavior-final.txt',
 behavior_scope='Source idle/acquisition and acceleration, committed target and moving-player prediction, shared movement, wandering, solid/deep-water collision, stuck release, contact/fire/stun, exact death offsets/impulses, overkill, retained capacity/completion, immutable config validation and actual seeded early-floor residents. Existing resident corridor/entry lifecycle and all Mulligan placements also pass.')
browser={'cases':8,'report':BASE+'web/results.json','errors':[],'scope':web['scope']}
save(BASE+'implementation-review.json',{'scope':source['scope'],'mechanics_fingerprint':fingerprint,'native':native,
 'browser':browser,'visual':visual,'adaptations':source['adaptations'],'remaining':source['remaining'],
 'complete':False,'historical_artifacts_preserved':len(history)})
status=load('docs/research/isaac-enemy-port-status.json');save(BASE+'status-before.json',status)
records=load(BASE+'records.json')
for ident in ['85.0.0','94.0.0']:
 r=next(r for r in status['records'] if r['id']==ident);big=ident=='94.0.0'
 r['review']='reviewed';r['disposition']='ordinary';r['implementation']='in_progress'
 r['runtime']=list(dict.fromkeys(r['runtime']+runtime))
 r['evidence'].append({'source':BASE+'source-review.json','supports':'Installed shared dispatch/controller, checked movement and death constants, target/room-clamp helpers, XML HP/radii/habitats and animation metadata. Local adaptations and unfinished native branches are explicit.'})
 r['contract']={
  'movement':'Shared30Hz stop-and-burst controller. Initial idle counter, random acquisition100..200source units with LOS; otherwise wander70..110 with authored margins. Acceleration6 then retention0.6. Arrival14 or negative counter plus speed<3 releases target, retaining final impulse. Full body collision blocks solids and impassable water.',
  'targeting':'Commits to player position plus10source velocity updates; no continuous homing. Wander target uses source left60/top70/right40/bottom60 margins and1/20trimmed-gap fallback. Narrow local rooms collapse impossible margin axes to centre.',
  'attacks':'Contact damage10before existing1.25multiplier; no projectile attack.',
  'vulnerability':('SourceHP20,stageHP0 ->64local.' if big else 'SourceHP6.5,stageHP0 ->20.8local.')+' Normal gunfire/fire vulnerability and equal local0.4collider. Native item/status special branches remain open.',
  'phases':'Idle initialization, paused target selection, committed movement burst and release. Stun interrupts/reset local clock. Source appear/thrown state6 are not reproduced here.',
  'offspring':'Exactly two independent full-health85.0.0children. Opposite player-perpendicular offsets1local unit and outward velocities30local units/s. Source APPEAR flag cleared. Post-hitHP<=-64suppresses; capacity/placement retains births and impulse.' if big else 'None. Required child of Big Spider and other reviewed/unreviewed spawners; parent-specific thrown state6 still requires separate implementation.',
  'completion':'Living spiders and pending births keep rooms sealed. Death children persist independently after Big Spider is removed; defeating all remaining threats permits completion.',
  'source_numbers':{k:records[ident]['xml'].get(k) for k in ['baseHP','stageHP','collisionDamage','collisionRadius','friction']},
  'adaptations':'; '.join(source['adaptations']),'unknowns':'; '.join(source['remaining'])}
 if big:r['children']=list(dict.fromkeys(r['children']+['85.0.0']))
 else:r['parents']=list(dict.fromkeys(r['parents']+['94.0.0']))
 r['placement']=[{'kind':'weighted_specialist' if big else 'weighted_basic','bands':[0,1,2],'approved':True,
  'evidence':BASE+'source-review.json','note':'Pursuit '+('specialist weight1/cost3/max1.' if big else 'pairs weight2/cost2/max4.')+' Sparse early/middle adaptation of Cellar/Catacombs and other source habitats.'}]
 r['unresolved']=source['remaining']
 r.setdefault('implementation_notes',[]).append('Regular Spider/Big Spider checkpoint adds the shared source-based ordinary burst controller and grounded two-child death split. No placeholder counts as complete; appear/thrown/item/status/grid details and full six-gate acceptance remain open.')
 for gate,path,scope in [
  ('behavior',BASE+'behavior-final.txt',native['behavior_scope']),
  ('reachability',BASE+'behavior-final.txt','Actual production Spider seed0/floor0/room3 and Big Spider seed71/floor0/room1; zero-based indices.'),
  ('visual_linux',BASE+('native-big-spider.png' if big else 'native-spider-group.png'),visual['result']),
  ('visual_wasm',BASE+'web/results.json',browser['scope'])]:
  r['validation'][gate].append({'path':path,'result':'partial_pass','scope':scope})
status['next_work']=['USER PRIORITY: regular enemies and required offspring first; additional boss/Hornfel expansion deferred.',
 'Spider85.0.0 and BigSpider94.0.0 now use source-based normal-hostile bursts, proper two-child death impulses and actual early-floor pools. Continue regular roster and close ordinary-enemy acceptance gaps.',
 'Strider814 and SwarmSpider884 have distinct native controllers; next spider-family work must review them separately. Native appear/thrown/item/status/grid branches and all six gates remain explicit; registry presence is not completion.']
status['priority_override']['current_focus']=['Regular enemies and their required offspring','Continue regular roster and close ordinary-enemy acceptance gaps before more boss work']
status['latest_source_review']=BASE+'source-review.json'
status['checkpoint'].update(mechanics_fingerprint=fingerprint,report=BASE+'checkpoint.json',native_tests=71,
 runtime_definitions=168,reviewed_records=140,partial_implementations=98,enemy_bomb_profiles=6,
 direct_pool_ids=52,enabled_pool_ids=55,wasm_final_build_cases=8,
 note='Spider/Big Spider regular-enemy slice: shared stop-and-burst movement, committed lead, solid/deep-water collision, two outward full-health death children and early-floor placement.71unique native suites pass across initial run and two fixture-correction reruns;8WASM cases pass;Original captures inspected. Native appear/thrown/item/status/grid and full six-gate acceptance remain open;zero complete ports.')
save('docs/research/isaac-enemy-port-status.json',status)
checked=json.loads(subprocess.check_output(['python3','scripts/isaac-reference/track-enemies.py','--check','--csv'],cwd=ROOT,text=True))
assert checked['reviewed']==140 and checked['complete']==0 and checked['implementations']['in_progress']==98
assert checked['implementations']['missing']==471 and checked['implementations']['existing_unverified']==72
save(BASE+'checklist-final.json',checked);save('docs/research/isaac-enemy-port-validation.json',checked)
p=ROOT/'docs/isaac_monsters.md';text=p.read_text();marker='Current implementation checkpoint:\n';assert marker in text
text=text.replace(marker,marker+'''
The [Spider and Big Spider checkpoint](reports/isaac-enemy-port/spiders/checkpoint.json)
adds source-based regular enemies 85.0.0 and 94.0.0. Both pause and commit to
movement bursts, predict a moving player and respect solid/deep-water barriers.
Big Spider produces two full-health ordinary spiders with opposite grounded
impulses, unless extreme overkill suppresses them. Both occur in actual seeded
early-floor rooms, with sparse pursuit pools across bands 0–2.
Fingerprint `aed14fc9bf892f8c`: **168 definitions, 140 reviewed, 98 in progress,
72 existing-unverified, 471 missing, 12 excluded; zero complete ports**.
The direct pool has 52 identities, 55 including conditional replacements.
**71 unique native suites pass** across the full run and two fixture-correction
reruns; **eight WASM cases pass**. Original captures were inspected. Native
appear/thrown/item/status/grid branches, broader readability, balance and
controlled performance acceptance remain open. Regular enemies and required
offspring remain the priority.

''',1);p.write_text(text)
p=OUT/'README.md';text=p.read_text().replace('Validation results will be recorded after execution.','''## Validation

All **71 unique native suites pass** in the [combined native report](native-results.json).
The [full run](native.xml) initially passed 69 and exposed two older fixture
assumptions: fixed Mulligan placement seeds and a universal generic attack
cooldown on room entry. Both were corrected and [Mulligan](native-corrected.xml)
and [resident lifecycle](native-residents-corrected.xml) reruns pass. Their
original failures remain preserved. No game runtime changed for these fixes.

The focused [Spider fixture](behavior-final.txt) checks source timing, acceleration,
committed prediction, collision, damage, two-child impulses, capacity/completion,
configuration and seeded reachability. All **eight WASM cases pass** with no
browser or GL errors in the [browser report](web/results.json).

The [visual review](visual-review.json) records nine inspected Linux/WASM
captures, including the two children and actual seeded rooms. A visible water
surface may be a walkable ford; collision correctness comes from fixtures and
telemetry, not a screenshot alone. All **5,646 older report artifacts** were
hash-verified unchanged. Both records remain in progress; the full goal is active.
''');p.write_text(text)
sourcepaths=set(old['source_sha256'])|{'scripts/isaac-reference/analyze-spiders.py',BASE+'source-review.json',BASE+'extract-metadata.py',BASE+'records.json',BASE+'wiki-source.json'}
sourcepaths|={str(p.relative_to(ROOT)) for folder in ['source','animations'] for p in (OUT/folder).rglob('*') if p.is_file()}
buildpaths=set(old['build_sha256'])|{'build/deathward_spider_tests','build/deathward_mulligan_tests','build/deathward_resident_enemies_tests'}
save(BASE+'checkpoint.json',{'status':'Partial regular Spider/Big Spider port; full goal active; regular enemies prioritized.',
 'created_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'mechanics_fingerprint':fingerprint,'runtime_definitions':168,'item_definitions':13,'enemy_bomb_profiles':6,
 'checklist':checked,'native':native,'browser':browser,'visual':visual,'remaining':source['remaining'],
 'implementation_review':BASE+'implementation-review.json','previous_checkpoint':PREVIOUS,
 'runtime_sha256':{p:sha(p) for p in sorted(set(old['runtime_sha256'])|set(runtime))},
 'build_sha256':{p:sha(p) for p in sorted(buildpaths)},'source_sha256':{p:sha(p) for p in sorted(sourcepaths)},
 'artifacts_sha256':{str(p.relative_to(ROOT)):sha(str(p.relative_to(ROOT))) for p in OUT.rglob('*') if p.is_file() and p.name!='checkpoint.json'}})
print(json.dumps({'checkpoint':BASE+'checkpoint.json','native_unique_pass':71,'wasm_pass':8,'historical_unchanged':len(history),'complete':0}))
