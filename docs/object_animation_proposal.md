# Animation for objects without skeletons

The shared prop runtime and train milestone are implemented. Object transforms animate without skeletons; meshes and textures remain shared and unchanged. Current controls are in the [editor guide](town_editor.md#animating-props).

## Runtime

`ObjectAnimationSystem` advances on a fixed simulation step and outputs current transforms and bounds. Authored matrices remain separate from runtime poses, including imported reflection and shear. Rendering, culling, picking, transparency and shadows consume the same poses. Animated parts are excluded from the cached static shadow pass and drawn into the dynamic pass. Pause freezes motion, missions retain hub motion state, and switching hubs resets that hub's motion. Editor preview has its own clock.

Spin and Sway rotate around a local axis and pivot. The Tumbleweed preset combines seeded wind, ground following, clearance checks, rolling proportional to actual travel and a small bounce. Black Creek's two original tumbleweeds use independent phases and do not block walking.

## Trains

The original town has a continuous rail loop with four 25-unit-radius corners. Both original trains follow it: a passenger train with a tender and two coaches, and a freight train with a tender and two wagons. Eight vehicle groups bind all 62 mesh instances by stable source IDs. Groups derive child bindings from the original world matrices, preserving their appearance at rest. Front/rear route samples determine each vehicle's position and heading, so carriages follow curves instead of pivoting around the locomotive.

The default shared route cruises at 3 units/second, accelerates at 0.8 units/second squared, and waits six seconds at the original starting positions before departure and after each circuit. Both trains share route progress, retaining their separation when one stops for the player. Route samples wrap continuously without teleporting. This is an authored route for the verified rail layout; importing another layout does not silently attach this route to similarly named vehicles.

Sixteen separate locomotive wheel meshes rotate around their original local X axles using traveled distance divided by wheel radius. The initial asset review misidentified three `Stick` meshes per locomotive: they are upright cab levers, not connecting rods. They remain attached to the cab. Coach/tender/freight wheels and the remaining linkage geometry are combined with body meshes and remain rigid parts of those meshes; splitting them for additional mechanical animation is future work.

## Collision and navigation

Moving vehicles are excluded from both the original collider bake and the editor's visible-mesh bake. The ground underneath their original placements becomes available again. Current oriented vehicle hulls provide a dynamic occupancy layer for WASD movement, route searches, smoothing and replanning. Obsolete occupied cells are cleared as the train moves. Existing mouse destinations are retained while temporarily covered by a train.

A route stops before its next pose overlaps the player's clearance, then accelerates again when clear. Distance-driven wheels stop with it. Tumbleweeds also avoid the current train hulls. Vehicles are not rideable platforms and have no damage/crushing simulation. The authored track route is assumed clear of static scenery; route-aware collision with newly placed buildings is not implemented.

## Persistence and editing

Scene format 3 adds `path`, `group` and `member` records. Groups reference paths by ID, and instances reference groups by ID; member records also hold a wheel radius when applicable. Original instance matrices stay unchanged. Formats 1 and 2 remain readable, and scenes without paths still save as format 2. Loading validates missing/duplicate bindings, dimensions, finite settings and disconnected loop endpoints.

Selecting a vehicle part focuses and outlines its group. The Animation inspector exposes route speed, acceleration, station wait, centerline display and Play/Pause/Reset. Saving during playback retains authored poses and route settings. Deleting a bound part removes its complete vehicle; undo restores all bindings. Detach Vehicle returns the group to static, individually editable parts at their original placements. Bound parts cannot be independently moved or duplicated onto the same track. General route point authoring, adding trains and grouping arbitrary parts remain future editor features.

## Verification

The train suite covers a complete circuit, curve/axle alignment, station stops, independent wheel pivots, 30/60/120 FPS agreement, original rest transforms, rigid attachments, player stops, resumed travel, dynamic navigation and format-3 persistence. Editor tests cover shared settings, rejected edits, group deletion/detach/undo and saving during preview. Graphics tests compare cached versus freshly rebuilt shadows and capture station/curve views with original textures. Browser tests cover route progress and exact pause behavior alongside normal gameplay.

Implementation: [ObjectAnimationSystem](../src/world/ObjectAnimation.cpp), [TownDocument](../src/world/TownDocument.hpp), [HubWorld](../src/world/HubWorld.cpp), [train authoring](../scripts/town_train_motion.py).
