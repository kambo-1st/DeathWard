# Ordinary tear initial placement — Repentance1.7.9b

This checkpoint corrects the baseline producer's fixed forward projectile origin.
The native empty-build weapon requests a single tear at the owner's center. The
existing0.7-world-unit barrel offset remains a legacy/presentation choice; it is
no longer added to baseline projectile origins. Universal dodge retains its
movement boost and immunity. HP/damage values and the regular-health control
are unchanged.

## Native evidence

The installed executable is SHA256
`04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.
`analyze-shot-placement.py` executes the complete ordinary WeaponTears::Fire
method959500 and its normal placement/count/effect/query helpers, with the
explicit actor-birth boundary described below. Its192 supplied cases cover two
positions,four cardinal directions,three prior player velocities,four negative
counter values and zero/nonzero tear offsets. Another1,080 calls cover four
270-state moving/turning sequences,with52 ordinary births.

The whole native empty-inventory multishot query74a910 returns one shot and one
lane. The original constructor stores clear the player's tear-offset vector.
The whole shot-layout helper74aef0 and wrapper943a80 calculate the single-shot
layout; the weapon reads the owner's position at95a261. Ordinary requests have
zero forward barrel displacement. The original player tear-offset addition and
post-birth correction are separate operations and remain represented.

Trigonometry executes the pinned local x86 UCRT numeric instructions through
loader-style import resolution in emulated memory. Provider SHA256 is
`e4f8f92eef00ff6a0c6d418af756a59d5a4b818d0d1de0d96cc193b4d6759432`.
There is no host math substitution or instruction patch. The provider manifest
records import contracts,exports and call counts. Live loader selection and
OS/error paths remain unaccepted. No CRT allocation/copy imports execute in
these supplied cases.

## Explicit boundary and limits

Player::FireTear757690 is the actor-birth boundary. Its initial tear-offset block
75770e..757747 executes original instructions. The fixture then returns a supplied
ordinary body with unchanged velocity and the resulting position. The complete
actor creation/Update is outside this boundary; default friction1 movement rewind
was separately captured in v20. The surrounding helper9453d0 resumes and executes
its original post-birth position correction. The weapon method returns normally.
The supplied body does not establish native actor flags,size,RNG,bookkeeping,
initialization or collision. Cached shot speed1 and delay10 are supplied ordinary
inputs; the complete player cache/init path is not executed.

Inventories,trinkets,effects and modifiers are empty native containers. Item
metadata is supplied for empty-inventory queries. The original query functions
execute; this does not establish item/character/unlock eligibility or behavior.
No original game process,save data or original files are modified.

## Runtime comparisons

`native_shot_placement` checks all192 native requests/velocities/corrections and
1,080 actual gameplay states,including52 born projectile origins and velocities.
Native-coordinate arithmetic uses.00003 position tolerance; world positions
use.0003 and converted velocities.0001. Damage scale remains1 in the captures.
The focused placement/birth/fire/baseline set passes in2.74seconds. The v21
application build,all20 selected suites in73.45seconds and the desktop source-input
check pass. Exact scope,source/artifact/application hashes are in validation.json.

The existing70 custom Scatter pellet comparisons now use owner-center origins.
Their velocities/offsets remain supplied from the v20 fixture. Original player
motion is replayed,and the original post-birth position block calculates their
new positions. This does not accept DeathWard's custom Scatter item/spread as a
native collectible. The older v20 seven-unit supplied-muzzle capture is retained
as historical arithmetic evidence rather than rewritten to suggest it verified
native initial placement.

Still unfinished: complete player/tear initialization and cache,full Tear::Update,
native flags,size,character/item/child branches,grid and damage collision ordering,
complete manager birth traversal,room/floor transition behavior,persistence and
matched live observations. All six broad parity areas remain open.

Reproduce with pefile,capstone,Unicorn2.1.4 and the pinned local x86 UCRT:

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-shot-placement.py --check
ctest --test-dir build -R '^(native_shot_placement|native_tear_birth|native_player_fire|isaac_baseline)$' --output-on-failure
build/deathward_input_tests --source-fire-only
```

## Field audit and incomplete actor probe

The historical v20 label `scale_setter` for6500d0 was incorrect: it writes
collision damage2e0 and the duplicate tear damage field3a4. The base setter
5b6ba0 writes2e0;the original player cache initializes13b8 to3.5 at722b18. Tear
visual scale370/374 is separate. The v21 supplied body now carries ordinary
collision damage3.5;all CSV numeric captures are byte-identical after this input
audit. Gameplay damage values were not changed. V20's documentation includes
a dated correction,its original README hash and unchanged numeric captures.

The [whole-actor diagnostic](diagnostics/README.md) remains incomplete. With
corrected supplied size/damage fields,it reaches the original `RegularTear6`
size/animation initialization and stops at an unresolved formatting/resource
boundary. It is not counted as a passing whole-actor test. The next step is
native initialized size/cache/collider verification and full update/collision
execution. Native XML radius alone does not prove the effective collider.
