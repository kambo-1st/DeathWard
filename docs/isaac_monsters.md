# Isaac enemy integration

## Full enemy port plan — 2026-10-25

This is the implementation specification for expanding the existing adaptations
to the full researched roster. The plan itself is research; implementation work
is now tracked separately below. It supersedes the older roster's progression description.

The baseline is **installed Repentance 1.7.9b**, using the preserved XML, room
libraries and boss pools, plus the revision-pinned behavior dossiers in the
[mechanics reference](reports/isaac-mechanics-reference-2026-10-25.html).
Later wiki/Repentance+ behavior must be identified separately. The preserved
public code consists of mod hooks/API definitions and selected native
disassembly; it is not a complete source implementation of Isaac enemy AI.

The reproducible [JSON analysis](research/isaac-enemy-port-plan.json) and
[653-row CSV review queue](research/isaac-enemy-port-review.csv) contain exact IDs,
existing implementation matches, source stage evidence, candidate placements,
identity conflicts and review requirements. Rebuild them with:

```sh
python3 scripts/isaac-reference/plan-enemies.py
```

These generated files are research inputs, **not runtime configuration or an
approved roster**. Every row starts unapproved. Preserve completed manual review
and implementation status in a separate versioned manifest; regenerating the
analysis must not erase that work.

### Implementation progress

The maintained [per-record checklist](research/isaac-enemy-port-status.json) and
[progress CSV](research/isaac-enemy-port-status.csv) distinguish identity checks,
behavior review, implementation and six validation gates. Check them with
`python3 scripts/isaac-reference/track-enemies.py --check`; `--csv` refreshes the
progress export without replacing review decisions. `--init` refuses to overwrite
the maintained file. Native CTest includes this check when Python is available.

Current work in progress:

**Validation update, 2026-10-28:** the user requested skipping WASM checks.
Continue Linux behavior, placement, visuals, balance and performance validation.
Existing browser evidence below is historical and does not certify later changes.
The checklist retains that history, but its completion validator now explicitly
waives `visual_wasm` under the recorded user instruction. All five other gates
remain required; this does not mark any record complete.

**Current priority: finish ten first-floor enemies in two batches of five.**
Batch 1 is Frowning Gaper, Gaper, Gusher, Pacer and Horf. Batch 2 is Fly,
Pooter, Attack Fly, Spider and Mulligan. Preserve existing implementations and
park further roster expansion until these batches meet their acceptance criteria.

The [first batch report](reports/isaac-enemy-port/first-floor-batch1/native-summary.json)
records corrected Horf projectile flight/passive friction and a missing common
acceleration term in Gusher shots. Ten selected Linux suites pass across the
recorded runs; eight mixed starting-kit fights clear with 62.5–100 HP remaining.
Thirty-two generated opening floors cover all supported expedition lengths and
202 legal, idle-before-entry residents from these five identities. Twelve native
captures were inspected, and Gusher/Pacer silhouettes were clarified. A matched
CPU-only comparison measures this correction's cost; it is not rendered or full
pre-port performance acceptance. Shared status/champion behavior and the
remaining cohort acceptance work stay open. No record was promoted to complete.
That physics checkpoint used mechanics fingerprint `80f52693ea14c415`.

The subsequent [Fear/Confusion report](reports/isaac-enemy-port/first-floor-batch1/statuses/native-summary.json)
adds opt-in timed statuses for these same five identities. Moving bodies evade;
confused Gapers use cached random targets; Horf and Gusher block new attacks
while preserving committed shots. Native timer/reapplication rules, independent
expiry, headless transformations, inactive-room storage, physical cover and
contact damage are tested. Nine Linux suites pass, including the existing mixed
starting-kit and seeded first-floor checks. Six final native Original-style
captures were inspected after enlarging the initial status cues. The API and
external values are implemented; no new player perk was added. Other applicable
statuses, item hooks, champion/knockback interactions and remaining cohort
acceptance are still open. The roster remains unchanged and no record was
promoted to complete. That checkpoint used mechanics fingerprint `15f0be51f04a2a48`;
216 definitions. WASM remains skipped.

The [ordinary Freeze report](reports/isaac-enemy-port/first-floor-batch1/freeze/native-summary.json)
adds independently configured freezing for those same five enemies. AI, animation,
windups and reloads pause; source polling time, other status durations and already
emitted projectiles continue. Native `.01` passive friction retains external
movement and collision. Contact damage, ordinary damage reception, same-entity
headless transformations and room-threat accounting remain intact. Ten Linux
suites pass, including a new long-frame regression that caught and fixed Horf's
initialization phase when frozen before its first update. Eight final native
captures were inspected at Original style and 160% zoom, including a matched
Gusher pose and Horf thawing. The source windows, configuration checks, initial
failure and final passing evidence are preserved. That checkpoint's fingerprint:
`fdb13e137f49c8c6`; still 216 definitions and no newly completed records. Slow,
remaining applicable statuses/item interfaces, champion/knockback interactions
and full cohort acceptance remained open at that checkpoint.

The [Slow report](reports/isaac-enemy-port/first-floor-batch1/slow/native-summary.json)
adds independently configured Slow to those same five enemies. Movement uses the
native force/friction transformation; AI acquisition and status expiry retain
their real-time polling while animation, windups and reloads advance more slowly.
New Horf/Gusher shots inherit their own slowdown, including vertical flight, and
keep it after the owner recovers or dies. Twelve selected Linux suites pass,
including contact/damage, Freeze/Fear combinations, headless transformations,
room storage, external configuration and timestep partition checks. Seven native
Original-style captures were inspected at 160% zoom. Their isolated status cues
are visible, but warm-ground contrast and crowded/occluded readability still
need broader acceptance. That checkpoint's mechanics fingerprint: `4196dc02ae1cd555`;
216 definitions and no newly completed records. Remaining applicable statuses,
item-source interfaces, champion/knockback interactions and full cohort
visual/balance/rendered-performance acceptance stay open. Roster expansion stays
parked; WASM remains skipped.

The [Poison/Burn report](reports/isaac-enemy-port/first-floor-batch1/damage-statuses/native-summary.json)
adds both periodic damage effects to the same five identities. Each keeps its own
duration, damage and tick phase. Stronger reapplications preserve cadence; Freeze
and Slow do not stop the damage. Ordinary damage processing preserves headless
transformations, rewards and room threats. External profiles expose timing and
damage floors; the API accepts damage and producer context for later item hooks.
Thirteen selected Linux suites pass after fixing a Horf initialization-phase
regression under long steps. Eight final native captures show green poison cues,
side flames, recovery and combined Freeze/Burn. Initial failures and source
windows remain preserved. That checkpoint's fingerprint: `694232c4e57bfc17`; still 216
definitions and zero newly completed records. Shrink/Charm/control, remaining
applicable damaging statuses, item duration/source integration,
champion/knockback interactions and full cohort acceptance remain open. Batch 2
and roster expansion stay queued; WASM stays skipped.

The [Shrink report](reports/isaac-enemy-port/first-floor-batch1/shrink/native-summary.json)
adds shrinking to these same five enemies. Moving bodies flee, new shooting
attacks are suppressed and committed shots continue. Visual size approaches
one third on the real source clock, including during Freeze/Slow. Collision
size follows the installed baseline's separate application/removal rules.
Player contact squashes the enemy without harming the player or triggering a
headless transformation. Fourteen selected Linux suites pass, including swept
contact, cover, bounded queue retry, damage/morph, combined statuses, room storage
and external tuning. Eight inspected native captures show all five shrunken,
a normal baseline, recovery and contact death. Tiny details and mixed-room
readability still need broader acceptance. That checkpoint's fingerprint:
`9722794efbc282f3`; 216 definitions and no newly completed records. Remaining
applicable Charm/control/damaging statuses, item integration, champion/knockback
and full cohort acceptance stay open. Batch 2 remains queued; WASM is skipped.

The initial [Charm source review](reports/isaac-enemy-port/first-floor-batch1/charm/source/manifest.json)
preserves 18 executable windows for the same five identities. It distinguishes
temporary Charm from permanent friendly conversion, including target selection,
projectile collision/damage, NPC contact and room-clear rules. That historical
checkpoint contains source evidence only. Recheck the evidence with
`python3 scripts/isaac-reference/analyze-first-floor-charm.py --check`.

The subsequent [temporary Charm report](reports/isaac-enemy-port/first-floor-batch1/charm/native-summary.json)
implements the timed effect for these same five. Gapers pursue eligible enemies;
Horf aims at its resolved target; Gusher and Pacer retain their wandering.
NPC shots keep independent player/enemy collision and damage rules, including
after their owner recovers or dies. Swept NPC contact uses the source max-HP
damage curve and hit cadence. Temporary Charm still permits player damage and
keeps the affected enemy counted as a room threat. External profiles control
target polling, range and damage conversion. Sixteen selected Linux suites pass,
including the existing starting-kit fights and seeded first-floor placement
checks. Eight native Original-style captures were inspected at 160% zoom.
Additional source windows, the initial test failure and final passing logs are
preserved. Current mechanics fingerprint: `c8006956361ec3bb`; still 216 definitions
and zero completed records. Permanent conversion is not implemented; negative
Charm durations are explicitly rejected. No new player item was added. Remaining
status/item/champion interactions and full cohort visual, balance and rendered
performance acceptance remain open. Batch 2 stays queued; WASM stays skipped.

The [permanent Charm source checkpoint](reports/isaac-enemy-port/first-floor-batch1/charm/permanent-checkpoint.json)
adds four verified native windows: source-affiliation immunity, active-enemy
eligibility, persistent registration and list removal. A diagnostic string
confirms the persistent registry; registration deduplicates actors and checks
capacity. Permanent conversion also prevents player-source damage and requires
Horf to reject the player as an attack target even when its position resolver
falls back to the player. Exact registry consumption during room/floor travel
still needs tracing. This checkpoint changes evidence only; permanent conversion
is still unimplemented, and the runtime fingerprint and completion counts above
are unchanged.

The preceding four Leper parent forms `310.0.0`–`310.0.3` have source-backed evasion,
pursuit, batched damage/shedding, final-form creep and same-entity gray Gusher
mortality. Their required Flesh births retain capacity and room completion; the
existing `310.1.0` Flesh also remains a natural final-band resident. All four
parents have actual seeded placement witnesses. Ten selected Linux suites passed
across this slice; a new split-frame test caught early child admission, which was
fixed and revalidated. Four starting-kit encounters and fourteen inspected native
captures supply scoped evidence. That checkpoint used mechanics fingerprint:
`45d263966d0bc5b7`; 216 definitions. See the
[parent report](reports/isaac-enemy-port/leper-parent/README.md) and
[current roster count](reports/isaac-enemy-port/leper-parent/roster-progress.json).

There are **248 missing non-boss records**: four confirmed ordinary records,
233 awaiting classification and eleven other categories. Another **150 confirmed
ordinary records have implementations in progress**. The four confirmed missing
ones are Bouncer, Quakey, Gas Dwarf and Clickety Clack. This is **not** the whole
remaining regular-enemy backlog: the 233 pending records still require review.
Exact variants/subtypes count separately; no record has full acceptance yet.
Full visual, balance and performance acceptance remain open. WASM stays skipped.

The preceding Black Globin `278.0.0`, its head `279.0.0` and body `280.0.0` have
source-backed implementations. The parent polls accumulated HP loss above a
strict threshold, throws Spiders and splits without goo regeneration. The head
pursues and leaves red creep; the body wanders and releases Spiders below a room
population of five, with a 90-or-180-update cooldown. Only the parent enters the
final-band pool. Required offspring stay independent and retain room completion
under capacity pressure. Its checkpoint used mechanics fingerprint
`f731696ff0c76e5e` and 211 definitions. See the
[Black Globin report](reports/isaac-enemy-port/black-globin/README.md).

The preceding Nest `205.0.0` checkpoint added source-backed fleeing, a 130–149-update randomized spit
cooldown, contact-expiring live Spiders, and an equal Big Spider/Trite death
choice. It has actual residents in all three approved floor bands. Ten selected
Linux suites pass, including 656 generated floors, offspring/capacity checks and
eight isolated starting-kit encounters. Eight native captures were inspected,
four from that checkpoint's final rendering. Its mechanics fingerprint was `5db864532e552b5e`.
See the [Nest report](reports/isaac-enemy-port/nest/README.md),
[validation evidence](reports/isaac-enemy-port/nest/native-summary.json), and
[historical roster count](reports/isaac-enemy-port/nest/roster-progress.json).
Native status/grid behavior, required-child acceptance and broader
visual/balance/performance work remain open.

Rotten Gaper `10.3.0`–`10.3.5` now use a dedicated external controller with
76.8 HP, source force/retention, seeded default subtype selection, variable brood
spawning after a minimum delay, owned Small Maggot children and momentum-projected
orbit steering. All five forms and the default selector have actual seeded
Storm Cut witnesses. Five selected Linux suites pass, including a repaired doorway crowd-steering
regression; the floor regression covers966floors. Ten native captures were inspected
with explicit readability limits. That batch's mechanics fingerprint was `44afc2d79a64a284`.
See the [implementation contract](reports/isaac-enemy-port/rotten-gaper/implementation-contract.json)
and [native evidence](reports/isaac-enemy-port/rotten-gaper/native-summary.json).
Native status, grid-cache, full balance and performance work remain open.

Previous Small Maggot validation batch:

Small Maggot853.0.0 now has a dedicated external controller and32HP. Its variable
startup timer, curved momentum, awareness spreading, clear-line pursuit multiplier
and obstacle turns replace the provisional fixed-speed chase. Three selected Linux
suites pass. An actual late-band witness is seed0/floor5/room1, zero-based;
four native Original-style captures were inspected with explicit contrast and
occlusion limitations. See the [Small Maggot contract](reports/isaac-enemy-port/small-maggot/implementation-contract.json)
and [native evidence](reports/isaac-enemy-port/small-maggot/native-summary.json).
That batch's configuration fingerprint is `96d4ddaff380d3af`. The regression passes
across753canyon floors, and four production WASM scenario types pass. The natural
room includes a Black Knight whose fire wave kills the maggot; a native diagnostic
confirmed the32Flame hit and the browser test now verifies that interaction.
Four browser images were also inspected; see the [browser evidence](reports/isaac-enemy-port/small-maggot/browser-summary.json).
At that checkpoint, Rotten Gaper parents remained provisional; their
offspring already used this new controller. The parent replacement is described above. Full status, thrown-state, visual,
balance and performance acceptance remain open.

Previous ordinary Gaper validation batch:

Gaper10.0/10.1/10.2 now use dedicated external30Hz controllers, source HP
32/32/28.8, momentum-based pursuit and source-timed Frowning eye opening.
Seven selected Linux suites pass. Actual seeded opening witnesses exist for
all three forms; the broad regression passed across 753 canyon floors. Tests exposed and fixed
both unsafe corner advancement after crowd displacement and a room-budget bug
where stronger basic replacements consumed the second support actor's reserve.
Original-style native captures show closed/open eyes and visible Flaming flames;
small facial detail and post overlap still limit visual acceptance.
See the [movement contract](reports/isaac-enemy-port/gaper/movement-contract.json),
[Linux evidence](reports/isaac-enemy-port/gaper/movement-native-summary.json), and
[visual review](reports/isaac-enemy-port/gaper/movement-visual-review.json).
That batch's configuration fingerprint is `ec8492eb3ee9db9`. Its WASM bundle
includes the room-budget correction and passes seven movement scenarios plus
six mortality scenarios. Three mortality cases force child selection only in the
browser's disposable filesystem; native tests check production probabilities.
Nine browser captures were inspected, with crowded readability still unaccepted.
See the [current browser evidence](reports/isaac-enemy-port/gaper/movement-browser-summary.json).
Full status/control/champion behavior, production contexts,
balance and controlled performance remain open.

The earlier Gaper mortality slice at `25efabc006603172` passed five scoped Linux
suites and six browser cases. Ordinary/Frowning outcomes are half true death,
one sixth Pacer and one third Gusher; Flaming outcomes are half death and half
Gusher. Same-entity morphs preserve ownership/momentum and do not pay an early
kill reward. Browser child-selection overrides are explicitly documented; native
tests validate production probabilities. See the [mortality contract](reports/isaac-enemy-port/gaper/morph-contract.json)
and [browser evidence](reports/isaac-enemy-port/gaper/morph-browser-summary.json).
These older browser checks do not certify the newer movement implementation.
Counts remain227 reviewed,191 implementations in progress (143 ordinary),432
missing,18 existing/unverified,12 excluded and zero complete ports.

Rotten Gaper (10.3.0–5) and its Small Maggot offspring (853.0.0) were the next
source-review batch; their current implementation is described above.

Previous Gusher/Pacer validation batch:

Gusher11.0 and Pacer11.1 now use dedicated, externally configured controllers
instead of their provisional behavior graphs. Both have32HP; Gusher fires along
its movement with source cooldowns and lob physics, while Pacer only wanders and
deals contact damage. Actual Gaper children and Faceless transformations use these
controllers. Eight scoped Linux suites pass, including the full Faceless regression.
Natural opening witnesses are Gusher seed4/floor0/room6 and Pacer
seed0/floor0/room2, zero-based. See the [headless contract](reports/isaac-enemy-port/headless/implementation-contract.json)
and [Linux evidence](reports/isaac-enemy-port/headless/native-summary.json).
The direct broad regression passed across753canyonfloors. Four production WASM
scenarios passed (both isolated and naturally seeded variants), with five browser
captures inspected. See the [browser evidence](reports/isaac-enemy-port/headless/browser-summary.json).
That validation uses fingerprint `79025961123d4945` with207definitions and
predates the Gaper mortality changes above; it does not certify those changes.
Full status behavior, readability, balance and controlled performance acceptance
remain open.

Previous Faceless validation batch:

Faceless827.0 and Tainted Faceless827.1 now use dedicated external controllers.
They retain movement during their source-timed radial attacks, spread aggression
between nearby Faceless, and use distinct projectile physics. Ordinary Faceless
can become a real Gusher or Pacer on death, with source probability and overkill
gates; its entity and ownership survive without premature kill rewards.
The focused Faceless and Danny suites and six broader Linux regressions pass.
Actual seeded witnesses are ordinary seed50/floor2/room3 and Tainted
seed11/floor4/room2, zero-based. Tainted uses an explicit rare late-floor adaptation
of its Ascent-only source placement. See the [implementation review](reports/isaac-enemy-port/faceless/implementation-review.json)
and [scoped Linux evidence](reports/isaac-enemy-port/faceless/native-summary.json).
The broad regression passed across 774 canyon floors, and four final native
captures were inspected with explicit readability limits. Four production WASM
scenarios pass at fingerprint `de4d3f2edf6a893c`; four browser images were also
inspected. See the [browser evidence](reports/isaac-enemy-port/faceless/browser-summary.json). The checklist is **227 reviewed,191 implementations in progress
(143 ordinary),432 missing,18 existing/unverified,12 excluded and zero complete**.
The Gusher/Pacer dependency is now being corrected above. Its new pool entry
changes the ordinary Faceless witness to seed51/floor2/room7; Tainted remains
seed11/floor4/room2. Full status, readability, balance and performance acceptance
remain open.

Previous frozen Danny batch:

Danny820.0 and Coal Boy820.1 now have dedicated external controllers, source-timed
attacks, persistent offspring ownership and actual thrown Rock/Coal Spider actors.
Their different room caps and recent-damage response come from the installed
controller. Eight selected Linux suites and four production WASM scenarios pass;
four final native and six browser captures were inspected. The floor regression
covered 1,087 generated floors and exposed a river-edge placement bug: checking
only a larger clearance ring missed water touched by the actual body radius.
Both placement paths now check the actual footprint too, with seed 404 retained
as a regression. See the [family review](reports/isaac-enemy-port/danny/implementation-review.json)
and [checkpoint](reports/isaac-enemy-port/danny/checkpoint.json).
Full status/champion/collision fidelity, crowded-scene readability, balance and
controlled performance remain open. Current Quarry witnesses are Danny at
seed 4/floor 2/room 4 and Coal Boy at seed 9/floor 2/room 2 (zero-based).
The checklist records **226 reviewed,189 implementations in progress (141 ordinary),
434 missing,18 existing/unverified,12 excluded and zero complete ports**.
The next ordinary family is Faceless/Tainted Faceless; its
[source preflight](reports/isaac-enemy-port/faceless/preflight.json) preserves the
controller and both animation files. That extraction adds no runtime or completed
port. Regular enemies and their required offspring remain the priority.
The [Faceless implementation contract](reports/isaac-enemy-port/faceless/implementation-contract.json)
now records seven verified helper windows, fixed radial volleys, movement rules,
death replacement gates and unresolved status behavior. An incremental
[Danny overlap fix](reports/isaac-enemy-port/faceless/danny-overlap-review.json)
preserves zero aim at coincident targets and passes the Linux family suite;
its WASM validation remains pending. The frozen Danny checkpoint is unchanged.

