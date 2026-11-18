# D14a.7 — Mom's Eye and the recorded treasure room

Selected on 2026-11-18 by “coool, lets go!” after the proposed D14a.6 commit and Mom's Eye delivery. The accepted Duke checkpoint is committed as `5741f7cd`. **Main-game integration and developer verification pass; the user accepted the scoped handoff with “nice it works continue.”** Full native equivalence and the complete recorded floor remain unfinished.

The opening-floor treasure pool now includes Mom's Eye55. When it is selected with SOURCE LAYOUTS enabled, the treasure room supplies recorded **4.6.0**: a central collectible and two ordinary pennies at source cells (4,3)/(8,3). Touching the pedestal grants the passive once. Ordinary firing then has a nominal50% chance to add one backward shot, rising by10 percentage points per Luck. Extra copies do not add rolls or shots. Existing eight-direction firing, mouse/keyboard controls, universal dodge, walking, forward cadence and damage are retained.

## Source evidence and limits

`source/manifest.json` pins the installed Repentance1.7.9b executable, XML item55 and its weight1 treasure-pool entry. `scripts/isaac-reference/capture-moms-eye.py` executes the ordinary weapon1 inventory/Luck gate in the preserved executable:632 supplied cases cover absent/one/multiple copies, negative/positive Luck and probability boundaries. The original inventory helpers execute; only the global RNG call is supplied. Another24 cases execute backward-vector arithmetic at eight directions/three speeds. Caller and rear-tear-request assembly windows are preserved separately.

The exact native comparison is `float32(0.5 + float32(0.1 * Luck)) > float32(uint32 RNG) * 2^-32`. This is a strict single-precision comparison; at a threshold of1, the largest RNG words round to1 and fail. The consumer retains that boundary rather than replacing it with a clamped percentage roll. The UI displays the nominal bounded chance.

`content-verification.json` matches all three slots and their order against preserved `00.special rooms.stb`. The middle slot is the random collectible marker5.100.0, **not a fixed55 STB subtype**. The actual Mom's Eye outcome is established by the earlier live observation in `../d14a-floor-content/treasure-verification.json`. These facts do not prove DeathWard reproduces the source floor's procedural selection or seed.

The supported treasure pool contains seven equally weighted eligible entries in source XML order:1/4/8/10/45/55/58. Its existing native numeric scan is retained, with a DeathWard seed adapter and a restricted pool. Adding an item can change a seed's selected treasure. Fixed existing choices remain; mode7 explicitly selects Mom's Eye for testing. The recorded arrangement is attached to a supported Mom's Eye selection, not to a native full-floor room allocator. All three spawn slots consume the existing descriptor-derived RNG sequence, including the central collectible slot.

The backward shot uses the shared projectile/event path and the already resolved attack specification, with rear-direction velocity inheritance. The horizontal bearing reverses; DeathWard's existing vertical aiming, item modifiers, projectile dimensions, collision and range adapters remain. One trigger advances cadence/cylinder once. The roll uses DeathWard's combat RNG; full native global-RNG order, other weapon wrappers, modifier/cache interactions and the tear factory are not accepted by these bounded checks. Familiars retain their own shot controllers.

## Live configuration and persistence

**TUNING → SHOOTING → TREASURE → MOM'S EYE** changes the chance multiplier in5% steps, from0–200%. The reference is100%; at baseline Luck0 it gives50% chance. Changes apply to the next volley, retaining the active firing wait and emitted shots. The Luck buttons edit the existing shared Luck stat, which also affects its established reward consumers. Reset Chance restores only this item's multiplier.

Schema52 exports, loads and remembers `moms_eye_chance_multiplier`; schemas1–51 migrate with1x and retain earlier settings. The additive item catalog fingerprint is `ff9ac597a5f92395`. Invalid values and incompatible configurations are rejected before application. Treasure offering/map edits still wait for **Apply map changes**; source layouts OFF/test omit the complete recorded arrangement. Apply remains unrestricted and keeps the owned build/tuning while resetting current-floor contents. Descent retains the passive and tuning; death retry starts a fresh uncollected room with the applied settings.

