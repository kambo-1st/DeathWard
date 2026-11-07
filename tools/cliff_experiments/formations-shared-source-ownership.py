#!/usr/bin/env python3
"""Verify complete canonical source ownership against fixed crop columns."""
import argparse
from collections import defaultdict
from fractions import Fraction as F
import hashlib
import json
import math
from pathlib import Path
import runpy


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('certificate', type=Path)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    data = json.loads(args.certificate.read_text())
    api = runpy.run_path(str(Path(__file__).with_name('formations-source-reuse.py')))
    base = [(tuple(map(F, row['box'])), [tuple(map(F, p)) for p in row['cuts']])
            for row in data['base_columns']]
    bins = defaultdict(set)
    for i, (box, _) in enumerate(base):
        for x in range(math.floor(box[0]), math.floor(box[2])+1):
            for z in range(math.floor(box[1]), math.floor(box[3])+1):
                bins[x, z].add(i)
    failures, maximum = [], F(0)
    for i, claim in enumerate(data['claims']):
        raw = [(F(p[0]), F(p[2])) for p in claim['source']]
        canonical = [tuple(map(F, p)) for p in claim['canonical']]
        shifts = [sum((a-b)**2 for a, b in zip(p, q)) for p, q in zip(raw, canonical)]
        maximum = max(maximum, *shifts)
        bounded = all(abs(a-b) <= F(1, 131072) for p, q in zip(raw, canonical) for a, b in zip(p, q))
        matches = max(shifts) == F(claim['maximum_displacement_squared_exact'])
        # Quantization must be to the exact canonical lattice, not merely close.
        grid = all((v*65536).denominator == 1 for p in canonical for v in p)
        box = api['bounds'](canonical)
        nearby = set()
        for x in range(math.floor(box[0]), math.floor(box[2])+1):
            for z in range(math.floor(box[1]), math.floor(box[3])+1):
                nearby.update(bins[x, z])
        remaining = [canonical]
        for owner in sorted(nearby):
            b, cuts = base[owner]
            if not api['meets'](box, b):
                continue
            remaining = [part for piece in remaining for part in api['subtract'](piece, cuts)]
            if not remaining:
                break
        if remaining or not (bounded and matches and grid):
            failures.append(dict(claim=i, uncovered_positive_fragments=len(remaining),
                                 displacement_bounded=bounded, certificate_matches=matches,
                                 exact_grid=grid))
    result = dict(scope='Exact complete canonical-domain subtraction uses ONLY the fixed base construction columns. All original-to-canonical vertex displacements are bounded by half a grid quantum per axis. No area cutoff or recursive ownership growth is allowed. This does not certify final assembled/rendered topology or complete world acceptance.',
                  certificate=str(args.certificate), sha256=hashlib.sha256(args.certificate.read_bytes()).hexdigest(),
                  fixed_base_columns=len(base), claims=len(data['claims']), failures=failures,
                  maximum_displacement_squared_exact=str(maximum),
                  half_quantum_exact='1/131072', recursive_growth=False,
                  full_assembly_proved=False)
    args.output.write_text(json.dumps(result, indent=2)+'\n')
    print('Shared source ownership:', len(data['claims']), 'complete claims,', len(failures), 'failures', flush=True)
    return int(bool(failures))


if __name__ == '__main__':
    raise SystemExit(main())
