#!/usr/bin/env python3
"""Exact positive overlaps in captured input roof-cell footprints."""
import argparse
from collections import defaultdict
from fractions import Fraction as F
import hashlib
import json
import math
from pathlib import Path
import runpy


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('cells',type=Path);parser.add_argument('--output',type=Path,required=True)
    args=parser.parse_args();api=runpy.run_path(str(Path(__file__).with_name('formations-source-reuse.py')))
    source=json.loads(args.cells.read_text());polys=[p for c in source['chunks'] for p in c['cells']]
    cells=[];bins=defaultdict(list);pairs=set()
    for i,p in enumerate(polys):
        domain=[(F(q[0]),F(q[2])) for q in p];box=api['bounds'](domain);cells.append((domain,api['sides'](domain),box))
        for x in range(math.floor(float(box[0])),math.floor(float(box[2]))+1):
            for z in range(math.floor(float(box[1])),math.floor(float(box[3]))+1):
                for j in bins[x,z]:
                    if api['meets'](box,cells[j][2]):pairs.add((j,i))
                bins[x,z].append(i)
    positives=[];witnesses=[]
    for i,j in sorted(pairs):
        overlap=cells[i][0]
        for cut in cells[j][1]:overlap=api['clip'](overlap,cut)
        if overlap:
            area=api['area'](overlap);positives.append(dict(pair=[i,j],exact_area=str(area),area_m2=float(area)))
            if len(witnesses)<12:witnesses.append(dict(pair=[i,j],left=polys[i],right=polys[j],intersection_xz=[[str(x) for x in p] for p in overlap],exact_area=str(area)))
    report=dict(scope='Exact positive intersections of original captured cell footprints; no area cutoff. Pair areas are not a union area. This diagnoses nominal input ownership, not the final Boolean surface or terrain/world acceptance.',cells=str(args.cells),sha256=hashlib.sha256(args.cells.read_bytes()).hexdigest(),cell_count=len(cells),candidate_pairs=len(pairs),positive_pairs=len(positives),overlaps=positives,witnesses=witnesses)
    args.output.write_text(json.dumps(report,indent=2)+'\n')
    print(f'{args.cells.name}: {len(positives)} positive overlaps / {len(pairs)} pairs')


if __name__=='__main__':main()
