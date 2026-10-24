# Expedition implementation progress

Goal started 2026-10-24. Specification: [Isaac expedition study](isaac_expedition_study.md).
Starting revision: `a413435`. The complete goal is all six milestones below.

| Milestone | Status | Validation and remaining work |
| --- | --- | --- |
| 1. Configurable room counts | Complete | Growing/Classic presets, safe room allocation, native/WASM and save validation passed (details below) |
| 2. Early room and corridor dimensions | Complete | Five reversible presets, 50 timed trials, Compact default, navigation/spawn fixes; native/WASM checks passed |
| 3. Destructible scenery and cache | Complete | 256-floor placement/navigation sweep; transactional blasts, persistent loot and cache; native/WASM/input checks passed |
| 4. Six interacting items | Pending | Both acquisition orders, duplicate effects, bounded chains, mouse/arrow firing |
| 5. Floor identities and first canyon boss | Pending | Progression by expedition floor, complete attack/phase/death behavior, resource-independent victory |
| 6. Boss expansion and optional rooms | Pending | Two further bosses, three optional room functions, separate pools, resource reachability and economy checks |

## Invariants

- Standard expeditions contain 4–8 seeded floors; The Lost Survey remains one five-room floor.
- Story locations fit inside each floor's room budget and remain reachable. Evidence stays attributed to its witness account.
- Original remains the default visual style. Existing assets are reused where appropriate.
- The existing 15-room layout remains available as a comparison preset during pacing trials.
- Native and WebAssembly builds must continue working. Each completed milestone receives focused validation and its own commit.
- The installed Isaac data in `reference/isaac-repentance-1.7.9b/` is research input, not game content.

## Work log

### Milestone 1

Implemented a default Growing preset: four-floor schedules use `9, 11, 13, 15`; eight-floor schedules use `9, 10, 11, 12, 13, 14, 15, 15`. Intermediate expedition lengths grow monotonically within the same range. Classic retains fifteen rooms throughout. Both preserve the five-room tutorial. Switch on the mission board, with native `--expedition-pacing growing|classic`, or browser `?pacing=growing|classic`.

Topology, room-state arrays, reward/boss indices, names, cheats and scripted captures now use the actual floor count. Floors under twelve rooms get one power cache; small floors reserve a shop before allocating keys and quiet rooms. All keys remain in the unlocked network. Story sites can share an ordinary encounter when slots are scarce. Landmark dressing now searches safe gaps across the room if its original radial search finds no space; paths, roads, water and other props remain protected.

Campaign format 6 records the pacing preset from launch through history. Formats 1–5 remain readable and retain Classic semantics. Advancing floors preserves the preset and the existing carry-over rules. The visual style and physical room/corridor dimensions are unchanged in this milestone.

Validation completed:

- Native build and all **27 CTest tests** passed. Extended topology checks cover **7,168 graphs** over every supported count (9–15), plus **10,004 Classic seeds**. Entrances retain multiple choices, ordinary networks need no key to traverse, and locked rewards/bosses remain leaf branches.
- Geometry/path checks cover **56 Mine/Canyon count-and-seed combinations**, including every objective, passage approach, shop and key. Plan tests cover 256 seeds and all five possible expedition lengths. Story-site checks span all 4–8-floor schedules.
- Full native input suite passed: arrow/mouse fire, shops, dynamite, coin/key/power pickups, doors, cheats, modal controls, camera and both pacing selections. The original seed-specific occlusion/pickup regression explicitly uses Classic; the dedicated combat/shop/dynamite cases and browser pickup checks use Growing.
- Full native story/input traversal passed: tutorial letter, Rourke launch, every floor, evidence and exit gates, journal controls, Eleanor return and saved progress. Format-4/5 migration, format-6 round trips and invalid evidence are checked.
- The ten-seed Classic layout CSV is **byte-for-byte identical** to `docs/research/deathward-floor-size-sample.csv`, including geometry, corridor lengths, roles and configured enemy budgets.
- WebAssembly Release build passed. `web/test.cjs` passed in Chromium with a display, including growing-floor money pickup, dynamite, shop, combat, final-room travel, victory, persistence and editor flows. `web/expedition-pacing-test.cjs` passed all four Growing/Classic power/boss cases with no JavaScript or GL errors. The first headless broad browser attempt was stopped because it fell back to slow software rendering; the displayed-browser rerun passed.
- Native Original-style canyon smoke capture inspected at `artifacts/expedition-growing-m1.png` (ignored artifact, not bundled game content).

