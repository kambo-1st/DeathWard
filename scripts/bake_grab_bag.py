"""Bake the owned Western single sack, preserving prefab albedo/UVs."""
import bpy,json,hashlib
from pathlib import Path
from mathutils import Matrix,Vector
ROOT=Path(__file__).resolve().parents[1];OUT=ROOT/'assets/pickups/grab-bag';OUT.mkdir(parents=True,exist_ok=True)
bpy.ops.wm.read_factory_settings(use_empty=True)
texture=ROOT/'assets/town/source/Textures/PolygonWestern_Texture_01_A.png'
mat=bpy.data.materials.new('PolygonWestern_Material_01_A');mat.use_nodes=True
shader=mat.node_tree.nodes.get('Principled BSDF');shader.inputs['Roughness'].default_value=.85
tex=mat.node_tree.nodes.new('ShaderNodeTexImage');tex.image=bpy.data.images.load(str(texture));tex.image.pack();mat.node_tree.links.new(tex.outputs['Color'],shader.inputs['Base Color'])
sources=[];baseHeight=0
for name,width in [('SM_Prop_Sack_01',.8)]:
 source=ROOT/'assets/town/source/Models'/f'{name}.fbx';old=set(bpy.data.objects)
 bpy.ops.import_scene.fbx(filepath=str(source),use_image_search=False,use_anim=False)
 objects=[o for o in bpy.data.objects if o not in old and o.type=='MESH']
 points=[o.matrix_world@v.co for o in objects for v in o.data.vertices]
 lo=Vector([min(v[i] for v in points) for i in range(3)]);hi=Vector([max(v[i] for v in points) for i in range(3)])
 scale=width/max(hi.x-lo.x,hi.y-lo.y);center=Vector(((lo.x+hi.x)/2,(lo.y+hi.y)/2,lo.z))
 for o in objects:
  world=o.matrix_world.copy();o.parent=None;o.matrix_world=Matrix.Identity(4)
  for v in o.data.vertices:v.co=(world@v.co-center)*scale+Vector((0,0,baseHeight))
  o.data.materials.clear();o.data.materials.append(mat)
 baseHeight+=(hi.z-lo.z)*scale
 sources.append(dict(path=str(source.relative_to(ROOT)),sha256=hashlib.sha256(source.read_bytes()).hexdigest()))
bpy.ops.object.select_all(action='DESELECT')
for o in bpy.data.objects:
 if o.type=='MESH':o.select_set(True)
bpy.ops.wm.save_as_mainfile(filepath=str(OUT/'grab-bag.blend'))
bpy.ops.export_scene.gltf(filepath=str(OUT/'grab-bag.glb'),export_format='GLB',use_selection=True,export_yup=True,export_animations=False)
(OUT/'manifest.json').write_text(json.dumps(dict(source='Owned Synty Polygon Western; existing game assets',sources=sources,texture=str(texture.relative_to(ROOT)),texture_sha256=hashlib.sha256(texture.read_bytes()).hexdigest(),output_sha256=hashlib.sha256((OUT/'grab-bag.glb').read_bytes()).hexdigest(),height=baseHeight,scope='Existing single sack; original proportions and UVs. Grounded, ordinary game mesh lighting/shadows.'),indent=2)+'\n')
