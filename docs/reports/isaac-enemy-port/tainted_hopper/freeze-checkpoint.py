"""Freeze the partial regular Tainted Hopper slice only after evidence passes."""
import datetime
import gzip
import hashlib
import json
import subprocess
import xml.etree.ElementTree as ET
from pathlib import Path

ROOT=Path(__file__).resolve().parents[4]
BASE='docs/reports/isaac-enemy-port/tainted_hopper/'
OUT=ROOT/BASE
PREVIOUS='docs/reports/isaac-enemy-port/eggy/checkpoint.json'
def load(p):return json.loads((ROOT/p).read_text())
def save(p,d):(ROOT/p).write_text(json.dumps(d,indent=2,ensure_ascii=False)+'\n')
def sha(p):
    h=hashlib.sha256()
    with (ROOT/p).open('rb') as f:
        for chunk in iter(lambda:f.read(4*1024*1024),b''):h.update(chunk)
    return h.hexdigest()

assert not (OUT/'checkpoint.json').exists(),'Already frozen'
cases=ET.parse(OUT/'native-final.xml').getroot().findall('.//testcase')
assert len(cases)==81
assert all(all(c.find(t) is None for t in ['error','failure','skipped']) for c in cases)
assert 'PASS Tainted Hopper' in (OUT/'native-flight.txt').read_text()
web=load(BASE+'web-final/results.json')
assert len(web['checks'])==5 and not web['errors']
assert {r['case'] for r in web['checks']}=={'isolated','cover','river','death','resident'}
assert all(r['pass'] for r in web['checks'])
visual=load(BASE+'visual-review.json')
assert len(visual['final_images'])>=9 and all(r['inspected'] for r in visual['final_images'])
captures=load(BASE+'native-captures.json')
assert len(captures)==4 and all(r['exit_code']==0 for r in captures)
history=load(BASE+'historical-integrity.json')['files'];assert len(history)==6662
for path,digest in history.items():assert sha(path)==digest,path
for path,digest in load(BASE+'preflight.json')['source_sha256'].items():assert sha(path)==digest,path
for script in ['analyze-tainted-hopper.py','analyze-tainted-hopper-flight-armor.py']:
    subprocess.run(['python3','scripts/isaac-reference/'+script,'--check'],cwd=ROOT,check=True,capture_output=True)
for name in ['index.js','index.wasm','index.data']:
    p=ROOT/'build-web'/name;assert gzip.decompress(p.with_suffix(p.suffix+'.gz').read_bytes())==p.read_bytes()
fingerprint='d6db0034dfe180f3'
current=subprocess.check_output(['build/deathward_check_mechanics'],cwd=ROOT,text=True)
assert 'fingerprint '+fingerprint in current
assert 'direct_pool_id_count=75' in (OUT/'pool-audit.txt').read_text()
native=dict(passed=81,failed=0,report=BASE+'native-final.xml',passing_suites=sorted(c.attrib['name'] for c in cases),
    behavior=BASE+'native-flight.txt',note='Fresh full81/81 regression run after final runtime changes.')
browser=dict(cases=5,report=BASE+'web-final/results.json',scope=web['scope'],errors=[],
    build=BASE+'build-wasm.txt',compression=BASE+'web-compression.txt')
scope=load(BASE+'implementation-scope.json');remaining=scope['remaining'];adaptations=scope['adaptations']
review=scope|dict(source_preflight=BASE+'source-review.md',flight_and_armor_review=BASE+'flight-armor-review.md',
    native=native,browser=browser,visual=visual)
save(BASE+'implementation-review.json',review)
old=load(PREVIOUS)
runtime=sorted({p for p,h in old['runtime_sha256'].items() if sha(p)!=h}|{
    'assets/mechanics/tainted_hopper.mechanics','tests/tainted_hopper_tests.cpp','web/tainted-hopper-test.cjs'})
status=load('docs/research/isaac-enemy-port-status.json');save(BASE+'status-before.json',status)
r=next(r for r in status['records'] if r['id']=='29.3.0')
assert r['implementation']=='existing_unverified' and r['review']=='pending'
r.update(review='reviewed',disposition='ordinary',implementation='in_progress')
r['runtime']=list(dict.fromkeys(r['runtime']+runtime))
r['evidence'] += [dict(source=BASE+'source-review.md',supports='Installed ordinary target-hop and four-stage Land sequence, projectile modes and source animation metadata.'),
    dict(source=BASE+'flight-armor-review.md',supports='Physical ring damping and native armor research. Armor runtime remains explicitly absent.')]
r['contract']=dict(
    movement='Shared source destination inertia.7*(velocity+force), zero random bonus, physical hops with safe actual3D landings.',
    targeting='Strict130native-unit acquisition, wander95; native clamp/grid selection with local legal-unsnapped fallback. No ordinary sight or velocity prediction requirement.',
    attacks='Source4/6/8/12 world-aligned landing rings at speeds8/10/8/10 x3,30shots per cycle; damped falling flight. Contact base20. No invented creep, area blast, demolition or offspring.',
    vulnerability='Source80HP x3.2=256. Adaptive shieldStrength30 armor NOT implemented; do not mistake HP conversion for vulnerability parity.',
    phases='Idle26; Hop/Hop2 duration23,Jump4,Land17 at30Hz. First three Land events chain atJump4 on legal ground; fourth returns to normal recovery. Alternating visual twist.',
    offspring='None in the reviewed normal hostile branch.',
    completion='One ordinary death/loot. Un-emitted queued rings cancel; emitted physical shots survive and gate local clear until impact/expiry. Whole-ring capacity retention; phase preserved through inactive rooms.',
    adaptations='; '.join(adaptations),unknowns='; '.join(remaining))
