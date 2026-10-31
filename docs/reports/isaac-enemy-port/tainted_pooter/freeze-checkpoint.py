"""Freeze a validated slice once; never rewrite historical checkpoints."""
import datetime,hashlib,json,subprocess,xml.etree.ElementTree as ET
from pathlib import Path
ROOT=Path(__file__).resolve().parents[4]
BASE='docs/reports/isaac-enemy-port/tainted_pooter/'
OUT=ROOT/BASE
PREVIOUS='docs/reports/isaac-enemy-port/attack_fly/checkpoint.json'
def load(p):return json.loads((ROOT/p).read_text())
def save(p,v):(ROOT/p).write_text(json.dumps(v,indent=2,ensure_ascii=False)+'\n')
def sha(p):
    h=hashlib.sha256()
    with (ROOT/p).open('rb') as f:
        for block in iter(lambda:f.read(4*1024*1024),b''):h.update(block)
    return h.hexdigest()
assert not (OUT/'checkpoint.json').exists()
xml=ET.parse(OUT/'native.xml').getroot()
assert xml.attrib['tests']=='66' and xml.attrib['failures']=='0'
assert 'PASS Tainted Pooter and reusable impact splitting' in (OUT/'behavior-final.txt').read_text()
web=load(BASE+'web/results.json');assert len(web['checks'])==5 and not web['errors']
assert all(c['quad'] and c['backPair'] for c in web['checks'] if c['case']!='tainted-skatole')
fingerprint=(OUT/'mechanics.txt').read_text().split('fingerprint ')[1].split()[0];assert fingerprint=='b0d8066e316c078e'
subprocess.run(['python3','scripts/isaac-reference/analyze-tainted-pooter.py','--check'],cwd=ROOT,check=True,capture_output=True)
history=load(BASE+'historical-integrity.json')['files']
for path,digest in history.items():assert sha(path)==digest,path
old=load(PREVIOUS);source=load(BASE+'source-review.json')
native={'covered_suites':66,'passed':66,'failed':0,'report':BASE+'native.xml','behavior':BASE+'behavior-final.txt',
 'scope':'Full66-suite final native run; focused Tainted and shared buzzing suites also passed. A pre-validation timing failure exposed float residuals postponing the63-frame delay by one acquisition interval; fixed before both final builds. The legacy monster test was corrected to reject timeout splitting.',
 'tests':'Source health, harmless contact, Shoot6/Attack14/delay63, current-target four-vector volley without normalization, atomic capacities, Skatole, windup death, released roots surviving owner death, wall/player/god-mode impact, exact backward pair/speed/size/attribution, no recursion/timeout/cancellation splitting, retained carrier retry and thin-wall clipping, live bounce separation, invalid config, immutable reload snapshots and ordinary-pool exclusion.'}
browser={'cases':5,'report':BASE+'web/results.json','errors':[],
 'scope':'Final WASM production mechanics: ordinary volley, cover, river, Skatole and death. Asserts source-scaledHP, real movement, root coefficients/radii/damage, physical pitch and backward child angle/size/speed. No dedicated natural route is claimed.',
 'note':'Initial7-second river observation was too short for the slow buzzing body. Extending that case to a30-second maximum allowed the production actor to cross and return to land by frame475, then stopped early. Initial log/results preserved; no runtime change for this observation-window correction.'}
visual={'result':'Inspected Original low-poly body, four-shot spacing and airborne shadow in native/browser captures, native scene after cover crossing and browser flight over deep water. No all-angle occlusion or performance acceptance.',
 'linux':[BASE+'native-volley.png',BASE+'native-cover.png'],
 'wasm':[BASE+'web/tainted-volley.png',BASE+'browser-river.png']}
runtime=['assets/mechanics/buzz_flies.mechanics','assets/mechanics/monsters.mechanics','src/content/Mechanics.hpp','src/content/Mechanics.cpp',
 'src/combat/Simulation.hpp','src/combat/Simulation.cpp','src/combat/BuzzFlies.cpp','src/combat/ProjectileMotion.cpp','src/main.cpp',
 'tests/tainted_pooter_tests.cpp','tests/monster_tests.cpp','web/tainted-pooter-test.cjs','CMakeLists.txt','README.md']
save(BASE+'implementation-review.json',{'scope':source['scope'],'mechanics_fingerprint':fingerprint,
 'changes':['Replace generic Tainted Pooter chase/spread with configured shared buzz, source health/timing and unnormalized four-vector volley.',
 'Reusable external impact-only backward pair with child-size/speed/offset, nonrecursive ownership and immutable birth snapshot.',
 'Atomically reserve roots/children; retry stopped impacts under capacity pressure; clip backward spawn against scenery.',
 'Retain dedicated placement requirement; no ordinary-stage expansion or change to player defaults, Original visuals or expedition structure.'],
 'adaptations':source['adaptations'],'native':native,'browser':browser,'visual':visual,'remaining':source['remaining']})
