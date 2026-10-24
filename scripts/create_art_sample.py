#!/usr/bin/env python3
"""Build isolated art-study derivatives. Never writes into a source asset pack.

Requires Python, numpy and Pillow. No Blender or Unity needed. The protagonist's
skin, skeleton and all nine animation streams are retained without resampling.
"""
from copy import deepcopy
import hashlib
import io
import json
import math
from pathlib import Path
import struct

import numpy as np
from PIL import Image

from create_redstone import Library, Pack

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'assets/art_sample'
TYPES = {5126: '<f4', 5123: '<u2', 5125: '<u4', 5121: 'u1'}
WIDTH = {'SCALAR': 1, 'VEC2': 2, 'VEC3': 3, 'VEC4': 4, 'MAT4': 16}


class Glb:
    def __init__(self, path):
        raw = path.read_bytes()
        size = struct.unpack_from('<I', raw, 12)[0]
        self.g = json.loads(raw[20:20 + size])
        self.b = bytearray(raw[28 + size:])
        self.images = {}

    def array(self, index):
        a = self.g['accessors'][index]
        v = self.g['bufferViews'][a['bufferView']]
        dtype = np.dtype(TYPES[a['componentType']])
        return np.ndarray((a['count'], WIDTH[a['type']]), dtype=dtype, buffer=self.b,
                          offset=v.get('byteOffset', 0) + a.get('byteOffset', 0),
                          strides=(v.get('byteStride', WIDTH[a['type']] * dtype.itemsize),
                                   dtype.itemsize)).copy()

    def blob(self, raw):
        self.b.extend(b'\0' * (-len(self.b) % 4))
        index = len(self.g['bufferViews'])
        self.g['bufferViews'].append({'buffer': 0, 'byteOffset': len(self.b), 'byteLength': len(raw)})
        self.b.extend(raw)
        return index

    def attribute(self, values, kind='VEC3', component=5126):
        a = np.asarray(values, dtype=TYPES[component]).reshape(-1, WIDTH[kind])
        item = dict(bufferView=self.blob(a.tobytes()), componentType=component,
                    count=len(a), type=kind)
        if kind == 'VEC3':
            item.update(min=a.min(axis=0).tolist(), max=a.max(axis=0).tolist())
        index = len(self.g['accessors'])
        self.g['accessors'].append(item)
        return index

    def color(self, material, uv):
        mat = self.g['materials'][material]['pbrMetallicRoughness']
        if 'baseColorTexture' not in mat:
            return np.array(mat.get('baseColorFactor', [1, 1, 1, 1])[:3])
        index = self.g['textures'][mat['baseColorTexture']['index']]['source']
        if index not in self.images:
            v = self.g['bufferViews'][self.g['images'][index]['bufferView']]
            raw = self.b[v.get('byteOffset', 0):v.get('byteOffset', 0) + v['byteLength']]
            self.images[index] = Image.open(io.BytesIO(raw)).convert('RGB')
        image = self.images[index]
        return np.array(image.getpixel((int(np.clip(uv[0], 0, .99999) * image.width),
                                        int(np.clip(uv[1], 0, .99999) * image.height)))) / 255

    def paint_material(self):
        image = len(self.g['images'])
        self.g['images'].append({'bufferView': self.blob((OUT / 'painted-atlas-v2.png').read_bytes()),
                                 'mimeType': 'image/png'})
        texture = len(self.g['textures'])
        self.g['textures'].append({'source': image})
        material = len(self.g['materials'])
        self.g['materials'].append({'name': 'Sample only / painted canvas, indigo, timber, leather',
                                   'doubleSided': True, 'pbrMetallicRoughness': {
                                       'baseColorTexture': {'index': texture},
                                       'metallicFactor': 0, 'roughnessFactor': 1}})
        return material

    def write(self, name):
        # All output destinations are fixed beneath the sample directory.
        path = OUT / name
        assert path.parent == OUT and path.suffix == '.glb'
        self.b.extend(b'\0' * (-len(self.b) % 4))
        self.g['buffers'] = [{'byteLength': len(self.b)}]
        raw = json.dumps(self.g, separators=(',', ':')).encode()
        raw += b' ' * (-len(raw) % 4)
        path.write_bytes(struct.pack('<III', 0x46546C67, 2, 28 + len(raw) + len(self.b)) +
                         struct.pack('<II', len(raw), 0x4E4F534A) + raw +
                         struct.pack('<II', len(self.b), 0x004E4942) + self.b)


