"""Fit Redstone's fort floor and worn approaches to the canyon terrain."""
from copy import deepcopy
import math

import numpy as np


def accessor(library, index):
    item = library.gltf['accessors'][index]
    view = library.gltf['bufferViews'][item['bufferView']]
    dtype = np.dtype({5126: '<f4', 5123: '<u2', 5125: '<u4'}[item['componentType']])
    size = {'SCALAR': 1, 'VEC2': 2, 'VEC3': 3, 'VEC4': 4}[item['type']]
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


def add_surface(library, name, source, vertices, material, operation, colors=None, origin=None):
    """Append derived meshes; never change the source catalog used by editor saves."""
    vertices = np.asarray(vertices, dtype=float).reshape(-1, 8).copy()
    assert len(vertices) and np.isfinite(vertices).all()
    if origin is None:
        origin = (vertices[:, :3].min(axis=0) + vertices[:, :3].max(axis=0)) / 2
        origin[1] = vertices[:, 1].min()
    else:
        origin = np.asarray(origin,dtype=float)
    vertices[:, :3] -= origin
    vertices = vertices.astype('<f4')
    operation['origin'] = origin.tolist()
    attrs = {}
    streams = [('POSITION', vertices[:, :3], 'VEC3'), ('NORMAL', vertices[:, 3:6], 'VEC3'),
               ('TEXCOORD_0', vertices[:, 6:], 'VEC2')]
    if colors is not None:
        colors = np.asarray(colors, dtype='<f4')
        assert colors.shape == (len(vertices),4) and np.all((colors >= 0) & (colors <= 1))
        streams.append(('COLOR_0', colors, 'VEC4'))
    for key, values, kind in streams:
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


def noise(x,y,seed):
    ix,iy = np.floor(x).astype(np.int64),np.floor(y).astype(np.int64)
    u,v = x-ix,y-iy
    u,v = u*u*(3-2*u),v*v*(3-2*v)
    def value(dx,dy):
        h = ((ix+dx)*374761393+(iy+dy)*668265263+seed*1442695041) & 0xffffffff
        h = ((h ^ (h >> 13))*1274126177) & 0xffffffff
        return ((h ^ (h >> 16)) & 0xffffff) / 0xffffff * 2-1
    return ((1-u)*value(0,0)+u*value(1,0))*(1-v) + ((1-u)*value(0,1)+u*value(1,1))*v


def dirt_colors(faces, path, style):
    """Bake soft, lengthwise soil variation without changing the walkable mesh."""
    points = np.asarray(path['points'], dtype=float)
    vertices = np.asarray(faces)[:,:3]
    along, across, nearest = np.zeros(len(vertices)), np.zeros(len(vertices)), np.full(len(vertices), np.inf)
    traveled = 0
    for a,b in zip(points,points[1:]):
        delta = b-a
        length = np.linalg.norm(delta)
        relative = vertices[:,[0,2]]-a
        t = np.clip(relative @ delta / length**2,0,1)
        distance = np.sum((relative-t[:,None]*delta)**2,axis=1)
        use = distance < nearest
        nearest[use] = distance[use]
        along[use] = traveled+t[use]*length
        across[use] = (relative @ np.array([-delta[1],delta[0]]) / length)[use]
        traveled += length

    seed = style['seed']
    broad = .65*noise(across*2.8,along*.22,seed) + .35*noise(across*1.3,along*.65,seed+1)
    grain = noise(across*8,along*2.3,seed+2)
    wander = .06*noise(np.zeros_like(along),along*.4,seed+3)
    if path['id'] == 'gate':
        wear = np.exp(-((np.abs(across-wander)-path['width']*.27)/.13)**2)
    else:
        wear = np.exp(-((across-wander)/.2)**2)
    tone = .94 + style['strength']*broad + .015*grain-style['wear']*wear
    warmth = .5+.5*noise(across*1.4,along*.32,seed+4)
    colors = np.c_[tone,tone*(1-.012*warmth),tone*(1-.025*warmth),np.ones(len(vertices))]
    colors = np.clip(colors,0,1)
    # Keep the shared palette at the junction so the path does not paint a
    # dark rectangular cap across the main road. Fade back at the courtyard join.
    blend = np.clip((along-1.9)/1.0,0,1)
    blend = blend*blend*(3-2*blend)
    if not path.get('taper_end'):
        end = np.clip((traveled-along)/.9,0,1)
        blend *= end*end*(3-2*end)
    colors[:,:3] = 1+(colors[:,:3]-1)*blend[:,None]
    return colors


