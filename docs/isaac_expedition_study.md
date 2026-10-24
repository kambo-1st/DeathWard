# Isaac mechanics and DeathWard expedition design

Analysis date: 2026-10-24. DeathWard baseline: `955ef8f` on `main`.

Status: reference study and proposed work. [Offline HTML edition](reports/isaac-expedition-study-2026-10-24.html) · [Preserved source data guide](../reference/README.md).

**The strongest opportunity is to connect builds, room choices, resources and terrain.** A stick of dynamite can kill an enemy, remove cover, expose supplies or open a secret passage. Spending it on one purpose changes the player's remaining options. Items can alter those decisions, and each floor can present different opportunities.

DeathWard already has interacting items, shops, currency, keys, dynamite and multi-floor expeditions. The principal gaps are a small item pool, limited optional-room functions, no bomb destruction of scenery, and canyon encounters that lack explicit progression across floors and dedicated bosses.

This study covers the locally installed Isaac data, targeted native-code reconstruction, and a proposed implementation sequence. **It does not change gameplay.** The current implementation has **4–8 seeded floors with 15 rooms per floor**; The Lost Survey has one floor with five rooms. The opening-floor follow-up below proposes a smaller initial floor for a future trial. Story rooms remain part of the expedition structure.

## What was actually recovered

The examined installation is `C:\Program Files (x86)\Steam\steamapps\common\The Binding of Isaac Rebirth`. It includes Repentance. Its changelog starts with **v1.7.9b, December 7, 2022**; the executable's PE timestamp is December 8, 2022. These identify the local evidence; current wiki pages can also describe later Repentance+ changes.

| Evidence | Result | What it establishes |
| --- | --- | --- |
| Installed files | 22 packed `.a` archives, a native 32-bit `isaac-ng.exe`, Lua API support, shipped editors and extractor | The game is not implemented entirely in readable Lua or XML |
| Selected DLC archive contents | 181 XML and STB files extracted; every advertised length and archive checksum matched | The analyzed data was decoded correctly |
| Latest relevant data | `resources-dlc3` definitions from `repentance.a` | Item, pool, stage, entity and room configuration for this installation |
| Room binary decoding | All 53 extracted STB1 files parsed to their exact end | Stored room metadata, doors and spawn records are readable |
| Native analysis | Three bomb/destruction interfaces located; one small function reconstructed completely | Concrete evidence of object-specific destruction dispatch |
| Gameplay behavior | Selected mechanics cross-checked against API documentation and game references | Explanations of effects that XML alone does not contain |

