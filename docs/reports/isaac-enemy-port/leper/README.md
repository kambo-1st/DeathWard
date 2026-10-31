# Leper family: source investigation and Flesh controller

**Historical checkpoint:** the parent gaps described below were subsequently
addressed in the [Leper parent slice](../leper-parent/README.md). This report
preserves the earlier investigation and its validation scope; use the parent
slice for current runtime status and roster counts.

Baseline: installed Repentance 1.7.9b. This is a partial family port. The four
parent records, `310.0.0` through `310.0.3`, are still missing from the runtime.
The independent `310.1.0` Leper Flesh controller is implemented; its acceptance
evidence and remaining gaps are recorded separately from the parent work.

## Reproducible evidence

- `source/records.json`: five exact XML/reference records, including source room
  presence. Flesh occurs in **two positive-weight Scarred Womb templates**. It
  is both a natural resident and offspring, so classifying it as owner-only was
  incorrect. The four parent subtypes occur in 17, 48, 63 and 40 such templates.
- `source/wiki-source.json`: retained Mulligan article, revision 271647. The
  attempted fresh retrieval during this investigation failed; no newly fetched
  wiki evidence is claimed.
- `source/manifest.json`: executable digest, bounded native functions, selected
  shared-update windows, constants and hashes of reused helper evidence.
- `animations/manifest.json`: five extracted animation metadata files. No Isaac
  sprite art is imported into DeathWard.

Reproduce with `python3 scripts/isaac-reference/analyze-leper.py --check` and
`python3 scripts/isaac-reference/extract-leper-animations.py --check`.

## Flesh behavior

Native state zero selects one of six Idle animations and a horizontal flip from
the entity seed. It sets the kill-on-player-contact flag and enters state four.
The first source frame initializes rather than steering. Subsequent 30 Hz
frames add `.15 * (unit direction to target + 2 * random unit direction)` to
velocity. The ordinary entity update then applies `.95` friction to **the whole
result**, including that impulse. This differs from a constant-speed chaser or
applying friction only to the old velocity.

The source's `gridCollision=walls` allows movement across internal obstacles and
pits. DeathWard uses its existing floating navigation: actual canyon boundaries
and closed gates block it, while interior cover raises its rendered/collision
height. This height adaptation prevents it disappearing inside 3D rocks. It does
not imply the source has the same vertical movement. Native HP is `5` plus the
standard `1.5` stage-HP term, converted at `3.2`; stage one therefore gives
20.8 HP and source stage seven gives 42.88 HP. Contact damage is 10 before the
existing game-wide hostile multiplier.

Touching the player consumes the flesh even if the player cannot take damage.
Ordinary damage, overkill and contact consumption all produce one death shot;
debug room clearing suppresses it. Its target is player position plus player
velocity per native frame multiplied by `.1 * native distance`. The planar
launch speed is 10 native units. The native shot uses mode zero's default
falling speed `-3` and acceleration `.1`; the `.3` write near the end of the
controller belongs to the color structure, **not** a gravity override.

The existing DeathWard projectile conversion gives planar speed 30, upward
speed 4.5, gravity 4.5 and launch height 1.15. The projectile uses the existing
`.9` flight-retention treatment. Those world-space conversions and the muted
tissue tint are adaptations, not native pixel/physics equivalence. Blood every
ten source frames and droplets every six are cosmetic; neither is a live attack
nor damaging creep. Six low-poly flesh silhouettes and a subtle 24-frame pulse
replace the source sprites in the Original visual style.

The selected death shot is retained when event/projectile capacity is full.
Room completion waits for that retained attack and its eventual flight. A
contact death request also survives temporary event admission failure. The
external `assets/mechanics/leper.mechanics` file controls steering, cadence,
health, projectile parameters and late-band placement. Reload uses the existing
immutable mechanics snapshots.

## Parent findings and unfinished work

The parent has four forms with native base HP 60, 45, 30 and 15. Form zero has
no contact damage; later forms do. Its state machine alternates evasion and
limited pursuit, except the last form always pursues. Chase forces are `.5`,
`.5`, `.7`, `.9`; each form change plays a nine-frame Transition. The last form
leaves small, short-lived damaging red creep.

Do **not** implement the shorthand “lose a piece every 15 HP” without resolving
the native update order. The controller predicts current HP minus queued damage
and compares it with `(3 - subtype) * maxHP / (4 - subtype)`. It increments the
subtype and emits flesh in a loop, using the same maxHP throughout that loop.
Only afterward does it call Morph, whose shared helper reloads maxHP and clamps
current HP. `68b970`, called inside the loop, is a damage-reaction helper rather
than the configuration reset previously suspected. General queued subtraction
occurs in the common entity update. The exact multi-hit/morph ordering needs its
own tests before the parent can be counted as implemented.

Final parent death always emits another flesh chunk. A successful 50% branch
above the strict native `-25` residual-HP cutoff morphs the **same entity** into
a gray Gusher, restores its HP and assigns a 20–39-frame timer. It must not pay
an extra kill or loot, allocate an unrelated Gusher, or lose reserved flesh.
State inheritance across a simultaneous form transition remains to be resolved.

The historical `*-preflight.asm` files are preserved for provenance. The manifest
explicitly identifies their incomplete or misaligned ranges. They must not be
mistaken for complete, authoritative function boundaries.

## Limits

The Flesh implementation does not finish the parent family. Source champion,
status/control interactions, exact native collision response and serialized
state parity remain open. Natural template presence justifies eligibility, not
an equivalent source spawn probability; the sparse final-band weight and cap
are DeathWard balancing decisions. Scoped Linux checks and screenshots are not
full visual, balance or performance acceptance. WASM validation is waived by the
user and remains skipped.
