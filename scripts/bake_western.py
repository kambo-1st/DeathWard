"""Blender half of import_western.py; exports a texture-embedded static mesh library."""
import hashlib
import json
import math
from pathlib import Path
import struct
import sys

import bpy
from mathutils import Matrix, Vector


def main():
    recipe_path = Path(sys.argv[sys.argv.index("--") + 1])
    recipe = json.loads(recipe_path.read_text())
    output = recipe_path.parent
    source = output / "source"
    bpy.ops.wm.read_factory_settings(use_empty=True)
    material_cache = {}
    for name, info in recipe["materials"].items():
        mat = bpy.data.materials.new(name)
        mat.use_nodes = True
        shader = mat.node_tree.nodes.get("Principled BSDF")
        shader.inputs["Base Color"].default_value = info["tint"]
        shader.inputs["Alpha"].default_value = info["tint"][3]
        shader.inputs["Metallic"].default_value = info["metallic"]
        shader.inputs["Roughness"].default_value = info["roughness"]
        if info["texture"]:
            image = bpy.data.images.load(str(source / info["texture"]), check_existing=True)
            image.pack()
            node = mat.node_tree.nodes.new("ShaderNodeTexImage")
            node.image = image
            mat.node_tree.links.new(node.outputs["Color"], shader.inputs["Base Color"])
        if info["transparent"]:
            mat.blend_method = "BLEND"
        material_cache[name] = mat

    records = {}
    for asset in recipe["assets"]:
        before = set(bpy.data.objects)
        for model in asset["models"]:
            bpy.ops.import_scene.fbx(filepath=str(source / model), use_image_search=False, use_anim=False)
        imported = set(bpy.data.objects) - before
        meshes = []
        matched = set()
        for obj in imported:
            if obj.type != "MESH" or obj.name not in asset["parts"]:
                continue
            matched.add(obj.name)
            names = asset["parts"][obj.name]
            obj.data.materials.clear()
            for name in names:
                obj.data.materials.append(material_cache[name])
            for polygon in obj.data.polygons:
                if polygon.material_index >= len(names):
                    raise RuntimeError(f"Missing material for {obj.name}")
                info = recipe["materials"][names[polygon.material_index]]
                for loop in polygon.loop_indices:
                    uv = obj.data.uv_layers.active.data[loop].uv
                    uv.x = uv.x * info["uv_scale"]["x"] + info["uv_offset"]["x"]
                    uv.y = uv.y * info["uv_scale"]["y"] + info["uv_offset"]["y"]
            obj.data.transform(obj.matrix_world)
            obj.parent = None
            obj.matrix_world = Matrix.Identity(4)
            meshes.append(obj)
        if matched != set(asset["parts"]):
            raise RuntimeError(f"Unmatched prefab mesh parts in {asset['name']}: {set(asset['parts']) - matched}")
        bpy.ops.object.select_all(action="DESELECT")
        for obj in meshes:
            obj.select_set(True)
        bpy.context.view_layer.objects.active = meshes[0]
        if len(meshes) > 1:
            bpy.ops.object.join()
        combined = bpy.context.object
        combined.name = combined.data.name = asset["name"]
        # These source sticks stand upright. Lay them down before normalizing
        # the pivot so room debris rests on the ground, with its UVs intact.
        if asset.get("ground_debris"):
            combined.data.transform(Matrix.Rotation(math.pi / 2, 4, "X"))
        # Center X/Z and rest on Y=0 in the exported glTF; retain original meters.
        points = [v.co for v in combined.data.vertices]
        lo = Vector([min(p[i] for p in points) for i in range(3)])
        hi = Vector([max(p[i] for p in points) for i in range(3)])
        offset = Vector((-(lo.x + hi.x) / 2, -(lo.y + hi.y) / 2, -lo.z))
        combined.data.transform(Matrix.Translation(offset))
        lo += offset
        hi += offset
        records[asset["name"]] = {
            "bounds": [[lo.x, lo.z, -hi.y], [hi.x, hi.z, -lo.y]],
            "vertices": len(combined.data.vertices),
            "triangles": sum(len(p.vertices) - 2 for p in combined.data.polygons),
        }
        for obj in list(bpy.data.objects):
            if obj in imported and obj != combined:
                bpy.data.objects.remove(obj, do_unlink=True)
        print(f"BAKED {asset['name']}: {records[asset['name']]}", flush=True)

    # A square ground tile retains samples from the original sand atlas while
    # matching the game's exact walkable footprint (no irregular mesh holes).
    ground = bpy.data.objects["ground"]
    top_faces = [p for p in ground.data.polygons if p.normal.z > 0.7]
    floor_mesh = bpy.data.meshes.new("floor")
    floor_mesh.from_pydata([(-1, -1, 0), (1, -1, 0), (1, 1, 0), (-1, 1, 0)], [], [(0, 1, 2), (0, 2, 3)])
    floor_mesh.materials.append(ground.data.materials[0])
    uv = floor_mesh.uv_layers.new()
    for polygon, original in zip(floor_mesh.polygons, top_faces):
        sample = sum((ground.data.uv_layers.active.data[i].uv for i in original.loop_indices), Vector((0, 0))) / len(original.loop_indices)
        for loop in polygon.loop_indices:
            uv.data[loop].uv = sample
    floor_obj = bpy.data.objects.new("floor", floor_mesh)
    bpy.context.collection.objects.link(floor_obj)
    records["floor"] = {"bounds": [[-1, 0, -1], [1, 0, 1]], "vertices": 4, "triangles": 2}

    # Solid stratified cover: all six faces exactly fill the collision box.
    # Sample the original cliff atlas rather than fitting a rounded boulder
    # into an invisible rectangular collision envelope.
    cliff = bpy.data.objects["cliff_wall"]
    samples = []
    for polygon in cliff.data.polygons:
        sample = sum((cliff.data.uv_layers.active.data[i].uv for i in polygon.loop_indices), Vector((0, 0))) / len(polygon.loop_indices)
        samples.append((polygon.center.z, polygon.normal.z, sample))
    samples.sort(key=lambda entry: entry[0])
    vertices, faces, colors = [], [], []
    def quad(points, sample):
        start = len(vertices)
        vertices.extend(points)
        faces.append(tuple(range(start, start + 4)))
        colors.append(sample)
    corners = [(-.5, -.5), (.5, -.5), (.5, .5), (-.5, .5)]
    bands = 6
    for side in range(4):
        a, b = corners[side], corners[(side + 1) % 4]
        for band in range(bands):
            low, high = band / bands, (band + 1) / bands
            sample = samples[min(len(samples)-1, int((band + .5) / bands * len(samples)))][2]
            quad([(*a, low), (*b, low), (*b, high), (*a, high)], sample)
    tops = [entry for entry in samples if entry[1] > .65]
    top_uv = tops[-1][2] if tops else samples[-1][2]
    quad([(*p, 1) for p in corners], top_uv)
    quad([(*p, 0) for p in reversed(corners)], samples[0][2])
    stone_mesh = bpy.data.meshes.new("sandstone")
    stone_mesh.from_pydata(vertices, [], faces)
    stone_mesh.materials.append(cliff.data.materials[0])
    stone_uv = stone_mesh.uv_layers.new()
    for polygon, sample in zip(stone_mesh.polygons, colors):
        for loop in polygon.loop_indices:
            stone_uv.data[loop].uv = sample
    stone = bpy.data.objects.new("sandstone", stone_mesh)
    bpy.context.collection.objects.link(stone)
    records["sandstone"] = {"bounds": [[-.5, 0, -.5], [.5, 1, .5]], "vertices": len(vertices), "triangles": 2 * len(faces)}

    bpy.ops.object.select_all(action="SELECT")
    glb = output / "western.glb"
    bpy.ops.export_scene.gltf(filepath=str(glb), export_format="GLB", use_selection=True,
                              export_yup=True, export_animations=False, export_skins=False,
                              export_morph=False, export_cameras=False, export_lights=False)
    raw = glb.read_bytes()
    length = struct.unpack_from("<I", raw, 12)[0]
    gltf = json.loads(raw[20:20 + length])
    # Preserve Unity's color multiplier alongside the base texture. Blender's
    # direct texture link otherwise exports a white multiplier.
    for material in gltf["materials"]:
        info = recipe["materials"][material["name"]]
        material["pbrMetallicRoughness"]["baseColorFactor"] = info["tint"]
    encoded = json.dumps(gltf, separators=(",", ":")).encode()
    encoded += b" " * ((-len(encoded)) % 4)
    tail = raw[20 + length:]
    raw = struct.pack("<III", 0x46546c67, 2, 20 + len(encoded) + len(tail)) + struct.pack("<II", len(encoded), 0x4e4f534a) + encoded + tail
    glb.write_bytes(raw)
    # Mesh ranges follow raylib 5.5's node order, one Mesh per triangle primitive.
    mesh_offset = 0
    lines = ["DEATHWARD_WESTERN 1"]
    for node in gltf["nodes"]:
        if "mesh" not in node:
            continue
        name = node["name"]
        primitives = gltf["meshes"][node["mesh"]]["primitives"]
        count = len(primitives)
        record = records[name]
        record["first_mesh"] = mesh_offset
        record["mesh_count"] = count
        lines.append(f"{name} {mesh_offset} {count} " + " ".join(str(v) for row in record["bounds"] for v in row))
        mesh_offset += count
    (output / "western.catalog").write_text("\n".join(lines) + "\n")
    manifest = {"format": 1, "blender": bpy.app.version_string, "assets": records,
                "materials": list(recipe["materials"]), "embedded_images": len(gltf.get("images", [])),
                "mesh_count": mesh_offset, "glb_sha256": hashlib.sha256(raw).hexdigest()}
    (output / "western.manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    print(f"EXPORTED {glb}: {len(records)} assets, {mesh_offset} meshes, {manifest['embedded_images']} embedded images")


if __name__ == "__main__":
    main()
