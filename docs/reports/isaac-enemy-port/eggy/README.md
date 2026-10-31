# Regular enemy port: Eggy

Eggy **29.2.0** now uses source-derived hopping, white slowing creep and a timed
Swarm Spider death sequence. It is a sparse ordinary pursuit specialist in
progression bands1–3, with at most one initial Eggy per room. Regular enemies and
their required offspring remain the priority.

| Property | Implemented behavior |
| --- | --- |
| Health | `(20 + 2 × source stage multiplier) × 3.2` |
| Hop | Eight-frame idle threshold; Hop26, Jump4, Land17, source30Hz |
| Target | Strict91-native-unit range, zero Trite overshoot bonus |
| Landing | White five-second slowing creep; one-in-three immediate re-hop |
| Lethal damage | Anchored, harmless husk; shots pass through; repeated hits do not restart it |
| Offspring | Fourteen real884.0.0 Swarm Spiders, released at measured Die frames |
| Child launch | Short/medium/long weights3:2:1, source launch speeds and advanced first-hop frames |
| Completion | Parent resolves once at Die70; living or pending children keep the room active |

Values are external in [eggies.mechanics](../../../../assets/mechanics/eggies.mechanics).
The [source review](source-review.md), [instruction windows](source/manifest.json)
and [animation metadata](animations/manifest.json) distinguish measured rules
from the authored3D, health and creep adapters. No source artwork is imported.

## Validation

- The completed [Linux regression run](native-final.xml) passes78/80 suites.
  The [corrected Prey witness](prey-corrected.xml) and
  [updated Eggy integration regression](monster-corrected.xml) pass the remaining
  suites:80 distinct suites pass across those runs, not a fresh full80/80 run.
- [Targeted native checks](native-navigation.txt): source timing/health,
  exact release cadence, real bullets through the husk, harmless companion
  overlap, single kill/loot, completion, capacity-delayed births with retained
  launch state, room suspension, stun, external validation/reload and placement.
- [Production WASM](web-navigation/results.json): five cases cover isolated
  hopping, physical cover, gun death, explosion death and a naturally generated
  resident. The browser reports no captured JavaScript or GL errors.
- [Visual review](visual-review.json): twelve individually inspected final
  images, four Linux and eight WASM, in Original style. Static captures do not
  establish all-angle combat readability or controlled performance.
- [Seeded witness](witness.json): Rourke seed8, zero-based floor4, room10.
- [Historical integrity](historical-integrity.json) pins6,554 earlier report
  files. [Checkpoint](checkpoint.json) freezes this slice's evidence and hashes.

Preview: `./build/deathward --smoke --theme canyon --style original
--scene enemy-29.2.0 --frames 100000`.

## Retained failures and fixes

The initial browser run passed four isolated cases but failed the natural-room
hop assertion. Its [diagnostic](web-diagnostic/results.json) and
[native reproduction](navigation-diagnostic.txt) show a legal player target
being snapped into a rock, making this zero-overshoot hopper repeatedly reject
the same destination. The shared target-hop adapter now falls back to the legal,
unsnapped candidate while preserving its terrain and predicted-landing checks.
The exact original seed/positions remain a native regression; final browser
acceptance still requires movement and creep in that room.

An initial native suspension fixture used overlapping room bounds, so entering
its empty room immediately cleared it and returned to the original room. A
stationary guard prevents that automatic return; the actual suspend/resume and
offspring assertions remain. Initial compilation also caught references to a
nonexistent `Enemy::impulse` field; those references were removed. Animation
extraction initially searched the older archive namespace; the successful
extraction uses the installed DLC3 path. Logs are retained.

The first full native regression run was interrupted after the navigation fix
made it stale. Its partial log is retained as `native.txt`; acceptance uses the
fresh full `native-final.xml` run. Initial images with the husk's misleading
health bar are retained but superseded by final captures without it.

One completed-run failure was Prey's old placement search, which examined
only the first band1 floor of256 seeds. Adding another weighted specialist
changed those choices. The corrected search examines all production-configured
Flooded band1 floors within1024 seeds. It finds Prey at seed242/floor3/room7 and
Small Leech at seed5/floor2/room3. Habitat restrictions, spawn odds, costs and
required assertions are unchanged. The original failure and corrected rerun are
both retained.

The other failed suite still expected the old five instantaneous Eggy children.
Its integration assertion now requires the harmless initial husk, all fourteen
releases before Die70, then removal of the parent with fourteen dedicated Swarms
remaining. The original failure and passing corrected regression are retained.
The first checkpoint-freeze attempt rejected the unexpected second failure
before changing status; its diagnostic is retained too.

## Open work

Native special statuses/champions, exact RNG/update ordering, the unidentified
release-suppression field, Bursting Sack, friendly/charm behavior and precise
source creep radius/slow semantics remain unresolved. Ordinary birth capacity
is tested; the shared generation-depth limit above four is still local policy.
Full mixed-room balance, all-angle readability and controlled Linux/WASM
performance remain open. This is an **in-progress port**, not six-gate completion.

The maintained total is123 in-progress records and zero fully certified complete
ports. Next regular-enemy work includes Tainted Hopper, Leapers and improved
normal/Flaming Hopper fidelity; bosses stay behind regular enemies.
