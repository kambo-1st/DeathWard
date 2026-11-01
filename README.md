# DeathWard

A playable C++20 / raylib 3D Weird West prototype. Borrow a broken build from Red Hollow Mine, bring its people home, and leave lasting consequences in Black Creek.

**The build is gone. The consequences remain.**

## Build and run on Linux

To build without launching the game (also works in WSL2):

```sh
./scripts/build-linux.sh
```

Launch the result with `./build/deathward`. The build script configures a Release
build and compiles the game, with its runtime
assets staged in `build/assets`. It works from any working directory. Use
`--jobs 8` (or `DEATHWARD_BUILD_JOBS=8`) to change the default four parallel jobs.
For a separate debug build, run:

```sh
./scripts/build-linux.sh --config Debug --build-dir build-debug
```

Use `--help` for all options. To build and launch in one step:

```sh
./scripts/run.sh
```

`run.sh` uses the same Linux build script and forwards its arguments to the game,
for example `./scripts/run.sh --hub redstone`. The first build downloads pinned
raylib 5.5; subsequent builds reuse it. No game assets or other third-party packages
are downloaded. CMake 3.20+, a C++20 compiler, OpenGL and X11 development libraries
are required. On Ubuntu/Debian:

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

The [Linux build reproducibility report](docs/reports/linux-reproducibility-2026-10-03.html)
([PDF](docs/reports/linux-reproducibility-2026-10-03.pdf)) records ten clean Release
builds, artifact hashes, timing measurements and the explanation of metadata
differences. It includes commands for repeating the audit.

## Build for Windows from WSL

Install **Visual Studio 2022** with **Desktop development with C++** and Windows
**CMake 3.20+**, then run in WSL:

```sh
./scripts/build-windows.sh
```

This invokes the installed Windows compiler through WSL interop and produces a
native **Windows x64 Release** build. It does not replace the Linux or browser
builds. WSL sources are mirrored into the disposable Windows build cache at
`%LOCALAPPDATA%\DeathWard\build-windows`, avoiding MSBuild's case-sensitive UNC
path problems. CMake output is in its `cmake` subdirectory; the portable
game and ZIP are in `dist/deathward-windows-x64` and
`dist/deathward-windows-x64.zip` in this checkout.

Extract the ZIP into a writable Windows folder and double-click **Play DeathWard.cmd**
for the full experience, or **deathward.exe** to start directly in town. Keep the
included `assets` folder beside the executable. All runtime models, textures,
maps, animations, fonts, music and effects are bundled; the game needs no WSL
installation or separate Visual C++ runtime installation. It requires 64-bit
Windows 10/11 with an OpenGL 3.3-capable graphics driver.

Windows saves and preferences live in `%LOCALAPPDATA%\DeathWard`, separately from
Linux and browser saves. Editors modify the packaged maps, without reaching into
the original WSL checkout. The build script enables `DEATHWARD_PACKAGED_ASSETS`
for this; ordinary development builds retain their editable source scenes.