Previous Hardy batch:

Hardy826.0.0 now has a dedicated, externally configured charge/impact controller,
three escalating rock attacks, actual thrown Rock Spiders, and a double-health
Dip on ordinary death. Its four-child projectile burst is separate from the
existing two-child backward split. Installed native controller/helper evidence
and explicit remaining fidelity gaps are preserved in the
[Hardy review](reports/isaac-enemy-port/hardy/implementation-review.json).
Nine selected Linux suites and three production WASM scenarios pass, including a
natural Quarry encounter. Eleven final captures were inspected with explicit
readability limitations. See the [Hardy checkpoint](reports/isaac-enemy-port/hardy/checkpoint.json).
The Hardy checkpoint recorded **225 reviewed,187 implementations in progress
(139 ordinary),18 existing/unverified,436 missing,12 excluded and zero complete ports**.

Previous validated batch:

The [Rock Spider batch](reports/isaac-enemy-port/rock-spiders/implementation-review.json)
adds normal and Coal Spiders with their three seeded visual subtypes, plus the
required hot-coal remnants. Normal shells transform into the same live Spider
entity without an extra kill reward. Coal Spiders leave a bouncing, shootable
hazard whose expiry also responds to water and room completion. Their distinct
reveal/skitter controller, fire reactions and external profiles are backed by
installed native code and animation metadata. Only the source default-subtype
entries enter ordinary pools: normal Rock Spiders in the Quarry band, Coal
Spiders in the Washes/Quarry bands. Tinted Rock Spiders still need their actual
Soul Heart and tinted-rock production mechanics. Hardy now consumes the thrown
Rock Spider system; at that checkpoint, Danny was the next regular-enemy source review.

The Rock Spider checkpoint recorded **224 reviewed records, 186 implementations in progress
(138 ordinary), 18 existing/unverified, 437 missing and 12 excluded; zero fully
accepted ports**. Four coal remnants were already reviewed as missing components;
the native controller now establishes their independent environmental role.
The [Rock Spider checkpoint](reports/isaac-enemy-port/rock-spiders/checkpoint.json) records15 selected Linux suites,14 production WASM scenarios and18 inspected captures, with full acceptance still open.
Current Dip-family witnesses after the new pool entries are Corn: seed2/floor2/room4,
Big Corn: seed11/floor2/room2, and Drip: seed1/floor3/room8 (zero-based indices).


The [Dip/Squirt variant batch](reports/isaac-enemy-port/dip-variants/implementation-review.json)
adds six regular identities: Corn217.1, Brownie Corn217.2, Big Corn217.3,
Dank Squirt220.1, Drip870 and Splurt871. Dedicated profiles preserve Corn's
stronger random impulse, Big Corn's predictive death shot, Drip's chained
bursts, Splurt's two independently aimed charges, and Dank Squirt's slowing
creep and two-Clot death. Three wet variants can cross flooded pits, with the
same collision policy applied to movement, offspring and crowd separation.
All six have natural seeded witnesses; source records, animation metadata,
contracts and explicit uncertainties are preserved in the batch directory.
Nine scoped Linux suites and twelve production WASM scenarios pass; sixteen
images were inspected. See its [checkpoint](reports/isaac-enemy-port/dip-variants/checkpoint.json),
[native summary](reports/isaac-enemy-port/dip-variants/native-summary.json), and
[browser summary](reports/isaac-enemy-port/dip-variants/browser-summary.json).

The [Dinga family](reports/isaac-enemy-port/dinga/implementation-review.json)
adds three ordinary controllers: Dip (217.0.0), Squirt (220.0.0), and Dinga
(223.0.0). Dip makes random friction-driven dashes; Squirt telegraphs its dash
until the Slide event, then commits to the sampled direction. Dinga uses its
45 FPS animation metadata, chooses between two living Dips and an eight-shot
brown ring, and pushes nearby Dips. Death produces two Squirts, then four Dips;
all descendants and retained births keep the room sealed. Profiles and stage HP
are external in `assets/mechanics/dinga.mechanics`.

The earlier Dinga checkpoint passed seven scoped Linux suites and six WASM
scenarios, with ten images inspected. Current natural witnesses after pool expansion are seed 0/floor 0/room 6 for Dip, seed 0/floor
2/room 5 for Squirt, and seed 4/floor 5/room 10 for Dinga (zero-based indices).
See the [checkpoint](reports/isaac-enemy-port/dinga/checkpoint.json),
[native summary](reports/isaac-enemy-port/dinga/native-summary.json), and
[browser summary](reports/isaac-enemy-port/dinga/browser-summary.json).
The earlier Dip checkpoint recorded **216 reviewed records, 174 implementations in progress
(130 ordinary), 18 existing/unverified, 449 missing and 12 excluded; zero fully
accepted ports**. There are 115 direct ordinary pool IDs, 118 with positive
replacement routes and 119 including spawn-identity replacement. Full native
status/item/control behavior, alternate production paths, balance, performance
and visual acceptance remain open; Squirt's windup needs broader readability
review at gameplay zoom. Regular enemies and required offspring remain first.

The earlier [Adult Leech implementation](reports/isaac-enemy-port/adult-leech/implementation-review.json)
adds a dedicated controller and external profile for854.0.0:288HP, horizontal
charges with vertical steering, strong-impact12-shot rings, and a one-time
low-health burrow followed by a falling10-shot attack. Animation events control
body collision. Explosions and direct scripted damage retain distinct rules;
hidden bodies have no health bar or hover target. Swept wall movement agrees
between30Hz and120Hz integration. Seed14/floor6/room7 is a natural band3 witness
(indices are zero-based). Eight scoped Linux suites and three production WASM
cases pass across initial/corrected test runs; eight final images were inspected.
See the [checkpoint](reports/isaac-enemy-port/adult-leech/checkpoint.json) and
[native test summary](reports/isaac-enemy-port/adult-leech/native-summary.json)
for the corrected Knight population fixtures and external-item input assertion.
That checkpoint recorded **207 reviewed records,165 implementations in progress
(121 ordinary),18 existing/unverified,458 missing and12 excluded; zero fully
accepted ports**. There are106 direct ordinary pool IDs,109 with positive
replacement routes,110 including spawn-identity replacement. External Adult
Leech charge states, full native status/control/champion behavior, balance and
controlled performance remain open. Continue regular enemies and dependencies;
Hardy826 has since received the dedicated controller and scoped validation described above.

Previous frozen batch:

The [MemBrain/Cyst batch](reports/isaac-enemy-port/membrains/source-review.md)
replaces four generic behaviors with source-reviewed wandering, source-timed
rings and rolling aimed shots. All three parents have198.4HP and remain
vulnerable during the visual hop. Dead Meat's slower rotated ring repeatedly
reflects from walls/rocks; each parent produces its exact two children on death.
Cyst has80HP and a31-source-update firing interval. Four ordinary identities
have natural seeded floor witnesses. Eight relevant Linux suites and eight
production WASM cases pass;12 final images were manually inspected.
The [checkpoint](reports/isaac-enemy-port/membrains/checkpoint.json) records
**206 reviewed records,164 implementations in progress (120 ordinary),18
existing/unverified,459 missing and12 excluded; zero fully accepted ports**.
Native status/control/creation-path fidelity, full visuals, balance and
performance remain open. Continue remaining regular enemies, including Adult
Leech854, before further boss work.

Previous frozen batch:

The [Lump batch](reports/isaac-enemy-port/lump/source-review.md) replaces generic
burrowing with source-timed Spit/Hide/Appear phases, independent targeting and
cooldown, constrained underground relocation and actual mode2 three-shot flight.
HP is corrected to96. Hidden bodies remain room threats; visible emergence
respects canyon terrain. Five scoped Linux suites and two production WASM cases
pass, including a natural band3 population. Seven images were inspected.
The [checkpoint](reports/isaac-enemy-port/lump/checkpoint.json) records
**202 reviewed records,160 implementations in progress (116 ordinary),22
existing/unverified,459 missing and12 excluded; zero fully accepted ports**.
Full status/creation-path, broad visual, balance and performance gates remain
open. MemBrain and required Cyst offspring are next, then other regular enemies.

Previous frozen batch:

The [Leech family batch](reports/isaac-enemy-port/leeches/source-review.md)
replaces generic charges with source-based flying wander, committed charges and
wall stops. All three variants have80HP and double contact; Kamikaze/Holy death
blasts are immediate. Holy Leech's required fly survives spawn-capacity pressure
and is removed with its parent. Eight scoped Linux suites and six production
WASM cases pass, including three natural residents. Nine images were inspected.
The [checkpoint](reports/isaac-enemy-port/leeches/checkpoint.json) records
**201 reviewed records,159 implementations in progress (115 ordinary),23
existing/unverified,459 missing and12 excluded; zero fully accepted ports**.
Status/creation-path fidelity and broad visual, balance and performance gates
remain open. Regular Lump/MemBrain and Adult Leech are next.

Previous frozen batch:

The [Dople/Evil Twin batch](reports/isaac-enemy-port/dople/source-review.md)
replaces generic movement reversal with room-centered reflection, source-delay
firing, the Twin's30frame cooldown and three-shot packet, equal source HP and
zero contact damage. External profiles and late-floor pools enforce one mirror
enemy per room. Four production WASM cases pass, including both natural residents;
six native/browser images were inspected. See its
[checkpoint](reports/isaac-enemy-port/dople/checkpoint.json) for scoped evidence.
That checkpoint had **198 reviewed records,156 implementations in progress
(112 ordinary),26 existing/unverified,459 missing and12 excluded; zero fully
accepted ports**. Native spike/status/physics, broad visuals, balance and
performance remained open at that checkpoint.

Previous frozen batch:

The [Knight/Pon batch](reports/isaac-enemy-port/knights/source-review.md) adds
directional mask protection, reflected shots, same-ID Loose-to-Brainless
transformation, linked Pon cleanup and source-timed hopping/landing creep.
Dedicated Knight movement replaces the generic warning and timed charge; Black
Knight now accelerates and emits three fire-jet directions on strong impact.
All five ordinary identities have actual seeded placement witnesses. Five scoped
Linux suites and eleven production WASM cases pass; eight final images were
inspected. The [checkpoint](reports/isaac-enemy-port/knights/checkpoint.json)
preserves scoped hashes and evidence.
That checkpoint had **196 reviewed records,154 implementations in progress
(110 ordinary),28 existing/unverified,459 missing and12 excluded; zero fully
accepted ports**. Full native physics/status parity, broad readability, balance
and performance remain open. See the batch checkpoint for scoped test evidence.

Previous frozen batch:

The [Guts-family batch](reports/isaac-enemy-port/guts/source-review.md) replaces
the three generic type40 wall followers with source-reviewed contour movement,
Scarred Guts red creep and Slog's windup, charge, recovery and tar trail. New
seeded encounter contexts restrict Slog to the Dank counterpart and the50% Guts
replacement to the Scarred counterpart. Seven scoped Linux suites and seven
production WASM cases pass. Eleven captures were inspected; player-body collision
parity, shadow readability and full balance/performance gates remain open.
That checkpoint had 190 reviewed records, 148 implementations in progress
(105 ordinary), 34 existing/unverified and 459 missing; zero fully accepted ports.
Its source and evidence artifacts remain frozen.

The [Vis-family source review](reports/isaac-enemy-port/vis/source-review.md)
covers four ordinary bodies and Chubber's required returning component. Pinned
native controllers and five animation files establish distinct one/two/four-beam
packets, windup/recovery timing, cardinal acquisition and the returning trajectory.
The [first implementation batch](reports/isaac-enemy-port/vis/implementation-review.md)
now replaces the three laser bodies with dedicated30Hz controllers, locked
cardinal aiming, source animation timing, owned beams and same-type immunity.
Its [incremental checkpoint](reports/isaac-enemy-port/vis/beam-checkpoint.json)
records seven scoped native suites and five production WASM scenarios passing,
with documented geometry adaptations and visual limitations.
The [Chubber batch](reports/isaac-enemy-port/chubber/implementation-review.md)
adds its dedicated returning component, zero-HP immunity, swept interception,
piercing exception, moving-parent return and ownership cleanup. All four Vis
bodies now have source-appropriate seeded placement. The checklist has145 ports
in progress, including102 ordinary records;187 are reviewed,37 remain existing
unverified,459 missing and12 excluded. No record has completed all six gates.
Final fidelity/visual/balance/performance checks remain open; the frozen Baby
figures below describe an earlier checkpoint.

Earlier full-build implementation checkpoint:

The [Baby checkpoint](reports/isaac-enemy-port/baby/checkpoint.json) replaces the
generic normal/Angelic/small/Wrinkly controllers. Source HP, movement, attack
events, physical projectile packets, teleport collision windows, Wrinkly's
committed dash, external profiles and the actual Holy Mulligan child route are
covered by Linux checks. Browser validation found and prompted removal of an
incorrect line-of-sight gate in hostile Wrinkly acquisition. The native source
and through-cover regression establish the correction.

Four starting-equipment fights and five actual generated populations pass,
including two interior-river rooms. Passing evidence covers all89 native suites;
all11 final production WASM cases pass on a verified GPU renderer. The report
records26 directly inspected images, including explicit camera/terrain limits.
These are scoped checks, not full visual, balance or performance acceptance.
Fingerprint `c0d4e092a3ac08b4`:179 runtime definitions,187 reviewed,
140 implementations in progress (98 ordinary),41 existing-unverified,
460 missing and12 excluded. There are85 direct ordinary pool IDs,89 including
replacements. No completed six-gate ports are claimed.

Earlier frozen implementation checkpoints:

The [Mr. Maw checkpoint](reports/isaac-enemy-port/mr-maw/checkpoint.json)
adds dedicated body/head behavior for35.0/1/2/3 and the harmless35.10 neck.
Focused Linux checks pass for separate health, source head launching and spring
return, survivor transformations, spontaneous separation, red death shots and
retained allocation. Passing evidence covers all88 registered Linux suites after
required-part coverage, stale seeded-witness and newborn attachment corrections.
Seven actual generated residents activate successfully, including both forms in
all approved bands and two interior-river cases; all seven also pass in WASM.
Native and WASM builds pass. Six focused browser behavior cases pass before an
observer-only capture change; ten cases pass on the final production build
(seven generated populations and three exact-frame capture cases). Four isolated
starting-equipment combat checks pass. Blank images from an earlier asynchronous
capture attempt are retained and rejected as visual evidence; corrected views
have been inspected. Two generated-room views retain foreground cliff limits.
Fingerprint `9dabb84db4838840`:179 definitions,178 reviewed,136 in progress,
45 existing-unverified,460 missing and12 excluded, with zero complete ports.
Full source/status parity, all-camera readability, mixed-floor balance and
controlled rendering performance remain open. Regular Baby/Angelic/Wrinkly
enemies are next, using the [preserved source review](reports/isaac-enemy-port/baby/source-review.md).

The preceding [Brain checkpoint](reports/isaac-enemy-port/brain/checkpoint.json) replaces
ordinary Brain's generic wanderer with source-derived cardinal movement,
aligned committed charging and independent red creep. Health is64, body contact
is25 and creep damage is12.5 after existing conversions. Actual generated
Works/Storm residents and a naturally populated interior-river room are verified.
Fingerprint `8f2115c5da5f2e7f`: **178 definitions, 173 reviewed, 131 in progress,
49 existing-unverified, 461 missing, 12 excluded; zero complete ports**.
There are80 direct ordinary pool identities,84 including replacements.
**All87 Linux suites have passing results;11 production WASM cases pass**
(seven Brain, four Spitty compatibility). The
[report](reports/isaac-enemy-port/brain/README.md) preserves source evidence,
13 accepted final smoke views, two earlier overlap-defect views, corrected test
fixtures, and all7,202 preceding artifacts unchanged. Regular enemies and required
offspring remain the priority; Mr. Maw's body/head/neck family is next.
Full six-gate acceptance remains open.

The previous [Maggot checkpoint](reports/isaac-enemy-port/maggot/checkpoint.json) replaces
ordinary Maggot's generic behavior with a dedicated contact-only cardinal
walker. It corrects health to 48, retains player-independent wandering, and
routes it to source-equivalent Quarry/Storm bands. The movement helper is shared
with Spitties; their attacks remain separate. Fingerprint `36419b360ab65602`:
**178 definitions, 172 reviewed, 130 in progress, 50 existing-unverified,
461 missing, 12 excluded; zero complete ports**. There are 79 direct ordinary
pool identities, 83 including replacements. **86/86 Linux suites and 10/10
production WASM cases pass** (six Maggot, four Spitty compatibility).
The [report](reports/isaac-enemy-port/maggot/README.md) preserves source evidence,
actual seeded activation, eleven inspected screenshots (seven accepted smoke
views, four limited), and all 7,131 previous artifacts unchanged. Regular enemies
and required offspring remain the priority; Brain's aligned charging and creep
are next. Full six-gate acceptance remains open.

The previous [Spitty checkpoint](reports/isaac-enemy-port/spitties/checkpoint.json) replaces
ordinary/Tainted generic behavior and adds Conjoined Spitty. It implements
source-timed cardinal wandering and shots, opposite Conjoined volleys, Tainted
moving bursts and slowing streams, and two opposed death spirals. Projectile
orbit/acceleration is reusable and independent of vertical flight.
Fingerprint `cc57c1a3e966dbf0`: **178 definitions, 171 reviewed, 129 in progress,
51 existing-unverified, 461 missing, 12 excluded; zero complete ports**.
There are 79 direct ordinary pool identities, 83 including replacements.
**85/85 Linux suites and 9/9 final production WASM cases pass.** The
[report](reports/isaac-enemy-port/spitties/README.md) preserves source evidence,
the corrected cover-capture failure, seeded activation, and 20 individually
inspected images (16 accepted smoke views, four limited). Regular enemies and
required offspring remain ahead of further boss work. Ordinary Maggot is next;
full six-gate acceptance remains open.

The previous [Hopper checkpoint](reports/isaac-enemy-port/hoppers/checkpoint.json) replaces
ordinary/Flaming fixed arcs with source destination hopping, exact animation
phases and Flaming target prediction. Normal Hopper HP is corrected to 32;
Flaming remains 64. Native flame morph health-fraction retention is verified;
continuing the committed flight remains an explicit 3D adaptation.
Fingerprint `c8998ed9107ff3de`: **177 definitions, 168 reviewed, 126 in progress,
53 existing-unverified, 462 missing, 12 excluded; zero complete ports**.
76 direct ordinary pool identities, 80 including replacements. These totals
are unchanged because this improves two already reviewed records.
**83 distinct Linux suites pass** across the full 81/83 run and corrected 2/2
rerun; nine focused production WASM cases pass. The
[report](reports/isaac-enemy-port/hoppers/README.md) preserves source evidence,
initial fixture failures, natural band 0–2 activation, and 12 individually
inspected images (10 accepted smoke views, two limited). Regular enemies and
required offspring remain ahead of further boss work. Its then-pending Spitty
family review is covered above. Full six-gate acceptance remains open.

The previous [Leaper checkpoint](reports/isaac-enemy-port/leapers/checkpoint.json) adds
source ordinary hopping, occasional committed high leaps and distinct normal/
Sticky landing payloads. Fingerprint `b813f5107948f58b`: **177 definitions,
168 reviewed,126 in progress,53 existing-unverified,462 missing,12 excluded;
zero complete ports**.76 direct ordinary pool identities,80 including replacements.
All83 Linux suites and7 production WASM cases pass. The
[report](reports/isaac-enemy-port/leapers/README.md) preserves source evidence,
fixture failures and12 inspected images, including two limited views. Normal
Leapers use bands1–2; Sticky Leapers use band2. Full six-gate acceptance remains
open. This preceded the ordinary/Flaming Hopper review above.