Reproduction: `cmake --build build --parallel 4`, `ctest --test-dir build --output-on-failure --parallel 4`, `./build/deathward_input_tests`, `./build/deathward_arrival_input_tests`. Browser build: `EMSDK=/path/to/emsdk scripts/build-web.sh`; serve with `python3 scripts/serve-web.py --port 8091`, then run the browser scripts with `DEATHWARD_WEB_URL=http://127.0.0.1:8091/`, `DEATHWARD_HEADFUL=1` and `DEATHWARD_BROWSER=/path/to/chromium`.

Next: measure room count, corridor spacing and room dimensions as separate milestone-2 trials. Human playtest pacing and final balance are not established by these structural checks.


### Milestone 2

Milestone 1 committed as `f3d1ad2`. Added initial, opt-in `corridors`, `rooms`, and `compact` pacing trials alongside Growing and Classic. The ten-seed comparison supports Compact as the new default. All trial presets use the same 9–15-room schedule. Smaller opening rooms target 20–28 metres; compact boss envelopes retain 32–40 metres. Later floors gradually regain larger room sizes. The tutorial keeps its original five room envelopes and can trial shorter connectors.

The corridor trial moves complete rows/columns after generating room sizes, shapes and objectives, using a separate spacing stream. It reserves each row/column's largest room extent to avoid overlap. Actual corridor lengths can therefore exceed the nominal gap beside smaller rooms or large boss arenas; measurements must report that rather than claim all corridors fit 8–16 metres. Compact size pools reset when exhausted so a small range cannot hang the generator.

Measurements, default selection and final validation are complete. Results are recorded below.


The automated player completed all **50 first-floor trials** (10 seeds × 5 presets), using normal navigation, weapons, enemy behavior and the first offered item, with invulnerability enabled. The CSV is `docs/research/deathward-pacing-trials.csv`; the reproducible controller is `scripts/measure-expedition-pacing.cpp`. Compact averaged 159.3 simulated seconds to clear every room and reach the exit, compared with 222.4 for Growing and 430.7 for Classic. These are scripted-player comparisons, not estimates of normal player completion time. The narrower-room-only trial lengthened corridors, confirming that the changes must be measured separately.

The trial exposed an existing interaction bug: passage movement could retarget a nearby altar and stop short of the next room. Explicit passage requests now keep their destination and skip object interaction; ordinary ground/object clicks retain their behavior. Regression coverage checks both direct passage use and click-to-door commands. All 50 trials completed after this fix. Content version advances to `deathward-m1-55` for the new default; all comparison presets remain available.


Milestone-2 validation:

- Native Release build and **28/28 CTest tests pass**, including early/final-floor population and safe-spawn checks over 32 seeds, all pacing variants, sealed-gate clearance, size-pair exhaustion, compact story dressing, navigation and the five-room tutorial.
- The native input suite passed with Compact as the default, as did the full tutorial/Rourke/evidence/return traversal. Original-style Compact combat was visually inspected in `artifacts/expedition-compact-m2.png`.
- The final WebAssembly build succeeds. The broad browser suite passed default Compact combat, pickups, dynamite, shop, victory, persistence and editor flows without JS/GL errors. The pacing-specific browser suite checks all five presets, including actual preset IDs, room dimensions and dynamically indexed power/boss rooms.
- Classic's original ten-seed layout CSV remains byte-identical. All 50 scripted pacing trials complete after the navigation and gate-spawn fixes; their final CSV is unchanged by the gate-spawn correction.
- The expanded enemy test correctly checks opening **and final** floors: smaller openings intentionally offer seven population sizes (5–11 enemies in the 32-seed Mine sample), so demanding eight sizes on the opening floor alone was obsolete. The late-floor sample verifies larger populations without weakening safe-spawn or roster coverage.

Remaining after milestone 2: destructible scenery/cache; six interacting items; floor identities/first canyon boss; two more bosses/optional rooms/reward pools. The overall goal remains active.

### Milestone 3

