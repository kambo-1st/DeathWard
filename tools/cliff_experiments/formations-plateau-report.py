#!/usr/bin/env python3
"""Persist Phase 2 plateau validation and matched native comparisons."""
from pathlib import Path
import hashlib
import html
import json
import re

root = Path(__file__).resolve().parents[2]
out = root / 'docs/reports/cliff-formations/phase2'
log = (out / 'volumes.log').read_text()

def records(prefix, source=log):
    result = []
    for line in source.splitlines():
        if not line.startswith(prefix + ' '):
            continue
        record = {}
        for token in line.split()[1:]:
            if '=' not in token:
                continue
            key, value = token.split('=', 1)
            try:
                record[key] = [float(x) for x in value.split(',')] if ',' in value else float(value)
            except ValueError:
                record[key] = value
        result.append(record)
    return result

def verified(source):
    union = records('PLATEAU_SURFACE', source)
    assert len(union) == 2 and union[0] == union[1], 'Union replay changed'
    assert union[0]['components'] == 1
    for key in ('open_edges', 'nonmanifold', 'duplicates', 'degenerate', 'winding'):
        assert union[0][key] == 0, key
    assemblies = records('PLATEAU_ASSEMBLY', source)
    assert len(assemblies) == 2 and assemblies[0] == assemblies[1], 'Assembled patch replay changed'
    assert 'PLATEAU_ASSEMBLY_REPLAY identical_triangles=PASS' in source
    assembly = assemblies[0]
    for key in ('unexpected_boundary', 'nonmanifold', 'duplicates', 'degenerate', 'winding'):
        assert assembly[key] == 0, key
    assert 'FORMATION_DETERMINISM identical_vertices=PASS' in source
    assert 'collision_heights=unchanged floor_triangles=unchanged' in source
    assert records('PLATEAU_TOP', source)[0]['coverage_rays'] == 336
    assert records('PLATEAU_SEAMS', source)[0]['targeted_rays'] > 1000
    exact = records('PLATEAU_EXACT', source)
    assembled_exact = records('PLATEAU_ASSEMBLY_EXACT', source)
    boundary = records('PLATEAU_BOUNDARY', source)
    assert len(exact) == len(assembled_exact) == len(boundary) == 2
    assert exact[0] == exact[1] and assembled_exact[0] == assembled_exact[1] and boundary[0] == boundary[1]
    for key in ('exact_open', 'exact_nonmanifold', 'vertex_links', 'crossings', 'coplanar_overlap', 'degenerate'):
        assert exact[0][key] == 0, key
    for key in ('vertex_links', 'crossings', 'coplanar_overlap', 'degenerate'):
        assert assembled_exact[0][key] == 0, key
    assert assembled_exact[0]['exact_open'] == assembly['intentional_boundary']
    assert boundary[0]['buried_fragments'] == boundary[0]['detached_fragments'] == 0
    return union[0], assembly

union, assembly = verified(log)
for mode in ('wireframe', 'triangles', 'massing', 'topview'):
    other_union, other_assembly = verified((out / (mode + '.log')).read_text())
    assert other_union == union and other_assembly == assembly, mode
before = json.loads((out / 'before-status.json').read_text())
runtime = {p: hashlib.sha256((root / p).read_bytes()).hexdigest()
           for p in before['production_runtime_hashes']}
assert runtime == before['production_runtime_hashes'], 'Production source/config changed'
profiles = {}
for record in records('FORMATION_PROFILE'):
    name = record.pop('name')
    if name in profiles:
        assert profiles[name] == record
    profiles[name] = record
