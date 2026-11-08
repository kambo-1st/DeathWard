# Ordinary Monstro: enabled controller, full acceptance open

Target: installed Repentance 1.7.9b, ordinary Monstro `20.0.0`, Basement pool boss ID1. This checkpoint enables ordinary Monstro through the spawn API and enemy inspection scene, with source-derived ordinary combat states. **The actor is not fully accepted, and production Basement boss selection is still absent.** Existing bosses and player defaults are unchanged; universal dodge retains its boost and immunity.

The NPC dispatch table at `0x69abc0` maps type20 to index8, case `0x6997a8`, which calls `0x45bec0`. The preserved [AI listing](ordinary_and_shared_ai.asm) includes its ordinary and shared-actor branches. Type43 also uses substantial shared code; its logic is not automatically Monstro behavior. [manifest.json](manifest.json) pins the executable, source XML and bounded windows.

The preserved XML specifies base HP250, stage HP0, collision damage1, mass50, radius40 and friction1 for ordinary Monstro. These are source values; they are not a new DeathWard HP conversion or proof of AI. The Basement pool contains this boss, but XML pool membership does not establish first-floor selection probability, unlock/exclusion rules or room eligibility.

## Executed native evidence

- [48 action-selection cases](native-decisions.csv): supplied unsigned RNG words enter **after** the native RNG call at `0x45c870`. The original unsigned modulo3 and subtype dispatch execute. Ordinary subtype0 selects small hop / spit / large jump as actions0/1/2. Subtype2 remaps action2 to1; that branch is recorded separately and does not establish a fully accepted champion encounter. The global RNG producer/stream is not executed.
- [32 force cases](native-forces.csv): supplied target deltas and velocities, ordinary controller and timeScale1. The common temporary-friction prefix executes before either small-hop or large-jump force code. The original sqrt and normalization helpers execute without substitutions. The samples establish velocity changes and temporary friction only; base physics, world collision and full trajectories are outside these captures.
- [24 projectile payload cases](native-projectile-payload.csv): native falling-speed, acceleration and size blocks execute with supplied RNG words/size bits and trajectory0/10. World spawning, planar imported trigonometry, parameter/item/status modifiers and the global RNG stream are outside this execution scope.
- Small-hop force uses normalized target direction scaled by1.2 and divides its contribution by the common temporary friction0.9. Its additional damping leaves temporary friction approximately0.81 before base physics.
- Large-jump force uses `0.006 * targetDelta + 0.3 * normalizedDelta`, divided by temporary friction0.9. Zero displacement produces no added force. The supplied examples include tiny, axial, diagonal and distant targets with stationary and moving initial velocities.

These are independent native outputs, not generated from a proposed C++ controller. **No whole-AI, full animation callback or live-game acceptance is claimed.**

## Animation and state dependencies

[Animation metadata](animations/manifest.json) comes from the highest matching installed archive override, `afterbirthp.a`, with pinned archive hash, entry length/checksum and extracted XML hash. No sprite artwork is imported. It declares FPS30:

| Animation | Frames | Native metadata events |
| --- | ---: | --- |
| Appear | 26 | None |
| Walk | 45 | Jump6, Land22 |
| Taunt | 66 | Shoot21 |
| JumpUp | 15 | Jump10 |
| JumpDown | 64 | Land32, Shoot34 |
| Death | 78 | BloodStart12, Explosion77 |

The AI distinguishes the current-frame and already-triggered animation queries. Source controller states are3 for selection,4 for the small hop,8 for the spit,6 for jump-up and7 for jump-down. Small-hop completion can restart Walk using another RNG bit rather than returning to a generic cooldown. The large-jump transition checks the Jump event rather than simply waiting for all15 JumpUp frames. Capturing metadata does not establish exact live update ordering or callback frequency.

The preserved Lua property registration and native getter/setter bodies independently identify **GridCollisionClass at offset0x17c** and **EntityCollisionClass at offset0x180**. The small-hop branch writes grid3/entity0 after Jump and before Land, and grid5/entity4 outside that interval. The large-jump branches likewise change these fields at their event boundaries. This resolves the field identities without borrowing offsets from another executable version. Full collision-handler eligibility and ordering still need verification; field writes alone are not actor acceptance.

Source attack calls matter:

