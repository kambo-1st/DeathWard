#!/usr/bin/env python3
"""Verify the whole-wall review and the seeded preview case matrix."""
from collections import Counter
from pathlib import Path
import hashlib
import html
import json
import re

root = Path(__file__).resolve().parents[2]
reports = root / 'docs/reports/cliff-formations'
wall = reports / 'wall-review'
cases_dir = reports / 'phase4'


def records(source, prefix):
    rows = []
    for line in source.splitlines():
        if not line.startswith(prefix + ' '):
            continue
        row = {}
        for key, value in re.findall(r'(\w+)=([^ ]+)', line):
            try:
                row[key] = int(value) if re.fullmatch(r'[+-]?\d+', value) else float(value)
            except ValueError:
                row[key] = value
        rows.append(row)
    return rows


def repeated(source, prefix):
    rows = records(source, prefix)
    assert len(rows) == 2 and rows[0] == rows[1], prefix
    return rows[0]


source = (wall / 'volumes.log').read_text()
for mode in ('volumes', 'wireframe', 'triangles', 'massing', 'topview', 'orbit0', 'orbit1', 'orbit2', 'orbit3'):
    capture = (wall / (mode + '.log')).read_text()
    for prefix in ('PLATEAU_EXACT', 'PLATEAU_ASSEMBLY_EXACT', 'PLATEAU_BOUNDARY', 'PLATEAU_ROUTES', 'PLATEAU_JOIN'):
        assert repeated(capture, prefix) == repeated(source, prefix), (mode, prefix)
    assert 'FORMATION_SCENERY_REPLAY identical_placements=PASS' in capture
    assert 'collision_heights=unchanged floor_triangles=unchanged' in capture
core = repeated(source, 'PLATEAU_EXACT')
assert all(core[k] == 0 for k in ('exact_open', 'exact_nonmanifold', 'vertex_links', 'crossings', 'coplanar_overlap', 'degenerate'))
assembly = repeated(source, 'PLATEAU_ASSEMBLY')
assert all(assembly[k] == 0 for k in ('unexpected_boundary', 'nonmanifold', 'duplicates', 'degenerate', 'winding'))
assert repeated(source, 'PLATEAU_ROUTES')['samples'] == 1935
assert repeated(source, 'PLATEAU_JOIN')['footprint_checks'] == 612
assert '100% tests passed' in (wall / 'regression-tests.log').read_text()
baseline = json.loads((reports / 'phase3/status.json').read_text())
hashes = {path: hashlib.sha256((root / path).read_bytes()).hexdigest()
          for path in baseline['production_runtime_hashes']}
assert hashes == baseline['production_runtime_hashes']
wall_status = {
    'status': 'whole_wall_review_and_structural_corrections_verified_for_authored_preview',
    'changes': ['Added the left/dominant roof transition',
                'Replaced overlapping rear strips with one triangulated footprint',
                'Joined actual rear roof corners into the shared body',
                'Sampled the upper envelope of all main caps instead of clamping to one nominal cap',
                'Clipped protected floor out of the body domain before constructing solids',
                'Removed buried assembled faces beneath preserved floor and verified hidden cuts over entire edges'],
    'core': core, 'solids': repeated(source, 'FORMATION_SOLIDS'),
    'assembled': assembly, 'whole_face_boundary': repeated(source, 'PLATEAU_BOUNDARY'),
    'routes': repeated(source, 'PLATEAU_ROUTES'), 'joins': repeated(source, 'PLATEAU_JOIN'),
    'scenery': repeated(source, 'FORMATION_SCENERY'),
    'production_runtime_hashes': hashes, 'production_enabled': False,
    'visual_acceptance': 'Structural review completed; visible cap-height breaks remain and no universal seamlessness claim is made',
    'limits': 'Sampled elevated routes establish useful connections, not smoothness of every cap edge. Facet/height breaks remain visible. Four diagnostic quadrants were reviewed. Sub-weld fragments below 40 micrometres of projected altitude are omitted before prism construction; final exact topology and 0.1 mm source-boundary checks still apply.',
    'remaining': ['Generalized composition acceptance', 'Broader visual/occlusion/performance validation', 'Production integration'],
}
(wall / 'status.json').write_text(json.dumps(wall_status, indent=2) + '\n')

