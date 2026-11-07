#!/usr/bin/env python3
"""Launch the archived authored demo without inherited experiment settings."""
import os
from pathlib import Path
import sys
import tempfile

root = Path(__file__).resolve().parent
check = sys.argv[1:] == ['--check']
if sys.argv[1:] and not check:
    raise SystemExit('Usage: ./run.sh [--check]')
program = root / 'runtime/deathward_cliff_alternatives'
if not program.exists():
    raise SystemExit('Packaged executable missing. Run ./rebuild.sh first.')
env = {k: v for k, v in os.environ.items() if not k.startswith('DW_CLIFF_')}
env.update(DW_CLIFF_OPTION='formations', DW_CLIFF_DETAIL='1',
           DW_CLIFF_FREEZE_SURROUNDINGS='1')
if not check:
    env['DW_CLIFF_INTERACTIVE'] = '1'
session = Path(tempfile.mkdtemp(prefix='deathward-archived-canyon-'))
args = [str(program), '--mute', '--smoke', '--theme', 'canyon', '--style',
        'original', '--scene', 'profile-works', '--save', str(session/'preview.save')]
if check:
    args += ['--frames', '30', '--screenshot', str(session/'preview.png')]
print('Archived authored-wall prototype; generalized integration remains unfinished.', flush=True)
print('Preview files: '+str(session), flush=True)
os.chdir(root)
os.execve(program, args, env)
