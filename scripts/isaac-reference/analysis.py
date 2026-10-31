"""Authored synthesis. These are engineering proposals, not recovered game code."""

CHAPTERS=[
 {'id':'scope','title':'Read this first: what the reference establishes','sections':[
  ('Purpose and edition boundary',[
   'This reference is the research input for a later DeathWard implementation. It combines the installed Repentance 1.7.9b configuration, current wiki revisions, public mod/API source, the previously preserved native disassembly, and an audit of DeathWard. It does not alter gameplay and does not certify the existing DeathWard enemies as faithful ports.',
   '“All” means every record in the installed items, item metadata, pocket items and entity configuration files is accounted for, plus the collected wiki families and mechanics. It does not mean every possible combination of items has been tested. Behavior implemented inside the closed native executable is not fully represented in XML, and the source snapshots here are not the complete original Isaac source.',
   'The baseline is deliberately pinned. The installed files are Repentance 1.7.9b; the wiki also describes older editions and Repentance+. Preserve edition labels. An unqualified current-wiki statement is documented evidence, but not proof it was unchanged in 1.7.9b. The catalog keeps XML facts and wiki descriptions separate instead of silently choosing whichever number is more convenient.'
  ]),
  ('How to use a dossier',[
   'Search by a name, collectible ID, or full entity tuple such as 10.1.0. Read local attributes first, then the specific variant description, then common family notes and interactions. A boss component linked to its parent encounter is clearly labeled as context, not an exact component specification.',
   'For enemies, the calculated HP table covers standard stage numbers 1–13. Room-library presence lists where the exact tuple occurs in stored templates. These lists include unused and zero-weight templates; they are not gameplay probabilities. An enemy can also be spawned by another enemy or an item without appearing in a room template.',
   'For items, XML metadata and pool weights describe configuration. The effects, notes and interaction sections explain behavior. The implementation contract supplies a checklist. Keyword feature tags are triage hints, not a replacement for reading the description.'
  ]),
  ('Evidence ladder',[
   'L — local data: exact bytes, file hash, entity tuple and configured numeric value. D — derived: a calculation explicitly applying a documented formula to local inputs. W — wiki: a community-maintained statement pinned to a revision. C — public code: a statement supported by a specific source file and commit, with the scope of that code identified. P — proposal: DeathWard architecture or adaptation. U — unresolved: no reliable value established.',
   'The public REPENTOGON snapshot targets Repentance+, not the installed executable. Its EntityConfig accessors expose baseHP and stageHP; this corroborates their meaning but does not implement every NPC. Its optional Hush laser-speed patch is a fix with an empirically chosen constant, not a vanilla speed specification. EID provides factual naming and useful comparison material, not the original game AI. EID description text is not republished in this report.',
   'The older native-analysis folder covers selected bomb/grid/door functions. It is useful evidence for that subsystem only. Nothing in this reference should be described as a complete decompilation of the game.'
  ])], 'sources':['Stage HP','Damage Scaling']},
 {'id':'coverage','title':'Catalog boundaries and completeness','sections':[
  ('What is included',[
   'The local catalog contains 721 collectible definitions, 188 trinkets, 98 card/rune definitions including the NULL sentinel, 50 pill effects, 49 null/internal item rows, and 1,337 entity rows. Entity type IDs 10–999 account for 653 NPC/hazard/component rows: 468 without the boss flag and 185 with it. Those are definition counts, not the number of unique normal enemies or boss encounters.',
   'Every collectible and trinket has a linked wiki dossier. Every pill is joined by numeric effect ID to the pill-effect table, retaining normal and horse-pill behavior. The NULL card is intentionally not a usable card. Internal records and effects remain visible in the data so later implementation cannot accidentally confuse them with obtainable content.',
   'NPC rows include limbs, chains, heads, phase controllers, environmental hazards, cut enemies and scenery. The report does not convert them all into independent encounters. The Beast background actors, Mother’s auxiliary entities and split boss fragments must be interpreted within their parent fight.',
   'The collected interaction statements include positive synergies, incompatibilities, overrides, duplicate-copy rules and nested conditions. A statement can mention several items and is not necessarily a pairwise edge. Missing an edge means undocumented in this collection, not “these items do nothing together.”'
  ]),
  ('Coverage is not parity',[
   'Exact-ID matches, variant-family links, name matches and parent-context links are separate evidence classes. Historical ID reuse is resolved by the installed definition name where possible. For example, collectible 474 is Broken Glass Cannon in this baseline; the old passive Tonsil occupied that number in an earlier edition.',
   'Two null/internal rows share ID 124. Their XML rows are both preserved with distinct record keys. Collectibles, trinkets, cards and pills also use overlapping numeric IDs. A flat integer registry would be ambiguous.',
   'Some XML entries have no reliable public behavior dossier. They remain in the unresolved list. Do not make up walk speeds, attack intervals, probabilities, phase thresholds or state durations to make a spreadsheet look complete. The next implementation can make explicit design choices, but those must be recorded as adaptation values.'
  ])], 'sources':['Items','Trinkets','Pills','Cut Content']},
 {'id':'health','title':'Enemy HP, floor scaling, champions and armor','sections':[
  ('Base HP and Stage HP',[
   'The standard documented formula is HP = baseHP + stageHP × [min(stage, 4) + 0.8 × clamp(stage − 5, 0, 5)]. Therefore the stage multipliers for stages 1–13 are 1, 2, 3, 4, 4, 4.8, 5.6, 6.4, 7.2, 8, 8, 8, 8. Stage V is a plateau, not another full increment. A configured stageHP of zero leaves HP unchanged under this formula.',
   'The wiki’s worked Dip example uses baseHP 3 and stageHP 1: 4 HP on stage I, 9.4 on stage VIII, and 11 at stage XII. This calculation is reproduced by the validator. The report uses each local row’s actual inputs, not the wiki’s current HP number, for its derived table.',
   'Stage is an Isaac progression index. It is not DeathWard’s room count or a display label. Alternative paths, Greed mode and exceptional encounters need their own stage mapping. Four to eight DeathWard floors should explicitly map to an intended difficulty curve instead of blindly using the floor number in every Isaac formula.',
   'XML HP is a starting configuration. Boss phases may share health, replace an entity, initialize HP at runtime or use untargetable helper entities. Never sum every boss-flagged row to obtain “boss HP.” Summing Mother’s body, ball helpers and effects would have no meaningful interpretation.'
  ]),
  ('Champions and room difficulty',[
   'Champion modifications are a separate layer: visual identifier, HP adjustment, projectile/contact behavior, death effect, drops and immunities. They must be specified by champion type and edition. The Champions article is included in full; its exceptions should not be flattened into one universal HP multiplier.',
   'The STB difficulty field ranks room templates, not individual enemy level. Room size, arrangement, environmental hazards and enemy combinations change practical difficulty even when entity HP is identical. A stationary Horf near an open exit and the same Horf covering a narrow gap present different encounters.',
   'Do not balance an entire expedition by raising HP alone. Prefer floor-specific pools and combinations, stronger variants, denser patterns, more demanding timing, and bosses whose moves have already been introduced by ordinary enemies. Keep safe entry space and a readable route around damage zones.'
  ]),
  ('Damage scaling / boss armor',[
   'The Damage Scaling article describes adaptive reduction using incoming damage over a four-second history window, with XML shieldStrength participating in the soft DPS limit. Starting armor and adaptive armor are distinct. Some bosses reapply starting armor during transitions. Large single hits and specific damage sources have special handling.',
   'This system cannot be recreated as a constant percentage resistance. It requires a time-stamped damage history, the correct pre/post-mitigation order, a definition of what counts toward that history, and encounter-specific exceptions. Preserve the complete article and verify those exceptions before implementing.',
   'Game logic and rendered frames are different units. Some descriptions count 30 Hz game ticks, while visual measurements may count 60 Hz frames. Store seconds plus the original unit and source. Never insert a number labeled “frames” directly into a render-frame timer.',
   'For DeathWard, decide explicitly whether adaptive armor is wanted. A canyon boss can use readable phases and encounter mechanics without copying every Isaac armor behavior. If parity is the objective, armor is a required subsystem and needs burst, sustained-DPS, idle-decay and phase-transition tests.'
  ])], 'sources':['Stage HP','Champions','Damage Scaling','Hard Mode','Greed Mode']},
 {'id':'ai','title':'How to turn enemy descriptions into executable behavior','sections':[
  ('State is more than a movement enum',[
   'Use the dossier to describe a directed state machine: spawn/activation → acquisition → movement → windup → emission → recovery, with damage, phase and death transitions. Some enemies omit most states; others have several independent controllers. A chasing body and a detachable attacking head cannot reliably be expressed by one shared cooldown.',
   'For each state record entry conditions, target-selection rules, exit conditions, movement authority, collision masks, vulnerability, emitted effects, animation events and RNG draws. Separate distance checks from line of sight, cardinal alignment and path reachability. Those conditions produce different behavior in rooms with obstacles.',
   'Keep navigation and attacks deterministic. Use explicit per-entity or per-attack RNG streams so a decorative dust particle cannot change whether a boss chooses a charge. Stable ownership is required for summons, split enemies, charm, reflected shots and kill credit.',
   'An attack needs a telegraph, active interval and recovery. Target coordinates may lock at the start of the telegraph or track until emission; homing can begin only after launch. These distinctions must be decided from evidence. “Fires toward the player” does not tell us all of them.'
  ]),
  ('Reusable behavior families',[
   'Pursuers require steering, obstacle handling, crowd avoidance and contact rules. Fleeing enemies need avoidance behavior and an escape preference. Chargers require alignment/acquisition, locked direction, acceleration or immediate velocity, wall response and a recovery state. Hoppers need an airborne interval and an explicitly timed landing hazard.',
   'Stationary shooters need a target/aim policy and attack schedule. Burrowers and teleporters need legal destination selection and invulnerable windows. Wall crawlers need a wall/topology representation. Mirrors require a player-input transform rather than a normal chase target. Chains and orbiters require ownership and constraint handling.',
   'Summoners and splitting enemies need child budgets, spawn-space checks and room-clear accounting. Invulnerable room hazards need a rule for when they stop attacking after the room is cleared. Boss helper entities should not keep a cleared floor locked because they were counted as ordinary enemies.',
   'Navigation belongs to the gameplay plane. Cosmetic height, rocks made transparent for visibility, and a projectile’s visible arc must not silently change whether it can hit or be hit. In canyon rooms, telegraphs and enemy silhouettes need to remain readable behind scenery without changing attack semantics.'
  ]),
  ('Measurement sheet for unresolved numbers',[
   'Use a pinned executable and controlled debug room. Record build hash, mode, seed, full entity tuple, champion status, floor stage, player stats, held items and starting positions. Remove other enemies and environmental hazards unless they are the variable being measured.',
   'Capture activation-to-windup, windup-to-emission, projectile displacement per logic tick, recovery and next attack. Repeat trials when the behavior is randomized. Record sample count, distribution and uncertainty rather than presenting one observed delay as a universal constant.',
   'Test line of sight with a wall, alignment with lateral displacement, destination validity with pits, and whether the target is locked by moving during the windup. Test slow, freeze and charm separately. For death effects, vary overkill and damage source, and inspect both spawned children and room-clear status.',
   'These are proposed experiments, not results claimed by this research. Unknown fields remain null until a reliable source or controlled observation establishes them.'
  ])], 'sources':['Monsters','Status Effects','Creep']},
 {'id':'items','title':'Items and perks: architecture for deliberate interactions','sections':[
  ('Classify the effect, not merely its rarity',[
   'Separate stat modifiers, weapon replacements, per-shot modifiers, on-hit/on-kill effects, damage-reactive effects, orbitals/familiars, active items, economy/pool effects, navigation/information effects, transformations and character-specific effects. One item can participate in several categories. Quality is a selection/balance attribute, not an implementation category.',
   'A collectible definition needs identity and version, acquisition/removal behavior, stacking, stat-cache effects, activation/charge policy, event subscriptions, duration and persistence, and all documented exceptions. A trinket additionally needs held versus swallowed behavior, duplicate copies, golden status and Mom’s Box amplification. The amplification is not universally “double every number.”',
   'Pills require a seeded run-level mapping between appearance and effect, identification state and pool changes. Horse pills have distinct effect rows. Cards/runes require consumable-specific target, duration, resource and room-state behavior. Treating all consumables as a single immediate buff loses essential mechanics.'
  ]),
  ('A proposed stat and attack pipeline',[
   'Recompute stats from a canonical base plus owned effects; do not repeatedly mutate the last computed value. Record additive changes, multiplicative changes, caps, special overrides and order-sensitive conversions. Tear delay and fire rate are different representations; some items operate before and others after their conversion.',
   'A proposed attack pipeline is: input and charge → resolve weapon form → apply form-specific overrides → compute stat snapshot → determine volley/pellet count → initialize projectile/beam/bomb → apply trajectory and targeting → resolve collision/damage → process hit/death/expiry child effects. This is an engineering design for DeathWard, not a claim about Isaac’s native function order.',
   'Each emitted attack must retain owner, source item(s), damage flags, initial stats, generation depth, RNG state and proc eligibility. Otherwise a split child can incorrectly reapply a parent-only multiplier or trigger an endless split/explosion loop. Snapshotting must be intentional: effects that read live stats should explicitly request that behavior.',
   'Repeated-contact weapons need per-target hit intervals. A knife, continuous beam and Tech X ring are not ordinary projectiles with a large collision radius. The center of a ring and its circumference have different collision semantics. Piercing, spectral travel, homing, penetration and damage-on-contact are independent properties.'
  ]),
  ('Interaction resolution',[
   'Build an explicit compatibility table for weapon forms and a rule registry for exceptions. Do not assume alphabetical item order, acquisition order or a universal “strongest weapon wins.” A rule can replace a form, add a secondary attack, change a rate formula, alter a proc source or suppress another effect.',
   'Store each rule’s selected edition, participating items, preconditions, consequence, precedence, supporting revision and tests. Positive synergies and negative interactions deserve equal representation. Keep nested statements with their parent condition; an indented explanation is not an independent universal rule.',
   'The collected interaction graph is a discovery index, not an executable truth table. Resolve target names to typed item IDs, inspect the complete source section, and create a reviewed rule. Higher-order combinations must be tested because two individually correct pair rules can conflict when a third modifier changes the weapon form.',
   'Do not generate all 721×721 pairs as implementation tasks. Begin with the documented graph, the high-risk weapon forms, shared mechanics and a targeted set of triples. The long tail still requires explicit review, but a combinatorial checklist without expected behavior would not establish correctness.'
  ])], 'sources':['Tears','Damage','Items','Trinkets','Pills','Item Quality','Item Tags','Transformations']},
 {'id':'weapon-examples','title':'Weapon forms and interaction cases that expose engine requirements','sections':[
  ('Representative form contracts',[
   'Brimstone: a charged, piercing, spectral blood laser with repeated damage ticks and edition-specific rate/duration behavior. The linked article documents nine ticks over roughly 0.63 seconds in Repentance, compared with thirteen over roughly 0.9 seconds before Repentance. At sufficiently high fire rate the continuous-beam case has its own damage treatment. Test actual tick scheduling rather than using damage-per-frame.',
   'Mom’s Knife: a charge-dependent thrown/returning hitbox with damage changing along its lifecycle and frequent repeated contact. A generic projectile speed and damage pair is insufficient. Tests must distinguish held, outbound, maximum-charge and returning behavior.',
   'Tech X: traveling laser-ring circumference, charge-dependent size and damage, repeated contact, and spectral/piercing behavior. Test a target at the center versus on the ring. Technology is a straight laser and has a different shape and cadence; sharing a renderer should not erase this distinction.',
   'Dr. Fetus: fired bombs with a fuse and a piecewise Repentance damage formula: 10× tear damage up to the 60-damage threshold, then 5× tear damage + 30. The fuse, bomb movement, owner damage and bomb-item interactions belong to the bomb subsystem. Epic Fetus instead uses a movable targeting marker and delayed missiles.',
   'Ipecac: arcing explosive poison shots, a large flat damage contribution and substantial rate/range changes. The damage bonus is not just a multiplier. Test explosion ownership, poison, self-damage and what happens when another weapon form consumes the explosive modifier.',
   'The Ludovico Technique: a persistent player-controlled attack object. It needs an alternate input/targeting mode and its own interactions. It cannot be modeled by spawning one ordinary tear every time the player presses fire.',
   'Haemolacria: arcing parent tears that burst into a random number of children with specified relative damage, plus a carefully ordered tear-delay adjustment. Cricket’s Body and The Parasite also spawn children, but their counts, triggers, range inheritance and recursion limits differ. Use separate effect policies on a common child-spawn service.'
  ]),
  ('Interaction regression cases',[
   '20/20 + Mutant Spider / The Inner Eye: verify the Repentance rate-penalty override and damage adjustment. Multiplying “double shot” by “quad shot” is not the documented implementation. Add duplicate-copy and maximum-volley tests.',
   '20/20 + Polyphemus: verify the documented special damage/rate combination rather than composing two generic stat records. Test both pickup orders and reloading the same build.',
   'Soy Milk + Brimstone: test how the very high fire rate changes beam behavior and damage ticks. Soy Milk + ordinary tears provides a separate baseline for its damage/rate changes. Almond Milk also changes trajectories and cannot reuse Soy Milk with a different tint.',
   'Haemolacria + rate modifiers: test rate multipliers below one, additive fire-rate changes and multipliers above one around Haemolacria’s delay conversion. The order is explicitly discussed in its dossier and is a good regression target for the stat engine.',
   'The Parasite + splitting/penetration effects: test collision-triggered children, child damage and remaining range, including termination below the documented thresholds. A generation cap is a safety mechanism, but it must not silently replace a documented rule.',
   'Active items + Book of Virtues / Car Battery / batteries: test distinct activation events, charge consumption and spawned wisps. A second activation is not universally equivalent to doubling the first activation’s numerical result.',
   'Damocles, reroll effects and temporary item grants: test persistent hidden effects and item identity. The active collectible and the granted passive implementation record can be different IDs even when they share a public name. Do not expose internal implementation items as ordinary loot.'
  ])], 'sources':['Brimstone',"Mom's Knife",'Technology','Tech X','Dr. Fetus','Epic Fetus','Ipecac','The Ludovico Technique','Haemolacria',"Cricket's Body",'The Parasite','20/20','Mutant Spider','Polyphemus','Soy Milk','Almond Milk','Book of Virtues','Car Battery','Damocles']},
 {'id':'enemy-examples','title':'Worked enemy specifications: preserving the distinguishing rules','sections':[
  ('Gaper / Frowning Gaper',[
   'Documented behavior: ordinary Gapers pursue and path around obstructions. Their death can produce a Pacer or Gusher: a 50% initial spawn check, followed by a one-third Gusher choice if that succeeds. This corresponds to about one-sixth Gusher, one-third Pacer and one-half no child. The family has an overkill exception described in its Notes.',
   'Proposed states: pursuing → dying → optional child handoff. Frowning Gaper adds eyes-closed pursuit → permanent eyes-open faster pursuit when line of sight is acquired. This is a persistent transition, not “move faster whenever visible.”',
   'Tests: obstacle pathing; loss and reacquisition of sight after the eye transition; no contact during the death handoff; offspring probabilities using seeded trials; overkill just above and below the documented threshold; Level 2 Gaper exception. Exact speed and the RNG sequence remain measurement tasks.'
  ]),
  ('Host / Red Host',[
   'Documented behavior: a lowered Host is invulnerable to ordinary direct damage, with listed status/knockback exceptions. It opens, becomes vulnerable, and fires a three-shot spread. Attacking it while closed delays opening. The article states that Hosts do not deal contact damage.',
   'Proposed states: closed → opening → exposed attack → closing. Damage filtering and timer extension belong to the state machine; they should not be emulated by a huge HP value. Red Host and other variants have their own rules. Repentance+ Hagalaz changes must not leak into a 1.7.9b profile.',
   'Tests: closed versus open projectile damage; contact in both states; status damage; repeated hits extending the closed period; no projectile emitted before the intended animation event; a room with only a Host must still be completable.'
  ]),
  ('Mulligan family and detachable heads',[
   'Mulligans flee, can release children on death and have an overkill exception. Mulligoons and Mullibooms change the death/attack consequences. Sharing a silhouette or family page does not justify sharing all damage and spawning rules.',
   'Mr. Maw combines a pursuing body and an attacking head, with different outcomes depending on which part is killed. Mr. Red Maw, Mr. Mine and Swinger extend that family in different ways. Model their owner/child relationships explicitly. A chain or neck is not an additional loot-paying enemy.',
   'Tests: kill body first, head first and both in one explosion; verify no duplicate rewards or orphan colliders; save/load while detached; apply charm or freeze; make the chain cross an obstacle. The contract must specify how the parts participate in room clear.'
  ]),
  ('Ordinary patterns still need variant-specific review',[
   'Use Horf/Pooter to establish aimed shooting, Clotty variants for cardinal versus diagonal patterns, Charger/Knight for acquisition and charges, Hopper/Leaper for landing timing, Spider for short movement bursts, Dople for mirroring, and Lump/Para-Bite for hidden movement. Each family dossier retains its full description and variant boxes.',
   'These are a useful implementation order because the primitives are reused by harder encounters. They are not a statement that every enemy can be reproduced by combining one movement enum and one attack enum. The timers, eligibility conditions, damage windows and exceptions still differ.'
  ])], 'sources':['Gaper','Host','Mulligan','Mr. Maw','Horf','Pooter','Clotty','Charger','Knight','Hopper','Leaper','Spider','Dople','Lump','Para-Bite']},
 {'id':'bosses','title':'Bosses, phases and canyon adaptations','sections':[
  ('Encounter contracts',[
   'A boss specification needs arena constraints, entry conditions, health ownership, phase thresholds, eligible move sets, selection rules, telegraphs, projectile geometry, adds, invulnerable windows, transitions, death resolution and rewards. The complete boss articles are attached, including phase and champion sections; the infobox alone is never the specification.',
   'Keep encounter controllers separate from targetable entities. The Haunt’s first phase ends when its required children die; a Mother transition changes the arena; segmented/splitting bosses can redistribute the encounter across entities. Treating all three as a single HP threshold discards their defining mechanics.',
   'Boss difficulty depends on room geometry. A dodge lane that works in a rectangular Isaac room may be blocked by a canyon decoration or river bank. Validate each generated arena against the move set before choosing the encounter. Telegraphs must remain visible under the selected original art style and occlusion system.'
  ]),
  ('Three concrete examples',[
   'Dingle: stationary projectile attack, a summon-and-shoot action, and a sequence of three long dashes with a recovery pause. The whistle distinguishes the summon action. A recreation needs separate move selection, summon count, dash sequence tracking, wall response and recovery; one generic charge action is insufficient.',
   'Monstro: short hops, a projectile cough and a high leap aimed at the player followed by a landing burst. The high jump needs a target-lock policy, airborne vulnerability/collision rules, landing telegraph and projectile timing. A canyon version could preserve the leap/cough grammar with an original creature design.',
   'The Haunt: invulnerable parent with staged child activation, followed by a wall-bound phase with downward beam/spread attacks and a proximity dash. Spawn the parent and children as one encounter with explicit completion accounting. Do not allow the parent to become vulnerable merely because an unrelated enemy died.'
  ]),
  ('Late-game and special-route fights',[
   'The catalog includes Mom, Mom’s Heart / It Lives, Isaac / ???, Satan, The Lamb, Mega Satan, Hush, Delirium, Mother, Dogma, the Ultra Horsemen, The Beast and Greed-route encounters, as well as ordinary floor bosses and minibosses. Their routes, components and phases differ; they should not be pooled indiscriminately into ordinary floors.',
   'Hush and Delirium need careful armor/timing work. Mother needs multiple targetable parts, projectile subpatterns and arena transition. Dogma and The Beast involve presentation and movement rules beyond the normal room encounter. These are later implementation stages after ordinary combat, ownership and boss controllers are reliable.',
   'For DeathWard, preserve the intentional expedition structure: 4–8 seeded floors, the current non-tutorial room progression, and story rooms inserted at appropriate points. Build original canyon boss presentations on reviewed combat contracts. This report does not propose replacing an expedition with a short sequence of story encounters.'
  ])], 'sources':['Bosses','Dingle','Monstro','The Haunt','Mom',"Mom's Heart",'Mega Satan','Hush','Delirium','Mother','Dogma','The Beast','Ultra Greed']},
 {'id':'floors','title':'Floor identity and room ecology','sections':[
  ('What changes between chapters',[
   'Early chapters teach individual movement and projectile patterns with relatively readable combinations. Later chapters add more dangerous variants, environmental constraints, invulnerability, beams, movement denial and multi-enemy combinations. Alternative-path floors also change hazards and progression rules. The stage articles and room-library tables provide the source material; this interpretation is a design synthesis.',
   'Build a floor profile from an eligible enemy pool, variant policy, room-size distribution, threat budget, hazard budget, resource availability, reward pools and boss set. Keep these controls separate. A larger room does not always deserve linearly more enemies, particularly when several enemies deny the same movement corridor.',
   'Use the STB presence data to investigate which enemies coexist in which floor libraries. It is evidence of authored possibilities, not a probability distribution. Actual selection also depends on room type, shape, difficulty, weights, progression, replacement rules and runtime spawns.'
  ]),
  ('DeathWard translation',[
   'A proposed canyon progression can distinguish open dry washes, tighter ravines, abandoned works/mines, military remnants and exposed storm routes through enemy pools and environmental rules. Rivers and interior tracks should constrain spawn and dodge space consistently. These are art/gameplay proposals, not Isaac floor equivalents.',
   'Keep the first standard floor compact enough to establish a build and a direction. The tutorial remains the separate five-room, one-floor Lost Survey expedition. A story/evidence room should be placed by narrative constraints inside an otherwise systemic floor.',
   'Your current restrictions—one trader total per room and no Field Surgeon on floors 1–3—belong in the room eligibility policy. Item implementation must not bypass them by accidentally spawning another service NPC from dressing or a separate reward pass.'
  ]),
  ('Optional rooms and costs',[
   'Shops trade currency for controlled choices; locked treasure rooms compete for keys; curse/sacrifice rooms can trade health for uncertain value; challenge rooms trade risk and time for rewards; secret rooms turn bombs and observation into resources. Pool identity and access cost are part of the reward, not merely room decoration.',
   'Keep opportunity costs visible. If a bomb can destroy a barrier, open a secret entrance, damage a boss or extract a resource, spending it changes the route. A free reward in every side room does not reproduce that decision structure.',
   'When porting pool behavior, keep pool weights, depletion and replacement rules separate from drop rates. The local XML lists Weight, DecreaseBy and RemoveOn. They are configuration inputs, not a direct percentage chance that a player receives the item during an expedition.'
  ])], 'sources':['Floor Generation','Chapters','Item Pool','Shop','Treasure Room','Curse Room','Sacrifice Room','Challenge Room','Secret Room','Basement','Downpour','Mines','Mausoleum','Corpse']},
 {'id':'bombs','title':'Bombs, destructible terrain and resource consequences','sections':[
  ('Separate entity damage from grid destruction',[
   'An explosion has several outputs: entity damage, knockback, grid damage/destruction, secret-door discovery, chain reactions and item-triggered effects. Those outputs can have different eligibility rules and radii. A visual sphere overlap alone is not a complete explosion implementation.',
   'Grid objects need a typed contract: rock family, poop, fireplace, TNT, mushroom, skull, pot, bucket, special barrier or door. Each needs allowed damage sources, stages of damage, destruction effect, drops, collision/navigation update and persistence. The Rocks, Poop, Fireplace and Obstacles sources provide the public rules; preserved native snippets cover selected grid/door paths.',
   'Special rocks, resource containers and explosive hazards must not be inferred solely from model shape. A destructible crate is an explicit gameplay object. A decorative barrel should not unexpectedly share TNT behavior because it uses a similar mesh.'
  ]),
  ('DeathWard contract',[
   'Use the existing placed dynamite and collision kick behavior as input to an explosion service. The porting work concerns what the explosion affects and which item modifiers alter it. Preserve ownership when an enemy, player or chain reaction detonates a charge.',
   'Apply damage/destruction once per explosion/object pair. Queue chain reactions to avoid recursive stack explosions and duplicate loot. Update collision, navigation, occlusion, shadows and interaction targets when an object is destroyed. Save the resulting room state so leaving and returning cannot farm the same container.',
   'Validate barriers as part of floor generation. A required exit must remain reachable with available resources, or the map must provide an alternative. Hidden optional passages can consume resources; a mandatory route should not become an accidental softlock because the player used the only bomb in combat.',
   'Tests: a row of TNT, a multi-part boss overlapping an explosion, a rock beside a secret door, a container hit by two simultaneous explosions, destruction beside a river/ford, and save/load after the explosion. Include bomb-enhancing items and self-damage immunities as separate interaction cases.'
  ])], 'sources':['Bombs','Obstacles','Rocks','Poop','Fireplace','Secret Room','Mr. Mega','Dr. Fetus','Host Hat','Pyromaniac']},
 {'id':'porting','title':'Implementation plan for the next phase','sections':[
  ('P0 — fix identity and define compatibility',[
   'Choose a named ruleset: Repentance 1.7.9b parity, current Repentance+ parity, or a documented DeathWard adaptation. Keep the selected ruleset in saved games and test fixtures. Do not accidentally combine 1.7.9b XML with Repentance+ balance changes.',
   'Replace the two-decimal-digit variant packing in monsterId before importing the complete registry. The current expression type×10000 + variant×100 + subtype collides when variants reach 100: 912.100.0 and 913.0.0 both pack to 9,130,000. The full data includes such variants. Use an explicit tuple/struct, typed namespaces and a save migration.',
   'Keep null/internal records separate from obtainable items. Give record provenance a first-class place in the data schema. Add an explicit mapping from Isaac units and stage indices to DeathWard world units, HP and floor progression. These are prerequisites for reliable import.'
  ]),
  ('P1 — foundations before hundreds of definitions',[
   'Implement canonical stat recomputation; typed damage and immunity; deterministic RNG streams; status effects; collision categories; projectile/beam/bomb shapes; ownership and child-spawn accounting; room/floor/run lifecycle events; item pool/resource services; and save serialization.',
   'Turn the existing movement and attack primitives into reusable state-machine actions, not the only available behavior model. Add a controlled encounter test room with fixed positions, visible hitboxes, state/timer display, spawn-by-tuple, damage logging and deterministic replay. A diagnostic tool should not intrude on the normal expedition HUD.',
   'Acceptance: a baseline projectile, beam, thrown/returning hitbox, arcing explosive and persistent controlled attack work at different render rates; damage and RNG logs match for the same fixed-tick input; child kills and room completion are counted exactly once.'
  ]),
  ('P2 — small vertical slices with real interactions',[
   'First implement a basic chase family, stationary shooter, cardinal/diagonal shooter, charge, hop, invulnerability-state enemy, summoner and split/death-child enemy. Include one multi-part boss and one phase-gated boss. For each, complete the variant and negative-condition tests before increasing catalog breadth.',
   'For items, select one stat modifier, one rate modifier, one multishot item, one homing/piercing modifier, one splitting item, one weapon replacement, one active item, one defensive item, one resource item and one familiar. Implement a few documented interactions across those systems, including an override or incompatibility.',
   'Acceptance: the player can assemble a build whose behavior changes visibly and correctly; all involved interactions have explicit expected outputs; existing Western item effects still work or have a deliberate migration path. This slice demonstrates the architecture without pretending a large list of names is a complete implementation.'
  ]),
  ('P3 — exhaustive registry work in reviewed batches',[
   'Use the per-record contracts as a work queue. For each collectible/trinket/consumable: select edition, review effect/notes, implement lifecycle and stat rules, resolve documented interactions, add representative tests, mark remaining unknowns and only then enable it in an eligible pool.',
   'For each enemy/variant: classify its role, bind configured HP and collision attributes, specify state transitions and parameter evidence, implement attacks/death behavior, test status effects and room completion, then add it to approved floor pools. Component-only and cut records should stay out of ordinary encounter selection.',
   'For bosses: implement the whole encounter and supporting entities together. Add the standard, champion and route-specific variants deliberately. Keep high-complexity forms, armor-heavy bosses, character-specific item behavior and special-route encounters in explicit later batches rather than approximating them silently.',
   'Acceptance is per record and interaction, not merely “the code compiles.” A status matrix should distinguish researched, specified, implemented, unit-tested, encounter-tested, balanced and enabled. This report establishes research coverage, not those later states.'
  ]),
  ('P4 — expedition integration and balance',[
   'Apply floor identities, encounter budgets, room-type eligibility, boss selection, destructibles and reward pools to the 4–8-floor expedition system. Place testimony/evidence rooms at the required floor/time without replacing the systemic run. Preserve safe entrance behavior and pre-entry enemy presence/animation.',
   'Test seeded full expeditions for reachability, resource bottlenecks, mandatory-route bombs, river/track conflicts, safe spawning, story-room eligibility, readable boss telegraphs, shopkeeper count and service-floor restrictions. Measure pacing and player outcomes separately from mechanical parity.',
   'Tune DeathWard units and aesthetics only after the behavior is understood. Document every intentional divergence—HP scaling, projectile speed, room dimensions, enemy density, weapon controls and encounter presentation—so future fixes do not mistakenly “correct” a design choice back to Isaac.'
  ])], 'sources':[]},
 {'id':'validation','title':'Validation matrix and completion criteria','sections':[
  ('Data checks',[
   'Require unique typed record keys, explicit handling of duplicate internal IDs, valid wiki section references, complete local XML inventory counts, all 50 pill effects, valid source hashes, and exact binary consumption for all room files. Verify that effects with a boss flag are not counted as normal bosses solely because of that flag.',
   'Spot-check entity family ID inheritance, historical item ID reuse and alternate item implementation records. Keep the local HP value and the wiki HP field side by side when they disagree. Do not resolve discrepancies by silently overwriting a source.',
   'The validator checks representative HP calculations and the monsterId collision. The HTML should work offline from file://, without third-party scripts, image downloads or a running server. Search and filters must not omit records beyond the first page.'
  ]),
  ('Future behavior checks',[
   'Movement: deterministic initial position, target motion and obstacles; expected state transitions and reachable path. Attack: telegraph event, projectile count/angles, target lock, speed, lifetime, damage and recovery. Damage: direct, contact, explosion, status, reflected, familiar, environmental and overkill sources.',
   'Items: pickup/removal/duplicate copies; both acquisition orders; charge/use; room/floor transitions; death/revival; save/load; weapon-form overrides; nested interactions; proc frequency and child ownership. Include positive and negative expectations.',
   'Bosses: phase thresholds and eligibility, shared health, simultaneous part damage, starting armor, invulnerability windows, child cleanup, reward exactly once and floor exit activation. Test extreme player damage as well as weak builds.',
   'Performance: dense projectiles, many familiars, repeated chain explosions and multi-child deaths must remain bounded and deterministic. Rendering load and AI behavior should be profiled independently so a visual slowdown cannot alter mechanics.'
  ]),
  ('What remains unknown',[
   'This research does not establish every native AI timer, attack weight, pathfinding tie-break, acceleration value or hidden interaction. Public descriptions often state relative speed or qualitative behavior. The explicit nulls and unresolved entries are an honest work list, not values to fill with guesses.',
   'No new controlled Isaac gameplay trials were performed for this report. No claim of binary-equivalent reimplementation is made. The selected public code is a modding/reverse-engineering project, and the previously preserved native snippets cover only a small subsystem.',
   'The report is ready to guide implementation because the sources, differences, component relationships, engine requirements and tests are explicit. “Everything implemented” will require the later per-record status matrix and measured parity checks, not just this research artifact.'
  ])], 'sources':[]}
]