cases = json.loads((cases_dir / 'cases.json').read_text())
results = json.loads((cases_dir / 'capture-results.json').read_text())
assert len(cases) == 12 and {c['seed'] for c in cases} == {0, 42, 404, 1866}
binary_hash = hashlib.sha256((root / 'build/deathward_cliff_alternatives').read_bytes()).hexdigest()
assert (cases_dir / 'capture-binary.sha256').read_text().strip() == binary_hash
audit = json.loads((cases_dir / 'geometry-audit/results.json').read_text())
assert audit['binary_sha256'] == hashlib.sha256((root / 'build/deathward_formation_audit').read_bytes()).hexdigest()
assert len(audit['cases']) == 12
headless = {row['case']: row for row in audit['cases']}
visual_path = cases_dir / 'visual-review.json'
visual = json.loads(visual_path.read_text()) if visual_path.exists() else {}
blend_baseline = json.loads((cases_dir / 'before-visual-blend/status.json').read_text())
blend_before = {row['id']: row for row in blend_baseline['cases']}
previous = {row['id']: row['outcome'] for row in json.loads((cases_dir / 'before-seven-case-recovery/status.json').read_text())['cases']}
matrix = []
for case in cases:
    rows = [r for r in results if r['case'] == case['id']]
    main = next(r for r in rows if r['mode'] == 'formations')
    assert main['exit_code'] == 0
    a = (cases_dir / case['id'] / 'a.log').read_text()
    b = (cases_dir / case['id'] / 'formations.log').read_text()
    expected = re.search(r'FORMATION_BASELINE geometry_and_scenery_hash=(\d+)', a)[1]
    assert re.search(r'FORMATION_BASELINE geometry_and_scenery_hash=(\d+)', b)[1] == expected
    final_result = records(b, 'FORMATION_RESULT')[-1]
    assert headless[case['id']]['outcome'] == final_result['outcome']
    assert headless[case['id']]['result']['geometry_and_scenery_hash'] == str(final_result['geometry_and_scenery_hash'])
    result = dict(case, **{k: v for k, v in main.items() if k != 'case'})
    result['previous_outcome'] = previous[case['id']]
    result['preferred_section_key'] = result.pop('section_key')
    result['last_attempted_section'] = records(b, 'FORMATION_SECTION')[-1]
    search_source = (cases_dir / 'geometry-audit' / headless[case['id']]['log']).read_text()
    result['rejected_candidates'] = re.findall(r'FORMATION_REJECT attempt=\d+ reason="([^"]+)"', search_source)
    assert records(search_source, 'FORMATION_SECTION')[-1] == result['last_attempted_section']
    if main['outcome'] == 'applied':
        result['applied_section_key'] = result['last_attempted_section']['key']
        result['applied_section_length'] = result['last_attempted_section']['length']
        result['edit_margin'] = records(b, 'FORMATION_EDIT_FIT')[-1]['margin']
        cap_quality = records(b, 'PLATEAU_CAP_SURFACE')[-1]
        assert cap_quality['samples'] > 0 and cap_quality['maximum_height_error_m'] < .004
        assert cap_quality['original_roofs'] == 'preserved'
        result['cap_surface_preservation'] = cap_quality
        result['roof_recipe'] = records(b, 'FORMATION_ROOF_RECIPE')[-1]
        old = blend_before[case['id']]
        old_log = (cases_dir / 'before-visual-blend' / case['id'] / 'formations.log').read_text()
        result['same_visual_baseline_section'] = old['applied_section_key'] == result['applied_section_key'] and abs(old['applied_section_length'] - result['applied_section_length']) < .0001 and re.findall(r'^FORMATION_PROFILE .+$', old_log, re.M)[:5] == re.findall(r'^FORMATION_PROFILE .+$', b, re.M)[:5]

        final_core = records(b, 'PLATEAU_EXACT')[-1]
        final_assembly = records(b, 'PLATEAU_ASSEMBLY_EXACT')[-1]
        final_edges = records(b, 'PLATEAU_ASSEMBLY')[-1]
        assert all(final_core[k] == 0 for k in ('exact_open', 'exact_nonmanifold', 'vertex_links', 'crossings', 'coplanar_overlap', 'degenerate'))
        assert all(final_assembly[k] == 0 for k in ('vertex_links', 'crossings', 'coplanar_overlap', 'degenerate'))
        assert all(final_edges[k] == 0 for k in ('unexpected_boundary', 'nonmanifold', 'duplicates', 'degenerate', 'winding'))
        assert final_assembly['exact_open'] == final_edges['intentional_boundary']
        assert records(b, 'PLATEAU_ROUTES')[-1]['samples'] == 1935
        result['verified_core'] = final_core
        result['verified_assembly'] = final_assembly
        result['verified_boundaries'] = final_edges
        assert 'FORMATION_SCENERY_REPLAY identical_placements=PASS' in b
        assert 'PLATEAU_ASSEMBLY_REPLAY identical_triangles=PASS' in b
        for mode in ('wireframe', 'topview', 'inspect-formations'):
            assert next(r for r in rows if r['mode'] == mode)['outcome'] == 'applied'
            diagnostic = (cases_dir / case['id'] / (mode + '.log')).read_text()
            assert records(diagnostic, 'FORMATION_RESULT')[-1]['geometry_and_scenery_hash'] == records(b, 'FORMATION_RESULT')[-1]['geometry_and_scenery_hash']
        inspection_a = (cases_dir / case['id'] / 'inspect-a.log').read_text()
        assert re.search(r'FORMATION_BASELINE geometry_and_scenery_hash=(\d+)', inspection_a)[1] == expected
        review = visual.get(case['id'], {'accepted': False, 'notes': 'not yet reviewed'})
        result['visual_review'] = review['notes']
        result['visually_accepted'] = review['accepted']
    else:
        actual = re.search(r'FORMATION_RESULT outcome=fallback geometry_and_scenery_hash=(\d+)', b)[1]
        assert actual == expected, 'Fallback modified A geometry/scenery'
        result['fallback_hash_matches_A'] = True
        result['visual_review'] = 'A retained; formations generation rejected'
    matrix.append(result)
