# Milestone 1 verification

## Western Music score and stingers

Eight full compositions and four stereo stingers from the user's Western Music pack are packaged with source/output hashes and an import script. Hubs, exploration, ordinary combat, final encounters, victory and defeat select their own score. Tracks crossfade; the three Hunt arrangements align playback positions. A two-second release avoids an immediate change at the last kill. Stingers mark departure, boss entry, victory and death, play once, and lower the score underneath. They share the independent Music volume control. Existing `DW_AUDIO_1` preferences migrate without losing prior levels. A missing music pack leaves effects and ambience available.

The Release build is warning-free. All eight headless suites and the full gameplay input suite pass. Input coverage includes the fourth volume row, independent music mute, both hub themes, mine/canyon exploration, ordinary combat, the canyon finale, victory, natural death and retreat. The expanded real-device audio suite passes on WSLg PulseAudio: imported PCM output, continuous playback, crossfades, Hunt timeline alignment, combat release, one-time stingers, death-to-summary continuity, cleanup when returning to a hub, independent volume, mute/unmute without delayed cues, editor fade-out, settings migration and resource reload. The no-device check also passes. Test mixer output is silenced unless `--audible` is supplied; native Windows playback remains untested.

All 12 packaged files were decoded and checked against their manifest hashes, frame counts, stereo layout and 44.1 kHz rate; decoded samples are finite and below full scale. Their original full durations are retained. The pause panel was visually reviewed. Two 60-frame actual-game checks with audio enabled completed in Frontier and the canyon finale. Logs use `artifacts/music-*`; the pause capture is `artifacts/audio-pause-controls.png`. Full multi-minute score loops were not timed end to end; the audio suite continues to cover the common stream backend across the shorter ambience loop boundary.

## First audio milestone

raylib audio is enabled with a 32-voice alias pool, priority/rate limits, camera-relative panning, distance attenuation and a stereo soft limiter. Confirmed gameplay transitions emit bounded presentation cues independently of combat event propagation and gameplay randomness. The original synthesized pack contains 30 mono effects and four streamed 16-second stereo ambience loops. Location changes crossfade ambience; pause reduces it and stops combat voices. The pause panel provides master/effects/ambience volume, mute and a test chime, with preferences stored separately from the campaign. `--mute` skips device initialization; smoke/benchmark modes are silent unless `--audio` is supplied. Missing devices or sound packs leave gameplay silent. The null backend is disabled so missing output cannot be reported as successful playback.

The Release build is warning-free. All eight headless suites and the full gameplay input suite pass, including cue priorities/capacity, no duplicated shot/death reports, unchanged simulation RNG, volume controls, clamping and modal input guards. The real-device suite passes on WSL2 through WSLg PulseAudio at 44.1 kHz stereo. It measures nonzero PCM, verifies actual left/right output after orbiting, fills the voice pool and replaces incidental sounds with hurt feedback, checks the limiter, runs beyond an ambience loop boundary, and verifies mute/pause/travel, settings persistence, cleanup and reload. Ambience continues through a simulated 500 ms loading stall using longer stream buffers; effects retain their normal immediate playback path. Test output is captured and silenced by default; `--audible` enables listening. Native Windows runtime playback has not been tested here.

The actual game also completed a 90-frame canyon combat check with audio enabled, and three-frame checks with an unavailable PulseAudio/ALSA output and with both `--audio --mute`. The muted launch did not initialize audio; the unavailable launch continued and exited cleanly. Pause controls were visually reviewed. Two 180-frame stress samples at 1440 × 900 measured 44.61 ms mean / 54.57 ms p95 muted and 44.32 ms mean / 51.17 ms p95 with audio. Combat counters matched exactly. These samples include initial loading and ran alongside another game process; they show no observed audio regression in that comparison, not a 60 FPS or isolated-hardware claim. Logs, screenshots and benchmark results use `artifacts/audio-*`.

## Occluded enemy silhouettes

Living hostile enemies receive a hollow warm-red outline along silhouette edges hidden by the rendered world. A separate mask renders their actual animated geometry without ground shadows, then compares its nearest depth against the scene depth. The outline is composited after world post processing and before UI. Visible edges stay unchanged; dead, friendly, buried and teleporting enemies are excluded. Both mission rosters use the same pass, and mask resources resize and unload with the world targets.

The Release build, full gameplay input suite and post-processing graphics checks pass, including full/partial occlusion, no outline on visible geometry, hollow interiors, empty-frame cleanup, UI layering, resizing and resource reload. The occlusion suite verifies actual walker, fly and worm models behind canyon terrain at close/wide zoom, along with excluded enemy states and existing player transparency. Captures were visually reviewed. Logs and images use `artifacts/enemy-outline-*`.

## Canyon boundary outlines

Faded canyon walls and outcrops retain a thin gray contour at the edge of the playable ground. The contour uses the same walkable-height threshold as terrain collision and follows the original triangles. It draws after translucent scenery with depth testing, so the player and opaque objects still cover it. Only faded canyon sections receive the line.

The Release build, mission-theme checks, occlusion graphics suite and Western asset/terrain suite pass. Close/wide captures were visually reviewed to confirm that the boundary stays readable through the faded cliff and the player remains visible. Logs and before/after captures use `artifacts/canyon-outline-*`.

## Player visibility through scenery

Town objects that obstruct body/head/shoulder sight rays render in full at 22% opacity, including every material section. Normal scenery stays in its instanced opaque batch; obstructing objects draw afterward without depth writes. The same behavior applies to mine props and complete canyon rock outcrops or basin-wall sections, including props supported by those sections. Canyon terrain and its props share a back-to-front translucent pass after actors. Floor meshes remain opaque, and a textured sand underlay prevents holes beneath faded mesas. Original collision and terrain heights stay intact. Scenery restores automatically when it no longer obstructs the player; the editor uses the full scene.

The Release build, full graphics input suite, town asset/lighting suite, Western terrain suite and occlusion graphics suite pass. Pixel comparisons verify changes across entire objects beyond the player's silhouette, restored player visibility, and exact restoration when the effect is disabled. Canyon checks verify opaque floor sections and collision rays against the original terrain across five seeds. The canyon transparency update additionally compares the translucent pass against complete removal to ensure walls remain visible; the Release build, occlusion suite and Western terrain suite were rerun for this update. Before/after canyon captures at normal/wide zoom were visually reviewed. Logs use `artifacts/whole-occlusion-*` and `artifacts/canyon-transparency-*`; captures use `artifacts/occlusion-*-before.png` and `artifacts/occlusion-*-after.png`.

## No automatic room healing

Removed the 15 HP bonus on first room entry and the 20 HP bonus on room completion. The expedition-loop contract now uses a wounded player and verifies health through first entry, final-enemy kills, room clears and peaceful-room revisits. The Release build and all seven headless suites pass. Logs use `artifacts/no-room-healing-*`.

