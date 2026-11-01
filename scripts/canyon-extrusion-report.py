#!/usr/bin/env python3
"""Build the offline correction report from preserved canyon captures and logs."""
from pathlib import Path
import os
import re
import json
import statistics
import html

os.chdir(Path(__file__).resolve().parents[1])
r = Path('docs/reports/canyon-extruded-cliffs')
geom_text = (r / 'geometry-tests.log').read_text()
g = re.search(r'GEOMETRY (.*)', geom_text)
geometry = dict(re.findall(r'(\w+)=([^\s]+)', g.group(1))) if g else {}
surfaces = [dict(re.findall(r'(\w+)=([^\s]+)', line)) for line in geom_text.splitlines() if line.startswith('SURFACES ')]
benches = {}
for mode in ('legacy', 'extruded'):
    benches[mode] = []
    for i in range(1, 4):
        p = r / f'benchmark-{mode}-{i}.log'
        if p.exists() and 'BENCHMARK ' in p.read_text():
            benches[mode].append(dict(re.findall(r'(\w+)=([^\s]+)', p.read_text().split('BENCHMARK ')[-1])))
render_stats = {}
for mode in ('legacy','extruded'):
    log = r / f'benchmark-{mode}-1.log'
    m = re.search(r'CANYON_RENDER: (.*)',log.read_text()) if log.exists() else None
    if m: render_stats[mode] = dict(re.findall(r'(\w+)=([^\s]+)',m.group(1)))
metrics = ['mean_ms', 'p95_ms', 'draw_ms', 'present_ms', 'simulation_ms']
medians = {m: {k: statistics.median(float(row[k]) for row in rows) for k in metrics} for m, rows in benches.items() if rows}
checks = {}
for name in ['geometry-tests', 'graphics-assets-tests', 'occlusion-tests', 'gameplay-regressions']:
    text = (r / f'{name}.log').read_text() if (r / f'{name}.log').exists() else ''
    checks[name] = 'PASS' if ('PASS' in text or '100% tests passed' in text) and 'FAIL' not in text else 'pending or failed'
complete = all(v == 'PASS' for v in checks.values()) and all(len(v) == 3 for v in benches.values())
if complete:
    keys = ['seed','resolution','frames','max_projectiles','min_active_enemies','min_active_projectiles','kills','max_chain_depth','suppressed']
    assert all(len({row[k] for rows in benches.values() for row in rows}) == 1 for k in keys)