The same build script can run directly in Windows PowerShell:

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\scripts\build-windows.ps1
```

Pass `-RunTests` to also compile the test executables and run the headless CTest
suites on Windows. `-BuildDirectory`, `-OutputDirectory` and `-Jobs` customize
the output and compilation parallelism; `-SkipPackage` builds only. Directory
arguments forwarded from WSL must use Windows paths. `-RaylibSourceDirectory`
can reuse an existing raylib 5.5 checkout; otherwise CMake fetches the pinned,
hash-checked archive on the first build.

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

Open **http://127.0.0.1:8080/**, wait for loading and click **Enter Black Creek**. The WebAssembly version includes all three hubs, missions, original textures, lighting, post processing, music and effects. It requires WebGL 2 and a keyboard; mouse controls also remain available. Campaigns, audio preferences and town-editor saves stay in that browser, separately from desktop saves. See the [browser guide](docs/browser.md) for setup, hosting, controls and verification.

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

The town editor has a **Sandstorm preview: ON / OFF** toolbar button. Its toggle affects only the editor view: it does not change the saved map, undo history, or the weather when returning to gameplay. Each time the editor opens, its preview starts from the hub's current weather.

In the editor, the top toolbar's **Draw allowed area** and **Draw blocked area** buttons let you click boundary points to define movement limits. **Walkable areas** opens the panel for managing existing outlines. Finish the outline, check **Rebuild path preview**, then **Save**. Both WASD and mouse movement stop at these saved limits; existing scenery still blocks movement. See the [walkable-area guide](docs/town_editor.md#walkable-areas).

A second hub imports the original **PolygonWesternFrontier Demo** with its village, fort, quarry, river, vegetation and original textures. Use **Travel to Frontier** at the bottom right while exploring, or **Travel to Black Creek** to return. Travel is also available in Pause. Start there directly with `./build/deathward --hub frontier`. Missions return to the hub you departed from. Hub choice lasts for the session; all three hubs share the campaign. See [the Frontier import notes](assets/frontier/README.md) for the scene audit and rendering boundaries.

A third authored hub, **Fort Mercy** (the Redstone Canyon map), combines Black Creek's full-sized canyon and rail route with Frontier's fort and an expanded settler camp. The train is stranded beside a buried line. Fifteen provisional residents populate the arrival, market, witness shelters and guarded fort; a covered wagon waits at the camp edge. Use **Travel to Fort Mercy**, `./build/deathward --hub redstone`, or `?hub=redstone` in the browser. F4 edits the map, residents and their routes. The tutorial and Rourke's first account are playable; later accounts and the ending are described in the [story brief](docs/redstone_story_hub.md). See the [map and rebuild notes](assets/redstone/README.md).

An optional [Redstone art-direction POC](docs/redstone_art_poc.md) adds weathered terrain/materials, lower sunlight, drifting dust and removable cloth details. Start with `--hub redstone --art-poc` (browser: `?hub=redstone&art=poc`); F6 compares with the original in the hub/editor. It leaves source assets and saved scenes unchanged and is off by default.

Seventeen **visual styles** can be compared live: **Original**, **Cel-shaded**,
**Western comic**, **Painted frontier**, **Wanted poster**, **Western noir**,
**Retro 3D**, **Woodcut / linocut**, **Watercolor**, **Colored pencil**, **Ink wash**,
**Miniature diorama**, **Spaghetti Western**, **CRT arcade**, **Spectral frontier**, **Sumi-e frontier**, and **Matte frontier**. In a hub or either editor, **F6**
cycles through them. In hubs and missions, **Pause → Visual Style** offers the
same selector; mission F6 keeps its cheat behavior. The choice lasts only for
that session and does not edit maps, saves or visual preferences. Ordinary
launches retain the original graphics.

Start directly with `./scripts/run.sh --hub redstone --style comic` or
`--style painted` (browser: `?hub=redstone&style=comic` or `&style=painted`).
`--style original` and `--style cel` select the other presets; the earlier
`--cel-shading` flag remains an alias for `--style cel`.
The remaining style names are `poster`, `noir`, `retro`, `woodcut`, `watercolor`,
`pencil`, `ink`, `diorama`, `cinema`, `crt`, `spectral`, `sumi`, and `matte`, also accepted by the
browser's `style` parameter. `--style okami` (or `?style=okami`) is an alias for
Sumi-e frontier, the Okami-inspired brush-and-ink preset.

Cel-shaded retains its three lighting bands, thin depth outlines and crisp finish.
Western comic adds stronger ink, shadow hatching and subtle static paper grain.
Painted frontier uses continuous lighting, cooler shadows, warmer highlights,
gentle color patches and muted distant scenery without ink outlines. Its small
edge-aware filter preserves geometry boundaries. These styles omit the normal
bloom, keep UI sharp, and apply to hubs, generated missions, characters, animals
and cinematic views. They also retain sandstorms and occluded-enemy outlines.
Selecting a stylized preset disables the separate, older art-direction POC.

Wanted poster uses six base ink tones, dark contours and paper fibres. Western
noir uses high-contrast monochrome with selective saturated warm and turquoise
accents. Retro 3D uses integer-sized world pixels, a reduced color palette and
ordered dithering; HUD text remains at full resolution.

Woodcut uses three base inks with irregular cream gouges through shadow blocks.
Watercolor layers translucent washes over pale paper with darker pigment at edges;
Colored pencil builds directional color strokes over paper tooth. Ink wash uses
soft monochrome stains and broad grays rather than Noir's photographic contrast.
These print/paper patterns are screen-anchored and stable while paused.

Miniature diorama softens the light, adds a screen-space depth contact approximation,
and gently defocuses depth away from the camera target. It is a rendering treatment
of the existing geometry, not a replacement miniature asset set or baked AO.
Spaghetti Western adds muted sun-bleached color, deep cool shadows and fine stable
grain. CRT arcade adds fixed scanlines, phosphor color, horizontal light bleed and
coarser world pixels, without flicker or screen warp. Spectral frontier uses cool,
desaturated scenery, luminous depth contours and color-selected warm accents.

Sumi-e frontier combines painted light bands, thick irregular ink contours, soft
ink bleed, warm paper and vivid vermilion/jade accents. It takes inspiration from
Okami's brush-and-ink presentation using DeathWard's existing assets, with no
uniform crosshatching or imported artwork.

Matte frontier follows the supplied low-poly timber-interior reference: continuous
diffuse light, subdued neutral fill, earthy surface colors, warm authored lamps
and soft depth-based contact shading. Original green foliage remains green in
Frontier. Facets stay crisp, with no ink, paper grain, bloom or lens blur. The
contact effect is a screen-space approximation, not baked AO or new geometry.
Try `./scripts/run.sh --hub frontier --style matte` or `?hub=frontier&style=matte`.
Switching back restores the original surfaces and foliage without changing assets.

`deathward_cel_shading_tests` captures matching fort, character and canyon views
in `artifacts/cel-<style>-<view>.png` (Original uses `before`, Cel uses `after`),
and checks distinct presets, UI colors, sandstorms, static-frame stability and exact restoration
of the original and cel-shaded renders after switching presets. Additional
`cel-before-{frontier,saloon}.png` and `cel-matte-{frontier,saloon}.png` captures
check foliage and an interior cutaway, including restoration of the original lighting.
The contours
come from visible depth edges. `web/cel-shading-test.cjs` checks all 17 WebGL
styles, F6, the Pause selector, unchanged scene data and default-off reloads.

After running the capture test, `python3 scripts/visual-style-report.py` creates
`artifacts/visual-style-comparison.html`: an offline HTML comparison with 51
embedded screenshots, a draggable split view, style selectors, and fort,
character and canyon viewpoints. The generated HTML can be shared on its own.
For a large gallery of all 51 captures, run the same command with `--layout gallery`.
It writes `artifacts/visual-style-gallery.html`, with one/two-column layouts,
style filtering and a full-screen image viewer supporting keyboard navigation,
actual-size inspection and PNG downloads. Images are embedded for offline use.

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

All non-tutorial missions have **4–8 seeded floors, growing from 9 to 15 rooms**, with junctions and loops that let you choose between routes. Health, powers, money, keys and dynamite carry between floors; there is no free heal. Each floor generates fresh encounters, shops and rewards. Combat rooms seal every doorway, including the entrance behind you. Each combat room starts with one enemy group; defeat it to reopen the doors. There are no later reinforcements; the mine boss has one encounter per floor with three attack phases. Cleared rooms stay cleared when revisited, without extra rewards or healing.

The default **Compact / 9 to 15 rooms** preset combines smaller early rooms with shorter corridors. The mission board cycles through **Classic** (the original fifteen-room layout), **Growing** (fewer rooms at the original dimensions), **Short Corridors**, **Small Rooms**, and **Compact**. Native launches accept `--expedition-pacing compact|classic|growing|corridors|rooms`; the browser accepts the same names with `?pacing=...`. The non-Classic presets use `9 → 11 → 13 → 15` rooms for four-floor runs and `9 → 10 → 11 → 12 → 13 → 14 → 15 → 15` for eight. The tutorial stays at five rooms. Selection carries across floors and is recorded in run history. Smaller early floors have one power cache, with keys placed in the unlocked network.

Compact opening rooms use **20–28-metre envelopes** and grow toward 24–40 metres on later floors. Boss envelopes retain 32–40 metres. Corridor spacing accounts for neighboring room widths; most early connectors are shorter, but a small room beside a larger column can still have a longer approach. The tutorial keeps its original room envelopes. See the [pacing trial report](docs/expedition_pacing_trials.md) for measured distances, automated run timings and their limits.

Small seeded clusters of dry grass, stones, fallen sticks and occasional bones decorate every generated room. Larger rooms receive more detail, mainly near edges and cover. Entrances, routes and objective spaces stay clear; these textured props cast shadows without blocking movement, shots or mouse targeting.

Pause in town or a mission to adjust **Vegetation → Less / More** from **0% to 200%**, in 25% steps (default 100%). This changes grass and cacti immediately and remembers your preference across launches, including the browser version. Rocks, debris and room layouts stay fixed. Cacti in generated canyons are restricted to flat ground with room around their full footprint, away from sloping shoulders and cliff edges.

Generated floors now have soft sand/dirt color patches, fine grain, tiny gravel flecks and soil buildup beside rocks, canyon walls and mine cover. The detail follows the seed and stays continuous across floor sections. **Pause → Ground Surface → Detail On/Off** compares it with the original flat floor; your choice is saved. This changes only the floor material, preserving collision, the established lighting and the static hubs.

**Enemies are already present before you enter.** Mission startup prepares every room's seeded group, and nearby rooms render their occupants with idle breathing, bobbing and creature animations. They ignore you in corridors; crossing the room threshold starts combat with those same enemies, without respawning or relocating them. Idle animation does not advance attack timers or create offspring. Hidden residents use the existing enemy outlines.

**The starting room is always enemy-free**, with open passages from the moment you enter. It counts toward the limit of 1–2 ordinary rooms with no enemies; each non-tutorial floor has a 20% seeded chance of one additional quiet room, separate from the peaceful power rooms and shop. An optional service room can use that extra quiet slot instead. These quiet rooms have open passages, no enemies or power pedestal, and may contain a key. The miners, altar and boss retain their encounters.

**The room network grows from the seed**: two or three starting routes, variable branch lengths and junctions, dead ends, and zero to three loops. Boss and power rooms attach at branch ends instead of fixed corners. Room spacing also varies, producing different corridor lengths. Click **New Mission** or press **N in the station menu** to choose a new seed; keeping the same seed deliberately reproduces the same layout.

Mine rooms have different dimensions (20–28 units per side on Compact opening floors, growing toward 24–40; Classic keeps 24–40), with rectangular, clipped-corner, L-shaped and cross-shaped footprints. Canyon basins use these variable envelopes for rounded, irregular footprints and curved connecting trails. The seed chooses the graph, room shapes, objective positions, obstacles, key locations and power-room count. Clear routes are reserved for doors and objectives, and cover that isolates walkable floor is rejected. The same seed and content version reproduce the same map independently of campaign outcomes.

**Fifteen ordinary enemy types are playable**, with distinct silhouettes and attacks: rushers, gunmen, shotgunners, sharpshooters, dynamite throwers, armored brutes, chargers, protective preachers, bell shockwaves, hook throwers, fire spitters, ricochet shooters, teleporting wraiths, explosive husks and chainbound pairs. See the [enemy roster](docs/enemy_roster_proposal.md) for their tells and counters.

**The Isaac monster roster for IDs 10–89 is also playable**, including variants, with new 3D creature silhouettes and seeded room groups. Special behaviors include regenerating piles, protective shells, directional armor, lasers, splitting shots, burrowing, linked enemies and offspring. Permanent hazards cannot prevent room completion. Use **comma / period**, then **Shift+F4**, to test a specific ID. See the [catalog and adaptation notes](docs/isaac_monsters.md).

**Western Mine and Classic Canyon enemy counts scale with the room's generated floor area:** subtract obstacle footprints, divide by 70, round up, then clamp to 4–24. Missing corners and corridors do not count. For example, 700 usable square units gives 10 enemies; 1,400 gives 20. Each group mixes up to three seeded types, with clear spawn space and safe landing areas at every doorway. Quiet rooms, power caches and the shop have no enemies; the first boss encounter stays a single Sheriff. Revisits after defeating the Sheriff use an area-scaled ordinary group.

**Free power-ups appear in 1–2 dedicated rooms per floor.** Unlock a power room, approach its pedestal, and choose one of two items. Each pedestal works once, yielding at most two free power-ups on that floor. Two additional powers can be bought at its shop. Powers carry into subsequent floors. Ordinary combat rooms do not award items. Modern canyon bosses offer one optional item choice; service rooms add finite exchanges, treatment and maximum-HP bargains. See [optional rooms and reward pools](docs/expedition_economy.md).

**Money appears on room floors and sometimes drops from defeated enemies.** Ground piles follow the mission seed, with 1–2 piles in the starting room and up to four in larger rooms. Each pile is worth 1–5 coins; ordinary enemies and bosses have a 35% drop chance. Walk over a pile or click it to approach and collect it. Enemy drops bounce briefly before collection. The wallet is shown beside the mission map and in all three hubs; collected money stays with the campaign after any mission outcome, including retreat or defeat. Run history records earnings. Summoned offspring, friendly creatures and permanent hazards do not drop money, and saves from before the money feature start with a zero wallet.

**Each non-tutorial floor has one enemy-free shop, marked S on the map.** Its location and two different power-ups follow the floor seed. Each shop or service room has at most one trader. Field Surgeons cannot appear on floors 1–3; they become eligible on floor 4. Click the shopkeeper at the counter to approach and trade, or press **E / Enter** while nearby. Field Medicine restores up to 40 HP for 10 coins; each power-up costs 25 coins. Each offer can be bought once per floor, and medicine cannot be purchased at full health. Trading pauses the mission; click **Leave Shop** or press Escape to continue. The shop is reachable without a key. Purchases checkpoint immediately, and spending stays deducted after victory, retreat, defeat or interrupted-run recovery. Bought powers last for the current expedition. Existing wallets are preserved when upgrading saves.

**Dynamite starts at three charges per expedition and defaults to ground placement.** Press **B** or click **Dynamite** above the health bar to put a charge at your feet. It stays on the ground and explodes after a two-second fuse, giving you time to move away. The cursor does not choose the placement location.

**Walk into lit dynamite to give it a small nudge.** Both WASD and click-to-move kick it automatically on contact, moving it roughly one character width. Walking away after placing a charge leaves it at your feet until you return and bump into it. Kicking uses no key or button, costs no ammo, and keeps the original fuse burning. The bundle bounces off solid scenery; high airborne charges remain out of foot reach.

Press **C** or click the adjacent **Place / Throw** switch to enable throwing. In Throw mode, **Dynamite** selects a mouse trajectory preview, then a world click throws. Escape, the right button, or the action button cancels targeting. Switching back to Place also cancels targeting without spending ammo. Mode choice lasts for the current game session; new sessions default to Place.

**B works even with the mouse parked over the HUD.** In Throw mode, B throws ten units in the held arrow direction, otherwise the movement direction, otherwise the direction the character faces. Hold B with an arrow to throw without firing a bullet on that press. Mouse targeting remains available through the Throw Dynamite button. **C** switches modes.

Both modes use the same red dynamite bundle, sparking fuse, explosion sound, fire and smoke. The blast deals 100 damage within a 4.5-unit radius and can hurt you for 25 HP. Solid cover blocks blast damage; dodging and invulnerability protect the player. Optional throws aim up to 12 units away and bounce off scenery; the preview includes bouncing and the blast area. Low cover can be cleared, while tall walls and canyon rock stop a throw. Dynamite kills trigger your existing kill effects.

**Destructible expedition scenery:** cracked boulders take one dynamite blast; gold-marked seams yield a few coins. A reinforced supply cache takes two blasts and contains a key and 8–12 coins. Its first hit leaves a visible crack, and damage and loot persist when revisiting rooms. Powder barrels ignite after two starting revolver hits, warn briefly, then explode. Free item explosions and barrel chains cannot open hard cover or caches. Required routes never depend on dynamite; boundary cliffs and story scenery remain intact. Classic and the tutorial retain their previous scenery. Test a complete cache opening with `--smoke --scene demolition-run --theme canyon --frames 430`.

The shop sells one **three-charge refill pack for 15 coins**, with a carrying limit of nine. Packs cannot overfill the inventory; the purchase checkpoints spending immediately. Unused charges expire when the expedition ends, and each new mission starts with three. Pausing, power choices and trading freeze fuses. Leaving a room or clearing its encounter removes pending ordnance along with other hazards.

**Golden doors require one key.** Keys appear at seeded locations in combat rooms after those rooms are cleared, or immediately upon entering a quiet room; left-click a key or walk over it to collect it. Keys are consumed when unlocking a power room or the boss room. Unlocks persist for the run. All keys are placed in the connected area accessible without spending a key, and there are enough for every lock, so choosing a power room first cannot make the boss unreachable.

The camera follows you through corridors. The mission map shows branches, your position, keys carried, and free powers claimed: **P** marks a power room, **E** an enemy-free room, **S** the shop, **B** the boss, **?** a story site, and **K** a discovered, uncollected key. Red gates are sealed for combat, golden gates need a key, and green gates are open. After clearing the final room, a pulsing teal exit beacon and a large **NEXT FLOOR** marker show where to continue; on the last floor the marker says **RETURN TO FORT/HUB**. The marker remains visible through scenery and stays within the screen at close zoom. Click it to approach, or walk to the beacon and press **E / Enter**. An amber **EXIT LOCKED** marker explains any required evidence or tutorial records still missing. Boss rewards are optional. The minimap marks an available exit with **>**. The HUD briefly shows the room name on entry. The expedition details in Pause show the floor identity, floor and room counts, seed and elapsed time. Owned powers use a compact icon strip; click an icon or press Tab for descriptions and stack counts. Use world clicks or E/Enter for nearby interactions; there is no interaction button on the HUD. Lit-powder warnings take priority over routine notifications. Expedition length and reward balance still need human playtesting.

| Control | Action |
| --- | --- |
| WASD | Move relative to the camera |
| Hold arrow keys | Fire relative to the camera; combine adjacent arrows for diagonal shots |
| Left-click ground / hold left button | Move to a point / keep steering around cover |
| Left-click an enemy / hold left button | Shoot / keep firing at that enemy as it moves |
| Left-click an objective | Approach and interact automatically |
| Shift + left button | Fire toward the cursor while standing still |
| Right button | Fire the revolver directly toward the cursor |
| Hold middle button + drag | Rotate around the character; drag vertically to tilt |
| Q / R | Rotate the camera using the keyboard |
| Insert / Delete | Tilt the camera up / down |
| Space / Dodge button | Dodge; brief invulnerability, then cooldown |
| Mouse wheel / Page Up / Page Down | Zoom in / out |
| B / Dynamite button | Place a charge at your feet (default mode) |
| C / Place / Throw button | Switch between ground placement and optional throwing |
| Walk into lit dynamite | Automatically nudge it a short distance |
| E / Enter | Open or unlock a nearby door, examine evidence, use a shop or reward, or continue through the floor exit |
| 1 / 2 | Choose one item at a power-room pedestal |
| 1 / 2 / 3 / 4 in the shop | Buy medicine / first power / second power / dynamite pack |
| Escape in the shop | Close trade and return to play |
| Escape / Pause button | Pause / resume; click Keep Going to resume with the mouse |
| Tab during play / click an owned item | Inspect your build and item descriptions; play pauses until Tab, Escape or Back closes it |
| Tab / Shift+Tab / arrows in menus | Select an available button; Enter or Space activates it |
| H while paused / Keyboard Controls button | Show the complete keyboard guide |
| T while paused | Retreat and resolve consequences |
| H in the hub | Inspect previous runs |
| J / Journal button | Read recovered claims, observations and open questions |
| L | Reread Eleanor's letter after recovering it |

Start each expedition with **100 HP** and **24 revolver damage**. Enemy kills, room clears and room entry provide no automatic healing. The revolver fires continuously while holding an enemy, an arrow key, Shift + LMB, or RMB; there is no reload action or reload pause. The repeating six-shot cycle still triggers last-round effects, without an ammunition display on the HUD. Judas Bullet still costs 20% of maximum health per copy.

Both enemy rosters now deal **25% more damage**, move **10% faster during ordinary movement**, and have **15% shorter attack cooldowns**. A former 10-damage hit now deals 12.5. The mine's Sheriff shares this tuning. Attack warnings, projectile speeds, committed charges/jumps, enemy health and the player's dodge/hurt protection retain their existing values; mirror movement, orbit positioning and friendly monsters retain their original movement behavior.

With cheats enabled, pause a mission to use **Player Settings**: adjust base health in steps of 25 and shot damage in steps of 4. During play, **minus / equals** (or keypad minus / plus) adjust damage; hold **Shift** with those keys to adjust health. **Home** restores the 100 HP / 24 damage defaults. Base health is bounded to 25–2,000 and damage to 1–500. Health changes preserve your current health percentage and still apply Judas Bullet's health cost; Shift+F2 fully heals. Settings apply immediately to new shots and carry into subsequent missions and hub travel for this session. Restarting the game restores the defaults. Split and ghost bullets use the adjusted shot damage; Powder of Jericho keeps its own explosion damage.

Left-click follows the contextual move/attack/interact pattern in [Blizzard's Diablo manual](https://ftp.blizzard.com/pub/misc/Diablo.PDF). Click ground to walk there, or hold to steer. Click an enemy's body to attack; holding keeps that target until release, and its death never turns the attack into a movement order. Attacking cancels the current mouse route. WASD overrides mouse navigation and remains available while firing; Shift holds position. RMB uses the prototype's only weapon, the revolver.

Arrow keys also fire during missions, independently of the cursor. Hold an arrow while moving with WASD to strafe, or hold two adjacent arrows for diagonal fire. Opposite arrows cancel each other. Arrow aiming takes priority over mouse aiming while held, follows camera rotation, and works with the cursor over the HUD. Release the arrows to return to mouse aiming. Menus and dynamite placement/targeting block gunfire. Release menu-navigation arrows before firing again after closing a panel.

Left-click the miners, altar, a key, a power pedestal, the shopkeeper, a doorway, or the return lantern to approach and use it. Dodge, dynamite and pause have clickable buttons, so the expedition is playable with a two-button mouse.

Hold the middle mouse button and drag to orbit the camera in town or a mission. Horizontal dragging rotates around the character; vertical dragging tilts between 25 and 75 degrees above the ground. Release to keep that angle. WASD follows the current camera direction, and ground clicks use the rotated view. Start the drag over the world; HUD controls and open menus do not start camera gestures.

Mouse-wheel zoom moves smoothly between a close character view and a wider room view while preserving the camera angle. Your chosen angle and zoom persist between rooms, town and expeditions during the session. Scrolling over the HUD controls, map or open cheat panel, or while paused, trading or choosing a power, does not change zoom.

In all three hubs, an entire rock or building object becomes semi-transparent when it blocks the player. Canyon wall sections and rock outcrops use the same 22% opacity, including props resting on them. A thin gray line follows the ground boundary of faded canyon rock so you can still see where the playable floor ends. Scenery returns to full opacity when the camera has a clear view. Playable floors and collision stay intact; this is a rendering effect.

Enemies hidden behind scenery have a thin warm-red silhouette outline in both mission themes. The outline follows their animated shape and appears only along concealed edges. Dead, friendly, buried and teleporting enemies do not receive it.

A small FPS counter in the top-right corner shows the rendering frame rate on every screen. In hubs and missions, the current camera zoom appears beside it. New sessions start at **160% zoom**; 100% remains the reference scale, higher percentages are closer, and lower percentages are wider. The value follows the camera smoothly as you scroll. Your chosen zoom carries between hubs and missions for the session.

World interactions use visual cues instead of floating control instructions: open exits have small floor arrows and colored lanterns, locked doors have golden locks, and pickups and objectives have glow or ground markers. Control reminders live in the hub, pause screen and this guide.

The player uses the textured **bandit model supplied in `assets/bandit`**. Its FBX clips drive breathing idle, walking, running, firing, sliding or jumping dodges and two death animations. Moving attacks blend the firing pose over the legs' movement; turning follows movement or aim. Animation pauses and slows with gameplay. Natural death plays a two-second animation before the results screen; the F9 testing shortcut still resolves immediately.

The generated rooms use **textured PolygonWestern scenery**: stacked crates for cover, boundary fences, railway passages and lanterns. Seeded saloons, jails, churches, stations, water towers, carts, barrels, rocks and cacti surround the playable routes. The original texture atlas and material tints are embedded in the models, with directional lighting adapted for raylib. Cover fits the existing collision boxes; buildings are exterior scenery. Keeping the same seed and theme reproduces the scenery as well as the map.

**Redstone Canyon** uses irregular basins and winding trails cut into a continuous rock terrain. Outcrops replace cube cover; the visible triangles also define movement, bullet and sight collisions. The original atlas supplies brown cliff faces and pale faceted caps, with directional terrain shadows and sparse rocks/cacti. Cliffs and cover keep their full generated height. The mine keeps its existing generator. A seed and theme reproduce their own geometry and encounters; canyon enemy counts use the basin's navigable floor area. Free missions in both settings share the miners and altar objectives; the Redstone story search has its own objective. Canyon completion is tracked separately from defeating the mine’s Sheriff. See [mission theming](docs/mission_themes.md) for extension points.

**Isaac Canyon is the default mission choice.** Its ordinary encounters use the Isaac monster catalog; modern canyon floors end with seeded **Ridgeback, Powder Foreman or Storm Marshal** encounters, without immediate repeats. Classic retains its original final monster group. **Western Mine** retains all fifteen original enemy types and the Hollow Sheriff. Random spawn cheats follow the selected theme; the specific-ID cheat remains available in either setting. See [the enemy review and Isaac character comparison](docs/isaac_review.md).

The miners are in chamber 3. The altar is in chamber 4. Both are optional; the town remembers which you completed. Closing the window counts as retreat, or death if the character is already dying. A crash resolves retreat from the last checkpoint on the next launch. Rescues persist even when the expedition fails. Clearing a later expedition with the miners safe repairs the mine's lost prosperity. Resolved objectives never award the same permanent bonus twice; the defeated Mine Sheriff becomes a follow-up encounter on subsequent visits. Modern canyon floors always contain a living guardian, even after a previous expedition succeeded.

Modern canyon expeditions progress through **Outer Washes → Broken Quarry → Abandoned Works → Storm Cut** across their existing 4–8 floors. Room area caps crowding; threat budgets and specialist limits select pursuit, crossfire, charge-lane and guarded-pocket patterns. Later bands add role combinations, faster cooldowns and different breakable/scenery mixes. Ridgeback marks its burrow and charge, becomes vulnerable during recovery, and chains two charges below half health. Fragile cover can interrupt it; dynamite is optional. Story evidence still gates departure. See [floor progression and boss rules](docs/expedition_progression.md).

## Eleven expedition items

| Item | Rule change |
| --- | --- |
| Ricochet Coin | Bullets bounce off walls three times per copy |
| Split Lead | Hits create two angled bullets that can split again |
| Judas Bullet | Every sixth shot pierces six bodies; each copy costs 20% maximum health |
| Powder of Jericho | Kills explode; explosion kills can explode again |
| Hangman's Coin | Ghosts repeat the original projectile specification, including after an explosive kill |
| Scatter Cylinder | Short fan of weaker pellets; combines with Rail into a smaller fan of spikes |
| Rail Spike | Heavy, slower piercing shots with a slower firing cadence |
| Lodestone Sight | Slower projectiles curve toward nearby visible enemies |
| Return Spring | Short outward flight followed by a return; separate body-hit allowance on each leg |
| Blasting Cap | Lower direct damage; one small, potentially self-damaging blast per projectile |
| Fuse Braid | Smaller main dynamite blast leaves two weaker delayed charges that can strike cover again |

Combinations follow explicit rules independent of acquisition order. Split inherits remaining lifetime; ghosts retain the originating projectile's damage rather than explosion damage; sixth-shot effects count primary trigger pulls. Copies stack with documented caps for the new items. Depth, event, projectile and hazard budgets bound branching effects. Classic and the tutorial retain the original five-item reward selection. See [complete item and interaction rules](docs/expedition_items.md), including balance values and reproducible build scenes.

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
| F6 / Shift + F6 | Grant all loaded items / add three keys |
| F7 | Start or replay the final encounter: seeded guardian in modern Canyon, Isaac group in Classic, Sheriff/follow-up in Mine |
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

## Editable mechanics

Gameplay definitions load from [`assets/mechanics`](assets/mechanics) at startup.
The current eleven Western powers, My Shadow and 216 monster definitions use this
registry. These remain DeathWard adaptations; the research catalog has **not**
been imported wholesale or certified as exact Isaac behavior.

| File | Editable values |
| --- | --- |
| [`items.mechanics`](assets/mechanics/items.mechanics) | Stable item keys, names, descriptions, pickup health costs and native effect subscriptions |
| [`builds.mechanics`](assets/mechanics/builds.mechanics) | Damage, projectile speed/lifetime/radius, homing, returning shots, blast values, piercing, ricochets, pellet count, cadence, copy limits and conditional combinations |
| [`pools.mechanics`](assets/mechanics/pools.mechanics) | Armory, shop, boss and bargain item weights for the canyon progression preset |
| [`encounters.mechanics`](assets/mechanics/encounters.mechanics) | Floor-band eligibility, weighted enemy roles, threat costs and per-room limits |
| [`monsters.mechanics`](assets/mechanics/monsters.mechanics) | HP, speed, collision radius, attack cooldown, windup, eligibility, legacy movement/attack/appearance choices and behavior graph selection |
| [`behaviors.mechanics`](assets/mechanics/behaviors.mechanics) | Named enemy states, movement, vulnerability, attack patterns, transitions and enter/exit actions |
| [`rotten_gapers.mechanics`](assets/mechanics/rotten_gapers.mechanics) | Source-timed Rotten subtype selection, force-based pursuit, brood spawning/avoidance and orbit steering |
| [`horf.mechanics`](assets/mechanics/horf.mechanics) | Horf health, opening-band placement, acquisition interval, attack/Shoot/cooldown frames, range and projectile values |
| [`buzz_flies.mechanics`](assets/mechanics/buzz_flies.mechanics) | Fly/Pooter/Attack Fly forces, shot timing, item and dung morphs, live-summon contact policy and seeded destructible dung |
| [`evaders.mechanics`](assets/mechanics/evaders.mechanics) | Hive/Drowned Hive fleeing, population-sensitive spawning, animation events and Flooded replacement |
| [`nest.mechanics`](assets/mechanics/nest.mechanics) | Nest fleeing, randomized spit cooldown, live-spider contact expiry and Trite/Big Spider death choice |
| [`black_globin.mechanics`](assets/mechanics/black_globin.mechanics) | Black Globin accumulated-damage Spider throws, independent pursuing head/creep and wandering brood body |
| [`leper.mechanics`](assets/mechanics/leper.mechanics) | Four Leper forms: evasion/pursuit, batched shedding, creep and gray Gusher mortality; independent Flesh drifting/contact/death shot; final-band placement |
| [`mulligans.mechanics`](assets/mechanics/mulligans.mechanics) | Mulligan family evasion/pursuit, collision-triggered detonation, death payloads and early-floor placement |
| [`prey.mechanics`](assets/mechanics/prey.mechanics) | Prey spawning and thrown death children, Small Leech wet/dry movement, wet-floor placement |
| [`mullighoul.mechanics`](assets/mechanics/mullighoul.mechanics) | Willo orbit, shared attack timing and wall-passing shots; Mullighoul hover, spawning and wet-floor placement |
| [`spiders.mechanics`](assets/mechanics/spiders.mechanics) | Spider/Big Spider stop-and-burst movement, committed targeting, split impulses and early-floor placement |
| [`rock_spiders.mechanics`](assets/mechanics/rock_spiders.mechanics) | Rock/Coal Spider disguise, reveal, skitter counters, falling bounce, fire/death transformations and temporary hot-coal wear |
| [`dannies.mechanics`](assets/mechanics/dannies.mechanics) | Danny/Coal Boy movement, timed rock/coal attacks, owned offspring limits and damage-driven aggression |
| [`hardies.mechanics`](assets/mechanics/hardies.mechanics) | Hardy charge timing, impact stages, projectile clusters, thrown Rock Spiders and stronger death Dip. |
| [`spider_variants.mechanics`](assets/mechanics/spider_variants.mechanics) | Strider rowing, Swarm hop events/weights and wet-floor birth replacement |
| [`long_legs.mechanics`](assets/mechanics/long_legs.mechanics) | Baby/Crazy Long Legs, Sack regeneration, offspring and projectile arcs |
| [`boils.mechanics`](assets/mechanics/boils.mechanics) | Boil/Gut growth, walking variants, blood/Ipecac volleys, explosion immunity and stage pools |
| [`deaths.mechanics`](assets/mechanics/deaths.mechanics) | Weighted or population-scaled death offspring, overkill suppression, child health scaling and regeneration/splitting rules |
| [`bosses.mechanics`](assets/mechanics/bosses.mechanics) | Dedicated boss pools, Peep/Bloat attacks/forms and owned bouncing eyes |
| [`loki.mechanics`](assets/mechanics/loki.mechanics) | Loki/Lokii body counts, teleport and volley timing, fly caps, action weights and boss routing |
| [`segmented.mechanics`](assets/mechanics/segmented.mechanics) | Tuff chain composition, armor, movement, attacks, variant-filtered boss routing and four-way flyer death shots/creep |
| [`shell.mechanics`](assets/mechanics/shell.mechanics) | Shell chains, invulnerable heads, explosive armor, grounded flesh, attacks and doubled boss arena routing |
| [`fly_bombs.mechanics`](assets/mechanics/fly_bombs.mechanics) | Normal and owned Fly Bombs, contact/death ordnance and sparse floor placement |
| [`enemy_bombs.mechanics`](assets/mechanics/enemy_bombs.mechanics) | Hostile regular/Troll/Hot/Bloody Sad/Brimstone payloads, trajectory, fuse, damage and producer immunity; no NPC spawn entries |
| [`rails.mechanics`](assets/mechanics/rails.mechanics) | Authored rail cells, ordinary pits, rocks, restricted entrances and validated wall-to-wall routes |
| [`hornfel.mechanics`](assets/mechanics/hornfel.mechanics) | Partial Hornfel controller: cart/doors, bombs, repeated charge passes, recovery fire waves, dismount/escape and seeded Broken Quarry arenas |
| [`boom_flies.mechanics`](assets/mechanics/boom_flies.mechanics) | Diagonal flyer variants, bone shots, fire/gas/death effects, offspring and ordered replacements |
| [`stages.mechanics`](assets/mechanics/stages.mechanics) | Explicit source-stage mapping for HP formulas within the four expedition bands |
| [`chargers.mechanics`](assets/mechanics/chargers.mechanics) | Charge axes, reflection, steering, stationary recovery, tar, tail armor and death volleys |
| [`companions.mechanics`](assets/mechanics/companions.mechanics) | Friendly charge actors, contact/damage conversion, room lifetime and item-driven contact familiars |
| [`statues.mechanics`](assets/mechanics/statues.mechanics) | Stationary hazard attacks, clear/plate policies, re-entry removal and separate seeded hazard pools |
| [`first_floor_statuses.mechanics`](assets/mechanics/first_floor_statuses.mechanics) | Opt-in Fear/Confusion/Freeze/Slow, Poison/Burn, Shrink and Charm for Frowning Gaper, Gaper, Gusher, Pacer and Horf |

Edit the files, validate, then restart the game. Native development builds read
the checkout's files directly, so balance edits need **no C++ rebuild**. Portable
builds read `assets/mechanics` beside the executable. Browser builds preload the
files into the WASM filesystem: rebuild and redeploy the browser package after
an edit. Files are not watched or reloaded during play.

```sh
cmake --build build --target deathward_check_mechanics
./build/deathward_check_mechanics assets/mechanics
ctest --test-dir build -R 'mechanics_content|item_builds|monster_behaviors' --output-on-failure
```

The first five enemies also read `hit_responses.mechanics`: `hit_response ID MASS PROJECTILE_IMPULSE EXPLOSION_IMPULSE MAXIMUM_SPEED`.
Mass comes from the installed Isaac data; impulse strengths and the speed cap are
DeathWard tuning. Admitted projectile and blast hits add momentum without a stun;
existing terrain collision and Freeze/Slow behavior still apply. Scripted damage
and periodic status damage add no recoil.

All `.mechanics` files in that directory are loaded in filename order. Each
begins with `DEATHWARD_MECHANICS 1`. Fields are whitespace separated; quote names
and descriptions containing spaces. `#` starts a comment outside a quoted value.
Duplicate identities, unknown operations, invalid numeric values and missing
rule/graph/pool references fail validation. Syntax errors include file and line;
cross-reference errors name the definition. The loader builds a complete new
snapshot before publishing it, so a failed load cannot partly replace live rules.