## Stronger, more aggressive enemies

Content version `deathward-m1-21` applies 25% more damage at impact across enemy contact, projectiles and hazards, 10% faster ordinary movement, and 15% shorter attack cooldowns to both rosters and the Sheriff. Windups, committed jumps/charges, projectile speeds, enemy HP, dodge/hurt protection, mirror/orbit positioning and friendly-monster behavior retain their previous values.

The Release build and all seven headless suites pass. Actual melee, contact, projectile, chain and ring damage are verified, alongside faster Rusher/Gaper pursuit and shorter Gunman/Horf attack cycles with full warnings. Existing coverage checks every catalog entry, obstacle collision, hazards, armor, spawning, room budgets and deterministic generation. Logs use `artifacts/enemy-pressure-*`.

## Starting camera zoom

New sessions start at 160% zoom in both hubs and missions. The wheel limits and session zoom retention are unchanged. The Release build and full graphics input suite pass, including the starting zoom, camera framing, smooth wheel movement, both zoom limits and hub/mission transitions. The Black Creek startup capture was visually checked and displays 160%. Logs and the capture use `artifacts/zoom-default-*`.

## Player balance and camera zoom display

Content version `deathward-m1-20` starts the player with 100 HP and 24 shot damage. Player Settings, Home and Restore Defaults use those values. Enemy health and damage are unchanged. Hubs and missions display the current camera zoom beside FPS: 100% is the reference distance, higher values zoom in, and the value follows the actual smoothed camera. The readout blocks pointer input into the world behind it.

The Release build, all seven headless suites and full graphics input suite pass. Existing checks verify the new starting stats, shot damage, item health penalties, reset defaults and session settings. Zoom checks verify the displayed value against actual camera distance and prevent wheel input through the readout. The pause screen was rendered and visually inspected with 100 HP, 24 damage and the zoom indicator. Logs and the capture use `artifacts/player-half-*` and `artifacts/player-zoom-*`.

## Isaac review and separate mission rosters

Content version `deathward-m1-19` defaults to Isaac Canyon. Natural canyon encounters, random debug/stress spawns and the final Infested Mesa group use only catalog monsters; the mine retains the Western roster and Sheriff. Canyon completion has an independent campaign flag, so its victory and replay do not remove the mine's boss. Both mission descriptions and the canyon objective HUD reflect the new encounter.

Reference corrections remove Tainted Sucker contact damage, add a bounce to its splitting death shots, remove Bulb's invented dodge drain, and give Eggy distinct Swarm Spider offspring. Summoners now respect the six-child limit even when partially occupied. The catalog has 128 entries including offspring. Isaac's character stats and the remaining behavior differences are recorded in [the review](isaac_review.md); this pass retains the current character balance.

The Release build and all seven headless suites pass. The new Swarm Spider hop check observes its randomized initial cooldown before checking movement. The full graphics input suite passes. Coverage includes all catalog entries, theme-exclusive groups and random spawns, area budgets including companions, reproducible placements, canyon final-room exit/replay, independent persisted completion, and the four enemy corrections. The mission menus and canyon finale were rendered and visually inspected. Logs and captures use `artifacts/isaac-review-*`.

## Player health and damage controls

The mission pause menu includes Player Settings while cheats are enabled. Base health changes in steps of 25 (25–2,000), and shot damage changes in steps of 4 (1–500). Minus/equals or keypad minus/plus work during play; Shift changes health instead of damage, and Home restores defaults. Values carry through missions and hub travel for the session. Changing health preserves the injured fraction and recalculates existing Judas penalties. Normal shots, split bullets and ghost bullets use the chosen damage; existing projectiles retain their values.

The Release build, all seven headless suites and full graphics input suite pass. Added coverage verifies health penalties, healing, bounds, real player shots, derived bullets, frozen pause controls, live shortcuts, disabled-cheat guards, restoring defaults and a fresh mission after hub travel. The pause panel was rendered and visually checked. Logs and the capture use `artifacts/player-settings-*`.

## Monster catalog, IDs 10–89

Content version `deathward-m1-18` adds 120 catalog entries in the requested range, including variants and detachable head components, plus seven required offspring entries. Seeded combat groups choose from the Western roster or the monster catalog with depth gates, area budgets and safe placement. Invulnerable hazards do not block completion; queued offspring are created before checking completion. Cheats can select a specific catalog ID and spawn it with Shift+F4. See [the roster and adaptation notes](isaac_monsters.md).

The Release build is warning-free. All seven headless suites pass; the monster suite simulates every catalog entry and checks attack warnings, directional armor, Host exposure, reflected shots, regeneration, bounded offspring, linked deaths, room hazards, beam cover/dodge behavior, explosion ownership, mirrored shooting, split projectiles and burrow placement. The monster behavior suite also passes AddressSanitizer and UndefinedBehaviorSanitizer with leak detection. Population checks include attached companions in the initial room budget and validate clear placements and reproducible timers. The full graphics input suite passes, including the new selector and spawn shortcut alongside hub travel and ordinary combat controls. Roster captures use the actual game renderer. Logs and images use `artifacts/monsters-*` and `artifacts/monster-roster-*`.

## Direct hub travel

Both hubs now show a destination button at the bottom right during exploration: Travel to Frontier or Travel to Black Creek. Pause-screen travel remains available. Retreat, history and expedition-return labels follow the selected hub. Both locations share campaign progress, and missions return to their departure hub.

The Release build and full graphics input suite pass, including direct travel in both directions, pause-screen travel, blocking ground clicks and camera gestures over the new control, Frontier movement, editor selection and mission return. Both hub layouts were rendered and visually checked. Logs and captures use `artifacts/hub-travel-*`.

## Gentle blur and distance fog

The world composite blends a 1.25-pixel cross filter at 22% strength for light softening. A sampled depth texture supplies perspective eye distance for lavender haze, starting near the camera's focal distance and capped at 18% opacity. The focal distance follows zoom; nearby geometry retains contrast. Menus, labels and health bars remain outside both effects. The pass adds no extra render targets or blur passes beyond the existing bloom pipeline.

The Release build and expanded post-processing graphics suite pass. New pixel checks verify a softened edge with retained contrast, stronger fog on an otherwise identical distant surface, and exact UI pixels after fog and blur; the existing palette, bloom, resize and resource-reload checks also pass. Logs and previews use `artifacts/soft-fog-*`.

## Reference palette and post processing

The world now renders through an HDR color target, a quarter-resolution highlight extraction and separable bloom blur, then a composite with edge antialiasing, amber/plum split toning, richer saturation, soft highlight compression and a restrained vignette. Both hubs, generated missions and the town editor share the treatment. Menus, text, mission labels and enemy health bars render after the composite. Window resizing recreates the targets; resource/shader failure falls back to direct world rendering.

