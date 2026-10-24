# Canyon floor progression and bosses

Milestone 5 of the [expedition study](isaac_expedition_study.md) adds four canyon bands and Ridgeback. Standard expeditions still have 4–8 floors, growing from 9 to 15 rooms. The Lost Survey remains its original five-room tutorial. The Classic preset retains its original geometry and final monster groups. Mine expeditions retain the Western roster and Hollow Sheriff. The changes below apply to modern canyon expeditions, including Rourke's account.

The separation between a floor profile, its encounters and its boss follows the preserved Isaac stage/boss-pool metadata described in the study. The four bands, threat values and Ridgeback behavior are original DeathWard designs, not decompiled Isaac boss logic.

The band is `min(3, floorIndex * 4 / floorCount)`. Four-floor runs visit each band once; eight-floor runs spend two floors in each. Repeated bands still have different floor seeds, layouts, encounter patterns, roads, rivers and placements. Floor identity does not depend on distance from the entrance within a floor.

| Band | Encounter emphasis | Scenery and resources |
| --- | --- | --- |
| Outer Washes | Slow basic enemies with at most one ranged specialist; pursuit patterns dominate | Fewer outcrops, open escape lanes, two cracked rocks, one seam and one barrel |
| Broken Quarry | Charge lanes and staggered crossfire, at most three specialists | More outcrops, four cracked rocks, two seams and one barrel |
| Abandoned Works | Guarded pockets with delayed lobs and explosive enemies; at most four specialists | Reused timber and rail remnants, two cracked rocks, two seams and three barrels |
| Storm Cut | A mix of familiar patterns, beams and shorter cooldowns; at most five specialists | Eroded low cover, three cracked rocks, one seam and two barrels; subtle existing moving dust |

Each floor can still have its optional reinforced supply cache. Counts above are placement targets; unsafe sites are omitted. Boss counterplay rocks are separate and have no loot. Dressing stays off roads, water, entrances, keys, evidence and mandatory routes. The cache approach is explicitly reserved from later props. Dust fades around the player and enemies and is omitted inside the boss arena. The Original palette, lighting and shaders remain unchanged. Existing exploration/combat music transitions continue; boss entry selects the existing boss score and attacks have warning/impact cues.

## Encounter rules

Area caps ordinary populations at `clamp(ceil(usableArea / 70), 4, 14)`. A separate threat budget is `clamp(ceil(usableArea / areaPerThreat) + band, 4, maxThreat)`. The four bands use area divisors 95/85/80/75 and maximum threat 9/14/18/22. Basic bodies cost one point, simple ranged roles two, chargers/lobs/crossfire three and late beams four. Specialist caps also apply. This avoids filling a large room with a large group of expensive attack roles.

The weighted patterns are pursuit around cover, staggered crossfire, a charge lane and a guarded pocket. Each tries positions relative to the room's entrance, center or objective, checks terrain and body spacing, and searches nearby safe positions. If the intended position does not fit, the normal safe-placement search supplies a simpler arrangement. Stationary pattern placements require a firing line toward the room center. Initial specialist cooldowns are staggered.

Base health and movement speed are unchanged. Ordinary enemy cooldown factors are 1.10/1.00/0.94/0.88, applied alongside the game's existing enemy tuning. Threat grows mainly through role combinations and timing, not inflated health. Residents remain visible and idle before entry; combat starts only when their room is entered. No waves were added.

## Ridgeback

Ridgeback is a distinct boss identity, separate from the Sheriff. Its original low-poly model is a broad, plated burrower. The arena retains a continuous outer dodge loop with no baked outcrops or river opening. Up to two low cracked rocks inside the loop provide optional counterplay. Story props remain outside the loop.

The cycle is:

1. Choose a clear landing at least six metres from the player and mark it for 0.75 seconds. Ridgeback is invulnerable while buried. If the player moves onto the landing marker, emergence waits until it is clear.
2. Surface for 0.70 seconds, then lock a charge lane for 1.15 seconds. The displayed lane does not track later player movement.
3. Charge at 15 metres/second, up to 16 metres. The attack stops at solid scenery or water and deals 20 player damage after the existing enemy damage multiplier. Ordinary dodge immunity still applies.
4. Recover for 1.35 seconds, or two seconds after colliding with cover. Normal bullets deal 125% damage during recovery. A charge can crush cracked rocks, but cannot open ore seams, caches or narrative routes.
5. Below half health, each cycle can contain two charges, each with its own 0.85-second warning. A collision cancels the remaining charge and creates the longer recovery window.

Health is 620/720/820/920 by band. Dynamite helps but is not required. Defeat removes the boss's attacks, opens normal combat seals, grants one dynamite stick up to inventory capacity, and places 6/8/10/12 coins on accessible arena ground. This payout happens once per floor, including debug replays. There is no healing on kill. An unseen scheduled story site still blocks departure; the boss does not resolve any testimony's truth.

Ridgeback is the only new canyon boss in milestone 5 and therefore repeats across floors. Milestone 6 adds two identities and a seeded selection policy; this is not presented as a finished large boss roster.

## Checking it

Run `./build/deathward_floor_progression_tests` for all run-length mappings, floor geometry/encounter checks, boss phases/cover/pause/rewards and live starting-revolver victories with no items, dynamite or invulnerability. Full validation results are recorded in [the progress log](expedition_implementation.md).

Native scripted views use `--smoke --theme canyon --style original --scene NAME` with the default Compact pacing (or another non-Classic preset):

- `ridgeback`: opening-floor arena, without firing, to watch tells and attacks.
- `ridgeback-late`: final-floor arena at phase two, without firing.
- `ridgeback-fight`: a moving automated player with the starting revolver and no dynamite or invulnerability.
- `profile-quarry`, `profile-works`, `profile-storm`: ordinary encounters in the later bands.

In the browser, use `?verify&mute&smoke&frames=100000&theme=canyon&scene=NAME`. The smoke save is isolated from normal campaign play. Automated victories establish feasibility and regression coverage; they do not replace human difficulty and readability playtests.
