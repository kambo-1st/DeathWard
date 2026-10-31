# Prey and Small Leech — regular enemy slice

This work follows the user's priority: regular enemies before further boss work.
It covers **817.0.0 Prey** and its required child **810.0.0 Small Leech** against
installed Repentance 1.7.9b. Both remain partial ports until all six acceptance
gates are closed. No hub, player-default, Mine-roster or visual-style change is
intended. Earlier checkpoints are immutable.

## Source and behavior

The [native source manifest](source/manifest.json) preserves seven disassembly
windows, exact executable hash, dispatch targets and checked float constants.
The [animation manifest](animations/manifest.json) preserves both installed
ANM2 files and events without importing sprite artwork. [XML and room data](records.json)
and [pinned wiki articles](wiki-source.json) are also retained. The wiki is a
secondary description; installed code resolves its abbreviated death-count and
movement descriptions. Initial extraction/build failures are retained alongside
corrected results, rather than erased.

Prey uses the shared Hive evasion controller, an 18-frame head attack with a
Shoot event at frame 4, and a 75-frame cooldown subject to room population.
Its live offspring are full-health Small Leeches without the Hive's disposable
fly contact flag. The body is harmless and has 44.8 local HP (14 × 3.2).

Death count is `max(1, ceil(4 / (1 + 0.2 × population)) - 1)` for the native
zero counter case: three when alone, two with two other actors, one with five.
Post-hit HP at or below −64 suppresses births. Death children start at the
parent, airborne. Initial source height −10, vertical velocity −8, gravity
+0.7 per source update and planar velocity `0.04 × (target − origin)` come
from the installed controller/helper. The initial exporter asserted 0.05 and
correctly failed; direct byte inspection established **0.04** before runtime
configuration and final preservation. Landing occurs after 23 source updates
with these values. Airborne births have no projectile/body contact collision;
area damage remains possible. Reserved births retain room completion until
admitted, and living offspring remain threats.

Small Leeches have 16 local HP (5 × 3.2). Wet movement accelerates by 0.016
per 30 Hz update to a 0.35 force cap, retains 0.96 momentum and caps speed at
10 source units/update. Outward room-edge velocity bounces by −0.6; margins
are source X 10, top 20, bottom 4, constrained by the physical body radius.
Dry movement damps by 0.7 and has a 1/2 chance to begin a hop per ready
update. Impulse is 2–4 source units toward the target, coasting until the
Land event at frame 6 and returning to ready at frame 10. This dry hop is
an animated grounded body, distinct from the thrown birth state.

## DeathWard adaptations and limits

- Source HP × 3.2, distances × 0.1 and 30 Hz source velocities × 3 preserve
  existing player defaults. Half-heart contact maps to 10 before the existing
  1.25 enemy-damage multiplier. No new global difficulty multiplier is applied.
- Wet rooms include authored flooded rooms and rooms crossed by an interior
  river. Swimming bypasses water but preserves rocks, walls, gates, room edges
  and raised terrain. This is a room-wide wet policy, not a water-depth check
  on each actor; it adapts Isaac's room wet-state field.
- Thrown targets use a bounded local free-point search and scatter instead of
  importing Isaac's grid. The entire 3D arc and actual landing are validated
  before admission. A vertical fallback can work in tight spaces; otherwise
  the birth remains pending. Physical 3D cover may reject an arc that Isaac's
  walls-only sprite flight would permit. Exact source free-point distribution
  and late dynamic geometry changes are not certified.
- Grounded dry hops use a small local visual lift while keeping ground collision.
  Existing Original-style worm/walker silhouettes remain; source sprite/art
  parity is not claimed.
- Native nonzero death counter `NPC+bc6`, friendly/owner-orbit behavior,
  fear/confusion, champions, subtype 1 and complete item/status/time-scale
  interactions remain open. Shared Hive grid-path equivalence remains open.
- Both regular identities enter sparse wet band-1 pursuit pools (Broken Quarry),
  based on Downpour/Dross presence; Prey also occurs in Flooded Caves source
  rooms. Weights, costs and local scales require broader balance acceptance.

## Validation

All **69 native suites pass** in [CTest](native.xml), including the focused
[Prey/Small Leech fixture](behavior-final.txt). All **eight WASM cases pass**
in [the browser report](web/results.json), with no browser or GL errors.
The [visual review](visual-review.json) records selected inspected Original-style
Linux and WASM captures and its limits. The two production witnesses are
Small Leech seed 41/floor 2/room 7 and Prey seed 119/floor 2/room 3.
These are zero-based floor/room indices. All 5,480 earlier report artifacts were
hash-verified unchanged. No complete behavior, balance or controlled performance
acceptance is claimed; both records remain **in progress**.

