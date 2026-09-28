"""Place the fireplace POC beside Black Creek's spawn; retain all Unity placements.

Run after a fresh town import to restore the optional demo, then rebake navigation.
"""
import json
from pathlib import Path
from bake_navigation import rebake_navigation

ROOT = Path(__file__).resolve().parents[1]


def main():
    pack = ROOT / "assets/town"
    labels = dict(line.split(maxsplit=1) for line in (pack / "town.labels").read_text().splitlines())
    lines = (pack / "town.scene").read_text().splitlines()
    if int(lines[0].split()[1]) < 2:
        raise ValueError("Import a town with stable instance IDs first")
    assets = [line.split()[1] for line in lines if line.startswith("asset ")]
    asset = next(name for name in assets if labels[name] == "SM_Env_CampFire_01")
    transform = [1, 0, 0, -2, 0, 1, 0, .06, 0, 0, 1, 0, 0, 0, 0, 1]
    identity = "fireplace-poc"
    lines = [line for line in lines if not line.startswith(f"instance {assets.index(asset)} {identity} ")]
    lines.append(f"instance {assets.index(asset)} {identity} " + " ".join(map(str, transform)))
    (pack / "town.scene").write_text("\n".join(lines) + "\n")
    manifest_path = pack / "town.manifest.json"
    manifest = json.loads(manifest_path.read_text())
    manifest["authored_placements"] = [p for p in manifest.get("authored_placements", []) if p["object"] != identity]
    manifest["authored_placements"].append({"object": identity, "asset": asset, "transform": transform})
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n")
    rebake_navigation(pack, ROOT / "build/deathward_bake_navigation")


if __name__ == "__main__":
    main()
