# D04: ordinary Gaper movement in the main game

2026-11-11. **Selected D04 is enabled in ordinary main-game expedition encounters. Developer checks pass; human review and full native enemy acceptance remain open.** D03 is committed as `16ec148d`. No HP, damage, room-generation or other enemy-variant rollout is included.

## Playable handoff

Restart the main game with the committed copy of your accepted settings and a repeatable natural encounter:

```sh
build/deathward --expedition --seed 57 --mute --save /home/kambo/.local/share/deathward/reviews/first-floor-d04/campaign.save --balance-preset docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json
```

Seed **57**, first floor, displayed **room 2**, directly connected to the starting room, contains **six ordinary Gapers and one stationary Horf**, with no champions. This is the normal generated room and normal residents: no replacement pool, injected demonstration actor, god mode or private review executable is required. The original seed 1866 has no ordinary Gapers on its first floor under these settings, so it is unsuitable for this actor's review.

The command preserves Speed 1, the accepted walking/stopping/dodge/aiming, Tears 1.9272734, Shot Speed 0.9, Range 6.5, room size 110%, minimum/maximum 7/9 half-tiles, route length 26% and default zoom 165%. A separate D04 campaign path avoids changing an already running D02 session. Schema-5 presets load with reference Gaper movement 100%; your original external export and committed backup remain unchanged. The same feature is enabled for ordinary Gapers in every other normal main-game expedition and the tutorial.

Three short checks:

1. Enter **room 2** and circle the walking Gapers before firing. They accelerate into a slower pursuit, turn toward you and go around cover. Dodging and the accepted player pace stay familiar. The Horf's ranged attack is unchanged.
2. Open **TUNING → ENEMIES**, lower **Gaper movement** to 50%, close the panel and observe their slower pursuit. **Reset Gaper movement to 100%** restores the reference. Existing momentum settles rather than disappearing on an edit.
3. **Export**, then **Use next expedition**. Reload that exported preset in a fresh main-game launch and confirm the movement value and effect. Death retry keeps the active settings; ordinary floor descent keeps them too.

Injured/killed Gapers can still morph into the existing headless enemies. Those controllers are outside D04; judge the ordinary body movement first. A window started before rebuilding must be restarted to use D04. This handoff does not silently replace the user's running game.

## Source model and explicit conversion

The immutable source Gaper profile retains force **0.497999996**, pursuit retention **0.7**, blocked retention **0.85**, arrival retention **0.5**, distance gain **0.1**, cap **2**, arrival distance **1 native coordinate**, and **30 NPC updates/s**. See [source-scope.json](source-scope.json) and the preserved [native trajectories](../gaper-trajectories/README.md). No wiki value supersedes the pinned Repentance 1.7.9b records.

The ordinary far-target recurrence has steady velocity `2 × 0.498 / (1 − 0.7) = 3.32` native coordinates per NPC update. The preserved native ordinary player reaches `4.414238452911377` per movement invocation at 60 invocations/s. The adaptation therefore uses:

```text
world scale = accepted base walking 4.8 / (4.414238452911377 × 60)
Gaper steady pursuit = 3.32 × 30 × world scale ≈ 1.80506
Gaper / base player = 0.37605 ≈ 38%
```

The previous `.1` conversion yielded 9.96 world units/s, exceeding the accepted player pace. The new conversion is fixed against **base** walking; changing the player's Speed stat does not automatically accelerate enemies. Room resizing and zoom do not change it. This reuses the verified native relative movement model while preserving the user's chosen player pace; it is not proof of equal native room-crossing time or full encounter difficulty.

`Game::startExpedition` enables the ordinary `10.1.0` controller and preset value before simulation updates. The shared controller/spawn path handles generated residents and later spawns. Standalone historical Simulation/reference fixtures retain authored units unless explicitly configured; private source-room experiments keep their existing flags/scales. Frowning, Flaming, Rotten and headless variants are unchanged. Existing champion motion multipliers still compose with an ordinary Gaper's base; complete champion acceptance is separate.

## Movement and physical-world fixes

