# S04 selected walking pace integration

The user selected option 2 (4.8 world units/s), then requested continuation. Normal expedition walking now defaults to that pace, 20% below the earlier 6. The same default applies to fresh tutorial expeditions. A/B review fixtures still explicitly select 6 or 4.8; preserved review executables are unchanged.

Universal dodge keeps its existing absolute speed (20.4 world units/s), duration and immunity. Stopping remains immediate. Existing mouse/keyboard controls, eight-direction firing, projectile stats and enemy HP remain unchanged. Existing slow effects retain 3.2 units/s. No inertia was introduced.

Checks are recorded in validation.json after completion. The Game-input verifier includes a separate default-player case, in addition to explicitly configured A/B movement, click-to-walk, dodge immunity and firing cases.

Launch the actual game directly into an expedition:

```sh
./build/deathward --expedition
```

This uses the normal campaign. For an isolated test, add `--save /tmp/deathward-s04-playtest.save`.

Still unfinished: exact live Isaac speed/stopping calibration, complete first-floor combat acceptance, subsequent individually selected projectile/cadence/damage/HP/hitbox stages, and the existing health/enemy acceptance gaps. The accepted movement pace is an adaptation choice, not proof of native parity. No other S difference was implemented in this step.
