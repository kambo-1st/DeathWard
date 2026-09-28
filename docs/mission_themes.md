# Mission themes

The station offers **Seeded Theme**, **Western Mine** and **Isaac Canyon** (the default). Seeded Theme resolves deterministically from the mission seed. An explicit setting persists for the session, including new offers. Replay with the same seed and theme. The CLI accepts `--theme seeded|mine|canyon` for normal play, smoke scenes and benchmarks.

The settings share the 15-room graph, locks, keys, objective structure and Black Creek campaign consequences. Canyon uses its own geometry: irregular basins, winding connecting trails and rock outcrops. Its encounter count follows its navigable floor area. Each theme reproduces its own geometry and encounters for a given seed and content version. Mission names persist in results, history and interrupted checkpoints.

## Enemy rosters

Canyon exclusively uses Isaac catalog entries, including the final Infested Mesa group and random cheat/stress spawns. Mine retains the original Western roster and Hollow Sheriff. The specific-ID monster cheat is an explicit testing override available in either setting. Canyon clearance is stored independently in the existing campaign flags, preserving the mine boss for later. See [the enemy and character review](isaac_review.md).

## Canyon geometry and rendering

`CanyonTerrain` cuts the union of irregular basin shapes and curved trail segments into a continuous height field. Paths to every gate and objective are reserved before adding seeded outcrops. The surface is triangulated on a 1.25-unit grid, with cap facets spanning 3.75 units. Navigation tiles are derived from the resulting ground; the renderer does not add a separate box-shaped collision envelope around rocks.

Movement tests the player's footprint against the terrain, and route smoothing sweeps that footprint continuously along the mesh. Bullets and sight rays traverse grid cells and intersect the same triangles used for rendering. Enemy placement checks the terrain before spawning. The mine retains its original wall/cover collision path. Gates remain explicit barriers at canyon necks: colored veils and ground marks replace the mine's overhead beams and bars.

Rendering divides the shared surface into culled mesh chunks. Steep irregular shoulders form tall rock faces; a coarser seeded surface supplies broad, planar cap facets. Cliff faces and caps sample separate brown and sandy swatches from the original PolygonWestern atlas. Flat face normals, directional terrain shadows and distance haze provide shading without horizontal stripes or color noise on mesa tops. Small imported rocks and sparse cacti decorate banks and terraces. There are no repeated stretched cliff cards or rectangular border walls.

Cliffs and outcrops stay at their full generated height as the player moves or rotates the camera. Mouse target picking and physics use the same visible terrain surface.

## Extension points

- `src/world/MissionTheme.hpp`: theme identifiers, seeded resolution, titles and base colors.
- `src/world/CanyonTerrain.cpp`: canyon terrain, navigation footprint and surface rays.
- `src/world/Dungeon.cpp`: theme dispatch and shared collision/navigation entry points.
- `src/render/CanyonScene.cpp`: terrain meshes, atlas sampling, lighting, shadows and dressing.
- `src/render/WesternScene.cpp`: scenery loading, cache and mine placement. Changing arenas/themes releases old terrain resources.
- `src/core/Game.cpp`, `src/render/Renderer.cpp`, `src/main.cpp`: station selection, launch, mouse picking, HUD and CLI.
- `src/combat/Simulation.cpp`: themed room names and summaries; `CampaignStore::begin` records the title before the first checkpoint.
- `scripts/import_western.py` and `scripts/bake_western.py`: retained-source conversion; see [asset notes](../assets/western/README.md).

## Verification

`deathward_theme_tests` (CTest) checks terrain reproduction, routes to all doors/objectives, combat seals, safe repeatable encounters, vertical surface rays and saved canyon recovery. It includes seed 69175541 from the visual review. `deathward_western_assets_tests` compares vertical and oblique collision rays with uploaded terrain meshes, and checks switching/resource cleanup. `deathward_input_tests` launches Canyon and exercises the complete mouse, keyboard and camera controls in addition to the hub.
