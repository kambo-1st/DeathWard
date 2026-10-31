# Regular enemy port: Host family

Five normal-state Host variants have dedicated, externally configured behavior.
This is partial progress toward the full port: no enemy in this checkpoint is
certified complete across all six acceptance gates. Regular enemies and their
required offspring remain the priority over further bosses.

| Enemy | Local HP | Behavior | Expedition placement |
| --- | ---: | --- | --- |
| Host 27.0 | 44.8 | Stationary, armored while closed, three aimed shots | Bands 1–3 |
| Red Host 27.1 | 48 | Stationary, always vulnerable, five aimed shots | Bands 1–3 |
| Mobile Host 204.0 | 44.8 | Walking armored Host, three shots, contact damage | Bands 1–3 |
| Flesh Mobile Host 247.0 | 86.4 | Walking vulnerable Host, five shots, contact damage | Bands 1–3 |
| Floast 859.0 | 64 | Floating diagonal motion, armored, three shots | Band 3 |
| Hard Host 27.3 | Legacy value | Source reviewed; generic behavior still unverified | Not newly approved |

Bands are the existing progression categories, not floor numbers. These are
specialist pool entries with one of each identity at most per room. The placement
weights and costs are authored adaptations. The opening floor, tutorial, Mine,
hubs, player defaults and expedition length are preserved.

## What changed

The dedicated controller uses the source's 30 Hz animation events for opening,
shooting and closing. Closed armor, cumulative hit-induced opening delay, the
Burning exception, live aim, distinct three/five-shot spreads and movement are
separate mechanics. Stationary Hosts have no contact damage. Whole volleys wait
under capacity pressure, and room changes preserve actor state.

The projectile implementation includes the native common post-pass: unequal side
velocities, speed multipliers and inherited parent motion. Floast skips that
post-pass as in the inspected controller. See [source-review.md](source-review.md)
for exact values and caveats. Values live in
[hosts.mechanics](../../../../assets/mechanics/hosts.mechanics); parser validation
and immutable reload behavior have native coverage.

Original-style procedural bodies distinguish skull/stem, exposed red flesh,
walking legs and hovering motion. No Isaac artwork was imported. Visual review
caught and fixed a legacy pedestal underneath Hosts and a floating stem on the
stationary body. Early, rejected captures are preserved alongside corrected ones.

## Validation and evidence

The frozen [checkpoint](checkpoint.json) is the authoritative result manifest.
Its creation script requires passing results before updating the maintained
checklist. **76 unique native suites and 10 production WASM cases pass**, with
28 images inspected. Browser coverage uses five isolated cases and five real
seeded resident cases, with physical projectiles, armor windows, health and
movement assertions. The seeded Flesh Mobile Host did not fire in the sampled
window; its isolated case verifies firing, while that seeded case establishes
reachability and runtime state.

- [Native behavior evidence](native-targeted.txt): armor windows, aggregate delay,
  direct damage versus Burning, explosions, contact, physical volley speed/live
  aim, capacity, sight, stun, movement recurrence, bounce, lifecycle and config.
- [Seeded witnesses](witnesses.json): repeatable production floor/room locations.
- [Accepted Linux captures](native-accepted-captures.json): ten open/resident
  views plus three closed views after camera settling.
- [Visual review](visual-review.json): individually inspected Linux/WASM images;
  these are appearance checks, not full combat readability certification.
- [Source review](source-review.md), [native source windows](source/manifest.json),
  [animation metadata](animations/manifest.json), and preserved wiki/API evidence.
- [Historical integrity](historical-integrity.json): hashes of 6,162 earlier
  report files, verified unchanged when this checkpoint is frozen.

The expanded pool exposed two overly narrow test fixtures. The Maw witness search
assumed that floor index 1 always belonged to band 1; it now reads the actual
expedition plan. The Bone Fly sample missed that identity within its old seed
window; the original candidates remain and an independently found seed 93 witness
is added. An interrupted Bone Fly retry is retained as an interruption, not a pass.

Initial browser attempts failed before game startup. The diagnostic captured an
`Invalid Host profile` error from the first new configuration row. The incremental
build had compiled the parser while the format was changing. A clean production
WASM build removed the startup failure; all ten fresh browser cases pass without
page/GL errors. This is consistent with stale build output; no additional runtime
source change was needed. Compressed WASM assets were refreshed and checked by
decompression. Earlier timeouts and the separate unavailable-server attempt
remain in this directory.

## Remaining work

Hard Host needs its aimed physical rock shockwave, obstacle destruction and nearby
knockback. Mushroom has a separate controller and is outside this slice. Native
status/control/champion branches, transformations, additional damage channels,
projectile height/fall behavior, exact grid/RNG parity and replacement probabilities
remain open. Local contact overlap is visible in some mobile resident captures;
full combat readability, balance and controlled performance still need acceptance.

The overall goal remains active. Registry entries and generic AI do not count as
completed ports.
