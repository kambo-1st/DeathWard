"""Freeze validated Willo/Mullighoul work once; preserve all prior evidence."""
import datetime,hashlib,json,subprocess,xml.etree.ElementTree as ET
from pathlib import Path
ROOT=Path(__file__).resolve().parents[4]
BASE='docs/reports/isaac-enemy-port/mullighoul/'
OUT=ROOT/BASE
PREVIOUS='docs/reports/isaac-enemy-port/prey/checkpoint.json'
def load(p):return json.loads((ROOT/p).read_text())
def save(p,v):(ROOT/p).write_text(json.dumps(v,indent=2,ensure_ascii=False)+'\n')
def sha(p):
 h=hashlib.sha256()
 with (ROOT/p).open('rb') as f:
  for b in iter(lambda:f.read(4*1024*1024),b''):h.update(b)
 return h.hexdigest()
assert not (OUT/'checkpoint.json').exists()
xml=ET.parse(OUT/'native.xml').getroot();assert xml.attrib['tests']=='70' and xml.attrib['failures']=='0'
assert 'PASS Willo and Mullighoul' in (OUT/'behavior-second.txt').read_text()
(OUT/'behavior-final.txt').write_bytes((OUT/'behavior-second.txt').read_bytes())
web=load(BASE+'browser-results.json');assert len(web['checks'])==9 and not web['errors']
fingerprint=(OUT/'mechanics.txt').read_text().split('fingerprint ')[1].split()[0];assert fingerprint=='13e2ff60d3fc3643'
assert load(BASE+'pool-audit.json')['counts']=={'direct':50,'enabled':53}
subprocess.run(['python3','scripts/isaac-reference/analyze-willo.py','--check'],cwd=ROOT,check=True,capture_output=True)
history=load(BASE+'historical-integrity.json')['files']
for p,h in history.items():assert sha(p)==h,p
old=load(PREVIOUS);source=load(BASE+'source-review.json');visual=load(BASE+'visual-review.json')
runtime=['assets/mechanics/mullighoul.mechanics','src/combat/Willos.cpp','src/combat/Evaders.cpp','src/combat/MonsterMovement.cpp',
 'src/combat/Navigation.cpp','src/combat/Enemies.cpp','src/combat/Monsters.cpp','src/combat/Simulation.cpp','src/combat/Simulation.hpp',
 'src/world/Dungeon.hpp','src/content/Mechanics.hpp','src/content/Mechanics.cpp','src/content/EncounterVariants.cpp',
 'src/render/MonsterVisuals.hpp','src/main.cpp','tests/mullighoul_tests.cpp','web/mullighoul-test.cjs','CMakeLists.txt','README.md']
native={'covered_suites':70,'passed':70,'failed':0,'report':BASE+'native.xml','behavior':BASE+'behavior-final.txt',
 'scope':'Full native CTest run. Focused fixtures verify elliptical orbit, regrouping, player tracking, shared attack lock, Warn6/Shoot24/Attack36, projectile physics and capacity, interruption, harmless contact and fire vulnerability, wall-passing shots versus ordinary shots, Mullighoul hover and water/rock navigation, live/death children, population counts, overkill, retained completion, immutable configuration/rejection and both actual seeded residents.'}
browser={'cases':9,'report':BASE+'browser-results.json','errors':[],'scope':web['scope']}
save(BASE+'implementation-review.json',{'scope':source['scope'],'mechanics_fingerprint':fingerprint,'native':native,'browser':browser,'visual':visual,
 'adaptations':source['adaptations'],'remaining':source['remaining'],'complete':False,'historical_artifacts_preserved':len(history)})
