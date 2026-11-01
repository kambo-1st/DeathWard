import bpy,math
from pathlib import Path
root=Path(__file__).resolve().parents[3]
from mathutils import Vector
bpy.ops.wm.read_factory_settings(use_empty=True)
bpy.ops.import_scene.gltf(filepath=str(root/'assets/western/western.glb'))
names=['cactus_a','flower_cactus','green_bush','desert_grass','desert_tree','grass_b']
for o in list(bpy.data.objects):
 if o.name not in names:bpy.data.objects.remove(o,do_unlink=True)
for i,n in enumerate(names):
 o=bpy.data.objects[n];o.scale*=min(2.4/max(o.dimensions.x,o.dimensions.y),2.1/max(.01,o.dimensions.z));o.location=Vector(((i%3-1)*3.5,(.5-i//3)*4,0))
 # Labels are native scene objects, not image edits.
 bpy.ops.object.text_add(location=(o.location.x-1.3,o.location.y-1.2,.05),rotation=(0,0,0))
 t=bpy.context.object;t.data.body=str(i+1)+' '+n;t.data.size=.22;t.data.extrude=0
 mat=bpy.data.materials.get('label') or bpy.data.materials.new('label');mat.diffuse_color=(.04,.04,.04,1);t.data.materials.append(mat)
bpy.ops.mesh.primitive_plane_add(size=200,location=(0,0,-.03));mat=bpy.data.materials.new('neutral');mat.diffuse_color=(.48,.43,.35,1);bpy.context.object.data.materials.append(mat)
bpy.ops.object.light_add(type='AREA',location=(-3,-4,10));bpy.context.object.data.energy=1800;bpy.context.object.data.size=8
bpy.ops.object.camera_add(location=(0,-12,14));c=bpy.context.object;c.rotation_euler=(Vector((0,0,0))-c.location).to_track_quat('-Z','Y').to_euler();c.data.type='ORTHO';c.data.ortho_scale=12;bpy.context.scene.camera=c
s=bpy.context.scene;s.render.engine='BLENDER_EEVEE';s.eevee.use_gtao=True;s.world=bpy.data.worlds.new('World');s.world.color=(.5,.5,.5);s.view_settings.view_transform='Standard';s.view_settings.look='Medium High Contrast';s.render.resolution_x=1600;s.render.resolution_y=1000;s.render.resolution_percentage=100;s.render.image_settings.file_format='PNG';s.render.filepath=str(root/'docs/reports/canyon-reference-match/selected-native-models.png');bpy.ops.render.render(write_still=True)
