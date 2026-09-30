# Browser build

DeathWard has an Emscripten / WebAssembly build using WebGL 2 and Web Audio. Both
original hubs, canyon and mine missions, enemy rosters, the animated player,
lighting, post processing, scenery transparency, outlines, music and sound effects
use the same game code and packaged assets as the desktop build. A keyboard and
mouse are required; touch controls are not provided.

## Build and run locally

Install an [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html),
Python 3 and CMake 3.20 or newer. This port is tested with **Emscripten 4.0.15** and
the repository's pinned **raylib 5.5**. For a new SDK checkout:

```sh
git clone https://github.com/emscripten-core/emsdk.git /path/to/emsdk
/path/to/emsdk/emsdk install 4.0.15
/path/to/emsdk/emsdk activate 4.0.15
source /path/to/emsdk/emsdk_env.sh
./scripts/build-web.sh
python3 scripts/serve-web.py
```

Open **http://127.0.0.1:8080/** and click **Enter Black Creek** after loading.
The server binds to localhost by default. `--port` and `--bind` change that.
The native `build` directory remains separate from `build-web`.

`EMSDK=/path/to/emsdk ./scripts/build-web.sh` also works without activating the
SDK in the current shell. `DEATHWARD_BUILD_JOBS` controls compilation concurrency.
Extra script arguments go to CMake. The build script also generates gzip versions
of the JavaScript, WASM and data bundle; the included server serves them when
supported. The initial transfer is approximately **38 MiB compressed** or
**74 MiB uncompressed**, dominated by both imported towns and the soundtrack.

## Playing and local saves

The start button activates browser audio. The game's pause panel has the same
independent volume and mute controls. Canvas clicks focus the game. Scrolling
zooms, right-clicking fires, and middle dragging rotates without browser scrolling
or context menus. The Fullscreen button expands the canvas. Resizing preserves
input coordinates and recreates rendering targets. Changing tabs or losing focus
pauses gameplay; resume from the game's pause menu.

Campaigns, audio preferences and saved town-editor changes use IndexedDB in this
browser, at this site address. The header shows when a save is in progress or has
completed. Wait for **Saved in this browser** before closing immediately after a
change. These saves are separate from the native campaign. Different browsers,
profiles, hostnames and ports have separate saves. Clearing site data removes
them. If local storage is unavailable, the game reports that and continues for
the current session. Reloading during an expedition resolves it from its last
checkpoint as an interrupted run, as with desktop recovery.

The town editor still opens with **F4**. Its save operation persists the scene
and rebuilt navigation locally; it cannot overwrite the original files on the
host computer. The original large models and textures stay in the read-only
asset bundle and are not copied to IndexedDB.

Optional URL parameters:

| Parameter | Purpose |
| --- | --- |
| `?hub=frontier` | Start in the Frontier hub |
| `?theme=mine` | Offer the mine mission by default |
| `?theme=seeded` | Select mission theme from the seed |
| `?mute` | Skip audio initialization |
| `?smoke&scene=hub&frames=180` | Run a scripted check using a temporary campaign |
| `?smoke&scene=boss&audio` | Scripted finale with audio enabled |
| `?verify` | Expose read-only frame state for integration checks |

## Hosting

Create the upload package from the completed browser build:

```sh
python3 scripts/package-web.py
```

This produces **`dist/deathward-web.zip`** (approximately 38 MiB) and the same
files unpacked in **`dist/deathward-web/`**. Upload/extract the ZIP's contents into
the public directory so `index.html` sits directly inside it:

| Address | Upload destination |
| --- | --- |
| `https://kambo.us/deathward/` | The main website's public `deathward` directory |
| `https://deathward.kambo.us/` | The subdomain's document root |

The exact same package works at either address, or another domain/subdirectory.
Every runtime URL is relative to the hosting page; no domain or base-path setting
needs editing. Configure the subdomain's DNS, document root and HTTPS through
your host if using that option. The package does not change hosting settings.

