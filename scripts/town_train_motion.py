"""Author reusable train paths/groups from the verified Black Creek import."""
import math
from pathlib import Path


def train_motion(placements, assets):
    trains = [p for p in placements if Path(p['prefab']).stem.startswith('SM_Veh_Train_')]
    if not trains:
        return [], [], {}
    # This route belongs to the original Black Creek rail layout. Do not silently
    # attach it to another imported scene with similarly named vehicle assets.
    curves = {(round(p['transform'][3], 2), round(p['transform'][11], 2))
              for p in placements if p['name'].startswith('SM_Env_Train_Track_Curve_01')
              and not p['name'].endswith('_Dirt')}
    if curves != {(50, 18), (75, 83), (-65, 43), (-40, 108)}:
        return [], [], {}
    points = []

    def line(a, b):
        steps = math.ceil(math.dist(a, b) / 2)
        for n in range(steps):
            points.append([a[0] + (b[0]-a[0])*n/steps, 0,
                           a[1] + (b[1]-a[1])*n/steps])

    def arc(cx, cz, start):
        for n in range(90):
            angle = math.radians(start-n)
            points.append([cx+25*math.cos(angle), 0, cz+25*math.sin(angle)])

    arc(-40, 43, -90)
    line((-65, 43), (-65, 83))
    arc(-40, 83, 180)
    line((-40, 108), (50, 108))
    arc(50, 83, 90)
    line((75, 83), (75, 43))
    arc(50, 43, 0)
    line((50, 18), (-40, 18))
    paths = [dict(id='black-creek-rail', speed=3, acceleration=.8, dwell=6, points=points)]
    cumulative = [0.]
    for a, b in zip(points, points[1:]+points[:1]):
        cumulative.append(cumulative[-1]+math.dist(a, b))

    def offset(p):
        position = [p['transform'][3], 0, p['transform'][11]]
        best = (float('inf'), 0.)
        for n, (a, b) in enumerate(zip(points, points[1:]+points[:1])):
            delta = [b[k]-a[k] for k in range(3)]
            length2 = sum(d*d for d in delta)
            t = max(0., min(1., sum((position[k]-a[k])*delta[k] for k in range(3))/length2))
            distance = math.dist(position, [a[k]+delta[k]*t for k in range(3)])
            best = min(best, (distance, cumulative[n]+t*math.sqrt(length2)))
        assert best[0] < .001, 'Vehicle root is not on the authored rails'
        return best[1]

    groups, members = [], {}
    for prefix in sorted({p['object'].split(':')[0] for p in trains}):
        parts = [p for p in trains if p['object'].split(':')[0] == prefix]
        stem = Path(parts[0]['prefab']).stem
        root = next(p for p in parts if p['name'].split(' (')[0] == stem)
        group = 'vehicle-' + prefix
        wheelbase = 8.05 if stem == 'SM_Veh_Train_01' else (12 if 'Carriage' in stem else 5)
        groups.append(dict(id=group, path=paths[0]['id'], offset=offset(root), wheelbase=wheelbase))
        for p in parts:
            bounds = assets[p['asset']]['bounds']
            radius = (bounds[1][1]-bounds[0][1])*.5 if '_Wheel_' in p['name'] else 0
            # Wheels are separate meshes centered on a local X axle. The three
            # vertical 'Stick' meshes are cab levers, not wheel connecting rods.
            members[p['object']] = [group, radius]
    return paths, groups, members


def train_lines(paths, groups, members):
    lines = []
    for p in paths:
        values = [p['id'], p['speed'], p['acceleration'], p['dwell'], len(p['points'])]
        values += [v for point in p['points'] for v in point]
        lines.append('path ' + ' '.join(map(str, values)))
    for g in groups:
        lines.append('group ' + ' '.join(map(str, (g['id'], g['path'], g['offset'], g['wheelbase']))))
    for object_id, member in members.items():
        lines.append('member ' + ' '.join(map(str, [object_id, *member])))
    return lines
