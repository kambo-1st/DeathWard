"""Audit the imported scene against its resolved Unity recipe (requires NumPy/Pillow)."""

import hashlib
import io
import json
from pathlib import Path
import struct
import numpy as np
from PIL import Image

root = Path(__file__).resolve().parents[1] / "assets/town"
r = json.loads((root / "town.source.json").read_text())
m = json.loads((root / "town.manifest.json").read_text())
assert len(r["prefab_instances"]) == m["source_prefab_instances"] == 1269
assert len(r["renderers"]) == len(m["placements"]) == 1516
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
raw = (root / "town.glb").read_bytes()
n = struct.unpack_from("<I", raw, 12)[0]
gltf = json.loads(raw[20 : 20 + n])
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
assert len(gltf["images"]) == 12
for material in gltf["materials"]:
    assert (
        material["pbrMetallicRoughness"]["baseColorFactor"]
        == r["materials"][material["name"]]["tint"]
    )
# A legacy FBX uses an explicit import scale rather than an additional file-unit
# factor. The original sky must surround the scene, not become a ball in town.
sky = next(p for p in m["placements"] if p["name"] == "SkyDome")
bounds = m["assets"][sky["asset"]]["bounds"]
assert (bounds[1][0] - bounds[0][0]) * abs(sky["transform"][0]) > 1000
assert m["navigation"]["walkable_cells"] > 10000
print(
    f"PASS 1269 prefab instances, 1516 exact scene transforms/material mappings, {len(r['source_sha256'])} source hashes, 12 pixel-identical textures, sky scale and output hashes"
)
