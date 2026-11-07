#!/usr/bin/env python3
"""Exact necessary source-domain/upper-owner checks before terrain reuse.

Never removes geometry or establishes shared-interface closure. Saved binary64
coefficients and binary32 vertices are interpreted as exact rational numbers.
"""
import argparse
from fractions import Fraction as F
import hashlib
import itertools
import json
import math
from pathlib import Path


def area(p):
    return abs(sum(a[0]*b[1]-a[1]*b[0] for a,b in zip(p,p[1:]+p[:1])))/2


def at(h,p):
    return h[0]*p[0]+h[1]*p[1]+h[2]


def clip(p,h):
    """Keep h(x,z) <= 0, retaining every positive-area fragment."""
    out=[]
    for a,b in zip(p,p[1:]+p[:1]):
        u,v=at(h,a),at(h,b)
        if u<=0:out.append(a)
        if u*v<0:
            t=u/(u-v);out.append(tuple(a[k]+t*(b[k]-a[k]) for k in range(2)))
    return out if len(out)>=3 and area(out)>0 else []


def sides(p):
    signed=sum(a[0]*b[1]-a[1]*b[0] for a,b in zip(p,p[1:]+p[:1]))
    if signed==0:raise ValueError('Source domain has zero area')
    sign=1 if signed>0 else -1
    result=[(sign*(b[1]-a[1]),sign*(a[0]-b[0]),sign*(b[0]*a[1]-a[0]*b[1])) for a,b in zip(p,p[1:]+p[:1])]
    if any(at(h,q)>0 for h in result for q in p):raise ValueError('Source domain is not convex')
    return result


def subtract(p,hs):
    """Disjoint positive-area convex fragments outside a convex cutter."""
    remaining=p;out=[]
    for h in hs:
        outside=clip(remaining,tuple(-v for v in h))
        # A coincident constraint has no strictly outside region.
        if outside and any(at(h,q)>0 for q in outside):out.append(outside)
        remaining=clip(remaining,h)
        if not remaining:break
    return out


def roof(poly):
    a=poly[0]
    for b,c in itertools.combinations(poly[1:],2):
        ux,uz,uy=b[0]-a[0],b[2]-a[2],b[1]-a[1]
        vx,vz,vy=c[0]-a[0],c[2]-a[2],c[1]-a[1]
        det=ux*vz-uz*vx
        if det:
            x,z=(uy*vz-uz*vy)/det,(ux*vy-uy*vx)/det
            h=(x,z,a[1]-x*a[0]-z*a[2])
            if any(at(h,(p[0],p[2]))!=p[1] for p in poly):raise ValueError('Source polygon is not exactly planar')
            return h
    raise ValueError('Source roof has no projected area')


def bounds(p):return (min(q[0] for q in p),min(q[1] for q in p),max(q[0] for q in p),max(q[1] for q in p))
def meets(a,b):return a[0]<b[2] and b[0]<a[2] and a[1]<b[3] and b[1]<a[3]


def source_checks(domain,h,originals,margin):
    """Return exact uncovered fragments and any strictly higher owner."""
    remaining=[domain];higher=[];owners=[];box=bounds(domain)
    for index,p,s,hs,pbox in originals:
        if not meets(box,pbox):continue
        overlap=domain
        for side in hs:overlap=clip(overlap,side)
        if not overlap:continue
        delta=tuple(s[k]-h[k] for k in range(3))
        high=(delta[0],delta[1],delta[2]-margin)
        above=clip(overlap,tuple(-x for x in high))
        if above and any(at(high,q)>0 for q in above):higher.append((index,above))
        band=[(delta[0],delta[1],delta[2]-margin),(-delta[0],-delta[1],-delta[2]-margin)]
        covered=overlap
        for cut in band:covered=clip(covered,cut)
        if covered:
            owners.append(index)
            remaining=[piece for old in remaining for piece in subtract(old,hs+band)]
    return remaining,higher,owners


