#!/usr/bin/env python3
"""Persist the bounded ordinary Sub Horf champion checkpoint and current gaps."""
import datetime,hashlib,html,json,re,shlex
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/sub-horf/champions'
def read(p):return json.loads((ROOT/p).read_text())
def write(p,v):p.write_text(json.dumps(v,indent=2)+'\n')
e=html.escape
first=(OUT/'tests.log').read_text();retry=(OUT/'tests-retry.log').read_text();behavior=(OUT/'behavior.log').read_text()
assert first.count('   Passed')==5
assert '100% tests passed, 0 tests failed out of 1' in retry
for token in ['types=26 charm_combinations=52','affiliation_scenarios=52','residents=8 distinct_types=8','PASS Sub Horf']:assert token in behavior,token
traits={p['id']:p['combat'] for p in read('docs/reports/isaac-enemy-port/charger-champions-creatures/summary.json')['champions']}
rows=[]
for line in (ROOT/'assets/mechanics/champions.mechanics').read_text().splitlines():
 t=shlex.split(line,comments=True)
 if t and t[0]=='champion':rows.append(dict(id=int(t[1]),name=t[2],hp_multiplier=float(t[3]),speed_multiplier=float(t[4]),visual_multiplier=float(t[5]),collision_multiplier=float(t[6]),damage_multiplier=float(t[7]),first_source_stage=int(t[8]),combat=traits[int(t[1])],status='combat_enabled_scoped_tests_pass'))
rows.sort(key=lambda r:r['id']);assert [r['id'] for r in rows]==list(range(26))
captures=[]
for name,hp,shots in [('dark-red',22.4,0),('split',0,1),('rainbow',110.4,3)]:
 text=(OUT/(name+'.log')).read_text();line=next(x for x in text.splitlines() if x.startswith('ENEMY_PROBE id=812.0 '))
 assert float(re.search(r' hp=([\d.]+)',line)[1])==hp
 assert int(re.search(r' shots=(\d+)',line)[1])==shots
 img=OUT/(name+'.png');captures.append(dict(name=name,image=img.name,sha256=hashlib.sha256(img.read_bytes()).hexdigest(),probe=line,inspected=True,scope='Isolated Original1440x900/160percent; three representative states, not all26visual/occlusion acceptance.'))
