"""Render the saved composition at 320 × 180; leave the master scene unchanged."""
import bpy
from pathlib import Path

scene = bpy.context.scene
scene.render.resolution_x = 320
scene.render.resolution_y = 180
scene.render.resolution_percentage = 100
scene.cycles.samples = 32
scene.render.filepath = str(Path(__file__).resolve().parent / 'thumbnail-320x180.png')
bpy.ops.render.render(write_still=True)
