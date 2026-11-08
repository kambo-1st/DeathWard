# Projectile speed comparison: 3 / 5 / 8 added

The user reported that 10/11/12 still felt too fast and requested lower speeds. **Updated demo ready; checks pass; final speed choice pending.** Normal expedition projectiles are unchanged.

```sh
./build/deathward_projectile_review
```

- **1 = 3 units/s**
- **2 = 5 units/s** (initial choice)
- **3 = 8 units/s**
- **4 / 5 / 6 = previous 10 / 11 / 12 units/s**, retained for comparison.

Each selection resets the same room, spawn and camera. All speeds keep the 24×24 room, 11-unit range ceiling, .88-second lifetime, enlarged art, 48-HP/two-hit targets, unchanged cadence and natural maximum of three active ordinary shots. Lifetime is fixed, so lower speeds also shorten natural reach: approximately 2.6 / 4.3 / 6.9 units at 3 / 5 / 8. Moving shots can inherit additional velocity; their total travel still obeys the 11-unit cap.

**T** now cycles nearer targets at none / **2 / 4 / 6 / 9 units**, allowing low-speed shots to reach test bodies. **F8** resets; **F11** follows a shot. Existing arrows/RMB firing, WASD/click walking and camera controls remain. The isolated review uses a temporary campaign. CLI `--speed` accepts any of the six speeds.

[Current evidence](low-speed-comparison/validation.json) records all six speeds at 30/60/144 input partitions. Each reaches a peak of three active projectiles while preserving damage, radius, lifetime and cadence. The full existing projectile verifier also passes. Earlier comparison evidence remains in the report subdirectories; older key mappings describe their historical binaries. Current preserved binary location/hash is in validation.json; mechanics are snapshotted, visual assets still use this checkout.

Still unfinished: your final speed choice, matched live Isaac calibration and normal-expedition integration; full native actor/flags/items/RNG/hit geometry, later combat stages and earlier health/enemy acceptance gaps. These remain review values rather than verified native parity.
