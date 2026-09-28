# PolygonParticleFX fireplace proof of concept

The stone-ring fire beside Black Creek's starting point uses the original
`SM_Flame_FX` mesh from `PolygonParticleFX`, the `FX_Fire_Small_03` emission,
lifetime, rotation, size and color/opacity curves, and the ember settings from
`FX_Fire_Small_01`. `ember.png` and `smoke.png` are byte-identical copies of
`PolygonParticles_Circle_01.png` and `PolygonParticles_Smoke_01.png`.
The flame material has no source texture; its color comes from the particle gradient.

This is a selected-effect port, not a Unity ParticleSystem interpreter. DeathWard
adds hearth-sized placement/scaling, a restrained smoke layer, HDR emission,
warm flickering point lighting and analytic turbulence in place of Unity noise.
Embers use ordinary billboards rather than Unity's stretched billboard renderer.
The pack contains 180 prefabs; only the fireplace effect is ported in this POC.

## Files and reuse

- `flame.glb`: original low-poly FBX geometry, baked into meter-scale Y-up coordinates.
- `fire.particles`: portable emitter definitions; rates, random ranges, Hermite
  size curves and linear color/alpha keys are data rather than gameplay code.
- `town.attachments`: exact prop labels, emitter names, local offsets, effect scales
  and optional light ranges. Both towns' campfire assets use the same library.
- `manifest.json`: source/output hashes and the deliberate adaptations.

F4 opens the editor. Search **CampFire**, add or select the stone-ring prop, and
use **Play preview**. Move, rotate, scale, duplicate, delete, undo and save operate
on the prop; its attached fire follows automatically. Preview pause/reset also
controls particles. There is no standalone particle-authoring panel yet.
The town's closed metal `SM_Prop_Fireplace_01` stoves are unchanged.

The demo is `fireplace-poc` at `(-2, .06, 0)`, close to Black Creek's spawn.
All original Unity placements remain intact. Existing browser-authored towns
are preserved; add a CampFire in the editor if that saved scene predates the demo.

Particles are prewarmed and sampled deterministically from the scene clock and
instance ID. Culling/revisiting cannot restart a fire; pause freezes it. Alpha
particles are sorted from back to front, test scene depth and do not write depth;
embers use additive blending. The existing bloom/fog/color pass processes them.
At most 4,096 nearby particles and four local fire lights render per view.
Point lights have no additional shadow maps. Fire is cosmetic in this POC.

## Rebuild

Normal native/WASM builds use these checked-in files and need no Windows asset
directory, Unity, Blender or Python. To import again, use Python with PyYAML and
Blender 3.6 LTS:

```sh
python3 scripts/import_particles.py \
  --source '/mnt/c/Users/bohus/My project (1)/Assets/PolygonParticleFX' \
  --blender /path/to/blender
```

After a fresh original town import, `python3 scripts/add_fireplace_demo.py`
restores the optional demo placement and rebakes navigation. It requires the
native `deathward_bake_navigation` target. Source Unity assets are required only
for rebuilding the imported effect.
