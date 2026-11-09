# Frowning Gaper activation checkpoint

The pinned Repentance1.7.9b activation gates and animation helpers execute successfully in **six controlled cases /288 evaluations**. Both private geometric-room Gaper variants also pass six physical navigation scenarios. **This checkpoint adds research and regression coverage, with no gameplay changes. Whole native NPC animation scheduling and obstacle routing remain unfinished.**

## Executed source behavior

`capture-frowning-activation.py` executes original x86 instructions from the pinned installed executable: the Head initialization block, force selection, direct-path wake gate, and their real overlay/frame/animation helpers. It maps the local32-bit Windows UCRT and binds the game's `floor` and `nextafterf` import entries to its real exports. No instruction patches or Python math helper stubs are used. Both executable and runtime hashes are checked before execution and recorded in `manifest.json`.

The animation's preserved ANM2 supplies Head's20 nonlooping frames and absence of frame events. The fixture supplies a minimal in-memory animation table with visual layers omitted. It supplies healthy type10 variant0 state, direct-path flags, sprite playback increments and explicit animation-update calls. Runtime DLL initialization is omitted; the fixture supplies masked x87/MXCSR control state. This executes the finite arithmetic used here; it does not establish which UCRT module the live game loads.

Verified within those boundaries:

- Initialization selects Head, sets frame0 and leaves it stopped.
- The default force is.6; the force-selection block reads the integer overlay frame and selects.72 only above frame0.
- A direct-path flag starts **or restarts** Head while its integer frame is0 or less. Force selection precedes this wake gate in the controller.
- After it starts, losing the direct-path flag does not stop Head. It reaches final integer frame19 and stops playing.
- With a supplied animation increment1 between AI gate evaluations, a clear path first starts Head at frame0; the next evaluation sees frame1 and selects.72.

Cases: never clear, immediately clear, clear after three evaluations, one clear pulse, and two exploratory half-speed animation cases. Every row of `native-activation.csv` records the supplied inputs, frame before/after the gate, selected force and playing flag.

## Timing-sensitive gap, not a gameplay fix

**Animation update cadence/order is supplied, not recovered from the whole NPC scheduler.** The fixture deliberately calls one Sprite.Update after each gate evaluation. Its row number is an evaluation count, not measured wall-clock time. The native NPC wrapper temporarily suppresses automatic base-entity sprite updating; reconstructing the actual ordinary NPC animation path remains necessary before declaring live wake-up timing equivalent.

The half-speed experiments expose why that matters: with an explicit.5-frame animation update between repeated clear-path evaluations, Head reaches.5, its integer frame remains0, and the native gate restarts it at0. A single clear pulse instead lets it continue. The current DeathWard controller latches `wakeStarted` once and accumulates a separate fractional counter. **That difference under the supplied experiment is recorded, but does not establish native Slow/status behavior or justify a runtime change without the real scheduler.** Neither the native gate nor a source force is changed to hide this gap. Head may retain a fractional final frame (19.5 in the single-pulse experiment); its public integer frame is19.

## DeathWard physical navigation checks

The actual Simulation uses the private geometric source-room scale, finite13×7 floor and corrected pursuit flag. For both Frowning and ordinary Gaper, the expanded trajectory test checks:

| Scenario | Checked result |
| --- | --- |
| Central finite cover | Actor rounds cover, never enters solid geometry and reaches the target within.032 world units after15 seconds. |
| Sealed barrier | Actor stays on its original side; Frowning remains closed. |
| Barrier removed after two seconds | Direct pursuit refreshes promptly; actor reaches the target within.032 world units and Frowning finishes opening. |

Footprint checks run at each of900 fixed60Hz steps per scenario:5,400 actor steps across six scenarios. As in the collision-free trajectory fixture, the actor is friendly without Charm solely to suppress player-contact displacement while retaining the ordinary player target. This is test isolation, not gameplay. Existing hostile collision/contact regressions still pass.

**These tests certify DeathWard's physical path safety and reachability in these layouts. They do not execute native FindGridPath, compare native waypoint choice, or establish native obstacle avoidance/clearance.** Existing ten supplied-route native trajectory cases remain unchanged and pass.

## Reproduce and next work

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-frowning-activation.py --check
cmake --build build --target deathward_gaper_trajectory_tests -j4
ctest --test-dir build -R '^(gaper_family|gaper_trajectories|gaper_trajectories_substeps|source_room_review)$' --output-on-failure
```

All four focused suites pass. `navigation.log`, `ctest.log`, `build.log` and the validation file retain the results. The120Hz partition check remains the separately bounded numerical stress test documented in the earlier Gaper trajectory report; it is not strict native equivalence.

**Next:** resolve the real native NPC animation update path/order and execute a controlled obstructed native route before promoting Frowning activation or navigation to verified gameplay parity. Then compare Spider bursts and Pooter wandering, followed by enemy projectile timing. Full contact/status/champion/lifecycle behavior, live NPC timing, human acceptance and production rollout remain open. HP encounter acceptance stays on hold; player pace, damage/health, eight-direction firing and universal dodge are preserved.

Later checkpoint: [ordinary NPC branch order and native grid-search reference](../gaper-scheduler-routing/README.md) identifies the ordinary AI-before-late-base path and compares64 native waypoint decisions to a C++ reference. The complete wrapper/live timing, masks/direct-line behavior and gameplay integration remain open.
