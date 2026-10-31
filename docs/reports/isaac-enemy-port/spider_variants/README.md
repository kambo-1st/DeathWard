# Strider and Swarm Spider — regular enemy slice

This slice follows the regular-enemy priority and covers **814.0.0 Strider**
and **884.0.0 Swarm Spider**. Both remain in progress against installed
Repentance 1.7.9b. Original visuals and the existing player, hubs, Mine roster,
tutorial and multi-floor expedition structure are retained.

The [native manifest](source/manifest.json) preserves both dispatch entries,
controllers, Strider facing helper and checked constants. [Animation metadata](animations/manifest.json),
[XML/habitats](records.json) and the [pinned Spider article](wiki-source.json)
are retained. The [source review](source-review.json) distinguishes recovered
behavior, local adaptations, corrections and unfinished branches.

Strider uses 20-frame rowing strokes with one impulse at frame 6. It either
tracks the player's current direction or keeps a wandering direction. Each
stroke adds source speed 6–9; velocity retains 95% per update. Its body can
cross impassable river water, while solid rocks and room boundaries constrain it.
It has 20.8 local HP.

Swarm Spider selects short, medium or long hops according to player distance.
Their event schedules are 10/Jump2/Land8, 12/Jump3/Land9 and 18/Jump4/Land14.
The launch vector is committed before takeoff. Nearby spiders always turn
sideways or backward before angular jitter; distant spiders favor long hops.
Ground retention is 70%, while the airborne phase retains its launch velocity.
The hop uses a visual lift with ground collision, matching the native controller's
unchanged grid mode. It has scaled source HP 4.5 plus stage HP 0.2.

Swarm's source player-objects collision allows enemy bodies to overlap and
prevents fireplace-body damage. It remains vulnerable to bullets, bombs,
player flames and burning. The interaction test exposed and fixed an older
fireplace contact bug: temporary contact hazards inherited a delay of one second
and were tested immediately, so no monster damage occurred. They now use zero delay.

The external `replace_spawn` rule applies wet-floor Spider-to-Strider replacement
to residents and spawned children, including Big Spider death children. Their
health, pending-capacity behavior and outward impulses are preserved. Spawn
rewrites cannot chain or cycle. Swarm appears in sparse pursuit groups of four
across bands 0–2; Strider appears through the wet band-1 replacement.
Actual witnesses are Swarm seed 0/floor 0/room 2 and Strider seed 2/floor 2/room 4
(zero-based floor and room indices).

The 60 Hz physical integration, canyon collision, visual height and procedural
silhouettes are explicit adaptations. Native thrown/player-control/status/item
branches, nonzero-subtype Swarm expansion and its source jump sound remain open,
as do exact grid/RNG/frame parity and broad readability, balance and performance.

## Validation

All **72 unique native suites pass** in the [combined native report](native-results.json).
The [first full run](native.xml) passed 69. Three fixture assumptions were corrected:
stage eligibility now follows all four replacement phases, the Eggy test checks
source-equal Spider/Swarm collision radii, and flying offspring are checked against
the flying collision mask and support height. All three [focused reruns](native-corrected.xml)
pass. Their original failures remain preserved.

The focused [behavior fixture](behavior-final.txt) checks rowing, weighted hop events,
launch commitment, collision, actual fireplace contact, normal fire vulnerability,
wet retained death children, immutable configuration and seeded placement.
All **eight final-build WASM cases pass**, with no browser or GL errors in the
[browser report](web-final/results.json). The initial browser run exposed a cover
fixture that put Strider inside a crate; the corrected fixture starts it outside.
Both reports are retained.

The [visual review](visual-review.json) records **10 inspected final Linux/WASM
captures**. Strider initially inherited short legs that floated with its lifted
body; the corrected long legs reach the ground. Swarm retains smaller artwork,
source-equal collision size and yellow hopping tint. Original style is preserved.
The images include actual seeded rooms. Water occupancy is verified by telemetry,
not inferred from a bank-side screenshot. Incidental FPS displays are not benchmarks.

All **5,721 older report artifacts** are checked unchanged when freezing this
checkpoint. Both records remain in progress: special native branches, full
readability, balance and controlled performance acceptance are still open.
The full goal stays active, with regular enemies and offspring first.

