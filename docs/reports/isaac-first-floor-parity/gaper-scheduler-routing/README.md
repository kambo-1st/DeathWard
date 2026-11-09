# Gaper ordinary animation order and native grid-search reference

This checkpoint resolves the previously ambiguous **ordinary NPC branch order**, executes72 native activation/base-animation evaluations, and ports a bounded native grid search into a C++ reference. The reference matches **64 original native waypoint decisions across six layouts**. **No new gameplay behavior is enabled. Full native NPC acceptance remains open.**

## Ordinary update order: the earlier branch was special

The previous activation report correctly left its explicit Sprite.Update cadence supplied. Looking only at the earlier base call in the NPC wrapper was insufficient to determine ordinary scheduling:

- At69b5a0, an ordinary actor with no immobilization/special flag takes the jump at69b5d0 to69b756. That path bypasses the early base call at69b6cd/69b6e4. The fixture executes this bypass with ordinary supplied fields.
- Ready state4 then bypasses death-state processing to69cda8; that short branch also executes.
- The ordinary AI call is at69ce94, conditional on the actor's common skip field. The earlier69b7c0 AI call belongs to initialization handling, not every ordinary update.
- The later wrapper code calls the base entity at69f8a9 for type10. The base-animation interval6860e7..68618c advances enabled animations unless suppressed, multiplying playback speed by entity timeScale and then restoring playback speed.

Thus the scoped ordinary path runs **AI before the later base-animation update**. The early temporary NO_SPRITE_UPDATE flag does not demonstrate that ordinary actors lack animation advancement. Native instruction listings retain both branches, ordinary AI and late base call. Branch evidence plus execution of the actual base-animation block narrows the gap; the complete wrapper and all intervening callbacks/status/physics logic are still not executed by this fixture.

The new fixture executes Head initialization, AI force/wake gates, then the real base-animation block. At supplied ordinary timeScale1 it selects.6 and starts Head at frame0, then the base block advances Head to1. The next AI evaluation selects.72. The nonlooping animation finishes at integer frame19. At supplied timeScale.5 the repeated clear-path experiment still restarts frame0; with NO_SPRITE_UPDATE it stays at0. These are controlled entity-time inputs, **not acceptance of the native Slow item/status scheduler**. The entity's time counter advances and the original playback speed is restored in every evaluation.

The current port advances its head counter before steering and keeps it at0 during the first activation tick. Its ordinary force progression matches the controlled.6→.72 sequence, but presentation/activation fields need comparison at a common end-of-update phase. No speculative animation or timing adjustment is enabled. NPC real-time cadence remains unmeasured; the player60Hz/world30Hz capture does not itself verify every NPC phase.

## Native obstructed search: original helpers execute

`capture-gaper-scheduler-routing.py` executes original instructions at7a4383..7a451e, including native queue push/pop, then the native gradient selection and steering at7a4570..7a47f5. It supplies a15×9 room with13×7 interior, cost0 floors and cost1000 barriers, start/goal indices and a preallocated scratch vector. Allocation, cleanup, RNG/cache setup and mask generation are excluded; no source instructions or helper functions are patched/stubbed. The source executable and the reused activation fixture's real UCRT image remain hash-pinned.

Each decision starts a fresh search. The grid-only approach stops when it reaches a cell adjacent to the target: the omitted direct-target branch normally handles final arrival. Open and reopened layouts are controlled grid-search baselines; the full native function could choose direct pursuit there. These are not continuous collision/physics traces or native cache-refresh measurements.

| Layout | Result |
| --- | --- |
| Open | Grid approach advances toward the target. |
| Central cover | Search finds the upper route; native gradient tie order is retained. |
| Sealed barrier | Search returns no route; original steering applies.85 friction retention. |
| Upper opening | Grid approach goes through the upper opening. |
| Lower opening | Grid approach goes through the lower opening. |
| Reopened baseline | Fresh search matches the unobstructed grid approach. |

All traversed waypoints are adjacent passable cells and approaches are cycle-free. The CSV preserves exact selected indices. Native outgoing friction during moving pursuit is.7; outgoing velocity is stored before that friction is consumed, so it must not be mistaken for realized displacement speed.

## C++ reference and current gameplay distinction

`src/combat/reference/NativeGridPath.hpp` implements the bounded flood/gradient calculation with native neighbor/tie behavior, traversal limits and blocked-cell threshold. The existing Gaper trajectory test now compares its found flag and exact waypoint index against **all64 original native decisions**. This is useful reference code for the subsequent private integration; it has no gameplay callers. Positive weighted masks, larger footprints, special room shapes and full pathfinder branches are outside current acceptance.

DeathWard gameplay currently uses physical A* navigation and route smoothing around cover. Native search returns an adjacent grid waypoint; DeathWard may instead choose a longer clear segment. The previous six physical navigation scenarios establish safe routing in those layouts, not matching waypoint behavior. Replacing that routing requires an explicit mask/direct-line adapter and collision verification; the reference port alone does not implement that integration.

The existing ten supplied-route trajectories/1,620 half-step comparisons and six physical navigation scenarios still pass. All four focused CTest suites pass; the120Hz partition check retains its separately bounded numerical-stress scope. Player pace, HP, attack damage, universal dodge and eight-direction firing are unchanged.

## Reproduce and next steps

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-gaper-scheduler-routing.py --check
cmake --build build --target deathward_gaper_trajectory_tests -j4
ctest --test-dir build -R '^(gaper_family|gaper_trajectories|gaper_trajectories_substeps|source_room_review)$' --output-on-failure
```

Next: execute native direct-line/mask behavior for these room layouts, map that contract into the private source-room review, and compare routing plus end-of-update activation fields at matched phases. Then validate Spider bursts, Pooter wandering and enemy projectile timing. Full wrapper reachability, live NPC cadence, collision/contact, statuses/champions/lifecycle, human acceptance and production rollout remain unfinished. **HP encounter acceptance stays on hold.** The complete first-floor comparison remains open.

Subsequent integration: [native mask/line checks and private cover review](../gaper-grid-lines/README.md) verifies55 classification/288 line cases and enables bounded private Gaper grid routing. Native room-mask generation, cache/status/collision and full actor acceptance remain open.

Subsequent checkpoint: [private Frowning activation phase](../frowning-phase-review/README.md) fixes the post-base Head-state delay and matches288 controlled native phase states. Full native status/wrapper/live timing and user acceptance remain open; next actor work is Spider/Pooter.
