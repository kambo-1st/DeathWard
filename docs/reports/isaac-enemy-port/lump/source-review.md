# Lump56.0.0 — dedicated implementation in progress

Baseline: installed Repentance1.7.9b. The exact executable, two native windows,
constants and installed animation metadata are pinned in [source/manifest.json](source/manifest.json)
and [animations/manifest.json](animations/manifest.json). Reproduce/check with
`scripts/isaac-reference/analyze-lump.py --check`. The archive's checksum and
previously recorded SHA-256 are verified. No source sprite artwork is imported.
The [preserved dossier](source-discovery.json) includes the installed XML,
room-template presence and Lump wiki revision266755, by The Binding of Isaac:
Rebirth Wiki contributors under CC BY-SA4.0. The wiki supports the broad
stationary spread/burrow behavior; timing below comes from installed code.

## Source contract

- Type56 dispatch index36/case699ab8 invokes5106d0..51115c. HP30, no stageHP,
  contact1, mass30, radius13; ordinary grounded actor. No death offspring.
- Initialization saves current position as the anchor and selects state3.
  Thereafter friction is multiplied by.7 and velocity is replaced with
  anchor minus position. It approaches an anchor rather than instantly teleporting.
- Ready state plays Shake (2 looping frames). With no cooldown it has a1/50
  per-source-frame chance to enter Hide. This is also how it burrows away from
  an out-of-range player, without first firing.
- Cooldown decreases every source update. At zero, the shared acquisition
  helper tests strict range260, seven-frame global/entity cadence, target
  eligibility and sight. It is not limited to ready state: it can interrupt
  Hide, underground search or Appear. On acquisition it shows the body, plays
  Spit, sets state8 and cooldown63.
- Spit lasts20 frames, Shoot at4 (all30FPS). Aim samples the current target
  at Shoot, with base velocity7 and default ProjectileParams, mode2.
  Mode2 emits center plus two sides. Side vectors are
  `.9*(.961*forward +/-.276*perpendicular)`, followed by velocity1.2 and
  parent-velocity inheritance.4. See the previously pinned complete
  [projectile helper](../dople/source/fire_projectiles.asm) and
  [Baby source findings](../baby/source-review.md). Default mode2 has falling
  speed-4 and default falling acceleration; unlike Baby, Lump does not add
  FallingAccelModifier=-.05 or VelocityMulti=1.07.
- Spit completion selects Hide. Hide lasts16 frames, Sound at1. The body
  remains visible/collidable until Hide finishes. Then Visible=false and
  EntityCollisionClass=0. There is no ordinary shadow/tracking ring underground.
- Each fully hidden update tries one random room position with margin20.
  Reject distance below200; also reject distance below400 when either target
  axis differs by less than20. A candidate with path-grid score>=500 is rejected.
  Otherwise it becomes the corresponding40-unit grid center. Each hidden
  update independently has a1/20 chance of Appear, even if no candidate passed.
  Failure keeps the previous anchor; the source does not relax minimum distance.
- Appear lasts22 frames, Sound at6. On the transition update the collision
  class remains0. Subsequent updates restore class4 even while Appear plays.
  Completion returns to Shake. Acquisition can replace this animation earlier.
- The controller's6971a0 call updates coloration, not vulnerability. The
  pre-Shoot6afe20 call clears ordinary control aim; it does not grant armor.
  Controlled-player branches are distinct from ordinary hostile behavior.

## DeathWard implementation and explicit adaptations

`assets/mechanics/lumps.mechanics` exposes HP scaling, contact, source frame
counts, chance denominators, targeting, relocation geometry and shot flight.
`src/combat/Lumps.cpp` owns a30Hz controller and pending complete volley.
The three shots use the real projectile system; capacity pressure retains the
packet and its emission-time aim rather than losing bullets or retargeting it.

HP30*3.2=96; contact/projectile1 becomes10 before the existing hostile1.25
multiplier. Distance uses.1, horizontal velocity uses3, source projectile
vertical distance uses.05: mode2 initial up6, gravity9 and retention.9.
World radius.6 and shot radius.22 retain DeathWard readability. Player defaults
remain100HP and24damage. Grounded movement uses real canyon collision.

The source's room grid/random-region sampling becomes room-relative cells
and the generated room bounds. Terrain, water and occupied body footprints
are rejected. A hidden transit may cross solids; visible emergence/acquisition
is deferred at an invalid footprint, and visible movement is swept through
terrain. This is an explicit3D safety adaptation, not a claim that the native
controller itself checks every intermediate underground point. In a small room
with no valid200-unit candidate, the old anchor remains; no shortened teleport
has been invented to make a test pass. Exact native path scores, multi-region
sampling and RNG call ordering are not reproduced.

The Original-style procedural low body uses an open mouth during Spit and
squashes/rises during Hide/Appear. The body, shadow and generic aim warning are
absent underground; no imported Isaac art or whole-scene filter is used. The
mesh deformation is authored, not a claim of pixel animation parity.

Ordinary Womb/Utero/Scarred Womb templates contain47/43/52 instances of the
identity (template counts, not probabilities). Local band3 crossfire pools
use authored weight2/cost3/cap2. Greed/special templates remain separate.

## Outstanding acceptance work

This is a partial port. Native slow/freeze/fear/confusion/charm/control,
champions and attraction, exact grid scoring/RNG/animation update order,
source audio/effects and boss-produced appearances remain open. Common stun
suspends this controller, an existing DeathWard adaptation. Full mixed-camera
readability, default-kit expedition balance, persistence and controlled Linux/
WASM performance are not certified by focused behavior tests or screenshots.
