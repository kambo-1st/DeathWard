# Source room and geometric movement review

The selected follow-up is implemented in a private interactive review. The normal room now has **13×7 floor tiles** and the native player curve and six selected NPC motion profiles use one conversion derived from tile spacing. Normal expedition defaults, HP, attack values and production mechanics remain unchanged.

## Spatial contract

The verified source room has40-coordinate cells and interior bounds(60,140)..(580,420). One source tile maps to the existing DeathWard `FloorTile=2`, so the conversion is **2/40=.05**. Source top-left maps to world(0,0); source centre(320,280) maps to world(13,7). The interior is26×14 world units. This positive-origin placement aligns all91 cells with the real floor lattice and avoids a half-cell shift for an odd tile count.

`tools/source_room_reference.hpp` supplies the shared room, transform and floor-cell set. It does not derive scale from accepted walking speed. `makePack` accepts this explicit scale for the two Gapers, Gusher/Pacer dependencies, Pooter and Spider. The earlier accepted-pace conversion remains available only through historical review modes; production files are not modified.

The ordinary native player adapter advances at the independently verified60Hz movement clock. Its steady geometric pace is13.2426 in world coordinates, compared with13.2137 after converting the longest measured native pass: agreement within0.3%. These internal units are not displayed as a tuning metric. Ordinary/Frowning Gaper steady chase ratios are approximately.376/.544 of that player baseline, matching the source arithmetic/clock relationship. Full per-actor trajectories, initialization, target selection, prediction and integration order are not accepted by these steady-speed checks.

## Validation and control fix

- All **91** native interior grid centres map to navigable floor cells and roundtrip through the coordinate transform.
- **1,380** original-code player trace states across seven sequences match the actual Simulation in the geometric conversion.
- Actual Game keyboard motion/coasting matches the native reference at30/60/144 render FPS. As in the prior fixture, the144FPS held interval delivered89 rather than90 fixed ticks; expected values use actual invocation counts. Long traces use an explicit open-plane fixture, separate from the bounded interactive room.
- Real Game mouse clicking reaches the actual requested ground point within.022 world units and clears the route. An initial test projected its marker at player height rather than ground; the final test projects to ground and records the real requested route point. A separate headless click reproduced actual residual drift after arrival. The native review adapter now resets residual velocity only when a click route completes. This is a DeathWard mouse-control adaptation; keyboard release retains the verified native curve, and ordinary default movement is unchanged.
- Seven focused suites are covered. The initial run passed six; the new suite's final dodge assertion had omitted its movement direction after its mouse test cleared input. Giving that fixture its explicit direction fixes the assertion; the targeted suite passes. `initial-focused-tests.log` and `source-targeted-tests.log` preserve both results. No dodge speed was changed.
- The existing actual Game damage/HP review still passes all18 body cases plus death/retry checks. HP/source stage data and the regular-health control remain unchanged. This regression is not a live HP acceptance verdict.
- Rendered and inspected the actual bounded room (`review.png`). The visible grid represents13×7 logical floor tiles. Scene art and camera projection remain DeathWard's.

## Run and controls

```sh
build/deathward_damage_health_review --source-room-review --body 2
```

The initial mode is the geometric native player curve with a Gaper. **1/2** compares previous/corrected enemy conversion in the same room. **3** toggles native/responsive player curves (responsive retains the earlier adapted player pace). **T** switches single enemy/encounter, **[ / ]** selects an enemy, **F8** restarts and **Enter** restarts after death. Normal eight-direction firing and universal dodge remain. `launch.json` records the copied executable and live session; it depends on development assets in this checkout and is not a portable release.

Still unfinished: human review of the new room/movement, native per-enemy target/pause/trajectory and integration verification, player/enemy hit sizes and wall clearance, enemy projectile timing/acquisition and wider roster. Player firing speed/reach still use the earlier accepted adaptations. Full native collision/stopping/other-room-shape acceptance and production rollout remain open. HP encounter acceptance stays held until the movement and enemy-pressure gates are sound. This is not a complete1:1 combat or expedition acceptance claim.

## Gaper pursuit follow-up

[Ten native supplied-route trajectory cases](../gaper-trajectories/README.md) now verify fixed60Hz acceleration, turning, reversal and arrival in the corrected review. Its Gapers refresh clear-route targets and distinguish valid zero-distance arrival from an absent route. Full native initialization/navigation/contact remains open; default expeditions and HP remain unchanged.