The first five enemy ports expose `Simulation::applyEnemyStatus(id, status, frames)`
and `removeEnemyStatus`. `EnemyStatus::Fear`, `EnemyStatus::Confusion` and
`EnemyStatus::Freeze` use
30-Hz source-frame durations: positive applications add up to the configured cap
(120 by default); negative applications retain at least the absolute duration.
The effects remain independent through headless transformations and pause in
inactive rooms. Other controllers reject application until explicitly supported.
This API does not grant the player a new perk. To inspect it in a native capture:

```sh
./build/deathward --smoke --theme canyon --style original --scene enemy-10.1.0 \
  --enemy-status 1 confusion 120 --enemy-camera-follow --frames 90 --mute
```

Repeat `--enemy-status FRAME fear|confusion|freeze|slow|poison|burn|shrink|charm DURATION` for scripted changes;
duration `0` removes a timed effect; it does not undo permanent conversion. `FRAME` is the capture frame, while `DURATION`
uses the 30-Hz simulation clock. This option requires an isolated enemy smoke
scene. It does not change ordinary gameplay controls.

Freeze holds AI, animation, attack windups and reloads until thawing. Enemies
retain contact damage, ordinary vulnerabilities and room-threat status. Existing
projectiles keep moving, while selected shots waiting for capacity resume after
thawing. `freeze_effect ID CAP RETENTION` enables the effect independently for
a reviewed controller; the native defaults are `120 .01`. Small passive motion
and external impulses still use physical collision. This is ordinary Freeze;
Midas freezing, ice corpses and player item hooks remain separate work.

`EnemyStatus::Slow` uses different duration rules: positive durations add without
the 120-frame cap; a negative duration replaces the remaining time with two
source frames. `slow_effect ID ACTOR_SCALE SHOT_SCALE NEGATIVE_REFRESH` controls
the values, with native defaults `.5 .5 2`. Animation and cooldowns slow while
AI acquisition checks retain their real-time cadence. Movement uses the source
force/friction calculation and physical collision. Newly selected Horf/Gusher
shots retain their own slower flight after the shooter recovers or dies;
already emitted shots keep their previous speed. These configuration scales are
custom tuning controls, not Isaac's API `SlowValue` parameter, which the reviewed
ordinary NPC clock does not read. Other controllers and projectile families are
not claimed supported until reviewed.

`EnemyStatus::Poison` and `EnemyStatus::Burn` have separate duration, tick phase
and damage. `damage_status ID poison|burn CAP PERIOD FIRST_TICK MIN_DAMAGE`
uses defaults `120 20 2 6.4` for these five enemies. Duration expires before the
hit check, so three source frames are needed for the first hit on update two;
later hits are twenty updates apart. Reapplication keeps the original tick phase
and stronger damage, with capped positive accumulation and minimum-duration
negative refresh. Freeze and Slow do not slow periodic damage.

`applyEnemyStatus(id, status, frames, damage, context)` accepts explicit damage
in DeathWard HP units and snapshots producer attribution. Nonpositive power uses
the resolved player build damage for Player/Ally sources, or the configured
minimum otherwise. The native two-HP floor maps to 6.4 under the existing enemy
HP conversion. Both effects use the existing Burning damage channel, preserving
ordinary death/morph and item-event handling. A full event queue retains one due
hit per effect and pauses that effect's clock until admission. This queue policy
and retained producer attribution are local adaptations; arbitrary native
source ancestry and item duration multipliers remain separate integration work.
The CLI uses the default player damage; no new player item is granted.

`EnemyStatus::Shrink` uses `shrink_effect ID CAP TARGET_SCALE APPROACH`, with
defaults `150 .333 .166666667`. Moving enemies flee and new Horf/Gusher attacks
are suppressed; committed shots continue. The model approaches one-third size
on the real 30-Hz clock, including during Freeze or Slow, then gradually recovers.
The installed baseline samples collision size only on initial application and
restores it immediately on removal; visual scale and collision radius are separate.
Walking over a shrunken enemy kills it without contact damage or a headless
transformation. DeathWard uses its existing execution/event pipeline, retaining
one kill intent if the queue is full. These five controllers are supported;
player item producers, champions and other controllers still need review.
See the [Shrink source evidence](docs/reports/isaac-enemy-port/first-floor-batch1/shrink/source/manifest.json)
for native rules and explicit adaptations.

`EnemyStatus::Charm` implements temporary and permanent conversion for those same five.
Positive durations retain the greater of the existing and new duration, without
the 120/150-frame cap. Negative duration permanently converts the enemy.
A converted actor remains charmed, rejects player/ally damage, cannot hurt the
player and stops blocking room completion. Positive reapplication cannot expire
conversion. Converted actors travel between rooms and floors; DeathWard places
them on legal floor, retaining them for retry when capacity or geometry prevents
placement. Floor travel assigns fresh entity IDs. This is an explicit DeathWard
travel adaptation; exact Isaac registry transfer/save behavior is not claimed.
Temporary Charm keeps the enemy a room threat that can still hurt the player. With another eligible enemy present, Gapers pursue it and Horf
aims at it; Gusher/Pacer retain their random movement. Confusion, Fear, Freeze,
Slow and headless transformations preserve their separate rules.

```text
# ID target-period range squared-Charm-penalty contact-period HP-scale offset divisor gain NPC-shot-damage
charm_effect 12.0.0 15 500 1600 3 3.2 110 100 33 19.2
```

Target selection caches the nearest eligible enemy and penalizes another
temporarily charmed target. Physical cover still blocks movement, firing and
contact. Horf/Gusher shots keep their NPC flight and independent player damage;
Charm adds enemy collision and 19.2 enemy HP damage under the default conversion.
Already emitted shots and selected Gusher payloads retain that policy after
expiry. They do not inherit the player's weapon build.

NPC contact uses the source max-HP damage curve and a three-source-frame hit
history. Freeze holds that history; queue pressure retains one selected hit per
actor. Contact is sampled at 30 Hz with swept physical bodies. Arbitrarily long
caller steps do not reconstruct every missing inter-actor physics frame.
No new player item grants Charm yet. Permanent conversion, related item producers
and the cohort's full acceptance remain open. The
[Charm evidence](docs/reports/isaac-enemy-port/first-floor-batch1/charm/source/manifest.json)
and [runtime source review](docs/reports/isaac-enemy-port/first-floor-batch1/charm/source-runtime/manifest.json)
record the native rules and adaptations.

To add a simple power, create another `.mechanics` file, for example:

```text
DEATHWARD_MECHANICS 1
item demo:collectible:1 "Heavy Lead" "COMMON" "Ten extra damage per copy, up to three copies."
end
rule heavy_lead 5 demo:collectible:1 3 always
modify damage add 10 0 per_copy
end
pool armory demo:collectible:1 4
pool shop demo:collectible:1 2
```

This adds a working item and reward entries without expanding the `ItemId` enum.
The key is `package:kind:number`; kinds are `collectible`, `trinket`, `card`,
`pill` and `internal`. Categories keep identities separate; card/pill use slots,
trinket equipment and new art are still separate implementation work. New powers
currently use a generic icon. Retain the shipped `dw:collectible:0` through `10`
keys, which are also referenced by existing native mechanics and old saves.

A rule header is `rule key priority owner stack_cap always|sixth`. A zero cap
uses all owned copies. Rules execute by ascending `(priority, key)`, independent
of pickup order, starting from fresh base attack values. Add
`requires dw:collectible:6 1 -1` for a Rail interaction, or use `0 0` to require
its absence. Requirements are ANDed; `-1` means no maximum. A modifier is
`modify stat operation first extra once|per_copy`, where its operand is
`first + extra * (effective_copies - 1)`. `per_copy` repeats the operation that
many times. Operations are `set`, `add`, `multiply`, `min` (upper bound), `max`
(lower bound), and `ratio`. Ratio inserts a denominator stat before the two
numbers: `modify life ratio speed 14 0 once` gives 14 units of travel.

Supported stats are `damage`, `speed`, `life`, `radius`, `homing`, `return_range`,
`cap_damage`, `cap_radius`, `cap_self_damage`, `pierce`, `bounces`, `pellets`,
`cadence`, `scatter` and `rail`. The last two are flags. Final values are bounded;
integer projectile counts are truncated. There is a 256-copy inventory limit.
Pool weights are integers from 0 to 10000; zero excludes an entry. Each named
pool must have at least two positive entries, and each pair of offers is drawn
without replacement. Tutorial/Classic rewards keep their original restricted
selection. The existing build-inspection layout still targets a small inventory;
paging and custom icons will be needed before exposing hundreds of powers.

Enemy IDs are full `type.variant.subtype` tuples, avoiding decimal-packing
collisions such as `912.100.0` versus `913.0.0`. A `monster` row uses the columns
listed at the top of its file. Speeds are DeathWard world units per second;
timings are seconds, and existing global/floor difficulty multipliers still
apply. Keep the shipped enemy IDs while native encounters and offspring depend
on them. `natural`/`depth` govern legacy selection; the progression preset uses
the external encounter pools. Peep Eye is `68.10.0`; `68.1.0` is reserved for The
Bloat boss. Boss eyes cannot spawn independently from encounter pools.

