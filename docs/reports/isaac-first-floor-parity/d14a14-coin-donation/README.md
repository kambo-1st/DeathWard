# D14a.14 — ordinary coin donation in the main game

Selected by “nice it works, continue!” after D14a.13's proposed playable coin economy. **The ordinary coin register is enabled in matching opening-floor recorded shops. The user accepted this scoped delivery on2026-11-20 (“cool, next!”).** It is separate from Temperance's health-payment machine.

## Playable result

The recorded shop's original slot0 (source cell3,0; actor6.8) now creates a solid, reachable register in an ordinary eligible DeathWard context. Its presentation uses the existing Synty Western cash-register and crate meshes, their prefab albedo/UVs, and normal scene lighting/shadows. It uses the original slot seed; other stock/rocks are unchanged. Numerical procedural seeds and custom balance settings are not treated as Isaac's `IsCustomRun` flag.

Walk into the register to donate one coin. Move away to stop further donations; an already paid insertion completes. Credit occurs at the adapted CoinInsert event, rather than at contact. Holding contact accelerates the source insertion/cooldown schedule. Ordinary source rolls include a2% +1 Luck effect and the escalating jam rule `RandomInt(2000) < 3 * donationsThisExpedition` after incrementing that count. The added Luck enters the existing combined attribute snapshot and survives floors/Apply, but resets on a new expedition.

The bank persists in the campaign, including death, retreat and interruption recovery. A jam persists throughout the expedition, including room revisits, floors and Apply; a new expedition resets it. Jammed machines ignore explosions in this source build. An intact machine hit by ordinary dynamite withdraws7–15 units, capped by the displayed bank, and creates one fewer ordinary random coin pickups. A repeated blast cannot withdraw again. Destroying it cancels a paid insertion that has not yet credited the bank, removes its collision and excludes another coin machine for that expedition. Ordinary bullets do not destroy it.

The native persistent counter is cumulative. The display and withdrawable balance use its final three digits. The1000th donation breaks the machine, releases15 dimes and displays0; the next expedition starts with that0 displayed balance. The full counter remains stored, matching the pinned arithmetic. Source item achievements/shop upgrades are **not** implemented by storing this counter.

## Live controls and persistence

**TUNING → REWARDS → SHOP → DONATIONS** provides:

- Donations enabled/disabled: next coin admission. An already paid insertion completes.
- Destruction enabled/disabled: next explosion; existing jams and destruction remain fixed.
- Cycle speed .25–4× and jam probability scale0–3×, in5% steps: snapshot on the next paid insertion. Cycle speed changes the insertion animation interval, not the separate source cooldown.
- Source jam rolls / labelled Never Jam test / Jam Next Donation test: snapshot at admission. These do not repair a jammed machine.

Schema58 exports, loads and remembers the controls; schemas1–57 migrate with ordinary defaults. Preset loading does not overwrite the bank, revive actors, reroll resolved payouts or apply pending map edits. The bank belongs to the campaign save, not the tuning preset. Campaign schema13 adds the bank to world/checkpoint summaries, supports old saves and commits bank changes through the existing atomic save path. Repeated checkpoints and resolution are idempotent. This is **not live expedition save/resume**.

Apply still regenerates the current floor without restarting and preserves player/build, bank, expedition jam/exclusion/count and configuration. It resets floor actors and unfinished insertion phases; already resolved pending pickup identities are retained. A stale collision body found during the minimum-size Apply check was fixed before handoff.

The user's original schema57 preset remains untouched. `review-preset.json` is its schema58 migration, retaining zoom165 and accepted movement, shooting, map, combat and reward settings.

## Verification

- `capture-coin-donation.py` executes1,280 native supplied deposit cases and2,048 native withdrawal cases; the C++ calculations match all3,328 rows. `--check` reproduces the preserved evidence exactly. D14a.13's1,280 initializer gate cases remain the eligibility reference.
- Preserved coin-machine ANM2 metadata supplies CoinInsert6/4/2 event frames and8/6/4 animation lengths. Sprite artwork is not imported.
- Eight focused suites pass: donation, blood-machine explosions, Temperance, preset contracts, keeper, recorded shop, core contracts and save slots. Donation checks cover small/normal/large rooms, actual movement paths, collision, admission/credit, pause, jam immunity, repeated blasts, overflow, revisit, Apply, floor transition, persistence/interruption/death and preset rejection.
- Four separate CLI checks pass: schemas48/57/58 and a copied campaign12 →13 migration. The original campaign remains byte-for-byte unchanged; see `cli-checks.json`.
- `game-review.cpp` passes with the actual Game/Renderer: mouse and keyboard tuning, walk-to-register, immediate campaign checkpoints, export/load/remember, staged Apply, revisit, death/retry, ordinary B-key dynamite and fresh campaign loading. Screenshots show the shop, settings, credited bank, jam and destruction. Runtime packaging includes the new model for native/web builds.

Native capture hosts visual/profile/achievement and bank persistence endpoints; original numerical decisions execute from the pinned installed1.7.9b executable. The overflow throwing loop is hosted; ordinary withdrawal counts are executed before physical spawning. Prior actor RNG history, full contact/animation scheduler, native pickup physics and profile queries are not accepted. The30Hz active-room schedule, canyon collision, grounded accessible pickup placement and child-seed stream through withdrawal throwing are explicit adapters. Native bank-store instructions are separately preserved as assembly evidence. Source-game seed/profile gates are not globally reproduced by this feature.

## Human check and next steps

Launch the isolated shop review described in `interactive-latest.json`. It starts in displayed room7 with20 labelled test coins, four red half-heart units, god mode off and165% zoom. The register is behind/left of the wagon. Donate a few coins, step away, and revisit: the bank should remain. The Donations page can force the next completed donation to jam. Death/retry clears the expedition jam while retaining the bank; an intact machine can be bombed withB. The bank belongs to this review save; a different `--save` path has its own bank.

Unfinished: donation milestone unlocks and their shop-stock effects; full native factory/profile/RNG/scheduler/physics acceptance; historical captured-shop absence context; remaining special rooms and complete floor allocation; live expedition save/resume. Pixel/performance work stays deferred. The user selected the donation milestone/shop-upgrade continuation on2026-11-20. Bulk parity remains paused.
