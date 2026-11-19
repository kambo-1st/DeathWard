"""Run against a relocated saved .blend; verify editability and packed resources."""
import bpy,json,hashlib,sys
from mathutils import Vector
from pathlib import Path
OUT=Path(__file__).resolve().parent
scene=bpy.context.scene
main=bpy.data.objects['ROUGHSHOD · EDIT THIS TEXT'];shadow=bpy.data.objects['Title shadow']
assert main.type=='FONT' and main.data.body=='ROUGHSHOD' and shadow.data==main.data
main.data.body='EDITABLE TITLE CHECK';assert shadow.data.body=='EDITABLE TITLE CHECK';main.data.body='ROUGHSHOD'
assert main.data.font.packed_file is not None
font_hash=hashlib.sha256(bytes(main.data.font.packed_file.data)).hexdigest()
assert font_hash=='8a959b9e8bbaed9dbd02e3dc284389c303ae6ee358b0a5d9102b270a75be8ae9'
assert all(n not in bpy.data.objects for n in ['Left near canyon','Left middle shelf','Front sandstone'])
images=[im for im in bpy.data.images if im.source=='FILE' and im.users]
assert images and all(im.packed_file is not None for im in images)
meshes=[o for o in bpy.data.objects if o.type=='MESH' and any(not c.hide_render for c in o.users_collection)]
assert meshes and all(o.get('source_asset') and o.get('source_object') for o in meshes)
rig=bpy.data.objects['GUNSLINGER · original 48-bone rig'];assert rig.type=='ARMATURE' and len(rig.data.bones)==48
assert bpy.data.objects['REVOLVER · hand attachment'].parent_bone=='Hand_R'
assert not any('spider' in o.name.lower() or 'game-spider' in str(o.get('source_asset','')) for o in bpy.data.objects)
assert bpy.data.objects['STORY · tipped crate and cargo'].type=='EMPTY'
box=bpy.data.objects['STORY · overturned open supply crate']
assert box['source_asset']=='assets/western/western.glb' and box['removed_front_panel_faces']>10
assert box.modifiers.get('EDITABLE · wooden wall thickness') is not None
assert max(box.dimensions)<2.5
assert abs(min((box.matrix_world@Vector(v)).z for v in box.bound_box))<.05
assert len([o for o in meshes if o.name.startswith('STORY · spilled supply sack')])==8
track=bpy.data.objects['WHEEL TRACKS · path control']
assert track.parent==bpy.data.objects['WAGON · placement control']
ground=bpy.data.objects['Sand floor / source atlas']
assert ground.active_material.node_tree.nodes.get('Wheel ruts · shallow editable relief')
assert ground.active_material.node_tree.nodes['Coordinates following cart'].object==track
sand=ground.active_material.node_tree.nodes['Sand grain · subtle relief']
assert ground.active_material.node_tree.nodes['Wheel ruts · shallow editable relief'].inputs['Normal'].links[0].from_node==sand
assert ground.active_material.node_tree.nodes['Wheel ruts · compressed sand color'].inputs[1].links[0].from_node.name=='Sand · visible fine grain'
assert len(bpy.data.libraries)==0 and scene.camera.type=='CAMERA'
assert [scene.render.resolution_x,scene.render.resolution_y]==[2560,1440] and scene.cycles.samples==64
source=json.loads((OUT/'source-assets.json').read_text())
root=OUT.parents[2]
for name,digest in source['source_sha256'].items():assert hashlib.sha256((root/name).read_bytes()).hexdigest()==digest
# Recheck the actual saved meshes rather than trusting the build-time report.
exec((OUT/'cargo_contacts.py').read_text(), globals())
expected=json.loads((OUT/'cargo-contacts.json').read_text())
assert expected['revision']==8
sacks=[bpy.data.objects[f'STORY · spilled supply sack {i:02}'] for i in range(1,9)]
deck=('crate interior floor',cargo_surface(box,crate_deck=True)[0])
sand_support=(ground.name,cargo_surface(ground)[0])
for i,obj in enumerate(sacks):
    supports=[deck] if i<2 else ([(o.name,cargo_surface(o)[0]) for o in sacks[:2]] if i==2 else [sand_support,deck])
    contact=cargo_contact_gap(obj,supports)
    assert abs(contact['gap']+(.004 if i<3 else .006))<.001, (obj.name,contact)
    assert contact['support']==expected['sacks'][i]['support']

# Deliberately invalidate paths in memory. Packed images and fonts must render.
for im in images:im.filepath='/unavailable-source/'+im.name
main.data.font.filepath='/unavailable-source/display.otf'
scene.render.resolution_x=256;scene.render.resolution_y=144;scene.cycles.samples=4
scene.render.filepath='/tmp/roughshod-portability-probe.png';bpy.ops.render.render(write_still=True)
assert Path(scene.render.filepath).stat().st_size>1000
result={'revision':8,'game_font_exact_sha256':font_hash,'left_edge_cliff_and_stone_removed':True,'restored_from':'history/v2/roughshod-banner.blend','enemy_or_spider_objects':0,'composition_change':'sacks settled on actual sand, crate floor and lower cargo surfaces; sand, wheel tracks and composition retained','cargo_contacts_rechecked_from_saved_meshes':True,'hand_fit':'palm-aligned original gun, outward wrist, curled index; visually reviewed in close-up','title':'ROUGHSHOD','render_resolution':[2560,1440],'render_samples':64,'editable_font_objects':2,'shared_title_shadow':True,'rig_bones':48,'visible_repo_mesh_instances':len(meshes),'packed_used_images':len(images),'packed_font':True,'external_linked_libraries':0,'source_asset_hashes_unchanged':True,'relocated_blend_opens':True,'render_with_invalidated_external_image_font_paths':True,'generated_bitmap_inputs':0,'human_visual_acceptance':'pending','steam_crop_package':'not yet prepared'}
(OUT/'verification.json').write_text(json.dumps(result,indent=2)+'\n')
print('PASS editable title/linked shadow, rig, original mesh provenance, packed images/font, source hashes and relocated render')
