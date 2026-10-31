# Guts family: installed source review and first implementation

This batch covers ordinary Guts `40.0.0`, Scarred Guts `40.1.0`, and Slog
`40.2.0`. They are separate, damageable room threats. No owned component is
required. Mama Guts may produce ordinary Guts, but implementing this offspring
does not certify Mama Guts. Cyst `862.0.0` shares the native controller and needs
its own later attack review. None of these records is a completed six-gate port.

The previous goal turn was a user-requested status check: **no implementation
progress**. Its checklist hashes still matched the Chubber checkpoint. This
turn resumed source review, extracted new evidence and replaced the three
generic wall followers. Prior Chubber and Vis evidence remains historical.

## Preserved evidence

`python3 scripts/isaac-reference/analyze-guts.py --check` verifies the installed
executable SHA-256, dispatcher entries, four instruction windows, constants,
direction table and three highest-DLC animation files. The exports are in
[source/manifest.json](source/manifest.json) and
[animations/manifest.json](animations/manifest.json). No Isaac artwork is loaded
into DeathWard. Preliminary XML, room-library evidence and the preserved
[Guts article, revision 266739](https://bindingofisaacrebirth.wiki.gg/index.php?oldid=266739)
are retained in `source-discovery.json`.

The main NPC dispatch compresses type40 and type862 to index24, then enters
`69a26b`, calling `5031b0`. An adjacent Vis case does **not** establish this
mapping: the jump table was read explicitly. `5031b0..5054da` also handles
other actors; only the type40 branches apply here.

XML health is25/28/28, with zero stage growth, collision damage1 and collision
radius13. The existing local HP conversion3.2 gives80/89.6/89.6. Original local
model/hit radii remain. Native subtype-directed initial headings are outside
these three subtype0 records.

## Locomotion and charging

The source direction table is down/right/up/left. Initial state sets direction
to−1 and Slog's charge cooldown to60. Initial heading searches the four adjacent
40-unit cells for obstruction, falling back to a random cardinal heading.
The contour rule checks a rear-side cell and side cell, turns around outside
corners, and turns the other way when blocked ahead. Destroying an obstacle
therefore leaves the actor traveling forward until it finds new terrain.

The controller's force is3 for Guts,3.3 for Scarred Guts and2.45 for Slog.
It applies .6 friction and compensates its force before common physics;
DeathWard expresses the ordinary-axis recurrence as `.6 * velocity + force`
at30Hz. Perpendicular correction uses .4. Roll animations are24frames.
Exact native common-physics phase order, state/status multipliers, collision
cell costs and RNG consumption still need further comparison.

Slog predicts target movement five source frames ahead. The alignment helper
requires matching grid row or column, different cells, and unblocked
intermediate cells. The source first clips the predicted target against room
geometry. DeathWard currently checks the predicted target directly with sight
and ground clearance; native prediction clipping remains an explicit gap.

`ChargeStart` lasts6frames, `ChargeLoop`8, and both directional impact
animations11. During the warning, the movement multiplier loses .1 per source
frame, with a .1 minimum. Charge commits a cardinal direction and uses
multiplier1.8. Impact ends the charge, resets cooldown60, and lowers the
multiplier to .1; ordinary recovery restores .05 per frame. The local controller
ends charge at actual swept geometry collision, rather than at a coarse grid
cell boundary. The source also emits cosmetic dark particles behind a charge;
that cosmetic emission is not yet reproduced.

## Trails

The native global-frame-plus-entity-index cadence is every2frames for Scarred
Guts, every4 for rolling Slog, and everyframe for charging Slog. Effect22 has
lifetime20frames; effect26 has lifetime150. These are separate from the harmless
fade. Ordinary Guts makes no damaging trail.

DeathWard uses existing red-creep and tar hazards. Red creep's base damage10
becomes12.5 after the existing combat multiplier. Tar slows without damage.
The .75 local footprint, 40-frame harmless shrink, and existing tar speed
reduction are explicit local adaptations; effect collision-size and slowdown
parity are not certified. Trail persists after owner death; room clearance
starts harmless fading. One due emission is retained when hazard capacity is
full, pausing that actor until the footprint can be emitted.

## Canyon adaptation and placement

The new external `guts`, `guts_charge`, and `guts_creep` profiles live in
`assets/mechanics/guts.mechanics`. Reload produces a new immutable library.
Invalid forces, friction, ranges, lifetimes and incomplete charge/trail profiles
are rejected. The controller operates against radius-aware continuous canyon
geometry, including obstacles, doors and water, with clipped approach targets.
It does not teleport to a native cell hidden inside rock. This is a deliberate
navigation adaptation, not an assertion of identical native paths.

Source positive-weight room templates place Guts in Depths through Womb,
Scarred Guts in Womb/Scarred Womb, and Slog specifically in Dank Depths.
Local routes are Guts bands2–3, Scarred Guts band3, and Slog band2 in the Dank
context. Two appended encounter contexts map to Seeping Works and Scarred
Storm Cut; both retain Original rendering. Authored selection weights are
2standard:1variant, not inferred source probabilities. The source's50% Guts
replacement applies only to the Scarred context. Direct Scarred placement is
also justified by the Womb room library. No family member enters bands0–1.

## Acceptance still open

The final [native contracts](native-contracts.txt) pass for all three variants,
including force/retention, perpendicular correction,30/120Hz movement, all four
sides of an interior rock, removal of an anchor, six-frame charge warning,
committed heading, wall impact/recovery, creep harm/slow/fade, stun, retained
capacity emissions, five invalid profiles and actual seeded residents.
[Six regression suites](native-regression.txt) also pass: mechanics content,
catalog behavior, replacements, floor progression, Vis and Chubber. Together
these are seven scoped suites, not the entire92-suite native registration.

The production WASM build passes [seven browser cases](web/results.json): three
isolated variants, Slog on river terrain, and three real seeded populations.
The natural witnesses are Guts seed7/floor3/room3, Scarred Guts9/6/5 and Slog19/3/3
(zero-based floor/room). The browser uses hardware-backed ANGLE/D3D12 and checks
Original style, GL errors, legal ground, health, actual movement, trails,
context selection and Slog's acquired charge/wall recovery. The earlier failed
run is retained in `web-initial/`: a stationary invulnerable spectator physically
pinned Slog, so its charge could not reach terrain. The corrected test moves
that spectator aside at frame150, after windup. Runtime stopping rules were not
changed to make that test pass. Ordinary player/NPC collision parity remains
an unresolved cross-cutting requirement.

Eleven captures were inspected (three Linux, eight browser). Bodies, red trails,
tar trails and the yellow charge warning are visible. Native frame180 captures
show the body partly overlapping the spectator; the initial browser charge
capture similarly shows the pinned state, while the impact capture shows its
subsequent trip to the wall. The naturally generated Slog warning/charge views
and river view show actual traversal away from that fixture. Slog loses contrast
against dark cliff shadows, and some foreground terrain obscures actors. The
warning is short; these captures do not establish all-angle readability. The
impact timer is represented in runtime but does not yet have a distinct squash
pose. Screenshot FPS labels are not controlled performance measurements.

Further work includes
native timing/collision comparison, status/charm/control interactions, Strange
Attractor immunity when that item exists, source effect sizing, generated-room
readability, broader Linux/WASM render checks, default-player balance and controlled
performance. The full653-record goal remains active, with regular enemies first.
