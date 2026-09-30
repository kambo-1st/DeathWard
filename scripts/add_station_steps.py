"""Connect Black Creek's raised station platform using an original textured stair asset.

Original Unity placements remain unchanged. Run after a fresh import if desired.
"""
import json
from pathlib import Path
from bake_navigation import rebake_navigation

ROOT = Path(__file__).resolve().parents[1]


def main():
    pack = ROOT / 'assets/town'
    lines = (pack/'town.scene').read_text().splitlines()
    assets = [line.split()[1] for line in lines if line.startswith('asset ')]
    label = dict(line.split(maxsplit=1) for line in (pack/'town.labels').read_text().splitlines())
    asset = next(name for name in assets if label[name] == 'SM_Bld_Stairs_01')
    identity = 'station-entrance-steps'
    transform = [1,0,0,4.4, 0,.35,0,-.4, 0,0,.5,4.55, 0,0,0,1]
    lines = [line for line in lines if not (line.startswith('instance ') and line.split()[2] == identity)]
    lines.append(f'instance {assets.index(asset)} {identity} '+ ' '.join(map(str,transform)))
    (pack/'town.scene').write_text('\n'.join(lines)+'\n')
    path=pack/'town.manifest.json'
    manifest=json.loads(path.read_text())
    manifest['authored_placements']=[p for p in manifest.get('authored_placements',[]) if p['object'] != identity]
    manifest['authored_placements'].append(dict(object=identity,asset=asset,transform=transform))
    path.write_text(json.dumps(manifest,indent=2)+'\n')
    rebake_navigation(pack,ROOT/'build/deathward_bake_navigation')


if __name__ == '__main__':
    main()
