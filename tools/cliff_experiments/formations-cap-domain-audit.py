#!/usr/bin/env python3
"""Independently verify whole-component cap-domain input selection."""
import argparse
from collections import Counter, defaultdict
from fractions import Fraction as F
import hashlib
import json
from math import gcd
from pathlib import Path
import runpy


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ('sources', 'input_cells', 'certificate', 'output_cells'):
        parser.add_argument(name, type=Path)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    load = lambda p: json.loads(p.read_text())
    api = runpy.run_path(str(Path(__file__).with_name('formations-source-reuse.py')))
    old = [cell for chunk in load(args.input_cells)['chunks'] for cell in chunk['cells']]
    new = [cell for chunk in load(args.output_cells)['chunks'] for cell in chunk['cells']]
    cert, source = load(args.certificate), load(args.sources)
    assert len(old) == cert['cells'] == len(cert['cell_components']) == len(cert['retained_source_cells'])
    parent = list(range(len(old)))

    def root(i):
        while parent[i] != i:
            parent[i] = parent[parent[i]]
            i = parent[i]
        return i

    lines = defaultdict(lambda: defaultdict(Counter))
    for i, cell in enumerate(old):
        points = [(F(p[0])*65536, F(p[2])*65536) for p in cell]
        assert all(x.denominator == z.denominator == 1 for x, z in points)
        points = [(int(x), int(z)) for x, z in points]
        for a, b in zip(points, points[1:]+points[:1]):
            dx, dz = b[0]-a[0], b[1]-a[1]
            scale = gcd(dx, dz)
            assert scale
            dx, dz = dx//scale, dz//scale
            if dx < 0 or (dx == 0 and dz < 0):
                dx, dz = -dx, -dz
            key = (dx, dz, dx*a[1]-dz*a[0])
            low, high = sorted((dx*a[0]+dz*a[1], dx*b[0]+dz*b[1]))
            lines[key][low][i] += 1
            lines[key][high][i] -= 1
    shared_intervals, nonmanifold_intervals = 0, 0
    for events in lines.values():
        active, previous = Counter(), None
        for position, changes in sorted(events.items()):
            if previous is not None and previous < position and len(active) > 1:
                shared_intervals += 1
                nonmanifold_intervals += len(active) > 2
                owners = sorted(active)
                for i in owners[1:]:
                    a, b = root(owners[0]), root(i)
                    parent[max(a, b)] = min(a, b)
            active.update(changes)
            active = Counter({i: count for i, count in active.items() if count})
            assert all(count == 1 for count in active.values())
            previous = position
        assert not active
    groups, claimed = defaultdict(list), defaultdict(list)
    for i, owner in enumerate(cert['cell_components']):
        groups[root(i)].append(i)
        claimed[owner].append(i)
    partition_equal = {tuple(v) for v in groups.values()} == {tuple(v) for v in claimed.values()}
    caps = [api['sides']([(F(p[0]), F(p[2])) for p in polygon]) for polygon in source['caps']]
    attached = defaultdict(bool)
    cap_parts = 0
    for i, cell in enumerate(old):
        domain = [(F(p[0]), F(p[2])) for p in cell]
        for cuts in caps:
            overlap = domain
            for h in cuts:
                overlap = api['clip'](overlap, h)
            if overlap:
                attached[root(i)] = True
                cap_parts += 1
    expected = [not attached[root(i)] for i in range(len(old))]
    mask_equal = expected == cert['retained_source_cells']
    identity = lambda cell: tuple(tuple(p) for p in cell)
    actual_equal = Counter(map(identity, new)) == Counter(identity(c) for i, c in enumerate(old) if not expected[i])
    report = dict(scope='Integer-grid collinear interval sweeps independently establish positive-edge cell connectivity including T junctions. Rational positive-area cap intersections determine whole-component selection. Actual output cell coordinates/multiplicities must match selected input cells. This does not certify original retained backing, Boolean surfaces, cap volume contact or full assembly/world acceptance.',
                  input_sha256={str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in
                      (args.sources, args.input_cells, args.certificate, args.output_cells)},
                  input_cells=len(old), output_cells=len(new), components=len(groups),
                  positive_shared_edge_intervals=shared_intervals,
                  nonmanifold_intervals=nonmanifold_intervals,
                  component_partition_matches=partition_equal,
                  positive_cap_overlap_parts=cap_parts,
                  whole_component_selection_matches=mask_equal,
                  actual_output_exactly_selected_inputs=actual_equal,
                  original_backing_cells=sum(expected),
                  retained_component_sizes=sorted(len(v) for k, v in groups.items() if not attached[k]),
                  full_assembly_proved=False)
    args.output.write_text(json.dumps(report, indent=2)+'\n')
    print(args.certificate.name, 'partition', partition_equal, 'selection', mask_equal,
          'actual cells', actual_equal, len(old), '->', len(new), flush=True)
    return int(not (partition_equal and mask_equal and actual_equal and not nonmanifold_intervals))


if __name__ == '__main__':
    raise SystemExit(main())
