#!/usr/bin/env python3
"""Verify and persist the Phase 3 native detail/scenery comparison."""
from pathlib import Path
import hashlib
import html
import json

root = Path(__file__).resolve().parents[2]
out = root / 'docs/reports/cliff-formations/phase3'


def records(source, prefix):
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


def repeated(source, prefix):
    values = records(source, prefix)
    assert len(values) == 2 and values[0] == values[1], (prefix, 'replay mismatch')
    return values[0]


def verify(source, detail):
    core = repeated(source, 'PLATEAU_EXACT')
    for key in ('exact_open', 'exact_nonmanifold', 'vertex_links', 'crossings', 'coplanar_overlap', 'degenerate'):
        assert core[key] == 0, (key, core)
    patch = repeated(source, 'PLATEAU_ASSEMBLY')
    for key in ('unexpected_boundary', 'nonmanifold', 'duplicates', 'degenerate', 'winding'):
        assert patch[key] == 0, (key, patch)
    exact_patch = repeated(source, 'PLATEAU_ASSEMBLY_EXACT')
    assert exact_patch['exact_open'] == patch['intentional_boundary']
    for key in ('vertex_links', 'crossings', 'coplanar_overlap', 'degenerate'):
        assert exact_patch[key] == 0, (key, exact_patch)
    coverage = repeated(source, 'PLATEAU_BOUNDARY')
    assert coverage['buried_fragments'] == coverage['detached_fragments'] == 0
    assert repeated(source, 'PLATEAU_SURFACE')['components'] == 1
    solids = repeated(source, 'FORMATION_SOLIDS')
    assert solids['triangles'] < 2400 and solids['union_rays'] == 640
    assert repeated(source, 'PLATEAU_TOP')['coverage_rays'] == 336
    assert 'FORMATION_DETERMINISM identical_vertices=PASS' in source
    assert 'PLATEAU_ASSEMBLY_REPLAY identical_triangles=PASS' in source
    assert 'FORMATION_SCENERY_REPLAY identical_placements=PASS' in source
    assert 'collision_heights=unchanged floor_triangles=unchanged' in source
    if detail:
        details = repeated(source, 'FORMATION_DETAIL')
        assert details['rim_cuts'] == details['base_buttresses'] == 2
        buttresses = records(source, 'FORMATION_BUTTRESS')
        assert len(buttresses) == 4 and all(p['exposed_upper_area'] > .03 for p in buttresses)
        scenery = repeated(source, 'FORMATION_SCENERY')
        assert scenery['added'] > 0 and scenery['support_tests'] > 0
        assert scenery['outside_and_floor_placements'] == 'unchanged'
    return {'core': core, 'assembled': patch, 'exact_assembled': exact_patch,
            'whole_face_coverage': coverage, 'solids': solids}


logs = {name: (out / (name + '.log')).read_text()
        for name in ('volumes', 'wireframe', 'triangles', 'massing', 'topview')}
checks = {name: verify(source, True) for name, source in logs.items()}
assert all(value == checks['volumes'] for value in checks.values()), 'Capture modes changed geometry'
for name in ('volumes', 'wireframe', 'triangles'):
    verify((out / 'detail-off' / (name + '.log')).read_text(), False)
tests = (out / 'geometry-tests.log').read_text()
assert 'PASS rock formations:' in tests
for seed in (0, 42, 1866):
    assert f'DETAIL_SYNTHETIC seed={seed} ' in tests
assert '100% tests passed' in (out / 'regression-tests.log').read_text()
before = json.loads((out / 'before-status.json').read_text())
runtime = {path: hashlib.sha256((root / path).read_bytes()).hexdigest()
           for path in before['production_runtime_hashes']}
assert runtime == before['production_runtime_hashes'], 'Production source/config changed'
profiles = {record['name']: {k: v for k, v in record.items() if k != 'name'}
            for record in records(logs['volumes'], 'FORMATION_PROFILE')}
