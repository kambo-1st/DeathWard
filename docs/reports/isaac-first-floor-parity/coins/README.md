# Source coin pickups: world lifecycle adapter, full acceptance open

Target: installed Repentance 1.7.9b, ordinary Isaac/Normal/empty inventory. Baseline v10 adds all seven coin subtype identities to the source placement API, including lucky, sticky and golden behavior. **General source coin drops and room-clear rewards remain disabled.** V11 now connects golden-heart/Midas effect drops and appearance gates through the [producer integration](../coin-producers/README.md). Existing custom money piles and generic enemy coin drops still differ. Universal dodge retains its movement boost and immunity.

## Independent native evidence

`scripts/isaac-reference/analyze-coins.py` reads the pinned executable and records the following original-code outputs. [manifest.json](manifest.json) pins executable/instruction-window hashes and the exact scope.

- [Seven coin values](native-values.csv): whole native getter; penny 1, nickel 5, dime 10, double penny 2, lucky penny 1, sticky nickel 5 and golden penny 1.
- [35 ordinary wallet mutations](native-wallet.csv): whole native `AddCoins`, including actual empty-inventory cap queries and one-player bookkeeping. Supplied counts cover 0/1/94/98/99; deltas cover negative, zero and ordinary coin values. Source ordinary cap 99 and clipping are distinct from the legacy partial pile adapter.
- [Six lucky counter cases](native-lucky-counter.csv): original counter addition at player+0x1480 and Luck-cache dirty flag 0x400, stopped before the complete cache rebuild. C++ compares the counter change; its immediate Luck refresh is scoped to the empty source build, not a complete item/cache port.
- [40 sticky damage cases](native-sticky-damage.csv): execute the actual pickup damage function until return or before its animation call. Positive damage with flags intersecting 0x1000004 converts subtype 6 to subtype 2 and clears its touch counter. Other subtypes, zero damage and unrelated flags do not convert.
- [335 golden predicate cases](native-golden-decision.csv): actual native RNG, unsigned-word-to-float conversion and comparison execute with a **supplied threshold** after the imported power function. C++ matches the exact float roll, predicate and RNG endpoint. This group stops after a supplied threshold; the complete-power group below additionally executes the linked original power routine. Placement, seed initialization and spawning remain outside both groups.

- [1,201 native power thresholds](native-golden-power.csv) and [4,804 complete decisions](native-golden-complete-decision.csv): execute the original game wrapper and local x86 UCRT power export for every counter 0–1200, with four RNG seeds including the minimum positive roll. C++ matches every threshold exactly and all complete power/RNG/predicate outputs. At counter 1200 the threshold is below the minimum positive native RNG value; an ordinary chain starting at 0 and incrementing by 1 cannot pass that bound. This covers its reachable numeric counter domain, not the complete world actor.

The golden probability to float `.98` raised to the float collection counter through imported double `pow`, then narrowed to float. The initial counter is 0, so the first admitted collection always continues. A continuation spawns a new golden penny and writes the old counter plus 1. The original numeric DLL is pinned in `native_math` metadata. `native_math.py` resolves the executable's three math import pointers in the isolated fixture, maps the local x86 UCRT image and uses explicit masked/default rounding controls. No DLL binary is copied into the repository and no host math is substituted in the native captures. Native OS/error paths, other control modes and live loader selection are not established by these finite-input calls. World lifecycle acceptance remains open.

`extract-coin-animations.py` preserves metadata from the highest installed DLC override, with archive hashes and checksums in [animations/manifest.json](animations/manifest.json). Golden `Reappear` has 24 animation frames and its DropSound trigger at 16; sticky `Touched` has 12 frames and DropSound at 1. These are animation metadata, not measured simulation seconds or proof of collision activation timing. No sprite artwork is imported.

## Enabled behavior

`spawnSourceCoinPickup` accepts subtypes 1–7 and preserves their identity, owning room and explicit drop RNG state. Ordinary values clip to the remaining 99-coin wallet space and consume the whole admitted source pickup. Unlike the older money-pile adapter, a dime is not split into a residual pile. A lucky penny adds one native coin-Luck contribution even when the wallet is full. That counter remains separate from cached Luck; the current ordinary build applies its one-point Luck increase immediately. Source item recalculation remains unfinished.

A sticky nickel remains uncollectible on touch. The actual DeathWard explosion event path invokes its qualifying-damage conversion, changing it to an ordinary nickel which can then be collected once. The world blast radius/line-of-sight recipient selection is still an adapter, not a native physics acceptance result.

A golden penny pays one coin per admitted collection. Its counter-dependent continuation uses the native comparison/RNG calculation and the source power expression through the host math library. A selected continuation retains its next seed until a legal position in the same room is available; failed placement never repeats the payout or rerolls survival. Once placed, the counter increments. The world adapter uses DeathWard room geometry, reward RNG and free-point sampling, and currently maps the selected child seed directly to its next drop RNG state. The host power expression matches all 1,201 recorded original-UCRT thresholds in the reachable ordinary domain. **Native room-position RNG, seed initialization and appearance timing are not accepted.** V11 now uses the measured Reappear collision gate and frame/event values through the existing source-clock adapter. Full native sprite rendering, scheduler and world-clock acceptance remain open.

All source coin actors render through procedural shapes. Pickups in another room cannot be collected. The owning simulation retains them across room changes; a new floor constructs a new pickup set. Player coin-Luck is part of the carried player state. Legacy fixtures retain their prior currency behavior. V11 additionally enables the existing golden-heart/Midas effect producers through these actors. General drop/room-clear generation and full first-floor acceptance remain open.

## Checks and reproduction

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-coins.py --check
python3 scripts/isaac-reference/extract-coin-animations.py --check
cmake --build build --target deathward_source_coin_tests deathward -j4
ctest --test-dir build -R '^source_coins$' --output-on-failure
build/deathward --smoke --scene coins --frames 180 --screenshot /tmp/deathward-coins.png --mute
```

The new suite compares all captured outputs within their stated scope and tests actual world collection, cap clipping, capped lucky collection, touch refusal, blast conversion, golden continuation/termination, blocked-placement recovery without repeat payout, room isolation and legacy separation. Existing baseline tests retain universal dodge activation/boost/immunity. The inspection explicitly places all seven coin subtypes, grants a lucky penny, collects the first golden penny and blasts the sticky nickel at frame 60. Inspection god mode is not a difficulty/performance acceptance result.

Unfinished: native pickup eligibility, creation/appearance/delays, physics and complete collision; live loader/control-mode/RNG/seed/placement acceptance; all coin-triggered collectible/trinket/character/co-op effects and Luck recalculation; source natural drop/room reward generation, other reward families, eligible pools and all six original parity areas.
