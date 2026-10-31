# Baby family: source review in progress

The regular scope is Baby38.0.0, Angelic Baby38.1.0, its required small
offspring38.1.1, and Wrinkly Baby38.3.0. Ultra Pride Baby38.2.0 is a boss
component retained in the overall goal; it is not an ordinary encounter entry.
No new runtime controller or completed port is claimed by this review.

The [pinned wiki article](source-discovery.json) is revision270035, by The
Binding of Isaac: Rebirth Wiki contributors under CC BY-SA4.0. Installed XML
and room-template evidence accompanies it. Native values below come from the
installed Repentance1.7.9b executable, SHA-256
`04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.
The authoritative full hash is recorded in [the manifest](source/manifest.json).
Seven native windows and five checksum-verified animation files are preserved
by `scripts/isaac-reference/analyze-baby.py`; `--check` verifies them again.
The first truncated projectile export is retained separately, not used as a
complete helper contract. Sprite artwork is not imported into the game.

## Identity and health

All four ordinary identities have source contact1. Source HP is25 for Baby,
Angelic and Wrinkly, and16 for small Angelic, with no stage HP. The existing
x3.2 conversion therefore requires80,80,80 and51.2 respectively. Current
Angelic96, Wrinkly96 and small40 placeholders are incorrect. Small Angelic is
variant1/subtype1 in installed XML; the article's inherited infobox variant0
does not override that identity.

Baby's source habitats are Depths/Womb families (local bands2–3). Angelic is
Cathedral (band3), and small Angelic is summoned by Holy Mulligan22.2.0 rather
than independently pooled. Wrinkly's source stage evidence must be retained
when choosing its band3 habitat. Special-mode tables are not ordinary weights.

Type38 dispatches via index22, case699974 to5185e0. Variant3 immediately takes
the separate controller53c8f0. The shared controller also serves Imp259; its
burst and projectile-evasion branches are not Baby behavior.

## Baby and Angelic behavior

- Ready movement applies friction.7 and normalized pursuit force.33, giving
  `.7 * oldVelocity + .33 * direction` after base movement. While the attack
  cooldown is positive, ordinary hostile pursuit force is absent; momentum
  still decays. Native statuses/control alter this and remain a separate gate.
- Attack acquisition requires the shared global/entity7-frame cadence, strict
  range200, current-target sight and allowed status flags. It sets cooldown35.
  Cooldown decreases in ready state, including during the attack animation;
  it is not an unrelated random2.8-second cooldown.
- Move loops12 frames. Attack lasts32 frames with Shoot at5, all at30FPS.
  The projectile direction is sampled from the current player at Shoot.
- Normal and small Angelic use mode0 (one shot); full Angelic uses mode2
  (center and two sides). Native normal-difficulty speed is8. Hard difficulty
  increases the mode0 speed to10; full Angelic's mode2 speed remains8.
- Their parameters set FallingAccelModifier=-.05 and VelocityMulti=1.07.
  Mode0 gives fallingSpeed=-3, fallingAccel=.1 before modifiers. Mode2 gives
  fallingSpeed=-4, applies velocity1.2 and inherits.4 of parent velocity.
  The side vectors are `.9 * (.961*forward +/- .276*side)`, not equal-speed
  normalized directions. The final1.07 multiplier applies after inheritance.
  The shared vertical update also adds.1; omitting it changes landing time.
- Taking recent damage sets the teleport accumulator to20. While either axis
  differs from the target by less than20 and distance is below400, it gains1
  per ready update; it also gains uniform[0,.1) each update.
- Above20 charge, with no stored destination, up to two candidates are tried
  per ready update. Each lies60+250*U from the current actor at a random angle.
  Normal Baby requires both target-axis gaps>20 and target distance>200.
  Angelic instead requires target distance in(50,120). Both reject occupied
  native path cells and nonempty grid-collision cells, then snap to the cell.
- Above40 charge with a destination, state6 plays Vanish and disables entity
  collision. After the native counter exceeds24 it relocates, clears the
  stored destination and charge, and plays Vanish2. Ready/collision return
  follows animation completion. Vanish metadata lasts24 with Jump at5;
  Vanish2 lasts19 with Land at5. Exact animation/collision update ordering
  must be checked, not inferred solely from those names.
- Teleport processing can replace an attack animation in the same update.
  Preserve event ordering rather than inventing an unconditional post-teleport
  shot. The wiki notes an animation mismatch when those events coincide.

## Wrinkly behavior

- No teleport branch. Initialization sets ready state and a5..14-frame delay.
- Ready movement uses friction.7 and force.33. Within120 units, its movement
  target is shifted to a point120 units from the player on the actor's side,
  causing retreat. Beyond that distance it approaches.
- After its delay, with valid target visibility/status, a1/4 per-update check
  considers an attack. Below120 it plays Attack starting at frame3. Between
  120 and280 it plays the7-frame DashStart. At the end of that windup it
  snapshots the player's position and normalized dash direction.
- Dash motion adds3.75 along the locked direction and uses friction.85. It
  projects velocity along that direction and corrects lateral position drift
  from the committed line. It switches to Attack when the remaining projected
  distance is below20. The native common collision response at walls still
  needs tracing; a timed homing charge would not match this controller.
- Attack lasts38 frames, Shoot at11. It aims at the current player and uses
  mode2 with SpreadModifier.6, origin offset4 units toward the target, speed8
  (10 on hard), default vertical parameters, and the shared1.2/.4 velocity
  post-pass. Unlike full Angelic, Wrinkly does not set VelocityMulti1.07.
- Attack completion clears the dash vectors/target and sets delay15..44.
  Its ordinary state then chooses retreat/approach again. It does not fire
  continuously every frame while the player remains close.

## Required implementation and validation

Replace the four generic motion/attack entries with external profiles and
dedicated30Hz state, using the existing real projectile and flight/navigation
systems. Keep the original low-poly visual style and default player equipment.
Use source animation events for shot and disappearance timing. Preserve the
required small child route; this does not certify Holy Mulligan's own AI.

Tests need independent HP, firing cadence and shot counts, actual side vectors
and inherited velocity, current-target aim at emission, projectile flight,
teleport destination/collision rules, no contact or damage while absent,
Wrinkly windup/locked dash/retreat/recovery, capacity retention, room suspension
and completion, seeded habitat activation, and Linux/WASM visual/balance checks.
Exact native status/charm/control, RNG ordering, grid weighting, appearance,
champion/difficulty integration and controlled performance remain explicit
acceptance work. This review does not mark those requirements complete.
