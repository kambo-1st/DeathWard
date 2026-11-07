#!/usr/bin/env python3
"""Capture and verify locked legacy/blended backing comparisons."""
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
import hashlib
import html
import json
import os
import re
import struct
import subprocess

root = Path(__file__).resolve().parents[2]
out = root / 'docs/reports/cliff-formations/visual-blend'
out.mkdir(exist_ok=True)
binary = root / 'build/deathward_cliff_alternatives'
fingerprint = hashlib.sha256(binary.read_bytes()).hexdigest()
examples = [dict(id='seed0-floor0-room0', seed=0, floor=0, room=0, attempt=4, target='-7.20624,9.20144'),
            dict(id='seed404-floor3-room2', seed=404, floor=3, room=2, attempt=8, target='107.85,51.3461')]

def capture(case):
    directory = out / case['id']
    directory.mkdir(exist_ok=True)
    rows = {}
    sources = {}
    for backing in ('legacy', 'blended'):
        env = dict(os.environ, DW_CLIFF_BACKING=backing, DW_CLIFF_LAYOUT='seeded', DW_CLIFF_OPTION='formations',
                   DW_CLIFF_SEED=str(case['seed']), DW_CLIFF_FLOOR=str(case['floor']), DW_CLIFF_ROOM=str(case['room']),
                   DW_CLIFF_ATTEMPT=str(case['attempt']), DW_CLIFF_DETAIL='1', DW_CLIFF_INSPECT_TARGET=case['target'])
        for key in ('DW_CLIFF_WIRE', 'DW_CLIFF_MASSING', 'DW_CLIFF_FREEZE_SURROUNDINGS', 'DW_CLIFF_INTERACTIVE', 'DW_CLIFF_SECTION', 'DW_CLIFF_EDGE_PROBE'):
            env.pop(key, None)
        with (directory / (backing + '.log')).open('w') as log:
            subprocess.run([str(binary), '--mute', '--smoke', '--theme', 'canyon', '--style', 'original',
                            '--scene', 'profile-works', '--frames', '60', '--screenshot', str(directory / (backing + '.png'))],
                           cwd=root, env=env, stdout=log, stderr=subprocess.STDOUT, check=True)
        source = (directory / (backing + '.log')).read_text()
        final = re.search(r'FORMATION_RESULT outcome=applied attempts=(\d+) section_key=(\d+) geometry_and_scenery_hash=(\d+)', source)
        assert final and int(final[1]) == case['attempt'], (case['id'], backing, 'Candidate rejected')
        assert 'PLATEAU_ASSEMBLY_REPLAY identical_triangles=PASS' in source
        assert 'FORMATION_SCENERY_REPLAY identical_placements=PASS' in source
        assert 'collision_heights=unchanged floor_triangles=unchanged' in source
        assert struct.unpack('>II', (directory / (backing + '.png')).read_bytes()[16:24]) == (1440, 900)
        rows[backing] = dict(section_key=final[2], geometry_and_scenery_hash=final[3], image=case['id'] + '/' + backing + '.png')
        sources[backing] = source
    assert rows['legacy']['section_key'] == rows['blended']['section_key']
    assert re.findall(r'^FORMATION_PROFILE .+$', sources['legacy'], re.M)[:5] == re.findall(r'^FORMATION_PROFILE .+$', sources['blended'], re.M)[:5], 'Primary formation profiles differ'
    assert re.search(r'FORMATION_BASELINE geometry_and_scenery_hash=(\d+)', sources['legacy'])[1] == re.search(r'FORMATION_BASELINE geometry_and_scenery_hash=(\d+)', sources['blended'])[1]
    quality = re.findall(r'PLATEAU_CAP_SURFACE samples=(\d+) maximum_height_error_m=([^ ]+) original_roofs=preserved', sources['blended'])[-1]
    assert int(quality[0]) > 0 and float(quality[1]) < .004
    print(case['id'], 'matched primary profiles and camera; geometry/replay PASS', flush=True)
    return dict(**case, modes=rows, cap_samples=int(quality[0]), maximum_local_cap_height_error_m=float(quality[1]))

with ThreadPoolExecutor(max_workers=2) as pool:
    comparisons = list(pool.map(capture, examples))
assert hashlib.sha256(binary.read_bytes()).hexdigest() == fingerprint, 'Binary changed during comparison capture'
status = dict(capture_binary_sha256=fingerprint, comparisons=comparisons, production_enabled=False,
              scope='Locked candidate comparisons; all ordinary matrix cases are verified separately. Cap height errors are measured in the local construction frame.',
              remaining=['Full per-case visual acceptance', 'Broader boundary-shape and neighbouring-section coverage', 'Performance/gameplay/occlusion acceptance', 'Production integration'])
(out / 'status.json').write_text(json.dumps(status, indent=2) + '\n')
page = '''<!doctype html><html lang="en"><meta charset="utf-8"><title>Canyon plateau blending</title><style>
body{background:#20272b;color:#eadfce;font:17px/1.5 system-ui;margin:25px auto;max-width:1550px;padding:20px}a{color:#9cdccf}.pair{display:grid;grid-template-columns:1fr 1fr;gap:12px}img{width:100%}figure{margin:0}figcaption{padding:9px;background:#2b383c}.status{padding:15px;border-left:5px solid #dfbd7f;background:#2b383c}</style><main>
<h1>Cap and plateau blending</h1><p class="status">Regional roof controls replace the high centre fan. The backing is limited below primary roofs, and its rear points meet existing terrain. These locked comparisons use identical primary profiles, camera, light, material settings and 60 scripted frames.</p>
<p><a href="../phase4/index.html">Full twelve-room gallery and technical results</a> · <a href="status.json">Comparison verification</a> · <a href="../../../canyon_rock_formations_plan.md">Plan</a></p>
<p>These are deliberately pinned wall candidates for a controlled comparison. The ordinary matrix search can select a different valid candidate. Front cap roofs and intentional shoulders retain their shape. Broader visual acceptance, neighbouring sections, performance and production integration remain unfinished.</p>'''
for case in comparisons:
    page += f'<h2>{html.escape(case["id"])} — candidate {case["attempt"]}</h2><div class="pair">'
    for backing, caption in [('legacy', 'Before: legacy backing'), ('blended', 'After: cap-limited regional roof')]:
        path = case['modes'][backing]['image']
        page += f'<figure><figcaption>{caption}</figcaption><a href="{path}"><img src="{path}"></a></figure>'
    page += f'</div><p>Primary profiles match; both meshes pass their geometry and replay checks. The new roof preserves {case["cap_samples"]} sampled cap positions within {case["maximum_local_cap_height_error_m"]:.3g} m in construction coordinates. <a href="{case["id"]}/legacy.log">Before log</a> · <a href="{case["id"]}/blended.log">After log</a></p>'
page += '</main></html>'
(out / 'index.html').write_text(page)
