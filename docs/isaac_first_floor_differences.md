# First-floor gameplay differences: DeathWard vs Isaac

Date: 2026-11-07. DeathWard snapshot: `28023a49dbd8712820ba6953219cfdb7866bdcb6`. Reference: installed **The Binding of Isaac: Repentance 1.7.9b**, not Repentance+.

**DeathWard is not currently a graphics-only adaptation of Isaac's first stage.** Health representation, weapon effectiveness, movement/evasion, encounter composition, bosses, rewards, economy and room rules differ. Some source-based enemy controllers exist, but their presence is not full gameplay acceptance.

This is an initial evidence-backed differences report, not an implementation or certification of 1:1 parity. No gameplay values were changed. The prior canyon graphics work remains paused.

## Implementation follow-up

**2026-11-08: the subsequent bulk parity implementation was reverted. The automatic goal is paused; future work requires explicitly selected IDs or ranges in the [current comparison report](isaac_first_floor_implementation.md). H01 was selected first; H02–H18 were then explicitly selected and now have scoped gameplay implementations with verification and remaining gaps recorded there.** The original audit below remains a pre-change snapshot.

This report preserves the **pre-change** audit and its captured numbers. Track subsequent enabled changes and remaining gaps in [the implementation progress report](isaac_first_floor_implementation.md). The user explicitly requested retaining **universal dodge**, including its movement and immunity, as an exception to the nonvisual 1:1 target. Its audit row records the original difference; it is no longer a removal requirement.

**Later control decision:** S06 is a retained exception. Keep the current eight-direction firing mechanism and existing mouse/keyboard controls for isometric gameplay. The original firing-direction audit below is historical and is not a requirement to replace these controls.

## Comparison contract

The baseline is regular **Isaac, Normal difficulty, Basement I**, before collecting items. DeathWard means a fresh, non-tutorial **Canyon expedition, floor index 0, Compact pacing**, default player settings, no god mode, no starting powers. A floor is part of an expedition; it is not the entire expedition.

The comparison permits different art, models and rendering. Changing movement, hit detection, aiming options, health rules, item effects or enemy behavior is a mechanical difference even when motivated by 3D presentation.

Important unresolved baseline choices:

- Isaac's starting D6 depends on unlock state. Audit basic stats without it, then test the unlocked-D6 variant separately. Missing `items` in `players.xml` does not prove unlock-dependent starting behavior is absent.
- Cellar I and Burning Basement I are separate first-stage contexts. They are inventoried here, not silently treated as Basement I.
- Native unlock profile, seeded/daily/challenge exclusions and special-room eligibility must be fixed before claiming complete floor-I coverage. This report does not assume every room in a chapter library can occur on the first floor.
- Hard mode, other characters, co-op, Repentance+ and later stages are outside this baseline. Mechanics reachable through legitimate first-stage pickups still belong in the eventual 1:1 target.
- The authored `profile-works` graphics demo uses inspection setup/god mode and is **not** the gameplay comparison fixture.

## Evidence and confidence

| Label | Meaning |
| --- | --- |
| XML/STB | Read from the preserved selected-version game resources. Definitions and library membership do not prove runtime probabilities or AI. |
| DW runtime | Observed from the active DeathWard content library or a narrow simulation fixture. The exact observation scope is recorded. |
| DW source | Current code/configuration inspection, not a full gameplay measurement. |
| Documented | Character/API documentation; a pinned native observation is still required where it affects acceptance. |
| Partial / unknown | Existing implementation or evidence does not establish the requested behavior. |

