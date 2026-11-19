"""Render a detail of the cart story from the saved banner camera."""
import bpy
from pathlib import Path
scene=bpy.context.scene
scene.render.resolution_x=2560
scene.render.resolution_y=1440
scene.render.resolution_percentage=100
scene.cycles.samples=32
scene.render.use_border=True
scene.render.use_crop_to_border=True
scene.render.border_min_x=0.0
scene.render.border_max_x=.58
scene.render.border_min_y=.035
scene.render.border_max_y=.555
scene.render.filepath=str(Path(__file__).resolve().parent/'cart-story-detail.png')
bpy.ops.render.render(write_still=True)