The previous [shared adaptive armor checkpoint](reports/isaac-enemy-port/adaptive_armor/checkpoint.json)
adds source30Hz damage batching and rolling resistance to seven existing regular
variants, with physical-bomb bypass, correct source HP and persistent pending hits.
Fingerprint `22962f261b57f4d`: **177 definitions,166 reviewed,124 in progress,
55 existing-unverified,462 missing,12 excluded;zero complete ports**.
75direct ordinary pool identities,79including replacements. **82distinct Linux
suites pass** across a full81/82 run and corrected Boom Fly1/1 rerun;10production
WASM cases pass. The [report](reports/isaac-enemy-port/adaptive_armor/README.md)
preserves failures, evidence and remaining source/acceptance gaps. Spitty and
Sucker remain behavior-unverified; armor alone does not certify their AI.
Regular enemies and required offspring stay ahead of further boss work.

The previous [Tainted Hopper checkpoint](reports/isaac-enemy-port/tainted_hopper/checkpoint.json)
adds a dedicated four-hop sequence with4/6/8/12 physical landing shots and rare
late-floor placement. Fingerprint `d6db0034dfe180f3`: **177 definitions,
166 reviewed,124 in progress,55 existing-unverified,462 missing,12 excluded;
zero complete ports**.75 direct ordinary pool identities,79 including replacements.
A fresh81/81 Linux suite run and five production WASM cases pass. The
[report](reports/isaac-enemy-port/tainted_hopper/README.md) distinguishes source
rules,3D adaptations and remaining work. Adaptive armor was absent at that
checkpoint; the shared implementation above supersedes that gap. Earlier
checkpoints remain historical.


The [Eggy checkpoint](reports/isaac-enemy-port/eggy/checkpoint.json) adds
source-derived hopping, white slowing creep and a timed fourteen-Swarm death
sequence to ordinary encounters. Fingerprint `74a0ff8b3a6d27d2`:
**177 definitions, 165 reviewed, 123 in progress, 56 existing-unverified,
462 missing, 12 excluded; zero complete ports**. There are74 direct ordinary
pool identities,78 including replacements. **80 distinct native suites pass**
across the full run and two corrected regressions; five production WASM
cases pass and twelve accepted images were inspected. The
[report](reports/isaac-enemy-port/eggy/README.md) preserves initial failures,
the real generated-room navigation fix, sources and adaptations. Regular enemies
and required offspring remain first; full six-gate acceptance is open.
Earlier checkpoints below are historical.


The [Trite checkpoint](reports/isaac-enemy-port/trite/checkpoint.json) adds
dedicated destination hopping, source-frame inertia and physical cover/water
traversal to ordinary encounters. Fingerprint `d16f1a8e6aa61d3f`:
**177 definitions, 164 reviewed, 122 in progress, 57 existing-unverified,
462 missing, 12 excluded; zero complete ports**. There are 73 direct ordinary
pool identities, 77 including replacements. **79 distinct native suites pass**
across the full run and two corrected witness searches; four production WASM
cases pass and eleven accepted images were inspected. The
[report](reports/isaac-enemy-port/trite/README.md) preserves initial failures,
sources and adaptations. Regular enemies and required offspring remain first;
full six-gate acceptance is open. Earlier checkpoints below are historical.


The [Mushroom checkpoint](reports/isaac-enemy-port/mushroom/checkpoint.json)
adds Mushroom's closed resistance, timed reveal and four-shot cardinal/diagonal
cross to ordinary Caves-equivalent encounters. Fingerprint `6cb687923a293a80`:
**177 definitions, 163 reviewed, 121 in progress, 58 existing-unverified,
462 missing, 12 excluded; zero complete ports**. There are 72 direct ordinary
pool identities, 76 including replacements. **78/78 native suites and three
production WASM cases pass**, with eleven inspected images. The
[report](reports/isaac-enemy-port/mushroom/README.md) preserves sources, adaptations
and the Classic statue-route regression and fix. Regular enemies and required
offspring remain first; full six-gate acceptance is open. Earlier checkpoints
below describe historical states.


The [Hard Host checkpoint](reports/isaac-enemy-port/hard_host/checkpoint.json)
replaces Hard Host's generic bullet attack with its armored slam, physical crush
wave, eligible terrain destruction and nearby player hop. Fingerprint
`8f59a76434a3149b`: **176 definitions, 162 reviewed, 120 in progress,
58 existing-unverified, 463 missing, 12 excluded; zero complete ports**.
There are 71 direct ordinary pool identities, 75 including replacements.
**77 unique native suites and three production WASM cases pass**, with 11 images
inspected. The [report](reports/isaac-enemy-port/hard_host/README.md) preserves
sources, adaptations, initial failures and corrected results. Regular enemies
and required offspring remain the priority; full fidelity and six-gate acceptance
are still open. Earlier checkpoints below describe their historical states.


The [Host-family checkpoint](reports/isaac-enemy-port/hosts/checkpoint.json)
adds source-derived normal-state Host, Red Host, Mobile Host, Flesh Mobile Host
and Floast controllers. Hard Host is researched but retains unverified legacy
behavior. Fingerprint `f76820643f7192cc`: **176 definitions, 162 reviewed,
119 in progress, 59 existing-unverified, 463 missing, 12 excluded; zero complete
ports**. There are 70 direct ordinary pool identities, 74 including replacements.
**76 native suites and 10 production WASM cases pass.** The
[report](reports/isaac-enemy-port/hosts/README.md) records sources, adaptations,
test corrections and 28 inspected Original-style images. Regular enemies and
required offspring remain the priority; balance/performance and full parity
acceptance are still open.


The [Maw-family checkpoint](reports/isaac-enemy-port/maw_family/checkpoint.json)
adds source-derived normal Maw, Red Maw and Psychic Maw controllers, with the
Psychic Maw's Eternal Fly orbit/release dependency. Required births now survive
resident-room preparation and room changes. A zero-normal lighting defect found
in its halo capture is fixed. Fingerprint `2508db221cb94f34`: **173 definitions,
156 reviewed, 114 in progress, 61 existing-unverified, 466 missing, 12 excluded;
zero complete ports**. There are 65 direct ordinary pool identities, 69 including
replacements. **75 native suites and 6 production WASM cases pass.** See the report
for source gaps, adaptation details and inspected Original-style captures.
Regular enemies and their required offspring remain the priority.


The [Boil family checkpoint](reports/isaac-enemy-port/boils/checkpoint.json)
replaces generic Boil 30.0, Gut 30.1 and Walking Boil/Gut/Sack 88.0/88.1/88.2
behavior and extends Sack 30.2. Stationary bodies regenerate; walkers wander
without healing. Blood volleys, explosive Gut lobs and independently thrown
Spider/Strider offspring use source animation events, physical trajectories
and source-aware damage rules. All six occur in appropriate seeded stage pools.
Fingerprint `bb632c6e46f99362`: **173 definitions, 152 reviewed, 110 in progress,
65 existing-unverified, 466 missing, 12 excluded; zero complete ports**.
The direct ordinary pool has 62 identities, 66 including replacements.
**74 unique native suites and 13 WASM cases pass.** Original-style Linux/WASM
captures were inspected. Hard/champion/control branches, native substitutions,
full readability, balance and controlled performance remain open.
Regular enemies and required offspring remain the priority.


The [Long Legs and Sack checkpoint](reports/isaac-enemy-port/long_legs/checkpoint.json)
adds source-based controllers for Baby/Small Baby Long Legs 206.0/206.1,
Crazy/Small Crazy Long Legs 207.0/207.1, and Sack 30.2. Babies flee and lay
independent children; Crazy variants chase and fire eight-way/diagonal volleys.
Sacks regenerate from 7/20 source HP and throw spiders. The four parents enter
sparse seeded stage pools; Small Baby supplies Sacks. Values are external.
Fingerprint `64bd7ece6bf04647`: **173 definitions, 147 reviewed, 105 in progress,
70 existing-unverified, 466 missing, 12 excluded; zero complete ports**.
The direct ordinary pool has 57 identities, 61 including replacements.
**73 unique native suites pass** across the full run and two seeded witness
corrections; **ten WASM cases pass**. Twelve usable Original-style captures were
inspected. Native special cases, broader readability, balance and controlled
performance acceptance remain open. Regular enemies remain the priority.


The [Strider and Swarm Spider checkpoint](reports/isaac-enemy-port/spider_variants/checkpoint.json)
adds distinct source-based regular-enemy controllers for 814.0.0 and 884.0.0.
Strider rows over deep water and replaces Spider births on wet band-1 floors,
including Big Spider children. Swarm uses three distance-weighted hop patterns,
source-equal collision radius and fireplace-specific contact immunity. Both
appear in actual seeded rooms. A real fireplace contact-delay bug was also fixed.
Fingerprint `834662978ecb9391`: **169 definitions, 142 reviewed, 100 in progress,
71 existing-unverified, 470 missing, 12 excluded; zero complete ports**.
The direct pool has 53 identities, 57 including conditional replacements.
**72 unique native suites pass** across the full run and three fixture-correction
reruns; **eight final-build WASM cases pass**. Original captures were inspected.
Native special branches, broader readability, balance and controlled performance
acceptance remain open. Regular enemies and offspring remain the priority.


The [Spider and Big Spider checkpoint](reports/isaac-enemy-port/spiders/checkpoint.json)
adds source-based regular enemies 85.0.0 and 94.0.0. Both pause and commit to
movement bursts, predict a moving player and respect solid/deep-water barriers.
Big Spider produces two full-health ordinary spiders with opposite grounded
impulses, unless extreme overkill suppresses them. Both occur in actual seeded
early-floor rooms, with sparse pursuit pools across bands 0–2.
Fingerprint `aed14fc9bf892f8c`: **168 definitions, 140 reviewed, 98 in progress,
72 existing-unverified, 471 missing, 12 excluded; zero complete ports**.
The direct pool has 52 identities, 55 including conditional replacements.
**71 unique native suites pass** across the full run and two fixture-correction
reruns; **eight WASM cases pass**. Original captures were inspected. Native
appear/thrown/item/status/grid branches, broader readability, balance and
controlled performance acceptance remain open. Regular enemies and required
offspring remain the priority.


The [Willo and Mullighoul checkpoint](reports/isaac-enemy-port/mullighoul/checkpoint.json)
adds regular enemies 808.0.0 and 817.1.0. Willos share a player-centred elliptical
orbit and take turns attacking with Warn6/Shoot24 timing and wall-passing,
damped shots. Mullighoul hovers across water while respecting solid scenery,
spits full-health Willos and retains population-adjusted death births.
Both occur in actual seeded wet band-1 rooms; a natural Willo room also verifies
interaction with an attraction statue.
Fingerprint `13e2ff60d3fc3643`: **167 definitions, 138 reviewed, 96 in progress,
73 existing-unverified, 472 missing, 12 excluded; zero complete ports**.
The direct pool has 50 identities, 53 including conditional replacements.
All **70 native suites and nine WASM cases pass**. Selected Original captures
were inspected. Owner/status/counter/path and special boss branches, broader
readability, balance and controlled performance acceptance remain open.
Regular enemies and required offspring remain the priority.


The [Prey and Small Leech checkpoint](reports/isaac-enemy-port/prey/checkpoint.json)
adds regular enemies 817.0.0 and 810.0.0, with source-based spawning, thrown death
children, wet swimming and dry hops. Swimming crosses water while preserving
solid cover and room edges. Thrown births use the recovered 0.04 planar factor
and land after 23 source updates; airborne contact/projectile collision restores
on landing. Both enemies occur in actual seeded wet band-1 rooms.
Fingerprint `3aa583b1c562abba`: **165 definitions, 137 reviewed, 94 in progress,
73 existing-unverified, 474 missing, 12 excluded; zero complete ports**.
The direct pool contains 48 identities, 51 with conditional replacements.
All **69 native suites and eight WASM cases pass**; selected Original captures
were inspected. Source status/owner/counter/path details, late geometry changes,
broad balance and controlled performance acceptance remain open. Regular enemies
and required offspring remain the priority ahead of additional bosses.


The [Mulligan family checkpoint](reports/isaac-enemy-port/mulligans/checkpoint.json)
replaces the fixed-age trigger with proved grid-collision checks and a 29-frame
windup. Mulligan gets four independent death children; Mulligoon gets diagonal
shots and a real Troll Bomb; Mulliboom uses the native five-frame proximity test
and immediate blast. All have 41.6 HP and harmless body contact. Early-floor
placement expands the pool to 46 direct identities, 49 with replacements.
All 68 native suites and 10 browser cases have passing coverage (nine from the
full run, one focused capture/sampling retry). Original captures are inspected.
Troll Bomb wall-clock fuse, exact navigation/counter/status behavior and full
balance/performance acceptance remain open. These records are partial ports.


The [Hive/Drowned Hive checkpoint](reports/isaac-enemy-port/hive/checkpoint.json)
replaces generic spawning with source-based evasion, Attack18/Shoot4/cooldown75,
room-wide population delay and independent death offspring. Health is 64/57.6;
Drowned children have half health. Reserved births retry placement and keep
their contact policy after the parent disappears. Hive now has sparse pursuit
placement in bands 0–2; Flooded band 1 can replace it with Drowned Hive.

Fingerprint `b6d232227ffffd87`: **163 monster definitions, 13 item definitions,
136 reviewed, 92 in progress, 73 existing unverified, 476 missing, 12 excluded,
zero complete**. **67 native suites are covered** after correcting a rare-event
seed sample; **eight WASM cases pass**. Original Linux/browser views were
inspected. There are **44 directly weighted pool identities, 46 including
conditional I. Blob and Drowned Hive**. Native path/status/counter details and
full acceptance remain pending. Regular enemies remain first; further boss work
stays deferred. See the [readable report](reports/isaac-enemy-port/hive/README.md).

The preceding Tainted Pooter checkpoint:

The [Tainted Pooter checkpoint](reports/isaac-enemy-port/tainted_pooter/checkpoint.json)
replaces its generic chase/spread with source-based buzzing, 240 HP,
Attack14/Shoot6/delay63, and a four-shot volley retaining the native outer-shot
slowdown. Physical terminal impacts create two smaller backward shots at ±24°.
Timeouts and cancellation do not split; released shots survive owner death.
External profiles and live projectile snapshots preserve reload isolation.

Fingerprint `b0d8066e316c078e`: **163 monster definitions, 13 item definitions,
136 reviewed, 92 in progress, 73 existing unverified, 476 missing, 12 excluded,
zero complete**. **All 66 native suites and five WASM cases pass**. Original
Linux/browser views were inspected. The 43 directly weighted pool identities
plus conditional I. Blob are unchanged. Tainted Pooter's dedicated
Ascent-equivalent route and native height curves remain pending. Regular enemies
remain first; further boss work stays deferred. See the
[readable report](reports/isaac-enemy-port/tainted_pooter/README.md).

The preceding Attack Fly checkpoint:

The [Attack Fly checkpoint](reports/isaac-enemy-port/attack_fly/checkpoint.json)
replaces its generic chase with source-based buzzing pursuit: cached target3,
force2, second-axis scaling, native deadzone/force cap, and 16 HP. Live Hive
summons expire on contact; death offspring remain persistent. Skatole now
transforms Attack Fly to Fly in place without healing damage or awarding a kill.
The unfinished item remains outside natural rewards.

Fingerprint `bef0b7c155852203`: **163 monster definitions, 13 item definitions,
136 reviewed, 91 in progress, 74 existing unverified, 476 missing, 12 excluded,
zero complete**. **65 native suites are covered** after two fixture corrections;
**seven WASM cases pass**. Original
Linux/browser captures were inspected. There are 43 directly weighted pool
identities plus conditional I. Blob. Regular enemies remain first; Tainted
Pooter and other unfinished ordinary fly-family controllers are next. Further
boss work stays deferred. See the
[readable report](reports/isaac-enemy-port/attack_fly/README.md).

The preceding Super Pooter checkpoint:

The [Super Pooter checkpoint](reports/isaac-enemy-port/super_pooter/checkpoint.json)
replaces its generic graph with shared buzzing, source HP (25.6), and native
normal-mode two-shot coefficients (`.961`, `±.276`). Attack14/Shoot6/delay35,
current-target aim, physical elevated shots and whole-pair admission are tested.
Super Pooter now has sparse crossfire placement in all four bands. Configurable
Skatole suppression covers ordinary/Super Pooter, but the unfinished collectible
remains outside natural rewards.

Fingerprint `72c06a2ea58542e1`: **163 monster definitions, 13 item definitions
(one unpooled dependency), 136 reviewed, 91 in progress, 74 existing unverified,
476 missing, 12 excluded, zero complete**. **65 native suites are covered**
after an economy-fixture correction; **six final-build WASM cases pass**.
Linux/browser captures were inspected. There are 42 directly weighted pool
identities plus conditional I. Blob. Regular enemies remain first; Attack Fly
and remaining ordinary fly variants are next. Further boss work stays deferred.
See the [readable report](reports/isaac-enemy-port/super_pooter/README.md).

The preceding ordinary Fly/Pooter checkpoint:

The [ordinary Fly/Pooter checkpoint](reports/isaac-enemy-port/fly_pooter/checkpoint.json)
adds shared buzzing movement, source health and normal-mode Pooter shooting
(Attack14, Shoot6, cooldown35). Normal dung can be shot or bombed; Fly can damage
it and transform into a Pooter while keeping its actor identity and room threat.
The transformation gives no kill reward. Damaged piles and remnants persist.

Fingerprint `7c56c978127ef66`: **163 definitions, 136 reviewed, 91 in progress,
74 existing unverified, 476 missing, 12 excluded, zero complete**. **65 native
suites are covered**, including six affected suites rerun after fixing a real
seed24 cache-approach obstruction; **five final-build WASM cases pass**. Native
and browser generated-room captures were inspected. There are 41 directly
weighted pool identities plus conditional I. Blob. Super/Tainted Pooter,
item/status/parent exceptions, native integration details, full balance and
controlled rendered performance remain unfinished. Regular enemies stay first.

The preceding Horf checkpoint:

The [Horf checkpoint](reports/isaac-enemy-port/horf_fly/checkpoint.json) replaces
the old generic shooter with normal-mode source timing: a 20-frame cast, Shoot
at frame 4, current-target aim and a 28-frame cooldown from acquisition. Horf
now has 32 HP and appears in opening-band rooms. Values live in `horf.mechanics`.

Fingerprint `9c60a5f38a727412`: **163 definitions, 136 reviewed, 90 in progress,
75 existing unverified, 476 missing, 12 excluded, zero complete**. All **64 native
suites are covered** after two fixture-only corrections; **three final-build
WASM cases pass**, with actual Linux/browser generated-room captures inspected.
There are 40 directly weighted pool identities plus conditional I. Blob.
Hard-mode/status/knockback and projectile-height parity, full balance and
controlled rendered performance remain open. Fly's native source preflight is
preserved; its movement and dung interaction are next. Regular enemies and their
required dependencies retain priority over further boss work.

The preceding Crackle checkpoint:

The [Crackle checkpoint](reports/isaac-enemy-port/crackle/checkpoint.json) adds the
regular fire variant's physical lob and separate cardinal fire jets. The jets
cross pits, stop at solid cover, retain their source after its death and damage
only during two brief pulses. Crackle now appears sparsely in standard Broken
Quarry rooms. Its attack and fire values are external configuration.

Fingerprint `79cef7b6589ae5d1`: **163 definitions, 136 reviewed, 89 in progress,
76 existing unverified, 476 missing, 12 excluded, zero complete**. All **63 native
suites and 14 WASM cases pass**. Actual native/browser generated-room captures
were inspected. There are 40 directly weighted pool identities plus conditional
I. Blob. Source spawn-frame/cooldown details, movement/status parity, full balance
and controlled rendered performance remain open. Regular enemies retain priority;
the older Horf/Fly controllers and remaining ordinary families are next.

The preceding Gurgle/Splasher lob checkpoint:

The [regular Gurgle/Splasher lob checkpoint](reports/isaac-enemy-port/gurgle_lobs/checkpoint.json)
replaces delayed ground hazards with visible damped projectiles, collision and
explosion. Gurgle shoots at the current target after its windup; Splasher shoots
along its actual movement. Both now appear as limited specialists in bands 1–3.
Splasher retains its source initial delay when generated or transformed.

Fingerprint `47a8963e629feeec`: **163 definitions, 136 reviewed, 89 in progress,
76 existing unverified, 476 missing, 12 excluded, zero complete**. There are
39 directly weighted pool identities, plus conditional I. Blob. **62 native
suites are covered** after correcting an isolated replacement-test fixture;
the final five affected suites and **11 final WASM cases** pass. Source movement
parity, Crackle's fire-wave attack, broader balance and rendered-performance
acceptance remain open. Regular enemies retain priority over further boss work.

The preceding mortality checkpoint:

