"""Assemble the fixed Redstone Canyon hub from the two retained Western packs.

No Unity or Blender dependency: mesh attributes, materials and embedded textures
are copied byte for byte. Run deliberately to regenerate the authored layout;
normal game/editor builds use its checked-in runtime files.
"""
import argparse
from collections import defaultdict
from copy import deepcopy
import hashlib
import json
from pathlib import Path
import struct

import numpy as np

from bake_navigation import rebake_navigation
from town_train_motion import train_lines

ROOT = Path(__file__).resolve().parents[1]


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


class Pack:
    def __init__(self, name):
        self.name = name
        self.directory = ROOT / 'assets' / name
        self.manifest = json.loads((self.directory / 'town.manifest.json').read_text())
        self.labels = dict(line.split(maxsplit=1) for line in
                           (self.directory / 'town.labels').read_text().splitlines())
        raw = (self.directory / 'town.glb').read_bytes()
        length = struct.unpack_from('<I', raw, 12)[0]
        self.gltf = json.loads(raw[20:20 + length])
        size, kind = struct.unpack_from('<II', raw, 20 + length)
        assert kind == 0x004E4942
        self.binary = raw[28 + length:28 + length + size]
        self.unlit = {p[1]: int(p[4]) for line in
                      (self.directory / 'town.scene').read_text().splitlines()
                      if (p := line.split()) and p[0] == 'asset'}
        self.groups = defaultdict(list)
        for placement in self.manifest['placements']:
            self.groups[placement['object'].split(':')[0]].append(placement)


class Library:
    """Copy only referenced glTF resources, retaining original encoded images."""
    def __init__(self):
        self.gltf = dict(asset={'version': '2.0', 'generator': 'DeathWard authored hub composer'},
                         scene=0, scenes=[{'nodes': []}], nodes=[], meshes=[], materials=[],
                         textures=[], images=[], samplers=[], accessors=[], bufferViews=[])
        self.binary = bytearray()
        self.cache = {}
        self.assets = {}

    def resource(self, pack, kind, index):
        key = (pack.name, kind, index)
        if key in self.cache:
            return self.cache[key]
        item = deepcopy(pack.gltf[kind][index])
        if kind == 'bufferViews':
            assert item.get('buffer', 0) == 0
            start = item.get('byteOffset', 0)
            self.binary.extend(b'\0' * (-len(self.binary) % 4))
            item['buffer'], item['byteOffset'] = 0, len(self.binary)
            self.binary.extend(pack.binary[start:start + item['byteLength']])
        elif kind == 'accessors':
            assert 'sparse' not in item
            item['bufferView'] = self.resource(pack, 'bufferViews', item['bufferView'])
        elif kind == 'images':
            assert 'uri' not in item
            item['bufferView'] = self.resource(pack, 'bufferViews', item['bufferView'])
        elif kind == 'textures':
            item['source'] = self.resource(pack, 'images', item['source'])
            if 'sampler' in item:
                item['sampler'] = self.resource(pack, 'samplers', item['sampler'])
        elif kind == 'materials':
            def textures(obj):
                for name, value in obj.items():
                    if isinstance(value, dict):
                        if name.endswith('Texture') and 'index' in value:
                            value['index'] = self.resource(pack, 'textures', value['index'])
                        else:
                            textures(value)
            textures(item)
            item['name'] = pack.name + '/' + item.get('name', str(index))
        elif kind == 'meshes':
            assert len(item['primitives']) == 1
            for primitive in item['primitives']:
                assert 'targets' not in primitive
                primitive['attributes'] = {name: self.resource(pack, 'accessors', value)
                                           for name, value in primitive['attributes'].items()}
                if 'indices' in primitive:
                    primitive['indices'] = self.resource(pack, 'accessors', primitive['indices'])
                if 'material' in primitive:
                    primitive['material'] = self.resource(pack, 'materials', primitive['material'])
        result = len(self.gltf[kind])
        self.gltf[kind].append(item)
        self.cache[key] = result
        return result

    def asset(self, pack, key):
        name = pack.name + '_' + key
        if name in self.assets:
            return name
        original = pack.manifest['assets'][key]
        first = len(self.gltf['meshes'])
        for index in range(original['first_mesh'], original['first_mesh'] + original['mesh_count']):
            node = next(n for n in pack.gltf['nodes'] if n.get('mesh') == index)
            assert set(node) <= {'mesh', 'name'}
            mesh = self.resource(pack, 'meshes', index)
            assert mesh == len(self.gltf['nodes'])
            self.gltf['scenes'][0]['nodes'].append(mesh)
            self.gltf['nodes'].append(dict(mesh=mesh, name=name + '_' + str(index)))
        self.assets[name] = dict(source_pack=pack.name, source_asset=key, label=pack.labels[key],
                                 first_mesh=first, mesh_count=original['mesh_count'],
                                 unlit=pack.unlit[key], bounds=original['bounds'])
        return name

    def write(self, path):
        self.binary.extend(b'\0' * (-len(self.binary) % 4))
        self.gltf['buffers'] = [{'byteLength': len(self.binary)}]
        self.gltf['extensionsUsed'] = sorted({name for m in self.gltf['materials']
                                               for name in m.get('extensions', {})})
        encoded = json.dumps(self.gltf, separators=(',', ':')).encode()
        encoded += b' ' * (-len(encoded) % 4)
        path.write_bytes(struct.pack('<III', 0x46546C67, 2, 28 + len(encoded) + len(self.binary)) +
                         struct.pack('<II', len(encoded), 0x4E4F534A) + encoded +
                         struct.pack('<II', len(self.binary), 0x004E4942) + self.binary)


