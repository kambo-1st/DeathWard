"""Retarget original Western passenger meshes to the retained animated Bandit rig.
Run with Blender 3.6. Original embedded atlas, Idle and Walk clips are retained.
"""
from pathlib import Path
import bpy
from mathutils import Matrix
ROOT=Path(__file__).resolve().parents[1]
SOURCE=Path('/mnt/c/Users/bohus/My project (1)/Assets/PolygonWestern/Models/Characters.fbx')
OUT=ROOT/'assets/cinematic_cast'

def export(name,mesh_name):
    bpy.ops.wm.read_factory_settings(use_empty=True)
    bpy.ops.import_scene.gltf(filepath=str(ROOT/'assets/bandit/bandit.glb'))
    rig=next(o for o in bpy.data.objects if o.type=='ARMATURE')
    oldmesh=next(o for o in bpy.data.objects if o.type=='MESH')
    material=oldmesh.data.materials[0]
    for track in list(rig.animation_data.nla_tracks):
        clip=track.name.split('_')[0]
        if clip not in ['Idle','Walk']:rig.animation_data.nla_tracks.remove(track)
        else:
            track.name=clip
            for strip in track.strips:strip.name=clip;strip.action.name=clip
    rig.animation_data.action=None
    before=set(bpy.data.objects)
    bpy.ops.import_scene.fbx(filepath=str(SOURCE),use_image_search=False)
    imported=set(bpy.data.objects)-before
    source=bpy.data.objects[mesh_name]
    mesh=source.copy();mesh.data=source.data.copy();mesh.name=name
    mesh.data.transform(source.matrix_world)
    mesh.parent=rig;mesh.matrix_parent_inverse=Matrix.Identity(4);mesh.matrix_basis=Matrix.Identity(4)
    mesh.animation_data_clear();mesh.data.materials.clear();mesh.data.materials.append(material)
    # Unity-specific vertex masks are not surface opacity in the runtime shader.
    for attribute in list(mesh.data.color_attributes):mesh.data.color_attributes.remove(attribute)
    for poly in mesh.data.polygons:poly.material_index=0
    for group in mesh.vertex_groups:
        if group.name.endswith('.001'):group.name=group.name[:-4]+'_1'
    unbound=[g.name for g in mesh.vertex_groups if g.name not in rig.data.bones
             and any(w.group==g.index and w.weight>0 for v in mesh.data.vertices for w in v.groups)]
    if unbound:raise RuntimeError(f'{name}: weighted groups missing from retained rig: {unbound}')
    for modifier in mesh.modifiers:
        if modifier.type=='ARMATURE':modifier.object=rig
    bpy.context.scene.collection.objects.link(mesh)
    for obj in imported:bpy.data.objects.remove(obj,do_unlink=True)
    bpy.data.objects.remove(oldmesh,do_unlink=True)
    # Grey side hair/moustache and a muted dress make the two travellers read older.
    # Preserve the source atlas; only selected hair faces receive a grey material.
    hair=bpy.data.materials.new('Silver hair');hair.diffuse_color=(.53,.51,.47,1);hair.use_nodes=True
    hair.node_tree.nodes.get('Principled BSDF').inputs['Base Color'].default_value=(.53,.51,.47,1)
    mesh.data.materials.append(hair)
    image=next(n.image for n in material.node_tree.nodes if n.type=='TEX_IMAGE')
    pixels=list(image.pixels);w,h=image.size
    if name!='conductor':
        for poly in mesh.data.polygons:
            center=sum((mesh.data.vertices[i].co for i in poly.vertices),mesh.data.vertices[poly.vertices[0]].co*0)/len(poly.vertices)
            uv=mesh.data.uv_layers.active.data[poly.loop_start].uv;x=min(w-1,max(0,int(uv.x*w)));y=min(h-1,max(0,int(uv.y*h)))
            r,g,b=pixels[(y*w+x)*4:(y*w+x)*4+3]
            dark_hair=r<.32 and g<.25 and b<.22
            auburn_hair=name=='elder_woman' and r<.65 and r>g*1.6 and g<.3 and b<.22
            if 1.22<center.z<1.68 and (dark_hair or auburn_hair):poly.material_index=1
    if name=='conductor':
        uniform=bpy.data.materials.new('Railway navy');uniform.use_nodes=True
        uniform.node_tree.nodes.get('Principled BSDF').inputs['Base Color'].default_value=(.035,.065,.11,1)
        mesh.data.materials.append(uniform)
        for poly in mesh.data.polygons:
            center=sum((mesh.data.vertices[i].co for i in poly.vertices),mesh.data.vertices[poly.vertices[0]].co*0)/len(poly.vertices)
            uv=mesh.data.uv_layers.active.data[poly.loop_start].uv;x=min(w-1,max(0,int(uv.x*w)));y=min(h-1,max(0,int(uv.y*h)))
            r,g,b=pixels[(y*w+x)*4:(y*w+x)*4+3]
            if center.z>1.68 or (.85<center.z<1.35 and max(r,g,b)<.33):poly.material_index=2
        for v in mesh.data.vertices:
            if v.co.z>1.68:
                v.co.x*=.78;v.co.y*=.78;v.co.z=1.68+(v.co.z-1.68)*.50
    for image in bpy.data.images:
        if image.size[0] and not image.packed_file:image.pack()
    bpy.ops.object.select_all(action='DESELECT');rig.select_set(True);mesh.select_set(True);bpy.context.view_layer.objects.active=rig
    bpy.context.scene.frame_set(0)
    bpy.ops.export_scene.gltf(filepath=str(OUT/(name+'.glb')),export_format='GLB',use_selection=True,export_animations=True,export_animation_mode='NLA_TRACKS',export_force_sampling=True,export_frame_range=False,export_skins=True,export_def_bones=False,export_morph=False)
    print('EXPORTED',name,len(mesh.data.vertices),'vertices')
OUT.mkdir(parents=True,exist_ok=True)
for name,mesh in [('elder_man','Character_Business_Man_01'),('elder_woman','Character_Woman_01'),('conductor','Character_Business_Man_01')]:export(name,mesh)
