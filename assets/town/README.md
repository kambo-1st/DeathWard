# Original PolygonWestern town hub

DeathWard starts in the original `PolygonWestern/Scenes/Demo.unity` town. This import retains the authored arrangement, rather than generating a town from the modular room assets. The bandit can explore the outdoor streets and approach the railway station's added mission board. Missions use the existing seeded dungeon generator; their result screen returns to the town.

The source scene contains **1,269 prefab instances**. Resolving the prefab hierarchy, inactive objects and scene overrides produces **1,516 active mesh placements**, represented by 398 mesh/material sections, 20 materials and **12 original embedded textures**. These include the color atlases, signs and sky texture. Instance positions, rotations, scales, parent transforms, material replacements and mesh overrides are retained. Converting Unity's coordinate handedness reflects world X consistently; no objects are rearranged or fitted to generated room dimensions.

## Assets and conversion

- `town.glb`: shared local meshes and material variants, with embedded textures.
- `town.scene`: mesh ranges, original instance matrices and directional/point lights.
- `town.nav`: outdoor navigation sampled from original scene colliders.
- `town.source.json`: resolved Unity recipe, source references and hashes.
- `town.manifest.json`: output hashes, placement audit, mesh bounds and navigation summary.
- `source/`: the original scene and all resolved prefabs, FBXs, collider meshes, materials, textures and metadata needed to rebuild it.

Normal builds only package the GLB, scene catalog and navigation file. They do not need Unity, Blender, Python or access to the Windows project folder. Keep `assets/town` beside the executable when moving a build.

Rebuilding requires Python 3 with NumPy and PyYAML, plus Blender 3.6 LTS:

```sh
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

Navigation uses the imported box/capsule and triangle colliders, including Unity's serialized convex mesh assets. Three collider references are missing from the supplied source pack; their matching visible mesh is used and the substitutions are recorded. An outdoor height grid has 0.4-unit spacing, rejects steep/disconnected surfaces, allows steps up to 0.6 units, and reserves clearance around obstacles. It follows street elevation and excludes disconnected roofs. Building interiors, upper floors and distant scenic terrain are not a navigable hub feature.

The added arrival point and mission board lie on connected street terrain. Click-to-walk preserves the selected terrain point, moves directly across open ground, and smooths routes around obstacles without cutting blocked corners. Holding a ground click steers; holding a board click keeps approaching the board until release. WASD moves relative to the camera with collision checks. The mission button walks to the board before opening its menu. Hub exploration does not begin a campaign run or resolve an outcome. New offers receive a random seed, which remains editable for replay. The original scene arrangement remains fixed while mission layouts vary.

Raylib uses the original textures, UVs, vertex colors, material tints, alpha and scene light transforms/colors with an instanced diffuse shader. Glass and water transparency draw after opaque geometry; the sky is unlit. Unity URP post-processing, baked lighting, shadow maps, water effects and material-specific shader behavior are not reproduced pixel for pixel. No Unity scripts execute in DeathWard.

## Verify

```sh
python3 scripts/verify_town.py  # NumPy and Pillow; verifies source/output hashes and original texture pixels
./build/deathward_hub_tests
./build/deathward_town_assets_tests  # requires an OpenGL display
./build/deathward_input_tests       # includes the hub-to-mission-to-hub flow
./build/deathward --smoke --scene hub --frames 90 --screenshot artifacts/town-hub.png
```

The audit compares every imported placement and material mapping with the resolved source, verifies all 691 source hashes and 12 embedded images, and checks the original sky scale. Tests cover navigation, station reachability, elevation, barriers, seed selection, launch/return, asset loading away from the repository, rendering and resource cleanup.
