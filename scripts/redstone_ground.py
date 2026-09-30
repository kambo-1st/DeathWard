"""Fit Redstone's fort floor and worn approaches to the canyon terrain."""
from copy import deepcopy
import math

import numpy as np


def accessor(library, index):
    item = library.gltf['accessors'][index]
    view = library.gltf['bufferViews'][item['bufferView']]
    dtype = np.dtype({5126: '<f4', 5123: '<u2', 5125: '<u4'}[item['componentType']])
    size = {'SCALAR': 1, 'VEC2': 2, 'VEC3': 3}[item['type']]
    return np.ndarray((item['count'], size), dtype=dtype, buffer=library.binary,
                      offset=view.get('byteOffset', 0) + item.get('byteOffset', 0),
                      strides=(view.get('byteStride', size * dtype.itemsize), dtype.itemsize)).copy()


def triangles(library, placement):
    asset = library.assets[placement['asset']]
    assert asset['mesh_count'] == 1
    primitive = library.gltf['meshes'][asset['first_mesh']]['primitives'][0]
    attrs = {key: accessor(library, value) for key, value in primitive['attributes'].items()}
    matrix = np.array(placement['transform']).reshape(4, 4)
    positions = (matrix @ np.c_[attrs['POSITION'], np.ones(len(attrs['POSITION']))].T).T[:, :3]
    normals = attrs['NORMAL'] @ np.linalg.inv(matrix[:3, :3])
    normals /= np.linalg.norm(normals, axis=1)[:, None]
    vertices = np.c_[positions, normals, attrs['TEXCOORD_0']]
    indices = (accessor(library, primitive['indices']).reshape(-1) if 'indices' in primitive
               else np.arange(len(vertices)))
    return vertices[indices].reshape(-1, 3, 8), primitive['material']


def add_surface(library, name, source, vertices, material, operation):
    """Append derived meshes; never change the source catalog used by editor saves."""
    vertices = np.asarray(vertices, dtype=float).reshape(-1, 8).copy()
    assert len(vertices) and np.isfinite(vertices).all()
    origin = (vertices[:, :3].min(axis=0) + vertices[:, :3].max(axis=0)) / 2
    origin[1] = vertices[:, 1].min()
    vertices[:, :3] -= origin
    vertices = vertices.astype('<f4')
    operation['origin'] = origin.tolist()
    attrs = {}
    for key, values, kind in [('POSITION', vertices[:, :3], 'VEC3'),
                              ('NORMAL', vertices[:, 3:6], 'VEC3'),
                              ('TEXCOORD_0', vertices[:, 6:], 'VEC2')]:
        values = np.ascontiguousarray(values)
        library.binary.extend(b'\0' * (-len(library.binary) % 4))
        view = len(library.gltf['bufferViews'])
        library.gltf['bufferViews'].append(dict(buffer=0, byteOffset=len(library.binary),
                                              byteLength=values.nbytes))
        library.binary.extend(values.tobytes())
        attrs[key] = len(library.gltf['accessors'])
        entry = dict(bufferView=view, componentType=5126, count=len(values), type=kind)
        if key == 'POSITION':
            entry.update(min=values.min(axis=0).tolist(), max=values.max(axis=0).tolist())
        library.gltf['accessors'].append(entry)
    mesh = len(library.gltf['meshes'])
    library.gltf['meshes'].append(dict(name=name, primitives=[dict(attributes=attrs, material=material)]))
    library.gltf['nodes'].append(dict(name=name, mesh=mesh))
    library.gltf['scenes'][0]['nodes'].append(mesh)
    original = library.assets[source]
    library.assets[name] = dict(source_pack=original['source_pack'], source_asset=original['source_asset'],
                               label=original['label'] + '_Redstone', first_mesh=mesh, mesh_count=1,
                               unlit=0, bounds=[vertices[:, :3].min(axis=0).tolist(),
                                               vertices[:, :3].max(axis=0).tolist()], derived=operation)
    return name


def place_surface(library, placement, asset):
    matrix = np.eye(4)
    matrix[:3,3] = library.assets[asset]['derived']['origin']
    placement.update(asset=asset, transform=matrix.flatten().tolist(), derived=True)
    placement.pop('composition_transform', None)