The ZIP contains `index.html`, three versioned runtime files (`.js`, `.wasm`,
`.data`), `manifest.json` with SHA-256 checksums, and a short `README.txt` for the
server administrator. Only these packaged files are needed on the server; do
not upload the repository, native builds or local campaign saves.

Use an ordinary HTTP(S) static host with `index.html` as its directory index and
the usual redirect from `/deathward` to `/deathward/`. Serve `.wasm` as
`application/wasm`, `.js` as JavaScript, and `.data` as `application/octet-stream`.
Exclude this directory from any other site's single-page-app fallback routing.
No Node.js/Python runtime, backend, database, special cross-origin isolation
headers or Windows filesystem access is required. Do not open the HTML using
`file://`.

Runtime filenames include content hashes to prevent stale browser caches mixing
different releases. Upload new versioned assets first and `index.html` last;
retain old versioned assets while old HTML may still be cached. Revalidate the
HTML on each visit (`Cache-Control: no-cache`); versioned assets can use long
immutable caching. Enable gzip/Brotli HTTP compression for `.js`, `.wasm` and
`.data` when supported. The portable ZIP contains ordinary uncompressed runtime
files and does not require precompressed-file server rules. Without HTTP
compression, the first visit transfers approximately 74 MiB.

Browser saves remain separate between `kambo.us` and `deathward.kambo.us`.

Verify the actual upload ZIP on a plain static server at both the root and a
subdirectory (requires the Playwright setup below):

```sh
npm run test:package --prefix web
```

The packaging command accepts `--build-dir` and `--output` for other locations;
it packages an existing build, so rebuild first after changing the game.

## Implementation and verification

The shared synchronous application loop yields to `requestAnimationFrame` using
[Asyncify](https://emscripten.org/docs/porting/asyncify.html), retaining the same
simulation/input path and object lifetime as native. Web builds enable C++
exception handling, an 8 MiB stack and growable memory (256 MiB initially, capped
at 2 GiB). This is a desktop browser target, not a small mobile download.

GLSL sources use ES 3.00 declarations and precision qualifiers on the web. Sized
24-bit depth textures and depth-only framebuffer configuration retain shadows
and occlusion outlines. HDR rendering uses `EXT_color_buffer_float` when present,
with an 8-bit color fallback. Models, source placement data and textures are
unchanged. The raylib 5.5 Web Audio backend requires the exported `HEAPF32` view
with this Emscripten version. It runs its mixer on the browser thread, so a large
synchronous scene load can briefly interrupt sound.

[IDBFS](https://emscripten.org/docs/api_reference/Filesystem-API.html#idbfs)
restores `/persist` before the game starts. Completed campaign/settings/editor
writes request serialized, coalesced asynchronous persistence. Model paths stay
under `/assets`; only editable files go into `/persist`.

To run Chromium integration checks against a running local server:

```sh
npm ci --prefix web
npx --prefix web playwright install chromium
npm test --prefix web
```

Use `DEATHWARD_HEADFUL=1` on WSLg to run with a visible GPU-accelerated Chromium
window. `DEATHWARD_BROWSER=/path/to/chrome` selects an existing Chromium binary;
`DEATHWARD_WEB_URL` selects the server URL. Captures and logs go into `artifacts`.
The tests use a fresh browser profile and do not touch the player's native saves.
See [verification results](verification.md#browser-version) for tested coverage
and current limits.

## Redstone Canyon

Use `?hub=redstone` to start beside the stranded train in the authored canyon fort and settler camp. Both other hubs have a direct travel button; missions return to the departure hub. Redstone has independent editor files under `/persist/redstone`. Its parked train, fifteen provisional residents, original textures, campfires and canyon audio also ship in the universal upload package.

`node web/redstone-test.cjs` checks travel, mission return, train pause, editor saving and reload. The package check also starts Redstone from a nested deployment path.

The story-hub upgrade replaces only the known untouched pre-story scene/navigation pair. Other saved layouts keep their authored objects, routes and markers; new unused asset entries and labels append to make the expanded model catalog compatible.
