# D07 — main-game damage, enemy HP and incoming hits

Selected after the user accepted and committed D04–D06 (`50f44a47`), then said “lets go!”. D07 is implemented in the normal main-game expedition and tutorial paths. Developer verification is recorded below; **the user accepted the scoped D07 encounter playtest and requested a commit**. The user also selected D08 next; implementation follows this checkpoint.

## Play it

```sh
build/deathward --expedition --seed 69 --mute --save /home/kambo/.local/share/deathward/reviews/first-floor-d07/campaign.save --balance-preset docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json
```

This loads the user's accepted preset: Speed 1 / walking 4.8, Tears 1.9272734, Shot Speed 0.9, Range 6.5, zoom 165%, rooms 110%, room range 7–9 half-tiles and routes 26%. Migration supplies the newly selected Damage 3.5 and regular HP 100%. The original external export and its D03 backup are unchanged.

1. Enter **room 3 beside the entrance**, naturally containing four ordinary Gapers and one Pooter. Fight normally; their first bodies take three successful ordinary hits at the unupgraded baseline. A Gaper can transform into another body, whose health is separate. Seed 0's adjacent room 6 supplies ordinary Spiders, taking two hits.
2. Allow one separated Gaper/Spider contact or Pooter bullet to hit. It removes half a red heart, followed by the existing hurt-immunity window. Pooter body contact is harmless. Universal dodge and death retry remain available.
3. Open **TUNING → COMBAT**. Compare Damage 3.5 and 7, or regular HP 100% and 75%, then reset. Export/load/remember reproduces these settings. A wounded enemy keeps the same remaining-health percentage when HP changes.

The check should take about 1–3 minutes. The interactive handoff uses normal damage, with no god mode or injected enemies. God mode/held AI in automated tests is explicitly test-only. The user is judging encounter feel, not being asked to measure units or research source values.

## Damage and HP unit policy

The previous main-game ordinary shot dealt **24 internal damage**, while these selected source bodies used **3.2 internal HP per source HP**. That meant **7.5 comparable source damage** per hit. Simply setting runtime damage to 3.5 while leaving those HP values would mix units.

D07 preserves the established internal damage/HP unit throughout the roster and converts canonical Damage once at the player attack boundary:

`ordinary base damage = canonical Damage × 3.2`

Damage **3.5** therefore becomes **11.2 internal damage**. Source base/stage HP, authored conversion/adaptation factors and the audited regular-health control remain distinct. No mechanics asset files or source constants were retuned. This implementation supersedes the earlier private review's limited direct-HP conversion-1 pack; that pack remains research, not production content.

| Body | Source HP | Internal HP at 100% | Actual ordinary body hits |
| --- | ---: | ---: | ---: |
| Frowning Gaper / Gaper / Gusher / Horf / Hopper | 10 | 32 | 3 |
| Fly | 3 | 9.6 | 1 |
| Pooter | 8 | 25.6 | 3 |
| Attack Fly | 5 | 16 | 2 |
| Spider | 6.5 | 20.8 | 2 |

Both source Gaper successor possibilities (Gusher and Pacer), strict overkill boundaries, champion HP and offspring use the same existing internal-unit path. Gaper's source overkill boundary 25 remains authored 80 internal units; no conversion-1 threshold can leak from the private review.

All **155 audited regular profiles** were checked against the preserved installed Repentance 1.7.9b XML: base and stage values agree. [Source verification and policy](source-reference.json) records the pinned hash. [Health inventory](health-unit-inventory.csv) accounts for all **221 registered identities**, including their authored conversions and separate adaptation factors. Source stage mapping is unchanged; expedition floor number is not substituted into the source growth formula.

**Scope limit:** retained custom adaptation factors on other regulars, custom legacy enemies, boss HP and boss/armor/phase behavior are not newly source-accepted. Bosses and nonmembers are excluded from the regular-health override. The global player-damage baseline changes consistently against every target; this consequently changes their kill times too. Existing authored item additions, special damage, explosions and status effects remain in their existing internal unit and are not certified as native item/effect balance. Owned attack modifiers resolve once on new attacks; the panel shows effective ordinary damage with those modifiers in comparable source units. Companion damage derived from the player base continues to use that same internal unit.

