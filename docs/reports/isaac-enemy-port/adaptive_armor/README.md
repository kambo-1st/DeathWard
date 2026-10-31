# Regular enemy port: shared adaptive armor

Seven existing regular variants now use the installed-source rolling damage
resistance: Tainted Pooter, Mulligan, Boom Fly, Hopper, Spitty, Sucker and Level2
Charger. This is shared mechanics work, **not seven completed enemy ports**.
Spitty and Sucker retain their existing-unverified behavior status.

The [source review](source-review.md) records exact health/strength, the30Hz
current-batch formula, distinct bypass flags and the native Bomb producer.
[External configuration](../../../../assets/mechanics/adaptive_armor.mechanics)
controls strength, history length and correction. Real bombs bypass reduction
but contribute to history; projectile piercing, NPC explosion markers and new
item explosions do not automatically inherit that bypass. Deferred hits retain
attribution and chain budgets across room suspension and resolve once.

The original style, protagonist100HP/default damage, encounter weights,
4–8-floor expedition structure, tutorial, Mine roster and hubs are preserved.
No boss implementation or new natural route is added. Source maximum HP corrects
three legacy variant values; historical reports remain unchanged.

## Validation

- [Native summary](native-summary.json): **82 distinct Linux suites pass**.
  The full run passed81/82; a corrected Boom Fly test fixture then passed1/1.
  Both original and corrected results are retained, not presented as a clean
  single run. The final correction records elapsed warning time before room
  suspension instead of assuming it was still zero after deferred death.
- [Focused native checks](native-final-focused.txt): exact source-frame formula,
  simultaneous hits, zero frames, history expiry, large hits, separate bypasses,
  real player/enemy bombs versus NPC explosion markers, item chains, removed
  source attribution, bounded queues, re-entry, execution and ordinary death,
  seven source profiles and immutable validated reloads.
- [Seven production WASM cases](web-final/results.json): burst reduction, rolling
  expiry and full small-hit damage after quiet history. Their recorded damage
  matches the [independent formula calculation](browser-formula-check.json).
  The native rendered Hopper HP matches the browser result too.
- Two additional [Hopper cases](web-hopper/results.json) pass ordinary death and
  natural Rourke seed22/floor7/room1. One [Pooter death case](web-pooter/results.json)
  passes with the required lethal amount and source-frame delay. Total: **10
  final-build browser cases**, no captured JavaScript/GL errors. Shared harness
  boilerplate may describe its full case set; these files contain only the
  explicitly selected cases above.
- [Visual review](visual-review.json):10 individually inspected images,9accepted
  smoke views and1limited view. Tainted Sucker overlaps the protagonist; distant
  Boom Fly contrast and existing legacy cues need separate review. No full
  visual, balance or rendered-performance gate is certified.
- [Integrity check](integrity-check.json):6,752 preceding report artifacts and
  all15 pinned source files match their preserved hashes.

Earlier build failures used private test helpers; the tests now exercise public
placement/actual death producers. Older immediate-damage and lethal fixtures were
updated for genuine armor resolution, with explicit bypass only where a test
isolates exact overkill boundaries. The first browser expiry observation landed
on the last retained frame; its retained failure led to an observation safely
after expiry. Production timing was unchanged.

## Remaining work

Reconcile source-version claims about extra initial protection and large-hit
adjustments; review every damage/status producer and linked-owner armor. Preserve
remaining full-AI, dedicated Ascent reachability, mixed-build balance, all-camera
readability and controlled performance gaps. Counts remain177 definitions,
166 reviewed,124 in progress,55 existing-unverified,462 missing,12 excluded and
**zero complete ports**. There are75 direct ordinary pool identities,79including
replacement routes.

Regular enemies and required offspring remain the priority. Next: Leaper variants
and normal/Flaming Hopper fidelity, then remaining regular-family gaps. The full
653-record goal remains active. The [checkpoint](checkpoint.json) pins this slice.
