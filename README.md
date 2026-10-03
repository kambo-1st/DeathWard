# DeathWard

A playable C++20 / raylib 3D Weird West prototype. Borrow a broken build from Red Hollow Mine, bring its people home, and leave lasting consequences in Black Creek.

**The build is gone. The consequences remain.**

## Run on Linux

```sh
./scripts/run.sh
```

The script configures a Release build, downloads pinned raylib 5.5 on the first build, compiles, and launches. No game assets or other third-party packages are downloaded. CMake 3.20+, a C++20 compiler, OpenGL and X11 development libraries are required. On Ubuntu/Debian:

```sh
sudo apt install build-essential cmake libasound2-dev libpulse0 libx11-dev libxrandr-dev libxi-dev libxcursor-dev libxinerama-dev libgl1-mesa-dev
```

See the [raylib Linux build guide](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux) for other distributions.

Or build directly:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel 4
./build/deathward
```

Windows is kept in scope through CMake and portable C++, but this milestone is tested on Linux. On Windows, use a C++20-capable Visual Studio toolchain with `cmake --build build --config Release`, then run `build/Release/deathward.exe`.

## Full experience

```sh
./build/deathward --full-experience
```

Shows the **Bubak Games** ghost logo, the **DeathWard** title, then three save-slot cards with **Settings** and **Exit**. Click a card and **Begin Journey** or **Continue Journey**. Keyboard navigation uses Tab or arrow keys and Enter; click or press Enter to skip each logo. Settings expose master/music/effects/ambience volume, mute, vegetation density, ground detail and canyon rivers. **Apply & Back** saves; **Cancel** or Escape discards the previewed changes.

A new slot starts the Westbound train opening, then arrives at Redstone in the storm and begins the conductor/tent/commander quest. Click **Skip intro** or press **Escape** to go directly to that same playable arrival; **Pause / Resume** and Space control playback. Finishing or skipping the opening never opens the cinematic editor. Continuing returns to the last story checkpoint; an unfinished opening restarts aboard the train. Expeditions retain the existing checkpoint/result system: an interrupted expedition is resolved as interrupted on loading, rather than restoring mid-combat. The menu describes that state before continuing.

Slots are independent `slots/slot-1.save` through `slot-3.save` beside the normal campaign. The existing `campaign.save` stays separate. Browsing slots performs no campaign writes, and unreadable slots are shown as unavailable without overwriting them. For an isolated playthrough, use `--full-experience --slots /path/to/folder`; this also places that playthrough's shared settings in the specified folder. The flag is separate from direct editor, cinematic, smoke-test and `--save` launches. Without it, the existing Black Creek startup remains available.

In a browser use **`?full-experience`**, then click **Start DeathWard** to enable sound and enter the logo sequence. All three slots persist in that browser. The new front end uses a vector ghost emblem, a serif wordmark and an animated desert/railway backdrop; the bundled fonts and license are in [assets/ui](assets/ui).

## Run in a browser

With Emscripten activated (tested with 4.0.15):

```sh
./scripts/build-web.sh
python3 scripts/serve-web.py
```

Open **http://127.0.0.1:8080/**, wait for loading and click **Enter Black Creek**. The WebAssembly version includes all three hubs, missions, original textures, lighting, post processing, music and effects. It requires WebGL 2, a keyboard and a mouse. Campaigns, audio preferences and town-editor saves stay in that browser, separately from desktop saves. See the [browser guide](docs/browser.md) for setup, hosting, controls and verification.

To prepare a static-server upload, run `python3 scripts/package-web.py` after building. Extract `dist/deathward-web.zip` into the destination's public directory. The same package works at a domain root or a subdirectory, including `deathward.kambo.us/` and `kambo.us/deathward/`, without editing paths.

## Audio

Sound is enabled for ordinary play. The first audio pack includes revolver/enemy shots, stone and flesh impacts, hurt/death feedback, dodges, attack warnings, pickups, doors, room completion, UI sounds and footsteps. Both hubs, the canyon and the mine have distinct ambient loops that crossfade on travel. Effects pan with the camera and become quieter with distance; cover does not silence enemy attack warnings.

Open **Pause** in a hub or mission for **Master**, **Effects**, **Ambience** and **Music** volume, **Mute**, and a **Test** chime. Settings are saved in `audio.cfg` beside the campaign file; existing preferences retain their levels when the music channel is added. Pause reduces music/ambience and stops combat sounds. Dead or dodging players do not make walking sounds.

On **WSL2 with WSLg**, raylib connects to WSLg's PulseAudio server through the existing `PULSE_SERVER` environment, normally `unix:/mnt/wslg/PulseServer`. Keep that environment when launching from a terminal or IDE. No additional Windows sound server is needed for this setup. If the output device cannot be opened, the game continues silently and the pause panel shows **Audio unavailable**. Older WSL2 installations without WSLg need an audio server before playback is available. Native Windows uses raylib/miniaudio's Windows audio backend.

Use `./build/deathward --mute` to skip audio initialization entirely. Smoke tests and benchmarks are silent by default; add `--audio` to test their sound. `--mute` takes precedence. Scripted checks do not change saved volume preferences.

The checked-in [audio pack](assets/audio/README.md) contains original synthesized effects and soundscapes. Footstep variants follow the location rather than per-mesh surface materials. The imported [Western Music score](assets/audio/music/README.md) adds eight full tracks: separate hub and exploration themes, combat/finale arrangements, victory and defeat. Music crossfades without restarting at every room; the three Hunt arrangements keep their shared playback position. Four stingers mark mission departure, boss entry, victory and defeat, briefly lowering the score underneath. The **Music** slider controls both the score and stingers, initially at 40%. The music files ship with the game and require no access to the original Unity project at runtime.

## Play

You start as the bandit in **Black Creek**, a walkable import of the original PolygonWestern demo town, with its authored buildings, train, streets and original textures. Explore with WASD or click the ground; the mouse wheel zooms. Click **Missions** to walk to the railway station's mission board, or approach and click the board yourself. Select **Seeded Theme**, **Western Mine** or **Canyon**, then choose **Leave** to start a generated expedition. Seeded Theme chooses the setting deterministically from the mission seed. **New Mission** chooses another random seed; type digits or use Backspace to edit a seed when replaying a layout. Mission results return you to town with a fresh offer. Exploring the hub does not begin a campaign run.

Each canyon seed chooses a boundary river replacing exterior cliffs or an interior river crossing rooms with shallow fords. A mission uses one type. Try seed **1866** for a boundary river and **42** for an interior river. Use **River On / River Off** on the mission board to compare with the original terrain; the choice is saved and applies to the next mission. The same seed and river setting reproduce the layout. See [the river trial](docs/mission_themes.md#canyon-river-trial).

Generated canyons also include a seeded dirt road through three connected rooms, with soft edges, color variation and wheel ruts. Roads follow existing passages and stay clear of rivers, rocks and vegetation. Seed **1866** shows one in the first room.

Press **K** to toggle a sandstorm in any hub, generated mission, or editor preview. It adds wind-driven ground dust, moving haze and fine airborne grit, fading in and out while keeping the HUD clear. A **Sandstorm On / Off** button is also available in Pause. This visual trial starts off and lasts for the session; it does not change terrain, rivers, roads, aiming or enemy behavior. Start enabled with `--sandstorm` (browser: `?sandstorm=on`).

A second hub imports the original **PolygonWesternFrontier Demo** with its village, fort, quarry, river, vegetation and original textures. Use **Travel to Frontier** at the bottom right while exploring, or **Travel to Black Creek** to return. Travel is also available in Pause. Start there directly with `./build/deathward --hub frontier`. Missions return to the hub you departed from. Hub choice lasts for the session; all three hubs share the campaign. See [the Frontier import notes](assets/frontier/README.md) for the scene audit and rendering boundaries.

A third authored hub, **Fort Mercy** (the Redstone Canyon map), combines Black Creek's full-sized canyon and rail route with Frontier's fort and an expanded settler camp. The train is stranded beside a buried line. Fifteen provisional residents populate the arrival, market, witness shelters and guarded fort; a covered wagon waits at the camp edge. Use **Travel to Fort Mercy**, `./build/deathward --hub redstone`, or `?hub=redstone` in the browser. F4 edits the map, residents and their routes. The tutorial and Rourke's first account are playable; later accounts and the ending are described in the [story brief](docs/redstone_story_hub.md). See the [map and rebuild notes](assets/redstone/README.md).

An optional [Redstone art-direction POC](docs/redstone_art_poc.md) adds weathered terrain/materials, lower sunlight, drifting dust and removable cloth details. Start with `--hub redstone --art-poc` (browser: `?hub=redstone&art=poc`); F6 compares with the original in the hub/editor. It leaves source assets and saved scenes unchanged and is off by default.

**Walk into town buildings** with the same mouse or WASD controls. Doors swing open as you approach. Once inside, roofs and upper walls cut away to reveal the original textured interiors; leaving restores them. This works in Black Creek and Frontier, with added steps connecting Black Creek's station platform. Walls and furnishings remain solid. Ground-floor interiors are supported; overlapping upstairs/downstairs navigation remains limited.

Black Creek's **two tumbleweeds roll through the streets**, following gentle seeded wind, ground height and scenery boundaries. Their rotation follows distance traveled, and their shadows and picking bounds move with them. They are decorative and do not block walking. Pause and mission menus freeze their motion. The town editor's **Animation** inspector lets any object use **Static**, **Spin**, **Sway** or **Tumbleweed**, with editable speed, timing, seed and local rotation pivot, plus Play/Pause/Reset preview. Saving keeps the original placement and the motion settings. See [object animation controls](docs/town_editor.md#animating-props).

Black Creek's **passenger and freight trains run around the original rails**. Carriages follow the curves, locomotive wheels turn with travel, and the trains ease away from their stops. They stop for the player; WASD and mouse paths respect their current positions. Select a train part in the editor's **Animation** tab to change speed, acceleration and station wait or preview the route.

The **fort flags in Redstone and Frontier wave in the wind**, with a fixed attachment, sag, traveling folds and stronger gusts during sandstorms. Original textures remain, and shadows follow the moving fabric. Editor **Play/Pause/Reset preview** and cinematic seeking control the cloth as well; copies of the existing flag fabric animate automatically.

The [converted animal catalog](assets/animals/CATALOG.md) contains **98 textured, animated variants** from all 66 current Polyperfect animal folders. Black Creek now has **a horse, cow, orange cat and two hens** near the starting street. These Polyperfect animals use their original textures and skeletal animations, with independent idle, walking and eating poses and short roaming routes over clear ground. They are ambient residents. Use **F4 → Animals → Species** to place any variant in either town, edit its home, size, facing and roaming radius, or preview its animations. Existing residents are selectable too. See the [animal import and placement guide](assets/animals/README.md).

Black Creek also includes a **cowgirl walking a four-stop route** near the starting street. Use **F4 → People** to place her in any hub, click route stops, set speed and pauses, and preview or save the result. See the [character route controls](docs/town_editor.md#characters-and-walking-routes).

All three hubs use imported sunlight and lamps, with warm ground bounce, cooler sky fill and sun-cast shadows from scenery, the animated bandit and town animals. Shadows follow the camera as you walk, orbit and zoom. The town editor previews the same lighting while objects move. Original textures and placements remain intact.

Generated canyon and mine missions share sun-cast shadows from terrain, scenery, the animated player, enemies, gates and objective props. Ground and characters receive those shadows. Canyon walls keep casting when they fade to reveal the player; camera orbit and zoom do not change the sun direction. Static scenery depth is cached and moving actors update each frame, on native and WebGL builds. Missions also use the static hubs’ warm sunlight, cool sky fill and shared color grading, without an extra canyon tint or brown fog layer.

The world uses an autumn color treatment inspired by the supplied visual reference: amber highlights, plum shadows, richer colors, soft bloom and a subtle vignette. A gentle blur softens fine detail, and light lavender fog builds with scene depth while keeping the camera's focal area clear. Frontier's leafy trees vary between copper and gold; bark, grass and evergreen foliage keep their source palette. The same post processing covers all three hubs, missions and the editor. Menus, text and enemy health bars are drawn afterward to stay sharp and retain their original colors.

In missions, aiming passes through both transparent and solid scenery. Click an enemy's body or outline to attack, or use right-click / Shift-click to aim at the ground behind a model. Movement clicks still approach solid scenery, and physical cover still stops bullets and movement.

Press **F4 in town** or choose **Town Editor** in the pause screen to edit the city in 3D. Select objects, drag move/rotate/scale handles, enter exact transforms, or add models from the asset palette. The editor includes search, duplication, deletion, undo/redo and arrival/mission markers. **Ctrl+S** saves the layout and rebuilds navigation, retaining backups. Launch it directly with `./build/deathward --editor`. See the [town editor guide](docs/town_editor.md) for controls, save locations and navigation details.

The town editor's **Cinematic Editor** button opens a separate timeline tool for camera shots and zoom, carriage interiors, timed sound, sandstorm intensity and train movement/braking. Start its train-and-storm demo with `./build/deathward --cinematic --hub redstone` (browser: `?hub=redstone&cinematic`). Sequences save separately from maps, and previewing preserves the current map-editing session. See the [cinematic editor guide](docs/cinematic_editor.md).

**Westbound**, the authored opening, uses a separate sparse desert map. The seated protagonist talks with an elderly couple before a growing sandstorm stops the train; a conductor reassures them, then the scene cuts to Redstone with the storm active. Choose **Train opening → Play story** in the Cinematic Editor, or edit it directly with `./build/deathward --cinematic --intro`. `./build/deathward --intro` plays the opening and hands control to the player at Redstone. Browser: `?intro&cinematic` to edit, `?intro` to play. Actor movement and subtitles have their own editable timeline tracks.

The **arrival tutorial** continues at **Fort Mercy** (the existing Redstone map): ask the conductor about departure, sleep, then meet the commander. He sends you to recover Silas Bell's survey records. **The Lost Survey** is a single generated floor with five rooms, two small fights and a peaceful document cache containing Eleanor Bell's letter. Read it, use the return lantern and report to the commander. Recovered documents persist and the letter can be reread. Click gold markers to approach conversations. Start with `--hub redstone` (browser: `?hub=redstone`).

After the report, **speak to Caleb Rourke** and follow his account from the badlands trail. Survey Camp, Split Rock, Old Railway Cutting and Dry Creek are mixed into a full multi-floor expedition. Clear their encounters and inspect the marked evidence before leaving each story floor. **Journal** or **J** opens the collected witness claims, observations and questions. Complete the run and return to Eleanor for her competing account. Later testimony runs and animated reconstructions remain future work; Cole's eventual reconstruction must stay explicitly framed as his account. See [expedition structure and story progression](docs/redstone_story_hub.md#full-expeditions-and-the-first-account).

All non-tutorial missions have **4–8 seeded floors, each with 15 rooms**, with junctions and loops that let you choose between routes. Health, powers, money, keys and dynamite carry between floors; there is no free heal. Each floor generates fresh encounters, shops and rewards. Combat rooms seal every doorway, including the entrance behind you. Each combat room starts with one enemy group; defeat it to reopen the doors. There are no later reinforcements; the mine boss has one encounter per floor with three attack phases. Cleared rooms stay cleared when revisited, without extra rewards or healing.

Small seeded clusters of dry grass, stones, fallen sticks and occasional bones decorate every generated room. Larger rooms receive more detail, mainly near edges and cover. Entrances, routes and objective spaces stay clear; these textured props cast shadows without blocking movement, shots or mouse targeting.

Pause in town or a mission to adjust **Vegetation → Less / More** from **0% to 200%**, in 25% steps (default 100%). This changes grass and cacti immediately and remembers your preference across launches, including the browser version. Rocks, debris and room layouts stay fixed. Cacti in generated canyons are restricted to flat ground with room around their full footprint, away from sloping shoulders and cliff edges.

Generated floors now have soft sand/dirt color patches, fine grain, tiny gravel flecks and soil buildup beside rocks, canyon walls and mine cover. The detail follows the seed and stays continuous across floor sections. **Pause → Ground Surface → Detail On/Off** compares it with the original flat floor; your choice is saved. This changes only the floor material, preserving collision, the established lighting and the static hubs.

**Enemies are already present before you enter.** Mission startup prepares every room's seeded group, and nearby rooms render their occupants with idle breathing, bobbing and creature animations. They ignore you in corridors; crossing the room threshold starts combat with those same enemies, without respawning or relocating them. Idle animation does not advance attack timers or create offspring. Hidden residents use the existing enemy outlines.

**The starting room is always enemy-free**, with open passages from the moment you enter. It counts toward the limit of 1–2 ordinary rooms with no enemies; the seed may choose one additional quiet room, separate from the peaceful power rooms and shop. These quiet rooms have open passages, no enemies or power pedestal, and may contain a key. The miners, altar and boss retain their encounters.

**The room network grows from the seed**: two or three starting routes, variable branch lengths and junctions, dead ends, and zero to three loops. Boss and power rooms attach at branch ends instead of fixed corners. Room spacing also varies, producing different corridor lengths. Click **New Mission** or press **N in the station menu** to choose a new seed; keeping the same seed deliberately reproduces the same layout.

Mine rooms have different dimensions (24–40 units per side), with rectangular, clipped-corner, L-shaped and cross-shaped footprints. Canyon basins use these variable envelopes for rounded, irregular footprints and curved connecting trails. The seed chooses the graph, room shapes, objective positions, obstacles, key locations and power-room count. Clear routes are reserved for doors and objectives, and cover that isolates walkable floor is rejected. The same seed and content version reproduce the same map independently of campaign outcomes.

**Fifteen ordinary enemy types are playable**, with distinct silhouettes and attacks: rushers, gunmen, shotgunners, sharpshooters, dynamite throwers, armored brutes, chargers, protective preachers, bell shockwaves, hook throwers, fire spitters, ricochet shooters, teleporting wraiths, explosive husks and chainbound pairs. See the [enemy roster](docs/enemy_roster_proposal.md) for their tells and counters.

**The Isaac monster roster for IDs 10–89 is also playable**, including variants, with new 3D creature silhouettes and seeded room groups. Special behaviors include regenerating piles, protective shells, directional armor, lasers, splitting shots, burrowing, linked enemies and offspring. Permanent hazards cannot prevent room completion. Use **comma / period**, then **Shift+F4**, to test a specific ID. See the [catalog and adaptation notes](docs/isaac_monsters.md).

**Enemy count scales with the room's generated floor area:** subtract obstacle footprints, divide by 70, round up, then clamp to 4–24. Missing corners and corridors do not count. For example, 700 usable square units gives 10 enemies; 1,400 gives 20. Each group mixes up to three seeded types, with clear spawn space and safe landing areas at every doorway. Quiet rooms, power caches and the shop have no enemies; the first boss encounter stays a single Sheriff. Revisits after defeating the Sheriff use an area-scaled ordinary group.

**Free power-ups appear in 1–2 dedicated rooms per floor.** Unlock a power room, approach its pedestal, and choose one of two items. Each pedestal works once, yielding at most two free power-ups on that floor. Two additional powers can be bought at its shop. Powers carry into subsequent floors. Combat rooms do not award items.

**Money appears on room floors and sometimes drops from defeated enemies.** Ground piles follow the mission seed, with 1–2 piles in the starting room and up to four in larger rooms. Each pile is worth 1–5 coins; ordinary enemies and bosses have a 35% drop chance. Walk over a pile or click it to approach and collect it. Enemy drops bounce briefly before collection. The wallet is shown beside the mission map and in all three hubs; collected money stays with the campaign after any mission outcome, including retreat or defeat. Run history records earnings. Summoned offspring, friendly creatures and permanent hazards do not drop money, and saves from before the money feature start with a zero wallet.

**Each non-tutorial floor has one enemy-free shop, marked S on the map.** Its location and two different power-ups follow the floor seed. Click the shopkeeper at the counter to approach and trade, or use the nearby **Trade** button. Field Medicine restores up to 40 HP for 10 coins; each power-up costs 25 coins. Each offer can be bought once per floor, and medicine cannot be purchased at full health. Trading pauses the mission; click **Leave Shop** or press Escape to continue. The shop is reachable without a key. Purchases checkpoint immediately, and spending stays deducted after victory, retreat, defeat or interrupted-run recovery. Bought powers last for the current expedition. Existing wallets are preserved when upgrading saves.

**Dynamite starts at three charges per expedition and defaults to ground placement.** Press **B** or click **Place Dynamite** above the health bar to put a charge at your feet. It stays on the ground and explodes after a two-second fuse, giving you time to move away. The cursor does not choose the placement location.

**Walk into lit dynamite to give it a small nudge.** Both WASD and click-to-move kick it automatically on contact, moving it roughly one character width. Walking away after placing a charge leaves it at your feet until you return and bump into it. Kicking uses no key or button, costs no ammo, and keeps the original fuse burning. The bundle bounces off solid scenery; high airborne charges remain out of foot reach.

Click the **Mode: Place / Mode: Throw** switch above that button to enable the retained throwing mode. In Throw mode, **B** throws at the cursor; **Throw Dynamite** selects a trajectory preview, then a world click throws. Escape, the right button, or the action button cancels targeting. Switching back to Place also cancels targeting without spending ammo. Mode choice lasts for the current game session; new sessions default to Place.

Both modes use the same red dynamite bundle, sparking fuse, explosion sound, fire and smoke. The blast deals 100 damage within a 4.5-unit radius and can hurt you for 25 HP. Solid cover blocks blast damage; dodging and invulnerability protect the player. Optional throws aim up to 12 units away and bounce off scenery; the preview includes bouncing and the blast area. Low cover can be cleared, while tall walls and canyon rock stop a throw. Dynamite kills trigger your existing kill effects.

The shop sells one **three-charge refill pack for 15 coins**, with a carrying limit of nine. Packs cannot overfill the inventory; the purchase checkpoints spending immediately. Unused charges expire when the expedition ends, and each new mission starts with three. Pausing, power choices and trading freeze fuses. Leaving a room or clearing its encounter removes pending ordnance along with other hazards.

**Golden doors require one key.** Keys appear at seeded locations in combat rooms after those rooms are cleared, or immediately upon entering a quiet room; left-click a key or walk over it to collect it. Keys are consumed when unlocking a power room or the boss room. Unlocks persist for the run. All keys are placed in the connected area accessible without spending a key, and there are enough for every lock, so choosing a power room first cannot make the boss unreachable.

The camera follows you through corridors. The mission map shows branches, your position, keys carried, and free powers claimed: **P** marks a power room, **E** an enemy-free room, **S** the shop, **B** the boss, **?** a story site, and **K** a discovered, uncollected key. Red gates are sealed for combat, golden gates need a key, and green gates are open. The final room's lantern advances to the next floor; on the last floor it returns to the hub. The HUD shows the floor and room counts. Expedition length and reward balance still need human playtesting.

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
| B / Place Dynamite button | Place a charge at your feet (default mode) |
| Mode: Place / Throw button | Switch between ground placement and optional throwing |
| Walk into lit dynamite | Automatically nudge it a short distance |
| E / nearby interaction button | Interact near an objective or shopkeeper |
| 1 / 2 | Choose one item at a power-room pedestal |
| 1 / 2 / 3 / 4 in the shop | Buy medicine / first power / second power / dynamite pack |
| Escape in the shop | Close trade and return to play |
| Escape / Pause button | Pause / resume; click Keep Going to resume with the mouse |
| T while paused | Retreat and resolve consequences |
| H in the hub | Inspect previous runs |
| J / Journal button | Read recovered claims, observations and open questions |

Start each expedition with **100 HP** and **24 revolver damage**. Enemy kills, room clears and room entry provide no automatic healing. The revolver fires continuously while holding an enemy, Shift + LMB, or RMB; there is no reload action or reload pause. The six-round display tracks the next shot in a repeating cycle, so every sixth shot still triggers last-round effects. Judas Bullet still costs 20% of maximum health per copy.

Both enemy rosters now deal **25% more damage**, move **10% faster during ordinary movement**, and have **15% shorter attack cooldowns**. A former 10-damage hit now deals 12.5. The mine's Sheriff shares this tuning. Attack warnings, projectile speeds, committed charges/jumps, enemy health and the player's dodge/hurt protection retain their existing values; mirror movement, orbit positioning and friendly monsters retain their original movement behavior.

With cheats enabled, pause a mission to use **Player Settings**: adjust base health in steps of 25 and shot damage in steps of 4. During play, **minus / equals** (or keypad minus / plus) adjust damage; hold **Shift** with those keys to adjust health. **Home** restores the 100 HP / 24 damage defaults. Base health is bounded to 25–2,000 and damage to 1–500. Health changes preserve your current health percentage and still apply Judas Bullet's health cost; Shift+F2 fully heals. Settings apply immediately to new shots and carry into subsequent missions and hub travel for this session. Restarting the game restores the defaults. Split and ghost bullets use the adjusted shot damage; Powder of Jericho keeps its own explosion damage.

Left-click follows the contextual move/attack/interact pattern in [Blizzard's Diablo manual](https://ftp.blizzard.com/pub/misc/Diablo.PDF). Click ground to walk there, or hold to steer. Click an enemy's body to attack; holding keeps that target until release, and its death never turns the attack into a movement order. Attacking cancels the current mouse route. WASD overrides mouse navigation and remains available while firing; Shift holds position. RMB uses the prototype's only weapon, the revolver.

Left-click the miners, altar, a key, a power pedestal, the shopkeeper, a doorway, or the return lantern to approach and use it. Nearby interactions, dodge and pause also have clickable buttons, so the expedition is playable with a two-button mouse.

Hold the middle mouse button and drag to orbit the camera in town or a mission. Horizontal dragging rotates around the character; vertical dragging tilts between 25 and 75 degrees above the ground. Release to keep that angle. WASD follows the current camera direction, and ground clicks use the rotated view. Start the drag over the world; HUD controls and open menus do not start camera gestures.

Mouse-wheel zoom moves smoothly between a close character view and a wider room view while preserving the camera angle. Your chosen angle and zoom persist between rooms, town and expeditions during the session. Scrolling over the HUD controls, map or open cheat panel, or while paused, trading or choosing a power, does not change zoom.

In all three hubs, an entire rock or building object becomes semi-transparent when it blocks the player. Canyon wall sections and rock outcrops use the same 22% opacity, including props resting on them. A thin gray line follows the ground boundary of faded canyon rock so you can still see where the playable floor ends. Scenery returns to full opacity when the camera has a clear view. Playable floors and collision stay intact; this is a rendering effect.

Enemies hidden behind scenery have a thin warm-red silhouette outline in both mission themes. The outline follows their animated shape and appears only along concealed edges. Dead, friendly, buried and teleporting enemies do not receive it.

A small FPS counter in the top-right corner shows the rendering frame rate on every screen. In hubs and missions, the current camera zoom appears beside it. New sessions start at **160% zoom**; 100% remains the reference scale, higher percentages are closer, and lower percentages are wider. The value follows the camera smoothly as you scroll. Your chosen zoom carries between hubs and missions for the session.

World interactions use visual cues instead of floating control instructions: open exits have small floor arrows and colored lanterns, locked doors have golden locks, and pickups and objectives have glow or ground markers. Control reminders live in the hub, pause screen and this guide.

The player uses the textured **bandit model supplied in `assets/bandit`**. Its FBX clips drive breathing idle, walking, running, firing, sliding or jumping dodges and two death animations. Moving attacks blend the firing pose over the legs' movement; turning follows movement or aim. Animation pauses and slows with gameplay. Natural death plays a two-second animation before the results screen; the F9 testing shortcut still resolves immediately.

The generated rooms use **textured PolygonWestern scenery**: stacked crates for cover, boundary fences, railway passages and lanterns. Seeded saloons, jails, churches, stations, water towers, carts, barrels, rocks and cacti surround the playable routes. The original texture atlas and material tints are embedded in the models, with directional lighting adapted for raylib. Cover fits the existing collision boxes; buildings are exterior scenery. Keeping the same seed and theme reproduces the scenery as well as the map.

**Redstone Canyon** uses irregular basins and winding trails cut into a continuous rock terrain. Outcrops replace cube cover; the visible triangles also define movement, bullet and sight collisions. The original atlas supplies brown cliff faces and pale faceted caps, with directional terrain shadows and sparse rocks/cacti. Cliffs and cover keep their full generated height. The mine keeps its existing generator. A seed and theme reproduce their own geometry and encounters; canyon enemy counts use the basin's navigable floor area. Free missions in both settings share the miners and altar objectives; the Redstone story search has its own objective. Canyon completion is tracked separately from defeating the mine’s Sheriff. See [mission theming](docs/mission_themes.md) for extension points.

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
| Shift + B | Refill dynamite to nine charges |
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
./build/deathward_building_tests
./build/deathward_redstone_render_tests
./build/deathward_mission_lighting_tests
./build/deathward_occlusion_tests
./build/deathward_post_process_tests
./build/deathward_audio_tests
./build/deathward --smoke --theme mine --frames 180 --screenshot artifacts/combat.png
./build/deathward --smoke --theme canyon --scene combat --frames 90 --screenshot artifacts/canyon-combat.png
./build/deathward --smoke --scene hub --frames 2 --screenshot artifacts/hub.png
./build/deathward --benchmark --frames 600 --screenshot artifacts/stress.png
```