Frontier birch and tree-clump assets receive copper/gold variation on their green leaf swatches, derived from each placement. Bark, evergreens, ground and desert plants keep their source material colors. Sun intensity is tuned for the brighter art treatment. The source assets, saved scene placements, navigation, input coordinates and campaign format are unchanged.

The Release build, all six headless suites, both hub asset checks, editor suite and full input suite pass. `deathward_post_process_tests` verifies shadow/highlight grading, image orientation, a localized bloom halo, exact UI pixels after compositing, odd-sized window resizing and repeated resource unload/reload. Captures and logs use the `artifacts/post-*` prefix.

## Hub sunlight and shadows

Black Creek and Western Frontier now share filtered sun shadows, sky fill and warm ground bounce. The strongest imported directional light supplies the shadow direction and color; original secondary lights and lamps remain active. The animated bandit casts and receives the same lighting. Transparent glass/water and unlit sky/background scenery do not cast opaque shadows. The editor uses the same renderer and refreshes shadows after geometry edits.

A 2048-square depth map uses nine comparison taps, slope-aware bias, texel-aligned projection and an edge fade. A separate static depth cache avoids redrawing the town every frame; camera travel, zoom and document edits refresh it. Each frame starts from that cache and draws the current animated character, preventing trails from previous poses. The original scene catalogs, GLBs, textures, navigation and campaign format are unchanged. This is a native raylib lighting pass; Unity baked lighting, reflections and water effects remain outside the import.

The Release build and all six headless CTest suites pass. Graphics asset tests cover both packs, actual pixels darkened by occlusion, preserved sunlit pixels, identical cached shadow output, removing/restoring the sun, reload and cleanup. Editor, bandit and full input suites pass, including hub travel, mission return, movement, camera controls and combat. Viewpoint captures cover Frontier's village, fort, quarry, river, camera orbit and close/wide zoom, plus Black Creek. Logs and captures use the `artifacts/lighting-*` prefix.

At 1440 × 900 with 4× MSAA and the frame cap disabled, eight stationary-camera views with an animated character measured 8.84–13.14 ms mean and 10.63–16.31 ms p95 over 200 frames per view after warmup. The Frontier arrival measured 10.04 ms mean; Black Creek measured 13.14 ms. These measurements use the static shadow cache on the current WSL display, and do not guarantee frame times during travel, cache rebuilds or on other hardware.

## Second hub: PolygonWesternFrontier

The original `PolygonWesternFrontier/Scenes/Demo.unity` now forms a separate hub alongside Black Creek. Pause-screen travel switches packs; `--hub frontier` starts there directly. Mouse/WASD movement, camera controls, the mission board and expedition return use the selected hub. F4 and `--editor --hub frontier` select Frontier's own scene and navigation.

The import accounts for all 2,031 scene prefab instances and retains 2,216 active mesh placements, 346 mesh/material sections, 11 materials and five original textures. The audit verifies the actual runtime catalog as well as the manifest: transforms, mesh/material assignments, 1,366 source/metadata hashes, runtime hashes and pixel-identical embedded images all match. All 2,496 original collider components resolve; the navigation pack contains 316,697 connected cells. The imported Unity arrangement remains fixed; the avatar and mission board are gameplay additions. Original textures and source material semantics are retained, including ignoring the auxiliary tree vertex channels that Unity Lit does not use. Rendering differences from Unity are documented in [the Frontier asset notes](../assets/frontier/README.md).

The Release build, all six core suites, both-hub navigation/rendering checks and the full graphics input suite pass. Input coverage includes pause-screen travel in both directions, Frontier mouse/WASD movement, editor pack selection, preventing travel during expeditions and returning to Frontier after a mission. The original Black Creek asset audit also passes. Actual village, fort, quarry and river views plus direct Frontier editor entry were rendered and inspected. Logs and captures use `artifacts/frontier-*`; normal campaign files and the original Black Creek pack were not modified by these checks.

## Faceted canyon reference style

Content version `deathward-m1-17` gives canyon walls steeper irregular shoulders and broad, seeded cap facets. Brown faces and pale caps sample the original cliff atlas directly. Horizontal shader bands are removed, and flat normals plus a soft sky fill keep shaded rock faces readable. Cover has broader tops. Automatic cliff lowering stays disabled; mouse picking, navigation and bullets use the rendered terrain triangles.

The Release build, all six core suites, full input suite and Western graphics asset checks pass. Coverage includes five canyon seeds, route clearance, sealed entrances, safe spawns and vertical/oblique collision rays against uploaded meshes. Close and wide views of seed 69175541, room 10 were rendered and inspected using the actual game renderer. Logs and captures: `artifacts/canyon-faceted-*`. Campaign files were not used by the visual checks.

## Canyon terrain and mission themes

Content version `deathward-m1-16` adds Seeded Theme, Western Mine and Canyon choices. Canyon has a dedicated terrain generator with irregular basins, curved trails, continuous mesas and rock outcrops. Navigation, bullets and sight use the same triangulated height field that is rendered. Enemy counts use navigable basin area. Original atlas colors, terrain shadows and world-space strata distinguish sand and rock; cliffs and cover retain their full generated height. Mouse target picking follows the visible terrain surface. Mission titles persist through checkpoints, results and history.

The new terrain replaces the first canyon pass's rectangular borders, cube cover, stretched cliff pieces and overhead beams. The existing mine and town remain available. See [mission themes](mission_themes.md) for implementation boundaries and [Western asset notes](../assets/western/README.md) for source texture provenance.

The Release build, all six headless suites, full graphics input suite and terrain asset suite pass. Coverage includes routes to every objective/door, sealed canyon necks, repeatable encounters, safe spawns and terrain ray agreement with rendered triangles. The terrain suites also pass AddressSanitizer/UndefinedBehaviorSanitizer; graphics uses the existing `ASAN_OPTIONS=detect_leaks=0` driver shutdown exclusion.

Verification artifacts use the `artifacts/canyon-v2-` prefix. Visual review includes the supplied seed 69175541 and room 10, plus combat, quiet rooms and low-angle rotated camera views. Tests use temporary campaigns. Human review remains the final check for the environment's visual quality.

## Native 3D town editor

The town now has an in-game placement editor, opened with F4 in the hub, the pause-screen Town Editor button, or `--editor`. It renders the original textured library with mesh picking, a searchable scene list and asset palette, move/rotate/scale handles, numeric transforms, snapping, duplication/deletion, 80-step undo/redo, free camera controls and gameplay markers. Saving retains backups, validates staged files and rebuilds outdoor navigation from the edited visible geometry. Returning to the hub after saving reloads both resources. The editor and game use source town assets in a checkout and fall back to assets beside the executable in a packaged build. See [the editor guide](town_editor.md) for controls and navigation limits.

