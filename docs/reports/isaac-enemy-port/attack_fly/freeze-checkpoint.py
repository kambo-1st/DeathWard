"""Freeze this completed validation slice once; never rewrite an existing checkpoint."""
import datetime, hashlib, json, subprocess, xml.etree.ElementTree as ET
from pathlib import Path

ROOT=Path(__file__).resolve().parents[4]
BASE='docs/reports/isaac-enemy-port/attack_fly/'
OUT=ROOT/BASE
PREVIOUS='docs/reports/isaac-enemy-port/super_pooter/checkpoint.json'
def load(p):return json.loads((ROOT/p).read_text())
def save(p,v):(ROOT/p).write_text(json.dumps(v,indent=2,ensure_ascii=False)+'\n')
def sha(p):
    h=hashlib.sha256()
    with (ROOT/p).open('rb') as f:
        for block in iter(lambda:f.read(4*1024*1024),b''):h.update(block)
    return h.hexdigest()

assert not (OUT/'checkpoint.json').exists()
xml=ET.parse(OUT/'native.xml').getroot();fixed=ET.parse(OUT/'fixtures-final.xml').getroot()
assert xml.attrib['tests']=='65' and xml.attrib['failures']=='2'
assert {t.attrib['name'] for t in xml if t.find('failure') is not None}=={'mechanics_content','monster_formations'}
assert fixed.attrib['tests']=='2' and fixed.attrib['failures']=='0'
assert {t.attrib['name'] for t in fixed}=={'mechanics_content','monster_formations'}
assert 'PASS Attack Fly' in (OUT/'behavior-final.txt').read_text()
web=load(BASE+'web/results.json');assert len(web['checks'])==7 and not web['errors']
fingerprint=(OUT/'mechanics.txt').read_text().split('fingerprint ')[1].split()[0]
assert fingerprint=='bef0b7c155852203'
subprocess.run(['python3','scripts/isaac-reference/analyze-attack-fly.py','--check'],cwd=ROOT,check=True,capture_output=True)
history=load(BASE+'historical-integrity.json')['files']
for path,digest in history.items():assert sha(path)==digest,path
old=load(PREVIOUS);source=load(BASE+'source-review.json')
native={'covered_suites':65,'passed':65,'failed':0,'initial_report':BASE+'native.xml','corrected_test_report':BASE+'fixtures-final.xml','behavior':BASE+'behavior-final.txt',
    'scope':'Full65-suite run passed63. Two outdated fixtures were corrected: quarter-health offspring now expect4HP from16rather than8from32; Ring Fly reachability samples32seeds instead of requiring one fixed seed to retain its previous weighted selection. Both complete affected suites were rebuilt/rerun successfully. Runtime was unchanged; no second full65-suite run is claimed.',
    'tests':'Attack Fly source health, normalized anisotropic pursuit and cached target, ordinary contact, same-actor HP-clamped Skatole morph, pre-morph contact suppression, real live/death Hive spawn routes, live-child friction/contact expiry including god mode and parent removal, harmless converted live child, full-queue retry, no summoned money, invalid data/reload snapshots, all-four-band natural placement; existing buzzing/flight regressions.'}
browser={'cases':7,'report':BASE+'web/results.json','errors':[],
    'scope':'Final WASM build: ordinary pursuit, physical rock crossing, deep-river crossing and return to land, healthy and damaged Skatole morphs, one final death, natural seed0/floor0/room2 resident.',
    'note':'No production-data overrides. Browser morph tests follow the same entity, not the requested debug tuple. Isolated smoke resets initial cooldown. Natural case keeps real generated residents. These cases do not certify full balance or rendered performance.'}
visual={'result':'Inspected Original low-poly Attack Fly, flight elevation/shadow, actual crate crossing in browser and real seeded room in Linux/browser. Native cover capture is after crossing. No broad all-angle occlusion acceptance.',
    'linux':[BASE+'native-cover.png',BASE+'native-resident.png'],
    'wasm':[BASE+'web/attack-cover.png',BASE+'web/natural-attack.png']}
