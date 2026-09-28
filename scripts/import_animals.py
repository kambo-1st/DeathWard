"""Collect Polyperfect FBX rigs, clips and original textures, then bake runtime GLBs."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess
import yaml

ROOT = Path(__file__).resolve().parents[1]
ANIMALS = [('horse', 'Horse', 'HorseThoroughbred', 'Horse_Brown'),
           ('hen', 'Hen', 'Hen', 'Hen'),
           ('cow', 'Cow', 'Cow_NoHorns', 'Cow_Brown'),
           ('cat', 'Cat', 'cat', 'Cat_Orange')]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', type=Path, default=ROOT/'assets/animals/source')
    parser.add_argument('--output', type=Path, default=ROOT/'assets/animals')
    parser.add_argument('--blender', default='blender')
    args = parser.parse_args()
    source, output = args.source.resolve(), args.output.resolve()
    if (source/'Low Poly Animated Animals').is_dir():
        source /= 'Low Poly Animated Animals'
    output.mkdir(parents=True, exist_ok=True)
    hashes = {}
    textures = {}
    for meta in (source/'Textures').rglob('*.meta'):
        match = re.search(r'^guid: (\w+)', meta.read_text(), re.M)
        if match: textures[match[1]] = meta.with_suffix('')

    def collect(path):
        relative = path.relative_to(source)
        target = output/'source'/relative
        target.parent.mkdir(parents=True, exist_ok=True)
        if path != target: shutil.copyfile(path, target)
        hashes[str(relative)] = hashlib.sha256(path.read_bytes()).hexdigest()
        meta = path.with_name(path.name+'.meta')
        if meta.exists():
            dest = target.with_name(target.name+'.meta')
            if meta != dest: shutil.copyfile(meta, dest)
            hashes[str(meta.relative_to(source))] = hashlib.sha256(meta.read_bytes()).hexdigest()
        return str(relative)

    animals = []
    for id_, folder, mesh, material in ANIMALS:
        mat_path = source/f'Materials/Animals/{material}.mat'
        text = re.sub(r'^%.*\n|^--- !u!\d+ &-?\d+\n', '', mat_path.read_text(), flags=re.M)
        properties = yaml.safe_load(text)['Material']['m_SavedProperties']
        env = next(e['_MainTex'] for e in properties['m_TexEnvs'] if '_MainTex' in e)
        tint = next(e['_Color'] for e in properties['m_Colors'] if '_Color' in e)
        animals.append(dict(id=id_, mesh=mesh,
            rig=collect(source/f'Meshes/Animals/{folder}/SKM_{folder}_Rig.fbx'),
            animation=collect(source/f'Meshes/Animals/{folder}/SKM_{folder}_Animations.fbx'),
            material=collect(mat_path), texture=collect(textures[env['m_Texture']['guid']]),
            tint=[tint[c] for c in 'rgba'], uv_scale=[env['m_Scale'][a] for a in 'xy'],
            uv_offset=[env['m_Offset'][a] for a in 'xy']))
        collect(source/f'Prefabs/Animals/{material}.prefab')
    recipe = dict(format=1, animals=animals, source_sha256=hashes)
    path = output/'animals.source.json'
    path.write_text(json.dumps(recipe, indent=2)+'\n')
    subprocess.run([args.blender, '-b', '-t', '2', '--python-exit-code', '1', '--python', str(ROOT/'scripts/bake_animals.py'), '--', str(path)], check=True)


if __name__ == '__main__': main()
