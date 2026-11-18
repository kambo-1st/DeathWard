# D14a.8 — Mom's Coin Purse and ordinary health/stat pills

Selected on 2026-11-18 after the user's D14a.7 acceptance (“nice it works continue”). Accepted D14a.7 is committed as `96b32557`. This is a bounded main-game dependency of the recorded shop, not the complete recorded shop or the full native pill catalog. The user accepted the scoped main-game handoff on 2026-11-18 ("nice its awesome! Whats next?"); see `human-acceptance.json`.

Mom's Coin Purse195 is now offered in the existing restricted shop pool, alongside Steam Sale64 and BOGO Bombs250, in source XML order with weight1 each. An ordinary new acquisition queues four pill actors. The existing touch/purchase consumer charges once; placement retries retain paid identities and seeds. Fixed Steam Sale/BOGO test choices remain; a fixed Purse test choice is added. Stock selection remains staged until **Apply map changes**. No new pill producers or Temperance/machine content are enabled.

## Short human check

The review opens directly in seed2's displayed room7, at a naturally selected Mom's Coin Purse costing15coins. The existing stock-review option explicitly supplies20test coins and four red half-hearts; it does not grant the item or enable invulnerability. It retains the latest accepted export, including165% zoom, movement/shooting and canyon settings.

1. Walk up to the purse. Four colored capsules appear; the purse disappears and the purchase costs15coins.
2. Walk over one capsule. It occupies the pill slot without being used. **F** uses it; **H** drops it. The HUD buttons perform the same actions.
3. The first use reveals that color's effect for this expedition. Touching another pill swaps the held one onto the ground. Step away before collecting a dropped/swapped pill again.
4. **TUNING → SHOOTING → PILLS** displays effective stats and edits future purse count, consumed stat strength and use/drop binding. Export/load/remember retains these settings. An alternate binding uses **N/comma**, avoiding existing combat/camera/debug keys.

Health and stat effects are the first supported batch. Unknown colors can have negative effects, as in the source game.

## Native evidence and adapter boundaries

`source/manifest.json` pins the installed Repentance1.7.9b executable and XML. `scripts/isaac-reference/capture-coin-purse.py` executes bounded original-code slices with supplied state:

- Eight fresh/not-fresh acquisition cases establish four spawn requests, seed advancement and ordinals. World placement and actor factories are hosted, so this does not verify the native spawn/physics wrapper.
- 515 ordinary color cases verify the shift2/7/9 draw and thirteen-color arithmetic with golden/horse gates off and absent mod callback.
- Forty cache cases verify counter contributions before final cache callbacks/caps; sixty ordinary red-health cases verify health APIs and the last-red-container Health Down conversion.
- `animations/manifest.json` preserves thirteen ordinary ANM2 metadata files, without sprite artwork: Appear36, Drop26 and Collect15 at the explicit30Hz adapter boundary. Pill models are original low-poly capsules; the purse uses the existing rendering primitives.

| Effect | Source change |
|---|---|
| Balls of Steel | +4 soul half-heart units |
| Full Health | Refill red health |
| Health Down / Up | −2 / +2 red capacity; new capacity is empty; Health Down converts to Up when ordinary max-red capacity is at most2 |
| Speed Down / Up | −0.12 / +0.15 |
| Tears Down / Up | −0.4 / +0.5 raw tear stat, through the ordinary fire-delay curve |
| Range Down / Up | −1 / +1.25 source tiles |
| Shot Speed Down / Up | −0.15 / +0.15 |
| Luck Down / Up | −1 / +1 |

The fourteen supported effects are deterministically shuffled once per expedition; thirteen are assigned to the thirteen ordinary colors. This restricted pool and its seed stream are **DeathWard adaptations**, not native pool generation, unlock/profile weighting, RNG order or seed parity. Effects are identified by color and persist through rooms/floors; held ownership and consumed counters are separate from editable base attributes. No unsupported outcome is silently called implemented.

Stat strength multiplies consumed stat contributions live. The retained adapter applies Speed limits0.1–2, Shot Speed limits0.6–2 and Range minimum1 when the relevant contribution is present; these adapter limits and later item ordering are not certified full native cache equivalence. Signed Tears contributions extend the already accepted inverse-base adapter; custom rates above the ordinary cap retain their excess. Existing Onion/Screw contributions resolve once before Cancer, and Screw/Whip Shot Speed contributions remain separate. Luck feeds the selected clear-reward and Mom's Eye consumers. Incoming damage, base balance and universal dodge remain unchanged.

## Configuration and lifecycle

Schema53 exports/loads/remembers `pills` (`purse_count`1–8, default4; `stat_strength`0–2, default1, 5% steps; `binding`0/1). Schemas1–52 migrate to defaults via audited additive catalog hashes. Current mechanics fingerprint: `983f9891046b7e94`. Invalid/incompatible files are rejected before application.

Count changes affect future purchases; queued births keep their selected count/color/seed. Stat changes affect future movement/attacks and the selected Luck consumers, preserving firing waits and emitted projectile specifications. Use/drop keys change immediately. Base tuning stays separate from consumed effects; loading a preset does not erase the expedition's pill history.

Inactive-room pill phases pause. Leave/revisit retains ground actors. Testing Apply retains held pill, color identification, consumed effects and queued paid births (remapped to the new room), while resetting existing ground actors alongside other floor transients. Descent retains the held pill/mapping/effects and leaves uncollected ground/pending drops behind. Retry starts unowned/unidentified with the same seed-derived mapping and retained configuration.

The configuration is persistent; full live expedition save/resume remains D18 work. Pill ownership/effect history is not serialized as a live resumable Simulation by this delivery.

## Verification and unfinished work

See `verification.json`, `game-review.cpp`, `tests/coin_purse_tests.cpp`, native CSV/JSON evidence and the rendered captures for the final check results. Scoped human acceptance is recorded; the D14a.8 checkpoint commit remains pending.

Still unfinished: the full pill pool and unusual/horse/golden effects; native full use/cache/modifier/factory/physics/RNG behavior; the recorded shop's Temperance15/machine and complete layout; remaining special rooms and full recorded-floor allocation/review; full expedition save/resume. Pixel/performance work remains deferred.

Next proposed after this acceptance: checkpoint the accepted bounded pill delivery, then address Temperance15 and its machine dependency as a separate small playable delivery. This report does not authorize unrelated catalog expansion.