runtime=['assets/mechanics/buzz_flies.mechanics','assets/mechanics/monsters.mechanics','src/content/Mechanics.hpp',
    'src/content/Mechanics.cpp','src/combat/Simulation.hpp','src/combat/Monsters.cpp','src/combat/BuzzFlies.cpp',
    'tests/buzz_fly_tests.cpp','tests/mechanics_tests.cpp','tests/formation_tests.cpp','web/attack-fly-test.cjs']
save(BASE+'implementation-review.json',{'scope':source['scope'],'mechanics_fingerprint':fingerprint,
    'changes':['Replace generic ordinary Attack Fly chase with cached source-based pursuit, jitter and source HP.',
        'External item morph clamps HP in place and preserves ownership/reward identity.',
        'External live Hive contact policy differs from death offspring, including contact friction and bounded expiry.',
        'Sparse pursuit placement across four stage bands; retain player defaults, Original visuals and expedition structure.'],
    'adaptations':source['adaptations'],'native':native,'browser':browser,'visual':visual,'remaining':source['remaining']})
status=load('docs/research/isaac-enemy-port-status.json')
r=next(r for r in status['records'] if r['id']=='18.0.0')
r['implementation']='in_progress';r['runtime']=list(dict.fromkeys(r['runtime']+runtime))
r['evidence'].append({'source':BASE+'source-review.json','supports':'Installed ordinary pursuit force/target cadence, source health/room presence, live Hive contact flag and kill branch, Skatole transformation/current-HP clamp, extracted animation metadata; explicit3D adaptations and pending boss policies.'})
r['contract'].update(
    movement='Shared30Hz buzzing with target refresh3, pursuit impulse2, second planar axis*.5 before normalization, native deadzone25/gain.08/cap1.2 and world scale.1; physical flight and local room limits.',
    targeting='Cached current player position; ordinary non-parent pursuit only. Status/control and boss parent tether remain unfinished.',
    attacks='No projectile. Source5HPx3.2=16. Local contact10before1.25hostile multiplier. Ordinary/death-spawned fly survives contact; live Hive child expires, even on invulnerable contact.',
    vulnerability='Normally damageable physical airborne body. Radius.45 matches harmless Fly for a collision-safe morph.',
    phases='Owned configured Skatole morphs18to13 on the next local source tick, retaining actor, remaining HP up to9.6max, summoner, generation and contact flag. No kill or reward. Item prevents pre-morph contact damage; removing it does not reverse morph.',
    offspring='No death offspring. Live Hive22 summons latch.9pursuit friction/contact expiry. Hive death offspring do not. Boss-specific child policies remain pending.',
    completion='One ordinary room threat. Contact expiry uses bounded execution queue and spent latch; resolves once after capacity returns. Summoned generation suppresses money.',
    adaptations='; '.join(source['adaptations']),unknowns='; '.join(source['remaining']))
r['placement']=[{'kind':'ordinary seeded pursuit specialist','approved':True,'bands':[0,1,2,3],
    'note':'Weight2/cost1/max3per room. Installed authored room evidence supports all four local bands. Native witnesses: seed0/floor0/room2; seed20/floor2/room2; seed7/floor3/room3; seed1/floor6/room9. WASM verifies the first.'}]
r['unresolved']=source['remaining'];r['implementation_notes'].append('Ordinary source-based pursuit, HP and required live-Hive/Skatole interactions now replace the old generic chase. Boss-child/status/full-acceptance work remains pending.')
for gate,path,scope in [('behavior',BASE+'behavior-final.txt',native['tests']),('reachability',BASE+'behavior-final.txt',r['placement'][0]['note']),
    ('visual_linux',BASE+'native-resident.png',visual['result']),('visual_wasm',BASE+'web/results.json',browser['scope'])]:
    r['validation'][gate].append({'path':path,'result':'partial_pass','scope':scope})
