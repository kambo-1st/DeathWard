"""Blender half of import_particles.py; bake the FBX mesh at its authored scale."""
import sys
import argparse
import bpy

parser = argparse.ArgumentParser()
parser.add_argument('source')
parser.add_argument('output')
parser.add_argument('--normalize', action='store_true')
parser.add_argument('--texture')
args = parser.parse_args(sys.argv[sys.argv.index('--')+1:])
source, output = args.source, args.output
bpy.ops.wm.read_factory_settings(use_empty=True)
bpy.ops.import_scene.fbx(filepath=source, use_anim=False, use_image_search=False)
for obj in list(bpy.data.objects):
    if obj.type != "MESH":
        bpy.data.objects.remove(obj, do_unlink=True)
        continue
    obj.data.transform(obj.matrix_world)
    obj.matrix_world.identity()
    if args.normalize:
        points = [v.co for v in obj.data.vertices]
        low = [min(v[a] for v in points) for a in range(3)]
        high = [max(v[a] for v in points) for a in range(3)]
        extent = max(high[a]-low[a] for a in range(3))
        for v in obj.data.vertices:
            for a in range(3):
                v.co[a] = (v.co[a]-(high[a]+low[a])*.5)/extent
    obj.data.materials.clear()
    material = bpy.data.materials.new("ParticleColor")
    material.diffuse_color = (1, 1, 1, 1)
    if args.texture:
        material.use_nodes = True
        shader = material.node_tree.nodes.get('Principled BSDF')
        texture = material.node_tree.nodes.new('ShaderNodeTexImage')
        texture.image = bpy.data.images.load(args.texture)
        material.node_tree.links.new(texture.outputs['Color'], shader.inputs['Base Color'])
        shader.inputs['Roughness'].default_value = 1
    obj.data.materials.append(material)
bpy.ops.export_scene.gltf(filepath=output, export_format="GLB", export_animations=False,
                         export_yup=True, export_normals=True)
