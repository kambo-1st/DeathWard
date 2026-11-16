# D12f — two supported shop collectibles

Selected on 2026-11-16 by “ok, ltes go!” after the proposed shop collectible expansion. D12e was accepted and committed as `e4f41461`. This delivery is integrated in the main game. The user accepted the scoped playtest and requested its commit with “commit, it allright, what next?”; see [human-acceptance.json](human-acceptance.json). The automatic bulk parity effort stays paused.

Compatible source shop category pairs can now offer **Steam Sale64** or **BOGO Bombs250**, both with a reference base price of15. The existing red/soul heart, key and dynamite companion slots, sale-slot discounts, centered solid cart, touch purchases and once-only sold state remain. BOGO uses paired sticks on a brass card; loose supplies use their existing one/two-stick model. No player movement, firing, health, damage or room geometry is changed.

BOGO changes an ordinary single-dynamite pickup into a double when its actor is created. Extra copies do not multiply again. Already created actors retain their subtype and timing; collected amounts are never multiplied a second time. The shared factory covers room layouts, ordinary clear rewards, chest supplies and shop stock. Doubles clamp at99, refuse collection at full capacity and keep once-only payment/collection. Steam Sale can coexist with BOGO. Double shop dynamite retains the source base5 price.

**TUNING → REWARDS → SHOP → STOCK** cycles `TWO ITEM POOL`, `BOGO BOMBS TEST`, `STEAM SALE TEST`. This setting waits for **Apply map changes**. Applying explicitly resets this floor’s encounters/pickups/purchases while retaining player health/build/resources/spending. Export, load, remember, retry and subsequent expedition generation carry the selection. Loading stages it without changing current stock. Schema35 migrates1–34 to the restricted pool and preserves accepted settings, including the original165% preset. Fixed-item modes are labelled test overrides; they are not native pool selection. Existing independent prices remain live.

## Source verification

Installed Repentance1.7.9b executable and XML hashes are preserved in [source/manifest.json](source/manifest.json). `scripts/isaac-reference/capture-shop-collectibles.py --check` reproduces the evidence without modifying the installed game or running process.

- Both entries are eligible passive shop items with weight1, decrease1, remove threshold.1, no achievement requirement or price override in the preserved XML.
- 524 original RNG/weighted-scan cases execute with two supplied eligible entries, including float boundaries. The coefficient at`0xb6a198` is bits`0x2f7ffffe`, slightly below2^-32; replacing it with2^-32 failed the boundary comparisons and was corrected.
- 112 whole pickup-resolver cases execute real item-presence queries with supplied ordinary-player inventory and explicit subtypes. BOGO changes only bomb40.1 to40.2 in this matrix. Other tested variants/subtypes remain unchanged; this does not enable their unsupported actors.
- 60 original collectible-price cases verify15. Twelve ordinary single/double bomb-price cases verify5.

This is a **restricted two-entry pool**, not Isaac’s complete shop pool. DeathWard mixes the expedition floor seed into a separate item seed; native descriptor item-seed generation, eligibility wrappers, acquisition history, pool depletion, rerolls and full profile/modifier handling remain open. The recorded weighted scan stops before those wrappers. An empty numeric choice has an explicit Steam Sale fallback without another draw. Lazy/deferred actor admission, physical contact, pickup presentation, special bombs and full native lifecycle acceptance remain adaptations or unfinished work.

## Human check

Launch the natural two-item-pool witness:

```sh
build/deathward --expedition --seed 32 --review-shop-stock --mute --save /home/kambo/.local/share/deathward/reviews/d12f-shop-collectibles/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

The review opens directly at the shop with20 labelled test coins and normal health/controls. Buy the paired-stick collectible for15. The existing loose stick stays a single. To inspect the next birth immediately, open the stock tuning panel, cycle to `STEAM SALE TEST` and Apply. The floor reset retains owned BOGO and5 coins; the newly created loose supply has two sticks. Buy it for5: starting3 charges become5. Normal expeditions do not receive the review coins or direct travel.

Seven focused suites pass, covering collectible/stock/reference/soul-heart/preset/bomb/chest gameplay. Actual Game/Renderer mouse and keyboard checks pass for the new BOGO flow and the fixed Steam Sale comparison. Separate CLI loads of schemas5/34/35 pass. The original preset SHA is unchanged. See [validation.json](validation.json), [tests.log](tests.log), [game-input.log](game-input.log), [CLI checks](cli-validation.json) and [shop preview](shop-collectibles-before.png). Broader shop items/categories, full source pool/profile/seed/factory/physics equivalence, browser execution and gameplay-save continuity remain unfinished. This accepted delivery is included in the checkpoint. Next proposed: D11b treasure-room variety, adding eligible Cricket’s Head4 alongside The Sad Onion1, verifying its complete effects and providing a short main-game check with reusable tuning. This proposal is not selected or started; source item-pool XML confirms eligibility, not complete effect acceptance.
