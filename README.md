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

You start as the bandit in **Black Creek**, a walkable import of the original PolygonWestern demo town, with its authored buildings, train, streets and original textures. Explore with WASD or click the ground; the mouse wheel zooms. Click **Missions** to walk to the railway station's mission board, or approach and click the board yourself. Select **Seeded Theme**, **Western Mine** or **Canyon**, then choose **Leave** to start a generated expedition. Seeded Theme chooses the setting deterministically from the mission seed. **New Mission** chooses another random seed; type digits or use Backspace to edit a seed when replaying a layout. Mission results return you to town with a fresh offer. Exploring the hub does not begin a campaign run.

A second hub imports the original **PolygonWesternFrontier Demo** with its village, fort, quarry, river, vegetation and original textures. Use **Travel to Frontier** at the bottom right while exploring, or **Travel to Black Creek** to return. Travel is also available in Pause. Start there directly with `./build/deathward --hub frontier`. Missions return to the hub you departed from. Hub choice lasts for the session; both hubs share the campaign. See [the Frontier import notes](assets/frontier/README.md) for the scene audit and rendering boundaries.

Both hubs use their imported sunlight and lamps, with warm ground bounce, cooler sky fill and sun-cast shadows from scenery and the animated bandit. Shadows follow the camera as you walk, orbit and zoom. The town editor previews the same lighting while objects move. Original textures and placements remain intact.

The world uses an autumn color treatment inspired by the supplied visual reference: amber highlights, plum shadows, richer colors, soft bloom and a subtle vignette. A gentle blur softens fine detail, and light lavender fog builds with scene depth while keeping the camera's focal area clear. Frontier's leafy trees vary between copper and gold; bark, grass and evergreen foliage keep their source palette. The same post processing covers both hubs, missions and the editor. Menus, text and enemy health bars are drawn afterward to stay sharp and retain their original colors.

Press **F4 in town** or choose **Town Editor** in the pause screen to edit the city in 3D. Select objects, drag move/rotate/scale handles, enter exact transforms, or add models from the asset palette. The editor includes search, duplication, deletion, undo/redo and arrival/mission markers. **Ctrl+S** saves the layout and rebuilds navigation, retaining backups. Launch it directly with `./build/deathward --editor`. See the [town editor guide](docs/town_editor.md) for controls, save locations and navigation details.

Each mission has **15 rooms**, with junctions and loops that let you choose between routes. Combat rooms seal every doorway, including the entrance behind you. Each combat room starts with one enemy group; defeat it to reopen the doors. There are no later reinforcements; the boss has one encounter with three attack phases. Cleared rooms stay cleared when revisited, without extra rewards or healing.

**The starting room is always enemy-free**, with open passages from the moment you enter. It counts toward the limit of 1–2 ordinary rooms with no enemies; the seed may choose one additional quiet room, separate from the peaceful power rooms. These quiet rooms have open passages, no enemies or power pedestal, and may contain a key. The miners, altar and boss retain their encounters.

**The room network grows from the seed**: two or three starting routes, variable branch lengths and junctions, dead ends, and zero to three loops. Boss and power rooms attach at branch ends instead of fixed corners. Room spacing also varies, producing different corridor lengths. Click **New Mission** or press **N in the station menu** to choose a new seed; keeping the same seed deliberately reproduces the same layout.

Mine rooms have different dimensions (24–40 units per side), with rectangular, clipped-corner, L-shaped and cross-shaped footprints. Canyon basins use these variable envelopes for rounded, irregular footprints and curved connecting trails. The seed chooses the graph, room shapes, objective positions, obstacles, key locations and power-room count. Clear routes are reserved for doors and objectives, and cover that isolates walkable floor is rejected. The same seed and content version reproduce the same map independently of campaign outcomes.

**Fifteen ordinary enemy types are playable**, with distinct silhouettes and attacks: rushers, gunmen, shotgunners, sharpshooters, dynamite throwers, armored brutes, chargers, protective preachers, bell shockwaves, hook throwers, fire spitters, ricochet shooters, teleporting wraiths, explosive husks and chainbound pairs. See the [enemy roster](docs/enemy_roster_proposal.md) for their tells and counters.

**The Isaac monster roster for IDs 10–89 is also playable**, including variants, with new 3D creature silhouettes and seeded room groups. Special behaviors include regenerating piles, protective shells, directional armor, lasers, splitting shots, burrowing, linked enemies and offspring. Permanent hazards cannot prevent room completion. Use **comma / period**, then **Shift+F4**, to test a specific ID. See the [catalog and adaptation notes](docs/isaac_monsters.md).