counts = Counter(r['outcome'] for r in matrix)
phase4 = {
    'status': 'experimental_seeded_preview_case_matrix_complete_acceptance_incomplete',
    'production_enabled': False, 'cases': matrix, 'counts': {key: counts[key] for key in ('applied', 'fallback')},
    'headless_audit_binary_sha256': audit['binary_sha256'],
    'headless_and_rendered_hashes_match': True,
    'recovered_cases': sum(row['previous_outcome'] == 'fallback' and row['outcome'] == 'applied' for row in matrix),
    'visually_accepted_cases': sum(r.get('visually_accepted', False) for r in matrix),
    'capture_binary_sha256': binary_hash,
    'backing_recipe': 'Rear-plane extensions and five rear stations where strict checks pass; checked previous regional roof retry otherwise',
    'extended_roof_cases': sum(row.get('roof_recipe', {}).get('finished', 0) == 1 for row in matrix),
    'previous_roof_cases': sum(row.get('roof_recipe', {}).get('finished', 0) == 0 for row in matrix),
    'visual_blend_baseline_counts': blend_baseline['counts'],
    'maximum_local_cap_height_error_m': max(row['cap_surface_preservation']['maximum_height_error_m'] for row in matrix if row['outcome'] == 'applied'),
    'cap_guard_scope': 'Local construction coordinates; world-space topology and source-boundary audits remain independently required',
    'construction': 'Four width fits down to 55%, at most 4.8 m retreat, local contour facing, steep primary-roof height correction, 1/1.5/2 m finite edit fits, terrain welding up to 0.3 mm, optional old-minus-new context closure; exact emitted-mesh checks remain mandatory',
    'manifest_section_scope': 'Manifest metadata describes the preferred candidate; applied_section_key identifies its contour origin and applied_section_length distinguishes shorter fits from that origin',
    'preservation': 'A baseline hashes match; rejected builds return byte-identical geometry/scenery records; successful builds check exact floor restoration, collision heights, strict emitted meshes and replay',
    'limitations': ['Rendered matrix currently selects curved sections; straight/concave/convex/short/exit coverage remains incomplete',
                    'Composition varies optional shoulder/base counts with bounded clearance fitting; five primary roles and uncoordinated neighbouring sections remain limitations',
                    'Failed placements, core geometry or assembled joins retain A; source numeric values and acceptance checks are not relaxed',
                    'Controlled timings for one locked case are recorded separately; wider hardware/case acceptance remains open. Screenshot FPS is not acceptance evidence'],
    'remaining': ['Expand verification beyond the recovered twelve-case matrix', 'Complete boundary-shape and coordinated-section coverage',
                  'Finish per-case visual acceptance', 'Phase 5 performance/occlusion/gameplay validation', 'Phase 6 production integration'],
}
(cases_dir / 'status.json').write_text(json.dumps(phase4, indent=2) + '\n')

