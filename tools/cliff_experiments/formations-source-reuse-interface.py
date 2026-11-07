#!/usr/bin/env python3
"""Exact saved-grid adjacency and nominal height gaps across reuse boundaries.

Necessary interface diagnosis only; does not prove a retained-world assembly.
"""
import argparse
from collections import defaultdict
from fractions import Fraction as F
import hashlib
import json
import math
from pathlib import Path


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    for name in ['chunks','core','mapping','reuse']:parser.add_argument(name,type=Path)
    parser.add_argument('--output',required=True,type=Path)
    args=parser.parse_args()
    load=lambda p:json.loads(p.read_text())
    cells=[p for chunk in load(args.chunks)['chunks'] for p in chunk['cells']]
    core=load(args.core);mapping=load(args.mapping);reuse=load(args.reuse)
    assert hashlib.sha256(args.core.read_bytes()).hexdigest()==reuse['input_sha256'][str(args.core)]
    volumes=core['volumes'][mapping['body_begin']:mapping['body_begin']+mapping['body_count']]
    if len(cells)!=len(volumes):raise ValueError('One-cell/one-prism correspondence not established')
    selected=set(reuse['eligible_prisms']);events=defaultdict(lambda:defaultdict(lambda:defaultdict(int)));roofs=[]
    max_side_residual=F(0);max_height_residual=F(0)
    for i,(cell,volume) in enumerate(zip(cells,volumes)):
        top=list(map(F,volume[0]));h=(-top[0]/top[1],-top[2]/top[1],top[3]/top[1]);roofs.append(h)
        ring=[]
        for p in cell:
            p=list(map(F,p));x,z=p[0]*65536,p[2]*65536
            if x.denominator!=1 or z.denominator!=1:raise ValueError('Cell is not on exact saved grid')
            ring.append((int(x),int(z)))
            max_height_residual=max(max_height_residual,abs(h[0]*p[0]+h[1]*p[2]+h[2]-p[1]))
            for side in volume[2:]:
                a,b,c,d=map(F,side);max_side_residual=max(max_side_residual,a*p[0]+b*p[1]+c*p[2]-d)
        for a,b in zip(ring,ring[1:]+ring[:1]):
            x,z=b[0]-a[0],b[1]-a[1]
            if x==z==0:continue
            g=math.gcd(x,z);A,B=z//g,-x//g;C=-A*a[0]-B*a[1]
            if A<0 or (A==0 and B<0):A,B,C=-A,-B,-C
            axis=0 if B else 1;lo,hi=sorted((a[axis],b[axis]));key=(A,B,C)
            events[key][lo][i]+=1;events[key][hi][i]-=1
    # This verifies correspondence only, not reuse acceptance or a weld.
    if max_side_residual>F(1,10**8) or max_height_residual>F(1,10**5):raise ValueError('Cell/prism correspondence exceeds diagnostic bound')
    neighbours=[set() for _ in cells];interfaces=[];adjacency=[];outer=[0,0];nonmanifold=[];same_kind=[0,0]
    for line,positions in events.items():
        active=defaultdict(int);order=sorted(positions);A,B,C=line
        for k,left in enumerate(order[:-1]):
            for i,delta in positions[left].items():
                active[i]+=delta
                if active[i]==0:del active[i]
            right=order[k+1]
            if not active or left==right:continue
            ids=sorted(active)
            if len(ids)>2:
                nonmanifold.append(dict(line=line,interval=[left,right],cells=ids));continue
            if len(ids)==1:outer[int(ids[0] in selected)]+=1;continue
            a,b=ids;neighbours[a].add(b);neighbours[b].add(a)
            points=[(F(q),F(-A*q-C,B)) if B else (F(-C,A),F(q)) for q in [left,right]]
            gaps=[abs(sum((roofs[a][j]-roofs[b][j])*p[j]/65536 for j in range(2))+roofs[a][2]-roofs[b][2]) for p in points]
            segment=dict(cells=ids,endpoints_xz=[[str(v/65536) for v in p] for p in points],maximum_nominal_vertical_gap_m=float(max(gaps)),within_20um=max(gaps)<=F(1,50000))
            adjacency.append(segment)
            if (a in selected)==(b in selected):same_kind[int(a in selected)]+=1;continue
            interfaces.append(dict(segment,eligible_cell=a if a in selected else b))
    # Retain extra transition cells in reconstruction instead of moving a
    # boundary across an unsupported height jump. Only shrink reuse eligibility.
    bad_neighbours=[set() for _ in cells]
    for segment in adjacency:
        if not segment['within_20um']:
            a,b=segment['cells'];bad_neighbours[a].add(b);bad_neighbours[b].add(a)
    guarded=set(selected);todo=[]
    for i in selected:
        if any(j not in selected for j in bad_neighbours[i]):guarded.remove(i);todo.append(i)
    while todo:
        i=todo.pop()
        for j in bad_neighbours[i]:
            if j in guarded:guarded.remove(j);todo.append(j)
    guarded_interfaces=[s for s in adjacency if (s['cells'][0] in guarded)!=(s['cells'][1] in guarded)]
    assert guarded<=selected and all(s['within_20um'] for s in guarded_interfaces)
    def components(ids):
        remaining=set(ids);sizes=[]
        while remaining:
            seed=remaining.pop();todo=[seed];size=0
            while todo:
                i=todo.pop();size+=1
                for j in neighbours[i]:
                    if j in remaining:remaining.remove(j);todo.append(j)
            sizes.append(size)
        return sorted(sizes,reverse=True)
    result=dict(scope='Exact collinear saved-grid edge splitting, including T junctions. Roof gaps compare nominal adjacent prism planes at both segment endpoints, not complete original-source/backing geometry. Bound of 20 micrometres is a necessary simple-weld precheck, not a general acceptance or closure proof. Cap membership, foundation, side-wall cutting, emitted welded mesh and full world/floor/replay acceptance are excluded.',chunks=str(args.chunks),reuse=str(args.reuse),input_sha256={str(p):hashlib.sha256(p.read_bytes()).hexdigest() for p in [args.chunks,args.core,args.mapping,args.reuse]},cells=len(cells),eligible_cells=len(selected),maximum_cell_prism_side_residual_m=float(max_side_residual),maximum_cell_prism_height_residual_m=float(max_height_residual),eligible_component_sizes=components(selected),modified_component_sizes=components(set(range(len(cells)))-selected),outside_segments=dict(eligible=outer[1],modified=outer[0]),same_kind_internal_segments=dict(eligible=same_kind[1],modified=same_kind[0]),nonmanifold_collinear_segments=nonmanifold,interface_segments=len(interfaces),interfaces_exceeding_20um=sum(not x['within_20um'] for x in interfaces),maximum_nominal_vertical_gap_m=max((x['maximum_nominal_vertical_gap_m'] for x in interfaces),default=0),interfaces=interfaces,shared_closure_proved=False,safe_omission_proved=False)
    result['guarded_reuse']=dict(scope='Monotonic eligibility erosion along above-20um adjacent roof jumps. Additional cells stay reconstructed; no geometry is omitted or moved. This only bounds nominal top gaps at shared saved-grid edges. Whole original-source/weld/link/foundation/assembly closure remains unproved.',eligible_prisms=sorted(guarded),eligible_cells=len(guarded),additional_transition_cells_retained=len(selected-guarded),retained_transition_prisms=sorted(selected-guarded),interface_segments=len(guarded_interfaces),interfaces_exceeding_20um=0,maximum_nominal_vertical_gap_m=max((s['maximum_nominal_vertical_gap_m'] for s in guarded_interfaces),default=0),eligible_component_sizes=components(guarded),modified_component_sizes=components(set(range(len(cells)))-guarded))
    args.output.write_text(json.dumps(result,indent=2)+'\n')
    print(f'{args.chunks.name}: {len(interfaces)} interface segments; {result["interfaces_exceeding_20um"]} over 20um; {len(nonmanifold)} collinear nonmanifold segments')


if __name__=='__main__':main()