The Release build and all five headless suites pass (11.21 seconds). The full graphics input suite passes, including the hub editor shortcut and the previous movement, camera, combat and mission checks. Original town asset loading/rendering checks pass. The dedicated editor graphics suite verifies exact round trips for all original affine instance transforms, rejected malformed loads, actual mesh picking and handle dragging, transform/placement/delete history, clean/dirty transitions, scene/navigation backups, failed-save preservation, saved station reachability, camera gestures and unsaved-close handling. A floor/block fixture confirms that moving and deleting geometry updates both old and new navigation footprints. A full-town save and native navigation rebuild measured about 115 ms in the Release test; this is a local measurement, not a guarantee for larger scenes.

The editor suite also passes AddressSanitizer/UndefinedBehaviorSanitizer with `ASAN_OPTIONS=detect_leaks=0`, using the existing exclusion for external graphics-stack shutdown allocations. The actual executable's direct editor entry and interface were rendered and visually inspected. Tests edit temporary town packs; the original town scene, navigation, GLB and textures remain unchanged. Logs: `artifacts/editor-{build,tests,core-tests,input-tests,town-assets-tests,asan-tests,main}.log`. Captures: `artifacts/editor-main.png` and `artifacts/town-editor.png`.

## Middle-button camera rotation

Holding the middle mouse button and dragging now orbits the camera in both town and expeditions. Horizontal movement rotates around the character; vertical movement tilts between 25 and 75 degrees. Rotation keeps the current zoom, stops on release, and persists through room changes, returning to town and launching another expedition. WASD and ground picking use the current view. HUD-origin drags and modal screens do not rotate; pausing cancels an active drag until another press. Middle-click no longer dodges; Space and the Dodge button remain available.

The Release build and full graphics input suite passed. New checks exercise rotation without a press-time jump, immediate release, constant camera distance, both tilt limits, precise ground clicks in rotated town/mission views, camera-relative WASD, unchanged position/shots/dodge from rotation alone, HUD and modal guards, and retained angles across room/mission transitions. Existing zoom, combat, interaction, navigation, cheat and death checks also pass. Logs: `artifacts/camera-orbit-build.log` and `artifacts/camera-orbit-input-tests.log`.

## Hub mouse navigation correction

Town mouse movement now follows direct segments over clear terrain and smooths obstacle routes instead of visiting every grid-cell center. Valid clicks retain their exact position, including clicks within the player's current cell. Segment checks preserve blocked corners and the terrain's step-height limits. Analytic ray intersections replace fixed-distance terrain sampling so small visible patches can be selected. Clicks on blocked ground request a nearby walkable edge. Holding a mission-board click retains the interaction when the cursor moves away; dragging a HUD click into the world does not start movement. WASD movement is unchanged.

The Release build, all five headless CTest suites (12.52 seconds), and the complete graphics input suite passed. New regressions cover direct diagonal travel, precise arrival, repeated steering requests, obstacle detours, blocked corners, gradual slopes, and oblique/vertical rays near terrain-cell edges. Graphics checks cover precise town clicks at normal and closer zoom, HUD drags, and held board interactions alongside existing WASD, mission, combat and camera checks. Town navigation also passes AddressSanitizer/UndefinedBehaviorSanitizer. Logs: `artifacts/hub-mouse-{build,core-tests,input-tests,nav-asan}.log`.

## Original demo town as the starting hub

Content version `deathward-m1-14` replaces the status-only start screen with a walkable import of `PolygonWestern/Scenes/Demo.unity`. The authored town stays fixed; the station's added mission board launches the existing randomly seeded expeditions. Clicking Missions automatically walks to the station. The menu offers a fresh seed, an editable seed for replay, and departure. Victory, death and retreat resolve through the existing result screen and return to the town arrival point with another mission offer. Walking around town does not create a pending expedition or change campaign outcomes.

The import resolves **1,269 prefab instances into 1,516 active mesh placements**, including hierarchy, scene overrides, added children, inactive objects, material variants and FBX pivots. Its GLB contains **398 mesh/material sections, 20 materials and 12 embedded textures**. `scripts/verify_town.py` passes: every placement matrix matches its resolved Unity source after the coordinate-handedness conversion; every mesh/material assignment matches; all **691 source hashes**, output hashes and **12 pixel-identical embedded images** match. The retained sources successfully rebuild without accessing the external Windows project. Fourteen stale overrides have no source target; three unavailable collider references use the corresponding visible meshes. Both are recorded. See [the town import notes](../assets/town/README.md) for conversion details and rendering differences from Unity.

The Release build is warning-free. All **five headless CTest suites pass** (11.25 seconds), including new navigation checks for station reachability, a complete round trip, collision barriers, ground-height following, mouse-ray terrain picking and missing-asset handling. The grid includes 200,110 connected outdoor cells at 0.4-unit spacing. The full graphics input suite passes actual WASD and mouse movement in town, walking to the station, fresh-seed selection, invalid-seed recovery, mission launch and return with persisted outcomes, alongside the previous combat, zoom, key, power, cheat and death checks. The bandit model suite also passes after adding support for terrain elevation and hub animation.

`deathward_town_assets_tests` passes packaged loading away from the repository, exact placement/mesh counts, texture and glass presence, drawing at three town locations, missing-pack handling and repeated cleanup/reload. Its intentional missing-pack check emits a `TOWN: Missing town scene catalog` error before the final PASS. Town navigation passes AddressSanitizer/UndefinedBehaviorSanitizer. The town graphics suite passes address/undefined-behavior checks with `ASAN_OPTIONS=detect_leaks=0`; the previously isolated WSL/X11 shutdown leak baseline remains excluded from graphics runs.

The town, station menu, generated mission entrance and post-mission return were rendered through the real Game/Renderer and visually inspected. A separate 600-frame hub run at 1440 × 900 with 4× MSAA, **after initial loading**, measured **11.62 ms mean**, **14.20 ms p95**, and **17.81 ms maximum**. This is an arrival-street measurement on the current WSL graphics setup, not a guarantee for every view or machine. Original directional/point light transforms and colors feed a raylib diffuse shader; Unity-specific shadows, post-processing and water shaders are not reproduced pixel for pixel.

Logs: `artifacts/town-{build,tests,input,assets-tests,player-tests,source-verification,nav-asan,assets-asan,preview}.log`. Captures: `artifacts/town-hub.png`, `artifacts/town-missions.png`, `artifacts/town-mission-start.png`, and `artifacts/town-return.png`.

## Textured PolygonWestern scenery

