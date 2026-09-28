# Isaac enemy and character review

Reviewed on 2026-09-28. This records the implemented behavior and its limits; catalog coverage does not establish behavior parity with Isaac.

## Mission rosters

New sessions offer **Isaac Canyon** by default. All natural canyon groups, the final Infested Mesa encounter, random testing spawns and their offspring use the Isaac catalog. **Western Mine** retains the original fifteen enemies, their AI and the Hollow Sheriff. Seeded Theme still chooses either setting reproducibly. The specific-ID cheat intentionally remains available in either theme.

The final canyon encounter is an area-budgeted monster group, not a newly implemented Isaac boss. Clearing it opens the exit and persists `canyon_cleared`; it does not mark the mine's Sheriff dead. Both settings retain the existing miners, altar, keys and power rooms.

The catalog now contains **128 entries**: 120 within type IDs 10–89 (including variants and detachable heads), plus eight supporting creatures. The added support entry is Swarm Spider, 884.0.

## Reference checks and corrections

| Enemy | Finding and change | Reference |
| --- | --- | --- |
| Tainted Sucker, 61.7 | Removed incorrect contact damage. Its six death projectiles now have a wall bounce before splitting into six smaller bullets each. The timed splitting remains an approximation. | [Sucker](https://bindingofisaacrebirth.fandom.com/wiki/Sucker) |
| Bulb, 61.5 | Removed the invented dodge-cooldown drain. Since DeathWard has no active-item charges, it now follows the reference's harmless wandering case, using right-angled turns. | [Sucker](https://bindingofisaacrebirth.fandom.com/wiki/Sucker) |
| Eggy, 29.2 | Replaced ordinary Spider offspring with a distinct small, hopping, flashing Swarm Spider entry. The configured group is five; exact spawning thresholds/counts and Eggy's lingering death animation remain unimplemented. | [Hopper](https://bindingofisaacrebirth.fandom.com/wiki/Hopper), [Spider](https://bindingofisaacrebirth.fandom.com/wiki/Spider) |
| Summoners | Fixed the local capacity check: a summoner with five surviving children can add only one, even if its attack normally requests six. This is DeathWard's population rule. | Implementation audit |

The catalog and spawn routes are covered by automated checks, including simulation of every entry, IDs, finite state, cleanup, special attacks, linked entities and population limits. These checks test the implementation, not equivalence to Isaac's original AI.

Remaining known differences include ground collision for flying/hopping enemies; shared movement/windup routines; simplified teleport/burrow decisions; Hard Host's projectile volley instead of a travelling rock wave; ground-marked delayed explosions instead of airborne Ipecac projectiles; simplified death/spawn timings; custom health/damage values; and missing coin, active-item, champion and floor-replacement systems. Enemy art uses procedural 3D models. A full enemy-by-enemy behavioral comparison remains outstanding.

## Main-character reference

The [Isaac character page](https://bindingofisaacrebirth.fandom.com/wiki/Isaac) lists three red-heart containers, 3.5 damage, speed 1.0, shot speed 1.0, luck 0 and Repentance range 6.5. Isaac starts with one bomb; the D6 is conditional on its unlock. The [Tears page](https://bindingofisaacrebirth.fandom.com/wiki/Tears) gives his base fire rate as approximately 2.73 shots per second.

| Property | Isaac reference | Current DeathWard character |
| --- | --- | --- |
| Health | Three red hearts | 100 numeric HP by default; adjustable |
| Shot damage | 3.5 | 24 by default; adjustable |
| Fire rate | Approximately 2.73 shots/second | 0.29-second cooldown, approximately 3.45 shots/second before fixed-tick rounding |
| Movement / range | Isaac stat and tile units | World-space movement, mouse aiming, WASD and dodge; no direct unit equivalence |
| Starting equipment | One bomb; D6 after unlock | Revolver and dodge; no player bomb inventory or active-item charge system |
| Appearance | Isaac's character art | Existing animated bandit |

This pass checks the character reference and retains the current player configuration. It does not replace the bandit or silently convert the health system. A coherent Isaac balance preset would need player hearts, incoming damage, enemy HP, shot damage, healing and item effects converted together: changing only 24 damage to 3.5 would make the existing enemies roughly 6.9 times as durable, while changing only health would make ordinary 10-point contact hits immediately lethal.

The subsequent player-balance adjustment sets the DeathWard defaults to 100 HP and 24 shot damage. Enemy tuning in `deathward-m1-21` increases incoming enemy damage by 25%, ordinary movement speed by 10%, and reduces attack cooldowns by 15%. Warning times, committed charge/jump trajectories, enemy HP, mirroring, orbit positioning and friendly-monster behavior retain their prior values. Ordinary contact now deals 12.5 damage; Globin contact deals 25.
