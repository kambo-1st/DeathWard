"""Freeze one validated regular-enemy slice, preserving earlier report evidence."""
import datetime, hashlib, json, subprocess, xml.etree.ElementTree as ET
from pathlib import Path
ROOT=Path(__file__).resolve().parents[4]
BASE='docs/reports/isaac-enemy-port/mulligans/'
OUT=ROOT/BASE
PREVIOUS='docs/reports/isaac-enemy-port/hive/checkpoint.json'
def load(p): return json.loads((ROOT/p).read_text())
def save(p,v): (ROOT/p).write_text(json.dumps(v,indent=2,ensure_ascii=False)+'\n')
def sha(p):
 h=hashlib.sha256()
 with (ROOT/p).open('rb') as f:
  for block in iter(lambda:f.read(4*1024*1024),b''):h.update(block)
 return h.hexdigest()
assert not (OUT/'checkpoint.json').exists()
native_xml=ET.parse(OUT/'native.xml').getroot()
assert native_xml.attrib['tests']=='68' and native_xml.attrib['failures']=='0'
assert 'PASS Mulligan family' in (OUT/'behavior-final.txt').read_text()
web=load(BASE+'web/results.json');assert len(web['checks'])==10 and not web['errors']
fingerprint=(OUT/'mechanics.txt').read_text().split('fingerprint ')[1].split()[0]
assert fingerprint=='6db1f4889ab4996d'
assert load(BASE+'pool-audit.json')['counts']=={'direct':46,'enabled':49}
subprocess.run(['python3','scripts/isaac-reference/analyze-mulligans.py','--check'],cwd=ROOT,check=True,capture_output=True)
history=load(BASE+'historical-integrity.json')['files']
for path,digest in history.items():assert sha(path)==digest,path
old=load(PREVIOUS);source=load(BASE+'source-review.json')
runtime=['assets/mechanics/mulligans.mechanics','assets/mechanics/monsters.mechanics','assets/mechanics/deaths.mechanics',
 'src/combat/Evaders.cpp','src/combat/EnemyBombs.cpp','src/combat/Monsters.cpp','src/combat/Simulation.hpp',
 'src/content/Mechanics.hpp','src/content/Mechanics.cpp','tests/mulligan_tests.cpp','tests/monster_tests.cpp','web/mulligan-test.cjs','CMakeLists.txt','README.md']
native={'covered_suites':68,'passed':68,'failed':0,'report':BASE+'native.xml','behavior':BASE+'behavior-final.txt',
 'scope':'Full native CTest run. Focused family fixture verifies actual collision-triggered detonation,29-frame timing/death interruption,4independent weighted children and scaled overkill,4/8shot rings,real randomized Troll Bomb,atomic capacity retry and actual room completion,5-frame proximity/half-heart damage,nearby monster/rock blast effects,immutable snapshots and three actual production residents.'}
