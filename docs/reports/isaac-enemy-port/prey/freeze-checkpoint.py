"""Freeze validated Prey/Small Leech work without modifying prior checkpoints."""
import datetime,hashlib,json,subprocess,xml.etree.ElementTree as ET
from pathlib import Path
ROOT=Path(__file__).resolve().parents[4]
BASE='docs/reports/isaac-enemy-port/prey/'
OUT=ROOT/BASE
PREVIOUS='docs/reports/isaac-enemy-port/mulligans/checkpoint.json'
def load(p):return json.loads((ROOT/p).read_text())
def save(p,v):(ROOT/p).write_text(json.dumps(v,indent=2,ensure_ascii=False)+'\n')
def sha(p):
 h=hashlib.sha256()
 with (ROOT/p).open('rb') as f:
  for b in iter(lambda:f.read(4*1024*1024),b''):h.update(b)
 return h.hexdigest()
assert not (OUT/'checkpoint.json').exists()
xml=ET.parse(OUT/'native.xml').getroot();assert xml.attrib['tests']=='69' and xml.attrib['failures']=='0'
assert 'PASS Prey and Small Leech' in (OUT/'behavior-third.txt').read_text()
(OUT/'behavior-final.txt').write_bytes((OUT/'behavior-third.txt').read_bytes())
web=load(BASE+'web/results.json');assert len(web['checks'])==8 and not web['errors']
fingerprint=(OUT/'mechanics.txt').read_text().split('fingerprint ')[1].split()[0];assert fingerprint=='3aa583b1c562abba'
assert load(BASE+'pool-audit.json')['counts']=={'direct':48,'enabled':51}
subprocess.run(['python3','scripts/isaac-reference/analyze-prey.py','--check'],cwd=ROOT,check=True,capture_output=True)
history=load(BASE+'historical-integrity.json')['files']
for p,h in history.items():assert sha(p)==h,p
old=load(PREVIOUS);source=load(BASE+'source-review.json');visual=load(BASE+'visual-review.json')
runtime=['assets/mechanics/prey.mechanics','src/combat/Swimmers.cpp','src/combat/MonsterMovement.cpp','src/combat/Charging.cpp',
 'src/combat/Monsters.cpp','src/combat/Simulation.hpp','src/world/Dungeon.hpp','src/world/FlightNavigation.cpp',
 'src/content/Mechanics.hpp','src/content/Mechanics.cpp','src/content/EncounterVariants.cpp','src/main.cpp',
 'tests/prey_tests.cpp','web/prey-test.cjs','CMakeLists.txt','README.md']
native={'covered_suites':69,'passed':69,'failed':0,'report':BASE+'native.xml','behavior':BASE+'behavior-final.txt',
 'scope':'Full native CTest run. Focused fixtures independently verify wet acceleration/friction and bounce, dry Hop10/Land6, swimming across actual water while respecting rock/room bounds, Prey Shoot4 live child, population-adjusted death counts and retained births, overkill,23sourceupdate thrown arc, airborne projectile/contact exclusion with blast vulnerability, legal landings/cover clearance, configuration rejection/immutable reload and two actual seeded residents.'}
browser={'cases':8,'report':BASE+'web/results.json','errors':[],'scope':web['scope']}
save(BASE+'implementation-review.json',{'scope':source['scope'],'mechanics_fingerprint':fingerprint,'native':native,'browser':browser,'visual':visual,
 'adaptations':source['adaptations'],'remaining':source['remaining'],'complete':False,'historical_artifacts_preserved':len(history)})