An encounter entry is `encounter first_band last_band pattern role id weight
cost maximum [members [variant]]`. Bands run from 0 (Outer Washes) to 3 (Storm Cut); ranges are
inclusive. Patterns are `any`, `pursuit`, `crossfire`, `charge_lane` and
`supply_guard`; roles are `basic` or `specialist`. Weight 0 disables a choice;
maximum 0 leaves it limited by the room's threat and population budgets.
Optional `members` defaults to one. Cost buys the entire group; the maximum
still caps individual actors. A group consumes one specialist choice and all
of its actor slots. If it cannot fit, selection skips it rather than silently
spawning part of a group. Two ordinary support slots remain reserved.
Selection is seeded and ignores room graph depth and combat RNG. Duplicate
entries for an overlapping band/pattern fail validation, even across roles.
Each band/pattern requires an unlimited, positive-weight cost-1 single-actor basic and a
positive-weight specialist. Components/hazards cannot enter ordinary pools.
For example, `encounter 1 1 charge_lane specialist 23.0.0 3 3 2` permits up to
two Chargers in Broken Quarry charge-lane rooms. This edits the
existing row; adding it twice is an error. Tutorial, Classic and Mine roster
selection remain separate. Pool inclusion does not certify Isaac behavior.

Optional `variant` restricts an encounter to `standard`, `scorched` or `flooded`; omit it
for any context. In `replacements.mechanics`, `floor_variant band variant weight`
selects a floor context on its own seeded stream. An omitted band defaults to
Standard. Shipped opening-band weights are Standard 2, Scorched 1; this ratio is
DeathWard tuning. Scorched Washes has local ash deposits and a distinct name on
the expedition screen. Band 1 similarly uses Standard 2 / Flooded 1. Flooded
Quarry adds flat damp-sediment decals and marks ordinary combat rooms flooded,
so dry-only fire reactions no longer apply there. These are local environment
adaptations; full source shallow-water art is not reproduced. Geometry, story
sites, roads and rivers keep their seeds.

Conditional substitutions use:

```text
replace_monster 15.0.0 15.2.0 0 3 any 100 1
replace_monster 15.1.0 15.2.0 0 3 any 100 1
replace_monster 29.0.0 54.0.0 0 0 scorched 6000 1
```

Columns are source ID, target ID, first/last band, `any|standard|scorched|flooded`,
chance in basis points (0–10000), and extra reserved threat. Thus I.Blob has a
1% chance to replace a selected Clotty or Clot; normal Hopper has a 60% chance
to become Flaming Hopper in Scorched Washes, the Burning Basement analogue.
`replace_monster 23.0.0 23.1.0 1 1 flooded 5000 1` gives normal Chargers a
50% replacement chance in Flooded Quarry. It does not replace Maggots/Spitties
using their pre-Repentance rule or apply in dry Quarry/other bands.
These are per selected actor, not per room or floor. The source entry's caps and
slots apply; substitutions run once after composition, never recursively.
Extra threat is reserved even on a failed/disabled roll, keeping composition
stable when only chance changes. Overlapping conditions, linked bodies,
formations, hazards and grouped sources fail validation. A cost-1 unconditional
basic with no extra reservation and an unconditional specialist must remain.
Explicit/debug/offspring spawns do not run these room substitutions. Existing
run snapshots and residents never reroll after editing the file or re-entry.

Clotty is currently selected in bands 1 and 3; Clot in 1–3; Grilled only in
Scorched opening pursuit rooms. Delaying Clotty/Clot to Broken Quarry is local
difficulty tuning. Grilled's Chest source route awaits a dedicated encounter.

`formations.mechanics` binds a reusable ring controller:

```text
formation 222.0.0 ring 10 2.4 2.6 1.4 8
```

After the ID and shape come capacity, radius, angular speed in radians/second,
center speed and assembly speed. The installed Ring Fly rule permits ten
members. Speeds and radius are local 3D tuning. The group center pursues the
player while flies rotate in stable slots. Deaths leave gaps; arrivals fill
them or split the largest angular gap without moving existing slots. Group
identity is independent of the founding fly and summoner. Inactive-room state
is retained. Formation clearance respects walls and gates while crossing
interior cover/water. A room too narrow for a ring uses individual flight
pursuit until a valid circle can form. Existing runs retain their immutable
rules when the file changes. Specialized item reactions remain unfinished.

Normal pursuit rooms in Outer Washes through Abandoned Works can select four
Ring Flies for three threat points, capped at four initial members per room.
This does not change the tutorial, Classic selection or native Mine roster.
Capture a ten-fly formation and founder death with `--smoke --scene enemy-222.0.0
--enemy-count 10 --enemy-hit 200 1000 --frames 240 --theme canyon --style original`.
Browser smoke scenes accept `enemy-count=10`; probes expose group centers,
slots and each actor's independent formation ID.

A graph starts with `behavior key initial_state range`, optionally followed by
`projectiles count angular_spacing_radians damage speed`. States use
`state name ready|windup|exposed still|chase|flee|wander|orbit duration incoming_damage_scale`;
`duration` can be `windup` to use the monster's value. Scale 0 gives immunity,
1 gives normal damage. `enter` and `exit` accept `lock_target`, `warning`, `fire`
`reset_cooldown`, or `summon`. A transition is `transition target guard value`; guards are
`always`, `timer`, `attack_ready`, `cooldown_ready`, and `health_below`. Only `health_below` uses
the value (a health fraction); use 0 otherwise. Transitions use file order as
priority, with at most one transition per fixed simulation tick. Close states
with `endstate` and the graph with `end`. Graph state survives room re-entry;
inactive rooms continue ambient animation without attacks.

Graph headers also accept `projectile_aim locked|facing|player` (default locked),
`projectile_life seconds` (default 5), and `wander minimum_seconds maximum_seconds`
(default 0.7–1.8). `motion_speed multiplier` inside a state scales the monster's
movement speed (default 1). `cooldown_ready` fires autonomously without range or
line-of-sight acquisition; `attack_ready` requires both. Gusher uses autonomous
facing shots with a 0.8-second life; Pooters use slow wandering and aimed fire.

Fixed room-axis patterns use `projectile_pattern radial angle_radians`; the
existing aimed fan remains the default (`fan 0`). Radial shots divide a full
circle evenly and ignore player direction. `projectile_curve radians_per_second
fixed|alternate` adds constant world-up curvature; alternating volleys retain
their order through stun and room re-entry. Shot motion survives its shooter.
`projectile_kind bullet|tar|ember|brown` selects the shot presentation; only
`tar` makes a slowing patch. Ember color alone does not create ground fire.
Clotty, Clot, I.Blob, Grilled Clotty and Cloggy use these primitives. Cloggy
currently appears only as one specialist in Broken Quarry crossfire rooms.
Rare I.Blob replacement and full source parity remain unfinished. All angular speeds,
world-unit movement and timings are explicitly local tuning.


`fire.mechanics` defines reactive damage and in-place transformations:

```text
# id condition flame-scale burning-scale target|none trigger health-policy
fire_reaction 15.0.0 dry 0 0 15.3.0 both fraction
fire_reaction 15.3.0 dry 0 0 none both fraction
fire_reaction 29.0.0 any 0 1 54.0.0 flame fraction
fire_reaction 54.0.0 any 0 1 none flame fraction
```

`dry` disables that rule in a room whose `RoomLayout::flooded` flag is true;
`any` applies in either condition. `Flame` and `Burning` are separate damage
channels, distinct from physical damage. Clotty transforms and ignores fire
in a dry room, but takes ordinary fire damage without transforming in a flooded
room. Hopper transforms on flame contact and its flaming form still takes
burning-status damage. `fraction` retains the remaining health percentage and
scaled spawn HP; `current` retains current HP, capped by the new maximum. These
health policies are explicit DeathWard conversions, not verified native values.
The loader rejects unknown targets, cycles, mismatched collision bodies and
known multipart/formation transformations that need a dedicated controller.

A transformation preserves entity ID, position, team, summoner, stun and existing
projectiles. It cancels the old attack and never produces kill rewards. A
compatible hopping form finishes its committed arc before using its new hop
parameters, so transformation cannot drop it into water or cover. The
public `Simulation::addFire` primitive creates a bounded real flame, with separate
player/monster damage targeting. Existing hostile fire keeps the Mine roster's
friendly-fire policy while exposing reactive monsters to flame contact. Monster
contact pulses share a 0.5-second target cooldown; that interval and the 3D
vertical reach are local tuning. Flame visuals follow the actual fire height,
including fire above cover. A burning damage channel does not yet implement
a timed burning status or its item producers.

For isolated captures, repeat `--enemy-flame-hit FRAME DAMAGE` or
`--enemy-burn-hit FRAME DAMAGE`, or use `--enemy-fire FRAME` to create a real flame
at the actor. `--enemy-flooded` sets the room gameplay condition for testing;
it does not generate flooded map art. The browser accepts the corresponding
query parameters, with typed hits written as `FRAME:DAMAGE`. River crossings
retain dry banks and do not automatically set the room-wide flooded condition.
All fire rules participate in immutable mechanics snapshots and their fingerprint.

`hops.mechanics` configures source-derived ordinary/Flaming Hopper locomotion:

```text
# id scale idle hop jump land bonusA bonusB rangeBase rangeBonus overshoot wander
# margin grid arrival nearRange farForce groundFactor retention stuckSpeed stuckAge
# releaseChance localHeight contactDamage [targetVelocityLeadFrames]
target_hop 29.0.0 .1 0 26 4 17 0 0 130 1.3 200 95 5 40 10 30 .05 .1 .7 .75 30 10 1.4 10
target_hop 54.0.0 .1 0 26 5 18 50 0 130 1.3 200 95 5 40 10 30 .05 .1 .7 .75 30 10 1.8 10 5
```

Both forms wander outside their detection range and pursue nearby targets.
At the source rate of 30 Hz, ordinary Hopper uses a strict 130-unit range and no random bonus.
Flaming Hopper adds a uniform 0–50 bonus to range/destination distance and leads
target velocity by 5 source frames. Destination-based inertia replaces the older
fixed-distance/flight-time tuning. Hop lasts 26 frames: normal Jump 4/Land 17,
Flaming Jump 5/Land 18. Source HP 10/20 converts to 32/64. Existing protagonist stats
and conditional replacement odds are unchanged.

A hop commits a destination and predicts a legal landing through the actual
stepped trajectory. Local height/cover clearance permits rocks and water while
preserving full boundaries and closed gates. Projectiles, contact, aiming and
fire use the physical airborne body. Stun and a compatible fire transformation
retain the committed flight; the latter keeps the old motion profile until
landing, then adopts the new one. Source flame conversion preserves HP fraction
without a kill/reward. Room re-entry preserves motion. `--enemy-terrain hop-cover`
provides an isolated crate-crossing capture; WASM accepts the same query value.
The optional final leadFrames value defaults to 0 and accepts 0–60; invalid content
rejects the entire immutable snapshot.

Normal Hoppers are sparse pursuit specialists in bands 0–2. On Scorched Washes,
the external replacement rule substitutes Flaming Hopper in 60% of selected
Hopper slots. The replacement reserves its additional threat cost before rolling.

`enemy_bombs.mechanics` defines five hostile payload profiles. `throwEnemyBomb`
uses real terrain-aware ballistic charges; Hot adds contact damage and lingering
fire, Sad adds a ten-shot ring, and Brimstone adds four cover-clipped cardinal
beams. Player upgrades do not modify them. Aftermath persists through producer
death and room clear, and pauses in inactive rooms. Event/projectile saturation
retains the whole armed burst until capacity recovers. Timings, damage, producer
immunity and hostile fire lifetime are declared local tuning; source-exact fire
durability, bomb pushing and other interactions remain unresolved. These are
components for dedicated Hornfel/Horny Boys encounters. Hornfel now uses them;
Horny Boys remains unimplemented. They are not ordinary enemies. Test with `--smoke --scene enemy-69.0.0 --enemy-bomb hot`
(browser: `?smoke&scene=enemy-69.0.0&enemy-bomb=hot`). See the
[source review](docs/reports/isaac-enemy-port/ordnance/source-review.json) and
[native corrections](docs/reports/isaac-enemy-port/hornfel/native-review.json).
The `normal` profile is a Troll Bomb (`4.3`); `hornfel_normal` is the regular bomb
(`4.0`) used by Hornfel. The `sad` profile uses Bloody Sad Bomb (`4.16`), corrected
from the earlier candidate `4.7`. The verified native selection weights are
6:3:1 for regular/Hot/Bloody Sad are used by the partial Hornfel controller.
Current flight and fuse values remain local tuning.

`rails.mechanics` contains 15 source-backed Hornfel layouts. Its format is:

```text
rail_layout example 2 2
# layout x z rail-variant over-pit
rail_cell example 0 0 0 0
rail_cell example 1 0 0 0
```

Here variant `0` is an east/west straight tile. Every internal port must have a
reciprocal neighbor; ports at the footprint edge become wall entries. Invalid
dimensions, duplicate tiles, disconnected ports and entry routes trapped in
loops reject the entire candidate snapshot. Existing expeditions retain their
immutable content; a successful reload affects a new expedition. Browser builds
require repackaging. `RailNetwork::fit` provides curved paths, distance sampling,
swept movement segments and pit-cell geometry. Native disassembly now supports
centered straight crossing traversal and end-stop reversal; the current curves
and exact turning point remain documented world-space adaptations.
`rail_pit`, `rail_rock` and `rail_closed_entrances` retain additional source
geometry and disabled player entrances. The generator rotates a template when
needed to keep a source pit from blocking its entrance.

`hornfel.mechanics` selects ten normal templates for Standard Broken Quarry.
The generated footprint has rendered rails, grounded-blocking pits, destructible
rocks and separately animated rail doors. Hornfel rides a typed cart, throws
single/double bombs and Brimstone mines at source animation events, and dismounts
with 320 HP when the 768-HP cart phase ends. Killing him gives three extra
dynamite; escape resolves the encounter without that bonus or a kill event.
Eligible paired tracks can also select seven to nine accelerating passes along
the same route, followed by a slower recovery traversal. Its frame-46 fireball
lands and sends four flame trails along the cardinal axes. Cover and pits stop
the trails; emitted fire survives the rider's death and ordinary room clear.
`hornfel_charge` and `hornfel_recovery` configure the drive, cooldowns, ballistics
and fire values. New content snapshots leave an existing run's rules intact.
The native drive constants and animation events are sourced; elapsed cooldowns,
world physics and fire propagation values remain declared local adaptations.
Decoys use separate reserved tracks, hit-count health and six-bomb explosions.
Ordinary entries can also bring two Fly Bomb escorts. They steer around the
living rider, then detach and retain at most 11.2 HP when he exits. Cart loss
keeps the living rider as their parent; his removal releases them without that
exit-only health cap. Surviving flies remain room-clear threats.

```text
# owner child one-in-N count combined-fly/small-bomb-limit player-clearance
# spawn-radius launch-spread-degrees released-HP-cap; zero N disables escorts
hornfel_escort 906.0.0 819.0.0 3 2 4 24 .6 20 11.2
```

`fly_bomb_follow` in `fly_bombs.mechanics` exposes the attached movement forces.
Both rows are validated and reload into new immutable content snapshots. Their
source formulas, local 3D conversions and remaining uncertainty are recorded in
the [escort source review](docs/reports/isaac-enemy-port/hornfel_escorts/source-review.json).
`rail_passengers.mechanics` now configures independent cart traffic plus normal
fireplace and movable TNT payloads, including hit-count damage, ignition and
quiet exits. Five creature payload slots, source fireplace dressing and the
special collectible bonus remain unfinished. The
[passenger source review](docs/reports/isaac-enemy-port/hornfel_passenger_review/source-review.json)
identifies all seven payloads and the separate timed room controller; its
[implementation handoff](docs/reports/isaac-enemy-port/hornfel_passenger_review/implementation-plan.json)
does not enable unfinished payloads in gameplay. The
[partial transport review](docs/reports/isaac-enemy-port/hornfel_passengers/implementation-review.json)
records 58 passing native suites and six focused WASM cases; broader browser
timing fixtures and acceptance remain open. **Regular enemies now take priority
over further boss work.** Source-exact behavior, fight balance and
complete acceptance are not claimed. See the
[charge implementation review](docs/reports/isaac-enemy-port/hornfel_charge/implementation-review.json)
and the preceding [controller review](docs/reports/isaac-enemy-port/hornfel_controller/source-review.json).
The native `authored_rails`/`hornfel_boss` tests and browser probes check the
shared geometry and actual encounter separately.

`bony.mechanics` adds ordinary Bony: cardinal wandering, alignment and sight
acquisition, a stopped throw with a fast aimed bone, and a distinct skeleton model.
Its timing comes from the recovered 13-frame animation (Shoot at frame 4).
Sparse crossfire/supply-guard roles start in Broken Quarry. All 59 native suites
are covered after a roster-coverage test fix, and three focused WASM cases pass.
This remains a partial port; mounted behavior, special item/status interactions
and full acceptance are pending. See the
[Bony review](docs/reports/isaac-enemy-port/bony/implementation-review.json).

