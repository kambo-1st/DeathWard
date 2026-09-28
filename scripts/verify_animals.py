"""Audit retained Polyperfect sources, embedded textures, rigs and all animation clips."""
import hashlib
import io
import json
from pathlib import Path
import struct
import numpy as np
from PIL import Image

ROOT = Path(__file__).resolve().parents[1] / 'assets/animals'


def main():
    recipe = json.loads((ROOT / 'animals.source.json').read_text())
    manifest = json.loads((ROOT / 'animals.manifest.json').read_text())
    assert not manifest.get('failures'), manifest.get('failures')
    assert len(recipe['animals']) == recipe['prefab_count'] == 98
    assert len({entry['family'] for entry in recipe['animals']}) == recipe['family_count'] == 66
    assert {entry['id'] for entry in recipe['animals']} == set(manifest['animals'])
    assert {entry['id'] for entry in recipe['animals']} == {p.stem for p in ROOT.glob('*.glb')}
    assert recipe['source_sha256'] == manifest['source_sha256']
    for name, digest in manifest['source_sha256'].items():
        assert hashlib.sha256((ROOT / 'source' / name).read_bytes()).hexdigest() == digest, name
    for entry in recipe['animals']:
        name = entry['id']
        record = manifest['animals'][name]
        blob = (ROOT / (name + '.glb')).read_bytes()
        assert hashlib.sha256(blob).hexdigest() == record['output_sha256'], name
        assert struct.unpack_from('<III', blob) == (0x46546c67, 2, len(blob))
        size = struct.unpack_from('<I', blob, 12)[0]
        doc = json.loads(blob[20:20+size])
        binary = blob[28+size:]

        def view(index):
            item = doc['bufferViews'][index]
            start = item.get('byteOffset', 0)
            return binary[start:start+item['byteLength']]

        def accessor(index):
            item = doc['accessors'][index]
            count = {'SCALAR': 1, 'VEC2': 2, 'VEC3': 3, 'VEC4': 4, 'MAT4': 16}[item['type']]
            dtype = {5121: '<u1', 5123: '<u2', 5125: '<u4', 5126: '<f4'}[item['componentType']]
            data = np.frombuffer(view(item['bufferView']), dtype=dtype,
                                 count=item['count']*count, offset=item.get('byteOffset', 0))
            return data.reshape(item['count'], count)

        assert len(doc['images']) == 1 and 'uri' not in doc['buffers'][0]
        original = Image.open(ROOT / 'source' / entry['texture']).convert('RGBA')
        embedded = Image.open(io.BytesIO(view(doc['images'][0]['bufferView']))).convert('RGBA')
        assert original.size == embedded.size == tuple(record['texture_size'])
        assert original.convert('RGB').tobytes() == embedded.convert('RGB').tobytes(), (name, 'albedo RGB changed')
        assert embedded.getextrema()[-1] == (255, 255), (name, 'opaque material must ignore source alpha')
        assert all(m['pbrMetallicRoughness']['baseColorFactor'] == entry['tint'] for m in doc['materials'])
        joints = doc['skins'][0]['joints']
        assert len(joints) == record['bones'] and len(joints) <= 255
        for mesh in doc['meshes']:
            for primitive in mesh['primitives']:
                attributes = primitive['attributes']
                weights = accessor(attributes['WEIGHTS_0'])
                assert np.allclose(weights.sum(axis=1), 1, atol=.00001)
                assert accessor(attributes['JOINTS_0']).max() < len(joints)
                assert np.isfinite(accessor(attributes['POSITION'])).all()
                assert 'TEXCOORD_0' in attributes
        assert {clip['name'] for clip in doc['animations']} == set(record['clips'])
        for clip in doc['animations']:
            duration = record['clips'][clip['name']]['duration']
            for sampler in clip['samplers']:
                times = accessor(sampler['input']).ravel()
                assert len(times) >= 2 and abs(times[0]) < .00001 and abs(times[-1]-duration) < .00001
                assert np.all(np.diff(times) > 0) and np.isfinite(accessor(sampler['output'])).all()
        print(f"PASS {name}: original {original.width}px RGB/tint, opaque alpha, {len(joints)} bones, "
              f"{len(doc['animations'])} clips, normalized weights and source/output hashes")


if __name__ == '__main__':
    main()
