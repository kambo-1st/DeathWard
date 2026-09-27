# DeathWard

A playable C++20 / raylib 3D Weird West prototype. Borrow a broken build from Red Hollow Mine, bring its people home, and leave lasting consequences in Black Creek.

**The build is gone. The consequences remain.**

## Run on Linux

```sh
./scripts/run.sh
```

The script configures a Release build, downloads pinned raylib 5.5 on the first build, compiles, and launches. No game assets or other third-party packages are downloaded. CMake 3.20+, a C++20 compiler, OpenGL and X11 development libraries are required. On Ubuntu/Debian:

```sh
sudo apt install build-essential cmake libasound2-dev libx11-dev libxrandr-dev libxi-dev libxcursor-dev libxinerama-dev libgl1-mesa-dev
```

See the [raylib Linux build guide](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux) for other distributions.

Or build directly:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel 4
./build/deathward
```

Windows is kept in scope through CMake and portable C++, but this milestone is tested on Linux. On Windows, use a C++20-capable Visual Studio toolchain with `cmake --build build --config Release`, then run `build/Release/deathward.exe`.

## Play

Type a seed in the hub (Backspace edits; N generates another), then press Enter or click **Enter the Mine**. Clear three waves per chamber and choose one of three items to open the next doorway. Walk through its corridor, or click the doorway to travel to the next room. Six encounters lead to the Hollow Sheriff and his three attack phases. Use the final room's return lantern to finish. There is no forced minimum duration; the 5–10 minute target still needs human playtesting, and strong combinations can finish sooner.

The mine is one continuous, seed-generated map of seven rooms connected by corridors. Each room has different dimensions (24–40 units per side), with rectangular, clipped-corner, L-shaped and cross-shaped footprints. The seed also chooses the route's turns, objective positions, and obstacle positions, sizes and heights. Layout generation reserves routes to doors and objectives and rejects cover that isolates walkable areas. The same seed and content version reproduce the same map, independently of combat, rewards and campaign outcomes.

The camera follows you through corridors, and the mine map shows the connections and your position. Cleared passages stay open for backtracking; returning to a room does not restart its encounter or grant another reward. Unresolved miners and the altar remain accessible in their original rooms.

| Control | Action |
| --- | --- |
| WASD | Move relative to the camera |
| Left-click ground / hold left button | Move to a point / keep steering around cover |
| Left-click an enemy / hold left button | Shoot / keep firing at that enemy as it moves |
| Left-click an objective | Approach and interact automatically |
| Shift + left button | Fire toward the cursor while standing still |
| Right button | Fire the revolver directly toward the cursor |
| Middle button / Space / Dodge button | Dodge; brief invulnerability, then cooldown |
| E / nearby interaction button | Interact near a cage, altar, or exit lantern |
| 1 / 2 / 3 | Choose a reward while the game is paused |
| Escape / Pause button | Pause / resume; click Keep Going to resume with the mouse |
| T while paused | Retreat and resolve consequences |
| H in the hub | Inspect previous runs |

Start each expedition with **200 HP** and **48 revolver damage** (both doubled from the initial milestone). The revolver fires continuously while holding an enemy, Shift + LMB, or RMB; there is no reload action or reload pause. The six-round display tracks the next shot in a repeating cycle, so every sixth shot still triggers last-round effects. Enemy damage is unchanged; Judas Bullet still costs 20% of maximum health per copy.

Left-click follows the contextual move/attack/interact pattern in [Blizzard's Diablo manual](https://ftp.blizzard.com/pub/misc/Diablo.PDF). Click ground to walk there, or hold to steer. Click an enemy's body to attack; holding keeps that target until release, and its death never turns the attack into a movement order. Attacking cancels the current mouse route. WASD overrides mouse navigation and remains available while firing; Shift holds position. RMB uses the prototype's only weapon, the revolver.

Left-click the miners, altar, an open doorway, or the return lantern to approach and use it. Nearby interactions, dodge and pause also have clickable buttons, so the expedition is playable with a two-button mouse; pressing the wheel is an additional dodge shortcut.

The miners are in chamber 3. The altar is in chamber 4. Both are optional; the town remembers which you completed. Closing the window counts as retreat. A crash resolves retreat from the last checkpoint on the next launch. Rescues persist even when the expedition fails. Clearing a later expedition with the miners safe repairs the mine's lost prosperity. Resolved objectives never award the same permanent bonus twice; the defeated boss becomes a follow-up encounter on subsequent visits.

## Five starting items

| Item | Rule change |
| --- | --- |
| Ricochet Coin | Bullets bounce off walls three times per copy |
| Split Lead | Hits create two angled bullets that can split again |
| Judas Bullet | Every sixth shot pierces six bodies; each copy costs 20% maximum health |
| Powder of Jericho | Kills explode; explosion kills can explode again |
| Hangman's Coin | Ghosts repeat killing shots with the current projectile effects |

Copies stack. Items do not check for specific item pairs. Stable registry hooks modify projectile creation and react to queued hit, kill, explosion and other events. Generated work preserves chain provenance; depth, event and entity budgets bound pathological branching without banning secondary effects.

## Debug tools

Press **F1** to expose and enable the debug controls. They intentionally affect the current campaign; use `--save /tmp/deathward-playground.save` for an isolated playground.

| Control | Action |
| --- | --- |
| F2 / F3 | Toggle god mode / kill all |
| F4 / F5 | Spawn 20 / 100 enemies |
| F6 | Grant all five items |
| F7 | Jump to boss or follow-up encounter |
| F8 / F9 | Finish successfully / die |
| F10 | Toggle 3D collision volumes and projectile paths |
| F11 | Stress scene: 100 enemies and 600 shots with all five effects |
| [ / ] then I | Select and grant an item |
| V | Grant five random items |
| P / O | Freeze / slow simulation |
| M | Mark miners rescued |
| G in the hub | Set/clear the haunting flag and observe NPC dialogue |

The hub debug panel also offers campaign reset with a confirmation click and a `.bak` copy. The combat panel exposes entity, projectile, queue and chain counts, maximum depth, suppression diagnostics and effect counters.

## Save files and determinism

Linux saves to `$XDG_DATA_HOME/deathward/campaign.save`, or `~/.local/share/deathward/campaign.save`. Windows uses `%LOCALAPPDATA%/DeathWard/campaign.save`. Override with `--save PATH` or `DEATHWARD_SAVE_PATH`.

One checksummed, versioned snapshot contains world state, pending-run metadata and history. Writes use a temporary file and atomic replacement. Corrupt or unsupported saves produce an error and are preserved. Objective interactions, room completion and item acquisition checkpoint summary data; temporary combat state is never resumable. Only one process should use a given save file at a time.

Layout, encounter, reward and combat RNG streams are independent. The same seed and content version reproduce the complete map; initial campaign state and relevant choices also determine encounter setup and offers. Full combat input replay is not implemented. History records the version, seed and starting world context, along with the lost build, counters and consequences.

## Verify

```sh
ctest --test-dir build --output-on-failure
./build/deathward_input_tests
./build/deathward --smoke --frames 180 --screenshot artifacts/combat.png
./build/deathward --smoke --scene hub --frames 2 --screenshot artifacts/hub.png
./build/deathward --benchmark --frames 600 --screenshot artifacts/stress.png
```

The core CTest suite needs no graphics display. `deathward_input_tests` exercises mouse controls through raylib's input system in a hidden window and requires an X11/OpenGL display, as do the render checks; `xvfb-run` is also suitable where available. Input checks use a temporary campaign. Scripted render checks use a fresh temporary campaign by default. An explicit `--save PATH` opts into that campaign.

Tests cover swept 3D collisions, all five item effects and representative compositions, single-kill transitions, chain ceilings and reclamation, RNG independence, atomic campaign outcomes/recovery, repeat visits, and the complete chamber progression. Generated-map checks cover 64 seeds, identical-seed reproduction, different room dimensions/footprints, floor connectivity, gates, objectives, boss clearance, enemy spawns, continuous traversal and backtracking. The benchmark renders repeated stress bursts and reports frame times, population counts, peak projectiles, kills, chain depth and suppressions. See the [verification results](docs/verification.md) for the recorded baseline and its limits. Smoke scenes also include `reward`, `boss` and `summary`.

For sanitizer checks:

```sh
cmake -S . -B build-asan -DCMAKE_BUILD_TYPE=Debug -DDEATHWARD_SANITIZERS=ON
cmake --build build-asan --parallel 4
ctest --test-dir build-asan --output-on-failure
```

## Code map

- `src/combat`: fixed-step simulation, 3D collision, AI, spatial broad phase and event budgets.
- `src/items`: the item registry and independent effect handlers.
- `src/world`: seeded dungeon geometry, persistent world state, consequences, history and atomic save transactions.
- `src/core`: application flow, input, math and deterministic RNG.
- `src/render`: replaceable primitive 3D rendering and menus; no combat rules.
- `tests`: gameplay and persistence contract checks.

The [design brief](weird_west_3d_prototype_agent_brief.md) describes the wider experiment. This implementation targets Milestone 1; the 25-item catalog, five ordinary enemy types and three expeditions belong to Milestone 2.
