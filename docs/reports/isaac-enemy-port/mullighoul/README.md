# Willo and Mullighoul — regular enemy slice

This slice follows the user's priority: regular enemies and their offspring
before more boss work. It covers **808.0.0 Willo** and **817.1.0 Mullighoul**
against installed Repentance 1.7.9b. Both remain **in progress**. The Original
style, hubs, Mine roster, player defaults and expedition structure are retained.

## Preserved evidence

The [native manifest](source/manifest.json) contains 15 disassembly windows,
checked executable hash, dispatch targets, state table and float constants.
[Animation metadata](animations/manifest.json), [XML and room presence](records.json),
and [pinned wiki articles](wiki-source.json) are retained. No sprite artwork was
imported. The [source review](source-review.json) separates recovered rules,
local adaptations, corrections and missing branches. Earlier checkpoints remain
immutable.

The installed executable and XML take precedence where the wiki differs.
Mullighoul has **14 source HP**, despite the pinned wiki infobox's 13. Its death
count uses the same native type-817 adjustment as Prey; it is not simply a random
one or two Willos.

## Implemented behavior

Willo orbits the player along a 120 × 100.8 source-unit ellipse. Group members
share a clock and receive evenly spaced offsets. Losing or adding a member
redistributes the group from its smallest surviving offset; an attacking actor
retains its committed slot until the attack finishes. Tracking combines twice
the player's velocity with a capped correction toward the orbit target.

Only one ordinary Willo can attack at a time. A settled, eligible actor has a
1-in-9 check per ready update. Its 36-frame attack warns at frame 6 and fires at
frame 24. The shot aims one player-velocity update ahead, has source planar
speed 10, and explicitly passes through grid walls. It falls with the recovered
damped projectile physics and still collides with the player and ground.
Willo bodies also ignore grid scenery; shooting is suppressed outside the room.
They have 19.2 local HP and harmless contact.

Mullighoul uses the shared Hive evasion and population-dependent spawning
controller. Its 18-frame head attack spits a full-health Willo at frame 4.
It hovers 0.6 local units above the ordinary body centre and can cross water,
while solid rocks, gates and room bounds still constrain its path.
It has 44.8 local HP and harmless contact.

At death, the ordinary zero-counter formula is:

```
max(1, ceil(4 / (1 + 0.2 * other_population)) - 1)
```

This gives three Willos alone, two with two other actors, and one with five.
Post-hit HP at or below −64 suppresses the births. Children remain independent
threats after their parent is gone. Capacity restrictions retain the births and
keep the room sealed until they are admitted and defeated.

Both identities are in sparse wet band-1 pools, based on Downpour and Flooded
Caves habitats: Willo in crossfire pairs and Mullighoul in pursuit encounters.
Actual production witnesses are seed 3/floor 1/room 6 for Willo and seed 80/floor
2/room 8 for Mullighoul (zero-based floor and room indices).

## Adaptations and open work

HP ×3.2 and source XZ distance ×0.1 preserve existing player balance conventions.
The local 60 Hz movement integration, physical navigation, rectangular shooting
boundary, retained-event capacity rules and Original procedural silhouettes are
DeathWard adaptations. Shot vertical scale is 0.05; local height 1.15, upward
speed −1.5, gravity 9, damping 0.9 and ground radius 0.25 reproduce the recovered
ordinary downward shot. A four-second safety lifetime is local.

Owner/multiplayer/friendly Willo branches, native appear/initial-counter details,
fear/confusion/shrink suppression, complete item/status interactions, Min-Min's
special underwater states, nonzero death counters and full native grid-path
parity remain open. Min-Min expansion is deferred under the regular-enemy
priority. Full visual readability, broad balance and controlled performance
acceptance are also not claimed.

## Validation

All **70 native suites pass** in [CTest](native.xml), including the focused
[Willo/Mullighoul fixture](behavior-final.txt). All **nine WASM cases pass**
in the [combined browser report](browser-results.json), with no browser or GL
errors. Seven isolated cases and two natural cases retain separate evidence
files; the latter include an attraction-statue interaction that changes shot
speed after firing. [Fixture corrections](browser-fixture-corrections.txt)
explain the two browser assertion failures and why no runtime change was needed.

The [visual review](visual-review.json) records inspected Linux and WASM
captures and their limits. Earlier captures can hide fleeing actors behind the
HUD or scenery, so an additional early Linux capture shows the hovering parent
and child clearly. All 5,553 earlier report artifacts were hash-verified
unchanged. Neither record is certified complete; the broader goal remains active.

