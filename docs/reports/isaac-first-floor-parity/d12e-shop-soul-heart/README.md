# D12e: ordinary soul-heart shop stock

The user selected committing the accepted dynamite delivery and then adding soul-heart shop stock with “olets go”. D12d and removal of the TRADER CART label are committed as `7f1260e6`. D12e is implemented in the main game and developer-verified. The user accepted this scoped delivery with “nice perfect, commit”; it is included in this checkpoint. Bulk parity stays paused.

Compatible source shop category pairs now include **collectible8 + soul-heart4**, in either order. The category resolves to pickup10.3, rendered with the existing blue-heart appearance. It costs **5 coins** before discounts, or **3 with one Steam Sale**. At admitted contact it adds up to two protective half-heart units, using the existing source health rules; red health is unchanged. Full red health does not prevent purchase when protective capacity exists. A completely full health capacity refuses without payment. If only one half-unit fits, the ordinary full pickup is still bought at its full price and adds that half-unit. Purchased protection absorbs ordinary damage before red health. Existing black/bone/broken health ordering/capacity rules are retained.

The selected heart shares the existing shop-heart actor and once-only sold state; independent red and soul prices follow its actual kind. Collection pays/grants once, disappears after collection and stays sold on revisit. Dead/modal/combat/contact/appearance gates and deferred actor-capacity handling remain. Free hearts outside shops remain free. Existing cart placement/collision, canyon sizes/connections, controls, movement/shooting, universal dodge and blast behavior are retained.

The source-shop master policy and existing staged stock variation control generation. Supported pairs are now collectible plus red heart, soul heart, key or bomb. Unsupported categories keep the documented previous fixed key/heart fallback without reroll. Steam Sale64 remains the pinned eligible collectible; full item-pool selection is not implemented. Basic shop level0, ordinary config0/normal profile and the DW stock-seed adapter remain explicit supplied inputs/adaptations. Later floors, other themes, tutorial and service shops retain their prior menus.

## Configuration

**TUNING → REWARDS → SHOP → HEART → SOUL HEART** edits the soul-heart base price live in whole-coin steps from0–15; default5 is the native reference. The neighboring RED HEART page keeps its independent price3. Price changes affect unsold purchases without regenerating or restocking. Vary stock / Fixed pair remains pending until **Apply map changes**; the explicit testing regeneration resets floor purchases while retaining player/build/spending and health.

Schema34 (`d12e-shop-soul-heart-v34`) exports/loads/remembers the new price; schemas1–33 migrate with5 and preserve accepted settings. Loading immediately applies prices and stages map fields. Retry/floors/future expeditions retain configuration. Invalid fractional/out-of-range prices, changed source references and mismatched overrides are rejected. Catalog migration rules are unchanged; no new item definition is added. Presets remain separate from gameplay saves. Original165% preset SHA256 is unchanged: `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`.

## Native evidence

[Capture script](../../../../scripts/isaac-reference/capture-shop-soul-heart.py) and [manifest](source/manifest.json) pin installed Repentance1.7.9b. Thirty ordinary price calls return5; six supplied category4 resolver calls return10.3. Sixty-six supplied ordinary empty-inventory health cases execute the native soul admission helper and the original subtype quantity/AddSoulHearts call, checking red/soul/bone/broken capacity and partial admission. The quantity slice stops before sound/presentation; this does not execute the complete pickup/contact/payment wrapper or certify other characters/items. [Health rows](source/native-soul-health.csv) are compared with the existing C++ health adapter.

The [animation extractor](../../../../scripts/isaac-reference/extract-soul-heart-animation.py) resolves the highest installed override and preserves [metadata](animations/manifest.json):30Hz, Appear33, DropSound25, Collect12. Those values match the existing heart timing adapter, so no timing behavior change or sprite-art import is needed. Main-game shop actors begin idle/collectible like the existing red-heart offer; full native spawn/physics/scheduler acceptance remains separate.

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-shop-soul-heart.py --check
python3 scripts/isaac-reference/extract-soul-heart-animation.py --check
```

## Developer verification

- [New soul-heart suite](core-tests.log):30 source prices,66 native admission/health cases,27 generated size/range/route cases including both stock orders, funds/cap/partial-health and discounts, either purchase order, protection against damage, mixed health, live prices, gates, capacity-delayed birth, once-only payment, sold revisit, Apply/floor carryover and preset migration/rejection.
- [Six regression suites](regression-tests.log): previous heart/key/stock transactions, native player health, health gameplay and preset contract. All seven focused suites pass. The initial [placement-test failure](initial-placement-check.log) counted a legitimate half-heart in another room at seed41; the corrected assertion checks exactly one priced blue heart in the shop while retaining other-room hearts. No gameplay generation was changed for this fixture correction.
- Three actual Game/Renderer modes pass: [soul-heart](game-input.log), [red-heart](heart-input-regression.log), [dynamite](dynamite-input-regression.log). The new mode covers mouse purchase/discount, blue health display, sold revisit, independent red/soul price edits, keyboard reset, staged Apply/load, export/remember, retry and normal fresh launch.
- [Three fresh CLI processes](cli-validation.json) load schemas5/33/34 with retained165% view/map/walking and migrated/custom soul prices. [Before purchase](shop-soul-heart-before.png), [discount](shop-soul-heart-discount.png), [purchased blue heart](shop-soul-heart-purchased.png), and [tuning](shop-soul-heart-panel.png) were visually inspected. The saved [custom test export](shop-soul-heart-preset.json) intentionally uses soul6/red4; the human command below loads the original preset and baseline5/3.

## Short human check

```sh
./build/deathward --expedition --seed 18 --review-shop-stock --mute --save /home/kambo/.local/share/deathward/reviews/d12e-shop-soul-heart/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

This opens directly in displayed room7 at165% zoom with20 explicitly labelled review coins, two full red hearts and normal health rules. Buy Steam Sale for15: coins5 and the blue-heart price becomes3. Buy the blue heart: coins2 and one full blue protective heart is added; red health stays at two full hearts. Leave/revisit: neither item returns. Normal launches grant no review funds. Seed41 exercises the opposite slot order and a naturally selected collectible sale. The user accepted the scoped interactive delivery and requested its commit; see [acceptance record](human-acceptance.json).

## Remaining work

D12e is accepted and included in this checkpoint. Full collectible pool/RNG/eligibility, remaining stock categories, shop-level/profile/unlock/layout selection and native descriptor seed mapping remain unfinished. Other discount combinations, Restock/machines, full pickup factory/scheduler/physics/cache, browser runtime and gameplay-save continuity remain open. The next proposed work is selecting the first expansion of supported shop collectible choices; do not auto-start it or resume bulk parity.
