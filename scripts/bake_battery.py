"""Editable original low-poly battery pickup; no third-party sprite artwork."""
import bpy,json
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1];out=ROOT/'assets/pickups/battery';out.mkdir(parents=True,exist_ok=True)
bpy.ops.wm.read_factory_settings(use_empty=True)
def material(name,color):
 m=bpy.data.materials.new(name);m.diffuse_color=(*color,1);m.use_nodes=True;p=m.node_tree.nodes.get('Principled BSDF');p.inputs['Base Color'].default_value=(*color,1);p.inputs['Roughness'].default_value=.72;return m
brass=material('Weathered brass',(.55,.31,.10));body=material('Olive casing',(.20,.29,.19));cream=material('Charge marking',(.94,.83,.56));dark=material('Terminal gasket',(.10,.08,.06))
def cylinder(name,radius,depth,z,mat):
 bpy.ops.mesh.primitive_cylinder_add(vertices=12,radius=radius,depth=depth,location=(0,0,z));o=bpy.context.object;o.name=name;o.data.materials.append(mat)
def box(name,position,scale,mat):
 bpy.ops.mesh.primitive_cube_add(size=1,location=position);o=bpy.context.object;o.name=name;o.scale=scale;bpy.ops.object.transform_apply(location=False,rotation=False,scale=True);o.data.materials.append(mat)
cylinder('Lower rim',.30,.08,.04,brass);cylinder('Casing',.28,.62,.39,body);cylinder('Upper rim',.30,.10,.73,brass);cylinder('Insulator',.17,.025,.7925,dark);cylinder('Positive terminal',.11,.09,.84,brass)
for face in (-1,1):
 box('Plus horizontal',(0,face*.277,.44),(.28,.035,.065),cream);box('Plus vertical',(0,face*.277,.44),(.065,.035,.28),cream)
bpy.ops.wm.save_as_mainfile(filepath=str(out/'battery.blend'))
bpy.ops.export_scene.gltf(filepath=str(out/'battery.glb'),export_format='GLB',export_materials='EXPORT',export_yup=True)
(out/'manifest.json').write_text(json.dumps(dict(source='Original procedural mesh, scripts/bake_battery.py',editable='battery.blend',footprint=.6,height=.885,style='Twelve-sided olive/brass cell, flat facets, ordinary scene materials and shadows',source_sprite_art_used=False),indent=2)+'\n')
