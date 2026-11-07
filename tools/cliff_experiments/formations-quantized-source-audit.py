#!/usr/bin/env python3
"""Independently verify recorded float-degenerate source-cut collapses."""
import argparse
from collections import defaultdict
from fractions import Fraction as F
import hashlib
import json
from math import isqrt
from pathlib import Path
import runpy


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('certificate', type=Path)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    api = runpy.run_path(str(Path(__file__).with_name('formations-source-fragment-audit.py')))
    groups, failures = defaultdict(F), []
    rows = [json.loads(line) for line in args.certificate.read_text().splitlines() if line.strip()]
    maximum, total = F(0), F(0)
    for i, row in enumerate(rows):
        exact = [tuple(map(F, p)) for p in row['exact']]
        rendered = [tuple(map(F, p)) for p in row['rendered']]
        assert len(exact) == len(rendered)
        area = F(0)
        for k in range(1, len(exact)-1):
            vector = api['area_vector']([exact[0], exact[k], exact[k+1]])
            squared = sum(v*v for v in vector)/4
            scaled = squared.numerator << 200
            root = isqrt(scaled//squared.denominator)
            if root*root*squared.denominator < scaled:
                root += 1
            upper = F(root, 1 << 100)
            assert upper*upper >= squared
            assert not root or F(root-1, 1 << 100)**2 < squared
            area += upper
        distance = max(sum((a-b)**2 for a, b in zip(p, q)) for p, q in zip(exact, rendered))
        source = tuple(tuple(map(F, p)) for p in row['source'])
        groups[source] += area
        maximum = max(maximum, distance)
        total += area
        checks = dict(exact_positive=api['positive'](exact),
                      render_degenerate=not api['positive'](rendered),
                      area_certificate_equal=area == F(row['lost_area_upper_exact']),
                      displacement_certificate_equal=distance == F(row['maximum_displacement_squared_exact']),
                      declared_cumulative_area_valid=area <= F(row['source_face_lost_area_upper_exact']) <= F(1e-12),
                      displacement_within_existing_weld=distance <= F(1, 50000)**2)
        if not all(checks.values()):
            failures.append(dict(fragment=i, checks=checks))
    excessive = [dict(source=[[str(v) for v in p] for p in source], area_exact=str(area))
                 for source, area in groups.items() if area > F(1e-12)]
    report = dict(scope='Exact rational recomputation of lost fan-area upper bounds and maximum paired-vertex displacement. Every recorded float polygon must be degenerate; every exact polygon must be positive. Aggregate loss is bounded per source vertex sequence, conservatively combining duplicate source inputs. This verifies numerical preconditions, not complete source/world equivalence or assembled topology.',
                  certificate=str(args.certificate), sha256=hashlib.sha256(args.certificate.read_bytes()).hexdigest(),
                  fragments=len(rows), source_vertex_sequences=len(groups),
                  lost_area_upper_exact=str(total), maximum_displacement_squared_exact=str(maximum),
                  maximum_source_area_upper_exact=str(max(groups.values(), default=F(0))),
                  failures=failures, excessive_source_area=excessive,
                  existing_source_area_limit_exact=str(F(1e-12)),
                  existing_construction_weld_exact='1/50000', full_assembly_proved=False)
    args.output.write_text(json.dumps(report, indent=2)+'\n')
    print('Quantized source fragments', len(rows), 'failures', len(failures),
          'excessive source faces', len(excessive), flush=True)
    return int(bool(failures or excessive))


if __name__ == '__main__':
    raise SystemExit(main())
