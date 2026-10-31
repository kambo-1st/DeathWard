# Host-family source review — Repentance 1.7.9b

This is a partial regular-enemy implementation, not a completed parity claim.
The installed executable is pinned by SHA-256 in `source/manifest.json`.
`analyze-hosts.py --check` verifies dispatch, controller windows and constants.
Six animation/event metadata files have verified archive hashes and entry CRCs.
No source artwork is imported. The archived Host article (revision 270008)
covers the stationary, mobile and floating variants in one article.

| Identity | Source HP | Local HP | Open / Shoot / Close / End |
| --- | ---: | ---: | --- |
| 27.0 Host | 14 | 44.8 | 9 / 24 / 55 / 61 |
| 27.1 Red Host | 15 | 48 | 9 / 24 / 55 / 61 |
| 204.0 Mobile Host | 14 | 44.8 | 10 / 24 / 53 / 61 |
| 247.0 Flesh Mobile Host | 27 | 86.4 | 10 / 24 / 53 / 61 |
| 859.0 Floast | 20 | 64 | 10 / 24 / 54 / 63 |
| 27.3 Hard Host, research only | 15 | legacy value retained | 10 / slam54 / close54 / 71 |

Host27 and Floast859 dispatch to `4ff200–500132`; Mobile204 and Flesh247
share `51f510–52002d`. The former's armored predicate excludes variant1 and
subtype99; the latter excludes Flesh247 and subtype99. Only the five exact
ordinary tuples above are implemented here. Hard Host remains its previous,
unverified implementation: its aimed rock shockwave, obstacle destruction and
nearby knockback must replace its generic projectile attack in a later slice.
Mushroom300 has a different controller and is outside this slice.

Armor rejects damage before Open/Destructible and after Close/Invincible,
not merely outside a generic windup state. Damage flag `0x8000` is
**POISON_BURN**, verified against the public API flag table preserved here;
it is not INVINCIBLE. DeathWard's existing Burning channel bypasses armor.
Direct Flame and explosions do not. Poison, booger-tear and spike channels
are not represented by this port. In native closed idle, blocked damage is
summed for the update, rounded with `int(total+.5)/2`, added to the opening
delay and capped at10. It decays on seven-frame checks. Damage during the
attack does not add this idle delay. Blocked damage above20 plays Shake.
The associated native squash field is preserved as a visual approximation,
not an exact animation implementation. Stationary Host and Red Host have
**zero contact damage**; the mobile and floating bodies have contact damage.

Stationary acquisition uses global/entity seven-frame cadence, strict
240-source-unit range and line of sight. After acquisition, the cooldown is
7 idle cadence counts; it does not decrease during the61/63-frame attack.
Mobile acquisition additionally rolls1/3. Its cooldown70 decreases every
attack frame, then only on accepted idle rolls, and still needs the
seven-frame acquisition gate. Mobile's hit-delay decay uses actor age.
Shots aim at the current player at Shoot24, even after acquisition range
has been exceeded. The source status/control/friendly branches remain open.

FireProjectiles mode2 creates a center shot and two sides with forward/side
coefficients `.961*.9, ±.276*.9`; mode5 creates center plus pairs
`.978, ±.208` and `.914, ±.407`. These vectors are **not normalized** to equal
speed. The common mode2/5 post-pass multiplies velocity1.2 and adds `.4`
parent velocity. Host then applies VelocityMulti1.07, making its center
speed `7*30*.1*1.2*1.07=26.964`. Mobile's multiplier is1, giving25.2.
Floast sets the skip-common flag and VelocityMulti1.2: also25.2, without
inherited movement. The property binding and post-pass are preserved in
`source/projectile-bindings.json` and `source/fire_projectiles.asm`.
Source falling-speed/height/acceleration modifiers are not reproduced:
DeathWard uses physical combat-plane shots with a local five-second lifetime.

Floast keeps diagonal signed-axis acceleration `.55` and retention `.9`
even while attacking; physical wall collisions reflect the blocked axis.
Mobile uses the local collision-aware path solver. The native clear-path
helper's force is `.5*min(sourceDistance*.1,2)` with helper retention`.7`,
followed by controller retention`.8`. The port expresses the combined
retention`.56` and maximum net impulse`.8`, tapering within two world units.
Attack motion coasts with retention`.5`. Exact cell-cost steering, path
staleness, native collision response and obstructed-cell slowing differ.
Distances use the established x.1 conversion; velocities use x3 at30Hz.

All five are room threats with ordinary death/completion behavior and no
required offspring. Partial volleys are never silently dropped: the whole
cast waits at its Shoot event when event/projectile capacity is exhausted.
Stun cancels the cast and closes armor; this is an explicit local adaptation.
Room suspension preserves the actor's animation/cooldown/delay state.
The new bodies use original procedural skull/flesh forms with exposed stems,
walking legs and a floating silhouette, in the existing Original renderer.

The installed room libraries place the first four from Caves onward, and
Floast in Utero/Corpse. The port uses authored specialist pools in bands1–3
and Floast in band3, with one of each per room. Native room templates,
replacement probabilities and exact stage alternatives are not reproduced.
Tutorial, Mine, hub, player defaults and expedition floor counts are unchanged.

Remaining acceptance: Hard Host and Mushroom; native status/champion/control
branches, subtype99/Bracelet transformations and grimace interactions;
poison/booger/spike/crush distinctions; exact projectile height/lifetime,
grid/RNG parity; full combat readability, balance and controlled Linux/WASM
performance. The supplied normal-state tests and captures only establish
partial evidence for those six acceptance gates.
