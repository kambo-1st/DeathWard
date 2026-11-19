# D14a.11 — recorded keeper destruction and drops

The user accepted D14a.10 ("it its works focus on next") and selected its proposed continuation. The accepted recorded-shop checkpoint is committed as `22a86e73`. This delivery adds keeper demolition to that arrangement, using the retained merchant wagon. The user accepted the scoped seed68 handoff ("it works, next!") and selected the checkpoint plus blood-machine explosion continuation. See `human-acceptance.json`; full native shop acceptance remains open.

Accepted checkpoint commit: `a09da6e8`. The selected machine continuation is now enabled; see [D14a.12](../d14a12-blood-machine-explosions/README.md). Its human review remains pending.

## Main-game behavior

An ordinary dynamite blast can destroy the recorded shop keeper/wagon. Its five source HP stays separate from outgoing internal damage (×3.2); ordinary shots do not damage it. Destruction removes the wagon and its physical/navigation obstruction, leaves small charred debris, and resolves its drops once. Shop stock remains for sale. Existing legacy merchant arrangements are unchanged.

The native ordinary selector can choose nothing, two coins or two ordinary Spiders, with earlier rare collectible checks. Steam Sale64 is supported and can be collected for the existing price discount. Head of the Keeper429 and Coupon521 are not implemented: production explicitly supplies a Steam-Sale-only eligible catalog. The selector is verified with all eligibility masks, but that does not enable the missing items or certify their native unlock conditions.

Chosen drops wait for available actor capacity/placement without rerolling. Coins/items and living shop Spiders survive room departure and return. Spiders reuse the accepted ordinary movement/HP; safe grounded placement replaces native thrown arrival. The shop stays cleared, without a second combat-clear reward or new door seal. Apply resets floor actors/keeper state while retaining build and configuration; floor advance and retry retain configuration, and retry starts a fresh build.

## Live configuration

**TUNING → REWARDS → SHOP → KEEPER** has destruction and reward switches plus source rolls / explicit test outcomes (nothing, coins, Spiders, Steam Sale). Edits affect future blasts/destruction, never resurrect a keeper or reroll an already resolved drop. Map edits remain staged until **Apply map changes**, including unrestricted testing regeneration.

Schema56 exports, loads and remembers these settings; schemas1–55 migrate to enabled destruction/rewards and source rolls. Accepted walking, shooting, dodge, HP, room sizes/routes and default zoom are retained. Configuration persistence is distinct from live expedition saving.

## Preserved source evidence

`source/manifest.json`, `source/native-drops.csv`, preserved assembly windows and `source/entity.json` record pinned installed Repentance1.7.9b executable/XML evidence. `scripts/isaac-reference/capture-shopkeeper.py` reproduces the capture.

- Original ordinary drop branch: 4,120 supplied cases across eligibility masks0/1/3/7, including identities, order, output seeds and final RNG state, compared against the C++ consumer.
- Six original entity-initialization slices verify DropRNG starts from InitSeed with shifts4/3/17. DeathWard supplies its descriptor-derived keeper slot seed; global factory/seed-stream equivalence is not claimed.
- XML: keeper17.1, baseHP5, stageHP0, no contact damage, no room-door shutdown. The controller and vulnerability query support stationary, ordinary-shot-excluded keeper behavior; the complete native damage wrapper is not executed by this capture.

## Verification and playtest

Developer verification includes real dynamite/projectile interactions, all five modes at three room sizes, low-damage five-blast depletion, live gates, capacity-deferred Spider births, coin/item collection, revisit, Apply, floor transition and schema round-trips. Seed68 is a naturally selected matching shop with an unforced two-coin keeper result. Five focused CTest suites pass. The actual Game/Renderer check covers mouse entry to Keeper tuning, B-key dynamite, supported outcomes, stock purchase, live controls/export/load/remember, Apply and retry. CLI preset versions48/55/56 load successfully. See `verification.json` and the saved logs.

The isolated review loads the latest D14a.10 user export and keeps zoom165. Original D02 and latest D14a.10 exports are not overwritten. The short shop-stock review supplies **20 test coins and four red half-hearts**, god mode off; these are review overrides, not starting balance.

```sh
build/deathward --expedition --seed 68 --review-shop-stock --mute --balance-preset docs/reports/isaac-first-floor-parity/d14a11-shopkeeper/review-preset.json --save /home/kambo/.local/share/deathward/reviews/first-floor-d14a11/campaign.save
```

Walk beside the wagon, press **B**, and move away. The wagon should disappear and two coin actors appear; collect them, buy stock and leave/revisit. For other outcomes, choose a clearly labelled test mode and use Apply/retry for a fresh keeper. The source outcome remains selected in the supplied review preset.

## Unfinished / next proposed

Scoped human D14a.11 acceptance is recorded; this is the accepted checkpoint. Full native damage batching, factory/profile/unlocks, Spider thrown arrival/scheduling/collision, global RNG and shop/deal side effects are not accepted. Missing rare collectibles remain unsupported. Donation-machine eligibility, blood-machine explosion destruction, remaining special rooms/full-floor allocation and live expedition save/resume remain open; pixel/performance work stays deferred.

Next selected: D14a.12 blood-donation-machine explosion destruction as a separate bounded main-game delivery, with native evidence, live/export/load controls and a short human check.