def self_check():
    square=[(F(0),F(0)),(F(1),F(0)),(F(1),F(1)),(F(0),F(1))]
    def original(i,p,y):return (i,p,(F(0),F(0),F(y)),sides(p),bounds(p))
    h=(F(0),F(0),F(2));margin=F(1,10000)
    assert source_checks(square,h,[original(0,square,2)],margin)[:2]==([],[])
    gap=F(1,10**12)
    left=[(F(0),F(0)),(F(1,2)-gap,F(0)),(F(1,2)-gap,F(1)),(F(0),F(1))]
    right=[(F(1,2),F(0)),(F(1),F(0)),(F(1),F(1)),(F(1,2),F(1))]
    missing,_,_=source_checks(square,h,[original(0,left,2),original(1,right,2)],margin)
    assert sum(map(area,missing))==gap
    _,higher,_=source_checks(square,h,[original(0,square,2),original(1,right,3)],margin)
    assert higher and area(higher[0][1])==F(1,2)
    assert not source_checks(square,h,[original(0,square,F(2)+margin)],margin)[1]
    assert source_checks(square,h,[original(0,square,F(2)+margin+gap)],margin)[1]
    assert sum(map(area,subtract(square,[(F(0),F(0),F(0))])))==0
    return dict(controls=['covered','positive tiny domain gap','higher overlapping owner','exact height margin','positive tiny excess height','coincident half-plane'],passed=6)


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('sources',type=Path,nargs='?')
    parser.add_argument('core',type=Path,nargs='?')
    parser.add_argument('mapping',type=Path,nargs='?')
    parser.add_argument('--output',type=Path,required=True)
    parser.add_argument('--self-check',action='store_true')
    args=parser.parse_args()
    if args.self_check:
        args.output.write_text(json.dumps(self_check(),indent=2)+'\n');return
    if not all([args.sources,args.core,args.mapping]):parser.error('sources, core and mapping are required')
    source=json.loads(args.sources.read_text());core=json.loads(args.core.read_text());mapping=json.loads(args.mapping.read_text())
    originals=[];bins={};quantum=1e-8
    for i,p in enumerate(source['source']):
        p=[tuple(F(v) for v in q) for q in p];h=roof(p);domain=[(q[0],q[2]) for q in p]
        originals.append((i,domain,h,sides(domain),bounds(domain)))
        key=tuple(round(float(v)/quantum) for v in h);bins.setdefault(key,[]).append(h)
    points=[p for f in core['faces'] for p in f]
    box=tuple(F(v) for v in (math.floor(min(p[0] for p in points))-1,math.floor(min(p[2] for p in points))-1,math.ceil(max(p[0] for p in points))+1,math.ceil(max(p[2] for p in points))+1))
    margin=F(1,10000);rows=[];eligible=[];witnesses=[];candidates=0;total_area=F(0);eligible_area=F(0)
    for local,volume in enumerate(core['volumes'][mapping['body_begin']:mapping['body_begin']+mapping['body_count']]):
        top=tuple(F(v) for v in volume[0]);h=(-top[0]/top[1],-top[2]/top[1],top[3]/top[1])
        key=tuple(round(float(v)/quantum) for v in h)
        candidate=any(max(abs(float(a-b)) for a,b in zip(h,s))<=1e-10 for off in itertools.product((-1,0,1),repeat=3) for s in bins.get(tuple(key[k]+off[k] for k in range(3)),[]))
        domain=[(box[0],box[1]),(box[2],box[1]),(box[2],box[3]),(box[0],box[3])]
        for side in volume[2:]:
            x,y,z,d=map(F,side)
            if y:raise ValueError('Prism has nonvertical side')
            domain=clip(domain,(x,z,-d))
        if not domain:raise ValueError('Prism has no footprint')
        if any(p[0] in (box[0],box[2]) or p[1] in (box[1],box[3]) for p in domain):raise ValueError('Artificial bounding box truncates prism')
        a=area(domain);total_area+=a
        if not candidate:continue
        candidates+=1
        missing,higher,owners=source_checks(domain,h,originals,margin)
        ok=not missing and not higher
        row=dict(prism=local,volume=mapping['body_begin']+local,domain_covered=not missing,no_higher_original_owner=not higher,matching_original_domains=owners,projected_area_m2=float(a),uncovered_area_m2=float(sum(map(area,missing))),higher_owner_count=len(higher))
        rows.append(row)
        if ok:eligible.append(local);eligible_area+=a
        elif len(witnesses)<12:
            witness=dict(row)
            witness.update(domain=[[str(x) for x in p] for p in domain],uncovered=[[[str(x) for x in p] for p in fragment] for fragment in missing[:3]],higher=[dict(source=i,polygon=[[str(x) for x in p] for p in fragment]) for i,fragment in higher[:3]])
            witnesses.append(witness)
    result=dict(scope='Necessary exact projected original-domain coverage and upper-owner checks for nominal constructed-prism reuse. Vertical height band is exactly 0.1 mm. Plane match is only a conservative numerical prefilter. No positive uncovered area is discarded. Shared closure, cap coverage, full original-world/floor acceptance and safe omission remain unproved. No geometry changed.',sources=str(args.sources),core=str(args.core),mapping=str(args.mapping),input_sha256={str(p):hashlib.sha256(p.read_bytes()).hexdigest() for p in [args.sources,args.core,args.mapping]},prisms=mapping['body_count'],plane_match_candidates=candidates,domain_and_owner_eligible=len(eligible),eligible_prisms=eligible,total_summed_prism_area_m2=float(total_area),eligible_summed_prism_area_m2=float(eligible_area),candidates=rows,rejection_witnesses=witnesses,shared_closure_proved=False,safe_omission_proved=False)
    args.output.write_text(json.dumps(result,indent=2)+'\n')
    print(f'{args.sources.name}: {len(eligible)}/{candidates} plane candidates pass exact domain/owner checks; {mapping["body_count"]} total prisms',flush=True)


if __name__=='__main__':main()