status=load('docs/research/isaac-enemy-port-status.json')
r=next(r for r in status['records'] if r['id']=='14.2.0');r['implementation']='in_progress'
r['runtime']=list(dict.fromkeys(r['runtime']+runtime))
r['evidence'].append({'source':BASE+'source-review.json','supports':'Installed variant2 delay63, mode4 coefficients/parameters, shared Skatole branch, BACKSPLIT dead processing and player collision, extracted30FPS Attack14/Shoot6 metadata; explicit3D adaptations.'})
r['contract'].update(movement='Shared30Hz source-based buzzing, cooldown damping and physical3D flight. No old sudden-stop chase.',
 targeting='Sight/range20 on seven-frame checks; current physical player position sampled at Shoot6. Source63-frame delay starts at acquisition; full14-frame recovery.',
 attacks='Four large shots with unnormalized source coefficients(.99,+/-.1668),(.8226,+/-.43956)times21. Radius.308, damage10. Physical terminal impacts emit two backward+/-24degree children speed30/radius.22/damage10/offset1. No split on timeout/cancellation or live bounce.',
 vulnerability='Source75HPx3.2=240; normally damageable airborne body radius.6. No touch damage.',
 phases='No health phases. Native type14 Skatole branch suppresses acquisition and consumes pending Shoot without replay; movement continues. Item remains unpooled.',
 offspring='No actor offspring. Released projectiles preserve source attribution after owner death; smaller child bullets cannot recursively split.',
 completion='One room threat. Windup death cancels pending volley. Whole roots/pairs are capacity-checked; terminal impacts retain one stationary carrier without repeating damage until capacity is available.',
 adaptations='; '.join(source['adaptations']),unknowns='; '.join(source['remaining']))
r['placement']=[{'kind':'dedicated Ascent-equivalent encounter pending','bands':[],'approved':False,
 'note':'Source Ascent-only. Explicitly excluded from all ordinary basic/specialist pools. Debug scenes are not natural reachability.'}]
r['unresolved']=source['remaining'];r.setdefault('implementation_notes',[]).append('Source-based controller and impact splitter now replace the generic placeholder. Dedicated reachability, native height curves and broader acceptance remain unfinished; zero completed-port claim.')
for gate,path,scope in [('behavior',BASE+'behavior-final.txt',native['tests']),
 ('visual_linux',BASE+'native-volley.png',visual['result']),('visual_wasm',BASE+'web/results.json',browser['scope'])]:
 r['validation'][gate].append({'path':path,'result':'partial_pass','scope':scope})
for ident in ['13.0.0','14.0.0','14.1.0','18.0.0']:
 r=next(r for r in status['records'] if r['id']==ident)
 r.setdefault('implementation_notes',[]).append('The later tainted_pooter checkpoint supplies14.2source buzzing/volley and impact-only backward splitting, plus its native type14Skatole suppression. Earlier notes saying its old controller is still active are superseded. Dedicated route, height curve and complete item/status acceptance remain pending.')
status['next_work']=['USER PRIORITY: regular enemies and required dependencies first; further boss/Hornfel work deferred.',
 'Tainted Pooter source-based buzzing/volley and reusable backward impact splitting now have native/browser evidence. Continue remaining regular fly families and their required dependencies.',
 'Keep14.2out of ordinary pools until its source-appropriate dedicated encounter is implemented. Full item/status/height integration and six acceptance gates remain open; placeholders are not complete ports.']
status['priority_override']['current_focus']=['Regular enemies and required dependencies','Remaining ordinary fly-family controllers and the rest of the regular roster; Skatole remains unpooled until all required reactions are implemented']
status['latest_source_review']=BASE+'source-review.json'
status['checkpoint'].update(mechanics_fingerprint=fingerprint,report=BASE+'checkpoint.json',native_tests=66,partial_implementations=92,
 direct_pool_ids=43,enabled_pool_ids=44,wasm_final_build_cases=5,
 note='Tainted Pooter source-based buzzing/health/four-shot volley, impact-only backward children and external immutable config.66native suites and5WASM cases pass. Original Linux/browser views inspected. Dedicated Ascent route/height curves pending; zero certified complete ports.')
