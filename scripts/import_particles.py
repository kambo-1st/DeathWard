"""Import the fireplace POC from PolygonParticleFX (Python + PyYAML + Blender 3.6).

Only the selected fire mesh, ember/smoke textures and prefab parameters are
shipped. Unity ParticleSystem components are translated, not executed by raylib.
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


def documents(path):
    text = re.sub(r"^%.*\n", "", path.read_text(), flags=re.M)
    return list(yaml.safe_load_all(re.sub(r"--- !u!\d+ &-?\d+", "---", text)))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, default=Path(
        "/mnt/c/Users/bohus/My project (1)/Assets/PolygonParticleFX"))
    parser.add_argument("--blender", default="blender")
    args = parser.parse_args()
    out = ROOT / "assets/particles"
    out.mkdir(parents=True, exist_ok=True)
    sources = ["Prefabs/FX_Fire_Small_03.prefab", "Prefabs/FX_Fire_Small_01.prefab",
               "Models/SM_Flame_FX.fbx", "Models/SM_Flame_FX.fbx.meta",
               "Materials/PolygonParticleFX_Default_01.mat", "Materials/PolygonParticleFX_Circle.mat",
               "Textures/PolygonParticles_Circle_01.png", "Textures/PolygonParticles_Smoke_01.png"]
    manifest = {"format": 1, "source_pack": "PolygonParticleFX", "source_sha256": {
        p: hashlib.sha256((args.source / p).read_bytes()).hexdigest() for p in sources}}
    for source, dest in [(sources[-2], "ember.png"), (sources[-1], "smoke.png")]:
        shutil.copyfile(args.source / source, out / dest)
    lines = ["DEATHWARD_PARTICLES 1"]

    def parameter(value):
        if value["minMaxState"] not in (0, 3):
            raise ValueError("POC expects constant or random-between-constants initial values")
        return [value["minScalar"] if value["minMaxState"] == 3 else value["scalar"], value["scalar"]]

    def emit(key, *values):
        lines.append(key + " " + " ".join(str(v) for v in values))

    for name, prefab, mode, resource in [
            ("flame", sources[0], "mesh", "flame.glb"),
            ("ember", sources[1], "additive", "ember.png")]:
        systems = [d["ParticleSystem"] for d in documents(args.source / prefab) if "ParticleSystem" in d]
        x = systems[-1] if name == "ember" else systems[0]
        initial = x["InitialModule"]
        emit("emitter", name, mode, resource)
        emit("rate", x["EmissionModule"]["rateOverTime"]["scalar"])
        for key, source in [("lifetime", "startLifetime"), ("size", "startSize"), ("speed", "startSpeed")]:
            emit(key, *parameter(initial[source]))
        emit("gravity", -9.81 * initial["gravityModifier"]["scalar"])
        emit("radius", x["ShapeModule"]["radius"]["value"])
        rotation = x["RotationModule"]
        emit("spin", *parameter(rotation["y"] if rotation["separateAxes"] else rotation["curve"]))
        noise = x["NoiseModule"]
        emit("noise", noise["strength"]["scalar"] if noise["enabled"] else 0, noise["frequency"])
        emit("emission", 1.65 if name == "flame" else 1)
        curve = x["SizeModule"]["curve"]
        for key in curve["maxCurve"]["m_Curve"]:
            emit("sizekey", key["time"], *(key[k] * curve["scalar"] for k in ("value", "inSlope", "outSlope")))
        gradient = x["ColorModule"]["gradient"]["maxGradient"]
        for i in range(gradient["m_NumColorKeys"]):
            emit("color", gradient[f"ctime{i}"] / 65535,
                 *(gradient[f"key{i}"][c] for c in ("r", "g", "b")))
        for i in range(gradient["m_NumAlphaKeys"]):
            emit("alpha", gradient[f"atime{i}"] / 65535, gradient[f"key{i}"]["a"])
        lines.append("end")

    # A restrained chimney/campfire plume using the supplied smoke texture.
    # This layer is authored for DeathWard; it is not a claimed Unity prefab clone.
    lines.extend("""emitter smoke billboard smoke.png
rate 4
lifetime 2.4 3.4
size .22 .36
speed .35 .55
gravity .08
radius .11
spin -.25 .25
noise .1 .45
emission 1
sizekey 0 .6 1 1
sizekey 1 2.7 1 1
color 0 .40 .36 .32
color 1 .55 .53 .50
alpha 0 0
alpha .18 .19
alpha .6 .12
alpha 1 0
end""".splitlines())
    (out / "fire.particles").write_text("\n".join(lines) + "\n")
    subprocess.run([args.blender, "--background", "--python", str(ROOT / "scripts/bake_particle_mesh.py"),
                    "--", str(args.source / sources[2]), str(out / "flame.glb")], check=True)
    manifest["adaptations"] = [
        "FX_Fire_Small_03 lifetime, rate, size curve, color/alpha gradients and spin; original flame mesh.",
        "FX_Fire_Small_01 ember lifetime, rate, size/color/alpha, gravity and original Circle_01 texture.",
        "Analytic sine turbulence replaces Unity noise; ember billboards replace stretched billboards.",
        "DeathWard authors smoke, hearth offsets, effect scale, HDR emission and warm point lighting."]
    manifest["output_sha256"] = {p.name: hashlib.sha256(p.read_bytes()).hexdigest()
                                for p in (out / f for f in ["flame.glb", "ember.png", "smoke.png", "fire.particles"])}
    (out / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n")
    print("Imported fireplace fire, ember texture, smoke texture and particle curves")


if __name__ == "__main__":
    main()
