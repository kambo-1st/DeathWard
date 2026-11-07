#!/usr/bin/env python3
"""Persist the user-reported footprint-notch regression and native comparison."""
from pathlib import Path
from collections import Counter
import hashlib
import json

root = Path(__file__).resolve().parents[2]
out = root / 'docs/reports/cliff-formations/join-correction'


def records(source, prefix):
    rows = []
    for line in source.splitlines():
        if not line.startswith(prefix + ' '):
            continue
        row = {}
        for token in line.split()[1:]:
            if '=' not in token:
                continue
            key, value = token.split('=', 1)
            try:
                row[key] = float(value)
            except ValueError:
                row[key] = value
        rows.append(row)
    return rows


def obj(path):
    points, faces = [], []
    for line in path.read_text().splitlines():
        values = line.split()
        if values[0] == 'v':
            points.append(tuple(map(float, values[1:])))
        elif values[0] == 'f':
            faces.append(tuple(int(i) - 1 for i in values[1:]))
    return points, faces


def height(points, faces, x, z):
    result = None
    for face in faces:
        a, b, c = [points[i] for i in face]
        dx, dz, ex, ez = b[0]-a[0], b[2]-a[2], c[0]-a[0], c[2]-a[2]
        determinant = dx*ez - dz*ex
        if abs(determinant) < 1e-12:
            continue
        u = ((x-a[0])*ez - (z-a[2])*ex) / determinant
        v = (dx*(z-a[2]) - dz*(x-a[0])) / determinant
        if u >= -1e-8 and v >= -1e-8 and u+v <= 1+1e-8:
            y = a[1] + u*(b[1]-a[1]) + v*(c[1]-a[1])
            result = y if result is None else max(result, y)
    return result


native = (out / 'volumes.log').read_text()
for name in ('volumes', 'wireframe', 'triangles', 'massing', 'topview'):
    source = (out / (name + '.log')).read_text()
    for prefix in ('PLATEAU_JOIN', 'PLATEAU_EXACT', 'PLATEAU_BOUNDARY', 'PLATEAU_ASSEMBLY', 'PLATEAU_ASSEMBLY_EXACT'):
        rows = records(source, prefix)
        assert len(rows) == 2 and rows[0] == rows[1]
    assert records(source, 'PLATEAU_JOIN')[0] == {'connectors': 2, 'footprint_checks': 306}
    for row in records(source, 'PLATEAU_EXACT'):
        assert all(row[k] == 0 for k in ('exact_open', 'exact_nonmanifold', 'vertex_links', 'crossings', 'coplanar_overlap', 'degenerate'))
    for row in records(source, 'PLATEAU_ASSEMBLY_EXACT'):
        assert row['exact_open'] == 261
        assert all(row[k] == 0 for k in ('vertex_links', 'crossings', 'coplanar_overlap', 'degenerate'))
    assert 'PLATEAU_ASSEMBLY_REPLAY identical_triangles=PASS' in source
    assert 'FORMATION_SCENERY_REPLAY identical_placements=PASS' in source
    assert 'collision_heights=unchanged floor_triangles=unchanged' in source
assert '100% tests passed' in (out / 'regression-tests.log').read_text()
assert 'PASS rock formations:' in (out / 'geometry-tests.log').read_text()
before_points, before_faces = obj(out.parent / 'phase2/connection-audit/core.obj')
points, faces = obj(out / 'core.obj')
edges = Counter(tuple(sorted((f[i], f[(i+1) % 3]))) for f in faces for i in range(3))
assert all(count == 2 for count in edges.values())
samples = [(40.66+i*.014, -11.07+j*.011) for i in range(11) for j in range(11)]
before = [height(before_points, before_faces, x, z) for x, z in samples]
after = [height(points, faces, x, z) for x, z in samples]
assert sum(y is None for y in before) == 70
assert sum(y is not None and y < 0 for y in before) == 23
assert all(y is not None and y > 2.3 for y in after)
baseline = json.loads((out.parent / 'phase3/status.json').read_text())
hashes = {path: hashlib.sha256((root / path).read_bytes()).hexdigest()
          for path in baseline['production_runtime_hashes']}
assert hashes == baseline['production_runtime_hashes']
status = {
    'status': 'reported_footprint_notch_corrected_in_authored_wall',
    'cause': 'A closed solid may contain an exterior V-shaped notch. Previous manifold and rear-body top probes did not establish continuous coverage at the dominant/shoulder join.',
    'fix': 'Two closed triangular prisms connect actual roof-edge vertices at their actual unequal heights, forming a continuous sloped transition; protected floor remains clear.',
    'join_checks': records(native, 'PLATEAU_JOIN')[0],
    'independent_export_check': {
        'world_x': [40.66, 40.80], 'world_z': [-11.07, -10.96], 'samples': 121,
        'before_missing': 70, 'before_below_ground_only': 23, 'before_low_base_only': 28, 'after_missing': 0,
        'before_remaining_max_height': max(y for y in before if y is not None),
        'after_height_range': [min(after), max(after)],
        'baseline': '../phase2/connection-audit/core.obj',
        'baseline_note': 'The same notch survives in the Phase 3 before-image; Phase 2 supplies the preserved exported mesh for independent numeric comparison.',
    },
    'core': records(native, 'PLATEAU_EXACT')[0],
    'assembled': records(native, 'PLATEAU_ASSEMBLY')[0],
    'source_boundary': records(native, 'PLATEAU_BOUNDARY')[0],
    'solids': records(native, 'FORMATION_SOLIDS')[0],
    'production_runtime_hashes': hashes, 'production_enabled': False,
    'limits': '306 connector probes are inset by 0.001 of the distance to each triangle centre to avoid exact-corner ray ambiguity. Exact boundary and source-solid audits independently check the emitted surface. This correction does not prove every future room visually seamless.',
    'remaining': ['Further visual review of all plateau transitions before accepting the whole wall as seamless',
                  'Phase 4 seeded composition', 'Phase 5 broader visual/gameplay/performance validation',
                  'Phase 6 production integration'],
}
(out / 'status.json').write_text(json.dumps(status, indent=2) + '\n')


