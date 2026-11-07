#!/usr/bin/env python3
"""Export a captured terrain adapter and its rejected assembly for visual review.

The GLBs preserve triangle coordinates. They are inspection artifacts, not
accepted game assets; the native geometry/source/floor gates remain authoritative.
"""
import argparse
import json
import math
from pathlib import Path
import struct


def read_fixture(path):
    tokens = iter(path.read_text().split())
    version = next(tokens)
    if version not in ('DWADAPTER1', 'DWADAPTER2'):
        raise ValueError('Expected a complete adapter fixture')
    header = [next(tokens) for _ in range(8)]
    bounds = [float(next(tokens)) for _ in range(6)]
    flags = [next(tokens) for _ in range(5)] if version == 'DWADAPTER2' else []

    def polygons():
        return [[[float(next(tokens)) for _ in range(3)]
                 for _ in range(int(next(tokens)))]
                for _ in range(int(next(tokens)))]

    return polygons(), polygons(), {'version': version, 'flags': flags,
                                    'state': header, 'bounds': bounds}


def triangles(polys):
    return [[p[0], p[k], p[k + 1]] for p in polys for k in range(1, len(p) - 1)]


def write_glb(path, groups):
    binary = bytearray()
    doc = {'asset': {'version': '2.0', 'generator': 'DeathWard rejected-join inspector'},
           'scene': 0, 'scenes': [{'nodes': list(range(len(groups)))}],
           'nodes': [], 'meshes': [], 'materials': [{'doubleSided': True,
               'pbrMetallicRoughness': {'metallicFactor': 0, 'roughnessFactor': 1}}],
           'bufferViews': [], 'accessors': []}

    def accessor(data, component, kind, count, **extra):
        while len(binary) % 4:
            binary.append(0)
        offset = len(binary)
        binary.extend(data)
        view = len(doc['bufferViews'])
        doc['bufferViews'].append({'buffer': 0, 'byteOffset': offset,
                                  'byteLength': len(data), 'target': 34962})
        idx = len(doc['accessors'])
        doc['accessors'].append({'bufferView': view, 'componentType': component,
                                'count': count, 'type': kind, **extra})
        return idx

    for name, faces, problems in groups:
        positions, normals, colors = [], [], bytearray()
        for i, (a, b, c) in enumerate(faces):
            u = [b[k] - a[k] for k in range(3)]
            v = [c[k] - a[k] for k in range(3)]
            n = [u[1]*v[2] - u[2]*v[1], u[2]*v[0] - u[0]*v[2],
                 u[0]*v[1] - u[1]*v[0]]
            length = math.sqrt(sum(x*x for x in n))
            n = [x / length for x in n] if length else [0, 1, 0]
            rgb = (235, 183, 113) if max(a[1], b[1], c[1]) < .3 else (
                (204, 145, 83) if n[1] > .65 else (157, 86, 56))
            if i in problems:
                rgb = (255, 45, 45)
            for p in (a, b, c):
                positions.extend(p)
                normals.extend(n)
                colors.extend((*rgb, 255))
        count = len(positions) // 3
        low = [min(positions[k::3]) for k in range(3)]
        high = [max(positions[k::3]) for k in range(3)]
        pos = accessor(struct.pack('<%sf' % len(positions), *positions), 5126,
                       'VEC3', count, min=low, max=high)
        norm = accessor(struct.pack('<%sf' % len(normals), *normals), 5126,
                        'VEC3', count)
        color = accessor(colors, 5121, 'VEC4', count, normalized=True)
        doc['nodes'].append({'name': name, 'mesh': len(doc['meshes'])})
        doc['meshes'].append({'name': name, 'primitives': [{'attributes': {
            'POSITION': pos, 'NORMAL': norm, 'COLOR_0': color},
            'mode': 4, 'material': 0}]})
    doc['buffers'] = [{'byteLength': len(binary)}]
    encoded = json.dumps(doc, separators=(',', ':')).encode()
    encoded += b' ' * (-len(encoded) % 4)
    binary += b'\0' * (-len(binary) % 4)
    path.write_bytes(struct.pack('<III', 0x46546C67, 2, 28 + len(encoded) + len(binary))
                     + struct.pack('<I4s', len(encoded), b'JSON') + encoded
                     + struct.pack('<I4s', len(binary), b'BIN\0') + binary)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--fixture', type=Path, required=True)
    parser.add_argument('--assembly', type=Path, required=True)
    parser.add_argument('--output-dir', type=Path, required=True)
    args = parser.parse_args()
    old, outside, metadata = read_fixture(args.fixture)
    candidate = json.loads(args.assembly.read_text())
    context = triangles(outside)
    original = triangles(old)
    bad = {i for pair in candidate['pairs'] for i in pair}
    args.output_dir.mkdir(parents=True, exist_ok=True)
    write_glb(args.output_dir/'01-original.glb', [
        ('Original terrain', original, set()), ('Unchanged context and floor', context, set())])
    for filename, highlight in [('02-REJECTED-candidate.glb', set()),
                                ('03-REJECTED-highlighted.glb', bad)]:
        write_glb(args.output_dir/filename, [
            ('REJECTED assembly', candidate['faces'], highlight),
            ('Unchanged context and floor', context, set())])
    metadata.update({'fixture': str(args.fixture), 'assembly': str(args.assembly),
                     'original_faces': len(original), 'candidate_faces': len(candidate['faces']),
                     'context_faces': len(context), 'status': 'rejected, inspection only',
                     'highlighted_faces': len(bad)})
    (args.output_dir/'provenance.json').write_text(json.dumps(metadata, indent=2)+'\n')
    print(json.dumps(metadata, indent=2))


if __name__ == '__main__':
    main()
