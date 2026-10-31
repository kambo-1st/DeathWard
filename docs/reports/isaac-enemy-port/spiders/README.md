# Spider and Big Spider — regular enemy slice

This slice prioritizes regular enemies and their required offspring. It covers
**85.0.0 Spider** and **94.0.0 Big Spider** against installed Repentance 1.7.9b.
Both remain **in progress**. Original visuals, player defaults, hubs, the Mine
roster and the existing expedition structure are preserved.

## Evidence

The [native manifest](source/manifest.json) preserves the shared dispatch and
controller, target helper, room clamp, executable hash and checked constants.
[Animation metadata](animations/manifest.json), [XML and room presence](records.json)
and the [pinned Spider wiki](wiki-source.json) are retained. The
[source review](source-review.json) distinguishes recovered rules, local
adaptations and unfinished branches. No source sprite artwork was imported.

## Behavior

Both spiders pause, choose a destination and make a committed burst toward it.
They acquire the player only within a random 100–200 source-unit range with
line of sight, predicting ten source updates of player movement. Otherwise they
try a random 70–110-unit wandering destination with the recovered room margins.
They do not continuously home toward the player during a burst.

The 30 Hz controller accelerates by six source units and retains 60% of velocity
per update. The first two moving updates produce local speeds 10.8 and 17.28.
A burst ends within 14 source units of its destination, or after its counter
expires while movement remains below speed three. The last stopping update
still applies its movement impulse. Ordinary spiders cannot cross impassable water or
solid obstacles. Source HP 6.5 and 20 become local HP 20.8 and 64.

Big Spider produces two ordinary spiders when killed. Their initial positions
and velocities point in opposite directions perpendicular to the player: local
offsets one, speeds 30. Children have full health and remain independent threats.
Post-hit HP at or below −64 suppresses them. Capacity or placement delays retain
the births and keep the room sealed. These are grounded births; the reusable
`offspring_impulse` property is distinct from airborne `offspring_launch`.

Spider pursuit pairs and sparse Big Spider specialists are available in bands
0–2. Actual production witnesses are seed 0/floor 0/room 3 for Spider and seed
71/floor 0/room 1 for Big Spider (zero-based floor and room).

## Adaptations and open work

The source decision clock runs inside DeathWard's 60 Hz movement simulation.
Physical canyon collision, body separation, narrow-room margin clamping,
retained births and local encounter weights are explicit adaptations. Existing
Original procedural legs stop while idle; Big Spider has a larger rear abdomen.
These silhouettes are not exact sprite-animation reproductions.

Native appear and thrown states, Bursting Sack neutrality, friendly/control and
full status/champion interactions remain open. Strider and Swarm Spider have
separate native controllers and are not covered here. Full native grid/timing
parity and broader readability, balance and performance acceptance remain open.

## Validation

All **71 unique native suites pass** in the [combined native report](native-results.json).
The [full run](native.xml) initially passed 69 and exposed two older fixture
assumptions: fixed Mulligan placement seeds and a universal generic attack
cooldown on room entry. Both were corrected and [Mulligan](native-corrected.xml)
and [resident lifecycle](native-residents-corrected.xml) reruns pass. Their
original failures remain preserved. No game runtime changed for these fixes.

The focused [Spider fixture](behavior-final.txt) checks source timing, acceleration,
committed prediction, collision, damage, two-child impulses, capacity/completion,
configuration and seeded reachability. All **eight WASM cases pass** with no
browser or GL errors in the [browser report](web/results.json).

The [visual review](visual-review.json) records nine inspected Linux/WASM
captures, including the two children and actual seeded rooms. A visible water
surface may be a walkable ford; collision correctness comes from fixtures and
telemetry, not a screenshot alone. All **5,646 older report artifacts** were
hash-verified unchanged. Both records remain in progress; the full goal is active.

