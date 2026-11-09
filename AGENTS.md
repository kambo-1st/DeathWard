# DeathWard project terminology

- Call the randomized gameplay portion an **expedition**, or an **expedition into the Badlands**, in player-facing text, documentation and discussions.
- An expedition is the entire run. It contains **floors**, and each floor contains connected **rooms**. Do not use these terms interchangeably.
- Standard expeditions have 4–8 seeded floors, growing from 9 to 15 rooms per floor (Classic comparison preset: 15 throughout). The tutorial expedition, **The Lost Survey**, is the exception: one floor with five rooms.
- **Fort Mercy** is the story hub the player returns to between expeditions.
- Expeditions deliberately follow The Binding of Isaac's room-based roguelike structure. Story rooms are woven into the appropriate floors; they do not replace the multi-floor structure with a short linear story level.
- Existing internal names such as `MissionTheme` may remain. The terminology decision alone does not require renaming code APIs or save fields.

## Enemy fidelity and balance

- Target installed **The Binding of Isaac: Repentance 1.7.9b**. Resolve numeric wiki conflicts against its preserved XML; use measured native behavior for AI conflicts. XML attributes alone do not prove AI behavior.
- Keep source base HP and stage HP separate from DeathWard conversions and adaptation factors. Preserve the current starting balance until a requested playtest adjustment; document deviations rather than changing source values to hide them.
- The audited regular-enemy HP control is `regular_health_multiplier` in `assets/mechanics/regular_enemy_health.mechanics`. Its default is `1`; `.75` means 25% less HP. Use the shared calculation for spawning, champions, offspring and HP-dependent lifecycle rules. The selected H01 starting default is 6 red half-heart units / 24 damage; keep attack damage and bosses separate. H02–H18 are now selected, including incoming damage and healing conversion.
- An expedition floor is mapped to a source stage; do not insert the expedition floor number directly into the source Stage HP formula.
- Registry presence or a wiki description match does not constitute full enemy acceptance. Preserve explicit gaps and scope verification by enemy and behavior.
- Whenever stopping work or ending a work turn, state what remains unfinished. Update the relevant persisted progress report when the remaining work changes; distinguish verified research from enabled gameplay and full acceptance.

## Manual difference selection for Isaac comparisons

- The bulk Isaac parity implementation was reverted at the user's request. The automatic parity goal is paused.
- Consult `docs/isaac_first_floor_implementation.md` for the current state, difference selection register, historical research and recovery archive.
- Implement comparison differences only after the user explicitly selects them (a named range is a valid selection). An archived plan, historical checklist or earlier broad parity objective does not authorize automatic implementation or resuming the bulk effort.
- H01 is implemented. The user has now explicitly selected H02–H18; implement that range and preserve universal dodge, including its speed boost and immunity. S04 walking pace is also explicitly selected: the user preferred option 2 (4.8 world units/s), then requested continuation to integrate it. Preserve immediate stopping, absolute universal dodge speed/immunity and firing controls. Exact native speed parity remains unverified; S07–S09 and the ordinary S02 rate consumer are selected; the accepted independent shooting base is integrated. Full native acceptance is still open. Other differences remain unselected.

## Combat controls retained by user request

- Preserve the current eight-direction firing mechanism and existing mouse/keyboard controls for isometric gameplay. This is an explicit exception to Isaac's firing-direction comparison (S06), alongside universal dodge.
- Do not replace firing with Isaac's four-direction restriction or change aim/input mapping as part of damage, enemy HP, fire-rate, range, movement or hitbox calibration. Those balance changes require their own manual selection and must retain the existing controls.

## Canonical attributes scope

- The user selected steps 1 and 2: the seven-attribute data/adapter model and its Speed movement consumer. Canonical Speed now drives ordinary walking through an explicit accepted-feel calibration; base pace, stopping and dodge are preserved. Runtime health remains in existing player fields; combined source attributes are a transient snapshot. Speed is enabled in ordinary gameplay. The user subsequently selected Tears, Shot Speed and Range wiring: the user accepted the base comparison and authorized continuation. Their independent consumers are now enabled in normal expeditions and the tutorial. Exact native counter/actor/cache/calibration acceptance remains open. The temporary cadence/travel coupling and artificial three-shot expectation are removed; increased stats may produce more simultaneous shots. Preserve the Faster review choice and eight-direction controls. Do not treat this work as authorization for bulk stat, damage/HP, item or save changes.

## Selected damage/HP calibration

- The user selected joint S01/S03 and E01–E09 HP-only calibration. A private review tool uses 3.5 damage and direct source HP, leaving production damage/HP and the regular-health multiplier unchanged. Pacer HP and selected Gaper overkill conversions are explicit necessary morph-unit dependencies. Human encounter acceptance and a consistent remaining-roster/boss unit policy are required before global rollout. No AI, spawning, boss or drop redesign is selected. See `docs/reports/isaac-first-floor-parity/damage-health-calibration/README.md`.