status=load('docs/research/isaac-enemy-port-status.json');save(BASE+'status-before.json',status)
records=load(BASE+'records.json')
for ident in ['808.0.0','817.1.0']:
 r=next(r for r in status['records'] if r['id']==ident);fly=ident=='808.0.0'
 r['review']='reviewed';r['disposition']='ordinary';r['implementation']='in_progress'
 r['runtime']=list(dict.fromkeys(r['runtime']+runtime))
 r['evidence'].append({'source':BASE+'source-review.json','supports':'Installed dispatch/orbit/attack/hover/death code, checked constants, XML HP and habitats, Attack36/Warn6/Shoot24 and HeadAttack18/Shoot4 metadata. Local adaptations and unfinished branches are explicit.'})
 r['contract']={
  'movement':'Player-centred 120x100.8 source ellipse; common angular rate 0.5*pi*0.035/update; twice player velocity carry plus half target correction capped10. Grid scenery ignored. Members redistribute evenly from minimum surviving offset.' if fly else 'Shared Hive evasion and wander with 14-frame proximity checks and .8 retention. Source height -6 and grid6 map to hover0.6 with water traversal and solid-rock/gate/room collision.',
  'targeting':'Single player; settled range20 and current-room eligibility. One attack at a time across the ordinary cohort; attack retains its committed orbit slot.' if fly else 'Player proximity controls fleeing and spitting; room population and pending births affect cooldown.',
  'attacks':'Ready1/9 check; Attack36, Warn6, Shoot24. One shot aims one target-velocity update ahead at source speed10 with NO_WALL_COLLIDE; recovered downward damped physics, ordinary player/ground collision.' if fly else 'HeadAttack18/Shoot4 creates one full-health Willo808.0.0. Cooldown75 with inherited population delays; child is persistent and has no disposable-contact flag.',
  'vulnerability':'Source HP6, stageHP0 ->19.2local. Harmless body; normally vulnerable to gunfire and fire.' if fly else 'Installed XML HP14, stageHP0 ->44.8local; pinned wiki13 is superseded. Harmless contact and normal vulnerability.',
  'phases':'Ready orbit, shared attack acquisition, warning, projectile event, recovery to ready. Stun interrupts and releases attack lock.' if fly else 'Ready evasion, head attack/spawn event, death or extreme-overkill suppression.',
  'offspring':'None; this is a directly placed enemy and Mullighoul live/death child. Parent-owned Min-Min special states are not implemented here.' if fly else 'Zero-counter death max(1,ceil(4/(1+.2*population))-1): 3 alone/2 with2others/1 with5. Post-hitHP<=-64 suppresses. Full-health independent Willos spawn directly, not thrown.',
  'completion':'Living bodies and pending death births keep the room sealed. Willos persist after the Mullighoul is removed; defeating all threats permits room completion.',
  'source_numbers':{k:records[ident]['xml'].get(k) for k in ['baseHP','stageHP','collisionDamage','collisionRadius','gridCollision']},
  'adaptations':'; '.join(source['adaptations']),'unknowns':'; '.join(source['remaining'])}
 r['placement']=[{'kind':'weighted_specialist','bands':[1],'approved':True,'evidence':BASE+'source-review.json',
  'note':'Wet Broken Quarry '+('crossfire pairs, weight1/cost2/max3; source Downpour and Flooded Caves.' if fly else 'pursuit, weight1/cost3/max1; source Downpour.')}]
 r['unresolved']=source['remaining']
 r.setdefault('implementation_notes',[]).append('Regular Willo/Mullighoul checkpoint adds source-based normal hostile behavior and seeded wet-band placement. Native special status/owner/boss paths and full six-gate certification remain open; both IDs remain in_progress.')
 for gate,path,scope in [('behavior',BASE+'behavior-final.txt',native['scope']),
  ('reachability',BASE+'behavior-final.txt','Actual seed3/floor1/room6 Willo and seed80/floor2/room8 Mullighoul production residents; zero-based floor/room.'),
  ('visual_linux',BASE+('native-willo-cohort.png' if fly else 'native-mullighoul-early.png'),visual['result']),
  ('visual_wasm',BASE+'browser-results.json',browser['scope'])]:
  r['validation'][gate].append({'path':path,'result':'partial_pass','scope':scope})
status['next_work']=['USER PRIORITY: regular enemies and required offspring first; additional boss/Hornfel expansion deferred.',
 'Willo808.0.0 and Mullighoul817.1.0 now have source-based normal-hostile behavior and actual seeded wet-floor placement. Continue regular roster and close remaining regular-enemy acceptance gaps.',
 'Owner/status/native-counter/path and full six-gate acceptance gaps remain explicit. Registry presence or partial controllers do not count as complete ports.']
status['priority_override']['current_focus']=['Regular enemies and their required offspring','Continue regular roster and close ordinary-enemy acceptance gaps before more boss work']
status['latest_source_review']=BASE+'source-review.json'
status['checkpoint'].update(mechanics_fingerprint=fingerprint,report=BASE+'checkpoint.json',native_tests=70,runtime_definitions=167,
 reviewed_records=138,partial_implementations=96,enemy_bomb_profiles=6,direct_pool_ids=50,enabled_pool_ids=53,wasm_final_build_cases=9,
 note='Willo/Mullighoul regular-enemy slice: source-based orbit and shared attack timing,wall-passing damped shots,hover navigation,live/death spawning and seeded wet-band placement.70native suites and9WASM cases pass;Original captures inspected. Owner/status/counter/path/special-boss branches and full six-gate acceptance remain open;zero complete ports.')