browser={'cases':10,'report':BASE+'web/results.json','errors':[],'scope':web['scope'],'coverage':web['coverage']}
visual=load(BASE+'visual-review.json')
save(BASE+'implementation-review.json',{'scope':source['scope'],'mechanics_fingerprint':fingerprint,'native':native,'browser':browser,'visual':visual,'adaptations':source['adaptations'],'remaining':source['remaining'],'complete':False,'historical_artifacts_preserved':len(history)})
status=load('docs/research/isaac-enemy-port-status.json')
for variant in range(3):
 ident=f'16.{variant}.0';r=next(r for r in status['records'] if r['id']==ident)
 r['implementation']='in_progress';r['runtime']=list(dict.fromkeys(r['runtime']+runtime))
 r['evidence'].append({'source':BASE+'source-review.json','supports':'Installed type16controller,proved CollidesWithGrid field,1/300trigger/29framewindup,5frame40unitproximity,death children/rings/blasts,Troll initialization and unresolved fuse interpretation;sourceHP13/stage0.'})
 r['contract'].update(movement='30Hz '+('chase:FindGridPath speed1.2/.9retention' if variant==2 else 'flee/wander with.8retention,proximity14/25visible/17hidden/3sticky checks')+' adapted to physical canyon navigation;exact native grid movement pending.',
  targeting='Distance<4local units every5source frames triggers death.' if variant==2 else 'Player proximity drives evasion; actual static terrain collision permits ready-state1/300detonation check. No fixed-age trigger.',
  attacks=['Voluntary29-frame detonation emits four cardinal speed21shots and immediate128damage/radius6blast;ordinary death has no blast.','Ordinary death:four diagonal speed21shots and Troll Bomb4.3. Voluntary29-frame detonation adds cardinal shots and immediate128damage/radius6blast:8shots total plus Troll Bomb.','Immediate128damage/radius6blast on proximity or death;no Troll Bomb or windup.'][variant],
  vulnerability='13sourceHPx3.2=41.6localHP;stageHP0;normally vulnerable;no body contact damage.',
  phases='Ready chase then immediate death.' if variant==2 else 'Ready evade/wander;collision-triggered29-frame explosion windup;normal damage during windup cancels the voluntary blast.',
  offspring=['Four independent Fly13/AttackFly18/Pooter14weighted7:3:1draws;no population divisor. Post-hitHP<=-32suppresses. NativeNPC+bc6nonzero cases pending.','No offspring body;real Troll Bomb source100damage/75radius/initialized45..74count→local320damage/7.5radius/provisional1.5..74/30secondfuse.','No offspring body or delayed bomb.'][variant],
  completion='Pending whole death payload retains dead carrier and prevents room completion until admitted. Offspring count as threats. Placed Troll Bomb survives producer removal and clear. Debug execution suppresses effects.',
  adaptations='; '.join(source['adaptations']),unknowns='; '.join(source['remaining']))
 r['placement']=[{'kind':['weighted_specialist','conditional_replacement','weighted_specialist_and_conditional'][variant],'bands':[0,1] if variant==2 else [0],'approved':True,'evidence':BASE+'source-review.json','note':['Band0pursuit weight2/cost2/max1;phase0Mulligoon9.49%,phase1Mulliboom1%.','9.49%Mulligan replacement then1%Mulliboom check in band0.','Band0phase1replacement1%;standardband1direct pursuit weight1/cost3/max1.'][variant]}]
 r['unresolved']=source['remaining']
 r.setdefault('implementation_notes',[]).append('Mulligan checkpoint supersedes generic fixed-age detonation,unscaled death threshold,owner-population and literal-contact assumptions. Proved native proximity is40source units. Remains in_progress; Troll fuse wall-clock/animation and full six-gate parity remain open.')
 for gate,path,scope in [('behavior',BASE+'behavior-final.txt',native['scope']),('reachability',BASE+'behavior-final.txt','Actual production witnesses plus configured source replacement odds;first-floor1%Mulliboom witness not claimed.'),('visual_linux',BASE+['native-mulligan.png','native-mulligoon.png','native-mulliboom-live.png'][variant],visual['result']),('visual_wasm',BASE+'web/results.json',browser['scope'])]:
  r['validation'][gate].append({'path':path,'result':'partial_pass','scope':scope})