def uv_tile(points, normal, tile, bounds=None):
    # Box projection in object space: continuous brushwork across adjacent faces.
    # A triangle never crosses a tile edge; the inset prevents filtering bleed.
    axes = [i for i in range(3) if i != np.argmax(np.abs(normal))]
    if tile == 2 and bounds is not None:
        long_axis = max(axes, key=lambda i: bounds[1][i] - bounds[0][i])
        axes = [i for i in axes if i != long_axis] + [long_axis]
    elif 1 in axes:
        axes = [i for i in axes if i != 1] + [1]
    if bounds is None:
        bounds = (np.full(3, -4.), np.full(3, 4.))
    uv = (points[:, axes] - bounds[0][axes]) / np.maximum(bounds[1][axes] - bounds[0][axes], .01)
    uv = np.clip(uv, 0, 1)
    uv[:, 1] = 1 - uv[:, 1]
    return uv * .46 + [(.5 if tile % 2 else 0) + .02, (.5 if tile >= 2 else 0) + .02]


def rewrite(glb, primitive, deform, paint, category, painted_material):
    attrs = {key: glb.array(index) for key, index in primitive['attributes'].items()}
    positions = attrs['POSITION']
    original = positions.copy()
    attrs['POSITION'] = deform(positions.copy())
    deformed = not np.array_equal(original, attrs['POSITION'])
    bounds = (attrs['POSITION'].min(axis=0), attrs['POSITION'].max(axis=0))
    indices = glb.array(primitive['indices']).ravel() if 'indices' in primitive else np.arange(len(positions))
    result = {False: [], True: []}
    for triangle in indices.reshape(-1, 3):
        p = attrs['POSITION'][triangle]
        center = original[triangle].mean(axis=0)
        rgb = glb.color(primitive['material'], attrs['TEXCOORD_0'][triangle].mean(axis=0))
        tile = category(center, rgb) if paint else None
        result[tile is not None].append((triangle, tile))
    primitives = []
    for painted, faces in result.items():
        if not faces:
            continue
        corners = np.concatenate([tri for tri, _ in faces])
        out = {key: value[corners].copy() for key, value in attrs.items() if key != 'TEXCOORD_1'}
        for face, (_, tile) in enumerate(faces):
            tri = slice(face * 3, face * 3 + 3)
            points = out['POSITION'][tri]
            normal = np.cross(points[1] - points[0], points[2] - points[0])
            normal /= max(np.linalg.norm(normal), 1e-8)
            if deformed:
                out['NORMAL'][tri] = normal
            if painted:
                out['TEXCOORD_0'][tri] = uv_tile(points, normal, tile, bounds)
        new = {'material': painted_material if painted else primitive['material'], 'attributes': {}}
        for key, values in out.items():
            comp = 5123 if key == 'JOINTS_0' else 5126
            new['attributes'][key] = glb.attribute(values, 'VEC' + str(values.shape[1]), comp)
        # raylib uses unsigned-short mesh indices. Fail instead of truncating.
        assert len(corners) < 65536, 'Split this primitive before exporting to raylib'
        new['indices'] = glb.attribute(np.arange(len(corners)), 'SCALAR', 5123)
        primitives.append(new)
    return primitives


def original_stage():
    frontier, town = Pack('frontier'), Pack('town')
    library = Library()
    wagon = next(group for group in frontier.groups.values()
                 if 'SM_Veh_Wagon_Travel_01.prefab' in group[0]['prefab'])
    root = np.array(next(p['transform'] for p in wagon if p['asset'] == 'part_0161')).reshape(4, 4)
    inv = np.linalg.inv(root)
    items = [('tent', frontier, 'part_0004', np.eye(4))]
    items += [('wagon', frontier, p['asset'], inv @ np.array(p['transform']).reshape(4, 4)) for p in wagon]
    items += [('fence', town, 'part_0021', np.eye(4))]
    groups = []
    for category, pack, key, matrix in items:
        name = library.asset(pack, key)
        a = library.assets[name]
        for mesh in range(a['first_mesh'], a['first_mesh'] + a['mesh_count']):
            groups.append((mesh, category, matrix))
    library.write(OUT / 'stage-original.glb')
    glb = Glb(OUT / 'stage-original.glb')
    minimum = {k: 1e6 for k in ('tent', 'wagon', 'fence')}
    for mesh, category, matrix in groups:
        for primitive in glb.g['meshes'][mesh]['primitives']:
            p = glb.array(primitive['attributes']['POSITION'])
            n = glb.array(primitive['attributes']['NORMAL'])
            p = (np.c_[p, np.ones(len(p))] @ matrix.T)[:, :3]
            n = n @ matrix[:3, :3].T
            primitive['attributes']['POSITION'] = glb.attribute(p)
            primitive['attributes']['NORMAL'] = glb.attribute(n)
            minimum[category] = min(minimum[category], p[:, 1].min())
    # A small, fixed tableau. Keep prop placement identical in all four states.
    offsets = {'tent': [-2.8, 0, -.8], 'wagon': [2.7, 0, -.9], 'fence': [-4.3, 0, 2.4]}
    for mesh, category, _ in groups:
        glb.g['meshes'][mesh]['name'] = category
        for primitive in glb.g['meshes'][mesh]['primitives']:
            p = glb.array(primitive['attributes']['POSITION'])
            p[:, 1] -= minimum[category]
            p += offsets[category]
            primitive['attributes']['POSITION'] = glb.attribute(p)
    glb.write('stage-original.glb')
    return offsets


