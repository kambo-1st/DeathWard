"""Audit the cowgirl's retained FBXs, portable texture, skin and three clips."""
import hashlib
import io
import json
from pathlib import Path
import struct
import numpy as np
from PIL import Image

ROOT = Path(__file__).resolve().parents[1] / 'assets/cowgirl'
manifest = json.loads((ROOT / 'cowgirl.manifest.json').read_text())
blob = (ROOT / 'cowgirl.glb').read_bytes()
assert hashlib.sha256(blob).hexdigest() == manifest['output_sha256']
for clip in manifest['clips'].values():
    assert hashlib.sha256((ROOT / clip['source']).read_bytes()).hexdigest() == clip['sha256']
size = struct.unpack_from('<I', blob, 12)[0]
doc = json.loads(blob[20:20 + size])
binary = blob[28 + size:]
def view(index):
    item = doc['bufferViews'][index]
    start = item.get('byteOffset', 0)
    return binary[start:start + item['byteLength']]
def accessor(index):
    item = doc['accessors'][index]
    count = {'SCALAR': 1, 'VEC2': 2, 'VEC3': 3, 'VEC4': 4, 'MAT4': 16}[item['type']]
    dtype = {5121: '<u1', 5123: '<u2', 5125: '<u4', 5126: '<f4'}[item['componentType']]
    return np.frombuffer(view(item['bufferView']), dtype=dtype, count=item['count'] * count,
                         offset=item.get('byteOffset', 0)).reshape(item['count'], count)
assert len(doc['images']) == 1 and 'uri' not in doc['buffers'][0]
image = Image.open(io.BytesIO(view(doc['images'][0]['bufferView']))).convert('RGBA')
assert image.size == (2048, 2048) and image.getextrema()[-1] == (255, 255)
assert len(doc['skins']) == 1 and len(doc['skins'][0]['joints']) == manifest['bones'] == 48
for mesh in doc['meshes']:
    for primitive in mesh['primitives']:
        attrs = primitive['attributes']
        assert 'TEXCOORD_0' in attrs
        assert np.allclose(accessor(attrs['WEIGHTS_0']).sum(axis=1), 1, atol=.00001)
        assert accessor(attrs['JOINTS_0']).max() < 48
        assert np.isfinite(accessor(attrs['POSITION'])).all()
assert {clip['name'] for clip in doc['animations']} == {'Idle', 'Idle2', 'Walk'}
for clip in doc['animations']:
    for sampler in clip['samplers']:
        times = accessor(sampler['input']).ravel()
        assert abs(times[0]) < .00001 and abs(times[-1] - manifest['clips'][clip['name']]['duration']) < .0001
        assert np.all(np.diff(times) > 0) and np.isfinite(accessor(sampler['output'])).all()
print('PASS cowgirl: source/output hashes, 2048px embedded texture, UVs, 48 bones, normalized weights and all clip durations')
