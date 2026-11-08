# S04 walking-only review candidate

Status: **user selected option 2 as the preferred walking pace**. The user accepted the responsive baseline and requested slower ordinary walking to approach Isaac's feel. Candidate walking is **4.8 world units/s**, 20% below the baseline 6. This is a playtest value, not a verified native conversion. No inertia was added.

```sh
./build/deathward_movement_review --candidate
```

Press **1** for baseline 6, **2** for candidate 4.8. Each switch resets the same room, spawn and camera. **F8** resets the current mode, **F7** records a two-simulation-second travel sample. Existing WASD/click movement, eight-direction arrows/RMB firing, camera controls and Space dodge remain. The fixture uses a unique temporary campaign.

Preserved executable: `/home/kambo/.local/share/deathward/reviews/movement-s04-walking-20261108T150808Z/deathward_movement_review`. It has a private mechanics snapshot; visual assets still come from this checkout. The separate frozen baseline remains available at the path in the [baseline report](../movement-review-baseline/README.md).

Only ordinary walking changes in the candidate. Dodge remains 20.4 units/s with the same duration, distance and immunity; stopping remains immediate. Projectile speed, lifetime, damage, enemy HP and normal expedition walking defaults remain unchanged. The shared Player now has a walking-speed field defaulting to 6; only this review fixture selects 4.8.

Actual Game/input checks pass for keyboard/diagonal walking at 30/60/144 input partitions, click-to-walk, stopping, dodge immunity and all eight firing directions. Separate Mine/Canyon arrow checks and three focused regression suites pass. These partitions establish simulation consistency, not rendering performance. [Measurements](measurements.csv), [inspection image](candidate.png) and validation hashes are adjacent. Baseline two-second walking covers 12 units; candidate covers 9.6. Dodge still covers 4.76 units over 14 boosted fixed ticks in either mode.

Still unfinished: live-reference speed/stopping calibration, any promotion into ordinary expeditions, subsequent combat stages and existing native-health/enemy acceptance gaps. No dependent stage proceeds from automated passes alone.

Human feedback: **2** — preferred the 4.8 units/s candidate. This records pace preference; native speed parity remains unverified.

## Subsequent integration

After selecting option 2, the user requested continuation. The [integration report](integration/README.md) records the new normal walking default of 4.8 and passing checks. Statements above about a default of 6 describe the preserved review checkpoint. Exact native parity and later combat acceptance remain open.
