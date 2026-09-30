"""Collect selected Unity prefabs, their FBXs and their actual material textures.

python3 scripts/import_western.py --source /path/to/Assets/PolygonWestern --blender blender
Requires PyYAML for Unity's text serialization and Blender 3.6 for FBX conversion.
Source files are copied read-only; normal game builds use the generated asset pack.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
import shutil
import subprocess

import yaml

ROOT = Path(__file__).resolve().parents[1]
ASSETS = {
    "crate": "Props/SM_Prop_Crate_01",
    "barrel": "Props/SM_Prop_Barrel_01",
    "sacks": "Props/SM_Prop_Sack_04",
    "woodpile": "Props/SM_Prop_Wood_Pile_01",
    "lantern": "Props/SM_Prop_Lantern_01",
    "coffin": "Props/SM_Prop_Coffin_01",
    "cart": "Vehicles/SM_Veh_Cart_01",
    "fence": "Buildings/SM_Bld_Fence_02",
    "saloon": "Buildings/SM_Bld_Saloon_01",
    "jail": "Buildings/SM_Bld_Jail_01",
    "church": "Buildings/SM_Bld_Church_01",
    "station": "Buildings/SM_Bld_TrainStation_01",
    "water_tower": "Buildings/SM_Bld_Water_Tower_01",
    "well": "Buildings/SM_Bld_Well_01",
    "rail": "Environments/SM_Env_Train_Track_Straight_01",
    "ground": "Environments/SM_Env_Sand_Ground_01",
    "rock_a": "Environments/SM_Env_Rock_01",
    "rock_b": "Environments/SM_Env_Rock_02",
    "cactus_a": "Environments/SM_Env_Cactus_01",
    "cactus_b": "Environments/SM_Env_Cactus_03",
    "cliff_wall": "Environments/SM_Env_Cliff_Straight_02",
    "cliff_pillar": "Environments/SM_Env_Cliff_Pillar_01",
    "cliff_cap": "Environments/SM_Env_Cliff_Cap_01",
    "grass_a": "Environments/SM_Env_Grass_01",
    "grass_b": "Environments/SM_Env_Grass_03",
    "stick_a": "Props/SM_Prop_Stick_01",
    "stick_b": "Props/SM_Prop_Stick_02",
    "skull": "Props/SM_Prop_Cow_Skull_01",
    "bones": "Environments/SM_Env_BonePile_Small_01",
}


def documents(path):
    text = path.read_text()
    headers = re.findall(r"^--- !u!(\d+) &(-?\d+)(?: stripped)?", text, re.M)
    text = re.sub(r"^%.*\n", "", text, flags=re.M)
    text = re.sub(r"^--- !u!\d+ &-?\d+(?: stripped)?", "---", text, flags=re.M)
    # Unity's hexadecimal buffers are strings even when they contain digits only.
    text = re.sub(r'^(\s*(?:m_IndexBuffer|_typelessdata):) (.*)$', r'\1 "\2"', text, flags=re.M)
    loader = getattr(yaml, "CSafeLoader", yaml.SafeLoader)
    return [(int(kind), int(key), next(iter(doc.values())))
            for (kind, key), doc in zip(headers, yaml.load_all(text, Loader=loader))]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, default=ROOT / "assets/western/source")
    parser.add_argument("--blender", default="blender")
    args = parser.parse_args()
    source = args.source.resolve()
    output = ROOT / "assets/western"
    copied = output / "source"
    output.mkdir(parents=True, exist_ok=True)
    index = {}
    for path in source.rglob("*.meta"):
        guid = re.search(r"^guid: (\w+)", path.read_text(), re.M)
        if guid:
            index[guid[1]] = path.with_suffix("")
    hashes = {}

    def collect(path):
        relative = path.relative_to(source)
        target = copied / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        if path != target:
            shutil.copy2(path, target)
        hashes[str(relative)] = hashlib.sha256(path.read_bytes()).hexdigest()
        meta = path.with_name(path.name + ".meta")
        if meta.exists() and meta != target.with_name(target.name + ".meta"):
            shutil.copy2(meta, target.with_name(target.name + ".meta"))
        return str(relative)

    def resolve(reference):
        guid = reference.get("guid")
        if guid not in index:
            raise RuntimeError(f"Missing asset reference: {reference}")
        return index[guid]

    materials = {}

    def material(reference):
        path = resolve(reference)
        key = path.stem
        if key in materials:
            return key
        collect(path)
        data = next(obj for kind, _, obj in documents(path) if kind == 21)
        props = data["m_SavedProperties"]
        textures = {k: v for entry in props.get("m_TexEnvs", []) for k, v in entry.items()}
        colors = {k: v for entry in props.get("m_Colors", []) for k, v in entry.items()}
        floats = {k: v for entry in props.get("m_Floats", []) for k, v in entry.items()}
        base = textures.get("_BaseMap", textures.get("_MainTex", {}))
        texture = base.get("m_Texture", {})
        color = colors.get("_BaseColor", colors.get("_Color", dict(r=1, g=1, b=1, a=1)))
        materials[key] = {
            "texture": collect(resolve(texture)) if texture.get("guid") else None,
            "tint": [color.get(c, 1) for c in "rgba"],
            "uv_scale": base.get("m_Scale", dict(x=1, y=1)),
            "uv_offset": base.get("m_Offset", dict(x=0, y=0)),
            "metallic": floats.get("_Metallic", 0),
            "roughness": 1 - floats.get("_Smoothness", floats.get("_Glossiness", 0)),
            "transparent": floats.get("_Surface", 0) == 1 or floats.get("_Mode", 0) in (2, 3),
            "source": str(path.relative_to(source)),
        }
        return key

    assets = []
    for name, prefab in ASSETS.items():
        path = source / "Prefabs" / (prefab + ".prefab")
        collect(path)
        docs = documents(path)
        renderers = {obj["m_GameObject"]["fileID"]: obj for kind, _, obj in docs if kind == 23}
        parts, models, colliders = {}, set(), []
        for kind, _, obj in docs:
            if kind == 33:
                renderer = renderers.get(obj["m_GameObject"]["fileID"])
                if not renderer or not renderer.get("m_Enabled", 1):
                    continue
                mesh = obj["m_Mesh"]
                model = resolve(mesh)
                if model.suffix.lower() != ".fbx":
                    raise RuntimeError(f"Expected an FBX render mesh: {model}")
                models.add(collect(model))
                meta = yaml.safe_load(model.with_name(model.name + ".meta").read_text())
                mesh_name = meta["ModelImporter"]["fileIDToRecycleName"][mesh["fileID"]]
                if name == "rail" and mesh_name.endswith("_Dirt"):
                    continue  # The game's continuous floor supplies the track bed.
                parts[mesh_name] = [material(ref) for ref in renderer["m_Materials"]]
            elif kind in (64, 65):
                colliders.append({"kind": "box" if kind == 65 else "mesh", **obj})
        if not parts:
            raise RuntimeError(f"No renderable parts in {path}")
        assets.append({"name": name, "prefab": str(path.relative_to(source)),
                       "models": sorted(models), "parts": parts, "unity_colliders": colliders})
        if name in ("stick_a", "stick_b"):
            assets[-1]["ground_debris"] = True
        print(f"COLLECTED {name}: {len(parts)} parts", flush=True)
    recipe = {"format": 1, "assets": assets, "materials": materials, "source_sha256": hashes}
    recipe_path = output / "western.source.json"
    recipe_path.write_text(json.dumps(recipe, indent=2) + "\n")
    subprocess.run([args.blender, "--background", "--threads", "2", "--python",
                    str(ROOT / "scripts/bake_western.py"), "--", str(recipe_path)], check=True)


if __name__ == "__main__":
    main()