style = '''<style>*{box-sizing:border-box}body{margin:0;background:#20272b;color:#eadfce;font:17px/1.55 system-ui}main{max-width:1550px;margin:auto;padding:28px}a{color:#9cdccf}p{max-width:1150px}.status{padding:16px;background:#2b383c;border-left:5px solid #dfbd7f}.pair{display:grid;grid-template-columns:1fr 1fr;gap:16px}.pair img{width:100%}figure{margin:0}figcaption{padding:8px;background:#2b383c}table{border-collapse:collapse}td,th{text-align:left;padding:8px 12px;border-bottom:1px solid #526168}.wide{overflow:auto}.sheet{display:flex;width:max-content}.sheet figure{border:2px solid #56636a}.crop{position:relative;width:1200px;height:560px;overflow:hidden}.crop img{position:absolute;width:2880px;height:1800px;max-width:none;left:-800px;top:0}pre{overflow:auto;background:#162126;padding:16px}</style>'''


def comparison(first, second):
    return f'<div class="wide"><div class="sheet" id="wall-sheet"><figure><figcaption>Before broader review</figcaption><div class="crop"><img src="{first}"></div></figure><figure><figcaption>After structural correction</figcaption><div class="crop"><img src="{second}"></div></figure></div></div>'


wall_page = f'''<!doctype html><html lang="en"><meta charset="utf-8"><title>Whole-wall plateau review</title>{style}<main>
<h1>Whole-wall review and structural corrections</h1><p class="status">The reviewed authored wall has a shared plateau body built from one triangulated footprint. The second roof notch and the end-mass connection are corrected. Exact topology checks, elevated route checks, replay and floor preservation pass. Generalized composition remains experimental.</p>
<p><a href="../../../canyon_rock_formations_plan.md">Plan and current progress</a> · <a href="status.json">Measured status</a> · <a href="../phase4/index.html">Seeded case matrix and remaining acceptance work</a></p>
{comparison('../join-correction/volumes.png','volumes.png')}
<h2>What changed</h2><p>The old seven-station ribbon could overlap itself on bends. Its nearest-cap height clamp also created low valleys behind taller neighbouring caps. The replacement uses a single hull/fan footprint, actual rear roof corners and the upper envelope of all five main roofs. Protected floor is clipped out before closed prisms are constructed. The front descriptors remain the shape baseline; the joined rear land deliberately changes the plateau surface.</p>
<p>A second sloped connector joins the left and dominant masses. Both connector patches receive 612 targeted samples. All five main roofs also have a sampled elevated connection into the common land: three lanes per roof, 129 samples per lane, 1,935 accepted samples total. Candidate routes may bend through triangle centres rather than cutting straight across intended front recesses. These samples establish connected elevated coverage; they are not a promise that every facet crease or height change is smooth.</p>
<h2>Four side/rear diagnostic views</h2><p>Actual emitted core mesh, neutral directional shading and bounds-centred orthographic cameras. Normal game lighting/materials remain in the comparison above. The finite back/bottom boundaries are diagnostic work-patch cuts, not proposed exposed world edges. Late game overlays and UI can remain.</p><div class="pair">'''
for quadrant in range(4):
    wall_page += f'<figure><figcaption>Quadrant {quadrant}</figcaption><a href="orbit{quadrant}.png"><img src="orbit{quadrant}.png"></a></figure>'