assert profiles == json.loads((out.parent / 'phase2/descriptors.json').read_text())
scenery = repeated(logs['volumes'], 'FORMATION_SCENERY')
plants = records(logs['volumes'], 'FORMATION_PLANT')[:int(scenery['added'])]
status = {
    'status': 'phase3_detail_and_scenery_verified_for_selected_wall',
    'production_enabled': False, 'seed': 1866, 'scene': 'profile-works', 'room': 2,
    'later_visual_review': {'finding': 'Topology checks missed a footprint notch at the dominant/shoulder junction',
                            'correction': '../join-correction/index.html',
                            'whole_wall_seamless_acceptance': False},
    'changes': repeated(logs['volumes'], 'FORMATION_DETAIL'),
    'geometry': checks['volumes'], 'scenery': scenery, 'new_plants': plants,
    'accepted_primary_dimensions_unchanged': True,
    'support': 'Final visible upper shell in the edited rectangle; original support outside it',
    'plant_support': 'Conservative rotated render footprint; complete clipped-surface height range plus independent rays at <=12 cm spacing; roots buried 2.5 cm below the sampled lowest surface; cactus support tolerance 10 cm, others 16 cm',
    'new_floor_encroachment': False, 'floor_triangles_unchanged': True,
    'collision_heights_unchanged': True, 'production_runtime_hashes': runtime,
    'synthetic_detail_seeds': [0, 42, 1866],
    'scope': 'One native authored wall; synthetic geometry/support fixtures. No multi-room visual or controlled performance acceptance.',
    'remaining': ['Phase 4: seeded composition and rendered room coverage',
                  'Phase 5: broader visual/gameplay/performance validation',
                  'Phase 6: production integration and rollback verification'],
}
(out / 'status.json').write_text(json.dumps(status, indent=2) + '\n')


def pair(identifier, first, second, label1, label2):
    def figure(source, label):
        return f'<figure><figcaption>{label}</figcaption><div class="crop"><img src="{source}"></div></figure>'
    return f'<div class="wide"><div class="sheet" id="{identifier}">{figure(first, label1)}{figure(second, label2)}</div></div>'


rows = ''.join(f'<tr><td>{html.escape(key)}</td><td>{html.escape(str(value))}</td></tr>'
               for key, value in scenery.items())
