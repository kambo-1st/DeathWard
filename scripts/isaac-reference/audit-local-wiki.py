#!/usr/bin/env python3
"""Read the supplied Fandom HTML mirror; audit numbers, never infer AI parity."""
import collections, datetime, hashlib, html, json, re, shlex
from pathlib import Path
from bs4 import BeautifulSoup
ROOT=Path(__file__).resolve().parents[2]
SOURCE=ROOT/'docs/reports/isaac-wiki/monsters-wiki'
OUT=ROOT/'docs/reports/isaac-wiki-verification'
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
def rel(p):return str(p.relative_to(ROOT))
def number(value):
    return float(value) if value is not None and re.fullmatch(r'\d+(?:\.\d+)?',value) else None
def field_element(box,key):
    return box.select_one(f'.pi-data-value[data-source="{key}"]') or box.select_one(f'[data-source="{key}"] .pi-data-value')
def field(box,key):
    el=field_element(box,key)
    return el.get_text(' ',strip=True) if el else None
def edition_number(box,key):
    el=field_element(box,key)
    if el is None:return None
    choices=[]
    ranks={'Rebirth':0,'Afterbirth':1,'Afterbirth+':2,'Repentance':3,'Repentance+':4}
    for slide in el.select('.infobox2-slide') or [el]:
        accepted=True
        for marker in slide.select('[title]'):
            title=marker.get('title','')
            match=re.fullmatch(r'(Added|Removed) in (Rebirth|Afterbirth\+?|Repentance\+?)',title)
            if match:
                rank=ranks[match[2]]
                if (match[1]=='Added' and rank>3) or (match[1]=='Removed' and rank<=3):accepted=False
        v=number(slide.get_text(' ',strip=True))
        if accepted and v is not None:choices.append(v)
    return choices[0] if choices and len(set(choices))==1 else None

manifest=json.loads((SOURCE/'manifest.json').read_text())
boxes=collections.defaultdict(list);files=[]
for p in sorted(SOURCE.rglob('*.html')):
    soup=BeautifulSoup(p.read_text(),'html.parser');files.append(dict(path=rel(p),sha256=sha(p)))
    for box in soup.select('aside.portable-infobox'):
        identity=field(box,'id')
        if not identity or not re.fullmatch(r'\d+\.\d+(?:\.\d+)?',identity):continue
        identity=identity if identity.count('.')==2 else identity+'.0'
        fields={k:field(box,k) for k in ['base hp','stage hp']}
        boxes[identity].append(dict(path=rel(p),base_hp=edition_number(box,'base hp'),stage_hp=edition_number(box,'stage hp'),raw=fields))
monsters={};stage={}
for p in sorted((ROOT/'assets/mechanics').glob('*.mechanics')):
    for line,text in enumerate(p.read_text().splitlines(),1):
        t=shlex.split(text,comments=True)
        if t and t[0]=='monster':monsters[t[1]]=dict(hp=float(t[6]),path=rel(p),line=line)
        if t and t[0]=='stage_health':stage[t[1]]=dict(base=float(t[2]),increment=float(t[3]),scale=float(t[4]),path=rel(p),line=line)
