#!/usr/bin/env python3
"""Build the canyon geometry report from preserved native evidence."""
from pathlib import Path
from html import escape
import hashlib
import json
import re
import statistics

root = Path(__file__).resolve().parents[1]
report = root / 'docs/reports/canyon-formations'


def read(name):
    path = report / name
    return path.read_text() if path.exists() else ''


def values(name, tag):
    match = re.search(r'^' + tag + r' (.*)', read(name), re.M)
    return dict(re.findall(r'(\w+)=([^\s]+)', match[1])) if match else {}


names = ['boundary-tests', 'geometry-tests', 'seed-sweep', 'gameplay-tests', 'boss-tests',
         'graphics-tests', 'occlusion-tests']
checks = {}
for name in names:
    log = read(name + '.log')
    checks[name] = 'PASS' if ('PASS' in log or '100% tests passed' in log) and 'FAIL' not in log else 'PENDING / FAILED'

benchmarks = []
for name in ['legacy-1', 'current-1', 'current-2', 'legacy-2']:
    result = values('benchmark-' + name + '.log', 'BENCHMARK')
    if result:
        benchmarks.append({'sample': name, **result})

summary = {}
for mode in ['legacy', 'current']:
    rows = [row for row in benchmarks if row['sample'].startswith(mode)]
    if rows:
        summary[mode] = {key: statistics.mean(float(row[key]) for row in rows)
                         for key in ['mean_ms', 'p95_ms']}
        match = re.search(r'CANYON_RENDER: (.*)', read('benchmark-' + rows[0]['sample'] + '.log'))
        if match:
            summary[mode]['render'] = dict(re.findall(r'(\w+)=([^\s]+)', match[1]))

files = ['src/world/CanyonTerrain.cpp', 'src/world/CanyonBoundary.hpp',
         'src/world/CanyonRoad.cpp', 'src/world/CanyonAppearance.cpp',
         'src/world/CanyonAppearance.hpp', 'src/world/CanyonFormations.cpp',
         'src/world/CanyonFormations.hpp', 'src/world/CanyonFacets.cpp',
         'src/world/CanyonFacets.hpp', 'assets/visual/canyon.cfg', 'CMakeLists.txt',
         'tests/canyon_boundary_tests.cpp', 'tests/canyon_appearance_tests.cpp',
         'tests/canyon_geometry_capture.cpp', 'tests/western_assets_tests.cpp',
         'third_party/canyon/SOURCES.txt', 'third_party/canyon/clipper.engine.cpp',
         'third_party/canyon/clipper.offset.cpp', 'third_party/canyon/earcut.hpp']
remaining = [
    'This is a new geometry candidate, not certification of an exact visual match. Some plateau stretches and faces remain plainer than the reference.',
    'The target composition and individual rock silhouettes are not reproduced exactly. Existing detached gameplay cover was retained.',
    'River channels, ford influence areas and boundary-river bank rooms retain their protected physical geometry.',
    'Visual cliff heights and the authoritative collision height field remain separate. Organic floor outlines are an intentional, separately tested gameplay-boundary change.',
    'Some seeds fill the 2,200-placement render budget at 100% vegetation; increasing density cannot add plants beyond that cap. The unchanged allocation policy can also leave later rooms sparsely dressed.',
    'Native Linux validation only. WASM checks remain waived; Windows was not rebuilt for this change.',
]
metrics = {
    'base_commit': 'b976baa',
    'status': 'Unified contour geometry implemented; exact reference fidelity remains open',
    'checks': checks,
    'geometry': values('geometry-tests.log', 'GEOMETRY'),
    'generation': values('boundary-tests.log', 'GENERATION'),
    'capture_geometry': values('geometry-final.log', 'GEOMETRY_CAPTURE'),
    'facet_graph': values('geometry-final.log', 'FACETS'),
    'benchmarks': benchmarks,
    'benchmark_summary': summary,
    'bare_mesh_control': values('geometry-legacy.log', 'GEOMETRY_CAPTURE'),
    'remaining': remaining,
    'source_sha256': {name: hashlib.sha256((root / name).read_bytes()).hexdigest() for name in files},
}
(report / 'measurements.json').write_text(json.dumps(metrics, indent=2) + '\n')


def pair(left, right, first, second):
    return f'<div class="pair"><figure><a href="{left}"><img src="{left}" alt="{escape(first)}"></a><figcaption>{escape(first)}</figcaption></figure><figure><a href="{right}"><img src="{right}" alt="{escape(second)}"></a><figcaption>{escape(second)}</figcaption></figure></div>'