- At `0x45cb00–0x45cb04`, ordinary Monstro calls `FireBossProjectiles` with **count13**, the current target position and trajectory modifier0. The helper is at `0x6a3420`; this is not projectile mode13. Its aimed branch adds independently randomized planar scatter.
- At `0x45d886–0x45d888`, its JumpDown Shoot event supplies **count18**, the zero-vector sentinel and trajectory modifier0. The helper draws a separate radial direction for each projectile. It is not an evenly spaced18-shot ring.
- The projectile helper also selects falling speed, acceleration and size. The [helper listing](boss_projectile_constructor.asm) and [parameter initializer](projectile_params_constructor.asm) are preserved. Their bounded falling/size arithmetic is executed separately; the whole world-spawning path remains disassembled rather than executed.

## Enabled integration and verification

`isaac-baseline-v7` registers ordinary `20.0.0` with source base HP250, stage HP0 and conversion1. The regular-enemy HP multiplier does not alter this boss. Unsupported forms/subtypes are not silently mapped to ordinary Monstro, and the actor is excluded from natural regular-enemy pools. The explicit `boss_monstro` controller requires an independent body. The source HP/stage values remain separate from conversion and adaptation factors.

The controller uses the ordinary selection, Walk, Taunt, JumpUp and JumpDown states, with the preserved event frames. Small-hop completion can continue the hop sequence; no guessed cooldown or HP-threshold phase replaces this. Supplied-input force kernels match the native captures. The current physics adapter applies native timeScale1/base friction1 endpoints at30 Hz within the60 Hz simulation; live ordering and clock calibration remain open.

Spit and landing produce thirteen aimed/scattered and eighteen independently radial projectiles respectively. Their default native falling/size arithmetic is wired into the existing damped-flight system. Each volley retains its selected samples and origin if queue/projectile capacity is unavailable, then admits once capacity returns. Source RNG draw roles are explicit, but the generator remains DeathWard's stream; native global RNG, imported trig endpoints and extra world-spawn draws are not accepted. Horizontal `.1`, vertical `.05`, collider geometry and fractional interpolation remain explicit world adaptations.

Source collision field writes drive the airborne windows: tears pass through without being consumed, contact is disabled and radial collection excludes the collision-zero body. A direct scripted damage call remains distinct and can still damage that body. This separation is supported by the pinned common [direct/radial damage evidence](../../isaac-enemy-port/adult-leech/source/damage-manifest.json); it is not a claim that all Monstro damage/status flags are accepted. Native room-grid selection is currently adapted to the DeathWard room bounds with four-world-unit spacing; exact origins, exclusions and room layouts remain open. Allocation rejects obstructed/narrow placements rather than admitting an invalid navigation hull.

A separate procedural model shows the jump lift and spit pose, without borrowing Peep's eye-socket presentation or inventing health phases. Graphics remain the accepted exception.

`native_monstro` checks all48 decision cases,32 force cases and24 payload cases against independent native outputs. Integration fixtures exercise13/18-shot emission, flight/size payloads, independent radial samples, queue-pressure recovery without new RNG draws, Jump/Land transitions, direct/radial damage separation, tear passage, contact damage, retained universal dodge, rejected unsupported forms,250-HP death and actual room completion. A3,600-tick normal sequence exercises all five action states, both attack families, finite motion and room containment. The application builds and **16 selected native/baseline/status/boss regression suites pass**. [encounter.png](encounter.png) is a300-frame rendered inspection encounter, with one living250-HP Monstro and13 emitted shots. Inspection god mode makes it a launch/render check, not native combat, balance or performance acceptance. See `validation.json` and the saved logs for exact input hashes and scope.

## Still required

1. Match complete native animation/birth/appearance/base-physics ordering, live timing and global RNG, including imported trig endpoints and world spawn side effects.
2. Replace the room-grid/collider/world-height adaptations with verified source room geometry and selection rules. Verify walls, pits, terrain, targeting changes, contact and projectile collision ordering against native play.
3. Finish source per-boss status/damage flags, modifiers, death/revival/execution behavior and rewards. Existing DW boss payouts and room progression are not a native reward port. Verify persistence, capacity limits and mixed encounters in live play.
4. Implement and accept eligible variants/subtypes and other Basement bosses. Shared type43 branches are a separate actor scope, not ordinary Monstro behavior.
5. Recover Basement-I boss pool unlock/exclusion/selection and boss-room conditions, then enable source production selection. One enabled ordinary controller is not equivalent to the full pool.

```sh
python3 scripts/isaac-reference/extract-monstro-animations.py --check
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-monstro.py --check
cmake --build build --target deathward_monstro_tests deathward -j4
ctest --test-dir build -R '^native_monstro$' --output-on-failure
./build/deathward --smoke --scene enemy-20.0.0 --frames 300 --screenshot /tmp/monstro.png
```

All six broader parity areas remain unfinished in the [main report](../../../isaac_first_floor_implementation.md). Universal dodge, including boost and immunity, remains the user's accepted exception.