reference=json.loads((ROOT/'docs/research/isaac-mechanics-reference.json').read_text())
installed={r['key']:r.get('xml',{}) for r in reference['records'] if 'key' in r}
status=json.loads((ROOT/'docs/research/isaac-enemy-port-status.json').read_text());rows=[]
for r in status['records']:
    if r['disposition']!='ordinary':continue
    key=r['id'];candidates=boxes.get(key,[])
    pairs={(c['base_hp'],c['stage_hp']) for c in candidates if c['base_hp'] is not None and c['stage_hp'] is not None}
    row=dict(id=key,name=r['name'],snapshot_candidates=candidates,runtime=monsters.get(key),behavior_verified=False)
    if not candidates:row.update(result='no_exact_infobox',reason='No unique exact ID box; this does not mean the article or runtime is missing.')
    elif len(pairs)!=1 or len(pairs)<len({(c['base_hp'],c['stage_hp']) for c in candidates}):
        row.update(result='ambiguous_numeric_data',reason='Missing scalar fields or conflicting boxes/editions; no automatic conclusion.')
    elif key not in monsters:row.update(result='no_runtime_definition',reason='Source box exists but runtime registry definition is absent.')
    else:
        base,increment=next(iter(pairs));row['source_base_hp']=base;row['source_stage_hp']=increment
        xml=installed.get(key,{})
        xml_base=number(xml.get('baseHP'));xml_stage=number(xml.get('stageHP'))
        row['installed_xml_hp']=dict(base=xml_base,stage=xml_stage)
        row['wiki_vs_installed_xml']='agree' if xml_base==base and xml_stage==increment else 'conflict' if xml_base is not None and xml_stage is not None else 'unknown'
        if key in stage:
            p=stage[key];same=abs(base-p['base'])<.001 and abs(increment-p['increment'])<.001
            row.update(result='numeric_match' if same else 'numeric_difference',runtime_stage_profile=p,reason='Source base/stage fields compared in native units; conversion remains explicit.')
        else:
            # This project documents3.2as its HP conversion. With nonzero StageHP,
            # a fixed fallback alone cannot prove progression at later stages.
            same=increment==0 and abs(base*3.2-monsters[key]['hp'])<.001
            row.update(result='numeric_match' if same else 'numeric_difference',reason='No stage profile: compare fixed runtime HP with source base*3.2; any nonzero StageHP needs review.')
    native=installed.get(key,{})
    native_base=number(native.get('baseHP'));native_stage=number(native.get('stageHP'))
    profile=stage.get(key)
    if profile and native_base is not None and native_stage is not None:
        agrees=abs(profile['base']-native_base)<.001 and abs(profile['increment']-native_stage)<.001
        row['baseline_resolution']=dict(version='Repentance1.7.9b',base_hp=native_base,stage_hp=native_stage,
            result='source_profile_matches_installed' if agrees else 'source_profile_difference',
            nominal_conversion=profile['scale'],adaptation=profile['scale']/3.2,
            evidence='docs/research/isaac-mechanics-reference.json',
            limit='Numeric XML metadata resolves this tuple, including subtypes; it does not certify subtype behavior from a shared wiki article.')
    rows.append(row)
expected={r['id'] for r in status['records'] if r['disposition']=='ordinary'}
assert len(rows)==len(expected) and {r['id'] for r in rows}==expected
# Human-reviewed claims: code and existing tests were inspected independently of
# the numeric scan. A wiki-description match never certifies hidden AI timings.
detailed=[
 dict(id='23.0.0',name='Charger',verdict='main_description_matches_with_local_tuning',finding='Idle wandering, cardinal alignment and immediate straight charge are present.',code=['src/combat/Charging.cpp:updateCharge','assets/mechanics/chargers.mechanics:charge23.0.0'],tests=['regressions','natural'],limits='Wander sampling, alignment tolerance, dash speed,1.5second cutoff and recovery are local tuning; the supplied article gives no exact values.'),
 dict(id='23.1.0',name='Drowned Charger',verdict='main_description_matches_with_local_tuning',finding='Shared charging;10percent extra HP; four diagonal death shots. Flooded replacement and reduced-health Hive births have separate configuration.',code=['src/combat/Charging.cpp:flushChargeDeath','assets/mechanics/replacements.mechanics','assets/mechanics/evaders.mechanics','assets/mechanics/deaths.mechanics'],tests=['drowned','regressions'],limits='Projectile timing/speed and authored encounter distribution are not certified by this description. Edition-specific replacement entries must remain distinct.'),
 dict(id='23.2.0',name='Dank Charger',verdict='main_description_matches_with_local_tuning',finding='Faster dash, wall reflections, slowing nondamaging tar and stationary recovery are present.',code=['src/combat/Charging.cpp:updateCharge','assets/mechanics/chargers.mechanics:charge_mode/trail'],tests=['dank'],limits='Trail placement deliberately excludes steep/wet ground. Exact speeds, durations, coverage and reflection limits remain DeathWard adaptations.'),
 dict(id='23.3.0',name='Carrion Princess',verdict='main_description_matches_placement_adapted',finding='Diagonal acquisition and spatial tail-only vulnerability are present, including head armor against piercing shots.',code=['src/combat/Charging.cpp:enemyProjectileHit','src/combat/Enemies.cpp:enemyDamage','assets/mechanics/encounters.mechanics'],tests=['princess','pools'],limits='Authored band1placement does not enforce an Ashpit-only map identity. Weak-point geometry and explosion/fire reach are3Dadaptations.'),
 dict(id='855.0.0',name='Level2Charger',verdict='main_description_matches_placement_adapted',finding='Starts on cardinal alignment and steers toward the moving target; dash speed9.5versus11for normal.',code=['src/combat/Charging.cpp:updateCharge','assets/mechanics/chargers.mechanics','assets/mechanics/adaptive_armor.mechanics'],tests=['levelTwo','championLifecycles'],limits='Exact steering, armor and duration are not established by the supplied article. Band3is an authored analogue; Home ascent is not reproduced.')]