The nineteen core CTest suites need no graphics display or audio device. Audio presentation checks cover confirmed cues, priorities, bounded queues and unchanged gameplay randomness. Mission-theme checks cover seeded selection, organic terrain reproduction, clear routes, sealed entrances, safe enemy placement, surface collision and persisted canyon checkpoints/history. `deathward_input_tests` exercises mouse controls and function-key cheats through raylib's input system in a hidden window. `deathward_player_model_tests` checks the packaged mesh, texture, all nine clips, blending, simulation timing, root-motion removal and resource cleanup. `deathward_western_assets_tests` checks the scenery atlas, glass, scale, collision alignment, route clearance, seed reproduction, canyon terrain/mesh alignment and resource cleanup. `deathward_occlusion_tests` compares whole-object transparency in towns and canyon wall sections at different zoom levels, checks that translucent scenery remains visible, verifies restoration and unchanged collision, and saves before/after captures under `artifacts`. `deathward_audio_tests` exercises the real audio device, packaged sounds, voice limits, panning, pause/mute, crossfades, looping, preferences and cleanup; it captures and silences its output unless passed `--audible`. The graphics suites require an X11/OpenGL display, as do the render checks; `xvfb-run` is also suitable where available. Input checks use a temporary campaign. Scripted render checks use a fresh temporary campaign by default. An explicit `--save PATH` opts into that campaign.

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