def junction_surface(ground, uv, path, settings, style):
    """One feathered dirt surface, with wagon turns merging into the gate track."""
    step = settings['sample_step']
    x0, z0, x1, z1 = settings['bounds']
    rows = [[[x, ground.height(x,z)+.018, z]
             for x in np.linspace(x0,x1,math.ceil((x1-x0)/step)+1)]
            for z in np.linspace(z0,z1,math.ceil((z1-z0)/step)+1)]
    faces = np.asarray(surface_grid(rows,uv))
    # Average the ground normals across the old road shoulder. Copying each
    # source triangle's flat normal would leave a straight lighting seam even
    # where the new dirt is fully opaque. Geometry still hugs the real terrain.
    grid = np.asarray(rows)
    heights = grid[:,:,1]
    kernel = np.array([1,4,6,4,1])/16
    for axis in (0,1):
        heights = np.apply_along_axis(lambda row: np.convolve(np.pad(row,2,mode='edge'),kernel,'valid'),
                                     axis,heights)
    dz,dx = np.gradient(heights,grid[1,0,2]-grid[0,0,2],grid[0,1,0]-grid[0,0,0])
    normals = np.stack([-dx,np.ones_like(dx),-dz],axis=2)
    normals /= np.linalg.norm(normals,axis=2)[:,:,None]
    ix = np.rint((faces[:,0]-x0)/(x1-x0)*(len(grid[0])-1)).astype(int)
    iz = np.rint((faces[:,2]-z0)/(z1-z0)*(len(grid)-1)).astype(int)
    faces[:,3:6] = normals[iz,ix]
    colors = junction_colors(faces,path,settings,style)
    # Fully invisible triangles are unnecessary for rendering, picking or nav.
    keep = colors[:,3].reshape(-1,3).max(axis=1) > .015
    return faces.reshape(-1,3,8)[keep].reshape(-1,8), colors.reshape(-1,3,4)[keep].reshape(-1,4)


