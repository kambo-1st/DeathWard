#!/usr/bin/env python3
"""Sequential comparison with a saved pre-optimization native audit executable."""
from pathlib import Path
import argparse
import hashlib
import json
import os
import re
import statistics
import subprocess

root=Path(__file__).resolve().parents[2]
parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('--baseline-binary',type=Path,required=True)
parser.add_argument('--case-file',type=Path,help='One case or a case manifest with --case-id')
parser.add_argument('--case-id')
parser.add_argument('--output-dir',type=Path,default=root/'docs/reports/cliff-formations/optimization')
options=parser.parse_args()
options.output_dir.mkdir(parents=True,exist_ok=True)
case=dict(id='seed404-floor3-room2',seed=404,floor=3,room=2,attempt=2)
if options.case_file:
    data=json.loads(options.case_file.read_text())
    choices=data if isinstance(data,list) else [data]
    if options.case_id:choices=[c for c in choices if c['id']==options.case_id]
    assert len(choices)==1,'Select exactly one benchmark case'
    case=choices[0]
flags=dict(boolean_source_restore='DW_CLIFF_BOOLEAN_SOURCE_RESTORE',early_target='DW_CLIFF_EARLY_TARGET',cap_connected_domain='DW_CLIFF_CAP_CONNECTED_DOMAIN',source_shared_edges='DW_CLIFF_SOURCE_SHARED_EDGES',source_reuse='DW_CLIFF_SOURCE_REUSE',source_retained_band='DW_CLIFF_SOURCE_RETAINED_BAND',boolean_source_checked='DW_CLIFF_BOOLEAN_SOURCE_CHECKED',boolean_vertex_repair='DW_CLIFF_BOOLEAN_VERTEX_REPAIR',source_affine_envelope='DW_CLIFF_SOURCE_AFFINE_ENVELOPE',source_vertex_blend='DW_CLIFF_SOURCE_VERTEX_BLEND',source_node_blend='DW_CLIFF_SOURCE_NODE_BLEND',exact_contacts='DW_CLIFF_EXACT_CONTACTS',source_snap_round='DW_CLIFF_SOURCE_SNAP_ROUND',source_shared_cuts='DW_CLIFF_SOURCE_SHARED_CUTS',source_regularize='DW_CLIFF_SOURCE_REGULARIZE',source_partition='DW_CLIFF_SOURCE_PARTITION',chunk_source_planes='DW_CLIFF_CHUNK_SOURCE_PLANES',join_single_round='DW_CLIFF_JOIN_SINGLE_ROUND',precise_join='DW_CLIFF_PRECISE_JOIN',boolean_float_repair='DW_CLIFF_BOOLEAN_FLOAT_REPAIR',solid_boolean='DW_CLIFF_SOLID_BOOLEAN',roof_contours='DW_CLIFF_POLYGON_CONTOURS',roof_chunks='DW_CLIFF_ROOF_CHUNKS',roof_region='DW_CLIFF_ROOF_REGION',ear_weld='DW_CLIFF_EAR_WELD',roof_boundary_grades='DW_CLIFF_ROOF_BOUNDARY_GRADES',roof_merged='DW_CLIFF_ROOF_MERGED',roof_collar='DW_CLIFF_ROOF_COLLAR',roof_shell='DW_CLIFF_ROOF_SHELL',
           world_grid='DW_CLIFF_WORLD_GRID',roof_world='DW_CLIFF_ROOF_WORLD',base_context='DW_CLIFF_BASE_CONTEXT',
           roof_envelope='DW_CLIFF_ROOF_ENVELOPE',roof_constrained='DW_CLIFF_ROOF_CONSTRAINED',require_new_roof='DW_CLIFF_REQUIRE_NEW_ROOF')
