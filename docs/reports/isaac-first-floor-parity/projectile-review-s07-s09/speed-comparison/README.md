# Projectile speed comparison: 10 / 11 / 12

The user likes the revised feel and requested three nearby speeds. **Comparison ready; checks pass; final selection pending.** Normal expedition projectiles are unchanged.

```sh
./build/deathward_projectile_review
```

- **1 = 10 units/s**
- **2 = 11 units/s**
- **3 = 12 units/s** (initial choice)

Each selection resets the same room, spawn and camera. All three keep the 24×24 room, 11-unit range ceiling, .88-second lifetime, enlarged bullet visuals, 48-HP/two-hit targets, unchanged cadence and a natural maximum of three active ordinary shots. Slower shots travel less far because lifetime is fixed. Damage, collision radius, walking, dodge and eight-direction controls are unchanged.

**T** cycles target distances; **F8** resets; **F11** follows a shot. Existing arrows/RMB firing, WASD/click walking and camera controls remain. This isolated review uses a temporary campaign. You can start a particular speed with `--speed 10`, `--speed 11` or `--speed 12`. The old projectile baseline is available only through `--baseline`; keys 1/2/3 now select the requested speeds.

[Current measurements and checks](speed-comparison/validation.json) include all three speeds at 30/60/144 input partitions. Each reaches exactly three active shots and never exceeds three, preserves damage/radius/lifetime/cadence, and obeys the range ceiling. The full earlier projectile verifier also passes with this binary, including independent native flight rows, eight-direction Game shots, inheritance, range/cover, two-hit targets and dodge. Historical room-calibration and first-preview evidence remains in the earlier report subdirectories; the first fast preview was rejected.

[Current inspection image](speed-comparison/comparison.png) verifies initial UI rendering. The preserved executable/private mechanics snapshot are outside Git; validation.json records their location. Visual assets still use this checkout.

Still unfinished: your final speed choice, matched live Isaac calibration and normal-expedition integration; native actor/flags/items/RNG/hit geometry, later combat stages and previous health/enemy acceptance gaps. These speeds remain review choices, not claimed native parity.
