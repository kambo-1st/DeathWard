#!/usr/bin/env python3
"""Check an emitted mesh against a separately preserved nominal source union."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import struct
import subprocess


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('mesh',type=Path);parser.add_argument('reference',type=Path)
    parser.add_argument('--binary',type=Path,required=True)
    parser.add_argument('--output-prefix',type=Path,required=True)
    args=parser.parse_args();mesh=json.loads(args.mesh.read_text());reference=json.loads(args.reference.read_text())
    lines=[str(len(mesh['faces']))]
    for face in mesh['faces']:lines.append(' '.join(str(struct.unpack('<I',struct.pack('<f',v))[0]) for p in face for v in p))
    lines.append(str(len(reference['volumes'])))
    for volume in reference['volumes']:lines.extend([str(len(volume)),' '.join(repr(v) for p in volume for v in p)])
    env={k:v for k,v in os.environ.items() if not k.startswith('DW_CLIFF_')};env['DW_CLIFF_EXACT_CONTACTS']='1'
    binary=args.binary.resolve();run=subprocess.run([str(binary)],input='\n'.join(lines)+'\n',text=True,capture_output=True,env=env)
    output=run.stdout+run.stderr;args.output_prefix.parent.mkdir(parents=True,exist_ok=True)
    Path(str(args.output_prefix)+'.log').write_text(output)
    summaries=re.findall(r'^COVERAGE_REPLAY (.+)$',output,re.M)
    metrics=dict(re.findall(r'(\w+)=([^\s]+)',summaries[-1])) if summaries else None
    passes=run.returncode==0 and metrics is not None and metrics['buried']=='0' and metrics['detached']=='0'
    status=dict(scope='Complete saved emitted float mesh versus a separately preserved nominal constructed source union, through the unchanged native half-space/area validator. This is not complete immutable-original terrain/world/floor or assembly acceptance.',mesh=str(args.mesh),reference=str(args.reference),binary=str(binary),input_sha256={str(p):hashlib.sha256(p.read_bytes()).hexdigest() for p in [args.mesh,args.reference,binary]},returncode=run.returncode,metrics=metrics,reference_source_boundary_pass=passes,full_assembly_proved=False)
    Path(str(args.output_prefix)+'.status.json').write_text(json.dumps(status,indent=2)+'\n')
    print(f'{args.mesh.name}: separate source reference pass={passes}; {metrics}')
    return int(not passes)


if __name__=='__main__':raise SystemExit(main())
