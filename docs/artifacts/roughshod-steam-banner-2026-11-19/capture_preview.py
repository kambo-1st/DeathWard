"""Refresh the editable draft and its render from the saved master."""
import bpy
from pathlib import Path
p=Path(__file__).resolve().parent
scene=bpy.context.scene
scene.render.resolution_x=1280
scene.render.resolution_y=720
scene.render.resolution_percentage=100
scene.cycles.samples=20
scene.render.filepath=str(p/'roughshod-preview.png')
bpy.context.preferences.filepaths.save_version=0
bpy.ops.wm.save_as_mainfile(filepath=str(p/'roughshod-preview.blend'),compress=True)
bpy.ops.render.render(write_still=True)
exec((p/'capture_thumbnail.py').read_text(),{'__file__':str(p/'capture_thumbnail.py')})
