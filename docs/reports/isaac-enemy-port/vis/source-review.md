# Vis family: installed 1.7.9b review

This is source analysis for the next regular-enemy implementation, not a claim
that the current generic Vis controllers reproduce it. The scope is Vis
`39.0.0`, Double Vis `39.1.0`, Chubber `39.2.0`, Scarred Double Vis `39.3.0`,
and required Chubber Projectile `39.22.0`. Gluttony `49`, Vis Versa `836`,
and Evis `865` remain separately tracked records.

The [export manifest](source/manifest.json) pins the installed executable,
seven disassembly windows, constants and animation-name strings.
The [animation manifest](animations/manifest.json) pins five highest-priority
DLC animation files, including frame counts and Shoot events. The reproducible
exporter is `scripts/isaac-reference/analyze-vis.py`; `--check` compares bytes.
Only reference metadata is extracted; no Isaac artwork is imported into the game.
The preserved wiki article is revision
[271633](https://bindingofisaacrebirth.wiki.gg/index.php?oldid=271633), by
The Binding of Isaac: Rebirth Wiki contributors, CC BY-SA 4.0. Native findings
below take precedence over statements explicitly labeled as older editions.

## Identity, health and routing

| Exact record | Installed base HP | Stage HP | Role | Proposed standard bands |
|---|---:|---:|---|---|
| 39.0.0 Vis | 25 | 0 | Ordinary beam enemy | 2–3 |
| 39.1.0 Double Vis | 25 | 0 | Ordinary opposing-beam enemy | 2–3 |
| 39.2.0 Chubber | 25 | 0 | Ordinary returning-body attacker | 1–3 |
| 39.3.0 Scarred Double Vis | 22 | 0 | Ordinary four-beam enemy | 3 |
| 39.22.0 Chubber Projectile | 1000 | 0 | Required owned attack component | Parent only |

These habitat proposals come from the exact source room-library rows in
`docs/research/isaac-enemy-port-plan.json`, not from template frequencies used as
spawn probabilities. Chubber has Catacombs and alternate Mines evidence; the
others start in Depths-family or Womb-family libraries. None belongs on the
opening band. The projectile has no independent ordinary-room placement.
The existing health conversion would produce 80/80/80/70.4 for the four bodies;
the component's nominal HP must not be confused with ordinary vulnerability.

## Body controller

Type 39 dispatches to `519dd0`. Variant 22 immediately delegates to `519980`.
The body function also handles other types; its Gluttony projectile burst and
Vis Versa homing-laser branches must not be copied into ordinary Vis.

- Initialization enters state 4. Walking calls the common random cardinal
  path routine `7a51e0` with parameter .7, and uses WalkHori (22 frames).
  The .7 is a steering parameter, not an established world-units/second speed.
  The common path routine chooses among terrain-cost-dependent cardinal cells,
  preserves a destination, corrects stalled motion and clamps to room bounds.
  Its full source is preserved; a faithful canyon navigation adapter is still
  required. A free-angle generic wander is not equivalent.
- Acquisition is checked on the global-frame/entity stagger every 3 frames.
  For ordinary hostile bodies, at least one target-axis gap must be less than
  20 source units, and Euclidean distance must be less than 400.
  `6593a0` snaps the larger-magnitude axis to a unit cardinal direction; ties
  select the vertical axis. This direction is stored before the windup.
- The additional helper `89fbb0` reads view/room bounds and player positions;
  its preserved code does not call a grid raycast. Treating it as terrain
  line-of-sight would invent a restriction. Its exact camera-dependent boundary
  semantics still need review before translating to DeathWard's 3D view.
- Allegiance/status checks and player-controlled branches are distinct.
  Ordinary hostile alignment must not inherit the controlled-entity helper's
  range/line-of-sight checks by accident.
- Beam bodies enter state 9; Chubber enters state 10. The animation name is
  chosen from the stored direction and variant. On completion, return to state
  4. No independent random attack cooldown is set in this branch.
- End-of-update multiplies the body's `2c4` motion/friction factor by .8.
  Confirm the common entity-update interpretation before treating this as a
  direct velocity multiplier or resetting momentum during windup.

| Variant | Selected attack | Total frames | Shoot frame | Packet |
|---|---|---:|---:|---|
| Vis | Attack01 | 79 | 28 | One cardinal beam |
| Double Vis | Attack02 | 82 | 30 | Forward and opposite beams |
| Chubber | Attack03 | 69 | 18 | One 39.22.0 owned body |
| Scarred Double Vis | Attack04 | 82 | 30 | All four cardinal beams |

Horizontal, up and down animations share the listed timing. The ordinary beam
call passes timeout 32 to `8c7550` at the Shoot event; it uses the stored cardinal
heading, an x-origin offset of heading.x × 6, and a sprite offset `(0,-20)`.
Draw-order values of -10/3000 are presentation depth, not beam length or damage.
The generic DeathWard helper currently supplies a .4-second extra warning,
.65-second beam lifetime, fixed maximum length and only player damage. It cannot
be reused unchanged: source animation windup is already the warning, timeout is
different, and the reviewed family damages non-Vis enemies while sparing Vis.
Exact native beam hit cadence, damage, obstruction and owner-death behavior
still require tracing in the common laser implementation.

## Chubber's returning component

The parent Shoot event spawns type 39 variant 22 subtype 0, attaches its parent
reference, and initializes velocity to `(heading.x × 16 × 1.4, heading.y × 16)`
in source units per update. Horizontal shots therefore move faster than vertical
shots. A horizontal shot receives a .1 source-unit y offset. The parent remains
in its attack animation; there is no conversion to an ordinary Vis body here.

`519980` stores the initial velocity and initializes counter zero. Grid collision
is disabled (`17c=0`), matching the XML's `gridCollision=none`. The two cleared
fields at `2d8/2dc` and the `b8c` byte need semantic confirmation; do not label
them as recovered damage flags merely from their offsets.

For subtype 0, let t be the counter and q = 1 − t/21. While q is nonnegative,
velocity is q times initial velocity. The outbound component slows to zero at
t=21. With a parent and negative q, it computes the current vector to that
parent, reduces its length by 20 source units, and multiplies it by
`(-q) / max(43-t,1)`. Thus the return tracks the parent's current position,
rather than following a prerecorded reverse path or aiming at the player.
The controller removes it after counter >42. If its parent reference is absent,
it invokes the death virtual function instead; the pre-Repentance wiki statement
about surviving the parent's death is not the installed behavior to copy.
Subtype 1 has a straight-flight/until-outside-room branch; the reviewed exact
catalog record is subtype 0, so subtype 1 is retained as context only.

The wiki describes normal projectile invulnerability, blocking player tears and
double contact damage. XML confirms collisionDamage=2 versus the parent's 1,
but the blocking/damage-exception implementation still needs native collision
review. A generic enemy with 3200 HP would be an incorrect substitute. This
component needs explicit ownership, no independent loot, and tested cleanup
when its parent dies, when the room is left, and at its timeout.

## Implementation and acceptance work remaining

Implement external body/component profiles and dedicated runtimes. Extend the
beam service with an explicit family damage policy and timed ownership rather
than changing every existing beam. Keep stored cardinal aiming, exact per-variant
animation events, atomic multi-beam emission, and the returning-body trajectory.
Trace unresolved shared movement, laser and collision semantics before claiming
source fidelity; keep documented 3D/terrain adaptations separate from source
values. Preserve Original visuals and the 100 HP/24 damage starting character.

Tests must cover diagonal non-acquisition, locked direction during windup,
one/two/four actual beam packets, friendly fire with Vis immunity, no second
invented windup, obstruction, Chubber's horizontal/vertical speeds and curved
return to a moved parent, parent death, tear interception, damage exceptions,
room persistence, capacity pressure, seeded bands and starting-kit fights.
Inspect native and WASM warning/attack views in ordinary, cover and river rooms.
No Vis record is implemented or accepted by this source review alone.
