# Ordinary chests: first playable main-game delivery

The user selected chests before further coin work on 2026-11-15. The first ordinary unlocked chest is integrated into opening-floor canyon combat clear rewards. **This is a pickup-batch adaptation, not complete Isaac chest parity.** The user positively acknowledged the first delivery but rejected its oversized chest and separate rendering approach. The user acknowledged the revised half-size chest and scene rendering, then reported the missing collision. The shared collision correction passes developer tests. On 2026-11-15 the user positively acknowledged the corrected playable chest ("ok, cool!"); this records scoped human acceptance, not full native parity. The automatic bulk parity effort remains paused.

## Enabled gameplay

The existing once-only native ordinary reward selector now delivers its chest50 outcome when CHESTS is enabled. Hearts and coins retain their existing single-roll rules; no extra roll or forced chest is added. Ordinary opening-floor combat eligibility, retained room geometry, controls and accepted balance remain unchanged. Preplaced chest layout slots are not enabled by this checkpoint.

The wooden chest appears closed, opens on player contact without a key, animates its hinged lid and scatters physical pickups. Clicking the chest selects a reachable edge; clicking beyond it routes around the body. Touch opening keeps the current destination rather than cancelling a route that happens to pass nearby. Both the closed and opened chest now remain solid character obstacles. The previous closed-only push-out/decorative-open behavior was rejected by the user and removed. Contents are resolved at chest birth and never rerolled by Luck/policy edits, room revisit, a full pickup store or blocked placement. Drops wait for reachable free ground/capacity and begin their collection clock only when actually spawned. Unopened/opened state and uncollected loot persist in memory across room visits; full expedition gameplay-save restore remains a separate unfinished feature. Explicit Apply map changes resets the floor actors as before.

Contents are 2–3 pickup batches, with public ordinary-batch weights coins35%, hearts20%, keys15%, bombs30%. Coin batches contain1–3 coins; other batches contain one pickup. The preserved native ordinary subtype resolver supplies supported coin and heart variants with rare unlock gates off. The existing typed-health consumer handles emitted red/soul/black/eternal/blended hearts. Ordinary keys add one to the retained key inventory, capped99. Bombs become one DeathWard dynamite stick, retaining MaxDynamite9. Refused pickups remain on the ground. All collections pay once. This does not enable key/bomb room-clear producers or rewrite doors, shops or dynamite physics.

## Explicit differences and evidence limits