**Enemy count scales with the room's generated floor area:** subtract obstacle footprints, divide by 70, round up, then clamp to 4–24. Missing corners and corridors do not count. For example, 700 usable square units gives 10 enemies; 1,400 gives 20. Each group mixes up to three seeded types, with clear spawn space and a six-unit buffer around the player. Quiet rooms and power caches stay empty; the first boss encounter stays a single Sheriff. Revisits after defeating the Sheriff use an area-scaled ordinary group.

**Power-ups only appear in 1–2 dedicated rooms per expedition.** Unlock a power room, approach its pedestal, and choose one of two items. Each pedestal works once, so normal play yields at most two power-ups for the entire run. Combat rooms do not award items.

**Golden doors require one key.** Keys appear at seeded locations in combat rooms after those rooms are cleared, or immediately upon entering a quiet room; left-click a key or walk over it to collect it. Keys are consumed when unlocking a power room or the boss room. Unlocks persist for the run. All keys are placed in the connected area accessible without spending a key, and there are enough for every lock, so choosing a power room first cannot make the boss unreachable.

The camera follows you through corridors. The mission map shows branches, your position, keys carried, and powers claimed: **P** marks a power room, **E** an enemy-free room, **B** the boss, and **K** a discovered, uncollected key. Red gates are sealed for combat, golden gates need a key, and green gates are open. Use the boss room's return lantern to finish. Expedition length with the larger map and rarer powers still needs human playtesting.

| Control | Action |
| --- | --- |
| WASD | Move relative to the camera |
| Left-click ground / hold left button | Move to a point / keep steering around cover |
| Left-click an enemy / hold left button | Shoot / keep firing at that enemy as it moves |
| Left-click an objective | Approach and interact automatically |
| Shift + left button | Fire toward the cursor while standing still |
| Right button | Fire the revolver directly toward the cursor |
| Hold middle button + drag | Rotate around the character; drag vertically to tilt |
| Space / Dodge button | Dodge; brief invulnerability, then cooldown |
| Mouse wheel | Zoom in / out; scroll up to move closer, down to pull back |
| E / nearby interaction button | Interact near a cage, altar, or exit lantern |
| 1 / 2 | Choose one item at a power-room pedestal |
| Escape / Pause button | Pause / resume; click Keep Going to resume with the mouse |
| T while paused | Retreat and resolve consequences |
| H in the hub | Inspect previous runs |

Start each expedition with **100 HP** and **24 revolver damage**. The revolver fires continuously while holding an enemy, Shift + LMB, or RMB; there is no reload action or reload pause. The six-round display tracks the next shot in a repeating cycle, so every sixth shot still triggers last-round effects. Judas Bullet still costs 20% of maximum health per copy.

With cheats enabled, pause a mission to use **Player Settings**: adjust base health in steps of 25 and shot damage in steps of 4. During play, **minus / equals** (or keypad minus / plus) adjust damage; hold **Shift** with those keys to adjust health. **Home** restores the 100 HP / 24 damage defaults. Base health is bounded to 25–2,000 and damage to 1–500. Health changes preserve your current health percentage and still apply Judas Bullet's health cost; Shift+F2 fully heals. Settings apply immediately to new shots and carry into subsequent missions and hub travel for this session. Restarting the game restores the defaults. Split and ghost bullets use the adjusted shot damage; Powder of Jericho keeps its own explosion damage.

