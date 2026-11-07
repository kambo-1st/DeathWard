#!/usr/bin/env python3
"""Publish conservative visual, boundary-coverage and performance progress."""
from collections import Counter
from pathlib import Path
import hashlib
import html
import json
import re

root = Path(__file__).resolve().parents[2]
reports = root / 'docs/reports/cliff-formations'
phase = reports / 'phase4'
out = reports / 'local-finish'
out.mkdir(exist_ok=True)
fingerprint = hashlib.sha256((root / 'build/deathward_cliff_alternatives').read_bytes()).hexdigest()
current = json.loads((phase / 'status.json').read_text())
assert current['capture_binary_sha256'] == fingerprint
old = json.loads((phase / 'before-local-finish/status.json').read_text())
prior = {row['id']: row for row in old['cases']}
inventory = json.loads((reports / 'coverage/inventory.json').read_text())
coverage_cases = json.loads((reports / 'coverage/cases.json').read_text())
coverage_audit = json.loads((reports / 'coverage/geometry-audit/results.json').read_text())
assert coverage_audit['binary_sha256'] == current['headless_audit_binary_sha256']
assert (reports / 'coverage/capture-binary.sha256').read_text().strip() == fingerprint
native_coverage = json.loads((reports / 'coverage/capture-results.json').read_text())
coverage_results = []
for case in coverage_cases:
    audit = next(row for row in coverage_audit['cases'] if row['case'] == case['id'])
    render = next(row for row in native_coverage if row['case'] == case['id'] and row['mode'] == 'formations')
    assert render['exit_code'] == 0 and audit['outcome'] == render['outcome']
    source = (reports / 'coverage' / case['id'] / 'formations.log').read_text()
    assert re.findall(r'FORMATION_RESULT .*geometry_and_scenery_hash=(\d+)', source)[-1] == audit['result']['geometry_and_scenery_hash']
    coverage_results.append(dict(case, outcome=audit['outcome'], reason=render.get('reason', ''),
                                 visually_accepted=False))
recipes = Counter()
matched = []
selected_curvature = Counter()
for case in current['cases']:
    source = (phase / case['id'] / 'formations.log').read_text()
    recipe = re.findall(r'FORMATION_ROOF_RECIPE finished=(\d+) previous_retry=(\d+)', source)[-1]
    recipes['extended' if recipe[0] == '1' else 'previous'] += 1
    candidates = [row for row in inventory if row['id'] == case['id'] and row['section_key'] == case['applied_section_key'] and abs(row['length']-case['applied_section_length']) < .001]
    assert len(candidates) == 1
    selected_curvature[candidates[0]['curvature']] += 1
    previous = prior[case['id']]
    old_log = (phase / 'before-local-finish' / case['id'] / 'formations.log').read_text()
    same = (previous['applied_section_key'] == case['applied_section_key'] and
            re.findall(r'inspect_x=([^ ]+) inspect_z=([^\s]+)', source)[-1] == re.findall(r'inspect_x=([^ ]+) inspect_z=([^\s]+)', old_log)[-1] and
            abs(previous['applied_section_length']-case['applied_section_length']) < .0001 and
            re.findall(r'^FORMATION_PROFILE .+$', source, re.M)[:5] == re.findall(r'^FORMATION_PROFILE .+$', old_log, re.M)[:5])
    if same and recipe[0] == '1':
        matched.append(case['id'])
performance = json.loads((reports / 'performance/status.json').read_text())
assert performance['capture_binary_sha256'] == fingerprint
status = dict(capture_binary_sha256=fingerprint, technical_counts=current['counts'], recipes=dict(recipes),
              visually_accepted_cases=current['visually_accepted_cases'], matched_comparisons=matched,
              inventory_candidates=len(inventory), inventory_rooms=len({(row['seed'],row['floor'],row['room']) for row in inventory}),
              inventory_curvature=dict(Counter(row['curvature'] for row in inventory)), selected_curvature=dict(selected_curvature),
              coverage_cases=coverage_results,
              short_boundary_scope='Missing and 8 m short sections reject in synthetic selector/unchanged-input fixtures; the real-room inventory contains no short candidates.',
              exit_adjacent_scope='Targeted section lies within 4 m of a connected passage gate centre in horizontal projection; gate collision/floor geometry is preserved. This is one case, not all exit layouts.',
              performance=dict(p95_ratio=performance['p95_ratio'], construction_ratio_lower_bound=performance['construction_ratio_lower_bound'],
                               frame_gate_passed=performance['frame_gate_passed'], construction_gate_passed=performance['construction_gate_passed']),
              production_enabled=False,
              remaining=['Residual cap lips, pointed end facets and full reference acceptance',
                         'Straight-section generation acceptance and unsupported boundary cases',
                         'Coordinated neighbouring plateau interfaces',
                         'Construction optimization and broader frame-time measurements',
                         'Interactive gameplay/occlusion acceptance', 'Production integration and rollback verification'])