`buzz_flies.mechanics` replaces ordinary Fly/Pooter legacy movement with shared
30 Hz buzzing forces. `buzz_shot` supplies Pooter's acquisition, cast, Shoot and
cooldown frames, projectile values and cooldown damping. `dung_morph` exposes the
one-in-N transformation chance; `dung_props` controls eligible floor bands,
maximum pile count, geometry and damage steps. Ordinary dung takes shots and
bombs, remains as a harmless remnant, and can trigger a live Fly-to-Pooter morph
without a kill reward. Placement protects mandatory routes and cache approaches.
Mine, Classic and the tutorial receive no dung. These files use the same immutable
snapshot/restart workflow as other mechanics. Special variants, items/statuses
and complete acceptance remain pending. See the
[Fly/Pooter review](docs/reports/isaac-enemy-port/fly_pooter/implementation-review.json).

`buzz_pair ID FORWARD SIDE` adds an atomic two-shot volley to a configured
buzzing shooter. Super Pooter uses native coefficients `.961 .276`, source
health 8 × 3.2, and the same normal-mode Attack14/Shoot6/delay35 as Pooter.
`buzz_suppress ID ITEM_KEY` binds a registered item to attack suppression while
preserving movement and room-threat participation. The Skatole dependency
currently covers all three Pooter variants and Attack Fly and is outside natural item pools;
its other fly effects remain unfinished. Super Pooter has sparse crossfire
roles across all four bands. The old generic graph remains available for
external compatibility. See the
[Super Pooter report](docs/reports/isaac-enemy-port/super_pooter/README.md).

`buzz_chase ID TARGET_FRAMES FORCE_FRAMES AXIS_SCALE DEADZONE GAIN FORCE CONTACT`
adds cached, distance-dependent pursuit. Attack Fly uses `3 2 .5 25 .08 1.2 10`:
the second planar axis is halved before normalization, preserving its weaker
pursuit along that axis. Its source 5 HP converts to 16. `buzz_item_morph ID ITEM
TARGET` transforms it to a harmless Fly in place when Skatole is owned, clamping
remaining HP without healing or granting a kill. `buzz_contact_summon CHILD
SOURCE RETENTION` marks live Hive summons for contact expiry and `.9` pursuit
friction; flies released on death remain persistent. These profiles are external,
validated and held in immutable snapshots. Sparse pursuit rooms use Attack Flies
across all four bands. Boss-specific children and full status/item parity remain
pending. See the [Attack Fly report](docs/reports/isaac-enemy-port/attack_fly/README.md).

`buzz_volley ID COUNT FORWARD SIDE ...` supplies unnormalized velocity
coefficients for a complete volley (2–16 shots). `buzz_back_split ID ROOT_RADIUS
ANGLE_DEGREES CHILD_SPEED CHILD_DAMAGE CHILD_RADIUS OFFSET LIFE` adds two smaller
backward shots on physical terminal impact. Tainted Pooter uses four source-based
vectors, Attack14/Shoot6/delay63, 240 HP, and backward splits at ±24 degrees.
Timeouts, cancellation and live bounces do not split. Whole volleys/pairs wait
when capacity is exhausted; released projectiles retain their birth configuration
after reload or owner death. Native projectile height curves and its dedicated
Ascent-equivalent encounter remain pending; ordinary floor pools are unchanged.
See the [Tainted Pooter report](docs/reports/isaac-enemy-port/tainted_pooter/README.md).

`evaders.mechanics` supplies a reusable ground evader/spawner:

```text
evader ID SCALE VISIBLE_RANGE HIDDEN_RANGE PROXIMITY_FRAMES STICKY_CHECKS RETENTION WANDER_FORCE WANDER_RETENTION PATH_FORCE ATTACK_RANGE ATTACK_FRAMES SHOOT_FRAME COOLDOWN_FRAMES POP_MIN POP_MAX CROWD_DELAY_MIN CROWD_DELAY_MAX CHILD_ID CHILD_HEALTH
```

Hive and Drowned Hive check proximity every 14 source frames and keep three
positive checks of evasion memory. They wander otherwise. HeadAttack lasts 18
frames and spits at frame 4; the 75-frame timer advances while evading. Room-wide
population, including reserved births, delays further spawning. The bodies have
64/57.6 HP and no contact damage; Drowned offspring have half normal Charger HP.
The native grid search is adapted to canyon navigation; its exact initial
impulse, diagonal bias and tile-cache behavior remain pending. Hive is a sparse
specialist in bands 0–2, with a 50% Drowned replacement in band-1 Flooded floors.
See the [Hive report](docs/reports/isaac-enemy-port/hive/README.md). These profiles
follow the existing immutable snapshot/restart reload policy.

`nest.mechanics` uses the same ground controller, with two optional extensions:

```text
evader_cooldown_bonus ID MINIMUM_EXTRA_FRAMES MAXIMUM_EXTRA_FRAMES
evader_child_contact_death ID
```

Nest adds a uniform 55–74 source frames to the base 75-frame cooldown. Its body
has 64 HP and harmless contact. Shoot at frame 4 emits one full-health Spider
that dies when touching the player, including during player invulnerability.
This policy is stored with the pending birth, so losing the parent cannot erase
it. Death instead releases one equally likely Big Spider or Trite; Big Spider's
later children keep ordinary contact behavior. Post-hit HP at or below −64
suppresses this death offspring. Sparse natural placement covers bands 0–2.
All ground evaders now consume their native initialization update before moving
or attacking. See the [Nest report](docs/reports/isaac-enemy-port/nest/README.md)
for evidence, geometry adaptations and remaining parity limits.

`leper.mechanics` configures all four parent forms and Leper Flesh. Parents use
shared evasion, timed pursuit, source-ordered batched damage/shedding, last-form
creep and a same-entity gray Gusher death branch. Births and accepted damage stay
consistent across split source frames and inactive-room round trips. Flesh uses
floating random pursuit, contact consumption and a predictive death shot. Required
offspring/attacks retain room completion under capacity pressure. All four forms
and independent Flesh have sparse final-band placement. See the
[parent report](docs/reports/isaac-enemy-port/leper-parent/README.md) and
[Flesh investigation](docs/reports/isaac-enemy-port/leper/README.md) for evidence,
external parameters and remaining acceptance gaps.

`black_globin.mechanics` configures three distinct threats. The parent emits a
Spider when HP lost since its previous emission strictly exceeds 16, polling
once per source update. Death separates the head and body without regrowing goo
or a second unconditional Spider. `brain_pursuit` selects direct ground pursuit
instead of ordinary Brain charge while retaining red creep. `headless_brood`
selects Spider production below five room enemies, with a 90-or-180-frame reload.
Health, motion, child identities, thresholds and timing remain external; the
shared ground path helper also serves Gapers. Pending required births retain
room completion. See the [Black Globin report](docs/reports/isaac-enemy-port/black-globin/README.md)
for native evidence, source-stage placement and open fidelity/acceptance work.

`mulligans.mechanics` extends the ground-evader controller with non-spawning bodies:

```text
evader_body ID SCALE VISIBLE_RANGE HIDDEN_RANGE PROXIMITY_FRAMES STICKY_CHECKS RETENTION WANDER_FORCE WANDER_RETENTION PATH_FORCE
evader_detonation ID CHANCE_DENOMINATOR ANIMATION_FRAMES
evader_chase ID CONTACT_CHECK_FRAMES CONTACT_RANGE
death_payload ID DAMAGE PLAYER_DAMAGE RADIUS always|self NORMAL_SHOTS SELF_SHOTS ANGLE SPEED SHOT_DAMAGE BOMB_KEY|-
enemy_bomb_fuse_jitter BOMB_KEY MAX_ADDED_FRAMES
```

Mulligan and Mulligoon can arm a 29-frame detonation on an actual terrain
collision, with a 1/300 check. Mulliboom pursues and checks a four-unit proximity
radius every five source frames. Their 41.6 HP bodies do no contact damage.
Mulligan releases four independent weighted offspring on death unless post-hit
HP is at most -32; this threshold scales source -10 by 3.2. Mulligoon releases
four diagonal shots and a real Troll Bomb, or eight shots plus an immediate
blast when self-detonating. Mulliboom explodes immediately. Pending payloads
retain all effects and prevent room completion until capacity returns.
The Troll Bomb adds 0–29 source frames to its configured fuse; translating its
initialized source count into wall-clock seconds remains provisional.
See the [Mulligan family report](docs/reports/isaac-enemy-port/mulligans/README.md)
for source evidence, seeded placement and remaining parity work.

`horf.mechanics` adds a reusable `head_shooter` controller. Its external row is
`head_shooter ID CHECK_FRAMES COOLDOWN_FRAMES ATTACK_FRAMES SHOOT_FRAME RANGE SPEED DAMAGE LIFE`.
Horf uses source normal-mode timing at 30 Hz, aims at the player's current position
on Shoot, stays grounded and appears in opening-band rooms. The existing generic
aimed-shooter graph remains available for other content. Invalid profiles are
rejected; loading a new snapshot leaves active expeditions unchanged. Hard-mode,
status/knockback and projectile-height parity remain unfinished. See the
[Horf review](docs/reports/isaac-enemy-port/horf_fly/implementation-review.json).

`gurgle.mechanics` now also defines `lob_walker` attack timing/movement and
`lob_projectile` physical flight profiles for Gurgle and Splasher. Source attack
frames run at 30 Hz; damped arcing shots collide with terrain, show ground shadows,
and preserve their explosions under queue pressure. Both enter seeded specialist
pools after the opening band. Crackle now adds `lob_fire_wave` for separate cardinal
fire jets: step interval/spacing/count, lifetime, damage pulse frames, radius,
monster/player damage and visual scale loss. Its sparse placement is limited to
standard Broken Quarry. Movement remains a documented 3D adaptation, and exact
source scheduling/status and full balance/performance acceptance remain open.
See the [lob review](docs/reports/isaac-enemy-port/gurgle_lobs/implementation-review.json)
and [Crackle review](docs/reports/isaac-enemy-port/crackle/implementation-review.json).

`gurgle.mechanics` began the regular Gurgle/Crackle/Splasher family with corrected
stage health and two reusable rules: `source_immunity ID FIRE EXPLOSION` preserves
player/allied/TNT exceptions, and `lethal_morph ID TARGET CHANCE OVERKILL MIN MAX`
uses basis-point probability and delay bounds in seconds. A successful morph
keeps its actor ID and gives no kill reward. As with the other external rules,
validation is atomic and running expeditions retain their existing snapshot.
The [mortality review](docs/reports/isaac-enemy-port/gurgle_mortality/implementation-review.json)
records passing Linux/WASM checks and unfinished movement, attacks and placement.

`black_bony.mechanics` adds the ordinary Black Bony variant: three complete
throw cycles, dark bones aimed at the current player, and an immediate death blast.
The reusable `death_blast` row exposes enemy/player damage and radius; pending
blasts survive event-queue pressure. Sparse cap-one specialists appear from
standard Broken Quarry onward. Native60/focusedWASM6 pass after a test-only
rare-replacement sampling fix; six/six bot mixed-room samples cleared. See the
[Black Bony review](docs/reports/isaac-enemy-port/black_bony/implementation-review.json)
for remaining source and acceptance work.

`loki.mechanics` adds dedicated Loki and Lokii controllers in bands 2 and 3.
Loki emits cardinal, diagonal, then cardinal volleys, an eight-shot ring, or a
Boom Fly; teleports choose and recheck a safe grounded destination. Lokii has
two independently attacking halves with 1120 HP **each** (source 350 × 3.2),
an aggregate health bar and one encounter payout. Its Red Boom Fly cap is shared
across both halves as an explicit local interpretation. Summoned flies survive
the boss and still gate room clear; story evidence still gates the floor exit.
Meat Cleaver conversion, optional support layouts and special encounter routes
remain unfinished. See the [contract and adaptations](docs/reports/isaac-enemy-port/loki/source-review.json).

`boom_flies.mechanics` now separates eight Boom Fly controller variants. Seven
have ordinary seeded routes; Tainted remains a partial Ascent-only controller
without a gameplay route or its source adaptive armor. Bone Fly fires on cardinal
alignment; Dragon/X death fires follow different axes; Sick leaves a gas trail,
eight death clouds and six green shots. Normal and Drowned explode immediately.
The Tainted warning/explosion chain survives ordinary room clear. Skatole,
Beelzebub, champions and source-exact numeric tuning remain unfinished.

```text
# source base HP, stage increment, DeathWard scale
stage_health 25.0.0 8 3 3.2
# band, source stage for first and second floor in this band
source_stages 1 3 4
# source target bands context chance/basis-points extra-cost phase
replace_monster 25.0.0 25.1.0 1 3 any 949 0 0
replace_monster 25.0.0 25.2.0 1 1 flooded 5000 1 1
replace_monster 25.1.0 25.2.0 1 1 flooded 5000 1 1
```

The optional final replacement phase is 0–3 and defaults to zero for existing
rules. One rule can apply per phase, with independent seeded rolls. Later phases
can transform the preceding result; rules in the same phase never recursively
reroll it. Threat reservation includes the most expensive configured branch,
even at zero chance, preserving base composition when only odds change.

Stage health uses the source formula
`(base + increment * (min(stage, 4) + .8 * clamp(stage - 5, 0, 5))) * scale`.
The `monster` HP column must match its stage-one fallback. The mapping preserves
4–8 expedition floors and does not use room depth. Existing runs keep immutable
snapshots; there is no live file watcher. Full configuration and declared local
conversions are in the [source review](docs/reports/isaac-enemy-port/boom_flies/source-review.json).

`bosses.mechanics` defines dedicated encounters separately from ordinary rooms:

```text
boss_native 1 5
boss_pool 1 68.0.0 normal 3
boss_pool 1 68.0.0 cyan 1
boss_pool 1 68.0.0 yellow 1
component_bounce 68.10.0 68.0.0 10 1.5
```

Band 1 is Broken Quarry, the Caves-equivalent part of the expedition. These local
weights retain the existing canyon boss half the time and select Peep otherwise.
Boss selection uses a separate seeded stream; it does not reroll ordinary rooms
or terrain. Tutorial and inactive progression profiles do not use these pools.
`component_bounce` takes component ID, owner ID, contact damage and bomb-deflection
strength. Components require a living matching owner and a unique detached slot;
they cannot be selected as independent threats or generic offspring.

The `boss_peep` row takes boss ID, eye ID, flight duration, jump distance, base/max
apex, creep radius/duration, shot speed/damage, body contact damage, yellow size/
speed multipliers, trail interval/radius and three action weights (creep, ring,
jump). Its monster row supplies HP, body radius, cooldown and windup. Peep's
8-shot ring, 12-shot landing and eye thresholds at two-thirds/one-third health
are controller rules. Cyan starts with both eyes; yellow is 15% smaller, faster
and leaves a continuous yellow trail. Numeric timing, distances, damage conversion
and complete airborne immunity are documented DeathWard adaptations.

`--scene enemy-68.0.0 --enemy-boss-form normal|cyan|yellow` isolates a form.
`--enemy-execute FRAME DAMAGE` bypasses defenses for deterministic cleanup probes;
it is not an implementation of Isaac's named instant-kill items. Browser values
use `FRAME:DAMAGE`. `--scene resident-68.0.0 --resident-seed 0 --resident-floor 2`
captures the actual seeded cyan boss with its owned eyes. As with other mechanics
edits, these definitions enter a new expedition snapshot; current runs retain
their original settings.

Bloat has a separate `boss_bloat` controller. Its fields are boss/eye/Charger IDs,
long-flight duration/distance/base and maximum apex, short-flight duration/apex,
large-creep radius/duration, landing-creep radius, shot speed/damage, contact damage
and three weights (large creep, short hop, long jump). Normal Bloat emits eight
fixed-orientation shots after either hop. Green Bloat emits two arcing explosives
after a short hop or three after a long jump, uses green creep and summons two
Chargers during the large-creep action. Its dedicated pools are bands 2 and 3;
the native bosses retain weight 6, normal Bloat 3 and green Bloat 1 in each band.

These rows must follow their `boss_bloat` declaration:

```text
# owner range radius duration recovery alignment-width damage
boss_lasers 68.1.0 32 .32 .7 1.5 .8 10
# owner flight-seconds gravity spread blast-radius blast-damage live/pending summon cap
boss_ipecac 68.1.0 1.1 12 2 2.8 20 12
```

The laser pair faces fixed world south or both lateral directions, never north,
and has no advance warning delay, matching the reviewed source onset. Solid
cover clips the rays; owner death cancels them. The local socket positions,
alignment width, durations and damage are explicit 3D adaptations. Green shots
use gravity and real impact explosions, with ordinary hostile-damage and soft
demolition rules. They are not an implementation of the player's Ipecac item.

`chargers.mechanics` now defines normal, Drowned, Dank, Carrion Princess and
Level 2 Charger movement. Their shared controller wanders without pursuing and
immediately acquires the configured alignment with line of sight:

```text
# id dash-speed max-dash-seconds alignment-width recovery wander-min wander-max
charge 23.2.0 17 1.7 .8 .8 .7 1.8
# id cardinal|diagonal stop|reflect turn-radians/sec stationary-recovery contact-damage
charge_mode 23.2.0 cardinal reflect 0 .65 10
# id tar-interval radius duration (slowing, never damaging)
charge_trail 23.2.0 .12 .7 2.5
# id tail-center-offset tail-radius, as fractions of the navigation radius
charge_tail 23.3.0 .65 .35
# id count angle-degrees speed damage
charge_death 23.1.0 4 45 7 10
```

