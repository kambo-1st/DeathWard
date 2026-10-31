# Spitty family implementation checkpoint

This batch replaces the generic Spitty and Tainted Spitty behavior and adds
Conjoined Spitty. It covers three regular enemies: **31.0.0, 31.1.0 and
243.0.0**. The full 653-record port remains active; these records remain
`in_progress`, with regular enemies and required offspring ahead of more bosses.

## Behavior and placement

The [source review](source-review.md) records the installed Repentance 1.7.9b
controller, animation events, projectile math, preserved evidence and explicit
DeathWard adaptations. Ordinary Spitty wanders on cardinal paths and spits in
its committed facing direction. Conjoined Spitty shoots from both ends.
Tainted Spitty adds moving bursts, a ten-shot slowing stream and two opposed
eight-shot spirals on death. The spirals keep their center after their owner is
removed. Resource limits defer complete packets without dropping half an attack
or awarding a second kill.

Health is 32 / 57.6 / 192 for ordinary / Conjoined / Tainted, using the existing
3.2 conversion from source HP. Tainted retains the shared adaptive armor.
The protagonist remains at 100 starting HP and 24 base damage.

Source Caves-family habitat maps to sparse ordinary/Conjoined band 1–2 pools.
Tainted is a rare band 3 specialist; this is an explicit adaptation of its
source Ascent placement. [Natural witnesses](natural-witnesses.json) record
actual seeded residents, not manually inserted demonstration enemies.

Profiles are externally configured in `assets/mechanics/spitties.mechanics`.
New libraries validate the complete profile before use; existing simulations
retain their immutable library. Source-rate planar acceleration and orbit
motion are reusable projectile features, independent of vertical flight.

## Validation

- [Full Linux run](native-full.txt): **85/85 suites pass**, including the new
  dedicated family and projectile-motion tests.
- [Focused family results](native-focused-4.txt): attack timing and direction,
  movement independence from the player, moving bursts, stun cancellation,
  room suspension, packet saturation, death retention, physical cover,
  external configuration and actual seeded activation.
- [Projectile checks](projectile-tests-1.txt): independently derived orbit
  endpoint, opposite handedness, source update order, 30/60/120 Hz subdivision,
  vertical independence, physical collisions and owner removal.
- Isolated default-kit probes defeated ordinary / Conjoined / Tainted in
  1.35 / 1.63 / 20.53 seconds, leaving 100 / 100 / 87.5 HP. The bot pursues,
  strafes and leads its shots. This is a basic feasibility check, not a
  full-floor or mixed-build balance result.
- Final Linux and production WASM builds include distinct Original-style
  silhouettes and a smoke-only camera-follow option. This option changes
  capture framing, not player position or enemy behavior.
- [Final browser run](web-final/results.json): **9/9 cases pass** in production
  WASM. It covers all three isolated variants, solid cover, a river bank,
  Tainted death and the three actual seeded residents. No browser/GL errors.
- [Visual review](visual-review.json): **20 images individually inspected**,
  16 accepted as smoke views and four explicitly limited views. These include
  Linux and browser captures in the Original style.

The [checkpoint](checkpoint.json) pins the final builds, runtime files and
report evidence. All 6,972 preceding report artifacts were checked unchanged.
The mechanics fingerprint is `cc57c1a3e966dbf0`: 178 definitions, 171 reviewed
records, 129 in progress, 51 existing-unverified, 461 missing, 12 excluded and
zero complete ports. There are 79 direct ordinary pool identities and 83 with
conditional replacements; this count does not include offspring or bosses.

## Preserved failures and limits

Earlier logs remain intact. The initial death-ring assertion exposed an angular
convention mismatch; the implementation now uses the source's increment-before-
emission angles and half-step offset. Two stationary-player fixture runs failed
to finish Tainted in the oversized test room. The moving default-kit probe
replaced that ineffective strategy without weakening the enemy.

An initial WASM compile failed because unparenthesized JavaScript object
literals confused the `EM_ASM` macro. The corrected build succeeded. Another
link process ended with exit 143; the log establishes termination, not its cause.
The later build was started only after confirming the prior process had ended.

The first browser run passed the three isolated variants, then correctly failed
the cover test: the capture harness spawned the grounded actor inside its crate.
The corrected harness places Spitties beside the crate, as it already did for
other grounded families. Browser checks now explicitly reject blocked ground
positions as well as deep water. Five subsequent diagnostic cases passed for
river movement, Tainted death and all three actual seeded residents. These
earlier runs remain preserved rather than being overwritten by the final run.

Early captures with a player-centered camera clipped wandering actors at the
edge. Final camera-follow captures show the actors, but foreground cliffs can
still obscure part of their bodies near a boundary. Those views are limited
evidence. FPS labels captured during compilation are not controlled performance
measurements.

Open acceptance work includes source charm/fear/confusion/control/champion
branches, complete item/status and parent-summon interactions, exact native
grid-ranking/RNG equivalence, all-camera mixed-room readability, full-floor
mixed-build balance and controlled Linux/WASM performance. No full acceptance
gate is inferred from the focused tests.
