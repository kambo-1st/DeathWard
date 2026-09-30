"""Continuous, feathered dirt wear over Redstone's existing canyon and fort ground."""
from copy import deepcopy
import math

import numpy as np

from redstone_ground import Ground, add_surface, junction_colors, noise, place_surface, triangles


def smooth(value):
    value = np.clip(value,0,1)
    return value*value*(3-2*value)


def curved_route(points):
    """Round the joins between imported road centers without rerouting the road."""
    points = np.asarray(points,dtype=float)
    result = []
    for n,(a,b) in enumerate(zip(points,points[1:])):
        before,after = points[max(0,n-1)],points[min(len(points)-1,n+2)]
        tangent_a, tangent_b = (b-before)/2,(after-a)/2
        t = np.linspace(0,1,max(2,math.ceil(np.linalg.norm(b-a)/.8)),endpoint=False)[:,None]
        result.extend((2*t**3-3*t*t+1)*a+(t**3-2*t*t+t)*tangent_a+
                      (-2*t**3+3*t*t)*b+(t**3-t*t)*tangent_b)
    return np.vstack([result,points[-1]])


def project(points, route):
    nearest = np.full(len(points),np.inf)
    across, along = np.zeros(len(points)), np.zeros(len(points))
    traveled = 0
    for a,b in zip(route,route[1:]):
        dx,dz = b-a
        length = math.hypot(dx,dz)
        relative = points-a
        t = np.clip((relative[:,0]*dx+relative[:,1]*dz)/length**2,0,1)
        d2 = (relative[:,0]-t*dx)**2+(relative[:,1]-t*dz)**2
        use = d2 < nearest
        nearest[use] = d2[use]
        across[use] = ((-relative[:,0]*dz+relative[:,1]*dx)/length)[use]
        along[use] = traveled+t[use]*length
        traveled += length
    return np.sqrt(nearest),across,along,traveled


def road_colors(points, routes, settings, gate, junction, dirt):
    x,z = points.T
    seed = dirt['seed']
    opacity, ruts = np.zeros(len(points)), np.zeros(len(points))
    for number,route in enumerate(routes):
        distance,across,along,length = project(points,route['curve'])
        half = route['width']/2
        feather = settings['feather'] if route['wagon'] else settings['path_feather']
        rough = .13*noise(along*.26,across*.8,seed+number)+.05*noise(along*1.7,across,seed+4)
        wander = .08*noise(along*.12,np.zeros_like(along),seed+6)
        # Round and fade the ends; vary the margins without widening the road
        # into the clear approaches reserved for furniture and residents.
        edge = smooth((half+feather*.5+rough-distance)/feather)
        edge *= smooth(along/route['end_fade'])*smooth((length-along)/route['end_fade'])
        opacity = np.maximum(opacity,edge)
        if route['wagon']:
            for offset,weight in [(0,1),(-.23,.45),(.29,.35)]:
                wear = np.exp(-((np.abs(across-wander-offset)-.62)/.16)**2)
                broken = .65+.35*noise(along*.6,across*.8,seed+7)
                ruts = np.maximum(ruts,wear*broken*edge*weight)
        else:
            ruts = np.maximum(ruts,.55*np.exp(-((across-wander)/.22)**2)*edge)
    tone = np.clip(.99+.027*noise(x*.55,z*.65,seed+14)+
                   .012*noise(x*2.6,z*2.6,seed+15)-.075*ruts,0,1)
    colors = np.c_[tone,tone,tone,opacity]
    # Composite the approved fork into the same mesh. One surface avoids
    # stacked transparent patches, double-darkening and depth fighting at joins.
    x0,z0,x1,z1 = junction['bounds']
    inside = (x >= x0) & (x <= x1) & (z >= z0) & (z <= z1)
    fork = np.zeros((len(points),4))
    if inside.any():
        fork[inside] = junction_colors(np.c_[x[inside],np.zeros(inside.sum()),z[inside]],gate,junction,dirt)
    remaining = opacity*(1-fork[:,3])
    alpha = fork[:,3]+remaining
    colors[:,:3] = (fork[:,:3]*fork[:,3,None]+colors[:,:3]*remaining[:,None])/np.maximum(alpha[:,None],1e-8)
    colors[:,3] = alpha
    return colors