Extension rows require a preceding `charge` row for the same ID. Defaults are
cardinal, stop on collision, no steering/pause/trail/tail/death volley and contact
10. Duplicate rows, invalid values and incompatible controllers are rejected.
The examples edit the existing rows; they should not be appended as duplicates.
All movement/timing/geometry values are documented local tuning. Existing runs
retain their immutable configuration; reloading applies to new snapshots.

Normal/Drowned Chargers keep a straight heading. Drowned has 10% more HP and
four fixed diagonal death shots. Dank uses a faster swept, reflecting dash and
pauses before moving again. Carrion Princess acquires diagonally; its rendered
pink tail is a separate hit volume, while head/midsection remain armored even
against piercing bullets. Explosions/fire must reach the tail under the local
3D policy. Level 2 starts cardinally and steers at a bounded rate during its
slower dash. Ordinary stages are normal 1/3, Drowned 1/2, Dank 2, Princess 1,
Level 2 3. Green Bloat can still summon normal Chargers in bands 2/3. Elleech
still needs a dedicated Ascent encounter; these records are partial ports.

My Shadow (`isaac:collectible:433`) is now available through seeded Smuggler
bargains, the local analogue of its source Devil pool. Its delayed shadow
produces friendly `23.0.1` Chargers when enemies touch it, up to sixteen living
allies. Duplicate item copies retain one producer. Allies wander and acquire
aligned enemies, take hostile contact/shots and damaging hazards, and expire
when the player leaves the room. They never seal doors or award enemy loot on
death. Ordinary player bullets pass through them and player dynamite is harmless
to them. Dark bodies and teal rings distinguish allies in Original rendering.

```text
# id outgoing-contact attack-interval hurt-interval incoming-scale lifetime
companion 23.0.1 27.84 .7 .45 .32 room
# item child live-cap lag radius contact-interval-per-enemy
contact_familiar isaac:collectible:433 23.0.1 16 .15 .6 .25
```

Source HP 20 and allied damage 8.7 use the existing 3.2 unit conversion (64 HP,
27.84 damage). The other values are explicit local tuning. Athame, Jumper Cables,
Duct Tape, Eraser, Ace cards, slowdown and Blood Puppy exceptions remain open;
the companion event system is not a claim those items are implemented.
`--enemy-item isaac:collectible:433` grants the real item in an isolated capture;
the browser accepts repeated `enemy-item` parameters. Resident captures reject
these inventory overrides. Native development changes take effect on restart;
WASM requires repackaging, as with the other mechanics files.

For isolated scripted pursuit/ricochet captures, `--enemy-player-at FRAME X Z`
moves the invulnerable spectator to a legal offset from the actor's initial
position. Browser syntax is `enemy-player-at=15:8:-8`; at most 64 moves are
allowed. For example, a Dank capture with `--enemy-player-side above
--enemy-player-at 15 8 -8` lets the committed dash reach the far wall.
Use `--scene enemy-68.1.0 --enemy-boss-form normal|green` and
`--enemy-player-side above|below|left|right|diagonal` for isolated captures.
`--scene resident-68.1.0 --resident-seed 1 --resident-floor 4` selects a real green
Bloat encounter. Browser queries accept the same values.

Grimace hazards have a separate controller and placement pool. Stone, Vomit and
Triple Grimaces stop firing when combat ends but remain solid. Constant Stone
Shooters and Brimstone Heads keep firing until the player steps on all of their
room's pressure plates. Cross shooters alternate cardinal and diagonal volleys;
ordinary variants stop after combat, while the explicit always-on variants
remain experimental and outside normal floor pools. Stone Eyes rotate and fire
flickering beams, stop after combat and disappear after cleared-room re-entry.
Vomit shots are real arcing explosives. Ordinary shots/bombs cannot destroy
these actors; the exceptional-death event path exists, but the named Isaac
instant-kill items are not implemented by this controller.

```text
# id attack clear interval windup damage speed spread range beam-radius beam-duration turn-rate initial-angle remove-on-cleared-reentry
statue 42.2.0 triple combat 3 .3 10 8 .22 32 .25 .08 0 0 0
statue_rooms 1 2500
statue_pool 1 3 any 42.2.0 2
```

`statue_rooms` is a room selection chance in basis points. At most one statue is
added to a selected combat room, separately from its ordinary enemy budget.
Placement checks footprints, entrances, objective paths, roads and river banks;
an optional hazard is omitted when no safe footprint exists. Walking, dodging,
mouse navigation and flight respect its body. These timings, damage conversions,
subtype startup phases and weights are local adaptations, not measured native
constants. Named item interactions, Cross re-entry quirks, full trap-room routing
and remaining hazard families are unfinished.

`--enemy-clear FRAME` invokes real room completion in an isolated capture;
`--enemy-reenter FRAME` leaves and re-enters it. Statue captures provide a plate
at offset `-5 5`; `--enemy-player-at 100 -5 5` presses it through actual movement
state. The browser accepts the same flags as query parameters. Resident captures
reject these lifecycle overrides and preserve the actual seeded hazard, ordinary
enemies and pressure plate. For example:

```sh
./build/deathward --smoke --scene resident-202.0.0 --resident-seed 2 --resident-floor 5 --theme canyon --style original --frames 120 --mute --screenshot /tmp/statue-room.png
```

Gaping Maw and Broken Gaping Maw attract the player and bend both player and
enemy projectiles without firing shots. Broken Maw alternates four seconds of
stronger attraction with four seconds inactive. Room clearance leaves these
fields active; stepping on their room's plates shuts them down. The cycle pauses
while the room is inactive and resumes on return. The original visual style uses
a larger open mouth and inward-moving dust; Broken Maw has visible cracks and
closes during its inactive phase.

```text
statue 236.0.0 attraction plates 1 0 1 1 0 24 .25 .08 0 0 0
# id player-speed projectile-acceleration projectile-speed-limit height active-seconds inactive-seconds
statue_attraction 236.0.0 4 24 40 4 4 4
```

The generic shot columns are unused for attraction. The `24` range is in world
units; force falls linearly to zero at that distance. Attraction is horizontal,
leaving projectile gravity unchanged. Combined fields cancel or add, capped at
the strongest participating configured peak. Faster incoming projectiles keep
their existing speed ceiling. These force/geometry/stacking choices are explicit
3D adaptations; the four-second Broken Maw cycle comes from the source review.
All numeric fields enter the immutable content snapshot. Edits apply to new
expeditions. D10 and other named source-item exceptions remain unfinished.

For projectile checks, repeat `--enemy-shot FRAME player|hostile X Z VX VZ` in an
isolated enemy capture. Offsets are relative to the captured actor and create
actual projectile events. The browser form uses colon-separated values, for
example `enemy-shot=5:hostile:-6:-6:6:0`. Resident captures reject injected shots.

Quake Grimace subtypes `804.0.0`–`804.0.3` keep their source left/up/right/down
axes (`-X/-Z/+X/+Z`). They hop in place and emit a travelling rock front on each
three-second landing. Plates stop future landings; ordinary combat clearance
does not. An emitted wave finishes its course. The visible trailing rocks do
not repeatedly damage the player.

```text
statue 804.0.3 quake plates 3 0 10 10 0 32 .25 .08 0 0 0
# id axis hop-height hop-seconds wave-radius visual-trail-seconds
statue_quake 804.0.3 3 1 .45 .5 .5
```

The generic interval is landing-to-landing; windup and beam columns are unused.
Speed, range, radius, hop shape and base damage are local 3D tuning. Base damage
10 uses the unchanged hostile multiplier of 1.25 on player impact. The wave stops
at the first solid obstruction and cannot hit through cover or into corridors.
It opens an optional cache wall, paying its existing seeded reward once, without
consuming dynamite. It also breaks cracked rocks; ore seams and structural walls
stay intact. This cache interaction is a declared analogue for the source's
secret-wall opening, **not full secret/super-secret-room implementation**.

All four Quakes enter only source-backed band 1, separately from ordinary enemy
budgets. Placement retains their fixed axis, at least six units of clear attack
lane and a reachable plate. Try an actual generated encounter:

```sh
./build/deathward --smoke --scene resident-804.0.0 --resident-seed 9 --resident-floor 2 --theme canyon --style original --frames 210 --mute --screenshot /tmp/quake-room.png
```

Bomb Grimace `809.0.0` supplies a separate throwable bomb. Unlit pickup `5.41.0`
does not add inventory; taking it starts the fuse of armed entity `4.13.0`.
Walk onto it, or click it to approach. While carrying it, mouse attack or arrow
fire throws it; **B** places it (or throws in Throw mode). The HUD bomb control
also works with zero ordinary dynamite. Throwing preserves the fuse, which can
expire while held. The lit-bomb hint and ground ring show the current danger.

```text
statue 809.0.0 supply never 1 0 1 1 0 24 .25 .08 0 0 0
# id replenish fuse radius damage self-damage range flight pickup-radius death-drops
statue_supply 809.0.0 2.5 3 4.5 100 25 12 .7 .75 10
```

These timings and dimensions are declared local tuning. Each supplier tracks its
own unlit stock; taking it schedules replacement even while the previous bomb
is still armed. Exceptional destruction produces ten additional unlit pickups.
The floor-wide limit is 128 supplied bombs; blocked/capped drops retry instead of
spawning inside cover. Ground stock persists across rooms, thrown bombs pause
with inactive rooms, and a carried fuse continues through room/floor travel.
Supplied explosions have their own demolition provenance and spend no inventory.
They do not silently inherit the player's Braid modifier.

This controller is **not in ordinary room pools**. Tuff Twins and The Shell
each create two suppliers in their dedicated encounters. Mother's Shadow escape
still needs encounter work. To inspect the support mechanic in isolation:

```sh
./build/deathward --smoke --scene enemy-809.0.0 --theme canyon --frames 220 --enemy-player-at 30 0 2 --enemy-player-attack 60 10 2 --mute --screenshot /tmp/supplied-bomb.png
./build/deathward_input_tests --supplied-bomb-only
```

Tuff Twins `19.2.0` is a paired segmented boss in **standard Broken Quarry**,
not Flooded Quarry. Each worm starts with six parts, independent stone armor,
and a shared encounter health bar. Supplied bombs strip armor; ordinary shots
then hurt the exposed parts. Both worms and their surviving offspring must be
defeated to clear the room. A severed head does not pay a separate boss reward.

```text
# id chains parts split-min supplier supplier-count spacing armor blast-near blast-far speed exposed-bonus turn-min turn-max contact
boss_chain 19.2.0 2 6 3 809.0.0 2 1.55 15 .25 .14 1.8 .8 1.2 3.4 10
# id armored-child exposed-child head-interval room-cap burst-max body-interval body-shots shot-speed shot-damage
boss_chain_attacks 19.2.0 61.3.0 61.0.0 5 4 2 3 7 7.5 10
boss_pool 1 19.2.0 normal 2 standard
# id angle shot-speed damage creep-radius duration creep-damage (zero = slowing)
death_cross 61.3.0 .7853981634 8 10 2 4 0
```

These values live in `assets/mechanics/segmented.mechanics`. The optional final
`boss_pool` field filters the floor variant. Loading a new mechanics snapshot
changes future runs; an active run retains its existing definitions. Sucker's
four death shots are cardinal; Ink's are diagonal with slowing black creep at
the death position. Their source HP 10 becomes 32 under the existing conversion.

This remains a **partial port**: exact split edge cases, native timings,
named-item exceptions and starting-kit balance remain open. Short rear fragments
currently reattach without losing HP, and armor-stripping explosions do not
spill excess damage into flesh; these are declared local policies.

```sh
./build/deathward --smoke --scene resident-19.2.0 --resident-seed 1 --resident-floor 2 --theme canyon --style original --frames 180 --mute --screenshot /tmp/tuff-room.png
```

`--enemy-player-attack FRAME X Z` drives the real attack input toward an offset
from the captured actor. Browser captures use `enemy-player-attack=60:10:2`.
It is separate from `--enemy-fire`, which creates environmental fire. Generated
resident captures reject both position and attack overrides.

Fly Bomb `819.0.0` now uses a separate pursuing/circling controller and appears
sparsely in standard Broken Quarry rooms. Contact detonates immediately for 40
enemy damage; a shot death drops a real delayed bomb dealing 100 enemy damage.
The delayed bomb remains dangerous after the room clears. Both damage paths
use the existing hostile player multiplier, yielding 12.5 and 25 player damage.

```text
# id ordnance circle-range curve-strength steering fuse radius contact-enemy contact-player death-enemy death-player
fly_bomb 819.0.0 4.14.0 6 .7 4 1 3 40 10 100 20
# child owner count radius angular-speed
fly_bomb_orbit 819.1.0 25.0.0 3 2 1.8
```

`assets/mechanics/fly_bombs.mechanics` holds both monster definitions, controller
values and the ordinary route. Reloading creates a new immutable snapshot;
active expeditions retain their original values. Speeds, fuse and dimensions
are local tuning. The tiny bomb's `4.14.0` mapping is inferred from installed
Small Bomb data, not confirmed by native AI code.

Eternal Fly Bomb `819.1.0` requires a real Boom Fly owner, keeps three orbital
slots, ignores ordinary damage, and drops bombs when that owner dies. This is
**a dependency implementation**: The Horny Boys producer is still missing,
so the variant has no ordinary gameplay pool. Its isolated capture creates the
actual owning group, rather than an unowned invulnerable enemy:

```sh
./build/deathward --smoke --scene resident-819.0.0 --resident-seed 0 --resident-floor 2 --theme canyon --frames 80 --mute --screenshot /tmp/fly-bomb-room.png
./build/deathward --smoke --scene enemy-819.1.0 --theme canyon --frames 55 --mute --screenshot /tmp/eternal-fly-bombs.png
```

Ordnance pauses in inactive rooms, survives ordinary room clear, and is discarded
by explicit debug clear. It neither consumes dynamite inventory nor inherits
player bomb-item modifiers. Native tests cover real explosions stripping Tuff
armor and demolishing authored rocks. Shell now supplies its normal Fly Bomb
offspring route. Fly-item exceptions and full behavior/balance acceptance remain open.

The Shell `19.3.0` appears in **standard Broken Quarry**, in a boss arena with
one doubled axis. Two five-part chains have invulnerable heads, 15-point bone
armor and 112-HP bodies. Explosions strip armor; grounded exposed middle parts
fire aimed triples, while exposed ends spawn Fly Bombs. Attached flesh slows
the chain. Detached groups pursue slowly; lone flesh stays stationary. Both
worms share one reward, and surviving offspring must die before the room clears.

`assets/mechanics/shell.mechanics` exposes the separate Shell controller:

```text
# id chains parts promotion-min supplier count spacing armor speed slowdown steer-range turn-rate flesh-speed settling-speed contact
boss_shell 19.3.0 2 5 3 809.0.0 2 1.55 15 3.5 .6 6 .35 .8 5 10
# id tail-child interval room-child-cap middle-interval shot-speed spread damage
boss_shell_attacks 19.3.0 819.0.0 5 4 2.8 8 .22 10
boss_pool 1 19.3.0 normal 1 standard
```

Movement/attack timings, grounded landing above cover/water and ambiguous split
edge cases are explicit local policies in the [source review](docs/reports/isaac-enemy-port/shell/source-review.json).
Tuff's explosive resistance and exposed acceleration do not apply to Shell.
Special source routes and named item exceptions remain unfinished.

```sh
./build/deathward --smoke --scene resident-19.3.0 --resident-seed 7 --resident-floor 2 --theme canyon --frames 190 --mute --screenshot /tmp/shell-room.png
./build/deathward --smoke --scene enemy-19.3.0 --enemy-segment 2 --enemy-blast 60 100 --theme canyon --frames 100 --mute --screenshot /tmp/shell-flesh.png
```

`--enemy-segment INDEX` selects a real member of the spawned encounter for damage
probes; it never creates a detached test body. Browser probes accept
`enemy-segment=2`. Index 0 is the first head, 1–4 its bodies, 5 the other head.
This option is limited to isolated smoke captures; resident captures retain
the actual generated encounter.

Graph headers can also define `summon TYPE.VARIANT.SUBTYPE count owner_limit
health_multiplier spacing`. The `summon` action queues those children and counts
both live and pending summons against that owner limit. Ownership is separate
from paired-body links and current attack targets. Children survive their
parent unless their own behavior says otherwise; ownership and timers persist
through room departure and return. Global population/generation/placement limits
still apply. Rotten Gaper `10.3.3` uses its dedicated source controller instead:
after more than 60 active frames at 30 Hz, each update has a 1-in-8 spawn chance.
A successful roll resets the counter even at the six-child cap. Small Maggots
start at the parent's position with zero velocity and use their own controller.

