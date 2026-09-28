"""Bake the supplied FBXs into a single, self-contained raylib-compatible GLB.

Run with Blender 3.6 LTS:
    blender --background --python scripts/convert_cowgirl.py

Blender is only an asset-authoring dependency; normal builds use the checked-in GLB.
"""

import hashlib
import json
import math
from pathlib import Path

import bpy
from mathutils import Matrix, Vector


ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "assets" / "cowgirl"
CLIPS = {
    "Idle": "Idle.fbx",
    "Idle2": "Idle (1).fbx",
    "Walk": "Walking (1).fbx",
}


def main():
    bpy.ops.wm.read_factory_settings(use_empty=True)
    scene = bpy.context.scene
    scene.render.fps = 30
    target_rig = target_mesh = None
    clips = {}
    manifest = {"format": 1, "blender": bpy.app.version_string, "clips": {}}
    # Source mesh/bone rest coordinates use centimeters, Y up, forward +Z.
    rest_conversion = Matrix.Rotation(math.pi / 2, 4, "X") @ Matrix.Scale(0.01, 4)

    for name, filename in CLIPS.items():
        path = SOURCE / filename
        if not path.is_file():
            raise RuntimeError(f"Missing source clip: {path}")
        before = set(bpy.data.objects)
        bpy.ops.import_scene.fbx(filepath=str(path), use_image_search=False)
        imported = set(bpy.data.objects) - before
        rig = next(obj for obj in imported if obj.type == "ARMATURE")
        mesh = next(obj for obj in imported if obj.type == "MESH")
        # FBX contains unrelated legacy Synty object tracks. Use the Mixamo take
        # on the skeleton AND its animated ancestors, otherwise the body is tilted.
        for obj in imported:
            action = bpy.data.actions.get(obj.name + "|mixamo.com|Layer0")
            if action:
                obj.animation_data_create().action = action
        action = rig.animation_data.action
        if not action or "mixamo.com" not in action.name:
            raise RuntimeError(f"No skeletal Mixamo take in {filename}")
        first, last = (int(value) for value in action.frame_range)
        scene.frame_set(first)

        if target_rig is None:
            target_rig = bpy.data.objects.new("CowgirlRig", rig.data.copy())
            scene.collection.objects.link(target_rig)
            target_rig.data.transform(rest_conversion)
            target_mesh = mesh.copy()
            target_mesh.data = mesh.data.copy()
            target_mesh.name = "CowgirlMesh"
            target_mesh.animation_data_clear()
            target_mesh.data.transform(rest_conversion @ rig.matrix_world.inverted() @ mesh.matrix_world)
            target_mesh.parent = target_rig
            target_mesh.matrix_parent_inverse = Matrix.Identity(4)
            target_mesh.matrix_basis = Matrix.Identity(4)
            for modifier in target_mesh.modifiers:
                if modifier.type == "ARMATURE":
                    modifier.object = target_rig
            scene.collection.objects.link(target_mesh)
            for image in bpy.data.images:
                if image.size[0] and not image.packed_file:
                    image.pack()
            if not any(image.packed_file for image in bpy.data.images):
                raise RuntimeError("The supplied cowgirl's embedded texture was not imported")

        names = [bone.name for bone in target_rig.data.bones]
        if set(names) != {bone.name for bone in rig.data.bones}:
            raise RuntimeError(f"Skeleton mismatch in {filename}")
        samples = {bone: [] for bone in names}
        for frame in range(first, last + 1):
            scene.frame_set(frame)
            world = {}
            for bone in names:
                location, rotation, scale = (rig.matrix_world @ rig.pose.bones[bone].matrix).decompose()
                # The source's object scale converts centimeters to meters. Bone
                # positions and mesh vertices already have that conversion baked;
                # retaining it in joint scales would shrink the skin a second time.
                world[bone] = Matrix.LocRotScale(location, rotation, scale * 100)
            # Bake animated ancestors into the skeleton, keeping vertical motion.
            # Remove X/Y ground travel so input/collision alone move the character.
            hips = world["Hips"].translation
            in_place = Matrix.Translation(Vector((-hips.x, -hips.y, 0)))
            world = {bone: in_place @ matrix for bone, matrix in world.items()}
            for bone in target_rig.data.bones:
                rest = bone.matrix_local
                desired = world[bone.name]
                if bone.parent:
                    rest = bone.parent.matrix_local.inverted() @ rest
                    desired = world[bone.parent.name].inverted() @ desired
                location, rotation, scale = (rest.inverted() @ desired).decompose()
                previous = samples[bone.name]
                if previous and rotation.dot(previous[-1][1]) < 0:
                    rotation.negate()
                samples[bone.name].append((location, rotation, scale))
        clips[name] = samples
        manifest["clips"][name] = {
            "source": filename,
            "sha256": hashlib.sha256(path.read_bytes()).hexdigest(),
            "frames": last - first + 1,
            "fps": scene.render.fps,
            "duration": (last - first) / scene.render.fps,
        }
        for obj in imported:
            bpy.data.objects.remove(obj, do_unlink=True)
        for old_action in list(bpy.data.actions):
            bpy.data.actions.remove(old_action)
        print(f"BAKED {name}: {last - first + 1} frames, {len(names)} bones")

    for name, samples in clips.items():
        action = bpy.data.actions.new(name)
        action.use_fake_user = True
        for bone_name, poses in samples.items():
            bone = target_rig.pose.bones[bone_name]
            bone.rotation_mode = "QUATERNION"
            for component, channel, count in ((0, "location", 3), (1, "rotation_quaternion", 4), (2, "scale", 3)):
                for axis in range(count):
                    curve = action.fcurves.new(bone.path_from_id(channel), index=axis, action_group=bone_name)
                    curve.keyframe_points.add(len(poses))
                    values = []
                    for frame, pose in enumerate(poses):
                        values.extend((frame, pose[component][axis]))
                    curve.keyframe_points.foreach_set("co", values)
                    for key in curve.keyframe_points:
                        key.interpolation = "LINEAR"
        target_rig.animation_data_create()
        track = target_rig.animation_data.nla_tracks.new()
        track.name = name
        track.strips.new(name, 0, action)
        track.mute = True

    # Export rest geometry, one identity armature and the named clips. No camera,
    # wrapper animation, external image path, or proprietary FBX runtime is needed.
    target_rig.animation_data.action = None
    target_rig.data.pose_position = "REST"
    bpy.ops.object.select_all(action="DESELECT")
    target_rig.select_set(True)
    target_mesh.select_set(True)
    bpy.context.view_layer.objects.active = target_rig
    scene.frame_set(0)
    target_rig.data.pose_position = "POSE"
    output = SOURCE / "cowgirl.glb"
    bpy.ops.export_scene.gltf(
        filepath=str(output), export_format="GLB", use_selection=True,
        export_yup=True, export_animations=True, export_animation_mode="ACTIONS",
        export_force_sampling=True, export_anim_slide_to_zero=True,
        export_frame_range=False, export_skins=True, export_def_bones=False,
        export_all_influences=False, export_morph=False, export_cameras=False,
        export_lights=False,
    )
    manifest["vertices"] = len(target_mesh.data.vertices)
    manifest["triangles"] = sum(len(poly.vertices) - 2 for poly in target_mesh.data.polygons)
    manifest["bones"] = len(target_rig.data.bones)
    manifest["output_sha256"] = hashlib.sha256(output.read_bytes()).hexdigest()
    (SOURCE / "cowgirl.manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    print(f"EXPORTED {output} ({output.stat().st_size} bytes)")


if __name__ == "__main__":
    main()