measurements = {'baseline_commit':'32fa160','geometry':geometry,'surface_areas':surfaces,'checks':checks,'render_stats':render_stats,'benchmark_runs':benches,'benchmark_medians':medians,'validation_finished':complete,'camera':{'zoom_percent':160,'resolution':[1440,900],'fov':45,'projection':'perspective','seed':1866,'capture_frame':120},'remaining':['Visual review of formation proportions against the concept; exact reference seed is unknown.','More green shrub/tree models from the existing library are not included; current green plants are cactus_a and cactus_b.','Original taller physical volumes remain authoritative for collision and projectiles, as required.'], 'scope':'Explicit contour caps, narrow bevels and extruded walls; no gameplay or camera changes.'}
(r / 'measurements.json').write_text(json.dumps(measurements, indent=2) + '\n')
css = Path('docs/reports/canyon-terraces/index.html').read_text().split('<style>')[1].split('</style>')[0]
css += '.pair{display:grid;grid-template-columns:1fr 1fr;gap:18px}.pair img{width:100%;height:auto;display:block}.pair figure{margin:0}.pair figcaption{color:var(--muted);padding:8px 0}.badge{padding:5px 12px;background:#30443b;border-radius:6px} @media(max-width:700px){.pair{grid-template-columns:1fr}}'
head = '<!doctype html><html lang="en"><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>DeathWard · Cliff geometry correction</title><style>' + css + '</style><main><p class="note">Archived earlier pass. See the <a href="../canyon-reference-match/index.html">current reference matching pass</a> for the latest geometry and foliage.</p>'
out = head + '''<div class="eyebrow">DeathWard · Canyon correction · 1 November 2026</div><h1>Cliff faces and real ledges.</h1><p class="lead">The sloping heightmap treatment from commit 32fa160 is replaced with explicit contour geometry: broad caps, short chamfers, and steep extruded walls. This report preserves the rejected result, undecorated iterations, target comparison, final captures and test evidence.</p><p class="note">The target is an art-direction reference, not a matching seed. Captures use the existing camera at 160% zoom, Original style and 1440 × 900. No camera, UI, controls, combat, enemy AI, room graph or collision code was changed.</p>'''
out += '<p class="badge">Automated validation: ' + ('finished' if complete else 'in progress') + '</p>'
out += '''<h2>Target beside current geometry</h2><div class="pair"><figure><a href="target.png"><img src="target.png" alt="Supplied target concept"></a><figcaption>Target: short sandstone faces, broad caps, irregular stepped formations.</figcaption></figure><figure><a href="geometry-final.png"><img src="geometry-final.png" alt="Final geometry at 160 percent zoom without vegetation"></a><figcaption>Actual game: final geometry without decoration. This isolates surface orientation and silhouette.</figcaption></figure></div><div class="pair"><figure><img src="target.png" alt="Target concept with vegetation"><figcaption>Target with its vegetation.</figcaption></figure><figure><a href="final-combat.png"><img src="final-combat.png" alt="Final decorated canyon"></a><figcaption>Actual game with existing grass, dry bush, stones and two cactus variants. Enemy bodies, gates and HUD are unchanged.</figcaption></figure></div>
<h2>What was wrong, and what changed</h2><p>The previous version only modified vertex heights on the original 1.25 m lattice. Its renderer still connected every pair of heights with triangles, producing broad embankments, stretched faces and pointed ridges. Calling that equivalent to the target was incorrect.</p><p>The new mesh clips the original source triangles into irregular contour polygons. Each elevation band gets its own approximately level cap; contour edges get wall quads triangulated internally. Adjacent tiers are never joined by a broad heightmap slope. Short top-edge chamfers provide faceting; paired coplanar wall triangles share material variation so their internal diagonal is not painted into the surface.</p><p>The outer wall keeps its original ground-contact contour. Its upper rim is slightly recessed, removing thin top spikes while making a short steep buttress rather than widening into the room. Terrace height limits and widths vary coherently with the visual seed; the distant field drops to lower tiers. Top undulation is restrained and remains nearly horizontal.</p>
<h2>Iteration record: undecorated geometry</h2>'''
iterations = [('geometry-v1.png','1 · Extruded walls','Slopes removed, but overly uniform continuous ribbons and perfectly sharp edges.'),('geometry-v2.png','2 · Small chamfers','Narrow top bevels added; stretched rim corners were still visible.'),('geometry-v3.png','3 · Coherent height variation','Caps become gently uneven and upper levels vary locally; outer contour still needed correction.'),('geometry-v4.png','4 · Proportions and sandstone','Lower total cap range and a local warmer face material. Lighting system unchanged.'),('geometry-v5.png','5 · Recessed upper rim','Canonical ground contact retained; upper rim recessed to remove pointed top wedges.'),('geometry-final.png','6 · Final contour variation','More local tier termination, lower distant terrain, signed shelf depth to seal rim transitions, and exact visual ray tests.')]
for i in range(0,len(iterations),2):
    out += '<div class="pair">'
    for filename,title,desc in iterations[i:i+2]:
        out += f'<figure><a href="{filename}"><img loading="lazy" src="{filename}" alt="{title}"></a><figcaption><b>{title}</b> · {desc}</figcaption></figure>'
    out += '</div>'
out += '<h2>Previous slope mesh versus corrected mesh</h2>'
for name in ['combat','quarry','works']:
    out += f'''<article><h3>{name.capitalize()} scene · same seeded camera and frame</h3><div class="compare" style="--split:50%"><img src="final-{name}.png" alt="Corrected {name}" width="1440" height="900"><div class="before"><img src="previous-{name}.png" alt="Previous slopes {name}" width="1440" height="900"></div><span class="old">Previous slopes</span><span class="new">Extruded cliffs</span><div class="divider"></div></div><label class="slider">Compare <input aria-label="Compare {name}" type="range" min="0" max="100" value="50"></label><a href="final-{name}.png">Full-resolution PNG</a> · <a href="final-{name}.log">Capture log</a></article>'''
