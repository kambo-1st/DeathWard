#!/usr/bin/env python3
"""Exact overlay of a shared-source simplification versus its complete input field."""
import argparse
from collections import Counter,defaultdict
from fractions import Fraction as F
import hashlib
import json
import math
from pathlib import Path
import runpy


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    for name in ['sources','input_cells','certificate','output_cells']:parser.add_argument(name,type=Path)
    parser.add_argument('--output',required=True,type=Path)
    args=parser.parse_args();load=lambda p:json.loads(p.read_text())
    api=runpy.run_path(str(Path(__file__).with_name('formations-source-reuse.py')))
    cert=load(args.certificate);source=load(args.sources)
    old=[p for c in load(args.input_cells)['chunks'] for p in c['cells']]
    actual=[p for c in load(args.output_cells)['chunks'] for p in c['cells']]
    new=[c['points'] for c in cert['output_cells']]
    def identity(p):return tuple(tuple(q) for q in p)
    assert Counter(map(identity,actual))==Counter(map(identity,new))
    assert len(old)==cert['input_cells']==len(cert['input_cell_planes']) and len(new)==cert['output_cell_count']
    roofs=[]
    for x,y,z,d in cert['planes']:
        x,y,z,d=map(F,(x,y,z,d));roofs.append((-x/y,-z/y,d/y))
    limit=F(cert['maximum_switched_vertical_difference_exact']);position=F(cert['maximum_original_edge_distance_exact']);assert limit==position==F(1,50000)
    original_edges=defaultdict(list)
    for polygon in source['source']:
        h=api['roof']([tuple(map(F,p)) for p in polygon])
        for a,b in zip(polygon,polygon[1:]+polygon[:1]):original_edges[tuple(sorted((tuple(a),tuple(b))))].append(h)
    edit_failures=[]
    for i,edit in enumerate(cert['edits']):
        edge=edit['source_edge'];owners=original_edges.get(tuple(sorted(map(tuple,edge))),[]);a,b=[(F(p[0]),F(p[2])) for p in edge]
        delta=(b[0]-a[0],b[1]-a[1]);length=delta[0]**2+delta[1]**2
        heights=[roofs[j] for j in edit['planes']]
        good=length>0 and all(any(max(abs(float(x-y)) for x,y in zip(h,s))<=1e-10 for s in owners) for h in heights)
        for name in ['a_grid','removed_grid','b_grid']:
            p=tuple(F(x,65536) for x in edit[name]);t=max(F(0),min(F(1),sum((p[k]-a[k])*delta[k] for k in range(2))/length)) if length else F(0)
            good &= sum((p[k]-a[k]-t*delta[k])**2 for k in range(2))<=position**2
            good &= abs(api['at'](heights[0],p)-api['at'](heights[1],p))<=limit
        if not good:edit_failures.append(i)
    def cell(p,g):
        dom=[(F(q[0]),F(q[2])) for q in p]
        return dict(domain=dom,cuts=api['sides'](dom),box=api['bounds'](dom),roof=roofs[g])
    before=[cell(p,g) for p,g in zip(old,cert['input_cell_planes'])]
    after=[cell(c['points'],c['plane']) for c in cert['output_cells']]
    def bins_for(box):
        for x in range(math.floor(float(box[0])),math.floor(float(box[2]))+1):
            for z in range(math.floor(float(box[1])),math.floor(float(box[3]))+1):yield x,z
    bins=defaultdict(set)
    for i,c in enumerate(before):
        for key in bins_for(c['box']):bins[key].add(i)
    old_missing=[[c['domain']] for c in before];new_missing=[];height_failures=[];max_difference=F(0);overlays=0
    for j,c in enumerate(after):
        nearby=set()
        for key in bins_for(c['box']):nearby.update(bins[key])
        missing=[c['domain']]
        for i in sorted(nearby):
            oldcell=before[i]
            if not api['meets'](c['box'],oldcell['box']):continue
            overlap=c['domain']
            for h in oldcell['cuts']:overlap=api['clip'](overlap,h)
            if not overlap:continue
            overlays+=1;difference=max(abs(api['at'](c['roof'],p)-api['at'](oldcell['roof'],p)) for p in overlap);max_difference=max(max_difference,difference)
            if difference>limit:height_failures.append(dict(old=i,new=j,exact_difference=str(difference)))
            missing=[part for p in missing for part in api['subtract'](p,oldcell['cuts'])]
            old_missing[i]=[part for p in old_missing[i] for part in api['subtract'](p,c['cuts'])]
        if missing:new_missing.append(dict(cell=j,positive_fragments=len(missing)))
    old_gaps=[dict(cell=i,positive_fragments=len(p)) for i,p in enumerate(old_missing) if p]
    old_area=sum((api['area'](c['domain']) for c in before),F(0));new_area=sum((api['area'](c['domain']) for c in after),F(0))
    result=dict(scope='Every emitted roof cell is overlaid against the complete saved constructed input field using rational arithmetic. Positive-area coverage is checked in both directions and affine-height differences at every overlap vertex. Original raw shared-edge identity, proximity and per-edit height bounds are checked. The original input partition is separately certified by native exact polygon-set operations. This does not prove final Boolean/float output, immutable-world terrain/cap/floor/backing joins, visuals, gameplay or performance.',input_sha256={str(p):hashlib.sha256(p.read_bytes()).hexdigest() for p in [args.sources,args.input_cells,args.certificate,args.output_cells]},input_cells=len(before),output_cells=len(after),removed_nodes=len(cert['edits']),actual_output_matches_certificate=True,edit_failures=edit_failures,positive_overlay_parts=overlays,maximum_exact_height_difference=str(max_difference),maximum_height_difference_m=float(max_difference),height_failures=height_failures,new_field_uncovered=new_missing,original_field_uncovered=old_gaps,total_summed_area_equal=old_area==new_area,full_assembly_proved=False)
    args.output.write_text(json.dumps(result,indent=2)+'\n')
    print(f'{args.certificate.name}: {len(before)} -> {len(after)} cells; {overlays} exact overlap parts; maximum height change {float(max_difference):.9g}m')
    return int(bool(edit_failures or height_failures or new_missing or old_gaps or old_area!=new_area))


if __name__=='__main__':raise SystemExit(main())
