# Trite: source review in progress

This directory starts the next regular-enemy slice after the frozen
[Mushroom checkpoint](../mushroom/checkpoint.json). **No new Trite behavior is
implemented or validated yet.** Its registry status remains existing-unverified.
The global checkpoint still describes Mushroom. Do not count these extracted
files as completed implementation evidence.

[Historical integrity](historical-integrity.json) pins 6,481 earlier report
files. [Record](record.json) preserves source identity, 10 HP, contact damage 1,
radius 13, animation path and standard room habitats. The archived
[Trite wiki article](wiki-source.json), revision 266778, retains its attribution
and CC BY-SA 4.0 license; it describes less frequent, longer-distance leaps.

## Native findings established so far

The [manifest](source/manifest.json) pins the same installed Repentance 1.7.9b
executable used by preceding slices. `analyze-trite.py --check` validates the
shared controller, constants, strings and preserved disassembly. Types 29, 34
and 54 dispatch through `69a19f` to `514450`. That function also contains other
families: a condition for Ragling, Eggy, Leaper or Tainted Hopper is not evidence
for ordinary Trite unless the branch admits type 29, variant 1.

- Initialization sets state 3. Normal Trite has a **15-frame idle threshold**
  (`51491c` / `51496c`, tested at `515650`). It uses the shared Idle/Hop names.
- Each normal-hostile controller update samples a bonus
  `b = 50 * U + 70 * V`, with independent RNG draws scaled by `2^-32`.
  This is a sum of uniforms, **not** a uniform draw over 0–120. The controlled
  branch instead uses a constant 120 and is a separate implementation question.
- Detection range is `130 + 1.3*b` source units. The `.7` multiplier applies to
  Eggy and a Ragling variant, not Trite. The ordinary target helper returns the
  target body's position; the passed 60 is not normal target-velocity prediction.
- With no pending destination and the idle threshold met, a target strictly
  inside that range produces candidate `target + (target - self) * b/200`.
  This overshoots the target along the approach direction. Outside range,
  candidate distance is `95 + b` in a random direction.
- The candidate is clamped with source margin 5, checked against room grid
  collision, and snapped to the chosen grid-cell position before state 4 / Hop.
  The normal selection path here does not impose a line-of-sight check.
- [Installed ANM2](animations/manifest.json) gives Hop **26 frames**, Jump at
  **4**, Land at **18**, at **30 Hz**. It was resolved from Afterbirth+ after
  checking DLC overrides. These are animation/event times, not proof that the
  native body travels to its selected destination within exactly 14 frames.
- In state 4, steering uses the remaining destination delta. Outside the Jump
  event interval the delta is scaled by `.1`; when destination distance is at
  least 30 source units the impulse path uses `.05*delta`. The closer branch
  normalizes the delta. Both involve additional entity fields whose full base
  update interaction still needs review.
- Target release requires the animation condition as well as either distance
  under 10 or a 1-in-10 random test after the stuck/age condition
  (speed under `.75` or state frame over 30). The code does not simply discard
  the destination at Land18. There are separate collision-category changes
  around Jump/Land; these need mapping to DeathWard's actual-height collision.
- The ordinary Trite branch has no projectile attack or death offspring.
  Tainted Hopper rings and Eggy creep/death behavior are separate branches.

## Before implementing

1. Resolve the base movement integration, animation event semantics, and the
   fields at native `+2c4` and `+2f4`. Current REPENTOGON source layouts use a
   different build/layout and must not be applied by matching offsets alone.
2. Decide and document the 3D collision adaptation. Reusing a fixed endpoint arc
   that always covers the whole chosen range in 14 frames would silently change
   the native destination/steering rule; the current evidence does not justify it.
3. Preserve destination and source-frame state across room suspension; handle
   stun, death, blocked landing and required cover/pit crossings explicitly.
4. Replace the generic Trite definition only after a dedicated controller and
   external parameters exist. Add source HP scaling, deliberate habitat pools,
   behavioral/terrain/capacity tests and Linux/WASM appearance/reachability checks.
5. Continue Eggy with its required Swarm Spider offspring, Tainted Hopper and
   Leapers. Keep bosses behind the regular-enemy work as the user requested.

No runtime files were changed by this research step. The original Mushroom
checkpoint and all of its acceptance limits remain intact.
