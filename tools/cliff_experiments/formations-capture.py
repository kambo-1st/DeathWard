#!/usr/bin/env python3
"""Capture the isolated wall and both wireframes with identical native settings."""
from pathlib import Path
import argparse
import os
import subprocess

root = Path(__file__).resolve().parents[2]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--output-dir', default='docs/reports/cliff-formations')
parser.add_argument('--massing', action='store_true', help='Also capture the neutral mesh diagnostic')
parser.add_argument('--detail', choices=('on','off'), default='off', help='Phase 3 detail/scenery; off preserves earlier capture recipes')
options = parser.parse_args()
out = root / options.output_dir
out.mkdir(parents=True, exist_ok=True)
args = [str(root / 'build/deathward_cliff_alternatives'), '--mute', '--smoke',
        '--theme', 'canyon', '--style', 'original', '--scene', 'profile-works',
        '--frames', '60']
modes = [('volumes', None), ('wireframe', '1'), ('triangles', 'triangles')]
if options.massing:
    modes.append(('massing', None))
    modes.append(('topview', None))
for name, wire in modes:
    env = dict(os.environ, DW_CLIFF_OPTION='formations', DW_CLIFF_FREEZE_SURROUNDINGS='1')
    env['DW_CLIFF_DETAIL'] = '1' if options.detail == 'on' else '0'
    for key in ['DW_CLIFF_WIRE', 'DW_CLIFF_BENCH', 'DW_CLIFF_MASSING']:
        env.pop(key, None)
    if wire:
        env['DW_CLIFF_WIRE'] = wire
    if name == 'massing':
        env['DW_CLIFF_MASSING'] = '1'
    if name == 'topview':
        env['DW_CLIFF_MASSING'] = 'top'
    with (out / (name + '.log')).open('w') as log:
        subprocess.run([*args, '--screenshot', str(out / (name + '.png'))], cwd=root,
                       env=env, stdout=log, stderr=subprocess.STDOUT, check=True)
    print('captured', name, flush=True)
