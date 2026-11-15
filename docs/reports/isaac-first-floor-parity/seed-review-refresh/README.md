# Seed-based room review refresh

Selected by “ok, continue” after checkpoint `10a1176b`, before D11a. The refresh is complete and developer-verified. No templates or outcomes are forced; the scanner verifies natural selections through actual Simulation generation. No new commit was requested.

The initial rebuild found nine of eleven room suites failing after shop reservation changed seeded roles and door inputs. Eight initially rejected missing/differently located templates or coverage counts; D08 reached the encounter but its selected room no longer awarded the expected full heart. Historical source selectors/content remain unchanged.

## Current review commands

Use the original accepted preset with these arguments:

```sh
./build/deathward --expedition --mute --save /home/kambo/.local/share/deathward/reviews/seed-review-refresh/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json --seed 195 --review-source-room 91
```

Replace the final seed/template pair using this table. Displayed room numbers are one-based. These commands replace the older handoffs for the same templates after the optional-shop correction; historical acceptance evidence still describes its original builds.

| Source template | Seed | Displayed room | Review arguments |
| --- | --- | --- | --- |
| 4 | 443 | 2 | `--seed 443 --review-source-room 4` |
| 30 | 84 | 5 | `--seed 84 --review-source-room 30` |
| 31 | 1290 | 6 | `--seed 1290 --review-source-room 31` |
| 32 | 1860 | 6 | `--seed 1860 --review-source-room 32` |
| 91 | 195 | 3 | `--seed 195 --review-source-room 91` |
| 108 | 853 | 5 | `--seed 853 --review-source-room 108` |
| 109 | 649 | 5 | `--seed 649 --review-source-room 109` |
| 214 | 1525 | 5 | `--seed 1525 --review-source-room 214` |
| 547 | 899 | 6 | `--seed 899 --review-source-room 547` |
| 548 | 487 | 5 | `--seed 487 --review-source-room 548` |
| 550 | 378 | 6 | `--seed 378 --review-source-room 550` |

For D08’s natural two-Gaper/full-heart-clear witness, use `--seed 3 --review-source-room 47` (displayed room2). Source91 retains the half/full pair, source214 two single keys, source32 three single dynamite pickups, and source30 ordinary coins.

## Verification

- [Before](before.log) records the nine failures.
- [Natural scanner](witnesses.csv) records three witnesses per template at three size boundaries; [grid](grid.csv) records all nine scale/range combinations for source4/91/108. `tests/RoomReviewSeeds.hpp` is shared by the core and interactive checks. The scanner target is an opt-in review utility, not a gameplay caller or normal test.
- [Eleven core suites](final-core-tests.log) pass, covering source4/91/108, broader formations, preplaced hearts/chests/coins/keys/bombs, D08 and generated room graphs.
- Eleven actual Game/Renderer modes pass across [initial input results](input-results.json), [rechecks](input-rechecks.json) and [final corrections](input-final.json). They retain mouse collection/navigation, real demolition, keyboard actions, staged Apply, export/load/remember, revisit/retry and normal starting health. Initial failures remain in the logs rather than being presented as passes.
- Source4/108 now cover all nine scale/range settings. The four-Gaper minimum-size route fixture tracks stable entity IDs and retires arrivals to test each route independently; it does not certify simultaneous crowd pressure. This matches the existing broader-room route test’s scope.
- Interactive paths now use visible short mouse waypoints where new coordinates fall behind HUD panels or off screen at165%. The chest retreat selects clear interior floor away from clickable doorways. These are review-fixture corrections, not changes to production movement, camera or hit geometry.

## Remaining

Human replay of the refreshed witnesses and broader native selection/contents/physics acceptance remain open. The selected next delivery is [D11a The Sad Onion](../d11a-treasure-upgrade/README.md). D12 shop stock/prices/purchases are not started; bulk parity remains paused.
