# Power-up categories: small main-game deliveries

Status: plan requested on 2026-11-16. The user clarified: **establish support for each category with one or two items first; implement the remaining catalog later.** The user subsequently selected **PW-F01 — Brother Bobby**; implementation and developer verification are complete; the scoped human review is accepted. PW-A01 Yum Heart is accepted. PW-T01 Cancer is implemented, developer-verified and scoped human-accepted; see [its progress report](reports/isaac-first-floor-parity/pw-t01-cancer/README.md). PW-C01 is scoped human-accepted. PW-T02 Whip Worm is scoped human-accepted; the other optional second examples remain unselected. The automatic bulk parity effort remains paused; the user selects each named delivery before it starts.

## First milestone

Make all four categories usable together in an ordinary DeathWard expedition:

| Category | First example | Second example | Initial status |
| --- | --- | --- | --- |
| Passive | The Sad Onion — collectible1 | Cricket's Head — collectible4 | Both enabled and scoped human-accepted; retain them. |
| Familiar | Brother Bobby — collectible8 | Halo of Flies — collectible10 | Brother Bobby accepted; Halo of Flies remains proposed. |
| Active | Yum Heart — collectible45 | Book of Shadows — collectible58 | Yum Heart scoped human-accepted. Second example unselected. |
| Trinket | Cancer — trinket39 | Whip Worm — trinket27 | Cancer and Whip Worm scoped human-accepted. |

The first milestone therefore needs **five example items total: two existing passives and one example from each missing category**. Second examples bring that to eight and follow after the four-category milestone. Existing Steam Sale, BOGO Bombs and DeathWard items remain available under their current rules.

“Category support” means the demonstrated acquisition, ownership and gameplay workflow. It does not mean every effect, subtype, synergy or item in that category is implemented.

## Current starting point and source

- D11b's Sad Onion/Cricket treasure offering is accepted and committed with PW-F01 as `d915e845`. See [D11b](reports/isaac-first-floor-parity/d11b-treasure-variety/README.md). This plan does not commit it or repeat its implementation.
- Stable item keys already distinguish collectibles, trinkets, cards, pills and internal entries in `src/content/ContentId.hpp`. Passive, familiar and active are collectible subcategories; retain existing IDs and save compatibility.
- `ItemDefinition`, owned-item counts, attack specifications, scoped stat consumers and item-event hooks already exist. Extend those paths incrementally. Existing My Shadow/allied-actor work is reusable code, not acceptance of a generic familiar system.
- A trinket identifier alone does not supply a usable trinket slot. This plan supplies actual category workflows with their example items, rather than stopping at metadata or a private demonstration.
- The preserved [1.7.9b item definitions](../reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3/items.xml) and [item pools](../reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3/itempools.xml) verify these identities. The proposed familiars and active items belong to the source treasure pool; Cancer and Whip Worm have no achievement attribute in the item XML. Complete caller eligibility and effects still require verification.

Source metadata, verified native behavior, implemented gameplay and human acceptance are separate statuses. Do not infer an effect formula from its cache tag, or treat a registry entry as a completed item.

## Delivery order

**PW-P01 (existing passive baseline) → PW-F01 → PW-A01 → PW-T01 → PW-C01 (combined check).** Then select second examples individually. Each new delivery should provide a one-to-three-minute human check with no more than three actions, directly in the normal game.

### PW-P01 — retain and expose the accepted passive baseline

**Items:** The Sad Onion1 and Cricket's Head4. Their ordinary acquisition and effects are already accepted; no additional passive item is needed to establish this category.

Keep base stats separate from owned modifiers. Preserve copy rules, the once-only Cricket multiplier, independent Tears/Shot Speed/Range and emitted attack snapshots. Show the owned item name, copies and effective result through the existing inspection/tuning UI; add only missing presentation needed for the category handoffs.

**Acceptance baseline:** collect each item through its ordinary pedestal, observe the relevant effect, revisit without receiving it twice. Their combination must remain valid during later category deliveries. Do not reopen accepted walking or shooting calibration as a prerequisite for adding item categories.

