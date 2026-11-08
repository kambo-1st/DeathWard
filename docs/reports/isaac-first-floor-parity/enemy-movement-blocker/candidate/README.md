# Private relative movement candidate

Implemented and running in the movement review only. Normal expedition mechanics and HP/damage remain unchanged. Live HP acceptance remains held.

The reference is the installed Repentance 1.7.9b executable, SHA256 `04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`. The original bounded player movement instructions gave steady velocity 4.414238452911377 per player invocation. Existing native dispatch evidence gives ordinary target clocks of 60 player / 30 NPC invocations. The adaptation anchors those rates to the accepted DeathWard base walk of 4.8: `worldScale = 4.8 / (4.414238452911377 * 60)`. This replaces the previous .1 controller conversion for two Gapers, Gusher/Pacer dependencies, Pooter and Spider. Horf remains stationary.

This is a **source-derived adaptation**, not a claim of complete 1:1 Isaac movement. The new scale also affects controller acquisition/arrival/wander distances. DeathWard body sizes, room geometry and player acceleration remain adaptations. Source forces, retention and timers remain unchanged. Enemy projectile speeds/ranges remain unchanged and uncalibrated; close encounter pressure therefore remains unsuitable for HP acceptance.

## Evidence and limits

- Pinned Gaper, Spider and buzz-fly source extraction checks pass (5/4/9 assembly windows).
- Actual Simulation Gaper long-distance steady chase is 1.80506 ordinary / 2.60973 awakened, versus player 4.8: native-derived relative ratios approximately .376/.544. This uses native recurrence evidence and bounded player execution, not a complete live NPC trace.
- Seven focused CTest suites pass. See `regression.log` and `motion-tests.log`.
- 840 paired fixed steps compare old/corrected controllers in corresponding scaled open fixtures, with attacks out of range. These verify consistent trajectory/momentum/burst conversion inside the existing port. They **do not independently prove native Spider/Pooter AI fidelity**. A first fixture put only the corrected Pooter within attack range and changed its cooldown friction; the final locomotion fixture avoids that confound.
- All mechanics directives except six controller scale values remain byte-for-byte identical in the candidate pack; production files are untouched. Tests cover HP/attack fields and stun stopping. No boss/global speed/HP balancing change.
- Captured/rendered the actual Game review (`gaper.png`); interactive launch details are in `launch.json`. The copied executable retains a compiled development asset dependency on this checkout; it is not a portable release.

Run `build/deathward_damage_health_review --movement-review --body 2` from the checkout. Controls: **1 Previous / 2 Corrected**, **[ / ] enemy**, **T one enemy / encounter**, **F8 restart**, **Enter after death**. Normal movement, eight-direction shooting and universal dodge remain. Current production HP/damage are used in both movement modes; the source-HP review is a separate mode.

Still unfinished: independent bounded/full native actor trajectories for Spider/Pooter and the other selected actors, live scheduler verification, projectile conversion, source/world room and collider calibration, wider roster coverage, human movement verdict, production rollout, then resumption of damage/HP acceptance. No complete native movement acceptance is claimed.

## Commit checkpoint and failure explanation

The player pace was accepted as a manual adaptation while existing enemy controllers retained another coordinate conversion. Their relative rates were not audited together before opening the HP encounter. This caused the fast-enemy failure and made the live HP comparison premature. The movement candidate addresses that inconsistency, but its conversion-preservation tests are not evidence of independent native AI fidelity. The user should not need to infer native base speed through subjective tuning. Next work must establish and verify the native base-player trajectory, clocks and spatial reference before claiming a 1:1 enemy movement result; report exactly where any retained DeathWard adaptation differs.
