# Ordinary tear terrain collision — Repentance 1.7.9b

The baseline tear now traces its center against terrain. Its radius of 0.7 world
units still applies to enemy hits. Previously the enemy-hit radius also expanded
terrain, so a shot beside an obstacle could disappear despite a clear center path.
Legacy projectiles retain their previous radius when tracing terrain. Universal
dodge, its speed boost and immunity, HP and damage remain unchanged.

## Executed evidence

The pinned executable SHA256 is
`04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.
`analyze-tear-terrain.py` executes the complete native entity grid-collision method
at `0x682280`. It uses the previous collider fixture's initialized ordinary tear,
actual configuration/size methods, eight native grid points and grid class 4.
The fixture supplies a 15 by 9 grid and one body in cell (8,2), covering native
x [340,380), y [180,220). Grid construction and body initialization are outside
this capture; their supplied metadata is consumed by original room lookup code.

There are 1,440 captures: three tear scales, six supplied collision classes, two
supplied grid body types, twenty center positions and two interpolation inputs.
The main collision call reports contact for supplied classes 2–5 when the tear's
center enters that cell, except for supplied body type 7. Classes 0–1 do not
report contact. Tear radius does not expand the cell boundary: radii 3.5, 7 and
21 give identical decisions. Tested positions stay unchanged. Interpolation
input 1 leaves the initially clear contact flag clear for these class-4 fixtures.
This is a result for the supplied ordinary state, not a blanket rule for all
tear flags, grid types or interpolation states.

The source manager dispatch at `0x4157ab` calls the same method with input 0
for non-player, non-laser actors in its collision list. That dispatch is preserved
as inspected instructions, not executed as a complete scheduler. Original UCRT
numeric methods and the prior fixture's CRT memory boundaries are retained; no
collision function is replaced by a host result or patched instruction.

## Enabled gameplay and limits

The runtime change separates terrain trace width from enemy-hit width for shots
using `PlayerTearFlight`. Actual player shots are tested against an obstacle and
a stationary target beyond it. Forty-two comparisons use the native matrix's
lateral positions and three supplied radii: centered paths stop, clear center
paths reach the target. Three legacy controls check grazing, centered contact
and outside-radius clearance. These world checks intentionally exclude exact
half-open grid boundaries; continuous box geometry has its own boundary policy.

**This is a terrain-width correction, not full source collision acceptance.**
DeathWard still traces continuous 3D geometry and resolves the earliest swept
contact. It does not yet reproduce native grid sampling phases, room grid
construction, interpolation/manager ordering, entity-pair ordering, target damage
callbacks, terminal tear effects, spectral/piercing/item rules or all grid classes.
Its world fixture tests behavior beside/through an obstacle; it does not establish
matched native hit timestamps or production source-room layouts. Those differences
remain required work. Global spatial calibration and live gameplay remain open.

The v23 application and full default build pass. All 22 selected regression suites
pass in 84.12 seconds; the five focused suites passed in 5.01 seconds. The desktop
source-input check also passes, including retained universal dodge. Native
regeneration with `--check` passes all 1,440 cases. Exact source, application and
evidence hashes are in `validation.json`. No new rendering/performance acceptance
is claimed for this terrain-width change.

All six broad parity areas remain unfinished. The next collision work is native
entity-pair detection/dispatch and its ordering relative to terrain contact.

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-tear-terrain.py --check
ctest --test-dir build -R '^(native_tear_terrain|native_tear_collider|native_shot_placement|native_tear_birth|isaac_baseline)$' --output-on-failure
```
