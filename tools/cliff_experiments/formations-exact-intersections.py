#!/usr/bin/env python3
"""Independent rational intersection oracle for emitted float-mesh probe files."""
from fractions import Fraction as F
from pathlib import Path
import argparse
import json

parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('mesh',type=Path)
parser.add_argument('--all-pairs',action='store_true')
parser.add_argument('--output',type=Path)
parser.add_argument('--source-boundary',action='store_true')
options=parser.parse_args()
source=json.loads(options.mesh.read_text())
def sub(a,b):return tuple(x-y for x,y in zip(a,b))
def add(a,b):return tuple(x+y for x,y in zip(a,b))
def mul(a,s):return tuple(x*s for x in a)
def dot(a,b):return sum(x*y for x,y in zip(a,b))
def cross(a,b):return (a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0])
faces=[tuple(tuple(F(float(x)) for x in p) for p in face) for face in source['faces']]
normals=[cross(sub(t[1],t[0]),sub(t[2],t[0])) for t in faces]
def inside(p,t,n):return all(dot(n,cross(sub(t[(k+1)%3],t[k]),sub(p,t[k])))>=0 for k in range(3))
def overlap(a,b,n):
    axis=max(range(3),key=lambda i:abs(n[i]))
    project=lambda p:tuple(p[i] for i in range(3) if i!=axis)
    turn=lambda a,b,c:(b[0]-a[0])*(c[1]-a[1])-(b[1]-a[1])*(c[0]-a[0])
    polygon=list(map(project,a));clip=list(map(project,b))
    sign=1 if turn(*clip)>0 else -1
    for k in range(3):
        result=[]
        for i,p in enumerate(polygon):
            q=polygon[(i+1)%len(polygon)]
            u=sign*turn(clip[k],clip[(k+1)%3],p);v=sign*turn(clip[k],clip[(k+1)%3],q)
            if u>=0:result.append(p)
            if u*v<0:result.append(add(p,mul(sub(q,p),u/(u-v))))
        polygon=result
    return abs(sum(polygon[i][0]*polygon[(i+1)%len(polygon)][1]-polygon[i][1]*polygon[(i+1)%len(polygon)][0] for i in range(len(polygon))))>0

def classify(i,j):
    a,b=faces[i],faces[j];na,nb=normals[i],normals[j]
    if dot(na,na)==0 or dot(nb,nb)==0:return 'degenerate'
    da=[dot(nb,sub(p,b[0])) for p in a];db=[dot(na,sub(p,a[0])) for p in b]
    separated=lambda values:all(v>0 for v in values) or all(v<0 for v in values)
    if separated(da) or separated(db):return 'disjoint'
    if all(v==0 for v in da+db):return 'coplanar_overlap' if overlap(a,b,na) else 'disjoint'
    common=set(a)&set(b)
    if len(common)>=2:return 'shared_edge'
    for frm,to,n,distances in [(a,b,nb,da),(b,a,na,db)]:
        for k in range(3):
            p,q=frm[k],frm[(k+1)%3];u,v=distances[k],distances[(k+1)%3]
            if u==0 and inside(p,to,n) and p not in common:return 'intersection'
            if u*v<0:
                hit=add(p,mul(sub(q,p),u/(u-v)))
                if inside(hit,to,n) and hit not in common:return 'intersection'
    return 'shared_vertex' if common else 'disjoint'

if options.all_pairs:
    boxes=[(tuple(min(p[k] for p in t) for k in range(3)),tuple(max(p[k] for p in t) for k in range(3))) for t in source['faces']]
    pairs=[]
    order=sorted(range(len(boxes)),key=lambda i:boxes[i][0][0])
    for at,i in enumerate(order):
        lo,hi=boxes[i]
        for j in order[at+1:]:
            low,high=boxes[j]
            if low[0]>hi[0]:break
            if all(lo[k]<=high[k] and low[k]<=hi[k] for k in range(3)):pairs.append(tuple(sorted((i,j))))
    pairs.sort()
