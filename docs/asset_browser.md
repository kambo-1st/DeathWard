# DeathWard asset browser

A separate, read-only C++ desktop app for inspecting the full `assets/` tree. It does not create the game, open saves, change balance, or write asset files.

```sh
cmake -S . -B build
cmake --build build --target deathward_asset_browser -j2
./build/deathward_asset_browser
```

The browser and its FBX reader are excluded from the default build. They link raylib independently of the game. The default asset directory is the checkout's `assets`; use `--root /path/to/assets` for another pack.

## Inspection

The folder tree, category buttons and search field filter the entire recursive inventory. Source files, Unity metadata and unknown formats remain visible. Click a file or use Up/Down to change selection. `R` rescans the directory. `Ctrl+F` focuses search; Escape/Enter leave it. `Ctrl+C` or **Copy path** copies the selected absolute filename. `Ctrl+Q` closes the app.

| Type | Preview and controls |
| --- | --- |
| FBX source models | Native ufbx geometry/material import, skinning and animation clips. |
| GLB/glTF/OBJ/IQM/M3D/VOX | Raylib model preview, textures and supported skeletal animation. |
| Models | Left drag orbits, right drag pans, wheel zooms, `F` fits, `W` toggles wireframe. `M` / `Shift+M` isolate the next/previous mesh section, including packed model libraries. **Sections: all** restores the complete model when cycled around. |
| Animation | Space toggles playback; `[` / `]` or the arrow buttons change clips. |
| Images | Transparency checkerboard, nearest-neighbor scaling, drag to pan, wheel to zoom, `F` to fit. |
| Fonts | A specimen of letters, digits and punctuation using the selected font. |
| Audio | Waveform and decoder details. Playback starts only with **Play** / Space, using the current output device. |
| Text / Unity files | Scrollable text, line numbers, Shift+wheel horizontal scrolling. |
| Binary / unsupported files | File details and a hex/ASCII preview. Decoder failures retain the file in the inventory and show a message. |

Unity prefab, material, animation and scene documents are inspected as files; Unity's renderer, controllers and scene runtime are not executed. Source FBX previews use FBX materials and referenced textures that can be resolved in the asset tree; Unity-only material assignments are not reconstructed. Runtime GLBs show their baked materials. Skeletal animation uses the decoder's clips; the supplied Mixamo source files start on their Mixamo take while retaining unused legacy takes in the clip selector. This is an asset inspector, not full game behavior acceptance.

Text previews are capped at 2 MB and binary previews at 4 KB. The original file is unchanged. Audio output is optional; waveform inspection remains available without an output device.

## Headless inventory

These commands need no window or audio device:

```sh
./build/deathward_asset_browser --list
./build/deathward_asset_browser --inventory-json
./build/deathward_asset_browser --list --kind models --query cactus --folder western
```

`--inventory-json` includes every matching path, kind and size, plus the full scan count and any reported scan errors. Unknown extensions are included. No source directories are hidden by default.

## Render checks

```sh
./build/deathward_asset_browser --smoke --screenshot-dir /tmp/deathward-browser-previews
./build/deathward_asset_browser --select animals/capybara.glb \
  --frames 30 --screenshot /tmp/capybara-browser.png
```

The smoke sequence opens FBX, GLB, image, mechanics text, font, audio, Unity metadata and binary previews in a real hidden OpenGL window. It requires a working display. Normal launch is visible and interactive. The report at [reports/asset-browser/status.json](reports/asset-browser/status.json) records the last inventory and representative render verification. It does not imply every individual model/animation/material has been visually accepted.

The pinned FBX reader and its upstream MIT/public-domain license are in [tools/asset_browser/third_party](../tools/asset_browser/third_party/README.md).
