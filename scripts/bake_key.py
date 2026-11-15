"""Blender: bake owned Synty key with its prefab albedo, UVs and proportions."""
import bpy,json,hashlib
from pathlib import Path
from mathutils import Matrix,Vector
ROOT=Path(__file__).resolve().parents[1]
OUT=ROOT/'assets/pickups/key'
bpy.ops.wm.read_factory_settings(use_empty=True)
bpy.ops.import_scene.fbx(filepath=str(OUT/'source/SM_Gen_Prop_Key_01.fbx'),use_image_search=False,use_anim=False)
meshes=[o for o in bpy.data.objects if o.type=='MESH']
assert len(meshes)==1
obj=meshes[0];obj.data.transform(obj.matrix_world);obj.parent=None;obj.matrix_world=Matrix.Identity(4)
lo=Vector([min(v.co[i] for v in obj.data.vertices) for i in range(3)])
hi=Vector([max(v.co[i] for v in obj.data.vertices) for i in range(3)])
print('SOURCE_BOUNDS',tuple(lo),tuple(hi))
# Bake a broad face upright (glTF XY); preserve source proportions and UVs.
axes=sorted(range(3),key=lambda i:hi[i]-lo[i],reverse=True)
center=(lo+hi)*.5;length=hi[axes[0]]-lo[axes[0]]
# Blender Z-up -> glTF Y-up: long X, broad Z, thin -Y.
transform=Matrix(((0,0,0),(0,0,0),(0,0,0)))
transform[0][axes[0]]=1;transform[2][axes[1]]=1;transform[1][axes[2]]=-1
if transform.determinant()<0:transform[1][axes[2]]=1
for v in obj.data.vertices:v.co=transform@(v.co-center)/length
mat=bpy.data.materials.new('Generic_01_A');mat.use_nodes=True
shader=mat.node_tree.nodes.get('Principled BSDF');shader.inputs['Metallic'].default_value=0;shader.inputs['Roughness'].default_value=.8
tex=mat.node_tree.nodes.new('ShaderNodeTexImage');tex.image=bpy.data.images.load(str(OUT/'source/Generic_01_A.png'));tex.image.pack()
mat.node_tree.links.new(tex.outputs['Color'],shader.inputs['Base Color'])
obj.data.materials.clear();obj.data.materials.append(mat)
bpy.ops.object.select_all(action='DESELECT');obj.select_set(True);bpy.context.view_layer.objects.active=obj
bpy.ops.export_scene.gltf(filepath=str(OUT/'key.glb'),export_format='GLB',use_selection=True,export_yup=True,export_animations=False)
m=json.loads((OUT/'manifest.json').read_text());m['output_sha256']=hashlib.sha256((OUT/'key.glb').read_bytes()).hexdigest();m['vertices']=len(obj.data.vertices);m['triangles']=sum(len(p.vertices)-2 for p in obj.data.polygons);m['source_bounds']=[list(lo),list(hi)];m['dimensions']=[1,(hi[axes[1]]-lo[axes[1]])/length,(hi[axes[2]]-lo[axes[2]])/length]
(OUT/'manifest.json').write_text(json.dumps(m,indent=2)+'\n')
