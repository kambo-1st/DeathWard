# Ordinary tear birth correction — Repentance1.7.9b

The installed executable is pinned by SHA256
`04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.
This checkpoint follows the v19 counter work. It does not accept the complete
tear actor, native spawn placement, collisions, items or live timing.

## Executed evidence

`analyze-tear-birth.py` executes original x86/SSE blocks without instruction or
helper patches. It records960 supplied post-spawn position cases,49 counter and
per-emission offset cases,168 bounded birth/main/interpolation states, and70
moving Scatter pellet births using supplied DeathWard muzzle/spread inputs.

The ordinary firing gate stores `-1-counter`. The emission body subtracts
`MaxFireDelay+1` from that offset for each following emission in the burst.
The post-spawn block94557f..94561b adds tear velocity times this offset to its
position. When its owner/parent guard permits, it subtracts owner movement times
the same offset: twice the previous player velocity for a player, or current
velocity for another owner. The960 cases cover absent/mismatched/null parents,
player and other owners, two origins, four tear velocities, three prior player
velocities and eight offsets. Only the player producer is enabled in gameplay.

The original birth caller757b10 dispatches through the original tear vtable to
Update642990, returning to757b53. The fixture stops on that Update entry; it does
**not** execute the whole Update. The caller then subtracts the updated velocity
from position before the post-spawn correction. Its scale setter at6500d0 is a
separate operation and is not projectile age.

The original ordinary-flight gate64d43b..64d52e is executed with real bitset
helpers and zero flags and reaches64d5eb. The bounded sequence composes original
base physics, ordinary flight, caller movement rewind and post-spawn correction.
Odd phases execute the **complete** original zero-flag interpolation function
653380 in a supplied empty room with grid collision class0. Main phases restore
its saved logical position and run the bounded base/flight blocks. All24 supplied
sequences have seven states. Friction1 is read from the pinned XML tear2.0 entry.
Initial falling speed.1 and velocity/position are supplied fixture inputs.

Nine supplied manager append cases execute the original last-entity snapshot
and loop-termination blocks. Appending0/1/3 actors to initial lists of1/2/4
actors does not extend the existing-entity pass beyond its original last actor.
These gates support the ordinary next-phase model; they do not execute complete
manager traversal, deletion/transition branches or the native spawn pipeline.

The moving Scatter fixture executes original player physics/motion, inheritance,
weapon counter/offset and birth-position blocks. Muzzle distance7 native units
and the five pellet angles are DeathWard inputs. Matching these70 positions does
not accept the native muzzle algorithm or the custom item as a source item.
The [frame20 witness](moving-scatter-witness.json) has an offset of approximately
-.2 and a center-pellet correction of-.134893 world units. The world comparison
checks its native expected position6.399852 within.0003 world units.

## Enabled implementation and verification

`PlayerFire.hpp` retains each emission's source offset and its elapsed phase time.
The baseline primary producer corrects each pellet origin using its own velocity
and the player's previous native velocity. It passes the elapsed time through
the queued shot event. Projectile creation performs the primary tear's immediate
flight initialization and retains its phase clock, so the intervening player
phase does not advance logical height. Source-child and item-specific birth
paths remain separate work. Legacy projectiles, HP/damage defaults, the regular
health multiplier, and universal dodge's movement boost and immunity are unchanged.

`native_tear_birth` compares960 position cases,49 emission-offset cases,168 bounded
states and70 gameplay pellet births against the independent original-code output.
The focused birth/fire/motion/baseline set passes. The v20 application build,
all19 selected projectile/status/boss/item/core regression suites in82.15seconds,
and the desktop source-input check pass. The desktop check retains queued
odd-phase/sub-tick taps and verifies the dodge key; the baseline suite verifies
dodge boost and immunity. Source/artifact/application hashes and exact scope are
recorded in validation.json. Historical v19 results are separate evidence.

## Still unfinished

Complete Tear::Update/initialization and initial spawn/muzzle placement; native
grid/collision ordering, damage/size flags and item/child/character branches;
manager scheduling of newly inserted tears; phase behavior across room/floor
transitions, persistence and matched live observations. The supplied bounded
sequence is not a substitute for full manager/actor acceptance. Existing graphical
height interpolation remains a DeathWard adaptation. Large simulation steps still
combine emission positions rather than interleave complete actors at native birth
times. All six broad parity areas remain open.

Reproduce with pefile,capstone and Unicorn2.1.4:

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-tear-birth.py --check
ctest --test-dir build -R '^(native_tear_birth|native_player_fire|native_player_motion|isaac_baseline)$' --output-on-failure
build/deathward_input_tests --source-fire-only
```

## Field-label correction — 2026-11-08

The historical `scale_setter` label for6500d0 was incorrect. It is the tear
collision-damage setter: it writes2e0 and3a4; the base setter5b6ba0 writes2e0.
Player damage cache13b8 initializes to3.5 at722b18. Tear visual scale370/374
is a separate field. The numerical position/flight captures never used2e0,so
this label correction does not change their results or gameplay attack values.
The original ASM filename is retained as a historical identifier. Whole actor
initialization remains unaccepted. See the v21 shot-placement report.
