# Mission themes

The station offers **Seeded Theme**, **Western Mine** and **Isaac Canyon** (the default). Seeded Theme resolves deterministically from the mission seed. An explicit setting persists for the session, including new offers. Replay with the same seed and theme. The CLI accepts `--theme seeded|mine|canyon` for normal play, smoke scenes and benchmarks.

Ordinary expeditions in both settings have 4–8 seeded floors, each using the existing 15-room graph, locks and keys. Health, powers, currency and consumables carry between floors; layouts, encounters and rewards regenerate. Their original objectives and Black Creek campaign consequences remain separate from story expeditions. Canyon uses its own geometry: irregular basins, winding connecting trails and rock outcrops. Its encounter count follows its navigable floor area. Each theme reproduces its own geometry and encounters for a given run seed and content version. Mission names and the floor reached persist in results, history and interrupted checkpoints. The Fort Mercy tutorial remains one five-room floor; [Rourke's account](redstone_story_hub.md#full-expeditions-and-the-first-account) embeds its story sites into full canyon floors.

## Enemy rosters

Canyon exclusively uses Isaac catalog entries, including the final Infested Mesa group and random cheat/stress spawns. Mine retains the original Western roster and Hollow Sheriff. The specific-ID monster cheat is an explicit testing override available in either setting. Canyon clearance is stored independently in the existing campaign flags, preserving the mine boss for later. See [the enemy and character review](isaac_review.md).

## Canyon geometry and rendering

`CanyonTerrain` cuts the union of irregular basin shapes and curved trail segments into a continuous height field. Paths to every gate and objective are reserved before adding seeded outcrops. The surface is triangulated on a 1.25-unit grid, with cap facets spanning 3.75 units. Navigation tiles are derived from the resulting ground; the renderer does not add a separate box-shaped collision envelope around rocks.

Movement tests the player's footprint against the terrain, and route smoothing sweeps that footprint continuously along the mesh. Bullets and sight rays traverse grid cells and intersect the same triangles used for rendering. Enemy placement checks the terrain before spawning. The mine retains its original wall/cover collision path. Gates remain explicit barriers at canyon necks: colored veils and ground marks replace the mine's overhead beams and bars.

Rendering divides the shared surface into culled mesh chunks. Steep irregular shoulders form tall rock faces; a coarser seeded surface supplies broad, planar cap facets. Cliff faces and caps sample separate brown and sandy swatches from the original PolygonWestern atlas. Flat face normals and shared directional shadows provide shading without horizontal stripes or color noise on mesa tops. Terrain, props and actors use the static hubs’ warm daylight and cool sky fill (`WorldPalette.hpp`); the common post-process supplies grading and distance haze. There is no additional canyon color multiplier or terrain-only brown fog. Small imported rocks and sparse cacti decorate banks and terraces. There are no repeated stretched cliff cards or rectangular border walls.

Cliffs and outcrops stay at their full generated height as the player moves or rotates the camera. Mouse target picking and physics use the same visible terrain surface.

## Canyon river trial

With rivers enabled, each canyon seed chooses **one** of two river types, with
an equal chance from an independent random stream:

- **Boundary:** replaces outward cliffs in one to three exterior rooms with a
  reachable bank, deep channel and low landscape across the water.
- **Interior:** crosses the entrance basin and two connected neighbours, with
  shallow fords connecting both banks and preserving routes to gates/objectives.

A mission uses a single type; the two treatments are not combined in one layout.
Replaying the same seed reproduces both its type and course. **1866** demonstrates
a boundary river in the first room; **42** demonstrates an interior river.

On the mission board, **River On / River Off** compares this with the original
dry canyon using the same seed. The setting applies to the next mission; it
cannot alter terrain beneath a running encounter. Native: `--canyon-river on|off`.
Browser: `?theme=canyon&river=on|off`. `visual.cfg` version 3 saves the choice and
reads older vegetation/floor settings.

For boundary rivers, the generator chooses an exposed side of the room graph,
preferring an early reachable room and resolving ties with the seed. The channel meanders outside
the rooms and continues to the terrain edges. Open banks taper into cliff
headlands between rooms; those headlands keep locked passages and combat seals
meaningful. The opposite plateau is lowered all the way to the landscape edge,
so the river genuinely replaces the enclosing rock face. Damp/gravel material,
small stones and driftwood dress the shores; dry room litter stays out of water.

Interior rivers follow curved passages, narrow at their necks and widen inside
the basins. The generator reserves shallow crossings and checks connectivity
before encounters are populated. Additional fords can be raised over originally
walkable floor to reconnect an isolated bank; this never carves a shortcut
through a mesa. A bounded fallback keeps the original floor fordable if needed.

Both river types share the cliffs' triangulated height field. Deep water blocks
movement. Boundary channels have no fords; their gate/objective routes remain
inland. Interior channels provide shallow crossings. Navigation, encounter
budgets and pickup placement use the resulting surface. Movement sweeps test every
terrain grid/triangle crossing, so long dodges and smoothed mouse paths cannot skip
the water. Bullet and sight
rays remain physical terrain tests and can cross the channel. Kicked/thrown
dynamite follows the actual bed rather than an invisible plane at floor height.

Water triangles are clipped to the terrain shoreline and use depth-colored,
opaque shading with subtle ripples following the curved channel. They receive
the shared directional shadows and post-process without casting opaque shadows
of their own. This is a lightweight native/WebGL 2 treatment, without fluid
simulation or screen-space reflections. Swimming, bridges, river audio and a
full drainage network are outside this trial.

## Interior dirt roads

Canyons also plan one seeded dirt track through three connected rooms and their
existing passages. It can coexist with either river type. Interior-river rooms
are excluded from road selection; boundary rivers retain a dry inland route.
The planner checks the full road width and soft shoulders against water, slopes
and cover. It keeps a gap from riverbanks, including shallow fords. If no safe
three-room route fits, that layout omits the road instead of forcing a crossing.

Roads use the existing terrain and passage graph. Rounded bends, varying widths,
softly worn ends, patchy earth colors and two irregular wheel ruts are material
detail on the actual ground. There is no raised overlay mesh, terrain cutting or
additional collision plane. Road selection and appearance use a separate seed
stream and cannot move rivers, rooms, gates, enemies or objectives. Decorations
and vegetation keep their footprints clear of the track and its shoulders.

Roads remain visible with optional floor detail disabled. **River Off** only
removes water; roads still generate. Seed **1866** has a road through the entrance
room alongside its boundary river. With **42**, the interior river occupies a
different region from the road through rooms **8, 13 and 14**.

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

## Ground surface trial

Both generated themes use the same optional `GroundSurface` treatment, enabled by
default. World coordinates drive seeded, softly warped sand/dirt patches and finer
grain/gravel. Fine frequencies fade with pixel footprint to avoid camera shimmer.
No texture is stretched to room bounds, and adjacent floor strips share the same
pattern. Canyon detail fades out above the low wall foot, leaving the upper cliffs
and caps in their original palette. Imported props keep their original materials.

A half-metre soil mask is generated once per arena (capped at 1024 pixels per axis).
An eight-neighbour distance transform finds ground near actual canyon relief,
mine obstacles and small ground rocks. It supplies subtle material darkening at
their bases. The mask is independent of vegetation density and camera fading.
It is sampled from a borrowed material map alongside the existing atlas and shadow
depth; `GroundSurface` owns and releases the texture. No geometry, collision or
gameplay random streams change.

**Pause → Ground Surface → Detail On/Off** switches immediately without regenerating
the map. `visual.cfg` saves this flag alongside vegetation density and river preference;
version 1 files retain their density and enable the new surface. Toggle off to
restore the original floor. Static hubs and the abandoned art experiment are
unaffected.

## Extension points

- `src/world/MissionTheme.hpp`: theme identifiers, seeded resolution, titles and base colors.
- `src/world/CanyonTerrain.cpp`: canyon terrain, navigation footprint and surface rays.
- `src/world/CanyonRoad.cpp`: dry route selection, clearance checks and smooth road paths.
- `src/world/CanyonRiver.cpp`: seeded boundary/interior selection, river courses, ford connectivity and water movement sweeps.
- `src/render/CanyonWater.cpp`: clipped water meshes, flow shading and shared shadow reception.
- `src/world/Dungeon.cpp`: theme dispatch and shared collision/navigation entry points.
- `src/render/CanyonScene.cpp`: terrain meshes, atlas sampling, lighting, shadows and dressing.
- `src/render/WesternScene.cpp`: scenery loading, cache, mine placement and small room decorations for both themes. Changing arenas/themes releases old terrain resources.
- `src/core/Game.cpp`, `src/render/Renderer.cpp`, `src/main.cpp`: station selection, launch, mouse picking, HUD and CLI.
- `src/combat/Simulation.cpp`: themed room names and summaries; `CampaignStore::begin` records the title before the first checkpoint.
- `scripts/import_western.py` and `scripts/bake_western.py`: retained-source conversion; see [asset notes](../assets/western/README.md).

## Verification

`deathward_theme_tests` (CTest) checks terrain reproduction, routes to all doors/objectives, combat seals, safe repeatable encounters, vertical surface rays and saved canyon recovery. It includes seed 69175541 from the visual review. `deathward_western_assets_tests` compares vertical and oblique collision rays with uploaded terrain meshes, and checks switching/resource cleanup. `deathward_input_tests` launches Canyon and exercises the complete mouse, keyboard and camera controls in addition to the hub.
