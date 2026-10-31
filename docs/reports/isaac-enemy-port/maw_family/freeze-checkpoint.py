"""One-time partial regular-enemy checkpoint; do not rewrite old evidence."""
import datetime,hashlib,json,subprocess,xml.etree.ElementTree as ET
from pathlib import Path
ROOT=Path(__file__).resolve().parents[4];BASE='docs/reports/isaac-enemy-port/maw_family/';OUT=ROOT/BASE
PREVIOUS='docs/reports/isaac-enemy-port/boils/checkpoint.json'
def load(p):return json.loads((ROOT/p).read_text())
def save(p,v):(ROOT/p).write_text(json.dumps(v,indent=2,ensure_ascii=False)+'\n')
def sha(p):
 h=hashlib.sha256()
 with (ROOT/p).open('rb') as stream:
  for chunk in iter(lambda:stream.read(4*1024*1024),b''):h.update(chunk)
 return h.hexdigest()
assert not (OUT/'checkpoint.json').exists(),'Already frozen'
cases=ET.parse(OUT/'native-final.xml').getroot().findall('.//testcase')
def passed(c):return all(c.find(tag) is None for tag in ['failure','error','skipped'])
assert len(cases)==75
corrected=ET.parse(OUT/'floor-corrected-2.xml').getroot().findall('.//testcase')
assert len(corrected)==1 and corrected[0].attrib['name']=='floor_progression' and passed(corrected[0])
assert {c.attrib['name'] for c in cases if not passed(c)}=={'floor_progression'}
passing=sorted({c.attrib['name'] for c in cases+corrected if passed(c)});assert len(passing)==75
assert 'PASS Maw family' in (OUT/'native-targeted-residents.txt').read_text()
web=load(BASE+'web-final/results.json');assert len(web['checks'])==6 and not web['errors']
assert all('PASS '+r['case'] in (OUT/'browser.txt').read_text() for r in web['checks'])
assert len(load(BASE+'native-final-captures.json'))==6
visual=load(BASE+'visual-review.json');assert len(visual['final_images'])==12
fingerprint=(OUT/'mechanics-final.txt').read_text().split('fingerprint ')[1].split()[0]
assert fingerprint=='2508db221cb94f34'
assert 'direct_pool_id_count=65' in (OUT/'pool-audit.txt').read_text()
history=load(BASE+'historical-integrity.json')['files'];assert len(history)==6054
for path,digest in history.items():assert sha(path)==digest,path
subprocess.run(['python3','scripts/isaac-reference/analyze-maw-family.py','--check'],cwd=ROOT,check=True,capture_output=True)
native=dict(passed=75,failed=0,report=BASE+'native-final.xml',passing_suites=passing,corrected_report=BASE+'floor-corrected-2.xml',
 behavior=BASE+'native-targeted-residents.txt',initial_run=BASE+'native.xml',
 corrections='Initial75-suite run passed74. Drowned Hive witness invalidated by larger pools; independent production search found118/floor2/room6. Fixture keeps earlier candidates. Final full run includes resident birth-queue lifecycle fix; floor fixture then corrected to distinguish mandatory orbiters from ordinary counts and allow their source-prescribed initial overlap with their parent. All75unique suites pass across full and corrected runs.')
browser=dict(cases=6,report=BASE+'web-final/results.json',scope=web['scope'],errors=[])
remaining=[
 'Native appearance/teleport overlays, parent visibility/grid ownership/outer margins, hard/champion/status/control branches and exact RNG/grid parity remain open.',
 'Eternal Fly corn-poop ownership and other parents are not complete; Holy Leech legacy cleanup retained pending parent review.',
 'Released Eternal Fly contact-death claim remains unresolved in native collision code; no unverified contact-death flag invented.',
 'Native three-frame homing target selection, friendly targeting, source shot height/lifetime and status-modified homing strength remain open.',
 'Native variant replacement probabilities, full combat readability, balance and controlled Linux/WASM performance acceptance remain open.']
adaptations=['Source30Hz with native distance x.1 and velocity x3; collision-aware3D flight and local finite projectile lifetime.',
 'HP x3.2 and established hostile damage conversion; authored band1–3 specialist costs/weights/cap1, no opening floor.',
 'Whole pending death volleys and required offspring survive capacity pressure; room-owned deferred births preserve lifecycle.',
 'Original procedural pale/red/purple heads, stitched mouths/Psychic eye, purple homing shots and white orbiting fly; safe shader normal fallback.']
