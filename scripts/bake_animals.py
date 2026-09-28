"""Bake Polyperfect FBX takes and Unity transform curves into portable skinned GLBs."""
import bisect
import hashlib
import json
import math
from pathlib import Path
import re
import struct
import statistics
import sys
import traceback
import bpy
from mathutils import Matrix, Vector, Quaternion, Euler

ROTATE = Matrix.Rotation(math.pi / 2, 4, 'X')
REFLECT = Matrix.Diagonal((-1, 1, 1, 1))
UNITY_TO_BLENDER = ROTATE @ REFLECT


def clip_name(take):
    action = re.search(r'(?:^|[_ ])(attack|death|dead|idle|walk|run|eat|eating|fly|flying|swim|swimming|sleep|slither|bark|sit|howl|rub|drink|scream|stand|fast|slow)', take, re.I)
    if action:
        take = take[action.start(1):]
    name = re.sub(r'[^A-Za-z0-9]', '', take)
    canonical = {'idle1': 'Idle', 'idlebreathing': 'Idle', 'idlebreath': 'Idle',
                 'eating': 'Eat', 'dead': 'Death', 'swimming': 'Swim', 'flying': 'Fly'}
    return canonical.get(name.lower(), name[:1].upper() + name[1:])


def normalized(matrix):
    loc, rot, scale = matrix.decompose()
    return Matrix.LocRotScale(loc, rot, Vector((1, 1, 1)))


def sample_curve(keys, t, axes):
    if t <= keys[0]['time']:
        return [float(keys[0]['value'][a]) for a in axes]
    if t >= keys[-1]['time']:
        return [float(keys[-1]['value'][a]) for a in axes]
    index = bisect.bisect_right([k['time'] for k in keys], t) - 1
    a, b = keys[index:index+2]
    span = b['time'] - a['time']
    u = (t - a['time']) / span
    result = []
    for axis in axes:
        v0, v1 = float(a['value'][axis]), float(b['value'][axis])
        m0, m1 = float(a['outSlope'][axis]), float(b['inSlope'][axis])
        # Unity's serialized transform curves use cubic Hermite tangents.
        if not math.isfinite(m0) or not math.isfinite(m1):
            result.append(v0)
        else:
            result.append((2*u**3-3*u*u+1)*v0 + (u**3-2*u*u+u)*span*m0 +
                          (-2*u**3+3*u*u)*v1 + (u**3-u*u)*span*m1)
    return result


def unity_frames(clip, target):
    channels = {}
    for field, component in [('m_PositionCurves', 'position'), ('m_RotationCurves', 'rotation'),
                              ('m_ScaleCurves', 'scale'), ('m_EulerCurves', 'euler')]:
        for curve in clip.get(field, []):
            channels.setdefault(curve['path'], {})[component] = curve['curve']['m_Curve']
            if component == 'euler':
                channels[curve['path']]['rotation_order'] = curve['curve'].get('m_RotationOrder', 4)
    paths = set(channels)
    for path in list(paths):
        while '/' in path:
            path = path.rsplit('/', 1)[0]
            paths.add(path)
    paths = sorted(paths, key=lambda p: (p.count('/'), p))
    bones = {b.name: b for b in target.data.bones}
    by_name = {path.rsplit('/', 1)[-1]: path for path in paths}
    # Blender and Unity import the same FBX bone frames with different handedness.
    rest = {name: UNITY_TO_BLENDER.inverted() @ bone.matrix_local @ REFLECT
            for name, bone in bones.items()}
    rest_paths = {path: rest.get(path.rsplit('/', 1)[-1], Matrix.Identity(4)) for path in paths}
    locals_ = {}
    for path in paths:
        parent = path.rsplit('/', 1)[0] if '/' in path else None
        locals_[path] = (rest_paths[parent].inverted() @ rest_paths[path] if parent else rest_paths[path]).decompose()
    fps = clip['m_SampleRate']
    settings = clip['m_AnimationClipSettings']
    start, stop = settings['m_StartTime'], settings['m_StopTime']
    count = int(round((stop-start)*fps)) + 1
    for n in range(count):
        t = start + n/fps
        worlds = {}
        for path in paths:
            loc, rot, scale = locals_[path]
            c = channels.get(path, {})
            if 'position' in c:
                loc = Vector(sample_curve(c['position'], t, 'xyz'))
            if 'rotation' in c:
                x, y, z, w = sample_curve(c['rotation'], t, 'xyzw')
                rot = Quaternion((w, x, y, z)).normalized()
            elif 'euler' in c:
                order = ('XYZ', 'XZY', 'YZX', 'YXZ', 'ZXY', 'ZYX')[c['rotation_order']]
                rot = Euler([math.radians(v) for v in sample_curve(c['euler'], t, 'xyz')], order).to_quaternion()
            if 'scale' in c:
                scale = Vector(sample_curve(c['scale'], t, 'xyz'))
            matrix = Matrix.LocRotScale(loc, rot, scale)
            parent = path.rsplit('/', 1)[0] if '/' in path else None
            worlds[path] = worlds[parent] @ matrix if parent else matrix
        result = {}
        for bone in target.data.bones:
            if bone.name in by_name:
                result[bone.name] = UNITY_TO_BLENDER @ worlds[by_name[bone.name]] @ REFLECT
            elif bone.parent:
                result[bone.name] = result[bone.parent.name] @ bone.parent.matrix_local.inverted() @ bone.matrix_local
            else:
                result[bone.name] = bone.matrix_local.copy()
        yield result