r['placement']=[dict(kind='weighted_specialist',bands=[3],approved=True,evidence=BASE+'source-review.md',
    note='Ascent-only source habitat adapted to rare late-expedition pursuit specialist weight1/cost6/cap1. Natural Rourke seed22/floor7/room1,zero-based.')]
r['unresolved']=remaining
for gate,path,description in [
    ('behavior','native-flight.txt','Partial normal hostile movement, exact rings and flight recurrence, capacity/lifecycle/stun/suspension/external validation. Adaptive armor and special branches remain open.'),
    ('reachability','web-final/results.json','Actual late-floor resident with dedicated physical hops and full ring cycle.'),
    ('visual_linux','native-fourth.png',visual['scope']),
    ('visual_wasm','web-final/resident-resident.png',visual['scope'])]:
    r['validation'][gate].append(dict(path=BASE+path,result='partial_pass',scope=description))
status['next_work']=['USER PRIORITY: regular enemies and required offspring before further bosses.',
    'Implement shared Tainted regular-enemy adaptive armor from preserved installed-source evidence; resolve batching, bypasses and remaining source/version questions.',
    'Continue Leaper variants and normal/Flaming Hopper source fidelity.',
    'Close regular-family behavior, placement, visual, balance and performance gaps.',*remaining]
status['latest_source_review']=BASE+'flight-armor-review.md'
status['checkpoint'].update(mechanics_fingerprint=fingerprint,report=BASE+'checkpoint.json',native_tests=81,
    runtime_definitions=177,reviewed_records=166,partial_implementations=124,direct_pool_ids=75,enabled_pool_ids=79,
    wasm_final_build_cases=5,note='Partial Tainted Hopper four-stage physical attack port;81/81 fresh native suites,5production WASM cases. Armor and six-gate acceptance remain open. Regular enemies first;zero complete ports.')
save('docs/research/isaac-enemy-port-status.json',status)
checked=json.loads(subprocess.check_output(['python3','scripts/isaac-reference/track-enemies.py','--check','--csv'],cwd=ROOT,text=True))
assert checked['reviewed']==166 and checked['complete']==0
assert checked['implementations']==dict(in_progress=124,existing_unverified=55,missing=462,excluded=12)
save(BASE+'checklist-final.json',checked);save('docs/research/isaac-enemy-port-validation.json',checked)
p=ROOT/'docs/isaac_monsters.md';text=p.read_text();marker='Current implementation checkpoint:\n';assert marker in text
p.write_text(text.replace(marker,marker+'''
The [Tainted Hopper checkpoint](reports/isaac-enemy-port/tainted_hopper/checkpoint.json)
adds a dedicated four-hop sequence with4/6/8/12 physical landing shots and rare
late-floor placement. Fingerprint `d6db0034dfe180f3`: **177 definitions,
166 reviewed,124 in progress,55 existing-unverified,462 missing,12 excluded;
zero complete ports**.75 direct ordinary pool identities,79 including replacements.
A fresh81/81 Linux suite run and five production WASM cases pass. The
[report](reports/isaac-enemy-port/tainted_hopper/README.md) distinguishes source
rules,3D adaptations and remaining work. **Adaptive armor is still absent**;
its preserved native formula is a shared regular-enemy follow-up. Regular enemies
and required offspring stay ahead of bosses. Earlier checkpoints are historical.

''',1))
sources=set(old['source_sha256'])|set(load(BASE+'preflight.json')['source_sha256'])|{
    'scripts/isaac-reference/analyze-tainted-hopper-flight-armor.py',BASE+'flight-armor-review.md'}
sources|={str(p.relative_to(ROOT)) for p in (OUT/'flight-armor-source').rglob('*') if p.is_file()}
builds=set(old['build_sha256'])|{'build/deathward_tainted_hopper_tests'}
save(BASE+'checkpoint.json',dict(status='Partial regular Tainted Hopper port; full goal active.',
    created_utc=datetime.datetime.now(datetime.timezone.utc).isoformat(),mechanics_fingerprint=fingerprint,
    runtime_definitions=177,item_definitions=13,enemy_bomb_profiles=6,checklist=checked,
    native=native,browser=browser,visual=visual,remaining=remaining,previous_checkpoint=PREVIOUS,
    implementation_review=BASE+'implementation-review.json',historical_artifacts_preserved=len(history),
    runtime_sha256={p:sha(p) for p in sorted(set(old['runtime_sha256'])|set(runtime))},
    build_sha256={p:sha(p) for p in sorted(builds)},source_sha256={p:sha(p) for p in sorted(sources)},
    artifacts_sha256={str(p.relative_to(ROOT)):sha(str(p.relative_to(ROOT))) for p in OUT.rglob('*') if p.is_file() and p.name!='checkpoint.json'}))
print(json.dumps(dict(checkpoint=BASE+'checkpoint.json',native_pass=81,wasm_pass=5,historical_unchanged=len(history),complete=0)))
