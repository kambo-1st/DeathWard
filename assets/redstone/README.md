# Redstone Canyon

A third, fixed hub combining Black Creek's canyon landscape and railway with
Western Frontier's fortified compound and neighboring covered-wagon settler camp.
It contains **923 authored placements, 192 mesh assets and eight original embedded
textures**. It is an authored composition of the two packs, rather than another
Unity demo import or a seed-generated mission.

Use **Travel to Redstone Canyon** in either town or its pause menu. From Redstone,
both Black Creek and Frontier have direct travel buttons. Start here with:

```sh
./build/deathward --hub redstone
./build/deathward --editor --hub redstone
```

The browser accepts `?hub=redstone` (also `?hub=canyon`). Arrival is at the caravan;
the mission board stands near the fort entrance. Mission outcomes return to this
hub. Redstone uses canyon ambience and music, the shared lighting/post processing,
campfire effects, automatic doors, object transparency and terrain navigation.
Black Creek remains the default starting hub.

## Composition

- The original Black Creek canyon terrain, cliffs, vegetation and exact railway
  centerline are retained. Town buildings, the station and station platforms are
  excluded; loose rocks/plants are cleared around the new settlement.
- The Frontier fort and settler caravan retain complete prefab groups, including
  gates, cabin, watchtowers, tents, five wagons, their wheels, supplies and fires.
  A shared translation `(31.5, 0, -115)` places them together in the canyon.
- One original locomotive, coal tender and two passenger carriages run around
  the original rails. Eight independent wheels and attached steam animate.
  The route's station wait is zero: it continues through the loop boundary.
  It still stops for a player in its path, and pauses with gameplay.
- The original source meshes, UVs, material properties and encoded image bytes
  are preserved. Only required assets are included in the new GLB. The other
  two source packs remain unchanged.

F4 opens this map's independent editor pack. Placement, duplicate/delete,
undo/redo, train preview/settings, characters, animals and navigation rebuild use
the existing editor controls. Scene saves stay in `assets/redstone` on desktop
and `/persist/redstone` in browser storage. Models and textures load from the
bundled GLB. Normal builds require no Unity, Blender or source-project access.

## Rebuild and verify

`scripts/create_redstone.py` reproduces the authored composition from the retained
town and Frontier packs. It deliberately replaces generated Redstone files; use
a separate output directory when preserving editor changes. It requires Python,
NumPy and the native navigation baker with an OpenGL display.

```sh
cmake --build build --target deathward_bake_navigation --parallel 1
python3 scripts/create_redstone.py --output /tmp/deathward-redstone-check
python3 scripts/verify_redstone.py --pack /tmp/deathward-redstone-check
./build/deathward_redstone_tests
./build/deathward_redstone_render_tests
```

`town.manifest.json` records source/output hashes, each source asset/placement,
component membership, navigation and train bindings. The audit checks exact
geometry/UV/index bytes, material properties, embedded textures, transformed
placements and absence of a station. A clean rebuild reproduces the checked-in
runtime files byte for byte. Intentional editor changes will differ from this
original authoring manifest.
