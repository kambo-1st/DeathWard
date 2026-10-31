# Knight masks, Loose Knight lifecycle and Pon — installed 1.7.9b

This is an incremental port of **41.0–41.4 and 840.0.0**. Directional protection,
reflection geometry, the Loose Knight/Pon lifecycle and Pon hopping now have
dedicated code and external profiles. The five Knight bodies now use a dedicated
30 Hz controller with cardinal acquisition and committed charges. Black Knight
adds acceleration, collision recoil, grounded recovery and three discrete fire
jet generators. **These are still partial ports; full acceptance is open.**

## Evidence and a correction to the wiki interpretation

`scripts/isaac-reference/analyze-knights.py --check` verifies the installed
executable hash, two dispatcher entries, six exact disassembly windows and six
animation descriptions. The native executable SHA-256 is
`04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.
The [source manifest](source/manifest.json) and
[animation manifest](animations/manifest.json) preserve the byte-level evidence.
The extractor resolves DLC overrides before base metadata and imports no artwork
into the game. Exploratory files in `discovery/` are not complete function proofs;
the bounded windows in `source/` are authoritative for this review.

The preserved [Knight article, revision 271631](https://bindingofisaacrebirth.wiki.gg/index.php?oldid=271631)
and [Brain article, revision 270038](https://bindingofisaacrebirth.wiki.gg/index.php?oldid=270038)
are credited to The Binding of Isaac: Rebirth Wiki contributors, CC BY-SA 4.0.
Their supplied contents and exact entity rows are saved in
[review-sources.json](review-sources.json). Later Repentance+ Hagalaz behavior is
outside the requested baseline.

The wiki describes a separate invisible shield leading a Knight. The inspected
1.7.9b damage path instead calls **6aa830**, reads the actual animation name
(`Up`, `Hori`, otherwise down) and horizontal flip, and rejects an incoming
velocity component opposite that facing axis. Exactly perpendicular and rear
components pass. The incoming vector is not normalized against an angular cone.
The path controller at actor+364 owns movement data; treating its owner pointer
as proof of a separate shield would be a mistaken interpretation. No independent
shield entity has been established by these windows, so none is invented here.

The tear collision caller at **64e852–64e8dc** checks piercing/spectral exceptions
before the direction helper. Other damage paths and every item interaction have
not been exhaustively traced. The current DeathWard rule applies to direct
physical hits; area, piercing and typed status damage bypass it. Spectral tears,
melee and all source status producers are not certified by this implementation.

## Reviewed identities

| ID | Source HP / mass | Role and dependencies | Current implementation |
|---|---|---|---|
| 41.0.0 Knight | 20 / 10 | Ordinary armored body | Directional mask and dedicated cardinal wander/charge |
| 41.1.0 Selfless Knight | 20 / 10 | Faster ordinary armored body | Directional mask and faster source walk/charge forces |
| 41.2.0 Loose Knight | 20 / 10 | Armored body that becomes 41.3 and releases 840 | Armor, dedicated movement and same-ID lifecycle |
| 41.3.0 Brainless Knight | 20 / 10 | Invincible remnant; source `shutdoors=false` | Ownership, immunity, independent radial/grid wander and charging |
| 41.4.0 Black Knight | 30 / 100 | Reflecting armored charger | Directional reflection, accelerating charge, three-direction impact and relative body mass |
| 840.0.0 Pon | 20 / 10 | Ordinary hopper, also required Loose Knight offspring | Source-driven hopping, landing creep and remnant cleanup implemented in progress |

All six XML rows have stage HP zero, contact damage 1 and collision radius 13.
DeathWard keeps the established 3.2 health conversion: 64 HP except Black Knight
at 96. Player defaults remain 100 HP / 24 damage. World body radii and damage
conversion remain local adaptations, not measurements of Isaac's pixel geometry.

## Mask and reflection behavior

The old rule incorrectly exempted Loose Knights and rejected side shots with a
`.35` dot-product threshold. `mask_armor` now uses the source sign test. The
procedural mask plate rotates with the same cardinal direction used for hits.

Black Knight collision at **6a3a39–6a3da4** reflects eligible tears. Its animation
direction can suppress reflection for **15 source frames** after a turn, while
the mask still blocks damage. Reflection uses `v - 2 dot(v,n) n`; sufficiently
grazing shots use a radial collision normal. The new code retains incoming planar
speed and tangential motion, rather than always firing directly backwards at a
fixed speed. Native projectile size conversion and every tear flag remain open;
local reflected damage is externally configured at 10.

## Loose Knight and Brainless Knight lifecycle

At **502c8b–502dc2**, the dead Loose Knight spawns a Pon at a random radius-10
offset, links both entities, updates the child and morphs its original body to
variant 3. There is no replacement body with a new identity. The new
`linked_remnant` profile preserves the original entity ID and health scale and
queues the required child, without an intermediate kill reward or room-clear
window. Native immediate newborn advancement remains unverified in the local
scheduler and is not claimed as exact.

Standalone Brainless Knights search for the nearest unclaimed Pon on their first
update (**50161f–50173b**). They do not manufacture one. Their ordinary damage
immunity does not depend on whether the partner pointer is already populated.
The body dies when its partner is absent/dead (**501797–5017ae**) and does not
hold the room doors shut independently. This replaces an old test assumption
that incorrectly required an automatically created Pon.

DeathWard represents this with a bidirectional pair. Killing Pon removes only
its matching remnant. The remnant pays no additional ordinary kill/loot reward
on that cleanup; the complete original reward semantics remain an explicit
verification task. A debug execution can still remove actors.

In real 3D rooms, a required child's placement is retained if terrain or capacity
prevents birth. The remnant waits while its retained request keeps room
completion pending. Child placement can overlap its parent, as the source birth
offset requires, but cannot appear inside terrain. Removing the body cancels
its pending child. Independently placed pairs cannot claim the same Pon.

## Pon controller and landing payload

Type 840 dispatches to shared Hopper controller **514450**. The Repentance Pon
animation has **Hop 26 / Jump 4 / Land 17** at 30 Hz, like ordinary Hopper.
It has no Flaming/Leaper random distance bonus. Target acquisition range is 130
native units; wandering distance 95; grid 40; arrival 10; retention .7; distant
force .05; grounded factor .1. These are loaded through `target_hop`.

The Pon branch retries a blocked destination up to ten times with random
wandering targets (**515956–515b11**). After its Land trigger, a per-update
one-in-three roll keeps destination release suppressed; the other two outcomes
allow the usual arrival/stuck release check (**51607b–51611c**). DeathWard requires
a legal 3D ground point before ending an airborne phase early. Crowd avoidance,
grid snapping and safe-landing prediction remain geometry adaptations.

At Land (**515cec–515d58**), Pon creates red creep effect 1000.22 at sprite scale
1.25 and immediately updates it. The previously pinned
[Brain effect review](../brain/source-review.md) establishes the effect's default
125-frame lifetime, radius `20 * scale`, damage 1, fade multiplier .98 and roughly
40-frame fade. `landing_creep` therefore configures a 2.5-world-unit radius,
125/30 seconds of damage and a 40/30-second harmless fade. A circle replaces the
original alpha-tested footprint; that shape difference is not certified parity.

Each Land event produces one patch. Patches survive their owner, and a delayed
patch is retained through capacity pressure and owner death. Pon uses a distinct
procedural lobed silhouette within Original style. It has a sparse band 2–3
pursuit pool, based on the source Mines/Mausoleum habitats; pool weight/cost are
DeathWard pacing rather than extracted spawn odds.

## Open work and acceptance limits

The pinned Knight controller establishes shared cardinal wandering, a three-frame
alignment check, random prediction up to 16 frames, range 200 and half-cell
alignment 20. Walking force differs: .75 / 1.25 / .6 / .75 / .66. Charge starts
at force 1, Selfless multiplies by 1.65, and Black starts at .7 and accelerates
by .07 toward 4. Ordinary retention is .8, Brainless .88. Black's sufficiently
strong aligned collision emits three fire-wave directions (back and both sides),
adds an impact lift and starts a 45-frame recovery. These values now drive the dedicated controller. Black charge magnitude follows
the source pre-increment limit test and may exceed 4 by one .07 increment.
Collision braking is .01, confirmed separately from the .1 cross-axis pull.
Brainless adds the shared MoveRandomly(true) radial target (distance40, arrival3,
force.5) before grid steering. It does not orbit or pursue its linked Pon.

The [movement supplement](source/movement-supplement.json) pins those additional
constants and the previously preserved random-walk/fire-jet evidence. The impact
fan reuses the installed1000.148/147 effect traced for Crackle, with three
authored directions rather than four fixed axes. Capacity retains one due fan
through owner death. The three directions, two jet damage pulses, timing and
wall rejection retain the existing fire-jet implementation.

Radius-aware path selection, current-room grid alignment, terrain-clipped
movement, collision-normal inference and inverse-mass crowd displacement are
DeathWard geometry adaptations. Mass100 versus10 affects relative displacement;
this is not a certified port of every native impulse/knockback rule. Source
status/charm/player-control branches and Black state7 remain open. Floating/Bone Knight branches sharing the helper remain separate records.

Also open: native RNG stream/order, champion/fear/charm/player-control behavior,
all damage/item/status combinations, exact projectile-size reflection, native
high-speed tint and full walk/impact animation detail, precise
newborn update order, full 3D alpha-mask equivalence, all-camera mixed-room
readability, default-kit balance and controlled Linux/WASM performance. Scoped
tests and rendered smoke cases do not close any record's six acceptance gates.
The full 653-record goal remains active, with regular enemies first.

## Current placement and validation

Knight is eligible from band1; Selfless and Black stay in band3. Loose and Pon
start in band2. These are authored DeathWard analogues of the preserved
Caves/Sheol/Ashpit/Mausoleum/Gehenna room libraries, not extracted spawn odds.
Brainless remains a required linked component outside ordinary pools.

The first broad witness search examined140 floors/1856 rooms and found all five
ordinary identities. Regression cases now use those fixed real seeds:
Knight0/2/5, Selfless0/5/7, Loose0/3/2, Black1/6/7, Pon33/4/7
(seed/floor/room, zero based). The source-health, mask, linked lifecycle,
movement, impact, capacity and configuration checks are in
`tests/knight_tests.cpp`. The final checkpoint separates build/test receipts
from visual observations and records all still-open acceptance requirements.

### Rendering exposed an open-passage bug

The first browser controller run used an invalid scripted player offset; the
capture helper correctly rejected it. A legal offset fixed that test setup.
A stronger visual assertion then found that Black Knight's impact generated no
visible jets: its unlimited charge had travelled through an open debug passage
into another room. The native controller now clips travel to the active room
bounds, treats that boundary as a collision and emits the fan inward. The
regression covers an open passage without relying on a closed door. Failed
receipts and the before-fix captures remain preserved; `boundary-*` receipts
identify the corrected final runtime.

The roster expansion also invalidated two old Brain population witnesses.
Actual replacements are seed4/floor5/room2 (band2) and seed51/floor5/room9
(band3, real interior river). The Brain tests still require real generated
residents and legal movement on the river terrain; no enemy is injected to
satisfy the test. The discovery receipt is retained.

A second visual check caught Black taking32 damage from its own first jet.
The installed controller at50154b..50157b clears that pending damage when its
EntityRef identifies effect1000.147 and SpawnerType is not1 (player). The pinned
EntityRef constructor establishes that the field is SpawnerType, not subtype.
The local jet path now honors that exception. Tests also require ordinary Flame
hits and player-produced jets to remain effective; this is not blanket fire
immunity. `jet-*` final receipts include this last correction.

## Final checkpoint

Five scoped Linux CTest suites pass, plus the final extra mass and player-jet
exception assertions. Eleven production WASM cases pass (six isolated, five
actual generated populations), with no captured GL or JavaScript errors.
Eight final images were inspected; see [visual-review.json](visual-review.json).
The [native](native-summary.json) and [browser](browser-summary.json) summaries
link exact receipts. [checkpoint.json](checkpoint.json) pins selected runtime,
build and evidence hashes and the current ledger counts. Neither those tests
nor these images certify the remaining full physics/status, visual, balance or
performance gates. Zero records are marked fully accepted.
