# Complete combat arrangement: Basement 1.4.0

The user accepted the ordinary caller/descriptor and direct-entry delivery on 2026-11-12. It is committed as `cf466e90`. This selected continuation adds one complete enemy-and-cover arrangement to ordinary main-game generation. Developer checks pass; the user accepted this scoped main-game playtest on 2026-11-15 ("ok, looks good!"). [Acceptance record](human-acceptance.json).

## Source and enabled contents

Pinned Repentance 1.7.9b Basement template **1.4.0** contains **two ordinary Gapers and seventeen plain rocks**, with no initial pickups or other actors. The Gapers occupy source cells (10,1) and (2,5). All nineteen spawn stacks contain a single weight-1 choice. The existing native descriptor/spawn sequence advances through all nineteen slots. [Complete source record](source-room.json).

```text
.............
.#.#.#.#.#G#.
.............
..#.#.#.#.#..
.............
.#G#.#.#.#.#.
.............
```

`#` is a plain rock; `G` is an ordinary Gaper. The existing uniform source-cell adapter maps this arrangement into the retained canyon basin. Room outlines, size/range controls, physical corridors and their route-length control remain DeathWard's deliberate exceptions. No source room dimensions or door positions are imposed.

When **SOURCE LAYOUTS** naturally selects template4 in a compatible opening-floor ordinary room, its enemies and rocks now replace that room's unrelated encounter/cover. It excludes random outcrops, river, supply cache, initial coins, ambient enemies and champions. Gapers retain accepted movement and HP32 at the regular-HP multiplier1; canonical Damage3.5 still produces11.2 internal damage. Eight-direction controls, walking and universal dodge are retained. Existing selected clear rewards still run after combat.

Compatibility is deliberately bounded: legacy miners/altar rooms (internal indices2/3), required-key sites, explicit story/special rooms and D08's separate injected template47 are not replaced by template4. A protected site's template4 selection remains metadata for its existing heart layer, with no heart slots; it is not rerolled and does not claim a complete imported encounter. `--review-source-room 4` requires the complete combat arrangement, not that metadata-only match. This restriction is a DeathWard progression adaptation, not a native eligibility rule.

Template91's accepted rock/heart arrangement and D08's two-Gaper template47 remain available. The **SOURCE COMBAT ROOM** switch still controls only template47; naturally selected template4 belongs to **REWARDS → ROOM LAYOUTS → SOURCE LAYOUTS**.

## Navigation and application boundaries

The small-room check reproduced physically passable aisles that the ordinary two-unit navigation grid could not sample. A bounded fallback aligned to the placed source cells now handles failed routes with an endpoint in this complete template. Local routes and connections through the existing door approaches retain full actor-radius collision on every segment. Ordinary Gaper steering, force/friction and speed are unchanged. This is a canyon navigation adaptation, not a claim of native obstacle-navigation equivalence.

OFF/SOURCE/test edits remain pending until **Apply map changes**. Apply is allowed during combat and rebuilds the floor without restarting the application or expedition, retaining player/build and expedition identity. The selected content policy is exported, loaded and remembered in **schema17**, contract `d09a-combat-rock-room-v17`, policy `basement-native-descriptor-rooms4-91-v5`. Schemas1–16 migrate with their existing settings. Invalid presets still reject atomically. No new numeric tuning control was introduced. Live stat changes do not reroll existing rooms.

## Verification

- The extraction script reproduces all seventeen rock cells and both enemy cells from the pinned STB, alongside the existing433-template pool and template91 record. Run `python3 scripts/isaac-reference/extract-room-heart-layouts.py --check`.
- Nine size/range combinations were generated for seed268. Six naturally selected the complete arrangement, spanning source-cell sizes1.323–3.572 world units. All six retain exact legal spawns, unchanged HP, seventeen rocks, no extra initial content, door access and collision-checked routes between each actor and the entrance, including cross-room routes. The other three naturally selected different content; review correctly rejects them instead of forcing template4.
- Actual Simulation checks exercise small-room click movement and both live Gapers navigating toward the player. A separate controlled-aim fixture holds enemies still to verify real projectile obstruction, ordinary damage/death handling and automatic room clear. This is not a full live-combat AI comparison. Normal dynamite opens rocks; destruction and cleared/reward state survive revisit. Apply OFF/ON preserves player/build/identity and consumes the selected HP override on regenerated enemies.
- Ten focused CTest suites pass: core contracts, destruction, authored rails, presets, heart layouts, heart rock room, combat rock room, native selector reference, red-heart rewards and D08 source combat room. [Regression log](regressions.log), [focused gameplay log](gameplay.log).
- Actual Game/Renderer checks pass for natural direct entry with normal HP and no god mode, mouse OFF/SOURCE/Apply during combat, export/remember/reload, accepted settings and death retry. The previous source91 Game/Renderer check also passes. [Input log](input.log), [source91 regression](heart-regression.log).
- Three separate application CLI launches pass with schema5,16 and17 presets. All open seed268/room5/template4 with HP6, normal damage enabled and zoom165%. The external preset remains unchanged at SHA256 `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`. [CLI validation](cli-validation.json), [exported preset](preset-v17.json).

[Room capture](room.png) and [layout controls](layouts.png) use the actual Game/Renderer. Their initial-frame FPS overlay is not a performance benchmark.

## Short human check

```sh
build/deathward --expedition --seed 268 --review-source-room 4 --mute --save /home/kambo/.local/share/deathward/reviews/native-combat-rock-room/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

This opens directly in displayed **room5**, with two Gapers among staggered rocks. Selection seed3126245951 produces descriptor spawn seed4153270430. This is a naturally generated encounter, with normal health/damage; death retry returns here.

1. Move between the rocks and shoot the two enemies. Rocks should block shots and movement; enemies should pursue through the gaps.
2. Optionally use PLACE beside a rock and retreat. The destroyed rock should stop blocking you.
3. Clear the encounter, leave and return. Enemies must stay cleared and demolished rocks must stay destroyed.

## Remaining work and next step

The scoped playtest is accepted. Full native acceptance remains open. Most other selected source templates still supply only their heart layer, so complete ordinary-room content coverage remains limited. The433-template shape1 subset, DW initial selection seed/order/weight lifetime, protected-room compatibility rule, actor/grid factory and substitution, native RNG/profile/unlocks/fallback wrappers, other descriptor consumers, full actor/physics/collision/drop equivalence and native bomb behavior remain unaccepted. Plain source rocks retain DeathWard destruction and intentionally do not introduce a new rock-coin producer. Exact Isaac room size/shape and connections are excluded by the user; coins and unrelated bulk parity remain deferred.

Next proposed delivery: extend the complete-content set to another compatible template using already supported actors/grid, and address its actual selection/factory dependencies. Do not treat this one-room delivery as full floor parity or resume the paused bulk effort.
