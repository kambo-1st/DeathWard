"""A dropped supply crate at the original trading cart, using existing assets."""
from mathutils import Vector, Euler
ROOT = OUT.parents[2]
props = bpy.data.collections['02 · WAGON + VEGETATION']
story_changed = set()
new_sources = {}

def grounded(obj):
    bpy.context.view_layer.update()
    obj.location.z -= min((obj.matrix_world @ Vector(v)).z for v in obj.bound_box)
    return obj

def place_existing(name, pos, scale=None, yaw=None):
    obj = bpy.data.objects[name]
    matrix = obj.matrix_world.copy()
    obj.parent = None
    obj.matrix_world = matrix
    obj.location = pos
    if scale is not None: obj.scale = (scale,) * 3
    if yaw is not None:
        obj.rotation_mode = 'XYZ'
        obj.rotation_euler = (0, 0, math.radians(yaw))
    story_changed.add(name)
    return obj

# Supporting objects form one stopped merchant's unloading area.
place_existing('Wagon supply barrel', (-1.9, 7.8, 0), 1.0, 10)
place_existing('Lantern on barrel', (-1.9, 7.8, 1.17), .8, 10)
place_existing('Supply crate lower', (-.65, 8.1, 0), 1.0, -7)
place_existing('Canvas supply sacks', (-1.55, 6.5, 0), .65, 8)
place_existing('Foreground trail crate', (-4.5, 4.5, 0), .65, -8)
place_existing('Lantern on trail crate', (-4.5, 4.5, .549), .85, -8)
place_existing('Trail skull', (.05, 5.0, 0), .8, -15)
place_existing('Bones near trail skull', (.25, 5.55, 0), .4, 30)
for name in ['Supply crate upper', 'Wagon spare barrel', 'Foreground trail satchels', 'Supply corner bush', 'Supply corner grass', 'Trail stones A', 'Trail stones B', 'Trail stones grass']:
    bpy.data.objects[name].hide_render = True
    bpy.data.objects[name].hide_viewport = True
    story_changed.add(name)
# Remove random plant/stone interruptions inside the local spill area only.
for obj in list(props.objects):
    if ' · ' in obj.name and obj.type == 'MESH':
        x, y = obj.matrix_world.translation.xy
        if -5.0 < x < .8 and 2.6 < y < 8.3:
            obj.hide_render = True
            obj.hide_viewport = True
            story_changed.add(obj.name)

# Import individual source cloth sacks for the visible spill.
asset = 'assets/town/town.glb'
path = ROOT / asset
new_sources[asset] = hashlib.sha256(path.read_bytes()).hexdigest()
before = set(bpy.data.objects)
bpy.ops.import_scene.gltf(filepath=str(path))
imported = list(set(bpy.data.objects) - before)
keep = {}
for obj in imported:
    key = obj.name.split('.')[0]
    if obj.type == 'MESH' and key in ['part_0271']:
        keep[key] = obj
        for coll in list(obj.users_collection): coll.objects.unlink(obj)
        props.objects.link(obj)
        obj['source_asset'] = asset
        obj['source_object'] = key
    else:
        bpy.data.objects.remove(obj, do_unlink=True)
for obj in keep.values():
    for mat in obj.data.materials:
        if mat and mat.use_nodes:
            for node in mat.node_tree.nodes:
                if node.type == 'BSDF_PRINCIPLED':
                    node.inputs['Roughness'].default_value = .88
                    node.inputs['Metallic'].default_value = 0

# Open a copy of the existing wooden crate, preserving its plank/frame geometry
# and UV atlas. Game asset files and other crate instances are untouched.
import bmesh
original = bpy.data.objects['crate']
box = original.copy()
box.data = original.data.copy()
props.objects.link(box)
box.name = 'STORY · overturned open supply crate'
bm = bmesh.new()
bm.from_mesh(box.data)
front_panel = [face for face in bm.faces
               if face.calc_center_median().y < -.30
               and abs(face.calc_center_median().x) < .34
               and .09 < face.calc_center_median().z < .755]
removed_faces = len(front_panel)
assert removed_faces > 10
bmesh.ops.delete(bm, geom=front_panel, context='FACES')
bm.to_mesh(box.data)
bm.free()
box.data.update()
interior = box.modifiers.new('EDITABLE · wooden wall thickness', 'SOLIDIFY')
interior.thickness = .015
interior.offset = -1
interior.use_even_offset = False
interior.thickness_clamp = .5
box.rotation_mode = 'XYZ'
box.location = CFG['cart_story']['crate_position']
box.rotation_euler = Euler(tuple(math.radians(v) for v in CFG['cart_story']['crate_rotation_degrees']))
box.scale = CFG['cart_story']['crate_scale']
grounded(box)
box['source_object'] = 'crate'
box['adaptation'] = 'Opened front planks on a copy of the original game crate; retained source frame/UVs; editable inward Solidify for interior walls.'
box['removed_front_panel_faces'] = removed_faces

# Cloth packages inside the opening and a short, irregular spill into the sand.
exec((OUT / 'cargo_contacts.py').read_text(), globals())
ground = bpy.data.objects['Sand floor / source atlas']
ground_support = (ground.name, cargo_surface(ground)[0])
deck_support = ('crate interior floor', cargo_surface(box, crate_deck=True)[0])
cargo_contacts = []
placed_sacks = []
sack = keep['part_0271']
spill = CFG['cart_story']['spill']
for i, entry in enumerate(spill):
    obj = sack if i == 0 else sack.copy()
    if i: props.objects.link(obj)
    obj.name = f'STORY · spilled supply sack {i + 1:02}'
    obj.rotation_mode = 'XYZ'
    obj.location = entry['position']
    obj.scale = tuple(entry['scale'])
    obj.rotation_euler = Euler(tuple(math.radians(v) for v in entry['rotation_degrees']))
    bpy.context.view_layer.update()
    if i < 2:
        supports = [deck_support]
    elif i == 2:
        supports = [(other.name, cargo_surface(other)[0]) for other in placed_sacks]
    else:
        supports = [ground_support, deck_support]
    cargo_contacts.append(settle_cargo(obj, supports, .004 if i < 3 else .006))
    placed_sacks.append(obj)
    obj['story_role'] = 'cargo inside tipped crate' if i < 3 else 'fallen cargo continuing out of the opening'

# Every added object stays individually editable under an optional story control.
control = bpy.data.objects.new('STORY · tipped crate and cargo', None)
props.objects.link(control)
control.location = box.location.copy()
bpy.context.view_layer.update()
(OUT / 'cargo-contacts.json').write_text(json.dumps({
    'revision': CFG['revision'],
    'method': 'Mesh underside / support-surface vertical sampling; 70x70 grid plus mesh vertices. Tiny cloth/sand embed for firm visible contact.',
    'sacks': cargo_contacts,
    'human_visual_acceptance': 'pending',
}, indent=2) + '\n')
for obj in list(props.objects):
    if obj.type == 'MESH' and obj.name.startswith('STORY · '):
        matrix = obj.matrix_world.copy()
        obj.parent = control
        obj.matrix_world = matrix
bpy.context.view_layer.update()
