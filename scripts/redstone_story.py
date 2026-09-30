"""Compose the first physical story hub without resizing its restored terrain."""
import json
import math
from pathlib import Path

import numpy as np


def dress_story(town, frontier, library, placements, motion):
    layout = json.loads(Path(__file__).with_name('redstone_story_layout.json').read_text())
    packs = {p.name: p for p in (town, frontier)}
    # Preserve the editor changes in the approved, restored map (5baadb7).
    removed = {'town-300634513:1895439576520662', 'town-914544425:1895439576520662',
               'town-1720565495:1445815111663670'}
    placements[:] = [p for p in placements if p['object'] not in removed]
    for p in placements:
        if p['object'] == 'frontier-1795388179:1019634710757188':
            p['transform'][7] -= .5
            p['editor_offset_y'] = -.5

    additions = []
    for prop in layout['props']:
        pack = packs[prop['pack']]
        group = pack.groups[prop['source_group']] if 'source_group' in prop else next(
            g for g in pack.groups.values() if Path(g[0]['prefab']).stem == prop['prefab'])
        root = next((p for p in group if p['name'].split(' (')[0] == prop['prefab']), group[0])
        inverse = np.linalg.inv(np.array(root['transform']).reshape(4, 4))
        angle = math.radians(prop['yaw'])
        matrix = np.array([[math.cos(angle),0,math.sin(angle),0], [0,1,0,0],
                           [-math.sin(angle),0,math.cos(angle),0], [0,0,0,1.]])
        scale = prop['scale'] if isinstance(prop['scale'], list) else [prop['scale']] * 3
        matrix = matrix @ np.diag([*scale, 1])
        transform = matrix @ inverse
        floor = float('inf')
        for original in group:
            bounds = pack.manifest['assets'][original['asset']]['bounds']
            local = transform @ np.array(original['transform']).reshape(4, 4)
            for x in (bounds[0][0], bounds[1][0]):
                for y in (bounds[0][1], bounds[1][1]):
                    for z in (bounds[0][2], bounds[1][2]):
                        floor = min(floor, (local @ [x,y,z,1])[1])
        transform[:3,3] += np.array(prop['position']) - [0,floor,0]
        for original in group:
            additions.append(dict(asset=library.asset(pack, original['asset']),
                object='story-' + prop['id'] + ':' + original['object'].split(':')[-1],
                transform=(transform @ np.array(original['transform']).reshape(4,4)).flatten().tolist(),
                source_pack=pack.name, source_object=original['object'], section=prop['section'],
                composition_transform=transform.flatten().tolist()))

    # Clear only loose canyon clutter close to new camp furniture; preserve every
    # cliff, terrain patch, original settlement building and railway transform.
    source = {p['object']: p for p in town.manifest['placements']}
    clear = []
    for p in placements:
        if p['source_pack'] != 'town':
            continue
        original = source[p['source_object']]
        stem = Path(original['prefab']).stem
        if any(s in stem for s in ('Rock', 'Grass', 'Cactus', 'Bush', 'Dead_Tree', 'DustPile')):
            x,z = p['transform'][3],p['transform'][11]
            if any(abs(x-a['position'][0]) < 4 and abs(z-a['position'][2]) < 4
                   for a in layout['props']):
                clear.append(p['object'])
    placements[:] = [p for p in placements if p['object'] not in clear] + additions
    motion['paths'][0]['speed'] = 0
    layout['preserved_editor_removals'] = sorted(removed)
    layout['cleared_clutter'] = clear
    return layout


def character_lines(characters):
    for c in characters:
        values = [c['id'], c['model'], *c['position'], c['yaw'], c['scale'], c['speed'],
                  c['dwell'], int(c['loop']), len(c['stops'])]
        values += [v for stop in c['stops'] for v in stop]
        yield 'character ' + ' '.join(map(str, values))
