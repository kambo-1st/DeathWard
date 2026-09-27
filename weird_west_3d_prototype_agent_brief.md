# Weird West 3D ARPG Roguelike

Prototype Agent Brief

C++20 + raylib • true 3D gameplay • temporary power, persistent consequences

## 1. Mission

Build a small playable 3D prototype in C++20 using raylib. Combine fast Diablo-like action combat, Binding of Isaac-style combinatorial run builds, temporary expedition power, persistent narrative/world consequences, and a Weird West setting.

Core principle: POWER IS MOSTLY TEMPORARY. CONSEQUENCES ARE PERSISTENT.

The experiment asks whether a player can begin ordinary, discover interacting effects, create a ridiculous or broken build, finish or fail, lose that build, and still feel that the expedition permanently mattered.

## 2. Non-negotiable 3D requirement

The prototype MUST be a true 3D game. Do not implement a 2D top-down game and do not fake 3D with sprites.

Use raylib Camera3D, Vector3 world positions, 3D collision volumes and 3D projectile movement. Use a Diablo-like elevated perspective camera looking down at the player at roughly 35–55 degrees.

Player movement occurs mainly on an XZ ground plane. Mouse aiming uses a ray cast from the screen into the 3D world and intersects the ground or world geometry.

Enemies, projectiles, pickups, walls, obstacles, explosions, effect areas and boss attacks occupy the 3D world.

Graphics are intentionally disposable. Prefer cubes, spheres, cylinders, planes, generated meshes, debug lines and text. Do not spend prototype time on models, textures, skeletal animation or an asset pipeline.

Rendering must remain separable from gameplay rules so primitive graphics can later be replaced without rewriting combat.

## 3. Primary research question

Can temporary, highly combinatorial power create memorable individual runs while persistent consequences make those runs meaningful to a larger campaign?

Keep Run Progression and Campaign Progression explicitly separate. Run progression is temporary, explosive and disposable. Campaign progression is persistent world state, story, relationships, unlocked possibilities and consequences.

Do not turn campaign progression into permanent stat inflation that recreates the strongest previous run.

## 4. Technology

Use C++20, raylib and CMake. Prefer standard C++ and avoid unnecessary dependencies. Deliver and test the first milestone on Linux while keeping the code portable to Windows. The expanded prototype must build and be tested on both Windows and Linux. Target 60 FPS.

Optimize architecture for rapid experimentation. Avoid both excessive abstraction and monolithic gameplay classes.

## 5. Fundamental loop

HUB → choose expedition → 3D expedition → combat/reward/event cycles → boss/objective → success or failure → resolve persistent consequences → destroy temporary RunState → changed HUB.

The first milestone targets a 5–10 minute expedition. The expanded prototype targets 15–25 minutes. Debug tools must allow the complete loop to be exercised in seconds.

## 6. 3D combat

Use an elevated Diablo-like camera, not first person or over-the-shoulder. Support Diablo-style contextual left-click alongside WASD: click ground to move, hold LMB to steer, click an enemy's body to attack, and click an available objective to approach and interact on arrival. Holding an enemy keeps attacking that target as it moves; when it dies, do not turn the held attack into a movement order. Attacking cancels mouse navigation. Shift holds position; Shift + LMB fires toward the cursor. RMB directly fires the revolver (the prototype's only weapon). MMB or SPACE dodges; E remains an interaction shortcut. Provide clickable dodge, nearby-interaction and pause controls so a two-button mouse can operate the complete expedition. Mouse routes should avoid walls and obstacles; WASD overrides the current mouse route and remains available while firing unless Shift is held.

Start with one revolver: continuous fire with no reload action or reload pause, moderate fire rate and real projectile entities. Preserve a repeating six-shot cycle, visibly showing the next round. Every sixth shot counts as the last round for item effects, then the cycle immediately starts again.

Starting player health is 200 HP and base revolver damage is 48, both doubled from the initial milestone. Enemy damage stays unchanged. Percentage-based item costs still apply to the increased health pool.