def junction_colors(faces, path, settings, style):
    points = faces[:,[0,2]]
    x, z = points.T
    seed = style['seed']

    def smooth(value):
        value = np.clip(value,0,1)
        return value*value*(3-2*value)

    def project(route):
        nearest = np.full(len(points),np.inf)
        across, along = np.zeros(len(points)), np.zeros(len(points))
        traveled = 0
        for a,b in zip(route,route[1:]):
            delta = b-a
            length = np.linalg.norm(delta)
            relative = points-a
            t = np.clip(relative @ delta / length**2,0,1)
            d2 = np.sum((relative-t[:,None]*delta)**2,axis=1)
            use = d2 < nearest
            nearest[use] = d2[use]
            across[use] = (relative @ np.array([-delta[1],delta[0]]) / length)[use]
            along[use] = traveled+t[use]*length
            traveled += length
        return np.sqrt(nearest), across, along, traveled

    def curve(controls):
        a,b,c,d = np.asarray(controls)
        t = np.linspace(0,1,81)[:,None]
        return (1-t)**3*a+3*(1-t)**2*t*b+3*(1-t)*t*t*c+t**3*d

    # Unequal left/right turns give a broad Y-shaped mouth. The same surface
    # continues to the courtyard, so there is no join between two road pieces.
    turns = [curve(c) for c in settings['turns']]
    spine = np.asarray(settings['spine'])
    rough = .10*noise(x*1.7,z*1.4,seed+10)+.04*noise(x*4,z*4,seed+11)
    feather = settings['feather']
    distance, across, along, length = project(spine)
    half = path['width']/2
    opacity = smooth((half+feather+rough-distance)/feather)
    opacity *= smooth(along/.7)*smooth((length-along)/.9)
    ruts = np.exp(-((np.abs(across)-half*.54)/.13)**2)*opacity
    for number,route in enumerate(turns):
        distance, across, along, length = project(route)
        progress = along/length
        width = 1.55-(1.55-half)*smooth(progress)
        end_fade = smooth(along/2.0)
        opacity = np.maximum(opacity,smooth((width+feather+rough-distance)/feather)*end_fade)
        # Different wagon lines share the road, then sweep and converge at
        # slightly different places. Keep ruts soft and broken, not drawn rails.
        for offset, weight in [(-.25,.5),(.06,1),(.33,.4)]:
            bend = offset*np.sin(progress*np.pi)
            wander = .045*noise(along*.7,np.full(len(x),number),seed+12)
            wheel = np.exp(-((np.abs(across-bend-wander)-half*.54)/.12)**2)
            broken = .65+.35*noise(along*1.2,across*.7,seed+13)
            ruts = np.maximum(ruts,wheel*weight*broken*end_fade)

    # Hooves and repeated turns also wear the space between the two wheel
    # approaches. Fill that rounded apron instead of leaving a pointed island
    # of the main road's original shoulder between the diverging tracks.
    center_x, center_z, radius_x, radius_z = settings['turning_apron']
    apron = np.sqrt(((x-center_x)/radius_x)**2+((z-center_z)/radius_z)**2)
    opacity = np.maximum(opacity,smooth((1+rough*.3-apron)/.35))

    # The source road atlas is retained. Alpha softly reveals the existing road
    # and surrounding sand; both remain visible through the worn outer margin.
    colors = dirt_colors(faces,path,style)
    junction = smooth((z+7)/3)
    mottling = .032*noise(x*.65,z*.8,seed+14)+.012*noise(x*3,z*3,seed+15)
    tone = np.clip(.99+mottling-.075*ruts,0,1)
    colors[:,:3] = colors[:,:3]*(1-junction[:,None])+tone[:,None]*junction[:,None]
    colors[:,3] = opacity
    return colors


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
    road = next(p for p in placements if library.assets[p['asset']]['label'] == 'SM_Env_Road_Straight_01')
    road_uv = triangles(library, road)[0][0,0,6:]
    for path in settings['paths']:
        p = next(p for p in placements if p['object'] == path['object'])
        old = deepcopy(p)
        _, material = triangles(library, p)
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
        faces = surface_grid(rows, road_uv)
        asset_name = add_surface(library, 'redstone_path_' + path['id'], p['asset'], faces, material,
                                dict(kind='ground_path', original=old, settings=path,
                                     dirt=settings['dirt']), dirt_colors(faces,path,settings['dirt']))
        place_surface(library, p, asset_name)

    # Preserve all earlier catalog entries (including the narrow gate path) for
    # edited saves, and append the new fork as a separately placeable asset.
    path = next(path for path in settings['paths'] if path['id'] == 'gate')
    p = next(p for p in placements if p['object'] == path['object'])
    old = deepcopy(p)
    _, material = triangles(library,p)
    blended = deepcopy(library.gltf['materials'][material])
    blended['name'] = 'Redstone feathered dirt'
    blended['alphaMode'] = 'BLEND'
    # Raylib routes translucent materials through the existing depth-tested,
    # no-depth-write pass and excludes them from the sun's shadow casters.
    blended['pbrMetallicRoughness']['baseColorFactor'][3] = 254/255
    blend_material = len(library.gltf['materials'])
    library.gltf['materials'].append(blended)
    faces, colors = junction_surface(ground,road_uv,path,settings['junction'],settings['dirt'])
    asset_name = add_surface(library,'redstone_gate_junction',p['asset'],faces,blend_material,
                            dict(kind='ground_junction',original=old,settings=settings['junction'],
                                 dirt=settings['dirt']),colors)
    library.assets[asset_name]['label'] = 'SM_Env_Road_Gate_Junction_Redstone'
    place_surface(library,p,asset_name)