hive=next(r for r in status['records'] if r['id']=='22.0.0')
hive.setdefault('implementation_notes',[]).append('The Attack Fly slice now distinguishes live Hive summons (.9pursuit friction/contact expiry) from persistent death offspring. This does not complete Hive movement, spitting cadence, death mixtures or other pending gates.')
hive['validation']['behavior'].append({'path':BASE+'behavior-final.txt','result':'partial_pass','scope':'Actual live-spawn/death-spawn routes produce distinct Attack Fly contact policies. Parent controller otherwise unchanged.'})
hive['evidence'].append({'source':BASE+'source-review.json','supports':'Live Hive spawn assigns native child contact-expiry flag; generic NPC collision invokes Kill.'})
for ident in ['13.0.0','14.0.0','14.1.0']:
    r=next(r for r in status['records'] if r['id']==ident)
    r.setdefault('implementation_notes',[]).append('Later attack_fly checkpoint implements required18to13Skatole conversion and live-summon contact-flag persistence. Earlier pending notes about that specific conversion are superseded; full item behavior remains unfinished and unpooled.')
    for key in ['adaptations','unknowns']:
        r['contract'][key]=r['contract'][key].replace('Tainted Pooter and Attack Fly remain prior partial controllers; implement them and other regular families before further boss work.',
            'Tainted Pooter retains its older controller. Ordinary Attack Fly now has source-based pursuit and required Hive/Skatole reactions; special cases and other regular families remain pending.')
status['next_work']=['USER PRIORITY: regular enemies and required dependencies first; further boss/Hornfel work deferred.',
    'Ordinary Attack Fly pursuit/health, Skatole conversion and live-Hive contact policy now have native/browser evidence. Continue Tainted Pooter and the other unfinished ordinary fly families, then the remaining regular roster.',
    'Complete source behavior, stage reachability and required dependencies per family; placeholders are not complete ports. Full item/status/controlled cases and six acceptance gates remain open.']
status['priority_override']['current_focus']=['Regular enemies and required dependencies','Tainted Pooter and remaining ordinary fly-family controllers; Skatole remains unpooled until its required reactions are implemented']
status['latest_source_review']=BASE+'source-review.json'
status['checkpoint'].update(mechanics_fingerprint=fingerprint,report=BASE+'checkpoint.json',native_tests=65,
    direct_pool_ids=43,enabled_pool_ids=44,wasm_final_build_cases=7,
    note='Attack Fly source-based pursuit/health, live-Hive contact policy and same-actor Skatole morph; sparse four-band placement.65native suites covered after two fixture corrections;7WASM cases pass. Original Linux/browser views inspected. Zero newly certified complete ports.')
