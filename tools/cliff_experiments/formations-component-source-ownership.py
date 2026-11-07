#!/usr/bin/env python3
"""Audit nominal roof-cell ownership for candidate detached construction bodies.

Exact positive-area footprint subtraction selects whole nominal cells. Original
roof coverage/upper ownership and cap contacts are checked without changing any
geometry. This is not a retained-backing or final emitted-surface certificate.
"""
import argparse
from fractions import Fraction as F
import hashlib
import json
from pathlib import Path
import runpy


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ('sources', 'chunks', 'core', 'mapping', 'bodies', 'provenance'):
        parser.add_argument(name, type=Path)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    load = lambda p: json.loads(p.read_text())
    api = runpy.run_path(str(Path(__file__).with_name('formations-source-reuse.py')))
    area, clip, sides, subtract = (api[k] for k in ('area', 'clip', 'sides', 'subtract'))
    source, chunks, core, mapping, raw, provenance = [load(getattr(args, k))
        for k in ('sources', 'chunks', 'core', 'mapping', 'bodies', 'provenance')]
    cells = [cell for chunk in chunks['chunks'] for cell in chunk['cells']]
    assert len(cells) == mapping['body_count']
    domains = [[(F(p[0]), F(p[2])) for p in cell] for cell in cells]
    originals = []
    for i, polygon in enumerate(source['source']):
        polygon = [tuple(map(F, p)) for p in polygon]
        domain = [(p[0], p[2]) for p in polygon]
        originals.append((i, domain, api['roof'](polygon), sides(domain), api['bounds'](domain)))
    caps = [sides([(F(p[0]), F(p[2])) for p in polygon]) for polygon in source['caps']]
    bodies, offset = [], 0
    for count in mapping['body_faces']:
        bodies.append([tuple(tuple(map(F, p)) for p in f)
                       for f in raw['faces'][offset:offset+count]])
        offset += count
    assert offset == len(raw['faces'])
    rows = []
    for satellite in provenance['satellites']:
        for comparison in satellite['equal_bounds_body_surface_comparisons']:
            body_id = comparison['body']
            body = bodies[body_id]
            bottom = min(p[1] for face in body for p in face)
            footprint = [[(p[0], p[2]) for p in face] for face in body
                         if all(p[1] == bottom for p in face)]
            assert footprint and all(area(p) > 0 for p in footprint)
            cuts = [sides(p) for p in footprint]
            box = api['bounds']([p for polygon in footprint for p in polygon])
            selected, partial, checks, cap_overlaps = [], [], [], []
            remaining_body = footprint
            for i, domain in enumerate(domains):
                if not api['meets'](box, api['bounds'](domain)):
                    continue
                missing = [domain]
                touched = False
                for cutter in cuts:
                    overlap = domain
                    for h in cutter:
                        overlap = clip(overlap, h)
                    touched |= bool(overlap)
                    missing = [part for piece in missing for part in subtract(piece, cutter)]
                if not touched:
                    continue
                if missing:
                    partial.append(dict(cell=i, positive_uncovered_fragments=len(missing)))
                    continue
                selected.append(i)
                remaining_body = [part for piece in remaining_body
                                  for part in subtract(piece, sides(domain))]
                top = list(map(F, core['volumes'][mapping['body_begin']+i][0]))
                assert top[1] > 0
                roof = (-top[0]/top[1], -top[2]/top[1], top[3]/top[1])
                missing_source, higher, owners = api['source_checks'](
                    domain, roof, originals, F(1, 50000))
                missing_domain, differences = [domain], []
                for source_id, source_domain, source_roof, source_cuts, source_box in originals:
                    if not api['meets'](api['bounds'](domain), source_box):
                        continue
                    overlap = domain
                    for h in source_cuts:
                        overlap = clip(overlap, h)
                    if not overlap:
                        continue
                    missing_domain = [part for piece in missing_domain
                                      for part in subtract(piece, source_cuts)]
                    delta = [api['at'](roof, p)-api['at'](source_roof, p) for p in overlap]
                    differences.append(dict(source=source_id, area_exact=str(area(overlap)),
                                            minimum_nominal_minus_source_m=float(min(delta)),
                                            maximum_nominal_minus_source_m=float(max(delta))))
                checks.append(dict(cell=i, original_domain_covered=not missing_source,
                                   no_higher_original_owner=not higher,
                                   original_owners=owners,
                                   uncovered_source_area_exact=str(sum(map(area, missing_source), F(0))),
                                   uncovered_original_footprint_area_exact=str(sum(map(area, missing_domain), F(0))),
                                   nominal_source_height_overlays=differences,
                                   higher_owner_count=len(higher)))
                for cap, cutter in enumerate(caps):
                    overlap = domain
                    for h in cutter:
                        overlap = clip(overlap, h)
                    if overlap:
                        cap_overlaps.append(dict(cell=i, cap=cap, area_exact=str(area(overlap))))
            rows.append(dict(component=satellite['component'], candidate_body=body_id,
                             exact_emitted_surface_equivalent=comparison['exact_surface_equivalent'],
                             whole_selected_cells=selected, partial_cell_overlaps=partial,
                             uncovered_body_footprint_fragments=len(remaining_body),
                             uncovered_body_projected_area_exact=str(sum(map(area, remaining_body), F(0))),
                             original_source_checks=checks, positive_cap_footprint_overlaps=cap_overlaps,
                             all_selected_cells_original_domain_and_owner=bool(checks) and all(
                                 c['original_domain_covered'] and c['no_higher_original_owner'] for c in checks)))
    paths = [getattr(args, k) for k in ('sources', 'chunks', 'core', 'mapping', 'bodies', 'provenance')]
    report = dict(scope=__doc__, input_sha256={str(p): hashlib.sha256(p.read_bytes()).hexdigest() for p in paths},
                  source_height_band_exact='1/50000', bodies=rows,
                  safe_omission_proved=False, original_retained_backing_closure_proved=False,
                  final_emitted_surface_proved=False, full_assembly_proved=False)
    args.output.write_text(json.dumps(report, indent=2)+'\n')
    print(args.core.name, [(r['candidate_body'], len(r['whole_selected_cells']),
                            len(r['partial_cell_overlaps']), r['uncovered_body_footprint_fragments'],
                            r['all_selected_cells_original_domain_and_owner'],
                            len(r['positive_cap_footprint_overlaps'])) for r in rows], flush=True)


if __name__ == '__main__':
    main()
