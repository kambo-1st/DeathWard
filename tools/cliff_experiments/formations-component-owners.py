#!/usr/bin/env python3
"""Locate interior witnesses of primary convex solids in emitted core components."""
import argparse
from collections import defaultdict
from fractions import Fraction as F
import hashlib
import itertools
import json
from pathlib import Path


def sub(a,b):return tuple(x-y for x,y in zip(a,b))
def dot(a,b):return sum(x*y for x,y in zip(a,b))
def cross(a,b):return (a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0])


def interior(planes):
    normals=[p[:3] for p in planes];vertices=set()
    for i,j,k in itertools.combinations(range(len(planes)),3):
        a,b,c=normals[i],normals[j],normals[k];det=dot(a,cross(b,c))
        if not det:continue
        u,v,w=cross(b,c),cross(c,a),cross(a,b)
        p=tuple((planes[i][3]*u[d]+planes[j][3]*v[d]+planes[k][3]*w[d])/det for d in range(3))
        if all(dot(n,p)<=plane[3] for n,plane in zip(normals,planes)):vertices.add(p)
    if len(vertices)<4:raise ValueError('No full-dimensional bounded primary polyhedron')
    p=tuple(sum(v[d] for v in vertices)/len(vertices) for d in range(3))
    if not all(dot(n,p)<plane[3] for n,plane in zip(normals,planes)):raise ValueError('Primary witness is not strictly inside its nominal solid')
    return p,len(vertices)


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('mesh',type=Path);parser.add_argument('mapping',type=Path)
    parser.add_argument('--output',type=Path,required=True);args=parser.parse_args()
    data=json.loads(args.mesh.read_text());mapping=json.loads(args.mapping.read_text());faces=[tuple(tuple(map(F,p)) for p in f) for f in data['faces']]
    parent=list(range(len(faces)));edge_owner={}
    def root(i):
        while parent[i]!=i:parent[i]=parent[parent[i]];i=parent[i]
        return i
    for i,f in enumerate(faces):
        for a,b in zip(f,f[1:]+f[:1]):
            edge=tuple(sorted((a,b)))
            if edge in edge_owner:
                x,y=root(i),root(edge_owner[edge]);parent[max(x,y)]=min(x,y)
            else:edge_owner[edge]=i
    grouped=defaultdict(list)
    for i in range(len(faces)):grouped[root(i)].append(i)
    components=sorted(grouped.values(),key=lambda c:(-len(c),c[0]));owners={i:k for k,c in enumerate(components) for i in c}
    boxes=[(min(float(p[0]) for p in f),min(float(p[2]) for p in f),max(float(p[0]) for p in f),max(float(p[2]) for p in f)) for f in faces]
    def contains(point):
        hits=[defaultdict(set) for c in components];x,y,z=point;fx,fz=float(x),float(z)
        for i,(a,b,c) in enumerate(faces):
            box=boxes[i]
            if not(box[0]<=fx<=box[2] and box[1]<=fz<=box[3]):continue
            ux,uz,uy=b[0]-a[0],b[2]-a[2],b[1]-a[1];vx,vz,vy=c[0]-a[0],c[2]-a[2],c[1]-a[1];det=ux*vz-uz*vx
            if not det:continue
            u=((x-a[0])*vz-(z-a[2])*vx)/det;v=(ux*(z-a[2])-uz*(x-a[0]))/det
            if u<0 or v<0 or u+v>1:continue
            height=a[1]+u*uy+v*vy
            if height>y:hits[owners[i]][height].add(1 if det<0 else -1)
        inside=[]
        for component,levels in enumerate(hits):
            for height in sorted(levels):
                if len(levels[height])>1:continue # Tangential edge/vertex event.
                if levels[height]=={1}:inside.append(component)
                break
        return inside
    rows=[]
    for i,volume in enumerate(data['volumes'][:mapping['body_begin']]):
        p,vertices=interior([tuple(map(F,h)) for h in volume]);inside=contains(p)
        rows.append(dict(primary=i,main_cliff=i<5,exact_interior_witness=list(map(str,p)),feasible_vertices=vertices,containing_components=inside))
    report=dict(scope='Exact feasible convex-primary interior witnesses and rational vertical-ray winding events locate primary solids in edge-connected emitted mesh components. Existing strict closed-surface validation is a prerequisite. This does not prove whole-volume containment, original-terrain ownership of unlabelled components or full assembly/world acceptance.',mesh=str(args.mesh),mapping=str(args.mapping),input_sha256={str(p):hashlib.sha256(p.read_bytes()).hexdigest() for p in [args.mesh,args.mapping]},components=[dict(component=i,triangles=len(c),primary_witnesses=[r['primary'] for r in rows if i in r['containing_components']],main_cliff_witnesses=[r['primary'] for r in rows if r['main_cliff'] and i in r['containing_components']]) for i,c in enumerate(components)],primaries=rows,all_primary_witnesses_in_unique_components=all(len(r['containing_components'])==1 for r in rows),main_cliffs_share_component=len({r['containing_components'][0] for r in rows[:5] if len(r['containing_components'])==1})==1 and all(len(r['containing_components'])==1 for r in rows[:5]),full_assembly_proved=False)
    args.output.write_text(json.dumps(report,indent=2)+'\n')
    print(args.mesh.name,[(c['triangles'],c['main_cliff_witnesses']) for c in report['components']], 'unique primaries',report['all_primary_witnesses_in_unique_components'])


if __name__=='__main__':main()
