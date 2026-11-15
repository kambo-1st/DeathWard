# DeathWard Display as the main game font

The user accepted the finished font and requested: "Nice commit and use it as a
main font." The font and six-letter study are preserved in commit `32991e0d`.
This checkpoint enables the accepted face in the native game.

The user accepted the native interactive font review after launch ("nice
commit..."). The font implementation is committed as `53c10729`; this follow-up
records that acceptance. It does not accept or commit the separate D09d gameplay
delivery visible in the same working build.

`MainFont` provides shared drawing and width measurement for the front-end title,
save-slot screen, settings, gameplay HUD, pause/tuning/build/journal screens and
runtime cinematic text. It normalizes size against the actual capital height,
aligns text against that cap line, and uses mipmapped atlases for smaller HUD text
and larger headings. The full atlas includes all 978 mapped characters; the
larger atlas covers ordinary Latin headings. Missing-font fallback retains the
raylib default. Font resources unload before the graphics context closes.

Wrapping, button fitting, notice panels and resident captions now measure the
font actually drawn. Bounded room/boss/objective titles and save-slot text shrink
to fit. The reproduced long canyon-guardian objective overflow is corrected.
Runtime cinematic subtitles use the same font; their panel can grow upward for
additional wrapped lines. Authoring-editor text and the developer style-comparison
overlay retain their existing fonts.

Native asset staging copies the OTF and OFL license into
`assets/ui/deathward-display/` beside the executable. The web preload manifest
also includes both files. The original accepted OTF bytes are unchanged.

## Verification

- `cmake --build build --target deathward deathward_input_tests -j 4` passed;
  `deathward` was rebuilt after final layout changes.
- A temporary harness used actual `FrontEnd`, `Game`, `Renderer` and
  `CinematicEditor` objects with a hidden graphics window and isolated saves.
  It verified custom-font load/unload/reload and captured title, slots, settings,
  expedition, tuning, reward, pause and runtime intro screens. Normal and smaller
  windows (1280×800 and 1024×640) were checked, including actual resize-event
  settling before capture. See `verification.log` and screenshots in this folder.
- The existing `deathward_input_tests --keyboard-only` suite passed, covering
  keyboard hub/setup, menus/settings, HUD input, trade/reward controls and returns.
- The older `--balance-only` test stops at `tests/input_tests.cpp:61`: it expects
  `/balance-v11:` while the current `GameTuning.cpp` writes `/balance-v13:`.
  This is an existing preset-version assertion, not a font/input failure. The
  actual failing temporary save also contains `/balance-v13:`. The unrelated
  assertion and tuning implementation were left unchanged.
- Native staged font/license hashes match the source artifacts. Source cmap and
  the runtime codepoint table agree. Source changes pass whitespace checks.

The screenshots show the current working game's independently pending gameplay
changes. This font commit does not select or commit those gameplay changes.
Only font-related hunks of the already modified renderer and CMake files belong
to this integration.

## Review

- `menu.png`: front end using DeathWard Display throughout.
- `settings.png`: settings labels and buttons.
- `expedition.png`: HUD, objective fitting, minimap and controls.
- `tuning.png`: dense settings screen and preset controls.
- `intro.png`: runtime dialogue and prompts.

Run from the repository root:

```sh
build/deathward --expedition --mute
```

Remaining: a browser-specific visual check (web assets are configured but a browser build/playtest was not performed
for this checkpoint). Less-common inherited Unicode forms and combining-mark
layout retain the documented font scope; no gameplay/balance changes are part
of this delivery.