binaries={'before':options.baseline_binary.resolve(),'optimized':root/'build/deathward_formation_audit'}
fingerprints={key:hashlib.sha256(path.read_bytes()).hexdigest() for key,path in binaries.items()}
rows=[]
for repetition in range(3):
    for mode in (('before','optimized') if repetition%2==0 else ('optimized','before')):
        env=dict(os.environ,DW_CLIFF_ATTEMPT=str(case['attempt']),DW_CLIFF_BACKING='blended')
        for key in ('DW_CLIFF_PROFILE','DW_CLIFF_ROOF_ARRANGEMENT','DW_CLIFF_REGION_PROBE','DW_CLIFF_CHUNK_PROBE','DW_CLIFF_INVALID_PROBE','DW_CLIFF_INTERFACE_PROBE','DW_CLIFF_VERIFY_WELD','DW_CLIFF_VERIFY_SUPPORT','DW_CLIFF_ROOF_PREVIOUS','DW_CLIFF_SECTION','DW_CLIFF_VERIFY_SIMPLIFIER','DW_CLIFF_NO_GRADE_PRUNE','DW_CLIFF_SOLID_BOOLEAN','DW_CLIFF_BOOLEAN_RAW', 'DW_CLIFF_BOOLEAN_SOURCE_CHECKED', 'DW_CLIFF_BOOLEAN_VERTEX_REPAIR', 'DW_CLIFF_BOOLEAN_FLOAT_REPAIR', 'DW_CLIFF_TOP_PROBE', 'DW_CLIFF_PRECISE_JOIN', 'DW_CLIFF_ASSEMBLY_PROBE', 'DW_CLIFF_JOIN_SINGLE_ROUND', 'DW_CLIFF_CHUNK_SOURCE_PROBE', 'DW_CLIFF_SOURCE_RETAINED_BAND', 'DW_CLIFF_SOURCE_AFFINE_ENVELOPE', 'DW_CLIFF_SOURCE_VERTEX_BLEND', 'DW_CLIFF_SOURCE_NODE_BLEND', 'DW_CLIFF_EXACT_CONTACTS', 'DW_CLIFF_SOURCE_SNAP_ROUND', 'DW_CLIFF_SOURCE_SHARED_CUTS', 'DW_CLIFF_SOURCE_REGULARIZE', 'DW_CLIFF_OWNER_SOURCE_PROBE', 'DW_CLIFF_SOURCE_PARTITION', 'DW_CLIFF_CHUNK_SOURCE_PLANES','DW_CLIFF_BOOLEAN_PADDING','DW_CLIFF_BOOLEAN_TOLERANCE',*flags.values()):
            env.pop(key,None)
        for key,flag in flags.items():
            if case.get(key):env[flag]='1'
        if case.get('solid_boolean'):
            for field,flag in (('boolean_padding','DW_CLIFF_BOOLEAN_PADDING'),('boolean_tolerance','DW_CLIFF_BOOLEAN_TOLERANCE')):
                if field in case:env[flag]=str(case[field])
        if case.get('grade_pruning') is False:env['DW_CLIFF_NO_GRADE_PRUNE']='1'
        log=options.output_dir/f'construction-{mode}-{repetition}.log'
        with log.open('w') as stream:
            subprocess.run([str(binaries[mode]),str(case['seed']),str(case['floor']),str(case['room'])],env=env,cwd=root,stdout=stream,stderr=subprocess.STDOUT,check=True)
        source=log.read_text()
        fields=dict(re.findall(r'(\w+)=([^ ]+)',re.findall(r'^FORMATION_CONSTRUCTION (.+)$',source,re.M)[-1]))
        final=re.findall(r'FORMATION_RESULT outcome=applied .*geometry_and_scenery_hash=(\d+)',source)[-1]
        baseline=float(re.findall(r'^FORMATION_BASELINE_CONSTRUCTION ms=([\d.e+-]+)',source,re.M)[-1])
        row=dict(mode=mode,repetition=repetition,construction_ms=float(fields['construction_ms']),
                 validation_ms=float(fields['validation_ms']),baseline_ms=baseline,geometry_and_scenery_hash=final,log=log.name)
        rows.append(row);print(mode,repetition,row['construction_ms'],flush=True)
assert len({row['geometry_and_scenery_hash'] for row in rows})==1
for key,path in binaries.items():assert hashlib.sha256(path.read_bytes()).hexdigest()==fingerprints[key]
medians={mode:statistics.median(row['construction_ms'] for row in rows if row['mode']==mode) for mode in binaries}
status=dict(case=case,binary_sha256=fingerprints,trials=rows,median_construction_ms=medians,
            optimized_over_before=medians['optimized']/medians['before'],
            optimized_over_A_lower_bound=statistics.median(row['baseline_ms']+row['construction_ms'] for row in rows if row['mode']=='optimized')/statistics.median(row['baseline_ms'] for row in rows if row['mode']=='optimized'),
            production_enabled=False,scope=f"One locked selected section ({case['id']}, candidate {case['attempt']}); three sequential alternating trials per binary, same mesh/scenery hash. Post-build validation and replay excluded; required constructive legality checks remain in construction time. Not frame-time or broad rollout acceptance.")
(options.output_dir/'construction.json').write_text(json.dumps(status,indent=2)+'\n')
print('Construction comparison',medians,'ratio',status['optimized_over_before'],flush=True)