[Public chest rules](https://bindingofisaacrebirth.wiki.gg/wiki/Chests) describe normal chest outcomes as78% pickup batches,10% trinket,10% pill,1% normal chest and1% locked chest. **This first version always uses pickup batches**, so its overall loot distribution differs. Pills, trinkets, nested/locked/special chests, their item pools/modifiers/unlocks and full native chest loot parity are unfinished. No rare roll is silently claimed as implemented. The optional scope question offered this playable first delivery or the larger missing-systems implementation; the working assumption was explicitly stated in commentary.

The installed Repentance1.7.9b ordinary reward selector and ordinary coin/heart subtype evidence are reused from [room awards](../room-awards/README.md) and [coins](../d09b-coins/README.md). No new native chest-wrapper capture was made. The chest's DW seed stream, equal2/3 batch-count choice, fixed ordinary key/bomb subtype, scatter layout, closed-body contact adapter, .8-second birth gate and .4-second lid animation are authored adaptations, not measured native scheduling/physics. Key/dynamite presentation reuses the coin timing adapter; non-red chest hearts currently reuse the existing selected heart timing. Native pushing, factory/animation gates, subtype exceptions and complete modifier/profile behavior remain open. Source chest chance is the existing initial5% reward band before later replacement, not a newly tuned final spawn rate.

## Model

The chest now reuses `part_0273` directly from the existing `assets/frontier/town.glb` library: this is Fort Mercy's `frontier_part_0273` (`SM_Prop_Chest_01`). The derived opening asset preserves that imported mesh, material and embedded texture/UV convention. Its lid is split at the seam; the interior lining is baked mesh rather than a runtime cube. There is no separate FBX importer. The obsolete export helper has been removed. Original scene libraries remain unchanged.

Both parts use the scene-supplied mesh shader/material/shadow-map contract used by the game's actors and Fort Mercy dressing. The expedition renderer draws the same hinge pose in the dynamic shadow and color passes. Chests cast and receive the existing sunlight shadows; the round fallback shadow is used only when scene lighting is unavailable. Runtime primitive chest/interior drawing has been removed.

The model scale is now0.9, half the rejected1.8 scale in each dimension. Shared `ChestGeometry` constants keep the model, movement body, touch margin, placement clearance and fallback shadow aligned. Player radius stays unchanged. Loot, timing, presets and accepted combat controls stay on their existing paths. This is an art/footprint correction, not a new balance preset field or a native chest-physics claim.

See [asset provenance](../../../../assets/pickups/chest/manifest.json). Regenerate with:

```sh
python3 scripts/bake_chest.py
```

## Collision correction

The chest now participates in `Arena::movementBodies`, the established solid-body movement/pathfinding path. The refresh includes statues and chests from all resident rooms, in either chest state. `Arena::move` applies the existing swept segment checks to walking, universal dodge and grounded movement; `Arena::path` routes around the same body. Chest contact no longer teleports/pushes the player out after movement. The retained collider is the chest body's stable, model-sized box; exact native pickup pushing/physics remain unfinished.

A direct chest click finds the cheapest reachable edge approach using ordinary navigation. Existing click paths are recalculated when a new chest occupies their route. An ordinary clear cannot place the new solid on a player, living enemy, existing pickup or uncollected required key; the same resolved award waits or uses another legal floor point. Loot scatter checks player reachability rather than trying to path from inside the now-solid chest. Debug revisit avoids occupied chest centers. Opening, leaving/revisiting and changing the reward toggle retain collision; an explicit floor regeneration resets the floor actors as before.

These are character movement bodies, as in the existing statue system: this change does not turn chests into bullet cover or change shooting controls/damage. Dynamic pushing, bomb interactions, exact native physical behavior and complete loot rules remain outside this correction.

## Live setting and presets

**TUNING → REWARDS → AFTER CLEAR → CHESTS** controls future first clears. Existing chests, contents and pending awards stay fixed. Schema20 (`ordinary-chests-v20`) exports/loads/remembers `chest_clear_rewards` and records `pickup-batches-adapted-v1`; schemas1–19 migrate enabled. Map edits stay staged until Apply. Death retry, floor transitions and new expeditions preserve the selected toggle. The original165% user preset is unchanged.

## Review

```sh
build/deathward --expedition --seed 50 --review-room 2 --mute --save /home/kambo/.local/share/deathward/reviews/ordinary-chests/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

1. Clear room2. Baseline Luck0 naturally gives an ordinary chest.
2. Walk into it: the lid opens without spending a key. This recorded seed gives three pennies and a half-heart.
3. Collect the coins; the half-heart remains if health is full. Leave and return: the chest stays open and pays nothing again. Death retry returns to the encounter.

## Verification and next

Five focused suites pass: chest gameplay, preset contracts, coin gameplay, red-heart gameplay and the preserved native award/subtype comparisons. Actual Game/Renderer mouse opening/collection, independent toggle, staged-map boundary, export/remember/fresh load, revisit and retry pass. The coin UI regression passes. Two fresh CLI schema20 ON/OFF loads and the interactive original-schema5 launch preserve normal health6, god0, accepted walking/shooting and165% zoom. The GLB payloads have normalized normals; closed/open renders were visually inspected. See [validation](validation.json), [gameplay](gameplay.log), [UI](input.log), [closed chest](closed.png) and [opened chest](open.png). The GUI fixture clears enemies through the developer helper to isolate chest interaction; it does not certify live enemy combat. The interactive review uses ordinary combat, health and damage.

The size/render correction additionally passes the existing chest gameplay suite (including refusal at the old oversized touch distance) and actual Game/Renderer mouse opening, collection, export/reload and revisit/retry checks. Closed/open images were visually inspected at the accepted165% zoom; the separate closed chest casts a visible directional shadow. See [correction build](size-render-build.log), [gameplay](size-gameplay.log), [UI](size-render-input.log) and [closed/open images](closed.png).

Collision verification passes: closed/open bodies stop ordinary walking and dodge from all four sides at30/60/120Hz; direct clicks open from a reachable edge; opposite-side destinations route around either state; minimum/maximum room sizes remain navigable; occupied-player births are refused; debug revisit preserves a legal spawn; existing routes adapt to a new chest. Five suites pass jointly: chest, statues, coin rewards, red-heart rewards and expedition destruction. The actual Game/Renderer mouse workflow now additionally reaches clear ground beyond an opened chest without entering its body. Its first destination overlapped a coin click target; the fixture was corrected to use unoccupied ground, preserving normal pickup targeting. See [collision tests](collision-tests.log), [detailed checks](collision-test-detail.log) and [actual mouse workflow](collision-input.log).

The scoped human collision handoff was acknowledged on 2026-11-15. Recommended next step: commit the accepted checkpoint, then select full ordinary loot dependencies or preplaced chest slots before returning to coin layouts. Full native chest contents/physics/timing/persistence acceptance and the previously recorded broader room/coin gaps remain unfinished. No commit or push is performed by this delivery.
