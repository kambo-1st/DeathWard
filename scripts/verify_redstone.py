"""Audit the authored canyon composition, original geometry and embedded textures."""
import argparse
from copy import deepcopy
import hashlib
import json
from pathlib import Path
import struct

import numpy as np

ROOT = Path(__file__).resolve().parents[1]


def digest(data):
    return hashlib.sha256(data).hexdigest()


def glb(path):
    data = path.read_bytes()
    length = struct.unpack_from('<I', data, 12)[0]
    return json.loads(data[20:20 + length]), data[28 + length:]


def view(model, index):
    data, binary = model
    info = data['bufferViews'][index]
    start = info.get('byteOffset', 0)
    return binary[start:start + info['byteLength']]


def material(model, index):
    data, _ = model
    result = deepcopy(data['materials'][index])
    result.pop('name', None)
    def textures(obj):
        for name, value in obj.items():
            if not isinstance(value, dict):
                continue
            if name.endswith('Texture') and 'index' in value:
                texture = data['textures'][value.pop('index')]
                value['image_sha256'] = digest(view(model, data['images'][texture['source']]['bufferView']))
                value['sampler'] = data['samplers'][texture['sampler']] if 'sampler' in texture else {}
            else:
                textures(value)
    textures(result)
    return result


def verify(directory):
    manifest = json.loads((directory / 'town.manifest.json').read_text())
    assert manifest['kind'] == 'authored-composition'
    for file, expected in manifest['output_sha256'].items():
        assert digest((directory / file).read_bytes()) == expected, file
    sources, original = {}, {}
    for pack, files in manifest['source_packs'].items():
        source = ROOT / 'assets' / pack
        for file, expected in files.items():
            assert digest((source / file).read_bytes()) == expected, (pack, file)
        sources[pack] = glb(source / 'town.glb')
        original[pack] = json.loads((source / 'town.manifest.json').read_text())
    composed = glb(directory / 'town.glb')
    for asset in manifest['assets'].values():
        source = sources[asset['source_pack']]
        old = original[asset['source_pack']]['assets'][asset['source_asset']]
        assert asset['bounds'] == old['bounds'] and asset['mesh_count'] == old['mesh_count']
        for n in range(asset['mesh_count']):
            before = source[0]['meshes'][old['first_mesh'] + n]['primitives'][0]
            after = composed[0]['meshes'][asset['first_mesh'] + n]['primitives'][0]
            assert before['attributes'].keys() == after['attributes'].keys()
            indices = [(before['attributes'][key], after['attributes'][key]) for key in before['attributes']]
            if 'indices' in before:
                indices.append((before['indices'], after['indices']))
            for a, b in indices:
                first, second = deepcopy(source[0]['accessors'][a]), deepcopy(composed[0]['accessors'][b])
                assert view(source, first.pop('bufferView')) == view(composed, second.pop('bufferView'))
                assert first == second
            assert material(source, before['material']) == material(composed, after['material'])
    lookup = {pack: {p['object']: p for p in data['placements']} for pack, data in original.items()}
    offset = np.eye(4)
    offset[:3, 3] = [31.5, 0, -115]
    for p in manifest['placements']:
        old = lookup[p['source_pack']][p['source_object']]
        transform = np.array(old['transform']).reshape(4, 4)
        if 'composition_transform' in p:
            transform = np.array(p['composition_transform']).reshape(4,4) @ transform
        elif p['source_pack'] == 'frontier':
            transform = offset @ transform
        transform[1,3] += p.get('editor_offset_y', 0)
        assert np.array_equal(transform.flatten(), p['transform'])
        assert 'TrainStation' not in old['name'] and 'TrainStation' not in old['prefab']
    # Check the actual runtime catalog, including full prefab children and IDs.
    assets, instances = [], []
    for line in (directory / 'town.scene').read_text().splitlines():
        parts = line.split()
        if parts[0] == 'asset':
            assets.append(parts[1])
            expected = manifest['assets'][parts[1]]
            assert list(map(int, parts[2:5])) == [expected['first_mesh'], expected['mesh_count'], expected['unlit']]
            assert np.array_equal(np.array(parts[5:], dtype=float).reshape(2, 3), expected['bounds'])
        elif parts[0] == 'instance':
            instances.append((assets[int(parts[1])], parts[2], list(map(float, parts[3:]))))
    assert instances == [(p['asset'], p['object'], p['transform']) for p in manifest['placements']]
    assert len({p['object'] for p in manifest['placements']}) == len(instances)
    assert len(manifest['train_motion']['groups']) == 4
    assert manifest['train_motion']['paths'][0]['dwell'] == 0
    assert manifest['train_motion']['paths'][0]['speed'] == 0
    assert manifest['train_motion']['paths'][0]['points'] == original['town']['train_motion']['paths'][0]['points']
    print(f'PASS {len(instances)} authored placements, {len(assets)} original mesh assets, '
          f'{len(composed[0]["images"])} byte-identical textures/materials, source hashes and stationless railway')


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--pack', type=Path, default=ROOT / 'assets/redstone')
    verify(parser.parse_args().pack.resolve())
