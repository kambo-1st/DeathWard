# Source key and bomb resources: enabled adapter, full acceptance open

Target: installed Repentance 1.7.9b, ordinary Isaac/Normal/empty inventory. Universal dodge, including movement boost and immunity, remains the requested exception. This checkpoint adds separate golden resource flags and supported world resource pickups; **production source room-clear rewards are still disabled**.

## Independent native evidence

`scripts/isaac-reference/analyze-resources.py` executes the pinned executable's admitted key and bomb collision branches. [manifest.json](manifest.json) records executable and instruction-window hashes. [native-collection.csv](native-collection.csv) contains 48 cases: six supported subtype branches, counts 0/1/98/99 and initial golden flags off/on. The actual native resource APIs and their one-player bookkeeping execute unchanged. The fixture supplies memory allocation/copy operations, not replacement resource arithmetic.

The supported identities are key variant 30: ordinary 1, golden 2, double/key-ring 3; bomb variant 40: ordinary 1, double 2, golden 4. Golden collection sets a byte flag without increasing the ordinary counter. Ordinary and double collection clamp the counter at 99. The admitted branch reports collection even when the counter or golden flag is already full. This capture excludes earlier collision prechecks, callbacks, price/eligibility checks and post-collection effects; it does not prove every world collision is eligible.

[native-floor-flags.csv](native-floor-flags.csv) records eight bounded executions of `0x76ae77–0x76ae92`: supplied argument 0 clears both golden bytes and argument 1 preserves them. Ordinary counts remain unchanged. The argument's complete caller semantics are not established by the slice. DeathWard applies the clear on new-floor travel and preserves flags on room travel; complete native transition acceptance remains open.

[native-coin-values.csv](native-coin-values.csv) separately records the native getter for seven coin subtypes. This is research only, not evidence that their collection effects or lifecycle are implemented.

## Enabled gameplay

The baseline v8 `Simulation` exposes `spawnSourceResource` and `collectSourceResource`. Supported pickups render in the world, remain attached to their room and collect through the existing distance/line-of-sight adapter. Keys and bombs use their existing canonical counters, with separate golden flags. Golden keys unlock ordinary locked doors without spending keys; golden bombs permit placing/throwing with zero ammunition and preserve existing stock. Cooldowns, capacity admission and other normal action guards still apply. HUD resource labels show GOLD while the respective flag is active. Flags survive room travel and clear on a successful new-floor transition; old-floor pickups do not transfer. Legacy fixtures retain their existing behavior.

These are API/world and spending integrations. **Natural generation is not enabled**, and the source contact radius, pickup delays, motion, collision eligibility, sounds and complete special-door/bomb behavior remain unaccepted. Charged key 4 is explicitly refused until source active slots and charging exist: native collection adds one key and attempts six charge units in slots 0–3, which cannot be represented honestly by the current custom active system. Troll bomb 3, super troll 5, golden troll 6 and giga 7 are explicitly refused rather than converted into ordinary ammunition. Coin variants, chests/sacks, cards/pills/trinkets, complete modifiers/unlock profiles and source seed/placement rules remain required. Existing custom coin piles, enemy drops, bomb physics and rewards still differ.

## Reproduction

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-resources.py --check
cmake --build build --target deathward_source_resource_tests deathward_isaac_baseline_tests deathward -j4
ctest --test-dir build -R '^(source_resources|isaac_baseline)$' --output-on-failure
build/deathward --smoke --scene resources --frames 120 --screenshot /tmp/deathward-resources.png --mute
```

`source_resources` compares all 48 native admitted-collection results and tests world collection, unsupported actor identities, golden spending with zero/existing stock, cooldown/capacity rejection, room isolation, floor expiry and legacy isolation. `isaac_baseline` retains the universal dodge activation, movement boost and immunity regressions. `--scene resources` is an inspection fixture with explicit golden flags, six manually placed resource pickups and god mode; it is not a production reward demonstration.
