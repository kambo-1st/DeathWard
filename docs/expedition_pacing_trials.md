# Expedition pacing trials

Milestone 2, 2026-10-24. This compares room count, corridor spacing and room dimensions separately before selecting **Compact** as the default. Original rendering and the Classic layout remain available.

## Results

Means across seeds `0–7`, `42`, and `1866`. Each controller explores one ordinary Canyon floor, obtains its first free item, visits the final encounter, then clears every remaining room and reaches the exit. The required-combat count includes the final encounter. A scheduled testimony room can add travel; this sample does not measure reading or story expeditions.

| Preset | Rooms | Ordinary width | Corridor length | First item | Final encounter arrival | Full clear + exit | Walking | Backtracking |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | ---: | ---: |
| Classic | 15 | 31.6 m | 23.4 m | 79.5 s | 171.0 s | 430.7 s | 315.8 s | 186.7 s |
| Growing: count only | 9 | 31.7 m | 23.9 m | 28.8 s | 99.7 s | 222.4 s | 171.4 s | 92.8 s |
| Short corridors | 9 | 31.7 m | 15.5 m | 25.5 s | 87.4 s | 194.5 s | 142.2 s | 76.9 s |
| Small rooms | 9 | 24.1 m | 30.9 m | 34.6 s | 99.3 s | 206.8 s | 172.0 s | 93.0 s |
| Compact: both | 9 | 24.1 m | 16.1 m | 27.5 s | 76.9 s | 159.3 s | 123.6 s | 65.7 s |

Compact reduced this controller's total floor time by about **28% against Growing**, and walking time by about **28%**. Shrinking rooms alone left their centers far apart and lengthened the corridors. Short Corridors reached the first item slightly sooner than Compact on average; Compact reached the final encounter and completed the floor sooner.

Compact had an average of **36.9 initial residents**, compared with 50.6 in Growing and 100.2 in Classic. Its route to the first item and final encounter crossed 4.2 combat rooms on average, leaving 1.3 optional combat rooms. Those are observed controller routes, not guarantees about the shortest possible route or all generated seeds.

The bare spacing target is 8–16 metres on the opening floor. Whole rows and columns reserve their largest room extents to prevent overlap, so the actual Compact corridors in this sample range from **8 to 26 metres**. Boss envelopes remain 32–40 metres. Ordinary envelopes begin at 20–28 metres and grow toward 24–40 metres as the expedition progresses. Classic retains its original geometry and dimensions.

## What the timings mean

The [controller](../scripts/measure-expedition-pacing.cpp) runs the actual fixed-tick simulation with normal weapons, generated residents, enemy attacks, navigation, keys, room seals and item effects. It enables invulnerability, uses no dynamite or dodge, chooses the first offered free item and never buys shop items. It fires while following a navigation route around the nearest eligible target. It takes shortest graph routes to available keys and rewards, then to remaining rooms. All **50 trials completed**, including the exit check.

These are **automated comparisons, not human playtest times or difficulty ratings**. Invulnerability ignores the cost of taking damage and cannot establish whether a layout is fair. The controller knows the graph, follows its own targeting policy, and does not account for hesitation or map discovery. Combat movement is part of total time; the walking column counts movement outside combat. Backtracking is the portion of walking assigned to approaches/passages already traversed.

The corridor-only variant preserves room envelopes, shapes and objective offsets. Terrain, cover and resident placement can change after repacking. Smaller-room variants also change geometry-dependent random draws, which can affect quiet-room and key placement. Consequently the timing differences should not be attributed solely to geometric distance. The separate collision, spawn, story and input tests remain necessary.

The controller caught a passage/interaction regression: a doorway command could redirect toward a nearby altar and stop before crossing the next threshold. Passage navigation now uses its exact destination; normal object clicks still interact. Both passage APIs have regression tests. Expanded early/late spawn checks also found a resident overlapping the corner of a gate once it closed; spawns now reserve the gate’s full collider. Re-running all 50 trials after that correction produced an identical CSV. The bounded item event system suppressed two over-depth chains during the sample; neither caused a timeout or prevented completion.

## Reproduction

These measurements describe milestone 2 at revision `79a2994`. Later milestones add destructible scenery and other gameplay, so use that revision to reproduce the recorded timings exactly. Classic continues to preserve the original geometry; current-head trials measure the current game.

Raw values, including per-seed outcomes and encounter counts, are in [deathward-pacing-trials.csv](research/deathward-pacing-trials.csv). Preset IDs are `0=Growing`, `1=Classic`, `2=Short Corridors`, `3=Small Rooms`, `4=Compact`.

```sh
cmake --build build --target deathward_core deathward_pacing_tests --parallel 4
./build/deathward_pacing_tests
c++ -std=c++20 -O2 -Isrc -Ibuild/_deps/raylib-src/src \
  scripts/measure-expedition-pacing.cpp build/libdeathward_core.a \
  -o /tmp/deathward-measure-pacing
/tmp/deathward-measure-pacing > /tmp/deathward-pacing-trials.csv
```

Append a seed, such as `1866`, to run only that seed across the five presets. Failed trials retain `-1` timing fields and a diagnostic result; do not average them as completed runs. The milestone progress log records build, graphics and regression validation separately.

For a reversible native comparison, launch with `--expedition-pacing classic`, `growing`, `corridors`, `rooms`, or `compact`. The mission-board button cycles the same presets. Browser launches accept `?pacing=classic` and the corresponding other names. The tutorial always keeps five rooms and its original room envelopes; the shorter-corridor variants can shorten its connectors.
