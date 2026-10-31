# Hive and Drowned Hive — regular-enemy checkpoint

This slice replaces the generic flee/spawn behavior of **22.0.0 Hive** and
**22.1.0 Drowned Hive** with a shared controller and configurable offspring rules.
It follows the user's priority: regular enemies and their dependencies first.
Further boss/Hornfel expansion remains deferred. These records remain **in
progress**, not certified complete ports.

## Recovered behavior

The installed Repentance 1.7.9b executable, XML and animation metadata establish:

| Rule | Hive | Drowned Hive |
|---|---|---|
| Source HP / DeathWard HP | 20 / 64 | 18 / 57.6 |
| Body contact damage | None | None |
| Ready-state friction | .8 | .8 × .95 |
| Live child | Attack Fly | Drowned Charger, half HP |
| HeadAttack / Shoot event | 18 / 4 source frames | 18 / 4 source frames |
| Cooldown set on acquisition | 75 source frames | 75 source frames |
| Death child selection | Independent Fly/Attack Fly/Pooter, weights 7:3:1 | Half-health Drowned Charger |
| Death count | `ceil(4 / (1 + .2 × room_population))` | Same, capped by a random 1–2 |
| Death suppression | Post-hit HP ≤ -20 source / -64 local | Same |

The 30 Hz controller checks proximity every 14 staggered ticks: visible distance
250 or hidden distance 170 in source units, converted to 25/17 local units.
Three positive checks of evasion memory persist after leaving range. Outside
evasion it wanders. Ordinary attack animation coasts without selecting a new
path. Cooldown only advances during evasion; the source check-before-decrement
order yields 76 ticks between acquisitions in the unobstructed timing fixture.

Spawning is limited by **room-wide population**, not just this Hive's children.
At cooldown expiry, a random threshold of 4–8 actors can add 20–69 retry frames.
Too much distance or blocked sight sets a short 3/7-frame retry.

Each death child gets its own weighted draw; the old grouped outcome could not
reproduce the mixed result. Live-spawned Attack Flies receive contact expiry and
.9 pursuit friction. Death-spawned Attack Flies remain persistent. Both live and
death Drowned Chargers have half normal health, 35.2 in DeathWard.

## Reusable runtime and external files

- [evaders.mechanics](../../../../assets/mechanics/evaders.mechanics) contains
  health, movement/attack values, live-child identity, population thresholds and
  natural placement.
- [deaths.mechanics](../../../../assets/mechanics/deaths.mechanics) adds
  `population_offspring`: budget, population factor, optional random cap and
  child offset radius. Each outcome selects exactly one child.
- [Evaders.cpp](../../../../src/combat/Evaders.cpp) provides the controller.
  [Monsters.cpp](../../../../src/combat/Monsters.cpp) reserves births and retries
  placement without losing the contact policy when the parent disappears.
- [evader_tests.cpp](../../../../tests/evader_tests.cpp) checks timing, global
  population, child health/policy, independent mixtures, overkill, retained
  births, room completion, invalid files and immutable reloads.

When active-body capacity is full, Shoot waits at its event frame. Once reserved,
a birth retries safe placement or capacity on later ticks. Pending births count
for population suppression and keep the room sealed. Reset/debug execution
clears them. The existing four-generation offspring bound remains. This does
not introduce a separately configurable hard limit on retained requests.

Files use the existing immutable content snapshot policy: new expeditions see
reloaded definitions; an existing expedition keeps its original rules.

## Natural placement

Hive is a sparse pursuit specialist in bands 0–2: weight 1, threat cost 3,
maximum one initial Hive per selected room. A band-1 Flooded floor substitutes
Drowned Hive with 50% probability. The source room libraries support the bands;
the pinned wiki supplies the Flooded replacement chance. Local weight, cost and
cap are DeathWard balance choices.

Actual generated witnesses with production content:

| Enemy | Seed | Floor, zero-based | Room | Band |
|---|---:|---:|---:|---:|
| Hive | 9 | 0 | 1 | 0 |
| Hive | 11 | 2 | 2 | 1 |
| Hive | 1 | 4 | 3 | 2 |
| Drowned Hive | 66 | 2 | 1 | 1, Flooded |

There are now 44 directly weighted pool identities and 46 including conditional
I. Blob and Drowned Hive. [Pool audit](pool-audit.json). This is a reachability
count, not a completed-port count.

## Evidence and remaining differences

[Source review](source-review.json), [six preserved disassembly windows](source/manifest.json),
[animation metadata](animations/manifest.json) and the
[pinned wiki attribution](wiki-source.json) preserve the provenance.
`scripts/isaac-reference/analyze-hive.py --check` verifies the installed executable
and saved windows. The source death-count thunk was resolved to imported `ceil`;
assuming integer truncation would undercount the offspring.

The native pathfinder is adapted to physical canyon navigation and body
avoidance. Source initial impulse, diagonal bias, adaptive search and tile-cache
logic are not fully reproduced. The signed native offspring counter at
`NPC+bc6` still needs investigation for nonzero cases; this slice models its
ordinary zero-initialized case. Full charm, friendly, champion, item, time-scale
and appearance-animation behavior remains open.

Holy/Tainted Hive, Mulligan variants, Nest and Prey still require their own
work. Sharing a native function does not certify those records. Broader balance,
all-angle readability and controlled Linux/WASM performance are also pending.
Player defaults, Original visuals, hubs, Mine, tutorial and the 4–8-floor
expedition structure are preserved.

## Validation

All **67 native suites have passing coverage** in the
[coverage manifest](native-coverage.json). The initial [full run](native.xml)
passed 66/67: the old 128-seed fallback missed a Hopper substitution after the
pool expanded. Keeping the 32-seed broad sweep and all assertions, the expanded
512-seed ceiling passed the [focused rerun](native-floor-retry.xml). Spawn chances
and runtime mechanics were unchanged. The [full retry output](floor-retry-full.txt)
finds the Hopper substitution at seed 140, floor 0, room 2, and verifies 46
enabled identities across 341 floors. The [focused Hive behavior log](behavior-final.txt)
also passes, including placement retry after the parent disappears.

All **eight WASM cases pass** without browser/GL errors in the
[browser report](web/results.json). The initial scripted Drowned death hit left
a tiny positive rounding remainder; the test now uses 58 damage. Its
[numeric explanation](browser-test-correction.json), original test/log/results
are retained. This required no runtime change.

[Native Hive](native-hive.png), [native Drowned resident](native-drowned-resident.png),
[browser Hive](web/hive-live.png), [browser Drowned](web/drowned-live.png) and
[browser Drowned resident](web/natural-drowned.png) were inspected. The later
browser resident framing lets the fleeing body pass behind the HUD, so this
does not close all-angle readability. Displayed FPS is not a benchmark.

The [checkpoint](checkpoint.json) freezes runtime, builds, source and evidence.
All 5,303 previously recorded report artifacts remain unchanged.
