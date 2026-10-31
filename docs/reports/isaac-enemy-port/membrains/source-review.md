# MemBrain family and Cyst — dedicated implementation in progress

Baseline: installed Repentance 1.7.9b. Native dispatch, exact executable hash,
seven disassembly windows and constants are preserved in
[source/manifest.json](source/manifest.json). Highest available DLC animation
metadata is preserved in [animations/manifest.json](animations/manifest.json).
Reproduce with `python3 scripts/isaac-reference/analyze-membrains.py --check`.
The archive checksum and previously pinned archive SHA-256 are checked; no Isaac
sprite artwork is imported into DeathWard.

The [source dossier](source-discovery.json) preserves installed XML, room-template
counts and revision-pinned wiki material: [MemBrain revision 267035](https://bindingofisaacrebirth.wiki.gg/index.php?oldid=267035)
and [Guts revision 266739, including Cyst](https://bindingofisaacrebirth.wiki.gg/index.php?oldid=266739).
Wiki attribution: The Binding of Isaac: Rebirth Wiki contributors, CC BY-SA 4.0.
Broad behavior/habitat comes from those articles; precise timings and conditions
below come from installed code and animation metadata.

## Ordinary source contracts

| Record | Source HP/contact | Death offspring | Ordinary habitat mapped to DeathWard |
|---|---|---|---|
| 57.0.0 MemBrain | 62 / 2 | Two 32.0.0 Brains | Bands 2–3: Depths/Dank Depths and Womb-family |
| 57.1.0 Mama Guts | 62 / 2 | Two 40.0.0 Guts | Bands 2–3: Necropolis and Womb-family |
| 57.2.0 Dead Meat | 62 / 2 | Two 862.0.0 Cysts | Band 3: Corpse |
| 862.0.0 Cyst | 25 / 1 | None | Band 3: Corpse; also required Dead Meat offspring |

All four have stageHP zero. They are grounded ordinary enemies, not bosses or
room hazards. Source body radii are 13; MemBrain mass is 30, Cyst mass 10.

### MemBrain movement, timing and vulnerability

Type 57 dispatches through case 699a34 into 50a450..50adae. Initialization sets
state 4 and consumes one source update. Every subsequent update multiplies
friction by .8. Ready state invokes MoveRandomly(false), helper 7a6180..7a64a9.
With no destination it samples one uniformly angled point 40 source units away,
accepting only an empty grid cell. It then clears the target if within 3 units,
grid collision occurred, or a 1/10 draw succeeds while velocity squared is below
.1. Clearing the target does not sample a replacement in that update. Otherwise
it adds normalized force .5, divided by current friction before the common
friction pass: ordinary planar velocity becomes `.8 * velocity + .5 * direction`.

Each ready update has a 1/30 attack draw, requiring the native population helper
6ad7a0 to return less than 8. Ordinary acquisition does not require player range
or line of sight. Flag mask 1000a00 suppresses acquisition; fear/confusion and
controlled-enemy branches need further work. The attack transition retains
Wiggle that update; subsequent updates play Attack. Wiggle loops over 30 frames;
Attack is 70 frames, with Shoot at 29 (30 FPS). Attack applies friction without
wander force. Its apparent hop is sprite animation: the controller does not
change body collision or give invulnerability. The body remains damageable.

### Actual projectile patterns

At Shoot, normal/Mama use FireProjectiles mode 8, velocity (10,0), Scale 1.4.
There are eight equally fast cardinal/diagonal shots; diagonal components use
.707106769. This is not the inherited-velocity three-shot mode 2.

Dead Meat uses mode 9, input (8,8), spread angle Pi/8, Scale 1.4,
FallingAccelModifier -.07, NO_WALL_COLLIDE low flag 2000 and BOUNCE high flag 400
(bit 42). The eight-shot set is rotated 22.5 degrees and travels at speed 8.
Mode 9 increments angle before emission; the local equivalent direction set
starts at Pi/8 instead, so array ordering/RNG-to-direction assignment is an
explicit remaining difference.

Fresh ProjectileParams height is -23 and random falling speed is in [-.1,.1).
Modes 8/9 retain that default; they do not apply mode 0's -3 falling-speed
and .1 acceleration modifiers. The common vertical update adds .1 acceleration
and applies .9 retention. Local conversion gives height 1.15, initial upward
speed [-.15,.15], gravity 4.5 (normal/Mama) or 1.35 (Dead Meat), retention .9.
Scale 1.4 produces projectile damage 2 in the source and local radius .308.

The dedicated native BOUNCE branch 636a23..636be1 gathers collision normals,
normalizes and reflects velocity if entering the collided surface. At height
below -50 it queries wall-only grid collision; closer to the floor it includes
rocks. NO_WALL_COLLIDE prevents ordinary grid destruction while this branch
handles reflection. There is no finite bounce budget. Ground landing remains
terminal. DeathWard reflects actual lateral terrain normals repeatedly; it
still traces real solid tops and floor surfaces. Native grid-height thresholds
and real 3D geometry are not equivalent, and that adaptation is not hidden.

### Death children

The dead-actor branch checks the dead byte and bc6 == 0, samples a random axis,
and spawns exactly two children at opposite 10-unit offsets with zero initial
velocity: Brain, Guts or Cyst according to variant. No ordinary overkill check
was found here. The meaning and all callers of bc6 remain unverified. Dinga
223 shares this function but has different living and death spawns; this batch
does not claim Dinga implemented.

### Cyst

Type 862 dispatches through case 69a26b to the Guts controller 5031b0..5054da.
Ordinary contour movement retains force 3, friction .6, grid distance 40,
arrival 10 and cross-axis pull .4. Roll loops over 24 frames. Its separate af4
counter starts at zero: when at least 30 it fires and resets; otherwise it
increments. Thus successive normal shots are 31 source updates apart, after
initialization. The shot immediately samples the current target with mode 0,
speed 10 and default parameters, then starts a 10-frame Shoot overlay while
rolling continues. There is no ordinary range, random or line-of-sight gate in
the installed firing branch. The controlled branch has separate acquisition.

Mode 0 converts to speed 30, height 1.15, upward speed 4.5, gravity 9,
retention .9 and radius .22. Ordinary Cyst does not lay damaging creep: the
shared variant-0 trail is a visual blood effect, not a damage hazard.

## DeathWard implementation and adaptations

`assets/mechanics/membrains.mechanics` holds four exact identities, HP conversion,
movement/timing/shot profiles, offspring references and encounter entries.
`MemBrains.cpp` implements parent wander/attack and Cyst emission; `Guts.cpp`
keeps Cyst's contour movement and timer. Source decisions use 30 Hz with movement
integrated between decisions. Attack frames pause at Shoot if the whole eight
shot packet cannot fit; Cyst retains a single shot while continuing to roll.
Snapshots retain emission-time origin/direction. This backpressure is an engine
safety adaptation, not source behavior.

HP conversion is 3.2: 198.4 for each parent and 80 for Cyst. Source damage 1/2
becomes local 10/20 before the shared 1.25 enemy multiplier (12.5/25 actual).
Player defaults remain 100 HP and 24 damage. Ordinary execution/overkill retain
offspring; developer clear explicitly suppresses them. Required births remain
pending at enemy capacity and keep completion blocked until both are resolved.
Shared spawn clearance may relocate children away from solid terrain or the
player; generation safety remains capped at four in the common spawn queue.

Continuous canyon clearance replaces source grid collision. MemBrain radial
candidates must also have a clear approach, rather than selecting a destination
behind a thin prop. Shared DeathWard stun pauses decisions/motion and retains
attack progress. Native status, champion and controlled branches are not yet
faithful. Room threat counting includes retained births for safe completion;
the native helper's exact exclusions are not yet reproduced.

Original-style authored folded lobes distinguish the three parent bodies;
Cyst uses the rolling Guts body with a green palette and shooting mouth.
The hop is visual only. This is not a source artwork or complete audiovisual
port. Encounter weights/costs/caps are authored: parents weight 1/cap 1,
Cyst weight 2/cap 2. Source template counts are habitat evidence, not rarity.
Mama Guts replacement probability and eligibility are not certified by these
ordinary pool entries.

## Still open

Full status/control/champion/attraction behavior; native grid/RNG and precise
animation update ordering; bc6 death suppression and all alternate production
paths; Mama Guts replacement rules; persistence; source gore/sound/visual parity;
broad mixed-room readability, default-kit balance and controlled Linux/WASM
performance. These records remain in progress; no full acceptance is claimed.