wall_page += f'''</div><h2>Verification</h2><p>The closed core has {int(wall_status['solids']['triangles'])} triangles, below 2,400; the adapted patch has {int(assembly['triangles'])}. The core has zero exact open/nonmanifold edges, vertex pinches, crossings, coplanar overlaps or degenerates. Whole-face source coverage reports no buried or detached fragments. The patch has zero unexpected boundaries; its {int(assembly['intentional_boundary'])} intentional edges are verified against terrain/floor or buried foundation. Source floor and collision, the six recorded production hashes, mesh replay and scenery replay remain unchanged/passing.</p>
<p><a href="topview.png">Top diagnostic</a> · <a href="wireframe.png">Wireframe</a> · <a href="geometry-tests.log">Geometry/support/composition/selection fixtures</a> · <a href="regression-tests.log">Four regression suites</a> · <a href="volumes.log">Native audit</a> · <a href="core.obj">Core OBJ</a></p>
<h2>Remaining</h2><p>Per-case visual acceptance, generalized joins and coordinated neighbouring sections, wider boundary-shape coverage, controlled performance/occlusion/gameplay checks and production integration remain unfinished. The regular game still uses A. No universal seamlessness claim is made.</p></main></html>'''
(wall / 'index.html').write_text(wall_page)

case_page = f'''<!doctype html><html lang="en"><meta charset="utf-8"><title>Seeded canyon formations — case matrix</title>{style}<main><h1>Experimental seeded composition</h1>
<p class="status">{counts['applied']} of 12 native cases produce verified formations; {counts['fallback']} retain unchanged A after a rejected placement or geometry check. An applied result means technical checks passed, not full visual/gameplay/performance acceptance. Production integration remains gated.</p>
<p>Recovery baseline: <a href="before-seven-case-recovery/status.json">5 generated / 7 unchanged fallbacks</a>. The <a href="before-visual-blend/status.json">matrix before visual refinement</a> passed twelve of twelve. The regional roof preserves the original cap surfaces. The latest pass tries rear-plane extensions and additional terrain stations, with a checked retry of the previous roof when an extension fails. <a href="geometry-audit/results.json">Headless geometry/replay results</a> match the rendered geometry/scenery hashes case by case. Visual acceptance remains a separate gate.</p>
<p><a href="../local-finish/index.html">Latest cap extensions, coverage and performance checkpoint</a> · <a href="../visual-blend/index.html">Earlier locked roof comparisons</a> · <a href="cases.json">Exact case manifest</a> · <a href="status.json">Results and rejected-candidate reasons</a> · <a href="capture-results.json">Capture ledger</a> · <a href="../wall-review/index.html">Authored wall review</a> · <a href="../../../canyon_rock_formations_plan.md">Plan</a></p>
<p>Seeds 0, 42, 404 and 1866; early, middle and final expedition floors; actual profile bands and room counts recorded per case. Selection uses world-space floor-level contours, bounded 14–30 m sections and six spatially distinct candidates at each of three target lengths (24, 18 and 14 m), at most eighteen candidates. Finite edit margins try 1, 1.5 and 2 m; every attempt retains the strict rejection checks. The fixed Works wall remains available separately. Composition has five primary roles and seeded optional shoulders (1–3) and bases (1–4); obstructed optional roles may be omitted. Clearance fitting is bounded and logged. Role selection uses a separate seed stream from primary profiles and detail. The current matrix does not yet supply all required boundary-shape coverage.</p>
<p>Each pair uses the same actual room, 60 scripted frames, 1440 × 900, original style, camera and light settings. The headless audit runs the full candidate search. Native views replay that successful section and roof recipe with all geometry/replay checks enabled, then verify an identical final geometry/scenery hash. Search rejections remain in the headless logs. A captures can be reused only when their complete geometry/scenery hash matches the current baseline. Successful previews check deterministic mesh/scenery replay and exact restoration of original floor vertices. Rejected candidates operate on copies; a final fallback must match the A geometry/scenery hash.</p>
<table><tr><th>Case</th><th>Profile</th><th>Before technical recovery</th><th>Current</th><th>Reason / visual review</th></tr>'''
for result in matrix:
    detail = result.get('reason', result['visual_review'])
    case_page += f'<tr><td><a href="#{result["id"]}">{result["id"]}</a></td><td>{result["profile_band"]}</td><td>{result["previous_outcome"]}</td><td>{result["outcome"]}</td><td>{html.escape(detail)}</td></tr>'
