# Enemy roster and room population

All fifteen ordinary enemy types are implemented in content version `deathward-m1-10`, alongside the Hollow Sheriff. Ash Rusher and Dust Gunman replace the original two basic behaviors. The roster uses primitive 3D models, distinct weapons, attack windups and ground effects; there are no floating control instructions.

Each type changes positioning, aiming or target priority. All enemies belong to the room's initial group: no reinforcement waves, summoners, splitting enemies or resurrection loops. Killing the group reopens the doors. Already-thrown bombs, fire and powder fuses can still be dangerous until they expire; entering another room or using the clear-room cheat removes them.

| # | Enemy | Behavior and visual warning | Player response |
| --- | --- | --- | --- |
| 1 | **Ash Rusher** | A scorched miner runs directly at the player, raises a pickaxe and commits to a short melee swing. | Keep moving; punish the missed swing. The basic pressure enemy. |
| 2 | **Dust Gunman** | A ragged outlaw holds medium range and fires deliberate single shots after a visible muzzle glint. Repositions when cover blocks its shot. | Strafe, use cover, or close the distance during its recovery. |
| 3 | **Shotgun Outlaw** | A broad-coated gunfighter closes to short range, braces and fires a wide cone, followed by a long reload. | Back out of the cone or dodge past it; attack during reload. |
| 4 | **Grave Sharpshooter** | A pale-coated rifleman holds a firing lane. Its muzzle glow and ground sight line warn before a powerful, narrow shot. | Break the sight line or dodge sideways, then rush its long recovery. |
| 5 | **Dynamite Prospector** | A miner lobs a sparking charge toward the player's recent position. The landing point and burning fuse make the delay visible. | Leave the marked area; pressure the thrower so it cannot deny cover safely. |
| 6 | **Ironhide Brute** | A large miner wears a furnace plate over its front. Frontal shots deal reduced damage; its back is exposed while it slowly turns. | Flank, bank shots around it or exploit piercing and area damage. Never fully immune to the player's weapon. |
| 7 | **Railbreaker** | A heavy rail worker lowers its shoulder, marks a straight charge lane and commits to a rush. Hitting a wall leaves it stunned. | Dodge sideways and bait the charge into cover. |
| 8 | **Hex Preacher** | A crooked preacher chants a temporary protective aura over nearby allies. Its raised book and visible circle identify the source. | Kill or interrupt the preacher, or pull enemies outside its limited aura. Protection reduces damage rather than preventing it. |
| 9 | **Bell Ringer** | A figure carrying a cracked church bell winds up before sending an expanding damaging ring across the floor. | Dodge through the ring during invulnerability or shelter behind solid cover. Rings respect walls. |
| 10 | **Hangman** | A rope-bearing executioner visibly aims before casting a hook that pulls the player toward it. | Dodge across the cast or put cover between player and attacker to break the line. |
| 11 | **Cinder Spitter** | A swollen coal creature spits burning oil that leaves a temporary ground hazard after a clear landing warning. | Move around the fire and prevent it from cutting off escape routes. Distinct from the prospector's short explosion. |
| 12 | **Ricochet Marshal** | A silver-badged gunfighter fires a slow, conspicuous shot that can bounce once from a wall. Sparks reveal the bounce. | Watch the rebound and fight away from tight corners; attack between deliberate shots. |
| 13 | **Lantern Wraith** | A lantern-bearing ghost marks its next destination inside the room, waits 0.9 seconds, relocates, then winds up a three-shot attack for another 0.75 seconds. | Track the destination and punish its exposed attack/recovery window. It remains targetable during the departure warning and never attacks immediately on arrival. |
| 14 | **Powder Husk** | A walking powder keg displays a bright fuse when mortally wounded, then explodes after a short delay. The blast can hurt its allies. | Kill it at range or use its position to start a chain reaction. Death warning and blast radius must stay readable. |
| 15 | **Chainbound Outlaw** | Two outlaws from the initial group drag a damaging chain between them, forming a moving barrier. The chain slackens when solid cover separates them. | Focus one outlaw to break the pair, use cover, or dodge across the taut chain. A survivor fights as an ordinary gunman. |

## Population rule

For each combat room:

```text
usable floor = sum of the generated room floor strips - obstacle footprints on that floor
initial enemies = clamp(ceil(usable floor / 70), 4, 24)
```

This counts the actual rectangular, clipped, L-shaped or cross-shaped floor, excluding corridors and missing corners. Room depth no longer determines the number of enemies. Obstacles reduce the area; the formula is a density budget rather than a count of collision-free player positions.

| Usable floor (square world units) | Initial enemies |
| ---: | ---: |
| 490 | 7 |
| 700 | 10 |
| 1,050 | 15 |
| 1,400 | 20 |
| 1,680 or more | 24 |

The starting room, other quiet rooms and power caches contain zero enemies. The first boss encounter contains one Hollow Sheriff. A later visit after the Sheriff is permanently defeated uses an ordinary group sized with the same area rule.

## Group composition and placement

The seed and room identity choose a basic role and two other distinct roles. Roughly half or more of a normal group uses the basic role; the other roles each occupy roughly a quarter, with pair rounding for Chainbound Outlaws. Rooms one passage from the start select from Rusher, Gunman, Shotgun, Sharpshooter, Prospector and Ironhide; deeper rooms can select any of the fifteen. Chainbound pairs consume two slots in the initial population and never summon a partner.

Composition has a separate random stream from placement, combat and rewards. Visiting rooms in another order does not change their population or types. Spawn positions and opening cooldowns also reproduce when entering from the same position. Positions avoid walls, obstacles, overlapping bodies and the six-unit safety area around the player. Positions can adjust when approaching through a different entrance to preserve that safety area.

F4/F5 still spawn exactly 20/100 test enemies when capacity and floor space allow, and now sample the complete roster. F11 exercises the expanded roster in the existing stress scene. These explicit testing requests bypass the normal density budget. Shift + F3 clears enemies, projectiles, lingering hazards and pulls; room jumps/restarts also discard old hazards.

## Balance starting point

These are initial tuning values, ready for playtesting. Ordinary enemy health ranges from 36 to 144, attacks have 0.45–1.15 second windups, and each special has recovery time. Ironhide takes 35% damage from ordinary frontal shots; rear, piercing and area hits bypass that plate. A preacher's aura reduces nearby allies' damage by 35%, does not stack, respects cover, and ends when the preacher takes damage. Dodge invulnerability applies to melee, hooks, charges, shockwaves, chains, blasts and fire.

Dynamite has a 1.05-second flight/fuse after the throw. Fire lands after 0.85 seconds and persists for 3.5 seconds. Powder Husks have a 1.1-second death fuse, and their blasts retain the triggering kill chain so the existing item effects can react to subsequent kills. Delayed hazards participate in the existing bounded chain accounting and expire without spawning enemies.