The small [runtime snapshot](reports/isaac-first-floor-parity/snapshot.json), [runtime TSV](reports/isaac-first-floor-parity/deathward-runtime.tsv), [input hashes](reports/isaac-first-floor-parity/input-hashes.json) and [enemy CSV](reports/isaac-first-floor-parity/enemy-comparison.csv) retain the data behind this report. Current documented Isaac base stats are 3.5 damage, approximately 2.73 tears/second, 1.0 Speed, 1.0 Shot Speed, 6.5 Range and 0 Luck. These are documented values, **not a fresh native-player trace**. [Character reference](https://bindingofisaacrebirth.wiki.gg/wiki/Isaac), [Repentance character table](https://strategywiki.org/wiki/The_Binding_of_Isaac%3A_Repentance/Regular_characters).

The preserved `players.xml` directly establishes Isaac's six red half-heart units and one starting bomb. It does not supply every base stat or conditional starting-item rule. The [player API](https://wofsauge.github.io/IsaacDocs/rep/EntityPlayer.html) distinguishes health types, damage cooldown, movement and projectile statistics; API availability alone is not measured behavior.

## Player health, hearts and survivability — blocking differences

| Mechanic | Isaac baseline / requirement | DeathWard now | Assessment / evidence |
| --- | --- | --- | --- |
| Starting health | Six red half-heart units: three full red hearts | 100/100 HP | Confirmed different representation; XML + DW runtime. |
| Health model | Typed health and containers, not one interchangeable bar | `hp`, `maxHp`, `baseHealth` floats | Missing typed-heart state in `Player`. |
| Red hearts | Filled red health is distinct from maximum red capacity | Current/max HP only; medicine heals a number | Not the same pickup/container contract. |
| Soul hearts | Separate non-refillable protective health | No dedicated player state | Missing. |
| Black hearts | Protective health with a depletion-triggered effect | No dedicated player state/depletion event | Missing. |
| Eternal hearts | Partial persistent-heart state and floor-transition rules | No corresponding state | Missing. |
| Bone hearts | Container and break behavior distinct from red/soul health | No corresponding state | Missing. |
| Rotten hearts | Typed red-health behavior and associated effects | No corresponding state | Missing. |
| Golden hearts | An attached effect, not extra ordinary HP | No corresponding state | Missing. |
| Broken hearts | Reduce usable capacity | No corresponding state/capacity accounting | Missing. |
| Health loss order | Depends on heart composition, damage flags and source | Subtract one damage amount from `hp` | Does not model native ordering/exceptions. |
| Representative normal contact hit | Usually half a heart for eligible ordinary contacts on Normal first stage; no-contact enemies remain exceptions | Raw 10 hostile damage becomes **12.5 HP** through `EnemyDamageMultiplier=1.25` | Source-derived DW policy, not a native damage-unit match. |
| Relative survival in that example | Three hearts permit six half-heart losses without healing | 100 HP permits eight 12.5-HP losses | Different survivability; do not generalize this to every damage source. |
| Hit invulnerability | Damage cooldown and source/item exceptions; pinned timing still to measure | `hurt=0.45 s`; damage rejected while hurt or dodging | DW source confirmed; native timing equivalence unknown. |
| Dodge immunity | No universal dodge-roll action for baseline Isaac | Every player can dodge and become immune while `dodge>0` | Additional mechanical advantage. |
| Health upgrades/deals | Change typed containers/health, with item/character exceptions | Arbitrary float max-health changes and percentage/floor item modifiers | Native costs, health ordering and pickup legality not reproduced. |
| Death/revival | Health-type- and item-dependent | Flat `hp<=0` death path; no complete native life/health model established | Missing/unknown beyond ordinary DeathWard death. |
| Between floors | Health and inventory persist, subject to source-specific effects | HP/items/keys/dynamite/money are copied to the next floor | Persistence exists; typed floor-transition effects are absent. No automatic full heal is inferred. |

Heart names above identify distinct required mechanics; their complete exception tables still need pinned tests. They are not instructions to implement all hearts as differently colored HP. Health APIs are documented in the [player API](https://wofsauge.github.io/IsaacDocs/rep/EntityPlayer.html); the current health path is [Player](../src/combat/Simulation.hpp), [hurtPlayer](../src/combat/Enemies.cpp) and [floor transfer](../src/combat/Simulation.cpp).

## Complete baseline player-stat and weapon inventory

The live probe starts at **100 HP, 0 keys, 3 dynamite, 0 money, 0 items, god mode off**.

| Field | Isaac reference | DeathWard current value / behavior | Difference or measurement gap |
| --- | --- | --- | --- |
| Base attack damage | 3.5 documented | 24 | Not a shared scale with enemy HP. |
| Fire rate | `30/(10+1)` ≈ 2.727 shots/s documented baseline | Resolved cooldown 0.29 s: nominal 3.448/s; measured **18 fixed ticks / shot = 0.30 s = 3.333/s** | Thirteen measured intervals in the DW fixture; no native side-by-side firing capture yet. |
| Sustained baseline DPS | About 9.545, before accuracy/defense/effects | Nominal 82.759; measured-cadence arithmetic **80** | Different attack/HP economy. This is arithmetic, not a real-combat DPS test. |
| Movement Speed | 1.0 stat; native velocity, acceleration and stopping distance still to record | Hardcoded 6 world units/s; diagonal input normalized | `1.0` and `6` have different units. Exact speed/inertia parity is unproven. |
| Movement inertia | Source-specific acceleration/friction | Input-driven velocity, collision response and additional launch/pull state | Cannot be certified by comparing one speed number. |
| Firing directions | Standard four-direction firing; input-specific analog behavior must be fixed | Free mouse aim plus directional controls | Broader aiming options are mechanical. |
| Shot Speed | 1.0 stat | 26 world units/s | Native launch velocity and one spatial scale must be measured. |
| Range | 6.5 displayed baseline | Speed/lifetime instead of native Range; 3.2-second lifetime | Maximum straight unobstructed lifetime travel is **83.2 world units**. This is not an Isaac Range conversion. |
| Bullet/tear arc | Source tear-height/fall and movement-inheritance behavior | Straight base player bullets; separate 3D NPC lob/arc rules | Base trajectory is different; inherited motion needs matched captures. |
| Luck | 0 starting value, with effects on applicable rolls | No corresponding general player Luck stat | Missing a shared luck calculation/consumer system. |
| Player collision size | Native collider/touch rules need selected-version capture | Movement/projectile collision uses radius **0.48 world units** | Scale and collision topology not calibrated. |
| Player height / aim | Source logical tear/actor height rules | Player starts at y=0.85; aim can target different 3D heights | Renderer and gameplay differences must be separated. |
| Evasion | No baseline roll | 0.22 s dodge, 1.1 s cooldown, movement multiplier 3.4 | Configured dash speed is 20.4 world units/s before collision. Extra mechanic. |
| Slow movement | Source effect-specific rules | 3.2 world units/s during ordinary player slow, versus 6 normally | Native effect comparison missing. |
| Projectile size | Native tear size/hitbox and damage/flag interactions | Radius 0.14 world units | No proven common scale or full native size formula. |
| Projectiles per trigger | One base tear | One base bullet | Same count only; not full attack parity. |
| Piercing / bounces | None at base; item-dependent flags | Zero at base | Equal absence only. Item behavior still differs. |
| Homing / returning | None at base | Homing=0, return range=0 | Equal absence only. |
| Explosive/rail/scatter modifiers | None at base | Cap damage/radius/self-damage=0; scatter=0; rail=0 | Equal absence only. These are DeathWard-specific modifier interfaces. |
| Cylinder state | No six-round revolver rule at base | `nextRound` cycles 1–6; selected powers react to the sixth shot | Additional state; no blanket base sixth-shot damage bonus is assumed. |
| Stat recalculation | Native cache ordering, additive/multiplicative interactions and caps | Ordered custom `BuildStat` rules and inventory predicates | Not a port of all native stat formulas. `BuildStat::Speed` is projectile speed, not player movement. |
| Active-item slot/charge | Native active item and charge rules; starting D6 conditional | No baseline D6/complete corresponding charge-slot interface in active content | Missing; enum/catalog infrastructure does not implement the mechanic. |
| Pocket slot/trinkets | Native use, swap, drop and capacity rules when obtained | Generic item-kind identifiers exist; active registry here has collectibles only | Missing corresponding active content/complete rules. |

Evidence: [constants](../src/core/Types.hpp), [player/update/fire](../src/combat/Simulation.cpp), [resolved build defaults](../src/content/Mechanics.cpp), [build stat definitions](../src/content/Mechanics.hpp), [item attack resolution](../src/items/Items.cpp), [runtime snapshot](reports/isaac-first-floor-parity/snapshot.json). The firing fixture uses 241 fixed 1/60-second steps and upward aim to avoid terrain impacts. It is a narrow **DeathWard-only** measurement, not an Isaac gameplay recording.

## Enemies: HP conversion does not preserve baseline hits to kill

For a source-stage-1 profile, the comparison uses native XML base HP plus its stage-HP contribution, separately from DeathWard's configured scale. Most examples below use ×3.2 conversion with `regular_health_multiplier=1`. Adaptation factors can change that conversion; Clotty is an example.

| Ordinary body | Isaac stage-1 XML HP | DW stage-1 runtime HP | Hits at Isaac 3.5 | Hits at DW 24 |
| --- | ---: | ---: | ---: | ---: |
| Frowning Gaper | 10 | 32 | 3 | 2 |
| Gaper | 10 | 32 | 3 | 2 |
| Gusher | 10 | 32 | 3 | 2 |
| Horf | 10 | 32 | 3 | 2 |
| Fly | 3 | 9.6 | 1 | 1 |
| Pooter | 8 | 25.6 | 3 | 2 |
| Attack Fly | 5 | 16 | 2 | 1 |
| Spider | **6.5** | 20.8 | 2 | 1 |
| Hopper | 10 | 32 | 3 | 2 |
| Clotty | 15 | 80 | 5 | 4 |

These are **simple body-HP counts**: no champions, armor, healing, invulnerability, damage procs or death transformations. Killing a Gaper body is not necessarily clearing its resulting encounter. Table membership is not a statement that each listed actor is eligible on every Basement I seed. Spider's 6.5 comes from the installed XML, not a conflicting remembered/wiki value.

For the common ×3.2 HP conversion, 1:1 per-hit scaling would require `DW attack / Isaac attack = 3.2`. The current ratio is `24/3.5 ≈ 6.857`, so player attacks are proportionally stronger against those bodies. This is a **difference diagnosis, not an instruction to change the current defaults**.

Other confirmed differences and gaps:

- `regular_health_multiplier=1` is the audited regular-enemy control. It does not govern player damage, player HP or bosses. Source base/stage HP must remain separate from conversion/adaptation.
- Generic enemy paths consume movement ×1.10 and cooldown ×0.85 tuning; the opening floor also has cooldown scale 1.1. These are not universal formulas for every actor: dedicated controllers can use separate native-frame logic.
- Registry speed/cooldown fields can be descriptive or bypassed. For example Gaper movement is force/retention-based, and Horf has a dedicated controller. Do not use the CSV's registry speed as a measured velocity.
- Native-controller timing and death behavior have substantial prior work. The existing ledger nevertheless contains **205 in-progress, 418 missing, 18 existing-unverified and 12 excluded identities; no fully accepted identities**. These are whole-project counts, not first-floor counts.
- Fear/confusion/freeze/slow/charm/shrink/poison/burn have scoped implementations for reviewed actors. Their availability, source-specific immunity, timing, stacking, projectile inheritance, transformations and item interactions must still be checked per actor. Matching a status name is not acceptance.
- Champion combat definitions exist, with a configured 500/10000 spawn roll for eligible actors. Stage gates, color effects, resources, death drops, status interactions and native Normal-mode probabilities need separate proof. Do not interpret 5% as a verified native rate.
- Horf explicitly uses horizontal scale 0.1 and vertical scale 0.03 for its projectile adaptation. That is a documented mechanical adaptation, not a demonstrated uniform graphics scale.

See [93-row candidate comparison](reports/isaac-first-floor-parity/enemy-comparison.csv) and [per-identity unresolved work](reports/isaac-first-floor-parity/enemy-gaps.json). The CSV includes native base/stage HP, source contact scalar/radius, runtime HP, scale/adaptation, body hit counts, pool membership, registry parameters and ledger state. **XML `collisionDamage=1` must not be read as “one full red heart.”**

## Encounter composition and floor eligibility

The live opening encounter tables contain **30 unique candidate IDs across four patterns**. Additional replacement, producer/offspring, hazard and champion paths mean this is not a complete list of everything that can appear.

The parsed source libraries contain 1,181 Basement, 1,148 Cellar and 1,311 Burning Basement entries. Their positive-weight ordinary-room candidate sets contain 71, 80 and 82 entity IDs respectively. These libraries cover chapter contexts and include conditional/difficulty content: **they are not a certified Basement I spawn list**.

Across the combined library/pool candidate set there are 93 identities, of which 47 have no exact registered DW identity. That is a **coverage investigation list**, not proof of 47 missing eligible first-floor enemies. Exact floor-I, unlock, difficulty, subtype and special-context eligibility remains to be resolved. The inventory avoids silently treating same-type numeric XML fallback as subtype behavior acceptance.

DeathWard currently chooses weighted pursuit/crossfire/charge-lane/supply-guard roles, budgets, group sizes and placement anchors. Source room templates and their encounter layouts are not used. Therefore even equal enemy names/HP would not reproduce room difficulty, distances, formations or spawn frequencies. Replacement odds and source-context mappings are also individually authored, with Standard/Scorched opening variants weighted 2:1 rather than proven native stage-selection odds.

Evidence: [floor encounter selection](../src/combat/FloorEncounters.cpp), [encounters](../assets/mechanics/encounters.mechanics), [replacement contexts](../assets/mechanics/replacements.mechanics), [room-library inventory](reports/isaac-first-floor-parity/room-library-inventory.json).

## First-stage bosses — blocking difference

Band 0 currently keeps DeathWard's boss selection. The first-floor weights are Ridgeback/Powder Foreman/Storm Marshal = **6:3:1**. Their starting HP at band 0 is **620 / 500 / 540**, with different attacks and encounter rules. No Isaac native-boss pool is configured for this opening band.

The preserved Basement pool instead lists candidates including Monstro, Gemini, Larry Jr., Dingle/Dangle, Gurglings/Turdlings, Steven, Duke of Flies, Little Horn and Baby Plum. Cellar/Burning Basement have different pool entries. XML pool weights alone do not establish first-floor probabilities: unlocks, exclusions, special selections and room context still need native verification.

For example, Monstro's ordinary XML entity has 250 base HP and zero stage HP. That does not make a 620-HP Ridgeback a scaled Monstro: the actor, phases, movement, attacks and rewards differ. For segmented or multi-entity bosses, the XML per-entity HP must not be summed or called encounter-total HP without recovering the native ownership rules.

The [boss comparison CSV](reports/isaac-first-floor-parity/boss-comparison.csv) and [raw pool summary](reports/isaac-first-floor-parity/source-boss-pools.json) preserve all three source-theme pool entries and per-entity HP/radius data. Conditional selectors, including exceptions outside the ordinary XML pool path, remain unaudited here.

Evidence: [boss weights](../src/world/Expedition.cpp), [configured pool selection](../src/content/EncounterVariants.cpp), [current boss bodies](../src/combat/CanyonBoss.cpp).

## Pickups, special functions, items and economy

| System | Isaac parity requirement | DeathWard evidence / difference |
| --- | --- | --- |
| Starting resources | One bomb, zero coins/keys for the selected Isaac baseline | Three dynamite, zero money/keys observed. |
| Bomb mechanics | Native fuse, blast geometry, collision, self-damage, knockback and variant/item rules | Dynamite has 2 s fuse, 4.5-unit radius, 100 enemy/25 self damage, 12-unit throw range and a 0.45 s action cooldown. Placement, throwing, kicking and supplied bombs have their own rules. Native timing/geometry comparison remains open. |
| Resource capacities | Source caps and item-dependent exceptions | Dynamite cap 9; wallet cap 999,999,999; keys use an ordinary counter. Native cap/effect rules are not reproduced. |
| Heart pickups | Type, healing amount, eligibility, replacement and drop rules | No complete ordinary red/soul/black/etc. pickup system tied to typed health. Shop medicine is not a heart pickup. |
| Bomb/key variants | Native denominations, golden effects, charged/key modifiers and contextual use | Ordinary locks/dynamite exist; full corresponding native variant system is not established. |
| Coins | Denominations, special-coin effects, collection and source drop rules | Preplaced random piles, plus a 35% eligible-enemy drop roll yielding 1–5 coins. Offspring/friendlies/hazards are deliberately excluded. This is a different loot policy. |
| Room-clear rewards | Source reward generation and conditions, not a generic per-enemy coin roll | `clearRoom` emits an event; no source-equivalent full pickup table is established. Custom power/boss rewards are handled separately. |
| Treasure reward | Default pedestal and source item-pool behavior; choice effects are conditional | Choose one of **two** authored offers. This choice is normal DW behavior, not a default Isaac equivalence. |
| Item catalog | All legitimately first-stage-reachable items/effects, filtered by source pools and unlocks | 13 active definitions: 11 DW powers, My Shadow and Skatole. Presence of two Isaac IDs is not complete behavior/availability acceptance. |
| Pool eligibility | Native weights, depletion, blacklist/unlock and reroll behavior | Four authored armory/shop/boss/bargain pools; each offer pair samples without replacement. No complete native pool-depletion/reroll system is established. |
| Active items / D6 | Use/charge, rooms charged, batteries and pedestal rerolls | Missing complete native system. Starting D6 is an unlock-dependent comparison case. |
| Cards/runes/pills | Real pickup pools, slots, identity/effects, use and pill identification | Identifiers can represent kinds, but the active runtime registry has no card/pill/trinket definitions. Full functions are missing. |
| Trinkets | Pickup/drop/swap, multipliers, stacking and luck interactions | No corresponding active trinket content in this snapshot. |
| Transformations and combinations | Preserve positive/negative interactions and state transitions | Custom priority-ordered builds implement some combinations; no full native first-stage interaction matrix. |
| Shop | Source stock, prices, locks, discounts, restocking, unlocks and interactions | Fixed medicine 10, power 25, three dynamite 15; room must be clear and purchase requires proximity. Different stock/pricing rules. |
| Services / bargains | First-floor source eligibility and exact resource/heart costs | Custom exchange/smuggler/surgeon systems have their own floor gates and float-health pricing. Their existence is not Isaac shop/devil/sacrifice parity. |
| Destructible props | Rocks, tinted variants, pots/dung/TNT, contents and item reactions | Physical breakables and some dung/fire reactions exist. Source loot and full variant/item interactions remain partial. |
| Damage/status special cases | Every reachable source flag, immunity, proc and ownership rule | Some audited families exist, but source-specific resource payouts and status/item integration remain open. |

The preserved whole-game XML contains **721 collectible definitions**; this is not the number obtainable on Basement I. Neither `721−13` nor the enemy catalog total is a valid first-floor “missing features” count. A reachable-item/pool/unlock matrix must establish that scope.

Evidence: [runtime items/pools](reports/isaac-first-floor-parity/snapshot.json), [content IDs](../src/content/ContentId.hpp), [item effects](../src/items/Items.cpp), [offers](../src/items/ItemPools.cpp), [shop](../src/combat/Shop.cpp), [services](../src/combat/Services.cpp), [loot](../src/combat/Loot.cpp), [dynamite](../src/combat/Dynamite.cpp).

## Rooms, map, collision and progression

| System | Isaac target | DeathWard difference / current gap |
| --- | --- | --- |
| First-floor map | Source map algorithm, room count distribution, loops and placement constraints | Standard expedition starts with **9 rooms**; Classic comparison uses 15. Same seed text does not reproduce an Isaac map. |
| Full expedition | First-stage behavior must integrate with the intended later progression | Current standard expeditions have 4–8 floors, growing 9→15 rooms. The Lost Survey is a separate five-room, one-floor tutorial. No structure was changed by this report. |
| Room taxonomy | Ordinary/treasure/shop/boss plus eligible secret/super-secret/curse/sacrifice and other conditional rooms | Six DW room kinds: Combat, Power, Boss, Empty, Shop, Service. Story overlays are a separate system. Complete source special-room taxonomy/rules are absent. |
| First-floor eligibility | Some room/deal types are gated; special teleports/items can create exceptions | No certified corresponding eligibility table. Do not require ordinary first-floor devil/angel spawning indiscriminately or ignore reachable exceptions. |
| Layouts | Source room templates, grid occupancy, collision and enemy placements | Seeded geometric rooms, cover, reserves, corridors, cliffs and authored threat roles. Binary room libraries are not the runtime layout source. |
| Room size / spatial scale | Consistent native geometry and speed/shot/radius conversion | DW uses two-metre tiles and variable room extents; Compact starts at half-extents 5–7 tiles. No single approved source-unit transform has been established. |
| Combat exits | Source doors, sealing, bombs and exceptions | Door traversal requires room clear, approach within 3 units and unsealed gates. Route/path constraints differ. |
| Locked rooms | Source key costs, floor-specific free doors and exceptions | Own key-site/lock graph; no complete first-stage lock-rule parity. |
| Secret discovery | Bombable secret/super-secret walls and source restrictions | Breakable terrain/dynamite exist; no full corresponding secret-room graph/discovery implementation. |
| Hazards | Source pits/spikes/creep/fire/poop/TNT and flying/grounded distinctions | Mix of imported controllers and custom 3D collision/terrain behavior. Type-by-type gameplay comparison is incomplete. |
| Sight/cover/height | Visual changes must preserve gameplay targetability and attack rules | Real 3D sight, projectile spheres, slopes and flying-height adjustments affect combat. This exceeds a graphics-only exception unless calibrated to the source rules. |
| RNG | Equivalent distributions and ownership of random streams; exact seed equivalence is a separate goal | Separate authored layout/combat/loot/reward/variant streams and weights. Determinism within DW is not identical source RNG. |
| Story gates | Story may change presentation, but not a claimed identical stage's mechanical exit rules | Some expeditions require story evidence before exiting; Fort Mercy is the between-expedition hub. These are additional rules. |
| Leaving floor I | Native next-stage transfer and reachable carry-over effects | Generated next expedition floor; basic inventory/HP carry over, but typed-health/active-charge transitions are incomplete. |
| Save/load | Preserve all canonical player, enemy, pickup and room state | DW checkpoints exist. Full source-compatible heart/charge/pocket/pool/RNG state cannot be preserved before those mechanics exist. |

Evidence: [expedition](../src/world/Expedition.cpp), [room graph](../src/world/RoomGraph.cpp), [dungeon](../src/world/Dungeon.cpp), [services allocation](../src/world/FloorDressing.cpp), [room travel/progression](../src/combat/Simulation.cpp), [source libraries](reports/isaac-first-floor-parity/room-library-inventory.json).

**Explicit count/position gap:** exact source shop and treasure/upgrade-room counts per floor,their graph-placement rules,boss/other upgrade opportunities and within-room stock/pedestal positions were not verified by this initial audit. They are now individually listed as R16–R23 in the [manual difference register](isaac_first_floor_implementation.md#per-floor-shop-and-upgrade-counts-and-positions). No native per-floor number or fixed position is certified here.

## What a 1:1 implementation would need to prove

| Priority | Work / acceptance evidence |
| --- | --- |
| P0 | Lock version, character, Normal difficulty, unlock profile, Basement I versus alternatives and input mode. Record native start state and identify every reachable first-stage mechanic. |
| P0 | Implement typed heart/container/damage semantics, with exact pickup, damage-order, invulnerability, death and floor-transfer fixtures. Rendering heart icons alone is insufficient. |
| P0 | Establish one canonical time/spatial model. Measure player acceleration, stopping, diagonal speed, hitbox, firing intervals, tear trajectory/range and movement inheritance against installed 1.7.9b. |
| P0 | Preserve baseline hits-to-kill, representative survival and bomb effectiveness. Keep source values, conversion and adaptation distinct; document any deliberate exception instead of calling it 1:1. |
| P0 | Reproduce source room/layout/encounter eligibility and first-stage boss selection/behavior. Test complete ordinary floors, not only isolated actors. |
| P1 | Implement reachable pickups/items, charges, pockets, trinkets, pools, shops, secrets, hazards, champions and special-room rules with conditional cases and interactions. |
| P1 | Verify per-enemy AI, timings, collision, statuses, deaths/offspring and exceptions in mixed rooms. Existing partial controller evidence remains useful, but is not blanket acceptance. |
| P1 | Record repeatable matched input traces and distributions, save/reload cases and complete-floor outcomes. A source registry entry, deterministic replay or a few matching samples does not prove all-stat parity. |

The eventual target still includes **all nonvisual first-stage mechanics**. The priorities above sequence verification; they do not redefine completion as a smaller subset.

## Reproducing this initial audit

The commands below are historical. The implementation/research scripts were moved into the recovery archive during rollback; they are not installed in the live worktree. Consult the current comparison report and restore reference tooling in an isolated checkout only when needed for a manually selected difference.

The read-only content/simulation probe is [archived tools/isaac_first_floor_probe.cpp](/home/kambo/.local/share/deathward/recovery/isaac-parity-20261108T080628Z/removed-files/tools/isaac_first_floor_probe.cpp). It loads the normal mechanics library, exports definitions/pools and performs the narrow DW firing fixture. It writes no campaign save and does not change configuration. Its TSV is archived with this report.

After rebuilding the current `deathward_core` target, the recorded Linux link command and reproduction instructions are in the [audit README](reports/isaac-first-floor-parity/README.md). Then run:

```sh
python3 scripts/isaac-reference/audit-first-floor-parity.py
```

This parses the preserved chapter libraries completely and joins their candidates to the runtime export and existing acceptance ledger. The malformed last closing tag of `bosspools.xml` is corrected only in memory. Source integrity and fixture checks are recorded separately from parity acceptance.

**Remaining:** matched installed-game player/floor measurements, exact floor-I/unlock eligibility, the gameplay implementation and complete first-stage acceptance. No 1:1 gameplay claim or balance change is made by this report.