def clip_floor(vertices, limits):
    result = []
    for triangle in vertices:
        polygon = list(triangle)
        for axis, edge, sign in [(0, limits[0], 1), (0, limits[2], -1),
                                 (2, limits[1], 1), (2, limits[3], -1)]:
            clipped = []
            for a, b in zip(polygon, polygon[1:] + polygon[:1]):
                da, db = (a[axis] - edge) * sign, (b[axis] - edge) * sign
                if da >= 0:
                    clipped.append(a)
                if (da >= 0) != (db >= 0):
                    clipped.append(a + (b - a) * da / (da - db))
            polygon = clipped
        for n in range(1, len(polygon) - 1):
            face = np.array([polygon[0], polygon[n], polygon[n+1]])
            if np.linalg.norm(np.cross(face[1, :3] - face[0, :3], face[2, :3] - face[0, :3])) > 1e-9:
                face[:, 3:6] /= np.linalg.norm(face[:, 3:6], axis=1)[:, None]
                result.extend(face)
    return result


class Ground:
    def __init__(self, faces):
        self.faces = np.asarray(faces)[:, :, :3]
        self.low, self.high = self.faces.min(axis=1), self.faces.max(axis=1)

    def height(self, x, z):
        faces = self.faces[(self.low[:, 0] <= x + 1e-6) & (self.high[:, 0] >= x - 1e-6) &
                           (self.low[:, 2] <= z + 1e-6) & (self.high[:, 2] >= z - 1e-6)]
        a, b, c = faces[:, 0], faces[:, 1], faces[:, 2]
        denom = (b[:, 2]-c[:, 2])*(a[:, 0]-c[:, 0]) + (c[:, 0]-b[:, 0])*(a[:, 2]-c[:, 2])
        valid = np.abs(denom) > 1e-9
        a, b, c, denom = a[valid], b[valid], c[valid], denom[valid]
        u = ((b[:, 2]-c[:, 2])*(x-c[:, 0]) + (c[:, 0]-b[:, 0])*(z-c[:, 2])) / denom
        v = ((c[:, 2]-a[:, 2])*(x-c[:, 0]) + (a[:, 0]-c[:, 0])*(z-c[:, 2])) / denom
        inside = (u >= -1e-6) & (v >= -1e-6) & (u+v <= 1.000001)
        if not inside.any():
            raise ValueError(f'No ground beneath authored frontage at {x}, {z}')
        return float((u*a[:, 1] + v*b[:, 1] + (1-u-v)*c[:, 1])[inside].max())


def surface_grid(rows, uv):
    faces = []
    for a, b in zip(rows, rows[1:]):
        for n in range(len(a)-1):
            for tri in ([a[n], b[n], a[n+1]], [a[n+1], b[n], b[n+1]]):
                tri = np.array(tri)
                normal = np.cross(tri[1]-tri[0], tri[2]-tri[0])
                if normal[1] < 0:
                    tri = tri[::-1]
                    normal = -normal
                normal /= np.linalg.norm(normal)
                faces.extend(np.c_[tri, np.tile(normal, (3,1)), np.tile(uv, (3,1))])
    return faces