assert profiles == json.loads((out / 'before-descriptors.json').read_text()), 'Accepted front descriptors changed'
assert 'PASS rock formations:' in (out / 'geometry-tests.log').read_text()
assert '100% tests passed' in (out / 'regression-tests.log').read_text()
solid = records('FORMATION_SOLIDS')[0]
assert solid['triangles'] < 2400
top = records('PLATEAU_TOP')[0]
seams = records('PLATEAU_SEAMS')[0]
locality = records('PLATEAU_LOCALITY')[0]
stations = records('PLATEAU_STATION')[:7]
repairs = list({json.dumps(item, sort_keys=True): item for item in records('PLATEAU_SLIT_REPAIR')}.values())
status = {
    'status': 'phase2_connected_plateau_verified_for_selected_wall',
    'production_enabled': False, 'seed': 1866, 'scene': 'profile-works',
    'room': 2, 'frames': 60, 'game_zoom_percent': 160,
    'accepted_front_descriptors_unchanged': True,
    'closed_union': union, 'solid_checks': solid, 'top_checks': top,
    'exact_connection': records('PLATEAU_EXACT')[0],
    'exact_assembly': records('PLATEAU_ASSEMBLY_EXACT')[0],
    'whole_face_boundary_coverage': records('PLATEAU_BOUNDARY')[0],
    'connection_closeups': 'connection-audit/index.html',
    'seam_checks': seams, 'assembled_render_patch': assembly,
    'locality': locality, 'numerical_slit_repairs': repairs,
    'floor_triangles_unchanged': True, 'collision_heights_unchanged': True,
    'production_runtime_hashes': runtime,
    'synthetic_wall_seeds': [0, 42, 1866],
    'scope': 'One native authored wall plus synthetic geometry fixtures; no multi-room visual or performance acceptance',
    'intentional_boundaries': 'Existing terrain/floor interfaces and the buried finite-patch foundation; not internal cracks',
    'remaining': ['Phase 3: restrained detail and vegetation support',
                  'Phase 4: seeded composition and rendered room coverage',
                  'Phase 5: broader visual, gameplay and controlled performance validation',
                  'Phase 6: production integration and rollback verification']
}
(out / 'status.json').write_text(json.dumps(status, indent=2) + '\n')
(out / 'plateau-stations.json').write_text(json.dumps(stations, indent=2) + '\n')
(out / 'descriptors.json').write_text(json.dumps(profiles, indent=2) + '\n')

def crop(source):
    return f'<div class="crop"><img src="{source}"></div>'

def pair(identifier, before_source, after_source, first, second):
    return f'<div class="wide"><div class="sheet" id="{identifier}"><figure><figcaption>{first}</figcaption>{crop(before_source)}</figure><figure><figcaption>{second}</figcaption>{crop(after_source)}</figure></div></div>'

rows = ''.join(f'<tr><td>{html.escape(key)}</td><td>{html.escape(str(value))}</td></tr>'
               for key, value in assembly.items())