review=dict(scope='Partial normal-hostile Maw26.0/26.1/26.2 and Psychic-linked Eternal Fly96.0; regular-enemy priority.',
 source=BASE+'source-review.md',adaptations=adaptations,remaining=remaining,native=native,browser=browser,visual=visual,complete=False)
save(BASE+'implementation-review.json',review)
runtime=['assets/mechanics/maw_family.mechanics','assets/mechanics/monsters.mechanics','src/combat/MawFamily.cpp',
 'src/combat/Monsters.cpp','src/combat/Simulation.hpp','src/combat/Simulation.cpp','src/combat/Encounters.cpp','src/combat/FloorEncounters.cpp',
 'src/combat/Enemies.cpp','src/combat/BuzzFlies.cpp','src/content/Mechanics.hpp','src/content/Mechanics.cpp','src/content/EncounterVariants.cpp',
 'src/render/MonsterVisuals.hpp','src/render/MissionLighting.cpp','src/render/Renderer.cpp','src/main.cpp','tests/maw_family_tests.cpp','tests/floor_progression_tests.cpp','tests/evader_tests.cpp','web/maw-family-test.cjs','CMakeLists.txt']
status=load('docs/research/isaac-enemy-port-status.json');save(BASE+'status-before.json',status)
ids=['26.0.0','26.1.0','26.2.0','96.0.0'];names=['maw','red-maw','psychic-maw','psychic-maw']
for ident,name in zip(ids,names):
 r=next(r for r in status['records'] if r['id']==ident);fly=ident.startswith('96.');red=ident=='26.1.0';psychic=ident=='26.2.0'
 r.update(review='reviewed',disposition='component' if fly else 'ordinary',implementation='in_progress')
 r['runtime']=list(dict.fromkeys(r['runtime']+runtime))
 r['evidence'].append(dict(source=BASE+'source-review.md',supports='Installed dispatch/controller windows and checked constants, four animation metadata records, exact XML/habitats and archived wiki revisions; homing parameter offset correction and release healing recurrence; explicit gaps.'))
 r['contract']=dict(
  movement='Parent-linked25x20ellipse, .04π angular step, seeded phase/direction, growing90frames, .5 follow per source tick.' if fly else 'Flying pursuit impulse'+('.39' if red else '.13')+' and friction.93 on30Hz clock; attack animation coasts without pursuit impulse.',
  targeting='Linked parent center, released fly uses the existing reviewed Attack Fly targeting.' if fly else 'Current player; non-Red acquisition strict200 source units and seven-frame stagger; shot aims at Shoot event.',
  attacks='Contact10 local damage while orbiting; released Attack Fly controller.' if fly else 'Four cardinal8-unit/frame death shots; no live projectile.' if red else 'Shoot20/event4; cooldown28 from acquisition; source speed7.'+(' Scale1.5 and default-strength homing; whole-heart base damage20 local.' if psychic else ''),
  vulnerability='300HP source, invulnerable/no-status orbit hazard; releases with Attack Fly maxHP and finite maxHP/60 healing for prior orbit ticks.' if fly else '20HP source,64local; ordinary projectile/contact damage; no invented armor or regeneration.',
  phases='Growing orbit; parent death morph preserves actor identity, changes to damageable room threat; finite regeneration.' if fly else 'Ready pursuit, acquisition, Shoot event, recovery; stun interrupts, death cancels live cast. Red has no cast.',
  offspring='Morph18.0.0, not a new reward entity.' if fly else 'Required96.0.0 at owner position, retained under capacity and across resident-room lifecycle.' if psychic else 'No offspring; Red death volley remains pending until all four shots fit.',
  completion='Released Attack Fly blocks completion. Pending births/Red death volleys must resolve. Orbit itself is a room hazard.',
  adaptations='; '.join(adaptations),unknowns='; '.join(remaining))
 r['children']=list(dict.fromkeys(r['children']+(['18.0.0'] if fly else ['96.0.0'] if psychic else [])))
 if fly:r['parents']=list(dict.fromkeys(r['parents']+['26.2.0']))
 r['placement']=[dict(kind='required_offspring' if fly else 'weighted_specialist',bands=[1,2,3],approved=True,evidence=BASE+'source-review.md',note='Psychic Maw dependency only.' if fly else 'Source habitats; authored weights/costs, cap1. Native substitutions not certified.')]
 r['unresolved']=remaining
 for gate,path,scope in [('behavior','native-targeted-residents.txt','Normal pursuit/cast/homing, cardinal death burst, orbit/release/finite regeneration, capacity and room round trip, immutable config; not all source branches.'),
  ('reachability','web-final/results.json','Three concrete production resident witnesses, Psychic required child retained before entry.'),
  ('visual_linux','native-final-'+name+'.png',visual['scope']),('visual_wasm','web-final/'+name+'.png',visual['scope'])]:
  r['validation'][gate].append(dict(path=BASE+path,result='partial_pass',scope=scope))
