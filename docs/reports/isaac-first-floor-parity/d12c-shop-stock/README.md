# D12c — Bounded source shop stock and Steam Sale

D12a/D12b are committed as `fbbf0306`. The user selected the proposed D12c source-stock continuation with “ok, lets go!”. D12c is integrated in the main game and developer-verified. The user acknowledged this scoped delivery and requested its commit on 2026-11-16. See [human acknowledgment](human-acceptance.json). Full native shop acceptance is not claimed.

## Playable scope

Opening-floor ordinary canyon shops use the original normal-mode/basic-config category schedule under a supplied shop level of zero. If its first two categories are a collectible and either a full red heart or ordinary key, those categories occupy their source first/second generic slots (5,4)/(7,4), through the retained canyon adapter. The collectible is pinned to **Steam Sale (64)**, an eligible installed shop-pool member with a working price effect. This is one bounded collectible dependency, not the native collectible pool resolver.

Unsupported category pairs retain the prior fixed key/heart pair. They are not rerolled. The partial coverage and fallback are deliberate limitations, not full native shop distribution. Existing source-shop and additional-key switches remain; suppressing a key does not replace it. Basic shop level, template and normal profile are supplied inputs, not verified full unlock/room selection. Later floors, Mine/Classic/tutorial and services retain their prior menus.

Steam Sale costs **15 coins** before discounts. Touch purchase validates funds, inventory capacity, player/modal/combat and reachability, then grants one owned item and charges once. The small floating brass sale tag uses the current world rendering path. A reproduced blocked slot at seed2/scale1.1/range7–9/routes1 led to a local terrain correction: opening-floor shop outcrops that intrude on the two center-to-stock approaches are filtered after seeded draws, before terrain baking. Canyon outlines/connections and outcrop RNG draws are retained; only outcrops intruding on shop approaches are removed. Sold stock stays sold on revisit. Its owned-copy count updates remaining source-shop prices immediately: one copy gives key **5 → 3**, heart **3 → 2**, collectible **15 → 7**. More copies use the installed count formula. The selected random sale slot uses the same effective count; it does not multiply with the owned discount. Full native inventory queries/cache, modifier combinations and Restock remain open. This effect applies only to implemented source-shop offers; retained legacy menus are outside this delivery.

## Native evidence

The [manifest](source/manifest.json) pins installed Repentance 1.7.9b executable/XML and code-window hashes. [Capture script](../../../../scripts/isaac-reference/capture-shop-stock.py) executes:

- 1,551 complete ordinary stock initializers: original shuffle, RNG and ordinary game queries, supplied normal config0/room2, levels0/3/4 and nonzero descriptor stock seeds.
- 155 original discount arithmetic branches for prices0–30 and effective counts0/1/2/3/8. The external CRT `ceil` import is hosted with standard `math.ceil`; native branches/division/conversion execute. This is not execution of the original CRT DLL or inventory/count wrapper.
- 30 original collectible base-price calls after executing the original item-config default-price store: 15 coins for installed XML item64, which has no price override. Its shop-pool weight1/decrease1/remove0.1 and no achievement gate are recorded.

The C++ adapter is compared with every captured category, final RNG state, sale slot, discount and item-price case. The native descriptor seed mapping remains unimplemented: this delivery explicitly maps the DeathWard floor seed with XOR `0x53544f43`, preserving other RNG streams. Source geometry/connections remain excluded by the user's scope decision.

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-shop-stock.py --check
```

## Developer verification

- [Seven focused suites](regression-tests.log) pass: native stock/price reference, stock integration, previous key/heart purchases, treasure upgrade, legacy shop and preset contract.
- [Stock integration](core-tests.log): 27 generated size/range/route cases across heart/key and both slot orders, contact-region separation and entrance reachability; source random-sale witness and unsupported-pair fallback; both purchase orders, insufficient funds, full inventory, live prices/effect/copies, once-only purchase and sold revisit, explicit Apply and next-floor carryover.
- [Actual Game/Renderer input](game-input.log) passes mouse purchase, immediate displayed discount, discounted key purchase, sold revisit, mouse/keyboard tuning, staged Apply/Load, live changes, export/remember, retry and ordinary fresh launch. The existing [key](key-input-regression.log) and [heart](heart-input-regression.log) input modes also pass.
- [Four fresh-process loads](cli-validation.json): schemas5/31/32 and remembered32 retain map1.1/range7–9/routes.26, zoom165, speed1 and independently selected prices/effect. Original preset SHA remains `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`.
- Visual inspection: [stock before purchase](shop-stock-before.png), [discount after purchase](shop-stock-discount.png), [tuning panel](shop-stock-panel.png). [Custom export](shop-stock-preset.json) deliberately has upgrade16 and owned discount off, proving independent reload; the direct human command below loads the original accepted preset and baseline15/on.

The placement test reproduced an intruding outcrop before the local correction; the same case and all27 configurations now pass. A prior treasure test's exact catalog expectation was updated for the explicitly added item64; arbitrary incompatible catalogs still fail. These are developer checks, not a human acceptance claim.

## Configuration boundaries

**TUNING → REWARDS → SHOP → STOCK** stages Vary stock / Fixed pair until **Apply map changes**. Apply explicitly resets current-floor stock/purchases while keeping player/build/spending, as with existing unrestricted test regeneration. Upgrade base price0–30 in one-coin steps and the owned Steam Sale effect comparison are live on unsold stock; these do not regenerate or restock. HEART and KEY tabs retain independent base prices. Default upgrade15 and enabled effect are reference behavior; other settings are testing overrides. Random sale selection is seeded stock, not rerolled by live edits.

Schema32 exports/loads/remembers variation, upgrade price and effect, migrating schemas1–31 to enabled/15/enabled. Loading stages map fields and immediately applies prices/effect. Retry/floor changes carry configuration; normal launches grant no review funds or items. Exact additive catalog migrations retain the accepted source preset: `2ccd5b1c274a302e` (through28) / `57e101e53ba57102` (through31) → `53ab4ae76cff6d8`. Arbitrary fingerprints remain incompatible. Configuration files are not gameplay saves.

## Direct human check

```sh
./build/deathward --expedition --seed 7 --review-shop-stock --mute --save /home/kambo/.local/share/deathward/reviews/d12c-shop-stock/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

This explicit review opens directly in the generated shop with **20 test coins**, zero keys, two full red hearts, accepted165% zoom and normal health rules. Buy the brass Steam Sale tag for15: money becomes5 and the key's displayed price becomes3. Buy the key: money becomes2 and keys1. Leave/revisit: both remain sold. Seed2 instead offers a heart beside Steam Sale (heart3 → 2 after purchase). These are naturally compatible category witnesses, not forced room/stock generation. The user acknowledged this scoped review on 2026-11-16.

## Remaining work

Full collectible pool/RNG/eligibility, unsupported stock categories, shop level/profile/unlock/layout selection, native descriptor mapping, other item/discount combinations, Restock/machines/scenery, full actor/factory/physics/cache, browser runtime and gameplay-save continuity remain unfinished. The bulk parity goal stays paused. Next proposed after acceptance: commit this bounded checkpoint, then select one additional supported stock category or the next item-pool dependency.
