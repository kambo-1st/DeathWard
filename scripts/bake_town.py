"""Bake a faithful static scene library and navigation for the original Unity town."""

import array
from collections import deque
import hashlib
import json
import math
from pathlib import Path
import struct
import sys
import bpy
sys.path.insert(0, str(Path(__file__).resolve().parent))
from town_train_motion import train_motion, train_lines
from mathutils import Matrix, Vector
from mathutils.bvhtree import BVHTree
from io_scene_fbx import parse_fbx
import numpy as np

UNITY_TO_BLENDER = Matrix(((-1, 0, 0, 0), (0, 0, -1, 0), (0, 1, 0, 0), (0, 0, 0, 1)))
BLENDER_TO_GAME = Matrix(((1, 0, 0, 0), (0, 0, 1, 0), (0, -1, 0, 0), (0, 0, 0, 1)))
UNITY_TO_GAME = BLENDER_TO_GAME @ UNITY_TO_BLENDER


def mesh_asset(info):
    d = info["unity_mesh"]
    v = d["m_VertexData"]
    channels = v["m_Channels"]
    channel = channels[0]
    assert (
        channel["stream"] == 0 and channel["format"] == 0 and channel["dimension"] == 3
    )
    stride = max(
        c["offset"]
        + (c["dimension"] & 15)
        * (
            {
                0: 4,
                1: 2,
                2: 1,
                3: 1,
                4: 1,
                5: 1,
                6: 2,
                7: 2,
                8: 4,
                9: 4,
                10: 4,
                11: 4,
            }.get(c["format"], 4)
        )
        for c in channels
        if c["stream"] == 0
    )
    raw = bytes.fromhex(v["_typelessdata"])
    verts = [
        UNITY_TO_BLENDER
        @ Vector(struct.unpack_from("<3f", raw, i * stride + channel["offset"]))
        for i in range(v["m_VertexCount"])
    ]
    inds = array.array("I" if d.get("m_IndexFormat", 0) else "H")
    inds.frombytes(bytes.fromhex(d["m_IndexBuffer"]))
    faces = []
    for sm in d["m_SubMeshes"]:
        assert sm["topology"] == 0
        start = sm["firstByte"] // inds.itemsize
        base = sm.get("baseVertex", 0)
        faces.extend(
            tuple(base + inds[j] for j in (i + 2, i + 1, i))
            for i in range(start, start + sm["indexCount"], 3)
        )
    m = bpy.data.meshes.new(info["source"])
    m.from_pydata(verts, [], faces)
    return m


def default_motion(placement):
    # Author a reusable preset into the scene; the runtime never checks asset names.
    if Path(placement["prefab"]).stem == "SM_Prop_Tumbleweed_01":
        return [3, 1.2, .04, 6, int(placement["object"].split(":")[0]) & 0xffffffff,
                0, 1, 0, 0, 0, 0]
    return None


