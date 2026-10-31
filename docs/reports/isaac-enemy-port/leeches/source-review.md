# Leech family: Repentance 1.7.9b

Scope: ordinary Leech **55.0.0**, Kamikaze Leech **55.1.0**, Holy Leech
**55.2.0**, and their existing Eternal Fly **96.0.0** dependency. Small Leech
810 and Adult Leech 854 use different controllers. This work does not certify
them or the full roster. Regular enemies remain the priority.

## Evidence

[Source discovery](source-discovery.json) preserves installed XML, positive
room-template counts and the revision-pinned wiki article. The article is
[revision 268624](https://bindingofisaacrebirth.wiki.gg/index.php?oldid=268624),
by The Binding of Isaac: Rebirth Wiki contributors, CC BY-SA 4.0. Repentance's
knockback immunity and variant descriptions are distinguished from source code.

`python3 scripts/isaac-reference/analyze-leeches.py --check` reproduces six
[disassembly windows](source/manifest.json) and three [animation metadata
files](animations/manifest.json). Installed executable SHA-256:
`04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.
The archive hashes and entry checksums are checked, highest DLC override first.
No Isaac artwork is imported into the game.

Type55 dispatches to shared controller `0x51afa0`. Other types' branches in
that function are not Leech behavior. Important Leech paths:

| Rule | Native evidence | DeathWard implementation |
|---|---|---|
| Health and contact | XML HP25/stageHP0/contact2 for all three variants | 80HP, contact20 before the existing hostile1.25 multiplier |
| Flight | XML walls-only collision; source sets grid collision3 | Shared flight navigation over low cover and pits; real cliffs/walls remain solid |
| Wander | Type55 force.85 at51b74a; shared cardinal helper7a51e0; friction.85 and Z correction.964705825 | Dedicated30Hz state using shared cardinal wander and flight-aware path checks |
| Acquisition |51c0e5 interval4/entity offset; predictionU*16; room clamp20; alignment within20 of current grid-cell axis | Predict player motion, test cardinal alignment and walls-only sight; no range cap for type55 |
| Charge |51c772 force1.55; normalized predicted delta from cell center | Commit slightly angled heading once; no continuous pursuit, windup, cooldown or fixed timeout |
| Acceleration |51ce9c friction.9; AddVelocity422b60 divides impulse by friction; base686406 applies friction | Same momentum recurrence, with cross-axis correction before final damping |
| Lane correction |51d116–51d19b interpolation base.7, applied to axis perpendicular to committed heading | Current grid-center pull.3, preserving slight source heading angle |
| Stop |51cd96 checks displacement squared<2, accumulates more than5frames; grid collision ends charge | Stop on real flight collision or six stuck source ticks; clear wander path |
| Animation | Hori/Up/Down8frames; Dash variants6; Appear20; no event triggers | Independent source-rate walk/dash loop and Original-style body pose; spawn timing remains unverified |
| Death |51b066–51b09d calls BombDamage40/radius60/lineChecktrue/flags4 for variants>0 | Immediate retained blast128/radius6/player20; no legacy.7-second marker |
| Holy offspring |51b2b3–51b32e spawns96 at parent and assigns parent pointer | One retained required orbiter, born at current parent, canceled if parent dies before admission |
| Orbiter death | Wiki explicitly says Holy explosion kills its fly | Parent death removes attached fly before completion, including execution/debug paths; no released Attack Fly |

The shared BombDamage identity and argument order are independently pinned in
[Black Bony's source manifest](../black_bony/source/manifest.json). A death
blast can damage nearby enemies and scenery and respects actual line of sight.
A full event queue retains the dead carrier until it can emit the whole payload.
The debug kill path intentionally suppresses blasts.

## Placement and adaptations

Ordinary Leech appears in Depths/Dank Depths and Womb-family/Sheol/Cathedral/
Corpse templates. Kamikaze appears in Necropolis, Sheol and Dark Room. Holy
appears in Utero and Cathedral. Corresponding ordinary expedition bands are
2–3 for normal/Kamikaze and3 for Holy, through charge-lane specialist pools.
Weights, costs and caps are local encounter design, not native frequencies.
Greed/special and boss-produced routes are separate outstanding work.

`assets/mechanics/leeches.mechanics` holds the profiles, health, immediate death
payloads, child identity and pools. Invalid/conflicting controllers and missing
child dependencies fail transactionally; running simulations retain their
immutable mechanics snapshot.

Distance scale.1, HP scale3.2, contact scale10, physical radius.55, real3D flight
height and original procedural geometry are explicit adaptations. Native cells
become a room-centered local grid with legal-flight fallback. The flying shared
wander helper now checks the same geometry as movement; grounded users retain
their existing checks. Required orbiters spawn at the moving parent rather than
searching for an unrelated vacant point. This also fixes the same capacity
edge case for Psychic Maw's retained Eternal Fly.

Holy cleanup is explicit owner cleanup rather than a simulation of native
explosion/morph/update ordering. It cannot grant a second ordinary kill or loot.
Knockback immunity retains controller-owned momentum while still accepting
actual physical collision response. Native sound/animation art is not copied.

## Still open

Native fear/confusion/charm, slow/freeze/control/champion interactions and
attraction toward type401 are not complete. The ordinary source stop under
slow is known (flag80 and speed<3) but DeathWard's full status model is still
pending. Exact native grid scoring, RNG consumption and update ordering, source
Appear collision timing, source sound/visual effects, rare variant replacement
eligibility and boss-produced routes need further work. The wiki's4.96% and1%
replacement percentages are not silently applied without edition-specific
creation-path review.

Scoped behavior, placement and visual checks do not prove all-camera combat
readability, full expedition/mixed-build balance or controlled Linux/WASM
performance. These records remain **in progress**, not fully accepted ports.
