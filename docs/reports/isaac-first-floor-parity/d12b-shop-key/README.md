# D12b — Ordinary shop key purchase

Checkpoint committed as `fbbf0306`; subsequent selected [D12c](../d12c-shop-stock/README.md) adds bounded stock variation and Steam Sale. The delivery details below describe this earlier checkpoint.

The user acknowledged D12a with “ok, continue” and selected the next shop offering. D12b is enabled in the main game and developer-verified. The user authorized committing D12a/D12b and selected D12c with “ok, lets go!”. Both are included in this checkpoint. This is scoped acknowledgment, not a separately observed new playtest or full native acceptance.

## Delivered behavior

The ordinary opening-floor canyon shop displays one ordinary key beside its full red heart. The existing imported key model and D09c collection animation are reused. Walking onto the key costs **5 coins** and adds **one key**, capped at 99. Insufficient coins, full key inventory, death, combat or a modal refuses the purchase without payment. The heart retains its independent 3-coin price and healing. Either purchase order works; neither pickup charges for the other. Sold stock remains absent on revisit.

The key occupies recorded special-room 2.0.0 first generic stock slot **(5,4)**; the heart retains **(7,4)**. Both use the existing canyon spatial adapter. No room geometry, controls, balance or player preset was changed.

This is a pinned key/heart pair, **not native randomized shop stock**. Generic stock resolution, unlock/shop-level selection and source scenery remain unfinished. The existing source-shop master policy still controls whether the room uses floor pickups or the legacy shop menu. The additional key switch only applies while that source shop is enabled. Later floors, Mine/Classic/tutorial and legacy services retain their prior behavior.

## Source and verification

[Source manifest](source/manifest.json) pins the installed Repentance 1.7.9b executable and basic-shop STB hashes. [Native capture](native-check.log) executes the original ordinary pricing function for 30 supplied descriptor/slot cases, all returning 5 coins. The first generic stock coordinate is checked against the previously decoded original template. This excludes sales/discounts and other item/character modifiers. Quantity, cap and animation reuse the existing [D09c key consumer](../d09c-keys/README.md).

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-shop-key.py --check
```

- [Core scenarios](core-tests.log): 27 size/route placement and entrance-path cases; exact payment/refusals/cap; both purchase orders; once-only collection and sold revisit; live price, explicit Apply reset and next-floor inventory/configuration.
- [Heart regression](heart-regression.log), [preset validation](preset-tests.log) and [key/lock/shop regressions](regression-tests.log) pass: six focused suites in total.
- [Actual Game/Renderer input](game-input.log): mouse purchase of key then heart, revisit, mouse/keyboard tuning, staged Apply/Load, export/remember, retry and fresh normal launch without test resources. [Heart input](heart-input-regression.log) and [legacy shop controls](legacy-shop-input.log) also pass.
- [Three CLI loads](cli-validation.json): schemas 5, 30 and 31 preserve 165% zoom and independent prices. The exported schema 31 custom 6-coin key price survives a fresh process. The original user preset hash is unchanged.
- Visual inspection: [before purchase](shop-key-before.png), [key sold with heart still available](shop-key-sold.png), [key tuning](shop-key-panel.png).

## Live tuning and persistence

**TUNING → REWARDS → SHOP → KEY** exposes the additional-stock switch and a price in one-coin steps, 0–15. The default 5 is the source reference; other prices are testing overrides. Price changes apply immediately to unsold stock and never restock a sold key. Stock changes stay pending until **Apply map changes**, whose existing explicit testing regeneration resets floor purchases while preserving build, inventory and spending.

Schema 31 exports/loads/remembers both new fields. Schemas 1–30 migrate to key enabled/price 5, preserving earlier fields including the source-shop master policy, independent heart price, map settings and zoom. Retry/floor changes carry configuration; retry starts fresh stock. Configuration persistence is separate from unfinished gameplay-save continuity.

## Direct human review

```sh
./build/deathward --expedition --seed 69 --review-shop-key --mute --save /home/kambo/.local/share/deathward/reviews/d12b-shop-key/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

The explicit review starts in displayed room 7 at 165% zoom, with **8 coins, zero keys and two full red hearts**. Buy the key: money becomes 3 and keys 1. Buy the heart: money becomes 0 and health three full hearts. Leave and return: neither offering should reappear. Retry repeats the labelled test setup; a normal expedition receives no review resources or travel. The existing `--review-shop-purchase` remains the separate three-coin heart review.

## Still unfinished

Full native stock/eligibility/profile/shop-level selection, other purchases and item effects, discounts/sales/Restock, donation machine/native scenery/actors, full pickup factory/physics, browser runtime and gameplay-save continuity remain open. Next proposed after review: source-based shop stock selection instead of the fixed pair. No automatic bulk parity resumption is authorized.
