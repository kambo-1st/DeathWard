# D06 — ordinary Pooter movement and enemy shots

Selected on 2026-11-11 when the user acknowledged D05 and requested the next delivery. Ordinary Pooter `14.0.0` now uses the shared source-relative movement scale, corrected ordinary attack timing and source mode-0 shot flight in the main game. The user accepted the scoped D06 playtest and requested a commit after the seed-69 launch ("ok, nice commit!"). Full native actor acceptance remains open. D07 is next selectable, not authorized by D06.

## Play it

```sh
build/deathward --expedition --seed 69 --mute --save /home/kambo/.local/share/deathward/reviews/first-floor-d06/campaign.save --balance-preset docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json
```

The main game uses the user's accepted shooting, map, route length and **165% zoom**. Room **3**, directly connected to the entrance, naturally contains **one ordinary Pooter and four ordinary Gapers**. All five use the selected movement consumers; no enemies were injected or encounter pools changed. The interactive game uses normal damage, with retry after death.

1. Enter room 3 and approach the Pooter. Watch it drift and fire a single aimed bullet after its windup.
2. Keep moving and dodge several attacks. Bullets should have readable travel and fall away rather than persist for five seconds. Cover still blocks them.
3. Open **TUNING → ENEMIES → POOTER**. Compare shot speed at 100% and 50%, or attack delay at 100% and 200%; reset afterward. A larger delay means longer waits. Existing attacks finish using their selected settings.

This check should take about 1–3 minutes. The original external export and D03 backup are preserved. `custom-pooter.json` is a **developer fixture**, not a replacement for the user's preset: movement 50%, shot speed 65%, attack delay 150%, staged map size 120%.

## Enabled gameplay and configuration

Ordinary `14.0.0` uses the selected consumer in normal expeditions and the tutorial, including future ordinary Pooter spawns. Historical direct Simulation fixtures keep their old behavior unless enabled explicitly. Fly, Attack Fly, Super/Tainted Pooter, Horf and other shooters remain unchanged. HP remains 25.6 from source base HP 8 / Stage HP 0 / conversion 3.2. Incoming shot damage remains authored 10, producing one half-heart after the existing health conversion; player damage remains 24. Body radius 0.45 and bullet radius 0.22 are retained. No mechanics assets, encounter pools, player pace, firing controls or universal dodge were changed.

Three independent controls use 5 percentage-point steps and a 100% reference:

| Control | Editor range | Application boundary |
| --- | --- | --- |
| Movement | 10–200% | Next steering update changes pursuit/jitter/edge drive. Current velocity and wander state settle naturally; no teleport or phase reset. |
| Shot speed | 10–200% | Latched when the next attack starts. An active or capacity-retained attack keeps its selected speed; emitted bullets keep birth properties. |
| Attack delay | 25–200% | The next acquisition selects the new delay, rounded to a whole source update. Existing waits and attack animation are retained. Source seven-update acquisition polls still quantize actual shot spacing. |

The panel identifies settings pending for an active attack/wait. Schema **8**, contract `d06-pooter-v8`, persists `pooter_movement_multiplier`, `pooter_shot_speed_multiplier` and `pooter_attack_interval_multiplier`. Schemas 1–7 migrate with all Pooter fields at reference 1, retaining their prior player/enemy/view/map settings. Whole-preset validation rejects incompatible metadata, out-of-range values and mismatched overrides before publication. Map edits remain staged until **Apply map changes**. Floor regeneration, descent, retry and fresh application loading retain all three controls. Configuration is separate from expedition state.

## Source comparison

The source is the pinned installed **Repentance 1.7.9b**, ordinary Normal-mode Pooter. [Capture script](../../../../scripts/isaac-reference/capture-pooter-attacks.py) executes unmodified instructions for Normal shot-vector normalization, acquisition interval arithmetic, cooldown decrement/damping, mode-0 falling defaults, projectile physics and landing. Native executable/window hashes and supplied boundaries are recorded in [native-manifest.json](native-manifest.json). Animation metadata is preserved from the installed ANM2; its full live animation wrapper is not executed by these bounded fixtures.

