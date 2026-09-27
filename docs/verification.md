# Milestone 1 verification

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
