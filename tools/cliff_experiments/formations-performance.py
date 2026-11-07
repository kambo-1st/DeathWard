#!/usr/bin/env python3
"""Measure sequential, uncapped native A/formation trials on one checked section."""
from pathlib import Path
import argparse
import hashlib
import json
import os
import platform
import re
import statistics
import subprocess

root = Path(__file__).resolve().parents[2]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--case', default='seed404-floor3-room2')
parser.add_argument('--repetitions', type=int, default=3)
parser.add_argument('--frames', type=int, default=480)
parser.add_argument('--output-dir', type=Path, default=root / 'docs/reports/cliff-formations/performance')
options = parser.parse_args()
assert options.repetitions >= 3 and options.frames >= 360
manifest = json.loads((root / 'docs/reports/cliff-formations/phase4/cases.json').read_text())
case = next(row for row in manifest if row['id'] == options.case)
audit = json.loads((root / 'docs/reports/cliff-formations/phase4/geometry-audit/results.json').read_text())
selection = next(row for row in audit['cases'] if row['case'] == options.case)
assert selection['outcome'] == 'applied'
assert audit['binary_sha256'] == hashlib.sha256((root / 'build/deathward_formation_audit').read_bytes()).hexdigest()
binary = root / 'build/deathward_cliff_alternatives'
fingerprint = hashlib.sha256(binary.read_bytes()).hexdigest()
options.output_dir.mkdir(parents=True, exist_ok=True)
rows = []
# Alternate order between repetitions; never overlap trials with one another.
for repetition in range(options.repetitions):
    for mode in (('original', 'formations') if repetition % 2 == 0 else ('formations', 'original')):
        name = f'{mode}-{repetition}'
        env = dict(os.environ, DW_CLIFF_LAYOUT='seeded', DW_CLIFF_OPTION=mode, DW_CLIFF_DETAIL='1',
                   DW_CLIFF_BACKING='blended', DW_CLIFF_SEED=str(case['seed']), DW_CLIFF_FLOOR=str(case['floor']),
                   DW_CLIFF_ROOM=str(case['room']), DW_CLIFF_ATTEMPT=selection['result']['attempts'],
                   DW_CLIFF_INSPECT_TARGET=f"{selection['result']['inspect_x']},{selection['result']['inspect_z']}",
                   DW_CLIFF_FRAME_BENCH='1')
        for key in ('DW_CLIFF_FREEZE_SURROUNDINGS', 'DW_CLIFF_INTERACTIVE', 'DW_CLIFF_SECTION', 'DW_CLIFF_WIRE',
                    'DW_CLIFF_MASSING', 'DW_CLIFF_ROOF_PREVIOUS', 'DW_CLIFF_BENCH'):
            env.pop(key, None)
        log = options.output_dir / (name + '.log')
        memory = options.output_dir / (name + '.resources')
        with log.open('w') as stream:
            subprocess.run(['/usr/bin/time', '-v', '-o', str(memory), str(binary), '--mute', '--smoke',
                            '--theme', 'canyon', '--style', 'original', '--scene', 'profile-works',
                            '--frames', str(options.frames)], cwd=root, env=env, stdout=stream,
                           stderr=subprocess.STDOUT, check=True)
        source = log.read_text()
        samples = [float(value) for value in re.findall(r'^CLIFF_FRAME sample=\d+ ms=([\d.e+-]+)', source, re.M)]
        assert len(samples) == options.frames - 120, (name, len(samples))
        ordered = sorted(samples)
        baseline = float(re.findall(r'^FORMATION_BASELINE_CONSTRUCTION ms=([\d.e+-]+)', source, re.M)[-1])
        row = dict(mode=mode, repetition=repetition, frames=len(samples), frame_ms=samples,
                   p95_ms=ordered[int((len(ordered)-1)*.95)], median_ms=statistics.median(samples),
                   baseline_construction_ms=baseline, log=log.name,
                   peak_process_rss_kib=int(re.search(r'Maximum resident set size \(kbytes\): (\d+)', memory.read_text())[1]))
        if mode == 'formations':
            fields = dict(re.findall(r'(\w+)=([^ ]+)', re.findall(r'^FORMATION_CONSTRUCTION (.+)$', source, re.M)[-1]))
            assert fields['replay_excluded'] == '1'
            final = re.findall(r'^FORMATION_RESULT outcome=applied .*geometry_and_scenery_hash=(\d+)', source, re.M)[-1]
            assert final == selection['result']['geometry_and_scenery_hash']
            row.update(construction_ms=float(fields['construction_ms']), validation_ms=float(fields['validation_ms']),
                       checked_ms=float(fields['checked_ms']), triangles=int(fields['triangles']))
        else:
            row['triangles'] = int(re.findall(r'^FORMATION_BASELINE_CONSTRUCTION .*triangles=(\d+)', source, re.M)[-1])
        rows.append(row)
        print(name, 'p95_ms', row['p95_ms'], flush=True)
assert hashlib.sha256(binary.read_bytes()).hexdigest() == fingerprint
plain = [r for r in rows if r['mode'] == 'original']
formed = [r for r in rows if r['mode'] == 'formations']
frame_ratio = statistics.median(r['p95_ms'] for r in formed) / statistics.median(r['p95_ms'] for r in plain)
# This is deliberately a lower bound: A's construction plus the measured replacement
# work excludes secondary contour-base construction and other dispatch overhead.
# If even this exceeds the target, the construction gate fails conclusively.
construction_ratio = statistics.median(r['baseline_construction_ms'] + r['construction_ms'] for r in formed) / statistics.median(r['baseline_construction_ms'] for r in plain)
renderer = re.findall(r'.*(?:Renderer:|GL_RENDERER).*', (options.output_dir / formed[0]['log']).read_text())
status = dict(case=case, capture_binary_sha256=fingerprint, trials=rows, hardware=dict(platform=platform.platform(),
              cpu=next((line.split(':',1)[1].strip() for line in Path('/proc/cpuinfo').read_text().splitlines() if line.startswith('model name')), platform.processor()),
              renderer=renderer), frames_per_trial=options.frames, warmup_frames=120, sequential=True,
              p95_ratio=frame_ratio, construction_ratio_lower_bound=construction_ratio,
              targets=dict(p95_ratio=1.10, construction_ratio=1.25),
              frame_gate_passed=frame_ratio<=1.10, construction_gate_passed=False if construction_ratio>1.25 else None,
              production_enabled=False,
              scope='One locked candidate; three alternating native trials per mode. Frame wall times include update, draw submission and presentation; not GPU timer queries. Timed validation includes strict topology, whole-face boundary coverage and sampled core route/ray/seam checks; replay is excluded. Required constructive validity/floor checks remain in construction time. Construction ratio is a lower bound, not a total generation estimate. RSS includes validation and replay. Other cases, occlusion/gameplay and deployment hardware remain unaccepted.')
(options.output_dir / 'status.json').write_text(json.dumps(status, indent=2)+'\n')
print('p95 ratio', frame_ratio, 'construction ratio lower bound', construction_ratio, flush=True)