CODE_REFERENCES=[
 {'title':'REPENTOGON: XML baseHP/stageHP accessors','path':'repentogon/LuaInterfaces/LuaEntityConfig.cpp','line':169,
  'finding':'GetBaseHP/GetStageHP return configuration fields. They expose values; they do not implement enemy AI.'},
 {'title':'REPENTOGON: Hush laser fix','path':'repentogon/Patches/ASMPatches/ASMEntityNPC.cpp','line':12,
  'finding':'Optional, daily-disabled patch with an explicitly empirical speed multiplier. Do not use it as the vanilla constant.'},
 {'title':'REPENTOGON: NPC state bindings','path':'libzhl/functions/EntityNPC.zhl','line':118,
  'finding':'Exposes Delirium transformation timer/state/attack fields. Existence of fields does not establish their complete transition logic.'},
 {'title':'REPENTOGON: Delirium patches','path':'repentogon/Patches/ASMPatches/ASMDelirium.cpp','line':1,
  'finding':'Transformation hooks/patches are source evidence about the modded hook, not a complete native boss implementation.'},
 {'title':'Preserved native explosion analysis','local':'reference/isaac-repentance-1.7.9b/native-analysis/game_bomb_explosion_effects.asm',
  'finding':'Previously preserved selected disassembly. Scope is bomb effects, not all monsters/items.'},
 {'title':'Preserved native grid destruction analysis','local':'reference/isaac-repentance-1.7.9b/native-analysis/room_destroy_grid.asm',
  'finding':'Previously preserved grid destruction disassembly; interpret with the original provenance and executable hash.'},
 {'title':'Preserved native door explosion analysis','local':'reference/isaac-repentance-1.7.9b/native-analysis/door_try_blow_open.asm',
  'finding':'Previously preserved door/explosion path; not evidence for unrelated interactions.'}
]
