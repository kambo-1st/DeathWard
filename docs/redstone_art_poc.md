# Redstone art-direction experiment

This is an **opt-in rendering experiment**, developed on `poc/redstone-art-direction`
from `8e17f81`. The original look remains the default.

```sh
./build/deathward --hub redstone --art-poc
# The same look in the editor:
./build/deathward --hub redstone --editor --art-poc
```

For the browser, append `?hub=redstone&art=poc` to the game URL. Relative hosting
paths work as before. **F6** switches between the POC and original rendering in
Redstone, including its editor. A small label identifies the comparison mode.
F6 retains its existing cheat behavior in missions.

To revert the appearance, press F6 or restart without `--art-poc` / `art=poc`.
The toggle is deliberately not saved. Other hubs and missions use their original
rendering even when the option was enabled at launch.

## Direction

Bone-colored sand, umber dirt, bleached timber, faded teal cloth and rust-colored
character accents replace the clean gold/plum treatment in this experiment.
The existing geometry, imported textures, scene layout and animations remain.

- World-space soil variation, fine grit, irregular approach footprints, small
  gravel clusters using an existing rock mesh, and dirt/sand collecting around
  static objects. Gravel sits on sampled source terrain. The original feathered
  road meshes and wheel-rut shapes remain visible.
- Material-specific diffuse weathering: wood fibers and bleaching, dusty lower
  surfaces and ledges, less saturated rock and canvas. This is a treatment of
  the existing diffuse renderer, **not a new PBR/roughness pipeline**.
- A lower sun (about 29 degrees), readable cool fill, and the existing filtered
  shadows. A derived contact mask darkens the soil immediately around objects;
  this is local ground contact shading, **not general screen-space AO**.
- Sparse, low-opacity drifting dust near the road/rail works and depth-dependent
  distant haze. Dust and cloth follow simulation/editor-preview time, so pause
  freezes them. The POC has no full-screen blur, much less bloom, and subtle grain.
- Patched, moving teal shade cloth over the existing market and repair tables,
  thin supports, and palisade repair straps. These follow static parent placements
  when edited; their shadow geometry respects the parent's Cast shadows setting.
- A removable rust poncho for the protagonist, teal scout wrap, shorter commander's
  shoulder cloth and muted plum shawl for the wife. They use the existing torso
  bones and original animation clips; the original rigs and GLBs are untouched.

The added cloth, repair details and gravel are a derived visual layer, not editable
scene instances or new collision. Move their source table/wall/scrub to reposition
them; changing an anchor into an animated prop is outside this POC's dressing scope.
There is no new NPC occupation system (carrying, smoking or wagon repair) yet;
existing residents continue their authored routes and idle animations.

## Preservation and implementation

No source model, texture, scene, navigation file, road generator or campaign format
is changed. The POC does not migrate saves or mark editor documents as modified.
Contact maps and accessory meshes are built in memory, released with their renderer,
and rebuilt after document edits. A copied lighting configuration supplies the POC
sun; switching back invalidates the shadow cache and restores the authored lights.

`src/render/RedstoneArt.cpp` owns the palette, weathering, contact map and dressing.
`ArtWardrobe.cpp` owns the small rig-attached accessories. `TownScene` selects the
profile; `PostProcess` applies its restrained finishing pass. The native and WebGL 2
builds use the same implementation.

## Review and verification

```sh
cmake --build build --target deathward_art_direction_tests --parallel 1
./build/deathward_art_direction_tests
DEATHWARD_BROWSER=/path/to/chromium node web/art-direction-test.cjs
```

The native check captures matching before/after fort, frontage, camp and close-up
views. It requires **pixel-identical original rendering after toggling off**, an
unchanged serialized scene and instance count, and no activation in Black Creek.
It also captures character accessories at close range and in a walking pose.
The browser test exercises the URL option, actual F6 input, editor comparison,
unchanged scene bytes, and default-off reload, while checking WebGL errors.

Review `artifacts/art-poc-before-frontage.png` against
`artifacts/art-poc-after-frontage.png`, plus the matching `fort` and `camp` images.
`artifacts/art-poc-original-assets.sha256` records the pre-edit Redstone assets.
The experiment is intended for visual review; the palette and accessory shapes
are provisional, and have not been performance-profiled on low-end browsers.
