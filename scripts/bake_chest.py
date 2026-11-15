#!/usr/bin/env python3
"""Bake an opening chest from the existing Frontier scene asset library.

Uses the same imported mesh/material as Fort Mercy's frontier_part_0273.
Only the hinged split and interior lining are new; there is no separate FBX import.
"""
import hashlib
import json
import math
from pathlib import Path
import struct

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / 'assets/frontier/town.glb'
CATALOG = ROOT / 'assets/frontier/town.manifest.json'
ASSET = 'part_0273'
OUT = ROOT / 'assets/pickups/chest'
SEAM = .48
HINGE = (0, SEAM, -.29)


def clipped(poly, above):
    result = []
    for a, b in zip(poly, poly[1:] + poly[:1]):
        ia, ib = (a[1] >= SEAM), (b[1] >= SEAM)
        if ia == above:
            result.append(a)
        if ia != ib:
            t = (SEAM - a[1]) / (b[1] - a[1])
            result.append([x + t * (y - x) for x, y in zip(a, b)])
    return result


def source_mesh():
    raw = SOURCE.read_bytes()
    json_size = struct.unpack_from('<I', raw, 12)[0]
    doc = json.loads(raw[20:20+json_size])
    binary = raw[28+json_size:]
    def view(index):
        v = doc['bufferViews'][index]
        return binary[v.get('byteOffset', 0):v.get('byteOffset', 0)+v['byteLength']]
    def accessor(index):
        a = doc['accessors'][index]
        assert not a.get('sparse')
        v = doc['bufferViews'][a['bufferView']]
        fmt = '<' + {5126: 'f', 5123: 'H', 5125: 'I'}[a['componentType']] * {'SCALAR': 1, 'VEC2': 2, 'VEC3': 3}[a['type']]
        stride = v.get('byteStride', struct.calcsize(fmt))
        data = view(a['bufferView'])
        return [struct.unpack_from(fmt, data, a.get('byteOffset', 0)+i*stride) for i in range(a['count'])]
    record = json.loads(CATALOG.read_text())['assets'][ASSET]
    assert record['mesh_source'] == 'c6eae656502a37b45a9aafea777de703_4300000'
    node = next(n for n in doc['nodes'] if n.get('name') == ASSET)
    assert set(node) == {'mesh', 'name'}, 'Expected baked asset coordinates'
    mesh = doc['meshes'][node['mesh']]
    assert len(mesh['primitives']) == 1
    prim = mesh['primitives'][0]
    positions, normals, uvs = [accessor(prim['attributes'][k]) for k in ['POSITION', 'NORMAL', 'TEXCOORD_0']]
    vertices = [list(positions[i]+normals[i]+uvs[i]) for (i,) in accessor(prim['indices'])]
    material = doc['materials'][prim['material']]
    texture = doc['textures'][material['pbrMetallicRoughness']['baseColorTexture']['index']]
    img = doc['images'][texture['source']]
    return vertices, material, view(img['bufferView'])


def lining():
    faces = [
        ([(-.5,.08,-.25),(-.5,.08,.25),(.5,.08,.25),(.5,.08,-.25)], (0,1,0)),
        ([(-.5,.08,-.25),(-.5,.48,-.25),(-.5,.48,.25),(-.5,.08,.25)], (1,0,0)),
        ([(.5,.08,.25),(.5,.48,.25),(.5,.48,-.25),(.5,.08,-.25)], (-1,0,0)),
        ([(-.5,.08,-.25),(.5,.08,-.25),(.5,.48,-.25),(-.5,.48,-.25)], (0,0,1)),
        ([(.5,.08,.25),(-.5,.08,.25),(-.5,.48,.25),(.5,.48,.25)], (0,0,-1)),
    ]
    return [list(points[i]+normal+(0,0)) for points,normal in faces for i in (0,1,2,0,2,3)]