def ground_grid(ground, xs, zs):
    """Rasterize soil heights and face normals, without inventing normals across height jumps."""
    heights = np.full((len(zs),len(xs)),-np.inf)
    normals = np.zeros((*heights.shape,3))
    normals[:,:,1] = 1
    for face,low,high in zip(ground.faces,ground.low,ground.high):
        ix0,ix1 = np.searchsorted(xs,[low[0]-1e-6,high[0]+1e-6])
        iz0,iz1 = np.searchsorted(zs,[low[2]-1e-6,high[2]+1e-6])
        if ix0 == ix1 or iz0 == iz1:
            continue
        a,b,c = face
        denom = (b[2]-c[2])*(a[0]-c[0])+(c[0]-b[0])*(a[2]-c[2])
        if abs(denom) < 1e-9:
            continue
        x,z = np.meshgrid(xs[ix0:ix1],zs[iz0:iz1])
        u = ((b[2]-c[2])*(x-c[0])+(c[0]-b[0])*(z-c[2]))/denom
        v = ((c[2]-a[2])*(x-c[0])+(a[0]-c[0])*(z-c[2]))/denom
        inside = (u >= -1e-6) & (v >= -1e-6) & (u+v <= 1.000001)
        target = heights[iz0:iz1,ix0:ix1]
        h = np.where(inside,u*a[1]+v*b[1]+(1-u-v)*c[1],-np.inf)
        normal = np.cross(b-a,c-a)
        normal *= (1 if normal[1] >= 0 else -1)/np.linalg.norm(normal)
        normals[iz0:iz1,ix0:ix1][h > target] = normal
        np.maximum(target,h,out=target)
    return heights,normals


def ground_samples(ground, points):
    order = np.argsort(points[:,0])
    ordered = points[order]
    heights = np.full(len(points),-np.inf)
    for face,low,high in zip(ground.faces,ground.low,ground.high):
        first,last = np.searchsorted(ordered[:,0],[low[0]-1e-6,high[0]+1e-6])
        candidates = order[first:last]
        candidates = candidates[(points[candidates,1] >= low[2]-1e-6) &
                                (points[candidates,1] <= high[2]+1e-6)]
        if not len(candidates):
            continue
        a,b,c = face
        denom = (b[2]-c[2])*(a[0]-c[0])+(c[0]-b[0])*(a[2]-c[2])
        if abs(denom) < 1e-9:
            continue
        x,z = points[candidates].T
        u = ((b[2]-c[2])*(x-c[0])+(c[0]-b[0])*(z-c[2]))/denom
        v = ((c[2]-a[2])*(x-c[0])+(a[0]-c[0])*(z-c[2]))/denom
        inside = (u >= -1e-6) & (v >= -1e-6) & (u+v <= 1.000001)
        heights[candidates] = np.maximum(heights[candidates],
            np.where(inside,u*a[1]+v*b[1]+(1-u-v)*c[1],-np.inf))
    return heights


def fit_creases(ground, vertices, colors):
    """Refine only triangles crossing terrain creases, avoiding buried dirt or floating plates."""
    pending = np.c_[vertices,colors].reshape(-1,3,12)
    fitted = []
    for level in range(5):
        a,b,c = pending[:,0],pending[:,1],pending[:,2]
        ab,bc,ca = (a+b)/2,(b+c)/2,(c+a)/2
        probes = np.stack([ab,bc,ca,(a+b+c)/3],axis=1)
        heights = ground_samples(ground,probes[:,:,[0,2]].reshape(-1,2)).reshape(-1,4)
        good = np.all(abs(probes[:,:,1]-heights-.018) < .006,axis=1)
        fitted.extend(pending[good])
        if good.all() or level == 4:
            break  # Remaining height steps have no continuous soil surface.
        probes[:,:3,1] = heights[:,:3]+.018
        ab,bc,ca = (probes[~good,n] for n in range(3))
        a,b,c = (pending[~good,n] for n in range(3))
        pending = np.stack([a,ab,ca,ab,b,bc,ca,bc,c,ab,bc,ca],axis=1).reshape(-1,3,12)
    result = np.asarray(fitted).reshape(-1,12)
    result[:,3:6] /= np.linalg.norm(result[:,3:6],axis=1)[:,None]
    return result[:,:8],result[:,8:]


