# Animation for objects without skeletons

Status: milestone 1 implemented. The shared runtime, stable IDs, Spin/Sway/Tumbleweed presets, two rolling tumbleweeds, editor controls, moving shadows/bounds and navigation exclusions are available. Vehicle groups, path motion, rods and moving solid collisions remain the train milestone below.

Use one reusable system that animates object transforms and groups of objects. Meshes and textures stay shared; moving a tumbleweed, spinning a wheel or opening a door changes the object's position and rotation. A skeleton is unnecessary for these rigid parts.

## Asset review before implementation

- Black Creek contains two tumbleweed placements using `part_0154`. Their source IDs are `488115655:1367905150670218` and `1856232637:1367905150670218`. The mesh is approximately centered on its origin, which is suitable for rolling.
- The two locomotive prefab instances each contain 14 visible parts, including individually named wheels, connecting rods, bell, smokestack and body. Carriages, freight cars and coal cars are also available. Grouping by prefab **instance** keeps separate vehicles independent.
- `town.manifest.json` retains source object IDs, original names and prefab ownership. Before milestone 1, both runtime scenes stored only flat asset references and matrices, without stable IDs or motion bindings. Black Creek now uses format 2 with those IDs and bindings; Frontier remains compatible format 1. Both imports pass their updated manifest audits.
- The importer resolves the Unity hierarchy and FBX pivots, but exports world transforms and loads FBX with animation disabled. Existing clips are not available to the runtime.
- `TownScene` already uses per-instance transforms. Its static shadow cache, picking bounds and the baked navigation grid need explicit treatment when objects move.

Relevant implementation: [TownDocument](../src/world/TownDocument.hpp), [TownScene](../src/render/TownScene.cpp), [HubWorld](../src/world/HubWorld.hpp), [TownNavigation](../src/world/TownNavigation.cpp), [scene importer](../scripts/import_town.py), [mesh bake](../scripts/bake_town.py).

## Design and remaining milestones

The following design covers both milestones. Milestone 1 implements per-object Spin, Sway and Tumbleweed presets; parent groups, routes, distance-driven wheels and moving solid collision are still planned. Current controls are documented in [the editor guide](town_editor.md#animating-props).

### Shared motion system

Introduce a renderer-independent `ObjectAnimationSystem` that outputs current transforms and bounds. Keep authored placements separate from runtime poses, so playing an animation never rewrites the scene or accumulates transform drift.

Each object or group has a stable ID, optional parent, original matrix, pivot and motion settings. Retain complete original matrices: imported reflections and shear must survive loading, grouping, preview and saving. Compute child bind transforms relative to the group's original pose, preserving every part's original world position at rest. Apply motion around explicit local pivots and test matrix composition against raylib's conventions.

Provide a few composable motion sources:

| Motion | Parameters | Examples |
| --- | --- | --- |
| Follow a path | Points, speed, stops, loop/reverse behavior | Train, cart, elevator |
| Rotate | Local axis, pivot, speed or distance driver | Wheels, windmill, tumbleweed |
| Oscillate | Axis, amplitude, period, phase | Hanging sign, bell, gentle bounce |
| Wind movement | Seed, speed range, gusts, allowed ground area | Tumbleweed |

Tumbleweed and train presets combine these motions. New objects use configuration rather than another renderer branch checking an asset name. Authored position/rotation keyframes can become another motion source later.

Run updates from the game update, before movement queries and rendering. Use a fixed step for contact/wind behavior and a separate deterministic random stream per object. Drawing, culling and shadow passes must never advance animation. Pause freezes it; hub switches reload that hub's motion state; returning from a mission can resume its retained state. Editor preview uses its own clock.

## First applications

**Tumbleweed:** drift slowly across valid street ground with gentle seeded gusts. Derive rolling rotation from actual distance traveled and the mesh's scaled radius, so it rolls instead of sliding. Use a small sphere for scenery contact, turn or bounce at obstacles, and follow ground height. Give each placement its own phase. Treat it as decoration that does not block the player. Avoid visible resets or teleporting across town.

**Train:** move each vehicle root along an authored route aligned with the existing rails. Group its body and attachments under that root; rotate wheels around their original axles using traveled distance divided by wheel radius. Drive rods from the same wheel phase. Carriages follow positions farther back along the route so they turn correctly through curves. Station stops slow the train and stop its wheels together. Verify a continuous rail route before enabling travel; a loop must not teleport the train across disconnected endpoints.

## Rendering and navigation

Evaluate each animated pose once and use it consistently for visible meshes, culling bounds, picking, player-occlusion transparency and shadows. Remove animated parts from the static shadow bake. Draw their current poses into the dynamic shadow pass after copying cached static depth, alongside the character. Rebuilding the entire town shadow cache every frame would defeat the existing optimization.

Remove moving objects from the static navigation bake as well. Both tumbleweeds currently have imported colliders: otherwise their old positions can remain blocked after they move. Apply the same exclusion policy in the Python import bake and the native editor bake.

For a moving train, add simple moving collision volumes and a dynamic occupancy layer used by player movement and pathfinding. Leaving the train only in the old static grid would create invisible obstacles at the station and let the player walk through it elsewhere. Full rigid-body simulation and riding on the train can be separate later features.

## Scene format and editor

Extend `town.scene` with a backward-compatible version 2 containing stable IDs, groups, pivots and motion definitions. Existing version-1 scenes load as static scenes. Using the existing scene file keeps animation settings inside the current scene/navigation save transaction and browser persistence path.

Migrate the current imports using their verified manifests. For edited scenes, require an unambiguous source match or assign new stable IDs; do not attach animations using a mutable list index. Duplicate creates new IDs and remaps duplicated group members; deletion, undo and redo update bindings with the objects. Export original parent/pivot metadata for future imports.

Add an Animation inspector with preset, speed, axis/pivot, path, loop and seed controls, plus Play/Pause/Reset preview. Save authored settings and rest transforms, never the temporary preview pose. Group selection allows the train to move as a vehicle while wheels remain individually editable.

## Suggested milestones

1. **Two rolling tumbleweeds:** stable bindings, reusable motion evaluation, ground/scenery handling, moving bounds and shadows, editor preset/preview/save. Verify both native and WASM builds and remove their obsolete static collision footprints.
2. **Train movement:** restore vehicle groups and axle pivots, author a valid rail route, synchronize wheels/rods and carriage spacing, implement moving collision and pathfinding occupancy.
3. **More props:** reuse the same rotate, oscillate and path settings for windmills, signs, doors and carts; add keyframe tracks when an object needs authored timing.

Acceptance checks should cover unchanged scene appearance at rest, frame-rate-independent motion, pause/resume, shared meshes with different instance phases, transformed pivots, no movement through scenery, matching shadow/picking/occlusion poses, no old collision footprints, and editor save/duplicate/delete/undo round trips. Browser and native checks should exercise the same motion definitions and renderer paths.
