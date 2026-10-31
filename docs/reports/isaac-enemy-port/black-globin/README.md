# Black Globin family — native implementation checkpoint

The ordinary hostile forms `278.0.0`, `279.0.0` and `280.0.0` have dedicated,
externally configured behavior. They remain **in progress**, not fully accepted
Isaac ports. Required offspring take priority over starting another boss family.

## Source findings

The installed Repentance 1.7.9b executable is pinned by SHA-256 in
[source/manifest.json](source/manifest.json). The reproducible extractor checks
dispatch, complete controller windows, constants and the body's `Spiders`
overlay string. [Animation metadata](animations/manifest.json) preserves the
three highest available archive overrides; no source sprite artwork is imported.
The old `head.asm` and `body.asm` are incomplete first-return preflight windows.
Use `head-complete.asm` and `body-complete.asm`, especially the body's cooldown
tail after its first return.

| Actor | Native HP → DeathWard HP | Ordinary behavior |
|---|---|---|
| Black Globin | 33 → 105.6 | Ground pursuit, force .6, contact 2 → 20 before the existing damage multiplier |
| Detached head | 20 → 64 | Ground pursuit, force .5, contact 2 → 20; red creep |
| Detached body | 10 → 32 | Pacer-style wandering, force .5 and retention .75; contact 1 → 10; occasional thrown Spider |

All three have zero native stage-HP growth. Native distances use the existing
0.1 conversion and source decisions run at 30 Hz.

The broad wiki description “on every hit” is insufficient. Parent controller
`4fc330` polls **HP at the previous emission minus current HP**, requiring
**strictly more than 5 source HP** (16 local HP). Small hits accumulate; multiple
hits before an update coalesce. A successful emission updates the baseline and
throws one full-health Spider toward 75% of the player's displacement. Its
initial height is −30, vertical velocity −8, gravity +.7, and horizontal step
.04 times the chosen target displacement.

Death releases body280 at the parent and head279 near it. There is **no goo
phase, regeneration or overkill cutoff**. There is also no separate forced death
Spider: a lethal hit passes the same HP-delta check. A small final hit can
therefore split the parent without emitting another Spider.

Head279 takes the direct-pursuit branch of the Brain controller, bypassing
ordinary Brain cardinal wandering and charge. Its common red-creep trail uses
12/24-update intervals below/at five room enemies, with an extra halfway
emission above native speed3. The body takes the shared Headless controller's
Spider branch: initial cooldown20–39, room population strictly below5, random
nearby throw target, then **90 or180** updates, not a uniform90–180 delay.
Its eight-frame `Spiders` overlay is not Gusher's blood jet.

## Runtime and placement

[black_globin.mechanics](../../../../assets/mechanics/black_globin.mechanics)
defines health, pursuit, damage threshold, child identities, throw height,
head placement radius, creep, brood timing and the final-band encounter entry.
`GroundPursuit.cpp` shares physical navigation/force integration with Gapers;
head279 extends the Brain controller with exclusive pursuit instead of charge;
body280 extends Headless with a population-gated brood option. Invalid or
conflicting configurations are rejected. Existing immutable mechanics snapshots
remain valid when a replacement configuration loads.

Only the parent enters the natural final-band pool, adapting source Sheol/Dark
Room presence. Head/body are required independent offspring, not owned parts
removed with their parent. Placement weights and one-parent-per-room cap are
DeathWard tuning, not claimed source probabilities. Natural parent witnesses:
seed7/floor4/room2, seed10/floor5/room7, seed12/floor6/room5 (zero-based indices).

Required births remain reserved under capacity/placement pressure and hold room
completion. Pending brood counts toward the local population limit. Terminal
children clamp ancestry to the local safety bound rather than disappearing at
depth4. Ground navigation, free-position selection, collision radii, retained
births and immediate lethal-damage handling are explicit 3D adaptations.

## Validation and remaining work

See [native-summary.json](native-summary.json) for exact test results and hashes,
[visual-review.json](visual-review.json) for inspected captures, and
[roster-progress.json](roster-progress.json) for the updated missing count.
Behavior checks exercise strict accumulated damage, coalescing, final-hit
deduplication, extreme overkill, source initialization, 30/60Hz parent movement,
cover routing, pursuit/creep, brood timing/population, real projectile collision,
contact behavior, deferred births, external snapshots and actual seeded rooms.
Starting-kit bots are scoped balance probes, not human mixed-room acceptance.

Open details include native grid cost900 versus continuous navigation; exact
free-position distribution; appearance protection; status/champion/control/item
interactions; slow-clock behavior; all-camera and mixed-room readability; and
measured rendering performance. The head's identity is weak from behind, and
its red creep uses the existing conspicuous circular hazard rendering.

Thrown births disable projectile/body contact collision while airborne. A
proposed blanket area-damage immunity conflicted with existing Prey semantics
and was removed. The saved generic radial collector skips collision-class0,
but exact bomb, generic radial and direct scripted damage paths require a
separate comparison before changing their shared policy. This remains an
explicit fidelity gap, not a completed vulnerability claim.

WASM builds/checks remain skipped under the user's standing instruction.