r=dict(date=datetime.datetime.now(datetime.timezone.utc).isoformat(),actor='812.0.0',status='all26combat_variants_enabled_and_scoped_tested',champion_types=rows,
 validation=dict(result='pass',native_suites=6,first_batch_passed=5,failed_suite_rerun_passed=1,logs=['tests.log','tests-retry.log','behavior.log'],stat_charm_scenarios=52,death_affiliation_scenarios=52,natural=dict(seeds=12,residents=8,distinct_types=8,forced_fixture='Replacement and champion chance100percent only in copied test content; production1/60and5percent remain unchanged.',stage_gates='Natural types retain first-source-stage restrictions; debug forcing covers all26.'),native_build='pass',binary_sha256=hashlib.sha256((ROOT/'build/deathward').read_bytes()).hexdigest(),captures=captures,test_history='New Brown destruction assertion initially used a soft blast, which only removes dung hits. Corrected fixture to spent-dynamite demolition, then reran the failed suite successfully. Earlier five regression suites passed; original failed run is retained.',wasm='Skipped by user instruction'),
 checked=['All26HP/size/contact modifiers with ordinary and permanent-Charm affiliation; stationary variants never acquire autonomous walking.','Green/Brown trails require physical movement. Brown droppings break under dynamite without loot.','White immunity releases without softlock; Black/Camouflage reveal behavior; spectral body/own death shot retain room bounds after owner cleanup.','Magenta fires independently at rest and retries under projectile pressure, including already queued shots. Violet/Gray fields and PulsingRed healing work on this body.','DarkRed collapse emits no own death shot/reward, revives, and final finishing pays once.','Every type retains the ordinary final shot; LightBlue/Rainbow add8for9total, without replacing or duplicating the base shot.','PulsingGreen creates two ordinary source-HP copies, retaining functional permanent Charm and safe descendant shots.','LightWhite orbiter releases plus extra fly; Pulsating caps offspring at5; Crown coloring and Skull chained deaths preserve correct per-body rewards and shots.','Orange final-shot coin loss remains after the owner is removed.','Production resident preparation selects seeded champions with stage gates; default tuning unchanged.'],
 fixes=['Enabled ordinary812.0through the shared champion eligibility checks; Tainted812.1remains excluded.','Reactive Green/Brown/Rainbow movement trails no longer accumulate while stationary.','Magenta checks queued shots as well as live projectiles before consuming its extra-shot timer.','Profiled permanently charmed champion offspring receive status runtime so their shots keep allegiance.'],
 adaptations=['Existing HP/size/generic combat definitions are reused; effect strengths, aura forces, delays and movement tuning are DeathWard values rather than exact native champion-engine recovery.','Yellow/Gray/DarkBlue speed modifiers do not manufacture autonomous motion or multiply external SubHorf recoil. This is the local stationary-body policy; exact native special impulse modifiers remain unverified.','Existing one-orbiter LightWhite policy is retained; wiki allows1-2. Global uniform eligible-type selection and ordinary DeathWard loot remain unchanged.'],
 remaining=['Isaac-specific champion pickup rewards and native rarity weighting remain unimplemented/adapted in the shared system.','Real pickup-to-status triggers and full body/build/status interaction matrix remain open.','Exact native champion knockback/status/item exceptions, mixed-room/all-angle visual acceptance, human balance and dense rendered performance remain open.','Tainted Sub Horf812.1is a separate missing actor.'],
 source=['docs/reports/isaac-wiki/monsters-wiki/Champions.html','docs/reports/isaac-wiki/monsters-wiki/pages/Horf.html','reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3/entities2.xml'],full_port_accepted=False)
