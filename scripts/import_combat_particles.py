"""Adapt PolygonParticleFX combat, steam and dust layers for DeathWard.

Requires PyYAML and Blender. Keeps source curves/gradients; all gameplay-scale
and visibility tuning is listed in combat-manifest.json, alongside source hashes.
"""
import argparse
import hashlib
import json
from pathlib import Path
import subprocess
from import_particles import ROOT, documents


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', type=Path, default=Path(
        '/mnt/c/Users/bohus/My project (1)/Assets/PolygonParticleFX'))
    parser.add_argument('--blender', default='blender')
    args = parser.parse_args()
    out = ROOT / 'assets/particles'
    sources = set()
    layers = []
    lines = ['DEATHWARD_PARTICLES 1']

    def emit(key, *values):
        lines.append(key + ' ' + ' '.join(str(v) for v in values))

    def pair(value):
        if value['minMaxState'] not in (0, 3):
            raise ValueError('Unsupported initial parameter curve')
        return (value['minScalar'] if value['minMaxState'] == 3 else value['scalar'], value['scalar'])

    def layer(name, prefab, index, mode='billboard', resource='smoke.png', alpha=1, tint=None,
              **tuning):
        source = 'Prefabs/' + prefab + '.prefab'
        sources.add(source)
        systems = [d['ParticleSystem'] for d in documents(args.source / source) if 'ParticleSystem' in d]
        x = systems[index]
        initial, emission = x['InitialModule'], x['EmissionModule']
        emit('emitter', name, mode, resource)
        params = {k: pair(initial[v]) for k, v in
                  [('lifetime', 'startLifetime'), ('size', 'startSize'), ('speed', 'startSpeed')]}
        params.update(rate=(max(1, emission['rateOverTime']['scalar']),),
                      gravity=(-9.81 * initial['gravityModifier']['scalar'],), radius=(.025,),
                      spin=(-2, 2), spread=(x['ShapeModule'].get('angle', 45),))
        if emission['m_Bursts']:
            params['burst'] = tuple(int(v) for v in pair(emission['m_Bursts'][0]['countCurve']))
        params.update(tuning)
        for key, values in params.items():
            emit(key, *(values if isinstance(values, tuple) else (values,)))
        size = x['SizeModule']
        if size['enabled']:
            curve = size['curve']
            for key in curve['maxCurve']['m_Curve']:
                emit('sizekey', key['time'], *(key[k]*curve['scalar'] for k in ('value','inSlope','outSlope')))
        else:
            emit('sizekey', 0, 1, 0, 0)
        gradient = x['ColorModule']['gradient']['maxGradient']
        if tint:
            emit('color', 0, *tint)
        elif x['ColorModule']['enabled']:
            for n in range(gradient['m_NumColorKeys']):
                emit('color', gradient[f'ctime{n}']/65535, *(gradient[f'key{n}'][c] for c in 'rgb'))
        else:
            emit('color', 0, .62, .53, .42)
        if x['ColorModule']['enabled']:
            for n in range(gradient['m_NumAlphaKeys']):
                emit('alpha', gradient[f'atime{n}']/65535, gradient[f'key{n}']['a']*alpha)
        else:
            for t, a in [(0, 1), (.65, 1), (1, 0)]:
                emit('alpha', t, a*alpha)
        lines.append('end')
        layers.append(dict(name=name, prefab=source, system=x['m_GameObject']['fileID'],
                           renderer=mode, resource=resource, overrides=tuning, opacity=alpha, tint=tint))

    layer('muzzle', 'FX_Gunshot_01', 0, 'additive', 'ember.png', tint=(1,.79,.37), size=(.38,.58))
    layer('gunsmoke', 'FX_Gunshot_01', 1, alpha=.35, lifetime=(.25,.65), size=(.18,.34),
          speed=(.15,.5), burst=(2,3), gravity=.2, spread=25)
    layer('stonechip', 'FX_Impact_Stone_01', 0, 'mesh', 'rock.glb', size=(.09,.18),
          speed=(1,3), gravity=-9.81)
    layer('stonedust', 'FX_Impact_Stone_01', 1, alpha=.38, tint=(.65,.51,.35), speed=(.5,1.8))
    layer('woodchip', 'FX_Impact_Wood_01', 0, 'mesh', 'woodchip.glb', tint=(1,1,1),
          size=(.18,.32), speed=(1.5,3.5), spin=(-8,8))
    layer('wooddust', 'FX_Impact_Wood_01', 1, alpha=.28, tint=(.54,.39,.24), speed=(.5,1.5))
    layer('spark', 'FX_Impact_Metal_01', 0, 'additive', 'ember.png', tint=(1,.8,.35),
          size=(.04,.08), lifetime=(.15,.4), speed=(2,5))
    layer('grit', 'FX_Impact_Dirt_01', 0, 'mesh', 'rock.glb', size=(.03,.07), tint=(.55,.38,.22))
    layer('dirtdust', 'FX_Impact_Dirt_01', 1, alpha=.32, tint=(.65,.49,.31), speed=(.4,1.5))
    # A small warm hit puff, not a persistent blood decal or a new gore system.
    layer('flesh', 'FX_Impact_Dirt_01', 1, alpha=.65, tint=(.48,.095,.05), burst=(3,5),
          lifetime=(.12,.26), size=(.035,.085), speed=(.4,1.4), gravity=-2)
    layer('blastfire', 'FX_Grenade_Explosive_01', 0, alpha=.8, size=(.25,.4), spread=85)
    layer('blastrock', 'FX_Grenade_Explosive_01', 1, 'mesh', 'rock.glb', burst=(8,12),
          lifetime=(.7,1.2), size=(.08,.22), speed=(2,6), spin=(-9,9))
    layer('blastember', 'FX_Grenade_Explosive_01', 2, 'additive', 'ember.png', burst=(12,18),
          lifetime=(.3,.9), size=(.035,.07), speed=(2,7))
    layer('blastsmoke', 'FX_Grenade_Explosive_01', 4, alpha=.27, burst=(5,8), lifetime=(.7,1.5),
          size=(.7,1.4), speed=(.4,1.4), tint=(.35,.30,.25))
    layer('steam', 'FX_Steam_03', 0, alpha=.23, rate=7, lifetime=(1.5,2.7), size=(.65,1.05),
          speed=(.8,1.5), gravity=.05, drift=(.16,0,.08), noise=(.12,.35), spin=(-.2,.2))
    layer('canyondust', 'FX_Dust_Blowing_Soft_01', 0, alpha=.32, rate=.65, lifetime=(4,6),
          size=(2.5,4), speed=(0,0), gravity=0, radius=1.3, drift=(.4,0,.12), spin=(-.05,.05))
    (out / 'combat.particles').write_text('\n'.join(lines)+'\n')
    atlas = 'Textures/PolygonParticles_Texture_01_A.png'
    for mesh, output, texture in [('FX_Shard_Rock_Small_01', 'rock.glb', None),
                                   ('FX_WoodChip_01', 'woodchip.glb', atlas)]:
        source = f'Models/{mesh}.fbx'
        sources.update([source, source+'.meta'])
        if texture:
            sources.add(texture)
            sources.add('Materials/PolygonParticles_Material_01_A.mat')
        command = [args.blender, '--background', '--python', str(ROOT/'scripts/bake_particle_mesh.py'),
                   '--', str(args.source/source), str(out/output), '--normalize']
        if texture:
            command.extend(['--texture', str(args.source/texture)])
        subprocess.run(command, check=True)
    manifest = dict(format=1, source_pack='PolygonParticleFX', layers=layers,
        adaptations=['Original size and opacity curves; tuned density, speed and scale for readable combat.',
                     'Raylib textured billboards replace Unity particle shaders, sphere clouds and stretched sparks.',
                     'Original woodchip UVs and embedded atlas; rock shard reused for stone and dirt fragments.',
                     'Debris meshes normalized to one metre maximum extent. Analytic cones and world gravity.',
                     'Steam uses world-space emission history; low dust has seeded walkable anchors.',
                     'No Unity collision, sub-emitter or Light-module simulation; existing explosion radius ring retained.'],
        source_sha256={p:hashlib.sha256((args.source/p).read_bytes()).hexdigest() for p in sorted(sources)},
        output_sha256={p:hashlib.sha256((out/p).read_bytes()).hexdigest()
                       for p in ['combat.particles','woodchip.glb','rock.glb']})
    (out/'combat-manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
    print(f'Imported {len(layers)} combat/environment layers')


if __name__ == '__main__':
    main()
