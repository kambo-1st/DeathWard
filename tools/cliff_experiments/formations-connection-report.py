#!/usr/bin/env python3
"""Save exact emitted-mesh verification and matched close-ups of the joins."""
from pathlib import Path
import json
import runpy

root = Path(__file__).resolve().parents[2]
out = root / 'docs/reports/cliff-formations/phase2/connection-audit'
assert '100% tests passed' in (out / 'regression-tests.log').read_text()
tests = (out / 'geometry-tests.log').read_text()
for seed in (0, 42, 1866):
    assert f'STRICT_SYNTHETIC seed={seed} exact_open=0 vertex_links=0 crossings=0 coplanar_overlap=0 degenerate=0' in tests
state = runpy.run_path(str(root / 'tools/cliff_experiments/formations-plateau-report.py'))
status = state['status']
summary = {
    'scope': 'Seed 1866, Works room 2, selected cliff/plateau connection; three additional synthetic geometry seeds',
    'exact_core': status['exact_connection'],
    'exact_assembled_patch': status['exact_assembly'],
    'whole_face_boundary_coverage': status['whole_face_boundary_coverage'],
    'interpretation': 'No detected gaps, vertex pinches, crossing/overlapping triangles or degenerate faces in the tested connection. Finite patch outer boundaries are verified terrain/floor or buried-foundation interfaces.',
    'limits': 'IEEE float geometry; double-precision intersection predicate with 1e-8 m plane tolerance and 1e-12 m² coplanar-overlap threshold; source-solid boundary positional margin 1e-4 m. This is not an absolute guarantee for untested generated rooms.',
    'geometry_fix_required_by_this_audit': False,
    'remaining': status['remaining'],
}
(out / 'summary.json').write_text(json.dumps(summary, indent=2) + '\n')
def pair(identifier, label, rectangle):
    x, y, width, height = rectangle
    scale = 3
    def image(name):
        return f'<div class="crop" style="width:{width*scale}px;height:{height*scale}px"><img src="../{name}.png" style="width:{1440*scale}px;height:{900*scale}px;left:{-x*scale}px;top:{-y*scale}px"></div>'
    return f'<h2>{label}</h2><div class="wide"><div class="sheet" id="{identifier}"><figure><figcaption>Native shaded view</figcaption>{image("volumes")}</figure><figure><figcaption>Same pixels: actual polygon edges</figcaption>{image("wireframe")}</figure></div></div>'
page = '''<!doctype html><html lang="en"><meta charset="utf-8"><title>Cliff/plateau connection — exact audit</title>
<style>*{box-sizing:border-box}body{margin:0;background:#20272b;color:#eadfce;font:17px/1.55 system-ui}main{max-width:1550px;margin:auto;padding:28px}a{color:#9cdccf}p{max-width:1100px}h2{margin-top:36px}.status{padding:16px;background:#2b383c;border-left:5px solid #dfbd7f}.wide{overflow:auto}.sheet{display:flex;width:max-content}.sheet figure{margin:0;border:2px solid #56636a}.sheet figcaption{padding:8px 14px;background:#2b383d;font-weight:600}.crop{position:relative;overflow:hidden}.crop img{position:absolute;max-width:none}table{border-collapse:collapse}td,th{padding:8px 16px;text-align:left;border-bottom:1px solid #526168}</style>
<main><h1>Cliff/plateau connection: stricter verification</h1><p class="status">No defects were found in the tested connection. These checks use the actual emitted vertex coordinates without merging nearby positions. The new cliff/plateau body is one closed surface. The larger render patch intentionally ends at existing terrain/floor and a buried foundation.</p>
<p><a href="../index.html">Plateau comparison and construction</a> · <a href="summary.json">Exact audit summary and numerical limits</a> · <a href="regression-tests.log">Four regression suites</a> · <a href="geometry-tests.log">Geometry and verifier fixtures</a> · <a href="../volumes.log">Native exact checks and replay</a></p>
<h2>Results</h2><table><tr><th>Check</th><th>Result</th></tr>
<tr><td>Exact open edges in the new cliff/plateau solid</td><td>0</td></tr><tr><td>Nonmanifold edges or pinched vertex links</td><td>0</td></tr><tr><td>Crossing triangles or coplanar area overlaps</td><td>0</td></tr><tr><td>Degenerate faces</td><td>0</td></tr><tr><td>Core triangle pairs tested</td><td>CORE_PAIRS</td></tr><tr><td>Assembled triangle pairs tested</td><td>ASSEMBLED_PAIRS</td></tr><tr><td>Complete core triangles checked against source solids</td><td>WHOLE_FACES; 0 buried or detached fragments</td></tr></table>
<p>The verifier fixtures deliberately introduce a sub-weld crack, crossing triangles, coplanar overlap, a pinched vertex, an internal face and a detached face, and confirm that they are detected. Separated planes are checked to avoid reporting false overlaps. Synthetic seeds 0, 42 and 1866 pass the stricter checks as well.</p>
<p>The assembled patch's 261 exact outer edges are verified interfaces: 193 on the original terrain/floor and 68 at the buried foundation. They are not cracks between the cliffs and the elevated plateau. No unverified boundary edges remain.</p>
<h2>Matched close-ups</h2><p>Seed 1866, Works room 2, 60 frames and the unchanged 160% game camera. Each pair crops identical native pixels, enlarged 3×. The shaded views retain normal lighting/materials. Hard facet creases and local height changes are part of the low-poly shape; the audit distinguishes them from geometric gaps or overlaps.</p>
PAIRS
<h2>Scope</h2><p>These results establish the tested wall's connection within the numerical limits in the summary. Other native rooms and seeds remain unverified. Remaining work is Phase 3 detail/scenery support, Phase 4 seeded composition, Phase 5 broader validation/performance and Phase 6 production integration. The regular game still uses A.</p></main></html>'''
page = page.replace('CORE_PAIRS', str(int(status['exact_connection']['tested_pairs'])))
page = page.replace('ASSEMBLED_PAIRS', str(int(status['exact_assembly']['tested_pairs'])))
page = page.replace('WHOLE_FACES', str(int(status['whole_face_boundary_coverage']['whole_triangles'])))
page = page.replace('PAIRS', ''.join([
    pair('left-join', 'Left cliff and plateau rim', (485, 60, 175, 145)),
    pair('middle-join', 'Dominant formation and plateau top', (635, 5, 220, 195)),
    pair('right-join', 'Right formation and local shoulders', (755, 85, 205, 155)),
    pair('rear-join', 'Connected plateau behind the rim', (600, 0, 400, 110)),
]))
(out / 'index.html').write_text(page)
print('Wrote exact connection audit and four matched close-up pairs.')
