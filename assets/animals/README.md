# Polyperfect animals

The complete current animal prefab catalog from `polyperfect/Low Poly Animated Animals` is converted: **98 textured variants across 66 animal folders**, with **784 exported animation clips** across those variants. Shared source animations appear in each applicable variant. See [CATALOG.md](CATALOG.md) for every runtime ID, source prefab and clip count. Archived `Legacy` alternatives and demo scenes are not separate catalog entries.

Each GLB embeds its original albedo RGB pixels, Unity material tint, UVs, skin weights and skeletal animations. The source materials are opaque; unused texture alpha is made fully opaque for raylib, while the original RGBA files remain untouched under `source/`. FBX scene units and animated ancestors are baked into a meter-scale, Y-up rig. Extra mesh-only bone tips follow their animated parents. Horizontal root travel is removed so navigation controls position; vertical motion is retained.

The importer supports named FBX takes, Unity's configured frame ranges, and 65 standalone Unity transform-animation files. Clip durations retain their source sampling rate. Separate animation-library scales are matched to the textured rig by bone segment lengths. Renderer and particle-component curves are recorded as excluded metadata; these are not skeletal animations. The male elephant keeps the textured rig's mesh and UVs, with its extra object scale removed and the animation FBX's matching rest skeleton replacing its inconsistent bind skeleton. The wool sheep retains its own mesh and texture but uses the ordinary sheep's compatible skeleton and corresponding 13 takes: the separate wool FBX deforms incorrectly even when played directly in Blender.

Runtime selects suitable idle, locomotion and optional eating clips, including fly, swim and slither names. Animal skinning preserves nonuniform bone scales and transforms lighting normals without position offsets. All other takes remain available in each GLB. Models load on demand, share assets and use independent animation clocks. Lighting, shadows, fog and color processing use the town's render pipeline. Native and browser packages contain all 98 GLBs and placement files; retained source FBXs and conversion metadata are excluded.

Black Creek still contains a horse, cow, cat and two hens near the starting street. They roam within a home radius, rest and eat, follow terrain, and avoid scenery, other residents, the mission board and current train occupancy. Animals are ambient decoration: they do not block the player, fight, drop loot or act as mounts. Simulation stops during pause, mission selection, editing and expeditions. Returning from a mission retains the same residents; switching hubs reloads the destination's population. Frontier currently has no animal placements.

The additional variants are available for placement, rather than automatically added to town. Flying and aquatic models have their animations converted, but the current ambient simulation follows ground navigation; air/water habitats and species-specific behavior need separate gameplay work.

## Placements

Edit `town.animals` to change residents. The header is `DEATHWARD_ANIMALS 1`, followed by one row per resident:

```text
animal stable-id species home-x home-z yaw-degrees scale roam-radius random-seed
```

Use any species ID from [CATALOG.md](CATALOG.md). The original `horse`, `hen`, `cow` and `cat` IDs remain stable. Y is sampled from navigation; yaw zero faces +Z. IDs must be unique. Scale is 0.25–3, radius 0–20, and the population limit is 64. Large animals need an appropriately clear area. If terrain was edited, loading searches up to five units around the home for a clear footprint and skips residents with no suitable placement. Placements are separate from `town.scene` and are **not yet selectable or editable in the town editor**. Reload the town/game after editing this file.

## Rebuild and verify

Requires Blender 3.6 (verified with 3.6.23), Python with PyYAML and Pillow; the asset audit also uses NumPy. Rebuild from the retained originals:

```sh
python3 scripts/import_animals.py --blender /path/to/blender
python3 scripts/verify_animals.py
cmake --build build --parallel 1
ctest --test-dir build --output-on-failure
./build/deathward_animal_model_tests
```

The first import can instead pass `--source '/mnt/c/Users/bohus/My project (1)/Assets/polyperfect'`. The supplied Unity project is read only. `animals.selection.json` explicitly maps every current prefab to its source mesh and material; the importer rejects missing or unselected prefabs. Full conversion runs three independent Blender workers. Use `--only elephant_male` (or multiple IDs) to rebake selected entries. Importing also finalizes opaque textures and regenerates the runtime catalog and documentation.

The graphics check needs a display and writes previews to ignored `artifacts/`. It loads all 98 models, checks every clip at its start/middle/end, and checks runtime blending and independent poses. The asset audit verifies source/output hashes, exact texture RGB and tint, opaque alpha, joint/weight validity and every clip's duration. Original FBXs, texture/material/prefab metadata and SHA-256 hashes are retained for reproducibility. Use these source assets under their existing Polyperfect license.
