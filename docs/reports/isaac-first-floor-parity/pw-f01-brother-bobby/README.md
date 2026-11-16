# PW-F01 — Brother Bobby

Selected explicitly on 2026-11-16: “Yes, strat with PW-F01 — Brother Bobby.” The main-game delivery and developer checks are complete; the user accepted the scoped playtest and requested this checkpoint commit. See [acceptance](human-acceptance.json). The unrelated bulk parity effort remains paused. This checkpoint also preserves the previously accepted D11b work.

Collectible8 now belongs to the bounded opening-floor treasure offering alongside Sad Onion1 and Cricket’s Head4. It creates one friendly following actor per owned copy. It fires while the player holds the existing firing control, with its own cooldown, source damage3.5 (11.2 internal units), velocity and falling-flight clock. It neither blocks the player nor counts as a hostile. Existing player weapon modifiers do not subscribe to familiar attack events. Native familiar-specific synergies are not enabled.

**TUNING → SHOOTING → TREASURE → FAMILIARS** independently edits following, shot interval, damage and shot speed in5% increments (25–200%). Movement applies on the next familiar update. A committed firing wait and flying projectiles retain their settings; new waits/shots use the new settings. The source counter is discrete at the explicit30Hz boundary, so fractional interval overrides round up to an update. Treasure pool changes, including the labelled fixed-Bobby comparison, wait for Apply map changes. Regeneration keeps ownership/configuration and reconstructs companions; retry starts a fresh build with retained configuration.

Schema37 exports/loads/remembers the familiar controls, stages pool edits and migrates schemas1–36 through exact additive catalog fingerprints. The original user165% preset remains untouched. Existing campaign checkpoints/history serialize the owned collectible key. Campaign recovery records interruption; it is not a live expedition-resume system. Complete gameplay-save continuity remains PW-C01/D18 work.

## Source and explicit adaptations

[source/manifest.json](source/manifest.json) pins the installed Repentance1.7.9b executable and item/entity/treasure definitions. `PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-brother-bobby.py --check` reproduces the bounded captures without modifying the installed game or process.

- 315 original ordinary FollowParent-tail/free-physics states, supplied parent positions and empty trinket effects. The20-coordinate following radius, nonlinear approach and.8 retention are preserved.
- 80 original cooldown-decrement/variant-interval/reset states under supplied held/released input. Ordinary variant1 uses16 updates. This does not prove every native actor scheduler or input-wrapper path.
- 48 original tear-creation-entry cases through the first factory boundary, with actual ordinary inventory queries and supplied player velocities/cardinal aims. Damage stays3.5 when player damage changes; scale.8, zero additional falling acceleration/base, launch10 plus owner-velocity inheritance with minimum10 resultant speed.
- XML confirms familiar collectible8, actor3.1, treasure weight1 and no item achievement gate. Registry membership is not complete effect acceptance.

Bobby’s bullet uses source scale.8 relative to the retained ordinary player bullet; it can pass above low cover just as other projectiles do. DeathWard uses its accepted shooting-space ratio11/260, existing ordinary tear flight model and explicit30Hz familiar boundary. Eight-direction aim, current world elevation/colliders, procedural blue companion model, a restricted three-item offering and canyon seed mixing are deliberate adaptations. Source actor factory/initial-height wrapper, parent-chain construction/cache, native RNG, collision/knockback, familiar synergies and full live native equivalence remain unaccepted. The current supported copy chain is rebuilt from stable owned keys; it does not implement the full source familiar inventory/cache system.

## Review and remaining work

Interactive review launched successfully with normal health, muted sound and165% zoom; see [launch record](interactive-launch.json). Natural witness: seed7, displayed room8, opening-floor treasure. The previous D11b seed7 now selects Bobby from the expanded pool; seed4 is the current natural Cricket witness. Historical D11b evidence remains historical.

```sh
build/deathward --expedition --seed 7 --review-room 8 --mute --save /home/kambo/.local/share/deathward/reviews/pw-f01-brother-bobby/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

Human check: collect the blue companion figurine; walk/fire in an ordinary encounter; leave and return to confirm one companion remains. Eight focused core suites, actual Bobby/Cricket Game/Renderer checks and ordinary CLI loads of schemas5/36/37 pass. Following/cadence are exercised at30/60/120Hz, including release and pause. The accepted user preset retains its original SHA256. See [validation](validation.json), [gameplay cases](gameplay-cases.log), [mouse/UI checks](game-input.log), [CLI checks](cli-validation.json), [companion preview](bobby-following.png) and [tuning panel](bobby-panel.png). The exported95%/105% review preset is a labelled developer test artifact; the human launch uses the original preset and100% familiar defaults. Full native wrapper/synergies and live save/resume remain unfinished. The user explicitly selected PW-A01 Yum Heart next; active-item implementation is still pending.
