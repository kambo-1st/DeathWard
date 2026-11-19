"""Editable paired wheel ruts on the existing sand material; no image overlay.

The four wheel bounds come from the original assembled cart's GLB primitives.
The same local spacing continues through a straight section and a smooth bend.
"""
import struct
from mathutils import Vector

cfg = CFG['wheel_tracks']
ground = bpy.data.objects['Sand floor / source atlas']
raw = (ROOT / 'assets/props/shop-cart/shop-cart.glb').read_bytes()
json_size = struct.unpack_from('<I', raw, 12)[0]
gltf = json.loads(raw[20:20 + json_size])
wheel_bounds = []
for primitive in gltf['meshes'][0]['primitives']:
    accessor = gltf['accessors'][primitive['attributes']['POSITION']]
    lo, hi = accessor['min'], accessor['max']
    span = [b - a for a, b in zip(lo, hi)]
    # These four vertical, thin round wheel meshes are the source assembly's
    # only primitives with almost equal X/Y dimensions and a small Z width.
    if 1.0 < span[0] < 1.3 and abs(span[0] - span[1]) < .03 and span[2] < .3:
        wheel_bounds.append({'min': lo, 'max': hi})
assert len(wheel_bounds) == 4
centers = [Vector(((v['min'][0] + v['max'][0]) / 2,
                   -(v['min'][2] + v['max'][2]) / 2, 0))
           for v in wheel_bounds]
front = sorted(centers, key=lambda v: v.x)[-2:]
center = sum(front, Vector()) / 2
gauge = max(c.y for c in centers) - min(c.y for c in centers)

controls = bpy.data.collections.new('07 · WHEEL TRACKS / editable sand material')
scene.collection.children.link(controls)
control = bpy.data.objects.new('WHEEL TRACKS · path control', None)
controls.objects.link(control)
control.parent = wagon
control.location = center
control.empty_display_type = 'ARROWS'
control.empty_display_size = .7
control['edit_note'] = 'Follows the wagon. Move/rotate this control to adjust the rut path; material values edit width, bend and fading.'
control['source_wheel_spacing'] = gauge

mat = ground.active_material.copy()
mat.name = 'SAND · original atlas + carriage wheel tracks'
ground.material_slots[0].link = 'OBJECT'
ground.material_slots[0].material = mat
nodes, links = mat.node_tree.nodes, mat.node_tree.links
frame = nodes.new('NodeFrame')
frame.name = 'WHEEL TRACKS · editable controls'
frame.label = 'CARRIAGE WHEEL TRACKS · paired shallow ruts'
index = 0