def bake(entry, output, unity):
    bpy.ops.wm.read_factory_settings(use_empty=True)
    scene = bpy.context.scene
    source = output / 'source'
    bpy.ops.import_scene.fbx(filepath=str(source / entry['rig']), use_anim=False, use_image_search=False)
    meshes = [bpy.data.objects[name] for name in entry['meshes']]
    rig = next(mod.object for mod in meshes[0].modifiers if mod.type == 'ARMATURE')
    if entry.get('bind_source'):
        # Explicit repairs retain the prefab mesh and UVs while borrowing a
        # compatible rest skeleton from the family's working animation file.
        before = set(bpy.data.objects)
        bpy.ops.import_scene.fbx(filepath=str(source / entry['bind_source']), use_anim=False, use_image_search=False)
        candidates = [o for o in set(bpy.data.objects) - before if o.type == 'ARMATURE']
        names = set(b.name for b in rig.data.bones)
        rig = max(candidates, key=lambda o: len(names & set(b.name for b in o.data.bones)))
    target = bpy.data.objects.new('AnimalRig', rig.data.copy())
    scene.collection.objects.link(target)
    target.data.transform(rig.matrix_world)
    # Rest bone scales must match the normalized, meter-space animation frames.
    material = bpy.data.materials.new(entry['id'])
    material.use_nodes = True
    shader = material.node_tree.nodes.get('Principled BSDF')
    shader.inputs['Roughness'].default_value = .85
    image = bpy.data.images.load(str(source / entry['texture']))
    image.pack()
    texture = material.node_tree.nodes.new('ShaderNodeTexImage')
    texture.image = image
    material.node_tree.links.new(texture.outputs['Color'], shader.inputs['Base Color'])
    targets = []
    for mesh in meshes:
        obj = mesh.copy()
        obj.hide_render = obj.hide_viewport = False
        obj.data = mesh.data.copy()
        obj.animation_data_clear()
        obj.data.transform(normalized(mesh.matrix_world) if entry.get('normalize_mesh_scale') else mesh.matrix_world)
        obj.parent = target
        obj.matrix_parent_inverse = obj.matrix_basis = Matrix.Identity(4)
        for mod in obj.modifiers:
            if mod.type == 'ARMATURE':
                mod.object = target
        for color in list(obj.data.color_attributes):
            obj.data.color_attributes.remove(color)
        obj.data.materials.clear()
        obj.data.materials.append(material)
        for polygon in obj.data.polygons:
            polygon.material_index = 0
        for uv in obj.data.uv_layers.active.data:
            uv.uv.x = uv.uv.x*entry['uv_scale'][0] + entry['uv_offset'][0]
            uv.uv.y = uv.uv.y*entry['uv_scale'][1] + entry['uv_offset'][1]
        scene.collection.objects.link(obj)
        targets.append(obj)
    keep = set(targets + [target])
    for obj in list(bpy.data.objects):
        if obj not in keep:
            bpy.data.objects.remove(obj, do_unlink=True)
    names = [b.name for b in target.data.bones]
    clips, details = {}, {}
    root = next(b.name for b in target.data.bones if b.parent is None)

    def store_clip(label, worlds, fps, source_file, take):
        name = clip_name(label)
        base, number = name, 2
        while name in clips:
            name = f'{base}V{number}'
            number += 1
        samples = {name: [] for name in names}
        for world in worlds:
            delta = world[root].translation - target.data.bones[root].matrix_local.translation
            in_place = Matrix.Translation(Vector((-delta.x, -delta.y, 0)))
            world = {bone: in_place @ matrix for bone, matrix in world.items()}
            for bone in target.data.bones:
                rest, desired = bone.matrix_local, world[bone.name]
                if bone.parent:
                    rest = bone.parent.matrix_local.inverted() @ rest
                    desired = world[bone.parent.name].inverted() @ desired
                loc, rot, scale = (rest.inverted() @ desired).decompose()
                previous = samples[bone.name]
                if previous and rot.dot(previous[-1][1]) < 0:
                    rot.negate()
                previous.append((loc, rot, scale))
        count = len(samples[root])
        if count < 2:
            raise ValueError(f'Clip has no duration: {source_file}: {take}')
        clips[name] = samples
        details[name] = dict(source_file=source_file, source_take=take, frames=count, fps=fps,
                             duration=(count-1)/fps)

    for animation in entry['animations']:
        file = animation['file']
        if animation.get('unity'):
            data = unity[file]
            store_clip(data['m_Name'], unity_frames(data, target), data['m_SampleRate'], file, data['m_Name'])
            continue
        for action in list(bpy.data.actions):
            bpy.data.actions.remove(action)
        before = set(bpy.data.objects)
        bpy.ops.import_scene.fbx(filepath=str(source / file), use_image_search=False)
        imported = set(bpy.data.objects) - before
        candidates = [o for o in imported if o.type == 'ARMATURE']
        rig = max(candidates, key=lambda o: len(set(names) & set(b.name for b in o.data.bones)))
        common = set(names) & set(b.name for b in rig.data.bones)
        if len(common) < len(names)*.5:
            raise ValueError(f'Incompatible skeleton: {file}: {len(common)}/{len(names)}')
        # Separate FBX libraries sometimes use a different overall rig scale
        # (notably the wolf, chimpanzee and bees). Match bone segment lengths
        # before transferring world-space translations to the textured rig.
        ratios = []
        for bone in target.data.bones:
            other = rig.data.bones.get(bone.name)
            if not bone.parent or not other or not other.parent or bone.parent.name != other.parent.name:
                continue
            a = (bone.matrix_local.translation - bone.parent.matrix_local.translation).length
            b = (rig.matrix_world @ other.matrix_local.translation -
                 rig.matrix_world @ other.parent.matrix_local.translation).length
            if min(a, b) > .000001:
                ratios.append(a/b)
        ratio = statistics.median(ratios) if ratios else 1
        translation_scale = ratio if sum(abs(r/ratio-1) < .01 for r in ratios) >= .8*len(ratios) else 1
        if abs(translation_scale-1) < .001:
            translation_scale = 1
        if translation_scale != 1:
            print('MATCH ANIMATION SCALE', entry['id'], file, translation_scale, flush=True)
        actions = list(bpy.data.actions)
        takes = {a.name.split('|')[1]: a for a in actions if a.name.startswith(rig.name+'|')}
        definitions = animation['clips'] or [dict(name=take, take=take) for take in takes if take != 'Take 001']
        for definition in definitions:
            take = definition['take']
            if take not in takes:
                raise ValueError(f'Missing take {take} in {file}')
            action = takes[take]
            for obj in imported:
                matching = next((a for a in actions if a.name == obj.name+'|'+take+'|BaseLayer'), None)
                if matching:
                    obj.animation_data_create().action = matching
            rig.animation_data.action = action
            first, last = [int(round(v)) for v in action.frame_range]
            if 'first' in definition:
                first, last = int(round(definition['first']))+1, int(round(definition['last']))+1
            fps = scene.render.fps / scene.render.fps_base

            def frames():
                for frame in range(first, last+1):
                    scene.frame_set(frame)
                    unit_scale = rig.matrix_world.decompose()[2]
                    world = {}
                    for bone in target.data.bones:
                        if bone.name in rig.pose.bones:
                            loc, rot, scale = (rig.matrix_world @ rig.pose.bones[bone.name].matrix).decompose()
                            loc *= translation_scale
                            world[bone.name] = Matrix.LocRotScale(loc, rot, Vector([scale[k]/unit_scale[k] for k in range(3)]))
                        elif bone.parent:
                            world[bone.name] = world[bone.parent.name] @ bone.parent.matrix_local.inverted() @ bone.matrix_local
                        else:
                            world[bone.name] = bone.matrix_local.copy()
                    yield world
            store_clip(definition['name'], frames(), fps, file, take)
        for obj in imported:
            bpy.data.objects.remove(obj, do_unlink=True)
    if not clips:
        raise ValueError(f'No animation clips: {entry["id"]}')
    for action in list(bpy.data.actions):
        bpy.data.actions.remove(action)
    bake_fps = math.lcm(*(int(round(info['fps'])) for info in details.values()))
    scene.render.fps, scene.render.fps_base = bake_fps, 1
    for name, samples in clips.items():
        action = bpy.data.actions.new(name)
        action.id_root = 'OBJECT'
        action.use_fake_user = True
        for bone_name, poses in samples.items():
            bone = target.pose.bones[bone_name]
            bone.rotation_mode = 'QUATERNION'
            for component, channel, count in ((0, 'location', 3), (1, 'rotation_quaternion', 4), (2, 'scale', 3)):
                for axis in range(count):
                    curve = action.fcurves.new(bone.path_from_id(channel), index=axis, action_group=bone_name)
                    curve.keyframe_points.add(len(poses))
                    values = []
                    for frame, pose in enumerate(poses):
                        values.extend((frame*bake_fps/details[name]['fps'], pose[component][axis]))
                    curve.keyframe_points.foreach_set('co', values)
                    for key in curve.keyframe_points:
                        key.interpolation = 'LINEAR'
        target.animation_data_create()
        track = target.animation_data.nla_tracks.new()
        track.name = name
        track.strips.new(name, 0, action)
        track.mute = True
    target.animation_data.action = None
    bpy.ops.object.select_all(action='DESELECT')
    for obj in keep:
        obj.select_set(True)
    bpy.context.view_layer.objects.active = target
    scene.frame_set(0)
    path = output / (entry['id']+'.glb')
    bpy.ops.export_scene.gltf(filepath=str(path), export_format='GLB', use_selection=True,
        export_yup=True, export_animations=True, export_animation_mode='ACTIONS', export_force_sampling=True,
        export_anim_slide_to_zero=True, export_frame_range=False, export_skins=True, export_def_bones=False,
        export_all_influences=False, export_morph=False, export_cameras=False, export_lights=False)
    blob = path.read_bytes()
    json_size = struct.unpack_from('<I', blob, 12)[0]
    document = json.loads(blob[20:20+json_size])
    for mat in document['materials']:
        mat['pbrMetallicRoughness']['baseColorFactor'] = entry['tint']
    encoded = json.dumps(document, separators=(',', ':')).encode()
    encoded += b' '*((-len(encoded)) % 4)
    tail = blob[20+json_size:]
    path.write_bytes(struct.pack('<III', 0x46546c67, 2, 20+len(encoded)+len(tail)) +
                     struct.pack('<II', len(encoded), 0x4e4f534a) + encoded + tail)
    points = [vertex.co for obj in targets for vertex in obj.data.vertices]
    bounds = [[min(v[k] for v in points) for k in range(3)], [max(v[k] for v in points) for k in range(3)]]
    return dict(clips=details, bones=len(names), texture=entry['texture'], texture_size=list(image.size),
                bind_source=entry.get('bind_source', entry['rig']),
                vertices=len(points), bounds_blender=bounds,
                output_sha256=hashlib.sha256(path.read_bytes()).hexdigest())


