"""Fine, editable sand texture layered under the existing carriage wheel ruts.

World-space procedural material only: preserves the source floor, UV atlas,
wheel path, composition and lighting. No bitmap overlay or new geometry.
"""
cfg = CFG['ground_noise']
ground = bpy.data.objects['Sand floor / source atlas']
mat = ground.active_material
nodes, links = mat.node_tree.nodes, mat.node_tree.links
grain_frame = nodes.new('NodeFrame')
grain_frame.name = 'SAND GRAIN · editable controls'
grain_frame.label = 'SAND GRAIN · fine grains / broad patches / shallow relief'
grain_frame.location = (0, -3000)
grain_index = 0

def sand_node(kind, name):
    global grain_index
    n = nodes.new(kind)
    n.name = name
    n.label = name
    n.parent = grain_frame
    n.location = ((grain_index % 6) * 240, -(grain_index // 6) * 250)
    grain_index += 1
    return n

def sand_value(name, value):
    n = sand_node('ShaderNodeValue', name)
    n.outputs[0].default_value = value
    return n.outputs[0]

def sand_math(op, a, b, name):
    n = sand_node('ShaderNodeMath', name)
    n.operation = op
    for i, value in enumerate((a, b)):
        if isinstance(value, (int, float)): n.inputs[i].default_value = value
        else: links.new(value, n.inputs[i])
    return n.outputs[0]

def sand_map(value, lo, hi, out_lo, out_hi, name):
    n = sand_node('ShaderNodeMapRange', name)
    n.clamp = True
    for key, item in [('Value', value), ('From Min', lo), ('From Max', hi),
                      ('To Min', out_lo), ('To Max', out_hi)]:
        if isinstance(item, (int, float)): n.inputs[key].default_value = item
        else: links.new(item, n.inputs[key])
    return n.outputs['Result']

position = sand_node('ShaderNodeNewGeometry', 'Sand · fixed world position')
camera_data = sand_node('ShaderNodeCameraData', 'Sand · distance from camera')
detail_fade = sand_map(camera_data.outputs['View Distance'], cfg['near_detail_distance'],
                       cfg['far_detail_distance'], 1, .15, 'Sand · quieter distant grain')

def sand_noise(name, scale, detail):
    n = sand_node('ShaderNodeTexNoise', name)
    links.new(position.outputs['Position'], n.inputs['Vector'])
    links.new(sand_value(name + ' scale', scale), n.inputs['Scale'])
    n.inputs['Detail'].default_value = detail
    n.inputs['Roughness'].default_value = .65
    return n.outputs['Fac']

fine = sand_noise('Sand · individual grains', cfg['grain_scale'], 2)
patch = sand_noise('Sand · broad dry patches', cfg['patch_scale'], 3)
scuff = sand_noise('Sand · smaller scuffed patches', cfg['scuff_scale'], 2)
fine_strength = sand_math('MULTIPLY', sand_value('Sand grain strength', cfg['grain_strength']),
                          detail_fade, 'Sand · distance-adjusted grain strength')
fine_centered = sand_map(fine, .25, .75, -1, 1, 'Sand · balanced light and dark grains')
fine_factor = sand_math('ADD', 1, sand_math('MULTIPLY', fine_centered, fine_strength,
                       'Sand · grain contrast'), 'Sand · grain multiplier')
scuff_factor = sand_map(scuff, .2, .8, 1 - cfg['scuff_strength'],
                        1 + cfg['scuff_strength'], 'Sand · subtle scuff multiplier')

# Insert color variation before the wheel-track mix, preserving the original
# atlas and keeping the existing grooves/rims on top of the sand texture.
wheel_color = nodes['Wheel ruts · compressed sand color']
base = wheel_color.inputs[1].links[0].from_socket
patch_tint = sand_node('ShaderNodeMixRGB', 'Sand · warm patch tones')
links.new(patch, patch_tint.inputs[0])
patch_tint.inputs[1].default_value = (.78, .74, .67, 1)
patch_tint.inputs[2].default_value = (1.22, 1.22, 1.21, 1)

def multiply_color(name, color, factor, strength=1):
    n = sand_node('ShaderNodeMixRGB', name)
    n.blend_type = 'MULTIPLY'
    n.inputs[0].default_value = strength
    links.new(color, n.inputs[1])
    links.new(factor, n.inputs[2])
    return n.outputs[0]

patch_color = multiply_color('Sand · original atlas with dry patches', base,
                             patch_tint.outputs[0], cfg['patch_strength'])
scuff_color = multiply_color('Sand · uneven worn surface', patch_color, scuff_factor, .5)
fine_color = multiply_color('Sand · visible fine grain', scuff_color, fine_factor)
links.new(fine_color, wheel_color.inputs[1])

bs = next(n for n in nodes if n.type == 'BSDF_PRINCIPLED')
roughness = sand_map(fine, .2, .8, .82, .98, 'Sand · matte grain roughness')
links.new(roughness, bs.inputs['Roughness'])
bump = sand_node('ShaderNodeBump', 'Sand grain · subtle relief')
bump.inputs['Distance'].default_value = cfg['bump_depth']
links.new(sand_math('MULTIPLY', detail_fade, cfg['bump_strength'],
                    'Sand · relief strength fades with distance'), bump.inputs['Strength'])
links.new(fine, bump.inputs['Height'])
links.new(bump.outputs['Normal'], nodes['Wheel ruts · shallow editable relief'].inputs['Normal'])

ground_noise_report = {
    'material': mat.name,
    'source_floor': ground['source_asset'],
    'method': 'World-space fine grains, broad sand-color patches and shallow bump, layered under existing wheel-track color and normal treatment.',
    'source_atlas_and_uvs_preserved': True,
    'wheel_tracks_preserved': True,
    'new_geometry': False,
    'bitmap_inputs_added': 0,
    'configuration': cfg,
}
(OUT / 'ground-noise.json').write_text(json.dumps(ground_noise_report, indent=2) + '\n')
