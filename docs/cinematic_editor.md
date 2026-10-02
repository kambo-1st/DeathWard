# Cinematic Editor

The **Cinematic Editor** is a separate tool with its own screen, timeline, undo history and `.cinematic` documents. Open the town editor with **F4**, then choose **Cinematic Editor** in the top toolbar. Closing it returns to the same town-editing session, including unsaved placements.

Launch directly into Redstone's train demo:

```sh
./build/deathward --cinematic --hub redstone
```

In the browser, use `?hub=redstone&cinematic`. Black Creek works too; Frontier supports cameras, weather and sound but has no authored train route.

The first opening creates a 20-second starter sequence: a moving-train establishing shot, a cut inside its passenger carriage, a growing sandstorm, then braking at 11 seconds. The interior uses the existing carriage geometry and textures. Save to keep this sequence or your changes.

## Westbound opening

Choose **Train opening** in the Cinematic Editor's upper-right toolbar, or launch:

```sh
./build/deathward --cinematic --intro
```

This opens the separate `assets/train_opening` desert set and its authored **82-second Westbound** sequence. The elderly couple and protagonist sit in a passenger carriage and discuss why he is travelling west. The storm builds during their conversation, the train slows and brakes, and the conductor walks down the aisle to reassure them about the nearby fort.

**Play story** shows the sequence and then cuts to a storm-covered Redstone preview. Escape returns to the cinematic editor. Ordinary **Preview** only plays the current map's sequence. The map being edited in the town editor is preserved, including unsaved placements. Save changes to the current cinematic before switching to the opening set.

To play it as the game's opening and hand control to the player at Redstone, use:

```sh
./build/deathward --intro
```

Click **Skip intro** at the bottom right, or press Escape, to skip the runtime opening and arrive at the same playable storm-covered destination. **Pause / Resume** and Space control playback; skipping also works while paused. Runtime playback blocks editor shortcuts, and both completion paths keep the cinematic view visible until gameplay is ready. The ordinary default start remains Black Creek. Browser equivalents are `?intro&cinematic` to edit and `?intro` to play; `?full-experience` starts with the logos and save slots. `--cinematic-at 69` (browser: `&cinematic-at=69`) starts at a chosen time for iteration; combine it with `--cinematic` for a paused preview.

Dialogue is subtitled, with train, wind and braking audio. Spoken voice recordings and lip-sync are not included. Characters reuse the retained rigs and source Western textures, with procedural sitting and speaking gestures.

## Cameras and editing

Click the time ruler or empty track space to scrub. Click a key to select it, drag it to change its time, or use the inspector's **Time** controls. Closely spaced cut keys select by distance to the pointer. Shift makes numeric `− / +` adjustments ten times smaller.

Move the camera with the pointer over the viewport:

| Control | Action |
| --- | --- |
| Hold right mouse button and move | Look around |
| Hold middle mouse button and move | Orbit the current target |
| W / A / S / D | Fly forward, left, backward and right |
| Q / E | Move down and up |
| Shift | Fly faster |
| Mouse wheel | Change lens zoom (field of view) |

**Wide train** and **Inside carriage** position the free camera. Adjust it and choose **Capture shot** to save its position, target, lens and selected vehicle anchor at the playhead. Capturing at an existing camera key replaces that shot; moving the camera alone leaves the sequence unchanged.

An **Anchor** of **world** keeps coordinates fixed in the scene. A vehicle anchor keeps the camera and its target relative to the moving train. Switching an existing shot's anchor preserves its position at the current preview time. Camera keys offer **Smooth**, **Linear** or **Cut** transitions to the next key. A cut holds the earlier shot until the next key's time. Lower FOV values zoom in.

## Timeline tracks

| Track | Controls |
| --- | --- |
| Camera | Position/target capture, FOV, anchor and transition |
| Sandstorm | Strength from 0 to 1, smoothly blended between keys |
| Train | Target speed, acceleration/braking and an existing route; `*` selects every route |
| Sound | Clip, volume, duration and audition |
| Actors | Cast member, carriage/world coordinates, facing and seated/standing/walking pose |
| Dialogue | Speaker, text, start time and duration |

