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

Type a seed in the hub (Backspace edits; N generates another), then press Enter or click **Enter the Mine**. The mine now has **15 rooms**, with junctions and loops that let you choose between routes. Combat rooms seal every doorway, including the entrance behind you. Each combat room starts with one enemy group; defeat it to reopen the doors. There are no later reinforcements; the boss has one encounter with three attack phases. Cleared rooms stay cleared when revisited, without extra rewards or healing.

**The starting room is always enemy-free**, with open passages from the moment you enter. It counts toward the limit of 1–2 ordinary rooms with no enemies; the seed may choose one additional quiet room, separate from the peaceful power rooms. These quiet rooms have open passages, no enemies or power pedestal, and may contain a key. The miners, altar and boss retain their encounters.

**The room network grows from the seed**: two or three starting routes, variable branch lengths and junctions, dead ends, and zero to three loops. Boss and power rooms attach at branch ends instead of fixed corners. Room spacing also varies, producing different corridor lengths. Press **N in the hub** to choose a new seed; keeping the same seed deliberately reproduces the same layout.

Each room has different dimensions (24–40 units per side), with rectangular, clipped-corner, L-shaped and cross-shaped footprints. The seed chooses the graph, room shapes, objective positions, obstacles, key locations and power-room count. Clear routes are reserved for doors and objectives, and cover that isolates walkable floor is rejected. The same seed and content version reproduce the same map independently of campaign outcomes.

**Fifteen ordinary enemy types are playable**, with distinct silhouettes and attacks: rushers, gunmen, shotgunners, sharpshooters, dynamite throwers, armored brutes, chargers, protective preachers, bell shockwaves, hook throwers, fire spitters, ricochet shooters, teleporting wraiths, explosive husks and chainbound pairs. See the [enemy roster](docs/enemy_roster_proposal.md) for their tells and counters.

**Enemy count scales with the room's generated floor area:** subtract obstacle footprints, divide by 70, round up, then clamp to 4–24. Missing corners and corridors do not count. For example, 700 usable square units gives 10 enemies; 1,400 gives 20. Each group mixes up to three seeded types, with clear spawn space and a six-unit buffer around the player. Quiet rooms and power caches stay empty; the first boss encounter stays a single Sheriff. Revisits after defeating the Sheriff use an area-scaled ordinary group.

**Power-ups only appear in 1–2 dedicated rooms per expedition.** Unlock a power room, approach its pedestal, and choose one of two items. Each pedestal works once, so normal play yields at most two power-ups for the entire run. Combat rooms do not award items.

**Golden doors require one key.** Keys appear at seeded locations in combat rooms after those rooms are cleared, or immediately upon entering a quiet room; left-click a key or walk over it to collect it. Keys are consumed when unlocking a power room or the boss room. Unlocks persist for the run. All keys are placed in the connected area accessible without spending a key, and there are enough for every lock, so choosing a power room first cannot make the boss unreachable.

The camera follows you through corridors. The mine map shows branches, your position, keys carried, and powers claimed: **P** marks a power room, **E** an enemy-free room, **B** the boss, and **K** a discovered, uncollected key. Red gates are sealed for combat, golden gates need a key, and green gates are open. Use the boss room's return lantern to finish. Expedition length with the larger map and rarer powers still needs human playtesting.

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
| 1 / 2 | Choose one item at a power-room pedestal |
| Escape / Pause button | Pause / resume; click Keep Going to resume with the mouse |
| T while paused | Retreat and resolve consequences |
| H in the hub | Inspect previous runs |

Start each expedition with **200 HP** and **48 revolver damage** (both doubled from the initial milestone). The revolver fires continuously while holding an enemy, Shift + LMB, or RMB; there is no reload action or reload pause. The six-round display tracks the next shot in a repeating cycle, so every sixth shot still triggers last-round effects. Judas Bullet still costs 20% of maximum health per copy.