page = '''<!doctype html><html lang="en"><meta charset="utf-8"><title>Canyon formations — connected plateau</title>
<style>*{box-sizing:border-box}body{margin:0;background:#20272b;color:#eadfce;font:17px/1.55 system-ui}main{max-width:1550px;margin:auto;padding:28px}a{color:#9cdccf}p{max-width:1150px}h2{margin-top:36px}.status{padding:16px;background:#2b383c;border-left:5px solid #dfbd7f}.wide{overflow:auto}.sheet{display:flex;width:max-content}.sheet figure{margin:0;border:2px solid #56636a}.sheet figcaption{height:42px;padding:6px 16px;background:#2b383d;font-weight:600}.crop{position:relative;width:1200px;height:560px;overflow:hidden}.crop img{position:absolute;width:2880px;height:1800px;max-width:none;left:-800px;top:0}.pair{display:grid;grid-template-columns:1fr 1fr;gap:16px}.pair img,.native{width:100%;height:auto}table{border-collapse:collapse}td,th{text-align:left;padding:8px 16px;border-bottom:1px solid #526168}pre{overflow:auto;background:#162126;padding:16px}</style>
<main><h1>Phase 2: the cliff forms an elevated plateau</h1>
<p class="status">Later visual review found a footprint notch missed by the topology checks. See the <a href="../join-correction/index.html">reported-junction correction and revised scope</a>.</p>
<p><a href="../phase3/index.html">Latest: Phase 3 detail and supported vegetation comparison</a></p>
<p class="status">The accepted front formations now connect to a solid elevated rear body and coherent top. This remains an isolated, fixed-scene preview. The regular game still uses A. Phase 3 detail/support, seeded composition, broader validation and production integration remain unfinished.</p>
<p><a href="../../../canyon_rock_formations_plan.md">Action plan and progress</a> · <a href="status.json">Validation/status data</a> · <a href="../phase1/index.html">Accepted Phase 1 shapes</a> · <a href="plateau-stations.json">Plateau control stations</a> · <a href="descriptors.json">Unchanged front descriptors</a></p>
<h2>Matched native comparison</h2><p>Seed 1866, Works room 2, 60 frames, 1440 × 900, original style and the existing 160% camera. Both crops use identical native pixels enlarged 2×. Normal-view lighting and material settings are unchanged. No added vegetation or debris hides the geometry.</p>SHADED
<p><a href="volumes.png">Full shaded capture</a> · <a href="before-volumes.png">Accepted front-shape baseline</a></p>
<h2>Actual assembled geometry</h2><p>The plain-massing view isolates the closed union of the 12 accepted formations and 12 rear-body prisms, before clipping against existing terrain. The wireframe shows the actual assembled render surface, including the retained-terrain join. Neutral diagnostic shading replaces scene materials only in massing diagnostics. The normal shaded comparison above is the visual-fidelity evidence.</p>MASSING
<h2>Plateau top and exposed triangles</h2><p>The orthographic top view is an additional diagnostic camera; it does not change the normal game camera or comparison captures. It isolates the new closed plateau body to show connected top coverage and local height variation behind the rim. Existing game UI/late overlays can remain in these diagnostics; they are not part of the mesh. The triangle view shows the actual emitted mesh.</p><div class="pair"><a href="topview.png"><img src="topview.png"></a><a href="triangles.png"><img src="triangles.png"></a></div>
<h2>Construction and locality</h2><p>BODY_DESCRIPTION</p><p>The old lowered skins were folded and unsuitable for a clean solid join. The selected backing is rebuilt from closed terrain prisms, with buried interfaces removed in both directions. At the edit perimeter, actual outside-surface crossings distinguish rock from the air below overhangs. A positive-cap-only approximation incorrectly buried the joining wall in those air gaps; the overhang fixture now guards this case.</p><p>The old nearest-contour calculation could underestimate distance beyond a segment corner. It now uses true nearest distance. Original crossing triangles are split at a finite work rectangle, and the deformation fades to zero there. Existing outside pieces retain their original planes; floor vertices and authoritative collision remain unchanged.</p>
<h2>Exact connection audit and close-ups</h2><p><a href="connection-audit/index.html">Shaded/wire close-ups and the stricter connection report</a>. The actual emitted coordinates are checked without positional merging: no exact open edges in the new cliff/plateau solid, pinched vertices, crossing triangles, coplanar area overlaps or degenerate faces. All complete core triangles are also checked against the source solid boundary within a 0.1 mm positional margin.</p><h2>Surface and coverage checks</h2><p>VALIDATION</p><p>The new solid union is one closed component with zero open/nonmanifold edges, duplicate/degenerate faces or inconsistent edge winding. The assembled render patch deliberately has an outer cut where it meets existing terrain/floor and a buried foundation. Every remaining open edge is checked against those actual surfaces or the buried outer boundary; none is accepted merely because it existed in the old skin. This verifies the selected patch, not a closed manifold for the entire canyon world.</p><table><tr><th>Assembled patch audit</th><th>Result</th></tr>AUDIT_ROWS</table>
<p>Targeted seam rays probe the incident faces just inside their common edges, avoiding silhouette-grazing amplification of the 80 μm weld tolerance. Sub-weld-scale slivers and origins occluded by nearby folds are counted separately; the complete edge audit still covers them. Top coverage includes shared edges; outer source corners may be probed 0.3 mm inside the welded perimeter. The convex/triangle ray agreement threshold remains 4 mm.</p>
<p>REPAIR_DESCRIPTION</p><p><a href="geometry-tests.log">Focused geometry and overhang fixtures</a> · <a href="regression-tests.log">Four CTest suites</a> · <a href="volumes.log">Native topology, replay, coverage, locality and floor checks</a> · <a href="build.log">Build log</a>. The capture FPS label is not a controlled performance measurement. Construction timings include debug validation and repeated generation.</p>
<h2>Scope and remaining work</h2><p>The plateau body/top and joins are verified for this authored wall. All 12 accepted front descriptor records are unchanged, as are the six recorded production runtime/configuration hashes. Synthetic walls with seeds 0, 42 and 1866 pass geometry checks; those are not rendered multi-room acceptance.</p><p>The plateau now reads as land behind the rim rather than isolated capped pillars. The sandstone reference remains the visual target; no exact reference-match claim is made. Grounded vegetation and restrained edge/base detail are Phase 3. Seed-driven composition across rooms/floors is Phase 4. Broader visual/gameplay/performance validation and regular-game integration are Phases 5–6.</p><div class="pair"><img src="../shaded-reference.png"><img src="../wireframe-reference.png"></div>
<h2>Reproduce</h2><pre>cmake --build build --target deathward_cliff_alternatives deathward_rock_formations_tests -j4
ctest --test-dir build -R '^(rock_formations|cliff_facet_refinement|canyon_visual_geometry|canyon_roads)$' --output-on-failure
python3 tools/cliff_experiments/formations-capture.py --output-dir docs/reports/cliff-formations/phase2 --massing
python3 tools/cliff_experiments/formations-plateau-report.py
node tools/cliff_experiments/formations-export.cjs docs/reports/cliff-formations/phase2</pre></main></html>'''
repairs_text = 'No numerical slit repair was needed.'
if repairs:
    repairs_text = (f'{len(repairs)} closed numerical slit was repaired; maximum width '
                    f'{max(x["width_m"] for x in repairs)*1000:.4f} mm. '
                    'A repair is allowed only for a narrow closed loop confirmed by independent solid-boundary probes; '
                    'true openings and unsupported chords are rejected. This repair is recorded separately from the surface audit.')
