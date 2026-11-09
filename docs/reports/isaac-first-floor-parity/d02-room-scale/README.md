# D02 — original canyon presentation, larger and adjustable rooms

D01 is committed as `809beb75`; the room/route/zoom tuning implementation and recovery report are committed as `a10e08c0`. The user rejected the first D02 candidate's straight borders, narrow connectors and faster walking. Those changes were removed. The selected implementation retains the original canyon generator, eight-unit-wide gates/trails, accepted 4.8 base walking pace, immediate stopping, universal dodge and existing firing/HP/damage rules.

The user subsequently required dynamic size, configurable minimum/maximum before generation, small adjustments, unrestricted resizing for testing, an explicit Apply button and adjustable connection-route length. These are implemented in the main game's tuning panel.

## Controls

- **SIZE / TUNING** in expedition setup, or **TUNING** in the expedition HUD/pause menu.
- **DEFAULT ZOOM −1% / +1%** previews the camera immediately, from 67% to 285% (original default 160%). **USE CURRENT** stores the current view, rounded to a whole percentage; **RESET 160%** restores the original view. Mouse wheel/Page Up/Page Down only change the temporary view. Retry uses the applied default; a new expedition uses its remembered preset default. Zoom never applies pending map edits or regenerates a floor.
- **ROOM SIZE −1% / +1%**, between 75% and 150%. Canyon envelopes use continuous dimensions so a 1% edit changes their size. Mine rooms retain tile rounding. Ordinary rooms have a minimum ten-tile envelope to retain generator clearance; boss envelopes and corridor width are unchanged.
- **MIN / MAX** select the ordinary room-size range before the percentage multiplier. The range is 10–20 floor tiles per side, in two-tile increments; X and Z are sampled independently. **AUTO RANGE** restores the selected pacing profile's range/progression.
- **ROUTE LENGTH −1% / +1%**, between 25% and 200%, scales the gaps between room rows/columns. It changes connection-route length without changing room sizes or eight-unit corridor width. Canyon placement is continuous; mine spacing rounds to tiles. Irregular trail bends remain, so this is a spacing factor, not a promise of an exact percentage of walking-path arc length.
- Size, range and route edits are **pending until APPLY MAP CHANGES**. Closing/reopening the panel retains the draft. The button applies the entire map draft once; pressing it with no changes does not regenerate anything.
- Before generation, Apply saves the selected map settings for the next expedition. In an expedition, Apply regenerates the **current floor for testing**, without restarting the application or expedition. Exploration, combat, collected items and later floors do not block resizing.
- Speed and default zoom remain immediate; changing/resetting either never applies a pending map draft. **LOAD PRESET** applies Speed/default zoom and stages map settings for Apply. **EXPORT** writes the selected settings, including pending map values. **USE NEXT EXPEDITION** explicitly remembers those selected settings for future generation without regenerating the current floor. Unapplied/unremembered drafts do not affect retry or a new expedition.
- Presets retain room size, range, route length, canonical Speed and default zoom. Existing schema 1–3 files migrate with their original values and zoom 160%; older files without route length use 100%. Walking calibration remains 4.8, not the rejected source-paced conversion.

**Testing regeneration is explicit:** it retains the same expedition ID, seed, current floor and room index, elapsed time, player health/stats, inventory, wallet/keys/bombs, and retained persistent companions. It regenerates room encounters, unclaimed pickups, scenery, locks and floor completion/reward state; active projectiles, placed/carried bombs, hazards and other transient room effects reset. The player is placed at a nearby clear position in the recalculated room. This can generate further test rewards; it is a testing control, not preservation of a played floor's complete state. The panel explains the regeneration behavior.

## Default size change

At 100% with automatic sizing, Compact/SmallRooms opening ordinary room envelopes are **24–32** world units per axis, previously **20–28**. Their final-floor pool is **28–40**, previously **24–40**. Original seeded shape variety, canyon basins, irregular borders, rivers, roads and decorations remain. Default tutorial geometry and default Growing/Classic/ShortCorridors dimensions remain as before; explicit size/range overrides may be used for testing those layouts too. A custom range replaces ordinary-room size progression on subsequent floors until automatic range is restored.

These are generator envelopes, **not exact Isaac footprints**. The irregular canyon's actual walkable area is smaller and nonrectangular. The preserved source table proves source dimensions; it does not make this adapted canyon generator native-equivalent.

## Short human check

```sh
build/deathward --expedition --seed 1866 --mute --save /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save
```

