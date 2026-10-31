# Regular enemy port: Hopper and Flaming Hopper

Normal and Flaming Hoppers now use the installed game's destination-based
hopping, replacing the earlier fixed-distance arcs. Their source animation
phases, acquisition range, random bonus, steering and Flaming target prediction
are externally configured. Normal Hopper health is corrected from 48 to **32**;
Flaming remains **64**. Both remain contact-only enemies.

The [source review](source-review.md) separates installed 1.7.9b evidence from
DeathWard's 3D adaptations. Three native disassembly windows and two animation
metadata files are preserved and reproducibly checked. Native flame morphing
preserves health fraction. Locally, the old flight profile, momentum and landing
target remain active until a safe landing, preventing a mid-air transformation
from shifting collision phases inside terrain.

Regular enemies and their required offspring remain the priority before further
boss work. This slice improves two existing records; it does not claim two new
completed enemies. Original rendering, player defaults, standard 4–8-floor
expeditions, the one-floor tutorial, hubs and Mine remain unchanged.

## Placement and validation

- Both forms retain sparse bands 0–2 pursuit pools. The existing first-band
  Scorched replacement rule is retained. [Natural witnesses](natural-witnesses.json)
  identify actual generated residents; the full stage regression activates
  both forms in every approved band.
- [Native summary](native-summary.json): **83 distinct suites pass**. The full
  run passed 81/83; two assertions still referenced the previous hop controller.
  The rebuilt landing/room-entry checks both pass in the retained focused rerun.
  Production runtime did not change between these runs.
- [Focused checks](native-focused-2.txt) establish exact source phases,
  destination commitment, strict range and target-velocity prediction; actual
  cover/water/gate collision; airborne damage; fire/burning distinctions;
  health-fraction morphing; stun, suspension, death, validation, immutable reloads
  and early-floor reachability. The default 100 HP/24-damage kit defeats both
  isolated forms. This is not full-floor balance acceptance.
- Production Linux and WASM builds succeeded. [Browser results](web/results.json)
  contain nine passing cases: both isolated forms, both cover crossings, in-flight
  morphing, river crossing, both natural early-floor residents and death.
  [Browser summary](browser-summary.json) also records the separate legacy-harness
  compatibility checks and any retained failed attempts.
- [Visual review](visual-review.json): 12 images individually inspected,
  10 accepted smoke views and two limited views. Early camera motion makes the
  two limited views unsuitable for readability acceptance. Native capture FPS
  overlapped build/test work; no controlled performance claim is made.
- [Historical integrity](historical-check.json): all 6,892 preceding report
  artifacts are unchanged.

## Retained diagnostics

Initial focused failures exposed test assumptions: an uncleared money pickup in
an isolated fixture; the old generic hop binding diagnostic; and pursuit and
wandering coincidentally snapping to the same destination. The reload test now
places the target on the opposite side and verifies distinct real destinations.
The full regression retained its obsolete airborne-flag/cooldown assertions
before correcting them to observe the actual source controller.

The broader browser harness also contained an obsolete natural replacement
seed. The passing native stage scan identifies the current witness at seed 116,
floor 0, room 1, source 29.0.0 → 54.0.0. The earlier failed browser attempt is
retained separately; this is not a runtime spawn-rule change. One source recheck
initially used a Python environment without Capstone; the system Python rerun
passes the byte-exact extraction check. A separate compatibility-browser attempt
also found the local test server had stopped; that connection failure is
retained, and the server was restarted for the rerun.

## Remaining scope

177 definitions, 168 reviewed records, 126 in progress, 53 existing-unverified,
462 missing and 12 excluded; **zero complete six-gate ports**. There are 76 direct
ordinary pool identities, 80 including replacement routes. These totals are
unchanged because this work refines already reviewed ordinary enemies.

Special targeting/control/champion branches, complete status/item/fire-producer
interactions, all-camera mixed-room visual acceptance, full-floor mixed-build
balance and controlled rendered performance remain open. The next regular family
to review is Spitty, including Tainted Spitty and its existing adaptive armor.
