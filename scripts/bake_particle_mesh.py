"""Blender half of import_particles.py; bake the FBX mesh at its authored scale."""
import sys
import bpy

source, output = sys.argv[sys.argv.index("--") + 1:]
bpy.ops.wm.read_factory_settings(use_empty=True)
bpy.ops.import_scene.fbx(filepath=source, use_anim=False, use_image_search=False)
for obj in list(bpy.data.objects):
    if obj.type != "MESH":
        bpy.data.objects.remove(obj, do_unlink=True)
        continue
    obj.data.transform(obj.matrix_world)
    obj.matrix_world.identity()
    obj.data.materials.clear()
    material = bpy.data.materials.new("ParticleColor")
    material.diffuse_color = (1, 1, 1, 1)
    obj.data.materials.append(material)
bpy.ops.export_scene.gltf(filepath=output, export_format="GLB", export_animations=False,
                         export_yup=True, export_normals=True)
