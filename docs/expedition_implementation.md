# Expedition implementation progress

Goal started 2026-10-24. Specification: [Isaac expedition study](isaac_expedition_study.md).
Starting revision: `a413435`. The complete goal is all six milestones below.

| Milestone | Status | Validation and remaining work |
| --- | --- | --- |
| 1. Configurable room counts | Complete | Growing/Classic presets, safe room allocation, native/WASM and save validation passed (details below) |
| 2. Early room and corridor dimensions | Pending | Separate trials, fixed-seed pacing measurements, navigation/spawn/terrain checks |
| 3. Destructible scenery and cache | Pending | Collision/render synchronization, deterministic once-only loot, safe blast ordering, room revisit state |
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