h = '''<!doctype html><html lang="en"><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>DeathWard — canyon geometry correction</title><style>
body{background:#20252a;color:#e6ddcf;font:17px/1.6 system-ui;margin:0}main{max-width:1700px;margin:auto;padding:30px}h1,h2,h3{color:#f1c27d;line-height:1.25}a{color:#8ed1c3}img{display:block;width:100%;height:auto}figure{min-width:0;margin:0;background:#171d21}figcaption{padding:12px}.pair{display:grid;grid-template-columns:minmax(0,1fr) minmax(0,1fr);gap:16px;margin:20px 0}.notice{border-left:5px solid #e0b368;background:#303138;padding:18px}table{table-layout:fixed;border-collapse:collapse;width:100%;margin:20px 0}td,th{overflow-wrap:anywhere;text-align:left;vertical-align:top;border-bottom:1px solid #596064;padding:12px}pre{background:#141a1d;padding:18px;overflow:auto;font-size:14px}code{color:#f1c27d;overflow-wrap:anywhere}.scroll{overflow:auto}@media(max-width:850px){.pair{grid-template-columns:1fr}main{padding:15px}}
</style><main><h1>Canyon boundary geometry correction</h1><p class="notice">The previous outline-only pass did not address the whole annotated specification. This pass changes the contour, terrace construction and wall topology together. The images below are native renders. Passing regression checks does not certify an exact visual match.</p>
<p><a href="measurements.json">Structured evidence and source hashes</a> · <a href="current.cfg">Current configuration</a> · <a href="legacy.cfg">Reversible previous band geometry</a> · <a href="native-build.log">Native build</a></p>
<h2>Before and after</h2><p>Original style, seed 1866, the same Works room and frame count, unchanged 160% zoom, 45° perspective and 1440 × 900 capture size. The physical outline is intentionally reshaped under the user's authorization. Enemy positions and supported decoration can consequently differ; their placement rules were not edited.</p>'''
h += pair('before.png', 'works-final.png', 'Before: previous band mesh on the earlier organic outline', 'Current: unified contour caps, local terraces and broad faces')
h += '<h2>Compare with the visual specification</h2><p>The target is 1640 × 959; native output is 1440 × 900. Its exact source seed and camera position are not available. Compare geometry, proportions and surface orientation; this is not a claim of pixel-identical composition.</p>'
h += pair('target.png', 'works-final.png', 'Target concept supplied by the user', 'Current native game capture')
h += '<h2>Geometry without dressing or post-processing</h2><p>The diagnostic uses the production camera offsets, 160% zoom and a 1.8-metre player-height cylinder. Neutral normal-based lighting exposes the mesh. It excludes vegetation, props, textures, shadows, UI and post-processing. The left control uses the previous band mode on the same current physical floor.</p>'
h += pair('geometry-legacy.png', 'geometry-final.png', 'Previous band geometry; current physical floor', 'Current unified contours and local terrace polygons')
h += '<h2>Another seeded room</h2><p>The quiet power room makes the outline and upper terrain easier to inspect. Both captures use the same 160% production camera and 120 frames.</p>'
h += pair('power-before.png', 'power-final.png', 'Previous quiet room', 'Current quiet room')
h += '''<h2>Each annotated issue</h2><table><tr><th>Issue</th><th>Concrete correction</th><th>Visual limit</th></tr>
<tr><td>Rectangular clearing / long straight wall outline</td><td>Seeded multiscale basin lobes, protected road corridors, and a linear signed-distance collar replace the grid-snapped edge. The upper contour is simplified independently of the exact ground contact.</td><td>Road shoulders and protected river regions constrain the contour. Some long faces remain.</td></tr>
<tr><td>Repeated vertical columns</td><td>Unified polygon boundaries replace per-cell wall strips. Open chains are traced back to their heads before meshing. Coarse irregular face widths and staggered interior heights span several source edges.</td><td>Sharper concave corners can still require smaller faces. Broad planes remain less eroded than the concept.</td></tr>
<tr><td>Repeated horizontal terrace bands</td><td>Finite, irregular geological patches are intersected as polygons. Higher patches nest inside lower ones. Caps are the difference between adjacent elevation regions; a terrace can start and end locally. A polygon opening removes narrow raised tongues after clipping.</td><td>Adjacent patches can merge into a longer shelf; this is no longer a room-wide distance band.</td></tr>
<tr><td>Uniform steps and heights</td><td>Independent patch footprints, increasingly rare higher tiers, bounded elevation variation and a shared coarse planar cap field.</td><td>The nominal elevations are still an art-direction parameter set, not a reconstruction of the exact reference formations.</td></tr>
<tr><td>Abrupt/repetitive ground contact</td><td>The complete canonical foot contour remains the lower wall boundary; the simpler upper edge is connected to it through irregular faceted faces.</td><td>No new rubble or prop-placement pass was added. Existing terrain-aware dressing is retained.</td></tr>
<tr><td>Steep faces, flat tops and visible surrounding terrain</td><td>Walls are explicit extrusions. Caps occupy separate approximately horizontal polygons extending beyond the playable floor.</td><td>Some upper terrain is still too broad and plain for full reference fidelity.</td></tr></table>
<h2>Why the former generator produced those artifacts</h2><p><code>buildCanyonBoundary()</code> constructs the authoritative 1.25-metre collision lattice from basins, passages, protected anchors and outcrops. A near-zero walkability threshold between a flat-zero floor and tall rock biased contour crossings toward lattice vertices. <code>buildCanyonAppearance()</code> then clipped each source triangle into distance-driven bands, preserving that rhythm in its walls and extending shelves around room boundaries. A later face-remeshing attempt also began open chains at arbitrary emitted edges, fragmenting reverse-ordered walls into single-edge pieces.</p>
<h2>Current architecture</h2><ol>
<li><code>CanyonTerrain.cpp</code> retains the seeded room graph, roads, sockets, rivers and outcrop stream. Organic basins and a small linear collar produce a more accurate curved physical edge. Walkable-side collar height remains at most 0.12 metres. Reserved roads and room cores remain clear.</li>
<li><code>CanyonFormations.cpp</code> extracts closed rock polygons. Shared source-edge intersections use a canonical endpoint order, so neighboring triangles produce the same crossing coordinates. A simplified upper contour retains a mapping to every original floor-contact segment.</li>
<li>Independent, finite patch polygons are intersected with the rock region and with their predecessor. A low-resolution polygon opening enforces a minimum raised-feature width, preventing blade-like terrace tips. These are true polygon intersections, rather than minima sampled separately at each source vertex. Cap regions are polygon differences; each boundary extrudes from its predecessor elevation.</li>
<li>Polygon caps are triangulated with holes, then clipped onto a shared 8-metre planar elevation field. Each nested elevation boundary supplies its own riser; coincident segments merge into full-height faces. Walls split at the same plane boundaries. This keeps caps and walls consistent at collinear vertices and terrace junctions, while avoiding source-grid terrace modules.</li>
<li><code>CanyonFacets.cpp</code> follows complete open or closed wall chains. It retains exact ground/top edges and triangulates scattered wall-coordinate points with Delaunay triangulation, avoiding a continuous middle row. Local steepness guards relax problematic nodes; closed-loop endpoints stay tied. A final 0.3-millimetre contact weld anchors rock vertices to untouched ground vertices. Unrecoverable tight corners retain their exact extrusion.</li>
<li>The existing renderer receives the same triangle/section interface. Owner cells are rebuilt for rendering, and visual height, ray and support queries use bins covering each triangle's actual bounds. Camera, materials, lighting, controls, UI, AI and combat code were not modified.</li></ol>
<p>Clipper2 and Earcut are vendored source dependencies under <code>third_party/canyon</code>, with their licenses and preserved source manifest. They require no runtime installation or new art assets. Their licenses are preserved alongside the source. The earlier rejected low-rim geometry is not enabled by copying these utility libraries.</p>
<h2>Actual traversable floor</h2><p>This plot uses the seed-1866 collision-test fixture, not screenshot editing or the floor-3 camera capture. It samples point walkability; actor-radius clearance is checked separately. The dashed outline is the classic floor. Roads, sockets and the room graph retain their established identities.</p><a href="floor-outlines.png"><img src="floor-outlines.png" alt="Actual collision outlines and protected routes"></a>
<h2>Regression results</h2><table><tr><th>Suite</th><th>Status</th><th>Evidence</th></tr>'''
for name, status in checks.items():
    h += f'<tr><td>{name}</td><td>{status}</td><td><a href="{name}.log">Native log</a></td></tr>'