Content version `deathward-m1-13` integrates individual Western pieces into the generated rooms. Twenty selected Unity prefabs and an adapted flat sand tile produce 21 assets in 26 mesh/material sections. The GLB embeds the original 2048 × 2048 atlas; a decoded-pixel comparison matches the source PNG exactly. All 43 source-file hashes, the GLB manifest hash and packaged GLB/catalog copies match. The retained sources and import scripts rebuild without the external Unity project. Details and rendering limits are in [the Western asset notes](../assets/western/README.md).

Crate stacks fit existing obstacle volumes, fence panels follow boundaries, and tracks and lanterns follow passages. Separately seeded buildings and props are rejected wherever they overlap playable floor. Ambient/directional lighting replaces Unity's URP setup; glass retains its tint and alpha and renders after opaque objects without writing depth. The room graph, gameplay collision volumes, encounter rules and gameplay RNG streams remain unchanged.

The Release build and all four headless CTest suites passed (12.41 seconds). The complete graphics input suite passed, including zoomed mouse controls, room traversal, keys, power choices, cheats and animated death. `deathward_western_assets_tests` passed **9,356 placements across five seeds**, checking original texture/glass, meter scale, catalog/mesh bounds, finite transforms, complete cover volumes, floor coverage, unobstructed routes, identical-seed reproduction, drawing, missing-asset fallback and resource reload/cleanup. The same asset suite passed with AddressSanitizer/UndefinedBehaviorSanitizer and `ASAN_OPTIONS=detect_leaks=0`; leak detection is excluded because the previously isolated WSL/X11 shutdown allocations also occur with an empty raylib window. This is not a clean graphics LeakSanitizer claim.

Quiet-room and combat captures were visually inspected at 1440 × 900, along with a close mouse-wheel view of the textured cover and bandit. The final **600-frame stress run** measured **11.39 ms mean**, **14.95 ms p95**, and **472.84 ms maximum**, including initial asset loading. Mean simulation/draw/presentation times were 0.95/4.58/5.87 ms. The workload retains 1,082 peak projectiles, 999 kills, depth 16 and 1,164 suppressed descendants. Mean and p95 meet the 16.67 ms budget; loading and occasional frame spikes remain, and this is not a guarantee for every room or machine.

Logs: `artifacts/western-{build,core-tests,input-tests,assets-tests,assets-asan,benchmark}.log`. Captures: `artifacts/western-empty.png`, `artifacts/western-combat.png`, `artifacts/western-close.png`, and `artifacts/western-stress.png`.

## Visible FPS counter

A compact counter now shows raylib's measured frame rate in the top-right corner on every screen, independently of cheat mode and the shortcut panel. The Release build passed; 90-frame hub and combat smoke checks completed and their captures were visually inspected for legibility and placement above the existing HUD. Captures: `artifacts/fps-hub.png` and `artifacts/fps-combat.png`.

## Mouse-wheel camera zoom

Content version `deathward-m1-12` adds smooth vertical-wheel zoom, with upward scrolling moving closer and downward scrolling widening the view. Camera distance is bounded to 0.35–1.5 times the original distance. The viewing angle stays fixed, and the framing offset scales with zoom to keep the player visible. Zoom persists across room changes, debug room jumps and new expeditions within the same session. HUD controls, horizontal scrolling, pause and power-choice screens do not issue zoom commands; pressing the middle button still dodges.

The Release build and complete graphics input suite passed. Added checks exercise smooth movement, both limits, unchanged viewing angle, no movement/fire/dodge caused by scrolling, ignored HUD/modal input, accurate ground clicks at both limits, and retained zoom across room jumps and expeditions. The close and wide views were rendered with the real Game/Renderer and visually inspected at 1440 × 900. Log: `artifacts/zoom-input-m1-12.log`; captures: `artifacts/zoom-close-m1-12.png` and `artifacts/zoom-wide-m1-12.png`.

## Animated bandit player

Content version `deathward-m1-11` replaces the player's primitive character with the supplied FBX bandit and original embedded texture. A Blender 3.6.23 conversion produces one self-contained GLB with 48 bones and nine clips: idle, walk, run, fire, a running slide, two jumps and two deaths. Moving dodges use the slide; dodges from rest use the standing jump. The forward jump is retained as an additional imported clip. Planar root motion is removed; vertical motion is retained. Local bone transforms interpolate and crossfade, with firing blended over locomotion on the upper body. Animation follows simulation time, including pause, reward screens and slow time. Natural death freezes combat and plays a two-second animation before resolution; F9 still resolves immediately.

The Release build and all four headless CTest suites passed (12.81 seconds total). Graphics input checks passed, including a new natural-death presentation, frozen combat during death, eventual summary and correct death resolution when closing the window during the animation. The dedicated `deathward_player_model_tests` passed: loading from another working directory, packaged asset availability, original 2048 × 2048 texture, normalized skin weights, all nine clips, changing poses, movement/fire selection and blending, pause/slow timing, stationary roots, bounded finite skinned vertices, non-looping death, reset between expeditions, missing-asset fallback and repeated resource cleanup. The manifest's nine source hashes, output hash and packaged copy also match.

Gameplay contracts passed under AddressSanitizer/UndefinedBehaviorSanitizer (28.14 seconds). The model and input graphics suites passed their assertions under sanitizers, but default LeakSanitizer reported shutdown allocations in the external graphics stack. A minimal program that only opens and closes a raylib window reproduces the model test's exact 67,032 bytes in nine allocations, including X11 input-method memory. The graphics suites were rerun with `ASAN_OPTIONS=detect_leaks=0` for address/undefined-behavior checks; these pass. This does not claim a clean LeakSanitizer exit for graphics. Logs are in `artifacts/bandit-*-asan*.log` and `artifacts/bandit-graphics-leak-baseline.log`.

The actual player renderer was visually inspected across idle, walking, two running strides, firing, firing while running, both dodges, both deaths and a facing change in `artifacts/bandit-animation-preview.png`. The packaged model was also inspected in the game at 1440 × 900 in `artifacts/bandit-game-empty.png` and `artifacts/bandit-game-combat.png`.

The 600-frame stress check with the animated player measured **12.29 ms mean**, **16.10 ms p95**, and **193.33 ms maximum**, including the initial asset load. Peak projectiles (1,082), kills (999), maximum chain depth (16) and suppressed descendants (1,164) match the previous workload. This measurement ran alongside a sanitizer build, so it is not an isolated performance comparison. Human review of the slide/jump animations compressed into the existing 0.22-second dodge remains useful. Log: `artifacts/bandit-benchmark.log`.

## Fifteen enemy types and room-area populations

Content version `deathward-m1-10` implements the complete [enemy roster](enemy_roster_proposal.md). Ordinary attacks have warning and recovery states, distinct primitive models and weapon/ground cues. The update includes frontal armor, interruptible protective auras, wall-stunned charges, expanding shockwaves, colliding hooks and player pulls, delayed explosives, lingering fire, one-bounce hostile rounds, warned teleportation, delayed friendly-fire death blasts, and paired chain barriers. No type summons reinforcements. Delayed hazards retain bounded event-chain accounting; room changes and clear-room cheats remove them.