Milestone 2 committed as `79a2994`. Added an optional reinforced supply alcove, two cracked boulders, one marked ore seam and one powder barrel to non-tutorial, non-Classic floors. A separate seeded placement stream prefers a single ordinary room, falling back to other eligible rooms when necessary. Alcoves have full-size and smaller variants. Terrain, roads, water, doors, keys, story sites and central routes remain protected. Unsafe placements are omitted rather than cutting into terrain or mandatory routes. These independent props never become part of the canyon height field.

Rules:

- A cracked boulder takes one spent dynamite blast, removes its cover and leaves flat rubble. Four out of five seeded rolls contain no loot; the remaining roll gives 1–2 coins.
- A marked seam takes one spent dynamite blast and yields 3–6 coins.
- The reinforced cache takes two blasts, visibly cracks after the first, and releases one key plus 8–12 coins inside its opened enclosure. Its three stone side walls remain intact. Nothing mandatory is inside it.
- Powder barrels have 30 health, so two starting revolver bullets ignite one. A visible 0.65-second fuse precedes an 80-damage, 3.6-metre blast with 20 player damage. The warning radius, fuse and barrel body are visible before detonation. There is no barrel loot. Leaving its room pauses the fuse; revisiting resumes it. Modal screens pause it too.
- Free Powder-of-Jericho explosions and secondary barrel blasts can ignite barrels but cannot break hard rocks or resource gates. A dynamite kill explicitly loses its hard-demolition permission before generating a free Powder explosion.

Each object has a stable ID, loot seed, health and once-only payout state. One explosion snapshots enemies, player and reachable prop surfaces before applying any destruction; a later explosion sees the changed geometry. Collision is rebuilt from the same object states used by the renderer, including its per-frame shadow casters. Broken props leave only flat, nonblocking debris. Opaque props participate in mouse picking; whole-object player occlusion fading also applies to these props. Player and enemy damage retain their existing cover protection and damage multipliers.

Cache interiors are reserved from resident placement, ordinary coins, summons, burrowing and teleport destinations. Reward positions are traversable after opening. Destroyed objects, partial damage, rewards and armed barrels survive room revisits. The game still resolves interrupted expeditions at load; this milestone does not introduce mid-floor save/resume. Classic remains available without the new props for the original comparison; the five-room tutorial is unchanged. Content version: `deathward-m1-56`.

Milestone-3 validation:

- All **29 native CTest groups passed**, including the new destruction suite. The placement sweep covers **256 floors**: 64 seeds × Mine/Canyon × opening/final floors of Rourke expeditions. All contain the complete set and a sealed, optionally accessible cache; **246/256** fit the entire set into one room. Paths to objectives, door approaches and ordinary keys require no dynamite.
- Focused tests check pre-blast cover with reversed prop order, later blasts through opened cover, partial damage and visits, exactly-once loot, independent deterministic loot streams, barrel gunfire/fuse/pause/revisit behavior, and free-explosion permission isolation. Additional targeted checks prevent both Western and Isaac-roster teleports/burrowing into the cache and complete a twelve-barrel cascade with exactly twelve secondary explosions and no retained chains.
- Native Release and WebAssembly Release builds pass. `web/destruction-test.cjs` passes in both Canyon and Mine: two actual placed sticks detonate on their normal fuse, open the cache, and a movement command walks into it and collects the key and coins. No JS or GL errors were reported.
- Original-style captures inspected: `artifacts/demolition-native-closed.png` and `artifacts/demolition-canyon-open.png`. Initial bright box-shaped rocks were replaced with muted, faceted rocks; demolition guidance uses an information panel rather than an inoperative action button. Generated screenshots are local ignored artifacts.
- The full native input suite passed: mouse/arrow firing, dynamite placement/kicking/throwing, keys, shops, doors, cheats, camera and modal guards. The broad browser suite passed hub travel/audio, pickups/dynamite/shop/combat/victory, save/reload, interrupted-run recovery and editor flows with no JS/GL errors. The final renderer also excludes the barrel warning ring and fuse glow from shadow casting; physical barrels still cast shadows.

Reproduce the focused suite with `./build/deathward_destruction_tests`. Visual smoke scenes: `--smoke --theme canyon --scene demolition` (closed), `demolition-open` (opened), or `demolition-run` (two real placements followed by entry/collection). Use `--frames 430` for the complete scripted traversal. The browser script uses the same displayed-Chromium environment variables as milestones 1 and 2.

Remaining after milestone 3: six interacting items; floor identities/first canyon boss; two more bosses/optional rooms/reward pools. The overall goal remains active.
