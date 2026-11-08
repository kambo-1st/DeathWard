# Ordinary tear effective collider — Repentance1.7.9b

The baseline ordinary tear now resolves radius0.7 world units instead of0.14.
This follows native initialized radius7 at scale1 and the existing.1 coordinate
conversion. HP/damage,regular-health multiplier and universal dodge's movement
boost/immunity remain unchanged. Legacy projectile radius stays0.14. Custom
item radius overrides remain authored and are not accepted as native size rules.

## Executed native evidence

`analyze-tear-collider.py` pins executable SHA256
`04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.
It executes the complete native entity-config constructor66cba0,which initializes
unit collision-radius multipliers. XML attribute binding preserves radius at
config38 and multipliers at3c/40. The installed tear2.0 XML supplies radius7,
mass8,friction1,shadow size8 and eight grid points. Original base-size initialization
681f87..681fdd invokes the complete native setter6843a0 and copies friction.
Original initialization stores set grid class4 and entity collision class4.

The complete native size method651770 executes with a preselected graphics cache
and empty animation layers. Its selected key is derived by executing its original
size prefix. The default key is `RegularTear6`;it is not a guessed sprite index.
The method invokes the native size setter with configured radius times tear scale,
retains the size multipliers and generates the collision points. Captures include
36 supplied scale/axis cases and288 generated point values. Non-unit multipliers
are supplied through configuration before initialization so point geometry and
stored multipliers stay consistent. Only the ordinary unit-scale default is
newly enabled in gameplay;these extra cases do not accept native item rules.

Whole living Tear::Update642990 and whole interpolation653380 execute in a supplied
empty standard room with real native grid points,class4 and empty callback registries.
There are972 complete living updates,1,980 sequence states in36 cases and36 native
floor-death intents. A native birth update and its original movement rewind precede
each sequence. The supplied cases vary scale,initial falling speed and velocity.
At the terminal650dd0 entry the fixture records the native death intent and stops;
world death effects and the rest of that terminal update are outside the capture.

Native UCRT numerical instructions handle trigonometry. Only CRT memory operations
are provided by the existing fixture;no AI/physics calculation is hosted or patched.
Native empty callback queries execute normally. Whole resource loading and actor
creation are not executed;the initialized configuration,graphic cache and empty-room
state are explicit fixture inputs. There are no NPC targets or nonempty terrain.
Manager restoration of interpolated positions is supplied from its previously
verified contract,rather than a complete Game/Room update traversal.

## Runtime checks

`native_tear_collider` compares1,980 logical flight/interpolation states and36
floor-death phases against the independent native outputs. Living position
tolerance is.0001 native units,height.00002 and falling speed.00001. Native death
visual/effect origins are not ported or compared. The actual baseline projectile's
radius matches the captured default after world conversion. Supplied grazing
fixtures confirm an offset.75 target is hit,an offset1.2 target is missed,and the
legacy narrow shot preserves its miss. These target fixtures verify use of the
radius;they do not prove native target damage/collision ordering.

The initial four collider/placement/birth/baseline suites pass in2.84seconds.
The v22 application build,all21 selected suites in78.51seconds and the desktop
source-input check pass. A12-frame canyon empty-room render smoke completed and
its [preview](current-radius.png) was viewed. This is rendering inspection,not
performance or live source-timing acceptance. Exact hashes/scope are in validation.json. The current renderer uses the physical radius for its mesh,so
ordinary baseline tears also appear larger;graphical scaling remains an adaptation.

Still unfinished:complete native actor/resource/player initialization,appearance,
nonempty grids and target collision/damage ordering,size/flags/character/item/child
rules,RNG stream mapping,manager/transition/persistence integration and matched
live gameplay. Global room/player/target spatial calibration remains open. All
six broad parity areas remain open.

Reproduce with pefile,capstone,Unicorn2.1.4 and the pinned local x86 UCRT:

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-tear-collider.py --check
ctest --test-dir build -R '^(native_tear_collider|native_shot_placement|native_tear_birth|isaac_baseline)$' --output-on-failure
```