def stage_variant(offsets, shapes, paint, suffix):
    glb = Glb(OUT / 'stage-original.glb')
    material = glb.paint_material() if paint else None
    for mesh in glb.g['meshes']:
        category = mesh['name']
        offset = np.array(offsets[category])

        def deform(points):
            if not shapes:
                return points
            p = points - offset
            if category == 'tent':
                # Sag along the ridge, retain planted edges and doorway clearance.
                fall = np.maximum(0, 1 - (p[:, 2] / 2.1) ** 2)
                p[:, 1] -= .32 * fall * np.clip((p[:, 1] - .4) / 1.7, 0, 1)
                p[:, 0] += .12 * np.sin(p[:, 2] * 1.8) * np.clip(p[:, 1], 0, 1)
            elif category == 'wagon':
                # A lower, listing canvas crown; running gear stays true.
                upper = np.maximum(0, p[:, 1] - 2)
                p[:, 0] += .14 * upper
                p[:, 1] -= .19 * upper * (1 + .35 * np.cos(p[:, 2] * 2.5))
            else:
                p[:, 1] *= .96 + .06 * np.sin(p[:, 0] * 3.2)
                p[:, 0] += .085 * p[:, 1] * np.sin(p[:, 0] * 2.1)
                p[:, 2] += .06 * p[:, 1] * np.cos(p[:, 0] * 2.5)
            return p + offset

        def surface(center, rgb):
            p = center - offset
            if category == 'fence':
                return 2
            if category == 'tent':
                return 0 if max(rgb) > .43 else 2
            if p[1] > 2.25:
                return 2  # Exposed hoops are wood, not canvas.
            if max(rgb) - min(rgb) < .025 and max(rgb) < .32:
                return None  # Keep iron fittings distinct from wood.
            return 2 if p[1] < 2.05 else 3

        mesh['primitives'] = [p for old in mesh['primitives']
                              for p in rewrite(glb, old, deform, paint, surface, material)]
    if shapes:
        add_stage_repairs(glb, offsets, paint, material)
    glb.write('stage-' + suffix + '.glb')


def extra_mesh(glb, vertices, triangles, tile, paint, material, weights=None):
    points, normals, uvs, joints, skin = [], [], [], [], []
    vertices = np.array(vertices)
    for tri in triangles:
        p = vertices[tri]
        n = np.cross(p[1] - p[0], p[2] - p[0])
        n /= max(np.linalg.norm(n), 1e-8)
        points.extend(p); normals.extend([n] * 3)
        uvs.extend(uv_tile(p, n, tile, (vertices.min(axis=0), vertices.max(axis=0))) if paint else [[.5, .5]] * 3)
        if weights:
            for i in tri:
                joints.append(weights[i][0]); skin.append(weights[i][1])
    attrs = {'POSITION': glb.attribute(points), 'NORMAL': glb.attribute(normals),
             'TEXCOORD_0': glb.attribute(uvs, 'VEC2')}
    if weights:
        attrs.update(JOINTS_0=glb.attribute(joints, 'VEC4', 5123),
                     WEIGHTS_0=glb.attribute(skin, 'VEC4'))
    assert len(points) < 65536
    return {'attributes': attrs, 'material': material,
            'indices': glb.attribute(np.arange(len(points)), 'SCALAR', 5123)}