def assemble(output):
    town, frontier = Pack('town'), Pack('frontier')
    library, placements = Library(), []

    def place(pack, original, transform=None, section='canyon'):
        asset = library.asset(pack, original['asset'])
        matrix = np.array(original['transform']).reshape(4, 4)
        if transform is not None:
            matrix = transform @ matrix
        placements.append(dict(asset=asset, object=pack.name + '-' + original['object'],
                               transform=matrix.flatten().tolist(), source_pack=pack.name,
                               source_object=original['object'], section=section))

    # Preserve the proven terrain and exact rail centerline. One four-vehicle
    # convoy runs continuously; every station/platform/town-building is omitted.
    motion = deepcopy(town.manifest['train_motion'])
    motion['paths'][0].update(id='redstone-rail', dwell=0)
    motion['groups'] = [g for g in motion['groups'] if g['offset'] > 300]
    vehicles = {g['id'] for g in motion['groups']}
    for g in motion['groups']:
        g['path'] = 'redstone-rail'
    motion['members'] = {'town-' + key: value for key, value in motion['members'].items()
                         if value[0] in vehicles}
    retained = set()
    for prefix, group in town.groups.items():
        stem = Path(group[0]['prefab']).stem
        if stem.startswith('SM_Veh_Train_'):
            keep = 'vehicle-' + prefix in vehicles
        else:
            keep = stem.startswith('SM_Env_') or stem in ('SM_Prop_Tumbleweed_01', 'SM_Prop_Bush_01')
        if not keep:
            continue
        # Keep the terrain, but clear loose vegetation/rocks where the fort and
        # caravan are placed. Large surrounding canyon formations stay intact.
        x, z = group[0]['transform'][3], group[0]['transform'][11]
        settlement = -39 < x < 26 and -67 < z < -7
        loose = any(word in stem for word in ('Rock', 'Grass', 'Cactus', 'Bush', 'Dead_Tree', 'CampFire'))
        if settlement and loose:
            continue
        for p in group:
            place(town, p)
            retained.add(p['object'])

    # Complete source prefab groups retain doors, glass, wagon wheels and props.
    # The fortified compound and the covered-wagon settler camp remain neighbors.
    offset = np.eye(4)
    offset[:3, 3] = [31.5, 0, -115]
    for group in frontier.groups.values():
        in_fort = any(-50.5 <= p['transform'][3] <= -9.5 and
                      73.5 <= p['transform'][11] <= 104.5 for p in group)
        in_camp = any(-65 <= p['transform'][3] <= -45 and
                      55 <= p['transform'][11] < 73.5 for p in group)
        if not (in_fort or in_camp):
            continue
        for p in group:
            place(frontier, p, offset, 'fort' if in_fort else 'settler-camp')

    output.mkdir(parents=True, exist_ok=True)
    library.write(output / 'town.glb')
    asset_indices = {key: i for i, key in enumerate(library.assets)}
    lines = ['DEATHWARD_TOWN 5']
    for key, asset in library.assets.items():
        fields = [key, asset['first_mesh'], asset['mesh_count'], asset['unlit']]
        fields += [v for row in asset['bounds'] for v in row]
        lines.append('asset ' + ' '.join(map(str, fields)))
    for p in placements:
        lines.append('instance ' + ' '.join(map(str, [asset_indices[p['asset']], p['object'], *p['transform']])))
    object_motion = {}
    for key, values in town.manifest['object_motion'].items():
        if key in retained:
            object_motion['town-' + key] = values
            lines.append('motion town-' + key + ' ' + ' '.join(map(str, values)))
    lines.extend(train_lines(motion['paths'], motion['groups'], motion['members']))
    # Retain the canyon sunlight, without orphaned lamps from removed buildings.
    lines.extend(line for line in (town.directory / 'town.scene').read_text().splitlines()
                 if line.startswith('light 1 '))
    (output / 'town.scene').write_text('\n'.join(lines) + '\n')
    (output / 'town.labels').write_text(''.join(f'{key} {a["label"]}\n' for key, a in library.assets.items()))

    # A valid initial map supplies bounds/markers to the shared geometry baker.
    width = depth = 1200
    spawn, mission = [-21, 0, -46], [4, 0, -50]
    heights = np.zeros(width * depth, dtype='<f4')
    (output / 'town.nav').write_bytes(b'DWTNAV03' + struct.pack('<II9f', width, depth,
        -120, -90, .2, *spawn, *mission) + heights.tobytes())
    manifest = dict(format=1, kind='authored-composition', title='Redstone Canyon',
                    description='Fixed canyon hub with a running train, Frontier fort and covered-wagon settler camp; no station.',
                    source_packs={p.name: {name: sha(p.directory / name)
                        for name in ('town.glb', 'town.manifest.json', 'town.labels')}
                        for p in (town, frontier)},
                    assets=library.assets, placements=placements, train_motion=motion,
                    object_motion=object_motion, navigation={}, output_sha256={})
    (output / 'town.manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')
    rebake_navigation(output, ROOT / 'build/deathward_bake_navigation')
    manifest = json.loads((output / 'town.manifest.json').read_text())
    manifest['output_sha256'] = {name: sha(output / name) for name in
                                ('town.glb', 'town.scene', 'town.labels', 'town.nav')}
    (output / 'town.manifest.json').write_text(json.dumps(manifest, indent=2) + '\n')
    print(f'Created {len(placements)} placements, {len(library.assets)} assets, '
          f'{len(library.gltf["images"])} original textures in {output}')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, default=ROOT / 'assets/redstone')
    assemble(parser.parse_args().output.resolve())
