#!/usr/bin/env python3
"""Independently compare a normalized silhouette with actual core triangles.

All predicates use Python integers. Witnesses include projected vertices, edge
midpoints, triangle interiors, both sides of silhouette edges, and a grid.
This audits the projection; it is not full assembled-terrain acceptance.
"""
import argparse
from collections import defaultdict
import hashlib
import json
import math
from pathlib import Path


def cross(a, b, p):
    return (b[0]-a[0])*(p[1]-a[1]) - (b[1]-a[1])*(p[0]-a[0])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--projection', type=Path, required=True)
    parser.add_argument('--core', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    certificate = json.loads(args.projection.read_text())
    core = json.loads(args.core.read_text())['faces']
    bits = certificate['binary_scale_bits']
    scale = 1 << bits
    rings = [[(6*x, 6*z) for x, z in p] for p in certificate['normalized']]
    triangles = []
    for face in core:
        points = []
        for p in face:
            x, z = math.ldexp(p[0], bits), math.ldexp(p[2], bits)
            if not x.is_integer() or not z.is_integer():
                raise ValueError('Core point does not lie on exact clipping grid')
            points.append((6*int(x), 6*int(z)))
        if cross(*points):
            triangles.append(points)
    queries = set()
    for a, b, c in triangles:
        queries.update((a, b, c))
        queries.add(((a[0]+b[0]+c[0])//3, (a[1]+b[1]+c[1])//3))
        for p, q in ((a, b), (b, c), (c, a)):
            queries.add(((p[0]+q[0])//2, (p[1]+q[1])//2))
    edges = [(p[k], p[(k+1) % len(p)]) for p in rings for k in range(len(p))]
    delta = max(1, round(6*scale*.00001))
    for a, b in edges:
        queries.update((a, b))
        midpoint = ((a[0]+b[0])//2, (a[1]+b[1])//2)
        queries.add(midpoint)
        dx, dz = b[0]-a[0], b[1]-a[1]
        offset = (0, delta if dx > 0 else -delta) if abs(dx) >= abs(dz) else (-delta if dz > 0 else delta, 0)
        for side in (-1, 1):
            queries.add((midpoint[0]+side*offset[0], midpoint[1]+side*offset[1]))
    low = [min(p[k] for t in triangles for p in t) for k in range(2)]
    high = [max(p[k] for t in triangles for p in t) for k in range(2)]
    for x in range(65):
        for z in range(65):
            queries.add((low[0]+(high[0]-low[0])*x//64,
                         low[1]+(high[1]-low[1])*z//64))
    width = 12*scale
    bins = defaultdict(list)
    for triangle in triangles:
        for x in range(min(p[0] for p in triangle)//width, max(p[0] for p in triangle)//width+1):
            for z in range(min(p[1] for p in triangle)//width, max(p[1] for p in triangle)//width+1):
                bins[x, z].append(triangle)

    def expected(p):
        for a, b, c in bins[p[0]//width, p[1]//width]:
            signs = (cross(a, b, p), cross(b, c, p), cross(c, a, p))
            if min(signs) >= 0 or max(signs) <= 0:
                return True
        return False

    def actual(p):
        winding = 0
        for a, b in edges:
            turn = cross(a, b, p)
            if turn == 0 and min(a[0], b[0]) <= p[0] <= max(a[0], b[0]) and min(a[1], b[1]) <= p[1] <= max(a[1], b[1]):
                return True
            if a[1] <= p[1] < b[1] and turn > 0:
                winding += 1
            elif b[1] <= p[1] < a[1] and turn < 0:
                winding -= 1
        return winding > 0

    def near_boundary(p):
        # Two integer units cover endpoint rounding in the clipping certificate.
        # This is <2 picometres at bits=40, not a terrain acceptance tolerance.
        radius = 12
        for a, b in edges:
            dx, dz = b[0]-a[0], b[1]-a[1]
            length = dx*dx+dz*dz
            dot = (p[0]-a[0])*dx + (p[1]-a[1])*dz
            if 0 <= dot <= length and cross(a, b, p)**2 <= radius*radius*length:
                return True
            if min((p[0]-q[0])**2+(p[1]-q[1])**2 for q in (a, b)) <= radius*radius:
                return True
        return False

    failures, rounded = [], 0
    for p in sorted(queries):
        if expected(p) != actual(p):
            if near_boundary(p):
                rounded += 1
            elif len(failures) < 32:
                failures.append([p[0]/(6*scale), p[1]/(6*scale)])
    result = {'scope': 'exact integer projection witnesses; not assembled acceptance',
              'core_sha256': hashlib.sha256(args.core.read_bytes()).hexdigest(),
              'projection_sha256': hashlib.sha256(args.projection.read_bytes()).hexdigest(),
              'core_faces': len(core), 'projected_triangles': len(triangles),
              'raw_rings': len(certificate['raw']), 'normalized_rings': len(rings),
              'binary_scale_bits': bits, 'input_vertices_exact': True,
              'queries': len(queries), 'boundary_rounding_witnesses': rounded,
              'boundary_rounding_bound_m': 2/scale,
              'failures': failures, 'pass': not failures}
    args.output.write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps(result, indent=2))
    return 0 if not failures else 1


if __name__ == '__main__':
    raise SystemExit(main())