- Clear pursuit selects the current target on every NPC steering update instead of holding a stale destination. Arrival is distinct from an absent route, preserving source 0.5 versus 0.85 retention.
- Conversion into arbitrary world coordinates can round an exact one-coordinate arrival just outside the source boundary. A guard bounded by four float epsilons times the involved world-coordinate magnitude stabilizes that comparison. It does not retune the source distance/friction or relax the verification bounds. Tests cover three translated placements, including coordinates beyond the handoff room's magnitude.
- Current canyon routing, physical footprint checks and crowd separation remain active. When a player stands at a legal narrow edge that cannot fit the larger Gaper footprint, the Gaper selects a reachable approach point within the existing contact reach. Every route segment still checks full body clearance and line of sight. The generated-room regression reproduced a 10-second standstill before this fix and now records sustained legal pursuit.
- Existing ordinary-Gaper fleeing motion uses the same conversion and explicit drive multiplier to keep its units consistent. This does not certify native fear targeting, random choices or status scheduling.

The retained body radius is **0.6** and the player contact radius is **0.48**. Preserved XML gives source Gaper radius **13**; simply applying the movement conversion would give about 0.236. D04 checks existing terrain/contact behavior and records this difference; it does not silently change hit geometry. Contact still removes one half-heart on the tested eligible hit, respects hurt immunity and does not pass through walls.

## Live tuning and persistence

**Gaper movement** defaults to **100%**, uses **5 percentage-point** steps, and allows **10–200%** for testing. These are editor bounds, not Isaac stat caps. The setting scales movement drive, with source values preserved in immutable mechanics. It takes effect at the next ordinary 30 Hz steering update; current velocity, animation phase, position, HP, items and projectile state are not reset. Existing enemies, dormant room residents and future spawns consume the active value.

Schema **6**, contract `d04-gaper-v6`, stores `gaper_movement_multiplier` in resolved configuration and explicit overrides, with calibration identifier `player-relative-v1`. Schemas 1–5 migrate with multiplier 1 while retaining their existing fields. Export/load/remember, CLI loading, map Apply, floor descent and retry are wired. Invalid or incompatible presets reject before changing runtime settings. Shooting edits and enemy edits leave map drafts pending until Apply. The [custom preset](custom-gaper.json) is a test example (65% movement and a pending 120% map), not a replacement for the accepted user preset.

## Verification

- **Seven unique focused suites pass:** `gaper_gameplay`, `gaper_trajectories`, `gaper_family`, `first_floor_status_effects`, `balance_preset_contract`, `canonical_shooting_integration`, `player_speed_attribute`. The final navigation correction reruns the four relevant Gaper/status suites.
- The D04 consumer matches **1,260 preserved ordinary trajectory samples across eight cases**, replayed at three world placements (**3,780 comparisons**, not 3,780 independent source samples). Cases include long/short pursuit, arrival, a coincident waypoint, turning, reversal, moving target and blocked route. Maximum observed errors are about **0.0004044 position / 0.001322 interval velocity**, below the predeclared **0.002 / 0.005** bounds.
- Real Simulation checks cover multiplier bounds/intermediates, transition back to reference, unchanged variants/HP/body, stun/freeze, rounding finite cover, remaining behind sealed cover, resuming after cover removal and ordinary contact/hurt immunity.
- Actual **Game/Renderer** input verifies mouse/keyboard controls, a naturally generated Gaper consuming the edited drive, 600 further Game updates of legal crowd pursuit toward the edge case, invalid-load isolation, preserved user stats/map drafts, export/load, map Apply, floor transfer, death retry and a fresh Game instance. The existing D03 shooting UI regression passes.
- Separate main-executable processes load the accepted schema-5 preset, a custom schema-6 preset and the remembered schema-6 configuration. All resolved values match; the external export's SHA-256 remains unchanged. See [CLI evidence](cli-verification.json), [validation](validation.json) and [panel capture](enemies-panel.png).

## Remaining work

Human D04 review is pending. Full native room/body/hit geometry, terrain-mask generation and route caching, live full NPC scheduling, status/champion branches, death morph/offspring movement and broader actor acceptance remain open. Source movement evidence and enabled adapted gameplay are distinct. HP encounter acceptance remains held until the relevant enemy pressure is accepted; no HP tuning compensates for motion.

**Next selectable after this review: D05 — Spider burst/idle movement in ordinary encounters.** D05 and the rest of the floor are not authorized or completed by D04. The wider automatic parity effort remains paused.


Subsequent checkpoint: the user positively acknowledged this delivery and selected [D05 ordinary Spider movement](../d05-spider-movement/README.md). D05 is now enabled and developer-verified; its human verdict is pending. This acknowledgment does not close the full native Gaper gaps above. Current presets use schema 7 and migrate D04 schema 6 without losing its movement override.
