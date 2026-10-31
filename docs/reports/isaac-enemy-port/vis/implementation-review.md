# Vis beam bodies: implementation work in progress

This supplement follows the frozen `source-review.md`. It does not replace that
review or certify a complete port. The first runtime batch covers Vis `39.0.0`,
Double Vis `39.1.0` and Scarred Double Vis `39.3.0`. Chubber `39.2.0` and its
returning component `39.22.0` remain next; the old Chubber controller is not parity.

## Additional installed-source evidence

`scripts/isaac-reference/analyze-vis-lasers.py --check` verifies the supplementary
[manifest](laser-source/manifest.json), disassembly windows and constants against
the same pinned Repentance 1.7.9b executable. Exploratory windows remain in
`laser-discovery`; they include failed/truncated scans and are not authoritative
exports. In particular, `npc_collision.asm` started at an invalid instruction
boundary and supplies no collision evidence.

- `8c7550` assigns both the laser's parent and spawner and records its offset.
  `8cc3d6` follows the parent's current position. A moving Vis therefore moves
  the beam origin without choosing a new heading.
- `8c5a90` rejects its owner, dead entities, entities with no collision class,
  entities with nonpositive maximum HP, and its owner's entity type unless the
  owner is charmed. Ordinary type39 beams consequently spare all type39 variants.
- `8cc396` calls the interval helper with the constant at `b6a7b0`, which is **2**.
  It clears the hit list for each damage pass. `8d6600` applies player damage1
  separately from the NPC damage parameter. Repentance's exact XML record7.1.0
  supplies NPC damage11 and collisionRadius16; older DLC XML damage22 is obsolete.
- `8d099f` decrements the positive timeout. Variant1 switches to the fade state
  after32 source frames. The fade update multiplies horizontal sprite scale by
  **.895**, decrements the counter and removes it below−18. A dead parent sets
  the laser's dead flag, stopping subsequent ordinary damage passes.
- The common movement window multiplies planar velocity by the accumulated
  friction factor before moving. Vis's `.8` factor belongs to both axes.
- The common damage window rejects maximum HP≤0. The Chubber component clears
  both HP fields during initialization; nominal XML HP1000 must not become a
  damageable3200-HP enemy in DeathWard. Its projectile blocking is still pending.

## Implemented batch

`assets/mechanics/vis.mechanics` contains immutable, validated profiles. The three
bodies use native health25/25/22 through the existing3.2 conversion, a30Hz
controller, cardinal-cell wandering, force.7 and retention.8, staggered3-frame
alignment checks, locked cardinal heading, exact Attack79/82/82 and Shoot28/30/30
events, and one/two/four-beam packets. Capacity pressure retains a whole packet at
its Shoot event. It does not invent an independent attack cooldown or a second
laser warning delay. Stun cancels a pending attack; inactive rooms suspend it.

The owned-beam service follows and retraces its owner, pulses every2 source
frames, applies local player damage10 and NPC damage35.2, and spares the owner's
type. Existing unrelated beam policies are unchanged. Owner death and room clear
start a harmless visible fade; leaving the room removes the beam. Rendering keeps
Original geometry/colors and gives the body one/two/four mouths that charge in
the committed directions. No Isaac artwork is used.

## Explicit adaptations and remaining verification

- Source units convert at.1; native walking grid cells become radius-aware canyon
  paths. Native view bounds are approximated by the active room. Acquisition has
  no invented line-of-sight test. Exact off-screen behavior is not certified.
- The3D beam uses a100-unit cap, .35 local collision/render radius, a configured
  height and a trace against solid
  cliffs/cover. This is a canyon collision adaptation, not proof of Isaac's
  obstacle-penetration rules. Ordinary river water should not block it. Directly converting the XML radius16
  by the movement scale produced an unreadably large beam in the first native
  capture; the configured width retains the previous canyon beam footprint.
- Expiry fade is currently **harmless**. Native timeout fade uses a flag distinct
  from death, and continued collision during that fade remains unresolved.
  The rendering scale/collision-width relation, beam knockback, charm and status
  branches need further review. Do not report full behavioral parity.
- Chubber's returning body, its interception of player projectiles and special
  damage exceptions are not implemented by this batch.
- Additional seeded pool placements, generated-room witnesses, native/browser
  visual review, default-kit balance and representative performance acceptance
  remain open. Unit contracts do not close the six completion gates.

Validation results are recorded alongside this file after commands actually
finish; counts and evidence in the earlier Baby checkpoint remain historical.

The [beam checkpoint](beam-checkpoint.json) records seven scoped native suites
passing after two stale generic-test assumptions were corrected: dodge starts at
the actual beam event, and the cover test fixes the committed lane independently
of wandering. The new contract suite also covers three actual-input starting-kit
fights. This batch does not claim a fresh run of every registered native suite.

The production WASM build passes five isolated scenarios across the three beam
bodies, solid cover and an interior river. The initial river target was diagonal;
the final fixture uses the existing legal-position CLI to align the player across
the water. An intermediate frame0 argument was rejected by that CLI; the final
frame1 run passes. Failed attempts remain alongside the accepted evidence.
Eight named screenshots were inspected, with the oversized first beam rejected
and the cover capture explicitly limited by foreground occlusion. See
`browser-summary.json` and `visual-review.json`. No completion gate is closed.