The [Gurgle-family mortality checkpoint](reports/isaac-enemy-port/gurgle_mortality/checkpoint.json)
corrects health, source-dependent fire/explosion immunity and Gurgle's 15% in-place
Splasher transformation. Player/allied attacks and TNT remain exceptions. The
transformation preserves identity and room threat, gives no kill reward, restores
stage-scaled Splasher health and rejects sufficiently strong overkill.

Fingerprint `b6613abd43d1890b`: **163 definitions, 136 reviewed records,
89 in progress, 76 existing unverified, 476 missing, 12 excluded, zero complete**.
All **61 native suites** are covered after fixing one old hard-coded HP assertion;
**seven focused WASM cases** pass. The positive browser morph case forces probability
in its disposable filesystem; the production 15% rule passes a seeded native
1,000-trial check. Movement, physical lob attacks, family visuals and ordinary
placement are still unfinished. Gurgle and its Splasher dependency remain next.

The preceding Black Bony checkpoint:

**User priority: regular enemies first.** Continue ordinary-enemy behavior,
required offspring and seeded floor placement before further boss/special encounter
work. Black Bony now repeats the complete throw animation three times, aims
each bone at the current player, and explodes on death. The immediate blast uses
external values and survives event-queue pressure before room completion. Its
dark skeleton and bones distinguish it from ordinary Bony. Sparse ordinary room
roles start in standard Broken Quarry and continue into later bands.

The [Black Bony checkpoint](reports/isaac-enemy-port/black_bony/checkpoint.json)
uses fingerprint `c5b1a1be8d2a9025`: **163 NPC definitions, 134 reviewed records,
86 in progress, 79 existing unverified, 476 missing, 12 excluded, zero complete**.
All **60 native suites** are covered after correcting a rare-replacement test's
sampling, and **six focused WASM cases** pass. Six/six automated starting-loadout
mixed rooms cleared. Special item/status fidelity, human/varied-build balance
and controlled rendered performance remain open. The next regular family is
Gurgle with its required Splasher replacement; its preserved native preflight
already differs from the old generic runtime's death chance and attack timing.

The preceding ordinary Bony increment added cardinal wandering, alignment-based acquisition,
a fast aimed bone on the recovered animation's firing frame, a distinct skeleton
model, and sparse Broken Quarry onward placement. See the
[Bony checkpoint](reports/isaac-enemy-port/bony/checkpoint.json) and
[source/adaptation review](reports/isaac-enemy-port/bony_review/source-review.json).
All **59 native suites** are covered by passing results after a pool-coverage test
fix, and **three focused WASM cases** pass. Five of six starting-loadout mixed
rooms cleared in automated probes; human balance, item/status exceptions and
rendered performance remain open. The Hornfel passenger stays unavailable: native
ordinary acquisition has an explicit Hornfel-spawner guard.

Preceding Bony fingerprint: `a75ed88e17329b04`, **162 NPC definitions**. Checklist:
**133 reviewed, 85 in progress, 79 existing unverified, 477 missing, 12 excluded,
zero complete**. At that checkpoint, among 66 reviewed ordinary records, 49 were in progress,
three retain unverified older implementations, and 14 are missing. This is not
the total ordinary-enemy roster; many source records still await review.

The preceding environmental checkpoint remains historical evidence:

The [partial environmental/transport checkpoint](reports/isaac-enemy-port/hornfel_passengers/checkpoint.json)
adds normal fire and movable TNT as independent rail passengers: special durability,
flame ignition, quiet exits, paired reservations and room-clear cleanup. Five creature
slots remain unavailable. All **58 native suites** and **six focused WASM cases** pass;
the old Hornfel browser timing fixtures still need rediscovery after shared RNG changes.
Its counts were **133 reviewed, 84 in progress, 79 existing unverified, 478 missing,
12 excluded, zero complete**. Source loot/item exceptions, broader placement,
balance and rendered performance remain open. Further Hornfel work is deferred.

- All 653 research tuples and stored XML attributes match the preserved installed
  XML. This is identity verification, not 653 reviewed or implemented behaviors.
- 133 records have reviewed dispositions/contracts: 121 non-excluded records and
  12 confirmed cut/unused records. The exclusions cite specific cut-content
  evidence plus absent authored room/boss-pool routes, and retain every source
  record. Console/glitched-item access is documented rather than mistaken for
  ordinary encounter eligibility. **No full behavior port is certified complete.**
- Peep Eye now uses `68.10.0`. Both boss-eye components are excluded from independent
  selection. Bloat uses its separate body tuple `68.1.0` and owned eye `68.11.0`.
- Peep (`68.0.0`) now has a dedicated controller and Broken Quarry boss pool.
  Normal, cyan and yellow forms retain 8-shot rings, 12-shot jump landings,
  yellow creep and the two eye thresholds. Cyan starts with both eyes; yellow
  is smaller, faster and leaves a trail. Owned Peep Eyes bounce, fly over cover,
  intercept projectiles, respond to bombs and disappear with their owner without
  additional rewards. Failed spawns retry; detached slots and committed jumps
  survive room re-entry. The native canyon bosses remain in the pool.
  `bosses.mechanics` exposes weights, dimensions, pacing and damage. These are
  local tuning; exact native timing/immunity windows and named special-item
  exceptions remain open. This adds one dedicated boss and one owned component
  beyond the 25 ordinary/conditional identities; both records stay **in progress**.
- Bloat now has its own normal/green controller in Abandoned Works and Storm Cut.
  It starts with both eyes detached, performs short in-place hops and longer
  player-directed jumps, emits fixed eight-shot rings and red creep, and fires
  paired lasers forward or to both sides. The source's near-instant, untelegraphed
  laser onset is retained; there is no upward laser. Green Bloat emits two/three
  real arcing explosives instead of the respective hop/jump rings, creates green
  creep and summons two normal Chargers on the large-creep action.
  Owned eyes/lasers disappear with their owner; normal summoned Chargers survive
  as ordinary room threats under the documented DeathWard policy.
- Normal Charger (`23.0.0`) now uses an external cardinal-charge controller:
  slow untargeted wandering, immediate aligned acquisition with line of sight,
  a locked straight dash and collision/recovery. Its ordinary stage pool is
  corrected to bands 1/3; band 2 can still receive green Bloat's summons.
  The variant-specific work below extends this controller. That checkpoint brought
  the routed roster to 25 ordinary/conditional identities plus two dedicated
  bosses and two owned eye identities; registration is still not full acceptance.
- Drowned, Dank and Carrion Princess now use distinct configurable charge modes;
  Level 2 Charger (`855.0.0`) is newly registered with steering during its slower
  dash. Drowned emits four fixed diagonal death shots. Dank reflects from actual
  wall normals, leaves slowing tar only while dashing, and pauses in recovery.
  Princess acquires diagonally and has matching armored-body/pink-tail render
  and hit volumes; a shot's direction alone no longer grants damage. Local
  explosions and fire must reach the tail. Source-specific item exceptions remain
  open. These are movement/geometry adaptations with declared local timing.
- Their stage pools follow positive authored room evidence: Drowned bands 1/2,
  Dank 2, Princess 1 and Level 2 3. Each direct entry is a sparse charge-lane
  specialist with threat cost 4 and cap 1. Drowned replacements retain normal
  Charger source slots and reserve one additional threat point per slot; their
  final room count can therefore exceed the direct-entry cap. The enabled
  ordinary/conditional roster is now **29
  identities**. My Shadow is an item-generated ally, described below; Elleech
  remains an unfinished dedicated encounter.
- A seeded **Flooded Quarry** context enables the source's **50%** normal-to-Drowned
  Charger replacement in band 1. Standard/Flooded floor weights are locally 2:1.
  Damp sediment, the expedition name and ordinary combat-room environment flags
  expose the context while preserving canyon geometry, roads/rivers and story
  sites. This is not full source water-floor rendering. Drowned HP is now exactly
  10% above the local normal Charger value (70.4 versus 64); Drowned Hive children
  retain their half-health contract at 35.2. Dank/Princess use 83.2 HP and Level 2
  uses 128; these apply the documented source-HP times 3.2 conversion.
- My Shadow (`23.0.1`) now has an actual **item/familiar producer**: collectible
  `isaac:collectible:433` is available through seeded Smuggler bargains, the local
  Devil-pool analogue. One delayed shadow follows the player's path, regardless
  of duplicate copies. Enemy contact creates up to 16 room-limited friendly black
  Chargers. They wander, acquire aligned enemies and dash using the shared charge
  controller. Source 20 HP and 8.7 damage become 64 and 27.84 under the declared
  local conversion. Their incoming damage has a separately configured conversion
  and hurt window. Enemy contact/projectiles and damaging hazards hurt them;
  player bullets and ordinary player dynamite do not. Ally deaths are separate
  events without ordinary kill rewards. They never seal exits or survive room
  transitions, while the acquired item persists between floors. A real campaign
  journal round trip preserves its stable item key; live combat is still not saved.
  This is **partial implementation**, not completion of its named item/status
  exceptions or source-exact timings. It never enters a hostile floor pool.
- Elleech (`855.1.0`) is classified as a **dedicated Ascent encounter**,
  backed by 12 positive-weight backwards-room templates; its source listing does
  not authorize ordinary Downpour placement. Its encounter remains unimplemented.
- Seventeen Grimace-family hazard/support tuples have a separate
  [source review](reports/isaac-enemy-port/hazards/source-review.json). Seventeen now
  have partial stationary-hazard controllers in `statues.mechanics`: aimed,
  triple, ballistic, fixed, alternating-cross, fixed/rotating beam, attraction, directional ground waves and bomb supply.
  Fourteen identities enter separate seeded hazard pools; the two always-on Cross
  variants remain debug-only. Physical solids, pressure plates, inactive bodies,
  exceptional respawn and Stone Eye cleared-room removal have concrete checks.
  Bomb Grimace now supports Tuff Twins and Shell; escape routing remains pending. Repentance+ Stone Eye
  startup and Hagalaz destruction are excluded from the 1.7.9b baseline.
  See the [implementation review](reports/isaac-enemy-port/hazards/implementation-review.json)
  for declared local tuning and unresolved item, subtype and trap dependencies.
- Gaping Maw (`235.0.0`) and Broken Gaping Maw (`236.0.0`) now apply real
  attraction to the player and both projectile factions without emitting shots.
  Broken alternates four seconds active/inactive with stronger force. A planar
  field preserves swept movement, arrow aim and projectile gravity; keyboard,
  mouse movement and dodge can counter the configured attraction. Plates disable
  it; ordinary combat clearance does not. Cycle state pauses in inactive rooms
  and survives re-entry. Fields never act in corridors. External force strength,
  falloff/range, vertical extent, stacking cap and startup/offscreen policy are
  declared 3D adaptations. Both identities have source-backed optional hazard
  routes in bands 1–3 and reachable plates; the opening band is unchanged.
  Named item/reroll exceptions and full acceptance remain open. See the
  [Maw review](reports/isaac-enemy-port/maws/source-review.json).
- Four Quake Grimace identities (`804.0.0`–`.3`) now hop in place and emit
  moving rock fronts on the source three-second landing cycle. Animation axes
  remain fixed left/up/right/down. Swept contacts respect cover and room bounds;
  ordinary combat clearance leaves them active and plates stop future landings.
  Separate source-band-1 placements require an inward axis, usable attack lane
  and reachable plate. A wave opens the current optional cache wall without
  spending dynamite, and breaks cracked rock. This is an explicit local analogue;
  it does not implement the source's full secret/super-secret-room graph.
  Timing dimensions, force/damage conversion and geometry policy remain declared
  adaptations. See the [Quake review](reports/isaac-enemy-port/quake/source-review.json).
- Coal remnant tuples `33.11.0`–`33.11.3` now cite Coal Spider's behavior instead
  of the unrelated A Lump of Coal item. Their subtype differences remain open.
- Tuff Twins (`19.2.0`) has two six-part chains, real Bomb Grimace supply,
  independent 15-point armor, exposed 112-HP parts, split/head promotion and one
  aggregate reward. Standard Broken Quarry has a dedicated weighted boss route;
  Flooded Quarry, tutorial and Mine do not. Ink/Sucker offspring have corrected
  32 HP and diagonal/cardinal death shots; Ink leaves slowing black creep, not
  damaging creep or extra projectile-impact puddles. Motion, attack timings,
  linear explosive attenuation and no armor spillover are declared local tuning.
  Short fragments reattach under a provisional policy; native split edge cases,
  named item interactions and full balance acceptance remain open. See the
  [Tuff review](reports/isaac-enemy-port/tuff/source-review.json). No new record
  is certified complete.
- Dragon Fly X (`25.3.1`) now joins its own diagonal-fire section instead of
  inheriting the cardinal-fire variant's generic index label. The installed
  `#DRAGON_FLY_X` name and pinned article agree on the subtype identity.
- Normal canyon pools now load from `assets/mechanics/encounters.mechanics`:
  bands, weights, threat costs and room caps are external. This migrates the
  existing 13 roles; it does not enable the unreviewed catalog. Maggots and Chargers
  begin in Broken Quarry rather than Outer Washes. Tutorial, Classic and Mine
  selection retain their existing paths.
- Five exact Rotten Gaper subtypes (`10.3.1`–`10.3.5`) now enter **Storm Cut only**,
  expanding the previous 13-role pool. They have separate pursuit speeds,
  a timed brood behavior, or inertial circling, plus stable procedural visual cues.
  Each subtype has a room cap of one; threat costs are 3/3/5/2/4. The `.0` default
  dispatch remains unverified and stays outside natural/floor pools with an
  explicitly provisional `.1` debug behavior alias.
- Horf, Gusher, Pacer, Pooter and Super Pooter use behavior graphs. Gusher fires a
  short-lived shot along its wandering direction; Pooters drift slowly and Super
  Pooter fires a pair. Flaming Gaper's unsupported fire trail is removed.
  Item reactions, full death behavior, visuals and other per-record gaps remain
  listed in the checklist.
- Death recipes in `assets/mechanics/deaths.mechanics` define weighted offspring,
  empty outcomes, inclusive post-hit overkill suppression, child health scaling
  and split direction. Ordinary Gaper uses 50% no child, one-third Pacer and
  one-sixth Gusher. Sharing those weights with Frowning/Flaming Gapers is
  explicitly provisional. Moter splits perpendicular to the player approach;
  Drowned Hive offspring have half normal Charger health. Mixed fly weights
  and counts remain local tuning where the source does not specify them.
- Mulligan and Mulligoon no longer deal contact damage. Voluntary detonation
  is recorded separately from ordinary death, so synthetic lethal damage does
  not suppress its children and an old actor killed normally does not gain an
  extra self-detonation burst. Their exact detonation trigger still needs work.
  Mulliboom's death explosion no longer uses the Troll Bomb fuse.
- Globin's maximum health decreases on collapse. Cursed Globin's two goo bodies
  receive the same reduction exactly once and have a configured split limit.
  Retention fractions, goo HP, regeneration delay and split cap are documented
  DeathWard tuning. Collapsed bodies remain room threats; finishing goo prevents
  regeneration and rewards only the true kill.
- The new reviewed contracts cover Rotten Gaper subtypes, Clotty, Mulligan/Hive,
  Charger, Globin, Boom Fly, Moter, Small Maggot and Ring Fly families. This is an
  implementation queue, not a claim those families now match Isaac. Rotten's
  fabricated temperament/spitting logic has been removed. Small Maggots now
  emerge, then pursue slowly; their 0.5-second pause and 0.65-unit speed are local
  tuning. Frowning/Globin speeds also now preserve the reviewed relative hierarchy.
- State graphs support bounded `summon` actions and accelerating `orbit` motion.
  Summon ownership is separate from linked body parts and attack targets, counts
  pending children and survives room re-entry. Rotten brood emits one maggot
  every two seconds, up to six live children. Its death leaves those children
  active.
- Ring Fly now uses an externally configured translating formation, with at most
  ten members and stable angular slots. Deaths leave gaps; neither founder nor
  summoner death removes the remaining group. The center uses flight clearance
  for the whole ring, while each member retains actual airborne height. Group
  state survives room re-entry. Pink bodies distinguish the family in the
  Original style. Item/status interactions and full acceptance remain open.
  Four-member groups are eligible in pursuit rooms from Outer Washes through
  Abandoned Works, costing three threat points and four actor slots. This raises
  the enabled pool to **19 identities**. Group size, cost, geometry and speeds
  are explicit DeathWard tuning; the source establishes the ten-member maximum.
- Clotty, Clot, I.Blob and Grilled Clotty now use continuous-wander graphs with
  fixed cardinal, diagonal, eight-way or slightly offset volleys. I.Blob no longer
  rotates its launch axes with actor age. Clot's short-lived tar shots produce
  the existing slowing patch; Grilled uses ember-looking shots without invented
  ground-fire patches. Grilled's higher movement speed is retained; the source
  does not establish faster firing. Fire reactions now use the system below;
  replacement rules are now implemented below; complete environment/item integration remains open.
- Cloggy (`872.0.0`) now has four brown shots that curve in alternating directions
  on successive volleys. External graph fields specify radial launch axes,
  shot kind and angular velocity. Volley parity survives stun and room re-entry;
  shots continue independently after the shooter dies. Cloggy is limited to
  **one specialist in Broken Quarry crossfire rooms**, bringing enabled pools
  to **20 identities**. Brown-shot contrast was improved after inspecting the
  first captures. Values and procedural appearances are DeathWard adaptations,
  not extracted Isaac attack constants or art.
- External `fire.mechanics` rules now distinguish physical hits, flame contact
  and burning damage. Clotty becomes Grilled in dry rooms without a kill/reward;
  a flooded room disables this rule and permits ordinary fire damage. Hopper
  becomes Flaming Hopper on flame contact; burning damage still hurts it.
  In-place transformation retains entity/team/owner/stun and a configurable HP
  policy. Fractional HP retention is local tuning, not a verified Isaac value.
  Real fire checks cover, height, activation/expiry and a shared target cooldown.
  Elevated fire now renders at its actual height. The two Hopper records have
  reviewed contracts and partial fire tests; their locomotion and stage work
  is described below. Replacement routing follows; complete acceptance remains open.
  The room condition is not flooded map art or a Flush item; typed burning hits
  are not yet a timed status system. Grilled burning/flooded inheritance remains
  an explicitly provisional family interpretation requiring direct verification.
- Normal and Flaming Hopper now use `hops.mechanics` with separate detection
  ranges, wander/chase distances, flight durations and bounded arc heights.
  Both wander outside detection range; Flaming no longer pursues unconditionally.
  Jumps lock a legal landing point, cross interior cover/deep water, and respect
  enclosing cliffs, gates and room bounds. Actual body height drives collision,
  aiming and fire exposure. Compatible fire transformation, stun and room
  re-entry preserve committed flight. This is a 3D adaptation with explicit local
  dimensions/timing; it is not a claim of measured Isaac physics.
  Both forms enter sparse pursuit groups in bands 0–2, supported by authored
  Basement/Caves/Depths room records. Normal has cost 2/cap 2; Flaming cost 3/cap 1.
  This previous checkpoint enabled **22 identities**. Conditional replacement
  routing is added below; full item/status rules and complete acceptance remain open.
- `replacements.mechanics` now preserves source spawn conditions: I.Blob replaces
  a selected Clotty or Clot with **1%** probability; normal Hopper becomes Flaming
  Hopper with **60%** probability specifically in **Scorched Washes**, a seeded
  Burning Basement encounter-context analogue. Opening context weights are
  Standard 2 / Scorched 1, an explicit DeathWard choice. Sparse ground deposits
  and the expedition-screen name identify it without a global rendering filter.
  Conditional encounter entries admit Grilled there; Clot enters bands 1–3, and
  ordinary Clotty now stays in bands 1 and 3 rather than acquiring a Depths route.
  Delayed Clotty/Clot introduction and Grilled's unfinished Chest-equivalent route
  are documented adaptations/gaps. The enabled roster now has **25 identities**.
  Replacement runs once on original slots, on a separate seeded stream. Extra
  threat is reserved before the roll; source caps apply. Explicit/debug/offspring
  spawns bypass substitution, and re-entry never rerolls existing residents.
- Ground pursuit now steers around other bodies, with bounded physical
  separation before projectile collision. Corrections sweep through terrain;
  stationary shooters remain anchored and player movement/dodging stays under
  player control. Body clearance, rather than a thin sight ray, determines
  whether pursuit needs a route around cover. Deterministic yielding lets a
  crowd queue through a narrow opening. These collision/steering constants are
  explicit DeathWard adaptations. Intangible states, linked formations
  and room hazards retain their separate, still incomplete policies.
