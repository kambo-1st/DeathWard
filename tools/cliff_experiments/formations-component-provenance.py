#!/usr/bin/env python3
"""Compare detached emitted cores with checked pre-union body surfaces.

This diagnoses construction provenance. It does not authorize deleting an output
component or establish equivalence with the immutable original terrain.
"""
import argparse
from collections import Counter, defaultdict
from fractions import Fraction as F
import hashlib
import importlib.util
import json
from pathlib import Path
import runpy

spec = importlib.util.spec_from_file_location(
    'component_owners', Path(__file__).with_name('formations-component-owners.py'))
owners = importlib.util.module_from_spec(spec)
spec.loader.exec_module(owners)
sub, dot, cross = owners.sub, owners.dot, owners.cross
planar = runpy.run_path(str(Path(__file__).with_name('formations-source-reuse.py')))


def components(faces):
    parent = list(range(len(faces)))
    edges = {}

    def root(i):
        while parent[i] != i:
            parent[i] = parent[parent[i]]
            i = parent[i]
        return i

    for i, face in enumerate(faces):
        for a, b in zip(face, face[1:] + face[:1]):
            key = tuple(sorted((a, b)))
            if key in edges:
                a, b = root(i), root(edges[key])
                parent[max(a, b)] = min(a, b)
            else:
                edges[key] = i
    groups = defaultdict(list)
    for i in range(len(faces)):
        groups[root(i)].append(i)
    return sorted(groups.values(), key=lambda group: (-len(group), group[0]))


def signature(faces):
    # Preserve winding, multiplicity and exact emitted coordinates.
    return Counter(min(face, face[1:] + face[:1], face[2:] + face[:2])
                   for face in faces)


def bounds(faces):
    points = [p for face in faces for p in face]
    return [tuple(min(p[d] for p in points) for d in range(3)),
            tuple(max(p[d] for p in points) for d in range(3))]


def surface_coverage(subject, reference):
    """Exact same-oriented-plane coverage, independent of triangulation."""
    def projected(face):
        normal = cross(sub(face[1], face[0]), sub(face[2], face[0]))
        scale = abs(next(n for n in normal if n))
        key = tuple(n / scale for n in normal) + (dot(normal, face[0]) / scale,)
        drop = max(range(3), key=lambda d: abs(normal[d]))
        poly = [tuple(p[d] for d in range(3) if d != drop) for p in face]
        return key, poly

    cutters = defaultdict(list)
    for face in reference:
        key, poly = projected(face)
        cutters[key].append(planar['sides'](poly))
    uncovered = []
    area = F(0)
    for i, face in enumerate(subject):
        key, poly = projected(face)
        remaining = [poly]
        for cuts in cutters[key]:
            remaining = [part for piece in remaining
                         for part in planar['subtract'](piece, cuts)]
            if not remaining:
                break
        if remaining:
            uncovered.append(i)
            area += sum(map(planar['area'], remaining), F(0))
    return dict(uncovered_faces=uncovered, summed_projected_missing_area_exact=str(area))


def clip(poly, planes):
    for plane in planes:
        result = []
        for a, b in zip(poly, poly[1:] + poly[:1]):
            da, db = dot(plane[:3], a) - plane[3], dot(plane[:3], b) - plane[3]
            if da <= 0:
                result.append(a)
            if (da < 0 < db) or (db < 0 < da):
                t = da / (da - db)
                result.append(tuple(x + t * (y - x) for x, y in zip(a, b)))
        poly = result
        if len(poly) < 3:
            return []
    return poly


def strict_patch(poly, planes):
    if len(poly) < 3:
        return False
    area = tuple(sum(cross(sub(poly[i], poly[0]), sub(poly[i+1], poly[0]))[d]
                     for i in range(1, len(poly)-1)) for d in range(3))
    if not any(area):
        return False
    center = tuple(sum(p[d] for p in poly) / len(poly) for d in range(3))
    return all(dot(plane[:3], center) < plane[3] for plane in planes)


