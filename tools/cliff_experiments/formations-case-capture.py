#!/usr/bin/env python3
"""Capture exact seeded room cases with A and the generalized formations preview."""
from pathlib import Path
import argparse
import hashlib
import json
import os
import re
import subprocess
from concurrent.futures import ThreadPoolExecutor, as_completed

root = Path(__file__).resolve().parents[2]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--output-dir', type=Path, default=root / 'docs/reports/cliff-formations/phase4')
parser.add_argument('--limit', type=int)
parser.add_argument('--jobs', type=int, default=1)
parser.add_argument('--audit-selections', type=Path, help='Render candidates selected by a current full headless audit')
parser.add_argument('--diagnostics', action='store_true')
parser.add_argument('--reuse-baselines', action='store_true', help='Reuse A captures after verifying their geometry/scenery hash')
options = parser.parse_args()
out = options.output_dir
out.mkdir(parents=True, exist_ok=True)
cases = json.loads((out / 'cases.json').read_text())
if options.limit:
    cases = cases[:options.limit]
selections = {}
selected_roofs = {}
if options.audit_selections:
    audit = json.loads(options.audit_selections.read_text())
    assert audit['binary_sha256'] == hashlib.sha256((root / 'build/deathward_formation_audit').read_bytes()).hexdigest(), 'Stale headless audit'
    selections = {row['case']: row for row in audit['cases']}
    for row in audit['cases']:
        if row['outcome'] == 'applied':
            source = (options.audit_selections.parent / row['log']).read_text()
            recipes = re.findall(r'FORMATION_ROOF_RECIPE finished=(\d+) previous_retry=\d+', source)
            assert recipes, 'Audit lacks a reproducible roof recipe'
            selected_roofs[row['case']] = recipes[-1]
    assert {case['id'] for case in cases} <= selections.keys()