h += '</table><p>The physical suites cover deterministic replay, exact road samples, river courses and fords, clear sockets and objectives, five-room tutorial maps, all-room reachability, combat seals, backtracking, floor profiles and weak-build canyon bosses. Appearance checks cover source collision invariance, actual cap-ray coverage, clear visual room cores, forward/reverse wall-emission equivalence, bounded mesh/dressing budgets, supported vegetation and seed replay. An additional 32-map sweep exercises expedition floor profiles 0 and 3. Rendered-mesh suites compare visible mesh rays with CPU rays and exercise transparency, outlines, aiming and firing. Extruded surfaces can overhang another chunk; vertical probes require the selected chunk to hit and compare the global sampler with the nearest hit across all rendered chunks.</p>'
h += '<p>The vegetation test retains strict growth for uncapped scenes. Equality at 200% is accepted only when the actual render placement budget is already full and no additional-density plants fit. The production placement rules and budget were not changed.</p>'
for key in ['generation', 'geometry', 'facet_graph']:
    h += '<pre>' + escape(json.dumps(metrics[key], indent=2)) + '</pre>'
h += '<h2>Performance</h2><p>Matched geometry-mode benchmark samples use the same current physical floor, seed, Works floor profile, original style, 1440 × 900 resolution and existing 100-enemy stress scenario, which reaches the 4,096-projectile cap. They run sequentially in legacy/current/current/legacy order, without concurrent regression tests. Each run contains 360 uncapped frames. This is a local WSL observation, not a cross-machine FPS guarantee. The built-in mean includes first-frame preparation; p95 is useful alongside that startup-sensitive mean.</p>'
if benchmarks:
    h += '<div class="scroll"><table><tr><th>Sample</th><th>Mean ms</th><th>p95 ms</th><th>Maximum ms</th><th>Log</th></tr>'
    for row in benchmarks:
        h += '<tr>' + ''.join('<td>' + escape(row.get(key, '')) + '</td>' for key in ['sample', 'mean_ms', 'p95_ms', 'max_ms']) + f'<td><a href="benchmark-{row["sample"]}.log">Log</a></td></tr>'
    h += '</table></div>'