Status: scoped item gameplay accepted. Shared inspection changes, if needed, belong to the next selected delivery rather than a separate framework project.

### PW-F01 — familiar ownership and Brother Bobby

Status: explicitly selected; implemented and developer-verified in the main game. See [PW-F01 report](reports/isaac-first-floor-parity/pw-f01-brother-bobby/README.md). Scoped human acceptance recorded; full native acceptance remains open.

**Visible result:** collect Brother Bobby from an eligible ordinary treasure pedestal; a companion follows and fires with the player.

Implement the minimum collectible-category metadata and runtime familiar ownership together with this item. Establish owner/item/copy identity, spawn and removal, following, attack scheduling, friendly projectiles and pause/room/floor lifecycle. Use source-verified familiar damage, shot timing and travel; do not automatically inherit the player's damage or shooting modifiers. Keep the eight-direction control exception and document the familiar's isometric aiming/space adaptation.

The companion must not block the player, duplicate on revisit or count as a hostile that seals a room. Owned companions must reappear correctly on room/floor transitions; emitted shots retain their selected birth properties. Reuse existing allied-actor code where applicable without importing unrelated behaviors.

Add the supported item to the bounded ordinary treasure offering with its source membership/weight. Supply a repeatable natural seed and direct room access. A labelled forced-item test mode may supplement that route.

**Human check:**

1. Collect Brother Bobby; one companion appears for the acquired copy.
2. Walk and fire during an ordinary fight; it follows and hits enemies without changing player movement or firing.
3. Leave and return; ownership survives and no extra companion appears.

**Developer gates:** verify native following/attack cases and copy behavior, actual friendly damage and collision, pause/transition cleanup, owned-stat independence, live configuration/export/load and retry. Add only the familiar state/serialization fields this delivery needs.

### PW-A01 — active slot, use and recharge with Yum Heart

Status: implemented in ordinary expeditions; developer checks pass; scoped human review accepted. See [PW-A01 report](reports/isaac-first-floor-parity/pw-a01-yum-heart/README.md).

**Visible result:** a usable active item with a named HUD slot, charge display and a dedicated activation action.

Integrate one active-item slot, pickup/swap transactions, charge state, use admission and eligible room-clear recharge. The source XML declares four charges for Yum Heart; verify its healing amount, full-health/no-capacity behavior, activation/charge-consumption order and recharge caller rules before enabling them. Reuse the selected half-heart health model and actual healing consumer.

Provide a HUD button and a separate rebindable use action after checking existing bindings. Preserve movement, aim, firing, dodge and placed-dynamite controls. Avoid accidental repeated activation from a held button or duplicate event. A full-slot swap must preserve the old item and applicable charge state in the world, with no immediate swap-back loop. Use a second source-eligible Yum Heart pedestal to exercise the swap path before introducing another active effect.

Recharge only on verified qualifying events. Revisit, pause, preset loading and explicit floor regeneration must not accidentally award repeated charges. Record the deliberate testing-reset policy. Active charge is gameplay state, not a balance-preset setting.

**Human check:**

1. Collect Yum Heart and inspect its slot/charge display.
2. Take damage and use it; verify healing and charge consumption.
3. Clear the required eligible encounters and use it again; also inspect the supplied swap example.

**Developer gates:** actual health caps, invalid-use behavior, one use per input, duplicate-clear protection, swaps/room/floor transitions, charge serialization and migration, configuration reload and fresh-build retry. Do not defer correctness of the slot while shipping only a healing hotkey.

### PW-T01 — trinket slot, swap and drop with Cancer

Status: explicitly selected after accepted PW-A01; main-game implementation, native bounded comparisons, nine core suites, actual Game/Renderer and CLI checks pass. Scoped human review accepted; see [PW-T01 report](reports/isaac-first-floor-parity/pw-t01-cancer/README.md).

