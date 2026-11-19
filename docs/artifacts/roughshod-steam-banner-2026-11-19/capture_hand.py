"""Render an actual 3D close-up of the saved scene's grip; do not edit the .blend."""
import bpy
from pathlib import Path
from mathutils import Vector
scene=bpy.context.scene
rig=bpy.data.objects['GUNSLINGER · original 48-bone rig']
center=rig.matrix_world@rig.pose.bones['Hand_R'].tail+Vector((0,0,-.15))
cam=scene.camera;direction=(cam.location-center).normalized()
cam.location=center+direction*4
cam.rotation_euler=(center-cam.location).to_track_quat('-Z','Y').to_euler()
cam.data.type='ORTHO';cam.data.ortho_scale=1.7
bpy.data.collections['05 · ROUGHSHOD / editable 3D type'].hide_render=True
scene.render.resolution_x=800;scene.render.resolution_y=800;scene.cycles.samples=32
scene.render.filepath=str(Path(__file__).resolve().parent/'hand-detail.png')
bpy.ops.render.render(write_still=True)
