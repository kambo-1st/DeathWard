# Tainted Hopper 29.3.0 — source preflight

This is preserved research for the next regular-enemy slice. **No dedicated
Tainted Hopper runtime has been implemented by this preflight.** The validated
runtime checkpoint remains [Eggy](../eggy/checkpoint.json). The existing generic
Hop/Ring definition is still unverified.

## Identity and placement

Installed Repentance 1.7.9b names the record `Ultra Hopper` internally and uses
`#TAINTED_HOPPER` for display. It is a non-boss, non-champion regular enemy with
80 base HP, zero stage HP, contact damage2, collision radius18, mass20 and
**shieldStrength30**. The archived
[Hopper article revision267012](wiki-source.json) calls it Tainted Hopper.
Its six positive-weight source room templates occur only in the Ascent library.
Any ordinary late-expedition pool is therefore a deliberate DeathWard adaptation,
not a claim that it appears throughout normal Isaac floors.

## Extracted normal hostile controller

[The source manifest](source/manifest.json) pins twelve instruction windows,
the installed executable hash, dispatch tables, constants and animation names.
The [animation manifest](animations/manifest.json) pins the installed DLC3 ANM2
metadata without importing sprite artwork.

- Type29 routes to the shared Hopper controller at `514450`.
- Variant3 sets the ordinary idle threshold to26 source frames at `514902`.
  Unlike Trite and Flaming Hopper, it uses zero random movement bonus. The
  acquisition range is130 native units and wandering distance95. Normal target
  selection, clamping, grid snapping, inertia and post-animation release rules
  otherwise use the common controller already reviewed for Trite/Eggy.
- The phase at entity`+b10` selects `Idle`/`Hop` on even phases and
  `Idle2`/`Hop2` on odd phases. Both Hop animations last23 frames, with Jump4
  and Land17, at30Hz.
- The current Land event emits a ring using the **old** phase number, before
  advancing it. The first three Land events increment the phase, clear the
  destination and return to idle with counter9999. The next valid destination
  starts the next Hop at frame4, skipping preparation. The fourth Land resets
  the phase to0 and lets the current animation/recovery finish normally.
- Thus this is a four-landing sequence, not one generic radial attack at the
  end of every independent jump. It emits30 bullets across the sequence.
- The accumulated Jump event retains the shared airborne collision classes
  until the Hop ends. Immediate chained hops require a legal local3D landing
  policy; copying the2D state change blindly could strand a body in a rock.

| Phase | Helper mode | Source velocity/count argument | Emission |
| --- | --- | --- | --- |
| 0 | 6 | `(8,0)` | Four cardinal shots at speed8 |
| 1 | 9 | `(10,6)` | Six evenly spaced shots at speed10 |
| 2 | 9 | `(8,8)` | Eight evenly spaced shots at speed8 |
| 3 | 9 | `(10,12)` | Twelve evenly spaced shots at speed10 |

The phase jump table at `516ddc` resolves these four call sites. The projectile
mode table at `6a33ec` resolves mode6 to `6a269d`, which emits the cardinal cross,
and mode9 to `6a2e74`, which derives count from the second component and emits
successive angles spaced by2π/count. Tainted Hopper explicitly sets the ring
angle field to0, so these rings are not randomly rotated or aimed at the player.
“Increasing size” in the article refers to increasing projectile count; the
measured speed is **8,10,8,10**, not a monotonic speed increase.

The projectile parameters also set byte`+98` to1, field`+18` to0 (ring angle),
and field`+c` to approximately−.07. The helper uses the last field as an additive
modifier of projectile`+368` (fall acceleration); byte`+98` skips an initial
mode-dependent adjustment. Native initial projectile height/fall values and
the complete resulting travel curve still need review before asserting vertical
parity. An authored flat-projectile adapter must be explicitly labelled if used.

The landing calls `68d7b0` with scale1; that helper creates effect1000.7. The call
does not establish a damaging area explosion. The separate grid marker900 call
does not by itself establish obstacle destruction either. Do not invent bomb
damage, rock destruction or slowing creep from these visual calls.

## Armor is required follow-up

`shieldStrength30` is not extra HP or a flat damage reduction. The preserved
Damage Scaling article revision271609 describes adaptive incoming-damage history,
initial protection and source-specific bypasses, including explosive exceptions.
Its archive is saved separately as [armor-wiki-source.json](armor-wiki-source.json).
The exact installed normal-hostile armor path must be traced and tested before
claiming Tainted Hopper vulnerability parity. This reusable work also matters to
other regular Tainted enemies already marked partial. Keep it in the regular-enemy
queue; it does not justify switching to more boss implementations.

## Implementation contract to validate

Use external source-frame timing and a reusable landing-ring sequence, with
explicit3D landing and projectile adapters. Retain the four-stage phase across
room suspension. Check stun, lethal interruption, event/projectile-capacity
handling, exact4/6/8/12 counts and8/10/8/10 speeds, cardinal alignment, no invented
offspring, one ordinary completion event, cover/water navigation, and source80HP
before the established local conversion. Contact2 requires the full-heart local
damage conversion rather than the existing half-heart default.

Validate an authored late-floor natural encounter, Linux/WASM visuals showing
the alternating twist, starting-kit balance and controlled performance. Keep
Original style, the100HP/default-damage protagonist, Mine roster, hubs, tutorial
and4–8-floor expeditions. Tainted Hopper remains `existing_unverified` until
an implementation has evidence; this research alone must not increment status.
