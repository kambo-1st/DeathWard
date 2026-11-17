#!/usr/bin/env python3
"""Extract Black Creek's existing stone-ring campfire, retaining mesh/material bytes."""
import argparse,copy,hashlib,json,struct
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'assets/town/town.glb'
OUT=ROOT/'assets/props/campfire'
def main():
    parser=argparse.ArgumentParser();parser.add_argument('--check',action='store_true');args=parser.parse_args()
    raw=SOURCE.read_bytes();length=struct.unpack_from('<I',raw,12)[0]
    src=json.loads(raw[20:20+length]);binary=raw[28+length:]
    node=next(n for n in src['nodes'] if n.get('name')=='part_0362');assert set(node)=={'name','mesh'}
    mesh=copy.deepcopy(src['meshes'][node['mesh']]);blob=bytearray();views=[];accessors=[];materials=[];textures=[];images=[]
    vm={};am={};mm={}
    def view(index):
        if index not in vm:
            v=copy.deepcopy(src['bufferViews'][index]);start=v.get('byteOffset',0);data=binary[start:start+v['byteLength']]
            blob.extend(b'\0'*(-len(blob)%4));v.update(buffer=0,byteOffset=len(blob));blob.extend(data);vm[index]=len(views);views.append(v)
        return vm[index]
    def accessor(index):
        if index not in am:
            a=copy.deepcopy(src['accessors'][index]);assert 'sparse' not in a;a['bufferView']=view(a['bufferView']);am[index]=len(accessors);accessors.append(a)
        return am[index]
    for p in mesh['primitives']:
        p['attributes']={k:accessor(v) for k,v in p['attributes'].items()};p['indices']=accessor(p['indices'])
        index=p['material']
        if index not in mm:
            m=copy.deepcopy(src['materials'][index]);t=m['pbrMetallicRoughness']['baseColorTexture'];tex=copy.deepcopy(src['textures'][t['index']]);im=copy.deepcopy(src['images'][tex['source']]);im['bufferView']=view(im['bufferView'])
            t['index']=len(textures);tex['source']=len(images);images.append(im);textures.append(tex);mm[index]=len(materials);materials.append(m)
        p['material']=mm[index]
    doc=dict(asset=dict(version='2.0',generator='DeathWard unchanged Black Creek campfire extraction'),scene=0,scenes=[dict(nodes=[0])],nodes=[dict(name='SM_Env_CampFire_01',mesh=0)],meshes=[mesh],accessors=accessors,bufferViews=views,buffers=[dict(byteLength=len(blob))],materials=materials,textures=textures,images=images,samplers=src.get('samplers',[]))
    js=json.dumps(doc,separators=(',',':')).encode();js+=b' '*(-len(js)%4);blob+=b'\0'*(-len(blob)%4)
    result=struct.pack('<III',0x46546c67,2,28+len(js)+len(blob))+struct.pack('<II',len(js),0x4e4f534a)+js+struct.pack('<II',len(blob),0x004e4942)+blob
    manifest=dict(source='assets/town/town.glb',source_sha256=hashlib.sha256(raw).hexdigest(),source_node='part_0362',label='SM_Env_CampFire_01',town_instance='fireplace-poc',output_sha256=hashlib.sha256(result).hexdigest(),triangles=sum(accessors[p['indices']]['count']//3 for p in mesh['primitives']),adaptation='Unchanged positions, normals, UVs, indices, original material and embedded atlas. Runtime uniform scale fits existing fire radius; particles read the same town.attachments entries.')
    outputs={'campfire.glb':result,'manifest.json':(json.dumps(manifest,indent=2)+'\n').encode()}
    if not args.check:OUT.mkdir(parents=True,exist_ok=True)
    for name,data in outputs.items():
        if args.check:assert (OUT/name).read_bytes()==data,name
        else:(OUT/name).write_bytes(data)
    print('PASS unchanged campfire extraction:',manifest['triangles'],'triangles,',len(result),'bytes')
if __name__=='__main__':main()