Generate a continuous mine from the expedition seed: seven rooms joined by traversable corridors, with different room dimensions and footprints and seeded obstacle positions, sizes and heights. Use real 3D walls and cover for ricochets, line of sight and area effects. Reserve clear paths between entrances, exits and objectives, validate floor connectivity, and place enemies only on safe floor. Open the next doorway after the current room's reward choice; walk between rooms without teleporting. Keep cleared passages open for backtracking without repeating encounters, rewards or healing. The camera and navigation must work throughout the map, with a small map showing room connections and the player's position.

Provide a debug toggle for collision volumes, projectile paths, effect radii and target points.

## 7. Hub and WorldState

The hub is Black Creek, a frontier settlement. It may remain a menu/status screen. A navigable 3D town is not required for this prototype.

Persist population, prosperity, law, locations, character states, world flags, completed expeditions and run history to disk. Reload them on application start.

Example persistent characters: Sheriff Cole, Mary Bell, Father Gabriel, Silas Reed and Dr. Whitmore.

Before entering an expedition, persist a pending-run record with a unique run ID, expedition ID, seed and the campaign context needed to resolve retreat. Checkpoint objective progress and a non-restorable partial run summary after important interactions and encounters. This is recovery metadata, not a resumable RunState.

Save WorldState, Run History and pending-run status together in one versioned campaign snapshot. Write to a temporary file and atomically replace the previous snapshot. Resolve each run ID only once; saving its consequences and history must also clear its pending status. If startup finds a pending run, resolve retreat from its last committed checkpoint before showing the hub.

## 8. Consequences

Expeditions must have multiple persistent outcomes. Success is not merely XP and failure is not a rewind.

Failure should create recoverable setbacks and new complications. Show the stakes before departure and important actions, while leaving exact consequences uncertain. Outcomes depend on combat results and optional actions in the world, such as rescuing miners or destroying an altar.

For the first Red Hollow Mine expedition, implement three outcome categories: defeating the boss and rescuing the miners; defeating the boss while miners remain stranded; or retreating/failing while the threat remains. These alter mine access, prosperity, relationships and recovery opportunities. Optional-objective flags may further modify an outcome. Avoid permanent NPC deaths or permanently inaccessible locations as routine failure penalties in this milestone.

Locations can be revisited and must reflect previous outcomes. Rescued miners stay rescued, unresolved objectives remain available, and a cleared boss is replaced by a simple follow-up encounter on later visits. Completed objectives cannot award the same population or prosperity increase repeatedly. Provide a playable way to recover from a mine setback on a later visit.

Prototype target: 3 expeditions, 2–4 outcomes each, about 5 persistent NPCs and 10–15 world flags.

## 9. RunState

RunState is completely separate from WorldState. It owns temporary health modifiers, weapon transformations, items, effects, combat counters and run RNG state.

At expedition end, destroy RunState. Do not serialize the temporary build into permanent character power.

## 10. Enemies and density

Implement roughly five archetypes: Bandit, Rusher, Gunman, Abomination and Preacher. Primitive 3D shapes are sufficient.

The first milestone uses only Rusher and Gunman, plus the boss. Add the remaining archetypes after the complete campaign loop works.

Early encounters may contain 5–10 enemies, middle 10–20 and late 20–40. Stress testing should support around 100 enemies.

## 11. Item philosophy

Do not center the prototype on +10% damage, +15% attack speed or similar stat sticks. Numerical modifiers can support the system, but important items CHANGE RULES.

Implement roughly 25 items. Candidate effects include: Ricochet Coin (wall bounce), Split Lead (split on hit), Judas Bullet (every sixth shot penetrates), Powder of Jericho (kills explode), Hangman's Coin (ghost repeats killing shot), Silver Teeth (penetration increases damage), Blood Cylinder (every sixth shot trades health for projectile count), Undertaker's Nail (corpse nails become projectiles), Preacher's Lie (periodic homing), Snake Oil (overheal becomes poison shots), Grave Dust (explosions create clouds), Sheriff's Badge (elite kills create Wanted targets), Black Powder Bible (explosion chains), Devil's Cartridge (ignite and death explosion).

Start with five items: Ricochet Coin, Split Lead, Judas Bullet, Powder of Jericho and Hangman's Coin. Prove their interactions inside a complete expedition before expanding the catalog.

