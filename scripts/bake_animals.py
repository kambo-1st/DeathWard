"""Bake clean, identity-space animal rigs and all FBX takes for raylib 5.5."""
import hashlib
import json
from pathlib import Path
import re
import struct
import sys
import bpy
from mathutils import Matrix, Vector


def clip_name(take, species):
    name = re.sub(r'^'+species+r'[_ ]*', '', take, flags=re.I)
    name = re.sub(r'[^A-Za-z0-9]', '', name)
    return {'idle1': 'Idle', 'idlebreathing': 'Idle', 'eating': 'Eat'}.get(name.lower(), name)


def bake(entry, output):
    bpy.ops.wm.read_factory_settings(use_empty=True)
    scene = bpy.context.scene
    source = output/'source'
    bpy.ops.import_scene.fbx(filepath=str(source/entry['rig']), use_anim=False, use_image_search=False)
    rig = next(o for o in bpy.data.objects if o.type=='ARMATURE')
    mesh = bpy.data.objects[entry['mesh']]
    target_rig = bpy.data.objects.new('AnimalRig', rig.data.copy())
    scene.collection.objects.link(target_rig)
    target_rig.data.transform(rig.matrix_world)
    target_mesh = mesh.copy()
    target_mesh.data = mesh.data.copy()
    target_mesh.name = 'AnimalMesh'
    target_mesh.animation_data_clear()
    target_mesh.data.transform(mesh.matrix_world)
    target_mesh.parent = target_rig
    target_mesh.matrix_parent_inverse = Matrix.Identity(4)
    target_mesh.matrix_basis = Matrix.Identity(4)
    for mod in target_mesh.modifiers:
        if mod.type=='ARMATURE': mod.object=target_rig
    scene.collection.objects.link(target_mesh)
    # Unity's Standard material uses this albedo and tint, not auxiliary vertex colors.
    for color in list(target_mesh.data.color_attributes): target_mesh.data.color_attributes.remove(color)
    material = bpy.data.materials.new(entry['id'])
    material.use_nodes = True
    shader = material.node_tree.nodes.get('Principled BSDF')
    shader.inputs['Roughness'].default_value = .85
    image = bpy.data.images.load(str(source/entry['texture']))
    image.pack()
    texture = material.node_tree.nodes.new('ShaderNodeTexImage')
    texture.image = image
    material.node_tree.links.new(texture.outputs['Color'], shader.inputs['Base Color'])
    material.diffuse_color = entry['tint']
    target_mesh.data.materials.clear()
    target_mesh.data.materials.append(material)
    for poly in target_mesh.data.polygons: poly.material_index=0
    for uv in target_mesh.data.uv_layers.active.data:
        uv.uv.x=uv.uv.x*entry['uv_scale'][0]+entry['uv_offset'][0]
        uv.uv.y=uv.uv.y*entry['uv_scale'][1]+entry['uv_offset'][1]
    for obj in list(bpy.data.objects):
        if obj not in (target_mesh,target_rig): bpy.data.objects.remove(obj,do_unlink=True)
    before=set(bpy.data.objects)
    bpy.ops.import_scene.fbx(filepath=str(source/entry['animation']),use_image_search=False)
    imported=set(bpy.data.objects)-before
    rig=next(o for o in imported if o.type=='ARMATURE')
    names=[b.name for b in target_rig.data.bones]
    print('BONE DIFFERENCES',entry['id'],'mesh only',set(names)-set(b.name for b in rig.data.bones),'animation only',set(b.name for b in rig.data.bones)-set(names))
    assert set(b.name for b in rig.data.bones)<=set(names), 'Animation contains unknown bones'
    actions=list(bpy.data.actions)
    takes=[a for a in actions if a.name.startswith(rig.name+'|')]
    clips={}
    details={}
    for action in takes:
        take=action.name.split('|')[1]
        name=clip_name(take,entry['id'])
        assert name not in clips, 'Duplicate normalized take'
        for obj in imported:
            matching=next((a for a in actions if a.name==obj.name+'|'+take+'|BaseLayer'),None)
            if matching: obj.animation_data_create().action=matching
        rig.animation_data.action=action
        first,last=[int(round(v)) for v in action.frame_range]
        samples={name:[] for name in names}
        root=next(b.name for b in target_rig.data.bones if b.parent is None)
        # Bake all animated ancestors and normalize scene-unit scale exactly once.
        for frame in range(first,last+1):
            scene.frame_set(frame)
            unit_scale=rig.matrix_world.decompose()[2]
            world={}
            for bone in target_rig.data.bones:
                if bone.name in rig.pose.bones:
                    loc,rotation,scale=(rig.matrix_world @ rig.pose.bones[bone.name].matrix).decompose()
                    world[bone.name]=Matrix.LocRotScale(loc,rotation,Vector([scale[k]/unit_scale[k] for k in range(3)]))
                else:
                    assert bone.parent, 'An unanimated root cannot be retargeted'
                    world[bone.name]=world[bone.parent.name] @ bone.parent.matrix_local.inverted() @ bone.matrix_local
            rest=target_rig.data.bones[root].matrix_local.translation
            delta=world[root].translation-rest
            in_place=Matrix.Translation(Vector((-delta.x,-delta.y,0)))
            world={bone:in_place @ matrix for bone,matrix in world.items()}
            for bone in target_rig.data.bones:
                rest=bone.matrix_local
                desired=world[bone.name]
                if bone.parent:
                    rest=bone.parent.matrix_local.inverted() @ rest
                    desired=world[bone.parent.name].inverted() @ desired
                loc,rotation,scale=(rest.inverted() @ desired).decompose()
                prior=samples[bone.name]
                if prior and rotation.dot(prior[-1][1])<0: rotation.negate()
                prior.append((loc,rotation,scale))
        clips[name]=samples
        details[name]=dict(source_take=take,frames=last-first+1,fps=scene.render.fps/scene.render.fps_base,
                           duration=(last-first)*scene.render.fps_base/scene.render.fps)
    assert 'Idle' in clips and 'Walk' in clips, list(clips)
    for obj in imported: bpy.data.objects.remove(obj,do_unlink=True)
    for action in list(bpy.data.actions): bpy.data.actions.remove(action)
    for name,samples in clips.items():
        action=bpy.data.actions.new(name)
        action.use_fake_user=True
        for bone_name,poses in samples.items():
            bone=target_rig.pose.bones[bone_name]
            bone.rotation_mode='QUATERNION'
            for component,channel,count in ((0,'location',3),(1,'rotation_quaternion',4),(2,'scale',3)):
                for axis in range(count):
                    curve=action.fcurves.new(bone.path_from_id(channel),index=axis,action_group=bone_name)
                    curve.keyframe_points.add(len(poses))
                    values=[]
                    for frame,pose in enumerate(poses): values.extend((frame,pose[component][axis]))
                    curve.keyframe_points.foreach_set('co',values)
                    for key in curve.keyframe_points: key.interpolation='LINEAR'
        target_rig.animation_data_create()
        track=target_rig.animation_data.nla_tracks.new()
        track.name=name
        track.strips.new(name,0,action)
        track.mute=True
    target_rig.animation_data.action=None
    bpy.ops.object.select_all(action='DESELECT')
    target_rig.select_set(True);target_mesh.select_set(True)
    bpy.context.view_layer.objects.active=target_rig
    scene.frame_set(0)
    path=output/(entry['id']+'.glb')
    bpy.ops.export_scene.gltf(filepath=str(path),export_format='GLB',use_selection=True,
        export_yup=True,export_animations=True,export_animation_mode='ACTIONS',export_force_sampling=True,
        export_anim_slide_to_zero=True,export_frame_range=False,export_skins=True,export_def_bones=False,
        export_all_influences=False,export_morph=False,export_cameras=False,export_lights=False)
    # A linked Blender base-color texture hides material.diffuse_color from the exporter.
    # Preserve Unity's separate albedo multiplier explicitly, without altering texture pixels.
    blob=path.read_bytes()
    json_size=struct.unpack_from('<I',blob,12)[0]
    document=json.loads(blob[20:20+json_size])
    for mat in document['materials']:
        mat['pbrMetallicRoughness']['baseColorFactor']=entry['tint']
    encoded=json.dumps(document,separators=(',',':')).encode()
    encoded+=b' '*((-len(encoded))%4)
    tail=blob[20+json_size:]
    path.write_bytes(struct.pack('<III',0x46546c67,2,20+len(encoded)+len(tail))+
                     struct.pack('<II',len(encoded),0x4e4f534a)+encoded+tail)
    return dict(clips=details,bones=len(names),texture=entry['texture'],texture_size=list(image.size),
                vertices=len(target_mesh.data.vertices),output_sha256=hashlib.sha256(path.read_bytes()).hexdigest())


def main():
    recipe_path=Path(sys.argv[sys.argv.index('--')+1])
    recipe=json.loads(recipe_path.read_text())
    manifest=dict(format=1,blender=bpy.app.version_string,source_sha256=recipe['source_sha256'],animals={})
    for entry in recipe['animals']:
        manifest['animals'][entry['id']]=bake(entry,recipe_path.parent)
        print('BAKED ANIMAL',entry['id'],manifest['animals'][entry['id']])
    (recipe_path.parent/'animals.manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')

if __name__=='__main__': main()