status['next_work']=['USER PRIORITY: regular enemies and dependencies first; additional boss/Hornfel work deferred.','Mulligan16.0/16.1/16.2now have source-based body/death rules and seeded placement. Continue remaining regular Mulligan/Hive-family variants and roster.','Close explicit source movement/counter/Troll timing and full six-gate gaps; no partial controller or registry entry counts as a complete port.']
status['priority_override']['current_focus']=['Regular enemies and required dependencies','Remaining ordinary Mulligan/Hive family and regular roster before more bosses']
status['latest_source_review']=BASE+'source-review.json'
status['checkpoint'].update(mechanics_fingerprint=fingerprint,report=BASE+'checkpoint.json',native_tests=68,enemy_bomb_profiles=6,direct_pool_ids=46,enabled_pool_ids=49,wasm_final_build_cases=10,note='Mulligan family source-based collision/proximity/death rules,real Troll Bomb and seeded early-floor placement.68native suites and10WASM cases pass. Original captures inspected. Movement/counter/Troll timing and six-gate acceptance remain open;zero complete ports.')
save('docs/research/isaac-enemy-port-status.json',status)
checked=json.loads(subprocess.check_output(['python3','scripts/isaac-reference/track-enemies.py','--check','--csv'],cwd=ROOT,text=True))
assert checked['reviewed']==136 and checked['complete']==0 and checked['implementations']['in_progress']==92
save(BASE+'checklist-final.json',checked);save('docs/research/isaac-enemy-port-validation.json',checked)
p=ROOT/'docs/isaac_monsters.md';text=p.read_text();marker='Current implementation checkpoint:\n';assert marker in text
text=text.replace(marker,marker+'''
The [Mulligan family checkpoint](reports/isaac-enemy-port/mulligans/checkpoint.json)
replaces the fixed-age trigger with proved grid-collision checks and a 29-frame
windup. Mulligan gets four independent death children; Mulligoon gets diagonal
shots and a real Troll Bomb; Mulliboom uses the native five-frame proximity test
and immediate blast. All have 41.6 HP and harmless body contact. Early-floor
placement expands the pool to 46 direct identities, 49 with replacements.
All 68 native suites and 10 browser cases have passing coverage (nine from the
full run, one focused capture/sampling retry). Original captures are inspected.
Troll Bomb wall-clock fuse, exact navigation/counter/status behavior and full
balance/performance acceptance remain open. These records are partial ports.

''',1);p.write_text(text)
p=OUT/'README.md';text=p.read_text();text+='''
## Validation

All **68 native suites pass** in [CTest](native.xml), including the focused
[family behavior fixture](behavior-final.txt). All **10 browser cases have passing coverage** in
[the WASM report](web/results.json): nine from the full run plus the focused
natural-Mulliboom capture/sampling retry, with the same WASM build and no
browser/GL errors. Two delayed-death visual captures also pass separately. The
[visual review](visual-review.json) records inspected Original-style native and
browser captures and its limits. No controlled benchmark or complete balance
acceptance is claimed. Earlier report artifacts remain hash-verified unchanged.
''';p.write_text(text)
sourcepaths=set(old['source_sha256'])|{'scripts/isaac-reference/analyze-mulligans.py',BASE+'source-review.json',BASE+'extract-metadata.py',BASE+'records.json'}
sourcepaths|={str(p.relative_to(ROOT)) for folder in ['source','animations'] for p in (OUT/folder).rglob('*') if p.is_file()}
save(BASE+'checkpoint.json',{'status':'Partial regular Mulligan family port; full goal active; regular enemies prioritized.','created_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'mechanics_fingerprint':fingerprint,'runtime_definitions':163,'item_definitions':13,'enemy_bomb_profiles':6,'checklist':checked,'native':native,'browser':browser,'visual':visual,'remaining':source['remaining'],'implementation_review':BASE+'implementation-review.json','previous_checkpoint':PREVIOUS,'runtime_sha256':{p:sha(p) for p in sorted(set(old['runtime_sha256'])|set(runtime))},'build_sha256':{p:sha(p) for p in old['build_sha256']},'source_sha256':{p:sha(p) for p in sorted(sourcepaths)},'artifacts_sha256':{str(p.relative_to(ROOT)):sha(str(p.relative_to(ROOT))) for p in OUT.rglob('*') if p.is_file() and p.name!='checkpoint.json'}})
print(json.dumps({'checkpoint':BASE+'checkpoint.json','native_pass':68,'wasm_pass':10,'historical_unchanged':len(history),'complete':0}))
