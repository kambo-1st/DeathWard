#!/usr/bin/env python3
"""Refresh scoped Sub Horf evidence and the explicit interaction backlog HTML."""
import hashlib,html,json,re
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/sub-horf'
e=html.escape
style='body{max-width:1100px;margin:36px auto;padding:0 18px;background:#182024;color:#eee5d7;font:17px/1.6 system-ui}a{color:#8fd5ce}h1,h2{line-height:1.3}li{margin:9px 0}img{width:100%;height:auto}table{width:100%;border-collapse:collapse}td,th{border:1px solid #596364;padding:10px;text-align:left}.table{overflow:auto}code{overflow-wrap:anywhere}'
def ul(values):return '<ul>'+''.join('<li>'+e(v)+'</li>' for v in values)+'</ul>'
def page(title,body):return '<!doctype html><html lang="en"><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>'+e(title)+'</title><style>'+style+'</style><h1>'+e(title)+'</h1>'+body+'</html>'
def write(p,obj):p.write_text(json.dumps(obj,indent=2)+'\n')
r=json.loads((OUT/'status.json').read_text())
assert '100% tests passed, 0 tests failed out of 6' in (OUT/'tests.log').read_text()
r['validation']['captures']=[]
for name,hp,shots in [('idle',44.8,0),('reactive',20.8,2),('combined',20.8,0)]:
 log=(OUT/(name+'.log')).read_text();line=next(v for v in log.splitlines() if v.startswith('ENEMY_PROBE id=812.0 '))
 assert float(re.search(r' hp=([\d.]+)',line)[1])==hp
 assert int(re.search(r' shots=(\d+)',line)[1])==shots
 image=OUT/(name+'.png');assert image.is_file()
 r['validation']['captures'].append(dict(image=image.name,sha256=hashlib.sha256(image.read_bytes()).hexdigest(),probe=line,inspected=True,scope='Isolated Original1440x900/160percent; confirms visible body and post-hit displacement. Mixed-room, all-angle readability and performance not accepted.'))
r['validation']['binary_sha256']=hashlib.sha256((ROOT/'build/deathward').read_bytes()).hexdigest()
write(OUT/'status.json',r)
body='<p><strong>Ordinary812.0implemented; exact1-in-60Horf replacement enabled. Full acceptance remains open.</strong></p><p>14sourceHP ×3.2 =44.8before the shared regular health multiplier. Tainted812.1is a separate missing actor.</p><h2>Implemented behavior</h2>'+ul(r['behavior'])+'<h2>Combined effects checked</h2>'+ul(r['combined_checked'])+'<p>Six affected native suites pass. The seeded fixture found6substitutions among346Horf slots across4000room plans, and spawned the target actor. This is controlled evidence, not full expedition balance or native binary parity.</p><p><a href="tests.log">Test results</a> · <a href="behavior.log">Detailed behavior checks</a> · <a href="source/manifest.json">Native evidence</a> · <a href="../horf_fly/replacement-review/index.html">Spawn conditions</a></p>'
if r.get('champions'):body+='<h2>Champion variants</h2><p>All26combat types are enabled with scoped body-specific checks. <a href="champions/index.html">Champion checkpoint, tests and native captures</a>.</p>'
for name in ['idle','reactive','combined']:body+='<h2>'+name.title()+'</h2><img src="'+name+'.png" alt="Sub Horf '+name+' native capture">'
body+='<h2>Explicit adaptations</h2>'+ul(r['adaptations'])+'<h2>Still missing</h2>'+ul(r['remaining'])+'<p><a href="status.json">Machine-readable checkpoint</a> · <a href="../interaction-gaps/index.html">Remaining champion/item interactions</a></p>'
(OUT/'index.html').write_text(page('Sub Horf implementation and combined-effect checks',body))
p=ROOT/'docs/reports/isaac-enemy-port/interaction-gaps';g=json.loads((p/'status.json').read_text())
body='<p>'+e(g['context'])+'</p><h2>Checked in this checkpoint</h2>'+ul(g['combined_checked'])+'<p><a href="../sub-horf/index.html">Sub Horf implementation, native captures and test evidence</a></p><h2>Champion combinations still excluded</h2><div class="table"><table><tr><th>Actor IDs</th><th>Enabled</th><th>Still excluded</th></tr>'
for c in g['champion_scope']:body+='<tr><td>'+e(', '.join(c['ids']))+'</td><td>'+str(len(c['enabled']))+'/26</td><td>'+e(', '.join(t['name']+' ('+str(t['id'])+')' for t in sorted(c['not_enabled'],key=lambda t:t['id'])))+'</td></tr>'
body+='</table></div>'
for gap in g['gaps']:body+='<h2>'+e(gap['area'])+'</h2><p><strong>'+e(gap['state'])+'</strong> — '+e(gap['details'])+'</p>'+ul(gap.get('examples',[]))
body+='<h2>Still missing</h2>'+ul(g['remaining'])+'<p><a href="status.json">Detailed backlog and code references</a></p>'
(p/'index.html').write_text(page('Remaining champion and item interactions',body))
status_path=ROOT/'docs/research/isaac-enemy-port-status.json';status=json.loads(status_path.read_text());actor=next(x for x in status['records'] if x['id']=='812.0.0')
actor['validation']['visual_linux']=[v for v in actor['validation']['visual_linux'] if v['path']!='docs/reports/isaac-enemy-port/sub-horf/status.json']+[dict(path='docs/reports/isaac-enemy-port/sub-horf/status.json',result='partial_pass',scope='Three inspected Original1440x900/160percent native captures: idle, after real player shot, and Freeze+Poison+temporary Charm; confirms render and reactive displacement. Mixed-room/all-angle/animation/balance/performance acceptance remains open.')]
write(status_path,status)
print('PASS: six native suites and three inspected native captures; Sub Horf and interaction backlog reports refreshed')
