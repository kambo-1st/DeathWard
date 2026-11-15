# D12a — Ordinary shop red-heart purchase

Selected on 2026-11-15 after the user authorized the D11a checkpoint and the proposed first shop delivery. D11a is committed as `7d97f72d`. D12a is enabled in the main game. Native reference, generated placement, transaction, Game/Renderer and preset/CLI checks pass. The user acknowledged the handoff with “ok, continue” and selected another shop offering. This is scoped acknowledgment, not a separately observed playtest or full native acceptance. The user subsequently authorized committing D12a/D12b and continuing with D12c; both are included in this checkpoint.

## Scope

An ordinary opening-floor canyon shop offers one full red heart on the floor at the second stock position, cell (7,4), of installed special-room 2.0.0. The retained canyon cell adapter maps that position into the dynamic DeathWard room. Touch purchase heals up to two red half-heart units and charges the displayed price once. Full red health, insufficient money, death, combat or a modal prevents purchase. Sold state survives leave/revisit. Explicit testing Apply resets floor stock while preserving the player's build and accounting; retry starts a new expedition.

The scoped source shop bypasses DeathWard's old medicine/power/dynamite menu. Its unrelated free custom coin piles are removed after the original generation draws, keeping later rooms' coin stream intact. Other floors/modes/services retain their existing shops. The accepted free opening-floor entrance and optional single-entrance shop remain.

This is one supported stock slot, **not a complete native shop layout or pool**. The original template contains two generic shop-item 150 slots, a shopkeeper, rocks and a donation machine. Its second slot is deliberately pinned to a full red heart here; full stock resolution, the other offering, native scenery/actors/machine and native shop-level selection are unfinished. Existing canyon scenery and shopkeeper remain. No unsupported result is claimed as implemented.

## Source evidence

[Manifest and recorded template](source/manifest.json) preserve the installed 1.7.9b executable and complete special-room file hashes. The native ordinary pricing function executes with supplied shop/descriptor/ordinary empty-inventory inputs: 60 full/half-red cases produce 3 coins. The original red-admission helper and its type/capacity calls pass 49 cases. The recorded collection dispatch gives the full red heart two half-heart healing units. Existing source-aware health and red-heart collection timing supply the gameplay consumers.

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-shop-heart.py --check
```

The [shop wiki](https://bindingofisaacrebirth.wiki.gg/wiki/Shop) was consulted as secondary context; the installed native code supplies this delivery's numeric price. Discounts/sales, Restock, co-op, alternate characters/items, factory scheduling and full native pickup physics are outside the verified case.

## Tuning and persistence

**TUNING → REWARDS → SHOP** exposes a stock-policy switch staged until Apply map changes and a live price in one-coin steps, 0–15. Reference price is 3; all other values, including free, are explicit testing overrides. A live edit changes the displayed unsold price and the next eligible contact, never restocks a sold heart. Export/Load/Use next expedition carry both settings through schema 30, with schemas 1–29 migrating to enabled/3 while preserving accepted map, movement, shooting and zoom.

`--review-shop-purchase` is an explicit test start in the generated shop with two full red hearts and at least three coins; retry repeats it. This resource grant and travel are labelled and never enabled by a normal launch or a preset. The ordinary generated offering uses the same purchase code with the expedition's actual health and earned coins.

## Verification and human check

- [Native recheck](native-check.log): 60 ordinary prices, 49 red-admission cases and the recorded source stock positions.
- [Core scenarios](core-tests.log): 27 generated size/route configurations, exact payment/healing/refusals, sold revisit, live price, Apply/floor boundaries and a purchase funded by normally collected coin actors.
- [Five focused suites](regression-tests.log): shop heart, treasure upgrade, room lock policy, mission shop and preset contract.
- [Game/Renderer interaction](game-input-ui-final.log): actual mouse purchase, sold revisit, keyboard/mouse tuning, staged Apply/Load, export/remember, retry and normal launch without review resources. The first input run exposed a missing live/launch price assignment; both are corrected and the nondefault-price reload check passes.
- [Treasure regression](treasure-input-regression.log) and [legacy Mine/Canyon shop controls](legacy-shop-input.log) pass. The [broad keyboard fixture](keyboard-input-isolated-final.log) also passes: it explicitly selects legacy lock/menu policies, targets a locked treasure door and isolates supplied inventory from nearby generated key pickups. Dedicated suites retain source-policy coverage.
- [CLI loads](cli-validation.json): original schema 5, previous schema 29 and exported schema 30 all launch with 165% zoom; the schema 30 custom 4-coin price survives a fresh process. [Custom test preset](shop-heart-preset.json) is separate from the unchanged original user preset.
- [Before purchase](shop-heart-before.png), [after purchase](shop-heart-sold.png) and [shop tuning](shop-heart-panel.png) were visually inspected. The heart and price are clear of the existing shop scenery.

Direct review from the repository root:

```sh
./build/deathward --expedition --seed 69 --review-shop-purchase --mute --save /home/kambo/.local/share/deathward/reviews/d12a-shop-heart/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

This starts in displayed room 7 with two full red hearts and three coins. Walk onto the 3-coin heart: health should become three full hearts and money 0. Leave/revisit: the bought heart must remain absent. The review flag grants only this explicit test setup; remove it for an ordinary expedition with earned funds. TUNING → REWARDS → SHOP allows live price changes; stock-policy changes require Apply map changes.

## Still unfinished

Broader D11a acceptance gaps remain open. Full shop stock/eligibility/profile selection, other purchases/item effects, discounts/Restock, donation machine/scenery/native actors, native physics and gameplay-save continuity remain open. No full native shop or floor acceptance is claimed; unrelated bulk parity remains paused.
