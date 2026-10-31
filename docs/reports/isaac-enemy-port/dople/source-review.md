# Dople / Evil Twin — installed Repentance 1.7.9b

This batch replaces the unverified type53 controller. Both records remain
**in progress**, not fully accepted ports. The full653-record goal remains active,
with regular enemies and required offspring prioritized.

## Preserved evidence

`scripts/isaac-reference/analyze-dople.py --check` verifies the installed executable
SHA256 `04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`,
the type53 dispatcher and these complete disassembly windows:

- `0x5135e0..0x51444a`: shared Dople/Evil Twin controller.
- `0x695680..0x695a26`: target assignment, including unique-player ownership.
- `0x6a1a20..0x6a33ec`: projectile modes and shared parameter application.

`source/room-center.json` additionally pins `0x7ce9c0..0x7cea86`: the called
helper returns the bounds midpoint for ordinary shapes, with selected grid
anchors for native L-shaped rooms9–12. Canyon reflection uses the generated
room's own center; it does not reproduce those source-specific grid anchors.

`source/manifest.json` pins all window bytes, extracted text and selected float
constants. `animations/manifest.json` pins both30FPS ANM2 metadata files, resolved
from the highest available DLC archive. Source metadata is retained for reference;
no Isaac artwork is imported into DeathWard.

The preserved `Dople` article in `docs/research/isaac-mechanics-reference.json`
is revision270036, dated2026-10-03, attributed to The Binding of Isaac: Rebirth Wiki
contributors under CC BY-SA4.0. Its edition markers are retained. The native1.7.9b
controller, rather than later wiki wording alone, establishes the mechanics below.
The installed `entities2.xml` gives both variants20baseHP, zero stageHP and zero
contact damage, radius13, mass10. Main room-template evidence places Dople in
Womb/Utero/Scarred Womb and Gehenna, Evil Twin in Sheol and Dark Room; Greed and
special-library presence do not establish ordinary expedition eligibility.

## Source contract

- Initialization sets state4, zeroes attack/display counters, and returns. Normal
  Dople sets an alternating eye sign to1 and grid collision class5; Evil Twin
  selects class3 and leaves the eye sign zero.
- Target assignment treats all type53 variants together. Each player can be
  claimed by one such actor. If none remains unclaimed, the extra actor is
  removed. DeathWard has one player, so this becomes one mirror enemy per room.
- For the ordinary NPC branch, position is assigned to
  `2 * roomCenter - targetPosition`. This is absolute reflection; simply negating
  player velocity while preserving an arbitrary spawn offset is incorrect.
  The stored velocity is minus twice the player's velocity. Facing is the
  opposite cardinal player shooting direction.
- Firing detects an increase in the integer current weapon-delay field versus
  its previous sample. It does not count spawned tears. This explains the wiki's
  high-rate aliasing warning. Native status flags can suppress firing; the
  player-controlled branch uses separate movement and attack helpers.
- Normal Dople has no extra firing cooldown. Evil Twin sets30sourceframes and
  requests projectile mode2; normal Dople requests mode0. The firing pose lasts
  three frames. There is no target-distance or line-of-sight gate here.
- Base planar velocity is10units along the opposite cardinal direction plus
  .6of the actor velocity. A negative component of that inherited velocity along
  the firing axis is removed; lateral movement is retained.
- Normal Dople offsets the shot origin using alternating sign and a random
  factor `.3 + .2*U`. The native arithmetic swaps the velocity components before
  subtracting them from the origin. Evil Twin's eye sign remains zero.
- Mode2 produces center and two side shots. Side vectors are
  `.9 * (.961*velocity +/- .276*perpendicularVelocity)`, without normalization.
  It then applies velocity1.2 and adds .4of the parent's velocity.
- Dople parameters set falling-speed modifier1, falling-acceleration modifier
  -.101 and **scale1.4**. The1.4 value is projectile scale, not velocity.
  Mode0's base falling speed-3 becomes-2; mode2's-4 becomes-3. Base falling
  acceleration.1 plus modifier-.101 and the shared vertical-update.1 gives.099.
  Existing DeathWard conversions yield up3/4.5, gravity4.455, retention.9,
  height1.15 and radius.308. Planar10units/frame becomes30worldunits/second.
- Both are ordinary threats until killed, have no required offspring, and deal
  no contact damage. The grounded variant can be hurt by native spikes; the
  flying variant is immune to those ground hazards.

## Implementation and explicit adaptations

`assets/mechanics/mirrors.mechanics` owns HP, movement inheritance, projectile
parameters, spread coefficients, alternating origin range and cooldown. Parser
validation rejects invalid profiles and incompatible controllers. Immutable
content reloads use the existing mechanics system.

`src/combat/Mirrors.cpp` owns the dedicated source-clock attack controller and
room-centered movement. Translation is reflected each simulation step for smooth
3D motion; attack counters sample at30Hz. Common crowd separation cannot displace
the mirrored actor. Duplicate mirrors are removed without combat rewards, and
the seeded encounter planner prevents allocating two variants in the first place.

The local terrain is not symmetric. After reflection, a blocked footprint searches
up to16 half-metre rings with16 angular samples, retaining the old legal position
if no candidate is available. Active-room edges are clamped. This replaces native
grid collision resolution, is bounded, and is explicitly not exact native physics.
Flight uses the existing low-cover height and pit traversal policy; tall cliffs
remain solid. A blocked alternating muzzle offset is clipped back to the body.

Continuous mouse aim is quantized to a cardinal direction; keyboard aiming is
already cardinal. The local revolver cooldown is the current equivalent of the
native weapon-delay field. Unimplemented charged weapons and multiple-player
ownership are not claimed as supported. A full projectile pool retains one whole
volley while its actor lives, rather than emitting a partial three-shot attack.

Health uses the established3.2conversion:64HP for both variants. Player defaults
remain100HP/24damage. Projectile base damage10 still goes through the common
1.25player-hurt multiplier. The Original low-poly style is retained, with authored
red/charcoal body colors, a third-eye cue for Evil Twin, and a brief firing accent.
These are local procedural visuals, not a faithful reproduction of source art.

Both ordinary pool entries use late band3, matching their source habitats.
Weights/costs are authored local encounter values, not template probabilities.
Standard4–8-floor expeditions, the five-room tutorial, Fort Mercy and Mine roster
are not shortened or replaced.

## Validation and remaining gates

See `checkpoint.json` for final commands, artifacts and hashes. Native contracts
cover center reflection, room bounds, equal HP, zero contact, duplicate cleanup,
delay-driven firing, one/three-shot output, the30frame cooldown, unnormalized
spread, ballistic parameters, retained capacity, stun and high-rate aliasing,
terrain projection, low-cover flight, config rejection and immutable reloads.

A bounded natural-placement search inspected90generated floors and910rooms.
Witnesses: Evil Twin seed13/floor4/room6; Dople seed14/floor6/room3 (zero-based).
These are actual residents generated by the normal floor encounter code.

Still open: native spike/button interaction, full status/confusion/charm and
player-controlled branches, multiplayer/temporary-player lifecycle, exact native
RNG/update order, complete projectile flags and native grid/physics parity.
The source grid-collision behavior should be measured further around asymmetric
obstacles. Source walk/head animation timing is not fully reproduced. Broad
all-camera readability, starting-equipment balance and controlled Linux/WASM
performance acceptance are not yet complete. No six-gate completion is claimed.