case_page += '</table>'
for result in matrix:
    identifier = result['id']
    case_page += f'<h2 id="{identifier}">{identifier}: {result["outcome"]}</h2><div class="pair"><figure><figcaption>A</figcaption><a href="{identifier}/a.png"><img src="{identifier}/a.png"></a></figure><figure><figcaption>Formations preview / retained A</figcaption><a href="{identifier}/formations.png"><img src="{identifier}/formations.png"></a></figure></div>'
    if result['outcome'] == 'applied':
        case_page += f'<div class="pair"><figure><figcaption>A — section inspection</figcaption><a href="{identifier}/inspect-a.png"><img src="{identifier}/inspect-a.png"></a></figure><figure><figcaption>Formations — same inspection camera</figcaption><a href="{identifier}/inspect-formations.png"><img src="{identifier}/inspect-formations.png"></a></figure></div>'
        if result['same_visual_baseline_section']:
            case_page += f'<details><summary>Same selected wall before and after roof refinement</summary><div class="pair"><figure><figcaption>Previous backing, same wall</figcaption><img src="before-visual-blend/{identifier}/inspect-formations.png"></figure><figure><figcaption>Refined backing, same wall</figcaption><img src="{identifier}/inspect-formations.png"></figure></div></details>'
        else:
            case_page += '<p>The new recipe selected a different valid section in this room. Use the locked comparisons for a controlled shape comparison.</p>'
        case_page += f'<p>{html.escape(result["visual_review"])} · <a href="{identifier}/wireframe.png">Wireframe</a> · <a href="{identifier}/topview.png">Selected-section top view</a></p>'
    else:
        case_page += f'<p>A retained unchanged: {html.escape(result["reason"])}.</p>'
    case_page += f'<p><a href="geometry-audit/{identifier}.log">Full candidate search and rejection reasons</a> · <a href="{identifier}/formations.log">Native selected-candidate checks</a></p>'
case_page += '''<h2>What is not finished</h2><p>The varied-room rollout is not accepted. The recovered matrix is a technical checkpoint. The roof blending pass is implemented; full per-case visual acceptance and remaining localized facets need review; the role template needs broader composition and boundary-shape coverage; neighbouring sections must share plateau interfaces. The separate performance checkpoint records repeated native timings; full performance acceptance has not been reached. FPS labels in these screenshots are not performance measurements. Production remains on A.</p>
<h2>Reproduce</h2><pre>cmake --build build --target deathward_cliff_alternatives deathward_formation_audit deathward_formation_cases deathward_rock_formations_tests -j4
./build/deathward_formation_cases docs/reports/cliff-formations/phase4/cases.json
python3 tools/cliff_experiments/formations-audit.py --require-all
python3 tools/cliff_experiments/formations-case-capture.py --diagnostics --jobs 4 --audit-selections docs/reports/cliff-formations/phase4/geometry-audit/results.json
python3 tools/cliff_experiments/formations-blend-comparison.py
python3 tools/cliff_experiments/formations-progress-report.py</pre></main></html>'''
(cases_dir / 'index.html').write_text(case_page)
print('Verified whole-wall corrections and seeded case matrix:', phase4['counts'])