def node(kind, name):
    global index
    obj = nodes.new(kind)
    obj.name = name
    obj.label = name
    obj.parent = frame
    obj.location = ((index % 8) * 220, -(index // 8) * 230)
    index += 1
    return obj

def parameter(name, value):
    n = node('ShaderNodeValue', name)
    n.outputs[0].default_value = value
    return n.outputs[0]

def math_node(op, a, b=None, name=None):
    n = node('ShaderNodeMath', name or op)
    n.operation = op
    for i, value in enumerate((a, b)):
        if value is None: continue
        if isinstance(value, (float, int)): n.inputs[i].default_value = value
        else: links.new(value, n.inputs[i])
    return n.outputs[0]

def remap(value, lo, hi, out_lo, out_hi, name):
    n = node('ShaderNodeMapRange', name)
    n.clamp = True
    n.interpolation_type = 'SMOOTHSTEP'
    for key, value_ in [('Value', value), ('From Min', lo), ('From Max', hi),
                        ('To Min', out_lo), ('To Max', out_hi)]:
        if isinstance(value_, (float, int)): n.inputs[key].default_value = value_
        else: links.new(value_, n.inputs[key])
    return n.outputs['Result']

half_gauge = parameter('Half wheel spacing · source cart', gauge / 2)
bend = parameter('Start of bend', cfg['bend_start'])
radius = parameter('Bend radius', cfg['bend_radius'])
end = parameter('End angle · radians', math.radians(cfg['end_angle_degrees']))
fade = parameter('End fade · radians', math.radians(cfg['end_fade_degrees']))
half_width = parameter('Rut half width', cfg['half_width'])
softness = parameter('Soft sand edge', cfg['edge_softness'])
darkness = parameter('Compressed sand strength', cfg['darkness'])
coord = node('ShaderNodeTexCoord', 'Coordinates following cart')
coord.object = control
split = node('ShaderNodeSeparateXYZ', 'Along cart / across wheels')
links.new(coord.outputs['Object'], split.inputs[0])
x, y = split.outputs['X'], split.outputs['Y']

straight_d = math_node('ABSOLUTE', math_node('SUBTRACT', math_node('ABSOLUTE', y), half_gauge))
dx = math_node('SUBTRACT', x, bend)
dy = math_node('SUBTRACT', y, radius)
radial = math_node('SQRT', math_node('ADD', math_node('MULTIPLY', dx, dx), math_node('MULTIPLY', dy, dy)))
arc_d = math_node('ABSOLUTE', math_node('SUBTRACT', math_node('ABSOLUTE', math_node('SUBTRACT', radial, radius)), half_gauge))
straight_gate = math_node('LESS_THAN', x, bend)
arc_gate = math_node('GREATER_THAN', x, bend)
distance = math_node('ADD', math_node('MULTIPLY', straight_d, straight_gate), math_node('MULTIPLY', arc_d, arc_gate), 'Distance from nearest wheel rut')
theta = math_node('ARCTAN2', dx, math_node('SUBTRACT', radius, y))
end_fade = remap(theta, math_node('SUBTRACT', end, fade), end, 1, 0, 'Distant tracks fade into sand')
start_fade = remap(x, cfg['rear_start'], cfg['rear_start'] + cfg['rear_fade_length'], 0, 1, 'Tracks meet rear wheels')
gate = math_node('MULTIPLY', start_fade, math_node('ADD', straight_gate, math_node('MULTIPLY', arc_gate, end_fade)))
core = remap(distance, half_width, math_node('ADD', half_width, softness), 1, 0, 'Soft groove profile')
core = math_node('MULTIPLY', core, gate)

# Small sand variations prevent ruler-straight, uniformly painted marks.
noise = node('ShaderNodeTexNoise', 'Fine broken sand compression')
noise.inputs['Scale'].default_value = 23
noise.inputs['Detail'].default_value = 2
links.new(coord.outputs['Object'], noise.inputs['Vector'])
grain = remap(noise.outputs['Fac'], .15, .85, 1 - cfg['grain_variation'], 1, 'Subtle rut grain')
core = math_node('MULTIPLY', core, grain)
rim_center = math_node('ADD', half_width, softness)
rim_distance = math_node('ABSOLUTE', math_node('SUBTRACT', distance, rim_center))
rim = remap(rim_distance, .005, .025, 1, 0, 'Soft displaced sand rim')
rim = math_node('MULTIPLY', rim, gate)

bs = next(n for n in nodes if n.type == 'BSDF_PRINCIPLED')
base = bs.inputs['Base Color'].links[0].from_socket
mix = node('ShaderNodeMixRGB', 'Wheel ruts · compressed sand color')
mix.blend_type = 'MULTIPLY'
links.new(math_node('MULTIPLY', core, darkness), mix.inputs[0])
links.new(base, mix.inputs[1])
mix.inputs[2].default_value = (.48, .40, .30, 1)
rim_mix = node('ShaderNodeMixRGB', 'Wheel ruts · subtle sand edge')
rim_mix.blend_type = 'MULTIPLY'
links.new(math_node('MULTIPLY', rim, .25), rim_mix.inputs[0])
links.new(mix.outputs[0], rim_mix.inputs[1])
rim_mix.inputs[2].default_value = (1.13, 1.09, 1.03, 1)
links.new(rim_mix.outputs[0], bs.inputs['Base Color'])
bump = node('ShaderNodeBump', 'Wheel ruts · shallow editable relief')
bump.inputs['Distance'].default_value = cfg['rut_depth']
bump.inputs['Strength'].default_value = .55
links.new(math_node('SUBTRACT', math_node('MULTIPLY', rim, .22), core), bump.inputs['Height'])
links.new(bump.outputs['Normal'], bs.inputs['Normal'])

wheel_track_report = {
    'source_cart': 'assets/props/shop-cart/shop-cart.glb',
    'source_wheel_bounds': wheel_bounds,
    'source_wheel_spacing': gauge,
    'world_wheel_spacing': gauge * CFG['wagon']['scale'],
    'path_control': control.name,
    'material': mat.name,
    'method': 'Original sand atlas plus paired straight/curved shallow shader ruts; no image input or added mesh.',
    'configuration': cfg,
}
(OUT / 'wheel-tracks.json').write_text(json.dumps(wheel_track_report, indent=2) + '\n')