basic_five=[
 dict(id='10.0.0',name='Frowning Gaper',result='core_matches_with_native_baseline_conflict',finding='Pursuit, persistent eye-opening and increased speed are implemented. A clear physical route drives the3Dwake trigger.',limits='Wiki death-morph frequency is not authoritative: installed-source evidence/configuration uses50percent morph, then1:2Pacer:Gusher. Exact geometric sight equivalence remains an adaptation.'),
 dict(id='10.1.0',name='Gaper',result='core_matches_with_native_baseline_conflict',finding='Direct pursuit and obstacle/body avoidance are implemented; mortality can preserve the actor as a headless form.',limits='Fandom prose favors Pacer; preserved native behavior favors Gusher among successful morphs. Keep1.7.9bweights. Named interactions and full visual/balance acceptance remain open.'),
 dict(id='11.0.0',name='Gusher',result='core_and_magenta_scoped_pass',finding='Wandering and periodic movement-directed blood shots are implemented. Magenta Gusher has a separate extra-shot timer; scoped native tests cover both timers, Freeze and projectile-capacity retry.',limits='Magenta extra-shot cadence1.2seconds, speed7 and lifetime0.8seconds remain DeathWard adaptations. Exact3Dflight/speed and full visual/champion acceptance are not established by prose.'),
 dict(id='11.1.0',name='Pacer',result='core_description_matches',finding='Aimless wandering with no ordinary projectile attack is implemented; it is a configured decapitation outcome.',limits='Special-status/item completeness and full rendered/mixed-room acceptance remain open.'),
 dict(id='12.0.0',name='Horf',result='core_matches_replacement_gap',finding='AI stays stationary, acquires an in-range target and fires aimed shots; emitted shots have independent lifetime.',limits='Native replacement conditions are verified:1/60, pre-spawn override/room exclusions, no stage gate. Ordinary Sub Horf812.0.0 and exact1/60replacement odds are now enabled, with scoped native tests. See isaac-enemy-port/horf_fly/replacement-review/index.html. Range20world units remains a3Dconversion.')]
champion_findings=[
 dict(result='missing',topic='Champion payouts',finding='Special pickup rewards, including Crown battery drops, remain unimplemented; ordinary loot is used.'),
 dict(result='different',topic='Type rarity',finding='Eligible champion types are sampled uniformly; the saved wiki distinguishes their rarity. Overall base chance5percent is separately configured.'),
 dict(result='behavior_gap',topic='Walk-dependent trails',finding='Green/Brown update paths do not require realized movement. A newly stationary body can deposit a trail. Brown subsequently avoids nearby duplicate dung.'),
 dict(result='source_conflict',topic='Snapshot edition/maintenance differences',finding='This Fandom copy gives LightWhite1–2orbiters and Brown/Rainbow roughly100times rarer. The pinned wiki.gg reference describes one Repentance orbiter and different rarity guidance. Gray/Small2/3versus.66also differs. Preserve provenance; do not silently replace the installed1.7.9bbaseline.'),
 dict(result='not_verified',topic='Combat-effect constants and interactions',finding='26implemented combat IDs and130existing Charger combinations are test coverage, not evidence that every wiki contract or special interaction is fulfilled.')]
