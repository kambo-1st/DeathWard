# Original PolygonWesternFrontier hub

This second hub imports `PolygonWesternFrontier/Scenes/Demo.unity` from the supplied Unity project. Its authored village, fort, quarry, river, rocks, vegetation and background scenery keep their original placement and scale. Black Creek remains available as the first hub.

Start with `./build/deathward --hub frontier`, or choose **Pause → Travel to Frontier** in Black Creek. The same button returns to Black Creek. Hub choice persists for the session, including mission departure and return. Both locations share the campaign. The only added scene objects are the playable bandit and the mission board; the imported scenery is not rearranged.

## Import fidelity

- All **2,031 scene prefab instances** are accounted for. Hierarchies, overrides and inactive flags resolve to **2,216 active mesh placements**.
- The library has **346 mesh/material sections**, **11 original materials** and **five embedded source textures**, including all four color atlases and the broken-window texture. Decoded texture pixels and material tints match their sources.
- Every output placement matrix and mesh/material assignment is checked against the resolved Unity source. Unity's coordinate handedness is converted consistently by reflecting X.
- All **2,496 collider components** resolve without missing-source substitutions. Outdoor navigation uses a 0.4-unit grid over X -160 to 170 and Z -120 to 140. The arrival is in the village courtyard; the mission board uses nearby connected ground.
- **1,366 source and metadata hashes** and all runtime output hashes are audited. Nine stale overrides target objects absent from the original prefabs and are recorded in `town.source.json`.
- Auxiliary vertex colors on tree meshes are ignored, matching the source Standard/URP Lit shaders. These channels contain magenta and zero-alpha data; using them as albedo would recolor trunks and hide foliage. The original FBXs retain them.
- Unity's built-in water plane is reproduced at its original dimensions and transform. Distant background cards remain visible despite ordinary scenery distance culling.

This is an exact import of the authored static arrangement, not a pixel-identical Unity renderer. Raylib uses the source textures, UVs, material tints, transparency and directional light. Unity's baked lighting, reflections, water shader effects, post-processing and Animator controllers are not executed. Outdoor navigation excludes disconnected roofs and does not supply multi-floor interiors.

## Files and editing

`town.glb`, `town.scene`, `town.nav` and `town.labels` are the standalone runtime pack. `town.source.json`, `town.manifest.json` and `source/` retain the conversion recipe, audit and original dependencies. Normal builds need no Unity, Blender or Windows source folder.

F4 edits the active hub. `./build/deathward --editor --hub frontier` opens this pack directly. Saves affect `assets/frontier` in a checkout, or the same folder beside a packaged executable. Black Creek's files remain separate. See [the editor guide](../../docs/town_editor.md) for backup and navigation rebuild behavior. Intentional edits change the scene/navigation hashes relative to the original import.

## Rebuild and verify

Python with NumPy/PyYAML and Blender 3.6 are required only for conversion. Rebuild entirely from retained sources:

```sh
python3 scripts/import_town.py \
  --source assets/frontier/source --output assets/frontier \
  --nav-bounds -160 -120 170 140 --spawn 61 -25 --mission 50 -24 \
  --blender /path/to/blender
```

To recollect the original pack, replace `--source` with `/mnt/c/Users/bohus/My project (1)/Assets/PolygonWesternFrontier` (quoted in the shell). The importer reads that project and writes only into the output pack.

```sh
python3 scripts/verify_town.py --pack assets/frontier
./build/deathward_hub_tests
./build/deathward_town_assets_tests
./build/deathward_input_tests
./build/deathward --smoke --hub frontier --scene hub --frames 120 \
  --screenshot artifacts/frontier-hub.png
```

The source audit requires NumPy/Pillow. Navigation checks run headlessly; rendering and input checks require an OpenGL display. Tests exercise both hubs, switching, mouse/WASD controls, editor pack selection, and returning to Frontier after a mission.
