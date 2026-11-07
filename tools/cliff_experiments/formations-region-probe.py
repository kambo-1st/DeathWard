#!/usr/bin/env python3
"""Inspect complete source roof regions for locked seeded wall candidates."""
from pathlib import Path
import argparse
import hashlib
import json
import os
import re
import subprocess

root = Path(__file__).resolve().parents[2]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--manifest', type=Path, required=True)
parser.add_argument('--output-dir', type=Path, required=True)
parser.add_argument('--binary', type=Path, default=root / 'build/deathward_formation_audit')
options = parser.parse_args()
options.output_dir.mkdir(parents=True, exist_ok=True)
binary = options.binary.resolve()
fingerprint = hashlib.sha256(binary.read_bytes()).hexdigest()
rows = []
for case in json.loads(options.manifest.read_text()):
    destination = options.output_dir / (case['id'] + '.json')
    log = options.output_dir / (case['id'] + '.log')
    env = {k: v for k, v in os.environ.items() if not k.startswith('DW_CLIFF_')}
    with log.open('w') as stream:
        run = subprocess.run([str(binary), '--region-probe', str(case['seed']), str(case['floor']),
                              str(case['room']), str(case['attempt']), str(destination.resolve())],
                             cwd=root, env=env, stdout=stream, stderr=subprocess.STDOUT)
    matches = re.findall(r'^REGION_PLAN (.+)$', log.read_text(), re.M)
    row = dict(case=case['id'], exit_code=run.returncode, log=log.name)
    if run.returncode == 0:
        assert matches, 'Successful region probe lacks its result'
        row.update(probe=destination.name, metrics=dict(re.findall(r'(\w+)=([^\s]+)', matches[-1])))
    rows.append(row)
    (options.output_dir / 'results.json').write_text(json.dumps(dict(binary_sha256=fingerprint, cases=rows,
        scope='Source connectivity/footprint planning only. Does not prove a constructed or accepted regional roof.'), indent=2) + '\n')
    print(case['id'], 'planned' if run.returncode == 0 else 'rejected', flush=True)
assert hashlib.sha256(binary.read_bytes()).hexdigest() == fingerprint, 'Binary changed during region probes'
if any(row['exit_code'] for row in rows):
    raise SystemExit(1)