save('docs/research/isaac-enemy-port-status.json',status)
checked=json.loads(subprocess.check_output(['python3','scripts/isaac-reference/track-enemies.py','--check','--csv'],cwd=ROOT,text=True))
assert checked['reviewed']==136 and checked['complete']==0 and checked['implementations']['in_progress']==91
save(BASE+'checklist-final.json',checked);save('docs/research/isaac-enemy-port-validation.json',checked)
p=ROOT/'docs/isaac_monsters.md';text=p.read_text();marker='Current implementation checkpoint:\n';assert marker in text
text=text.replace(marker,'''Current implementation checkpoint:

The [Attack Fly checkpoint](reports/isaac-enemy-port/attack_fly/checkpoint.json)
replaces its generic chase with source-based buzzing pursuit: cached target3,
force2, second-axis scaling, native deadzone/force cap, and 16 HP. Live Hive
summons expire on contact; death offspring remain persistent. Skatole now
transforms Attack Fly to Fly in place without healing damage or awarding a kill.
The unfinished item remains outside natural rewards.

Fingerprint `bef0b7c155852203`: **163 monster definitions, 13 item definitions,
136 reviewed, 91 in progress, 74 existing unverified, 476 missing, 12 excluded,
zero complete**. **65 native suites are covered** after two fixture corrections;
**seven WASM cases pass**. Original
Linux/browser captures were inspected. There are 43 directly weighted pool
identities plus conditional I. Blob. Regular enemies remain first; Tainted
Pooter and other unfinished ordinary fly-family controllers are next. Further
boss work stays deferred. See the
[readable report](reports/isaac-enemy-port/attack_fly/README.md).

The preceding Super Pooter checkpoint:
''',1);p.write_text(text)
p=OUT/'README.md';text=p.read_text();marker='## Remaining work\n';assert marker in text
text=text.replace(marker,'''## Validation

All **65 native CTest suites are covered**: the [full run](native.xml) passed 63,
and both corrected [fixture suites](fixtures-final.xml) passed on rerun. One
fixture expected quarter-health children from the old 32 HP definition; it now
checks 4 HP from the corrected 16 HP. Formation reachability now samples 32 seeds
and verifies complete four-member groups instead of relying on one seed's old
weighted selection. Runtime was unchanged; no second full run is claimed.
The [focused behavior log](behavior-final.txt) covers the new controller and
shared Fly/Pooter regressions, including actual contact damage, HP-preserving
conversion, real Hive spawn paths, capacity pressure and source-axis asymmetry.
Existing [physical flight tests](flight-initial.txt) also pass without changing
their cover, river, gate or elevated-combat expectations.

All **seven browser cases pass** with no browser/GL errors in the
[final WASM report](web/results.json): pursuit, crate crossing, river crossing,
healthy and damaged Skatole transformations, one death, and a real generated
resident. [Linux cover scene](native-cover.png),
[Linux generated room](native-resident.png), [browser crate crossing](web/attack-cover.png)
and [browser generated room](web/natural-attack.png) were inspected.
Displayed FPS values are not a controlled performance benchmark.

Natural witnesses span all four bands: seed0/floor0/room2,
seed20/floor2/room2, seed7/floor3/room3 and seed1/floor6/room9. The first is also
verified in WASM. The [checkpoint](checkpoint.json) freezes runtime, source,
build and evidence hashes at mechanics fingerprint `bef0b7c155852203`.
All '''+f'{len(history):,}'+''' previously recorded artifacts checked remain unchanged.

'''+marker,1);p.write_text(text)
sourcepaths=set(old['source_sha256'])|{'scripts/isaac-reference/analyze-attack-fly.py',BASE+'source-review.json',BASE+'extract-metadata.py'}
sourcepaths|={str(p.relative_to(ROOT)) for folder in ['source','animations'] for p in (OUT/folder).rglob('*') if p.is_file()}
save(BASE+'checkpoint.json',{'status':'Partial ordinary Attack Fly port; full goal active; regular enemies prioritized.',
    'created_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'mechanics_fingerprint':fingerprint,
    'runtime_definitions':163,'item_definitions':13,'enemy_bomb_profiles':5,'checklist':checked,
    'native':native,'browser':browser,'visual':visual,'remaining':source['remaining'],
    'implementation_review':BASE+'implementation-review.json','previous_checkpoint':PREVIOUS,
    'runtime_sha256':{p:sha(p) for p in sorted(set(old['runtime_sha256'])|set(runtime))},
    'build_sha256':{p:sha(p) for p in old['build_sha256']},
    'source_sha256':{p:sha(p) for p in sorted(sourcepaths)},
    'artifacts_sha256':{str(p.relative_to(ROOT)):sha(str(p.relative_to(ROOT))) for p in OUT.rglob('*') if p.is_file() and p.name!='checkpoint.json'}})
print(json.dumps({'checkpoint':BASE+'checkpoint.json','native_pass':65,'wasm_pass':7,'historical_unchanged':len(history),'complete':0}))