(out / 'status.json').write_text(json.dumps(status,indent=2)+'\n')
style='''<style>body{background:#20272b;color:#eadfce;font:17px/1.5 system-ui;max-width:1550px;margin:auto;padding:25px}a{color:#9cdccf}.pair{display:grid;grid-template-columns:1fr 1fr;gap:12px}img{width:100%}figure{margin:0}figcaption,td,th{padding:9px;background:#2b383c;text-align:left}.status{padding:15px;border-left:5px solid #dfbd7f;background:#2b383c}</style>'''
page=f'''<!doctype html><html lang="en"><meta charset="utf-8"><title>Remaining plateau work: measured checkpoint</title>{style}<main>
<h1>Cap extensions, wider coverage and performance</h1>
<p class="status">{current['counts']['applied']}/12 rooms pass technical generation. {recipes['extended']} use the extended roof; {recipes['previous']} retain the previous checked roof after a rejected extension. Visual rollout remains unaccepted. Production remains on A.</p>
<p><a href="../phase4/index.html">Twelve-room gallery</a> · <a href="../coverage/inventory.json">Boundary inventory</a> · <a href="../performance/status.json">Raw performance results</a> · <a href="status.json">Checkpoint data</a> · <a href="../../../canyon_rock_formations_plan.md">Plan</a></p>
<p>The extension continues the chosen rear cap plane 0.45 m behind its rim and adds two rear terrain stations. Both recipes pass the same strict audits, floor/collision restoration and replay. A failed extension retries the previous recipe on an independent copy; failure of both keeps A. These changes do not establish smoothness at every rear or cap edge.</p>
<h2>Matched selected sections</h2><p>Only pairs with the same section origin, length, five primary profiles and inspection camera appear here. Other rooms may select a different valid section. Residual lips, steep ramps and pointed end transitions remain visible; no pair is labelled fully accepted.</p>'''
for identifier in matched:
    page += f'<h3>{identifier}</h3><div class="pair"><figure><figcaption>Previous regional roof</figcaption><img src="../phase4/before-local-finish/{identifier}/inspect-formations.png"></figure><figure><figcaption>Extended rear roof plane</figcaption><img src="../phase4/{identifier}/inspect-formations.png"></figure></div>'
page+=f'''<h2>Broader coverage</h2><p>The inventory enumerates {status['inventory_candidates']} candidates across {status['inventory_rooms']} rooms, without changing selection ranking. Curvature uses equal-distance contour chords to distinguish concave, convex, mixed and straight paths. The original coarse shape field is retained. Current generated sections: {html.escape(str(dict(selected_curvature)))}. This is measured contour classification, not visual acceptance.</p><table><tr><th>Target</th><th>Case / candidate</th><th>Outcome</th><th>Reason</th></tr>'''
for row in coverage_results:
    page+=f'<tr><td>{row["coverage"]}</td><td><a href="../coverage/{row["id"]}/formations.png">{row["id"]} / {row["attempt"]}</a></td><td>{row["outcome"]}</td><td>{html.escape(row["reason"])}</td></tr>'
page+='</table><p>Rejected targeted candidates retain byte-identical A geometry/scenery records. Short/missing-section rejection and straight/concave/convex classification are also covered by synthetic fixtures; these do not substitute for native acceptance. No short sections occur in this real-room inventory. The exit-adjacent threshold is explicitly 4 m from a connected gate centre. Neighbouring sections still lack a coordinated shared interface.</p>'
page+=f'''<h2>Sequential native performance trials</h2><p>Three alternating trials per mode, 480 deterministic uncapped frames each, first 120 discarded. Same room, selected section, inspection camera, original material/light settings and binary. Results concern one case and this machine.</p><table><tr><th>Metric</th><th>Measured ratio</th><th>Target maximum</th><th>Gate</th></tr><tr><td>Median trial p95 frame wall time, formations / A</td><td>{performance['p95_ratio']:.3f}</td><td>1.10</td><td>{'pass for this case' if performance['frame_gate_passed'] else 'fail'}</td></tr><tr><td>Construction ratio lower bound, formations / A</td><td>{performance['construction_ratio_lower_bound']:.3f}</td><td>1.25</td><td>{'fail' if performance['construction_gate_passed'] is False else 'not established'}</td></tr></table><p>Construction excludes measured topology, whole-face boundary and sampled route/ray/seam validation, plus replay. Required constructive validity/floor checks remain. The ratio omits secondary contour-base construction and dispatch overhead; a lower bound above 1.25 conclusively fails the target. Frame wall times include update, draw submission and presentation; these are not GPU timer queries. Process peak RSS includes audits and replay. See raw results for hardware, per-trial counts and every frame sample.</p>
<h2>Unfinished</h2><ul>'''
for item in status['remaining']:page+='<li>'+html.escape(item)+'</li>'
page+='</ul><p>Production integration is not ready while visual, supported-layout and performance gates remain open. The ordinary executable and its A-derived terrain path are unchanged.</p></main></html>'
(out / 'index.html').write_text(page)
print('Wrote remaining-work checkpoint',status['recipes'],status['performance'])