Left-click follows the contextual move/attack/interact pattern in [Blizzard's Diablo manual](https://ftp.blizzard.com/pub/misc/Diablo.PDF). Click ground to walk there, or hold to steer. Click an enemy's body to attack; holding keeps that target until release, and its death never turns the attack into a movement order. Attacking cancels the current mouse route. WASD overrides mouse navigation and remains available while firing; Shift holds position. RMB uses the prototype's only weapon, the revolver.

Left-click the miners, altar, a key, a power pedestal, a doorway, or the return lantern to approach and use it. Nearby interactions, dodge and pause also have clickable buttons, so the expedition is playable with a two-button mouse; pressing the wheel is an additional dodge shortcut.

World interactions use visual cues instead of floating control instructions: open exits have small floor arrows and colored lanterns, locked doors have golden locks, and pickups and objectives have glow or ground markers. Control reminders live in the hub, pause screen and this guide.

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

## Cheat mode / quick testing

**Cheat mode is enabled by default**, with hotkeys ready immediately and the shortcut panel hidden so it does not cover the game or block mouse controls. The backtick key opens or hides the optional shortcut panel independently. Press **F1** to disable cheat hotkeys, invincibility, slow time and collision overlays; press it again to re-enable the mode. Invincibility itself is still toggled with F2. Granted items/keys and completed actions remain. Cheats affect the current campaign; use `--save /tmp/deathward-playground.save` for an isolated playground.

| Control | Action |
| --- | --- |
| F1 | Toggle cheat mode; enabling it keeps the panel hidden |
| Backtick key | Show/hide the optional cheat shortcut panel |
| F2 / Shift + F2 | Toggle invincibility / heal fully and reset cooldowns |
| F3 / Shift + F3 | Kill current enemies / clear the whole room, remove pending effects and reopen combat seals |
| F4 / F5 | Spawn 20 / 100 enemies drawn from all fifteen types |
| F6 / Shift + F6 | Grant all five items / add three keys |
| F7 | Start or replay the boss or follow-up encounter |
| F8 / F9 | Finish successfully / die |
| F10 | Toggle 3D collision volumes and projectile paths |
| F11 | Stress scene: 100 enemies and 600 shots with all five effects |
| F12 / Shift + F12 | Jump to the next numbered room (wraps after the boss) / restart the current room |
| [ / ] then I | Select and grant an item |
| V | Grant five random items |
| P / O | Freeze / slow simulation |
| M | Mark miners rescued |
| G in the hub | Set/clear the haunting flag and observe NPC dialogue |

Room jumps and restarts heal you, resume play and move the camera immediately. They preserve the seed, build, keys, unlocked doors and claimed power rewards. Restarting a claimed power room does not grant another normal reward. Shift + F3 or a room restart also ends a stress scene. Cheat keys work while paused or choosing a power; victory/death resolve immediately.

The hub cheat panel also offers campaign reset with a confirmation click and a `.bak` copy. The optional combat panel exposes entity, projectile, queue and chain counts, maximum depth, suppression diagnostics and effect counters.

## Save files and determinism

Linux saves to `$XDG_DATA_HOME/deathward/campaign.save`, or `~/.local/share/deathward/campaign.save`. Windows uses `%LOCALAPPDATA%/DeathWard/campaign.save`. Override with `--save PATH` or `DEATHWARD_SAVE_PATH`.

One checksummed, versioned snapshot contains world state, pending-run metadata and history. Writes use a temporary file and atomic replacement. Corrupt or unsupported saves produce an error and are preserved. Objective interactions, room completion and item acquisition checkpoint summary data; temporary combat state is never resumable. Only one process should use a given save file at a time.

Room-network growth, room geometry, per-room enemy composition/placement, reward and combat RNG streams are independent. Room populations and types do not depend on visitation order. Spawn positions reproduce when entering from the same position; a different entrance can adjust placements to keep the player safe. The same seed and content version reproduce the complete map; power-room offers are fixed per room, while initial campaign state and relevant choices also determine encounter setup. Full combat input replay is not implemented. History records the version, seed and starting world context, along with the lost build, counters and consequences.

## Verify

```sh
ctest --test-dir build --output-on-failure
./build/deathward_input_tests
./build/deathward --smoke --frames 180 --screenshot artifacts/combat.png
./build/deathward --smoke --scene hub --frames 2 --screenshot artifacts/hub.png
./build/deathward --benchmark --frames 600 --screenshot artifacts/stress.png
```

The core CTest suite needs no graphics display. `deathward_input_tests` exercises mouse controls and function-key cheats through raylib's input system in a hidden window and requires an X11/OpenGL display, as do the render checks; `xvfb-run` is also suitable where available. Input checks use a temporary campaign. Scripted render checks use a fresh temporary campaign by default. An explicit `--save PATH` opts into that campaign.

Enemy tests cover all fifteen behaviors, attack warnings, armor and support, cover and dodge counters, delayed hazards and chain cleanup, plus area-scaled populations and safe placements across 32 seeds. Tests also cover swept 3D collisions, all five item effects and representative compositions, single-kill transitions, chain ceilings and reclamation, RNG independence, atomic campaign outcomes/recovery, repeat visits, and the complete chamber progression. Fast room-network checks cover 10,004 seeds, including rotation/reflection-independent footprint comparisons and graph diversity checks across 256 seeds. Generated-map checks cover 64 seeds, identical-seed reproduction, different room dimensions/footprints, floor connectivity, branching and loops, combat seals, key reachability, locked doors, limited power and enemy-free rooms, objectives, boss clearance, enemy spawns, continuous traversal and backtracking. Cheat checks cover disabled hotkeys, unobstructed play with cheats enabled, single-group encounters, effect cleanup, room/boss replay, preserved rewards and paused/modal outcomes. The benchmark renders repeated stress bursts and reports frame times, population counts, peak projectiles, kills, chain depth and suppressions. See the [verification results](docs/verification.md) for the recorded baseline and its limits. Smoke scenes also include `key`, `power`, `reward`, `empty`, `cheats`, `boss` and `summary`.

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

The [design brief](weird_west_3d_prototype_agent_brief.md) describes the wider experiment. This implementation extends Milestone 1 with fifteen ordinary enemy types and seeded room networks. The 25-item catalog and three expeditions remain future content work.