else:pairs=source['pairs']
rows=[dict(pair=list(pair),classification=classify(*pair)) for pair in pairs]
conflicts=[row for row in rows if row['classification'] in ('intersection','coplanar_overlap','degenerate')]
reported=[dict(pair=pair,classification=classify(*pair)) for pair in source['pairs']]
status=dict(mesh=str(options.mesh),triangles=len(faces),checked_pairs=len(rows),all_bounding_box_pairs=options.all_pairs,
            conflicts=conflicts,reported_pairs=reported,scope='Exact rational arithmetic on every emitted binary-float coordinate, with no coplanarity/contact epsilon. Shared indexed-position edges and vertices are legitimate; other contact/intersection and every positive coplanar overlap are conflicts.')
if options.output:options.output.write_text(json.dumps(status,indent=2)+'\n')
from collections import Counter
print('Reported-pair exact classifications',dict(Counter(row['classification'] for row in reported)))
print('Checked',len(rows),'pairs;',len(conflicts),'exact conflicts')

if options.source_boundary:
    margin=F(.0001)
    volumes=[[tuple(F(float(x)) for x in plane) for plane in volume] for volume in source['volumes']]
    def value(p,plane):return dot(p,plane[:3])-plane[3]
    def clip(poly,plane,outside=False):
        if not poly:return []
        values=[value(p,plane) for p in poly]
        if outside and max(values)<=0:return []
        if not outside and min(values)>0:return []
        if (outside and min(values)>=0) or (not outside and max(values)<=0):return poly
        result=[]
        for i,p in enumerate(poly):
            j=(i+1)%len(poly);q=poly[j];u,v=values[i],values[j]
            if (u>=0 if outside else u<=0):result.append(p)
            if u*v<0:result.append(add(p,mul(sub(q,p),u/(u-v))))
        return result
    def area_vector(poly):
        total=(F(0),F(0),F(0))
        for k in range(1,len(poly)-1):total=add(total,cross(sub(poly[k],poly[0]),sub(poly[k+1],poly[0])))
        return total
    def substantial(poly):
        total=area_vector(poly)
        return dot(total,total)>4*F(1e-12)**2
    def positive(poly):
        total=area_vector(poly)
        return dot(total,total)>0
    def intersect(poly,volume):
        for plane in volume:
            poly=clip(poly,plane)
            if len(poly)<3:return []
        return poly
    expanded=[[plane[:3]+(plane[3]+margin,) for plane in v] for v in volumes]
    shrunk=[[plane[:3]+(plane[3]-margin,) for plane in v] for v in volumes]
    buried=[];detached=[];detached_fragments=0
    for face_id,face in enumerate(faces):
        for volume_id,volume in enumerate(shrunk):
            if substantial(intersect(list(face),volume)):buried.append(dict(face=face_id,volume=volume_id))
        if any(all(value(p,plane)<=0 for p in face for plane in volume) for volume in expanded):continue
        parts=[list(face)]
        for volume in expanded:
            keep=[]
            for part in parts:
                if not positive(intersect(part,volume)):keep.append(part);continue
                inside_part=part
                for plane in volume:
                    outside=clip(inside_part,plane,True)
                    if positive(outside):keep.append(outside)
                    inside_part=clip(inside_part,plane)
                    if len(inside_part)<3:break
            parts=keep
            if not parts:break
        total=(F(0),F(0),F(0))
        for part in parts:total=add(total,area_vector(part))
        if dot(total,total)>4*F(1e-12)**2:detached.append(face_id);detached_fragments+=sum(positive(part) for part in parts)
    status['exact_source_boundary']=dict(margin_m=.0001,buried=buried,detached=detached,detached_fragments=detached_fragments,
        area_policy='Total positive uncovered area per input face must not exceed 1e-12 m2; all positive intermediate pieces retained')
    if options.output:options.output.write_text(json.dumps(status,indent=2)+'\n')
    print('Exact source boundary:',len(buried),'buried;',len(detached),'detached',flush=True)