The playable `review-preset.json` is a schema52 migration of the user's latest D14a.6 export, with no new review balance overrides:165% zoom,95% room size,7–9 range,26% routes, Speed1.1, Tears1.9272734, Shot Speed1.05, Luck0 and chance1x. Fixed Duke/Screw are retained from that export. Both earlier user exports remain untouched. The original D02 export still has SHA256 `22e143a736697ccc780ab31bde3c3a1f7ac0d88392e9bf7aa45055ccd3895604`.

## Developer verification

- `runtime-tests.log`: all632 native gate comparisons; actual volleys in eight directions with zero/one/two copies; matching attack specs, one cadence/cylinder advance, preserved emitted shots and real11.2-damage rear hit. Three generated sizes75%/110%/150% verify two accessible pennies, once-only collection, passive collection, revisit, Apply and descent; OFF/test/other-offering boundaries are separate checks.
- `preset-tests.log`: general preset round trips, migrations, rejection and atomic replacement checks pass. The new suite separately checks schema5/51 migration and schema52 custom chance/fixed selection round trips.
- `regression-tests.log` plus `treasure-regression-final.log`: Book of Shadows, Cricket's Head, treasure upgrades, Screw and the recorded Duke arrangement pass. The first treasure regression stopped at its obsolete catalog-hash assertion after geometry/route checks passed; the assertion now pins the independently computed additive Mom's Eye hash, and the corrected suite passes.
- `game-review.log`: actual Game/Renderer natural selection at seed0/displayed room8, normal health, touch pickup and forward/backward volley; mouse controls, keyboard reachability, live chance while map changes are pending, export/load/remember, Apply, **death-state retry** and fresh startup pass. `treasure.png` and `tuning.png` were inspected. The extra shot capture explicitly uses developer Luck20; this is absent from the playable preset.
- `cli-verification.json`: fresh schema48 original, schema51 latest Duke and schema52 Mom's Eye launches pass, preserving both user exports. The new review starts with two pennies, six half-heart units and god mode off.
- Main-game build and `git diff --check` pass. Capture FPS is not a performance benchmark.

## Short human check

```sh
build/deathward --expedition --seed 0 --review-source-room 4000006 --mute --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d14a7/campaign.save.balance/export.json --save /home/kambo/.local/share/deathward/reviews/first-floor-d14a7/campaign.save
```

This opens the naturally selected treasure in displayed room8, with ordinary health and the saved165% view. The review identifier separates treasure type4/template6 from ordinary combat template6; it does not inject a different offering.

1. Collect both pennies and touch the pedestal to take Mom's Eye.
2. Hold fire in several directions. Approximately half the volleys at Luck0 should also fire backward; forward pace and aim stay familiar.
3. Optionally change Chance Multiplier, export/load it, then continue into connected rooms. Death Retry returns to the same uncollected treasure.

## Unfinished and next proposal

Human D14a.7 acceptance; full native weapon/factory/cache/global-RNG/physics equivalence; the recorded shop offerings and special rooms; complete source-floor allocation and review; full expedition save/resume. Pixel/performance work remains deferred.

After this short review, checkpoint D14a.7. The next proposed bounded dependency is **Mom's Coin Purse195**, including its pill-spawn dependency; **Temperance15** and its machine dependency should follow as a separate delivery before assembling the recorded shop. These are proposals, not enabled content or authorization for unrelated bulk parity.

## Scoped human acceptance

On 2026-11-18 the user acknowledged the playable delivery with “nice it works continue.” See `human-acceptance.json`. The user selected its checkpoint commit and the proposed bounded Mom’s Coin Purse/pill continuation. Full native equivalence and remaining recorded-floor dependencies stay open.
