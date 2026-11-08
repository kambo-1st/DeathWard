# Installed 1.7.9b ordinary player tear arithmetic

`analyze-player-tears.py` uses the same isolated native-code executor as the [movement evidence](../player-motion/README.md). Reproduce with:

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-player-tears.py --check
```

`native-flight.csv` contains 171 states across six fixed raw RNG values. Native unsigned integer conversion, birth falling speed, damped flight and the floor comparison execute from the pinned PE. The supplied RNG result is fixed deliberately; no native RNG stream/seed equivalence is claimed. The native `SetHeight` logical store is retained; its room/render callbacks are omitted and declared in the manifest.

The base cached state is height -23.75, falling-speed stat 0, acceleration 0 and nominal Range 260. Ordinary birth adds native float-converted random jitter up to 0.2. Ordinary flight uses the native time-scale retention helper, adds `0.1 * timeScale` plus the configured falling acceleration, then advances height. Ground contact is checked at height greater than -5 before the next flight update. Displayed Range is not substituted for this executed trajectory or claimed to be exact traveled distance.

The source weapon's base direction is multiplied by 10 native units; movement inheritance and shot-speed scaling are separate. Whole-game update/birth ordering, spatial/time calibration, flags, item interactions, collider sizes and complete collision behavior remain unfinished. The DW random stream is still different.

The enabled ordinary DW path uses logical planar targeting and a separate rendered height, so the vertical placement of a 3D model does not make an otherwise eligible ordinary target unhittable. Native invulnerability exclusions remain in place. Full terrain/obstacle and special-body acceptance is separate from the arithmetic and ordinary planar collision regression.
