# Spitty family: installed Repentance 1.7.9b

Scope: ordinary Spitty **31.0.0**, Conjoined Spitty **243.0.0**, and Tainted
Spitty **31.1.0**. These are three regular enemies, not boss components.
The original visual style and existing player defaults are retained.

## Preserved evidence

- [Installed source windows](source/manifest.json): eleven bounded disassembly
  windows, with executable and byte hashes, extracted by
  `scripts/isaac-reference/analyze-spitties.py`. `--check` compares the files
  byte for byte with the pinned installed executable. The executable SHA-256 is
  `04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.
- [Animation metadata](animations/manifest.json): three source ANM2 files,
  archive/checksum verified, selecting the highest available DLC override.
  No source sprite artwork is imported into the runtime.
- [XML and room evidence](stage-evidence.json): exact identities, health,
  contact damage, mass/radius, and stored source room templates. Room-template
  counts establish habitat, not encounter probabilities.
- [Spitty wiki revision 266770](https://bindingofisaacrebirth.wiki.gg/index.php?oldid=266770),
  preserved in [wiki-source.json](wiki-source.json), by The Binding of Isaac:
  Rebirth Wiki contributors, CC BY-SA 4.0. This supports the qualitative
  wandering, facing-based shots, Conjoined opposite shots, Tainted moving
  bursts/forward stream/death rings, and parent summoning relationships.
  Native values below come from the installed baseline, not newer wiki changes.

## Source contracts

Both type31 and type243 dispatch through case `0x699968` to the shared
controller `0x51afa0`; ordinary walking is state4 and attacking state9.
No generic distance-based player acquisition or fixed attack cooldown applies.

| Property | Installed rule | DeathWard conversion |
|---|---|---|
| HP | 10 / 18 / 60, no stage HP | 32 / 57.6 / 192, established x3.2 scale |
| Contact | 1 / 1 / 2 | 10 / 10 / 20 before shared hostile multiplier |
| Walk | axis-aligned random path; force .72; friction .85; extra vertical-axis retention .964705825 | source30Hz momentum, horizontal distance scale .1; physical canyon navigation |
| Attack acquisition | `Random()%35==0` on walking updates | seeded source30Hz check; no player distance or sight gate |
| Attack | 16 frames, Shoot at frame6; direction stored at acquisition | facing snapshot, full packet, recovery at16 |
| Walk animation | horizontal12, vertical24; only Tainted has Shoot at6 | dedicated walking clock and Tainted burst event |
| Ordinary projectile | mode0; horizontal8; HeightModifier14, FallingSpeedModifier-.1, FallingAccelModifier-.102 | speed24, height.45, initial upward4.65, gravity4.41, vertical retention.9 |
| Conjoined projectile | same packet emitted a second time in opposite direction | two simultaneous facing/opposite shots |
| Tainted stream | ten mode0 shots, horizontal18; sizes1.7-.1n; acceleration multiplier1-.03n; jitter `(U-.5)*n` degrees; falling modifier `(10-n)*.005-.08` | speed54; height.65, initial upward4.5; gravity7.65-.225n; radius .22 times scale; per-frame slowing |
| Tainted moving burst | 3 or4 shots via FireBossProjectiles(count,zeroTarget,10,defaults) | uniform directions, speed21; upward7.5..43.5; height1.15; gravity63.9; radius .22 times (.9+.4bit+.05U) |
| Tainted death | two mode9 rings, eight shots each; horizontal8; first CW, second CCW with angle offset pi/8; Scale1.25; falling modifier-.07 | sixteen speed24 shots; fixed death-position orbit center; radius.275, height1.15, upward-.15..+.15, gravity1.35 |

Normal HP corrects the previous48 placeholder. Conjoined is a new runtime
identity. Tainted retains the previously implemented native adaptive armor,
shieldStrength30; this work does not redefine its damage formula.

### Walking and firing

The walking argument is loaded at `0x51b792`, and the ordinary path helper
`0x7a51e0` is called at `0x51bf69`. It tries cardinal grid paths, with grid40,
length draws modulo12, at most10 candidate attempts, arrival below5, and a
stuck predicate below speed.6 for more than10 updates. Targeting/control/status
branches take other helper paths; they are not silently claimed complete here.
Facing is selected from the preceding velocity. Acquisition at `0x51c95f`
uses divisor35 and rejects source flag mask `0x1000a00`. A stored animation
axis and horizontal flip determine the direction at emission; ordinary shots
do not turn toward Isaac. The runtime preserves the facing snapshot and source
chance/timing but does not yet implement every native status flag.

`0x51d2d3` constructs the ordinary parameters. The Tainted stream at
`0x51d390` constructs a separate parameter block, so it does not inherit the
ordinary HeightModifier14/falling modifiers. The Conjoined second projectile
is the negation at `0x51d5b3`. The moving burst is a walk-animation event at
`0x51c05b`; it is not an extra ring appended to the primary attack.

### Flight and planar motion

FireProjectiles mode0 sets fallingSpeed=-3 and fallingAccel=.1 before adding
modifiers (`0x6a3096`). The source height update has an additional +.1:
`fallingSpeed = .9*fallingSpeed + .1 + fallingAccel`. Therefore ordinary shot
acceleration is .098, stream acceleration .17-.005n, and moving-burst
acceleration **1.42**, not1.32. The helper's trajectory argument10 controls
falling physics; it does not make horizontal speed10.

Mode9 **skips** the mode0 defaults. It retains initializer fallingSpeed
`(U-.5)*.2` and fallingAccel0, then adds-.07, giving total acceleration.03.
The death ring therefore does not inherit fallingSpeed=-3 or the ordinary
shot's gravity. Mode9 increments its angle before emitting its first member;
its first member is one angular step beyond the configured offset.

Orbit flags0x800/0x1000 disable native grid collision (`0x62f74d`) and use
`0x6350a2` with a fixed stored center. For delta=position-center, form the
perpendicular (-delta.y,delta.x), negated for CCW. Add a radial component
`delta*.5` when OrbitDistance=0; otherwise use
`delta*.5*clamp(1-length(delta)/OrbitDistance,-1,1)`. Normalize the sum and
restore the previous horizontal speed. This creates an outward spiral for
Tainted death shots, not a constant angular-velocity curve.

Source base movement runs before the orbit/acceleration update. DeathWard
subdivides planar travel at30Hz boundaries, sweeps collisions along each
segment, then updates the next segment's velocity. The retained fixed center
and source attribution survive owner removal. Acceleration multiplier1-.03n
is applied after each source movement frame; values below1 deliberately slow
shots even though the native flag is named ACCELERATE. Vertical velocity is
independent. Existing straight shots and constant-curvature controllers retain
their behavior.

## Explicit adaptations and incomplete scope

- Native room-grid path ranking is adapted to bounded cardinal rays with
  physical body radius, room margins and collision clipping against the actual
  3D canyon. It cannot select a route through cliffs, deep rivers, gates or
  solid props. This is not a byte-for-byte port of native cell weighting or RNG
  consumption. The recovered force/friction, cardinal intent and lack of player
  pursuit are retained. Exact native/global time ordering remains a parity gate.
- Source horizontal scale.1 and vertical scale.05, body radii.6/.65/.8,
  projectile radius.22 times size, physical sphere collisions, eight-second
  lifetime cap and world-floor landing are DeathWard adaptations. Source2D
  collision-height cutoffs are not substituted for the real3D geometry.
- Under resource saturation, a complete attack packet waits at its emission
  frame. The death packet retains one non-living owner until all16 shots can be
  admitted. No partial ring, duplicate kill/reward or unbounded queue growth.
  Room completion waits for the retained packet and physical projectiles.
  Debug clear explicitly discards pending work. Ordinary execution still emits
  the death payload.
- Ordinary/Conjoined source Caves-family habitats map to sparse bands1–2
  crossfire pools, one of each identity per room at most. Tainted source rooms
  are Ascent-only; its rare band3 crossfire placement is explicitly a local
  progression adaptation, not a claim that it spawns in ordinary source floors.
- Original low-poly silhouettes show one mouth, two opposite mouths, or an
  enlarged Tainted body with inflamed growths. Warning mouths expand during
  the committed attack. Source sprite frames provide timing, not imported art.
- Source charm/fear/confusion/control/champion branches, complete item/status
  interactions, all parent summons, exact source RNG/path ranking, mixed-room
  readability, full-floor/mixed-build balance and controlled rendered
  performance remain unaccepted. No record is marked complete on this evidence.
