# Maw family — regular-enemy priority

This slice replaces the generic behavior for Maw, Red Maw and Psychic Maw,
and implements the Psychic Maw's required Eternal Fly orbit and release.
**These are partial ports. The full enemy-port goal remains active.**

| Enemy | Implemented normal behavior |
| --- | --- |
| Maw | Flying pursuit with momentum; seven-frame targeting checks; source firing and recovery timing; aimed physical shots |
| Red Maw | Three times the pursuit impulse; no live shots; four cardinal projectiles on death |
| Psychic Maw | Maw pursuit and timing; larger purple homing shots; required orbiting Eternal Fly |
| Eternal Fly | Invulnerable growing orbit; changes into a damageable Attack Fly when its parent dies; regeneration expires after its recorded orbit duration |

All three Maws have 64 local HP, equivalent to the source's 20 HP under the
existing conversion. Psychic Maw previously had an unsupported 88 HP.
Their movement, firing, homing, death and orbit values live in
[`maw_family.mechanics`](../../../../assets/mechanics/maw_family.mechanics).
They enter appropriate specialist pools from the second stage band onward,
with at most one of each identity per room. Eternal Fly is dependency-only.

The [source review](source-review.md) documents the installed controllers,
archived wiki revisions, animation events and adaptations. Psychic Maw's native
projectile Scale is 1.5; its homing strength remains the default. The new homing
profile reproduces acceleration and retention inside the source range instead
of constantly normalizing projectile speed. Existing generic homing is separate.

Two integration defects were found through actual scene captures:

- Generated-room preparation discarded queued offspring. Births now resolve
  during preparation; requests still waiting for capacity belong to their room
  and survive leaving and returning.
- The Eternal Fly's halo could produce an undefined lighting normal and a black
  rectangle through bloom. A guarded normal fixes the observed artifact.

**75 unique native suites and six production WASM cases pass**, combining the
full native run with the corrected progression fixture.

Validation includes source timing and movement recurrences, physical shots,
current-target aim, homing range, invulnerable orbit and damageable release,
finite regeneration, retained volleys and offspring, room round trips, strict
configuration validation, and actual seeded residents. Linux and WASM capture
results are recorded in the [checkpoint](checkpoint.json) and
[visual review](visual-review.json). These checks do not certify full balance,
readability, performance or every source branch.

Placement witnesses use zero-based floor and room indices:

| Enemy | Seed | Floor | Room |
| --- | ---: | ---: | ---: |
| Maw | 3 | 1 | 6 |
| Red Maw | 3 | 1 | 7 |
| Psychic Maw, with Eternal Fly | 9 | 2 | 6 |

Earlier test failures are retained. Adding specialists changed the former
Drowned Hive seed fixture; an independent search found seed 118, floor 2,
room 6. The progression fixture also needed to distinguish required orbiters
from ordinary enemies and allow their prescribed initial overlap with a parent.
Those corrections retain checks for the exact child count, correct parent,
ordinary budgets, independent-body spacing and seeded identity order. The first
browser fixture also assumed constant projectile speed inside a room containing
a suction statue. Isolated checks still require speed 21; the resident check
allows physical redirection only when the corresponding room actor is present.

An initial Chromium 1248 run rendered at roughly 1 FPS and was stopped after
its first image. The retry uses Chromium 1194, the build used by earlier
checkpoints, and records the reported NVIDIA/D3D12 renderer. This is not a
controlled browser-performance comparison. Both attempts remain available.

Remaining work includes native status/control/champion branches, appearance
and parent-visibility transitions, corn-poop ownership, other Eternal Fly
parents, native replacement rates, exact grid/RNG and shot-height parity,
and the unresolved released-fly contact-death flag. Holy Leech's existing
cleanup is preserved until that parent's own source review.