`orbit desired_radius acceleration` configures momentum for the `orbit` motion.
The actor accelerates toward a tangential/radial steering direction instead of
instantly aiming at the player. Collision clips actual velocity; occluded
approaches use navigation. Inertia can produce a wider path than the desired
radius. This generic graph motion remains available for authored content.
Rotten Gaper `10.3.5` instead uses source momentum projection, a six-world-unit
steering radius, distance-dependent force and 0.9 velocity retention. Its actual
path can be wider. Default subtype `.0` now selects uniformly among `.1`–`.5`
using the seeded encounter stream. All forms enter Storm Cut only. Pool limits
apply to entries; a default selector can resolve to an already present subtype.
See [`rotten_gapers.mechanics`](assets/mechanics/rotten_gapers.mechanics) and the
[source contract](docs/reports/isaac-enemy-port/rotten-gaper/implementation-contract.json).

For an isolated original-style enemy capture:

```sh
./build/deathward --smoke --scene enemy-14.1.0 --theme canyon --style original --frames 42 --mute --screenshot artifacts/enemy-14.1.png
```

To inspect actual residents from the seeded stage regression without replacing
the room's population, use `--scene resident-ID`. These captures use Rourke's
account, zero-based floor numbers, a temporary save and an invulnerable spectator:

```sh
./build/deathward --smoke --scene resident-15.2.0 --resident-seed 46 --resident-floor 2 --resident-from 15.0.0 --frames 200 --mute
./build/deathward --smoke --scene resident-15.3.0 --resident-seed 1 --resident-floor 0 --frames 130 --mute
./build/deathward --smoke --scene resident-54.0.0 --resident-seed 98 --resident-floor 0 --resident-from 29.0.0 --frames 130 --mute
```

`--resident-from` optionally filters the original selected identity. A missing
resident is an explicit error, not a fallback spawn. Native and browser probes
retain the source tuple, floor context and complete room population. The browser
accepts these same named query parameters with `?verify&smoke&scene=resident-ID`.
Scripted damage, terrain, counts and flooded overrides remain isolated-enemy
options and cannot change a resident capture.

The browser equivalent is `?verify&mute&smoke&theme=canyon&scene=enemy-14.1.0&frames=42`.
`Module.enemyProbe` exposes the selected tuple, state, HP and projectile counts
for browser checks. Missing definitions fail explicitly instead of spawning a
fallback. These captures verify the current implementation, not source parity.

Add `--enemy-hit 30 96` to damage that actor on simulation frame 30. Repeat the
option to test successive phases, for example `--enemy-hit 190 96
--enemy-hit 220 50` to collapse it again and then finish the goo. Hits target the original actor and have
no effect after its true death. Browser captures accept repeated
`&enemy-hit=30:96` parameters. `Module.enemyProbe.actors` reports live children,
their exact tuples, health, maximum health, state, physical radius, position,
velocity and summon owner. These controls require an
isolated smoke scene and keep the temporary-save behavior.

Ground pursuers steer around nearby bodies. A bounded collision pass separates
actual actor positions before projectile collision, sweeps corrections through
terrain, and leaves the player's walking/dodge controls intact. Stationary
shooters stay anchored. Pursuit navigation checks body clearance at corners;
crowded narrow approaches use deterministic yielding. Intangible actors,
linked formations and room hazards still need their own reviewed collision
policies. Contact skins, inverse-area pushing weights and steering/yield values
are DeathWard adaptations, not recovered Isaac engine constants.

Flying definitions use separate navigation: they cross interior outcrops,
props and deep water, while enclosing cliffs, sealed gates and the active room
boundary remain solid. Their actual position and hitbox rise over cover; mouse
picking and aimed shots follow that height. Arrow fire keeps its horizontal
bearing and adjusts elevation toward the nearest visible body along that line.
Homing can turn vertically. Grounded offspring are not allowed to spawn in deep
water where a flying parent died. This is a 3D interpretation of airborne grid
collision, not Isaac's original height system. Per-family transformations,
formations and item interactions still require their own implementation checks.

Use `--enemy-terrain cover` with an isolated enemy smoke scene to add a two-metre
crate. `--enemy-terrain river` finds a real seeded interior channel with safe
banks and no ford along the test route. Browser smoke scenes accept
`&enemy-terrain=cover` or `&enemy-terrain=river`. The probe includes actual actor
height, starting position and flight/water collision results.

Death recipes start with `death key`; `overkill -25` suppresses offspring when
**post-hit** health is at most -25. Omit it for no overkill suppression.
`offspring_layout radial|perpendicular spacing` chooses child offsets; blocked
offsets still use safe placement. Each `outcome positive_weight` contains zero
or more `offspring TYPE.VARIANT.SUBTYPE minimum maximum health_multiplier`
lines and ends with `endoutcome`. An empty outcome means no child. End the
recipe with `end`, then bind it using `death_for TYPE.VARIANT.SUBTYPE key`.
One outcome is selected per death. Each outcome is limited to 64 potential
children, additionally bounded by the existing population/placement limits.
Voluntary self-detonation bypasses overkill suppression. Cheat execution skips
death offspring. New content snapshots see edits; existing expeditions retain
their loaded rules.

The optional `population_offspring BUDGET CROWD_SCALE CAP_MIN CAP_MAX RADIUS_MIN RADIUS_MAX`
changes a death recipe to independent weighted draws. The draw count is
`ceil(BUDGET / (1 + CROWD_SCALE * room_population))`, including reserved births.
A nonzero cap range supplies a random upper bound; `0 0` disables that cap.
Each outcome must contain exactly one child. Hive uses budget 4, factor .2 and
Fly/Attack Fly/Pooter weights 7:3:1. Drowned Hive adds a cap of 1–2 and produces
half-health Drowned Chargers. Their overkill threshold is -64 local HP, converting
the recovered source threshold -20 by the same 3.2 scale as their health.
Reserved children retry capacity or safe placement and keep the room sealed;
room reset and debug execution clear pending births. The existing offspring
generation bound still applies. Live-spit contact behavior is captured with the
request so it survives removal of the summoner; death children do not inherit it.

`regrowth TYPE.VARIANT.SUBTYPE health_retention goo_fraction delay minimum_max_health split_limit`
configures collapse and regrowth for legacy actors. Maximum health decreases
once per collapse, down to its floor; goo has the configured fraction of that
reduced health. Finishing goo kills it. A positive split limit also creates a
second goo body with the same reduced health and remaining split budget.
Graph actors need explicit collapsed-state support before using this rule.
The shipped fractions, delays, mixture weights and split cap are documented
DeathWard tuning unless a family report establishes recovered values. Older
overkill profiles retain source numbers in **DeathWard health points**; the Hive
profiles above explicitly convert their threshold with their HP scale.

This is an extension foundation. The existing event queue still bounds effect
chains and snapshots projectile properties. Native `split`, `powder`, `ghost`
and `cap` hooks can be attached to new items; their algorithms, Fuse Braid,
boss-specific logic, most legacy AI and some numeric constants remain C++.
Further mechanics such as composable beams, shared boss health, additional formation shapes or active items need
additional engine primitives and tests before graphs/rules can compose them.

Each expedition keeps an immutable mechanics snapshot across floors. Run records
include its content fingerprint and namespaced item keys. Save format 7 reads
formats 1–6, converts legacy item numbers, and preserves unknown package keys in
history. Older executables cannot read format 7. The fingerprint identifies the
loaded text; it is not a replay guarantee or a full live-combat save.

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

The core CTest suites need no graphics display or audio device. The mechanics suite covers invalid definitions, file-only items and combinations, immutable snapshots, event provenance, full enemy IDs, graph phases and old/new inventory save formats. Audio presentation checks cover confirmed cues, priorities, bounded queues and unchanged gameplay randomness. Mission-theme checks cover seeded selection, organic terrain reproduction, clear routes, sealed entrances, safe enemy placement, surface collision and persisted canyon checkpoints/history. `deathward_input_tests` exercises mouse controls, keyboard-only play and function-key cheats through raylib's input system in a hidden window. Use `--hud-only` for compact-control hitboxes, item inspection, modal input guards and danger-warning priority; it saves HUD and build-detail captures in `artifacts/`. Use `--keyboard-only` for hub/setup navigation, menus, dynamite over the HUD, directed throws, camera controls, key-locked doors, purchases, rewards and evidence-gated floor exits; it saves exit and controls captures in `artifacts/`. `deathward_player_model_tests` checks the packaged mesh, texture, all nine clips, blending, simulation timing, root-motion removal and resource cleanup. `deathward_western_assets_tests` checks the scenery atlas, glass, scale, collision alignment, route clearance, seed reproduction, canyon terrain/mesh alignment and resource cleanup. `deathward_occlusion_tests` compares whole-object transparency in towns and canyon wall sections at different zoom levels, checks that translucent scenery remains visible, verifies restoration and unchanged collision, and saves before/after captures under `artifacts`. `deathward_audio_tests` exercises the real audio device, packaged sounds, voice limits, panning, pause/mute, crossfades, looping, preferences and cleanup; it captures and silences its output unless passed `--audible`. The graphics suites require an X11/OpenGL display, as do the render checks; `xvfb-run` is also suitable where available. Input checks use a temporary campaign. Scripted render checks use a fresh temporary campaign by default. An explicit `--save PATH` opts into that campaign.

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

## Research and design reports

The [complete Isaac mechanics reference](docs/reports/isaac-mechanics-reference-2026-10-25.html)
is a searchable offline catalog of items, trinkets, consumables, enemies, boss
components, HP scaling and documented interactions. It includes a DeathWard
implementation plan, source/version distinctions and explicit unknowns. The
[structured dataset](docs/research/isaac-mechanics-reference.json) and
[implementation review queue](docs/research/isaac-implementation-backlog.csv)
support the next implementation phase; collecting a record does not mean its
behavior has been ported or verified in gameplay.