def flat_material(glb, name, color):
    index = len(glb.g['materials'])
    glb.g['materials'].append({'name': name, 'doubleSided': True,
                             'pbrMetallicRoughness': {'baseColorFactor': color,
                                                     'metallicFactor': 0, 'roughnessFactor': 1}})
    return index


def add_stage_repairs(glb, offsets, paint, painted_material):
    timber = painted_material if paint else flat_material(glb, 'Sample repair timber', [.34, .27, .19, 1])
    canvas = painted_material if paint else flat_material(glb, 'Sample patched canvas', [.47, .43, .35, 1])
    primitives = []

    def board(a, b, width, depth, tile, material):
        a, b = np.array(a), np.array(b)
        along = (b - a) / np.linalg.norm(b - a)
        side = np.cross(along, [0, 0, 1])
        side /= max(np.linalg.norm(side), .001)
        thickness = np.cross(along, side)
        vertices = [p + side * x * width / 2 + thickness * y * depth / 2
                    for p in (a, b) for x, y in ((-1, -1), (1, -1), (1, 1), (-1, 1))]
        faces = [[0, 2, 1], [0, 3, 2], [4, 5, 6], [4, 6, 7],
                 [0, 1, 5], [0, 5, 4], [1, 2, 6], [1, 6, 5],
                 [2, 3, 7], [2, 7, 6], [3, 0, 4], [3, 4, 7]]
        primitives.append(extra_mesh(glb, vertices, faces, tile, paint, material))

    # Diagonal repairs and a partial replacement cover change the silhouette.
    o = np.array(offsets['wagon'])
    board(o + [1.08, .95, -.95], o + [1.13, 1.85, .95], .16, .09, 2, timber)
    board(o + [-.92, .92, 1.7], o + [.98, 1.08, 1.7], .2, .11, 2, timber)
    # A leaned brace makes the fence look repaired rather than factory straight.
    o = np.array(offsets['fence'])
    board(o + [.17, .18, .08], o + [2.94, 1.04, .08], .13, .09, 2, timber)
    board(o + [3.03, .01, -.04], o + [3.1, 1.15, -.08], .15, .17, 2, timber)
    # Canvas over the rear two thirds; the front hoop and seat remain exposed.
    o = np.array(offsets['wagon'])
    cover, faces = [], []
    for row, z in enumerate([-1.93, -1.38, -.82, -.27, .18]):
        for i in range(13):
            angle = i * math.pi / 12
            x = 1.03 * math.cos(angle)
            y = 2.29 + 1.05 * math.sin(angle)
            y -= .08 * math.sin(row * math.pi / 2) ** 2
            x += .12 * max(0, y - 2)
            edge = z + (.065 * math.sin(i * 1.6) if row == 4 else 0)
            cover.append(o + [x, y, edge])
    for row in range(4):
        for i in range(12):
            a = row * 13 + i
            faces += [[a, a + 1, a + 14], [a, a + 14, a + 13]]
    primitives.append(extra_mesh(glb, cover, faces, 0, paint, canvas))
    # Loose, uneven entrance valance. Short enough to leave the entrance open.
    o = np.array(offsets['tent'])
    verts = [o + [-.9, 1.76, 2.05], o + [0, 2.48, 2.05], o + [.85, 1.85, 2.05],
             o + [-.91, 1.59, 2.10], o + [-.1, 2.08, 2.18], o + [.83, 1.65, 2.10]]
    primitives.append(extra_mesh(glb, verts, [[0, 3, 4], [0, 4, 1], [1, 4, 5], [1, 5, 2]], 0, paint, canvas))
    mesh = len(glb.g['meshes'])
    glb.g['meshes'].append({'name': 'Sample repairs', 'primitives': primitives})
    node = len(glb.g['nodes'])
    glb.g['nodes'].append({'mesh': mesh})
    glb.g['scenes'][0]['nodes'].append(node)