- Flying definitions now cross interior rocks, props and deep water using a
  separate navigation surface. Enclosing canyon cliffs, closed gates and the
  active room boundary remain solid. Actual positions and hitboxes rise above
  cover; elevated mouse picking, downward enemy shots, arrow elevation assistance
  and vertical homing follow those positions. Flight clearance uses the canyon
  shape before interior rocks are added, preserving later river/road cuts.
  This is a documented 3D adaptation; it does not implement every flying family's
  transformation, formation, item reaction or special movement rule.
- `--smoke --scene enemy-14.1.0 --theme canyon --style original --frames 42`
  isolates a registered actor in the canyon arena for native/WASM capture. It
  uses a temporary save, an invulnerable stationary player and no player firing.
  Unimplemented IDs fail explicitly. This is the capture foundation; interactive
  reset/state/hitbox controls and comprehensive scripted cases remain open.
  Repeated `--enemy-hit FRAME DAMAGE` options now exercise damage, collapse,
  regrowth and final death in that arena on Linux and WASM.
  `--enemy-terrain cover|river` adds a crate or selects an actual seeded interior
  river crossing for flight checks; browser probes expose height and water state.
  `--enemy-flame-hit FRAME DAMAGE`, `--enemy-burn-hit FRAME DAMAGE`,
  `--enemy-fire FRAME` and `--enemy-flooded` exercise fire interactions. Browser
  typed hits use `FRAME:DAMAGE`. River banks do not imply room-wide flooding.
  `--enemy-terrain hop-cover` places a configured Hopper beside a crate for a
  committed crossing; browser probes expose the arc and actual grounded clearance.
  `--scene resident-ID --resident-seed N --resident-floor N` instead captures an
  actual Rourke-account floor resident with its generated companions/cooldown.
  `--resident-from ID` filters the source slot. It fails if no matching actor
  exists; it never silently spawns one. The spectator alone is invulnerable.

Milestone 1 is still in progress. The Peep/Bloat/Tuff/Shell/Loki controllers, owned parts and
external pools extend the vertical slice, but their remaining acceptance gaps
and the unfinished population review prevent completion of the milestones.

The latest [passenger source review](reports/isaac-enemy-port/hornfel_passenger_review/source-review.json)
resolves the separate `1000.152` controller and its seven payloads: Quakey,
Danny, Faceless, Bony, Gurgle, a normal fireplace and movable TNT. The controller
uses an initial 150–359-update timeout; later intervals are halved only in rooms
larger than 135 grid cells. It admits carts through unreserved paired doors,
stops spawning when no bosses remain, and cleans up mounted actors when the room
clears. These are distinct conditions. Fire and TNT require special durability
and destruction behavior, rather than ordinary linear enemy HP.

The review preserves 26 bounded native code windows, the exact dispatch/table
and API anchors. Verify them with
`python3 scripts/isaac-reference/analyze-hornfel-passengers.py --check`.
Five additional creature contracts bring the checklist to **133 reviewed**;
implementation counts remain **82 in progress, 79 existing unverified, 480 missing,
12 excluded and zero complete**. This pass changes no runtime or pool selection.
The [implementation handoff](reports/isaac-enemy-port/hornfel_passenger_review/implementation-plan.json)
separates shared transport, environmental payloads, creature AI and encounter
acceptance. No generic passenger substitute is approved.

The preceding runtime checkpoint was the Hornfel escort increment, fingerprint `18c70b73086ac372`.
Ordinary rail entries can spawn a distance- and population-gated pair of real
Fly Bombs. They use soft parent-aware steering, retain the living rider as their
parent after cart loss, and detach on his ordinary exit with at most 11.2 HP.
Removing the parent releases survivors without that exit-only HP cap. They stay
ordinary room-clear threats and follow the existing summoned-offspring rule
against coin farming. Both new external configuration rows are validated.

The [source review](reports/isaac-enemy-port/hornfel_escorts/source-review.json)
separates recovered native forces from local clock, friction and 3D conversions.
All **57 native suites and 17 selected WASM cases** pass on this build. Earlier
broader browser results remain historical evidence. Six automated starting-kit
fights clear **3/6**; balance and rendered performance acceptance remain open.
See the [checkpoint](reports/isaac-enemy-port/hornfel_escorts/checkpoint.json).
At that runtime checkpoint the checklist had **128 reviewed, 82 in progress,
79 existing unverified, 480 missing, 12 excluded, zero complete**. The newer
source review above supplies the passenger implementation requirements;
inherited tiny-bomb behavior and encounter acceptance also remain unfinished.

The preceding Hornfel decoy increment used fingerprint `cc88d803c4f27347`:
**159 NPC definitions, 12 items, five hostile bomb profiles and 15 rail layouts**.
`906.1.0` is created by the existing Broken Quarry Hornfel encounter. Decoys reserve
separate entrance/exit pairs, retain four hit-health points with the recovered
per-hit rules, and leave quietly at the end of their rail. Damage or contact
destruction produces an immediate blast and six physical Troll Bombs. Pending
salvos retain their chosen velocities and have a bounded lifetime record when
capacity is unavailable. Configuration stays in `assets/mechanics/hornfel.mechanics`.
See the [implementation review](reports/isaac-enemy-port/hornfel_decoys/implementation-review.json)
and [native source review](reports/isaac-enemy-port/hornfel_decoys/source-review.json).

All 57 native suites passed, with an additional retained-death capacity contract.
The initial browser regression passed 147 cases; all 11 Hornfel cases passed on
the final build, including contact destruction. This is 148 distinct cases across
two builds, with 137 unrelated cases on the initial build. The
[checkpoint](reports/isaac-enemy-port/hornfel_decoys/checkpoint.json) preserves each
segment and build hash. Six automated starting-kit fights clear 3/6, so balance
acceptance remains open. Counts are **128 reviewed, 82 in progress, 79 existing
unverified, 480 missing, 12 excluded, zero complete**. Native room-controller timing,
passenger carts, escorts, source reward rules, item/status exceptions and full
acceptance remain unfinished. The next escort review records the native parent
attachment and exit-time HP clamp without claiming an implemented escort.

The preceding Hornfel charge/recovery increment used fingerprint `28be346a260e0f07`.
It retains **158 NPC definitions, 12 items, five hostile bomb profiles and 15 rail
layouts**, with no new ordinary pool or boss-band entry. Eligible distinct paired
doors select seven to nine accelerating passes on the original track, then a
separate recovery traversal. The frame-46 fireball produces four persistent
cardinal flame trails. Recovery ends at the physical exit; the fireball can land
after the cart has left. Emitted flames stop at cover/pits, pause in inactive
rooms, and survive producer death and ordinary clear. See the
[implementation review](reports/isaac-enemy-port/hornfel_charge/implementation-review.json).

The new drive/cooldown/ballistic/fire settings are external and validated. Native
force/friction and animation constants are distinguished from local integration,
elapsed cooldowns and fire propagation values. All 57 native suites passed;
additional focused checks cover invalid configurations, immutable content
snapshots, pit boundaries, real fire reactions and damageable companions.
All eight Hornfel browser cases passed with the refined flame rendering. The
broader regression covers145 distinct browser cases across two renderer builds
with identical mechanics;93cases use the final flame rendering. The
[checkpoint](reports/isaac-enemy-port/hornfel_charge/checkpoint.json) preserves
segment/build hashes and the repaired screenshot-timing fixture.
Four starting-kit fights cleared in 44.3–102.6 seconds at 12.5–62.5 HP. These
automated inputs and CPU-only timings do not establish varied-build balance or
rendered performance acceptance. Decoys, escorts/passengers, special rewards,
optional encounters, source-exact physics and the six full acceptance gates
remain unfinished. Checklist counts are unchanged: **128 reviewed, 81 in progress,
79 existing-unverified, 481 missing, 12 excluded, zero complete**.

The preceding [Hornfel charge review](reports/isaac-enemy-port/hornfel_charge_review/source-review.json)
preserves seven more bounded native windows and the installed API registration
for `FireBossProjectiles`. That checkpoint was analysis only. It resolves the
same-track repeat count (six to eight repeats
after the initial fast pass), original-door recovery, the frame-46 projectile
event and its `FIRE_WAVE` flag. Recovery continues until rail exit; the 87-frame
animation does not itself end that state. The cart's charge parameter feeds
acceleration/friction, rather than being a direct speed. `FireBossProjectiles`'s
third argument is a trajectory modifier, not established projectile speed.

The review also corrects an earlier timing assumption: the 100/150 charge/mine
cooldown counters decrement through a scaled-counter crossing helper, rather
than unconditionally once per AI update. The current five-second mine cooldown
remains local tuning until those clock fields are verified. Source values must
not be described as exact seconds merely by dividing by 30. The newer API
signature did not match this executable; its installed function/name registration
provides the method identity. See the [review checkpoint](reports/isaac-enemy-port/hornfel_charge_review/checkpoint.json)
for preserved hashes, scope and the remaining implementation work.

The preceding partial Hornfel controller used fingerprint `99a48de5cb37b4bb`:
**158 NPC definitions, 12 items, five hostile bomb profiles and 15 rail layouts**.
Ten normal source templates now form seeded Standard Broken Quarry boss arenas.
Separate typed cart (`965.0`) and door (`967.0`) components support the actual
`906.0` rider, source-timed single/double throws and Brimstone mine salvos.
Cart loss changes 768 HP to a grounded 320-HP fleeing phase. Killing and escape
both resolve the encounter; only killing adds three dynamite and a kill event.
The source collectible bonus is not implemented.

The [controller review](reports/isaac-enemy-port/hornfel_controller/source-review.json)
separates recovered behavior from local world-unit/timing adaptations. Source
ordinary pits and rocks are retained, restricted entrance sides are respected,
and the navigation footprint is rebuilt after reshaping the canyon terrain.
All ten normal templates pass native entry/exit and actual grounded escape
checks. Existing story requirements remain necessary for the floor exit.
Native minecart signatures now support centered straight crossing and end-stop
reversal; exact curves, projection and turning offsets remain adaptations.

At that checkpoint, charge/recovery, decoys, other cart passengers, source
fireplace props, special item rules and optional encounter routes were unfinished. Checklist:
**128 reviewed, 81 in progress, 79 existing-unverified, 481 missing, 12 excluded,
zero complete**. All **57 native suites** pass. Four final native captures and
all **142 rendered browser cases** pass after the dry-pit water-render correction.
Four starting-kit fights cleared in 55.9–84.3 seconds at 37.5–62.5 HP, with no
items, bomb use, invulnerability or combat teleports. This is automated-input
evidence, not human or mixed-build acceptance. CPU-only step measurements do
not establish rendered native/WASM performance. See the
[controller checkpoint](reports/isaac-enemy-port/hornfel_controller/checkpoint.json);
older results below retain their original scope and fingerprints.

The preceding rail/source checkpoint used fingerprint `ebae5e0738972c1`:
**157 NPC definitions, 12 items, five hostile bomb profiles and 15 rail layouts**.
The [rail source manifest](reports/isaac-enemy-port/hornfel/rail-source.json)
preserves 928 cells, 30 rail-over-pit cells and separate normal/Double Trouble/Void
categories. All 121 wall entries have bounded routes. Reciprocal ports, curved
movement and actual swept segments are validated in 120 fitted footprints.
Vertical end caps are corrected to `9 = south port`, `10 = north port`, resolving
the five unmatched ports in the preceding candidate analysis. Straight crossing
traversal and end-stop reversal remain explicit local policies until the native
minecart controller is reviewed. No new enemy enters a floor pool yet.

The [native review](reports/isaac-enemy-port/hornfel/native-review.json) preserves
bounded disassembly from the verified installed 1.7.9b executable and five
checksum-verified animation metadata files. Hornfel selects regular (`4.0`),
Hot (`4.8`) and Bloody Sad (`4.16`) bombs with weights 6:3:1. The runtime payload
identities are corrected; the controller's selection logic is still pending.
The mine attack makes three bombs, or four when the native room-grid area exceeds
135. Cart loss resets HP to 100 before the fleeing phase, rather than triggering
at a guessed health fraction. Authored animations run at 30 FPS: single throws
fire at frame 17, double throws at 17/27, and mines at 34. Native launch arithmetic
is recovered but not implemented; current flight/fuse values remain local.
Decoys also require special per-hit damage handling, not ordinary 4-HP targets.

All **56 native suites** passed after rail integration; the three affected suites
passed again after the final payload identity corrections. The same rail tests
passed in browser WASM, and all **five focused rendered payload cases** passed
without JavaScript/WebGL errors. The complete browser suite was not rerun in this
batch; its preceding 136-case result belongs to the older ordnance fingerprint.
The [checkpoint](reports/isaac-enemy-port/hornfel/checkpoint.json) distinguishes
these scopes. Native/WASM captures confirm isolated payload presentation only.
CPU measurements cover content loading and rail traversal, not rendered boss
performance. Hornfel, his decoys, cart actors, doors, pit collisions, seeded
encounters and fight balance remain unfinished. Checklist totals are unchanged:
**128 reviewed, 78 in progress, 79 existing-unverified, 484 missing, 12 excluded,
zero complete**. The full goal remains active.

The preceding hostile ordnance foundation used fingerprint `2801c8cd382db5bd`:
**157 NPC definitions, 12 items and four separate bomb payload profiles**.
Normal blasts, Hot contact/fire, Sad's ten-shot ring and Brimstone's four cardinal
beams now share bounded, room-persistent ordnance. They use explicit hostile
damage and immutable configuration, with no player item scaling. Whole bursts
wait when event/projectile capacity is exhausted. The
[source review](reports/isaac-enemy-port/ordnance/source-review.json) separates
documented payload shapes from unmeasured hostile values and local policies.

All **55 native suites** and **136 WASM cases** pass, including four focused
component cases, with no JavaScript/WebGL errors. The
[checkpoint](reports/isaac-enemy-port/ordnance/checkpoint.json) preserves the
results, screenshots and source review. These isolated payload probes do **not**
establish Hornfel/Horny Boys gameplay reachability: their dedicated controllers,
rail arenas, phases, carriers and special interactions still need implementation.
No additional NPC record is counted as implemented or complete. The checklist
remains **128 reviewed, 78 in progress, 79 existing-unverified, 484 missing,
12 excluded and zero complete**. The full 653-record goal remains active.

The [preceding Hornfel geometry study](reports/isaac-enemy-port/ordnance/hornfel-rail-preflight.json)
preserves 16 installed templates, including the special layouts and separate
Void entries. Its provisional vertical end-cap assignment is superseded above.
Ordinary rails and rails over pits need real traversal and carrier
ownership; a rail decoration over generic wandering AI is insufficient.
Three CPU-only payload stress cases stayed within the configured storage limits.
This does not establish rendered performance, boss balance or final readability:
the armed models are small at the default zoom, fire overlaps blast particles,
and long Brimstone rays can extend outside the camera view.

The preceding Loki/Lokii batch uses fingerprint `8c776d256f195ffa`: **157 NPC
definitions and 12 items**. Both bosses have dedicated controllers, grounded
teleports, ordered cardinal/diagonal/cardinal volleys, eight-shot rings and
variant-specific Boom Fly summons. Lokii creates two independent 1120-HP halves
atomically, retains aggregate health after either half dies, and pays one boss
reward. Summoned flies still gate room clear; story evidence still gates leaving
the floor. Loki enters Abandoned Works and Lokii enters Storm Cut. Full source
behavior and the explicit local timing, health and lifetime policies are separated
in the [source review](reports/isaac-enemy-port/loki/source-review.json).

All **54 native suites** pass, including actual generated encounters and the
170-floor progression regression. All **132 browser cases** pass with no
JavaScript/WebGL errors, including five new Loki/Lokii cases and the previous
Tainted explosion artifact regression. Eight generated
starting-kit fights clear with no items, bombs, god mode or combat teleports,
ending at 50–100 HP; this is limited automated balance evidence. CPU-only step
measurements cover one Loki, one Lokii pair and twelve pairs; they do not establish
rendered Linux/WASM performance. The [checkpoint](reports/isaac-enemy-port/loki/checkpoint.json)
retains the logs, captures, hashes and remaining gaps. The [artifact comparison](reports/isaac-enemy-port/loki/artifact-regression.json)
preserves both the failure and the fixed native/WASM captures: a barrel-warning
line in the lit primitive pass produced the black region, removed by drawing
the warning with thin triangle geometry.

The checklist has **128 reviewed, 78 in progress, 79 existing-unverified,
484 missing, 12 excluded and zero complete records**. Meat Cleaver conversion,
optional Poky/four-corner Grimace layouts, special source encounter routes and
full validation remain open. The full 653-record goal remains active.

The preceding Boom Fly family checkpoint uses fingerprint `457b314e1d705383`:
**155 NPC definitions and 12 items**, with **36 ordinary/conditional identities**
in seeded pools. Seven Boom Fly variants have distinct diagonal motion and
source stage-scaled health, immediate blasts, cardinal bone shooting, cross/X
fire or gas/death volleys. Tainted has a partial delayed explosion-chain controller;
its Ascent route and adaptive armor remain missing. Skatole, Beelzebub, champions
and full acceptance remain open. The [source review](reports/isaac-enemy-port/boom_flies/source-review.json)
separates source facts from local damage, timers, terrain and lifetime policies.

All **53 native suites** passed in the final full run, including the new family
suite and existing generated-floor regressions. All **127 browser cases** passed
with no JavaScript/WebGL errors: fifteen new family/resident cases and 112 prior
cases. A stale Fly Bomb resident fixture was refreshed from actual generation
(seed 19 / floor 2 / room 8), not replaced with a forced actor. Initial failures and
visual findings are retained in the [checkpoint](reports/isaac-enemy-port/boom_flies/checkpoint.json).
Seven starting-kit autopilot rooms cleared without items or bomb use; six ended
at 100 HP, one at 75 HP. This is limited balance evidence. CPU-only stress measurements
are not rendered Linux/WASM performance acceptance.

Checklist at the Boom Fly checkpoint: **128 reviewed, 76 in progress, 79 existing-unverified,
486 missing, 12 excluded and zero complete records**. Seven newly reviewed
Loki/Lokii/Hornfel/Horny Boys and component contracts were entirely unimplemented
at that checkpoint; the current Loki batch above advances two of them.
The [dependency review](reports/isaac-enemy-port/boom_flies/next-contracts.json)
corrects Hornfel Decoy to `906.1.0`; `967.0.0` is his rail door. The external `1000.152` room
controller is also required. Continue with the [next engine/dependency review](reports/isaac-enemy-port/boom_flies/next-dependency-review.json),
including stage-health transformations before migrating a transforming family.

The preceding Shell checkpoint uses fingerprint `b72f26fd9c7309c5`: **155 NPC
definitions and 12 items**. Shell `19.3.0` is a dedicated standard Broken Quarry
boss with two five-part chains in a doubled arena. Heads are invulnerable;
15-point bone armor protects 112-HP bodies. Exposed flesh becomes grounded,
slows attached chains, shoots aimed triples from middle sections, and spawns
real Fly Bombs from ends. Detached groups pursue slowly; single flesh stays put.
Contiguous split rules, automatic head/armor retirement and landing above
cover/water are explicit local policies in the [source review](reports/isaac-enemy-port/shell/source-review.json).
Tuff's explosive resistance and exposed acceleration are not copied.

All **52 native suites** and **112 browser cases** pass, including four new Shell
cases and 170 generated-floor regressions. Natural Shell fixtures are seed7
floor2, seed23 floor2 and seed28 floor3 (zero-based), each with reachable bomb
supplies. The larger arena preserves floor room counts and repacks room extents
to keep passages separated. A normal-input starting-kit autopilot clears those
three fights at 100/37.5/50 HP in 22.57/19.57/33.88 seconds, with 24 shot damage,
no items, no initial dynamite, no god mode or fight-time teleports. This is
limited balance evidence. CPU-only synthetic-room timings are retained separately;
they do not establish rendered canyon or browser frame-budget acceptance.

The [checkpoint](reports/isaac-enemy-port/shell/checkpoint.json) retains exact
build/source hashes, tests, screenshots and probes. The new boss-pool weights
move Tuff's browser fixture to seed10/floor2 and cyan Peep to seed21/floor2;
both still use real generated encounters. Promotion now restores diagonal head
motion even if the former body was following a cardinal path. Browser probes
retain actual cover landing and delayed collateral barrel explosions.

