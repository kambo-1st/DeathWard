#!/usr/bin/env python3
"""Independently verify a native source-reuse mask against its captured inputs."""
import argparse
from collections import defaultdict
from fractions import Fraction as F
import hashlib
import json
import math
from pathlib import Path
import runpy
import struct


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    for name in ['sources','cells','mask']:parser.add_argument(name,type=Path)
    parser.add_argument('--constructed-chunks',type=Path,required=True)
    parser.add_argument('--output',type=Path,required=True)
    args=parser.parse_args();api=runpy.run_path(str(Path(__file__).with_name('formations-source-reuse.py')))
    load=lambda p:json.loads(p.read_text())
    source=load(args.sources);data=load(args.cells);mask=load(args.mask)
    cells=[p for c in data['chunks'] for p in c['cells']];roofs=[]
    for x,y,z,d in mask['roof_planes']:
        x,y,z,d=map(F,(x,y,z,d));roofs.append((-x/y,-z/y,d/y))
    eligible=set(mask['eligible']);guarded=set(mask['guarded']);margin=F(mask['height_margin_exact'])
    assert margin==F(1,50000) and len(cells)==len(roofs)==mask['cells'] and guarded<=eligible
    assert [p for c in load(args.constructed_chunks)['chunks'] for p in c['cells']]==[p for i,p in enumerate(cells) if i not in guarded]
    originals=[];bins=defaultdict(set)
    def bins_for(box):
        for x in range(math.floor(float(box[0])),math.floor(float(box[2]))+1):
            for z in range(math.floor(float(box[1])),math.floor(float(box[3]))+1):yield x,z
    for i,p in enumerate(source['source']):
        p=[tuple(map(F,q)) for q in p];domain=[(q[0],q[2]) for q in p];box=api['bounds'](domain)
        originals.append((i,domain,api['roof'](p),api['sides'](domain),box))
        for key in bins_for(box):bins[key].add(i)
    source_failures=[]
    for i in sorted(eligible):
        domain=[(F(p[0]),F(p[2])) for p in cells[i]];nearby=set()
        for key in bins_for(api['bounds'](domain)):nearby.update(bins[key])
        missing,higher,_=api['source_checks'](domain,roofs[i],[originals[j] for j in sorted(nearby)],margin)
        if missing or higher:source_failures.append(dict(cell=i,uncovered_fragments=len(missing),higher_owners=[j for j,p in higher]))
    events=defaultdict(lambda:defaultdict(lambda:defaultdict(int)))
    for i,p in enumerate(cells):
        ring=[(F(q[0])*65536,F(q[2])*65536) for q in p]
        assert all(x.denominator==z.denominator==1 for x,z in ring)
        ring=[(int(x),int(z)) for x,z in ring]
        for a,b in zip(ring,ring[1:]+ring[:1]):
            x,z=b[0]-a[0],b[1]-a[1];g=math.gcd(x,z)
            if not g:continue
            A,B=z//g,-x//g;C=-A*a[0]-B*a[1]
            if A<0 or (A==0 and B<0):A,B,C=-A,-B,-C
            axis=0 if B else 1;lo,hi=sorted((a[axis],b[axis]));events[A,B,C][lo][i]+=1;events[A,B,C][hi][i]-=1
    vertex_cells=defaultdict(set);vertex_edges=defaultdict(set);edge_failures=[];gap_failures=[];interface_count=0;maxgap=F(0)
    for (A,B,C),positions in events.items():
        active=defaultdict(int);order=sorted(positions)
        for left,right in zip(order,order[1:]):
            for i,delta in positions[left].items():
                active[i]+=delta
                if not active[i]:del active[i]
            if not active:continue
            ids=sorted(active)
            if len(ids)>2:edge_failures.append(dict(line=[A,B,C],interval=[left,right],cells=ids))
            points=[(F(t),F(-A*t-C,B)) if B else (F(-C,A),F(t)) for t in [left,right]]
            for point in points:
                assert all(q.denominator==1 for q in point)
                key=tuple(int(q) for q in point);vertex_cells[key].update(ids)
                if len(ids)==2:vertex_edges[key].add(tuple(ids))
            if len(ids)==2 and (ids[0] in guarded)!=(ids[1] in guarded):
                interface_count+=1
                gap=max(abs(api['at'](roofs[ids[0]],tuple(q/65536 for q in p))-api['at'](roofs[ids[1]],tuple(q/65536 for q in p))) for p in points);maxgap=max(maxgap,gap)
                if gap>margin:gap_failures.append(dict(cells=ids,exact_gap=str(gap)))
    # Same binary32 roof heights as construction, but a separate graph audit.
    f32=lambda x:struct.unpack('<f',struct.pack('<f',x))[0]
    fan_failures=[];sub_weld_fan_failures=[];intervals=0
    minimum_interval=F(mask.get('fan_minimum_interval_exact','0'))
    assert minimum_interval in (F(0),margin)
    for point,ids in vertex_cells.items():
        x,z=(q/65536 for q in point);heights={}
        for i in ids:
            nx,ny,nz,d=mask['roof_planes'][i];heights[i]=F(f32((d-nx*x-nz*z)/ny))
        levels=sorted({F(f32(-.12)),*heights.values()})
        for low,high in zip(levels,levels[1:]):
            level=(low+high)/2;active={i for i,h in heights.items() if i not in guarded and h>level};intervals+=1
            if len(active)<2:continue
            graph=defaultdict(set)
            for a,b in vertex_edges[point]:
                if a in active and b in active:graph[a].add(b);graph[b].add(a)
            visited=set();todo=[min(active)]
            while todo:
                i=todo.pop()
                if i in visited:continue
                visited.add(i);todo.extend(graph[i]-visited)
            if visited!=active:
                row=dict(point_grid=point,exact_height=str(level),interval_exact=str(high-low),interval_m=float(high-low),active_cells=sorted(active),first_component=sorted(visited))
                (sub_weld_fan_failures if high-low<=minimum_interval else fan_failures).append(row)
    result=dict(scope='All claimed eligible actual input cells: exact original-domain coverage and upper-owner checks at a 20um vertical band. Exact split saved-grid interfaces and emitted-height vertex-fan intervals of the reconstructed subset. This does not prove actual emitted core or original backing/cap/foundation/floor/world assembly, triangle budget, visual/gameplay or performance acceptance.',input_sha256={str(p):hashlib.sha256(p.read_bytes()).hexdigest() for p in [args.sources,args.cells,args.mask,args.constructed_chunks]},cells=len(cells),eligible_cells_checked=len(eligible),reused_cells=len(guarded),constructed_subset_matches_mask=True,source_failures=source_failures,nonmanifold_collinear_intervals=edge_failures,interface_segments=interface_count,maximum_interface_gap_m=float(maxgap),interface_gap_failures=gap_failures,vertex_fan_intervals_checked=intervals,vertex_fan_failures=fan_failures,complete_assembly_proved=False)
    result.update(fan_minimum_interval_exact=str(minimum_interval),sub_weld_fan_intervals_deferred_to_mesher=sub_weld_fan_failures)
    args.output.write_text(json.dumps(result,indent=2)+'\n')
    print(f'{args.mask.name}: {len(eligible)} eligible cells, {intervals} fan intervals; failures source={len(source_failures)} edges={len(edge_failures)} gaps={len(gap_failures)} fans={len(fan_failures)}')
    return int(bool(source_failures or edge_failures or gap_failures or fan_failures))


if __name__=='__main__':raise SystemExit(main())
