# Ordinary Brain implementation checkpoint

Brain **32.0.0** now has a dedicated controller for cardinal wandering,
alignment-triggered charges and red creep. It replaces the generic wanderer.
The [source review](source-review.md) documents the installed Repentance 1.7.9b
instructions and animation metadata, together with the 3D adaptations.

The external profile in `assets/mechanics/brains.mechanics` controls movement,
charge prediction and timing, creep damage/lifetime/fade, animation length and
floor placement. Source HP20 becomes **64HP**. Body contact deals **25 damage**;
creep deals **12.5**, after the existing hostile multiplier. Player defaults
remain 100HP and 24 base damage.

Wandering does not pursue the player. Alignment checks run on the source-derived
global seven-frame interval. A charge commits to one cardinal direction, slows
its old velocity by.8 before adding force, and stops on real terrain or bodies.
Grid centering cannot pull the enemy through canyon geometry. Brain does not
inherit Spitty projectiles or the other branches in its shared native function.

Red creep has its own lifetime, surviving the owner's death while other enemies
remain. Killing the final enemy clears the room and starts a harmless fade.
The local circular footprint explicitly replaces native animation-mask sampling.
Overlapping translucent pools now blend without coplanar depth-fighting stripes.
The pink folded body is original low-poly geometry; no Isaac artwork is imported.

Ordinary encounters use Works/Storm bands2 and3, adapting the source Depths/Womb
habitats. [Actual seeded witnesses](natural-witnesses.json) cover both bands and
an interior-river room. Floor indices in the evidence are zero-based:

| Seed | Floor index | Room index | Purpose |
| --- | --- | --- | --- |
| 22 | 5 | 6 | Works-band resident |
| 2 | 5 | 6 | Storm-band resident |
| 101 | 6 | 9 | Natural resident in an interior-river room |

## Validation and corrections

- [All 87 registered Linux suites have passing results](native-summary.json).
  The first broad regression passed 85/86; an Eggy fixture still assumed an old
  encounter roll. Its separate natural-spawn test remains, while the navigation
  counterexample now retains its original terrain and coordinates independently
  of roster changes. Corrected Eggy and Brain pass 2/2.
- [Focused Brain checks](native-focused-final.txt) cover movement endpoints,
  moving-target prediction, charge commitment, solid/body collisions, safe grid
  centering, dense/sparse/fast creep intervals, damage, expiry, owner-independent
  lifetime, automatic room clear, capacity pressure, stun, room suspension,
  external configuration and actual seeded activation.
- The unmodified starting kit defeats Brain in 8.68 simulated seconds with 100HP
  remaining. The earlier bot followed it down active creep and died; the revised
  bot leaves the charge lane and avoids visible patches. Enemy stats and damage
  assertions were retained. This proves isolated feasibility, not full-floor balance.
- [Seven production WASM Brain cases pass](web/results.json): open, cover, river,
  death/expiry and all three actual seeded witnesses. No browser or GL errors.
- [Four Spitty compatibility cases pass](web-spitty-final/results.json), including
  Conjoined and Tainted attacks and Tainted death spirals, for 11 total browser cases.
- [Fifteen Brain screenshots were individually inspected](visual-review.json).
  Thirteen final Linux/WASM views are accepted as smoke evidence. Two preserved
  earlier views expose the overlap artifact that prompted the rendering fix.
- The first 64 seeds contained the two ordinary-band witnesses but no qualifying
  natural river resident. The retained [offline search](river-search-1.txt)
  found seed 101. Regression now tests those concrete witnesses in seconds.
- One final WASM link was terminated with exit143; its log is preserved. The
  retry completed successfully. A later compatibility attempt found the local
  server had stopped; connection refusal is retained as harness evidence.

The source extraction is reproducible with
`python3 scripts/isaac-reference/analyze-brain.py --check`. All 7,202 preceding
report artifacts remain unchanged. The final checkpoint pins source, runtime,
build and report hashes; it does not certify every acceptance gate.

## Remaining work

Exact native grid/RNG/global-update equivalence, source appearance and
status/control/champion paths, all item-immunity and producer routes, and exact
animation-mask collision remain open. Mixed-room/all-camera readability,
full-floor mixed-build balance and controlled rendered Linux/WASM performance
also need broader evidence. Screenshot FPS during other jobs is not a benchmark.

Regular enemies and required offspring remain the priority. The next ordinary
family is Mr. Maw 35: its body, returning heads and neck relationship must be
reviewed together. The complete 653-record goal remains active.