status=load('docs/research/isaac-enemy-port-status.json')
records=load(BASE+'records.json')
for ident in ['810.0.0','817.0.0']:
 r=next(r for r in status['records'] if r['id']==ident);small=ident=='810.0.0'
 r['review']='reviewed';r['disposition']='ordinary';r['implementation']='in_progress'
 r['runtime']=list(dict.fromkeys(r['runtime']+runtime))
 r['evidence'].append({'source':BASE+'source-review.json','supports':'Exact installed dispatch/controller/launch helper, source constants, XML/stage presence, Hop10/Land6 and HeadAttack18/Shoot4 metadata; adaptations and remaining branches distinguished.'})
 r['contract']={
  'movement':'Wet30Hz acceleration+.016 capped.35, retention.96, speed cap10; outward axis bounce-.6. Dry .7retention and1/2ready-update hop chance,2..4impulse; Hop10/Land6.' if small else 'Shared Hive flee/wander:14frame proximity checks,25/17local visibility range,3sticky evade checks,.8retention; physical canyon navigation adaptation.',
  'targeting':'Normalized current player delta during wet pursuit or dry hop launch; committed thrown-birth vector has no retargeting.' if small else 'Player proximity drives evasion and spitting. Room-wide population including pending births delays cooldown.',
  'attacks':'Contact10before existing1.25multiplier; no ranged attack. Ordinary dry animation hop keeps ground collision.' if small else 'HeadAttack18/Shoot4 emits one full-health persistent SmallLeech810.0.0.75frame cooldown plus20..69crowd delays using random4..8population gate.',
  'vulnerability':'SourceHP5/stage0 ->16local. Ordinary ground/wet body vulnerable. Thrown birth has no projectile/body collision; area damage remains effective.' if small else 'SourceHP14/stage0 ->44.8local. Harmless contact; normally vulnerable.',
  'phases':'Wet ready pursuit or dry ready/hop. Prey death births have state6-like airborne launch lasting23sourceupdates before normal behavior.' if small else 'Ready evasion, head attack/spawn event, death/overkill.',
  'offspring':'None; this is Prey live/death offspring as well as a directly placed regular enemy.' if small else 'Death max(1,ceil(4/(1+.2*population))-1), zero nativebc6counter. Post-hitHP<=-64 suppresses. Children thrown at parent:sourceheight-10,vy-8,gravity+.7,planar.04*(target-origin). Live children remain grounded.',
  'completion':'Living and airborne bodies count as room threats; pending retained births keep room sealed until admitted. Children remain after parent removal.',
  'source_numbers':{k:records[ident]['xml'].get(k) for k in ['baseHP','stageHP','collisionDamage','collisionRadius','gridCollision']},
  'adaptations':'; '.join(source['adaptations']),'unknowns':'; '.join(source['remaining'])}
 r['placement']=[{'kind':'weighted_specialist','bands':[1],'approved':True,'evidence':BASE+'source-review.json',
  'note':'Wet BrokenQuarry pursuit pool; source Downpour/Dross habitats'+('; also FloodedCaves Prey template.' if not small else '.')+' Weight1/cost'+('1/max2.' if small else '3/max1.')}]
 r['unresolved']=source['remaining']
 r.setdefault('implementation_notes',[]).append('Prey checkpoint adds source-based normal-hostile wet/dry/offspring behavior. Source launch multiplier corrected from initial .05 assertion to measured .04. Both records remain in_progress; six-gate certification is not claimed.')
 for gate,path,scope in [('behavior',BASE+'behavior-final.txt',native['scope']),('reachability',BASE+'behavior-final.txt','Actual seed41/floor2/room7 SmallLeech and seed119/floor2/room3 Prey production residents in approved wet band1.'),('visual_linux',BASE+('native-small-leech-river.png' if small else 'native-prey-death.png'),visual['result']),('visual_wasm',BASE+'web/results.json',browser['scope'])]:
  r['validation'][gate].append({'path':path,'result':'partial_pass','scope':scope})
status['next_work']=['USER PRIORITY: regular enemies and required offspring first; additional boss/Hornfel expansion deferred.',
 'Prey817.0.0 and SmallLeech810.0.0 have source-based normal hostile controllers, thrown births and seeded wet-floor placement. Continue remaining ordinary Mulligan/Hive variants and regular roster.',
 'Close explicit native path/counter/status/launch-search and six-gate acceptance gaps. Registry entries or partial controllers are not completed ports.']
status['priority_override']['current_focus']=['Regular enemies and their offspring','Remaining ordinary Mulligan/Hive variants and regular roster before additional bosses']
status['latest_source_review']=BASE+'source-review.json'
status['checkpoint'].update(mechanics_fingerprint=fingerprint,report=BASE+'checkpoint.json',native_tests=69,runtime_definitions=165,
 reviewed_records=137,partial_implementations=94,enemy_bomb_profiles=6,direct_pool_ids=48,enabled_pool_ids=51,wasm_final_build_cases=8,
 note='Prey/SmallLeech regular-enemy slice: source-based wet/dry movement,live/death spawning,23update airborne birth,water navigation and seeded wet-band placement.69native suites and8WASM cases pass;Original captures inspected. Native status/path/counter/late-geometry and full six-gate acceptance remain open;zero complete ports.')
