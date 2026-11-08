# Canonical attributes — step 1 only

**Implemented and checked: data model and conversion boundary. Gameplay wiring is not enabled.** The user authorized step 1 of the feature-by-feature plan. No current movement, shooting, health consumer, item, save format or enemy HP code was changed for this step.

`src/combat/PlayerAttributes.hpp` defines `SourcePlayerAttributes`: typed Health via existing `SourcePlayerHealth`, Speed, Tears per second, Damage, Range in tiles, Shot Speed and Luck. Ordinary documented baseline values are three filled red hearts, Speed 1, Tears 30/11, Damage 3.5, Range 6.5, Shot Speed 1 and Luck 0. These encode the agreed reference contract; they do not certify a complete native cache/init/actor trace.

`AttributeSpace` is an explicit conversion boundary with one shared spatial scale and separately supplied player/tear invocation clocks. There is no default calibration. Tile distances, source coordinate distances and already-resolved native velocities use this boundary. Speed and Shot Speed remain dimensionless source attributes; this adapter does not invent their producer formulas or treat a value of 1 as a world velocity.

The nominal interval helper reads only Tears; it is arithmetic rather than a native scheduling implementation. The nominal straight-flight helper derives duration from configured reach and caller-resolved launch velocity. It cannot rewrite Tears or Range. Native trajectories, flags, terrain and scheduling remain future consumer work. No fixed three-shot limit, half-room cap, HUD indicator band or review cadence coupling is embedded in the model. Zero Tears yields no periodic firing; invalid conversion inputs are rejected without silent balance clamps. General attribute caps and native cache/modifier formulas are not implemented.

## Verification

```sh
cmake --build build --target deathward_player_attributes_tests
ctest --test-dir build -R '^player_attributes_contract$' --output-on-failure
```

The standalone test target passes. It checks typed health snapshots, documented baseline representation, shared tile/coordinate scaling, different explicit actor clocks, negative velocity, absence of a default calibration, invalid inputs and disabled zero-rate firing. It also checks the regression contract: changes to Shot Speed cannot change configured Range or Tears; higher Tears shortens only the nominal interval; increased Range survives beyond a review-room cap; slower/faster launch velocities can traverse the full same distance by changing duration. Calibration numbers in tests are synthetic fixtures, not production settings or live-reference acceptance.

The model is referenced only by its standalone test. No `Player` instance holds a second health/stat authority, and no save migration is needed at this checkpoint. When wiring it, retain one authoritative health state rather than storing unsynchronized legacy and canonical copies. Broad game tests were not rerun: no gameplay target consumes this header and the focused target has no runtime dependency.

Still unfinished: step 2 movement consumer and calibrated spatial/clock settings; step 3 independent Tears/Shot Speed/Range wiring and removal of review cadence coupling; human review before accepted projectile integration; coordinated Damage/enemy HP/DPS work; Luck consumers, source modifier/cache formulas and persistence/HUD integration when selected. Full native calibration, actor/item/flag/hit-geometry and earlier health/enemy acceptance gaps remain. Universal dodge and eight-direction controls are retained. No broader difference selection or bulk goal resumption is implied.