def self_check():
    point = lambda x, y: (F(x), F(y), F(0))
    a, b, c, d = point(0, 0), point(1, 0), point(1, 1), point(0, 1)
    old, new = [(a, b, c), (a, c, d)], [(a, b, d), (b, c, d)]
    assert not surface_coverage(old, new)['uncovered_faces']
    assert not surface_coverage(new, old)['uncovered_faces']
    assert surface_coverage(old, [tuple(reversed(f)) for f in new])['uncovered_faces'] == [0, 1]
    assert surface_coverage(old, new[:1])['uncovered_faces']
    assert signature([(a, b, c)]) == signature([(b, c, a)])
    assert signature([(a, b, c)]) != signature([(a, c, b)])
    planes = [tuple(map(F, p)) for p in [(1, 0, 0, 1), (-1, 0, 0, 0),
              (0, 1, 0, 1), (0, -1, 0, 0), (0, 0, 1, 1), (0, 0, -1, 0)]]
    interior = [(F(-1), F(1, 2), F(1, 2)),
                (F(2), F(1, 2), F(1, 2)), (F(1, 2), F(2), F(1, 2))]
    assert strict_patch(clip(interior, planes), planes)
    assert not strict_patch(clip([a, b, d], planes), planes)
    outside = [(F(2), F(0), F(0)), (F(3), F(0), F(0)), (F(2), F(1), F(0))]
    assert not strict_patch(clip(outside, planes), planes)
    return ['alternate triangulation both directions', 'opposite winding rejected',
            'missing area detected', 'cyclic face identity', 'reversed face rejected',
            'strict interior clipping', 'tangent patch excluded', 'disjoint patch excluded']


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('mesh', type=Path)
    parser.add_argument('mapping', type=Path)
    parser.add_argument('checked_bodies', type=Path)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    controls = self_check()
    data = json.loads(args.mesh.read_text())
    mapping = json.loads(args.mapping.read_text())
    raw = json.loads(args.checked_bodies.read_text())
    decode = lambda fs: [tuple(tuple(map(F, p)) for p in face) for face in fs]
    faces, input_faces = decode(data['faces']), decode(raw['faces'])
    groups = components(faces)
    assert sum(mapping['body_faces']) == len(input_faces)
    bodies, offset = [], 0
    for count in mapping['body_faces']:
        bodies.append(input_faces[offset:offset+count])
        offset += count
    body_groups = [components(body) for body in bodies]
    body_signatures = [signature(body) for body in bodies]
    body_bounds = [bounds(body) for body in bodies]
    primary_planes = [[tuple(map(F, p)) for p in volume]
                      for volume in data['volumes'][:mapping['body_begin']]]
    rows = []
    for component, indices in enumerate(groups[1:], 1):
        surface = [faces[i] for i in indices]
        sig, box = signature(surface), bounds(surface)
        exact = [i for i, candidate in enumerate(body_signatures) if sig == candidate]
        containing_boxes = [i for i, candidate in enumerate(body_bounds)
                            if all(candidate[0][d] <= box[0][d]
                                   and box[1][d] <= candidate[1][d] for d in range(3))]
        equal_boxes = [i for i in containing_boxes if body_bounds[i] == box]
        coverage = []
        for body in equal_boxes:
            forward = surface_coverage(surface, bodies[body])
            reverse = surface_coverage(bodies[body], surface)
            coverage.append(dict(body=body, emitted_against_input=forward,
                                 input_against_emitted=reverse,
                                 exact_surface_equivalent=not forward['uncovered_faces']
                                 and not reverse['uncovered_faces']))
        patches = []
        for face_id in indices:
            for primary, planes in enumerate(primary_planes):
                polygon = clip(list(faces[face_id]), planes)
                if strict_patch(polygon, planes):
                    patches.append(dict(face=face_id, primary=primary))
        rows.append(dict(component=component, triangles=len(surface),
                         bounds=[[float(x) for x in p] for p in box],
                         exact_oriented_checked_body_matches=exact,
                         containing_checked_body_boxes=containing_boxes,
                         equal_bounds_body_surface_comparisons=coverage,
                         strict_primary_interior_boundary_patches=patches))
    report = dict(
        scope='Exact oriented triangle-multiset equality establishes equality only to a checked pre-union constructed body. Bounding-box containment is a candidate association, not ownership. Rational clipping tests satellite boundary patches strictly inside nominal primary solids; absence alone is not full-volume disjointness or original-terrain equivalence. No geometry is changed.',
        input_sha256={str(p): hashlib.sha256(p.read_bytes()).hexdigest()
                      for p in (args.mesh, args.mapping, args.checked_bodies)},
        checked_bodies=[dict(body=i, triangles=len(body),
                             component_triangles=[len(c) for c in body_groups[i]])
                        for i, body in enumerate(bodies)],
        emitted_component_triangles=[len(group) for group in groups],
        satellites=rows, post_union_deletion=False,
        analytic_controls_passed=controls,
        immutable_original_terrain_equivalence_proved=False,
        full_assembly_proved=False)
    args.output.write_text(json.dumps(report, indent=2) + '\n')
    print(args.mesh.name, [(row['triangles'], row['exact_oriented_checked_body_matches'],
                            len(row['strict_primary_interior_boundary_patches'])) for row in rows])


if __name__ == '__main__':
    main()
