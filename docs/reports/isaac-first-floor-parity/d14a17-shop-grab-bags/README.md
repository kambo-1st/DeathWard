# D14a.17 — ordinary shop grab bags

Selected explicitly by the user after the source audit: “Implement ordinary shop grab bags—the actual missing stock category (recommended).” Accepted batteries are committed as `4763449d`. Main-game implementation and developer verification pass; the user accepted the scoped playtest (“NIce it works, next!”).

## Corrected source identity

The earlier shop report incorrectly called category7 a trinket. Installed Repentance1.7.9b's original dispatcher maps category7 to5.69.1 Grab Bag. Category11 is5.350 Trinket and is absent from the ordinary0–8 stock pool. The existing battery implementation is unaffected. The proposed trinket delivery is superseded by the user's grab-bag selection.

The source price is7coins, before existing random-sale/Steam Sale arithmetic. Original subtype1 contents select2or3 entries, with weights bombs15, keys20, coins15, batteries4, cards4. The generator retains DropRNG4/3/17, copied weighted RNG5/9/7, the unused draw and each ordered spawn seed. `capture-shop-grab-bag.py --check` reproduces520 numeric contents cases,48 category resolutions and48 prices from the pinned executable. It intercepts only output-list append; the original choice/count/seed instructions execute. Full actor/factory/payment/physics/scheduler equivalence is not claimed.

## Main-game behavior

Naturally selected category7 now produces the owned Western single-sack model in compatible basic or upgraded shops. Touching it with sufficient funds pays once, marks stock sold and releases supported contents. No extra category roll or substitution into an unrelated stock slot is added. The model uses ordinary mesh lighting and shadows; its editable source and bake script are retained.

Contents are fixed at bag admission. Capacity or terrain delays retry the same rewards without another payment or reroll. Revisit retains sold state and outstanding deliveries. Apply explicitly resets floor stock while preserving build/configuration; retry starts a fresh expedition. Existing canyon geometry, map controls, walking/shooting, eight-direction controls, universal dodge and165% view remain intact.

Batteries released from bags use the accepted charge/capacity/timing rules and cost nothing to collect. Coins, ordinary single/double keys and dynamite use existing pickup actors. BOGO applies at bomb birth as before. Card outcomes use the existing bounded Temperance adapter. **Full card-pool resolution, golden-key and troll/golden-bomb identities remain unsupported**: special key/bomb requests retain their resolved identity without reroll or conversion, and remain unspawned. Therefore source contents-category selection is verified, but complete contents delivery parity is unfinished.

## Live configuration

TUNING → REWARDS → SHOP → GRAB BAGS edits purchases on/off and base price0–30 in one-coin steps. Edits apply to future purchases including existing unsold bags, without altering resolved contents or sold state. Schema61 exports/loads/remembers these controls and migrates1–60 to enabled/price7. Map changes remain staged until Apply. The selected schema60 user export is preserved unchanged.

## Verification / review

Six focused CTest suites pass: grab bags, batteries, shop stock, source stock reference, donation milestones and balance presets. This covers520 native contents comparisons, source price checks, naturally selected bags at75%/100%/150% room sizes, insufficient funds, live enable/price edits, Steam Sale, once-only purchase, capacity-deferred same-identity rewards, free battery recharge, revisit, Apply, floor transitions and schema60→61 migration/roundtrips/atomic invalid rejection.

Actual Game/Renderer checks pass for mouse tuning, normal movement into the bag,7-coin payment, coin/dynamite output, export/load/remember with pending map changes, Apply, retry and a fresh process. That check caught and fixed the new-action whitelist and missing draft/live preset copies. The Apply fixture now moves away before regeneration, since remaining on reset stock correctly permits another touch purchase. Four separate CLI loads (schemas58/60/61/custom61) retain165% zoom and the expected settings. Screenshots and logs are preserved here. No pixel/performance claim is made.

The interactive review is running; command, isolated save and preset are recorded in `interactive-latest.json`. The direct review uses seed5, displayed room7, naturally selected bag seed3656583694: one coin and one ordinary dynamite pickup, price7. Only20 labelled test coins and four red half-hearts are supplied; no forced bag contents or god mode. The original user's schema60 export remains byte-for-byte unchanged. `test-custom-preset.json` is automation-only (purchases off/price8/pending room-size edit); `review-preset.json` is the migrated user baseline.

1. Walk into the **GRAB BAG / 7 COINS** sack: money changes20→13 and the sack releases coin/dynamite pickups.
2. Collect both. Leave/revisit: the bag stays sold and neither reward repeats.
3. TUNING → REWARDS → SHOP → GRAB BAGS exposes live enable/price controls. Apply explicitly resets this floor for another test; move away from the stock first.

Next selected after scoped acceptance: checkpoint, then the rare bomb outcomes currently retained without spawning. Golden-key behavior and full card coverage remain separate dependencies; rare bomb outcomes are now selected; no bulk parity resumption.

Unfinished: rare downstream pickup variants and full card pool; source descriptor/seed/profile/factory/physics/scheduler equivalence; non-shop and special sacks; donation milestone items; remaining special rooms/full-floor allocation and live expedition save/resume. Pixel/performance work remains deferred.