The shared [PolygonParticleFX library](assets/particles/README.md) provides campfire
flames, textured gunfire/impact effects, dynamite bursts, locomotive steam trails
and sparse seeded canyon dust. Campfire and steam attachments follow props in the
town editor; effects pause with the game and work in native and browser builds.

The hub separately imports the complete original Demo scene into `assets/town`: 1,516 active mesh placements with 12 embedded textures, original material variants, hierarchy and transforms. Its scene catalog and terrain navigation are packaged beside the GLB. See [the town import notes](assets/town/README.md) for the source audit, rebuilding commands and differences from Unity's rendering. CTest includes town and building navigation; `deathward_town_assets_tests` checks the original scene's graphics assets and requires a display.

## Code map

- `src/combat`: fixed-step simulation, 3D collision, AI, spatial broad phase and event budgets.
- `src/items`: the item registry and independent effect handlers.
- `src/world`: seeded dungeon geometry, persistent world state, consequences, history and atomic save transactions.
- `src/core`: application flow, input, math and deterministic RNG.
- `src/render`: 3D rendering, instanced seeded scenery, player animation blending and menus; no combat rules.
- `tests`: gameplay and persistence contract checks.

The [design brief](weird_west_3d_prototype_agent_brief.md) describes the wider experiment. This implementation extends Milestone 1 with the Western and monster rosters and seeded room networks. The 25-item catalog and three expeditions remain future content work.