save('docs/research/isaac-enemy-port-status.json',status)
checked=json.loads(subprocess.check_output(['python3','scripts/isaac-reference/track-enemies.py','--check','--csv'],cwd=ROOT,text=True))
assert checked['reviewed']==136 and checked['complete']==0 and checked['implementations']['in_progress']==92
save(BASE+'checklist-final.json',checked);save('docs/research/isaac-enemy-port-validation.json',checked)
p=ROOT/'docs/isaac_monsters.md';text=p.read_text();marker='Current implementation checkpoint:\n';assert marker in text
text=text.replace(marker,'''Current implementation checkpoint:

The [Tainted Pooter checkpoint](reports/isaac-enemy-port/tainted_pooter/checkpoint.json)
replaces its generic chase/spread with source-based buzzing, 240 HP,
Attack14/Shoot6/delay63, and a four-shot volley retaining the native outer-shot
slowdown. Physical terminal impacts create two smaller backward shots at ±24°.
Timeouts and cancellation do not split; released shots survive owner death.
External profiles and live projectile snapshots preserve reload isolation.

Fingerprint `b0d8066e316c078e`: **163 monster definitions, 13 item definitions,
136 reviewed, 92 in progress, 73 existing unverified, 476 missing, 12 excluded,
zero complete**. **All 66 native suites and five WASM cases pass**. Original
Linux/browser views were inspected. The 43 directly weighted pool identities
plus conditional I. Blob are unchanged. Tainted Pooter's dedicated
Ascent-equivalent route and native height curves remain pending. Regular enemies
remain first; further boss work stays deferred. See the
[readable report](reports/isaac-enemy-port/tainted_pooter/README.md).

The preceding Attack Fly checkpoint:
''',1);p.write_text(text)
p=OUT/'README.md';text=p.read_text();marker='Validation results and immutable build/runtime/evidence hashes are added here\nwhen the current Linux and WASM checks finish.';assert marker in text
text=text.replace(marker,'''All **66 native CTest suites pass** in the [final run](native.xml).
The [focused behavior log](behavior-final.txt) covers timing, the real volley,
owner death, physical impacts, capacity retry, thin-wall clipping and immutable
reloads; [shared buzzing regressions](buzz-regression.txt) also pass.
The timing test exposed a float residual that delayed reacquisition by one
seven-frame interval; this was fixed before the final builds. The old monster
fixture was corrected to reject splitting on safety timeout.

All **five WASM cases pass** with no browser/GL errors in the
[final browser report](web/results.json). They use production mechanics and
cover volley coefficients, physical size/pitch, backward splitting, cover,
river, Skatole and death. The initial seven-second river observation ended too
soon; the extended observation saw the slow actor return to land at frame 475.
The [initial evidence](web-initial-run.txt) is retained. No runtime change was
needed for that observation-window correction.

[Linux volley](native-volley.png), [Linux scene after cover crossing](native-cover.png),
[browser volley](web/tainted-volley.png) and [browser river flight](browser-river.png)
were inspected. Displayed FPS is not a controlled benchmark.
The [checkpoint](checkpoint.json) freezes the exact runtime, build and evidence
hashes. All '''+f'{len(history):,}'+''' previously recorded report artifacts checked remain unchanged.''');p.write_text(text)
sourcepaths=set(old['source_sha256'])|{'scripts/isaac-reference/analyze-tainted-pooter.py',BASE+'source-review.json',BASE+'extract-metadata.py',BASE+'wiki-source.json',BASE+'pooter-wiki.wikitext',BASE+'projectile-flags.source.json',BASE+'projectile-flags.html'}
sourcepaths|={str(p.relative_to(ROOT)) for folder in ['source','animations'] for p in (OUT/folder).rglob('*') if p.is_file()}
save(BASE+'checkpoint.json',{'status':'Partial regular Tainted Pooter port; full goal active; regular enemies prioritized.',
 'created_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'mechanics_fingerprint':fingerprint,
 'runtime_definitions':163,'item_definitions':13,'enemy_bomb_profiles':5,'checklist':checked,
 'native':native,'browser':browser,'visual':visual,'remaining':source['remaining'],
 'implementation_review':BASE+'implementation-review.json','previous_checkpoint':PREVIOUS,
 'runtime_sha256':{p:sha(p) for p in sorted(set(old['runtime_sha256'])|set(runtime))},
 'build_sha256':{p:sha(p) for p in old['build_sha256']},
 'source_sha256':{p:sha(p) for p in sorted(sourcepaths)},
 'artifacts_sha256':{str(p.relative_to(ROOT)):sha(str(p.relative_to(ROOT))) for p in OUT.rglob('*') if p.is_file() and p.name!='checkpoint.json'}})
print(json.dumps({'checkpoint':BASE+'checkpoint.json','native_pass':66,'wasm_pass':5,'historical_unchanged':len(history),'complete':0}))