def write(name, vertices, source_material, texture):
    blob = bytearray()
    views, accessors = [], []
    def view(data):
        while len(blob) % 4:
            blob.append(0)
        views.append({'buffer': 0, 'byteOffset': len(blob), 'byteLength': len(data)})
        blob.extend(data)
        return len(views)-1
    def primitive(verts, material):
        attrs = {}
        for key, indices, kind in [('POSITION',(0,1,2),'VEC3'),('NORMAL',(3,4,5),'VEC3'),('TEXCOORD_0',(6,7),'VEC2')]:
            data = [[v[i] for i in indices] for v in verts]
            # UVs are already in glTF coordinates from the normal scene bake.
            if key == 'NORMAL':
                data = [[x/math.sqrt(sum(a*a for a in v)) for x in v] for v in data]
            if key == 'POSITION' and name == 'lid':
                data = [[v[i]-HINGE[i] for i in range(3)] for v in data]
            index = view(struct.pack('<'+'f'*len(data)*len(indices), *(x for v in data for x in v)))
            a = {'bufferView':index,'componentType':5126,'count':len(data),'type':kind}
            if key == 'POSITION':
                a.update(min=[min(v[i] for v in data) for i in range(3)],max=[max(v[i] for v in data) for i in range(3)])
            attrs[key] = len(accessors)
            accessors.append(a)
        return {'attributes':attrs,'material':material}
    primitives = [primitive(vertices, 0)]
    if name == 'base':
        primitives.append(primitive(lining(), 1))
    tex = view(texture)
    material = json.loads(json.dumps(source_material))
    material['pbrMetallicRoughness']['baseColorTexture']['index'] = 0
    material['doubleSided'] = True
    doc = {'asset':{'version':'2.0','generator':'DeathWard scene-library chest bake'},
           'scene':0,'scenes':[{'nodes':[0]}],'nodes':[{'mesh':0,'name':name}],
           'meshes':[{'primitives':primitives}],
           'materials':[material,{'name':'chest_interior','doubleSided':True,'pbrMetallicRoughness':{'baseColorFactor':[.19,.11,.08,1],'metallicFactor':0,'roughnessFactor':.8}}],
           'textures':[{'source':0}],'images':[{'bufferView':tex,'mimeType':'image/png'}],
           'buffers':[{'byteLength':len(blob)}],'bufferViews':views,'accessors':accessors}
    encoded = json.dumps(doc,separators=(',',':')).encode()
    encoded += b' ' * (-len(encoded)%4)
    blob += b'\0' * (-len(blob)%4)
    glb = struct.pack('<III',0x46546C67,2,28+len(encoded)+len(blob))+struct.pack('<II',len(encoded),0x4E4F534A)+encoded+struct.pack('<II',len(blob),0x004E4942)+blob
    (OUT/(name+'.glb')).write_bytes(glb)
    return {'triangles':len(vertices)//3+(10 if name=='base' else 0),'sha256':hashlib.sha256(glb).hexdigest()}


def main():
    raw, material, texture = source_mesh()
    OUT.mkdir(parents=True, exist_ok=True)
    records = {}
    for name, above in [('base', False), ('lid', True)]:
        vertices = []
        for i in range(0, len(raw), 3):
            poly = clipped(raw[i:i+3], above)
            for j in range(1, len(poly)-1):
                vertices.extend([poly[0], poly[j], poly[j+1]])
        records[name] = write(name, vertices, material, texture)
    manifest = {'source_model': str(SOURCE.relative_to(ROOT)), 'source_sha256': hashlib.sha256(SOURCE.read_bytes()).hexdigest(),
                'source_asset': ASSET, 'fort_mercy_asset': 'frontier_part_0273', 'texture_sha256': hashlib.sha256(texture).hexdigest(),
                'seam_y': SEAM, 'hinge': HINGE, 'adaptation': 'Existing scene-library mesh split at lid seam; original glTF UVs/material/embedded texture preserved. Interior lining is baked mesh; runtime only poses the lid.', 'outputs': records}
    (OUT/'manifest.json').write_text(json.dumps(manifest, indent=2)+'\n')
    print(json.dumps(records))


if __name__ == '__main__':
    main()