- Movement reuses the earlier native wandering recurrence: intermittent pursuit impulse 0.7, fourth-update jitter 0.6/retention 0.4, third-update wander impulse and retention 0.6, edge force 0.06. During a positive attack delay, velocity friction 0.8 and wander damping 0.7 apply **before** decrementing the counter, including its last positive update.
- D04's fixed conversion is `4.8 / (4.414238452911377 × 60)` world units per native coordinate. Current player Speed, map size and zoom do not alter that anchor. Source room-edge offsets 20/40 horizontally and 90/0 vertically are applied to canyon room bounds, an explicit geometry adaptation.
- Acquisition uses strict source range **200**, a **7-update** global-frame/entity-index poll and line of sight. The source sets a **35-update** delay at acquisition; it decrements on that same update. Animation metadata has **14 frames**, with **Shoot at frame 6**. The shot aims at the current player when Shoot is consumed, even if the player has left acquisition range. Capacity retention and Skatole suppression remain supported.
- Normal source shot speed **7 per 30 Hz update** converts to approximately **3.806 world units/s**, replacing the previous 21. In a flat source comparison, mode 0 begins at height **−23**, falling speed **−3**, falling acceleration field **0.1**. Each update uses `fallingSpeed = 0.9 × fallingSpeed + 0.1 + 0.1`, then advances height. The native strict `height > −5` landing condition occurs on update **31**, approximately 1.033 seconds and 217 native coordinates / 3.933 world units of unobstructed flat travel.
- The native height is separate from DeathWard's existing aimed collision trajectory. Rendered fall uses an explicit 0.03 vertical conversion. Existing 3D aim is retained so a Pooter above cover can shoot at a floor-level player; on that sloped trajectory the horizontal component is smaller than total shot speed. Existing swept spheres, cover and body geometry remain adaptations, not native collision equivalence.

## Verification and fixture corrections

Developer evidence is in [validation.json](validation.json), [final regression](regression.log), [actual Game check](input-tests.log) and [CLI reload checks](cli-verification.json).

- **144 independent native wandering states** pass at 30/60/120 Hz physics partitions: 432 comparisons, maximum position error about 0.00002077 world units. Bounds remain 0.002 position / 0.005 velocity / 0.0001 wander. Random draws are the same explicitly supplied DeathWard stream used by the prior native capture, not Isaac RNG replay.
- **490 native interval cases, 36 cooldown cases and four native shot vectors** pass through the selected Simulation consumer. Actual acquisitions verify the Shoot/recovery timeline, preserved current wait and new-attack latching. The full **31-update flight** passes at all three physics partitions, including landing.
- Physical tests cover walls, elevated cover, harmless body contact, one-half-heart bullet damage, stun cancellation/cooldown progress, projectile-capacity retention, suppression and unchanged unselected identities.
- Actual main Game/Renderer checks use the generated seed-69 room: normal controller updates produce six shots and visible wandering during the test. Mouse/keyboard editing, current-attack retention, subsequent tuned shots, reset, export/load/rejection, staged map, regeneration, floor descent, retry and fresh Game are exercised. God mode is test-only, absent from the interactive handoff.
- Separate main-executable launches cover the accepted schema-5 preset, previous schema-7 Spider preset, custom schema-8 Pooter export and remembered settings without a CLI preset. The original external export's SHA-256 remains unchanged.

The native motion captures explicitly exclude collisions. At the new scale their supplied edge coordinates intersect the retained, larger DW body, so that arithmetic fixture uses a point-sized body; generated-encounter tests retain the real 0.45 radius. This is not a collision bypass in gameplay. An initial main-game assertion supplied room 0 to a room-indexed flight check while testing room 2; its index was corrected.

The first broader regression exposed an older airborne-player-shot test using a 35-tick deadline at eight-unit distance. With the already accepted 8-unit/s shooting, the projectile could not arrive before that deadline and the moving Fly could evade it. The collision fixture now holds the Fly with the existing Stunned state and waits within the actual flight budget; motion is covered separately. Player mechanics were not changed. The elevated-Pooter test also checks a physically clear shot from cover and allows its verified slower travel time. Initial diagnostics remain in `initial-regression.log` and `elevation-diagnostics.log`.

## Remaining and next

**The scoped D06 playtest is accepted.** The user requested the main-game launch, then responded "ok, nice commit!"; see [acceptance record](human-acceptance.json). This accepts the delivered encounter feel, not every native behavior. Full native RNG/distribution, target-helper/status exceptions, actor initialization, animation/global scheduler phase, room/body/shot geometry, masks, champion and morph/offspring lifecycle remain unaccepted. Source hard-mode speeds and other shooter identities are outside this delivery. Existing Fly-to-Pooter morphs preserve their incoming momentum; this integration does not certify the full native morph. The retained movement safety cap and canyon edge mapping remain adaptations. No complete first-floor or overall combat-difficulty parity is claimed.

**Next selectable: D07 — damage, enemy HP and incoming hits together.** Enemy pressure has scoped playtest acceptance; production damage/HP changes still require D07 selection. D04–D06 are included in the containing checkpoint commit. The bulk automatic parity effort stays paused.
