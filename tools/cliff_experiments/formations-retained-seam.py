#!/usr/bin/env python3
"""Exact sampled comparison of chunk boundaries with their original source roof.

A mismatch proves a defect. Matching samples do not establish full seam acceptance.
Only samples outside both direct and nodal deformation support are compared.
"""
from collections import defaultdict
from itertools import combinations
from math import floor
from fractions import Fraction as F
from pathlib import Path
import argparse
import hashlib
import json

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('sources', type=Path)
parser.add_argument('chunks', type=Path)
parser.add_argument('--core', type=Path, required=True, help='Core probe with the five original cap half-spaces')
parser.add_argument('--reference', type=Path, help='Recheck the exact sample points from a saved oracle against the new roof cells')
parser.add_argument('--output', type=Path, required=True)
args = parser.parse_args()
source = json.loads(args.sources.read_text())
chunks = json.loads(args.chunks.read_text())
point = lambda p: tuple(F(float(x)) for x in p)
turn = lambda a, b, p: (b[0]-a[0])*(p[2]-a[2])-(b[2]-a[2])*(p[0]-a[0])
sub = lambda a, b: tuple(x-y for x, y in zip(a, b))
def cross(a, b):
    return (a[1]*b[2]-a[2]*b[1], a[2]*b[0]-a[0]*b[2], a[0]*b[1]-a[1]*b[0])

def bounds(face):
    return tuple(min(p[k] for p in face) for k in (0, 2)) + tuple(max(p[k] for p in face) for k in (0, 2))

def prepare(polygons):
    triangles = []
    for owner, face in enumerate(polygons):
        for k in range(1, len(face)-1):
            raw = (face[0], face[k], face[k+1])
            f = tuple(map(point, raw))
            n = cross(sub(f[1], f[0]), sub(f[2], f[0]))
            if n[1] != 0:
                triangles.append((owner, raw, f, n, bounds(raw)))
    return triangles

def roof_hits(p, triangles):
    hits = []
    for owner, raw, f, n, (lx, lz, hx, hz) in triangles:
        if float(p[0]) < lx-1e-10 or float(p[0]) > hx+1e-10 or float(p[2]) < lz-1e-10 or float(p[2]) > hz+1e-10:
            continue
        turns = [turn(f[k], f[(k+1) % 3], p) for k in range(3)]
        if not (all(t >= 0 for t in turns) or all(t <= 0 for t in turns)):
            continue
        height = f[0][1] - (n[0]*(p[0]-f[0][0])+n[2]*(p[2]-f[0][2]))/n[1]
        hits.append((height, owner, raw))
    return hits

triangles = prepare(source['source'])
generated = prepare([face for chunk in chunks['chunks'] for face in chunk['cells']]) if args.reference else []
caps = [tuple(map(point, face)) for face in source['caps']]
for cap in caps:
    signs = [turn(cap[k], cap[(k+1) % len(cap)], cap[(k+2) % len(cap)]) for k in range(len(cap))]
    assert all(t <= 0 for t in signs) or all(t >= 0 for t in signs), 'Expected convex cap domain'

def distance_squared(p, cap):
    turns = [turn(cap[k], cap[(k+1) % len(cap)], p) for k in range(len(cap))]
    if all(t <= 0 for t in turns) or all(t >= 0 for t in turns):
        return F(0)
    values = []
    for k, a in enumerate(cap):
        b = cap[(k+1) % len(cap)]
        dx, dz = b[0]-a[0], b[2]-a[2]
        length = dx*dx+dz*dz
        t = max(F(0), min(F(1), ((p[0]-a[0])*dx+(p[2]-a[2])*dz)/length)) if length else F(0)
        values.append((p[0]-a[0]-t*dx)**2+(p[2]-a[2]-t*dz)**2)
    return min(values)

dot = lambda a, b: sum(x*y for x, y in zip(a, b))
core = json.loads(args.core.read_text())
contact_boxes = []
for raw_planes in core['volumes'][:5]:
    planes = [tuple(F(float(x)) for x in plane) for plane in raw_planes]
    vertices = []
    for a, b, c in combinations(planes, 3):
        bc, ca, ab = cross(b[:3], c[:3]), cross(c[:3], a[:3]), cross(a[:3], b[:3])
        det = dot(a[:3], bc)
        if det == 0:
            continue
        p = tuple((a[3]*bc[k]+b[3]*ca[k]+c[3]*ab[k])/det for k in range(3))
        if all(dot(plane[:3], p) <= plane[3] for plane in planes):
            vertices.append(p)
    assert vertices, 'Cap half-spaces do not enclose a finite source'
    contact_boxes.append(bounds(vertices))

