# Milestone 1 verification

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
