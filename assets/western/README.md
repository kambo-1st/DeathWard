# PolygonWestern scenery

Selected assets from the user's `PolygonWestern` Unity project now furnish DeathWard's seeded rooms. `western.glb` embeds the original **2048 × 2048 PolygonWestern_Texture_01_A.png** atlas, mesh UVs, Unity material assignments, color tints and glass alpha. The embedded image's decoded pixels match the source PNG exactly. Normal builds need neither Unity nor Blender.

The library includes 23 source assets: a crate, barrel, sacks, woodpile, lantern, coffin, cart, fence, saloon, jail, church, railway station, water tower, well, straight track, sand ground, two rocks, two cacti and three cliff pieces (wall, cap and pillar). A rectangular floor tile samples the original sand mesh's atlas coordinates. A solid sandstone box samples the original cliff atlas in six strata; its six closed faces exactly fill an obstacle collider. Together these produce 25 catalog entries and 30 mesh/material sections sharing one embedded atlas.

## In the game

- Seeded crate stacks fill the generated cover boxes; their outer bounds match the existing collision volumes.
- Fence panels follow room and passage boundaries. These remain solid gameplay barriers, including the visual gaps between fence rails.
- Tracks follow connecting passages; imported lanterns retain colored door-state lights.
- Buildings and other props surround rooms, with overlap rejection keeping them outside every playable floor strip. They are scenery, with no accessible interiors.
- Canyon missions use a continuous triangulated terrain generated from seeded basins, curved trails and irregular outcrops. This surface defines collision as well as rendering; there are no rectangular cover proxies or low border walls. The terrain samples the original atlas: brown cliff faces and sandy caps retain the source palette. Steep shoulders, broad flat-shaded cap facets, directional shadows and small imported rocks/cacti complete the canyon. Cliffs and outcrops always keep their full height.
- Flat textured floors follow the exact generated footprint. The irregular sand mesh supplies its palette; it does not introduce holes or terrain collision.

Scenery uses a separate seeded random stream. Mine scenery preserves its gameplay geometry. Canyon terrain uses its own seeded geometry stream and retains the room graph, objectives and locks; encounter counts follow the resulting navigable area. Rendering groups repeated models into GPU instances and omits distant scenery. Ambient and directional diffuse lighting replace Unity's URP lighting; glass draws after opaque objects without writing depth. Canyon terrain additionally casts directional shadows using its height map. Unity baked lighting, reflections, metallic/smoothness texture effects and dynamic scenery shadows are not reproduced.

## Rebuild

Authoring requires Python 3 with PyYAML and Blender 3.6 LTS. The copied sources are sufficient:

```sh
python3 scripts/import_western.py --blender /path/to/blender
```

To collect again from the original Unity project:

```sh
python3 scripts/import_western.py \
  --source '/mnt/c/Users/bohus/My project (1)/Assets/PolygonWestern' \
  --blender /path/to/blender
```

`import_western.py` resolves prefab mesh and material GUIDs, including mesh names from FBX importer metadata. It copies the selected FBXs, prefabs, materials, atlas and metadata into `source/`, without modifying the Unity project. `bake_western.py` imports the meshes into Blender, applies their material assignments and UV transforms, normalizes pivots while preserving meters, and exports the GLB. This is a converter for these selected static prefabs, not a general Unity scene importer. The track's dirt submesh is omitted because the game's continuous floor provides its bed.

`western.source.json` records the conversion recipe, source hashes and original collider metadata. Gameplay uses the fitted room volumes described above, not Unity mesh colliders. `western.manifest.json` records model bounds, mesh counts and the output hash. `western.catalog` maps assets to raylib mesh ranges; keep it paired with its GLB.

CMake copies the GLB and catalog into `assets/western` beside each graphics executable. Keep that directory and `assets/bandit` when moving a build. Missing or invalid scenery assets fall back to the primitive environment.

```sh
./build/deathward_western_assets_tests
```

The graphics test checks the texture, glass, meter scale, matching mesh/catalog bounds, fitted cover, route clearance, repeatable placement across five seeds in both themes, terrain collision/mesh agreement with vertical and oblique rays, scenery cache invalidation, drawing and resource reload/cleanup. It needs an OpenGL display.
