#!/usr/bin/env python3
"""Verify optimized construction against saved geometry and brute-force oracles."""
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path
import argparse
import hashlib
import json
import os
import re
import subprocess

root=Path(__file__).resolve().parents[2]
parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('--jobs',type=int,default=4)
parser.add_argument('--output-dir',type=Path,default=root/'docs/reports/cliff-formations/optimization')
options=parser.parse_args()
phase=root/'docs/reports/cliff-formations/phase4'
manifest=json.loads((phase/'cases.json').read_text())
reference=json.loads((phase/'geometry-audit/results.json').read_text())
expected={row['case']:row for row in reference['cases']}
binary=root/'build/deathward_formation_audit'
fingerprint=hashlib.sha256(binary.read_bytes()).hexdigest()
options.output_dir.mkdir(parents=True,exist_ok=True)

def check(case):
    old=expected[case['id']]['result']
    source=(phase/case['id']/'formations.log').read_text()
    recipe=re.findall(r'FORMATION_ROOF_RECIPE finished=(\d+)',source)[-1]
    env=dict(os.environ,DW_CLIFF_ATTEMPT=old['attempts'],DW_CLIFF_BACKING='blended',
             DW_CLIFF_VERIFY_WELD='1',DW_CLIFF_VERIFY_SUPPORT='1')
    for key in ('DW_CLIFF_SECTION','DW_CLIFF_PROFILE','DW_CLIFF_ROOF_PREVIOUS'):
        env.pop(key,None)
    if recipe=='0':env['DW_CLIFF_ROOF_PREVIOUS']='1'
    log=options.output_dir/(case['id']+'.log')
    with log.open('w') as stream:
        subprocess.run([str(binary),str(case['seed']),str(case['floor']),str(case['room'])],cwd=root,env=env,
                       stdout=stream,stderr=subprocess.STDOUT,check=True)
    source=log.read_text()
    result=re.search(r'FORMATION_RESULT outcome=applied attempts=(\d+) section_key=(\d+) geometry_and_scenery_hash=(\d+)',source)
    assert result and result[1]==old['attempts'] and result[2]==old['section_key'] and result[3]==old['geometry_and_scenery_hash'],case['id']
    assert 'PLATEAU_ASSEMBLY_REPLAY identical_triangles=PASS' in source
    assert 'FORMATION_SCENERY_REPLAY identical_placements=PASS' in source
    support=re.findall(r'FORMATION_SUPPORT_OPTIMIZATION triangles=(\d+) exact_reference=PASS',source)
    assert len(support)>=2 and support[-1]==support[-2],case['id']
    print(case['id'],'unchanged mesh/scenery hash; exact support and weld oracles PASS',flush=True)
    return dict(case=case['id'],geometry_and_scenery_hash=result[3],support_triangles=int(support[-1]),
                roof_recipe=recipe,log=log.name)

results={}
with ThreadPoolExecutor(max_workers=max(1,options.jobs)) as pool:
    tasks={pool.submit(check,case):case['id'] for case in manifest}
    for future in as_completed(tasks):results[tasks[future]]=future.result()
assert hashlib.sha256(binary.read_bytes()).hexdigest()==fingerprint
status=dict(audit_binary_sha256=fingerprint,reference_audit_binary_sha256=reference['binary_sha256'],
            source_sha256={str(path.relative_to(root)):hashlib.sha256(path.read_bytes()).hexdigest() for path in [
                root/'tools/cliff_experiments/RockFormations.cpp',root/'tools/cliff_experiments/PlateauSurface.cpp',root/'tools/cliff_experiments/FormationScenery.cpp']},
            cases=[results[case['id']] for case in manifest],production_enabled=False,
            scope='Twelve saved selected sections/roof recipes; exact geometry/scenery hashes, full strict audits/replay, brute-force support shell and every weld segment candidate compared. Does not establish new visual, boundary, neighbouring-section, frame-time or gameplay acceptance.',
            remaining=['Residual cap lips/facets','Rejected boundary cases','Coordinated neighbouring plateau interfaces',
                       'Further construction/render optimization and controlled performance acceptance',
                       'Gameplay/occlusion acceptance','Accepted old/new mode integration'])
(options.output_dir/'status.json').write_text(json.dumps(status,indent=2)+'\n')
print('Verified twelve optimized selected sections',flush=True)