## 12. Emergent interaction system

This is the heart of the prototype. Do NOT implement bespoke pairwise combination checks such as hasRicochet && hasSplitLead.

Effects communicate through generalized events such as OnShot, OnProjectileCreated, OnProjectileHit, OnProjectileBounce, OnEnemyDamaged, OnEnemyKilled, OnExplosion, OnPlayerDamaged, OnRoomCleared and OnPickup. Shot events carry the six-shot cycle's last-round marker.

A valid emergent chain is: bullet → ricochet → hit → split → kill → explosion → another kill → ghost → repeated shot → ricochet/split again.

Adding a new item should naturally create possible interactions with existing items through the event model.

Use a fixed simulation timestep and a FIFO event queue. Handlers enqueue follow-up events instead of recursively dispatching them. Execute handlers in a stable order defined by explicit priority and stable effect IDs, including an instance ID when duplicate effects exist. Define whether each hook modifies a pending action or observes an already committed result; OnEnemyDamaged and OnEnemyKilled observe committed results.

Apply damage modifiers in that stable order, commit damage, and emit a kill event only on the first alive-to-dead transition. Mark dead entities immediately so later queued hits cannot kill them again. Use validated entity handles and immutable event payloads containing the position, damage and projectile information needed by follow-up effects. Reclaim dead entities at a safe simulation boundary; queued effects must never dereference stale pointers.

## 13. Provenance and recursion safety

Emergent chains may become ridiculous but must not crash or hang the game. Carry chainId, generation, sourceEntity and sourceEffect with generated events/effects.

Start with a maximum generation depth of 16 plus protection against pathological repeated cycles. Log terminated chains.

Depth alone does not bound branching. Add named, configurable limits for total events accepted per chain, events processed per simulation tick, total queued events and active generated entities. Descendants inherit the chain ID and advance generation; spawning a projectile or scheduling a delayed effect must not reset provenance or the chain budget. Keep chain accounting until all queued and active descendants finish.

When the tick processing budget is exhausted, defer remaining events in FIFO order. When a chain reaches its depth or total-event ceiling, suppress further descendants from that chain. At queue or entity capacity, reject new generated work deterministically. Record the chain, effect, limit and suppressed count, and show budget hits in the debug view. Keep these safety limits separate from balance tuning.

Do not solve recursion safety by broadly preventing secondary effects from triggering other secondary effects.

## 14. Rewards and rarity

After selected encounters, pause and offer three random items. The decision should primarily be about what combines with the current build, not a DPS comparison.

Use only COMMON, STRANGE and CURSED initially. Cursed items should provide transformative power with dramatic costs. Example: every bullet splits, but maximum health is reduced by 50%.

## 15. Desired power curve

For the expanded 15–25 minute expedition: 0 min: ordinary cowboy and plain revolver. 5 min: weapon noticeably altered. 10 min: clear synergy. 15 min: player intentionally exploits interactions. 20 min: build may be absurd.

Compress reward pacing for the first 5–10 minute milestone: offer an early transformation, allow several items before the boss, and give the player time to use their combined build.

Do not immediately nerf a combination because it deletes a room or boss. A genuinely broken run is an intended experimental result.

## 16. Boss

Implement one boss, The Hollow Sheriff, with roughly three simple phases. It exists to test wildly different builds against one common target.

Do not make the boss blanket-immune to the item system. If a broken build kills it in five seconds, allow it and record the result.

## 17. Failure and victory

On death, resolve world consequences rather than rewinding. On victory, resolve objective and optional-objective outcomes. Then destroy the run build and return to the changed hub.

Closing the application during an expedition counts as retreat: lose the temporary build and resolve retreat consequences. On an orderly close, use current objective progress and summary data. After a crash or forced termination, use the last committed checkpoint. Do not offer mid-run resume in the first milestone.

Death and retreat share the first milestone's recoverable failure outcome category but retain distinct reasons in Run History. Already completed rescues remain completed. Example failure: unrescued miners remain stranded, the mine closes temporarily, prosperity falls, and a recovery opportunity becomes available. Example victory: six miners rescued, mine reopens, prosperity rises, but an undestroyed altar creates a later flag.

