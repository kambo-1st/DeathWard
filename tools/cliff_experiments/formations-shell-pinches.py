#!/usr/bin/env python3
"""Locate emitted shell edges with excessive incidence against saved source cutouts.

Diagnostic only: exact membership in projected cutouts does not establish floor
placement acceptance, and no mesh is repaired or accepted by this tool.
"""
import argparse
from collections import defaultdict
from fractions import Fraction
import hashlib
import json
import math
from pathlib import Path


def membership(point, polygon):
    """Winding membership on exact binary-float coordinates, including edges."""
    x, z = map(Fraction, point)
    ring = [(Fraction(p[0]), Fraction(p[2])) for p in polygon]
    winding = 0
    for a, b in zip(ring, ring[1:] + ring[:1]):
        turn = (b[0] - a[0]) * (z - a[1]) - (b[1] - a[1]) * (x - a[0])
        if turn == 0 and min(a[0], b[0]) <= x <= max(a[0], b[0]) and min(a[1], b[1]) <= z <= max(a[1], b[1]):
            return 'boundary'
        if a[1] <= z < b[1] and turn > 0:
            winding += 1
        elif b[1] <= z < a[1] and turn < 0:
            winding -= 1
    return 'interior' if winding else 'outside'


def boundary_distance(point, polygon):
    """Approximate distance for diagnosis; never used by membership or guards."""
    x, z = point
    distances = []
    for a, b in zip(polygon, polygon[1:] + polygon[:1]):
        dx, dz = b[0] - a[0], b[2] - a[2]
        length2 = dx * dx + dz * dz
        t = max(0, min(1, ((x - a[0]) * dx + (z - a[2]) * dz) / length2)) if length2 else 0
        distances.append(math.hypot(x - a[0] - t * dx, z - a[2] - t * dz))
    return min(distances)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('mesh', type=Path)
    parser.add_argument('sources', type=Path)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--uncut', type=Path, help='Compare projected point contacts with an uncut footprint probe')
    parser.add_argument('--active-grid', type=Path, help='Exclude deliberate active-field boundaries from the comparison')
    args = parser.parse_args()
    mesh = json.loads(args.mesh.read_text())
    source = json.loads(args.sources.read_text())
    uses = defaultdict(list)
    for i, face in enumerate(mesh['faces']):
        for a, b in zip(face, face[1:] + face[:1]):
            uses[tuple(sorted((tuple(a), tuple(b))))].append(i)
    rows = []
    for (a, b), owners in sorted(uses.items()):
        if len(owners) <= 2:
            continue
        vertical = a[0] == b[0] and a[2] == b[2] and a[1] != b[1]
        row = dict(edge=[a, b], incident_faces=owners, vertical=vertical)
        if vertical:
            p = (a[0], a[2])
            for key in ('source', 'holes'):
                row[key + '_membership'] = [dict(index=i, membership=m, approximate_boundary_distance_m=boundary_distance(p, polygon)) for i, polygon in enumerate(source[key])
                                            if (m := membership(p, polygon)) != 'outside']
        rows.append(row)
    status = dict(mesh=str(args.mesh), sources=str(args.sources),
                  mesh_sha256=hashlib.sha256(args.mesh.read_bytes()).hexdigest(),
                  sources_sha256=hashlib.sha256(args.sources.read_bytes()).hexdigest(),
                  nonmanifold_edges=len(rows), vertical_edges=sum(r['vertical'] for r in rows),
                  vertical_points_in_original_holes=sum(bool(r.get('holes_membership')) for r in rows),
                  edges=rows, accepted=False,
                  scope='All exact-position edges with more than two incident emitted triangles. Original projected source/cutout membership uses rational arithmetic. Later floor trimming and snapped cutout domains are not reconstructed.')
    if args.uncut:
        def disconnected_links(faces):
            links = defaultdict(lambda: defaultdict(set))
            for face in faces:
                for k in range(3):
                    p, a, b = (tuple(face[j % 3]) for j in (k, k + 1, k + 2))
                    links[p][a].add(b)
                    links[p][b].add(a)
            result = {}
            for p, graph in links.items():
                remaining = set(graph)
                components = 0
                while remaining:
                    stack = [next(iter(remaining))]
                    components += 1
                    while stack:
                        q = stack.pop()
                        if q in remaining:
                            remaining.remove(q)
                            stack.extend(graph[q])
                if components > 1:
                    result[p] = components
            return result

        uncut = json.loads(args.uncut.read_text())
        active = json.loads(args.active_grid.read_text()) if args.active_grid else None
        original_links = disconnected_links(uncut['faces'])
        projected = []
        for p, count in sorted(disconnected_links(mesh['faces']).items()):
            x, _, z = p
            candidates = [f for f in uncut['faces'] if min(q[0] for q in f) <= x <= max(q[0] for q in f)
                          and min(q[2] for q in f) <= z <= max(q[2] for q in f)]
            hits = [membership((x, z), f) for f in candidates]
            projected.append(dict(point=p, disconnected_fans=count,
                                  exact_uncut_vertex_fans=original_links.get(p, 1),
                                  uncut_triangle_interior_hits=hits.count('interior'),
                                  uncut_triangle_boundary_hits=hits.count('boundary')))
            if active:
                candidates = [f for f in active['faces'] if min(q[0] for q in f) <= x <= max(q[0] for q in f)
                              and min(q[2] for q in f) <= z <= max(q[2] for q in f)]
                projected[-1]['active_grid_triangle_interior_hits'] = sum(membership((x,z),f) == 'interior' for f in candidates)
        status['projected_link_comparison'] = dict(uncut=str(args.uncut),
            uncut_sha256=hashlib.sha256(args.uncut.read_bytes()).hexdigest(),
            uncut_disconnected_vertices=len(original_links), current_disconnected_vertices=len(projected),
            same_position_uncut_pinches=sum(p['exact_uncut_vertex_fans'] > 1 for p in projected), vertices=projected,
            scope='Exact vertex equality and rational projected triangle membership. Uncut whole-source footprint and active field have different extents; total counts alone do not establish regression or causation.')
        if active:
            status['projected_link_comparison'].update(active_grid=str(args.active_grid),
                active_grid_sha256=hashlib.sha256(args.active_grid.read_bytes()).hexdigest(),
                pinches_strictly_inside_uncut_and_active_triangles=sum(bool(p['uncut_triangle_interior_hits']) and bool(p['active_grid_triangle_interior_hits']) for p in projected))
    args.output.write_text(json.dumps(status, indent=2) + '\n')
    print(status['nonmanifold_edges'], 'nonmanifold edges;', status['vertical_edges'],
          'vertical;', status['vertical_points_in_original_holes'], 'in original cutouts')


if __name__ == '__main__':
    main()
