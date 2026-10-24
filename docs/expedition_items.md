# Expedition item rules

Milestone 4 implements the first six proposed additions from [the expedition study](isaac_expedition_study.md). These are DeathWard weapon designs, informed by the preserved Isaac data's distinction between item metadata, attack forms and modifiers. No Isaac item code or artwork is bundled. The Original visual style remains the default.

The eleven items are available in seeded armory rewards and shops. Classic and the tutorial retain their original five-item reward selection. Dedicated weighted room pools are milestone 6. Existing item IDs 0–4 stay stable; IDs 5–10 append the six new items, with no change to the campaign format. Builds carry across expedition floors and remain in resolved/interrupted run history.

## New mechanics

Values below assume the starting 24-damage revolver. They are initial balance settings, not a claim of completed human playtesting.

| Item | First copy | Additional copies |
| --- | --- | --- |
| Scatter Cylinder | Five pellets, 38% damage each, 14-metre reach, 0.34-second cadence. One fan advances the cylinder once. | Two more pellets per copy, maximum nine. |
| Rail Spike | 165% damage, speed 18 instead of 26, three extra body penetrations, 0.50-second cadence. | +15 percentage points damage, +2 penetrations, +0.04-second cadence per copy; five-copy effect cap. |
| Lodestone Sight | 82% projectile speed. Visible targets within 12 metres; maximum turn rate 1.5 radians/second. No steering toward enemies behind cover. | +0.35 radians/second per copy, four-copy cap. The speed penalty applies once. |
| Return Spring | Eight metres of outward travel, then returns toward the player. One body can be damaged on each leg; piercing adds more bodies per leg. Total lifetime 2.2 seconds. | +1.5 metres outward reach per copy, four-copy cap. |
| Blasting Cap | 70% direct damage. First direct body hit makes one 10-damage, 1.5-metre blast with 7 self-damage. | +4 blast damage, +0.1-metre radius and +2 self-damage per copy, four-copy cap. The direct-damage penalty applies once. |
| Fuse Braid | One paid stick: main blast 70 damage / 3.3 metres / 18 self-damage; two secondary charges at 0.65 and 0.95 seconds after the main blast, each at half damage, 70% radius and two-thirds self-damage. | Main and child damage grow by 10% of first-copy values per extra copy; primary fuse grows by 0.15 seconds. Four-copy effect cap. Always two children. |

Scatter + Rail explicitly produces three spikes, each at 48% of the modified rail damage (19.008 starting damage), with Scatter's short reach and Rail's cadence. Extra Scatter copies grow this hybrid to four and five spikes, not nine full-power spikes.

Fuse Braid works with both placed and thrown charges. Its paid children retain hard-demolition permission, so one stick can strike reinforced cover again. This resource advantage is intentional. Free Blasting Cap, Powder and barrel explosions still cannot open hard cover or caches. Children inherit the charge's captured bomb modifiers; they cannot create more children. They use the existing charge collision, gravity, fuse and kick behavior. A normal room clear removes enemy hazards but leaves player charges burning; room travel, debug clearing and run termination retain their existing cleanup rules.

## Combination rules

Resolve a primary attack in this order: choose the fan/spike form; calculate damage, speed, cadence and reach; create the projectiles under one root chain; apply motion and collision; resolve hits; resolve kills and secondary effects. Registry order is fixed, so acquisition order cannot decide a hybrid.

- **Scatter + Split:** fragments use 65% of pellet damage instead of ordinary Split's 80%, and shrink in radius. Each fragment inherits remaining lifetime, remaining bounces and remaining piercing. Creating a fragment does not create another full fan.
- **Rail + Ricochet:** a bank shot consumes a wall bounce, not body penetration. Judas adds six penetrations per copy to every projectile in the sixth primary fan; it adds no damage multiplier.
- **Lodestone + Split/Ricochet:** each fragment acquires its own eligible target. A bounce clears the previous guidance target, allowing another visible target to be chosen. Limited turn rate and the speed penalty remain.
- **Return + Ricochet:** only outward travel can bounce. Outward distance includes banked travel. A wall without a remaining bounce starts the return; a wall on the return stops the projectile. Neither event resets lifetime.
- **Return + piercing:** after exhausting its body-hit allowance, the bullet keeps flying without further hits that leg. Turning clears its already-hit set and restores that leg's allowance. Each body can be hit at most once outward and once returning. Returning shots steer home rather than continuing to home on enemies.
- **Return + Split:** a fragment created during the return starts in the return phase, with no new outward leg. It excludes the body that created it. All fragments retain their parent's remaining lifetime.
- **Cap + piercing/return:** one explosion per projectile lifetime, including both legs. Duplicate Caps strengthen that one blast. Area damage never becomes a direct projectile impact.
- **Cap + Split:** each new fragment has its own one-use cap. Neither its direct-damage penalty nor another item's stat modifiers are applied again.
- **Ghost + explosive kills:** every projectile keeps its birth damage, heading and modifiers. Damage and kill events carry that snapshot through explosions. Ghost repeats that specification, not the explosion's damage and not newly acquired modifiers. A shotless kill, such as dynamite, repeats one projectile from the current weapon at the player's base damage with current modifiers; it never copies the bomb's damage. Ghosts do not produce a new primary fan or advance the cylinder.
- **Terrain + kill effects:** destroying an object never emits an enemy kill. A barrel starts one finite delayed source; it cannot repeatedly pay out or reproduce.

Body penetration, wall bouncing, guidance, return travel, hit explosions and hard demolition are separate properties. None permits a bullet to pass through a solid cliff. Occlusion fading changes visibility and mouse picking, not collision.

Legacy Ricochet, Split, Judas, Powder and Ghost copies retain their stacking rules. New-item effect caps are documented above; the inventory can still contain further copies. All secondary work uses the existing depth/event/queue/projectile/hazard limits. Pauses freeze movement and fuses. Leaving a room retires its active projectiles, charges and queued chains. No item restores health on enemy kills, and no reload system was added.

## Readability and verification

Pellets are small, rail spikes are elongated, guided trails are pale blue, and returning trails are teal. Armed caps have an amber body that returns to its ordinary color after use. Cap detonations use brief small rings without full dynamite smoke. Braid's child bundles are smaller and each shows its own fuse and blast radius. The dynamite preview reflects Braid's reduced main radius. The inventory and result screens fit all eleven item names.

`deathward_item_build_tests` exercises all 66 unordered item pairs (including duplicates), both acquisition orders, and equivalent mouse/arrow inputs across live combat. Additional cases verify trade-offs, sixth-shot cadence, cover, return phases, per-projectile explosions, original shot provenance, bomb children, resource access, capacities, boss targets, in-flight snapshots, seeded availability and save/recovery.

Native visual comparisons use `--smoke --theme canyon --scene build-bank`, `build-shrapnel`, `build-return` or `build-braid`. The browser equivalent is `?verify&mute&smoke&scene=build-bank&theme=canyon&frames=100000`, with the other scene names substituted. `web/item-build-test.cjs` checks live behavior and saves local screenshots. Final validation results are recorded in [the progress log](expedition_implementation.md).