save('docs/research/isaac-enemy-port-status.json',status)
checked=json.loads(subprocess.check_output(['python3','scripts/isaac-reference/track-enemies.py','--check','--csv'],cwd=ROOT,text=True))
assert checked['reviewed']==138 and checked['complete']==0 and checked['implementations']['in_progress']==96
assert checked['implementations']['missing']==472
save(BASE+'checklist-final.json',checked);save('docs/research/isaac-enemy-port-validation.json',checked)
p=ROOT/'docs/isaac_monsters.md';text=p.read_text();marker='Current implementation checkpoint:\n';assert marker in text
text=text.replace(marker,marker+'''
The [Willo and Mullighoul checkpoint](reports/isaac-enemy-port/mullighoul/checkpoint.json)
adds regular enemies 808.0.0 and 817.1.0. Willos share a player-centred elliptical
orbit and take turns attacking with Warn6/Shoot24 timing and wall-passing,
damped shots. Mullighoul hovers across water while respecting solid scenery,
spits full-health Willos and retains population-adjusted death births.
Both occur in actual seeded wet band-1 rooms; a natural Willo room also verifies
interaction with an attraction statue.
Fingerprint `13e2ff60d3fc3643`: **167 definitions, 138 reviewed, 96 in progress,
73 existing-unverified, 472 missing, 12 excluded; zero complete ports**.
The direct pool has 50 identities, 53 including conditional replacements.
All **70 native suites and nine WASM cases pass**. Selected Original captures
were inspected. Owner/status/counter/path and special boss branches, broader
readability, balance and controlled performance acceptance remain open.
Regular enemies and required offspring remain the priority.

''',1);p.write_text(text)
p=OUT/'README.md';text=p.read_text().replace('Validation results will be recorded after execution.','''## Validation

All **70 native suites pass** in [CTest](native.xml), including the focused
[Willo/Mullighoul fixture](behavior-final.txt). All **nine WASM cases pass**
in the [combined browser report](browser-results.json), with no browser or GL
errors. Seven isolated cases and two natural cases retain separate evidence
files; the latter include an attraction-statue interaction that changes shot
speed after firing. [Fixture corrections](browser-fixture-corrections.txt)
explain the two browser assertion failures and why no runtime change was needed.

The [visual review](visual-review.json) records inspected Linux and WASM
captures and their limits. Earlier captures can hide fleeing actors behind the
HUD or scenery, so an additional early Linux capture shows the hovering parent
and child clearly. All 5,553 earlier report artifacts were hash-verified
unchanged. Neither record is certified complete; the broader goal remains active.
''');p.write_text(text)
sourcepaths=set(old['source_sha256'])|{'scripts/isaac-reference/analyze-willo.py',BASE+'source-review.json',BASE+'extract-metadata.py',BASE+'records.json',BASE+'wiki-source.json'}
sourcepaths|={str(p.relative_to(ROOT)) for folder in ['source','animations'] for p in (OUT/folder).rglob('*') if p.is_file()}
save(BASE+'checkpoint.json',{'status':'Partial regular Willo/Mullighoul port; full goal active; regular enemies prioritized.',
 'created_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'mechanics_fingerprint':fingerprint,'runtime_definitions':167,'item_definitions':13,'enemy_bomb_profiles':6,
 'checklist':checked,'native':native,'browser':browser,'visual':visual,'remaining':source['remaining'],'implementation_review':BASE+'implementation-review.json','previous_checkpoint':PREVIOUS,
 'runtime_sha256':{p:sha(p) for p in sorted(set(old['runtime_sha256'])|set(runtime))},'build_sha256':{p:sha(p) for p in old['build_sha256']},
 'source_sha256':{p:sha(p) for p in sorted(sourcepaths)},'artifacts_sha256':{str(p.relative_to(ROOT)):sha(str(p.relative_to(ROOT))) for p in OUT.rglob('*') if p.is_file() and p.name!='checkpoint.json'}})
print(json.dumps({'checkpoint':BASE+'checkpoint.json','native_pass':70,'wasm_pass':9,'historical_unchanged':len(history),'complete':0}))