def fit_roads(library, placements, story):
    settings, dirt = story['road_surface'],story['ground_fit']['dirt']
    old_roads = [p for p in placements if 'Road' in library.assets[p['asset']]['label']]
    main = [p for p in old_roads if library.assets[p['asset']]['label'] == 'SM_Env_Road_Straight_01'
            and p['object'] not in story['roads']['fort_branch']]
    centers = []
    for p in main:
        bounds = np.array(library.assets[p['asset']]['bounds'])
        center = bounds.mean(axis=0)
        ends = np.tile(center,(3,1))
        ends[0,0],ends[2,0] = bounds[:,0]
        points = (np.c_[ends,np.ones(3)] @ np.array(p['transform']).reshape(4,4).T)[:,[0,2]]
        centers.append(points[np.argsort(points[:,0])])
    centers.sort(key=lambda points: points[1,0])
    main_points = [centers[0][0],*[p[1] for p in centers],centers[-1][2]]
    routes = [dict(id='wagon-road',width=story['roads']['wagon_width'],wagon=True,
                   end_fade=2,points=np.asarray(main_points).tolist()),*deepcopy(settings['routes'])]
    for route in routes:
        route['curve'] = curved_route(route['points'])

    # Dirt belongs on soil, including the authored fort banks and grade. Rocks
    # cover that surface; projecting onto their silhouettes makes sawtooth
    # triangles and turns otherwise flat road normals toward the cliff wall.
    ground = Ground([face for p in placements if 'Ground' in library.assets[p['asset']]['label']
                     for face in triangles(library,p)[0]])
    rocks = Ground([face for p in placements if 'Cliff' in library.assets[p['asset']]['label']
                    for face in triangles(library,p)[0]])
    source = main[0]
    road_faces, _ = triangles(library,source)
    uv = road_faces[0,0,6:]
    fork_asset = library.assets['redstone_gate_junction']
    material = library.gltf['meshes'][fork_asset['first_mesh']]['primitives'][0]['material']
    gate = next(p for p in story['ground_fit']['paths'] if p['id'] == 'gate')
    junction = story['ground_fit']['junction']
    # Original meshes remain in the catalog for saved edits. Only the current
    # authored placements are replaced by four adjoining, separately editable regions.
    placements[:] = [p for p in placements if p not in old_roads]
    step = settings['sample_step']
    halo = 6  # One neighbor for steps, three cells of margin, then a two-cell blur.
    for region in settings['regions']:
        x0,z0,x1,z1 = region['bounds']
        # Integer global-grid indices ensure identical boundary vertices, colors
        # and normals even when neighboring regions are exported independently.
        xs = np.arange(round(x0/step)-halo,round(x1/step)+halo+1)*step
        zs = np.arange(round(z0/step)-halo,round(z1/step)+halo+1)*step
        heights,soil_normals = ground_grid(ground,xs,zs)
        x,z = np.meshgrid(xs[halo:-halo],zs[halo:-halo])
        points = np.c_[x.ravel(),z.ravel()]
        colors = road_colors(points,routes,settings,gate,junction,dirt)
        h = heights[halo:-halo,halo:-halo].ravel()
        assert np.isfinite(h[colors[:,3] > .015]).all(), region['id']
        # Buried road ends must not paint the top of a mesa. Fade before steep
        # high ground, retaining the original route through the canyon floor.
        colors[:,3] *= 1-smooth((h-settings['height_fade'][0])/
                               (settings['height_fade'][1]-settings['height_fade'][0]))
        colors[~np.isfinite(h),3] = 0
        # Leave a soft margin before unsupported ground or steep soil. The
        # distant backdrop plane is not a road surface. Eroding before blurring
        # keeps the visible dirt away from grid triangles cut at those borders.
        # Fade before a rock meets the soil as well: the lifted decal must not
        # intersect its shallow lower faces or acquire a hard, serrated edge.
        rock_heights,_ = ground_grid(rocks,xs,zs)
        supported = (np.isfinite(heights) & (heights > -5) & (soil_normals[:,:,1] > .75) &
                     (rock_heights < heights-.05))
        # Adjacent overlapping terrain tiles can have a height step even when
        # both faces are shallow. Fade before that step instead of exposing the
        # sawtooth silhouette of the road triangles rejected by the fitter.
        for axis in (0,1):
            delta = np.abs(np.diff(np.where(np.isfinite(heights),heights,-1000),axis=axis))
            jumps = delta >= .18
            before,after = [slice(None),slice(None)],[slice(None),slice(None)]
            before[axis],after[axis] = slice(None,-1),slice(1,None)
            supported[tuple(before)] &= ~jumps
            supported[tuple(after)] &= ~jumps
        padded = np.pad(supported,3,mode='edge')
        margin = np.minimum.reduce([padded[dz:dz+len(zs),dx:dx+len(xs)]
                                    for dz in range(7) for dx in range(7)]).astype(float)
        kernel = np.array([1,4,6,4,1])/16
        for axis in (0,1):
            margin = np.apply_along_axis(lambda row: np.convolve(np.pad(row,2,mode='edge'),kernel,'valid'),axis,margin)
            soil_normals = np.apply_along_axis(lambda row: np.convolve(np.pad(row,2,mode='edge'),kernel,'valid'),axis,soil_normals)
        colors[:,3] *= margin[halo:-halo,halo:-halo].ravel()
        heights[~np.isfinite(heights)] = 0
        normals = soil_normals[halo:-halo,halo:-halo].reshape(-1,3)
        normals /= np.linalg.norm(normals,axis=1)[:,None]
        vertices = np.c_[points[:,0],heights[halo:-halo,halo:-halo].ravel()+.018,points[:,1],
                         normals,np.tile(uv,(len(points),1))]
        grid = np.arange(len(points)).reshape(x.shape)
        a,b,c,d = grid[:-1,:-1].ravel(),grid[1:,:-1].ravel(),grid[:-1,1:].ravel(),grid[1:,1:].ravel()
        indices = np.stack([a,b,c,c,b,d],axis=1).reshape(-1,3)
        indices = indices[colors[indices,3].max(axis=1) > .015]
        # Do not bridge a cliff edge with a long painted triangle.
        indices = indices[np.ptp(vertices[indices,1],axis=1) < .18]
        indices = indices.ravel()
        vertices,colors = fit_creases(ground,vertices[indices],colors[indices])
        name = 'redstone_road_' + region['id']
        asset = add_surface(library,name,source['asset'],vertices,material,
                            dict(kind='road_network',region=region,recipe='story.road_surface'),colors,
                            origin=region['origin'])
        library.assets[asset]['label'] = 'SM_Env_Worn_Road_' + region['id'].title()
        p = dict(asset=asset,object=name.replace('_','-'),source_pack=source['source_pack'],
                 source_object=source['source_object'],section='roads',derived=True)
        place_surface(library,p,asset)
        placements.append(p)
    # Store shared provenance once, rather than repeating the entire road
    # network's source placements and route definitions in every region asset.
    settings['source_roads'] = deepcopy(old_roads)
    settings['resolved_routes'] = [{k:v for k,v in r.items() if k != 'curve'} for r in routes]