**+ Actor** captures the selected actor at the playhead; the inspector edits its local X/Y/Z and facing. Keys interpolate positions, so two walking keys make a route down the aisle. Vehicle anchors keep passengers attached to the train. Before an actor's first key it is hidden. If several actors have keys at the same time, click that marker repeatedly to cycle through them. **+ Dialogue** creates a subtitle cue. **Edit dialogue text** opens its text field: Ctrl+A replaces the text, Enter keeps it and Escape cancels. Undo/redo and sequence saves cover both tracks. Cast membership, model names and destination are stored as `cast` and `destination` records in the version-2 sequence file; their roster/destination creation is currently done in that file. Version-1 sequences still load.

Use **+ Weather**, **+ Train cue** and **+ Sound** at the playhead. The train inspector's **Emergency stop** sets speed to zero and braking to 12 m/s². Train cues control the existing rail simulation, including vehicle and wheel motion. Route geometry and scenery are edited in the town editor.

The sound selector lists WAV and OGG clips beneath `assets/audio`. Duration **0** plays the whole clip once; a positive duration loops or trims it to that many seconds. Scrubbing is silent. Starting playback within a ranged clip resumes it at the matching offset; earlier one-shot cues are not replayed. **Audition sound** previews the selected clip separately. Sound uses the game's master/effects volume and existing native/WSL or browser audio device. Normal gameplay music and ambience are silenced during this editor.

The demo includes original synthesized train rolling, wind and brake sounds in `assets/audio/cinematic`. They are editable placeholder effects, generated by `scripts/generate_cinematic_audio.py` (Python + NumPy). To add your own clips, put WAV/OGG files under `assets/audio` and reopen the tool. Rebuild the browser package to include new audio assets.

## Playback and saving

| Control | Action |
| --- | --- |
| Space / Play | Play or pause |
| Stop / Home | Rewind to the beginning |
| Left / Right arrows | Scrub by 0.1 seconds |
| Preview | Play with the controls hidden |
| F11 | Toggle clean preview |
| Escape | Leave clean preview, or close the editor |
| Delete | Remove the selected key; retain at least one camera key |
| Ctrl+Z / Ctrl+Y | Undo / redo |
| Ctrl+S / Save | Save the sequence |

**Length −5 / +5** adjusts duration up to ten minutes. Shortening requires moving/deleting keys beyond the new endpoint first. Click the filename, edit it and press Enter to choose another `.cinematic` filename in the hub directory. Save writes to that name. **Reload** loads that file when the current sequence has no unsaved changes. Closing a modified sequence offers Save, Discard or Keep editing.

Native files default to `arrival.cinematic` beside the selected map's `town.scene`. `--sequence PATH` opens or creates a different document. `--town DIRECTORY` previews a custom map. Browser saves live in IndexedDB under `/persist/<hub>/`, separately from desktop files; wait for **Saved in this browser** before closing the page.

The preview runs a private copy of the map and animations. Seeking rebuilds train motion from the beginning in fixed steps, so playing and seeking produce the same train placement. Saving a cinematic writes no scene, navigation, train defaults or campaign changes. Existing residents and animals animate alongside its authored cast. Weather particles retain the renderer's normal visual animation rather than a frame-exact particle replay.

The `--intro` entry point connects the opening to playable Redstone. Additional automatic story triggers and encoded movie export are not connected yet.

## Verification and still captures

```sh
cmake --build build --target deathward deathward_cinematic_tests deathward_cinematic_editor_tests deathward_cinematic_cast_tests -j4
ctest --test-dir build -R 'cinematic_timeline|train_motion|object_animation' --output-on-failure
./build/deathward_cinematic_editor_tests
./build/deathward_cinematic_cast_tests
./build/deathward --cinematic --hub redstone --cinematic-at 6 --smoke --frames 2 --screenshot artifacts/cinematic-interior.png
```

The explicit editor test requires graphics and audio devices; it verifies actual input, persistence, map isolation and audio reaching the mixer while suppressing test output. The cast test checks textured models and seated poses. After building and serving the browser version on port 8091, run `node web/cinematic-test.cjs` and `node web/opening-test.cjs`; the opening test also verifies dialogue editing and the playable Redstone handoff. `DEATHWARD_URL` changes the server address and `DEATHWARD_BROWSER` selects a local Chromium executable.