The shipped resource extractor exited with code 116 while opening the Repentance archive. Its cause was not established. A separate read-only decoder, informed by [Gibbed.Rebirth's archive implementation](https://github.com/gibbed/Gibbed.Rebirth) and its [chunk decoding source](https://raw.githubusercontent.com/gibbed/Gibbed.Rebirth/main/projects/Gibbed.Rebirth.Unpack/ArchiveCompression.cs), recovered the selected data instead. The STB parser follows the documented field layout in [Basement Renovator's room converter](https://github.com/Basement-Renovator/Basement-Renovator/blob/main/src/roomconvert.py).

The installed executable and the ten other fingerprinted source files retain their original SHA-256 hashes. The 181 extracted files and 12 supporting files are preserved in `reference/isaac-repentance-1.7.9b/` inside this checkout. Every preserved payload file was verified against its source SHA-256. This local reference directory is excluded from Git and game builds; the report, aggregate measurements, provenance and analysis tools remain versionable. Reading the report does not depend on the temporary extraction directory or a running Steam installation.

**Scope of decompilation:** targeted x86 disassembly and manual pseudocode reconstruction, not recovery of the complete C++ source. Complete item interaction logic, boss state machines, generation algorithms and loot probabilities were not reconstructed or validated by running Isaac.

### Verified counts and their meaning

| Local data | Count | Interpretation |
| --- | ---: | --- |
| Passive collectible definitions | 425 | Metadata rows, including any hidden or special entries |
| Active collectible definitions | 170 | Charge and presentation metadata; behavior remains code-driven |
| Familiar collectible definitions | 126 | Collectible definitions, not all familiar entity variants |
| Collectible definitions total | **721** | 721 distinct IDs across those three categories |
| Trinket definitions | 188 | Separate category |
| Null definitions | 49 | Do not count these as obtainable collectibles |
| Named item pools | **31** | Different selection contexts, with overlapping membership |
| Stage definitions | 30 | Includes special and mode-related entries; not floors in one run |
| Named boss pools | 25 | 19 nonempty; six empty entries do not mean those stages have no bosses |
| Entity definitions | 1,337 | Includes enemies, variants, pickups and effects; not 1,337 enemy species |
| Stored room entries | **28,464** | 23,859 in 29 non-Greed files; 4,605 in 24 Greed files |

Room entries can repeat or vary across files and can include special, unused or conditional content. For example, `34.mortis.stb` contains one entry, but Mortis is absent from the parsed stage definitions. These counts describe stored data, not unlocked content or runtime encounter frequencies. Exact per-file results are in [the aggregate JSON](research/isaac-local-data-summary.json).

## Build changing items and deliberate interactions

### What Isaac separates

The local `items.xml` holds names, graphics, pickup grants, charges, unlock references and stat-cache flags. `items_metadata.xml` adds quality and tags. `itempools.xml` controls selection contexts using `Weight`, `DecreaseBy` and `RemoveOn`. None of these is a complete script for firing a Brimstone beam or combining two weapons. The [item configuration documentation](https://wofsauge.github.io/IsaacDocs/rep/xml/items.html) explains the metadata fields; the [item-pool API](https://wofsauge.github.io/IsaacDocs/rep/ItemPool.html) exposes selection and removal operations.

For example, the local entries for The Inner Eye and Mutant Spider invalidate damage and fire delay; Brimstone, Dr. Fetus and Tech X invalidate all caches; C Section explicitly includes the weapon cache. These flags identify affected systems, not the complete resulting behavior.

The important distinction is between **an attack modifier** and **an attack replacement**. Homing, piercing, splitting and status effects can modify attacks. A beam, charged shot or bomb launcher changes how the player attacks. Combinations need explicit rules: Repentance's Dr. Fetus can produce homing bombs, its combination with The Parasite produces additional bombs, and it overrides some other attack forms. Therefore, “all effects always stack” is not an accurate description of Isaac. [Dr. Fetus mechanics and interactions](https://bindingofisaacrebirth.wiki.gg/wiki/Dr._Fetus).

Distinct pools also give destinations meaning. In this installation, treasure has 407 entries, shop 95, boss 59, devil 94, angel 66 and secret 62. These are pool memberships, not guaranteed availability or drop percentages. A room can be worth seeking because of the *kind* of build change it offers.

### DeathWard already has a useful interaction core

[Items.cpp](../src/items/Items.cpp) defines five stackable items:

| Item | Existing behavior | Design value |
| --- | --- | --- |
| Ricochet Coin | Adds three wall bounces per copy | Positioning and bank shots |
| Split Lead | Hits emit two angled shots at 80% damage; fragments can split again | Branching attacks and crowd clearing |
| Judas Bullet | Every sixth shot gains piercing; each copy costs maximum health | Cadence and a permanent risk/reward decision |
| Powder of Jericho | Kills create explosions; those kills can trigger more explosions | Chain reactions |
| Hangman's Coin | Repeats a killing shot as a ghost shot carrying projectile effects | Builds that grow through kills |

The existing event queue already has chain identity, depth limits, event budgets and projectile limits. Preserve those protections as the system expands. The gap is largely in **attack forms, trajectory choices, statuses, defensive decisions and resource manipulation**, rather than a complete absence of synergies.

### Proposed first expansion

These are DeathWard designs, not effects recovered from Isaac. Start with the first six new items, bringing the pool to eleven; add the remaining four after interaction testing. Exact damage multipliers and timings require playtesting.

| New item | Changes the build | Trade-off | Deliberate interaction |
| --- | --- | --- | --- |
| Scatter Cylinder | Replaces each shot with a short fan of pellets | Lower damage per pellet and shorter range | Split Lead generates smaller fragments; total output stays within chain limits |
| Rail Spike | Slower, heavier projectile that pierces bodies | Slower firing cadence and turn commitment | Ricochet preserves body piercing after a bank shot; Judas adds pierce rather than another damage multiplier |
| Lodestone Sight | Shots curve toward nearby visible enemies | Limited turn rate and lower projectile speed | Split fragments acquire their own targets; a ricochet can redirect toward another target |
| Return Spring | Bullets travel out and return | Short outward reach | A target may be hit once outward and once returning; wall bounces only affect the outward phase |
| Blasting Cap | Adds a small blast to a direct bullet hit | Lower direct damage; a visible self-damage risk | One blast per projectile lifetime, including each Split fragment; area damage cannot recursively trigger the same hit effect |
| Fuse Braid | Placed dynamite leaves two weaker secondary charges | Smaller main blast and a more dangerous area to escape | Secondary charges inherit bomb modifiers but cannot produce further secondary charges |
| Oilskin Rounds | Applies a brief, capped slowing/oil effect | Lower immediate damage | A blast ignites oil once, consuming that application rather than repeatedly retriggering it |
| Prospector's Lens | Makes marked seams and breakable cache entrances easier to identify | An exploration reward in place of direct combat power | Explosive builds become more resource-efficient through better decisions, not free unlimited bomb refunds |
| Blast Apron | Reduces damage from the player's explosions | Slightly slower dodge recovery | Supports close-range Blasting Cap play without making all hazards harmless |
| Surveyor's Chalk | Marks an enemy on the sixth primary shot | Benefit depends on maintaining the firing cadence | The next qualifying hit on the mark splits once; ghost shots and fragments do not advance the primary-shot counter |

Three build examples worth supporting deliberately:

- **Bank-shot hunter:** Ricochet + Rail Spike + Lodestone. Fight around cover and line up multiple targets.
- **Shrapnel gambler:** Scatter Cylinder + Split Lead + Blasting Cap. Strong close-range coverage with self-damage and visual-density risks.
- **Demolition prospector:** Fuse Braid + Blast Apron + Prospector's Lens. Spend explosives on terrain and resource access as well as damage.

No reload system is needed. Mouse and arrow-key firing should produce the same attack definitions. Preserve the removal of automatic healing on enemy kills; no proposed item depends on reintroducing it.

### Define compatibility before adding more effects

Use an explicit sequence: **choose attack form → apply stats and cadence → create projectiles → apply trajectory and collision modifiers → resolve hits → resolve kills and secondary effects**.

Keep independent properties for body piercing, wall bouncing, obstacle passing, homing and terrain damage. Passing through an enemy must not imply passing through a cliff. Visual occlusion transparency must not change these physical rules.

| Combination | Proposed rule |
| --- | --- |
| Scatter + Rail Spike | A smaller fan of weaker spikes; explicit hybrid rather than acquisition-order dependence |
| Ricochet + Return Spring | Bounce during outbound travel; switch to return behavior once; no reset of lifetime |
| Split + homing | Fragments inherit homing, remaining lifetime and the originating chain budget |
| Split + explosive hits | Each fragment can explode once; blast damage does not count as another projectile impact |
| Ghost + explosive kills | Retain the original shot specification; an area-damage event must not silently become an arbitrarily stronger bullet |
| Sixth-shot effects + fragments | Count player-triggered primary shots only |
| Bomb destruction + kill effects | Destroying a crate is an object event, not an enemy kill |

Store attack provenance, generation and already-hit targets. Test pairs in both acquisition orders, duplicates, boss targets and room exits. In particular, define how Hangman's Coin uses explosion damage before adding many more explosive sources: its current implementation takes the larger of player shot damage and killing-event damage.

Add separate reward pools for armory caches, shops, bosses and risky bargains. Start with broad overlap and different weights. Do not attempt thirty-one pools with eleven items. A later active-tool slot could recharge on first clears of hostile rooms; empty rooms, revisits and cheats must not farm charges. That is a separate feature, not a prerequisite for the first expansion.

## Floor identities and progression

### Isaac combines room libraries with selection rules

Each decoded STB1 room carries a type, variant, subtype, difficulty, selection weight, dimensions, shape, doors and positioned spawn records. Random generation chooses and connects authored content; it does not simply scatter arbitrary monsters into arbitrary rectangles.

| Local room file | Stored entries | Default-room entries | Rooms containing ordinary-rock spawn type 1000 | Rooms containing pit spawn type 3000 |
| --- | ---: | ---: | ---: | ---: |
| Basement | 1,181 | 1,162 | 905 | 1 |
| Caves | 1,111 | 1,092 | 375 | 825 |
| Mines | 930 | 838 | 620 | 421 |

These are **unweighted counts across all entries in each file**, not probabilities of seeing rocks or pits during play. They nevertheless show different authored terrain vocabularies. Basement's default rooms also have several difficulty values, including 0, 1, 2, 5, 10, 15 and 20; stored entries are not all eligible on every visit.

The documented normal-mode selection distinguishes the first and second floors of a chapter: difficulty 1–5 versus 5–10. Hard mode uses different ranges. That selection rule is externally documented; this analysis decoded the values but did not reconstruct the native selector. [Level generation](https://bindingofisaacrebirth.wiki.gg/wiki/Level_Generation).

Stage metadata connects room libraries with music, backdrop and presentation. Boss pools are separately weighted: Basement has eleven entries, Cellar eight, Mines four and Ashpit five. Local entity definitions also contain `baseHP`, `stageHP`, collision and boss flags. Those fields supply parameters; attack patterns and phase behavior require code.

### The specific DeathWard progression gap

[Encounters.cpp](../src/combat/Encounters.cpp) selects natural canyon monsters using `monster.depth <= max(1, room.depth)`. That is distance into the **current floor's graph**, not expedition floor number. The normal enemy-count rule is `ceil(usableArea / 70)`, clamped to 4–24. The seed changes each floor, but this does not create a designed escalation across the expedition.

The canyon's final room uses that ordinary-group route. The mine has the Hollow Sheriff; the canyon needs its own boss selection and encounter behavior. [Expedition.cpp](../src/world/Expedition.cpp) already provides the floor count, seeds and story schedule, while [Simulation.cpp](../src/combat/Simulation.cpp) carries the build, health and resources between floors.

### Proposed four stages of an expedition

Use four progression bands across the existing 4–8 floors. A starting mapping is `band = min(3, floorIndex * 4 / floorCount)`: a four-floor run visits each band once; an eight-floor run spends two floors in each. Alternate terrain profiles within a band and vary encounters on repeated visits.

| Band | Identity | Encounter grammar | Terrain and resources |
| --- | --- | --- | --- |
| 1 | Outer Washes | Slow pursuit plus one clearly readable ranged role | Open dirt, scattered low cover, simple breakables, generous escape lanes |
| 2 | Broken Quarry | Charges and ranged pressure arrive from complementary directions | Fragile stone, ore seams, occasional river/ford layouts where compatible |
| 3 | Abandoned Works | Delayed explosives and enemies that punish stationary play | Timber barriers, powder stores, rail debris and winding routes |
| 4 | Storm Cut | Familiar roles combined under tighter timing and positioning demands | Selective moving dust, eroded cover and a dedicated final arena; combat cues remain visible |

A floor profile should define room-pattern weights, eligible enemy roles, difficulty bands, breakable mix, optional-room weights, boss pool and art/audio dressing. Roads, interior rivers and boundary rivers remain seeded alternatives where the geometry permits them. Do not force every feature into every room.

Use room area as a capacity limit, then spend a **threat budget** on role combinations. A large room should not automatically become twenty simultaneous specialists. Increase combinations and timing pressure before heavily increasing HP. Keep telegraph readability, a safe entrance and at least one viable dodge route as constraints.

Start with reusable encounter patterns—pursuers around a central barrier, ranged crossfire with staggered attacks, a charge lane, a guarded supply pocket—adapted to the generated geometry. Validate them against actual walkable area and cover. Fall back to a simpler pattern if a river, slope or road prevents a fair placement. This adopts authored encounter intent without discarding DeathWard's generated terrain.

### Proper canyon bosses

The following are original proposed encounters, not decompiled Isaac bosses. Begin with one complete boss, then expand the pool.

| Boss concept | Recognizable fight | Counterplay and phase change | Arena requirements |
| --- | --- | --- | --- |
| Ridgeback | A heavy burrower surfaces, aims a charge, then commits | Dodge the indicated lane; a collision with fragile cover creates a recovery window; later charges chain twice | Broad continuous loop, low breakable cover, no unavoidable river choke |
| Powder Foreman | Throws clearly marked charges and fires in deliberate bursts | Move charges by contact kicks; use powder barrels tactically; later phase shortens the interval between distinct attacks | Space to retreat, visible fuses, barrels outside entrance landing |
| Gallows Warden | Sweeps chains across marked sectors and pulls toward an anchor | Move into the open sector; optional dynamite destroys an anchor to cancel one pull | Open sectors sized for dodge distance; every attack also avoidable without dynamite |
| Storm Marshal | Alternates aimed volleys with sweeping lanes | Read the windup, move through the deliberate gap, punish recovery; later phase combines learned patterns | Stable arena boundary, clear projectile contrast, dust kept below combat-obscuring density |

Every boss needs a complete windup/attack/recovery state machine, phase transitions, death cleanup, resource reward and exit integration. Budget duration against a weak but viable build. Dynamite should offer an advantage, never be the only way to defeat the boss. Separate boss identity from the mine-specific Sheriff flag.

Eventually give each band more than one boss option and avoid immediate repeats. Four bosses alone will repeat in an eight-floor run; arena variants and an explicitly limited remix can bridge development, but should not be presented as a large boss roster.

### Story integration

Preserve Survey Camp, Split Rock, Railway Cutting and Dry Creek at their scheduled floors. A story location can overlay an ordinary room and become examinable after its single encounter clears. Preserve the current evidence gate at the floor exit.

Witness testimony can influence dressing, encounter patterns and optional evidence placement. The account label remains visible, and recovered observations remain separate from claims. **Cole's modest reconstruction remains Cole's account**, not a truth mode. Bosses and gameplay danger must not silently establish which witness committed the murder.

## Opening floor size follow up

**A smaller opening floor is worth testing, and corridor length is also a substantial contributor.** DeathWard currently repeats the same room-count target from the first standard floor to the last. The data below measures the current implementation; the proposed smaller counts have not been implemented.

### How many rooms Isaac generates per floor

Isaac has no single fixed count. The published ordinary-floor base budget is approximately `min(20, 3.33 × floorDepth + random(5, 6))`; Hard mode adds 2–3 rooms, and Curse of the Lost adds four. XL and The Void use different budgets. [Level generation reference](https://bindingofisaacrebirth.wiki.gg/wiki/Floor_generation).

| Normal main-path floor | Approximate base generation budget |
| --- | ---: |
| Basement I | 8–9 |
| Basement II | Around 12 |
| Caves I | Around 15 |
| Caves II | Around 18–19 |
| Depths I and later ordinary floors | Around 20 before modifiers |

These are reference-budget estimates, **not measured final room totals from the installed executable**. Special-room placement and multi-cell rooms complicate final counts: some special rooms replace generated endpoints, and the total can also include additional destinations. A room occupying four minimap cells is still one encounter room. The 28,464 stored room entries measured earlier are the available layout library, not rooms in one floor.

An often-cited older formula, `5 + random(2) + level × 2.6`, comes from the original Flash game's algorithm. Its author explicitly separates that analysis from Rebirth's changes; it should not be substituted for a verified Repentance count. [Original algorithm study and developer interviews](https://www.boristhebrave.com/2020/09/12/dungeon-generation-in-binding-of-isaac/).

An exact local count distribution would require running the installed version over fixed seeds and recording unique room descriptors per stage, difficulty, curse and special-room category. The extracted STB libraries do not provide that distribution. This follow-up therefore does not claim that DeathWard has exactly twice as many rooms as Isaac's first floor.

### What makes DeathWard large now

The generator sets room bounds to **24–40 metres on each axis**, with neighbouring graph-cell centres spaced **48–64 metres** apart. The start room uses the same size selection as other rooms. The tutorial changes the graph to five rooms, but still uses this physical sizing. See [Dungeon.cpp](../src/world/Dungeon.cpp) and [Dungeon.hpp](../src/world/Dungeon.hpp).

A headless sample generated ten ordinary canyon layouts, with rivers enabled and no story overlay: seeds 0–7, 42 and 1866. The core library was rebuilt before running the measurement. Raw results are in [deathward-floor-size-sample.csv](research/deathward-floor-size-sample.csv).

| Current DeathWard measurement | Ten-seed result |
| --- | --- |
| Total rooms per standard floor | 15 in every sample |
| Ordinary combat rooms | 9–11, plus one boss-designated room |
| Mean room bounding dimensions | Approximately 31.5 × 32.1 metres |
| Mean usable room area | Approximately 597 square metres, after the generator's area calculation |
| Mean corridor length | Approximately 23.4 metres, averaging each sampled floor's mean |
| Individual corridor lengths | 10–40 metres |
| Layout bounding extent | Width 156–320 metres; depth 198–328 metres; this includes empty space between rooms |
| Shortest graph route from entrance to boss | 3–8 passage transitions, ignoring locks and required evidence |
| Configured whole-floor enemy budget | 87–116 from the current area rule; not a count of successful spawns or combat time |

Ordinary unslowed movement is six world metres per second. A 23.4-metre corridor alone therefore costs roughly **3.9 seconds of straight walking**, before crossing the rooms at either end, detours, fights or backtracking. Dodging can shorten that; terrain and resource collection can lengthen it. This calculation is not a measured playthrough time. See [Simulation.cpp](../src/combat/Simulation.cpp).

The concern is consequently broader than “15 is too many.” The player begins with a weak, limited build, encounters roughly ten ordinary combat rooms, and repeatedly crosses substantial distances. Reducing only the map's bounding box would not guarantee a shorter required route; reducing only room dimensions would leave the corridors.

### Proposed compact opening trial

Start a standard expedition with **8–10 total rooms, targeting nine**, then grow toward **13–15** on later floors. These totals include entry, rewards, shop and boss. Example schedules are `9 → 11 → 13 → 15` for four floors and `9 → 10 → 11 → 12 → 13 → 14 → 15 → 15` for eight. Seeded variation can follow once the basic pacing is measured. Keep The Lost Survey at five rooms.

| Role in a nine-room first floor | Rooms |
| --- | ---: |
| Quiet arrival | 1 |
| Ordinary combat | 3 |
| Combat room containing the scheduled story location | 1 |
| Item reward | 1 |
| Shop | 1 |
| Optional resource or discovery room | 1 |
| Boss | 1 |
| **Total** | **9** |

If no story location is scheduled, its slot becomes an ordinary encounter or exploration room. The story location is counted once. Keep at least two initial choices, a meaningful optional branch and safe access to necessary keys/evidence. Aim to offer the first build-changing item after one or two fights, with a clearly navigable path to the boss after roughly three or four required encounters. These are playtest targets, not promises about the current generator.

For a separate physical-size trial, use **20–28-metre ordinary early rooms** and **8–16-metre corridors**; let boss arenas remain larger where their attacks need room. Measure room count and corridor changes separately before combining them. The tutorial may benefit from shorter corridors without losing any of its five story steps.

This is not a one-line change to `RoomCount`: [RoomGraph.cpp](../src/world/RoomGraph.cpp) and [Dungeon.cpp](../src/world/Dungeon.cpp) use fixed-size arrays and fixed end indices for special rooms. A proper implementation needs a per-floor room budget, dynamic indexing and revised room-role allocation. Preserve the minimum room count needed for the tutorial and mandatory story placements. Smaller room dimensions also require checking the current unique-size rule, since fewer available size pairs can exhaust its retry loop.

Acceptance should record time to first item, first-boss arrival, total clear time, walking/backtracking time and number of required versus optional encounters across fixed seeds. The preferred opening is the one that gets a build and a boss into play sooner while retaining useful choices—not simply the smallest graph.

## Optional rooms and resource trade offs

### The Isaac lesson is opportunity cost

Isaac's room types change what resources can buy. Shops trade coins for supplies or items and generally require a key after the first floor. Secret rooms generally consume a bomb to open a suitable wall and draw from their own item context. Curse rooms charge health through their entrances; sacrifice rooms trade health for outcomes; challenge rooms make taking a reward a combat commitment. [Shops](https://bindingofisaacrebirth.wiki.gg/wiki/Shop), [secret rooms](https://bindingofisaacrebirth.wiki.gg/wiki/Secret_Room), [other room types](https://bindingofisaacrebirth.wiki.gg/wiki/Rooms).

The important transferable idea is that a key, health point or explosive has competing uses. Isaac's exact prices, drop odds and heart-based damage should not be copied directly into DeathWard's numeric-HP economy.

### Current DeathWard economy

[Shop.cpp](../src/combat/Shop.cpp) already offers medicine restoring up to 40 HP for 10 coins, two powers at 25 coins each, and three dynamite sticks for 15 coins. Offers sell once per floor. Shop powers currently come from the same five-item collection.

[Dungeon.cpp](../src/world/Dungeon.cpp) puts `powerRooms + 1` keys in the unlocked network, supporting power rooms and the boss lock. This protects access, but leaves little deliberate uncertainty over what a key should buy. Existing room kinds are Combat, Power, Boss, Empty and Shop.

Money is also **campaign-persistent**, not simply lost at the end of each expedition: [Campaign.cpp](../src/world/Campaign.cpp) applies collected money minus spending when resolving the run, including defeat. That is a major balance difference. An unlimited repeatable exchange could become permanent wealth farming, and a wealthy campaign can make a 25-coin purchase trivial. Keep current persistence unless changed explicitly; assess prices against actual wallets and cap conversions per floor.

### Proposed room functions

| Room | Decision | Possible payoff | Constraints |
| --- | --- | --- | --- |
| Collapsed Supply Cache | Spend dynamite on the entrance or save it for combat | Supplies or an exploration-oriented item | Telegraph the seam; never contain mandatory evidence |
| Locked Armory | Spend a key here or on another optional lock | Choose one of two weapon modifiers | Contents become mutually exclusive after choosing |
| Prospector Exchange | Trade two keys for dynamite, or dynamite for coins | Convert a surplus into what the build needs | One transaction per offer; no reversible profit loop |
| Field Surgeon | Buy healing now or retain money for a power | Health or a clearly priced maximum-HP bargain | No concealed cost; cannot kill the player through the menu |
| Smuggler's Bargain | Permanently sacrifice some expedition maximum HP | A strong, unusual modifier | Preview the exact cost and resulting maximum HP |
| Guarded Pay Chest | Accept a tougher fight for a visible reward | Better-quality equipment or resources | One pre-placed group, visibly present before activation; no return to repeated waves |
| Survey Shelter | Take supplies or acquire route information | Resource recovery or a hint about optional rooms | Critical story facts remain obtainable through the story route |
| Abandoned Workshop | Replace one owned modifier or keep the existing build | A controlled build pivot | Show the replacement first; one use, no infinite rerolls |

Use a small seeded subset per floor. An example **15-room budget for a larger later floor** is one quiet entry, one boss, two power rooms, one shop, three optional-function rooms and seven combat rooms. If there is one power room, allocate the spare slot to combat. The compact opening proposal above uses nine slots instead. Story content overlays a suitable slot rather than adding another room. Optional functions must not consume every quiet moment or force a fixed checklist onto every floor.

Adding new key sinks requires an explicit reachability policy. A simple eventual design is to keep ordinary keys for optional rewards and make the boss approach accessible through combat progression. If retaining the current boss key lock, reserve its access through a separate guaranteed route key or validate resource reachability after every optional spend. Merely placing enough keys at generation time is insufficient once the player can exchange them away.

Likewise, mandatory evidence and the floor exit cannot require the last dynamite stick. Generate optional secret connections into already valid geometry and exclude sealed boundaries, deep water and story-critical passages. Cache loot when the floor is created or on its first valid reveal, so revisiting or reloading cannot reroll it.

## Bomb destructible objects

### What the local data and native code show

Isaac's room editor uses distinct spawn types for rocks (`1000`), bomb rocks (`1001`), alternate rocks (`1002`), TNT (`1300`) and invincible rocks (`1900`). Runtime `GridEntityType` values are a different namespace: ordinary rock is `2`, bomb rock is `5`, and TNT is `12`. Confusing these namespaces would produce incorrect conversions.

The API exposes destruction, damage, door blowing and unlocking as distinct operations. The installed binary's Lua registration references identify these native entry points at the executable's preferred image base:

| Operation | Preferred virtual address | Analysis extent |
| --- | --- | --- |
| `Room::DestroyGrid` | `0x007cf710` | Complete short control flow reconstructed |
| `GridEntityDoor::TryBlowOpen` | `0x006e02b0` | Entry located; conditional logic inspected, not fully reconstructed |
| `Game::BombExplosionEffects` | `0x006d26e0` | Entry located; partial disassembly inspected |

The following is explanatory pseudocode, not recovered original source. Field names are inferred. The third boolean is a native argument whose public meaning was not established; the inspected API documentation exposes a two-argument `DestroyGrid` method.

```text
destroy_grid(room, index, immediate, native_flag):
    if unsigned(index) > 447:
        return false
    grid = room.grid_entries[index]
    if grid is null:
        return false
    if native_flag and grid.type == 5:
        grid.type = 2
    return grid.virtual_slot_5(immediate)
```

The concrete observation is **virtual dispatch to the grid object's implementation**, with a specific type conversion on one path. It does not prove every rock's drop table or every blast's occlusion rules. The documented [Room API](https://wofsauge.github.io/IsaacDocs/rep/Room.html) independently distinguishes grid destruction from other room operations.

In documented gameplay, ordinary rocks can be destroyed by explosions; marked rocks offer resource rewards; bomb rocks explode when broken; some floor-specific obstacles can release hazards as well as loot. Destroying a correctly positioned rock can also fill a small gap. The last behavior is a useful later inspiration but would require actual traversable geometry in DeathWard. [Rock and obstacle mechanics](https://bindingofisaacrebirth.wiki.gg/wiki/Rocks).

### DeathWard has explosives but no object destruction pipeline

Dynamite starts at three sticks with a cap of nine, uses a two-second fuse and a 4.5-metre blast radius, deals 100 enemy damage and 25 self-damage, and can be kicked by contact. See [Types.hpp](../src/core/Types.hpp), [Dynamite.cpp](../src/combat/Dynamite.cpp) and [Enemies.cpp](../src/combat/Enemies.cpp).

The explosion handler in [Simulation.cpp](../src/combat/Simulation.cpp) emits effects and enemy damage with line-of-sight checks. It does not destroy props, remove their collision or change room connections. Self-damage for player dynamite is handled separately in the hazard update, so a new blast resolver must preserve and unify these rules deliberately.

### Proposed objects and their purposes

| Object | What breaks it | Result | Why the player cares |
| --- | --- | --- | --- |
| Small cracked boulder | One dynamite blast | Removes local cover and collision; mostly rubble | Changes movement and firing lanes |
| Marked ore seam | One blast | Small seeded supply reward | A readable alternative use for dynamite |
| Supply crate or pottery | Gunfire or blast | Small chance of ordinary supplies | Immediate feedback and minor scavenging; not a mandatory bomb tax |
| Powder barrel | Enough bullet damage or a blast | Telegraph, then secondary explosion | A combat opportunity with risk |
| Timber barricade | Blast | Opens an optional connection | Converts explosives into access |
| Reinforced cache wall | Two blasts, with a visibly damaged intermediate state | Higher-value optional cache | A larger investment rather than a disguised ordinary wall |
| Brittle mineral pocket | Blast | Supply chance plus a short, clearly marked hazardous release | Environment-specific risk/reward |
| Loose rubble above a narrow gap | Later feature, explicitly authored placement | Forms a walkable crossing | Changes traversal; requires geometry and path validation |

Keep canyon boundary cliffs, large terrain mesas, deep river borders, mandatory gates and story objects outside this system initially. Give breakable rocks a consistent crack pattern and scale. Do not rely only on color, and ensure the distinction remains visible when an object becomes transparent to reveal the player.

### Implementation boundaries that matter

**Separate breakable props from the canyon height field.** [CanyonTerrain.hpp](../src/world/CanyonTerrain.hpp) uses one triangulated height field for both visible rock and collision. Hiding a rock mesh while retaining its height field creates an invisible wall; removing collision alone can let the player enter a visually solid cliff. Small independent props avoid either problem and are a much safer first implementation.

A breakable needs a stable object ID, definition, position, collision shape, health/state, loot seed and an exactly-once destruction transition. Keep its state in the floor/room runtime data, not solely in a renderer's cached placement list. Visit persistence is needed immediately; save/reload persistence must follow the game's supported resume semantics rather than being assumed to exist already.

Resolve one blast as a transaction:

1. Collect potentially hit enemies, player and props using the pre-blast collision state.
2. Test prop surfaces as valid targets; the target's own collider must not incorrectly block the ray to its centre.
3. Compute hits against that snapshot. The same blast should not hit enemies through cover merely because that cover happened to be processed first.
4. Apply damage, transition destroyed props once, remove or alter collision, and refresh affected navigation, shadows and cached render data.
5. Spawn deterministic loot on reachable ground and queue secondary explosions through the existing bounded event system. A later secondary blast sees the changed geometry.

Preserve existing cover protection unless a particular effect explicitly penetrates it. Smoke and debris should be brief and should not obscure hostile telegraphs. Mark decorative debris nonblocking unless it has a deliberate gameplay role.

Derive loot from expedition seed, floor index and stable object ID, using an independent random stream. Destruction order, camera movement and cosmetic particle randomness must not change other loot. Destroying a barrel twice or receiving two blasts in one tick must never award twice.

Assign terrain permissions per explosion source. Ordinary spent dynamite can break hard cover and cache entrances. Powder of Jericho or unlimited projectile blasts can damage ordinary combat props, but allowing them to open every resource gate would erase the dynamite decision. If an item intentionally grants free demolition, make that a rare, clearly advertised build change and balance the reward pools around it.

## Suggested implementation order

This sequence incorporates the opening-floor follow-up. Implement and measure room-count changes before combining them with physical-size changes. Keep the current 15-room layout available as a comparison preset during the trial.

| Milestone | Deliverable | Acceptance evidence |
| --- | --- | --- |
| 1 | Configurable per-floor room counts, targeting a nine-room opening and growing toward 15 | Every 4–8-floor schedule generates valid branches and reachable objectives; the five-room tutorial remains valid; story slots and special-room indices use the actual room count |
| 2 | Separate trials of shorter early corridors and smaller ordinary rooms | Compare fixed-seed time to first item, boss arrival, walking and backtracking; validate terrain, entrances, spawn spacing and boss arena dimensions before choosing defaults |
| 3 | Cracked boulders, marked seams and powder barrels; one optional supply cache | Visual/collision agreement; deterministic single payout; revisits retain state; no blast damage through cover due to iteration order |
| 4 | First six proposed items plus explicit interaction rules | Pairwise checks in both acquisition orders; bounded Split/Powder/Ghost chains; readable mouse and arrow firing |
| 5 | Four progression bands and the first complete canyon boss | Floor number affects encounter selection; boss is beatable without dynamite; exit/evidence gates remain correct |
| 6 | Two more bosses, three optional-room functions and distinct reward pools | All 4–8 floor plans remain reachable; keys and dynamite offer competing uses; no currency conversion loop |

A focused first destruction playtest could use **two cracked boulders, one marked seam, one powder barrel and one cache entrance in a single room**, with the existing three starting dynamite sticks. The question is whether the player makes a meaningful choice about explosives. This tests the connection between terrain and resources before creating dozens of decorative breakables.

Keep the original visual style. Geometry readability, distinct object states and clear boss telegraphs matter more here than adding another rendering preset.

## Evidence and reproduction

The measurements are in [isaac-local-data-summary.json](research/isaac-local-data-summary.json); installation fingerprints, extraction scope and native-analysis addresses are in [isaac-analysis-provenance.json](research/isaac-analysis-provenance.json). The [reference guide](../reference/README.md) documents the preserved archive layers, supporting files and integrity check. The complete payload is 37,812,076 bytes across 193 files, plus its inventory.

From the repository root, run the standard-library analyzer against the preserved `resources-dlc3` directory:

```sh
python3 scripts/analyze-isaac-data.py \
  --resources reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3 \
  --output /tmp/isaac-local-data-summary.json
```

[The analyzer](../scripts/analyze-isaac-data.py) reads inputs without modifying them, parses every STB record, checks exact file consumption and records SHA-256 hashes. It emits aggregate counts rather than complete room layouts. It is not the archive extractor. The preserved input directory survives normal WSL restarts and `/tmp` cleanup; it must be copied separately when moving to another checkout because Git excludes it.

The Markdown report is the editable source. Regenerate the standalone HTML edition with `python3 scripts/report-isaac-study.py`; generation requires the `markdown-it-py` Python package. The generated HTML has its styling and contents embedded and needs no server or network connection to read. Citations and links to supporting files remain links.

To repeat the DeathWard layout measurements against the current Linux build:

```sh
cmake --build build --target deathward_core --parallel 4
c++ -std=c++20 -O2 -Isrc -Ibuild/_deps/raylib-src/src \
  scripts/measure-expedition-layout.cpp build/libdeathward_core.a \
  -o /tmp/deathward-measure-expedition-layout
/tmp/deathward-measure-expedition-layout > /tmp/deathward-floor-size-sample.csv
```

These commands use the repository's default CMake build and fetched-raylib include paths. The [measurement source](../scripts/measure-expedition-layout.cpp) records its fixed seeds and measures topology without changing saves, maps or game configuration. The recorded CSV corresponds to baseline `955ef8f`; later gameplay changes can legitimately change the results.

One input exception is explicit: the installed `bosspools.xml` has a mismatched final root closing tag. The analyzer repairs that closing tag **in memory only**, records the normalization, and hashes the original bytes. All 53 room binaries parse fully. Other extracted XML outside the study can also be nonstandard; this report does not claim all 181 files are strict XML documents.

The older [enemy and character review](isaac_review.md) is historical: its statements that coins and player bombs are missing are superseded by the current implementation examined here. Neither catalog coverage nor this data study establishes exact Isaac enemy-behavior parity.
