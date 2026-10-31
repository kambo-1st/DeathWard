# Mr. Maw family — source contract and implementation in progress

This family covers body35.0, head35.1, red body35.2, red head35.3 and
neck35.10. Runtime changes are under validation; no six-gate completion is
claimed. The preceding frozen checkpoint remains [Brain](../brain/checkpoint.json).

The installed Repentance1.7.9b executable is SHA-256
`04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.
The [native windows](source/manifest.json) and five [animation metadata files](animations/manifest.json)
are reproducible with `python3 scripts/isaac-reference/analyze-mr-maw.py --check`.
Highest available archive precedence finds all five in `afterbirthp.a`.
No source sprite artwork is imported into DeathWard.

[Source discovery](source-discovery.json) preserves XML/room evidence and wiki
revision269831, by The Binding of Isaac: Rebirth Wiki contributors under
CC BY-SA4.0. The article supports pursuit, head launching, separation, the two
survivor types and the red head's cardinal death shots. Native details below
come from the installed binary, not a claim that public mod API code contains
the original game implementation.

## Construction and health

Type35 selects dispatch index20, case6999f8, controller506130. On initialization,
body variant0/2 spawns variant1/3 at the same position, makes reciprocal parent/
child links and creates eight neck entities35.10 with indices0..7.
Head collision class2 is PLAYEROBJECTS; grid collision3 is WALLS (the preserved
`enums.lua` confirms these meanings). The neck has entity collision0, no grid
collision points, no independent room-completion obligation and is hidden
outside the body's attack state8. Missing/incompatible ownership removes it.

XML HP: bodies25, ordinary head25, red head10, neck25; all stageHP0. The
project's established x3.2 conversion gives80/80/32 for the damageable parts.
All damageable parts have collisionDamage1, converted to base10 and then the
existing hostile multiplier1.25. The neck's nominal XML damage does not override
its explicit native collision disable. Its nominal HP is not an additional
damageable health pool in the ordinary encounter.

Body animations `MrMawBodyHori` and `MrMawBodyVert` loop22 frames at30FPS.
Heads have a two-frame Down pose, neck a two-frame NeckSegment pose; none has
an attack event trigger. The four main parts also have Appear20 metadata.

## Pursuit and head attack

The ordinary ready body calls FindGridPath with speed.6, the red body with.8;
both use path marker900 and the final true flag. The common ordinary path-force
tail at7a4737 multiplies speed by min(distance*.1,2), changes friction by.7,
then adds the normalized force divided by that friction. Combined with the base
movement pass, unit-speed motion is `.7v + direction*speed*min(d*.1,2)`.
At distance<=1 it instead changes friction by.5. Failed direction lookup uses
.85. Path-cache/status/control branches are not equivalent to the local 3D
navigation and need to remain explicit adaptations.

In body state4, the head is carried by assigning velocity to
`body.position + body.velocity - head.position`. In attack state8 the ordinary
uncontrolled body coasts with.7 friction. Controlled actors have separate
movement branches (.3/.4 speeds); these are not ordinary hostile AI.

The head decrements the body's timer by elapsed integer source ticks, clamped
to-30. While the body is ready, acquisition is a **global4-frame staggered
check**, not random cooldown. It predicts target position by target velocity*3,
requires predicted squared distance<16900 (range130), a nonzero direction,
and a line check toward the current target. Source status mask0x1000a00 blocks
acquisition. The launch sets head speed14, body timer30, body state8. There is
no separate animation windup in this path.

Return steering uses the body's current position, not a new player target.
When distance<5 and body timer<15, the body returns to state4. Otherwise:

```
spring = 1.4 - .7 * clamp((timer + 30) / 45, 0, 1)
retention = .9 + .0028 * timer
velocity' = (velocity + directionToBody * spring) * retention
```

The multiplication applies to **both** old momentum and spring: the source
adds the spring first, then changes friction. This differs from the body path
tail. At zero distance the source returns without applying this spring branch.
The native timer does not gate acquisition as a conventional cooldown.

## Death and voluntary separation

Every ordinary head update checks RNG modulo1000. A zero result separates
uncontrolled owners, independently of attack progress. Controlled ownership
suppresses this spontaneous branch. The separate modulo10 shake helper is a
visual source branch, not the separation chance.

- Body death morphs the existing linked head into26.0 or26.1 and explicitly
  resets it to its new maximum HP. It does **not** create another Gusher.
- Head death morphs the existing body into11.0 (Gusher), resets its HP to the new
  maximum and changes its tint. Red head death additionally emits the native
  mode6 cardinal volley at speed8, locally24.
- Voluntary separation morphs both existing actors: body to11.0, head to26.0/1.
  It does not score kills or emit the red death volley.
- A head without a parent becomes the corresponding26.x; a body without its
  child becomes11.0. Neck pieces disappear when their owner is no longer type35.
- Morph explicitly restores HP here; retaining the damaged part's old fraction
  would contradict the controller writes after697c60.

The source red-head death also morphs that dying actor before ordinary death
cleanup. Local death keeps its old ID while delivering a retained death packet;
the surviving actor is transformed immediately before room completion checks.

## DeathWard implementation and remaining verification

`linked_heads.mechanics` supplies identities, health, movement, attack timers,
spring constants, separation probability, neck dimensions and death shots.
The dedicated controller replaces the generic Orbit/Head approximation.
Bodies and heads have independent HP and linked lifetime; eight harmless cord
points live in the head runtime instead of eight separately allocated enemy
objects. The shared35.10 registry identity cannot be independently spawned.
This preserves the required component role without charging eight extra threat
slots or exposing decorative pieces to damage/item rewards.

Distance scale.1 and30Hz decisions follow the existing source-controller adapter.
Native path grids are replaced by canyon collision/path queries. Stable local
entity IDs supply the global-frame stagger. Source-owned-head motion uses the
existing flight/collision layer; small scenery and pits follow that layer's
rules. Original procedural low-poly art remains, with a separate floating head
and eight visible cord beads. A curved 3D cord and.65 head lift replace source
screen-space neck offsets/sag; this is a visual adaptation, not pixel equality.

Required births and red death volleys are retained under capacity pressure.
Pending births and volleys prevent premature room completion. This differs from
unbounded source allocation but must never discard a survivor silently. A body
whose head is pending remains still until that part can be allocated.

Native status/charm/control, exact global RNG ordering, source appearance
activation, source shake/tint behavior, exact path-cache response, and collision
activation across source morph/death ordering still need review. Gusher uses its
existing configured behavior on release; this family does not certify that
separate controller. Seven generated populations pass on Linux and WASM; focused
behavior and four starting-kit fights also pass. The [checkpoint](checkpoint.json)
and [validation summaries](README.md) preserve the exact scope. Full visual
readability, broader balance and controlled performance remain open.
