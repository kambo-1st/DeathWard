# Live Isaac access and bounded movement capture, 2026-11-09

The user reported a running Isaac instance and authorized trying it, measuring it and reading its memory while preparing first-floor requirements. The existing reader successfully opened process 29964 with `QUERY_INFORMATION|VM_READ` and checked the installed executable against the pinned Repentance 1.7.9b SHA256 `04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.

No process-memory writes, injected code, process suspension, mod installation or direct game/save-file edits were used. The two active captures did send ordinary keyboard input to the foreground Isaac window: Enter to resume the visibly paused game, short A/D movement holds, and Escape afterward. These are observational memory captures with controlled normal input, not input-free recordings. Gameplay time and player position advanced. The final pause screen was visually checked; no death, restart, new expedition, item purchase or floor transition was requested.

## Captures

| Folder | Result |
| --- | --- |
| `20261109T200649Z` | Five-second input-free sample, 322 rows, zero world-frame advance. Speed/character/room observations are valid; active movement timing is not established by this paused sample. |
| `20261109T200940Z` | Five-second ordinary Enter/A600ms/D600ms input sequence. 321 rows, 150 world-frame advance, horizontal movement observed. Holds were too short for the existing analyzer's steady-speed segment requirement; no new steady-speed claim from this capture. |
| `20261109T201021Z` | Nine-second capture with A800ms/D1400ms/A1000ms/D500ms holds and intervening pauses. 578 rows, one phase-crossing row excluded, 261 world-frame advance and two accepted steady horizontal segments. All movement requests passed foreground-window checks; the final Escape pause request was sent. |

Each folder retains raw CSV, reader metadata, output log and analysis. Active folders also retain the exact capture script, derived from `scripts/isaac-reference/read-live-motion.ps1` with a guarded ordinary-key thread. Earlier standalone keyboard attempts failed foreground checks or did not visibly resume the game; they are not measurement evidence. Running focus, keyboard input and sampling within one PowerShell process allowed the active captures above.

## Verified observations and limits

- Character field 0 (ordinary Isaac), cached Speed 1, room shape 1, whole grid 15×9; stored bounds `(60,140)` to `(580,420)`, hence 520×280 source coordinates and the previously established 13×7 interior cells.
- The longer steady segment lasted about 0.658 seconds with 43 samples. Fitted movement was 263.825 source coordinates/second, average cached velocity 4.411457 per player invocation and inferred motion cadence 59.804 invocations/second. Fitted world cadence was 29.802/second. These agree with the earlier longer [room-scale/timing capture](../room-scale-timing/README.md).
- The shorter reverse segment lasted about 0.263 seconds with 18 samples and inferred 58.033 movement invocations/second. Retain this sampling variation; do not claim exact 60.000-Hz delivery from either short segment.
- The approximate `520 / 263.825 = 1.97 seconds` is a derived steady point-traversal equivalent across logical room width. It is not a measured wall-to-wall trip from rest, and excludes acceleration and body clearance.
- Both observed steady segments had Speed 1, time scale 1 and friction 1. The sampler does not log exact input delivery timestamps, so it does not newly certify stopping-distance/input latency.
- The inspected pause HUD showed three full red hearts, one bomb, zero coins/keys and an empty displayed item sheet. This is a visual observation, not a complete memory audit of health, inventory, stats or unlocks.
- No source stage, difficulty, unlock profile, whole floor graph, shop/treasure placement rules, projectile timings or enemy behavior was established by this capture. A normal room shape does not identify its floor eligibility.

**Current delivery:** live access and a repeatable ordinary movement capture work; DeathWard gameplay is unchanged. **Remaining:** the explicit first-floor profile/content manifest, verified generation/count/placement rules, coherent base-game integration and complete-floor acceptance. Reuse the existing and current measurements; do not repeat player-speed research as a substitute for integrating it.