attackFly=next(r for r in status['records'] if r['id']=='18.0.0');attackFly['parents']=list(dict.fromkeys(attackFly['parents']+['96.0.0']))
status['next_work']=['USER PRIORITY: regular enemies and required offspring before further bosses.',
 'Continue the unreviewed regular roster (e.g. Host family) and ordinary-enemy acceptance gaps; do not count generic placeholders as completed ports.',*remaining]
status['latest_source_review']=BASE+'source-review.md'
status['checkpoint'].update(mechanics_fingerprint=fingerprint,report=BASE+'checkpoint.json',native_tests=75,runtime_definitions=173,reviewed_records=156,partial_implementations=114,direct_pool_ids=65,enabled_pool_ids=69,wasm_final_build_cases=6,
 note='Partial Maw family source-derived controllers plus required Eternal Fly; resident queue lifecycle and zero-normal render fixes.75native suites/6WASM cases pass; full six-gate acceptance remains open;zero complete ports.')
save('docs/research/isaac-enemy-port-status.json',status)
checked=json.loads(subprocess.check_output(['python3','scripts/isaac-reference/track-enemies.py','--check','--csv'],cwd=ROOT,text=True))
assert checked['reviewed']==156 and checked['complete']==0 and checked['implementations']['in_progress']==114 and checked['implementations']['existing_unverified']==61
save(BASE+'checklist-final.json',checked);save('docs/research/isaac-enemy-port-validation.json',checked)
p=ROOT/'docs/isaac_monsters.md';text=p.read_text();marker='Current implementation checkpoint:\n';assert marker in text
text=text.replace(marker,marker+'''
The [Maw-family checkpoint](reports/isaac-enemy-port/maw_family/checkpoint.json)
adds source-derived normal Maw, Red Maw and Psychic Maw controllers, with the
Psychic Maw's Eternal Fly orbit/release dependency. Required births now survive
resident-room preparation and room changes. A zero-normal lighting defect found
in its halo capture is fixed. Fingerprint `2508db221cb94f34`: **173 definitions,
156 reviewed, 114 in progress, 61 existing-unverified, 466 missing, 12 excluded;
zero complete ports**. There are 65 direct ordinary pool identities, 69 including
replacements. **75 native suites and 6 production WASM cases pass.** See the report
for source gaps, adaptation details and inspected Original-style captures.
Regular enemies and their required offspring remain the priority.

''',1);p.write_text(text)
old=load(PREVIOUS)
sources=set(old['source_sha256'])|{'scripts/isaac-reference/analyze-maw-family.py',BASE+'source-review.md',BASE+'records.json',BASE+'extract-metadata.py',BASE+'maw-wiki-source.json',BASE+'fly-wiki-source.json'}
sources|={str(p.relative_to(ROOT)) for folder in ['source','animations'] for p in (OUT/folder).rglob('*') if p.is_file()}
builds=set(old['build_sha256'])|{'build/deathward_maw_family_tests'}
save(BASE+'checkpoint.json',dict(status='Partial regular Maw-family port; full goal active.',created_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),
 mechanics_fingerprint=fingerprint,runtime_definitions=173,item_definitions=13,enemy_bomb_profiles=6,checklist=checked,native=native,browser=browser,visual=visual,remaining=remaining,
 previous_checkpoint=PREVIOUS,implementation_review=BASE+'implementation-review.json',historical_artifacts_preserved=len(history),
 runtime_sha256={p:sha(p) for p in sorted(set(old['runtime_sha256'])|set(runtime))},build_sha256={p:sha(p) for p in sorted(builds)},source_sha256={p:sha(p) for p in sorted(sources)},
 artifacts_sha256={str(p.relative_to(ROOT)):sha(str(p.relative_to(ROOT))) for p in OUT.rglob('*') if p.is_file() and p.name!='checkpoint.json'}))
print(json.dumps(dict(checkpoint=BASE+'checkpoint.json',native_pass=75,wasm_pass=6,historical_unchanged=len(history),complete=0)))
