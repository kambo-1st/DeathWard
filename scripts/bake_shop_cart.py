#!/usr/bin/env python3
"""Extract the existing Fort Mercy merchant-wagon assembly with its original materials."""
import copy,hashlib,json,math,struct
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'assets/redstone/town.glb'
SCENE=ROOT/'assets/redstone/town.scene'
OUT=ROOT/'assets/props/shop-cart'

def main():
    raw=SOURCE.read_bytes();jsize=struct.unpack_from('<I',raw,12)[0]
    src=json.loads(raw[20:20+jsize]);binary=raw[28+jsize:]
    def data_view(i):
        v=src['bufferViews'][i];start=v.get('byteOffset',0);return binary[start:start+v['byteLength']]
    def accessor(i):
        a=src['accessors'][i];v=src['bufferViews'][a['bufferView']]
        fmt='<'+{5126:'f',5123:'H',5125:'I'}[a['componentType']]*{'SCALAR':1,'VEC2':2,'VEC3':3}[a['type']]
        stride=v.get('byteStride',struct.calcsize(fmt));data=data_view(a['bufferView'])
        return [struct.unpack_from(fmt,data,a.get('byteOffset',0)+n*stride) for n in range(a['count'])]
    assets=[];instances=[]
    for line in SCENE.read_text().splitlines():
        t=line.split()
        if t and t[0]=='asset':assets.append((t[1],int(t[2]),int(t[3])))
        if t and t[0]=='instance' and t[2].startswith('story-merchant-wagon:'):instances.append((int(t[1]),t[2],list(map(float,t[3:]))))
    assert len(instances)==13
    parts=[];points=[]
    for index,name,m in instances:
        assert len(m)==16
        # All existing assembly transforms are proper rotations (unit scale).
        for row in range(3):assert abs(sum(m[4*row+k]**2 for k in range(3))-1)<1e-5
        _,first,count=assets[index]
        for mesh in src['meshes'][first:first+count]:
            for p in mesh['primitives']:
                pos=accessor(p['attributes']['POSITION']);norm=accessor(p['attributes']['NORMAL']);uv=accessor(p['attributes']['TEXCOORD_0']);idx=accessor(p['indices'])
                transformed=[[sum(m[4*r+k]*v[k] for k in range(3))+m[4*r+3] for r in range(3)] for v in pos]
                normals=[[sum(m[4*r+k]*v[k] for k in range(3)) for r in range(3)] for v in norm]
                points+=transformed;parts.append((transformed,normals,uv,idx,p['material']))
    lo=[min(v[i] for v in points) for i in range(3)];hi=[max(v[i] for v in points) for i in range(3)]
    center=[(lo[0]+hi[0])/2,lo[1],(lo[2]+hi[2])/2]
    scale=4.4/max(hi[0]-lo[0],hi[2]-lo[2])
    blob=bytearray();views=[];accessors=[];materials=[];images=[];textures=[];material_map={};prims=[]
    def view(data):
        blob.extend(b'\0'*(-len(blob)%4));views.append({'buffer':0,'byteOffset':len(blob),'byteLength':len(data)});blob.extend(data);return len(views)-1
    def attr(rows,kind):
        v=view(struct.pack('<'+'f'*sum(len(r) for r in rows),*(x for r in rows for x in r)))
        a={'bufferView':v,'componentType':5126,'count':len(rows),'type':kind}
        if kind=='VEC3':a.update(min=[min(r[i] for r in rows) for i in range(3)],max=[max(r[i] for r in rows) for i in range(3)])
        accessors.append(a);return len(accessors)-1
    for pos,norm,uv,idx,mat in parts:
        if mat not in material_map:
            material_map[mat]=len(materials);m=copy.deepcopy(src['materials'][mat]);m['doubleSided']=True
            tex=m['pbrMetallicRoughness']['baseColorTexture'];image=src['images'][src['textures'][tex['index']]['source']]
            images.append({'bufferView':view(data_view(image['bufferView'])),'mimeType':image['mimeType']})
            tex['index']=len(textures);textures.append({'source':len(images)-1});materials.append(m)
        pos=[[(v[i]-center[i])*scale for i in range(3)] for v in pos]
        attrs={'POSITION':attr(pos,'VEC3'),'NORMAL':attr(norm,'VEC3'),'TEXCOORD_0':attr(uv,'VEC2')}
        v=view(struct.pack('<'+'I'*len(idx),*(r[0] for r in idx)));accessors.append({'bufferView':v,'componentType':5125,'count':len(idx),'type':'SCALAR'})
        prims.append({'attributes':attrs,'indices':len(accessors)-1,'material':material_map[mat]})
    doc={'asset':{'version':'2.0','generator':'DeathWard existing merchant-wagon extraction'},'scene':0,'scenes':[{'nodes':[0]}],'nodes':[{'name':'shop_cart','mesh':0}],'meshes':[{'primitives':prims}],'materials':materials,'textures':textures,'images':images,'buffers':[{'byteLength':len(blob)}],'bufferViews':views,'accessors':accessors}
    encoded=json.dumps(doc,separators=(',',':')).encode();encoded+=b' '*(-len(encoded)%4);blob+=b'\0'*(-len(blob)%4)
    out=struct.pack('<III',0x46546c67,2,28+len(encoded)+len(blob))+struct.pack('<II',len(encoded),0x4e4f534a)+encoded+struct.pack('<II',len(blob),0x004e4942)+blob
    OUT.mkdir(parents=True,exist_ok=True);(OUT/'shop-cart.glb').write_bytes(out)
    manifest={'source_prefab':'Frontier/SM_Veh_Wagon_Shop_01','source_assembly':'Fort Mercy story-merchant-wagon','source_glb':str(SOURCE.relative_to(ROOT)),'source_sha256':hashlib.sha256(raw).hexdigest(),'source_scene_sha256':hashlib.sha256(SCENE.read_bytes()).hexdigest(),'parts':len(parts),'triangles':sum(len(p[3])//3 for p in parts),'dimensions':[(hi[i]-lo[i])*scale for i in range(3)],'bounds_min':[(lo[i]-center[i])*scale for i in range(3)],'bounds_max':[(hi[i]-center[i])*scale for i in range(3)],'baked_uniform_scale':scale,'output_sha256':hashlib.sha256(out).hexdigest(),'adaptation':'Existing 13-part assembled merchant wagon, original UVs and embedded material. Uniform scale to 4.4 longest ground dimension; centered XZ and grounded at Y0.'}
    (OUT/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n');print(json.dumps(manifest,indent=2))
if __name__=='__main__':main()
