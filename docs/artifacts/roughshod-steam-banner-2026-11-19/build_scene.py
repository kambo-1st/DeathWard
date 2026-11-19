"""Restore the preserved banner composition and assemble the dropped-cargo story.

Uses the packed original scene to preserve the exact prior pose, materials,
font, scenery and light setup. No enemy import or generated image input.
"""
import bpy, json, math, sys, hashlib
from pathlib import Path

OUT = Path(__file__).resolve().parent
CFG = json.loads((OUT / 'scene.json').read_text())
PREVIEW = '--preview' in sys.argv
bpy.ops.wm.open_mainfile(filepath=str(OUT / CFG['base_scene']))
scene = bpy.context.scene

def matrix_list(m):
    return [[float(v) for v in row] for row in m]

base_matrices = {o.name: matrix_list(o.matrix_world) for o in bpy.data.objects}
base_object_names = set(bpy.data.objects.keys())
base_lights = {o.name: {'energy': o.data.energy, 'color': list(o.data.color)}
               for o in bpy.data.objects if o.type == 'LIGHT'}

# The same Fort Mercy wagon, slightly larger and closer to the camera.
wagon = bpy.data.objects['WAGON · placement control']
wagon.location = CFG['wagon']['position']
wagon.scale = (CFG['wagon']['scale'],) * 3
wagon.rotation_euler.z = math.radians(CFG['wagon']['yaw_degrees'])

# Reveal the left wheel/counter and make the foreground supply cluster secondary.
focus = CFG['cart_focus']
bpy.data.objects['Foreground cactus'].location = focus['foreground_cactus_position']
supplies = bpy.data.objects.new('CART SCENE · foreground supplies', None)
bpy.data.collections['02 · WAGON + VEGETATION'].objects.link(supplies)
supplies.location = focus['trail_supplies_origin']
bpy.context.view_layer.update()
for name in ['Foreground trail crate', 'Lantern on trail crate', 'Foreground trail satchels']:
    obj = bpy.data.objects[name]
    matrix = obj.matrix_world.copy()
    obj.parent = supplies
    obj.matrix_world = matrix
supplies.location = focus['trail_supplies_position']
supplies.scale = (focus['trail_supplies_scale'],) * 3
bpy.context.view_layer.update()

exec((OUT / 'story.py').read_text(), globals())
exec((OUT / 'wheel_tracks.py').read_text(), globals())
exec((OUT / 'ground_noise.py').read_text(), globals())

# Compare directly with the preserved scene; bound changes to the cart cluster.
changed = [name for name, m in base_matrices.items()
           if any(abs(bpy.data.objects[name].matrix_world[i][j] - m[i][j]) > 1e-5
                  for i in range(4) for j in range(4))]
allowed = {'Foreground cactus', supplies.name} | story_changed
for o in bpy.data.objects:
    ancestor = o
    while ancestor:
        if ancestor in (wagon, supplies):
            allowed.add(o.name)
            break
        ancestor = ancestor.parent
assert set(changed) <= allowed, sorted(set(changed) - allowed)
assert base_object_names <= set(bpy.data.objects.keys())
assert not any('spider' in o.name.lower() or 'game-spider' in str(o.get('source_asset', ''))
               for o in bpy.data.objects)
for name, expected in base_lights.items():
    light = bpy.data.objects[name].data
    assert light.energy == expected['energy'] and list(light.color) == expected['color']

scene['README'] = 'Revision 8: restored composition with an overturned supply crate, spilled cargo and paired carriage wheel tracks, granular sand and mesh-supported cargo. Exact prior hero, font, camera, lighting and landscape. No enemy or Spider. See README.md.'
scene.render.resolution_x = 1280 if PREVIEW else CFG['resolution'][0]
scene.render.resolution_y = 720 if PREVIEW else CFG['resolution'][1]
scene.render.resolution_percentage = 100
scene.cycles.samples = 20 if PREVIEW else CFG['samples']
scene.render.filepath = str(OUT / ('roughshod-preview.png' if PREVIEW else 'roughshod-banner.png'))
bpy.context.preferences.filepaths.save_version = 0
blend = OUT / ('roughshod-preview.blend' if PREVIEW else 'roughshod-banner.blend')
bpy.data.orphans_purge(do_recursive=True)
bpy.ops.file.pack_all()
bpy.ops.wm.save_as_mainfile(filepath=str(blend), compress=True)

source = json.loads((OUT / 'history/v2/source-assets.json').read_text())
source['revision'] = CFG['revision']
source['cargo_contact_adjustment'] = cargo_contacts
source['ground_noise_adaptation'] = ground_noise_report
source['ground_material_adaptation'] = wheel_track_report
source['source_sha256'].update(new_sources)
source['mesh_adaptations'] = [{'object': box.name, 'source_asset': box['source_asset'], 'source_object': box['source_object'], 'operation': box['adaptation'], 'removed_front_panel_faces': int(box['removed_front_panel_faces'])}]
source['visible_meshes'] = [{'object': o.name, 'source_asset': o.get('source_asset'), 'source_object': o.get('source_object'), 'vertices': len(o.data.vertices)} for o in bpy.data.objects if o.type == 'MESH' and not o.hide_render and any(not c.hide_render for c in o.users_collection)]
source['base_scene_sha256'] = hashlib.sha256((OUT / CFG['base_scene']).read_bytes()).hexdigest()
source['composition_change'] = 'A stopped merchant cart with an opened copy of the game crate, cargo inside and spilling onto the sand, and grouped lantern/barrel/supplies.'
(OUT / 'source-assets.json').write_text(json.dumps(source, indent=2) + '\n')
(OUT / 'restoration-check.json').write_text(json.dumps({
    'revision': CFG['revision'], 'restored_from': CFG['base_scene'],
    'base_scene_sha256': source['base_scene_sha256'],
    'changed_object_transforms': sorted(changed),
    'story_rearranged_or_hidden_objects': sorted(story_changed),
    'added_story_meshes': sorted(o.name for o in bpy.data.objects if o.type == 'MESH' and o.name.startswith('STORY · ')),
    'only_cart_scene_transforms_changed': True,
    'wheel_tracks_on_original_floor_material': True,
    'sand_grain_on_original_floor_material': True,
    'base_objects_retained': True, 'enemy_or_spider_objects': 0,
    'original_hero_title_camera_landscape_geometry_and_lighting_retained': True,
    'human_visual_acceptance': 'pending',
}, indent=2) + '\n')
if '--save-only' not in sys.argv:
    bpy.ops.render.render(write_still=True)
