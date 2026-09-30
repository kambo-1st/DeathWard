# Original PolygonWestern town hub

DeathWard starts in the original `PolygonWestern/Scenes/Demo.unity` town. This import retains the authored arrangement, rather than generating a town from the modular room assets. The bandit can explore the streets and building interiors, and approach the railway station's added mission board. Missions use the existing seeded dungeon generator; their result screen returns to the town.

The source scene contains **1,269 prefab instances**. Resolving the prefab hierarchy, inactive objects and scene overrides produces **1,516 active mesh placements**, represented by 398 mesh/material sections, 20 materials and **12 original embedded textures**. These include the color atlases, signs and sky texture. Instance positions, rotations, scales, parent transforms, material replacements and mesh overrides are retained. Converting Unity's coordinate handedness reflects world X consistently; no objects are rearranged or fitted to generated room dimensions.

One additional stone-ring campfire, `fireplace-poc`, sits beside the starting area
at `(-2, .06, 0)`. Its animated flames, embers, smoke and warm light use the
[PolygonParticleFX proof of concept](../particles/README.md). The original 1,516
placements are preserved. A second authored placement, `station-entrance-steps`, uses the original textured stair asset to connect the raised station platform to the street. The manifest records both additions separately.

## Assets and conversion

- `town.glb`: shared local meshes and material variants, with embedded textures.
- `town.scene`: mesh ranges, original instance matrices, lights, prop motion and stable train path/group bindings.
- `town.nav`: street/interior navigation baked from the scene geometry with standing headroom; moving props/vehicles supply their own collision.
- `town.labels`: source asset names for the editor, hollow building geometry and automatic door recognition.
- `town.source.json`: resolved Unity recipe, source references and hashes.
- `town.manifest.json`: output hashes, placement audit, mesh bounds and navigation summary.
- `source/`: the original scene and all resolved prefabs, FBXs, collider meshes, materials, textures and metadata needed to rebuild it.

Normal builds package the GLB, scene catalog, navigation file and editor labels. They do not need Unity, Blender, Python or access to the Windows project folder. Keep `assets/town` beside the executable when moving a build. In a development checkout, the game and editor prefer the source `assets/town` folder so saved edits survive builds.

Use **F4 in the hub** or `./build/deathward --editor` to edit placements in 3D. Saving updates the scene and rebuilds navigation from the edited visible geometry, preserving the original model library and textures. See the [editor guide](../../docs/town_editor.md) for controls, backups and navigation limits. The source manifest describes the original import; intentionally edited scene/navigation files no longer match its original hashes.

Rebuilding requires Python 3 with NumPy and PyYAML, plus Blender 3.6 LTS and the native navigation baker:

```sh
cmake --build build --target deathward_bake_navigation
python3 scripts/import_town.py --blender /path/to/blender
```

To collect from the original Unity project again:

```sh
python3 scripts/import_town.py \
  --source '/mnt/c/Users/bohus/My project (1)/Assets/PolygonWestern' \
  --blender /path/to/blender
```

The resolver follows scene and prefab transform hierarchies, added child objects, component additions, material assignments and overrides. Fourteen stale overrides refer to objects that no longer exist in their source prefabs; they are recorded and ignored, matching their lack of a target. The converter preserves **103 FBX rotation pivots**, including hinged doors. Both old and current Unity importer metadata are supported. The sky's legacy explicit import scale is applied without a second file-unit conversion.

## Navigation and rendering

The retained source audit includes imported box/capsule and triangle colliders, including Unity's serialized convex mesh assets; three missing source references have recorded mesh substitutions. Runtime navigation is rebuilt from visible geometry using the same baker as the editor. A 0.2-unit grid keeps hollow building floors reachable below their roofs, requires 1.9 units of headroom, allows steps up to 0.6 units and reserves player clearance around obstacles. Doors open automatically on approach; glass follows its door hinge. Entering cuts away the roof and upper walls while preserving the original textured floors and furnishings. Navigation stores one traversable height per X/Z cell, so overlapping upstairs/downstairs routes remain limited. Disconnected roofs and scenic terrain remain inaccessible.

Both original trains now follow the existing rail loop as eight vehicle groups. The sixteen separately modeled locomotive wheels rotate around their imported axles. Current vehicle hulls provide moving collision and navigation occupancy; their old static footprints are removed. The two tumbleweeds use wind-driven rolling. All original meshes, materials, textures and rest matrices remain intact. See the [motion design](../../docs/object_animation_proposal.md) for behavior and remaining mechanical/editor limitations.

The added arrival point and mission board lie on connected street terrain. Click-to-walk preserves the selected terrain point, moves directly across open ground, and smooths routes around obstacles without cutting blocked corners. Holding a ground click steers; holding a board click keeps approaching the board until release. WASD moves relative to the camera with collision checks. The mission button walks to the board before opening its menu. Hub exploration does not begin a campaign run or resolve an outcome. New offers receive a random seed, which remains editable for replay. The original scene arrangement remains fixed while mission layouts vary.

Raylib uses the original textures, UVs, vertex colors, material tints, alpha and scene light transforms/colors with an instanced lighting shader. Filtered sun shadows cover scenery and the animated bandit, with warm ground bounce and cooler sky fill. Glass and water transparency draw after opaque geometry; the sky is unlit. Unity URP post-processing, baked lighting, water effects and material-specific shader behavior are not reproduced pixel for pixel. No Unity scripts execute in DeathWard.

## Verify

```sh
python3 scripts/verify_town.py  # NumPy and Pillow; verifies source/output hashes and original texture pixels
./build/deathward_hub_tests
./build/deathward_town_assets_tests  # requires an OpenGL display
./build/deathward_input_tests       # includes the hub-to-mission-to-hub flow
./build/deathward --smoke --scene hub --frames 90 --screenshot artifacts/town-hub.png
```

The audit compares every imported placement and material mapping with the resolved source, verifies all 691 source hashes and 12 embedded images, and checks the original sky scale. Tests cover navigation, station reachability, elevation, barriers, seed selection, launch/return, asset loading away from the repository, rendering and resource cleanup.

The navigation baker is also available without reimporting meshes or textures:

```sh
python3 scripts/bake_navigation.py --pack assets/town
```

It uses the same geometry and headroom rules as an editor save, allowing passage beneath high entrance beams while retaining posts and low ceilings. It updates only navigation and its manifest metadata and keeps `town.nav.bak`. `DWTNAV03` marks the interior rules; older navigation remains readable and is rebuilt once on game startup, including saved browser layouts, without replacing the authored scene.

To restore the added station access after a fresh import, run `python3 scripts/add_station_steps.py`. Original Unity placements remain unchanged. `scripts/update_building_labels.py` restores child building/door labels in older converted packs without reconverting their models or textures.
