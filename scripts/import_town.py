"""Resolve a PolygonWestern Demo.unity, retaining hierarchy and overrides.

Requires PyYAML, NumPy and Blender 3.6. No authoring tools are needed at runtime.
"""

import argparse
import copy
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess
import numpy as np
import yaml
from import_western import documents, ROOT


def trs(obj):
    p = obj.get("m_LocalPosition", dict(x=0, y=0, z=0))
    s = obj.get("m_LocalScale", dict(x=1, y=1, z=1))
    q = obj.get("m_LocalRotation", dict(x=0, y=0, z=0, w=1))
    x, y, z, w = [q[a] for a in "xyzw"]
    n = np.linalg.norm([x, y, z, w])
    x, y, z, w = np.array([x, y, z, w]) / n
    m = np.eye(4)
    m[:3, :3] = [
        [1 - 2 * (y * y + z * z), 2 * (x * y - z * w), 2 * (x * z + y * w)],
        [2 * (x * y + z * w), 1 - 2 * (x * x + z * z), 2 * (y * z - x * w)],
        [2 * (x * z - y * w), 2 * (y * z + x * w), 1 - 2 * (x * x + y * y)],
    ]
    m[:3, :3] = m[:3, :3] @ np.diag([s[a] for a in "xyz"])
    m[:3, 3] = [p[a] for a in "xyz"]
    return m


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, default=ROOT / "assets/town/source")
    parser.add_argument("--output", type=Path, default=ROOT / "assets/town")
    parser.add_argument("--blender", default="blender")
    parser.add_argument("--resolve-only", action="store_true")
    parser.add_argument(
        "--nav-bounds", type=float, nargs=4,
        metavar=("MIN_X", "MIN_Z", "MAX_X", "MAX_Z")
    )
    parser.add_argument("--spawn", type=float, nargs=2, metavar=("X", "Z"))
    parser.add_argument("--mission", type=float, nargs=2, metavar=("X", "Z"))
    args = parser.parse_args()
    source = args.source.resolve()
    out = args.output.resolve()
    out.mkdir(parents=True, exist_ok=True)
    copied = out / "source"
    index = {}
    hashes = {}
    cache = {}
    for p in source.rglob("*.meta"):
        g = re.search(r"^guid: (\w+)", p.read_text(), re.M)
        if g:
            index[g[1]] = p.with_suffix("")

    def collect(p):
        rel = p.relative_to(source)
        if str(rel) in hashes:
            return str(rel)
        target = copied / rel
        target.parent.mkdir(parents=True, exist_ok=True)
        if p != target:
            shutil.copyfile(p, target)
        hashes[str(rel)] = hashlib.sha256(p.read_bytes()).hexdigest()
        meta = p.with_name(p.name + ".meta")
        dest = target.with_name(target.name + ".meta")
        if meta.exists() and meta != dest:
            shutil.copyfile(meta, dest)
        if meta.exists():
            hashes[str(meta.relative_to(source))] = hashlib.sha256(
                meta.read_bytes()
            ).hexdigest()
        return str(rel)

    def docs(p):
        if p not in cache:
            cache[p] = documents(p)
        return cache[p]

    def resolve(ref):
        if ref.get("guid") not in index:
            raise RuntimeError(f"Missing source {ref}")
        return index[ref["guid"]]

    scene = source / "Scenes/Demo.unity"
    collect(scene)
    scene_docs = docs(scene)
    instances = {}
    nodes = {}
    components = []
    material_defs = {}
    mesh_defs = {}
    missing_colliders = []
    source_instances = []
    stale_overrides = []
    # Expand prefab components into a namespace for each instance. Scene stripped
    # references alias these same objects, including parents of added prefab children.
    for c, k, obj in scene_docs:
        if c != 1001:
            continue
        p = resolve(obj["m_SourcePrefab"])
        collect(p)
        expanded = {
            key: (kind, copy.deepcopy(data))
            for kind, key, data in docs(p)
            if kind != 1001
        }
        mod = obj["m_Modification"]
        for change in mod["m_Modifications"]:
            target = change["target"]["fileID"]
            prop = change["propertyPath"]
            if target not in expanded:
                stale_overrides.append({"instance": k, **change})
                continue
            data = expanded[target][1]
            if prop.startswith(
                ("m_LocalPosition.", "m_LocalRotation.", "m_LocalScale.")
            ):
                field, axis = prop.split(".")
                data[field][axis] = float(change["value"])
            elif prop in ("m_IsActive", "m_Enabled", "m_Name"):
                data[prop] = (
                    change["value"] if prop == "m_Name" else int(change["value"])
                )
            elif prop.startswith("m_Materials.Array.data["):
                data["m_Materials"][int(re.search(r"\[(\d+)\]", prop)[1])] = change[
                    "objectReference"
                ]
            elif prop == "m_Mesh":
                data[prop] = change["objectReference"]
        for removed in mod.get("m_RemovedComponents", []):
            expanded.pop(removed["fileID"], None)
        if mod.get("m_RemovedGameObjects"):
            raise RuntimeError("Removed object support required")
        instances[k] = (p, expanded, mod)
        source_instances.append({"id": k, "prefab": str(p.relative_to(source))})
    aliases = {}
    for c, k, o in scene_docs:
        if o.get("m_CorrespondingSourceObject", {}).get("fileID") and o.get(
            "m_PrefabInstance", {}
        ).get("fileID"):
            aliases[k] = (
                o["m_PrefabInstance"]["fileID"],
                o["m_CorrespondingSourceObject"]["fileID"],
            )

    def scene_key(k):
        return aliases.get(k, (0, k)) if k else None

    gameobjects = {}
    for iid, (path, expanded, mod) in instances.items():
        for k, (c, o) in expanded.items():
            key = (iid, k)
            if c == 1:
                gameobjects[key] = o
            if c == 4:
                father = o["m_Father"]["fileID"]
                parent = (
                    (iid, father)
                    if father
                    else scene_key(mod["m_TransformParent"]["fileID"])
                )
                nodes[key] = {
                    "obj": o,
                    "parent": parent,
                    "go": (iid, o["m_GameObject"]["fileID"]),
                }
            else:
                components.append((c, key, o, str(path.relative_to(source))))
    for c, k, o in scene_docs:
        if k in aliases or c == 1001:
            continue
        key = (0, k)
        if c == 1:
            gameobjects[key] = o
        if c == 4:
            nodes[key] = {
                "obj": o,
                "parent": scene_key(o["m_Father"]["fileID"]),
                "go": scene_key(o["m_GameObject"]["fileID"]),
            }
        else:
            components.append((c, key, o, "Scenes/Demo.unity"))
    go_transform = {v["go"]: k for k, v in nodes.items()}

    def world(key):
        node = nodes[key]
        if "matrix" not in node:
            parent = node["parent"]
            node["matrix"] = (world(parent) if parent else np.eye(4)) @ trs(node["obj"])
            node["active"] = bool(gameobjects[node["go"]].get("m_IsActive", 1)) and (
                nodes[parent]["active"] if parent else True
            )
        return node["matrix"]

    for k in nodes:
        world(k)

    def component_go(key, o):
        return (
            (key[0], o["m_GameObject"]["fileID"])
            if key[0]
            else scene_key(o["m_GameObject"]["fileID"])
        )

    renderers = {component_go(k, o): o for c, k, o, _ in components if c == 23}
    filters = {component_go(k, o): o for c, k, o, _ in components if c == 33}

    def mesh(ref):
        key = f"{ref.get('guid','')}_{ref['fileID']}"
        if key in mesh_defs:
            return key
        primitives = {10202: "cube", 10209: "plane"}
        if (
            ref.get("guid") == "0000000000000000e000000000000000"
            and ref["fileID"] in primitives
        ):
            mesh_defs[key] = {"primitive": primitives[ref["fileID"]]}
            return key
        p = resolve(ref)
        collect(p)
        if p.suffix.lower() == ".fbx":
            meta = yaml.safe_load(p.with_name(p.name + ".meta").read_text())[
                "ModelImporter"
            ]
            names = meta.get("fileIDToRecycleName") or {
                next(iter(e["first"].values())): e["second"]
                for e in meta.get("internalIDToNameTable", [])
            }
            name = names[ref["fileID"]]
            mesh_defs[key] = {
                "model": str(p.relative_to(source)),
                "name": name,
                "scale": meta["meshes"].get("globalScale", 1),
                "use_file_scale": meta["meshes"].get("useFileScale", False),
            }
        elif p.suffix == ".asset":
            data = next(o for c, k, o in docs(p) if c == 43 and k == ref["fileID"])
            mesh_defs[key] = {"unity_mesh": data, "source": str(p.relative_to(source))}
        else:
            raise RuntimeError(f"Unsupported mesh {p}")
        return key

    def material(ref):
        key = ref["guid"]
        if key in material_defs:
            return key
        if key == "0000000000000000f000000000000000":
            material_defs[key] = {
                "name": "Unity_Default",
                "tint": [0.7, 0.7, 0.7, 1],
                "texture": None,
                "uv_scale": {"x": 1, "y": 1},
                "uv_offset": {"x": 0, "y": 0},
                "transparent": False,
                "unlit": False,
            }
            return key
        p = resolve(ref)
        collect(p)
        o = next(o for c, k, o in docs(p) if c == 21)
        props = o["m_SavedProperties"]
        tex = {k: v for e in props.get("m_TexEnvs", []) for k, v in e.items()}
        colors = {k: v for e in props.get("m_Colors", []) for k, v in e.items()}
        floats = {k: v for e in props.get("m_Floats", []) for k, v in e.items()}
        shader = o.get("m_Shader", {})
        # Unity Standard and URP/Lit do not consume mesh COLOR attributes.
        # Frontier trees contain auxiliary painted channels, including zero alpha.
        # Treating them as albedo would turn trunks magenta and erase foliage.
        standard_lit = shader.get("guid") == "933532a4fcc9baf4fa0491de14d08ed7" or (
            shader.get("guid") == "0000000000000000f000000000000000"
            and shader.get("fileID") == 10755
        )
        base = tex.get("_BaseMap", tex.get("_MainTex", {}))
        t = base.get("m_Texture", {})
        tint = colors.get("_BaseColor", colors.get("_Color", dict(r=1, g=1, b=1, a=1)))
        material_defs[key] = {
            "name": p.stem,
            "shader": shader,
            "uses_vertex_colors": not standard_lit,
            "tint": [tint[a] for a in "rgba"],
            "texture": collect(resolve(t)) if t.get("guid") else None,
            "uv_scale": base.get("m_Scale", dict(x=1, y=1)),
            "uv_offset": base.get("m_Offset", dict(x=0, y=0)),
            "transparent": floats.get("_Surface", 0) == 1
            or floats.get("_Mode", 0) in (2, 3),
            "unlit": "Sky" in p.stem or "Cloud" in p.stem,
            "double_sided": floats.get("_Cull", 2) == 0,
        }
        return key

    rendered = []
    colliders = []
    lights = []
    for c, key, o, path in components:
        if c not in (33, 64, 65, 136, 108):
            continue
        go = component_go(key, o)
        if go not in go_transform:
            continue
        node = nodes[go_transform[go]]
        if not node["active"] or not o.get("m_Enabled", 1):
            continue
        base = {
            "matrix": node["matrix"].tolist(),
            "object": f"{go[0]}:{go[1]}",
            "prefab": path,
            "name": gameobjects[go].get("m_Name", ""),
        }
        if c == 33:
            renderer = renderers.get(go)
            if renderer and renderer.get("m_Enabled", 1):
                rendered.append(
                    {
                        **base,
                        "mesh": mesh(o["m_Mesh"]),
                        "materials": [material(r) for r in renderer["m_Materials"]],
                    }
                )
        elif c == 108:
            lights.append(
                {
                    **base,
                    "type": o["m_Type"],
                    "color": list(o["m_Color"].values())[:3],
                    "intensity": o["m_Intensity"],
                    "range": o["m_Range"],
                }
            )
        elif not o.get("m_IsTrigger", 0):
            if c == 65:
                colliders.append({**base, "box": o["m_Size"], "center": o["m_Center"]})
            elif c == 136:
                colliders.append({**base, "capsule": o})
            elif o.get("m_Mesh", {}).get("fileID"):
                ref = o["m_Mesh"]
                if ref.get("guid") not in index:
                    missing_colliders.append({**base, "reference": ref})
                    if go in filters:
                        ref = filters[go]["m_Mesh"]
                    else:
                        continue
                colliders.append({**base, "mesh": mesh(ref)})
    recipe = {
        "format": 1,
        "scene": "Scenes/Demo.unity",
        "prefab_instances": source_instances,
        "renderers": rendered,
        "colliders": colliders,
        "lights": lights,
        "meshes": mesh_defs,
        "materials": material_defs,
        "missing_collider_fallbacks": missing_colliders,
        "source_sha256": hashes,
        "inactive_nodes": sum(not n["active"] for n in nodes.values()),
        "stale_overrides": stale_overrides,
    }
    recipe["navigation"] = {
        name: value
        for name, value in (
            ("bounds", args.nav_bounds), ("spawn", args.spawn), ("mission", args.mission)
        )
        if value is not None
    }
    target = out / "town.source.json"
    target.write_text(json.dumps(recipe, separators=(",", ":")) + "\n")
    print(
        f"RESOLVED {len(instances)} prefab instances, {len(rendered)} visible mesh placements, {len(colliders)} colliders, {len(material_defs)} materials; {len(missing_colliders)} missing collider references use render meshes",
        flush=True,
    )
    if args.resolve_only:
        return
    subprocess.run(
        [
            args.blender,
            "-b",
            "-t",
            "2",
            "--python-exit-code",
            "1",
            "--python",
            str(ROOT / "scripts/bake_town.py"),
            "--",
            str(target),
        ],
        check=True,
    )


if __name__ == "__main__":
    main()
