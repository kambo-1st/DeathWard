# Mulligan family — regular-enemy checkpoint

This slice replaces the shipped generic type-16 behavior with shared,
configurable controllers for **Mulligan, Mulligoon and Mulliboom**. Regular enemies
and required dependencies remain the priority; additional boss work is deferred.
These three records remain **in progress**, with explicit parity gaps below.

| Rule | Mulligan | Mulligoon | Mulliboom |
|---|---|---|---|
| Source HP / local HP | 13 / 41.6 | 13 / 41.6 | 13 / 41.6 |
| Body contact damage | None | None | None |
| Movement | Flee / wander | Flee / wander | Chase |
| Voluntary explosion | Grid collision, 1/300 check | Same | Within source distance 40, checked every 5 frames |
| Windup | 29 source frames | 29 source frames | Immediate |
| Ordinary death | Four independently chosen flies | Four diagonal shots and Troll Bomb | Immediate blast |
| Voluntary death | Four cardinal shots, blast and children | Eight shots, blast and Troll Bomb | Immediate blast |

Source timing runs at 30 Hz. The fleeing variants no longer use a fixed-age
self-detonation trigger. The installed Lua binding proves the tested native
field is `CollidesWithGrid`. Mulliboom's explicit squared-distance test is 1600;
that becomes four local units, rather than literal body-overlap contact.

Each ordinary Mulligan child independently chooses Fly, Attack Fly or Pooter
with weights **7:3:1**. There is no Hive-style population denominator. Post-hit
health at or below -32 suppresses births, scaling the source -10 threshold by
3.2. Death-spawned Attack Flies remain persistent. The ordinary zero-initialized
native offspring counter is modeled; nonzero cases remain unresolved.

Immediate blasts use source damage 40 and radius 60, converted to 128 damage
and six local units. They damage nearby enemies and destroy eligible rocks.
Player damage is 10 before DeathWard's existing 1.25 enemy multiplier. Mulligoon
also drops a real type-4.3 Troll Bomb with source damage 100, converted to 320,
7.5-unit radius and player damage 20 before the multiplier. Its source initialized
count is 45–74. Converting that to a 1.5–2.467-second fuse is **provisional**;
source appearance and animation-driven countdown still need recovery.

The complete death payload reserves capacity together. If bullets, bombs or
events cannot be admitted, the defeated body retains its pending work and the
room stays sealed. Recovery releases the payload once. A placed Troll Bomb
survives its producer and room clear. These are explicit bounded-runtime policies.

## External configuration and floor placement

[mulligans.mechanics](../../../../assets/mechanics/mulligans.mechanics) exposes
body movement, detonation chance/timing, chase proximity, death rings/blasts,
Troll Bomb fuse variation, and stage placement. Existing immutable snapshot
rules apply: loading new content does not alter a running expedition.
[deaths.mechanics](../../../../assets/mechanics/deaths.mechanics) owns offspring.

Mulligan is an opening-band pursuit specialist. Phase zero can replace it with
Mulligoon at 9.49%; phase one can replace either with Mulliboom at 1%. Standard
band 1 also offers a sparse direct Mulliboom encounter. These routes follow
installed room-library presence; weights, threat costs and caps are local tuning.

Actual production residents verified by the native fixture:

| Enemy | Seed | Floor, zero-based | Room |
|---|---:|---:|---:|
| Mulligan | 2 | 0 | 3 |
| Mulligoon | 105 | 0 | 4 |
| Mulliboom | 54 | 2 | 5 |

The pool now contains **46 directly weighted identities, 49 including conditional
replacements**. This is reachability configuration, not a completed-port count.
The 1% first-floor Mulliboom rule is checked, but this slice's natural Mulliboom
witness uses the direct band-1 route. [Pool audit](pool-audit.json).

## Evidence and limitations

The [source review](source-review.json), [13 preserved native windows](source/manifest.json),
[XML and room records](records.json) and [animation metadata](animations/manifest.json)
retain the installed Repentance 1.7.9b evidence. Verify it with
`python3 scripts/isaac-reference/analyze-mulligans.py --check`.
Wiki-derived replacement odds retain attribution and the preserved revision link
in the source review. No commercial art is imported into the runtime by this slice.

Physical canyon navigation adapts the source movement forces. Exact grid search,
initial impulse, diagonal bias, cache/retry, knockback and time-scale behavior
remain incomplete. Nonzero offspring-counter semantics, Troll Bomb animation
countdown and pushing, full status/item/champion behavior, hard-mode shots,
source eye/appearance animations, broad balance and controlled performance are
also open. Original body silhouettes remain; no visual parity is claimed.

Player defaults, Original visual style, hubs, Mine, tutorial and 4–8-floor
expeditions remain unchanged. The [checkpoint](checkpoint.json) records the
validation results and hashes once this slice passes its checks. Earlier failed
fixture attempts remain in [test corrections](test-corrections.json).

## Validation

All **68 native suites pass** in [CTest](native.xml), including the focused
[family behavior fixture](behavior-final.txt). All **10 browser cases have passing coverage** in
[the WASM report](web/results.json): nine from the full run plus the focused
natural-Mulliboom capture/sampling retry, with the same WASM build and no
browser/GL errors. Two delayed-death visual captures also pass separately. The
[visual review](visual-review.json) records inspected Original-style native and
browser captures and its limits. No controlled benchmark or complete balance
acceptance is claimed. Earlier report artifacts remain hash-verified unchanged.
