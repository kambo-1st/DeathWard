# Ordinary blue fly: enabled actor with scoped native evidence

Target: Repentance 1.7.9b, ordinary Isaac, familiar **3.43.0** (named `Attack Fly` in the preserved XML; distinct from enemy fly identities). The executable is read only and hash checked. [manifest.json](manifest.json) records the native windows, XML hash and exact capture limits. **Full familiar acceptance remains open.**

The [C++ kernels](../../../../src/combat/BlueFly.hpp) match independent executed native outputs:

| Evidence | Cases | What is established |
| --- | ---: | --- |
| [Steering/physics](native-motion.csv) | 318 states / 6 sequences | Supplied goals, acceleration limited to two native units, ordinary damping and native free-motion endpoints at timeScale1/base friction1. |
| [Orbit angle](native-orbit-angle.csv) | 36 | Native phase/frame/parity arithmetic before imported fmod/cos/sin. Imported trigonometry and complete orbit membership behavior are not executed. |
| [Target score](native-target-score.csv) | 64 | Supplied fly/owner distances and HP, ordinary nondirectional scoring flags. This does not execute world enumeration or complete target eligibility. |
| [Initial damage](native-damage.csv) | 5 | Base damage assigned as twice player damage during native initialization. Item/cache-refresh modifiers remain open. |
| [Special contacts](native-instakill.csv) | 22 | Native branch to direct NPC `Kill` for specific fly-type identities, with the explicit type14 variant2 exception. The fixture stops before the Kill callback. The preserved Lua binding confirms virtual slot0x24 is `Kill`, and the NPC method immediately sets the native dead flag. |
| [Rotten refill](../rotten-heart-flies/native-refill.csv) | 104 | Add only the positive `2 * rotten - alreadyOwned` deficit; retain owned excess. |

The numeric motion helpers and sqrt execute original instructions without substitutions. The ordinary physics fixture is not a whole familiar update. Source XML gives collision radius13 and friction1; native initialization sends variant43 through grid collision class0. Those attributes alone do not prove AI. The preserved update body separately shows the target polling, orbit/chase steering and contact branches.

Enabled integration in the baseline expedition (introduced and verified at `isaac-baseline-v5`; the later hurt-counter checkpoint is v6):

- A successful room-clear transition supplies the rotten-heart deficit. Calling refill repeatedly cannot duplicate existing stock, and losing rotten health does not delete owned flies. Other source refill/charge callback triggers remain unverified.
- Normal flies join an evenly spaced group-one ellipse (native radii35/30), steer using the source recurrence, poll through the native modulo3/global-frame-plus-seed gate, then pursue a selected target. The current world conversion and 30 Hz source clock remain dependencies of broader spatial/live-timing acceptance.
- Ordinary contact uses initialized damage; the starting 3.5 player damage gives seven fly damage. The native special target set uses direct execution rather than guessed excessive damage or altered enemy base HP. A fly is consumed by one admitted contact. Contact events resolve before a later fly observes the same killed target. Selected hits survive bounded queue pressure.
- Logical collision uses the plane and the converted native radius; graphics float above it. There is no grid collision. Exact native collider geometry/eligibility and global collision ordering remain open.
- Owned flies carry between rooms and floors; destinations clear old targets and reposition the surviving inventory. Floor transfer retains initialized damage. These are DeathWard integration checks, not a measured native transition/cache-refresh acceptance claim.

The source heart-pickup/drop generator is still absent. This actor runs when rotten health exists through the collection/placement APIs; the inspection scene supplies that health explicitly. Do not infer that native rotten-heart drop selection or the complete item pools are now reachable in ordinary generation.

`isaac_baseline` checks refill stock/excess, orbit grouping, ordinary contact, synthetic high-HP Pooter direct Kill, two-fly contact ordering, queue-pressure recovery, an actual room-clear producer, prevention of duplicate clear refill, floor carry-over and legacy isolation. All **12 selected kernel/baseline/status suites pass**, including retained universal dodge boost/immunity. [hud.png](hud.png) is an eight-frame render/launch check with two blue flies, two gold actors and the mixed health HUD. Inspection god mode is enabled only in that scene; this is not combat/performance or live-native acceptance.

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-blue-fly.py --check
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-rotten-heart-flies.py --check
cmake --build build --target deathward_blue_fly_tests deathward_isaac_baseline_tests deathward -j4
ctest --test-dir build -R '^(native_blue_fly|isaac_baseline)$' --output-on-failure
./build/deathward --smoke --scene health --frames 8 --screenshot /tmp/deathward-blue-fly.png
```

Still required: complete native target flags/query and special lifecycle interactions, full birth/update/collision ordering, imported orbit math and membership modifiers, delay states and other subtypes, item/trinket effects and damage cache refresh, all refill callback triggers, native global RNG/live clock and spatial calibration, native room/floor persistence comparison, and full actor acceptance. The original six-area objective remains open in the [progress report](../../../isaac_first_floor_implementation.md).