save('docs/research/isaac-enemy-port-status.json',status)
checked=json.loads(subprocess.check_output(['python3','scripts/isaac-reference/track-enemies.py','--check','--csv'],cwd=ROOT,text=True))
assert checked['reviewed']==137 and checked['complete']==0 and checked['implementations']['in_progress']==94
save(BASE+'checklist-final.json',checked);save('docs/research/isaac-enemy-port-validation.json',checked)
p=ROOT/'docs/isaac_monsters.md';text=p.read_text();marker='Current implementation checkpoint:\n';assert marker in text
text=text.replace(marker,marker+'''
The [Prey and Small Leech checkpoint](reports/isaac-enemy-port/prey/checkpoint.json)
adds regular enemies 817.0.0 and 810.0.0, with source-based spawning, thrown death
children, wet swimming and dry hops. Swimming crosses water while preserving
solid cover and room edges. Thrown births use the recovered 0.04 planar factor
and land after 23 source updates; airborne contact/projectile collision restores
on landing. Both enemies occur in actual seeded wet band-1 rooms.
Fingerprint `3aa583b1c562abba`: **165 definitions, 137 reviewed, 94 in progress,
73 existing-unverified, 474 missing, 12 excluded; zero complete ports**.
The direct pool contains 48 identities, 51 with conditional replacements.
All **69 native suites and eight WASM cases pass**; selected Original captures
were inspected. Source status/owner/counter/path details, late geometry changes,
broad balance and controlled performance acceptance remain open. Regular enemies
and required offspring remain the priority ahead of additional bosses.

''',1);p.write_text(text)
p=OUT/'README.md';text=p.read_text().replace('Validation results will be recorded below only after execution.','''## Validation

All **69 native suites pass** in [CTest](native.xml), including the focused
[Prey/Small Leech fixture](behavior-final.txt). All **eight WASM cases pass**
in [the browser report](web/results.json), with no browser or GL errors.
The [visual review](visual-review.json) records selected inspected Original-style
Linux and WASM captures and its limits. The two production witnesses are
Small Leech seed 41/floor 2/room 7 and Prey seed 119/floor 2/room 3.
These are zero-based floor/room indices. All 5,480 earlier report artifacts were
hash-verified unchanged. No complete behavior, balance or controlled performance
acceptance is claimed; both records remain **in progress**.
''');p.write_text(text)
sourcepaths=set(old['source_sha256'])|{'scripts/isaac-reference/analyze-prey.py',BASE+'source-review.json',BASE+'extract-metadata.py',BASE+'records.json',BASE+'wiki-source.json'}
sourcepaths|={str(p.relative_to(ROOT)) for folder in ['source','animations'] for p in (OUT/folder).rglob('*') if p.is_file()}
save(BASE+'checkpoint.json',{'status':'Partial regular Prey/Small Leech port; full goal active; regular enemies prioritized.',
 'created_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'mechanics_fingerprint':fingerprint,'runtime_definitions':165,'item_definitions':13,'enemy_bomb_profiles':6,
 'checklist':checked,'native':native,'browser':browser,'visual':visual,'remaining':source['remaining'],'implementation_review':BASE+'implementation-review.json','previous_checkpoint':PREVIOUS,
 'runtime_sha256':{p:sha(p) for p in sorted(set(old['runtime_sha256'])|set(runtime))},'build_sha256':{p:sha(p) for p in old['build_sha256']},
 'source_sha256':{p:sha(p) for p in sorted(sourcepaths)},'artifacts_sha256':{str(p.relative_to(ROOT)):sha(str(p.relative_to(ROOT))) for p in OUT.rglob('*') if p.is_file() and p.name!='checkpoint.json'}})
print(json.dumps({'checkpoint':BASE+'checkpoint.json','native_pass':69,'wasm_pass':8,'historical_unchanged':len(history),'complete':0}))