1. Walk and pass through a trail: the previous canyon style, corridor width and walking feel should be restored.
2. Open TUNING, adjust room size/MIN/MAX and ROUTE LENGTH. The map stays unchanged until **APPLY MAP CHANGES**. Apply, close the panel and walk the resized room/connection. This works later in the expedition too, with the displayed testing reset behavior.
3. Set DEFAULT ZOOM (or use the current view), export/use-next-expedition, then launch again: size, range, route length, Speed and default zoom reload. Loading a preset previews its zoom while map edits remain staged. Configuration is separate from inventory/gameplay saves.

## Load an exported preset from the CLI

Use this one-line command from the repository root:

```sh
build/deathward --expedition --seed 1866 --mute --save /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

`--balance-preset` loads the complete configuration before generating the expedition and remembers it for subsequent launches using the same `--save` path. Export alone writes a file; it does not select that file for startup. Inside an existing expedition, **LOAD PRESET** previews Speed/zoom and stages map changes until **APPLY MAP CHANGES**.

On 2026-11-10, actual main-game startup reported Speed 1, room scale 1.1, route scale 0.3 and zoom 165. The remembered configuration also matches the exported range of 7–9 half-tiles (14–18 full tiles). See `cli-preset-load.json`. The user positively acknowledged this CLI workflow; full native geometry/gameplay acceptance remains open.

## Implementation and validation

Schema 4 / contract `d02-view-v4` stores size/range/route length, Speed and `default_zoom_percent`, with immutable provenance and explicit overrides. Schema 1–3 files remain loadable; new exports use schema 4. The 160% camera reference is DeathWard framing, not a claim about Isaac camera parity. Range fields are integer half-spans (`room_min_half_tiles`, `room_max_half_tiles`); zero/zero means automatic pacing. Invalid, reversed, fractional or out-of-range values are rejected before applying. The rejected walking-timing schema is not accepted as this room-size schema.

Live regeneration constructs the replacement floor first and retains the current Simulation identity. Rendering invalidates regenerated geometry even when a mine keeps the same Arena address and seed. Player placement checks terrain and tries to avoid regenerated enemies. All dimensions are recalculated before terrain, scenery and encounter generation; changing size never modifies the movement consumer.

See `validation.json` and adjacent build/test/capture records for current verification. Checks cover the staged/apply boundary, preset-load staging, Speed isolation, no-op Apply, route spacing and initial generation across pacing/themes and scaled ranges, door/objective traversal, corridor width, fixed walking/dodge, presets, actual main-game controls, 1% geometry changes without changing player pace or expedition identity, later-floor/combat-room resizing with health/inventory preservation, and fresh-process reload.

## Source research and remaining work

`source-shapes.json` and `scripts/isaac-reference/capture-source-room-shapes.py` retain the pinned executable's 12 room shapes: normal 13×7; narrow 13×3/5×7; doubled 13×14/5×14/26×7/26×3; large 26×14; four L orientations with a 13×7 quadrant removed. These remain research, not enabled canyon masks. Chapter-template presence is not proof of floor-I eligibility/frequencies.

Unfinished: broader gameplay/visual acceptance beyond the positively acknowledged tuning and CLI workflow; exact source-equivalent area/traversal/clearance under the retained irregular canyon style; exact source room/door/content-generation rules and D03–D20. Full state-preserving resizing of an already played floor is not implemented: the requested unrestricted testing control regenerates that floor's encounters and rewards. The original D02 exact-geometry objective is not complete.

## Preset path recovery (2026-11-09)

The reported `first-floor-d01/campaign.save.balance/export.json` was absent. The export was intact under `first-floor-d02`, and the subsequent launch used the D01 save path. An identical copy was restored at the requested D01 path without changing the original; the production preset loader accepts it. Settings: Speed 1, room size 110%, range 14–18 tiles, routes 30%, default zoom 165%. See `preset-path-recovery.json`. No loader/code change was needed. Load this file, Apply its pending map changes, and Use next expedition to remember it. Preset directories remain tied to the selected campaign/save path; use one consistent save path for review launches. Broader native spatial acceptance and later deliveries remain open.

Next proposed delivery: **D03**, independent live Tears, Shot Speed and Range controls with preset persistence and shooting review in the main game. Existing independent consumers are already enabled; preserve the accepted baseline, eight-direction firing and universal dodge while verifying the selected source-flight/collision gaps. D03 is proposed, not newly authorized by this documentation checkpoint.
