# Optional expedition rooms and reward pools

Two optional service types remain on modern canyon floors, within the existing 9–15-room budget. The five-room tutorial, Classic comparison and Western Mine retain their earlier room allocation, locks and reward rules. Story sites remain attached to their scheduled floors and never become paid trades.

Early floors select up to one service room; floors with at least twelve rooms select up to two different services. Retired service slots are quiet empty rooms, preserving the other specialists’ seeded placement. Selection uses an independent seed stream and prefers side branches. Floors 1–3 can offer the smuggler; the Field Surgeon becomes eligible on floor 4, regardless of expedition length or difficulty band. The entry, miners, altar, shop, power rooms, boss and scheduled story site are protected. At least three ordinary combat rooms remain. Each shop or service room contains one trader; a shopkeeper and a specialist never share a room. Service rooms have no enemies. Walk to the person or click them to open the offers. The shop modal pauses combat, and both offers have mouse buttons and the existing number-key shortcuts.

| Function | Offer | Limit |
| --- | --- | --- |
| Field Surgeon (`H`) | 20 coins restore up to 60 HP; 35 coins grant 15 maximum HP and restore up to 15 HP | One treatment and one tonic per floor; ordinary healing cannot be purchased at full HP |
| Smuggler's Bargain (`D`) | Choose one of two powers for 20 expedition maximum HP, plus any intrinsic item cost | One choice for the room; the final maximum HP must remain at least 20 |

The bargain shows the **total** maximum-HP cost and the resulting current/maximum HP before purchase. For example, at 100 maximum HP, Judas Bullet costs the room's 20 HP plus 20% of the remaining 80: final maximum HP is **64**, total loss **36**. A purchase never reduces current HP below one. These changes and items carry between floors but expire when the expedition ends, as other expedition builds do.

Offers are generated once. Leaving, revisiting, choosing an item elsewhere or moving the camera cannot reroll them. Normal campaign recovery still resolves interrupted expeditions; it does not resume a saved mid-floor world. Coins retain the existing campaign persistence rules. Prospector Exchange has been removed: there is no keys-for-dynamite or dynamite-for-coins service.

## Resource reachability

Modern canyon boss approaches no longer consume an ordinary key. Combat clearance opens them. Keys remain useful for locked doors and chests; dynamite can be spent on combat and destructible obstacles. The free network contains every mandatory objective, evidence site and the boss. Spending all keys and all dynamite therefore cannot prevent departure. The generator still places `powerRooms + 1` initial keys, now allowing an explicit surplus trade-off. Classic retains its original boss lock.

## Distinct item pools

The local Isaac pool metadata provides the separation-of-context reference, not copied item effects, weights or odds. DeathWard's weights below are original tuning. Each offer draws two different items from its pool, without replacement within that pair. Copies acquired on other floors remain possible. Existing item interaction rules are in [expedition items](expedition_items.md).

| Item | Armory | Shop | Boss | Bargain |
| --- | ---: | ---: | ---: | ---: |
| Ricochet Coin | 4 | 4 | 1 | 0 |
| Split Lead | 4 | 0 | 3 | 1 |
| Judas Bullet | 0 | 0 | 0 | 4 |
| Powder of Jericho | 0 | 0 | 3 | 4 |
| Hangman's Coin | 0 | 0 | 3 | 4 |
| Scatter Cylinder | 5 | 2 | 0 | 0 |
| Rail Spike | 5 | 1 | 4 | 1 |
| Lodestone Sight | 3 | 5 | 3 | 0 |
| Return Spring | 3 | 4 | 2 | 0 |
| Blasting Cap | 1 | 1 | 0 | 4 |
| Fuse Braid | 1 | 5 | 2 | 0 |

Numbers are relative selection weights, not percentages. Armories emphasize weapon forms, shops utility, bosses pierce and kill-chain effects, and bargains unusual or risky effects. All eleven items are obtainable across these contexts.

Defeating a modern canyon boss also reveals an optional two-item choice on its own pedestal, separated from the evidence and exit. Take one, leave it for later, or leave the floor without it. Coins and a dynamite stick remain the finite boss supply payout. Replay cheats cannot pay it twice. The boss reward does not count against the floor's one or two armory pedestals, and neither item choice nor a trade is required for story progress.

## Verification

`deathward_expedition_economy_tests` checks pool membership/determinism, purchases, exact health previews, offer exhaustion, revisits, carry-over, boss rewards and zero-resource reachability across actual seeded floors. `web/expedition-economy-test.cjs` exercises rendered offers and mouse purchases alongside the new bosses. The final milestone validation status is tracked in [the implementation log](expedition_implementation.md).

Native smoke views: `--smoke --seed 69 --theme canyon --style original --scene service-surgeon`, `service-bargain`, or `boss-reward`. These use an isolated test save and explicit test resources/offers. They are verification scenes, not the natural offers of seed 1866.
