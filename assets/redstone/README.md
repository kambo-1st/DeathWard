# Redstone Canyon

A third, fixed hub combining Black Creek's canyon landscape and railway with
Western Frontier's fortified compound and neighboring covered-wagon settler camp.
It contains **1047 authored placements, 231 mesh assets and eight original embedded
textures**. It is an authored composition of the two packs, rather than another
Unity demo import or a seed-generated mission.

Use **Travel to Redstone Canyon** in either town or its pause menu. From Redstone,
both Black Creek and Frontier have direct travel buttons. Start here with:

```sh
./build/deathward --hub redstone
./build/deathward --editor --hub redstone
```

The browser accepts `?hub=redstone` (also `?hub=canyon`). Arrival is beside the
stranded passenger train; the mission board stands at the badlands trail. Mission outcomes return to this
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
  the original rails when enabled in the editor. The story layout parks the
  train at speed zero, with steam and all four vehicle colliders active. Eight
  wheel bindings and the full route remain available for a later departure.
- The canyon keeps its 240 × 240 navigation footprint, terrain scale, original
  fort and rail geometry. Three removed dust piles and the lowered camp ground
  from the approved editor revision are preserved.
- Additional prop groups establish luggage and boarding steps,
  railroad supplies and sand drifts, a merchant wagon, water and cookfires,
  witness shelters, settler tents, a holding yard, an evidence table and the
  covered wagon for the ending. Fifteen tents now spread around the fort.
- The kitchen and trading court sit beside a clear road; the prospectors' wagon
  has a level approach. Continuous holding-yard fences leave one guarded entrance.
  The command desk uses the cabin porch, and belongings sit under canvas. Reserved
  road, gate, passenger, wagon and gathering spaces keep new props and loose
  clutter out of circulation routes. The sand obstruction is retained.
  The existing cot and porch seating are reused; two old stockpiles crossed by
  the holding fence are removed explicitly in the layout's source-group list.
- The main road is a 3.8 m wagon track, reduced from approximately 10.9 m. Its
  crown is lowered with its width so the shoulders remain walkable. A narrower
  fort approach and three continuous worn paths replace the broad junction.
  The fort frontage has hitching rails, a trough and feed, waiting bench and
  notices, a repair cart, work table, spare wheel and timber. Broken clusters of
  dry grass, stones and bushes mark the shoulders without enclosing the courts.
  There are 118 added prop groups in total; the road, gate, court entrances and
  bench approach remain clear. One passenger now visits the waiting space.
- The fort's imported ground is clipped inside its palisade. A narrow earth
  bank meets the canyon around the walls, and a shallow grade supports the gate
  approach. The exterior furniture sits on the resulting ground. The three
  footpaths follow the actual terrain with a small rendering offset, avoiding
  the old raised apron edge and partly buried road patches. These eleven derived
  meshes append after the 220 original assets; their pivots sit at their own
  centres for normal editor placement and rotation.
- Fifteen provisional residents use the existing textured cowgirl and bandit
  models. The commander, outlaw, wife, spiritualist and scout have authored
  positions; ambient residents follow checked walking routes. Nearby role labels
  identify witnesses. This milestone has no testimony conversations or ending event.
- Original source meshes, UVs, material properties and encoded image bytes
  are preserved. The derived floor, bank and path meshes reuse the source
  materials and textures, with their construction recorded in the manifest. The other
  two source packs remain unchanged.

F4 opens this map's independent editor pack. Placement, duplicate/delete,
undo/redo, train preview/settings, characters, animals and navigation rebuild use
the existing editor controls. Scene saves stay in `assets/redstone` on desktop
and `/persist/redstone` in browser storage. Models and textures load from the
bundled GLB. Normal builds require no Unity, Blender or source-project access.

The character inspector's **Model** button switches between cowgirl and bandit;
placement, route editing, undo/redo and saving apply to both. New mesh assets
append after the previous catalog entries (192, then 212, then 220).
Browser startup upgrades known untouched shipped scene/navigation pairs through
`deathward-m1-41`. Other saved layouts retain their
instances and settings while receiving the extra unused catalog entries and
labels needed to load the expanded GLB.

## Rebuild and verify

`scripts/create_redstone.py` reproduces the authored composition from the retained
town and Frontier packs. It deliberately replaces generated Redstone files; use
a separate output directory when preserving editor changes. It requires Python,
NumPy and the native navigation baker with an OpenGL display.
`scripts/redstone_story_layout.json` stores the additional prop groups, resident
positions/routes, road dimensions/patch transforms and arrival/departure markers. `redstone_story.py` assembles
complete prefab children, preserves the approved edits and parks the train.
`redstone_ground.py` clips the fort floors, grades their perimeter and entrance,
grounds the frontage props, and builds the terrain-following paths.

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
placements and absence of a station. Derived floors are checked against the
source clipping operation; path vertices must sit just above the terrain.
A clean rebuild reproduces the checked-in
runtime files byte for byte. Intentional editor changes will differ from this
original authoring manifest.
