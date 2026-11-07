#!/usr/bin/env python3
"""Run the native seeded-preview geometry/replay path without a render window."""
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path
import argparse
import hashlib
import json
import os
import re
import subprocess

root = Path(__file__).resolve().parents[2]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--manifest', type=Path, default=root / 'docs/reports/cliff-formations/phase4/cases.json')
parser.add_argument('--jobs', type=int, default=2)
parser.add_argument('--binary', type=Path, default=root / 'build/deathward_formation_audit')
parser.add_argument('--cases', nargs='*', help='Case IDs; default is the full persisted matrix')
parser.add_argument('--output-dir', default='docs/reports/cliff-formations/phase4/geometry-audit')
parser.add_argument('--require-all', action='store_true')
options = parser.parse_args()
manifest_bytes = options.manifest.read_bytes()
cases = json.loads(manifest_bytes)
if options.cases:
    requested = set(options.cases)
    cases = [c for c in cases if c['id'] in requested]
    assert {c['id'] for c in cases} == requested, 'Unknown case IDs'
out = root / options.output_dir
out.mkdir(parents=True, exist_ok=True)
binary = options.binary.resolve()
fingerprint = hashlib.sha256(binary.read_bytes()).hexdigest()

def run(case):
    log = out / (case['id'] + '.log')
    env = dict(os.environ,DW_CLIFF_BACKING="blended")
    for key in ('DW_CLIFF_JOINT_WHOLE_SOURCE', 'DW_CLIFF_JOINT_TERRAIN_JOIN', 'DW_CLIFF_JOINT_FIXTURE', 'DW_CLIFF_JOINT_PROBE', 'DW_CLIFF_ATTEMPT', 'DW_CLIFF_SECTION', 'DW_CLIFF_FREEZE_SURROUNDINGS', 'DW_CLIFF_INTERACTIVE',
                'DW_CLIFF_WIRE', 'DW_CLIFF_MASSING', 'DW_CLIFF_INSPECT_TARGET', 'DW_CLIFF_ROOF_PREVIOUS',
                'DW_CLIFF_SOLID_BOOLEAN', 'DW_CLIFF_BOOLEAN_RAW', 'DW_CLIFF_BOOLEAN_SOURCE_RESTORE', 'DW_CLIFF_BOOLEAN_SOURCE_CHECKED', 'DW_CLIFF_BOOLEAN_VERTEX_REPAIR', 'DW_CLIFF_BOOLEAN_FLOAT_REPAIR', 'DW_CLIFF_TOP_PROBE', 'DW_CLIFF_PRECISE_JOIN', 'DW_CLIFF_ASSEMBLY_PROBE', 'DW_CLIFF_JOIN_SINGLE_ROUND', 'DW_CLIFF_CHUNK_SOURCE_PROBE', 'DW_CLIFF_EARLY_TARGET', 'DW_CLIFF_CAP_CONNECTED_DOMAIN', 'DW_CLIFF_SOURCE_SHARED_EDGES', 'DW_CLIFF_SOURCE_REUSE', 'DW_CLIFF_SOURCE_RETAINED_BAND', 'DW_CLIFF_SOURCE_AFFINE_ENVELOPE', 'DW_CLIFF_SOURCE_VERTEX_BLEND', 'DW_CLIFF_SOURCE_NODE_BLEND', 'DW_CLIFF_EXACT_CONTACTS', 'DW_CLIFF_SOURCE_SNAP_ROUND', 'DW_CLIFF_SOURCE_SHARED_CUTS', 'DW_CLIFF_SOURCE_REGULARIZE', 'DW_CLIFF_OWNER_SOURCE_PROBE', 'DW_CLIFF_SOURCE_PARTITION', 'DW_CLIFF_CHUNK_SOURCE_PLANES', 'DW_CLIFF_BOOLEAN_PADDING', 'DW_CLIFF_BOOLEAN_TOLERANCE',
                'DW_CLIFF_BASE_CONTEXT', 'DW_CLIFF_EXACT_PROBE', 'DW_CLIFF_ROOF_CONSTRAINED',
                'DW_CLIFF_ROOF_ENVELOPE', 'DW_CLIFF_ROOF_MERGED', 'DW_CLIFF_REQUIRE_NEW_ROOF',
                    'DW_CLIFF_POLYGON_CONTOURS', 'DW_CLIFF_ROOF_ARRANGEMENT', 'DW_CLIFF_ROOF_CHUNKS', 'DW_CLIFF_CHUNK_PROBE', 'DW_CLIFF_ROOF_REGION', 'DW_CLIFF_REGION_PROBE', 'DW_CLIFF_EAR_WELD', 'DW_CLIFF_ROOF_BOUNDARY_GRADES', 'DW_CLIFF_INVALID_PROBE', 'DW_CLIFF_INTERFACE_PROBE', 'DW_CLIFF_ROOF_COLLAR', 'DW_CLIFF_NO_GRADE_PRUNE', 'DW_CLIFF_ROOF_SHELL', 'DW_CLIFF_ROOF_WORLD', 'DW_CLIFF_WORLD_GRID'):
        env.pop(key, None)
    if case.get('joint_whole_source'):
        env['DW_CLIFF_JOINT_WHOLE_SOURCE'] = '1'
    if case.get('joint_terrain_join'):
        env['DW_CLIFF_JOINT_TERRAIN_JOIN'] = '1'
        env['DW_CLIFF_JOINT_FIXTURE'] = str(out / (case['id'] + '.join.txt'))
        env['DW_CLIFF_JOINT_PROBE'] = str(out / (case['id'] + '.join.json'))
    if case.get('boolean_source_restore'):
        env['DW_CLIFF_BOOLEAN_SOURCE_RESTORE'] = '1'
    if case.get('early_target'):
        env['DW_CLIFF_EARLY_TARGET'] = '1'
    if case.get('cap_connected_domain'):
        env['DW_CLIFF_CAP_CONNECTED_DOMAIN'] = '1'
    if case.get('source_shared_edges'):
        env['DW_CLIFF_SOURCE_SHARED_EDGES'] = '1'
    if case.get('source_reuse'):
        env['DW_CLIFF_SOURCE_REUSE'] = '1'
    if case.get('source_retained_band'):
        env['DW_CLIFF_SOURCE_RETAINED_BAND'] = '1'
    if case.get('source_affine_envelope'):
        env['DW_CLIFF_SOURCE_AFFINE_ENVELOPE'] = '1'
    if case.get('source_vertex_blend'):
        env['DW_CLIFF_SOURCE_VERTEX_BLEND'] = '1'
    if case.get('source_node_blend'):
        env['DW_CLIFF_SOURCE_NODE_BLEND'] = '1'
    if case.get('exact_contacts'):
        env['DW_CLIFF_EXACT_CONTACTS'] = '1'
    if case.get('source_snap_round'):
        env['DW_CLIFF_SOURCE_SNAP_ROUND'] = '1'
    if case.get('source_shared_cuts'):
        env['DW_CLIFF_SOURCE_SHARED_CUTS'] = '1'
    if case.get('source_regularize'):
        env['DW_CLIFF_SOURCE_REGULARIZE'] = '1'
    if case.get('owner_source_probe'):
        env['DW_CLIFF_OWNER_SOURCE_PROBE'] = str(out / (case['id'] + '.owner-sources.json'))
    if case.get('invalid_probe'):
        env['DW_CLIFF_INVALID_PROBE'] = str(out / (case['id'] + '.invalid.json'))
    if case.get('source_partition'):
        env['DW_CLIFF_SOURCE_PARTITION'] = '1'
    if case.get('chunk_source_planes'):
        env['DW_CLIFF_CHUNK_SOURCE_PLANES'] = '1'
    if case.get('chunk_source_probe'):
        env['DW_CLIFF_CHUNK_SOURCE_PROBE'] = str(out / (case['id'] + '.sources.json'))
    if case.get('join_single_round'):
        env['DW_CLIFF_JOIN_SINGLE_ROUND'] = '1'
    if case.get('precise_join'):
        env['DW_CLIFF_PRECISE_JOIN'] = '1'
    if case.get('assembly_probe'):
        env['DW_CLIFF_ASSEMBLY_PROBE'] = str(out / (case['id'] + '.assembly.json'))
    if case.get('boolean_source_checked'):
        env['DW_CLIFF_BOOLEAN_SOURCE_CHECKED'] = '1'
    if case.get('boolean_vertex_repair'):
        env['DW_CLIFF_BOOLEAN_VERTEX_REPAIR'] = '1'
    if case.get('boolean_float_repair'):
        env['DW_CLIFF_BOOLEAN_FLOAT_REPAIR'] = '1'
    if case.get('solid_boolean'):
        env['DW_CLIFF_SOLID_BOOLEAN'] = '1'
        for field, flag in (('boolean_padding', 'DW_CLIFF_BOOLEAN_PADDING'), ('boolean_tolerance', 'DW_CLIFF_BOOLEAN_TOLERANCE')):
            if field in case:
                env[flag] = str(case[field])
    env['DW_CLIFF_EXACT_PROBE'] = str(out / (case['id'] + '.core.json'))
    if case.get('world_grid'):
        env['DW_CLIFF_WORLD_GRID'] = '1'
    if case.get('roof_world'):
        env['DW_CLIFF_ROOF_WORLD'] = '1'
    if case.get('roof_shell'):
        env['DW_CLIFF_ROOF_SHELL'] = '1'
    if case.get('roof_contours'):
        env['DW_CLIFF_POLYGON_CONTOURS'] = '1'
    if case.get('roof_chunks'):
        env['DW_CLIFF_ROOF_CHUNKS'] = '1'
        env['DW_CLIFF_CHUNK_PROBE'] = str(out / (case['id'] + '.chunks.json'))
    if case.get('roof_region'):
        env['DW_CLIFF_ROOF_REGION'] = '1'
        if not case.get('roof_chunks'):
            env['DW_CLIFF_REGION_PROBE'] = str(out / (case['id'] + '.region.json'))
    if case.get('ear_weld'):
        env['DW_CLIFF_EAR_WELD'] = '1'
    if case.get('roof_boundary_grades'):
        env['DW_CLIFF_ROOF_BOUNDARY_GRADES'] = '1'
    if case.get('roof_collar'):
        env['DW_CLIFF_ROOF_COLLAR'] = '1'
    if case.get('grade_pruning') is False:
        env['DW_CLIFF_NO_GRADE_PRUNE'] = '1'
    if case.get('base_context'):
        env['DW_CLIFF_BASE_CONTEXT'] = '1'
    if case.get('roof_merged'):
        env['DW_CLIFF_ROOF_MERGED'] = '1'
    if case.get('require_new_roof'):
        env['DW_CLIFF_REQUIRE_NEW_ROOF'] = '1'
    if case.get('roof_envelope'):
        env['DW_CLIFF_ROOF_ENVELOPE'] = '1'
    if case.get('roof_constrained'):
        env['DW_CLIFF_ROOF_CONSTRAINED'] = '1'
    if 'attempt' in case:
        env['DW_CLIFF_ATTEMPT'] = str(case['attempt'])
    with log.open('w') as stream:
        process = subprocess.run([str(binary), str(case['seed']), str(case['floor']), str(case['room'])],
                                 cwd=root, env=env, stdout=stream, stderr=subprocess.STDOUT)
    source = log.read_text()
    final = re.findall(r'^FORMATION_RESULT (.+)$', source, re.M)
    assert process.returncode == 0 and len(final) == 1, case['id']
    fields = dict(re.findall(r'(\w+)=([^ ]+)', final[0]))
    outcome = fields['outcome']
    assert outcome in ('applied', 'fallback')
    if outcome == 'applied':
        assert 'PLATEAU_CAP_SURFACE ' in source
        assert 'PLATEAU_ASSEMBLY_REPLAY identical_triangles=PASS' in source
        assert 'FORMATION_SCENERY_REPLAY identical_placements=PASS' in source
    else:
        baseline = re.search(r'FORMATION_BASELINE geometry_and_scenery_hash=(\d+)', source)[1]
        assert fields['geometry_and_scenery_hash'] == baseline
    print(case['id'], outcome, flush=True)
    return dict(case=case['id'], outcome=outcome, result=fields, log=log.name)

results = {}
with ThreadPoolExecutor(max_workers=max(1, options.jobs)) as pool:
    tasks = {pool.submit(run, case): case['id'] for case in cases}
    for task in as_completed(tasks):
        results[tasks[task]] = task.result()
        ledger = [results[c['id']] for c in cases if c['id'] in results]
        (out / 'results.json').write_text(json.dumps(dict(
            binary_sha256=fingerprint,
            manifest=str(options.manifest.resolve()),
            manifest_sha256=hashlib.sha256(manifest_bytes).hexdigest(),
            effective_cases=cases,
            cases=ledger), indent=2) + '\n')
assert hashlib.sha256(binary.read_bytes()).hexdigest() == fingerprint, 'Audit binary changed during the batch'
passed = sum(row['outcome'] == 'applied' for row in results.values())
print(f'{passed}/{len(cases)} generated; {len(cases)-passed} unchanged fallbacks')
if options.require_all and passed != len(cases):
    raise SystemExit(1)
