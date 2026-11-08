# Enemy movement blocks live HP acceptance

**Enemy movement first. Live damage/HP acceptance remains on hold. A private movement-only candidate is now implemented; see [candidate evidence](candidate/README.md). No production motion or HP change has been applied.** Paused-body HP/count checks remain valid within their recorded scope; live encounter pressure is not an accepted HP verdict.

## Reproduced mismatch

A headless actual-Simulation probe runs each of the five encounter identities alone in an open field for two simulation seconds. It keeps player health protected for diagnostics, has no firing or incoming knockback, and records current velocities. This is an isolated movement measurement, not the earlier combat playtest. Both Gapers have sufficient open distance to establish sustained pursuit without reaching the stationary player.

- Ordinary Gaper settles at about **2.075 times accepted player walking speed**.
- Awakened Frowning Gaper settles at about **3 times accepted player walking speed**.
- Spider bursts in this supplied witness exceed **5 times player speed**; its full burst/pause/native sequence needs separate comparison.
- Horf remains stationary; Pooter wandering is variable. Do not assign a fabricated common fixed walking speed to either.

The Gaper controller uses source momentum/force/retention at a 30 Hz NPC clock and the old .1 world conversion. The accepted player now uses a separate walking calibration at Speed 1. The generic EnemyMovementMultiplier is not the explanation for these Gaper values: their dedicated source controller does not use it.

A fresh bounded execution of the pinned native player movement instructions for 360 held-input invocations reaches steady velocity **4.4142384529 native coordinates per player invocation**. Existing native update-phase evidence establishes ordinary 60 player / 30 NPC target dispatches, while live elapsed-time delivery and full actor/geometry acceptance remain open. The native Gaper open-route recurrence uses .7 retention and force×2 at long distance. On that documented basis, ordinary/Frowning chase velocities are about **.376/.544 of native base player movement**, not the current above-player ratios. This is a concrete conversion/relative-speed mismatch, not evidence that enemy HP should be reduced to compensate.

The force/retention values and controller path/arrival branches are preserved in the earlier pinned `gaper/source/movement-manifest.json`. Existing per-invocation matches do not certify the resulting world conversion. A correction must align player/enemy coordinate and clock conventions and verify per-enemy movement/acceleration/burst behavior. Independent guessed speed sliders or HP changes would not resolve this issue. Room/collider and enemy projectile conversion also remain calibration questions; no whole-game native equivalence is claimed.

## Evidence and next gate

`current-motion.csv` and its standalone C++ probe contain actual current-build samples for Frowning Gaper, Gaper, Horf, Pooter and Spider. `native-player-probe.json` records a fresh original-code steady-motion witness and pinned executable hash. `validation.json` separates measured current behavior, executed bounded native player behavior and derived chase ratios. The initial diagnostic enabled no candidate. The subsequent private candidate is described below.

The live HP window is stopped to avoid asking for an invalid balance verdict. Next required work is source-grounded enemy/player movement conversion and per-actor movement verification before reopening that encounter. Preserve HP source records/body-count checks. Do not promote the private damage/HP pack or change global balance while this blocker is unresolved.

Still unfinished: corrected and verified relative movement for the encounter roster; matched live/native timing, geometry and NPC projectile calibration; then the HP encounter verdict and consistent remaining-roster/boss units. Earlier native damage/item/AI/health acceptance gaps remain. No production gameplay was changed by this diagnostic.

## Subsequent candidate checkpoint

[Private movement review](candidate/README.md) now applies a source-derived player-relative conversion to the selected controllers. Seven suites pass, including preservation of production HP/attacks and open-space trajectory similarity. This is not independent native AI acceptance: Spider/Pooter behavior, live timing, projectiles and geometry remain unverified. The Gaper chase ratios are derived from pinned native arithmetic and bounded native player execution. No complete live Isaac actor comparison has been performed.

## Native player reference follow-up

[The new native reference](../native-motion-reference/README.md) executes the original baseline Speed write (1.0), then verifies 1,840 bounded source physics/steering states. An explicit private player adapter matches 2,760 Simulation states, including native stopping inertia. Source geometry, full NPC timing/AI and projectile calibration remain unfinished; the review display still uses an adapted scale. HP acceptance stays held.