support = F(float(source['support'])) + F(1, 1000)
contact_support = F(1001, 1000)
uses = defaultdict(list)
for chunk in chunks['chunks']:
    for face in chunk['cells']:
        for k, a in enumerate(face):
            b = face[(k+1) % len(face)]
            key = tuple(sorted(((a[0], a[2]), (b[0], b[2]))))
            uses[key].append((a, b))
rows = []
no_source = []
checked = 0
no_generated_roof = []
query_edges = [incidents[0] for incidents in uses.values() if len(incidents) == 1]
if args.reference:
    reference = json.loads(args.reference.read_text())
    query_edges = [row['edge'] for row in reference['samples']] + [row['edge'] for row in reference['no_source']]
for raw_a, raw_b in query_edges:
    a, b = point(raw_a), point(raw_b)
    p = tuple((x+y)/2 for x, y in zip(a, b))
    x, z = floor(p[0]), floor(p[2])
    u, v = p[0]-x, p[2]-z
    nodes = [(x, 0, z), (x, 0, z+1), (x+1, 0, z+1)] if u <= v else [(x, 0, z), (x+1, 0, z+1), (x+1, 0, z)]
    distances = [min(distance_squared(q, cap) for cap in caps) for q in [p, *nodes]]
    if min(distances) <= support*support:
        continue
    contact_distances = []
    for lx, lz, hx, hz in contact_boxes:
        dx, dz = max(lx-p[0], F(0), p[0]-hx), max(lz-p[2], F(0), p[2]-hz)
        contact_distances.append(dx*dx+dz*dz)
    if min(contact_distances) <= contact_support*contact_support:
        continue
    checked += 1
    original_query_height = p[1]
    if args.reference:
        actual = roof_hits(p, generated)
        if not actual:
            no_generated_roof.append(dict(edge=[raw_a, raw_b], midpoint=list(map(float, p))))
            continue
        p = (p[0], max(hit[0] for hit in actual), p[2])
    hits = roof_hits(p, triangles)
    if not hits:
        no_source.append(dict(edge=[raw_a, raw_b], midpoint=list(map(float, p))))
        continue
    height, owner, raw = max(hits, key=lambda hit: (hit[0], -hit[1]))
    delta = p[1]-height
    rows.append(dict(edge=[raw_a, raw_b], midpoint=list(map(float, p)), source_face=owner,
                     source_triangle=raw, source_height=float(height), generated_height=float(p[1]),
                     original_query_height=float(original_query_height), difference_m=float(delta),
                     exact_difference=str(delta), direct_and_node_distance_squared=[str(d) for d in distances], contact_box_distance_squared=str(min(contact_distances))))
rows.sort(key=lambda r: (-abs(r['difference_m']), r['edge']))
status = dict(sources=str(args.sources), chunks=str(args.chunks),
              source_sha256=hashlib.sha256(args.sources.read_bytes()).hexdigest(),
              chunks_sha256=hashlib.sha256(args.chunks.read_bytes()).hexdigest(),
              direct_and_node_support_margin_m=0.001, contact_support_margin_m=0.001, core=str(args.core),
              core_sha256=hashlib.sha256(args.core.read_bytes()).hexdigest(), boundary_edges=sum(len(v)==1 for v in uses.values()),
              far_boundary_midpoints=checked, compared=len(rows), no_source=no_source,
              reference=str(args.reference) if args.reference else None,
              reference_sha256=hashlib.sha256(args.reference.read_bytes()).hexdigest() if args.reference else None,
              no_generated_roof=no_generated_roof,
              mismatches_over_0_1mm=sum(abs(F(r['exact_difference'])) > F(1, 10000) for r in rows),
              maximum_absolute_difference_m=max((abs(r['difference_m']) for r in rows), default=0),
              samples=rows, accepted=False,
              scope='Exact rational source membership and heights at boundary-edge midpoints. The midpoint and all three interpolating grid nodes are farther than support + 1 mm from every cap domain. The midpoint is also farther than 1.001 m from every nominal cap-volume projected bounding box, excluding the local contact controls. The undeformed nodal baseline should agree with the retained source here. Not a full edge, assembly, visual, or gameplay acceptance check.')
if args.reference:
    status['scope'] += ' Queries use the fixed reference-edge midpoints and exact upper heights of the new triangulated roof cells; these are field-cell results, not accepted emitted-core or assembly results.'
args.output.write_text(json.dumps(status, indent=2)+'\n')
print('Compared', len(rows), 'far boundary midpoints;', status['mismatches_over_0_1mm'], 'mismatches; maximum', status['maximum_absolute_difference_m'], 'm')
