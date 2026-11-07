#!/usr/bin/env python3
"""Exact rational intersection areas between emitted chunk roofs and original convex cutouts."""
import argparse
from fractions import Fraction as F
import hashlib
import json
from pathlib import Path


def area2(poly):
    return sum(a[0]*b[1]-a[1]*b[0] for a,b in zip(poly,poly[1:]+poly[:1]))


def intersection(subject,clip):
    direction=1 if area2(clip)>0 else -1
    for a,b in zip(clip,clip[1:]+clip[:1]):
        def side(p):
            return direction*((b[0]-a[0])*(p[1]-a[1])-(b[1]-a[1])*(p[0]-a[0]))
        out=[]
        for p,q in zip(subject,subject[1:]+subject[:1]):
            u,v=side(p),side(q)
            if u>=0:out.append(p)
            if (u<0<v) or (v<0<u):
                t=u/(u-v);out.append((p[0]+t*(q[0]-p[0]),p[1]+t*(q[1]-p[1])))
        subject=out
        if len(subject)<3:return []
    return subject


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('sources',type=Path)
    parser.add_argument('chunks',type=Path)
    parser.add_argument('--output',type=Path,required=True)
    args=parser.parse_args()
    source=json.loads(args.sources.read_text());chunks=json.loads(args.chunks.read_text())
    def polygon(p):return [(F(v[0]),F(v[2])) for v in p]
    def box(p):return min(v[0] for v in p),min(v[1] for v in p),max(v[0] for v in p),max(v[1] for v in p)
    holes=[polygon(p) for p in source['holes']]
    for h in holes:
        turns=[(b[0]-a[0])*(c[1]-b[1])-(b[1]-a[1])*(c[0]-b[0]) for a,b,c in zip(h,h[1:]+h[:1],h[2:]+h[:2])]
        if area2(h)==0 or min(turns)<0<max(turns):raise ValueError('Cutout is not a positive convex polygon')
    boxes=[box(h) for h in holes];violations=[];candidates=0;count=0
    for chunk in chunks['chunks']:
        for cell in chunk['cells']:
            p=polygon(cell);b=box(p);count+=1
            for i,(h,hb) in enumerate(zip(holes,boxes)):
                if b[0]>=hb[2] or b[2]<=hb[0] or b[1]>=hb[3] or b[3]<=hb[1]:continue
                candidates+=1;area=abs(area2(intersection(p,h)))/2
                if area:violations.append(dict(cell=count-1,hole=i,intersection_area_m2=float(area),exact_area=str(area)))
    status=dict(sources=str(args.sources),chunks=str(args.chunks),source_sha256=hashlib.sha256(args.sources.read_bytes()).hexdigest(),chunks_sha256=hashlib.sha256(args.chunks.read_bytes()).hexdigest(),scope='Projected emitted chunk roofs versus every saved original convex cutout; excludes cap bodies and full assembled terrain. Exact zero-area contact is allowed; every positive area is recorded. Pair areas are not a union area.',cells=count,holes=len(holes),candidate_pairs=candidates,positive_overlap_pairs=len(violations),violations=violations)
    args.output.write_text(json.dumps(status,indent=2)+'\n')
    print(f"Checked {count} cells against {len(holes)} original cutouts: {len(violations)} positive overlaps")
    return 1 if violations else 0


if __name__=='__main__':
    raise SystemExit(main())
