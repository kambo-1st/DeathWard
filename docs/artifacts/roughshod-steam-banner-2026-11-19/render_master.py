"""Render the saved master without changing the composition."""
import bpy,json
from pathlib import Path
out=Path(__file__).resolve().parent
bpy.ops.render.render(write_still=True)
(out/"render-complete.json").write_text(json.dumps({"rendered":True,"samples":bpy.context.scene.cycles.samples,"resolution":[bpy.context.scene.render.resolution_x,bpy.context.scene.render.resolution_y]},indent=2)+"\n")