else:
    h += '<p>Benchmark samples are pending.</p>'
if len(summary) == 2:
    old, new = summary['legacy'], summary['current']
    delta = (new['mean_ms'] / old['mean_ms'] - 1) * 100
    h += f"<p>The two-run stress means are {old['mean_ms']:.1f} → {new['mean_ms']:.1f} ms ({delta:+.1f}%). These samples do not demonstrate a frame-time gain; the difference is smaller than the spread between the legacy runs. This is a saturated stress case, not an ordinary-play FPS measurement.</p>"
    h += '<pre>' + escape(json.dumps(summary, indent=2)) + '</pre>'
h += '<p>The isolated bare-mesh diagnostic excludes dressing and records its build duration below. These are single observations, not statistical averages.</p>'
h += '<pre>' + escape(json.dumps({'legacy': metrics['bare_mesh_control'], 'current': metrics['capture_geometry']}, indent=2)) + '</pre>'
h += '<p>Physical generation still uses two passes to preserve the exact established road. The generation timings above were collected during regression work and are not an isolated rendering benchmark. The new polygon pipeline reduces visible triangle count, but adds polygon-processing work during floor preparation. Native capture logs retain triangle/chunk counts; screenshot FPS counters are not used as measurements.</p>'
h += '''<h2>Configuration and reversibility</h2><pre># Current geometry and organic playable outline
./build/deathward --expedition --theme canyon --style original

# Previous band geometry on the current physical outline
DEATHWARD_CANYON_CONFIG=docs/reports/canyon-formations/legacy.cfg ./build/deathward --expedition --theme canyon --style original

# Previous band geometry and classic physical outline
DEATHWARD_CANYON_BOUNDARY=classic DEATHWARD_CANYON_CONFIG=docs/reports/canyon-formations/legacy.cfg ./build/deathward --expedition --theme canyon --style original

# Bare diagnostic, without changing the game renderer
./build/deathward_canyon_geometry_capture /tmp/canyon.png</pre>
<p><code>assets/visual/canyon.cfg</code> controls <code>formation_cliffs</code>, nominal minimum/maximum height, height variation, maximum local terrace count, terrace footprint width, silhouette irregularity and facet relief. Existing decoration controls remain available. Restart or generate a new expedition after changes. <code>formation_cliffs 0</code> selects the previous band path; <code>enabled 0</code> selects the older original rendering. These appearance switches are separate from the physical boundary-mode switch.</p>
<h2>Remaining work and limits</h2><ul>'''
for item in remaining:
    h += '<li>' + escape(item) + '</li>'
h += '</ul><p>Visual acceptance remains open. The report deliberately separates implemented geometry rules and passed regressions from reference fidelity.</p><h2>Changed implementation files</h2><ul>'
for name in files:
    h += '<li><code>' + escape(name) + '</code></li>'
h += '''</ul><p>Supporting changes include the vendored polygon utilities, the collision-outline plot/report scripts, README links, and a diagnostic message in the existing dungeon test. No automatic commit was made for this correction.</p><h2>Original annotated specification</h2><a href="specification.png"><img loading="lazy" src="specification.png" alt="User's complete annotated geometry specification"></a></main></html>'''
(report / 'index.html').write_text(h)
print(json.dumps(checks, indent=2))
