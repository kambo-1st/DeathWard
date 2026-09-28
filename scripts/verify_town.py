"""Audit the imported scene against its resolved Unity recipe (requires NumPy/Pillow)."""

import argparse
import hashlib
import io
import json
from pathlib import Path
import struct
import re
import numpy as np
from PIL import Image

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument("--pack", type=Path, default=Path(__file__).resolve().parents[1] / "assets/town")
args = parser.parse_args()
root = args.pack.resolve()
r = json.loads((root / "town.source.json").read_text())
m = json.loads((root / "town.manifest.json").read_text())
scene = (root / "source" / r["scene"]).read_text()
instance_ids = {int(i) for i in re.findall(r"^--- !u!1001 &(-?\d+)", scene, re.M)}
assert instance_ids == {p["id"] for p in r["prefab_instances"]}
assert len(instance_ids) == m["source_prefab_instances"]
assert len(r["renderers"]) == len(m["placements"]) == m["active_mesh_placements"]
assert len(r["renderers"]) > 0
assert len({p["object"] for p in m["placements"]}) == len(m["placements"])
for name, hash_ in r["source_sha256"].items():
    assert (
        hashlib.sha256((root / "source" / name).read_bytes()).hexdigest() == hash_
    ), name
for name, hash_ in m["output_sha256"].items():
    assert hashlib.sha256((root / name).read_bytes()).hexdigest() == hash_, name
reflection = np.diag([-1, 1, 1, 1])
for source, placed in zip(r["renderers"], m["placements"]):
    assert source["object"] == placed["object"]
    assert np.allclose(
        reflection @ np.array(source["matrix"]) @ reflection,
        np.array(placed["transform"]).reshape(4, 4),
        atol=0.0001,
    )
    asset = m["assets"][placed["asset"]]
    assert (
        asset["mesh_source"] == source["mesh"]
        and asset["materials"] == source["materials"]
    )
# Audit the actual runtime catalog as well as the conversion manifest.
assets = []
placements = []
lines = (root / "town.scene").read_text().splitlines()
version = int(lines[0].split()[1])
assert version in (1, 2)
motion = {}
for line in lines[1:]:
    fields = line.split()
    if fields[0] == "asset":
        name = fields[1]
        asset = m["assets"][name]
        assert [int(fields[2]), int(fields[3])] == [asset["first_mesh"], asset["mesh_count"]]
        assert np.allclose(np.array(fields[5:], dtype=float).reshape(2, 3), asset["bounds"], atol=.0001)
        assets.append(name)
    elif fields[0] == "instance":
        offset = 3 if version == 2 else 2
        source_id = fields[2] if version == 2 else None
        placements.append((assets[int(fields[1])], source_id, np.array(fields[offset:], dtype=float)))
    elif fields[0] == "motion":
        assert fields[1] not in motion
        motion[fields[1]] = [float(v) for v in fields[2:]]
assert motion == m.get("object_motion", {})
assert len(placements) == len(m["placements"])
for (asset, source_id, transform), placed in zip(placements, m["placements"]):
    assert asset == placed["asset"]
    assert source_id is None or source_id == placed["object"]
    assert np.allclose(transform, placed["transform"], atol=.0001)
raw = (root / "town.glb").read_bytes()
n = struct.unpack_from("<I", raw, 12)[0]
gltf = json.loads(raw[20 : 20 + n])
for mesh in gltf["meshes"]:
    for primitive in mesh["primitives"]:
        material = gltf["materials"][primitive["material"]]
        if not r["materials"][material["name"]].get("uses_vertex_colors", True):
            assert "COLOR_0" not in primitive["attributes"], "Unity Lit ignores auxiliary vertex colors"
bin_start = 28 + n
originals = {}
for material in r["materials"].values():
    if material["texture"]:
        p = root / "source" / material["texture"]
        image = Image.open(p).convert("RGBA")
        originals[p.stem] = (image.size, image.tobytes())
for entry in gltf["images"]:
    view = gltf["bufferViews"][entry["bufferView"]]
    offset = bin_start + view.get("byteOffset", 0)
    image = Image.open(io.BytesIO(raw[offset : offset + view["byteLength"]])).convert(
        "RGBA"
    )
    assert (image.size, image.tobytes()) == originals[entry["name"]], entry["name"]
assert len(gltf.get("images", [])) == len(originals) == m["embedded_images"]
for material in gltf["materials"]:
    assert (
        material["pbrMetallicRoughness"]["baseColorFactor"]
        == r["materials"][material["name"]]["tint"]
    )
# A legacy FBX uses an explicit import scale rather than an additional file-unit
# factor. The original sky must surround the scene, not become a ball in town.
for sky in (p for p in m["placements"] if p["name"] == "SkyDome"):
    bounds = m["assets"][sky["asset"]]["bounds"]
    assert (bounds[1][0] - bounds[0][0]) * abs(sky["transform"][0]) > 1000
assert m["navigation"]["walkable_cells"] > 10000
print(
    f"PASS {len(instance_ids)} prefab instances, {len(m['placements'])} exact scene transforms/material mappings, {len(r['source_sha256'])} source hashes, {len(originals)} pixel-identical textures, sky scale and output hashes"
)
