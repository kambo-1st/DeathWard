# D14a.15 — donation milestones and shop upgrades

Enabled in the main game on 2026-11-20; developer verification passes, and the user accepted the scoped playtest on 2026-11-20 ("nice it works!"); see `human-acceptance.json`. The user's “cool, next!” accepted D14a.14 and selected this continuation. The accepted D14a.13/14 checkpoint is `ad0241f7`.

Completed deposits now record permanent milestone flags independently of the withdrawable donation bank. The shop upgrades are earned at 20, 100, 200 and 600 coins. Withdrawals, overflow, death, recovery and subsequent expeditions do not revoke them. A newly earned upgrade applies when generating a future shop; the present shop does not replace its stock during a donation or an unrelated live tuning edit. The existing testing **Apply map changes** action can explicitly regenerate the current floor with the new upgrade.

## Source evidence and enabled behavior

`source/manifest.json` pins the installed Repentance 1.7.9b executable, XML and room payload. `capture-donation-milestones.py --check` executes the original milestone-call window at `0x63da85..0x63db69` and ordinary shop-level stores at `0x7b1717..0x7b1834`. There are 32 supplied threshold cases and 16 combinations of upgrade flags. Achievement calls are hosted endpoints; special profile/Greed paths and the complete native allocator are outside this verification.

| Displayed upgrade | Donation threshold | Native level field | Default source layout | Stock positions |
|---|---:|---:|---|---:|
| 0 | — | 1 | 2.0.0 | 2 |
| 1 | 20 | 2 | 2.1.1 | 3 |
| 2 | 100 | 3 | 2.2.2 | 4 |
| 3 | 200 | 4 | 2.3.3 | 5 |
| 4 | 600 | 5 | 2.4.4 | 6 |

The source field is **one-based**; using the displayed upgrade directly would wrongly delay the expanded collectible category at upgrade 3. The C++ caller uses `upgrade + 1`. The 20 stock coordinates and original slot ordinals come from the default source templates and retain the existing numeric category/sale selection.

The other threshold flags are recorded: Blue Map (10), There's Options (50), Black Candle (150), Red Candle (400), Blue Candle (900), Stop Watch (999). **Their item mechanics and shop-pool admission are unfinished.** Recording flags does not make these items playable.

Stock uses the retained canyon shop, wagon and rocks. Source positions are adapted around the wagon and uniformly fitted against finished terrain, player clearance, reachability and pickup separation. Source upgraded decorations/room allocation are not imported. If a layout cannot fit, its prior bounded stock remains and resize stays available. Recorded shops now use the existing fine navigation fallback when the coarse grid misses a physically open aisle; collision checks remain active.

Red/soul hearts, keys, dynamite, pills, Temperance and the existing three-item collectible pool use ordinary actors, payment, sale/Steam Sale, collection and revisit state. Source battery/trinket categories are preserved but remain unspawned without rerolling: a six-position layout need not have six visible actors. Pills/cards and collectible selection remain the existing bounded adapters, including no native item-pool depletion guarantee. Nonrecorded canyon shops use an explicit nonzero DW descriptor-seed fallback. This is not full source stock, factory, pool or room-selection parity.

## Configuration and persistence

**TUNING → REWARDS → SHOP → DONATIONS → SHOP UPGRADES** shows the earned/current levels and lets testing select levels 0–4 or **Use earned level**. Edits/load stage until **Apply map changes**, which resets current-floor encounters/pickups while keeping the player/build, bank, permanent flags and expedition identity. The level override never grants an achievement.

Preset schema 59 exports/loads/remembers the override, including pending map selections. Schemas 1–58 migrate to earned level (`-1`). The original user preset is untouched; `review-preset.json` migrates it with zoom165, Speed1.1, room range7–9, routes.26 and the accepted shooting/combat settings retained. `test-level4-preset.json` is explicitly an automation override, including Never Jam; it is not the interactive baseline.

Campaign schema 14 adds the permanent mask to world state and expedition summaries. Checkpoint/resolve merge unlocks monotonically, so a stale summary cannot remove an earned upgrade. Older saves infer only milestones supported by recorded bank values in the world/history/pending summary. An unrecorded peak withdrawn before migration cannot be recovered. `legacy-v13-bank600.save` is a synthetic migration fixture derived from the isolated previous review save, with its world bank set to600 and checksum rebuilt; it is not a real earned player record. Configuration presets do not carry campaign progress.

## Verification and human check

- Native threshold/level captures reproduce byte-for-byte; C++ agrees with all 48 supplied numeric cases and 20 source stock positions.
- All five levels at75%,100%,150% room size pass stock fit/access, native category retention, supported actor delivery, real purchases, once-only payment and revisit checks. Negative checks cover insufficient funds and full red health. Milestone checks cover20/100/200/600/999/1000, explicit regeneration, withdrawal, overflow and floor transition.
- Campaign permanence/recovery/schema13 migration and preset58→59 migration/all six settings/atomic rejection pass. Nine focused CTest suites pass; see `tests.log`.
- Actual `Game`/`Renderer` checks pass:19→20 campaign checkpoint, live edits retaining current stock, mouse navigation, staged export/load/remember, explicit Apply, level4 presentation, death/retry and fresh-process state. See `game-review.cpp`, screenshots and `game-review.log`.
- Four CLI loads cover schemas57/58/59, a level4 override, and campaign13→14 migration with an earned level4. See `cli-checks.json`.

The interactive launch is recorded in `interactive-latest.json`. It uses an **isolated test save seeded with bank19**, twenty labelled review coins, four red half-heart units and no god mode. Donate one coin at the register and step away: the bank reaches20 and earns Upgrade1. Under SHOP UPGRADES, press Apply to regenerate the floor and inspect the three positions. Levels0–4 can also be selected for testing; Use earned level restores normal behavior. Retry keeps the earned upgrade. Normal source jam rolls remain enabled.

Unfinished: milestone item mechanics/pool admission; battery and full trinket/card/pill/collectible stock coverage; full native profile/factory/RNG/scheduler/physics and item-pool acceptance; upgraded source decoration/selection rules adapted to canyon geometry; remaining special rooms/complete floor allocation; live expedition save/resume. Pixel/performance work remains deferred. Proposed next small delivery after review: ordinary shop battery pickups and active-item recharge, followed by the remaining stock dependencies. Bulk parity remains paused.
