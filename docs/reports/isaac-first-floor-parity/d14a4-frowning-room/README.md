# D14a.4 — Frowning Gaper and recorded room51

Status, 2026-11-18: enabled in the main game. Build, focused developer verification and rendered-game checks pass. The user accepted the scoped playtest and requested this checkpoint commit on 2026-11-18; see `human-acceptance.json`. Selected after the user accepted D14a.3, committed as `00313e5b`.

## Playable handoff

```sh
build/deathward --expedition --seed 456 --review-source-room 51 --mute --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json --save /home/kambo/.local/share/deathward/reviews/first-floor-d14a4/campaign.save
```

Opens directly in displayed **room6**, at normal six-half-heart health, with the user's165% zoom, Speed1.1, Shot Speed1.05,110% room size,7–9 half-tile range and26% route length. The original preset remains unchanged (SHA256 in `verification.json`). No god mode. Retry returns to this encounter at the recorded settings.

1. Let the two Frowning Gapers approach, circle them and clear the room. Their eyes open and pursuit gains speed; player movement and universal dodge stay familiar.
2. Shoot a poop pile, leave and revisit: the room remains cleared and the pile remains destroyed.
3. Optional tuning check: Escape → Tuning → Enemies → Frowning. Lower movement, then export/load or remember it for the next expedition.

## Main-game scope and source evidence

Source1.51.0 contains two ordinary Frowning Gapers10.0.0 at(6,2)/(6,4), two plain rocks and four ordinary poop grids. Its eight singleton slots, difficulty1, weight1 and original slot order are preserved in `source-room.json`, copied from the exact installed-STB/live-descriptor audit. Compatible opening-floor SOURCE layouts with prop layouts enabled now instantiate the complete arrangement; original descriptor-derived prop seeds and the accepted ordinary destruction/drop consumers are reused. Protected room roles/key sites and existing source selection remain intact. Canyon outlines, dimensions and connections remain deliberate exceptions.

The Frowning movement consumer is enabled for ordinary10.0.0 in main-game encounters, including future spawns. It uses the fixed D04 conversion: accepted base walking4.8 / (native player steady step4.414238452911377 ×60). Source force.6 rises to.72 after direct-route activation; steady pursuit is approximately45%/54% of base player pace. Current player Speed, zoom and room dimensions do not rescale the enemy. AI reads the old Head frame, evaluates its wake gate, then advances the20-frame nonlooping overlay. This promotes the bounded previously checked phase correction only for the selected identity; the global private review flag remains off.

Source HP10/stage0 remains32 internal HP. Existing incoming half-heart contact, body radius.6, physical routing, source-to-canyon scale adaptation, headless lifecycle and universal dodge are retained. Ordinary Gaper and Flaming Gaper movement are independently unchanged by the new control. Existing Fear uses the same selected spatial/drive conversion; complete native status behavior is not certified.

`source-evidence.json` links and hashes the pinned original-code trajectory/phase captures and source room audit. These are supplied-input comparisons, not a new full native NPC-wrapper or live scheduling capture.

## Live configuration

**TUNING → ENEMIES → FROWNING** exposes independent movement in5% steps from10–200%. Changes apply at the next steering tick, preserving position, momentum and Head state. Schema50 (`d14a4-frowning-room-v50`) exports/loads/remembers the value; schemas1–49 migrate with100%. Reference calibration remains separate from custom overrides; invalid/incompatible values reject before applying.

Map and prop changes stay pending until Apply. Runtime edits keep pending map settings intact; Apply, retry, fresh expeditions and floor transitions retain Frowning tuning. A geometry edit can legitimately change which source template is selected: seed456 is a witness at75%/5–5 and110%/7–9; the150%/10–10 witness is seed1205. The Game check restores the recorded110% dimensions before its source51 retry. It also verifies fresh normal startup with the remembered111% test map; no source template is forced to preserve a witness.

## Verification

- Main-game build passes; nine focused suites pass (the new delivery suite plus eight regressions). See `final-tests.log` and `regressions.log`.
- Two native Frowning trajectories:360 recorded60Hz states at each of three translated world positions, bounded by.002 position/.005 velocity. Six supplied Head cases/288 phase states match frame, force and playback. Half-time cases reproduce the supplied arithmetic without claiming native Slow scheduling acceptance.
- Independent drive bounds, next-tick settling,30/60/120Hz stepping, source/internal HP, retained body geometry, contact immunity and dodge pass. Ordinary/Flaming controls stay independent.
- Three natural seed/size/range cases verify exact contents and actor cells, both live routes to the entrance, actual projectile kills including retained headless lifecycle, ordinary room clear, real-shot poop destruction/collision/drop resolution, revisit persistence and SOURCE OFF/ON Apply.
- The largest prop requires a firing position outside its scaled collision bounds. The verification helper was corrected to choose that clearance; gameplay geometry was unchanged.
- Actual Game/Renderer mouse checks cover the new page, live values, reset/export/load/remember, pending map preservation, Apply, direct retry, actual awakening, clear/revisit and a fresh expedition. Screenshots were inspected. The UI harness uses explicit developer cleanup for clearing; the separate Simulation suite verifies real projectile kills. A completed-floor Simulation fixture verifies tuning through descent.
- Four normal CLI startup checks cover schemas5/48/49/50, source51, room6,165% zoom, health6 and god mode off. `review-preset.json` is a separate95% movement CLI fixture; it does not overwrite the user's preset.

## Unfinished and next step

The scoped D14a.4 playtest is accepted and included in this checkpoint. Full native RNG/masks/navigation/cache/collision/status/champion/lifecycle/scheduler equivalence remains unaccepted. Next proposed batch: **D14a.5 — recorded mixed Pooter/Attack Fly/poop arrangement (source1.414.0)**, verifying standalone Attack Fly movement before the combined pressure review. This proposal is not selected by the request for next steps. Exact Duke-room contents, Mom’s Eye treasure, Mom’s Coin Purse/Temperance shop, unresolved special-room content, complete recorded-floor allocation/acceptance and gameplay save/resume remain unfinished. This does not resume bulk parity; pixel/performance work stays deferred.
