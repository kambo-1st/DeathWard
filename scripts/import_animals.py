"""Collect every current Polyperfect animal prefab, source clip and original texture."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess
import sys
import yaml

sys.dont_write_bytecode = True
from import_western import documents

ROOT = Path(__file__).resolve().parents[1]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', type=Path, default=ROOT / 'assets/animals/source')
    parser.add_argument('--output', type=Path, default=ROOT / 'assets/animals')
    parser.add_argument('--blender', default='blender')
    parser.add_argument('--collect-only', action='store_true')
    parser.add_argument('--only', nargs='+', help='Rebake selected IDs; retain other manifest entries')
    args = parser.parse_args()
    source, output = args.source.resolve(), args.output.resolve()
    if (source / 'Low Poly Animated Animals').is_dir():
        source /= 'Low Poly Animated Animals'
    output.mkdir(parents=True, exist_ok=True)
    selection = json.loads((ROOT / 'assets/animals/animals.selection.json').read_text())['animals']
    # A missing/new prefab cannot silently disappear from a full import.
    actual = {str(p.relative_to(source)) for p in (source / 'Prefabs/Animals').glob('*.prefab')}
    expected = {a['prefab'] for a in selection}
    if actual != expected:
        raise ValueError(f'Prefab inventory differs: missing={expected-actual}, unselected={actual-expected}')
    index, hashes, unity = {}, {}, {}
    for meta in source.rglob('*.meta'):
        match = re.search(r'^guid: (\w+)', meta.read_text(), re.M)
        if match:
            index[match[1]] = meta.with_suffix('')

    def collect(path):
        relative = str(path.relative_to(source))
        if relative in hashes:
            return relative
        target = output / 'source' / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        if path != target:
            shutil.copyfile(path, target)
        hashes[relative] = hashlib.sha256(path.read_bytes()).hexdigest()
        meta = path.with_name(path.name + '.meta')
        if meta.exists():
            dest = target.with_name(target.name + '.meta')
            if meta != dest:
                shutil.copyfile(meta, dest)
            hashes[str(meta.relative_to(source))] = hashlib.sha256(meta.read_bytes()).hexdigest()
        return relative

    animals = []
    for selected in selection:
        entry = dict(selected)
        rig = source / entry['rig']
        collect(rig)
        if entry.get('bind_source'):
            collect(source / entry['bind_source'])
        collect(source / entry['prefab'])
        mat_path = source / entry['material']
        properties = documents(mat_path)[0][2]['m_SavedProperties']
        floats = {k: v for row in properties.get('m_Floats', []) for k, v in row.items()}
        if floats.get('_Mode', 0) != 0:
            raise ValueError(f'Expected opaque animal material: {mat_path}')
        env = next(e['_MainTex'] for e in properties['m_TexEnvs'] if '_MainTex' in e)
        tint = next(e['_Color'] for e in properties['m_Colors'] if '_Color' in e)
        entry.update(material=collect(mat_path), texture=collect(index[env['m_Texture']['guid']]),
                     tint=[tint[c] for c in 'rgba'], uv_scale=[env['m_Scale'][a] for a in 'xy'],
                     uv_offset=[env['m_Offset'][a] for a in 'xy'], family=rig.parent.name, alpha_mode='OPAQUE')
        files = sorted(rig.parent.glob('*.fbx'))
        # These families contain distinct skeletons and animation libraries.
        if rig.parent.name in ('Camel', 'Elephant', 'Lion', 'Sheep'):
            stem = re.sub(r'_(Rig|Animations?)$', '', rig.stem)
            files = [f for f in files if f == rig or
                     f.stem.startswith(stem + '_Animation')]
        if entry.get('animation_sources'):
            files = [source / name for name in entry['animation_sources']]
        # Prefer the animation library; auxiliary/rig clips get unique suffixes on collisions.
        files.sort(key=lambda f: (f == rig, f.name))
        animations = []
        for file in files:
            meta = yaml.safe_load(file.with_name(file.name + '.meta').read_text())['ModelImporter']
            clips = meta['animations']['clipAnimations']
            animations.append(dict(file=collect(file), clips=[dict(name=c['name'], take=c['takeName'],
                first=c['firstFrame'], last=c['lastFrame']) for c in clips]))
        for file in sorted(rig.parent.glob('*.anim')):
            key = collect(file)
            if key not in unity:
                clip = documents(file)[0][2]
                if clip.get('m_CompressedRotationCurves'):
                    raise ValueError(f'Unsupported compressed curves: {file}')
                unity[key] = {k: clip[k] for k in ('m_Name', 'm_SampleRate', 'm_AnimationClipSettings',
                                                  'm_PositionCurves', 'm_RotationCurves', 'm_ScaleCurves', 'm_EulerCurves')}
                # Legacy Renderer (25) and particle components are outside skeletal animation.
                ignored = clip.get('m_FloatCurves', [])
                if any(c['classID'] not in (25, 198, 199) for c in ignored):
                    raise ValueError(f'Unsupported animated property: {file}')
                unity[key]['excluded_component_curves'] = [
                    dict(path=c['path'], attribute=c['attribute'], class_id=c['classID']) for c in ignored]
            animations.append(dict(file=key, unity=True))
        entry['animations'] = animations
        animals.append(entry)
    recipe = dict(format=2, animals=animals, source_sha256=hashes,
                  prefab_count=len(expected), family_count=len({a['family'] for a in animals}))
    path = output / 'animals.source.json'
    path.write_text(json.dumps(recipe, indent=2) + '\n')
    (output / 'animals.unity.json').write_text(json.dumps(unity, separators=(',', ':')) + '\n')
    print(f'Collected {len(animals)} variants / {recipe["family_count"]} families; {len(unity)} Unity clips', flush=True)
    if not args.collect_only:
        if args.only:
            command = [args.blender, '-b', '-t', '2', '--python-exit-code', '1', '--python',
                       str(ROOT / 'scripts/bake_animals.py'), '--', str(path), *args.only]
        else:
            command = [sys.executable, str(ROOT / 'scripts/bake_animal_pack.py'),
                       '--blender', args.blender, '--output', str(output)]
        subprocess.run(command, check=True)
        subprocess.run([sys.executable, str(ROOT / 'scripts/finalize_animal_materials.py'), str(output)], check=True)
        subprocess.run([sys.executable, str(ROOT / 'scripts/catalog_animals.py'), str(output)], check=True)


if __name__ == '__main__':
    main()
