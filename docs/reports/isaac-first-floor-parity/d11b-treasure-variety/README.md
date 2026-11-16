# D11b — treasure-room variety

Selected by “lets go!” after accepted D12f commit `e43d91b1`. This delivery adds Cricket’s Head4 alongside The Sad Onion1 in the main game’s opening-floor treasure rooms. The main executable, six focused core suites, both actual Game/Renderer modes and three CLI preset loads pass. The user accepted the scoped playtest (“nice! Itr works...”); see [human-acceptance.json](human-acceptance.json). Automatic bulk parity stays paused.

One centered, solid pedestal offers one collectible, collected by touching its edge. The Sad Onion keeps its accepted Tears effect. Cricket’s Head uses the ordinary source damage contribution (+0.5 raw damage per copy) and presence multiplier (×1.5 once), with damage-derived bullet size. At source base Damage3.5 one copy produces about6.640783 source damage, adapted to21.2505 internal units. Existing authored weapon modifiers remain after the base adapter. This is not a global replacement of every item’s damage/cache behavior.

**TUNING → SHOOTING → TREASURE** cycles the two-item pool, Cricket test and Onion test. Offering changes wait for **Apply map changes**, which explicitly regenerates the floor and its rewards while retaining the player/build. Independent Onion and Cricket strength controls are live, in5% steps; 100% is the source contribution, other values are testing overrides. Current firing waits and already emitted attacks retain their birth specifications. Export/load/remember/retry carry the settings; loading stages offering changes. Schema36 migrates1–35, preserving accepted165% zoom/map/movement/shooting settings. The original user preset is not overwritten.

## Verified source and adaptations

The preserved installed Repentance1.7.9b executable/XML hashes are in [source/manifest.json](source/manifest.json). Run `PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-cricket-head.py --check` to reproduce the evidence without changing the installed game/process.

- 32 actual native owned-count contribution, ordinary damage-curve and presence-multiplier cases. Other modifier inputs are off; the intermediate raw-cache value is supplied explicitly.
- 32 complete `GetTearHitParams` comparisons with actual inventory queries. At equal cached damage the full104-byte output is identical with/without Cricket. Size follows `.55 + .01*damage + .23*sqrt(damage)`. These ordinary records do not introduce a separate Cricket velocity or knockback multiplier.
- Four ordinary shot-speed-cache cases stay at1, stopping before external callbacks. XML’s `shotspeed` cache flag alone is not an extra stat bonus.
- Both collectible entries have treasure weight1 and no achievement gate in preserved XML. The shared bounded native first-draw weighted-index implementation retains524 source cases, including float boundaries.

The two-entry eligible pool, canyon room/floor seed adapter, inverse mapping of the accepted editable base Damage and relative projectile radius are explicit DeathWard adaptations. Exact native pool/depletion/history/unlocks, whole cache order/other characters/item combinations, pickup animation/factory, source collision/knockback, browser and gameplay-save continuity remain unfinished. Eight-direction controls, universal dodge, accepted walking/shooting/range/HP, canyon room shapes and corridors remain.

## Human review

The review launches with natural pool seed7, displayed room8, normal three-heart health, sound muted and the accepted165% preset:

```sh
build/deathward --expedition --seed 7 --review-room 8 --mute --save /home/kambo/.local/share/deathward/reviews/d11b-treasure-variety/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

Walk to the brown cat head on the pedestal. It collects once and displays DAMAGE UP. Continue into an ordinary encounter: hits are stronger and bullets slightly larger; movement, firing cadence and range stay familiar. **TUNING → SHOOTING → TREASURE** shows owned copies/effective damage and allows live strength comparison. Death retry returns to the review room with a fresh build and retained tuning. The user accepted this scoped playtest; full native acceptance remains open.

See [pedestal preview](cricket-pedestal.png), [tuning panel](cricket-panel.png), [validation](validation.json), [native/gameplay cases](gameplay-cases.log), [Cricket input check](game-input.log), [Onion input check](onion-input.log) and [CLI checks](cli-validation.json). The initial regression log [tests.log](tests.log) records four passes and a stale catalog-hash expectation; the corrected [treasure recheck](treasure-recheck.log) passes. Preview exports with95% strength and the fixed-Cricket CLI preset are labelled test artifacts; the interactive review uses the unchanged original preset at100% strength.

Remaining: checkpoint commit; full pools, other source cache/item interactions, native physical/lifecycle behavior, browser and gameplay-save continuity. Next: inspect the source power-up catalog at the user’s request and select future items. The accepted checkpoint is not yet committed. Further item deliveries require selection.