def fit_frontage(library, placements, story):
    settings = story['ground_fit']
    limits = settings['fort_floor_bounds']
    # Remove only the redundant strip across the apron, preserving the interior roads.
    placements[:] = [p for p in placements if p['object'] != settings['replaced_gate_road']]
    ground_faces = []
    for p in placements:
        asset = library.assets[p['asset']]
        if 'Ground' not in asset['label'] and 'Cliff' not in asset['label']:
            continue
        faces, material = triangles(library, p)
        if p['source_pack'] == 'frontier' and p['section'] == 'fort' and 'Ground' in asset['label']:
            old = deepcopy(p)
            clipped = clip_floor(faces, limits)
            name = 'redstone_floor_' + p['source_object'].split(':')[0]
            asset_name = add_surface(library, name, p['asset'], clipped, material,
                                     dict(kind='clip_floor', original=old, limits=limits))
            place_surface(library, p, asset_name)
            faces, _ = triangles(library, p)
        ground_faces.extend(faces)
    ground = Ground(ground_faces)
    source = next(p for p in placements if p['source_pack'] == 'town' and
                  library.assets[p['asset']]['label'].startswith('SM_Env_Sand_Ground_'))
    source_faces, ground_material = triangles(library, source)
    uv = source_faces[0,0,6:]
    # Bury the palisade feet in a narrow earth bank. Its outer edge meets the
    # canyon, rather than exposing the vertical edge of a broad rectangular slab.
    bank = settings['wall_bank']
    left, back, right, front = limits
    outside = bank['width']
    rectangles = [(left-outside, front, right+outside, front+outside),
                  (left-outside, back-outside, right+outside, back),
                  (left-outside, back, left, front), (right, back, right+outside, front)]
    bank_faces = []
    for x0,z0,x1,z1 in rectangles:
        rows = []
        for z in np.linspace(z0,z1,math.ceil((z1-z0)/.4)+1):
            row = []
            for x in np.linspace(x0,x1,math.ceil((x1-x0)/.4)+1):
                base = ground.height(x,z)
                target = ground.height(np.clip(x,left+.001,right-.001),
                                       np.clip(z,back+.001,front-.001))
                distance = max(left-x,x-right,back-z,z-front,0)
                weight = 1-np.clip((distance-bank['plateau'])/(outside-bank['plateau']),0,1)
                weight = weight*weight*(3-2*weight)
                row.append([x,max(base,base+(target-base)*weight)+.005,z])
            rows.append(row)
        bank_faces.extend(surface_grid(rows,uv))
    asset = add_surface(library, 'redstone_wall_bank', source['asset'], bank_faces, ground_material,
                        dict(kind='wall_bank', settings=bank, limits=limits))
    placements.append(dict(asset=asset, object='redstone-wall-bank', transform=np.eye(4).flatten().tolist(),
                           source_pack=source['source_pack'], source_object=source['source_object'],
                           section='fort-approach', derived=True))
    place_surface(library, placements[-1], asset)
    ground_faces.extend(triangles(library, placements[-1])[0])
    ground = Ground(ground_faces)

    # A shallow graded entrance joins the canyon floor to the raised courtyard.
    ramp = settings['gate_ramp']
    cx, start, end, half = ramp['center_x'], ramp['start_z'], ramp['end_z'], ramp['half_width']
    target = ground.height(cx, end)
    rows = []
    for z in np.linspace(start, end, math.ceil(abs(end-start)/.25)+1):
        row = []
        t = np.clip((start-z)/(start-end), 0, 1)
        along = t*t*(3-2*t)
        for x in np.linspace(cx-half, cx+half, math.ceil(half*2/.25)+1):
            edge = np.clip((half-abs(x-cx))/.8, 0, 1)
            edge = edge*edge*(3-2*edge)
            base = ground.height(x, z)
            row.append([x, max(base, base+(target-base)*along*edge)+.008, z])
        rows.append(row)
    faces = surface_grid(rows, uv)
    asset = add_surface(library, 'redstone_gate_grade', source['asset'], faces, ground_material,
                        dict(kind='gate_grade', settings=ramp))
    placements.append(dict(asset=asset, object='redstone-gate-grade', transform=np.eye(4).flatten().tolist(),
                           source_pack=source['source_pack'], source_object=source['source_object'],
                           section='fort-approach', derived=True))
    place_surface(library, placements[-1], asset)
    ground_faces.extend(triangles(library, placements[-1])[0])
    ground = Ground(ground_faces)
    # Ground the exterior furniture after shaping both banks and the entrance.
    for prop in story['props']:
        if prop['section'] not in ('fort-frontage', 'road-shoulders'):
            continue
        x, y, z = prop['position']
        floor = ground.height(x,z)
        for p in placements:
            if p['object'].startswith('story-' + prop['id'] + ':'):
                p['transform'][7] += floor-y
                p['ground_offset_y'] = floor-y
        prop['position'][1] = floor
    # Include the wagon track and interior road surfaces where the paths join them.
    for p in placements:
        if library.assets[p['asset']]['label'] == 'SM_Env_Road_Straight_01':
            ground_faces.extend(triangles(library, p)[0])
    ground = Ground(ground_faces)
    for path in settings['paths']:
        p = next(p for p in placements if p['object'] == path['object'])
        old = deepcopy(p)
        original, material = triangles(library, p)
        rows = []
        points = np.array(path['points'], dtype=float)
        for segment, (a,b) in enumerate(zip(points, points[1:])):
            length = np.linalg.norm(b-a)
            side = np.array([-(b-a)[1], (b-a)[0]]) / length
            count = math.ceil(length/.25)
            for n in range(count + (segment == len(points)-2)):
                t = n/count
                center = a+(b-a)*t
                # A small irregular edge, not separate raised stones or road blocks.
                width = path['width']/2 + .07*math.sin(center[1]*2.3+center[0])
                if path.get('taper_end') and segment == len(points)-2:
                    width *= .2 + .8*min(1,(1-t)*length/.8)
                row = []
                for cross in np.linspace(-1, 1, 9):
                    x,z = center+side*cross*width
                    row.append([x, ground.height(x,z)+.018, z])
                rows.append(row)
        faces = surface_grid(rows, original[0,0,6:])
        asset_name = add_surface(library, 'redstone_path_' + path['id'], p['asset'], faces, material,
                                dict(kind='ground_path', original=old, settings=path))
        place_surface(library, p, asset_name)