page = '''<!doctype html><html lang="en"><meta charset="utf-8"><title>Canyon formations — detail and supported vegetation</title>
<style>*{box-sizing:border-box}body{margin:0;background:#20272b;color:#eadfce;font:17px/1.55 system-ui}main{max-width:1550px;margin:auto;padding:28px}a{color:#9cdccf}p{max-width:1150px}h2{margin-top:36px}.status{padding:16px;background:#2b383c;border-left:5px solid #dfbd7f}.wide{overflow:auto}.sheet{display:flex;width:max-content}.sheet figure{margin:0;border:2px solid #56636a}.sheet figcaption{height:42px;padding:6px 16px;background:#2b383d;font-weight:600}.crop{position:relative;width:1200px;height:560px;overflow:hidden}.crop img{position:absolute;width:2880px;height:1800px;max-width:none;left:-800px;top:0}.pair{display:grid;grid-template-columns:1fr 1fr;gap:16px}.pair img{width:100%;height:auto}table{border-collapse:collapse}td,th{text-align:left;padding:8px 16px;border-bottom:1px solid #526168}pre{overflow:auto;background:#162126;padding:16px}</style>
<main><h1>Phase 3: restrained detail and supported vegetation</h1>
<p class="status">Later visual review found a footprint notch missed by the topology checks. See the <a href="../join-correction/index.html">reported-junction correction and revised scope</a>.</p>
<p class="status">Two local rim cuts and two low base buttresses retain the broad cliff faces. Vegetation is anchored to the actual plateau/shoulder surface. The detailed cliff and plateau remain one verified closed body. This is still a fixed-wall preview; the regular game uses A.</p>
<p><a href="../../../canyon_rock_formations_plan.md">Plan and progress</a> · <a href="status.json">Machine-readable verification</a> · <a href="../phase2/index.html">Connected plateau baseline</a></p>
<h2>Detail off / detail on</h2><p>Matched native captures: seed 1866, Works room 2, 60 frames, 1440 × 900, unchanged 160% camera, lighting and materials. Crops enlarge the same pixel rectangle 2×. Detail-off reproduces Phase 2, including its temporary suppression of old unsupported scenery. Detail-on restores supported placements at their correct height and adds sparse tufts. UI and FPS labels are incidental.</p>SHADED
<p><a href="detail-off/volumes.png">Full detail-off image</a> · <a href="volumes.png">Full detail-on image</a></p>
<h2>What changed</h2><p>Only selected roof corners on the right mass and left shoulder are cut. Two small base buttresses are partly buried and unioned into the main body, with exposed area verified so invisible additions do not count as detail. A trial buttress buried completely in an existing base mass was repositioned. There is no continuous bevel ring or debris strip.</p>
<p>The accepted primary descriptor dimensions remain unchanged; the corner cuts deliberately alter two small roof junctions. The new body has TRIANGLES triangles, below the 2,400-triangle prototype limit; the complete adapted terrain patch has PATCH_TRIANGLES triangles. These are separate counts.</p>
<h2>Vegetation and support</h2><p>Four fresh grass tufts occupy a few plateau/shoulder pockets; two existing tufts and one existing small rock are reanchored. Five unsupported local scenery placements are omitted. Candidate shrub/cactus pockets that fail support remain empty. Broad faces and most rims remain unplanted.</p>
<p>The local support map now follows the emitted upper shell and its risers, excluding downward foundation faces. It retains the old support surface outside the edited rectangle. Placement uses a conservative bound for the renderer's rotated footprint, the clipped-triangle height range and independent mesh rays spaced at most 12 cm apart. Missing mesh and sharp height changes reject placement; roots sit 2.5 cm below the sampled minimum. Cactus candidates use the renderer's stricter 10 cm height-range limit; other placements use 16 cm. New footprints, including a margin, must not overlap any protected floor triangle. Existing floor/outside decoration records are preserved.</p><table>SCENERY_ROWS</table>
<h2>Geometry and support diagnostics</h2>WIRE
<p>Neutral massing and the orthographic top view are diagnostic modes; normal captures above retain the game rendering. Late overlays/UI may remain in diagnostics.</p><div class="pair"><a href="massing.png"><img src="massing.png"></a><a href="topview.png"><img src="topview.png"></a></div>
<h2>Verification</h2><p>All five capture modes repeat identical geometry and decoration placement. The core has zero exact open/nonmanifold edges, pinched vertices, self-intersections, coplanar overlaps or degenerate faces. Whole-face source-solid coverage has zero buried/detached fragments. The assembled patch has zero unexpected edges; its 261 intentional outer edges retain the verified terrain/floor and buried-foundation classification. Top coverage, targeted seam rays, protected-floor checks and unchanged collision all pass.</p>
<p>Fixtures cover stale physical/support heights, absent visible mesh, height discontinuities, local reanchoring and outside-placement preservation. Detailed synthetic seeds 0, 42 and 1866 pass the strict geometry checks. The four regression suites pass. The six recorded production source/configuration hashes match Phase 2. Capture FPS is not controlled performance acceptance.</p>
<p><a href="geometry-tests.log">Geometry/support fixtures</a> · <a href="regression-tests.log">Regression suites</a> · <a href="volumes.log">Native detail/support/connection checks</a> · <a href="build.log">Build</a></p>
<h2>Remaining</h2><p>Phase 4 seeded composition and plateau continuity across room layouts; Phase 5 broader visual/gameplay/performance validation; Phase 6 regular-game integration. This verifies one authored native wall, not the complete procedural canyon system.</p>
<h2>Reproduce</h2><pre>cmake --build build --target deathward_cliff_alternatives deathward_rock_formations_tests -j4
ctest --test-dir build -R '^(rock_formations|cliff_facet_refinement|canyon_visual_geometry|canyon_roads)$' --output-on-failure
python3 tools/cliff_experiments/formations-capture.py --output-dir docs/reports/cliff-formations/phase3/detail-off --detail off
python3 tools/cliff_experiments/formations-capture.py --output-dir docs/reports/cliff-formations/phase3 --massing --detail on
python3 tools/cliff_experiments/formations-detail-report.py
node tools/cliff_experiments/formations-export.cjs docs/reports/cliff-formations/phase3</pre></main></html>'''
page = page.replace('SHADED', pair('wall-sheet', 'detail-off/volumes.png', 'volumes.png', 'Detail off: verified plateau', 'Detail on: local cuts, base detail and supported vegetation'))
page = page.replace('WIRE', pair('wire-sheet', 'detail-off/wireframe.png', 'wireframe.png', 'Detail off: actual polygon edges', 'Detail on: actual polygon edges'))
page = page.replace('PATCH_TRIANGLES', str(int(checks['volumes']['assembled']['triangles'])))
page = page.replace('TRIANGLES', str(int(checks['volumes']['solids']['triangles'])))
page = page.replace('SCENERY_ROWS', rows)
(out / 'index.html').write_text(page)
print('Wrote verified Phase 3 detail and vegetation report.')
