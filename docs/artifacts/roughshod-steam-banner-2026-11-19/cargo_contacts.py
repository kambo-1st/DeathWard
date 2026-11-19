"""Settle the editable cloth meshes onto their visible support surfaces.

This is a still-scene placement helper, not a rigid-body simulation. It measures
the lower mesh surface against the sand, the crate's interior deck, or already
placed cargo. Bounding-box corners and guessed stacking heights are not used.
"""
from mathutils.bvhtree import BVHTree


def cargo_surface(obj, crate_deck=False):
    evaluated = obj.evaluated_get(bpy.context.evaluated_depsgraph_get())
    mesh = evaluated.to_mesh()
    vertices = [obj.matrix_world @ v.co for v in mesh.vertices]
    polygons = []
    for face in mesh.polygons:
        # Only the lower deck of this closed-roof crate can support its contents.
        if crate_deck and (face.center.z > .13 or face.normal.z < .5):
            continue
        polygons.append(tuple(face.vertices))
    tree = BVHTree.FromPolygons(vertices, polygons)
    evaluated.to_mesh_clear()
    return tree, vertices


def cargo_contact_gap(obj, supports):
    """Return the tightest sampled vertical gap, including actual mesh vertices."""
    bpy.context.view_layer.update()
    underside, vertices = cargo_surface(obj)
    x0, x1 = min(v.x for v in vertices), max(v.x for v in vertices)
    y0, y1 = min(v.y for v in vertices), max(v.y for v in vertices)
    points = {(v.x, v.y) for v in vertices}
    # Dense samples also catch contacts in the middle of a triangle, including
    # the peaked top of a supporting sack beneath a broad lower cloth face.
    steps = 70
    points.update((x0 + (x1-x0)*i/steps, y0 + (y1-y0)*j/steps)
                  for i in range(1, steps) for j in range(1, steps))
    best = None
    for x, y in points:
        lower = underside.ray_cast(Vector((x, y, -5)), Vector((0, 0, 1)))[0]
        if lower is None:
            continue
        for name, support in supports:
            upper = support.ray_cast(Vector((x, y, 5)), Vector((0, 0, -1)))[0]
            if upper is None:
                continue
            gap = lower.z - upper.z
            if best is None or gap < best['gap']:
                best = {'gap': gap, 'support': name,
                        'contact_xy': [float(x), float(y)]}
    assert best is not None, obj.name
    return best


def settle_cargo(obj, supports, embed):
    before = cargo_contact_gap(obj, supports)
    obj.location.z -= before['gap'] + embed
    bpy.context.view_layer.update()
    after = cargo_contact_gap(obj, supports)
    assert abs(after['gap'] + embed) < .0001
    obj['support_surface'] = after['support']
    obj['support_embed'] = embed
    return {'object': obj.name, 'support': after['support'],
            'vertical_adjustment': -before['gap'] - embed,
            'minimum_sampled_gap': after['gap'],
            'contact_xy': after['contact_xy'],
            'world_position': list(obj.matrix_world.translation)}
