#!/usr/bin/env python3
"""Replay captured checked bodies and nominal half-spaces without world generation."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import struct
import subprocess


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('mesh', type=Path, help='Captured .boolean.json')
    parser.add_argument('--map', type=Path, dest='body_map')
    parser.add_argument('--binary', type=Path, required=True, help='CoverageReplay executable')
    parser.add_argument('--output-prefix', type=Path, required=True)
    parser.add_argument('--tolerance', type=float, default=8e-6)
    parser.add_argument('--raw', action='store_true')
    parser.add_argument('--simplify', action='store_true')
    parser.add_argument('--vertex-repair', action='store_true')
    parser.add_argument('--source-checked', action='store_true')
    parser.add_argument('--source-restore', action='store_true')
    args = parser.parse_args()
    if args.source_restore and not args.source_checked:
        parser.error('Source restoration requires --source-checked')
    if not 0 < args.tolerance <= .0001:
        parser.error('Tolerance must be positive and at most .0001 m')
    body_map = args.body_map or args.mesh.with_name(args.mesh.name.replace('.boolean.json', '.boolean-map.json'))
    mesh = json.loads(args.mesh.read_text())
    mapping = json.loads(body_map.read_text())
    if sum(mapping['body_faces']) != len(mesh['faces']):
        parser.error('Body face counts do not match the captured mesh')
    lines = [str(len(mesh['faces']))]
    for face in mesh['faces']:
        lines.append(' '.join(str(struct.unpack('<I', struct.pack('<f', value))[0])
                              for point in face for value in point))
    lines.append(str(len(mesh['volumes'])))
    for volume in mesh['volumes']:
        lines.extend([str(len(volume)), ' '.join(repr(value) for plane in volume for value in plane)])
    lines.extend([f"{mapping['body_begin']} {mapping['body_count']} {len(mapping['body_faces'])}",
                  ' '.join(map(str, mapping['body_faces']))])
    prefix = args.output_prefix.resolve()
    prefix.parent.mkdir(parents=True, exist_ok=True)
    env = {key: value for key, value in os.environ.items() if not key.startswith('DW_CLIFF_')}
    env.update(DW_CLIFF_ROOF_CHUNKS='1', DW_CLIFF_EXACT_CONTACTS='1',
               DW_CLIFF_BOOLEAN_FLOAT_REPAIR='1', DW_CLIFF_INVALID_PROBE=str(prefix))
    if args.raw:
        env['DW_CLIFF_BOOLEAN_RAW'] = '1'
    if args.source_checked:
        env['DW_CLIFF_BOOLEAN_SOURCE_CHECKED'] = '1'
    if args.source_restore:
        env['DW_CLIFF_BOOLEAN_SOURCE_RESTORE'] = '1'
    if args.vertex_repair:
        env['DW_CLIFF_BOOLEAN_VERTEX_REPAIR'] = '1'
    binary = args.binary.resolve()
    argv = [str(binary), '--boolean', repr(args.tolerance)]
    if args.simplify:
        argv.append('--simplify')
    result = subprocess.run(argv, env=env, input='\n'.join(lines) + '\n', text=True,
                            stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    Path(str(prefix) + '.log').write_text(result.stdout)
    status = dict(argv=argv, environment={k: v for k, v in env.items() if k.startswith('DW_CLIFF_')},
                  input=str(args.mesh), input_sha256=hashlib.sha256(args.mesh.read_bytes()).hexdigest(),
                  map_sha256=hashlib.sha256(body_map.read_bytes()).hexdigest(),
                  binary_sha256=hashlib.sha256(binary.read_bytes()).hexdigest(),
                  returncode=result.returncode, tail=result.stdout.splitlines()[-5:])
    Path(str(prefix) + '.status.json').write_text(json.dumps(status, indent=2) + '\n')
    print(json.dumps(status, indent=2))
    return result.returncode


if __name__ == '__main__':
    raise SystemExit(main())