Normal population is `clamp(ceil(usableFloorArea / 70), 4, 24)`, using the generated room's floor strips minus obstacle intersections. Corridors and missing corners are excluded. Quiet/power rooms receive zero enemies; the initial boss remains one Sheriff. Group composition and placement use independent per-room seed streams. Three roles are selected per normal room, with basic enemies making up roughly half or more of the group; chain pairs consume existing slots.

Release build and all four CTest suites passed, as did the graphics input suite. The new behavior checks exercise every enemy type, warning delays, missed melee swings, shotgun spread, sniper speed, ricochet reflection, armor bypasses, aura interruption/cover, persistent fire, fuse timing and kill-chain provenance, charge collision/stun, shockwave and hook counters, warned teleportation, chain damage/cover/death, hazard-cap suppression and clear-room cleanup. Population checks across **32 seeds** found **481.942–1,568.02 square units** of usable combat-room floor and **7–23 enemies**, with all fifteen types appearing. Every initial group matched its calculated count and had safe, non-overlapping placements at least six units from the player. Checks also reproduce group composition, placement and opening cooldowns after different prior room visits and combat RNG draws. Existing suites cover 64 complete geometries and 10,004 room graphs. Logs: `artifacts/enemies-core-m1-10.log`, `artifacts/enemy-behaviors-m1-10.log`, `artifacts/enemies-input-m1-10.log`.

All four CTest suites also passed under AddressSanitizer/UndefinedBehaviorSanitizer: gameplay 22.09 seconds, enemy behaviors 59.63 seconds, generated dungeons 243.39 seconds, and room graphs 14.47 seconds. The expanded hazard-budget/cleanup checks additionally passed in the final enemy sanitizer run. Results are recorded in `artifacts/enemies-asan-m1-10.log` and `artifacts/enemy-behaviors-asan-m1-10.log`.

All fifteen models were rendered with the actual game renderer and visually inspected in `artifacts/enemy-roster-m1-10.png`. A normal three-role encounter and its targeting/bomb warnings were inspected in `artifacts/enemy-combat-m1-10.png`.

The 600-frame stress run at 1440 × 900 with the expanded roster measured **9.45 ms mean**, **13.17 ms p95**, and **50.27 ms maximum**. Ten bursts start with 100 enemies and 600 shots; peak active projectiles were 1,082, maximum accepted chain depth 16, and 1,164 descendants were suppressed by configured budgets. Mean simulation/draw/presentation times were 0.88/4.01/4.57 ms. Mean and p95 meet the 60 FPS budget; occasional frame spikes remain. This is a scripted stress measurement, not a guarantee across every room or machine. Log/capture: `artifacts/enemy-stress-m1-10.*`. Human tuning of the new encounter difficulty and attack readability remains playtest work.

## Interaction prompt cleanup

Removed floating control labels from passages, keys, power pedestals and objectives. Open exits now have small floor chevrons alongside the existing lanterns; locks, pickup models and objective markers remain visible. The expedition HUD uses action names without mouse-button abbreviations, and control reminders are available outside active play. The Release build and graphics input suite passed, including mouse doorway traversal, key pickup, locked-door unlocking, power selection, rescue, pause and retreat. The quiet starting room was rendered and visually inspected in `artifacts/clean-prompts-m1-9.png`; input results are in `artifacts/input-clean-prompts-m1-9.log`.

The [15-enemy roster](enemy_roster_proposal.md) is a design proposal only and does not change the current enemy implementation or single-group encounter rules.

## Seeded branching room networks

Content version `deathward-m1-9` replaces the nearly full 4×4 template with a growing room network. Seeds choose two or three starting routes, the preference for extending branches or creating junctions, zero to three optional loops, and branch-end locations for the boss and power caches. The boss is at least three passages from the start. Room identities are shuffled independently of growth order, and row/column spacing varies from 48 to 64 world units. Corridors connect neighboring graph cells, preserving distinct doorways without crossing other passages or unrelated rooms. Layouts still contain 15 rooms with an enemy-free start, one enemy group per combat room, one or two power caches and enough reachable keys for every lock.

Release gameplay, generated-dungeon and graphics-input checks passed. The new fast graph suite passed 10,004 seeds, including the largest unsigned seed values, checking reproduction, connectivity before locks, unique positions/passages, junctions, boss distance and locked leaf rooms. Across the first 256 seeds it measured **232 distinct footprints** after normalizing translation, rotation and reflection; **256 distinct structural profiles** based on degree and path-distance distributions; all four loop counts; seven dead-end counts; seven boss depths; and six graph diameters. These diversity checks do not depend on shuffled room labels or obstacle geometry.

The existing 64-seed geometry suite passed with the new arrangements, including room and corridor navigation, locked-door isolation, key availability, floor connectivity, enemy placement and forward/reverse traversal. All three CTest suites also passed under AddressSanitizer/UndefinedBehaviorSanitizer (22.37 seconds for gameplay, 229.04 seconds for full geometry, and 11.85 seconds for the 10,004 graph seeds); results are in `artifacts/layout-asan-m1-9.log`. Six generated maps were compared visually in `artifacts/layout-comparison-m1-9.png` and the scalable `.svg` version, using exported room floors and passage connections. The updated game/minimap was also rendered in `artifacts/branching-layout-m1-9.png`. The same seed and content version reproduce the same map; N in the hub selects a different seed.

## Unobstructed cheats and one enemy group per room

Content version `deathward-m1-8` keeps cheats enabled by default with the shortcut panel hidden. Hidden panels do not intercept mouse controls. F1 toggles cheats without opening the panel; the backtick key separately opens or hides the optional shortcuts and diagnostics, in the hub or expedition.

Combat rooms spawn a single enemy group on entry. Defeating it reopens the combat seals immediately; waiting or revisiting cannot spawn reinforcements. Wave counters, timers and the wave HUD are removed. The starting room remains enemy-free. Room and boss replays position the player before spawning enemies and begin exactly one encounter.

Release build, both CTest suites (including 64 generated seeds), raylib mouse/function-key input checks, and the gameplay contracts under AddressSanitizer/UndefinedBehaviorSanitizer passed. The complete expedition test verifies enemies on entry, immediate clearing after one group, no respawn after waiting, and empty revisits. Mouse checks now run with cheats enabled and the panel hidden, and verify the separate panel toggle. Sanitizer gameplay results are in `artifacts/asan-core-m1-8.log`; input results are in `artifacts/input-m1-8.log`. The unobstructed combat view was rendered and visually inspected in `artifacts/hidden-cheats-m1-8.png`.

## Default cheats and a quiet starting room

