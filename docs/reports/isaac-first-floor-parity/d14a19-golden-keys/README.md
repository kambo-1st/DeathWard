# D14a.19 — golden keys from ordinary shop grab bags

Selected after the user accepted D14a.18 and requested “itasawesome commit and continue”. The accepted Troll/Megatroll checkpoint is committed as `c7815541`. Golden-key delivery is enabled, developer-verified and scoped human-accepted on2026-11-20 (“its its perfect whats next?”). See [acceptance](human-acceptance.json). Its checkpoint commit remains pending. Full native acceptance is still open.

A naturally resolved key subtype2 now produces a golden key. Collection grants free ordinary lock use for the rest of the current floor, without changing the finite key count. It works at zero or99 ordinary keys; collecting another admitted golden key is idempotent. Room travel and testing Apply preserve the owned flag. Successful descent clears it; a refused descent preserves it. Retry/new expeditions start without it.

The existing bag selector, subtype odds, single purchase and original content seed remain intact. Disabled or capacity-blocked golden requests wait without rerolling or charging again. Already admitted keys keep their collection state when future drops are disabled. Other key producers retain their previous scope; this does not enable golden outcomes in all layouts, clear rewards or chests.

## Primary evidence and limits

[Native capture](source/manifest.json) executes the pinned installed Repentance1.7.9b executable, SHA256 `04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`:

- Twelve admitted collection cases at ordinary counts0/1/2/5/98/99, with and without a pre-existing golden flag. The original code sets the flag, leaves the count unchanged and consumes the admitted pickup.
- Twelve ordinary UseKey cases. A golden key succeeds at zero finite keys and consumes none; ordinary stock still spends one when available.
- Eight conditional floor-reset cases. The captured original slice clears golden resource flags for argument0 and preserves them for argument1, leaving finite stock unchanged. Complete native floor callers are outside this capture; DeathWard maps successful descent to expiration.

[Extracted golden-key animation metadata](animations/manifest.json) confirms Appear33, DropSound25 and Collect12 at30Hz. The existing key timing path therefore applies. Actual Simulation checks cover30/60/120Hz partitions. Idle42 and DoorOpen88 metadata are preserved but their native sprite playback is not implemented. Rendering reuses the owned Synty key mesh with a gold scene material, shared lighting and shadows. HUD and pause inventory show `+ GOLD` separately from the finite count.

These checks exercise original code with supplied state, not a new live native playthrough. Earlier collision/eligibility callbacks, native mass/grid/bounce, complete scheduler/floor callers, character/item modifiers and full actor equivalence remain open. The retained canyon placement, contact and navigation paths are explicit adaptations. Native global seed/order mapping is not claimed.

## Live configuration

**Tuning → Rewards → Shop → Grab Bags → Gold Keys** enables or pauses future golden-key admission from opened bags. It does not revoke an acquired golden key, delete a born actor or reroll its request. Re-enabling admits the original pending request when space is available. Ordinary keys and bag purchases remain independent.

Schema63 exports, loads and remembers `grab_bags.golden_keys`; older presets migrate to enabled. Invalid types and altered reference values are rejected. Accepted movement, shooting, HP, universal dodge, eight-direction controls, canyon dimensions/routes and165% zoom are retained. Pending map changes still require Apply. Configuration persistence does not save an acquired golden key or constitute live expedition save/resume.

## Short human check

Natural **seed940 / displayed room7** has a bag containing one ordinary dynamite pickup and one golden key, using stored bag seed3432815521 and golden-request seed768641475. The same contents are verified at75%/100%/150% room size.

```sh
build/deathward --expedition --seed 940 --review-golden-key --mute --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d14a19/campaign.save.balance/export.json --save /home/kambo/.local/share/deathward/reviews/first-floor-d14a19/campaign.save
```

The optional review supplies20 labelled test coins, zero ordinary keys and a **labelled test lock on the existing shop exit**. This lock is a review fixture because normal first-floor shop/treasure doors retain their accepted free-entry policy. Stock and bag contents are naturally generated; no golden key is granted in advance. God mode remains off. Normal expeditions do not receive this fixture.

1. Walk onto the bag to buy it for7coins, then collect the golden key.
2. Check the HUD reads `KEYS 0 + GOLD`.
3. Click through the marked exit. It opens while ordinary keys remain zero.

Death retry repeats the test fixture. Apply regenerates the floor under normal lock rules and retains owned gold; it does not recreate the artificial test lock. The new review uses a separate save/preset directory; the user's D14a.18 export is untouched.

## Verification

- Main game builds. Six focused suites pass: golden keys, ordinary keys, keyed doors, bag bombs, shop grab bags and preset contract. See [tests.log](tests.log).
- The golden suite compares actual collection/spending with24 native cases; checks no early collection, once-only cleanup, six denied lock conditions, repeat unlocks and custom testing costs; and exercises natural purchase, pause/capacity/identity, reachability, inactive rooms, revisit, Apply and successful/refused descent at three generated sizes.
- Actual Game/Renderer passes natural walk-to-purchase/collection, zero-key queued exit travel, mouse tuning, export/load/remember with staged map edits, Apply, retry and fresh startup. [Reproduction harness](verify-game.py); [game log](game-review.log). Dropped-key, collected-HUD and tuning screenshots were inspected.
- Four fresh CLI processes load schemas61/62/63/custom63, preserving165% zoom and enabled/disabled golden-drop settings. See [cli-loads.json](cli-loads.json).
- The native capture reproduces byte-for-byte with `capture-golden-keys.py --check`. The first predicted review seed wrongly assumed recorded-shop descriptor seeds; actual ordinary bag shops use their existing unrecorded-shop fallback. The corrected seed940 is verified in generated Simulation and Game, without changing generation or RNG policy.

## Unfinished / next proposal

The accepted delivery's checkpoint commit; other golden-key producers, special/locked chests and full card pools; remaining milestone items, special rooms, full-floor allocation/acceptance and live expedition save/resume; full native eligibility/physics/scheduler/RNG/modifier/floor equivalence. Pixel/performance work remains deferred.

Next proposed: commit this accepted checkpoint, then **D14a.20 locked golden chests**: spend one ordinary key or use the floor's golden key, open once and retain the accepted chest geometry/rendering. The user subsequently selected that proposal and the D14a.19 checkpoint commit (“yes you are right, lets go!”); implementation is the next delivery. Bulk parity remains paused.