replacement = {
    'SHADED': pair('wall-sheet', 'before-volumes.png', 'volumes.png', 'Accepted front shapes: isolated caps', 'Phase 2: connected plateau'),
    'MASSING': pair('massing-sheet', 'massing.png', 'wireframe.png', 'Closed plateau body: plain massing', 'Actual assembled surface: polygon edges'),
    'BODY_DESCRIPTION': f'{int(union["primary"])} accepted rock volumes are connected by {int(union["body"])} closed triangular rear prisms across seven control stations. Front profiles, widths, heights and clearance shifts are preserved. Rear elevations stay near the front levels, with local variation instead of a terrace ring. The exposed union has {int(solid["triangles"])} triangles, below its 2,400-triangle limit. The larger adapted render patch has {int(assembly["triangles"])} triangles; this separate count includes retained terrain reconstruction.',
    'VALIDATION': f'{int(solid["union_rays"])} independent random convex/triangle rays per construction; {int(top["coverage_rays"])} plateau-top probes; {int(seams["targeted_rays"])} targeted near-seam rays with {int(seams["sub_weld_or_occluded_skips"])} recorded sub-weld/occluded exclusions; {int(solid["floor_tests"])} protected-floor overlap tests. Top-edge neighbourhood guards used: {int(top["edge_guards"])}. Outside split vertices remain within {locality["max_plane_error_m"]:.8f} m of their original source planes. Vertex replay, floor triangles and authoritative collision checks pass.',
    'AUDIT_ROWS': rows, 'REPAIR_DESCRIPTION': repairs_text,
}
for key, value in replacement.items():
    page = page.replace(key, value)
(out / 'index.html').write_text(page)
print('Wrote Phase 2 plateau report and verified status.')
