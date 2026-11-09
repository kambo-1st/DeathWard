# Native Gaper grid-line verification and private cover review

The C++ reference matches **55 original native collision-classification cases and288 original native direct-line cases**. The bounded private source-room review now consumes the verified grid/line calculations around cover. **This is enabled only for corrected Gaper movement in that private review; production gameplay defaults are unchanged. Full enemy acceptance remains unfinished.**

## Executed native evidence

`capture-gaper-grid-lines.py` executes the complete native ordinary mode0 CheckLine at7af4b0 and collision lookup at7aeec0 from the hash-pinned installed Repentance1.7.9b executable. Original sqrt and cookie checks execute; no helper hooks or instruction patches are used. The caller option window is preserved as static context. The fixture supplies room dimensions, masks and optional synthetic grid-object collision fields; it does not construct native props or execute native mask generation.

The55 collision cases cover eleven mask costs (0,1,900,949,950,999,1000,2999,3000,3999,4000), each with no object or an explicit collision field0/1/3/4. Without an object, costs3000–3999 classify as1, other costs>=1000 as3, and lower costs as0. An object supplies its own collision class. These classifications do not mean all costs below1000 are traversable by the pathfinder: the separately verified flood calculation rejects costs>=950.

The288 line cases cover open ground, finite/sealed cover, upper/lower openings and positive-cost experiments, both line directions, diagonals, zero-length lines and positions close to a native cell edge. Ordinary mode0 tests four(+/-5,+/-5) offsets at10-coordinate intervals. Any collision class blocks; positive-cost probes outside the starting cell accumulate and the line is rejected above eight such probes. The ordinary caller uses threshold0; the900 threshold is an additional supplied experiment corresponding to other source branches. Zero-length CheckLine returns clear without probing geometry.

`NativeGridPath.hpp` now reproduces these ordinary mask/line semantics and passes every recorded result. Synthetic object overrides are covered by classification only; native object construction, special room-config and status branches are not accepted.

## Private gameplay integration

The corrected `--source-room-review` Gapers now use adjacent grid waypoints around cover instead of DeathWard's smoothed A* segments, within the bounded26×14 room/91 floor-cell fixture. The existing private opt-in flag remains false in normal gameplay. Other review arenas and ground-controller families retain their existing navigation.

The adapter rasterizes DeathWard physical obstacles at its13×7 cell centers into cost0/1000 masks. It converts positions using the established native40-to-world2 tile mapping. Native line clearance plus DeathWard physical clearance selects a direct current target; otherwise the verified flood/gradient calculation selects one adjacent waypoint. An absent route keeps the source.85 blocked retention. Every selected segment must still pass the actor's full physical-footprint clearance.

**Explicit adaptations:** the mask comes from DeathWard geometry and footprint tests, not the native prop/mask generator. Native four-probe line clearance is narrower than the current full physical-footprint check; physical safety remains an additional constraint. Search is recomputed each NPC update rather than using native RNG/cache refresh. Blocked targets and unusual footprints are outside the accepted source behavior. This is a playable movement candidate, not full native navigation/collision parity.

Across64 actual Simulation integration cases using the earlier native route evidence,36 take a direct live target,27 select the exact recorded adjacent waypoint and one correctly has no route behind a sealed barrier. Open native grid-reference baselines are allowed to take direct pursuit in the integrated function: the full source also has a direct-target branch, whereas that earlier fixture deliberately forced grid search.

The ten existing collision-free native trajectory cases/1,620 half-step comparisons remain unchanged and pass. Six continuous physical scenarios (both Gaper variants rounding cover, staying behind sealed cover and resuming after cover removal) also pass without entering solid geometry. Friendly-without-Charm isolation still excludes player-contact displacement from these motion fixtures; interactive enemies remain hostile. The120Hz partition test remains a separately bounded numerical stress result, not exact native equivalence.

## Playable cover scene and validation

```sh
build/deathward_damage_health_review --source-room-review --cover-review --body 2
```

The player and selected enemy start on opposite sides of a visible barrier. Use1/2 to compare previous/corrected movement, normal movement/fire/dodge controls, F8 to restart, and Enter after death. `--body1` selects Frowning Gaper. T leaves the cover scene for the ordinary encounter review; F8 otherwise preserves cover mode. The barrier is a plain review primitive. The capture in `cover-review.png` is a rendered smoke check, not user visual acceptance.

Five focused suites pass: Gaper family, strict trajectories, numerical partition stress, source-room review and status effects. All changed binary targets were rebuilt. Actual Game keyboard/native-player checks at30/60/144 render FPS and mouse-route arrival pass. A120-frame cover-scene launch/capture exits successfully. No player-pace, HP, damage, firing-control or dodge values are changed.

Reproduce research/tests:

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-gaper-grid-lines.py --check
cmake --build build --target deathward_gaper_trajectory_tests deathward_damage_health_review -j4
ctest --test-dir build -R '^(gaper_family|gaper_trajectories|gaper_trajectories_substeps|source_room_review|first_floor_status_effects)$' --output-on-failure
```

**Next:** manually review the cover candidate and compare end-of-update Frowning activation fields at matched phases. Native mask generation, route cache/status exceptions, full wrapper/live NPC cadence and collision/contact remain open. Then continue Spider/Pooter movement and enemy projectiles. Production rollout and full first-floor acceptance are unfinished; HP encounter acceptance remains held.

Subsequent checkpoint: [private Frowning activation phase](../frowning-phase-review/README.md) fixes the post-base Head-state delay and matches288 controlled native phase states. Full native status/wrapper/live timing and user acceptance remain open; next actor work is Spider/Pooter.
