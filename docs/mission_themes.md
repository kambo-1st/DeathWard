# Mission themes

The station offers **Seeded Theme**, **Western Mine** and **Isaac Canyon** (the default). Seeded Theme resolves deterministically from the mission seed. An explicit setting persists for the session, including new offers. Replay with the same seed and theme. The CLI accepts `--theme seeded|mine|canyon` for normal play, smoke scenes and benchmarks.

The settings share the 15-room graph, locks, keys, objective structure and Black Creek campaign consequences. Canyon uses its own geometry: irregular basins, winding connecting trails and rock outcrops. Its encounter count follows its navigable floor area. Each theme reproduces its own geometry and encounters for a given seed and content version. Mission names persist in results, history and interrupted checkpoints.

## Enemy rosters

Canyon exclusively uses Isaac catalog entries, including the final Infested Mesa group and random cheat/stress spawns. Mine retains the original Western roster and Hollow Sheriff. The specific-ID monster cheat is an explicit testing override available in either setting. Canyon clearance is stored independently in the existing campaign flags, preserving the mine boss for later. See [the enemy and character review](isaac_review.md).

## Canyon geometry and rendering

`CanyonTerrain` cuts the union of irregular basin shapes and curved trail segments into a continuous height field. Paths to every gate and objective are reserved before adding seeded outcrops. The surface is triangulated on a 1.25-unit grid, with cap facets spanning 3.75 units. Navigation tiles are derived from the resulting ground; the renderer does not add a separate box-shaped collision envelope around rocks.

Movement tests the player's footprint against the terrain, and route smoothing sweeps that footprint continuously along the mesh. Bullets and sight rays traverse grid cells and intersect the same triangles used for rendering. Enemy placement checks the terrain before spawning. The mine retains its original wall/cover collision path. Gates remain explicit barriers at canyon necks: colored veils and ground marks replace the mine's overhead beams and bars.

Rendering divides the shared surface into culled mesh chunks. Steep irregular shoulders form tall rock faces; a coarser seeded surface supplies broad, planar cap facets. Cliff faces and caps sample separate brown and sandy swatches from the original PolygonWestern atlas. Flat face normals and shared directional shadows provide shading without horizontal stripes or color noise on mesa tops. Terrain, props and actors use the static hubs’ warm daylight and cool sky fill (`WorldPalette.hpp`); the common post-process supplies grading and distance haze. There is no additional canyon color multiplier or terrain-only brown fog. Small imported rocks and sparse cacti decorate banks and terraces. There are no repeated stretched cliff cards or rectangular border walls.

Cliffs and outcrops stay at their full generated height as the player moves or rotates the camera. Mouse target picking and physics use the same visible terrain surface.

## Small room decorations

Both themes also populate each room with small, cosmetic grass/stone/debris clusters.
The per-room decoration stream depends only on seed, theme and room index, so room
clears, collected keys and gate state do not move the props or change encounters.
There are 5–16 requested patches based on usable floor area, each trying 3–5 small
pieces; unsuitable or crowded positions are skipped. Canyon favours dry vegetation
and stones; mine has more fallen sticks. Skulls and bone piles are limited to one
each per room. Door/objective approaches and keys have reserved space. These props
use the existing instancing, culling and shadow passes without becoming collision
or mouse-picking surfaces. Change `WesternScene::generateRoomDecorations` to tune
density, asset mix, size limits and clearance.

The pause menu's **Vegetation** control scales grass and cacti from 0–200%, in
25% steps. The current baseline is 100%. Density selects stable subsets of a
seeded candidate pool: increasing it adds plants, while returning to a previous
value restores the same placements. Extra vegetation candidates use the same
ground/route checks. Actual counts can be lower than the requested multiplier
where there is no safe space. Non-vegetation scenery and gameplay generation are
unchanged. Changing density refreshes instance lists and shadow depth without
rebuilding terrain meshes. The preference is stored in `visual.cfg` beside the
campaign save (browser: `/persist/visual.cfg`). Authored hubs are unaffected.

Canyon cacti require nearly level support over their whole footprint plus a
half-metre margin. A 5×5 ground sample rejects height spreads above 10 cm, so
steep banks and cliff edges cannot host them. The test suite probes the resulting
placements at a finer spacing as well.

## Extension points

- `src/world/MissionTheme.hpp`: theme identifiers, seeded resolution, titles and base colors.
- `src/world/CanyonTerrain.cpp`: canyon terrain, navigation footprint and surface rays.
- `src/world/Dungeon.cpp`: theme dispatch and shared collision/navigation entry points.
- `src/render/CanyonScene.cpp`: terrain meshes, atlas sampling, lighting, shadows and dressing.
- `src/render/WesternScene.cpp`: scenery loading, cache, mine placement and small room decorations for both themes. Changing arenas/themes releases old terrain resources.
- `src/core/Game.cpp`, `src/render/Renderer.cpp`, `src/main.cpp`: station selection, launch, mouse picking, HUD and CLI.
- `src/combat/Simulation.cpp`: themed room names and summaries; `CampaignStore::begin` records the title before the first checkpoint.
- `scripts/import_western.py` and `scripts/bake_western.py`: retained-source conversion; see [asset notes](../assets/western/README.md).

## Verification

`deathward_theme_tests` (CTest) checks terrain reproduction, routes to all doors/objectives, combat seals, safe repeatable encounters, vertical surface rays and saved canyon recovery. It includes seed 69175541 from the visual review. `deathward_western_assets_tests` compares vertical and oblique collision rays with uploaded terrain meshes, and checks switching/resource cleanup. `deathward_input_tests` launches Canyon and exercises the complete mouse, keyboard and camera controls in addition to the hub.
