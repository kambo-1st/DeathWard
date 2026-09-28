"""Adapt opaque Unity albedos for raylib, which otherwise blends unused PNG alpha."""
import hashlib
import io
import json
from pathlib import Path
import struct
import sys
from PIL import Image

ROOT = Path(sys.argv[1]).resolve() if len(sys.argv)>1 else Path(__file__).resolve().parents[1] / 'assets/animals'


def main():
    manifest_path = ROOT / 'animals.manifest.json'
    manifest = json.loads(manifest_path.read_text())
    recipe = json.loads((ROOT / 'animals.source.json').read_text())
    for entry in recipe['animals']:
        assert entry.get('alpha_mode', 'OPAQUE') == 'OPAQUE'
        path = ROOT / (entry['id'] + '.glb')
        blob = path.read_bytes()
        size = struct.unpack_from('<I', blob, 12)[0]
        doc = json.loads(blob[20:20+size])
        binary = blob[28+size:]
        image_views = {image['bufferView'] for image in doc['images']}
        packed = bytearray()
        changed = False
        for index, view in enumerate(doc['bufferViews']):
            offset = view.get('byteOffset', 0)
            data = binary[offset:offset+view['byteLength']]
            if index in image_views:
                original = Image.open(io.BytesIO(data)).convert('RGBA')
                if original.getextrema()[-1] != (255, 255):
                    original.putalpha(255)
                    png = io.BytesIO()
                    original.save(png, format='PNG')
                    data = png.getvalue()
                    changed = True
            packed.extend(b'\0' * (-len(packed) % 4))
            view['byteOffset'], view['byteLength'] = len(packed), len(data)
            packed.extend(data)
        if changed:
            doc['buffers'][0]['byteLength'] = len(packed)
            packed.extend(b'\0' * (-len(packed) % 4))
            for material in doc['materials']:
                material['alphaMode'] = 'OPAQUE'
            encoded = json.dumps(doc, separators=(',', ':')).encode()
            encoded += b' ' * (-len(encoded) % 4)
            path.write_bytes(struct.pack('<III', 0x46546c67, 2, 28+len(encoded)+len(packed)) +
                struct.pack('<II', len(encoded), 0x4e4f534a) + encoded +
                struct.pack('<II', len(packed), 0x004e4942) + packed)
            print('Opaque RGB preserved:', entry['id'])
        record = manifest['animals'][entry['id']]
        record['alpha_mode'] = 'OPAQUE'
        record['output_sha256'] = hashlib.sha256(path.read_bytes()).hexdigest()
    manifest_path.write_text(json.dumps(manifest, indent=2)+'\n')


if __name__ == '__main__':
    main()
