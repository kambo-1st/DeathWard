#!/usr/bin/env python3
"""Build the Phase 1 evidence page without replacing the cleaned baseline."""
from pathlib import Path
import hashlib
import html
import json
import re

root = Path(__file__).resolve().parents[2]
out = root / 'docs/reports/cliff-formations/phase1'
log = (out / 'volumes.log').read_text()
match = re.search(r'FORMATION_SOLIDS count=(\d+) triangles=(\d+) floor_tests=(\d+) shifted=(\d+) closed_convex=PASS union_rays=(\d+)', log)
assert match and 'FORMATION_DETERMINISM identical_vertices=PASS' in log
assert 'collision_heights=unchanged floor_triangles=unchanged' in log
assert 'PASS rock formations:' in (out / 'geometry-tests.log').read_text()
count, triangles, tests, shifted, rays = map(int, match.groups())
before = json.loads((out / 'before-status.json').read_text())
runtime = {p: hashlib.sha256((root / p).read_bytes()).hexdigest()
           for p in before['production_runtime_hashes']}
assert runtime == before['production_runtime_hashes'], 'Production runtime/configuration changed'
profiles = {}
for line in log.splitlines():
    if not line.startswith('FORMATION_PROFILE '):
        continue
    fields = dict(token.split('=', 1) for token in line.split()[1:])
    name = fields.pop('name')
    record = {k: [float(x) for x in v.split(',')] if ',' in v else float(v)
              for k, v in fields.items()}
    if name in profiles:
        assert profiles[name] == record, 'Authored descriptor changed on replay'
    profiles[name] = record
assert len(profiles) == count == 12
(out / 'descriptors.json').write_text(json.dumps(profiles, indent=2) + '\n')

# Coordinates refer to the unchanged 1440x900 native before-image. The overlay
# labels defects; it does not paint over or replace the underlying game render.
defects = [
    {'id': 1, 'formation': 'dominant', 'rect': [650, 22, 205, 145],
     'before': 'Oversized, nearly level cap with the same rim treatment as its neighbours.',
     'change': 'Independent low roof slope, asymmetric secondary crown and two selected rim bevels; retain the broad tall face.'},
    {'id': 2, 'formation': 'left_mass', 'rect': [495, 55, 150, 130],
     'before': 'Similar squat cap profile to the dominant mass; little independent lean.',
     'change': 'Narrower, taller supporting mass with its own yaw, lean and opposing crown cut.'},
    {'id': 3, 'formation': 'middle_shoulder / right_shoulder', 'rect': [750, 114, 125, 115],
     'before': 'Broad shelf above another broad shelf reads as a repeated staircase.',
     'change': 'Different shoulder widths, elevations and yaw; lower right shoulder and short, local shelves.'},
    {'id': 4, 'formation': 'left_join', 'rect': [419, 85, 79, 117],
     'before': 'Small end masses do not clearly bridge the main forms to the untouched canyon.',
     'change': 'Wider end masses, separate roof directions and reduced setback. Final interface welding remains Phase 2.'},
    {'id': 5, 'formation': 'middle_base / protected-floor join', 'rect': [575, 172, 100, 30],
     'before': 'Small polygonal ground seams remain between the rock bases.',
     'change': 'Lower, broader existing base masses; preserve the protected floor. Complete ground/body seam acceptance remains Phase 2.'},
    {'id': 6, 'formation': 'right_join', 'rect': [900, 104, 78, 108],
     'before': 'The final small mass meets the untouched wall at a conspicuous change of shape.',
     'change': 'Wider end formation with reduced setback and its own roof direction. Final exposed-interface validation remains Phase 2.'},
]
(out / 'defects.json').write_text(json.dumps(defects, indent=2) + '\n')
status = {
    'status': 'phase1_shape_refinement_delivered', 'production_enabled': False,
    'user_feedback': {'primary_shapes_accepted': True, 'scope': 'Selected Phase 1 wall shapes only', 'plateau_required': True, 'plateau_implemented': False},
    'seed': 1866, 'scene': 'profile-works', 'room': 2, 'frames': 60,
    'game_zoom_percent': 160, 'native_resolution': [1440, 900],
    'closed_solids': count, 'union_triangles_before': before['exposed_union_triangles'],
    'union_triangles': triangles, 'independent_union_rays': rays,
    'protected_floor_overlap_tests': tests, 'shifted_volumes': shifted,
    'deterministic_vertices_and_profiles': True, 'floor_triangles_unchanged': True,
    'collision_heights_unchanged': True, 'production_runtime_hashes': runtime,
    'synthetic_wall_seeds': [0, 42, 1866],
    'visual_scope': 'One authored wall; synthetic seeds are geometry coverage only',
    'massing_view': 'Actual union mesh, same camera, neutral directional diagnostic; not production materials/lighting',
    'remaining': [
        'Phase 2: elevated connected plateau body/top, exposed-boundary welding, ground seams and end-interface acceptance',
        'Phase 3: restrained detail and grounded vegetation',
        'Phase 4: seeded composition and rendered multi-room coverage',
        'Phases 5-6: performance validation and production integration',
        'No exact reference-match or complete procedural-cliff acceptance'
    ]
}
if (out.parent / 'phase2/status.json').exists():
    status['latest_refinement'] = '../phase2/status.json'
