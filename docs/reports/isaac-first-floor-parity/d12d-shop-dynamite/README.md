# D12d: ordinary dynamite shop stock

The user acknowledged the centered Western cart and requested “nice commit now, then continue” on 2026-11-16. The cart is committed as `b570950f`. This next bounded shop category is implemented and developer-verified in the main game; the user acknowledged the scoped delivery and requested removing the wagon label. The user subsequently authorized this checkpoint commit and selected soul-heart shop stock. The bulk parity goal stays paused.

An ordinary opening-floor Canyon shop can now offer one dynamite pickup beside Steam Sale when its existing source category schedule selects **8 + 1**, in either order. It uses the existing dynamite model and ordinary bomb pickup/collection timing. It costs **5 coins** before discounts, adds exactly **one charge**, and refuses at99 charges or without sufficient funds. Steam Sale reduces its price to3. Source random sale slots use the existing verified discount arithmetic. Payment and grant happen once at admitted contact; sold stock stays sold on revisit. Dead/modal/combat, appearance and physical-contact gates remain. Ordinary reward/layout bombs stay free.

The existing source-shop master and staged Vary stock / Fixed pair policy control eligibility. Supported pairs are now collectible with red heart, key or bomb. Other pairs retain the previous fixed key/heart fallback without reroll. Steam Sale64 remains a pinned eligible collectible; complete item-pool selection is not implemented. Basic shop level0, ordinary config0, normal profile and the DW floor-seed mapping remain explicit supplied inputs/adaptations. Later floors, other themes, tutorial and service shops keep their existing menus. Canyon geometry, centered cart, controls, walking/shooting, universal dodge and blast effects are retained.

## Configuration

**TUNING → REWARDS → SHOP → DYNAMITE** edits the base price live in one-coin steps, from0–15. Default5 is the source reference; other values are testing overrides. Live edits affect unsold purchases without restocking. Vary stock / Fixed pair stays pending until **Apply map changes**; explicit testing regeneration resets floor stock while retaining player/build/spending. This uses the existing stock-mode switch, without a new independent category toggle.

Schema33 (`d12d-shop-dynamite-v33`) exports/loads/remembers the new price, migrating schemas1–32 with price5. Loading applies price immediately and stages map fields. Floors, retry and future expeditions retain the setting. Invalid/nonintegral prices and mismatched override/reference data are rejected. Exact existing catalog migrations are retained; no new item definition/catalog change is needed. Presets remain separate from gameplay saves. The original165% preset is unchanged: SHA256 `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`.

## Verification

[Native capture](../../../../scripts/isaac-reference/capture-shop-bomb.py) executes the installed Repentance1.7.9b ordinary category resolver `0x7d04a0` for six supplied category1 slots, returning bomb40.1. It executes ordinary pricing `0x7d0950` for30 supplied seed/slot cases, all price5. [Manifest](source/manifest.json), [category outputs](source/native-category.json), and [prices](source/native-prices.csv) preserve these bounded results. Existing D12c whole stock initialization and discount reference comparisons remain passing; full caller/profile/factory/inventory wrapper acceptance is separate.

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-shop-bomb.py --check
```

Seven focused core suites pass across [initial](initial-core-checks.log) and [final](final-core-checks.log) checks: source heart/key/stock/reference, preset contract, ordinary bomb gameplay and preplaced bomb layout. The initial failures were test fixtures: the malformed-schema fixture still named32, and the floor-transition fixture forgot the retained Canyon boss's dynamite supply before departure. The corrected test checks the actual departure inventory exactly; gameplay boss supply was not changed. [Details](core-details.log) include27 new dynamite placement/access configurations (three seeds, three size/ranges, three route lengths), both stock orders, funds/cap/discount/gates, collection timing, sold revisit and Apply/floor carryover; previous27 heart/key placements and cart movement checks also pass.

Four actual Game/Renderer modes pass: [dynamite](game-input.log), [stock](stock-input-regression.log), [key](key-input-regression.log), [heart](heart-input-regression.log). The new mode exercises mouse purchase and discount, sold revisit, live price versus staged stock, keyboard reset, Apply, export/load/remember, retry and ordinary fresh launch. [Three CLI loads](cli-validation.json) verify schemas5/32/33 with retained165% view/map/walking and migrated/custom prices. [Before purchase](shop-dynamite-before.png), [discount](shop-dynamite-discount.png), and [tuning](shop-dynamite-panel.png) were visually inspected. The preserved [custom export](shop-dynamite-preset.json) intentionally uses price6; the human launch below uses baseline5.

## Short human check

```sh
./build/deathward --expedition --seed 4 --review-shop-stock --mute --save /home/kambo/.local/share/deathward/reviews/d12d-shop-dynamite/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

This opens directly in displayed room7 with20 explicitly labelled review coins, three dynamite charges, two full red hearts and normal health rules. Buy Steam Sale for15: coins5 and dynamite price3. Buy dynamite: coins2 and charges4. Leave/revisit: both stay sold. Normal launches grant no review funds. Seed26 exercises the other stock order. The user acknowledged the scoped delivery (“nice!”) and requested removing the “TRADER CART” label. The world label is removed; prices remain visible.

## Remaining work

The user acknowledged D12d and authorized this checkpoint commit, including the wagon-label removal. Broader stock categories, full collectible pool/RNG/eligibility, shop-level/profile/unlocks/layout selection and native descriptor seed mapping remain unfinished. Other discount combinations, Restock/machines, full pickup factory/scheduler/physics/cache, browser runtime and gameplay-save continuity remain open. The user selected the next ordinary soul-heart shop offering with “olets go”; that bounded continuation does not resume bulk parity.
