"""Retain original door/glass child names, so copied buildings share entrance behavior."""
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def update(pack):
    path = pack / 'town.manifest.json'
    manifest = json.loads(path.read_text())
    labels = dict(line.split(maxsplit=1) for line in (pack / 'town.labels').read_text().splitlines())
    changes = 0
    for placement in manifest['placements']:
        name = placement['name'].split(' (')[0]
        if name.startswith(('SM_Bld_', 'SM_Building_')):
            key = placement['asset']
            if labels[key] != name:
                labels[key] = name
                changes += 1
    text = ''.join(f'{key} {value}\n' for key, value in labels.items())
    (pack / 'town.labels').write_text(text)
    manifest['output_sha256']['town.labels'] = hashlib.sha256(text.encode()).hexdigest()
    path.write_text(json.dumps(manifest, indent=2)+'\n')
    print(pack.name, changes, 'building child labels updated')


if __name__ == '__main__':
    for name in ['town', 'frontier']:
        update(ROOT / 'assets' / name)