(out / 'status.json').write_text(json.dumps(status, indent=2) + '\n')

def crop(source, overlay=''):
    return f'<div class="crop"><img src="{source}">{overlay}</div>'

def pair(identifier, before_source, after_source, before_label, after_label):
    return f'<div class="wide"><div class="sheet" id="{identifier}"><figure><figcaption>{before_label}</figcaption>{crop(before_source)}</figure><figure><figcaption>{after_label}</figcaption>{crop(after_source)}</figure></div></div>'

labels = []
rows = []
for defect in defects:
    x, y, w, h = defect['rect']
    labels.append(f'<rect x="{x}" y="{y}" width="{w}" height="{h}"/><circle cx="{x+12}" cy="{y+12}" r="10"/><text x="{x+12}" y="{y+16}">{defect["id"]}</text>')
    rows.append(f'<tr><td>{defect["id"]}</td><td><code>{html.escape(defect["formation"])}</code></td><td>{defect["before"]}</td><td>{defect["change"]}</td></tr>')
overlay = '<svg viewBox="400 0 600 270">' + ''.join(labels) + '</svg>'
descriptor_rows = ''.join(
    f'<tr><td>{name}</td><td>{p["width"]} × {p["depth"]} × {p["height"]}</td><td>{p["yaw"]}</td><td>{p["lean"]}</td><td>{p["roof"]}</td><td>{p["crown"]}</td><td>{p["setback"]} + {p["placement_shift"]}</td></tr>'
    for name, p in profiles.items())