OUT.mkdir(parents=True,exist_ok=True)
report=dict(date=datetime.datetime.now(datetime.timezone.utc).isoformat(),scope='Numeric scan of reviewed ordinary tuples; detailed manual wiki/code review of five Chargers and five basic enemies, plus shared champion caveats. No all reviewedbehavior certification.',source=dict(root=rel(SOURCE),fetched_utc=manifest.get('fetched_utc'),method=manifest.get('method'),html_pages=len(files),linked_pages=len(manifest.get('pages',[])),failures=manifest.get('failures'),files=files,manifest_sha256=sha(SOURCE/'manifest.json')),numeric_summary=dict(collections.Counter(r['result'] for r in rows)),numeric_rows=rows,detailed_chargers=detailed,detailed_basic_five=basic_five,champion_findings=champion_findings,policy='No status promotion or full native/WASM parity claim. HP policy implementation is documented in the linked health report. Scalar comparison skips conflicting or non-scalar values. No hidden constants inferred from prose.')
(OUT/'audit.json').write_text(json.dumps(report,indent=2)+'\n')
esc=html.escape
stats=' · '.join(f'{esc(k)}: {v}' for k,v in report['numeric_summary'].items())
trs=''.join(f'<tr data-search="{esc(r["id"]+" "+r["name"]+" "+r["result"])}"><td>{r["id"]}</td><td>{esc(r["name"])}</td><td>{esc(r["result"])}</td><td>{esc(r["reason"])}</td></tr>' for r in rows)
items=''.join(f'<li><b>{esc(r["name"])} — {esc(r["verdict"].replace("_"," "))}</b><p>{esc(r["finding"])}</p><p>Limits: {esc(r["limits"])}</p></li>' for r in detailed)
basic_items=''.join('<li><b>'+esc(r['name'])+'</b>: '+esc(r['finding'])+'<p>Limits: '+esc(r['limits'])+'</p></li>' for r in basic_five)
gaps=''.join(f'<li><b>{esc(r["topic"])} ({r["result"]})</b>: {esc(r["finding"])}</li>' for r in champion_findings)
(OUT/'index.html').write_text(f'''<!doctype html><html lang="en"><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>Local wiki verification — DeathWard</title><style>body{{font:16px/1.6 system-ui;max-width:1200px;margin:auto;padding:24px;overflow-wrap:anywhere;background:#1c2226;color:#eee4d2}}a{{color:#94d5ca}}h1,h2,b{{color:#edc47b}}td,th{{text-align:left;padding:10px;border-bottom:1px solid #52606a}}table{{width:100%;border-collapse:collapse}}.table{{overflow:auto}}input{{font:inherit;padding:8px;width:min(90%,500px)}}li{{margin:16px 0}}p{{margin:8px 0}}code{{background:#303b42}}</style><h1>Verification against the supplied wiki mirror</h1><p>{esc(report['date'])}. Source/code audit; numeric baseline resolution is recorded separately. <a href="audit.json">All evidence and hashes</a> · <a href="../isaac-wiki/monsters-wiki/manifest.json">Supplied source manifest</a> · <a href="../isaac-wiki/monsters-wiki/pages/Charger.html">Saved Charger article</a> · <a href="../isaac-wiki/monsters-wiki/Champions.html">Saved Champions article</a></p><p><b>108HTML files,106linked pages, no manifest download failures.</b> Numeric scan covers154reviewed regular tuples. Detailed behavior review covers five Chargers and five basic enemies. Matching HP is not a behavior pass. Existing runtime statuses remain in progress.</p><h2>Numeric results</h2><p>{stats}</p><p>Exact tuple matching only. Missing infobox, non-scalar/multiple-edition HP or conflicting boxes require review. Differences are findings, not automatic implementation bugs. Stage progression is compared using source base/stage fields when configured; fixed HP uses the documented3.2conversion.</p><p>All154source HP profiles now agree with the preserved Repentance1.7.9bXML metadata. Twelve explicit adaptation factors preserve legacy starting balance. Five multi-edition boxes are resolved using their DLC labels;14subtypes use their exact XML tuple rather than an inferred parent HP. Mullighoul remains a wiki conflict:13HP in this mirror versus14in the baseline. <a href="../isaac-health-balance/index.html">HP policy, calculations and experiment calculator</a>.</p><h2>Five Chargers: manually checked descriptions</h2><ul>{items}</ul><h2>Basic five: next behavior batch</h2><ul>{basic_items}</ul><p>Native mortality evidence: <a href="../isaac-enemy-port/gaper/validation/morph-native-summary.json">preserved1.7.9bmorph analysis</a>. Fresh <a href="../isaac-health-balance/basic-five-tests.log">basic-five tests</a> are recorded separately. A main-description match is not full acceptance.</p><h2>Champion gaps and source conflicts</h2><ul>{gaps}</ul><h2>Numeric roster</h2><input id="search" aria-label="Filter enemies" placeholder="Filter by name, ID or result"><div class="table"><table><thead><tr><th>ID</th><th>Enemy</th><th>Numeric result</th><th>Scope</th></tr></thead><tbody>{trs}</tbody></table></div><h2>Verification limits</h2><p>Saved wiki prose cannot establish exact AI frames, hidden exceptions or every item interaction. Pinned wiki.gg evidence and native1.7.9bdata remain separate sources. No WASM work is included. The linked HP policy describes the separately implemented balance controls. Existing Charger test output is saved beside this report.</p><footer>Wiki contributors, CC BY-SA. Original supplied HTML remains unchanged. Automation: <a href="../../../scripts/isaac-reference/audit-local-wiki.py">audit-local-wiki.py</a>.</footer><script>document.querySelector('#search').addEventListener('input',e=>{{const q=e.target.value.toLowerCase();document.querySelectorAll('tbody tr').forEach(r=>r.hidden=!r.dataset.search.toLowerCase().includes(q))}});</script></html>''')
print(json.dumps(dict(output=rel(OUT/'index.html'),pages=len(files),numeric=report['numeric_summary'],detailed_enemies=len(detailed)+len(basic_five))))
