# Polyperfect animals

The first integration uses four species from `polyperfect/Low Poly Animated Animals`:

| Runtime model | Source mesh | Appearance | Exported clips |
| --- | --- | --- | --- |
| `horse.glb` | HorseThoroughbred | Horse_Brown | 8 |
| `hen.glb` | Hen | Hen | 12 |
| `cow.glb` | Cow_NoHorns | Cow_Brown | 9 |
| `cat.glb` | cat | Cat_Orange | 9 |

Each GLB embeds the original 2048×2048 albedo texture, Unity material tint, UVs, skin weights and animation takes. FBX scene units and animated ancestors are baked into a meter-scale, Y-up rig. Extra mesh-only bone tips follow their animated parents. Horizontal root travel is removed so navigation controls position; vertical motion is retained. All 38 clips remain in the GLBs. Runtime blends Idle, Walk and Eat; the cat has no Eat take and uses Idle instead. Original FBXs, textures, material/prefab metadata and SHA-256 hashes are retained under `source/` and in the two manifests.

Black Creek contains a horse, cow, cat and two hens near the starting street. They roam within a home radius, rest and eat, follow terrain, and avoid scenery, other residents, the mission board and current train occupancy. Animals are ambient decoration: they do not block the player, fight, drop loot or act as mounts. Simulation stops during pause, mission selection, editing and expeditions. Returning from a mission retains the same residents; switching hubs reloads the destination's population. Frontier currently has no animal placements.

Lighting, shadows, fog and color processing use the town's existing render pipeline. Instances share assets but sample independent animation clocks, including in the shadow pass. Runtime and browser packages include only the four GLBs and placements, not the original FBXs.

## Placements

Edit `town.animals` to change residents. The header is `DEATHWARD_ANIMALS 1`, followed by one row per resident:

```text
animal stable-id species home-x home-z yaw-degrees scale roam-radius random-seed
```

Species are `horse`, `hen`, `cow`, `cat`. Y is sampled from navigation; yaw zero faces +Z. IDs must be unique. Scale is 0.25–3, radius 0–20, and the population limit is 64. If terrain was edited, loading searches up to five units around the home for a clear footprint and skips residents with no suitable placement. These placements are separate from `town.scene` and are **not yet selectable or editable in the town editor**. Reload the town/game after editing this file.

## Rebuild and verify

Requires Blender 3.6 (verified with 3.6.23), Python with PyYAML; asset verification also uses NumPy and Pillow. Rebuild from the retained originals:

```sh
python3 scripts/import_animals.py --blender /path/to/blender
python3 scripts/verify_animals.py
cmake --build build --target deathward_animal_tests deathward_animal_model_tests --parallel 1
./build/deathward_animal_tests
./build/deathward_animal_model_tests
```

The first import can instead pass `--source '/mnt/c/Users/bohus/My project (1)/Assets/polyperfect'`. The supplied Unity project is read only. `ANIMALS` in the importer selects source species/mesh/material variants; adding another species also requires its runtime catalog and package entries.

The graphics check needs a display and writes individual animal previews to ignored `artifacts/`. The asset audit verifies source/output hashes, exact texture pixels and tint, joint/weight validity and every clip's duration. Use these source assets under their existing Polyperfect license.
