# Monster roster: IDs 10–89

The catalog implements the enemy entries in the requested type range from the [Monsters reference](https://bindingofisaacrebirth.fandom.com/wiki/Monsters), including DLC variants and subtypes. The [current wiki index](https://bindingofisaacrebirth.wiki.gg/wiki/Monster) supplies additional readable references. IDs are stored as separate integer components: `25.3.1` and `68.11` stay distinct. There are 120 entries within the requested range (including detachable Maw heads), plus eight supporting creatures outside it needed by spawners and paired enemies. Numeric gaps are not invented enemies; bosses on the separate boss list are outside this roster.

## Play and test

Canyon missions use only Isaac catalog monsters, including the final Infested Mesa group. Mine missions use only the original Western roster and the Hollow Sheriff. New sessions offer Canyon by default. Completing the canyon does not mark the Sheriff dead in the mine. Composition and placement use independent room seeds. A basic family fills most slots; one specialist fills roughly a third. An invulnerable specialist takes at most one slot. Difficulty gates later variants by room depth. Initial group size still uses navigable room area, with 4–24 slots, six units of arrival clearance and no overlapping initial bodies. Attached companions consume initial slots. Subsequent summons are additional bodies, bounded by the shared 256-enemy cap. Summoners retain at most six living children; offspring generations are bounded.

With cheats enabled, **comma / period** selects the previous / next catalog entry; the announcement shows its ID and name. **Shift+F4** places that selection on safe floor and keeps the encounter in test mode. **F4 / F5** spawn 20 / 100 random roots from the current mission's roster, with attached companions where required. **F3** kills existing enemies without creating replacement offspring; **Shift+F3** ends the test and clears the room, pending offspring, projectiles, hazards and event chains. The shortcut panel stays hidden until backtick is pressed. Hovering a monster displays its ID and name.

## Combat systems

The implementation includes committed attack warnings, radial and spread patterns, homing and splitting projectiles, returning head attacks, directional armor and reflected shots, opening Host shells, regenerating Globin piles, aimed beams clipped by cover, timed explosive landings, persistent damaging and slowing pools, burrowing and teleport arrival warnings, leaps, wall followers, linked chains, mirrored movement/shooting, on-death transformations and bounded summoning. Pons control their paired Knights; protected orbiting flies change state when their host dies. Permanent room hazards are excluded from completion objectives and deactivate on clear.

Names and IDs identify the references; meshes are new procedural 3D silhouettes built for this game. Walkers, headless bodies, insects, segmented crawlers, skulls, blobs, eyes and stone hazards have different geometry, with variant colors, wings, armor, flame details and state poses. HP, speed, range, damage and warning times are tuned for DeathWard's revolver and dodge.

## Adaptation boundaries

This is a DeathWard implementation of the roster and its combat roles, rather than a byte-for-byte simulation of Isaac. Floating creatures use DeathWard's solid-surface navigation so their rendered position and hit volume remain consistent with canyon and mine cover. Hops are shown as an animation above that collision surface. The game has no coin economy, active-item charges, destructible poop, champion system or Isaac floor replacement rules: Keeper retains its hopping spread attack without coin theft; Bulb wanders harmlessly because there are no active-item charges to steal; Fly stays harmless. Timing, spawn probabilities and a few projectile formations are simplified. Eggy now produces the distinct Swarm Spider support entry; its lingering death animation remains unimplemented. Tainted Sucker has no contact damage and its death projectiles can bounce. See [the review and character reference](isaac_review.md) for verified corrections and remaining differences. No original Isaac sprites, sounds or models are bundled.

## Catalog

The table below is generated from the runtime definitions for review. “Support” entries outside 10–89 are used only as offspring or attached companions; the test selector also exposes them.

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
| 68.1 | Peep Eye | Bounce | None |
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
| 222.0 | Ring Fly (support) | Orbit | None |
| 238.0 | Splasher (support) | Wander | Lob |
| 840.0 | Pon (support) | Hop | None |
| 853.0 | Small Maggot (support) | Wander | None |
| 861.0 | Pustule (support) | Still | None |
| 862.0 | Cyst (support) | Wall | Shot |
| 884.0 | Swarm Spider (support) | Hop | None |