## Current blocking priority

- The user explicitly requires enemy movement to be corrected/verified before resuming live HP balancing. The Gaper/player scale mismatch is reproduced in `docs/reports/isaac-first-floor-parity/enemy-movement-blocker/README.md`. HP body-count research remains valid, but live HP acceptance is on hold. Do not compensate for fast enemies by changing HP, and do not claim a corrected movement candidate is enabled until it has actually been implemented and verified.

- An explicit native-player review adapter now exists; see `docs/reports/isaac-first-floor-parity/native-motion-reference/README.md`. Its bounded native recurrence and actual Simulation traces pass. Normal expeditions still use the accepted responsive movement. The review display still uses an adapted spatial anchor, so do not claim independently verified source room-crossing speed or full NPC/native acceptance. Resolve live timing, geometry and per-actor trajectories before promoting it or reopening HP acceptance.

- Step1 reference verification now includes live normal-room geometry (520×280,13×7 native40-coordinate interior cells) and ordinary horizontal base-Isaac timing (about60 player movement steps/30 world updates per second). See `docs/reports/isaac-first-floor-parity/room-scale-timing/README.md`. Do not keep describing that scoped timing as unmeasured. Shared review scale/geometry has not been applied; collider/stopping/other-shape and NPC acceptance remain open.

- The subsequent private `--source-room-review` now applies geometric scale FloorTile2/native40=.05 and a13×7 interior. See `docs/reports/isaac-first-floor-parity/source-room-review/README.md`. The legacy review modes retain their historical scale. Production defaults and HP remain unchanged; the geometric review still needs human acceptance and full per-enemy/collider/projectile verification.

- The corrected private source-room mode now enables `nativeGaperPursuit`: fresh clear-route targets and valid zero-distance arrival braking. Ten ordinary/Frowning supplied-route cases match the native60Hz trajectory reference; full native navigation, awakening/contact/status/live NPC behavior remain unaccepted. The120Hz substep check is only a quarter-native-pixel numerical stress bound. See `docs/reports/isaac-first-floor-parity/gaper-trajectories/README.md`. Production defaults and HP remain unchanged.

- The subsequent Frowning activation checkpoint executes native Head initialization/gates/helpers in six cases under explicitly supplied animation cadence; six DeathWard physical routing scenarios pass. It does not verify full NPC animation scheduling or native obstacle routing. The supplied half-speed case exposes frame-zero replay sensitivity; do not silently change gameplay or call Slow behavior native-accepted without scheduler evidence. See `docs/reports/isaac-first-floor-parity/frowning-activation/README.md`. Those two gaps precede Spider/Pooter and HP acceptance.

- The next native Gaper checkpoint identifies ordinary AI-before-late-base animation order (the early base call is on a special path) and executes72 controlled base-animation evaluations. A bounded C++ grid-search reference matches64 native waypoint decisions in six supplied-mask layouts; it has no gameplay callers. Native masks/direct-line behavior, private routing integration, phase-aligned activation and live/full-wrapper acceptance remain open. See `docs/reports/isaac-first-floor-parity/gaper-scheduler-routing/README.md`. Do not keep treating ordinary branch order as wholly unknown or reference presence as accepted gameplay.

- The corrected bounded source-room Gaper review now consumes the grid/line reference:55 native classification cases,288 line cases and64 actual Simulation route selections pass. `--source-room-review --cover-review --body 2` exposes the candidate around visible cover. Rasterized DW masks, added physical-footprint safety and fresh search are explicit adaptations; native mask generation/cache/status/full wrapper/live NPC/collision and human acceptance remain open. Production defaults and HP are unchanged. See `docs/reports/isaac-first-floor-parity/gaper-grid-lines/README.md`.

- The private corrected Gaper review now advances Frowning Head state after AI, fixes the reproduced post-base frame delay and tracks nonlooping playback/fractional frame-zero restart. Six native cases/288 actual Simulation states match. Production/default Gaper behavior is unchanged; fractional-time experiments are not acceptance of native Slow scheduling. See `docs/reports/isaac-first-floor-parity/frowning-phase-review/README.md`. Next selected actor work is Spider burst/idle movement, then Pooter/enemy shots; broader Gaper acceptance and HP remain held.

- The private corrected source-room review now sets `nativeBurstWanderReview` for ordinary Spider85.0/Pooter14.0 phase correction; Pooter uses pinned asymmetric edge thresholds only in that geometric room.16 native Spider idle gates and192 Spider/Pooter movement states pass at30/60/120Hz partitions with supplied targets/DW random draws. Native RNG/acquisition/clamp/live scheduling/collision/full actor acceptance remain open. See `docs/reports/isaac-first-floor-parity/spider-pooter-movement/README.md`. Next is enemy projectile timing/speed, then human pressure review; production defaults and HP remain unchanged.