out += '''<h2>Comparison with the target</h2><div class="scroll"><table><tr><th>Feature</th><th>Assessment</th></tr><tr><td>Steep faces</td><td>Continuous wall faces are extruded separately from tops. Short buttresses and chamfers replace broad slopes. Automated area checks distinguish steep faces from caps and bevels.</td></tr><tr><td>Horizontal platforms</td><td>Explicit band caps with limited top undulation, rather than interpolated ramps. Four possible levels by default, with seeded local truncation.</td></tr><tr><td>Low proportions</td><td>Configured cap levels are 2.2, 3.73, 5.27 and 6.8 m before restrained downward top variation. The final sampled highland median is recorded below; old physical volumes are unchanged.</td></tr><tr><td>Chunky silhouettes</td><td>Separate ledges, shorter faces, faceted top edges and broad detached outcrop caps. The exact outline remains constrained by the existing room boundaries, so long boundary sections can remain more continuous than the concept.</td></tr><tr><td>Decoration</td><td>Only added after undecorated geometry inspection. Existing native grass/debris, the original dry bush and both green cactus meshes. Supported footprints only; routes and central encounter space reserved.</td></tr><tr><td>Remaining visual differences</td><td>The concept has richer, more deliberately arranged small sandstone blocks, more varied terrace proportions and richer green vegetation. This implementation addresses the sloping-face failure; it does not claim pixel-perfect concept fidelity or identical terrain outlines.</td></tr></table></div>
<h2>Architecture, picking and collision</h2><p><code>Arena::canyon</code> and the room graph stay authoritative for movement, flying-enemy placement, projectile collision, roads, river crossings and locks. <code>CanyonAppearance</code> now owns explicit triangle lists with original-cell ranges. <code>CanyonScene</code> builds the existing spatial chunks from those triangles; wall fading and rendered picking use the same explicit mesh. Visual ray queries use cell traversal and scale-relative triangle tolerances so narrow clipped polygons cannot report false hits far outside the rendered face.</p><p>Walkable ground triangles retain the original terrain. Steep outer walls meet the original floor contour. New decoration stays cosmetic. Original taller physical volumes still stop high shots above a lower visual ledge; that existing visual/physical height separation remains a limitation of preserving gameplay collision.</p><p>The sandstone adjustment is local to the new cliff shader path. It separates brown/orange faces from sandy horizontal caps; the existing lighting, shadows, post-processing and legacy materials remain intact.</p>
<h2>Configuration and rollback</h2><p>Use <a href="../../../assets/visual/canyon.cfg"><code>assets/visual/canyon.cfg</code></a>, copied beside the executable under <code>build/assets/visual/</code>. Restart after editing the runtime file. Geometry is deterministic from the visual seed. <code>enabled 0</code> still restores the original tall canyon and original dressing path.</p><pre>./build/deathward --expedition --theme canyon --style original

# Original geometry and decoration
DEATHWARD_CANYON_CONFIG=assets/visual/canyon-legacy.cfg ./build/deathward

# Capture final undecorated geometry with saved configuration
DEATHWARD_CANYON_CONFIG=docs/reports/canyon-extruded-cliffs/geometry-only.cfg \\
 ./build/deathward --mute --smoke --theme canyon --style original \\
 --scene combat --frames 120 --screenshot /tmp/canyon-geometry.png</pre>
<div class="scroll"><table><tr><th>Parameter group</th><th>Current meaning</th></tr><tr><td>minimum_height / maximum_height</td><td>Lowest and highest band caps, before restrained downward undulation. Defaults 2.2 / 6.8 m.</td></tr><tr><td>terrace_count / terrace_width</td><td>Three transitions / four possible levels; base shelf width 2.4 m, coherently varied.</td></tr><tr><td>height_variation</td><td>Seeded local upper-tier truncation; makes levels terminate rather than forming every tier everywhere.</td></tr><tr><td>silhouette_irregularity</td><td>Coherent contour warp.</td></tr><tr><td>facet_variation</td><td>Top undulation and small chamfer depth. No longer changes the ground triangle diagonal.</td></tr><tr><td>decorative_extent</td><td>Detailed exterior tier extent; farther terrain transitions to low tiers. Existing field footprint retained.</td></tr><tr><td>Density controls / budgets</td><td>Existing four vegetation categories and debris acceptance rates; maximum 2,200 cosmetic candidates. Global 0–200% vegetation still preserves stable subsets.</td></tr></table></div>
<h2>Validation and measurements</h2><div class="scroll"><table><tr><th>Check</th><th>Status</th><th>Evidence</th></tr>'''
for name,status in checks.items():
    out += f'<tr><td>{name}</td><td>{status}</td><td><a href="{name}.log">Saved log</a></td></tr>'