Checklist at the Shell checkpoint: **121 reviewed, 68 in progress, 87 existing-unverified,
486 missing, 12 excluded; zero fully accepted ports**. Native timing/split edge
cases, named item exceptions, special source routes, human/mixed-build balance,
all-camera readability and full performance acceptance remain open. The Horny
Boys producer still blocks Eternal Fly Bomb gameplay reachability.

The preceding Fly Bomb checkpoint used fingerprint `399a66917e81589c`: **154 NPC
definitions and 12 items**. Fly Bomb `819.0.0` now has circling flight, immediate
40-damage contact explosions and delayed 100-damage death ordnance. Player
damage uses the declared half/full-heart conversion (12.5/25 after the existing
hostile multiplier). The lit bombs survive ordinary room clear, pause while
their room is inactive, and use real blast/demolition handling without consuming
player inventory. Standard Broken Quarry has a sparse ordinary route, verified
in seeds 0, 4 and 10, floor 2 (zero-based).

Eternal Fly Bomb `819.1.0` has a real Boom Fly owner and three stable orbital
slots, ordinary damage immunity, contact detonation and owner-death bomb drops.
**The Horny Boys producer is not implemented**, so this remains an unrouted
dependency, not an accepted gameplay encounter. At that checkpoint Shell's normal
Fly Bomb spawning was pending; the Shell checkpoint above now supplies that route. The [source review](reports/isaac-enemy-port/fly_bombs/source-review.json)
distinguishes source behavior from local speed/fuse/geometry and the inferred
Small Bomb `4.14.0` mapping.

All **51 native suites** passed in one run, including **170 generated floors**;
the focused Fly Bomb suite then passed an added real rock-demolition check.
All **108 browser cases** passed with no JavaScript/WebGL errors. Four new
cases cover normal pursuit, post-clear death ordnance, owned lifecycle and a
natural resident. The [checkpoint](reports/isaac-enemy-port/fly_bombs/checkpoint.json)
retains exact artifacts and hashes. Native render inspection found and fixed a
degenerate line-halo artifact; initial failures are retained. The changed pool
also moved the natural I.Blob fixture to seed 92, floor 2, room 4; tests preserve
normal substitution odds. A starting-kit autopilot cleared three four-actor
Fly Bomb rooms at 100 HP in 2.05–2.64 seconds without items or bomb use. This is
limited balance evidence, not full acceptance.

That checklist had **120 reviewed, 67 in progress, 87 existing-unverified,
487 missing, 12 excluded; zero fully accepted ports**. Named fly-item exceptions,
exact native tuning, all-camera readability and controlled performance remain
open. Continue with the [Shell/Horny Boys dependency review](reports/isaac-enemy-port/fly_bombs/next-dependency-review.json).

The preceding Tuff checkpoint used fingerprint `f165227c92c50f2a`: **152 NPC
definitions and 12 items**. Its [source review](reports/isaac-enemy-port/tuff/source-review.json)
separates sourced armor/segment rules from local timings, attenuation and short-tail
policy. Fifty native suites passed in a single full run, including generated
floor routing; the new controller additionally checks actual zero-inventory
bomb pickup/fuse/explosion, shared offspring caps, room persistence and one reward.
Three independent generated Tuff arenas have reachable supplies. The starting-kit
probe then played these arenas through normal input: seeds 9 and 23 cleared with
12.5 HP; seed 1 died with four exposed parts left. This is **partial balance
evidence**, not human-play acceptance. The [probe log](reports/isaac-enemy-port/tuff/generated-balance-probe.txt)
preserves successes and failure. Source-exact split edge cases, named-item
exceptions, independent Sucker/Ink routing and controlled performance remain open.
That checklist had **118 reviewed, 65 in progress, 87 existing-unverified,
489 missing, 12 excluded; zero fully accepted ports**.

The full **104-case WASM run passed** without JavaScript/WebGL errors: five new
Tuff/flyer cases and all 99 preceding regressions. The
[checkpoint](reports/isaac-enemy-port/tuff/checkpoint.json) retains per-case state,
captures and hashes. Isolated browser blasts exercise real explosion handling;
the separate native supply test verifies pickup and fuse through normal input.
Initial fixture, timing and collateral-barrel assertion failures are preserved
under `tuff/first-run`, together with the source correction for Ink's creep.

The next [dependency review](reports/isaac-enemy-port/tuff/next-dependency-review.json)
orders Fly Bomb and its owned variant before The Shell. Shell's flight, grounded
flesh and ambiguous split/promotion rules require a separate controller; Tuff's
resistance and acceleration must not silently carry over.

Bomb Grimace `809.0.0` now has real supplied ordnance: unlit pickup `5.41.0`
becomes armed bomb `4.13.0` on contact. These two component identities are outside
the 653-record enemy checklist. Taking starts the fuse and schedules replacement;
throwing/placing preserves it, consumes no ordinary inventory and does not fire
the revolver. Mouse approach/throw, arrow aim, B and the HUD work at zero inventory.
Held explosions hurt the player. Exceptional destruction adds ten unlit pickups,
with bounded deferred spawning when space or capacity is unavailable.

Ground stock survives room changes, thrown bombs pause in inactive rooms, and
carried bombs retain their fuse across room and floor transitions. Ownership,
timings, physics and these persistence choices are explicitly local adaptations
in the [source review](reports/isaac-enemy-port/supply/source-review.json).
At that checkpoint Bomb Grimace remained outside gameplay pools, pending Tuff Twins,
The Shell or the escape sequence. Tuff now supplies its dedicated route. See the
[next dependency review](reports/isaac-enemy-port/supply/next-dependency-review.json)
for chain topology, armor, child actors and arena requirements.

The supplied-bomb [checkpoint](reports/isaac-enemy-port/supply/checkpoint.json)
uses fingerprint `46f7e5d8f901a81e`: **151 NPC definitions and 12 items**.
All **49 native suites passed in one full run**; after reference regeneration,
the coverage check also passed separately. Actual raylib input checks passed for
mouse pickup/throw, arrows over the HUD, B placement and zero-inventory HUD use.
The final **99-case browser run passed** with no JavaScript/WebGL errors: four
new supply cases plus the 95 earlier regressions. The unchanged generation check
covers 170 actual floors, 29 ordinary/conditional identities and 14 optional hazards.
This does not establish natural reachability for Bomb Grimace.

The first visual showed a carried bomb overlapping the hat; a display-only offset
fixed it. The [native capture](reports/isaac-enemy-port/supply/linux-carried.png)
and [browser probes](reports/isaac-enemy-port/supply/full/wasm-probes.json) retain
Original style. Initial timing/contact test assumptions and an incorrect browser
execution parameter are documented under `supply/first-run`; none is silently
counted as a pass. All-camera readability, dedicated boss completion, named-item
exceptions, human balance and controlled performance still require work.
That checkpoint's checklist: **115 reviewed, 62 in progress, 89 existing-unverified,
490 missing, 12 excluded; zero fully accepted ports**.

The preceding Quake validation is recorded in the
[checkpoint](reports/isaac-enemy-port/quake/checkpoint.json),
[source/adaptation review](reports/isaac-enemy-port/quake/source-review.json) and
[native results](reports/isaac-enemy-port/quake/native-results.json).
**48 native suites passed across the documented full run and coverage rerun**:
47 passed in the 48-suite run; reference regeneration changed the audit hash
while that run was active. The identity audit was refreshed without changing
review decisions, and the sole coverage check then passed separately. A later
render-only warning correction was rebuilt and checked in native/browser captures.
The final **95-case browser run passed**, with no reported JavaScript or WebGL
errors. Its [probes and captures](reports/isaac-enemy-port/quake/full/wasm-probes.json)
include four isolated directional Quakes and four actual generated Quake rooms,
plus all 87 preceding cases. Focused/repeated cases are not added to that total.

That checkpoint's fingerprint `ae56eab67c0e5584` contains **150 NPC definitions and 12 items**.
The 170-floor regression reaches **14 optional hazard identities** alongside
29 ordinary/conditional identities, preserving budgets and mandatory routes.
All Quakes occur in source-backed band 1: left at seed 9/floor index 2/room 2;
up at 31/2/3; right at 10/2/7; down at 23/2/6. Their fixed subtype directions,
terrain lanes and reachable optional plates are checked in generated layouts.
Opening, tutorial and Mine rosters remain unchanged.

Behavior checks cover actual landing cadence, swept player hits and cover,
height/corridor bounds, first-surface destruction, reward-once persistence,
inventory/provenance, inactive-room phases, ordinary clear, plate/re-entry policy,
capacity suppression and file-only speed edits with immutable snapshots.
The cache wall is only the documented secret-entrance analogue. Source-exact
wave properties, full secret-room routing and named item exceptions remain open.
The initial damage assertion omitted the unchanged hostile impact multiplier;
the corrected assertion uses it. The initial lane assertion included the
statue's own movement collider; the final check uses the actual wave's terrain
collision. Neither correction changes the player's defaults.

The first visual capture exposed a generic warning aimed at an unset target.
The final [hop](reports/isaac-enemy-port/quake/linux-hop.png) uses short arrows
along the fixed axis. [Wave](reports/isaac-enemy-port/quake/linux-wave.png) and
[generated-room](reports/isaac-enemy-port/quake/linux-resident.png) captures retain
Original style, with a broad stone brow and travelling low-poly crest.
Low contrast on sand and mixed-room overlaps still need all-camera review.
Screenshot FPS is not a controlled benchmark. Human/mixed-build balance and
controlled native/WASM performance remained unfinished. That checkpoint's checklist:
**115 reviewed, 61 in progress, 89 existing-unverified, 491 missing, 12 excluded;
zero fully accepted ports**.

The preceding Maw validation is recorded in the
[checkpoint](reports/isaac-enemy-port/maws/checkpoint.json),
[source/adaptation review](reports/isaac-enemy-port/maws/source-review.json) and
[native results](reports/isaac-enemy-port/maws/native-results.json).
All **47 native suites passed together**. The final **87-case browser run passed**
with no reported JavaScript or WebGL errors; its
[probes and captures](reports/isaac-enemy-port/maws/full/wasm-probes.json) include
four isolated Maw cases, two actual generated Maw rooms and 81 prior regressions.
The eight-case focused run repeats cases and does not increase the total.

That checkpoint used fingerprint `af388d4fc406063b`: **146 NPC definitions and 12 items**.
The 170-floor regression still reaches all 29 ordinary/conditional identities
and now **ten separate optional hazard identities**. Normal Maw occurs at seed 0,
floor index 5, room 5; Broken Maw at seed 1, index 2, room 5. Both use reviewed
bands 1–3 and actual reachable plates, without new opening/tutorial/Mine entries.
Adding their pool weights changes optional-hazard selections; the resident
capture fixtures were updated from actual generated results, without injecting
substitute actors. Ordinary threat choices and budgets remain unchanged.

Native checks exercise meaningful counter-movement, both projectile factions,
vertical bounds, real gravity, collision, inactive-room/corridor behavior,
cancellation/stacking limits, four-second boundaries, re-entry, ordinary-clear
persistence and exceptional destruction. A file-only force edit changes real
movement in a new snapshot while an existing snapshot retains its configuration.
Browser probes show the Broken Maw inactive at frames 245/400 and active again
at 490; after a plate press, player position remains unchanged from 120 to 300.
The initial browser fixture assumed a seven-unit starting separation; the actual
capture starts at eight. Its retained failure showed real inward movement, and
the corrected assertion now uses that verified starting state.

Inspected [native resident](reports/isaac-enemy-port/maws/linux-resident-broken.png)
and browser captures show wide dark mouths, Broken cracks, sparse inward dust
and a closed inactive face in Original style. Attraction crowds a stationary
spectator against the body and nearby enemies; some plates/threats overlap HUD
or scenery from particular views. These are partial visual checks, and screenshot
FPS is not a controlled performance measurement. The source's exact forces,
stacking and phase conventions remain unknown; local values are explicit.
D10 and other named item effects, dedicated trap contexts, mixed-build/human
balance and controlled performance remain unfinished. That checkpoint recorded
**115 reviewed, 57 in-progress, 89 existing-unverified, 495 missing and 12 excluded
records; zero fully accepted ports**.

The preceding stationary-hazard validation is recorded in the
[checkpoint](reports/isaac-enemy-port/hazards/checkpoint.json),
[implementation review](reports/isaac-enemy-port/hazards/implementation-review.json)
and [native results](reports/isaac-enemy-port/hazards/native-results.json).
All **46 native suites passed together**. A later capture-only correction lets
resident inspection find optional hazards after ordinary encounter slots; its
native rebuild and real seeded capture passed without changing combat code.
The final **81-case browser run passed**: ten isolated hazard cases, two actual
seeded hazard rooms, and 69 earlier regressions. Its
[probes and captures](reports/isaac-enemy-port/hazards/full/wasm-probes.json)
report no JavaScript or WebGL errors. A preceding browser run terminated when
Chromium closed unexpectedly; the failure log is retained and its cause is not
established. Historical/targeted runs do not increase the distinct-case count.

That checkpoint used fingerprint `f9b924cea5165609`, with **144 NPC definitions and
12 item definitions**. The 170-floor regression reaches all 29 ordinary/conditional
identities plus **eight separate stationary-hazard identities**. Hazards never
replace an ordinary kill-required actor, and their body/plate placement must
preserve entry, objective and door routes. One optional hazard is permitted per
combat room. The source-backed local band rules are:

| Hazard | Approved DeathWard bands |
| --- | --- |
| Stone, Vomit and Triple Grimace | Broken Quarry, Abandoned Works, Storm Cut |
| Stone Eye | Storm Cut |
| Fixed Stone Shooter | Broken Quarry, Abandoned Works, Storm Cut |
| Cross Stone Shooter, both variant-10 subtypes | Broken Quarry, Abandoned Works, Storm Cut |
| Brimstone Head | Abandoned Works, Storm Cut |
| Always-on Cross variant 11, both subtypes | Debug controller only; dedicated trap routing unfinished |

All timings, attack dimensions, damage, room chances and the alternate Cross
startup phase are declared local adaptations. Ordinary invulnerability, retained
inactive solids, pressure-plate shutdown, persistent turret fire and cleared
Stone Eye re-entry removal have concrete native/browser checks. A generic
execution flag does **not** implement Chaos Card or the other named item exceptions.
At that checkpoint, the remaining seven reviewed Maw/Quake/Bomb support tuples were source-only.

Inspected [native seeded turret](reports/isaac-enemy-port/hazards/linux-resident-turret.png)
and browser views retain Original rendering, actual companions and a floor plate.
Foreground cliffs still obscure some isolated views; procedural faces depend on
the camera, and the seeded turret visually overlaps a decorative floor grate.
These are partial visuals, not full camera/readability acceptance. Screenshot
FPS is not a controlled performance measurement. Human/mixed-build balance,
controlled Linux/WASM performance, named item dependencies and dedicated traps
remained open. That checkpoint contained **115 reviewed records, 55 in-progress,
89 existing-unverified, 497 missing and 12 excluded records**, with **zero fully
accepted ports**.

The preceding My Shadow validation is recorded in the
[checkpoint](reports/isaac-enemy-port/shadow/checkpoint.json),
[source review](reports/isaac-enemy-port/shadow/source-review.json) and
[native results](reports/isaac-enemy-port/shadow/native-results.json).
All **45 native suites passed together**. A later focused fixture also verifies
item carry to the next floor, expiry of old allies, a fresh familiar at the new
entrance, and the real item key/content fingerprint in the existing campaign
summary journal. The final **69-case browser regression passed** without reported
JavaScript or WebGL errors; its four added companion cases exercise actual item
ownership, delayed following, duplicate-copy handling, hostile attacks and
repeated fire damage. The full [probes and captures](reports/isaac-enemy-port/shadow/full/wasm-probes.json)
are archived separately from earlier batches.

That checkpoint used fingerprint `c52e6c762c1f93d7`, with **137 NPC definitions
and 12 item definitions**. An actual Smuggler offer at seed 3, floor 0, room 6,
slot 1 supplies My Shadow for the existing 20-max-HP trade. It remains outside
ordinary enemy pools. Native/browser views show dark allied bodies, teal rings
and health bars, plus the delayed ground familiar. Close swarms still crowd the
protagonist; these views do not establish all-camera readability or performance.
That checkpoint contained **115 reviewed records, 45 in-progress,
92 existing-unverified, 504 missing and 12 excluded records**, with **zero fully
accepted ports**. At that point the 17 hazard reviews were source-only. Named
item/status/faction exceptions, source-exact timings, varied-build balance and
controlled Linux/WASM performance remain open.

The preceding Charger-family validation is recorded in the
[checkpoint](reports/isaac-enemy-port/chargers/checkpoint.json),
[source review](reports/isaac-enemy-port/chargers/source-review.json) and
[native results](reports/isaac-enemy-port/chargers/native-results.json).
All **44 native suites passed together** after fixing a shared charge-controller
bug that prevented further flame damage after the first contact tick. The
fixtures now test repeated tail exposure and protected-front exposure, actual
projectiles and explosions, swept wall reflection, stationary recovery, curved
pursuit and Drowned death shots surviving room completion.
All **65 browser cases passed in one final run**, with no reported JavaScript or
WebGL errors. The preserved [browser probes](reports/isaac-enemy-port/chargers/full/wasm-probes.json)
include both repeated-fire checks, the later Princess view and actual flooded
replacement/Level 2 residents. Earlier 63-case and targeted runs are historical
and do not increase the distinct-case count. That native/browser content
fingerprint is `131ed398f76a5e9b`, with 137 registered definitions.

The 170-floor regression reaches **29 ordinary/conditional identities**, with
Drowned in bands 1/2, Dank in 2, Princess in 1 and Level 2 in 3. A 10,000-selection
replacement check produces 5,002 Drowned Chargers under the configured 50% rule.
Of 600 floor-context seeds, 192 select Flooded Quarry under the local 2:1
Standard/Flooded weights. These checks preserve geometry and ordinary route
clearance; the context is represented by damp sediment, not full water-floor art.

A simple starting-kit movement/fire/dodge bot defeats the four variants in
approximately 2.17/3.15/6.02/3.27 seconds, respectively, retaining 100 HP and
surviving 1.5 seconds after each kill. It uses no items, bombs or invulnerability.
This is a synthetic-room feasibility check, not acceptance of mixed-floor or
human difficulty. Native captures show distinct bodies and Princess's vulnerable
pink tail; foreground scenery can still obstruct threats. Exact native timers,
champion/item exceptions, all-camera readability and controlled performance
remain open. That checkpoint's checklist contained **44 in-progress, 93 existing-unverified,
504 missing and 12 excluded records**, with **zero fully accepted ports**.

The preceding Bloat/owned-eye/normal-Charger validation is preserved in the
[checkpoint](reports/isaac-enemy-port/bloat/checkpoint.json),
[source review](reports/isaac-enemy-port/bloat/source-review.json),
[native results](reports/isaac-enemy-port/bloat/native-results.json) and
[browser probes](reports/isaac-enemy-port/bloat/full/wasm-probes.json).
All **43 native suites passed in one complete run**; the Bloat fixture also
passed after adding explicit ordinary-Charger stage assertions. All **57 browser
cases passed**, with no reported browser/WebGL errors. Six targeted cases and a
supplemental green-creep capture repeat existing cases; they are not additional
distinct coverage. The native/browser mechanics fingerprint is
`d5c12bd7ccf59093`, with 136 definitions.

Native fixtures exercise immediate paired lasers, no upward laser, clipping and
damage, fixed rings, both hop types, actual explosive trajectories, green creep,
owned-eye isolation, Charger movement, cleanup, re-entry and one-time rewards.
Real generated Bloat encounters cover both forms in bands 2 and 3: seed/floor
index pairs 1/4 (green), 1/6 (normal), 2/3 (normal), and 5/4 (green).
The separate 170-floor regression still reaches all 25 ordinary/conditional IDs.
Normal Chargers now enter ordinary pools only in bands 1 and 3; green Bloat may
summon them in either boss band. A simple movement/fire/dodge bot wins against
normal/green Bloat in approximately 18.9/24.9 seconds, retaining 100/12.5 HP with
the unchanged 100-HP/24-damage starting kit, no items, bombs or invulnerability.
This is a synthetic-room check, not human or mixed-expedition balance acceptance.