def main():
    path = Path(sys.argv[sys.argv.index("--") + 1])
    recipe = json.loads(path.read_text())
    out = path.parent
    source = out / "source"
    bpy.ops.wm.read_factory_settings(use_empty=True)
    meshes = {}
    models = {}
    pivots_checked = 0
    for key, info in recipe["meshes"].items():
        if "unity_mesh" in info:
            meshes[key] = mesh_asset(info)
            continue
        if "primitive" in info:
            if info["primitive"] == "plane":
                # Unity's built-in plane is a 10 m square with ten subdivisions.
                data = bpy.data.meshes.new("Unity_Plane")
                vertices = [
                    UNITY_TO_BLENDER @ Vector((x - 5, 0, z - 5))
                    for z in range(11) for x in range(11)
                ]
                faces = [
                    (z * 11 + x, z * 11 + x + 1,
                     (z + 1) * 11 + x + 1, (z + 1) * 11 + x)
                    for z in range(10) for x in range(10)
                ]
                data.from_pydata(vertices, [], faces)
                uv = data.uv_layers.new()
                for loop in data.loops:
                    i = loop.vertex_index
                    uv.data[loop.index].uv = (i % 11 / 10, i // 11 / 10)
                meshes[key] = data
            else:
                bpy.ops.mesh.primitive_cube_add(size=1)
                o = bpy.context.object
                meshes[key] = o.data.copy()
                bpy.data.objects.remove(o, do_unlink=True)
            continue
        model = info["model"]
        if model not in models:
            raw, _ = parse_fbx.parse(str(source / model))
            objects = next(e for e in raw.elems if e.id == b"Objects")
            settings = next(e for e in raw.elems if e.id == b"GlobalSettings")
            props = next(e for e in settings.elems if e.id == b"Properties70")
            settings = {p.props[0].decode(): p.props[4:] for p in props.elems}
            assert settings["UpAxis"] == [1] and settings["UpAxisSign"] == [1], (
                model,
                settings,
            )
            units = (
                settings.get("UnitScaleFactor", [1])[0] * 0.01
                if info["use_file_scale"]
                else 1
            ) * info["scale"]
            pivots = {}
            for o in objects.elems:
                if o.id != b"Model":
                    continue
                name = o.props[1].split(b"\x00")[0].decode()
                pp = next((e for e in o.elems if e.id == b"Properties70"), None)
                values = (
                    {p.props[0].decode(): p.props[4:] for p in pp.elems} if pp else {}
                )
                pivots[name] = Vector(values.get("RotationPivot", [0, 0, 0]))
                if pivots[name].length > 0.001:
                    pivots_checked += 1
            before = set(bpy.data.objects)
            bpy.ops.import_scene.fbx(
                filepath=str(source / model), use_image_search=False, use_anim=False
            )
            imported = set(bpy.data.objects) - before
            models[model] = {}
            axis = Matrix(
                ((units, 0, 0, 0), (0, 0, -units, 0), (0, units, 0, 0), (0, 0, 0, 1))
            )
            for o in imported:
                if o.type == "MESH":
                    name = o.name if o.name in pivots else o.name.rsplit(".", 1)[0]
                    data = o.data.copy()
                    data.transform(
                        axis @ Matrix.Translation(-pivots.get(name, Vector((0, 0, 0))))
                    )
                    models[model][name] = data
            for o in imported:
                bpy.data.objects.remove(o, do_unlink=True)
        meshes[key] = models[model][info["name"]]
    print(
        f"MESHES {len(meshes)} including {pivots_checked} original FBX rotation pivots",
        flush=True,
    )
    materials = {}
    for key, info in recipe["materials"].items():
        m = bpy.data.materials.new(key)
        m.use_nodes = True
        s = m.node_tree.nodes.get("Principled BSDF")
        s.inputs["Base Color"].default_value = info["tint"]
        s.inputs["Alpha"].default_value = info["tint"][3]
        s.inputs["Roughness"].default_value = 0.8
        if info["texture"]:
            image = bpy.data.images.load(
                str(source / info["texture"]), check_existing=True
            )
            image.pack()
            n = m.node_tree.nodes.new("ShaderNodeTexImage")
            n.image = image
            m.node_tree.links.new(n.outputs["Color"], s.inputs["Base Color"])
        if info["transparent"]:
            m.blend_method = "BLEND"
        m.use_backface_culling = not info.get("double_sided", False)
        materials[key] = m
    variants = {}
    placements = []
    records = {}
    for entry in recipe["renderers"]:
        key = (entry["mesh"], tuple(entry["materials"]))
        if key not in variants:
            name = f"part_{len(variants):04d}"
            variants[key] = name
            data = meshes[entry["mesh"]].copy()
            data.materials.clear()
            for material in entry["materials"]:
                data.materials.append(materials[material])
            if not data.uv_layers.active:
                data.uv_layers.new()
            for p in data.polygons:
                assert p.material_index < len(entry["materials"]), (
                    entry,
                    p.material_index,
                )
                info = recipe["materials"][entry["materials"][p.material_index]]
                for i in p.loop_indices:
                    uv = data.uv_layers.active.data[i].uv
                    uv.x = uv.x * info["uv_scale"]["x"] + info["uv_offset"]["x"]
                    uv.y = uv.y * info["uv_scale"]["y"] + info["uv_offset"]["y"]
            o = bpy.data.objects.new(name, data)
            bpy.context.collection.objects.link(o)
            pts = [BLENDER_TO_GAME @ v.co for v in data.vertices]
            lo = [min(p[i] for p in pts) for i in range(3)]
            hi = [max(p[i] for p in pts) for i in range(3)]
            records[name] = {
                "bounds": [lo, hi],
                "mesh_source": entry["mesh"],
                "materials": entry["materials"],
            }
        transform = UNITY_TO_GAME @ Matrix(entry["matrix"]) @ UNITY_TO_GAME.inverted()
        placements.append(
            {
                "asset": variants[key],
                "transform": [v for row in transform for v in row],
                **{k: entry[k] for k in ("object", "prefab", "name")},
            }
        )
    bpy.ops.object.select_all(action="SELECT")
    glb = out / "town.glb"
    bpy.ops.export_scene.gltf(
        filepath=str(glb),
        export_format="GLB",
        use_selection=True,
        export_yup=True,
        export_animations=False,
        export_skins=False,
        export_morph=False,
        export_cameras=False,
        export_lights=False,
    )
    raw = glb.read_bytes()
    length = struct.unpack_from("<I", raw, 12)[0]
    gltf = json.loads(raw[20 : 20 + length])
    ignored_color_streams = 0
    for mesh in gltf["meshes"]:
        for primitive in mesh["primitives"]:
            material = gltf["materials"][primitive["material"]]
            info = recipe["materials"][material["name"]]
            if not info.get("uses_vertex_colors", True):
                ignored_color_streams += "COLOR_0" in primitive["attributes"]
                primitive["attributes"].pop("COLOR_0", None)
    for m in gltf["materials"]:
        info = recipe["materials"][m["name"]]
        m["pbrMetallicRoughness"]["baseColorFactor"] = info["tint"]
        if info["unlit"]:
            m.setdefault("extensions", {})["KHR_materials_unlit"] = {}
    gltf.setdefault("extensionsUsed", []).append("KHR_materials_unlit")
    encoded = json.dumps(gltf, separators=(",", ":")).encode()
    encoded += b" " * (-len(encoded) % 4)
    tail = raw[20 + length :]
    raw = (
        struct.pack("<III", 0x46546C67, 2, 20 + len(encoded) + len(tail))
        + struct.pack("<II", len(encoded), 0x4E4F534A)
        + encoded
        + tail
    )
    glb.write_bytes(raw)
    motions = {p["object"]: default_motion(p) for p in placements if default_motion(p)}
    paths, groups, members = train_motion(placements, records)
    lines = ["DEATHWARD_TOWN " + ("3" if paths else "2")]
    moving_prefabs = {object_id.split(":")[0] for object_id in members}
    offset = 0
    order = {}
    for n in gltf["nodes"]:
        if "mesh" not in n:
            continue
        name = n["name"]
        record = records[name]
        count = len(gltf["meshes"][n["mesh"]]["primitives"])
        order[name] = len(order)
        record.update(first_mesh=offset, mesh_count=count)
        unlit = all(recipe["materials"][m]["unlit"] for m in record["materials"])
        lines.append(
            "asset "
            + name
            + " "
            + str(offset)
            + " "
            + str(count)
            + " "
            + str(int(unlit))
            + " "
            + " ".join(str(v) for row in record["bounds"] for v in row)
        )
        offset += count
    for p in placements:
        lines.append(
            "instance "
            + str(order[p["asset"]])
            + " "
            + p["object"]
            + " "
            + " ".join(str(v) for v in p["transform"])
        )
        if p["object"] in motions:
            lines.append("motion " + p["object"] + " " + " ".join(map(str, motions[p["object"]])))
    for light in recipe["lights"]:
        if light["type"] not in (1, 2):
            continue
        transform = UNITY_TO_GAME @ Matrix(light["matrix"]) @ UNITY_TO_GAME.inverted()
        position = transform.translation
        direction = -(transform.to_3x3() @ Vector((0, 0, 1))).normalized()
        lines.append(
            "light "
            + str(light["type"])
            + " "
            + " ".join(
                str(v)
                for v in [
                    *position,
                    *direction,
                    *light["color"],
                    light["intensity"],
                    light["range"],
                ]
            )
        )
    lines.extend(train_lines(paths, groups, members))
    (out / "town.scene").write_text("\n".join(lines) + "\n")
    labels = {}
    for placement in placements:
        label = (
            placement["name"] if placement["prefab"] == recipe["scene"]
            else Path(placement["prefab"]).stem
        )
        # The cooking pot is a separate child of Frontier's small campfire.
        # Keep it distinct in the editor and avoid attaching a second fire to it.
        if placement["name"] in ("SM_Prop_Campfire_Pot_01", "SM_Veh_Train_01_Alt_Smokestack"):
            label = placement["name"]
        child = placement["name"].split(" (")[0]
        if child.startswith(("SM_Bld_", "SM_Building_")):
            label = child
        labels.setdefault(placement["asset"], label)
    (out / "town.labels").write_text(
        "".join(f"{asset} {labels.get(asset, asset)}\n" for asset in order)
    )
    # Seed grid bounds and gameplay markers from the original colliders.
    # import_town.py then runs the shared native geometry/headroom baker; this
    # intermediate DWTNAV01 grid is also upgraded automatically by the game.
    verts = []
    faces = []
    for entry in recipe["colliders"]:
        if entry["object"] in motions or entry["object"].split(":")[0] in moving_prefabs or any(s in entry["prefab"] for s in ("Cloud", "SkyDome")):
            continue
        world = UNITY_TO_BLENDER @ Matrix(entry["matrix"]) @ UNITY_TO_BLENDER.inverted()
        if "mesh" in entry:
            data = meshes[entry["mesh"]]
        elif "box" in entry:
            size = Vector([entry["box"][a] for a in "xyz"])
            center = Vector([entry["center"][a] for a in "xyz"])
            vv = [
                UNITY_TO_BLENDER
                @ (center + Vector((x * size.x, y * size.y, z * size.z)))
                for z in (-0.5, 0.5)
                for y in (-0.5, 0.5)
                for x in (-0.5, 0.5)
            ]
            data = bpy.data.meshes.new("collision_box")
            data.from_pydata(
                vv,
                [],
                [
                    (0, 2, 3, 1),
                    (4, 5, 7, 6),
                    (0, 1, 5, 4),
                    (2, 6, 7, 3),
                    (0, 4, 6, 2),
                    (1, 3, 7, 5),
                ],
            )
        elif "capsule" in entry:
            o = entry["capsule"]
            r = o["m_Radius"]
            h = o["m_Height"]
            center = Vector([o["m_Center"][a] for a in "xyz"])
            bpy.ops.mesh.primitive_uv_sphere_add(segments=12, ring_count=8, radius=1)
            obj = bpy.context.object
            data = obj.data.copy()
            bpy.data.objects.remove(obj, do_unlink=True)
            dimensions = [r, r, r]
            dimensions[o["m_Direction"]] = h / 2
            data.transform(
                UNITY_TO_BLENDER
                @ Matrix.Translation(center)
                @ Matrix.Diagonal((*dimensions, 1))
            )
        base = len(verts)
        verts.extend(world @ v.co for v in data.vertices)
        faces.extend(tuple(base + i for i in p.vertices) for p in data.polygons)
    tree = BVHTree.FromPolygons(verts, faces, all_triangles=False)
    # The useful town sits around the main street. Include all terrain except the
    # huge demo support cube and far scenic mountains/clouds in navigation bounds.
    step = 0.4
    navigation = recipe.get("navigation", {})
    minx, minz, maxx, maxz = navigation.get("bounds", [-120, -90, 120, 150])
    nx = round((maxx - minx) / step)
    nz = round((maxz - minz) / step)
    heights = np.full((nz, nx), np.nan, dtype=np.float32)
    down = Vector((0, 0, -1))
    top = max(v.z for v in verts) + 2
    for z in range(nz):
        for x in range(nx):
            p, n, _, _ = tree.ray_cast(
                Vector((minx + (x + 0.5) * step, -(minz + (z + 0.5) * step), top)),
                down,
                top + 100,
            )
            if p is not None and abs(n.z) > 0.7 and -5 < p.z < 12:
                heights[z, x] = p.z
    # Remove cliff edges and narrow surfaces using the character's footprint.
    clear = np.isfinite(heights)
    for dz, dx in [
        (0, 1),
        (0, -1),
        (1, 0),
        (-1, 0),
        (1, 1),
        (1, -1),
        (-1, 1),
        (-1, -1),
    ]:
        shifted = np.roll(heights, (dz, dx), (0, 1))
        clear &= np.isfinite(shifted) & (np.abs(shifted - heights) < 0.6)
    clear[[0, -1], :] = False
    clear[:, [0, -1]] = False

    # Spawn on the main street; choose the closest valid terrain sample. Markers
    # are gameplay additions only; imported scene transforms are never adjusted.
    def nearest(target, allowed):
        zz, xx = np.nonzero(allowed)
        best = np.argmin(
            (minx + (xx + 0.5) * step - target[0]) ** 2
            + (minz + (zz + 0.5) * step - target[1]) ** 2
        )
        return int(zz[best]), int(xx[best])

    spawn_cell = nearest(navigation.get("spawn", (0, -5)), clear)
    connected = np.zeros_like(clear)
    connected[spawn_cell] = True
    queue = deque([spawn_cell])
    while queue:
        z, x = queue.popleft()
        for dz, dx in ((0, 1), (0, -1), (1, 0), (-1, 0)):
            zz, xx = z + dz, x + dx
            if (
                0 <= zz < nz
                and 0 <= xx < nx
                and clear[zz, xx]
                and not connected[zz, xx]
                and abs(float(heights[zz, xx] - heights[z, x])) <= 0.6
            ):
                connected[zz, xx] = True
                queue.append((zz, xx))
    heights[~connected] = np.nan
    station = [p for p in placements if p["name"] == "SM_Bld_TrainStation_01"]
    station_position = [0, 0]
    if station:
        t = station[0]["transform"]
        station_position = [t[3], t[11]]
    mission_cell = nearest(navigation.get("mission", station_position), connected)

    def point(cell):
        z, x = cell
        return [minx + (x + 0.5) * step, float(heights[z, x]), minz + (z + 0.5) * step]

    spawn = point(spawn_cell)
    mission = point(mission_cell)
    with (out / "town.nav").open("wb") as f:
        f.write(b"DWTNAV01")
        f.write(struct.pack("<II9f", nx, nz, minx, minz, step, *spawn, *mission))
        f.write(heights.astype("<f4").tobytes())
    manifest = {
        "format": 1,
        "scene": recipe["scene"],
        "source_prefab_instances": len(recipe["prefab_instances"]),
        "active_mesh_placements": len(placements),
        "assets": records,
        "placements": placements,
        "object_motion": motions,
        "train_motion": {"paths": paths, "groups": groups, "members": members},
        "mesh_count": offset,
        "embedded_images": len(gltf.get("images", [])),
        "materials": recipe["materials"],
        "source_sha256": recipe["source_sha256"],
        "fbx_pivots": pivots_checked,
        "ignored_vertex_color_streams": ignored_color_streams,
        "collision_components": len(recipe["colliders"]),
        "missing_collider_fallbacks": recipe["missing_collider_fallbacks"],
        "navigation": {
            "dimensions": [nx, nz],
            "cell": step,
            "walkable_cells": int(connected.sum()),
            "spawn": spawn,
            "mission": mission,
            "station": station_position,
        },
        "output_sha256": {
            name: hashlib.sha256((out / name).read_bytes()).hexdigest()
            for name in ("town.glb", "town.scene", "town.nav", "town.labels")
        },
    }
    (out / "town.manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    print(
        "EXPORTED",
        len(placements),
        "placements",
        offset,
        "meshes",
        len(gltf.get("images", [])),
        "textures",
        "NAV",
        manifest["navigation"],
        flush=True,
    )


if __name__ == "__main__":
    main()