def hero_variant(shapes, paint, suffix):
    glb = Glb(ROOT / 'assets/bandit/bandit.glb')
    material = glb.paint_material() if paint else None

    def deform(p):
        if shapes:
            hat = p[:, 1] > 1.68
            brim = hat & (p[:, 1] < 1.74)
            p[hat, 0] *= 1.2
            p[hat, 2] *= 1.12
            p[hat, 1] = 1.68 + (p[hat, 1] - 1.68) * .86
            p[brim, 1] += .075 * p[brim, 0] / .3
            crown = p[:, 1] > 1.77
            p[crown, 0] *= .83
        return p

    def surface(p, rgb):
        # Follow the source garment palette, not triangle-center height: a
        # height threshold produces jagged boot boundaries on long leg faces.
        swatch = tuple(np.rint(rgb * 255).astype(int))
        return {(42, 44, 47): 0,   # coat and sleeves
                (59, 53, 44): 1,   # trousers
                (52, 55, 58): 3,   # hat and boots
                (130, 116, 95): 0, # shirt
                (179, 155, 119): 0,# cuffs
                (68, 74, 78): 1,   # hat band
                (97, 70, 55): 3}.get(swatch)  # belt; face/hands/metal retained

    for mesh in glb.g['meshes']:
        mesh['primitives'] = [p for old in mesh['primitives']
                              for p in rewrite(glb, old, deform, paint, surface, material)]
    if shapes:
        if not paint:
            material = flat_material(glb, 'Sample shoulder wrap', [.19, .24, .29, 1])
        names = [glb.g['nodes'][i]['name'] for i in glb.g['skins'][0]['joints']]
        upper, lower = names.index('Spine_03'), names.index('Spine_01')
        vertices, weights = [], []
        # Open-neck, short on the gun arm, long on the opposite shoulder.
        for ring in range(3):
            for i in range(12):
                angle = i * math.tau / 12
                x, z = math.cos(angle), math.sin(angle)
                rx, rz = [( .12, .12), (.33, .20), (.31, .22)][ring]
                y = [1.49, 1.36, 1.02 + .18 * x + .035 * math.sin(angle * 3)][ring]
                vertices.append([rx * x, y, rz * z])
                mix = [1, .9, .28][ring]
                weights.append(([upper, lower, 0, 0], [mix, 1 - mix, 0, 0]))
        faces = []
        for ring in range(2):
            for i in range(12):
                a, b = ring * 12 + i, ring * 12 + (i + 1) % 12
                faces += [[a, a + 12, b + 12], [a, b + 12, b]]
        glb.g['meshes'][0]['primitives'].append(extra_mesh(glb, vertices, faces, 1, paint, material, weights))
        # A narrow, stitched ivory hem makes the wrap a designed garment.
        trim, trim_weights = [], []
        for offset in (.002, .04):
            for i in range(12):
                p = np.array(vertices[24 + i]); p[1] += offset
                p[[0, 2]] *= 1.008
                trim.append(p); trim_weights.append(weights[24 + i])
        trim_faces = []
        for i in range(12):
            j = (i + 1) % 12
            trim_faces += [[i, j, j + 12], [i, j + 12, i + 12]]
        trim_material = material if paint else flat_material(glb, 'Sample wrap hem', [.63, .57, .44, 1])
        glb.g['meshes'][0]['primitives'].append(extra_mesh(glb, trim, trim_faces, 0, paint, trim_material, trim_weights))
    # Geometry may change; animation accessors, skin matrices and nodes must not.
    source = Glb(ROOT / 'assets/bandit/bandit.glb')
    assert glb.g['animations'] == source.g['animations']
    assert glb.g['skins'] == source.g['skins'] and glb.g['nodes'] == source.g['nodes']
    glb.write('hero-' + suffix + '.glb')


def main():
    OUT.mkdir(exist_ok=True)
    sources = [ROOT / 'assets/bandit/bandit.glb']
    sources += [ROOT / 'assets' / pack / name for pack in ('town', 'frontier', 'redstone')
                for name in ('town.glb', 'town.scene', 'town.nav')]
    hashes = {str(p.relative_to(ROOT)): hashlib.sha256(p.read_bytes()).hexdigest() for p in sources}
    offsets = original_stage()
    for shapes, paint, name in [(True, False, 'shapes'), (False, True, 'paint'), (True, True, 'combined')]:
        stage_variant(offsets, shapes, paint, name)
        hero_variant(shapes, paint, name)
        print('Built', name)
    assert hashes == {str(p.relative_to(ROOT)): hashlib.sha256(p.read_bytes()).hexdigest() for p in sources}
    manifest = {'source_sha256': hashes, 'hero_animation_streams': 'unchanged, all nine clips',
                'texture_generation': 'Built-in imagegen; selected prompt in texture-prompt-v2.txt',
                'scope': 'Standalone art sample. No game assets, maps or saves are modified.'}
    (OUT / 'manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')
    print('PASS: original assets and all three maps unchanged')


if __name__ == '__main__':
    main()