**Visible result:** a distinct trinket slot with a passive effect that is present only while the trinket is held.

Implement one held-trinket slot, source pickup admission, swap/drop behavior, safe world placement and effect removal. Cancer exercises the existing Tears consumer, but its exact cache stage, cap interaction and combination with Sad Onion must be verified; do not substitute the Onion formula for its effect. Do not count trinkets as permanent collectible copies.

Use the shared pickup actor/contact path. Connect a narrowly supported ordinary trinket producer after verifying its source eligibility/subtype selection and retaining the documented restricted-pool adaptation. Provide a naturally generated witness and direct access; a forced review spawn alone does not finish the delivery. Broader trinket drop distributions remain deferred and must be labelled incomplete.

Dropping/swapping must remove precisely this item's contribution, leave the old trinket in a reachable position and avoid immediate unintended recollection. The player needs a distinct drop/swap control without losing current combat controls. A duplicate Cancer actor can exercise same-kind swap behavior; a different-effect swap follows in PW-T02.

**Human check:**

1. Collect Cancer; inspect the trinket slot and changed firing cadence.
2. Drop it; cadence returns to the correct owned-passive baseline.
3. Pick it up again, then leave and return; the effect occurs once and the slot remains correct.

**Developer gates:** exact held/removed contributions, Sad Onion interaction and caps, drop placement/contact gates, same-item swaps, no duplicate ownership, source producer bounds, live configuration/presets, transitions and slot serialization.

### PW-C01 — all four categories in one ordinary expedition

Status: main-game implementation and developer verification pass; combined human review accepted. Accepted PW-A01/PW-T01 are committed as `27d7691c`. See [PW-C01 report](reports/isaac-first-floor-parity/pw-c01-category-check/README.md) for the launch and evidence. The real save audit confirms interrupted-history recovery only; full live expedition resume remains D18 work.

**Visible result:** the accepted passive build, Brother Bobby, Yum Heart and Cancer work together through the same expedition.

Use normal acquisition paths and a reproducible floor; direct review travel may shorten setup. Verify actual combat, active use/recharge, trinket removal, familiar transitions and owned-passive composition together. No special review executable or hidden combat buffs.

Exercise floor transition, death retry and configuration reload. Audit newly introduced item state against the real gameplay-save path: owned items, equipped slots, charges, applicable temporary effects, actor reconstruction and consumed world pickups. Add a bounded migration/continuity fix if required before claiming save/resume acceptance; do not treat a preset export as an expedition save or broaden into a replacement campaign system.

**Human check:** acquire the displayed build; use all four categories in one fight; traverse the recorded transition/reload case and verify the build/state. Keep the setup short; the developer handles numeric measurements and controlled edge cases.

**Completion gate:** all four categories have an accepted playable example, expected lifecycle/state behavior, live/export/load support and a tested main-game handoff. Full native item-system parity remains a separate goal.

## Optional second examples, after the first milestone

PW-T02 Whip Worm is implemented, developer-verified and scoped human-accepted after PW-C01 (`81138b55`). See [PW-T02 report](reports/isaac-first-floor-parity/pw-t02-whip-worm/README.md). The other second examples remain unselected.

| Delivery | Item | Additional capability exercised | Short visible check |
| --- | --- | --- | --- |
| PW-F02 | Halo of Flies10 | Orbital formation and enemy-projectile interception; verify source count, orbit/contact rules and any other owned effects. | Collect; observe the source-defined orbiters and blocked shots in an ordinary ranged encounter. |
| PW-A02 | Book of Shadows58 | Temporary active effects, expiry and different-item swapping. Verify source duration/admission/charges rather than inferring runtime duration from XML alone. | Swap from Yum Heart; activate protection; verify expiry and that universal dodge retains its own immunity rules. |
| PW-T02 | Whip Worm27 | Different-effect trinket swaps and the independent Shot Speed consumer. | Swap Cancer for Whip Worm; the Tears contribution is removed and the verified shot-speed effect appears. Swap back. |