results = []
binary = root / 'build/deathward_cliff_alternatives'
binary_hash = hashlib.sha256(binary.read_bytes()).hexdigest()
(out / 'capture-binary.sha256').write_text(binary_hash + '\n')
def capture(case):
    results = []
    directory = out / case['id']
    directory.mkdir(exist_ok=True)
    modes = [('a', 'original', None), ('formations', 'formations', None)]
    if options.diagnostics:
        modes += [('wireframe', 'formations', 'wire'), ('topview', 'formations', 'top'),
                  ('inspect-a', 'original', 'inspect'), ('inspect-formations', 'formations', 'inspect')]
    baseline = None
    if options.reuse_baselines and (directory / 'a.log').exists():
        source = (directory / 'a.log').read_text()
        baseline = re.search(r'FORMATION_BASELINE geometry_and_scenery_hash=(\d+)', source)[1]
        results.append(dict(case=case['id'], mode='a', exit_code=0, outcome='baseline', reused=True))
        modes = [mode for mode in modes if mode[0] != 'a']
    outcome = None
    for name, mode, diagnostic in modes:
        if diagnostic and any(row.get('outcome') == 'fallback' for row in results):
            continue
        if diagnostic and outcome != 'applied':
            continue
        env = dict(os.environ, DW_CLIFF_LAYOUT='seeded', DW_CLIFF_OPTION=mode, DW_CLIFF_BACKING='blended',
                   DW_CLIFF_SEED=str(case['seed']), DW_CLIFF_FLOOR=str(case['floor']),
                   DW_CLIFF_ROOM=str(case['room']), DW_CLIFF_DETAIL='1')
        for key in ('DW_CLIFF_FREEZE_SURROUNDINGS', 'DW_CLIFF_INTERACTIVE', 'DW_CLIFF_MASSING',
                    'DW_CLIFF_WIRE', 'DW_CLIFF_CONNECTION_AUDIT', 'DW_CLIFF_JOIN_PROBE',
                    'DW_CLIFF_ROOF_CONSTRAINED', 'DW_CLIFF_SOLID_BOOLEAN', 'DW_CLIFF_BOOLEAN_RAW', 'DW_CLIFF_BOOLEAN_SOURCE_RESTORE', 'DW_CLIFF_BOOLEAN_SOURCE_CHECKED', 'DW_CLIFF_BOOLEAN_VERTEX_REPAIR', 'DW_CLIFF_BOOLEAN_FLOAT_REPAIR', 'DW_CLIFF_TOP_PROBE', 'DW_CLIFF_PRECISE_JOIN', 'DW_CLIFF_ASSEMBLY_PROBE', 'DW_CLIFF_JOIN_SINGLE_ROUND', 'DW_CLIFF_CHUNK_SOURCE_PROBE', 'DW_CLIFF_EARLY_TARGET', 'DW_CLIFF_CAP_CONNECTED_DOMAIN', 'DW_CLIFF_SOURCE_SHARED_EDGES', 'DW_CLIFF_SOURCE_REUSE', 'DW_CLIFF_SOURCE_RETAINED_BAND', 'DW_CLIFF_SOURCE_AFFINE_ENVELOPE', 'DW_CLIFF_SOURCE_VERTEX_BLEND', 'DW_CLIFF_SOURCE_NODE_BLEND', 'DW_CLIFF_EXACT_CONTACTS', 'DW_CLIFF_SOURCE_SNAP_ROUND', 'DW_CLIFF_SOURCE_SHARED_CUTS', 'DW_CLIFF_SOURCE_REGULARIZE', 'DW_CLIFF_OWNER_SOURCE_PROBE', 'DW_CLIFF_SOURCE_PARTITION', 'DW_CLIFF_CHUNK_SOURCE_PLANES', 'DW_CLIFF_BOOLEAN_PADDING', 'DW_CLIFF_BOOLEAN_TOLERANCE', 'DW_CLIFF_BASE_CONTEXT',
                    'DW_CLIFF_ROOF_ENVELOPE', 'DW_CLIFF_ROOF_MERGED', 'DW_CLIFF_REQUIRE_NEW_ROOF',
                    'DW_CLIFF_POLYGON_CONTOURS', 'DW_CLIFF_ROOF_ARRANGEMENT', 'DW_CLIFF_ROOF_CHUNKS', 'DW_CLIFF_CHUNK_PROBE', 'DW_CLIFF_ROOF_REGION', 'DW_CLIFF_REGION_PROBE', 'DW_CLIFF_EAR_WELD', 'DW_CLIFF_ROOF_BOUNDARY_GRADES', 'DW_CLIFF_INVALID_PROBE', 'DW_CLIFF_INTERFACE_PROBE', 'DW_CLIFF_ROOF_COLLAR', 'DW_CLIFF_NO_GRADE_PRUNE', 'DW_CLIFF_ROOF_SHELL', 'DW_CLIFF_ROOF_WORLD', 'DW_CLIFF_WORLD_GRID'):
            env.pop(key, None)
        env.pop('DW_CLIFF_INSPECT_TARGET', None)
        env.pop('DW_CLIFF_SECTION', None)
        env.pop('DW_CLIFF_ROOF_PREVIOUS', None)
        env.pop('DW_CLIFF_FRAME_BENCH', None)
        env.pop('DW_CLIFF_ATTEMPT', None)
        if mode == 'formations' and case.get('source_regularize'):
            env['DW_CLIFF_SOURCE_REGULARIZE'] = '1'
        if mode == 'formations' and case.get('owner_source_probe'):
            env['DW_CLIFF_OWNER_SOURCE_PROBE'] = str(directory / (name + '.owner-sources.json'))
        if mode == 'formations' and case.get('invalid_probe'):
            env['DW_CLIFF_INVALID_PROBE'] = str(directory / (name + '.invalid.json'))
        if mode == 'formations' and case.get('boolean_source_restore'):
            env['DW_CLIFF_BOOLEAN_SOURCE_RESTORE'] = '1'
        if mode == 'formations' and case.get('early_target'):
            env['DW_CLIFF_EARLY_TARGET'] = '1'
        if mode == 'formations' and case.get('cap_connected_domain'):
            env['DW_CLIFF_CAP_CONNECTED_DOMAIN'] = '1'
        if mode == 'formations' and case.get('source_shared_edges'):
            env['DW_CLIFF_SOURCE_SHARED_EDGES'] = '1'
        if mode == 'formations' and case.get('source_reuse'):
            env['DW_CLIFF_SOURCE_REUSE'] = '1'
        if mode == 'formations' and case.get('source_retained_band'):
            env['DW_CLIFF_SOURCE_RETAINED_BAND'] = '1'
        if mode == 'formations' and case.get('source_affine_envelope'):
            env['DW_CLIFF_SOURCE_AFFINE_ENVELOPE'] = '1'
        if mode == 'formations' and case.get('source_vertex_blend'):
            env['DW_CLIFF_SOURCE_VERTEX_BLEND'] = '1'
        if mode == 'formations' and case.get('source_node_blend'):
            env['DW_CLIFF_SOURCE_NODE_BLEND'] = '1'
        if mode == 'formations' and case.get('exact_contacts'):
            env['DW_CLIFF_EXACT_CONTACTS'] = '1'
        if mode == 'formations' and case.get('source_snap_round'):
            env['DW_CLIFF_SOURCE_SNAP_ROUND'] = '1'
        if mode == 'formations' and case.get('source_shared_cuts'):
            env['DW_CLIFF_SOURCE_SHARED_CUTS'] = '1'
        if mode == 'formations' and case.get('source_partition'):
            env['DW_CLIFF_SOURCE_PARTITION'] = '1'
        if mode == 'formations' and case.get('chunk_source_planes'):
            env['DW_CLIFF_CHUNK_SOURCE_PLANES'] = '1'
        if mode == 'formations' and case.get('chunk_source_probe'):
            env['DW_CLIFF_CHUNK_SOURCE_PROBE'] = str(directory / (name + '.sources.json'))
        if mode == 'formations' and case.get('join_single_round'):
            env['DW_CLIFF_JOIN_SINGLE_ROUND'] = '1'
        if mode == 'formations' and case.get('precise_join'):
            env['DW_CLIFF_PRECISE_JOIN'] = '1'
        if mode == 'formations' and case.get('assembly_probe'):
            env['DW_CLIFF_ASSEMBLY_PROBE'] = str(directory / (name + '.assembly.json'))
        if mode == 'formations' and case.get('boolean_source_checked'):
            env['DW_CLIFF_BOOLEAN_SOURCE_CHECKED'] = '1'
        if mode == 'formations' and case.get('boolean_vertex_repair'):
            env['DW_CLIFF_BOOLEAN_VERTEX_REPAIR'] = '1'
        if mode == 'formations' and case.get('boolean_float_repair'):
            env['DW_CLIFF_BOOLEAN_FLOAT_REPAIR'] = '1'
        if mode == 'formations' and case.get('solid_boolean'):
            env['DW_CLIFF_SOLID_BOOLEAN'] = '1'
            for field, flag in (('boolean_padding', 'DW_CLIFF_BOOLEAN_PADDING'), ('boolean_tolerance', 'DW_CLIFF_BOOLEAN_TOLERANCE')):
                if field in case:
                    env[flag] = str(case[field])
        if mode == 'formations' and case.get('roof_contours'):
            env['DW_CLIFF_POLYGON_CONTOURS'] = '1'
        if mode == 'formations' and case.get('world_grid'):
            env['DW_CLIFF_WORLD_GRID'] = '1'
        if mode == 'formations' and case.get('roof_world'):
            env['DW_CLIFF_ROOF_WORLD'] = '1'
        if mode == 'formations' and case.get('roof_shell'):
            env['DW_CLIFF_ROOF_SHELL'] = '1'
        if mode == 'formations' and case.get('roof_chunks'):
            env['DW_CLIFF_ROOF_CHUNKS'] = '1'
        if mode == 'formations' and case.get('roof_region'):
            env['DW_CLIFF_ROOF_REGION'] = '1'
        if mode == 'formations' and case.get('ear_weld'):
            env['DW_CLIFF_EAR_WELD'] = '1'
        if mode == 'formations' and case.get('roof_boundary_grades'):
            env['DW_CLIFF_ROOF_BOUNDARY_GRADES'] = '1'
        if mode == 'formations' and case.get('roof_collar'):
            env['DW_CLIFF_ROOF_COLLAR'] = '1'
        if mode == 'formations' and case.get('grade_pruning') is False:
            env['DW_CLIFF_NO_GRADE_PRUNE'] = '1'
        if mode == 'formations' and case.get('base_context'):
            env['DW_CLIFF_BASE_CONTEXT'] = '1'
        if mode == 'formations' and case.get('roof_merged'):
            env['DW_CLIFF_ROOF_MERGED'] = '1'
        if mode == 'formations' and case.get('require_new_roof'):
            env['DW_CLIFF_REQUIRE_NEW_ROOF'] = '1'
        if mode == 'formations' and case.get('roof_envelope'):
            env['DW_CLIFF_ROOF_ENVELOPE'] = '1'
        if mode == 'formations' and case.get('roof_constrained'):
            env['DW_CLIFF_ROOF_CONSTRAINED'] = '1'
        if mode == 'formations' and selected_roofs.get(case['id']) == '0':
            env['DW_CLIFF_ROOF_PREVIOUS'] = '1'
        if mode == 'formations' and 'attempt' in case:
            env['DW_CLIFF_ATTEMPT'] = str(case['attempt'])
        if name == 'formations' and case['id'] in selections:
            selected = selections[case['id']]
            if selected['outcome'] == 'applied':
                env['DW_CLIFF_ATTEMPT'] = selected['result']['attempts']
        if diagnostic and mode == 'formations':
            normal = (directory / 'formations.log').read_text()
            selected = re.search(r'FORMATION_RESULT outcome=applied attempts=(\d+)', normal)
            assert selected, 'Missing successful normal-view attempt'
            env['DW_CLIFF_ATTEMPT'] = selected[1]
        if diagnostic == 'wire':
            env['DW_CLIFF_WIRE'] = '1'
        elif diagnostic == 'top':
            env['DW_CLIFF_MASSING'] = 'top'
        elif diagnostic == 'inspect':
            source = (directory / 'formations.log').read_text()
            target = re.search(r'inspect_x=([^ ]+) inspect_z=([^\s]+)', source)
            assert target, 'Applied section lacks a reproducible inspection target'
            env['DW_CLIFF_INSPECT_TARGET'] = target[1] + ',' + target[2]
        args = [str(root / 'build/deathward_cliff_alternatives'), '--mute', '--smoke',
                '--theme', 'canyon', '--style', 'original', '--scene', 'profile-works',
                '--frames', '60', '--screenshot', str(directory / (name + '.png'))]
        with (directory / (name + '.log')).open('w') as log:
            run = subprocess.run(args, cwd=root, env=env, stdout=log, stderr=subprocess.STDOUT)
        source = (directory / (name + '.log')).read_text()
        row = dict(case=case['id'], mode=name, exit_code=run.returncode)
        base = re.search(r'FORMATION_BASELINE geometry_and_scenery_hash=(\d+)', source)
        if base:
            if baseline is None:
                baseline = base[1]
            assert baseline == base[1], 'A/preview baseline geometry or scenery differs'
        match = re.search(r'FORMATION_FALLBACK reason="([^"]+)"', source)
        if run.returncode:
            row['outcome'] = 'failed'
        elif mode == 'original':
            row['outcome'] = 'baseline'
        elif match:
            row.update(outcome='fallback', reason=match[1])
            final = re.search(r'FORMATION_RESULT outcome=fallback geometry_and_scenery_hash=(\d+)', source)
            assert final and final[1] == baseline, 'Fallback changed A geometry/scenery'
        else:
            assert 'FORMATION_RESULT outcome=applied' in source, 'Missing applied/fallback result'
            assert 'PLATEAU_CAP_SURFACE ' in source
            assert 'FORMATION_SCENERY_REPLAY identical_placements=PASS' in source
            row['outcome'] = 'applied'
        if name == 'formations' and case['id'] in selections:
            expected = selections[case['id']]['result']
            final = re.search(r'FORMATION_RESULT outcome=applied attempts=(\d+) section_key=(\d+) geometry_and_scenery_hash=(\d+)', source)
            if selections[case['id']]['outcome'] == 'applied':
                assert final and final[1] == expected['attempts'] and final[2] == expected['section_key'] and final[3] == expected['geometry_and_scenery_hash'], 'Native selection differs from headless audit'
            else:
                assert row['outcome'] == 'fallback'
                assert re.search(r'FORMATION_RESULT outcome=fallback geometry_and_scenery_hash=(\d+)', source)[1] == expected['geometry_and_scenery_hash']
            row['selection'] = 'headless_audit'
        results.append(row)
        if name == 'formations':
            outcome = row['outcome']
        print(case['id'], name, row['outcome'], row.get('reason', ''), flush=True)
    return results
completed = {}
with ThreadPoolExecutor(max_workers=max(1, options.jobs)) as pool:
    tasks = {pool.submit(capture, case): case['id'] for case in cases}
    for future in as_completed(tasks):
        completed[tasks[future]] = future.result()
        rows = [row for case in cases for row in completed.get(case['id'], [])]
        (out / 'capture-results.json').write_text(json.dumps(rows, indent=2) + '\n')
assert hashlib.sha256(binary.read_bytes()).hexdigest() == binary_hash, 'Binary changed during the capture batch'