def main():
    args = sys.argv[sys.argv.index('--')+1:]
    path = Path(args[0])
    shard = next((a.split('=')[1] for a in args[1:] if a.startswith('--shard=')), None)
    selected = [a for a in args[1:] if not a.startswith('--shard=')]
    recipe = json.loads(path.read_text())
    output = path.parent
    unity = json.loads((output / 'animals.unity.json').read_text())
    manifest_path = output / ('animals.manifest.json' if not shard else f'animals.part-{shard.split("/")[0]}.json')
    existing = json.loads(manifest_path.read_text()) if manifest_path.exists() and selected else {}
    manifest = dict(format=2, blender=bpy.app.version_string, source_sha256=recipe['source_sha256'],
                    animals=existing.get('animals', {}), failures={})
    entries = recipe['animals']
    if shard:
        index, count = map(int, shard.split('/'))
        entries = entries[index::count]
    for entry in entries:
        if selected and entry['id'] not in selected:
            continue
        try:
            manifest['animals'][entry['id']] = bake(entry, output, unity)
            print('BAKED ANIMAL', entry['id'], len(manifest['animals'][entry['id']]['clips']), 'clips', flush=True)
        except Exception as error:
            traceback.print_exc()
            manifest['animals'].pop(entry['id'], None)
            manifest['failures'][entry['id']] = str(error)
        manifest_path.write_text(json.dumps(manifest, indent=2)+'\n')
    if manifest['failures']:
        raise RuntimeError(f'Failed animals: {manifest["failures"]}')


if __name__ == '__main__':
    main()
