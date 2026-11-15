# Preplaced ordinary chest — source room 1.31.0

Selected on 2026-11-15 after the user accepted the corrected chest and approved the proposed commit and preplaced-layout continuation. The earlier room/coin/chest checkpoint is committed as `c00b87a3`. **The preplaced chest is enabled and developer-verified. The user positively acknowledged the scoped playtest on 2026-11-15 ("ok, cool, whats next???").** This delivery is committed as `3dee8d4f`.

## Playable check

The main game is launched directly into displayed room6 with seed375, the unchanged user165% preset, normal health6, normal damage and god mode off. Death retry returns here.

```sh
build/deathward --expedition --seed 375 --review-source-room 31 --mute --save /home/kambo/.local/share/deathward/reviews/preplaced-chests/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

1. Find the closed chest inside the rock enclosure. Clicking it cannot pass through the intact rocks.
2. Approach the enclosure, press **B** to place dynamite, and retreat. Ordinary bullets do not destroy these rocks.
3. Click the chest through the opening. It opens without a key, scatters its fixed pickup batches and remains solid.
4. Leave and return: the rocks stay destroyed and the chest stays opened without paying again.

[Closed room](closed.png), [opened chest after demolition](open.png), [launch record](interactive-handoff.json).

## Enabled behavior

The pinned Basement record contains twelve plain rocks around one ordinary chest at source cell(6,3), original spawn ordinal6, and no enemies. The complete arrangement is admitted only when the existing native numeric/weighted selector chooses it for a compatible opening-floor canyon room. Protected objective/key/story sites retain their previous content without rerolling. Other chest-bearing templates remain unsupported. [Complete source record](source-room.json).

The chest seed comes from the existing native descriptor/ordinal sequence, including all omitted source spawn steps. Initial floor seeds/order and canyon spatial mapping remain DeathWard adapters. The chest stays at its enclosed source position and is ready on first room entry without the clear-reward birth wait. Capacity or occupied-position failures retain that exact position and seed. The accepted smaller scene-lit model and shared movement/navigation collision apply in both closed/open states. Demolition uses ordinary DeathWard dynamite; there is no extra combat-clear award in this empty source room.

Opening and delivered contents persist in memory on room revisit. Full expedition gameplay save/restore is still unfinished. Chest contents remain the previously accepted pickup-batch adaptation; this work does not implement the complete native loot table, timing or physics.

## Configuration

**TUNING → REWARDS → ROOM LAYOUTS → SOURCE LAYOUTS** includes this arrangement. OFF/SOURCE changes stay pending until **Apply map changes**. Apply regenerates the current floor without restarting the expedition; it retains the player/build/settings and places the player outside a reclosed enclosure. The existing full/half heart testing mode is unchanged.

Schema21 (`preplaced-chests-v21`) records the expanded layout policy, exports/loads/remembers the existing controls, and migrates schemas1–20. Loading a different map mode stages it. **AFTER CLEAR → CHESTS** still controls only future combat-clear chest rewards; disabling it does not remove preplaced chests. No new tunable or forced chest frequency is introduced. Accepted canyon geometry/connections, movement/shooting/dodge, health/damage and original preset bytes remain unchanged.

## Verification and limits

Five focused suites pass: preplaced chest layout, preset contracts, existing chest gameplay, source room coverage and heart/rock arrangements. Physical opening/navigation/loot/revisit checks cover the smallest supported size(.75,5–5; seed669), the accepted preset(1.1,7–9; seed375), and the largest supported size(1.5,10–10; seed375). This is boundary/reference coverage, not an exhaustive random-floor sweep. The original record, source cell and seventh spawn-state seed are checked; the source extractor verifies pinned data consistency.

The actual Game/Renderer check uses mouse OFF/SOURCE/Apply, normal-health keyboard dynamite placement and retreat, mouse chest opening, revisit, death retry, export/remember and a fresh load. Three CLI launches cover schema20 with clear-chests off, schema21 enabled, and schema21 source layouts off. Closed/open renders were inspected at165%. [Validation](validation.json), [tests](tests.log), [detailed size checks](test-detail.log), [actual input workflow](input.log), [CLI loads](cli-validation.json).

The accepted delivery is committed as `3dee8d4f`. The user subsequently selected [preplaced ordinary coins](../preplaced-coins/README.md) in one complete compatible source arrangement. Remaining work includes other preplaced chest templates, full native loot distribution/pills/trinkets/nested/special chests, native factory/RNG/pushing/timing/profile/modifiers, full gameplay save continuity and the earlier room/coin gaps. Exact Isaac size/shape/connections remain excluded; bulk parity stays paused.