Inspected [Linux](reports/isaac-enemy-port/bloat/linux-green-creep.png) and
[WASM](reports/isaac-enemy-port/bloat/creep/wasm-bloat-green-creep.png) captures
show the green body, damaging patch, owned eyes and summoned Chargers in Original
style. Summons can overlap the boss visually; HUD/foreground occlusion and
all-camera directional readability still need work. Exact native timing and
special-item exceptions remain open, and controlled performance was not measured
for this batch. That checkpoint recorded **40 in-progress, 96 existing-unverified,
505 missing and 12 excluded records**, with **zero fully accepted ports**.
Partial behavior checks and procedural shapes do not satisfy all six gates.

The preceding Peep/owned-eye validation is preserved in the
[checkpoint](reports/isaac-enemy-port/peep/checkpoint.json),
[source review](reports/isaac-enemy-port/peep/source-review.json),
[native results](reports/isaac-enemy-port/peep/native-results.json) and
[browser probes](reports/isaac-enemy-port/peep/full/wasm-probes.json).
All **42 native suites** passed across the complete run plus one targeted rerun:
the initial run passed 41/42, then the coverage check passed after re-auditing
the regenerated reference fingerprint. All **51 browser cases** passed with no
reported browser/WebGL errors. Initial failures and their corrections are retained.

The actual seeded boss fixtures cover cyan at seed 0 / floor index 2, normal at
seed 1 / index 2 and yellow at seed 3 / index 1. The separate floor regression
checks 170 canyon floors and reaches all 25 ordinary/conditional identities.
Native checks exercise exact health thresholds, capacity retry, no orphan eyes,
real projectile blocking and bomb deflection, 8/12-shot patterns, committed jumps,
mid-flight room re-entry and one-time completion. A simple circular movement/
fire/dodge bot defeats each form with the unchanged 100-HP/24-damage starting kit,
no items, no bombs and no invulnerability in roughly 19.5–20.1 seconds, retaining
87.5 HP. This synthetic-room result is not a human or mixed-expedition balance signoff.

Inspected [Linux](reports/isaac-enemy-port/peep/linux-resident-cyan.png) and
[WASM](reports/isaac-enemy-port/peep/full/wasm-resident-peep.png) captures show
the actual cyan encounter in Original style, elevated body and landing warning.
Named item exceptions for eye destruction, double/degraded encounter routes,
full camera/readability acceptance and controlled performance remain unfinished.
That checkpoint had **37 in-progress, 98 existing-unverified, 506 missing and
12 excluded records**. It still certifies zero complete ports; registry entries,
debug execution and sampled screenshots do not substitute for the six acceptance gates.

The preceding replacement/stage validation is preserved in the
[machine-readable results](research/isaac-enemy-port-validation.json),
[native results](reports/isaac-enemy-port/replacements/native-results.json),
[browser probes](reports/isaac-enemy-port/replacements/full/wasm-probes.json) and
[source review](reports/isaac-enemy-port/replacements/source-review.json).
**All 41 native suites passed in one complete run; all 47 browser cases passed
with no recorded JavaScript/WebGL errors.** The final 170-floor regression reaches
all 25 enabled identities, checks exact plan-to-resident identities, valid routes,
entrance clearance, budgets and caps, and retains actual formation/Hopper checks.
A preceding 393-floor discovery run is archived separately; the final test uses
its fixed rare-route seeds instead of repeating hundreds of unrelated floors.
These samples overlap and must not be summed as independent coverage.

The replacement fixture checks 10,000 synthetic selected slots per source:
90 Clotty-to-I.Blob, 90 Clot-to-I.Blob and 5,965 Hopper-to-Flaming outcomes. These
are slot fixtures, not thousands of generated maps. Actual default-rule residents
are verified at Rourke seed 46 / floor 3 (I.Blob), seed 1 / floor 1 (Grilled) and
seed 98 / floor 1 (Hopper substitution). CLI floor indices are zero-based.
Inspected native and browser captures retain Original rendering, live companions,
local ground deposits and active attack/jump probes. Coarse repeated deposit
shapes and similar procedural silhouettes remain visual limitations; no complete
mixed-floor balance, all-angle visual or controlled performance acceptance is
claimed. Immutable snapshots, target HP, safe placement, no recursive replacement,
re-entry and unchanged topology/heightfields under variant changes also pass.

The preceding Hopper checkpoint is preserved in the
[machine-readable results](research/isaac-enemy-port-validation.json),
[native results](reports/isaac-enemy-port/hops/native-results.json),
[browser probes](reports/isaac-enemy-port/hops/full/wasm-probes.json) and
[stage-reachability log](reports/isaac-enemy-port/hops/stage-reachability.txt).
**All 40 native suites have passing evidence across runs.** The initial complete
run passed 39/40; adding Hopper pool entries changed the seeded sample enough to
miss the two-Ring-group quota in one band. The corrected floor test preserves
that quota and the broad 32-seed baseline, then checks extra floors only in bands
missing activation coverage, with a 128-seed cap. Its standalone rerun passed.
The initial failure is retained; this is not claimed as one clean 40-suite run.
**All 44 browser cases passed in one complete run**: the previous 39 plus five
Hopper cases covering wandering, pursuit, normal/flaming cover crossings and an
in-flight transformation. Each new case checks both its arc and grounded landing.
The original 32 cover sixteen first-cycle actors, nine death/regrowth cases,
two longer Rotten brood/orbit checks, three flight checks, a formation check
and two successive Cloggy volleys with opposite curvature. The
168-floor sample reached all **22 enabled identities**, restricted Cloggy to
Broken Quarry crossfire rooms and preserved safe placement. Six Ring Fly groups
activate in actual canyon rooms, two per approved band. Both Hopper forms also
complete jumps in each of their three approved bands.

The [hop fixture](reports/isaac-enemy-port/hops/hop-behavior.txt) checks proximity
and relative movement, committed trajectories, real body/cover clearance, a
controlled river gap with safe banks, closed gates and room bounds. Stun,
transformation and re-entry retain flight; grounded contact and airborne bullet
hits still work. The default kit kills already-airborne normal/flaming actors in
0.77/0.72 seconds with 100 HP remaining in isolated aiming fixtures. This does
not establish mixed-room balance. Inspected
[native Hopper](reports/isaac-enemy-port/hops/linux-hopper-cover.png),
[native Flaming Hopper](reports/isaac-enemy-port/hops/linux-flaming-cover.png),
[WASM Hopper](reports/isaac-enemy-port/hops/targeted/wasm-hopper-cover.png) and
[airborne morph](reports/isaac-enemy-port/hops/targeted/wasm-hopper-cover-morph.png)
retain the Original renderer and show the airborne bodies clearing cover.
See the [hop source review](reports/isaac-enemy-port/hops/source-review.json) for
local dimensions/timing, stage evidence and unresolved replacement/status rules.
Runtime insertion of new solid geometry during a committed jump is not supported;
ordinary expedition demolition removes obstacles. Complete visual, balance and
controlled performance acceptance remains open.

The new [fire fixture](reports/isaac-enemy-port/fire/fire-behavior.txt) checks
identity/owner/team/stun retention, fractional health, actual fire and projectile
contact, flooded vulnerability and room completion, damage-channel differences,
cover/height/lifetime and overlapping-fire bounds. External edits change target,
HP policy and damage scales in new snapshots while existing runs retain their
original rules. Known incompatible bodies, linked forms and cyclic transforms
are rejected. An initial height fixture was corrected to freeze an explicitly
elevated body after spawn; it verifies the vertical contact gate, **not** Hopper's
full airborne collision behavior.

Inspected [native elevated fire](reports/isaac-enemy-port/fire/linux-fire-above-cover.png),
[browser elevated fire](reports/isaac-enemy-port/fire/final/wasm-fire-above-cover.png),
[transformed Clotty](reports/isaac-enemy-port/fire/final/wasm-clotty-live-fire.png)
and [Flaming Hopper](reports/isaac-enemy-port/fire/final/wasm-hopper-fire-burn.png)
retain the Original style. The flooded test uses ordinary terrain with a gameplay
flag; its screenshot does not demonstrate a flooded environment. See the
[fire source review](reports/isaac-enemy-port/fire/source-review.json) for pinned
evidence, explicit adaptations and remaining uncertainties. No new modern pool
route or complete family acceptance is claimed by these isolated fire checks.

The new [pattern fixture](reports/isaac-enemy-port/patterns/pattern-behavior.txt)
checks launch directions across target relocation, motion during windup,
alternating curvature through stun/re-entry, shot survival after shooter death,
cover collision, slowing-only tar and ember shots without ground-fire patches.
External edits reach actual projectile motion and keep existing immutable
expedition snapshots unchanged. Five isolated default-revolver fights clear in
1.33–1.38 seconds with 100 HP remaining; these simple stationary-player cases
do **not** certify mixed-room or complete-floor balance. The research report
passes 166 source-integrity assertions and its offline browser checks.

Inspected [native Cloggy](reports/isaac-enemy-port/patterns/linux-cloggy-curves.png),
[browser Cloggy](reports/isaac-enemy-port/patterns/wasm-cloggy-curves.png) and the
other four family captures show their distinct bodies and volleys in Original
style. Initial brown shots blended into the sand; the retained
[before capture](reports/isaac-enemy-port/patterns/linux-cloggy-low-contrast.png)
and final capture document the contrast correction. The
[source review](reports/isaac-enemy-port/patterns/source-review.json) corrects the
previous unsupported faster-Grilled-cadence assumption and distinguishes
flame-looking shots from ground fire. Complete flooded environments, replacement,
item/status/team rules and HP/stageHP conversion remain open. The five records
are **in progress**, not complete. Controlled performance and all-angle visual
acceptance are also outstanding; capture HUD FPS is not a benchmark.

Earlier formation/flight/brood checkpoints remain in the validation JSON with
their original hashes and limitations. The older formation full run's 16-seed
failure and later successful 32-seed rerun remain preserved as history. The
previous complete 39-suite fire run remains preserved. The current Hopper batch
records its initial full run and successful corrected floor rerun separately.

The [flight fixture](reports/isaac-enemy-port/flight/flight-behavior.txt) checks
160 real interior outcrops, 120 flyable water cells and 2,185 enclosing-cliff
samples across four seeds. It also checks closed/open gates, safe routes,
offspring placement, elevated damage and mouse/arrow targeting. Inspected
[native Pooter](reports/isaac-enemy-port/flight/linux-pooter-cover.png) and
[browser river crossing](reports/isaac-enemy-port/flight/wasm-flight-river.png)
show actual body elevation in the Original style. These are partial visual
checks. The expanded browser probe initially exceeded this Emscripten build's
sixteen-argument limit; splitting the call fixed the smoke-scene error, and the
failed diagnostic is retained alongside the passing results. Controlled
performance comparisons and complete per-family acceptance remain open.

The [earlier brood capture](reports/isaac-enemy-port/rotten/linux-rotten-brood.png)
documents a failed visual check: pursuing bodies occupied the stationary
player's position and hid most maggots. The
[new native capture](reports/isaac-enemy-port/ground-bodies/linux-rotten-brood.png)
shows separate bodies around the player. The 1,200-tick native brood fixture
retains all seven threats with a minimum player-to-body-edge distance of 0.475
and minimum enemy edge gap of approximately 0.0249. Contact still deals damage.
This resolves the reproduced physical pile-up; perspective overlap between
silhouettes remains possible. Full camera/occlusion acceptance is still open,
and the failed baseline is retained rather than overwritten.
Both legacy Gapers and graph-driven Rotten Gapers also pass a five-actor,
two-unit-wide passage check without crossing the walls. See the
[native behavior log](reports/isaac-enemy-port/ground-bodies/behavior-and-balance.txt)
and [browser brood capture](reports/isaac-enemy-port/ground-bodies/wasm-rotten-brood-spaced.png).

Original-style captures include [native Super Pooter](reports/isaac-enemy-port/linux-14.1.0.png)
and [WASM Super Pooter](reports/isaac-enemy-port/wasm-14.1.0.png); the directory also
contains Gusher, Pacer, Horf and Pooter browser captures. These are partial
presentation evidence, not all-phase/occlusion certification.
New captures show [native Cursed goo](reports/isaac-enemy-port/linux-cursed-goo.png),
[browser regrowth](reports/isaac-enemy-port/wasm-cursed-regrown.png) and
[Drowned Hive offspring](reports/isaac-enemy-port/wasm-drowned-hive-split.png).

The stress figures below belong to the **earlier graph/pool checkpoint**. They
were not rerun or accepted as performance evidence for the later death/regrowth or Rotten batches.

| 360-frame saturation stress | Before: mean frame / simulation | After: mean frame / simulation |
| --- | --- | --- |
| Linux/WSLg | 88.87 / 2.10 ms | 123.73 / 1.44 ms |
| WASM/Chromium | 73.43 / 3.55 ms | 105.16 / 2.36 ms |

**Performance acceptance remains open.** Mean frame time increased in these
captures. The stress harness draws from the natural roster, so removing the boss
eyes changed the seeded population and event workload: kills changed from 772
to 707 and suppressed events from 22,909 to 4,420. This is not a controlled
code-regression comparison or normal-play FPS. Both platforms matched these
counters within each checkpoint and respected the 4,096-projectile/depth-16
limits. A fixed-roster comparison is still required before performance signoff.

### What the audit establishes

| Finding | Count / consequence |
| --- | --- |
| Source records tagged enemy | 468; includes hazards, NPC-like entities and dependencies |
| Source records tagged boss | 185; includes body parts, phases and scripted actors |
| Total review population | 653 records across 329 type IDs; neither count is a count of independent encounters |
| Current runtime definitions | 159; registration still does not certify behavior against the selected edition |
| Source tuples absent from runtime | 494; this is an identity difference, not the total remaining work |
| IDs selected by the current normal canyon floor planner | 36 ordinary/conditional identities, fourteen optional hazards, Peep/Bloat/Tuff/Shell/Loki/Lokii/Hornfel dedicated bosses, owned eyes and rail components, Tuff's Ink/Sucker offspring, and both Tuff/Shell bomb suppliers with Shell's Fly Bomb offspring; My Shadow remains item-only |
| Definitions using the new state graph at the initial audit | One: Horf; implementation progress above records later migrations |
| Records without any stored room-template presence | 153; they may be summoned or scripted, not unused |
| Records with nonzero XML `stageHP` | 104; base HP alone is insufficient |
| Records without a collected article | `277.0.0` Black Boney, `963.0.0` Frozen Enemy, `965.0.0` Minecart |
| Cut-content context flags requiring review | 12; flags alone are not proof of exclusion |
| Mechanical parity currently certified by this audit | None; existing smoke/contract tests do not prove source-game parity |