Left-click follows the contextual move/attack/interact pattern in [Blizzard's Diablo manual](https://ftp.blizzard.com/pub/misc/Diablo.PDF). Click ground to walk there, or hold to steer. Click an enemy's body to attack; holding keeps that target until release, and its death never turns the attack into a movement order. Attacking cancels the current mouse route. WASD overrides mouse navigation and remains available while firing; Shift holds position. RMB uses the prototype's only weapon, the revolver.

Left-click the miners, altar, a key, a power pedestal, a doorway, or the return lantern to approach and use it. Nearby interactions, dodge and pause also have clickable buttons, so the expedition is playable with a two-button mouse.

Hold the middle mouse button and drag to orbit the camera in town or a mission. Horizontal dragging rotates around the character; vertical dragging tilts between 25 and 75 degrees above the ground. Release to keep that angle. WASD follows the current camera direction, and ground clicks use the rotated view. Start the drag over the world; HUD controls and open menus do not start camera gestures.

Mouse-wheel zoom moves smoothly between a close character view and a wider room view while preserving the camera angle. Your chosen angle and zoom persist between rooms, town and expeditions during the session. Scrolling over the HUD controls, map or open cheat panel, or while paused or choosing a power, does not change zoom.

A small FPS counter in the top-right corner shows the rendering frame rate on every screen. In hubs and missions, the current camera zoom appears beside it. New sessions start at **160% zoom**; 100% remains the reference scale, higher percentages are closer, and lower percentages are wider. The value follows the camera smoothly as you scroll. Your chosen zoom carries between hubs and missions for the session.

World interactions use visual cues instead of floating control instructions: open exits have small floor arrows and colored lanterns, locked doors have golden locks, and pickups and objectives have glow or ground markers. Control reminders live in the hub, pause screen and this guide.

The player uses the textured **bandit model supplied in `assets/bandit`**. Its FBX clips drive breathing idle, walking, running, firing, sliding or jumping dodges and two death animations. Moving attacks blend the firing pose over the legs' movement; turning follows movement or aim. Animation pauses and slows with gameplay. Natural death plays a two-second animation before the results screen; the F9 testing shortcut still resolves immediately.

The generated rooms use **textured PolygonWestern scenery**: stacked crates for cover, boundary fences, railway passages and lanterns. Seeded saloons, jails, churches, stations, water towers, carts, barrels, rocks and cacti surround the playable routes. The original texture atlas and material tints are embedded in the models, with directional lighting adapted for raylib. Cover fits the existing collision boxes; buildings are exterior scenery. Keeping the same seed and theme reproduces the scenery as well as the map.

**Redstone Canyon** uses irregular basins and winding trails cut into a continuous rock terrain. Outcrops replace cube cover; the visible triangles also define movement, bullet and sight collisions. The original atlas supplies brown cliff faces and pale faceted caps, with directional terrain shadows and sparse rocks/cacti. Cliffs and cover keep their full generated height. The mine keeps its existing generator. A seed and theme reproduce their own geometry and encounters; canyon enemy counts use the basin's navigable floor area. Both settings share the miners and altar objectives. Canyon completion is tracked separately from defeating the mine’s Sheriff. See [mission theming](docs/mission_themes.md) for extension points.

**Isaac Canyon is the default mission choice** and uses only the Isaac monster catalog, including its final encounter. **Western Mine** retains all fifteen original enemy types and the Hollow Sheriff. Random spawn cheats follow the selected theme; the specific-ID cheat remains available in either setting. See [the enemy review and Isaac character comparison](docs/isaac_review.md).

The miners are in chamber 3. The altar is in chamber 4. Both are optional; the town remembers which you completed. Closing the window counts as retreat, or death if the character is already dying. A crash resolves retreat from the last checkpoint on the next launch. Rescues persist even when the expedition fails. Clearing a later expedition with the miners safe repairs the mine's lost prosperity. Resolved objectives never award the same permanent bonus twice; the defeated boss becomes a follow-up encounter on subsequent visits.

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
| Minus / equals, or keypad minus / plus | Decrease / increase shot damage by 4 |
| Shift + minus / equals, or Shift + keypad minus / plus | Decrease / increase base health by 25 |
| Home | Restore default base health and shot damage |
| F2 / Shift + F2 | Toggle invincibility / heal fully and reset cooldowns |
| F3 / Shift + F3 | Kill current enemies / clear the whole room, remove pending effects and reopen combat seals |
| F4 / F5 | Spawn 20 / 100 enemy roots from the current mission's roster, plus attached companions |
| Comma / period | Select the previous / next monster ID |
| Shift + F4 | Spawn the selected monster on safe floor for testing |
| F6 / Shift + F6 | Grant all five items / add three keys |
| F7 | Start or replay the final encounter: Isaac group in Canyon, Sheriff/follow-up in Mine |
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
./build/deathward_player_model_tests
./build/deathward_western_assets_tests
./build/deathward_town_assets_tests
./build/deathward --smoke --theme mine --frames 180 --screenshot artifacts/combat.png
./build/deathward --smoke --theme canyon --scene combat --frames 90 --screenshot artifacts/canyon-combat.png
./build/deathward --smoke --scene hub --frames 2 --screenshot artifacts/hub.png
./build/deathward --benchmark --frames 600 --screenshot artifacts/stress.png
```

The six core CTest suites need no graphics display. Mission-theme checks cover seeded selection, organic terrain reproduction, clear routes, sealed entrances, safe enemy placement, surface collision and persisted canyon checkpoints/history. `deathward_input_tests` exercises mouse controls and function-key cheats through raylib's input system in a hidden window. `deathward_player_model_tests` checks the packaged mesh, texture, all nine clips, blending, simulation timing, root-motion removal and resource cleanup. `deathward_western_assets_tests` checks the scenery atlas, glass, scale, collision alignment, route clearance, seed reproduction, canyon terrain/mesh alignment and resource cleanup. These require an X11/OpenGL display, as do the render checks; `xvfb-run` is also suitable where available. Input checks use a temporary campaign. Scripted render checks use a fresh temporary campaign by default. An explicit `--save PATH` opts into that campaign.

Enemy tests cover all fifteen behaviors, attack warnings, armor and support, cover and dodge counters, delayed hazards and chain cleanup, plus area-scaled populations and safe placements across 32 seeds. Tests also cover swept 3D collisions, all five item effects and representative compositions, single-kill transitions, chain ceilings and reclamation, RNG independence, atomic campaign outcomes/recovery, repeat visits, and the complete chamber progression. Fast room-network checks cover 10,004 seeds, including rotation/reflection-independent footprint comparisons and graph diversity checks across 256 seeds. Generated-map checks cover 64 seeds, identical-seed reproduction, different room dimensions/footprints, floor connectivity, branching and loops, combat seals, key reachability, locked doors, limited power and enemy-free rooms, objectives, boss clearance, enemy spawns, continuous traversal and backtracking. Cheat checks cover disabled hotkeys, unobstructed play with cheats enabled, single-group encounters, effect cleanup, room/boss replay, preserved rewards and paused/modal outcomes. The benchmark renders repeated stress bursts and reports frame times, population counts, peak projectiles, kills, chain depth and suppressions. See the [verification results](docs/verification.md) for the recorded baseline and its limits. Smoke scenes also include `key`, `power`, `reward`, `empty`, `cheats`, `boss` and `summary`.

For sanitizer checks:

```sh
cmake -S . -B build-asan -DCMAKE_BUILD_TYPE=Debug -DDEATHWARD_SANITIZERS=ON
cmake --build build-asan --parallel 4
ctest --test-dir build-asan --output-on-failure
```

## Game assets

Normal builds use the supplied FBXs' converted `assets/bandit/bandit.glb`, which includes the original texture and animations. CMake copies it into `assets/bandit` beside the executable, so launching from a different working directory works. Keep that asset directory with the executable when moving a build. The source-tree asset is a development fallback; a missing model falls back to the primitive character.

Only rebuilding the asset requires Blender 3.6 LTS. Conversion instructions and clip mappings are in [the bandit asset notes](assets/bandit/README.md).

Western scenery uses `assets/western/western.glb` and its matching catalog, also copied beside the executable. The original atlas is embedded; no reference to the external Unity project is needed at runtime. Source prefabs, FBXs, materials and texture are retained for rebuilding. See [the Western asset notes](assets/western/README.md) for conversion commands, placement and collision rules, and lighting differences from Unity.

The hub separately imports the complete original Demo scene into `assets/town`: 1,516 active mesh placements with 12 embedded textures, original material variants, hierarchy and transforms. Its scene catalog and terrain navigation are packaged beside the GLB. See [the town import notes](assets/town/README.md) for the source audit, rebuilding commands and differences from Unity's rendering. CTest includes outdoor town navigation; `deathward_town_assets_tests` checks the original scene's graphics assets and requires a display.

## Code map

- `src/combat`: fixed-step simulation, 3D collision, AI, spatial broad phase and event budgets.
- `src/items`: the item registry and independent effect handlers.
- `src/world`: seeded dungeon geometry, persistent world state, consequences, history and atomic save transactions.
- `src/core`: application flow, input, math and deterministic RNG.
- `src/render`: 3D rendering, instanced seeded scenery, player animation blending and menus; no combat rules.
- `tests`: gameplay and persistence contract checks.

The [design brief](weird_west_3d_prototype_agent_brief.md) describes the wider experiment. This implementation extends Milestone 1 with the Western and monster rosters and seeded room networks. The 25-item catalog and three expeditions remain future content work.