Content version `deathward-m1-7` enables cheat mode and its shortcut panel on application startup. F1 still toggles the mode and F2 separately toggles invincibility. The starting room is always enemy-free with open exits, including on revisits and room restarts. It counts toward the existing one-to-two quiet-room limit; the seed may choose one additional quiet room.

Release build, both CTest suites and the raylib input suite passed. All 64 generated seeds have a quiet starting room while preserving the quiet-room limit and combat at objectives. Input checks verify that cheats work immediately without first pressing F1 and can still be disabled. The starting-room scene was rendered and visually inspected in `artifacts/start-room-m1-7.png`; input results are in `artifacts/input-m1-7.log`.

## Quiet rooms and function-key cheats

Content version `deathward-m1-6` chooses one or two ordinary enemy-free rooms per seed, in addition to the separate power caches. Quiet rooms open immediately, never start waves, and stay cleared on revisits without repeated healing or completion credit. They can contain a seeded key and are marked E on the map. Opening, objective and boss encounters remain intact.

F1 now exposes a labeled cheat mode with a complete shortcut legend. New shortcuts heal/reset cooldowns, grant keys, clear all remaining waves, jump to the next numbered room and replay the current room. Replays preserve the seed, build, keys, unlocked doors and claimed powers. Boss replay resets the encounter and seals its entrance even after a previous defeat. Whole-room clearing discards pending projectiles and effects, including stress-scene work. Victory and defeat work immediately from pause and reward screens. Disabling cheat mode gates the shortcuts and turns off invincibility, slow time and collision overlays.

Release CTest and the raylib input suite passed. The 64-seed suite checks deterministic placement and the one-to-two limit separately for quiet rooms and power rooms, alongside the existing connectivity and key checks. Gameplay contracts cover peaceful-room revisits, wave skipping, stress cleanup, room completion counts, preserved power rewards and repeated boss encounters. Real function-key events verify disabled-mode guards, healing, killing, full clears, item/key grants, room/camera jumps, replays and paused/modal outcomes.

Both CTest suites also passed under AddressSanitizer/UndefinedBehaviorSanitizer: gameplay contracts in 24.45 seconds and generated maps in 240.38 seconds. Results are recorded in `artifacts/sanitizers-m1-6.log`.

The cheat panel and quiet-room scene were rendered and visually inspected at 1440 × 900 in `artifacts/cheats-m1-6.png` and `artifacts/empty-m1-6.png`. Input results are recorded in `artifacts/input-m1-6.log`.

## Branches, combat doors, power rooms and keys

Content version `deathward-m1-5` expands the mine to 15 rooms with a connected combat network, junctions and three additional loop connections. The starting room always has two routes. One or two separate power rooms and the boss room have key-locked entrances. Each power pedestal offers two choices and can grant exactly one item once; normal combat rooms grant none. All keys are placed in the unlocked combat network, with one key available per locked door. Entering an uncleared combat room seals all of its doorways, including the previous entrance, only after the player has safely crossed the threshold. Clearing the room reopens the combat seals. Room clears, collected keys, unlocked doors and claimed powers persist for the run.

Release CTest, graphics input checks, and both CTest suites under AddressSanitizer/UndefinedBehaviorSanitizer passed. The 64-seed map suite verifies deterministic geometry and pickups, 15 distinct room dimensions, branching/loops, one or two power rooms, key reachability before any lock is opened, sufficient keys, closed-door collision, forward/reverse passage routes, objectives, boss clearance and floor connectivity. Gameplay checks verify entrance sealing without trapping or teleporting the player, reopened doors, no repeated healing, keys collected once, exactly one key spent per unlock, and no second charge on an unlocked door. The full expedition contract clears all 15 rooms and verifies the two-power maximum.

The mouse suite follows the complete pickup/unlock/claim flow through the real Game and Renderer: an attempted unlock without a key fails, clicking a key collects it, clicking a locked doorway spends one key and walks into the power room, and clicking its pedestal and reward button claims exactly one item. Existing combat, pause, rescue, retreat and persistence checks also pass. Key-room, power-room and two-choice reward captures were visually inspected in `artifacts/*-m1-5.png`.

The 600-frame stress check at 1440 × 900, seed `1866`, measured **10.38 ms mean**, **13.45 ms p95**, and **41.73 ms maximum**. Peak active projectiles: 1,073; maximum chain depth: 16; suppressed descendants: 311. Each of ten bursts starts with 100 enemies and 600 shots. Mean simulation/draw/present times: 1.02/4.11/5.26 ms. These measurements cover the current starting chamber and stress build; logs are in `artifacts/branching-benchmark-m1-5.log`.

## Connected, generated rooms

Content version `deathward-m1-4` replaces the repeated arena with one continuous seven-room mine. Its independent layout RNG determines room dimensions, footprint orientation, corridor turns, objective positions and cover geometry. Dimensions are distinct within each expedition, between 24 and 40 units on each axis. Four footprint families are used: rectangle, clipped corners, L and cross. Gates open after rewards; cleared corridors remain traversable. The camera follows world-space movement, and the map shows connected rooms and the player's position.

Release build and both CTest suites passed, including the complete AddressSanitizer/UndefinedBehaviorSanitizer run. `generated_dungeons` checks 64 seeds for exact geometry reproduction, variation, distinct room dimensions, obstacles in every room, connected walkable floor, blocked/open gates, reachable entry/exit/objective positions, a complete mine route and boss clearance. Additional checks cover campaign-independent geometry, valid enemy spawns in all seven rooms and continuous backtracking without repeated healing or encounter resets. The normal progression test now walks through all six corridors and asserts that transitions never teleport the player.

The graphics input suite passed with the generated layout: ground and enemy clicks, target tracking, Shift/RMB firing, HUD controls, mouse doorway traversal, camera tracking into another room, objective approach, rescue and retreat. Scripted combat and boss scenes use room-relative aiming and isolated temporary campaigns. The updated room geometry and map were rendered for visual inspection.

The 600-frame rendered stress check at 1440 × 900, seed `1866`, measured **6.56 ms mean**, **8.81 ms p95**, and **42.41 ms maximum**. Ten bursts each began with 100 enemies and 600 shots; peak active projectiles were 906, maximum chain depth 16, and 861 descendants were suppressed by the configured budgets. Mean simulation/draw/present times were 0.33/2.49/3.73 ms. This measures the current generated starting chamber and build, rather than performance across every seed or room. Logs and captures are in `artifacts/connected-rooms-*-m1-4.*`.

## Diablo-style control and balance update

Content version `deathward-m1-3` changes LMB to contextual ground movement, enemy targeting, and objective interaction. Holding a selected enemy tracks it until release; target death does not issue a movement command. Shift holds position and Shift + LMB force-fires; RMB directly fires the revolver. Starting health is 200 HP and revolver damage is 48. Enemy damage and the reload-free six-shot cycle are unchanged.