write(OUT/'status.json',r)
ul=lambda values:'<ul>'+''.join('<li>'+e(v)+'</li>' for v in values)+'</ul>'
body='<p><strong>All26ordinary Sub Horf combat variants are enabled and covered by scoped tests.</strong> Champion-specific loot and exact native rarity are separate remaining work.</p><p>52stat/contact/Charm scenarios and52death-affiliation scenarios cover every type. Six affected native suites pass across the initial batch and corrected-fixture retry. Natural preparation produced8championed SubHorfs of8types across12seeded test runs, respecting stage gates. Test-only100percent chances make rare actors reachable; production tuning is unchanged.</p><p><a href="status.json">Detailed checkpoint</a> · <a href="behavior.log">Behavior checks</a> · <a href="tests.log">Initial regressions</a> · <a href="tests-retry.log">Corrected-fixture retry</a> · <a href="../index.html">Ordinary Sub Horf</a></p><h2>Combat types</h2><div class="table"><table><tr><th>ID</th><th>Champion</th><th>HP multiplier</th><th>First source stage</th><th>Combat behavior</th></tr>'
for x in rows:body+='<tr><td>'+str(x['id'])+'</td><td>'+e(x['name'])+'</td><td>'+str(x['hp_multiplier'])+'</td><td>'+str(x['first_source_stage'])+'</td><td>'+e(x['combat'])+'</td></tr>'
body+='</table></div><h2>Checked interactions</h2>'+ul(r['checked'])+'<h2>Fixes</h2>'+ul(r['fixes'])
for c in captures:body+='<h2>'+e(c['name'].replace('-',' ').title())+'</h2><img src="'+c['image']+'" alt="Sub Horf '+e(c['name'])+' native capture">'
body+='<h2>Adaptations</h2>'+ul(r['adaptations'])+'<h2>Still missing</h2>'+ul(r['remaining'])+'<p>These captures and tests do not certify every native interaction or all26visual states. No full-port acceptance promotion.</p>'
(OUT/'index.html').write_text('<!doctype html><html lang="en"><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>Sub Horf champion variants</title><style>body{max-width:1100px;margin:36px auto;padding:0 18px;background:#182024;color:#eee5d7;font:17px/1.6 system-ui}a{color:#8fd5ce}h1,h2{line-height:1.3}li{margin:9px 0}img{width:100%;height:auto}.table{overflow:auto}table{border-collapse:collapse;width:100%}td,th{padding:10px;border:1px solid #596364;text-align:left}</style><h1>Sub Horf:26champion combat variants</h1>'+body+'</html>')
parent=ROOT/'docs/reports/isaac-enemy-port/sub-horf/status.json';p=json.loads(parent.read_text());p['champions']=dict(combat_types=26,status='enabled_and_scoped_tested',evidence='champions/status.json');p['remaining']=[v for v in p['remaining'] if not v.startswith('Sub Horf champion variants are disabled')];p['remaining'].insert(0,r['remaining'][0]);write(parent,p)
p=ROOT/'docs/reports/isaac-enemy-port/interaction-gaps/status.json';g=json.loads(p.read_text());c=next(c for c in g['champion_scope'] if c['ids']==['812.0.0']);c['enabled']=list(range(26));c['not_enabled']=[]
g['gaps'][0]['details']=g['gaps'][0]['details'].replace('Sub Horf currently allows zero champion types; it needs its own review.','Sub Horf now allows all26combat types with per-body scoped tests; its shared special loot/rarity gaps remain separate.')
g['remaining']=[v for v in g['remaining'] if not v.startswith('Sub Horf champion variants are disabled')];g['remaining'].insert(0,r['remaining'][0]);g['combined_checked'].append('Sub Horf all26combat types:52stat/Charm and52death-affiliation scenarios; revival, split offspring, nine-shot death volleys and seeded resident preparation. See sub-horf/champions/status.json.')
# Idempotent rebuilds should not duplicate the checkpoint note.
g['combined_checked']=list(dict.fromkeys(g['combined_checked']));write(p,g)
p=ROOT/'docs/research/isaac-enemy-port-status.json';g=json.loads(p.read_text());a=next(x for x in g['records'] if x['id']=='812.0.0');a['unresolved']=[x for x in a['unresolved'] if not x.startswith('Champion812.0variants remain disabled')]
note='All26champion combat types are enabled with52stat/Charm and52death-affiliation checks. Shared champion-specific loot/rarity, native special impulse exceptions and full acceptance remain open.'
if note not in a['implementation_notes']:a['implementation_notes'].append(note)
for file in ['src/combat/Champions.cpp','src/combat/Monsters.cpp']:
 if file not in a['runtime']:a['runtime'].append(file)
ev=dict(path='docs/reports/isaac-enemy-port/sub-horf/champions/status.json',result='partial_pass',scope='All26combat modifiers,52stat/Charm and52death-affiliation scenarios,12seeded natural-preparation fixtures; three inspected isolated Original captures. Does not include shared native loot/rarity or full visual/balance/performance acceptance.')
a['validation']['behavior']=[x for x in a['validation']['behavior'] if x['path']!=ev['path']]+[ev]
a['validation']['visual_linux']=[x for x in a['validation']['visual_linux'] if x['path']!=ev['path']]+[dict(ev,scope='Three inspected isolated Original1440x900/160percent captures: DarkRed collapse, PulsingGreen two children, Rainbow movement/creep/orbiter. Other angles/types/occlusion remain open.')]
a['contract']['unknowns']=a['contract']['unknowns'].replace('champion variants, ','');write(p,g)
print('PASS:26combat types,104affiliation scenarios,6native suites aggregate,3inspected captures; remaining gaps persisted')