## 18. Run memorialization

Make losing power meaningful by preserving history, not power. The post-run screen must juxtapose temporary mechanical history with permanent narrative history.

Show duration, kills, bullets fired, projectiles created, explosions, largest effect chain, acquired items and world consequences. End with the design statement: THE BUILD IS GONE. THE CONSEQUENCES REMAIN.

Persist summaries in Run History. Previous builds may be inspected but never restored.

## 19. Minimal narrative

Do not write a giant campaign. Give recurring NPCs simple alive/dead/missing states, relationship states and a few dialogue states.

NPC dialogue must react to actual world flags. The important property is that the game remembers what happened.

## 20. Determinism

Every expedition has a visible seed and supports manual seed entry. Item choices, encounters and procedural decisions should be reproducible where practical.

Derive independent layout, encounter, reward and combat RNG streams from the expedition seed using stable stream identifiers. Layout geometry must depend only on seed and content version, independently of campaign outcomes and combat/reward draws. Combat randomness must not consume reward or encounter randomness. Record seed, game/content version and relevant starting campaign context in Run History.

The first milestone guarantees repeatable encounter setup and reward offers for the same seed, version, starting campaign context and sequence of relevant player choices. It does not promise full combat replay from a seed alone. Keep debug scenario setup reproducible so item interactions can be checked without replaying an entire run.

Determinism is essential for reproducing broken builds and bugs.

## 21. Debug tooling

Debug tooling is mandatory: god mode; kill all; spawn enemy/20/100 enemies; spawn selected item; give random item/five items; start boss; finish/fail expedition; reset campaign; set/clear world flags; inspect active effects and event chains; toggle collision/effect-radius rendering; show entity/projectile/event counts; freeze/slow simulation if practical.

Build debug tooling and telemetry alongside the systems they inspect. The first milestone includes seed entry, god mode, selected-item grants, enemy spawning, start boss, finish/fail/retreat, campaign reset, chain inspection, count/budget displays and collision rendering. Do not defer these until content expansion.

## 22. Telemetry

Collect locally: run duration, damage dealt/taken, shots fired, projectiles generated, enemies killed, items acquired, explosions, maximum active projectiles, maximum effect-chain depth, largest kill chain, rooms cleared, boss duration and result.

No network analytics are required.

## 23. Performance

Stress test 100 enemies, 500+ projectiles, simultaneous explosions and recursive chains. Correctness and responsiveness matter more than visual fidelity.

Avoid obvious projectile-versus-every-entity designs when simple spatial partitioning is needed, but do not prematurely optimize.

Record benchmark hardware, OS, build configuration, resolution, scenario seed, frame times and safety-budget hits. Evaluate the 60 FPS target against that recorded environment. A passing stress test must remain responsive without silently discarding so much work that the intended interaction scenario no longer runs.

## 24. Suggested architecture

Suggested modules: core/Game, GameState, Random, EventBus; render/Renderer3D, CameraController, DebugRenderer; world/WorldState, WorldPersistence, ConsequenceSystem, ExpeditionDefinition, Arena3D; combat/CombatSystem, ProjectileSystem, DamageSystem, ExplosionSystem, Collision3D; entities/Player, Enemy, Boss; items/Item, ItemRegistry, ItemEffects; effects/Effect, EffectContext, EffectSystem; runs/RunState, RunHistory; ui/HubUI, RewardUI, DebugUI.

## 25. Implementation order

Milestone 1 is one complete 5–10 minute expedition on Linux. Keep every intermediate step compiling and playable:

1. Bootable CMake/raylib project with a 3D arena, camera, player, mouse-to-world aiming, revolver and one enemy.
2. Minimal hub, separate RunState/WorldState, placeholder expedition completion, saved consequences and Run History. Exercise the full loop using debug shortcuts immediately.
3. Queued event/effect system with provenance, bounded processing, deterministic RNG streams and chain inspection. Add the five initial items and reward choices.
4. Complete Red Hollow Mine with Rusher, Gunman, The Hollow Sheriff, a miner-rescue interaction and three outcome categories. Support revisits that reflect resolved and unresolved objectives.
5. Verify restart persistence, retreat on close, interrupted-run recovery, build destruction, interaction scenarios and a representative stress scenario. Tune the short expedition's reward pacing.