Release build, `ctest --test-dir build --output-on-failure`, `ctest --test-dir build-asan --output-on-failure`, and `./build/deathward_input_tests` passed. Core checks verify the new health/damage values, percentage health costs, cancellation of navigation when attacking or holding position, sustained fire, sixth-shot effects, and the existing gameplay/persistence contracts. The graphics input checks exercise contextual LMB movement without shooting, body picking, tracking an enemy after both it and the cursor move, holding after target death, Shift attacks, RMB attacks, short clicks between simulation ticks, objective body selection, dodge, pause/resume, retreat, and saved consequences. HUD and paused clicks do not fire.

The updated HUD was rendered and visually inspected in `artifacts/diablo-controls-m1-3.png`. This scripted scene grants all five items, so its health display is 160/160 after Judas Bullet's 20% cost; a fresh expedition starts at 200/200.

## Previous mouse control update

Content version `deathward-m1-2` adds continuous firing with no reload pause and mouse navigation alongside WASD. Release and AddressSanitizer/UndefinedBehaviorSanitizer contract checks passed after this change. Added checks verify sustained firing with unchanged cadence across six-shot cycles, sixth-shot penetration, navigation around cover, clicks inside cover/outside arena bounds, keyboard override, and automatic rescue/altar/exit interactions on arrival. The updated controls were rendered and visually inspected.

`./build/deathward_input_tests` also passed. This uses raylib's automation input events and the actual Game/Renderer code in a hidden graphics window. It verifies mouse launch, ground-point projection and movement, holding LMB across multiple cylinders, middle-button and onscreen dodging, pause/resume, right-click rescue, mouse retreat and saved consequences. HUD and paused clicks leave the shot count unchanged. It uses an isolated temporary campaign and is run explicitly because the normal CTest suite remains usable without a graphics display.

## Original milestone baseline

The results below were recorded on 2026-09-27 against `deathward-m1-1`; the rendered performance numbers are a historical baseline, not a new benchmark of the control or balance updates.

## Environment

- Ubuntu 22.04 userspace on WSL2, Linux `6.18.33.2-microsoft-standard-WSL2`.
- AMD Ryzen 5 5600X, 6 cores / 12 logical CPUs.
- NVIDIA GeForce RTX 4070 Ti SUPER through Mesa's D3D12 renderer, Mesa 23.2.1.
- GCC 11.4, CMake 3.22.1, C++20, pinned raylib 5.5.
- Release build, 1440 × 900 window, 4× MSAA; benchmark has no application FPS cap.

## Automated gameplay checks

`ctest --test-dir build --output-on-failure`: passed.

`ctest --test-dir build-asan --output-on-failure`: passed with AddressSanitizer and UndefinedBehaviorSanitizer enabled for gameplay and persistence code.

The contract suite checks:

- Swept sphere and box collisions, including misses above collision volumes.
- Each starting item, ricochet → hit → split, kill → explosion → kill → explosion, and ghost shots inheriting projectile effects.
- Exactly one kill transition when multiple queued hits target one enemy.
- Bounded branching, depth diagnostics and reclamation after descendants expire.
- Encounter and reward streams remaining identical after extra combat RNG draws.
- Rescue persistence, interrupted-run recovery, outcome idempotence, run-power reset, distinct incomplete victory, recovery from setbacks and repeat-visit reward protection.
- Save checksum rejection and campaign-reset backups.
- All six ordinary chambers, their reward choices, optional interactions, the boss chamber and expedition completion through debug shortcuts.

## Window-level checks

An X11 script sent actual keyboard and window-manager close events to the application, using an isolated temporary campaign. It verified:

1. Enter launches; debug grants and rescue checkpoint; window close resolves retreat. Population becomes 48 and prosperity 42.
2. The next expedition's victory shortcut restores the mine. Population stays 48 and prosperity becomes 62.
3. A later process is force-killed during an expedition. On restart, retreat resolves from the checkpoint and prosperity becomes 54.
4. A second restart leaves the campaign bytes unchanged, proving that recovery does not apply the outcome again.

Hub, combat, reward, boss and summary screenshots were captured and visually inspected for readable layout. The current 3D stress view was also inspected after rendering changes.

## Rendered stress baseline

```sh
./build/deathward --benchmark --frames 600 --screenshot artifacts/stress.png
```

Seed: `1866`. Ten bursts, each starting with 100 enemies and 600 projectiles, with all five effects. Bursts restart every 60 simulation ticks. The workload includes normal enemy attacks, secondary projectiles, explosions and recursive kill chains. Enemy count can fall to zero when the build clears a burst; this is a repeated burst benchmark, not a constant 100-enemy population.

| Measurement | Result |
| --- | ---: |
| Frames | 600 |
| Mean total frame time | 7.27 ms (~138 FPS) |
| 95th percentile frame time | 9.69 ms |
| Maximum frame time | 49.99 ms |
| Mean simulation time | 0.13 ms |
| Mean draw submission time | 3.04 ms |
| Mean presentation / remaining time | 4.10 ms |
| Peak active projectiles | 1,065 |
| Minimum active projectiles during sampled frames | 600 |
| Enemies killed | 999 |
| Maximum accepted chain generation | 16 |
| Suppressed descendants at generation limit | 788 |

Mean and 95th percentile are below the 16.67 ms budget for 60 FPS. The maximum shows occasional frame spikes; this is not a guarantee that every frame meets the target. Results include presentation through WSL's graphics stack and should be remeasured on the intended playtest machines.

The first baseline averaged 20.83 ms. Grouping projectile drawing by primitive type, using tiny generated projectile meshes, and caching explosion ring geometry reduced rendering cost. Combat rules, RNG, chain limits and workload were not reduced to obtain the final result. All benchmark versions produced the same 999 kills, 1,065 peak projectiles and 788 suppressed descendants.

The suppressions are explicitly counted and logged: deeply branching interactions reach the depth-16 limit. They do not represent hidden reductions to the starting stress load. Other default ceilings are 8,192 accepted events per chain, 2,048 processed events per tick, 16,384 queued events, 4,096 active projectiles and 256 living enemies.

## Remaining playtest work

- Human validation of combat feel, readability under extreme combinations, and the 5–10 minute expedition target. Automated shortcuts prove the loop, not whether its pacing is enjoyable.
- Windows build/runtime validation; this milestone was verified on Linux only.
- Encounter variety: the seven chambers reuse one primitive arena layout. Production art, sound and a larger item/expedition catalog are outside this slice.
- Saves currently assume one game process per save path. Use separate `--save` paths for simultaneous sessions.

Screenshots and raw rendering logs are local artifacts under `artifacts/` and are excluded from version control. Gameplay tests use temporary directories and do not modify the player's normal campaign.
