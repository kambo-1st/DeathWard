# D09b: ordinary room-clear coins in the main game

The user selected coins after source109 and broader room coverage on 2026-11-15. Ordinary opening-floor canyon combat now uses the existing native first-clear selector for coin outcomes as well as selected red hearts. Developer checks pass. The user accepted the launched ordinary penny playtest on 2026-11-15 ("ok, good it is..."). [Scoped acceptance](human-acceptance.json).

## Enabled behavior and source evidence

Penny, nickel and dime outcomes pay1,5 and10 respectively. They come from the same single award roll as hearts; this delivery does not add a second roll, reroll unsupported outcomes or change heart odds. Luck retains the existing native0–10 selector clamp. The coin subtype resolver preserves native overwrite order and RNG draws, verified against all1036 preserved coin cases, including explicit rare-gate input comparisons. Production uses sticky/lucky/golden gates off, ordinary Normal/empty-inventory assumptions. Those inputs do not establish a complete native unlock profile. Double-penny value2 is represented by the value helper but is not emitted by this scoped ordinary clear producer. Special coin actors are not enabled.

The coin actor uses preserved Appear33, Drop23 and Collect14 metadata through the existing active-room30Hz timing boundary. Admission changes currency once; the collection presentation cannot pay twice. Inactive and paused rooms freeze the clock. Capacity and blocked placement defer the resolved identity; later toggles or Luck edits do not reroll it. The selected placement adapter finds reachable legal floor near the room center; native factory/physics/motion and full scheduling are not claimed. See [hash-verified evidence](source-evidence.json).

Source coins admit while the retained wallet is below99. Their whole value is consumed, clipping the award at99; at/above99 they stay on the floor. Existing DeathWard currency is never deleted. DeathWard still shares currency with its retained campaign economy, and other retained producers can exceed99. This scoped source-coin admission rule is not a complete native wallet/shop/economy port.

When this policy is enabled, newly generated ordinary opening-floor combat rooms omit legacy random money piles, and ordinary enemy deaths in those rooms omit the generic35% money-drop roll. Existing pickups are not removed by live edits. Entrance/empty/special/story/boss/later-floor money policies, custom destructible payouts and golden-heart/Midas effect producers retain their existing paths. Native preplaced coin layout slots and complete special-coin/drop/economy rules remain unfinished. Unsupported source reward families remain recorded without substitution.

## Live controls, export and loading

**TUNING → REWARDS → AFTER CLEAR → COINS** controls future first clears and ordinary enemy drops independently of red hearts. Already resolved/pending awards and existing pickups stay fixed. Initial random-pile suppression applies on the next floor generation, including an explicit staged map edit followed by Apply; toggling alone does not regenerate the map. Death retry/new expeditions use the selected policy. The current first-clear outcome is never retroactively paid after enabling.

Schema19 (`d09b-ordinary-coins-v19`) exports/loads/remembers `coin_clear_rewards`; schemas1–18 migrate enabled while retaining all accepted settings. Map edits remain staged. The new `--review-room N` starts at displayed generated roomN with ordinary health/damage and repeats that entry on death retry. It is a launch aid, not a reward or combat override; it is mutually exclusive with `--review-source-room`.

## Verification

- Existing2196 native reward/RNG comparisons and1036 heart cases still pass;1036 coin subtype cases now pass. Pinned matrices/disassembly/ordinary ANM2 hashes are checked against their preserved manifests.
- Actual Simulation first clears emit pennies(seed20), nickels(seed0) and dimes(seed1506) in displayed room2, then collect exact values once. Timing boundaries pass at30/60/120Hz. Capacity, room ownership, inactive/pause clocks, refused/whole-coin clipped collection, live toggles, no retroactive awards, revisit and regeneration pass. [Gameplay log](gameplay.log).
- Fourteen focused suites pass jointly with the room continuation. [Main regression log](regressions.log), [core/destruction/rails](core-regressions.log).
- Actual Game/Renderer mouse coin controls, independent hearts, pending map edits, export/remember/fresh load, collection/revisit and retry pass. [UI evidence](input.log). The prior heart UI/actual mouse-fire workflow also passes. [Heart regression](heart-ui-regression.log).
- Six independent CLI launches cover schemas5/18/19 for source109, schemas5/19 for coin review and a disabled schema19 coin preset. All preserve zoom165%, normalHP6/god0 and the chosen policy. Two invalid review-option cases are rejected. [CLI evidence](cli-validation.json).

[Panel](panel.png), [coin actor](coin.png) and [preset](preset-v19.json) are captured from the actual application. Gameplay save/reload of a complete expedition is a separate D18 gap; this delivery proves preset reload and in-memory room revisit, not full gameplay-save continuity.

## Short review

```sh
build/deathward --expedition --seed 20 --review-room 2 --mute --save /home/kambo/.local/share/deathward/reviews/d09b-coins/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

1. Clear room2. Its baseline Luck0 outcome is one penny.
2. Wait for the appearance, walk over it and see money increase by1.
3. Leave and return; it stays collected. Death retry returns to the encounter.

For a nickel use seed0; for a dime use seed1506. Keep baseline Luck0 for these recorded outcomes.

## Unfinished and next

The scoped penny playtest is accepted. Preplaced native coin slots, special coin actors/producers, native seed/factory/placement/physics/profile/item modifiers, full currency/economy rules and gameplay save/reload remain open. The current seed/placement/30Hz adapter and retained legacy producers are explicit limitations. Next: source coin layout placement and another compatible complete room family; the other added room layouts remain available for human review. Coins are now selected; unrelated item/shop/boss deliveries and automatic bulk parity remain paused.
