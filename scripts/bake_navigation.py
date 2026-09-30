"""Rebuild a town's navigation with the same geometry/headroom rules as the editor."""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import subprocess
import numpy as np

ROOT = Path(__file__).resolve().parents[1]


def rebake_navigation(pack, baker):
    pack, baker = Path(pack).resolve(), Path(baker).resolve()
    if not baker.is_file():
        raise RuntimeError("Build the native baker first: cmake --build build --target deathward_bake_navigation")
    subprocess.run([str(baker), str(pack)], check=True)
    metadata = pack / "town.manifest.json"
    if metadata.is_file():
        manifest = json.loads(metadata.read_text())
        raw = (pack / "town.nav").read_bytes()
        width, depth, min_x, min_z, cell, *markers = struct.unpack_from("<II9f", raw, 8)
        heights = np.frombuffer(raw, dtype="<f4", offset=52)
        assert heights.size == width * depth
        manifest["navigation"].update(
            algorithm="geometry_interiors_v2", standing_clearance=1.9,
            dimensions=[width, depth], cell=cell, walkable_cells=int(np.isfinite(heights).sum()),
            spawn=markers[:3], mission=markers[3:],
        )
        for name in ("town.nav", "town.scene"):
            manifest["output_sha256"][name] = hashlib.sha256((pack / name).read_bytes()).hexdigest()
        metadata.write_text(json.dumps(manifest, indent=2) + "\n")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--pack", type=Path, default=ROOT / "assets/town")
    parser.add_argument("--baker", type=Path, default=ROOT / "build/deathward_bake_navigation")
    args = parser.parse_args()
    rebake_navigation(args.pack, args.baker)