Each optional example includes its complete scoped item effects and the same configuration, natural-acquisition and lifecycle gates. If a required effect depends on a missing system, record that dependency before coding; do not label a partial effect complete. Second examples are not prerequisites for showing the first example of every category.

## Shared rules for every delivery

| Area | Required boundary |
| --- | --- |
| Main game | Ordinary Game/Simulation, generation, pickups, inventory and encounters. No standalone demo as the delivered feature. |
| Source balance | Installed Repentance1.7.9b XML/native captures; preserve source values separately from conversions and user overrides. Verify effect/order/timing for the named item before handing it over. |
| Accepted controls and feel | Keep immediate walking stop, accepted base pace, eight-direction firing, mouse/keyboard mapping, universal dodge and placement-only ordinary dynamite. Keep canyon size/shape/connections and accepted165% preset. Only an owned item's selected effect changes the corresponding behavior. |
| Live edits | Each new tunable reaches its gameplay consumer. Stat changes affect the next eligible calculation/attack; emitted bullets and committed actions retain their snapshots. A familiar steering edit applies at the next steering tick. Define active-duration/recharge edit boundaries explicitly and avoid resetting a running timer or granting free charge. |
| Staged edits | Pool/producer/layout changes wait for Apply map changes. Explicit testing regeneration retains player/build and uses a documented charge/slot/companion policy while resetting floor content. It remains available after exploration/combat. |
| Presets | Export, load, remember and CLI next-expedition loading cover all new configuration fields. Validate atomically; migrate older supported presets without changing accepted settings. The original user preset stays intact. |
| Gameplay state | Owned items, slots, charges, pending effects and consumed pickups are distinct from presets. Add versioned serialization/reconstruction for new state and verify actual supported lifecycle paths. Death retry starts a new build while keeping the selected configuration. |
| Item presentation | Distinct, readable world object/icon and category/owned-state display using the normal renderer and existing asset conventions. Treasure bases remain centered and solid, with reachable collection edges. |
| Evidence and handoff | Focused behavior and integration checks, a tested exact launch command/direct target, up to three human actions, expected visible outcome and explicit remaining gaps. Record acceptance separately from developer verification. |

Build only the shared machinery the current example needs. For example, do not hold Brother Bobby behind complete orbitals, every familiar synergy, all transformations or a general scripting rewrite. When a source question blocks a delivery, identify that exact unresolved behavior; do not change source constants to hide the gap or keep expanding research scope.

## Deferred catalog expansion

After the first milestone and any selected second examples, classify the catalog by required behavior and implement small selected batches. Passive stat modifiers, projectile forms, event effects, different familiar behaviors, active charge types and trinket procs have different dependencies; category membership alone is not a batch boundary.

Deferred work includes the rest of the425 passive,126 familiar,170 active and188 trinket definitions; hidden/internal entries need explicit disposition, not automatic natural-pool inclusion. Also deferred are extra active/trinket slots, swallowed/golden trinkets, battery/overcharge variants, transformations, rerolls/depletion/unlock/profile parity, unimplemented supporting pickups and unrelated bosses/rooms. Required dependencies of a selected example must be identified and handled within its bounded delivery.

Maintain one row per item with identity, category, source effects/evidence, eligible producers/pools, dependencies, implementation status, ordinary availability, user verdict and known adaptations. A familiar/active/trinket framework is not an accepted count for every catalog entry. Do not publish a full-catalog completion percentage from these examples.

## Current checkpoint and next proposal

**PW-T02 — Whip Worm27: accepted checkpoint.** The second trinket is enabled with independently verified +0.5 Shot Speed, actual Cancer/Whip swaps, ordinary producer support and live/export/load boundaries. Developer checks and the scoped human playtest pass. Next proposed: **PW-F02 Halo of Flies**, then **PW-A02 Book of Shadows**. Neither is selected; full-catalog expansion remains deferred. Full native equivalence and full live expedition resume remain open.
