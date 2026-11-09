# Gaper trajectory comparison and private pursuit corrections

The ordinary Gaper and supplied Frowning states now match the bounded original-code reference in **ten cases and1,620 half-step transitions** at the game's fixed60Hz step. Two demonstrated pursuit differences are corrected in the private source-room review. **Player speed, HP, contact separation, production defaults and source forces are unchanged. Full enemy acceptance remains open.**

## Reference and timing alignment

`capture-gaper-trajectories.py` reads the pinned installed Repentance1.7.9b executable and executes original instructions, with original square-root code and no patched instructions or stubbed helper calls. The preserved XML confirms ordinary/Frowning base friction1. Executed blocks cover source force writes, ordinary direct-target selection, steering, base physics, alternate interpolation and Manager restoration. The native NPC wrapper/base/AI call windows are pinned as static call-order context; the complete wrapper is not executed by this fixture.

The first main physics/AI phase defines time0. Native interpolation then temporarily displays half of `friction * outgoingVelocity * timeScale`. The Manager restores the saved main position before the next main physics step. The recorded samples alternate interpolation/main at nominal1/60 intervals. Comparing on that timeline establishes that the existing continuous port's open-route acceleration, turning, reversal and blocked damping already match; no guessed extra delay or speed reduction was added.

Cases cover long/short pursuit, near arrival, a valid exact-position waypoint with incoming momentum,90-degree turns, reversal, a gradually moving target, an absent route, a closed-then-awake force schedule and an already-awake Frowning turn. There are1,630 source samples, including ten initial main states; actual Simulation comparison covers the1,620 subsequent transitions.

**Supplied boundaries:** clear-line results or an absent route, target coordinates, healthy state/timeScale1/base friction1 and Frowning activation schedule. The original direct-target branch executes its750-coordinate threshold and selects the supplied current target. Full grid-line queries/FindGridPath, natural animation initialization, statuses and collisions are not executed or certified. Frowning force scheduling is supplied, not a complete native awakening verdict.

## Differences reproduced and fixed

| Supplied reference case | Retained legacy maximum position error | Corrected fixed60Hz result |
| --- | ---: | --- |
| Valid waypoint exactly at current position | .0929441 world units | Passes strict.002 position/.005 interval-velocity bounds |
| Gradually moving target on a clear route | .345703 world units | Passes the same strict bounds |

The port reused a cached waypoint until the target moved more than.5 world units. The native direct-target branch instead uses the current supplied target each update within its ordinary clear-route range. The private correction refreshes that direct destination each NPC update, retaining physical navigation around cover and unreachable points.

The legacy port also treated any zero-distance waypoint as an absent route and applied.85 retention. Original instructions distinguish the zero-vector **absent waypoint sentinel** from a valid target point whose delta happens to be zero. Valid arrival uses.5. The corrected private branch checks route presence rather than collapsing both states into distance0.

`Simulation::nativeGaperPursuit` defaults false and is enabled only for the corrected source-room review. Shared ground-controller callers keep their old default path. Source force/retention fields, health profiles, movement scale and player pace are not changed by these corrections. Existing status behavior and contact separation remain documented adaptations, not newly certified native behavior.

## Fixture isolation, regressions and numeric limits

The first diagnostic mixed a collision-free native motion reference with DeathWard player-contact separation, producing large invalid comparison errors near the target. The final motion fixture marks its sole actor friendly **without Charm** only to bypass player-contact displacement; its ordinary pursuit target remains the supplied player point. Every compared step asserts that target. This is a test isolation rule, not enabled gameplay. Interactive Gapers remain hostile and retain normal contact rules. `initial-contact-confound.log` is preserved separately.

At the actual60Hz game step all ten cases pass the original strict position/interval-velocity bounds. A120Hz physics-partition stress check initially failed those bounds in the near-arrival case: maximum position difference.00550 world units, about.11 native pixel, and interval-velocity difference.12985. Float accumulation/rescaling around the exact1-coordinate arrival boundary is sensitive to partitioning. That exploratory check is explicitly bounded to **one quarter of a native pixel** (and the equivalent quarter-pixel per30Hz interval velocity), separately from the strict60Hz fidelity gate. Runtime arrival thresholds/forces were not biased to make it pass. **The stress result is not exact native equivalence or acceptance of a120Hz native simulation.** The real Game still advances at its fixed60Hz step across render rates.

Thirteen focused tests are covered and pass after the explicit stress-scope distinction, including legacy Gaper, Black Globin, headless and status regressions; player attributes/shooting; geometric-room and native references; HP preservation. Initial and targeted CTest logs preserve the failed strict stress check and the final scoped result. Actual Game native movement, click arrival and stopping pass at30/60/144 render FPS. The earlier144FPS one-tick input-partition difference remains recorded; no equal-wall-clock assertion is substituted for invocation counts.

## Run and next steps

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-gaper-trajectories.py --check
ctest --test-dir build -R '^gaper_trajectories' --output-on-failure
build/deathward_damage_health_review --source-room-review --body 2
```

The corrected review mode2 enables the two pursuit fixes. Mode1 retains the previous enemy conversion/behavior. F8 restarts and Enter restarts after death. Normal eight-direction firing and universal dodge remain.

**Next:** verify native Frowning activation/initialization and obstacle routing, then Spider bursts/Pooter wandering and enemy projectile timing. Still unfinished: full native navigation and contact/collision, live NPC phase timing, status/champion/Flaming variants and lifecycle, exact finer-partition arrival equivalence, human review and production rollout. HP encounter acceptance remains held. This checkpoint verifies supplied-route motion, not complete enemy or first-floor parity.

Subsequent checkpoint: [Frowning activation and physical navigation](../frowning-activation/README.md) now executes the native Head initialization/gates/helpers under supplied cadence and adds six physical routing regressions. Full NPC animation order and native obstructed routing remain open; the earlier supplied Frowning trajectory schedule is not retroactively certified.

Later checkpoint: [ordinary NPC branch order and native grid-search reference](../gaper-scheduler-routing/README.md) identifies the ordinary AI-before-late-base path and compares64 native waypoint decisions to a C++ reference. The complete wrapper/live timing, masks/direct-line behavior and gameplay integration remain open.

Subsequent integration: [native mask/line checks and private cover review](../gaper-grid-lines/README.md) verifies55 classification/288 line cases and enables bounded private Gaper grid routing. Native room-mask generation, cache/status/collision and full actor acceptance remain open.