The [full enemy port plan](docs/isaac_monsters.md#full-enemy-port-plan--2026-10-25)
audits the current runtime against all 653 researched enemy/boss/component
records and proposes placement within the existing expedition difficulty bands.
Its [review queue](docs/research/isaac-enemy-port-review.csv) and
[structured stage evidence](docs/research/isaac-enemy-port-plan.json) distinguish
candidate placements from approved spawns and include the Peep Eye/Bloat ID
conflict. This newer code audit supersedes the old report's runtime-coverage
snapshot; no gameplay changes are made by generating the plan.

The [Isaac expedition study](docs/isaac_expedition_study.md)
([offline HTML report](docs/reports/isaac-expedition-study-2026-10-24.html)) records
the local Repentance data analysis and proposals for build-changing items,
floor identities and canyon bosses, optional rooms and resource choices, and
bomb-destructible objects. It includes evidence, limitations and implementation
milestones. These are design proposals, not implemented gameplay.

The [reference directory guide](reference/README.md) locates the preserved
extracted files, disassembly and integrity manifests. The source-game files are
stored locally outside the game's assets and build output; Git excludes that
reference copy. Aggregate measurements and the analysis tools accompany the report.

## Code map

- `src/combat`: fixed-step simulation, 3D collision, AI, spatial broad phase and event budgets.
- `src/content`: validated external mechanics, stable identities, build rules and behavior definitions.
- `src/items`: resolved weapon builds, weighted reward pools and native event effect handlers.
- `src/world`: seeded dungeon geometry, persistent world state, consequences, history and atomic save transactions.
- `src/core`: application flow, input, math and deterministic RNG.
- `src/render`: 3D rendering, instanced seeded scenery, player animation blending and menus; no combat rules.
- `tests`: gameplay and persistence contract checks.

The [design brief](weird_west_3d_prototype_agent_brief.md) describes the wider experiment. This implementation extends Milestone 1 with the Western and monster rosters and seeded room networks. The 25-item catalog and three expeditions remain future content work.


### Prey and Small Leech configuration

[`prey.mechanics`](assets/mechanics/prey.mechanics) adds exact IDs 817.0.0 and
810.0.0. `swimmer` configures source scale, wet acceleration/cap/retention/speed,
dry retention/hop chance/impulse range, animation duration/Land event, visual
hop height, contact damage, bounce and three edge margins. Small Leeches swim
in flooded or river-crossed rooms and hop on dry ground. Swimming preserves
solid obstacles and room boundaries while allowing water crossings.

Within a death rule, `population_adjustment OFFSET MINIMUM` changes the
population-based offspring count before its optional cap. Prey uses −1 and 1.
`offspring_launch RADIUS SCATTER HEIGHT_SCALE INITIAL_HEIGHT INITIAL_VELOCITY
GRAVITY PLANAR_MULTIPLIER` defines an airborne birth; its children must have a
swimmer controller. Prey uses `8 1 .1 -10 -8 .7 .04`, producing a 23-update
flight at 30 Hz. These values are copied into each pending birth, so retained
requests keep their launch policy. Births wait for capacity and a validated
3D arc/landing; airborne children ignore projectile and body contact, with
normal collision restored on landing. Area damage remains effective.

These external profiles use the existing immutable mechanics reload system.
Invalid ranges, duplicate profiles, conflicting controllers and unsupported
thrown-child types are rejected. The [Prey report](docs/reports/isaac-enemy-port/prey/README.md)
distinguishes recovered values from local navigation/visual adaptations and
remaining parity work. These are partial regular-enemy ports.

### Willo and Mullighoul configuration

`mullighoul.mechanics` adds regular enemies 808.0.0 and 817.1.0. The `willo`
row supplies, in order: source scale, radius, ellipse ratio, angular step per
30 Hz update, tracking gain/cap, player-velocity carry, settled range, random
attack denominator, Attack/Warn/Shoot frames, target lead frames, projectile
planar speed/damage, height/upward speed/gravity/retention/radius/lifetime, and
wall-collision bypass. Attack timing must satisfy `Warn < Shoot < Attack`.
Willos redistribute their orbit when membership changes, retain the shooting
actor's committed slot, and allow one attack at a time. Capacity limits retain
the pending shot. Wall-passing projectiles still hit the player and ground.

`evader_hover ID HEIGHT` follows an existing `evader` row and enables movement
over water while retaining solid-obstacle and room-boundary collision. The
height must be positive and no greater than two local units. Mullighoul uses
0.6. This is distinct from unrestricted flight: ordinary Willo orbits ignore
grid scenery, while Mullighoul routes around it.

The existing population death policy gives Mullighoul three Willos alone,
two with two other actors, and one with five. Extreme overkill suppresses the
births. Both identities use sparse wet band-1 pools. File loading validates
these profiles, and active simulations retain immutable content snapshots;
reloads affect subsequent simulations. See the
[Willo/Mullighoul report](docs/reports/isaac-enemy-port/mullighoul/README.md)
for recovered source rules, local scales and incomplete interactions.

### Spider movement and grounded offspring impulses

`spiders.mechanics` configures Spider (85.0.0) and Big Spider (94.0.0) with the
same controller. A `spider` row takes: source scale, retention, movement force,
idle threshold, wandering counter, acquisition range minimum/maximum, target
lead in source frames, wandering distance minimum/maximum, arrival radius,
stuck-speed threshold, narrow-gap check denominator, contact damage, and target
margins left/top/right/bottom. Distances and movement force use source units;
contact damage uses local units. All event clocks run at 30 Hz inside the
existing 60 Hz simulation. A burst keeps its selected destination; it does not
continuously steer toward a moving player.

`offspring_impulse SPEED` belongs in a death rule before its outcomes. It applies
an outward velocity in the configured offspring layout, measured in local units
per second. It cannot be combined with `offspring_launch`. Requests retain their
impulse and keep the room sealed if capacity or legal placement delays birth.
Big Spider uses two perpendicular offsets of one local unit and speed 30, with
full-health ordinary Spider children. These are grounded births. The ordinary
overkill condition still suppresses the entire payload.

Both profiles are validated at load time and retain the existing immutable
snapshot/reload policy. Their [implementation report](docs/reports/isaac-enemy-port/spiders/README.md)
records source evidence, adaptations, seeded placement and remaining gaps.

### Strider, Swarm Spider and all-birth replacement

`spider_variants.mechanics` defines independent `strider` and `swarm_spider`
controllers. Strider exposes movement scale, glide retention, rowing force range,
ready/chase/wander probability denominators, stroke/Row event frames, angular
tracking, visual height and contact damage. Its 20-frame stroke applies one
impulse at frame 6 and uses water-crossing collision while respecting solid cover.

Swarm Spider exposes scale, ground retention, two distance thresholds, turning
and early-completion probabilities, visual hop height, damage and player-objects
collision. Three distance tiers each supply short/medium/long weights; each hop
then supplies total/Jump/Land frames, speed range and angle spread. The source
10/12/18-frame hops keep their ground collider. The player-objects policy also
prevents enemy crowd separation and fireplace-body contact damage; it does not
grant immunity to player flames, burning status, bullets or explosions.

`replace_spawn SOURCE TARGET FIRST_BAND LAST_BAND VARIANT` is a deterministic
final replacement in phase 3. It applies to both floor residents and every direct
or queued birth, before stats and placement. Unlike random `replace_monster`, it
can replace an entire grouped entry without splitting the group. Chained/cyclic
spawn replacements are rejected. The wet band-1 rule replaces ordinary Spider
births with Striders, including Big Spider children and their retained impulses.

These profiles use the existing immutable snapshot and reload policy. See the
[Strider/Swarm report](docs/reports/isaac-enemy-port/spider_variants/README.md)
for source evidence, local adaptations and remaining gaps.

### Long Legs and regenerating Sack profiles

`long_legs.mechanics` contains the four Baby/Crazy Long Legs identities and the
Sack child. `long_legs` selects flee/lay or chase/volley behavior, source attack
frames, event timing, population checks, child/twin rules and physical shot arcs.
`sack` configures initial HP, regenerative acceleration, population-gated attacks,
throw targeting and its child. Source-stage HP uses the existing `stage_health`
directive. Profiles are validated and reloaded through the same immutable mechanics
snapshots as the rest of the roster. See the [Long Legs report](docs/reports/isaac-enemy-port/long_legs/README.md)
for source evidence, local adaptations and pending parity work.

### Boil family profiles

`boils.mechanics` replaces generic Boil, Gut and walking-family behavior with
source-derived attack events and physical projectiles. A `boil` row selects
stationary growth or wandering, its payload, growth/attack cycle, movement and
throw height. A `boil_projectiles` row supplies volley counts, speed/scatter,
height/falling fields, aimed multipliers and explosion values. The existing
`sack` directive remains compatible and shares the cycle implementation.

Stationary variants start at 7/20 source HP and recover; walkers start full and
never regenerate. All six have source-aware explosion immunity. Values use the
same validated immutable reload snapshots as other mechanics: rejected content
cannot partially modify an active run. See the [Boil family report](docs/reports/isaac-enemy-port/boils/README.md)
for source evidence, local conversions and unfinished acceptance gates.

### Tainted Hopper landing rings

`tainted_hopper.mechanics` binds the shared `target_hop` controller to a four-stage
`hop_rings` sequence. Its first three landings chain into the next hop; the fourth
finishes recovery. The rings contain4/6/8/12 projectiles with physical falling
flight. A sparse band3 encounter rule adds at most one initial Tainted Hopper.

The `hop_rings` fields are monsterID,damage,lifetime,radius,height,minimum and
maximum upward velocity,gravity,flight retention,stage count,then count/speed
pairs. Invalid counts,speeds,flight ranges or incompatible bindings reject the
whole content snapshot. Changes use the existing immutable reload mechanism.
The [report](docs/reports/isaac-enemy-port/tainted_hopper/README.md) separates
source behavior from3D adaptations. Shared adaptive armor is now implemented
for this regular variant; the four-stage attack still has open acceptance gates.


### Regular enemy adaptive armor

`assets/mechanics/adaptive_armor.mechanics` binds the installed-source armor
algorithm to seven existing regular variants. Each source30Hz tick averages
raw accepted damage over up to120 frames, including the current batch and quiet
frames. The soft cap is maximumHP/strength. Above the cap, all ordinary hits in
that batch use `r + max(minimum - correction*r, 0)`, where `r=cap/recentDPS`.

```
adaptive_armor 29.3.0 30 120 .09 .18
```

Fields are exact monster ID, strength, history frames, minimum and correction.
Strength must be positive and at most1000; history is1–600; minimum and correction
are in0–1 with correction at least minimum. Bindings require ordinary independent
bodies, excluding registered bosses, components, companions and room hazards.
Invalid files reject the whole reload. Existing simulations retain their immutable
content snapshot; new simulations use the successful reload.

Real dynamite and physical source Bomb bodies bypass reduction while contributing
to recent damage. Piercing bullets and arbitrary explosive effects do not imply
that bypass. A separate internal flag skips both history and scaling. Pending
hits preserve their event context and chain budget through room suspension and
resolve once; execution cancels them. The protagonist's HP and damage are unchanged.

See the [source and implementation report](docs/reports/isaac-enemy-port/adaptive_armor/README.md).
Shared component/boss armor, source protection/version reconciliation and full
per-enemy acceptance remain open. Adding this mechanic does not certify seven
complete enemy ports.

### Leaper high jumps

`assets/mechanics/leapers.mechanics` extends `target_hop` with an occasional
committed high leap. Normal Leapers fire a four-way cardinal shot only on the
high landing. Sticky Leapers leave non-damaging slowing creep on ordinary and
high landings, with six scattered physical shots on the high landing. Their
bullet tint is independent of impact behavior, so shots do not create extra tar.

The `leaper` fields are ID, selection denominator, Up duration/Jump frame,
Down duration/Land frame, progress step, local arc height, legal-target search
radius, Sticky flag, shot count/speed/damage/life/height, upward velocity range,
gravity/retention, base radius, size base/step/jitter, small/big creep radii and
creep duration. Frames use source30Hz. Invalid phase ordering, flight values or
conflicting landing controllers reject the entire immutable reload snapshot.
Existing runs keep their loaded values; new runs use successfully reloaded data.

Normal Leapers now occupy sparse middle-floor bands1–2; Sticky Leapers occupy
band2. Their source HP converts to80 and89.6. Ground landing markers communicate
the committed target while Original procedural visuals distinguish the variants.
The [source review](docs/reports/isaac-enemy-port/leapers/source-review.md) records
source evidence, explicit3D adaptations and remaining acceptance work.

The [Vis beam-body batch](docs/reports/isaac-enemy-port/vis/implementation-review.md)
adds dedicated Vis, Double Vis and Scarred Double Vis controllers. Profiles in
`assets/mechanics/vis.mechanics` define cardinal wandering, acquisition, animation
events and complete one/two/four-beam attacks. Beams follow their owner and damage
other enemy types; fading beams are currently harmless as a documented adaptation.
The configured local width preserves canyon readability. Original visuals and the
100HP/24-damage starting character remain intact. The final six acceptance gates
remain unfinished; this is an implementation batch, not a claim of full Isaac parity.

The [Knight/Pon family](docs/reports/isaac-enemy-port/knights/source-review.md) uses
`knight`, `knight_random`, `knight_impact`, `knight_fire_wave`, `mask_armor`,
`linked_remnant` and `landing_creep` profiles in `assets/mechanics/knights.mechanics`.
They configure movement, armor, reflection, linked offspring and ground effects.
Content reload creates a validated immutable snapshot; existing runs retain their
current snapshot. Full behavioral/visual/balance acceptance is still open.

The [Leech family](docs/reports/isaac-enemy-port/leeches/source-review.md) uses
`leech` profiles in `assets/mechanics/leeches.mechanics`: flying cardinal wander,
committed charge, native momentum/timing, contact damage and optional owned fly.
Kamikaze and Holy use immediate `death_blast` profiles. Holy's retained orbiter
is canceled if its parent dies before it can spawn, and removed with the parent.
Content reload validates a new immutable snapshot. Full status, creation-path,
visual, balance and performance acceptance remains open.

The [Dople/Evil Twin family](docs/reports/isaac-enemy-port/dople/source-review.md)
uses `mirror` profiles in `assets/mechanics/mirrors.mechanics`. They configure
weapon-delay-driven attacks, the Twin's cooldown, projectile spread and motion,
and reflected movement inheritance. Both use room-centered positioning and zero
contact damage; the late-floor planner allows one mirror enemy per room. Immutable
reloads retain the existing run's snapshot. Native spike/status/physics and full
visual/balance/performance parity are still open.

The [Guts family](docs/reports/isaac-enemy-port/guts/source-review.md) uses external
`guts`, `guts_charge` and `guts_creep` profiles in `assets/mechanics/guts.mechanics`.
They control contour movement, source-frame timing, charge and independent ground
trails. The seeded `dank` and `scarred` encounter contexts preserve Original canyon
rendering while gating Slog and Scarred Guts replacement. This is an in-progress
port, with recorded Linux/WASM checks and explicit remaining parity gaps.

The [Chubber batch](docs/reports/isaac-enemy-port/chubber/implementation-review.md)
adds its owned returning attack body, with external tuning in
`assets/mechanics/chubber.mechanics`. It passes terrain, slows before returning
toward its moving parent, blocks ordinary/spectral shots, and allows piercing
shots through. Zero HP means invulnerability, without independent loot or a
room-completion requirement. All four Vis bodies have sparse seeded placements
in their reviewed floor bands. Exact common-physics timing, missing item/status
interactions, broader visual coverage, balance and performance remain open.

The [Lump controller](docs/reports/isaac-enemy-port/lump/source-review.md) uses
`lump` and `lump_shot` in `assets/mechanics/lumps.mechanics`. These expose its
30Hz attack/burrow timing, relocation constraints, chance denominators, anchor
motion and three-projectile flight. Hide remains vulnerable until its animation
ends; the buried body is invisible and intangible but remains a room threat.
Band3 placement follows its Womb-family source habitats. The previous position
is retained when a room has no valid relocation candidate. Full native status,
visual, balance and performance acceptance is still pending.

The [MemBrain family and Cyst](docs/reports/isaac-enemy-port/membrains/source-review.md)
use `membrain`, `membrain_shot` and `guts_shot` profiles in
`assets/mechanics/membrains.mechanics`. The parents wander, remain damageable
through their visual hop, and emit eight shots at Attack frame29. Dead Meat
uses a slower rotated ring that repeatedly reflects from lateral solids until
landing. Death produces two real Brains, Guts or Cysts; retained births prevent
premature room completion. Cyst rolls while firing every31 source updates.
Profiles include HP, timing, flight, damage, offspring and seeded late-floor
placement. Linux/WASM evidence and explicit remaining fidelity gaps are linked
from the batch checkpoint; this is still an in-progress port.

The [Adult Leech](docs/reports/isaac-enemy-port/adult-leech/implementation-review.json)
uses `adult_leech`, `adult_leech_burrow` and `adult_leech_shot` profiles in
`assets/mechanics/adult_leeches.mechanics`. Its horizontal charge steers slightly
vertically; strong wall hits release12 shots. Below66%HP it can burrow once,
then fall near the player and release10 shots. Source animation events control
collision and warning phases. The hidden body has no health bar or hover target.
It appears in late-band charge-lane rooms; natural witness seed5/floor4/room1
uses zero-based indices. This remains a partial port; special creation paths,
full status fidelity, balance and performance acceptance are still open.

The [Dinga family](docs/reports/isaac-enemy-port/dinga/implementation-review.json)
uses `dip`, `squirt`, `membrain`, `membrain_shot` and `dinga` profiles in
`assets/mechanics/dinga.mechanics`. These expose movement, attack timing,
stage HP, projectile flight, living/death offspring and floor placement. Dip
makes random dashes; Squirt winds up before a committed slide. Dinga's hop
spawns Dips or brown shots and pushes nearby Dips. Its death chain produces two
Squirts and then four Dips, with retained births preventing premature room clear.
Native/WASM checks cover these ordinary paths; full status, item, audiovisual,
balance and performance fidelity remain open.


The [Dip and Squirt variants](docs/reports/isaac-enemy-port/dip-variants/implementation-review.json)
add Corn217.1, Brownie Corn217.2, Big Corn217.3, Dank Squirt220.1, Drip870
and Splurt871. Profiles live in `assets/mechanics/dip_variants.mechanics`.
Corn has stronger random impulses; Brownie follows the installed ordinary
controller despite a conflicting wiki description. Big Corn shoots a predictive
corn projectile on death. Drip chains short bursts and sometimes aims at the
player. Splurt charges twice, retargeting during its shorter second windup,
and releases two moving Drips. Dank Squirt leaves slowing black creep and
releases two real Clots. Big Corn, Drip and Splurt cross flooded pits while
retaining solid-wall collision, including during offspring placement and crowd
separation. Deferred deaths/births keep the room sealed until resolved.

`slide_swim`, `drip_chain`, `splurt`, `slide_creep` and `slide_death_shot`
extend the existing `dip`/`squirt` profiles. Configuration reload creates a new
validated content snapshot; existing simulations retain their old snapshot.
Timing, movement, HP, shots, creep and seeded encounter weights are external.
Try `./build/deathward --smoke --scene enemy-871.0.0 --theme canyon --style original --frames 480 --mute` for the double charge. Natural witnesses and Linux/WASM
evidence are recorded in the [batch report](docs/reports/isaac-enemy-port/dip-variants/checkpoint.json).
These remain partial ports: source status/item/control interactions, full
creep-effect parity, alternate production and final acceptance remain open.


Ordinary Gapers (10.0/10.1/10.2) use `gaper` profiles in
`assets/mechanics/gapers.mechanics`. Profiles expose source-timed acceleration,
friction, head and walking frames, contact damage and HP. Frowning eyes open
once a ground path becomes clear, with the speed increase starting on the next
head frame. `lethal_morph_roll` and ordered `lethal_morph_choice` rows in
`deaths.mechanics` configure same-entity Gusher/Pacer transformations. These
keep their entity and ownership, and do not pay a premature kill reward.

Scorched Washes can replace either ordinary parent with Flaming Gapers; other
opening contexts use ordinary/Frowning bodies. Existing simulations retain
immutable configuration snapshots when files are reloaded. See the
[Gaper contract](docs/reports/isaac-enemy-port/gaper/movement-contract.json)
for source evidence, external field order and remaining acceptance gaps.

Small Maggots (853.0.0) use `small_maggot` profiles in
`assets/mechanics/small_maggots.mechanics`, both as offspring and as late-floor
residents. They have 32 HP, a seeded 10–39-frame initial delay, retained momentum,
curving movement and separate awareness/line-of-sight checks. The profile exposes
distance conversion, friction, force range, pursuit multiplier, curvature,
obstacle lookahead/turn limits, awareness range, contact damage, initial/turn
timer ranges, awareness cadence/chance, forget chance and walking frames.
Reloaded files affect new content snapshots; active simulations keep theirs.
Native status, camouflage, special thrown states and full acceptance remain open.


Eight ordinary champion types are available for Frowning Gaper, Gaper, Gusher,
Pacer and Horf: Red (0), Yellow (1), Green (2), Dark Cyan (5), Gray (7), Light
Blue (13), Small (18) and Large (19). They change HP, contact/projectile damage,
movement and/or size; Green leaves creep, Dark Cyan explodes on final death,
and Light Blue fires eight death shots. Headless morphs retain champion state.
Champion contact remains harmless after permanent conversion.

`assets/mechanics/champions.mechanics` controls HP, speed, visual/collision scale,
damage and source-stage eligibility. Eligible natural Canyon residents have a
seeded 5% chance; supported types have equal weights. Yellow unlocks at source
stage 3. Tutorial and Mine encounters keep their existing rules. Speed values,
creep/blast strengths and pickup behavior are DeathWard adaptations. Existing
ordinary loot remains in use; Isaac's champion-specific pickups and the other
18 champion types are not implemented.

To force a supported type in a capture (bypassing natural stage/chance rules):

```sh
./build/deathward --smoke --theme canyon --scene enemy-10.0.0 \
  --enemy-champion 0 --enemy-camera-follow --frames 60 --mute
```


`./build/deathward --practice-batch2` opens a playable mixed Fly, Pooter,
Attack Fly, Spider and Mulligan encounter in a generated combat room. It uses
ordinary mouse/keyboard controls, starting100HP/24damage and no perks. The default
save is a separate `deathward-batch2-practice.save` in the system temporary
directory; an explicit `--save` overrides it. This is a testing shortcut, not a
shortened expedition or story replacement. `--smoke --frames 30 --screenshot PATH`
can capture the same setup. Existing F-key cheats remain available.

This batch reuses the mass-based recoil system; airborne and evader controllers
now preserve externally supplied momentum between updates. Pooter and Mulligan
also support the existing eight champion types. Fly, Attack Fly and Spider
remain champion-ineligible. Other item/status interactions and full acceptance
remain in progress; see the honest regular-enemy HTML report.


`./build/deathward --practice-batch3` opens the Charger-family practice room:
Charger, Drowned Charger, Dank Charger, Carrion Princess and Level 2 Charger.
It uses normal controls, starting100HP/24damage, no perks, and a separate
`deathward-batch3-practice.save` in the system temporary directory. It combines
stage-specific enemies for testing; their normal expedition floor pools stay
stage-specific. The eight shared champion types also apply to these five.

Charges now respect their remaining duration on long simulation steps and use
swept contact checks. Drowned death shots retry under event/projectile pressure
without paying extra rewards or clearing the room early. Carrion Princess keeps
its spatial tail weakness; Dank retains reflection and harmless slowing tar.
Remaining native tuning, status/item interactions and full acceptance are listed
in the regular-enemy HTML report.

The consolidated [enemy work remaining report](docs/reports/isaac-enemy-missing-work/index.html)
separates completed checkpoints, shared systems still missing, and the full
per-record backlog. It can be rebuilt with `python3 scripts/isaac-reference/build-enemy-missing-work-report.py`.
