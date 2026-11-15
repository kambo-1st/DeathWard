# D10a — ordinary dynamite fuse and blast

Selected on 2026-11-15 after accepted D09d was committed as `12eccfa1`. D10a is enabled in the main game, developer-verified and human-accepted on 2026-11-15; the accepted delivery is included in this checkpoint. Bulk parity remains paused.

## Main-game scope

Ordinary inventory charges use the pinned Repentance 1.7.9b countdown/damage/radius/player-damage rules through explicit DeathWard adapters. B and the HUD place the shared single-stick model; no ordinary throw controls return. Fuse sparks, explosion particles and sound remain unchanged. Universal dodge and accepted player/enemy/shooting/map/view settings are retained.

TUNING → COMBAT → DYNAMITE provides fuse duration (25–400%, 5% steps), blast size (25–300%, 5% steps), enemy damage (1–500 source units, 5-unit steps) and self damage (Auto, or 0–6 hearts in half-heart steps). Auto uses the source blast-damage threshold. Zero is an explicit testing override. Each new charge snapshots all values; lit charges and existing placement cooldowns do not change. Schema25 exports/loads/remembers settings and migrates schemas1–24 with the new ordinary references. Map settings remain staged until Apply; current-floor regeneration clears transients under the existing testing contract.

## Verified source and adapters

The restored bounded reference script executes the installed executable, checks its pinned SHA256 `04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6` and preserves its XML fingerprint. No calculation/RNG/math hooks replace source logic. See [source manifest](source/manifest.json).

- Source ordinary countdown45 reaches zero after45 invocations and enters explosion on invocation46. The explicit30Hz adapter gives46/30 seconds (about1.53s). This is not a new live-native bomb-scheduler measurement.
- Source damage100 converts through the retained3.2 internal-HP units per source HP:320 internal outgoing damage. Incoming player damage uses the separate existing half-heart boundary.
- Source radius is75 at damage≤140,90 for140<damage<175,105 at damage≥175. D10a shares the accepted shooting-distance scale11/260 world units per source coordinate: baseline radius about3.173. This deliberately replaces the reverted archive's0.1 spatial scale and does not claim native canyon geometry. Room size, current Speed and Shot Speed do not change this conversion.
- For ordinary admitted positive damage and ordinary flags, source self-damage is one half-heart below85 damage, otherwise two. Auto retains that rule; the explicit self-damage override is custom testing behavior.

Source verification:48 initializations,82 countdown cases,12 base-radius cases,21 incoming-amount cases, plus6 inherited-velocity and72 historical free-motion records. Movement/inheritance results remain research only; this delivery retains accepted placement/contact kicking and does not enable archived movement adapters.

## Deliberate boundaries

Starting inventory3, current placement cooldown, contact kicking, DW physical recipients/line-of-sight/destruction and custom Braid effects retain their existing contracts. Braid owns its bomb transformation and is outside these ordinary-empty-build controls. Boss/supplied/enemy bombs are unchanged. Special flags/items/characters, source collision and pushing, live bomb scheduler, whole actor/factory/profile/seed equivalence, broader destructibles/keyed doors and gameplay save continuity remain unfinished or unselected.

## Verification and review

Native reference and native main-game/input builds pass. Both focused core suites pass: source matrices, actual fuse/damage at30/60/120Hz and the longest fuse, new-charge snapshots, radius/self-damage thresholds, zero override, dodge immunity, Braid/legacy isolation, schema25 round trips, older migrations and rejected overrides. [Core checks](core-tests.log).

Three actual Game/Renderer checks pass: new mouse/keyboard controls; lit-charge retention while tuning; reset; invalid-file rejection; staged Apply; export/load/remember; floor/death retry/fresh-session persistence; ordinary source32 rock access and once-only pickups; canyon/mine placement and contact kicking. Source32 still needs two charges and ends with four dynamite and full starting health when retreating. [Tuning check](dynamite-balance.log), [room check](bombs.log), [placement/kicking](dynamite.log), [viewed tuning panel](tuning.png).

Three separate CLI loads pass with normal six half-hearts and165% zoom: original schema5 preset, schema24 reward-off preset and exported custom schema25. The user's original export remains byte-identical. [CLI evidence](cli-validation.json). The [custom test preset](custom-test-preset.json) deliberately uses zero self-damage and altered bomb values; it is not the reference handoff.

Corrections during verification: float age accumulation delayed the120Hz detonation by one substep; double-precision accumulation fixes it. The existing tuning action guard needed the new action range. The first panel placed Reset too close to the preset footer; the final viewed layout separates them. The invalid-load fixture correctly paused gameplay and now explicitly resumes before testing placement. [Validation and remaining limits](validation.json).

The user accepted the source32, seed129 main-game review and requested this commit: [human acceptance](human-acceptance.json). The review used normal six half-hearts, three charges and the user's165% preset. This is scoped playtest acceptance, not full native scheduler/physics/item equivalence.

Remaining: live-native bomb timing and complete physical recipients/collision, special flags/items/profile/seed behavior, browser runtime and gameplay save continuity. Next proposed delivery is one ordinary destructible interaction (D10b), with keyed-door spending afterward; neither is selected by this commit request. Reproduce the accepted review with:


```sh
./build/deathward --expedition --seed 129 --review-source-room 32 --mute --save /home/kambo/.local/share/deathward/reviews/d10a-dynamite/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```
