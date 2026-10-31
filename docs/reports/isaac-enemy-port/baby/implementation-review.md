# Baby family implementation work

This extends the preserved [source review](source-review.md). The review and
extracted controller/animation files were frozen with the preceding Mr. Maw
checkpoint and remain unchanged. This file records subsequent implementation.

The ordinary scope is Baby38.0.0, Angelic Baby38.1.0, small Angelic38.1.1 and
Wrinkly Baby38.3.0. Ultra Pride's38.2.0 remains a separate boss dependency.

`Babies.cpp` replaces generic teleport/charge behavior for those four identities.
The immutable `babies.mechanics` profiles hold movement, attack/animation timing,
projectile flight, teleport geometry and Wrinkly's dash/recovery values. Existing
library reloads construct a new snapshot; active simulations retain their old
snapshot. HP is80/80/51.2/80 with the established source-to-game conversion.

Normal and small Angelic fire one projectile; full Angelic and Wrinkly fire the
native mode2 packet. Side vectors keep their source lengths and narrow spread,
including Wrinkly's.6 spread factor. Mode2 inherits.4 parent velocity after
multiplying projectile velocity by1.2. Baby's final1.07 multiplier follows that
operation. Gravity and initial vertical velocity use the existing physical
projectile adapter rather than a flat projectile with a cosmetic arc.

Normal/Angelic acquisition uses a7-frame global/entity stagger, cooldown35 and
Shoot5 of Attack32. The shot aims at the current player. Teleport processing
follows the shot event and can replace the animation. There is no invented
automatic shot after reappearance. Collision disables on the first update in
Vanish and returns on the next ready update after Appear19 completes. Jump5 and
Land5 drive a disappearing/reappearing procedural body, independently of those
damage windows. Relocation waits until the source counter exceeds24.

Wrinkly approaches or retreats around distance120, chooses attacks with the
source1/4 chance after its delay, and snapshots its dash target after DashStart7.
It adds3.75 force, retains.85 velocity, projects onto its committed direction and
corrects lateral drift. It then fires at Shoot11 of Attack38 and recovers for
15..44 source frames, including the native epilogue decrement. Close attacks
start at frame3. The hostile dash does not steer toward a moving player.

Ordinary source habitat evidence places Baby in bands2–3, Angelic in band3
(Cathedral), and Wrinkly in band3 (Utero, Sheol, Dark Room, Chest and alternate
Corpse). Small Angelic has no independent encounter entry: the existing Holy
Mulligan summoning route supplies it. These authored weights and caps are local
design values, not copied template frequencies. Adding this child controller
does not certify Holy Mulligan's old parent controller.

## Adaptations and open fidelity work

- 30Hz decisions use scale.1 for horizontal distances; vertical flight uses the
  existing source projectile adapter. Original procedural art is retained, with
  separate normal, winged and wrinkled silhouettes.
- Native path-cell costs become room-relative40-unit cells checked against
  actual terrain, live actors and reserved teleport destinations. Terrain may
  move after selection, so blocked destinations retry rather than embed the
  actor. Small rooms can leave normal Baby without a legal distant destination;
  shooting continues while it searches, as the controller permits.
- Vanish drift ignores grid collision but remains bounded by the current room.
  Common native wall response has not yet been independently traced; Wrinkly
  stops against physical canyon walls or player contact and begins its attack instead of sticking
  forever or clipping through them.
- The native recent-damage field currently maps to four source ticks after an
  accepted local hit. Its exact native decay still requires tracing. Damage
  flashes and this gameplay timer are separate.
- Volleys retain their event atomically under allocation pressure. This bounds
  source allocation without silently dropping part of a burst.
- Exact charm/control/status/champion behavior, appearance activation, hard-mode
  integration, native RNG ordering and alpha-mask collision footprints remain
  open. The configured projectile speeds currently represent normal difficulty.
- Generated activation, Linux/WASM visuals, full-floor balance and controlled
  performance require their own evidence. No completed six-gate port is claimed.

## Browser-discovered acquisition correction

The first hardware-backed run passed normal Baby, Angelic and small Angelic,
but Wrinkly stayed idle in the diagonal scene. Its native hostile branch calls
`6aeb40`, which checks entity types and allegiance flags only. It does not call
the normal Baby range/line-of-sight helper. The added local sight gate was wrong.
It is removed; a regression starts Wrinkly behind solid cover, waits for its
actual dash acquisition, and verifies the physical wall still stops that dash.
The retained [supplementary source](source/target-eligibility-manifest.json) pins
the exact executable bytes. The first failed browser run remains preserved.