DPS is derived, with no separate control: at reference Tears 30/11, nominal source DPS is about 9.545; the user's accepted Tears 1.9272734 gives about 6.745. Their accepted shooting preset is deliberately retained. Neither arithmetic figure proves native real-combat DPS/accuracy/cache behavior.

## Live controls and persistence

| Control | Step and range | Application |
| --- | --- | --- |
| Damage | 0.1; 0.1–50 | Subsequent attacks. Existing projectile/event birth damage and current firing wait are retained. |
| Regular enemy HP | 5 percentage points; 5–400% | The click/load explicitly applies to living enemies proportionally and to future spawns. No heal-to-full, teleport, room restart, death/reward or RNG event is generated. Boss HP is retained. |

HP is an immutable runtime override of the existing audited `regular_health_multiplier`, not a second multiplier stacked on top. Its default is 1. Content source base/stage values remain unchanged. Live actors, stored room residents and persistent charmed followers keep their current/max HP ratio, including champion/regrowth scaling. Black Globin's HP emission checkpoint and adaptive armor's normalized historical pressure scale with HP; pending attacks/status damage retain their selected values. State/phase/timers and source-unit counters stay intact. Future morphs, offspring, healing and HP-dependent rules consume the shared content snapshot.

Schema **9**, contract `d07-combat-v9`, exports/loads/remembers `player_damage` and `regular_health_multiplier`. Schemas 1–8 migrate with D07 references and retain all their prior fields. The asset fingerprint still identifies authored content; the versioned balance revision separately identifies runtime overrides. Invalid/incompatible presets are rejected before any partial settings publication. Pending map edits remain staged until **Apply map changes**. Reset, export/load, remembered next expedition, floor regeneration/descent and retry retain the declared behavior. Configuration is distinct from expedition saves. Legacy debug damage controls feed the same canonical preset; new expeditions use the selected next-expedition preset.

## Verification

- Nine actual Simulation primary-projectile body cases reproduce the table. Three-hit Gaper is independently exercised through mouse firing in the **actual Game and generated seed-69 canyon room**, with AI held solely for deterministic counting.
- All 155 audited regulars preserve source base/stage values and scale once at four source-stage inputs. Nonmember/boss HP remains unchanged. Checks cover wounded living/resident HP, champion scaling, Black Globin HP checkpoints, 128 seeded paired Gaper morph cases with both successor witnesses, and offspring HP.
- Damage edits preserve emitted projectiles and current firing wait; new attacks consume edited Damage and owned modifiers once. Shooting speed, reach and cadence remain independent. Actual Gaper/Spider contact, half-heart depletion, hurt-immunity timing and universal dodge pass.
- The main Game/Renderer check covers mouse/keyboard controls, reset, exported pending map values, valid/invalid loads, proportional injury preservation, map regeneration, floor descent, retry and a fresh Game. [Input evidence](input-tests.log), [panel](combat-panel.png) and [developer preset fixture](custom-combat.json).
- **14 focused CTest suites pass**: damage/HP gameplay, presets, existing regular-health/lifecycle and private calibration tests, typed health, canonical shooting, accepted walking, D04–D06 movement/shots, adaptive armor, Black Globin and Leper. [Regression log](regression.log).
- [Validation record](validation.json) includes final UI regressions and separate executable preset-reload cases. The fixture export is Damage 7 / regular HP 75% with pending room size 120%; it does not replace the user's accepted export.

## Remaining and next

**Human D07 verdict: accepted** ("nice its good, commit and hurtrpy up for a next item"). See [acceptance record](human-acceptance.json). Full native damage flags, item/cache ordering, accuracy/collision, source geometry and per-actor AI/status/lifecycle acceptance are still open. Other authored HP adaptations and boss combat balance are explicitly retained, not hidden behind a parity claim. No complete first-floor fidelity is claimed.

**Next selected delivery: D08 — one complete recorded source combat room inside the expedition.** D08 is selected; its actual enemy/template dependencies still require verification. D07 is committed as `56743a72`; no push is part of this delivery. The automatic bulk-parity goal remains paused.

D08 follow-up: the current enabled formation changes seed-69 room 3 to two Gapers. Disable **SOURCE COMBAT ROOM** and apply map changes to reproduce this historical D07 roster. See [D08](../d08-source-room/README.md).
