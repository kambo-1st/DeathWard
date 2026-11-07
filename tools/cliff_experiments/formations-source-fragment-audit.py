#!/usr/bin/env python3
"""Audit a rejected retained-source float collapse and whole-face coverage."""
import argparse
from fractions import Fraction as F
import hashlib
import json
from pathlib import Path


def value(plane, point):
    return sum(a*b for a, b in zip(plane[:3], point))-plane[3]


def clip(poly, plane):
    out = []
    for a, b in zip(poly, poly[1:]+poly[:1]):
        u, v = value(plane, a), value(plane, b)
        if u <= 0:
            out.append(a)
        if u*v < 0:
            t = u/(u-v)
            out.append(tuple(x+t*(y-x) for x, y in zip(a, b)))
    return out


def area_vector(poly):
    area = [F(0)]*3
    for i in range(1, len(poly)-1):
        a = [x-y for x, y in zip(poly[i], poly[0])]
        b = [x-y for x, y in zip(poly[i+1], poly[0])]
        for k in range(3):
            area[k] += a[(k+1)%3]*b[(k+2)%3]-a[(k+2)%3]*b[(k+1)%3]
    return area


def positive(poly):
    return any(area_vector(poly))


def uncovered(face, solids):
    remaining = [face]
    for solid in solids:
        after = []
        for part in remaining:
            intersection = part
            for plane in solid:
                intersection = clip(intersection, plane)
                if not positive(intersection):
                    break
            if not positive(intersection):
                after.append(part)
                continue
            for plane in solid:
                outside = clip(part, tuple(-p for p in plane))
                if positive(outside) and any(value(plane, p) > 0 for p in outside):
                    after.append(outside)
                part = clip(part, plane)
                if not positive(part):
                    break
        remaining = after
        if not remaining:
            break
    return remaining


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('fragment', type=Path)
    parser.add_argument('core', type=Path)
    parser.add_argument('mapping', type=Path)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    load = lambda p: json.loads(p.read_text())
    report, core, mapping = map(load, (args.fragment, args.core, args.mapping))
    decode = lambda poly: [tuple(map(F, p)) for p in poly]
    exact, rendered, source = map(decode, (report['exact_fragment'], report['rendered'], report['input']))
    assert positive(exact) and not positive(rendered)
    trials = []
    for margin in (F(0), F(1, 50000)):
        bodies = []
        for v in core['volumes'][mapping['body_begin']:mapping['body_begin']+mapping['body_count']]:
            planes = [tuple(map(F, p)) for p in v]
            assert planes[0][1] > 0 and planes[1][:3] == (0, -1, 0)
            assert all(p[1] == 0 for p in planes[2:])
            bodies.append(planes[:2]+[p[:3]+(p[3]+margin,) for p in planes[2:]])
        missing = uncovered(source, bodies)
        trials.append(dict(horizontal_halfspace_allowance_exact=str(margin),
                           roof_and_foundation_planes_unchanged=True,
                           whole_original_face_covered=not missing,
                           uncovered_positive_fragments=len(missing),
                           first_uncovered_vertices=[[str(v) for v in p] for p in missing[0]] if missing else []))
    result = dict(scope='Rational area and complete whole-source-face subtraction against nominal height-field prisms. Only horizontal side halfspaces receive the stated allowance; roof and foundation remain exact. This is a proposed safe operand-overlap precondition, not proof of assembled float topology or full terrain/world acceptance.',
                  input_sha256={str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in (args.fragment, args.core, args.mapping)},
                  exact_fragment_area_vector=list(map(str, area_vector(exact))),
                  render_area_vector=list(map(str, area_vector(rendered))),
                  maximum_render_coordinate_shift_m=max(float(abs(a-b)) for p, q in zip(exact, rendered) for a, b in zip(p, q)),
                  trials=trials, full_assembly_proved=False)
    args.output.write_text(json.dumps(result, indent=2)+'\n')
    print('Positive source fragment collapses; whole-source coverage',
          [(t['horizontal_halfspace_allowance_exact'], t['whole_original_face_covered']) for t in trials], flush=True)


if __name__ == '__main__':
    main()