out += '</table></div><p>The geometry suite covers 12 seeded maps, deterministic caps/walls and dressing, dry/boundary/interior rivers, collision hashes and 180 per-room collision/trace comparisons, support, density isolation and rollback. GPU checks cover five seeds, both themes, mesh/ray agreement and whole-footprint cactus support. Occlusion/input checks cover all three hubs, canyon/wide views, hidden enemies and actual left/right/Shift fire. Pixel-exact restoration uses a dry fixture because the lowered cliffs reveal animated river water. Separate river suites retain river coverage.</p>'
if geometry:
    out += '<pre>' + html.escape(json.dumps(geometry,indent=2)) + '</pre>'
if surfaces:
    totals={k:sum(float(row[k]) for row in surfaces) for k in ['caps','walls','bevels']}
    out += '<p>Surface-area totals across 12 maps: ' + ', '.join(f'{k}: {v:,.0f} m²' for k,v in totals.items()) + '. Caps are within approximately 11° of horizontal; steep faces are within approximately 20° of vertical. Narrow chamfers account for the remaining rock surface.</p>'
out += '<h2>Performance</h2><p>Three alternating pairs, same final executable and asset library: legacy original versus corrected extrusion, 240 uncapped stress frames, seed 1866, 1440 × 900. No other native graphics suites or builds run during measurement. This enemy/projectile stress benchmark is not ordinary gameplay FPS. Clipping and wall extrusion add triangles; the previous report’s “no added triangles” claim applies only to the superseded heightmap version.</p><div class="scroll"><table><tr><th>Metric (ms)</th><th>Legacy median</th><th>Extruded median</th><th>Change</th></tr>'
if all(len(v)==3 for v in benches.values()):
    for k in metrics:
        a,b=medians['legacy'][k],medians['extruded'][k]
        out += f'<tr><td>{k}</td><td>{a:.3f}</td><td>{b:.3f}</td><td>{(b/a-1)*100:+.1f}%</td></tr>'
else:
    out += '<tr><td colspan="4">Paired benchmark still in progress.</td></tr>'
out += '</table></div>'
if len(render_stats)==2:
    out += '<p>Measured scene: ' + ', '.join(f'{mode}: {v["triangles"]} triangles, {v["chunks"]} chunks, {v["instances"]} scenery instances ({v["vegetation"]} vegetation)' for mode,v in render_stats.items()) + '.</p>'
out += '<p>Triangle lists are indexed by source cell for ray tests; existing render chunks and asset batching are reused. Cap faces remain coplanar where possible, hiding internal triangulation. Geometry has an explicit test budget below six triangles per original cell on the sampled maps. One-time preparation cost is recorded separately above.</p><p>'
for mode in benches:
    for i in range(1,4):
        out += f'<a href="benchmark-{mode}-{i}.log">{mode} {i}</a> · '
out += '<a href="measurements.json">Machine-readable results</a></p><h2>Changed files and limitations</h2><p>The new algorithm lives in <code>src/world/CanyonAppearance.*</code>; rendering, fading and local material treatment in <code>src/render/CanyonScene.cpp</code>. <code>WesternScene.*</code>, its asset catalog/library and <code>scripts/import_western.py</code> add the existing dry bush and recognize vegetation. Geometry, graphics and occlusion tests are updated for extruded rather than heightmap surfaces. No gameplay source files were edited. The original target, rejected screenshot, intermediate images and raw logs are preserved here.</p><p>Remaining: exact art-direction review against the supplied concept, especially terrace continuity and local block shapes. More green shrubs/trees from the existing library remain to be selected; current green vegetation uses the two packaged cacti. Physical height volumes remain taller than the visible cliffs. WASM checks were omitted under the standing user waiver. This report distinguishes those remaining differences from verified geometry and gameplay invariants.</p><p><a href="native-build.log">Native build log</a> · <a href="rejected-in-game.png">User’s rejected in-game screenshot</a> · <a href="../canyon-terraces/index.html">Archived heightmap report</a></p></main><script>document.querySelectorAll(".slider input").forEach(e=>e.addEventListener("input",()=>e.closest("article").querySelector(".compare").style.setProperty("--split",e.value+"%")));</script></html>'
(r / 'index.html').write_text(out)
print('Report built. Validation finished:',complete,'benchmarks:',{k:len(v) for k,v in benches.items()})