def pair(identifier, first, second, rect):
    x, y, width, h = rect
    def figure(file, caption):
        return f'<figure><figcaption>{caption}</figcaption><div class="crop" style="width:{width*3}px;height:{h*3}px"><img src="{file}" style="width:4320px;height:2700px;left:{-x*3}px;top:{-y*3}px"></div></figure>'
    return f'<div class="wide"><div class="sheet" id="{identifier}">{figure(first,"Before: notch present")}{figure(second,"After: sloped solid connector")}</div></div>'


page = '''<!doctype html><html lang="en"><meta charset="utf-8"><title>Plateau junction correction</title>
<style>*{box-sizing:border-box}body{margin:0;background:#20272b;color:#eadfce;font:17px/1.55 system-ui}main{max-width:1550px;margin:auto;padding:28px}a{color:#9cdccf}.status{padding:16px;background:#2b383c;border-left:5px solid #dfbd7f}p{max-width:1100px}.wide{overflow:auto}.sheet{display:flex;width:max-content}.sheet figure{margin:0;border:2px solid #56636a}.sheet figcaption{padding:8px 14px;background:#2b383d;font-weight:600}.crop{position:relative;overflow:hidden}.crop img{position:absolute;max-width:none}.pair{display:grid;grid-template-columns:1fr 1fr;gap:16px}.pair img{width:100%}</style>
<main><h1>The reported plateau/shoulder notch</h1><p class="status">The user's visual rejection was correct. Earlier topology checks established a closed body but missed an exterior notch in its footprint. Two sloped solid connectors now fill that junction. The broad assertion that the entire plateau was seamless was unsupported.</p>
<p><a href="status.json">Measurements, scope and limits</a> · <a href="../../../canyon_rock_formations_plan.md">Updated progress</a> · <a href="regression-tests.log">Four regression suites</a></p>
<h2>Exact region from the reported top view</h2><p>Matched native pixels, enlarged 3×. The dark diagonal surface in the corrected view is the steep rock slope between unequal roof heights. It is solid geometry; independent vertical rays now hit it throughout the measured notch. The diagnostic can retain late game overlays and UI.</p>TOP
<h2>Normal game view</h2>SHADED
<p>The connector matches actual source roof-edge positions and heights. It changes the recess into a sloped transition; no vegetation hides the repair. Both prisms pass protected-floor clearance, exact topology, triangle-intersection and whole-face solid-boundary checks.</p>
<h2>Regression evidence</h2><p>An independent Python check of exported OBJ geometry samples an 11 × 11 rectangle at world x 40.66–40.80 m, z −11.07–−10.96 m. The preserved old mesh has 70 missing hits, 23 hits only below ground, and 28 hits only on low base geometry. The corrected mesh has 121 upper-surface hits, between 2.382 and 2.731 m. Generation also checks 306 points over the two connector triangles. These tests supplement the existing closed-surface checks; they test a different failure mode.</p>
<p>The core has 1,826 triangles in one closed body; the adapted patch has 10,619 triangles and its previous 261 intentional outer edges. Exact gap/nonmanifold/intersection/overlap checks, source-boundary coverage, floor preservation, deterministic mesh/scenery replay and all four regression suites pass. Three synthetic seeds also pass. Production source/configuration hashes remain unchanged.</p>
<p><a href="core.obj">Corrected core OBJ</a> · <a href="assembled.obj">Adapted patch OBJ</a> · <a href="geometry-tests.log">Geometry fixtures</a> · <a href="volumes.log">Native checks</a></p>
<div class="pair"><a href="topview.png"><img src="topview.png"></a><a href="volumes.png"><img src="volumes.png"></a></div>
<h2>Remaining</h2><p>The reported notch is corrected. Further visual review of the other plateau transitions remains before accepting the whole wall as seamless. Seeded composition, broader validation/performance and production integration are unfinished. The regular game still uses A.</p></main></html>'''
page = page.replace('TOP', pair('left-join', 'before-topview.png', 'topview.png', (880, 425, 145, 100)))
page = page.replace('SHADED', pair('wall-sheet', 'before-volumes.png', 'volumes.png', (640, 70, 160, 140)))
(out / 'index.html').write_text(page)
print('Verified and saved the footprint-notch correction report.')
