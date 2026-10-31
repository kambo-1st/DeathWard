# Ordinary Brain 32.0.0 — source review and dedicated implementation

The generic wanderer has been replaced in the working tree by a dedicated Brain
controller, external profile, and independently timed ground trails.
[Focused native checks](native-focused-final.txt) cover the movement and creep
contract below, starting equipment, configuration and actual seeded residents.
The separate [progress record](progress.json) and final checkpoint record the
validation scope; this document does not certify full six-gate acceptance.

The installed Repentance 1.7.9b executable is pinned to SHA-256
`04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.
[Native instruction windows](source/manifest.json) and
[highest-DLC animation metadata](animations/manifest.json) are reproduced by
`python3 scripts/isaac-reference/analyze-brain.py --check`. Animation metadata
comes from `afterbirthp.a`; no source artwork is imported into the game.

[Source discovery](source-discovery.json) preserves the XML, room-template counts
and wiki article revision270038, by The Binding of Isaac: Rebirth Wiki
contributors under CC BY-SA4.0. Its introduction describes cardinal wandering,
charging on alignment and red creep. Its shorter infobox omits charging, so
using the infobox alone would produce an incomplete enemy.

## Identity and ordinary movement

Type32 selects dispatch index18, case `699e4b`, controller `500140`.
The same function contains type279 Black Globin Head and type301 Poison Mind
branches. Neither belongs to ordinary Brain: its movement is grounded, cardinal,
and does not inherit direct pursuit, diagonal flight or an explosion on death.

XML gives HP20, stageHP0, collisionDamage2, mass10 and radius13. Earlier local
health56 is corrected to **64HP** under the project's established x3.2 conversion.
Contact is20 before the existing hostile1.25 multiplier, yielding **25 damage**.
Player defaults remain100HP and24 base damage.

Initialization sets state4 and returns. Subsequent updates keep the looping
**Walk30** animation active; Idle10 and Appear20 are also present, without event
triggers. Appearance metadata alone does not establish collision activation.

The ordinary state4 branch at `5008e9` calls the shared cardinal random-walk
helper with **force.75**, then damps X by **.85** and Y by **.8**. This differs
from Maggot's vertical damping. The source helper's grid40 and bounded random
destination behavior are already preserved in the Maggot/Spitty source reviews.

`7a6e20` computes the actor's **current grid cell** from its position and stores
it at pathfinder+20/entity+384. It is not a future destination. Brain uses that
cell's center for charge acquisition and lateral correction.

## Charge acquisition and motion

The state4 ordinary branch checks a **global frame interval7**, staggered by the
entity field at+20. The interval helper at `684790` establishes this as global
frame modulo timing; it must not be described as a fresh random 1-in-7 chance.
Controlled actors and source status mask `0x1000a00` bypass acquisition.

At an eligible check, the source predicts the target position by adding target
velocity times **16U**, where U is a uniform random fraction. The room helper
clamps that prediction with20-unit margins. From the actor's current grid-cell
center it requires:

- at least one axis difference strictly below **20**;
- Euclidean distance strictly below **200**;
- the native room line check to succeed.

The larger axis difference selects a committed cardinal direction. State becomes8.
There is no separate generic attack windup or attack cooldown in this branch.

While charging, collision/contact flags or the source control/status conditions
return the actor to state4 and clear the stored path vectors and charge vector.
Otherwise the controller multiplies the physical friction by.8, then adds the
committed direction scaled by speed/friction. The base movement pass multiplies
velocity by that friction and resets it to the base value. At ordinary unit
speed/base friction, the resulting recurrence is **v'=.8v+direction**, not an
unbounded acceleration. This derivation requires both the controller and the
preserved base-movement window.

The perpendicular position is corrected toward the current grid-cell center:
**.9 × old coordinate + .1 × grid coordinate**. The charge does not continuously
turn toward the target. Exact grid origin, native line-query behavior and source
global frame ordering need explicit treatment in the 3D adapter.

## Red creep

The common tail at `500dcd` queries the living-enemy count using `6ad7a0`.
The normal hostile path reads the room's living counters; a separate friendly
branch counts friendly actors. This is **not a floor/stage multiplier**.

- Fewer than5 living enemies: base emission interval **12 source frames**.
- At least5: base interval **24 source frames**.
- A second, half-period-offset emission occurs only when planar speed squared
  is greater than **9**, increasing trail density during faster motion.
- These emissions use actor-time interval crossings (`6847e0`) with a stable
  entity offset. They are distinct from the charge's global interval check.
- Each event creates effect **1000.22** at the current position, sets sprite
  scale **1.23** and immediately calls its update. Type301 would select green
  effect23, but ordinary Brain does not.

The effect dispatch table maps22 to `5d17fc`. Its initialization sets lifetime
**125 frames** (`5b7dfa`), scale property1, and the first update computes its
bounding radius as **20 × sprite scale × scale property**, i.e.24.6 native units
for this producer. Its damaging footprint additionally samples the source
animation alpha mask at threshold.5; the bounding circle is not the entire
source hit shape.

The hostile red/green/yellow branch at `5d1e81` applies **1 damage unit** with
creep damage flags and a30-frame damage-countdown argument, subject to player
vulnerability/collision and immunity checks. It does not deal Brain's2-unit
body contact damage. A 3D patch therefore needs its own configured damage.

The effect timer decrements once per update and marks the effect dead on expiry.
Dead creep stops its damage branch, multiplies its scale by.98 per source
update and fades over approximately40 updates,
then removes itself. Ordinary hostile creep also begins dying after room clear
when the source's remaining-enemy condition permits it. Killing only its owner
does not remove it while other enemies remain.

## Implementation work and explicit adaptations

The reusable axis-wander steering feeds a separate Brain controller for
initialization, committed charge and source-timed creep. External profiles set health,
contact, both axis dampings, charge period/range/alignment/prediction/friction,
animation length, emission thresholds, creep footprint/damage/lifetime/fade and
floor placement. No Spitty shooting behavior is attached.

Ground movement, charging and grid-centering corrections use the actual canyon
collision queries. The grid origin is the room center. A blocked current grid
cell falls back to the actor position; every correction is swept with the actual
body radius. The local body radius remains.6 rather than a direct conversion of
the source13-unit body. Source force/velocities use distance scale.1 and30Hz
decisions, interpolated by the existing60Hz physical simulation.

Native animation-mask creep becomes a visible2.46-radius circle, with the
existing player contact skin and line-of-sight damage query. It is an explicit
3D footprint adaptation, not a reproduction of the source alpha mask. The
visible boundary stays at that radius while damaging; shrinking begins only
after the patch is harmless. Translucent pools retain terrain depth testing but
share a pass with depth writes disabled, preventing coplanar overlap striping.

Local monotonic entity IDs provide stable phase offsets. Charge checks use
simulation-global time while emission uses the actor's source clock. Inactive
rooms retain their actor state. Stun cancels the charge and pauses its clock.
These choices do not establish exact source global RNG/update ordering or the
source control/champion/status branches. The patch lives125/30 seconds locally;
the source immediate creation update and global effect iteration can differ by
a simulation step. Capacity pressure retains one pending emission and pauses
the actor until it can be admitted, rather than silently discarding the trail.

Patches outlive their owner while another enemy remains. Last-enemy death
automatically clears the room and begins harmless fading; the fade cannot hold
the doors closed. This is tested through the real completion path.

The source's ordinary positive-weight templates occur in Depths/Necropolis/Dank
Depths and Womb/Utero/Scarred Womb. These map to **bands2 and3**. Void, Ascent and
Greed entries need separate routing review; template counts are not probabilities.

The focused checks cover axis damping, lack of pursuit while wandering,
aligned acquisition and prediction, committed direction, collision/body stopping,
safe grid-centering, sparse/dense and fast/slow creep intervals, creep damage
distinct from body contact, expiry/fade, survival after owner death, room-clear
cleanup, stun and room suspension, seeded placement and external reloads.
Linux/WASM rendering, mixed-room balance and controlled performance retain
their separate evidence and acceptance scope.

Open scope includes source status/control/champion and item immunity interactions,
global/entity clock equivalence, exact native RNG/grid ranking, animation-mask
collision and all parent dependencies. No acceptance gate is closed by this
source review alone.

One intermediate extraction check failed after replacing a constant label with
its actual immediate-instruction address: the manually updated JSON key order
differed from the extractor's byte-for-byte output. Restoring the generated order
resolved that metadata serialization mismatch; it was not a runtime behavior test.