The initial audit found a concrete identity error: the `68.1.0` entry was named **Peep
Eye**, but installed `entities2.xml` assigns `68.1.0` to **The Bloat** and
`68.10.0` to Peep Eye. The wiki's monster index also displays the ambiguous
`68.1`, whereas the [Bloat article](https://bindingofisaacrebirth.wiki.gg/wiki/The_Bloat)
identifies the boss with that ID. Use the installed XML's integer tuple, not a
decimal number parsed from a display label. The implementation pass corrected
the eye identity before adding The Bloat. The save journal does not serialize
live monster identities, so there is no live-enemy save migration for this fix.
`25.3.1` also had a naming alias (Dragon Fly X versus
Dragon Fly/dragonfly2). The reviewed XML/article join now resolves it as the
diagonal-fire variant; it was not a missing creature.

The older report's `deathward` match for The Bloat was therefore only a tuple
match to the mistaken eye definition. The separate Bloat controller described
above was added later. Neither the old match nor current procedural silhouettes
establish complete source behavior.

### Scope and evidence policy

“All enemies” means every shipped, applicable combat creature and variant in
this reference, including bosses, minibosses and the components they require.
Every one of the 653 records must receive a reviewed disposition:

- Standalone room enemy, including a specified floor/encounter policy.
- Boss or miniboss encounter root with its components and arena policy.
- Child, phase, body part, hazard, environmental actor or resource dependency,
  created through the appropriate encounter instead of a normal enemy pool.
- Confirmed unused/non-applicable content, with cited evidence and a reason.

Unknown or difficult content cannot silently become an exclusion. The three
missing-article entries need local-data, parent-encounter and source-version
investigation. Review helpers outside these 653 records when a required combat
behavior depends on them. Generic champion overlays and unique boss champion
behaviors are additional work; XML rows alone do not enumerate all champion
behavior. Do not expand this goal into porting every player item, but implement
the resource/status interfaces necessary for enemy mechanics and test them.

For each eligible actor, write a contract for activation, acquisition, movement,
attack selection, warning, emission, recovery, vulnerabilities, status responses,
phase changes, death/offspring and room-clear participation. Store source values
and citations separately from DeathWard values. Native timers/speeds and random
weights are not uniformly recovered: measure them when practical, otherwise
label tuned values and their rationale. A generic shooter with the correct name
does not satisfy a behavior contract.

### Proposed stage placement

Keep the existing **4–8 floors**, current **9–15 rooms per floor**, five-room
tutorial and story-site schedule. Use the four existing environment/difficulty
bands. These mappings are a DeathWard design proposal informed by source stage
membership, not a reproduction of Isaac's entire chapter graph.

| DeathWard band | Primary source families | Placement policy |
| --- | --- | --- |
| 0 — Outer Washes | Basement, Cellar, Burning Basement | Introduce readable pursuit, simple volleys and small groups; reviewed early bosses in suitable arenas. No automatic placement of every early-chapter variant. |
| 1 — Broken Quarry | Caves, Catacombs, Flooded Caves; reviewed Downpour/Dross and Mines/Ashpit groups | Add chargers, jumpers, controlled crossfire, first support combinations and terrain specialists. Alternate-path families require their mechanics and terrain support. |
| 2 — Abandoned Works | Depths, Necropolis, Dank Depths; Mausoleum/Gehenna | Introduce beams, armor, revival, teleportation and linked enemies in authored combinations with safe approaches. |
| 3 — Storm Cut | Womb, Utero, Scarred Womb, Corpse; reviewed late-route families | Advanced combinations and late bosses. Sheol/Cathedral/Chest/Dark Room actors require individual difficulty/arena review. Endgame and mode-specific encounters use dedicated policies. |

The proposed promotion of Downpour/Dross to band 1 avoids putting their extra
mechanical demands into the first floor by default. This is an adaptation choice,
not a claim that they occupy that position in Isaac. The [source chapter list](https://bindingofisaacrebirth.wiki.gg/wiki/Chapters)
and preserved stage files retain the original grouping.

The current normalized progression is `band = min(3, floor_index * 4 / floor_count)`:

| Floors in expedition | Band sequence (shown as names) |
| --- | --- |
| 4 | Washes → Quarry → Works → Storm |
| 5 | Washes → Washes → Quarry → Works → Storm |
| 6 | Washes → Washes → Quarry → Works → Works → Storm |
| 7 | Washes → Washes → Quarry → Quarry → Works → Works → Storm |
| 8 | Washes → Washes → Quarry → Quarry → Works → Works → Storm → Storm |

Source engine stage numbers used for HP, source chapter/theme, DeathWard band,
absolute expedition floor and graph depth within one floor are **different
fields**. Do not use room depth to unlock late-game enemies. The existing XML
stage-HP formula needs an explicit source-stage-to-DeathWard balance mapping;
do not feed a four-band number into it as though it were an Isaac stage number.
The preserved [Stage HP revision](https://bindingofisaacrebirth.wiki.gg/index.php?oldid=269064)
documents the source distinction.

Local positive-weight room templates give candidate habitat evidence. Boss
selection needs the separate `entities2.xml bossID → bosspools.xml id` join;
boss-pool IDs are not entity IDs and can be shared by components. Keep boss
encounter records separate from degraded-boss room appearances. Never infer a
spawn probability from the number of stored templates. Greed, special rooms,
Ascent/Home, Void and the undeclared Mortis library are not normal early-floor
evidence. A missing room entry does not disqualify a summoned actor.

The mechanical proposal currently finds an initial band candidate for 457 rows:
98 Washes, 168 Quarry, 82 Works and 109 Storm. **196 require classification,
parent or special-encounter review before initial placement.** Even the 457
candidates are not approved random spawns: some are components, hazards or boss
variants. All live spawn approvals remain false in the analysis artifacts.

Not every imported creature should appear in a single expedition. Each eligible
root must have a documented reachable route across seeds, stage variants or
optional encounters. Children must be reachable through their parents. A debug
selector is a test aid, not the only way a completed gameplay enemy appears.
Hush, Delirium, Mother, Dogma/Beast and similar cases need dedicated late encounter
controllers/arenas; their full scripts cannot be dropped into an arbitrary
ordinary room. Introduce such encounters through explicit late-floor variants
or optional challenge rooms without silently extending the run beyond 4–8 floors.

### Engine work that is still required

| Area | Current state | Required extension |
| --- | --- | --- |
| Identity and definitions | Tuple IDs, external stats, immutable snapshots, namespaced item keys | Resolve identity mismatches; add source edition, roles, dependency/parent links and reviewed parameters |
| State graphs | Still/chase/flee/wander/orbit, three poses, five guards, six actions including bounded summons, one shared projectile profile | Per-state attack profiles, weighted choices, alignment/LOS guards, timers/counters, steering/charge/hop/burrow/teleport nodes, animation/state events and lifecycle hooks |
| Combat primitives | Many attacks and offspring exist as native ID-specific branches | Reusable beams/rings/lobs/splits/homing, damage flags, per-target intervals, vulnerability rules, statuses, team targeting, reflection and champion policies |
| Navigation | Ground pursuit has body steering, contact separation and narrow-opening yielding; flight crosses interior cover/water with real elevation while respecting room boundaries, cliffs and gates | Complete linked/intangible and family-specific airborne rules; broaden camera, combat and performance acceptance across actual room compositions |
| Parent/child life cycle | Separate summon/part ownership, stable detached slots with capacity retry and owner-death cleanup; death recipes, regrowth and room-persistent ring formations | Required-child spawn reservation, shared HP, additional formation shapes/controllers, merge and broader lifecycle rules |
| Boss selection | Native canyon bosses plus external dedicated boss pools; separate Peep/Bloat controllers/forms, owned eyes, phase thresholds, immediate directional lasers and green ballistic/summon attacks | More reviewed encounter controllers, arena predicates, shared-health/phase trees and repeat rules; retain existing bosses |
| Encounter composition | 36 ordinary/conditional IDs with external band/pattern weights, group costs/counts, caps, floor variants and replacement rules | Reviewed roster expansion, room/terrain predicates, tags, family limits, mutual exclusions, summon-aware budgets and dependency-safe fallback |
| Rendering | Procedural family silhouettes, legacy-ID warnings, occlusion outlines | Distinct silhouettes/state poses and telegraphs driven by actual attacks; readable damage windows and projectiles in the original style |
| Verification | Catalog smoke tests and selected behavior contracts | Per-family/variant behavioral fixtures, reachability/coverage reports, state traces, arena captures and native/browser performance checks |

Keep existing native implementations behind named behavior adapters during
migration. Move families into reusable components when that reduces duplication;
do not erase a working unusual behavior merely because it does not fit the first
graph vocabulary. Some bosses merit dedicated native controllers with external
parameters. Do not grow one giant ID switch to cover the entire roster.

`encounters.mechanics` already provides runtime band/pattern pools and is packaged
for Linux and WASM. Floor profiles and the native boss fallback remain in C++;
dedicated boss weights and forms now load from `bosses.mechanics`.
`stages.mechanics` now maps each band's first/second floor to explicit source HP
stages. The new `stage_health` formula is currently applied to seven Boom Fly
tuples; the other stage-HP records still require migration. Broader stage geometry,
budgets and named environment contexts remain separate work.
Extend the existing definition validation with parent/dependency and required
capability checks. Unknown IDs, invalid graph edges and empty mandatory pools
must continue to fail before starting an expedition.

Keep source HP, stage HP and unit measurements distinct from tuned DeathWard
values. Preserve the player's current defaults and controls while calibrating
enemy time-to-kill, incoming damage and reaction windows as a coherent set.
Record every intentional 3D/balance adaptation. Do not claim frame-identical
Isaac parity from adapted speeds, visual scale or a passing smoke test.

### Implementation milestones

1. **Review and classify the complete population.** Resolve the Peep Eye/Bloat
   mismatch; pin edition/source evidence; review all 653 dispositions, dependencies,
   champion needs, stage/arena requirements and unknowns. Create a maintained
   coverage manifest separate from the generated review queue. Decide special
   encounter routes before treating their creatures as ordinary pool entries.
2. **Deliver one complete vertical slice.** Extend graph/native primitives,
   combat ownership and stage-pool loading; port representative pursuit, aimed
   shooter, charger, invulnerable hazard, summoner and a multipart boss. Verify
   real floor generation, visual tells, child cleanup, rewards and native/WASM
   behavior. Add an isolated test arena with ID selection, reset, state and hitbox
   display, and scripted input; keep test controls unobtrusive in ordinary play.
3. **Complete the opening band.** Implement every reviewed eligible opening
   family/variant and its dependencies and early bosses. Start with simple
   movement/projectile families, then their conditional/death variants. Prove the
   first floor is readable and beatable with the current starting character.
4. **Complete Quarry and Works.** Add every reviewed middle-band family,
   alternate-path specialist, champion policy, status behavior and required
   terrain support. Compose encounters around actual geometry, not just area.
5. **Complete Storm and special encounters.** Finish late families, multipart
   bosses, endgame controllers and relevant mode-specific behavior. Required
   components never enter ordinary room pools. Keep rewards and exit progression
   correct across transformations, simultaneous deaths and capped child spawns.
6. **Audit the complete result.** Every source row has a final reviewed outcome;
   every eligible actor has a contract, implementation, reachable route and test
   evidence. Finish visual readability, source/adaptation notes, performance and
   regression checks. Registry size alone does not complete this milestone.

Within each milestone work by shared behavioral family, not numeric ID order.
Keep functioning intermediate builds and update the coverage manifest as work
lands. A later milestone cannot hide unimplemented earlier variants behind a
generic fallback. Preserve unrelated existing work throughout.

### Acceptance and test strategy

- Contract tests assert targeting, movement/alignment, warning duration, emitted
  pattern, vulnerability, health ownership, statuses, offspring and completion.
  Add distinctions for each variant; one smoke test for a shared family is not
  sufficient. Unknown timings may be documented tuned constants, not claimed
  recovered values.
- Check every eligible pool/encounter is reachable. Sample seeded plans across
  all 4–8-floor lengths and every band; separately force each rare encounter to
  avoid relying on random discovery. Verify repeated seeds/content fingerprints
  reproduce composition and behavior, and invalid mandatory pools fail clearly.
- Spawn groups fit walkable area and entry clearances. Charge lanes, water,
  walls, bridges/fords and boss arenas satisfy their capabilities. Limit concurrent
  threats by their cost and interaction, including summons; reject combinations
  that eliminate all safe responses. Keep invulnerable hazards and harmless
  actors from blocking room completion.
- Preserve populated-but-idle unentered rooms, corridor inactivity, room re-entry,
  floor exits, shops/services, tutorial/story rooms, original Mine enemies and
  all authored hubs. Keep the surgeon excluded from the first three floors and
  one trader per service/shop room. Standard combat rooms retain one initial
  encounter; genuine summons/phases are part of that encounter, not a restored
  generic wave system.
- Test normal death, instant-kill cheats, boss phase interruption, simultaneous
  parent/child death, capacity exhaustion and cleanup. A failed required-child
  spawn cannot leave an immortal boss or permanently sealed room. Do not award
  component kills as repeated boss rewards or allow unlimited summon farming.
- Capture each family/major boss phase in representative canyon scenes using
  the original visual style. Check occlusion outlines, team/projectile colors,
  grounded hitboxes, warning/impact consistency and readable attack patterns.
  Reuse modular procedural visuals where appropriate without reducing every
  creature to an indistinguishable primitive.
- Build Linux and WASM, run behavior/progression/save regression tests and real
  browser scenarios, and compare fixed-seed worst-case frame/step times against a
  recorded pre-port baseline. Keep resource budgets effective. Document save
  compatibility; the current journal is not a full resumable live-enemy snapshot.

Completion requires all reviewed eligible behavior and routing work to be done.
Unresolved plausible combat entries remain open. Confirmed unused/non-applicable
records require evidence-backed exclusion; unique difficult bosses cannot be
excluded merely to make the report green. No exact parity claim without the
corresponding source/measurement evidence.

### Suggested implementation goal

> Implement the full Isaac enemy port in DeathWard following the full enemy port
> plan in `docs/isaac_monsters.md` and the evidence/review queues in
> `docs/research/isaac-enemy-port-plan.json`,
> `docs/research/isaac-enemy-port-review.csv` and
> `docs/research/isaac-mechanics-reference.json`. Use installed Repentance 1.7.9b
> as the source baseline. Review all 653 enemy/boss/component records, resolve
> identity conflicts, and implement every eligible creature, variant, boss and
> required dependency with faithful behavioral contracts and explicitly
> documented DeathWard adaptations. Extend the reusable mechanics system and
> external definitions rather than substituting generic AI. Place each actor in
> appropriate seeded floor pools or dedicated encounters within the existing
> 4–8-floor expedition structure. Preserve the tutorial, story, hubs, Mine roster,
> current player defaults/controls and original visual style. Work through the
> plan's six milestones, maintain a per-record coverage manifest, and verify
> behavior, routing, visuals, balance and resource limits in Linux and WASM.
> Complete only when every eligible record is implemented, reachable and tested,
> and every exclusion has source-backed justification. Do not count registrations,
> aliases, placeholders, unreviewed generic behavior or missing evidence as
> completed ports. Preserve unrelated existing changes.

This goal covers the whole roster in reviewable stages. No token/time estimate is
asserted by this analysis; the dependency review determines the actual scope.

## Existing roster: IDs 10–89

This section describes the earlier adaptation roster. The catalog implements the enemy entries in the requested type range from the [Monsters reference](https://bindingofisaacrebirth.fandom.com/wiki/Monsters), including DLC variants and subtypes. The [current wiki index](https://bindingofisaacrebirth.wiki.gg/wiki/Monster) supplies additional readable references. IDs are stored as separate integer components: `25.3.1` and `68.11` stay distinct. There are 120 entries within the requested range (including detachable Maw heads), plus eight supporting creatures outside it needed by spawners and paired enemies. Numeric gaps are not invented enemies; bosses on the separate boss list are outside this roster.

### Play and test

The earlier canyon roster uses Isaac catalog adaptations. Current non-Classic progression reaches 36 ordinary/conditional IDs through external floor encounter roles, plus Peep/Bloat/Tuff/Shell/Loki/Lokii encounters alongside the three native canyon bosses; the full port plan above extends this. Mine missions use only the original Western roster and the Hollow Sheriff. New sessions offer Canyon by default. Completing the canyon does not mark the Sheriff dead in the mine. Composition and placement use independent room seeds. Current floor pools select basic and specialist roles using band-specific threat budgets, specialist limits and per-ID caps. Legacy/Classic selection gates variants by room depth; current normal progression uses the floor difficulty band. Current floor plans cap initial ordinary combat populations at 4–14 slots according to usable area, with at most one separate optional statue hazard, while legacy/Classic initial counts use 4–24. Initial placement reserves six units of arrival clearance and separates bodies. Subsequent summons are additional bodies, bounded by the shared 256-enemy cap and configured owner limits; offspring generations are bounded. Ground pursuit now also resolves body contact during combat; linked, airborne and hazard policies remain separate work.

With cheats enabled, **comma / period** selects the previous / next catalog entry; the announcement shows its ID and name. **Shift+F4** places that selection on safe floor and keeps the encounter in test mode. **F4 / F5** spawn 20 / 100 random roots from the current mission's roster, with attached companions where required. **F3** kills existing enemies without creating replacement offspring; **Shift+F3** ends the test and clears the room, pending offspring, projectiles, hazards and event chains. The shortcut panel stays hidden until backtick is pressed. Hovering a monster displays its ID and name.

### Combat systems

The implementation includes committed attack warnings, radial and spread patterns, homing and splitting projectiles, returning head attacks, directional armor and reflected shots, opening Host shells, regenerating Globin piles, aimed beams clipped by cover, timed explosive landings, persistent damaging and slowing pools, burrowing and teleport arrival warnings, leaps, wall followers, linked chains, mirrored movement/shooting, on-death transformations and bounded summoning. Pons control their paired Knights; protected orbiting flies change state when their host dies. Permanent room hazards are excluded from completion objectives and deactivate on clear.

Names and IDs identify the references; meshes are new procedural 3D silhouettes built for this game. Walkers, headless bodies, insects, segmented crawlers, skulls, blobs, eyes and stone hazards have different geometry, with variant colors, wings, armor, flame details and state poses. HP, speed, range, damage and warning times are tuned for DeathWard's revolver and dodge.

### Adaptation boundaries

This is a DeathWard implementation of the roster and its combat roles, rather than a byte-for-byte simulation of Isaac. Flying creatures use separate navigation over interior cover and water, with actual elevated positions and hit volumes while respecting enclosing cliffs and gates. Hops are shown as an animation above that collision surface. The earlier port omitted the source coin-theft and charge-stealing behaviors. DeathWard now has coins and player dynamite, but Keeper still lacks coin theft, Bulb lacks an active-charge resource to steal, and Fly stays harmless. A general champion system and Isaac floor replacement rules are still missing. Timing, spawn probabilities and a few projectile formations are simplified. Eggy now produces the distinct Swarm Spider support entry; its lingering death animation remains unimplemented. Tainted Sucker has no contact damage and its death projectiles can bounce. See [the review and character reference](isaac_review.md) for verified corrections and remaining differences. No original Isaac sprites, sounds or models are bundled.

### Catalog

The table below preserves the earlier adaptation catalog; it is not a current
behavior or completion checklist. Later changes, including Rotten Gaper subtypes
and graph-based Pooters, are recorded above and in the maintained per-record
manifest. Consult `assets/mechanics/monsters.mechanics` for current definitions.
“Support” entries outside 10–89 were used only as offspring or attached companions;
the test selector also exposes them.

| ID | Name | Movement | Attack role |
| --- | --- | --- | --- |
| 10.0 | Frowning Gaper | Chase | None |
| 10.1 | Gaper | Chase | None |
| 10.2 | Flaming Gaper | Chase | None |
| 10.3 | Rotten Gaper | Chase | Shot |
| 11.0 | Gusher | Wander | Shot |
| 11.1 | Pacer | Wander | None |
| 12.0 | Horf | Still | Shot |
| 13.0 | Fly | Still | None |
| 14.0 | Pooter | Chase | Shot |
| 14.1 | Super Pooter | Chase | Spread |
| 14.2 | Tainted Pooter | Chase | Spread |
| 15.0 | Clotty | Wander | Cross |
| 15.1 | Clot | Wander | Diagonal |
| 15.2 | I.Blob | Wander | Ring |
| 15.3 | Grilled Clotty | Wander | Cross |
| 16.0 | Mulligan | Flee | None |
| 16.1 | Mulligoon | Flee | None |
| 16.2 | Mulliboom | Chase | None |
| 18.0 | Attack Fly | Chase | None |
| 21.0 | Maggot | Wander | None |
| 22.0 | Hive | Flee | Spawn |
| 22.1 | Drowned Hive | Flee | Spawn |
| 22.2 | Holy Mulligan | Flee | Spawn |
| 22.3 | Tainted Mulligan | Flee | Spawn |
| 23.0 | Charger | Charge | None |
| 23.0.1 | My Shadow | Charge | None |
| 23.1 | Drowned Charger | Charge | None |
| 23.2 | Dank Charger | Charge | None |
| 23.3 | Carrion Princess | Charge | None |
| 24.0 | Globin | Chase | None |
| 24.1 | Gazing Globin | Chase | None |
| 24.2 | Dank Globin | Chase | None |
| 24.3 | Cursed Globin | Chase | None |
| 25.0 | Boom Fly | Bounce | None |
| 25.1 | Red Boom Fly | Bounce | None |
| 25.2 | Drowned Boom Fly | Bounce | None |
| 25.3 | Dragon Fly | Bounce | None |
| 25.3.1 | Dragon Fly X | Bounce | None |
| 25.4 | Bone Fly | Bounce | Shot |
| 25.5 | Sick Boom Fly | Bounce | None |
| 25.6 | Tainted Boom Fly | Bounce | None |
| 26.0 | Maw | Chase | Shot |
| 26.1 | Red Maw | Chase | None |
| 26.2 | Psychic Maw | Chase | Shot |
| 27.0 | Host | Still | Spread |
| 27.1 | Red Host | Still | Spread |
| 27.3 | Hard Host | Still | Shot |
| 29.0 | Hopper | Hop | None |
| 29.1 | Trite | Hop | None |
| 29.2 | Eggy | Hop | None |
| 29.3 | Tainted Hopper | Hop | Ring |
| 30.0 | Boil | Still | Burst |
| 30.1 | Gut | Still | Lob |
| 30.2 | Sack | Still | Spawn |
| 31.0 | Spitty | Wander | Spitty |
| 31.1 | Tainted Spitty | Wander | Spitty |
| 32.0 | Brain | Wander | None |
| 34.0 | Leaper | Hop | Cross |
| 34.1 | Sticky Leaper | Hop | Burst |
| 35.0 | Mr. Maw | Chase | Head |
| 35.1 | Mr. Maw Head | Orbit | None |
| 35.2 | Mr. Red Maw | Chase | Head |
| 35.3 | Mr. Red Maw Head | Orbit | None |
| 38.0 | Baby | Teleport | Shot |
| 38.1 | Angelic Baby | Teleport | Spread |
| 38.1.1 | Angelic Baby (small) | Teleport | Shot |
| 38.3 | Wrinkly Baby | Charge | Spread |
| 39.0 | Vis | Wander | Beam |
| 39.1 | Double Vis | Wander | DoubleBeam |
| 39.2 | Chubber | Wander | Head |
| 39.3 | Scarred Double Vis | Wander | QuadBeam |
| 40.0 | Guts | Wall | None |
| 40.1 | Scarred Guts | Wall | None |
| 40.2 | Slog | Wall | None |
| 41.0 | Knight | Charge | None |
| 41.1 | Selfless Knight | Charge | None |
| 41.2 | Loose Knight | Charge | None |
| 41.3 | Brainless Knight | Charge | None |
| 41.4 | Black Knight | Charge | None |
| 42.0 | Stone Grimace | Still | Shot |
| 42.1 | Vomit Grimace | Still | Lob |
| 42.2 | Triple Grimace | Still | Spread |
| 44.0 | Poky | Bounce | None |
| 44.1 | Slide | Charge | None |
| 53.0 | Dople | Mirror | Shot |
| 53.1 | Evil Twin | Mirror | Spread |
| 54.0 | Flaming Hopper | Hop | None |
| 55.0 | Leech | Charge | None |
| 55.1 | Kamikaze Leech | Charge | None |
| 55.2 | Holy Leech | Charge | None |
| 56.0 | Lump | Burrow | Spread |
| 57.0 | MemBrain | Hop | Ring |
| 57.1 | Mama Guts | Hop | Ring |
| 57.2 | Dead Meat | Hop | Ring |
| 58.0 | Para-Bite | Burrow | None |
| 58.1 | Scarred Para-Bite | Burrow | Shot |
| 59.0 | Fred | Burrow | Cross |
| 60.0 | Eye | Still | Beam |
| 60.1 | Bloodshot Eye | Still | Beam |
| 60.2 | Holy Eye | Still | Light |
| 61.0 | Sucker | Chase | None |
| 61.1 | Spit | Chase | None |
| 61.2 | Soul Sucker | Chase | None |
| 61.3 | Ink | Chase | None |
| 61.4 | Mama Fly | Flee | Spawn |
| 61.5 | Bulb | Wander | None |
| 61.6 | Bloodfly | Chase | None |
| 61.7 | Tainted Sucker | Chase | None |
| 68.10 | Peep Eye (corrected installed tuple; boss-owned component) | Bounce | None |
| 68.11 | Bloat Eye | Bounce | None |
| 77.0 | Embryo | Hop | None |
| 80.0 | Moter | Chase | None |
| 85.0 | Spider | Wander | None |
| 86.0 | Keeper | Hop | Spread |
| 87.0 | Gurgle | Chase | Lob |
| 87.1 | Crackle | Chase | Lob |
| 88.0 | Walking Boil | Wander | Burst |
| 88.1 | Walking Gut | Wander | Lob |
| 88.2 | Walking Sack | Wander | Spawn |
| 89.0 | Buttlicker | Chain | None |
| 96.0 | Eternal Fly (support) | Orbit | None |
| 222.0 | Ring Fly | Shared moving ring | None |
| 238.0 | Splasher (support) | Wander | Lob |
| 840.0 | Pon (support) | Hop | None |
| 853.0 | Small Maggot (support) | Wander | None |
| 861.0 | Pustule (support) | Still | None |
| 862.0 | Cyst (support) | Wall | Shot |
| 884.0 | Swarm Spider (support) | Hop | None |
