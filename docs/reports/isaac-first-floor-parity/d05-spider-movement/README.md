# D05 — ordinary Spider movement in the main game

Implemented on 2026-11-11 after the user acknowledged D04 and selected the next delivery. Ordinary Spider `85.0.0` now uses source-derived burst/idle movement in generated main-game encounters. Developer checks pass; the user's D05 verdict and full native actor acceptance remain open. D04 Gaper behavior remains enabled. D06 is next selectable, not authorized by D05.

## Play it

```sh
build/deathward --expedition --seed 0 --mute --save /home/kambo/.local/share/deathward/reviews/first-floor-d05/campaign.save --balance-preset docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json
```

This retains the user's accepted map, route length, shooting and 165% default zoom. It starts the main game with ordinary generated encounters and normal damage, without practice mode or invulnerability. Room **6**, directly connected to the entrance, naturally contains **four ordinary Spiders and one stationary Horf**. Other rooms may contain actors whose movement has not yet been selected.

1. Enter room 6, approach a Spider, then retreat. Expect a pause, a short committed burst and another pause, rather than continuous pursuit.
2. Circle nearby cover. Spiders should keep their chosen destination during a burst and stop/recover when terrain obstructs it.
3. Open **TUNING → ENEMIES**, compare Spider burst movement at **100% and 50%**, then reset. Gaper movement, player movement and shooting have independent controls. Retry after death remains available.

Human review should take about 1–3 minutes. The report's `custom-spider.json` is a developer round-trip fixture (65% Spider drive and a staged 120% map), **not** the user's accepted preset. The original external export and its D03 backup were not modified.

## Gameplay and live-edit boundaries

Main `Game::startExpedition` enables the ordinary Spider consumer before the first tick, including normal expeditions and the tutorial. It also applies to future ordinary Spider spawns. Direct historical `Simulation` fixtures keep authored behavior unless explicitly opted in. Big Spider, Strider, Swarm Spider, Pooter and other identities keep their existing behavior. No encounter pools, source mechanics files, player pace, shooting, dodge, HP, damage or hitboxes were changed.

**Spider burst movement** uses 5 percentage-point buttons, a 100% reference reset and a 10–200% editor range. It changes drive on the next 30 Hz steering update. Existing velocity settles through the controller's retention; editing does not teleport the actor, reset its counter, choose another destination, alter perception distances or alter pause timing. It is not an instant override of knockback/birth impulses or a universal speed cap.

Schema **7**, contract `d05-spider-v7`, exports, loads and remembers `spider_movement_multiplier` independently from D04's `gaper_movement_multiplier`. Schemas 1–6 migrate with Spider movement at 100%, retaining their supported settings. Invalid values, calibration metadata and mismatched overrides are rejected before runtime publication. Map settings remain staged until **Apply map changes**. Regeneration, floor descent and retry preserve both enemy settings. Configuration remains separate from expedition save state.

## Source model and conversions

The target is the preserved installed **Repentance 1.7.9b** executable and XML. [Source record](source-scope.json) keeps source HP 6.5 / Stage HP 0 separate from retained DeathWard HP 20.8 (3.2 conversion); player damage remains 24.

The retained source recurrence is `v = (v + direction × 6) × 0.6` on burst steering updates. Idle damps momentum by 0.6. After initialization, the old idle counter must be at least 14 to attempt acquisition: the fifteenth ready update, about half a second at 30 Hz. A stopping update still applies its final impulse, as the native code does. Source arrival distance 14, stuck-speed threshold 3 and counters remain unchanged.

D05 shares D04's fixed calibration: `world/native = 4.8 / (4.414238452911377 × 60)`. This anchors enemy motion to accepted **base** player walking, independent of current player Speed, zoom or room-size overrides. A long unobstructed reference burst approaches 9 native coordinates per NPC step, about **4.893 world units/s / 102% of base player walking**. This replaces the old 27-world-unit/s burst ceiling; it does not slow the player's 4.8 pace. Source acquisition 100–200 and wandering 70–110 distances use the same conversion.

A newly executed native instruction window verifies that prediction adds **ten player-step velocities**, not ten NPC-step velocities. The former `/30` conversion doubled the lead for DeathWard's per-second player velocity. The selected ordinary consumer now uses `/60`, with six captured cases compared through actual acquisition in Simulation. [Capture script](../../../../scripts/isaac-reference/capture-spider-target-lead.py), [native cases](native-target-lead.csv), [instruction window](native-target-lead.asm). The target resolver and room clamp are explicitly outside this native execution window; no helper is stubbed or claimed verified by it.

## Verification

- Re-execution of the preserved Spider/Pooter native capture and new target-lead capture passes their byte-for-byte checks.
- **48 independent native Spider states**, compared at 30/60/120 Hz physics partitions and two translated positions: **288 comparisons**, maximum position error approximately 0.00002861 world units. Original bounds remain 0.002 position / 0.005 velocity; these are repeated comparisons, not 288 new native samples.
- All **16 native idle gates** and **six native target-prediction cases** pass through the selected consumer. Acquisition, committed destinations, repeated pauses/bursts, far wandering and independent live-drive transitions pass.
- Physical checks cover visible barriers, newly obstructed bursts, prediction clamping, narrow room bounds, river avoidance, stun and unchanged contact damage. Main-game checks exercise the natural four-Spider encounter against generated canyon terrain.
- **11 focused CTest suites pass**: Spider gameplay/family/variants, three private Spider/Pooter movement partitions, Gaper gameplay, status regression, preset contract, canonical shooting and player Speed. [Results](regression.log).
- Actual Game/Renderer mouse/keyboard checks pass: Spider edit/reset, retained actor state, pending map, export/load, rejection without partial application, regeneration, descent, death retry and fresh Game. D04 Gaper and D03 shooting UI regressions pass. [UI evidence](input-tests.log), [panel capture](enemies-panel.png).
- Three separate main-executable CLI launches verify accepted schema-5 loading, custom schema-7 export loading and remembered configuration without a preset argument. The external user export's SHA-256 remains unchanged. [CLI results](cli-verification.json).

During development, the new tests exposed fixture mistakes: float HP equality needed the existing conversion's rounding tolerance; Spider has no enabled Freeze profile, so a new test could not assert one; the first UI frame helper omitted drawing/dispatching controls. The fixtures were corrected. No Freeze behavior was added and no movement thresholds were relaxed to make tests pass.

## Remaining and next

**D05 human review is pending.** The source arithmetic and selected main-game integration are verified, not full native Spider equivalence. DeathWard still uses its RNG, target selection, room bounds/sight/sweep and body geometry. Native acquisition RNG/distribution, target-helper exceptions, exact clamp/masks, full NPC/live scheduling, status/champion/lifecycle coverage and shared room/body scale remain unaccepted. Spider's retained radius is 0.4, versus source XML radius 13; no new hitbox policy was selected. Big Spider birth impulses and thrown offspring behavior are unchanged even when their resulting ordinary Spider later uses D05 drive. The broader Freeze/status gap remains open.

HP encounter acceptance stays held until enemy pressure is accepted. **Next selectable: D06 — Pooter wandering and enemy shots**, including shot timing/speed and live tuning. Full first-floor parity and later deliveries remain unfinished; the bulk automatic effort stays paused. D04 and D05 are currently uncommitted.

## Subsequent delivery

The user positively acknowledged D05 and selected D06. Ordinary Pooter movement and shots are now enabled with schema-8 presets; schema-7 Spider presets migrate without losing their settings. See the [D06 handoff](../d06-pooter-shots/README.md). D05's full native actor gaps remain open; this acknowledgment does not certify them.