page = '''<!doctype html><html lang="en"><meta charset="utf-8"><title>Canyon formations — Phase 1</title>
<style>*{box-sizing:border-box}body{margin:0;background:#20272b;color:#eadfce;font:17px/1.5 system-ui}main{max-width:1550px;margin:auto;padding:28px}a{color:#9cdccf}h2{margin-top:36px}p{max-width:1100px}.status{padding:16px;background:#2b383c;border-left:5px solid #dfbd7f}.wide{overflow:auto}.sheet{display:flex;width:max-content}.sheet figure{margin:0;border:2px solid #56636a}.sheet figcaption{height:42px;padding:6px 16px;background:#2b383d;font-weight:600}.crop{position:relative;width:1200px;height:540px;overflow:hidden}.crop img{position:absolute;width:2880px;height:1800px;max-width:none;left:-800px;top:0}.crop svg{position:absolute;inset:0;width:100%;height:100%}svg rect{fill:none;stroke:#78e3ed;stroke-width:1}svg circle{fill:#13272c;stroke:#78e3ed}svg text{fill:white;font:12px system-ui;text-anchor:middle}table{border-collapse:collapse;width:100%}td,th{padding:10px;text-align:left;border-bottom:1px solid #526168;vertical-align:top}.pair{display:grid;grid-template-columns:1fr 1fr;gap:16px}.pair img{width:100%}pre{overflow:auto;background:#162126;padding:16px}</style>
<main><h1>Phase 1: primary rock shapes</h1><p class="status">The cleaned wall is preserved as the baseline. Each formation now has explicit orientation, lean, roof and crown slopes, recession and selected bevels. This is one authored wall in the isolated preview. Final seam/body acceptance and the later phases remain unfinished; the regular game still uses A.</p>
<p><a href="../../../canyon_rock_formations_plan.md">Action plan and progress</a> · <a href="status.json">Status</a> · <a href="descriptors.json">Current descriptors</a> · <a href="before-descriptors.json">Baseline dimensions/profile rules</a> · <a href="before-RockFormations.cpp">Preserved baseline source</a></p>
<h2>Remaining problems marked before editing</h2><p>The numbered overlay uses the original native screenshot. Coordinates, affected formations, and proposed corrections are saved in <a href="defects.json">defects.json</a>.</p>
<div class="wide"><figure id="annotations" style="margin:0;width:max-content">ANNOTATED_CROP</figure></div>
<table><tr><th>#</th><th>Formation / interface</th><th>Before</th><th>Correction and scope</th></tr>DEFECT_ROWS</table>
<h2>Matched shaded comparison</h2><p>Seed 1866, Works room 2, 60 frames, original style, 1440 × 900, 160% zoom. The crop is enlarged 2× from identical pixels; camera, normal-view lighting, materials and floor are unchanged. No new chips, props or vegetation were added.</p>SHADED_PAIR
<h2>Plain massing and wireframe</h2><p>The massing view renders the actual union triangles under neutral directional shading on a blank background, using the same active camera. It is a diagnostic for silhouette and primary planes, not a replacement lighting/material proposal. Existing UI remains visible outside the crop. The native shaded comparison above remains the visual-fidelity evidence.</p>MASSING_PAIR
<h2>Before/after wireframes</h2>WIRE_PAIR
<p><a href="volumes.png">Full shaded capture</a> · <a href="massing.png">Full plain massing</a> · <a href="wireframe.png">Polygon wireframe</a> · <a href="triangles.png">Triangle wireframe</a></p>
<h2>Authored controls</h2><p>Dimensions and setback are metres. Yaw is radians; lean and roof/crown values are tangent/outward slopes. Placement shift is a clearance correction applied after the authored setback. The JSON also records footprint corners, taper, crown position and selected rim bevels.</p><div class="wide"><table><tr><th>Name</th><th>Width × depth × height</th><th>Yaw</th><th>Lean</th><th>Roof</th><th>Crown</th><th>Setback + clearance</th></tr>DESCRIPTOR_ROWS</table></div>
<h2>Validation</h2><p>VALIDATION</p><p>The triangle side of the independent ray check now calculates intersections in double precision using the actual render vertices. This avoids float barycentric misses on a shared bevel edge; the existing 4 mm agreement threshold is unchanged. Geometry coverage for seeds 0, 42 and 1866 is synthetic-wall coverage, not multi-room visual acceptance.</p>
<p><a href="geometry-tests.log">Geometry fixtures, including the shared bevel edge</a> · <a href="regression-tests.log">Four CTest suites</a> · <a href="final-tests.log">Final focused CTest</a> · <a href="volumes.log">Native build/replay/clearance checks</a> · <a href="massing.log">Massing capture checks</a> · <a href="build.log">Build log</a></p>
<h2>Visual assessment and remaining work</h2><p>ASSESSMENT</p><p>The user accepted these primary rock shapes and confirmed that they must form the edge of a continuous plateau. The current isolated caps and lowered backing do not yet meet that requirement. Connecting an elevated rear body and coherent plateau top, together with final backing/body welding and ground-contact interfaces, remains Phase 2. Later phases cover restrained detail, vegetation support, seeded room composition, rendered multi-room/seed validation, controlled performance measurements and production integration. Technical validation is not a claim of an exact reference match.</p>
<h2>References</h2><div class="pair"><img src="../shaded-reference.png"><img src="../wireframe-reference.png"></div>
<h2>Reproduce</h2><pre>cmake --build build --target deathward_cliff_alternatives deathward_rock_formations_tests -j4
ctest --test-dir build -R '^(rock_formations|cliff_facet_refinement|canyon_visual_geometry|canyon_roads)$' --output-on-failure
python3 tools/cliff_experiments/formations-capture.py --output-dir docs/reports/cliff-formations/phase1 --massing
python3 tools/cliff_experiments/formations-shape-report.py
node tools/cliff_experiments/formations-export.cjs docs/reports/cliff-formations/phase1</pre></main></html>'''
replacements = {
    'ANNOTATED_CROP': crop('before-volumes.png', overlay), 'DEFECT_ROWS': ''.join(rows),
    'SHADED_PAIR': pair('wall-sheet', 'before-volumes.png', 'volumes.png', 'Cleaned baseline', 'Phase 1: independent formation profiles'),
    'MASSING_PAIR': pair('massing-sheet', 'massing.png', 'wireframe.png', 'Actual mesh: plain massing', 'Actual mesh: exposed polygon edges'),
    'WIRE_PAIR': pair('wire-sheet', 'before-wireframe.png', 'wireframe.png', 'Cleaned baseline wireframe', 'Phase 1 wireframe'),
    'DESCRIPTOR_ROWS': descriptor_rows,
    'VALIDATION': f'{count} closed solids; {triangles} union triangles (baseline {before["exposed_union_triangles"]}, budget 2,400); {rays} independent convex/triangle rays per build; {tests} protected-floor tests. Seeded replay agrees for vertices and authored descriptors. Original floor triangles, collision heights and all six production runtime/configuration hashes are unchanged.',
    'ASSESSMENT': 'The primary masses have different lean and crown profiles instead of a repeated cap rule. Smaller, lower base masses expose more uninterrupted main faces, and the shoulders occupy different widths and levels. End formations are wider and less recessed to bridge into the old wall. The dominant face remains broad and quiet. Review the shaded pair with the reference: this is still a composed wall, and full interface continuity is reserved for the assembled-boundary checks in Phase 2.'
}
for key, value in replacements.items():
    page = page.replace(key, value)
if (out.parent / 'phase2/index.html').exists():
    page = page.replace('<main>', '<main><p class="status">This page preserves the accepted Phase 1 shapes. See the <a href="../phase2/index.html">connected plateau and join validation from Phase 2</a>.</p>', 1)
(out / 'index.html').write_text(page)
print('Wrote Phase 1 report, annotated defect map, descriptors and status.')
