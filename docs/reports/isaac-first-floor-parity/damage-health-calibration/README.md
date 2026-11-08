**Live HP acceptance is on hold: [enemy movement blocker](../enemy-movement-blocker/README.md). Body-count checks remain scoped evidence.**

# S01 / S03 + E01–E09: joint damage and HP review

**Candidate implemented in a private mechanics snapshot; focused checks and actual Game hit counts pass. Human encounter review pending. Normal expedition damage/HP are unchanged.**

The preserved Repentance 1.7.9b XML was re-read and hash-checked. [Source records](source-health.csv) and [reference scope/hash](source-reference.json) distinguish base HP, stage HP and the source Damage baseline. The ten source rows include nine selected bodies plus one necessary morph-HP dependency; no original XML is redistributed here.

## One consistent convention

The review candidate uses native HP directly (conversion **1**) for E01–E09 and **3.5 ordinary damage** read from the canonical source Damage baseline. No per-enemy adaptation factor is used for those bodies. Source base/stage values are preserved; only their conversion and matching registry fallback change in a private pack. The audited `regular_health_multiplier` remains **1**, and its file is copied byte-for-byte. Production mechanics are verified byte-for-byte unchanged.

Current comparison mode retains existing **24 damage** and the selected bodies' **×3.2 HP conversion**. Thus current damage corresponds to 7.5 source HP per ordinary hit against these nine bodies, rather than 3.5. The nominal rate is unchanged in both modes. Derived sustained damage is 24×30/11 in current world units, or (24/3.2)×30/11 in comparable source HP units, versus 3.5×30/11 in the candidate. This is arithmetic, not proof of real-combat DPS or the full native damage pipeline.

Only baseline ordinary body health is reviewed. Bosses, unselected regular bodies, upgrades/status effects, native damage flags and full AI/encounter acceptance are not silently included. Player health, bullet travel/range/rate/size, accepted walking, eight-direction controls and universal dodge are preserved.

## Body counts verified with real primary projectiles

| Enemy | Current body hits | Source candidate body hits |
| --- | ---: | ---: |
| Frowning Gaper | 2 | 3 |
| Gaper | 2 | 3 |
| Gusher | 2 | 3 |
| Horf | 2 | 3 |
| Fly | 1 | 1 |
| Pooter | 2 | 3 |
| Attack Fly | 1 | 2 |
| Spider | 1 | 2 |
| Hopper | 2 | 3 |

The actual Game verifier uses ordinary input and the shared production Simulation, primary builder and damage pipeline, not HP bars assigned to 1000 or a ceiling calculation alone. The lab holds AI in an explicit stunned state. Actual hits are distinguished from shots fired: some shots are still in flight when the body ends. First-body timing includes travel; compare the recorded units and observation conditions before interpreting it as DPS. Measurements are adjacent.

Gaper body death/morph is a separate milestone from clearing its successor. Both tested source Gapers produce a surviving form in the fixed Game witness. Pacer (11.1.0) HP is included solely as an E01/E02 morph dependency, alongside selected Gusher. The candidate also converts the selected Gapers' strict overkill boundary from 80 DW HP to 25 source HP. Morph probabilities, weighted choices, delays and AI are unchanged. Equivalent normalized-damage tests preserve morph eligibility/identity across seeded cases; both Gusher/Pacer paths have witnesses. No AI acceptance is inferred from these HP checks.

## Interactive comparison

```sh
./build/deathward_damage_health_review
```

- **2 Source** is selected initially; **1 Current** restores the current damage/HP convention in the same room.
- **T** switches between a body check and a five-enemy live encounter (Frowning Gaper, Gaper, Horf, Pooter, Spider).
- **[ / ]** selects any of the nine lab bodies. **F8** resets. After death, the room stays open and **F8 or Enter** restarts the same selected test.
- Normal arrows/RMB firing, WASD/click movement and Space dodge remain. No god mode is enabled. The body check deliberately pauses AI, including successor forms; live encounter mode runs existing AI.

First try the source body check. Then press **T**, fight the small encounter and compare **1** versus **2**. Judge kill times and pressure. Source HP and numerical hit counts are our verification responsibility, not a manual guessing task. Gapers may leave another form, whose HP is counted separately.

Camera preparation happens before enemies spawn, so it cannot damage the player offscreen. Held inputs are cleared during reset to prevent shots from being fired during that preparation. The fixture uses a unique temporary campaign; no ordinary campaign is opened. Base Source mode reads canonical Damage when creating the review fixture; the production Damage consumer/upgrade recalculation is not enabled by this prototype.

## Completed checks and remaining work

The focused `damage_health_calibration` suite passes: independent XML-derived rows; source base/stage preservation across stage inputs; only ten HP profiles converted; unselected actor/boss HP unchanged; multiplier and production files unchanged; real spawns, 18 damage-pipeline body cases, champion HP scaling, Gaper strict overkill, seeded morph identity and Pacer HP dependency. The actual Game verifier independently passes all 18 primary-projectile body cases. Body and encounter rendering were inspected; images do not establish human acceptance. Production runtime code/assets were not modified, so the prior accepted movement/shooting verification remains a historical baseline rather than a newly claimed broad regression pass.

**Still unfinished:** human encounter verdict; production rollout and consistent units for the rest of the regular roster and bosses; live source DPS/timing/accuracy comparison and full native damage/item/status/AI/lifecycle/hit-geometry acceptance. Earlier health/enemy gaps remain. A global switch to 3.5 damage while leaving the remaining roster at older HP conversions would be incorrect; this limited review pack must not be enabled as a full expedition balance preset without that follow-up policy and coverage. No broader AI, spawning, boss or drop changes are selected here.

The [death/retry revision](death-retry/validation.json) keeps the review visible after death instead of taking the normal summary transition. A clear restart prompt is shown; fresh retries preserve balance/scenario/body choice and restore full health. This changes only the review tool. Human balance acceptance and broader rollout remain pending.