Milestone 2 expands content only after Milestone 1 passes its acceptance checks: grow to 20–25 items, five enemy archetypes, three expedition definitions, about five persistent NPCs and 10–15 flags; extend expeditions toward 15–25 minutes; complete the remaining debug tools and validate Windows support. Continue stress testing as content expands.

## 26. Acceptance criteria

Milestone 1 must pass the following observable checks before content expansion:

- Complete hub → Red Hollow Mine → summary → changed hub in a normal 5–10 minute playthrough and in seconds with debug controls.
- Exercise all three outcome categories. Restart the application and confirm that the expected world state and history remain, while all temporary items and modifiers are gone.
- Close during a run and verify retreat. Simulate interruption with a pending run, restart twice, and confirm consequences are applied exactly once. Interrupted summaries may contain only checkpointed data and must be marked accordingly.
- Revisit the mine after rescue, incomplete victory and failure. Confirm completed rescues are not awarded twice and recovery objectives can repair a prior setback.
- With a fixed debug setup, demonstrate a bounced projectile that hits and splits; a projectile kill that causes an explosion and another kill; and a ghost shot that can trigger ordinary projectile effects. Each initial item must also demonstrate its stated rule change.
- Trigger a pathological branching chain and verify that configured limits terminate or suppress it with diagnostics while input and rendering remain responsive. Ordinary multi-effect chains must still complete below those limits.
- Repeat encounter setup and reward choices with the same seed, version, campaign context and choices. Extra combat RNG draws must not change the encounter or reward streams.
- Run the recorded 100-enemy, 500-plus-projectile stress scenario and report frame times and budget hits against the 60 FPS target.

The expanded prototype must additionally satisfy the full target below:

The game is genuinely 3D using raylib 3D rendering, world coordinates and collision concepts.

A full hub → expedition → consequence → hub loop works.

Temporary run items disappear after the expedition and persistent consequences survive application restart.

At least 20–25 rule-changing items exist and interact through generalized events rather than hardcoded pair combinations.

Several combinations produce qualitatively surprising or broken behavior.

Large effect chains terminate safely without disabling normal emergent chaining.

A seed can reproduce relevant run setup.

Run History records the lost build and lasting consequences.

One boss and multiple enemy archetypes are playable.

Primitive graphics are accepted and preferred over spending time on art.

## 27. What NOT to build

Do not build production art, a full campaign, multiplayer, networking, elaborate procedural terrain, a full inventory/equipment economy, crafting, skill trees, voice acting, cinematic systems, sophisticated animation, realistic physics, or a large open world.

Do not convert the prototype into a generic Diablo clone. The experiment succeeds only if temporary item combinations materially alter rules and persistent consequences make each expedition matter.

## 28. Agent working rule

Work vertically. Keep the project compiling and playable after each milestone. Prefer a small complete loop over broad unfinished systems.

When uncertain between polish and another meaningful interaction, choose the interaction.

When a combination appears overpowered but mechanically coherent, do not nerf it automatically. Record it, make sure it is safe, and treat it as evidence.

The prototype is successful when repeated runs produce moments of discovery such as: 'I did not realize those two things would interact like that,' followed by a meaningful change to Black Creek after the build is gone.

## Appendix A. Minimal 3D camera sketch

```text
Camera3D camera{};
camera.position = {12.0f, 16.0f, 12.0f};
camera.target = player.position;
camera.up = {0.0f, 1.0f, 0.0f};
camera.fovy = 45.0f;
camera.projection = CAMERA_PERSPECTIVE;

// Each frame:
// 1. Smooth camera.target toward player.position.
// 2. GetMouseRay(GetMousePosition(), camera).
// 3. Intersect ray with the gameplay ground plane.
// 4. Aim weapon from muzzle world position toward that hit point.
```

## Appendix B. Example EffectContext

```text
struct EffectContext {
    uint64_t chainId = 0;
    int generation = 0;
    EntityId sourceEntity{};
    EffectId sourceEffect{};
};
```
