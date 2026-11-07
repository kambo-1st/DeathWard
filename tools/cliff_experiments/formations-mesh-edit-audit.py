#!/usr/bin/env python3
"""Independent exact projected-cutout and changed-face audit for a bounded mesh repair."""
import argparse
from collections import Counter
from fractions import Fraction as F
import hashlib
import json
import math
from pathlib import Path


def area2(p):return sum(a[0]*b[1]-a[1]*b[0] for a,b in zip(p,p[1:]+p[:1]))
def project(face):return [(F(p[0]),F(p[2])) for p in face]
def box(p):return min(v[0] for v in p),min(v[1] for v in p),max(v[0] for v in p),max(v[1] for v in p)
def meets(a,b):return a[0]<b[2] and a[2]>b[0] and a[1]<b[3] and a[3]>b[1]
def clip(poly,a,b,direction,outside=False):
    def side(p):return direction*((b[0]-a[0])*(p[1]-a[1])-(b[1]-a[1])*(p[0]-a[0]))
    values=[side(p) for p in poly]
    if not poly or (outside and min(values)>=0) or (not outside and max(values)<0):return []
    result=[]
    for i,p in enumerate(poly):
        q=poly[(i+1)%len(poly)];u,v=values[i],values[(i+1)%len(poly)]
        if (u<=0 if outside else u>=0):result.append(p)
        if u*v<0:
            t=u/(u-v);result.append((p[0]+t*(q[0]-p[0]),p[1]+t*(q[1]-p[1])))
    return result

def intersect(poly,cutter):
    direction=1 if area2(cutter)>0 else -1
    for a,b in zip(cutter,cutter[1:]+cutter[:1]):
        poly=clip(poly,a,b,direction)
        if len(poly)<3:return []
    return poly

def subtract(poly,cutter):
    if not area2(intersect(poly,cutter)):return [poly]
    direction=1 if area2(cutter)>0 else -1;result=[]
    for a,b in zip(cutter,cutter[1:]+cutter[:1]):
        outside=clip(poly,a,b,direction,True)
        if area2(outside):result.append(outside)
        poly=clip(poly,a,b,direction)
        if len(poly)<3:break
    return result

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('before',type=Path);parser.add_argument('after',type=Path)
    parser.add_argument('--cutouts',type=Path,required=True);parser.add_argument('--output',type=Path,required=True)
    args=parser.parse_args();before=json.loads(args.before.read_text());after=json.loads(args.after.read_text())
    if before['volumes']!=after['volumes']:raise ValueError('Nominal source planes changed')
    def key(face):return tuple(tuple(p) for p in face)
    previous=Counter(key(f) for f in before['faces']);edited=[];edited_ids=[]
    for i,f in enumerate(after['faces']):
        k=key(f)
        if previous[k]:previous[k]-=1
        else:edited.append(f);edited_ids.append(i)
    probe=args.output.with_suffix('.edited.json');probe.write_text(json.dumps(dict(faces=edited,pairs=[],volumes=after['volumes']))+'\n')
    old_vertices={tuple(p) for f in before['faces'] for p in f};new_vertices={tuple(p) for f in after['faces'] for p in f}
    def distance(a,b):return math.sqrt(sum((x-y)**2 for x,y in zip(a,b)))
    hausdorff=max([0]+[min(distance(p,q) for q in old_vertices) for p in new_vertices-old_vertices]+[min(distance(p,q) for q in new_vertices) for p in old_vertices-new_vertices])
    collapse=None
    if edited:
        common=set(tuple(p) for p in edited[0])
        for face in edited[1:]:common.intersection_update(tuple(p) for p in face)
        removed_vertices=old_vertices-new_vertices
        if len(common)==1 and 1<=len(removed_vertices)<=2:
            target=next(iter(common));expected=[];discarded=0
            for face in before['faces']:
                mapped=tuple(target if tuple(p) in removed_vertices else tuple(p) for p in face)
                if len(set(mapped))<3:discarded+=1
                else:expected.append(mapped)
            same=Counter(expected)==Counter(key(f) for f in after['faces'])
            collapse=dict(target=target,old_vertices=sorted(removed_vertices),removed_triangles=discarded,
                          exactly_reproduces_after_mesh=same,
                          maximum_vertex_displacement_m=max(distance(p,target) for p in removed_vertices))

    def projection_key(face):
        p=project(face);return tuple(sorted(p)) if area2(p) else None
    old_xy=Counter(k for f in before['faces'] if (k:=projection_key(f)) is not None)
    new_xy=Counter(k for f in after['faces'] if (k:=projection_key(f)) is not None)
    unchanged_xy=old_xy==new_xy;holes=[project(h) for h in json.loads(args.cutouts.read_text())['holes']]
    for h in holes:
        turns=[(b[0]-a[0])*(c[1]-b[1])-(b[1]-a[1])*(c[0]-b[0]) for a,b,c in zip(h,h[1:]+h[:1],h[2:]+h[:2])]
        if not area2(h) or min(turns)<0<max(turns):raise ValueError('Protected cutout is not convex')
    reference=[(p,box(p)) for f in before['faces'] if area2(p:=project(f))]
    violations=[];checked=0
    if not unchanged_xy:
        for i,face in zip(edited_ids,edited):
            p=project(face)
            if not area2(p):continue
            bounds=box(p)
            for hole_id,h in enumerate(holes):
                if not meets(bounds,box(h)):continue
                region=intersect(p,h)
                if not area2(region):continue
                checked+=1;parts=[region];bounds2=box(region)
                for old,old_box in reference:
                    if not meets(bounds2,old_box):continue
                    parts=[piece for part in parts for piece in subtract(part,old)]
                    if not parts:break
                total=sum(abs(area2(part)) for part in parts)/2
                if total:violations.append(dict(face=i,hole=hole_id,exact_added_area=str(total),added_area_m2=float(total)))
    status=dict(before=str(args.before),after=str(args.after),cutouts=str(args.cutouts),input_sha256={str(p):hashlib.sha256(p.read_bytes()).hexdigest() for p in [args.before,args.after,args.cutouts]},edited_faces=len(edited),edited_face_ids=edited_ids,removed_or_changed_old_faces=sum(previous.values()),net_faces_removed=len(before['faces'])-len(after['faces']),edited_source_probe=str(probe),nominal_source_planes_identical=True,vertex_set_hausdorff_m=hausdorff,independent_single_collapse=collapse,nonzero_projected_triangle_multiset_identical=unchanged_xy,checked_cutout_regions=checked,additional_cutout_overlap_pairs=len(violations),violations=violations,scope='Exact positive projected area added in each original convex cutout relative to the entire prior core footprint; all positive intermediate pieces retained, no area tolerance. Does not prove original floor/assembly acceptance or absence of pre-existing coverage. Pair areas are not union areas. Vertex-set Hausdorff is a separate displacement diagnostic.')
    args.output.write_text(json.dumps(status,indent=2)+'\n');print(f"Edited {len(edited)} faces; removed {status['net_faces_removed']}; new cutout coverage pairs {len(violations)}; vertex-set distance {hausdorff:.9g} m")
    return int(bool(violations) or hausdorff>.00002)

if __name__=='__main__':raise SystemExit(main())
