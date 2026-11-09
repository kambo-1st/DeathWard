# Private Spider burst/idle and Pooter wandering comparison

The corrected source-room review now applies ordinary Spider85.0 and Pooter14.0 AI at the beginning of their30Hz movement intervals and uses the pinned Pooter edge thresholds. **16 native Spider idle gates,48 Spider movement states and144 Pooter wandering states pass actual Simulation comparisons.** The192 movement states pass at30/60/120Hz physics partitions. These changes are private-review candidates; production defaults, source forces, HP, player pace, firing controls and universal dodge remain unchanged. Full enemy acceptance is unfinished.

## Native evidence and supplied boundaries

`capture-spider-pooter-movement.py` verifies the installed Repentance1.7.9b executable hash and preserved XML friction1 for both bodies. It executes original counter, stop/impulse, pursuit, cooldown, wander/edge, AddVelocity/normalization and base-physics instructions without patched code or stubbed helpers. Source instruction windows, hashes and CSV states are retained here.

Spider fixtures supply initialized ordinary state, starting momentum/counter and a committed destination. They cover idle damping, a far burst, arrival within14 source coordinates and a low-speed burst whose decremented counter turns negative. Original code clears the target but still applies the final impulse on a stopping update. The16 idle-counter probes execute the source threshold: the previous counter must exceed13, so selection becomes due on the15th ordinary ready update. Actual Simulation checks use a nearby clear target to make that gate deterministic. Full acquisition RNG, target-helper exceptions, prediction/clamp and navigation are not executed or certified by these fixtures.

Pooter fixtures supply a normal target outside attack range, initial momentum/wander, global frame1..24 and cooldown0 or35. Six cases cover center, upper/lower/left/right edges and cooldown damping. **Random pursuit outcomes and jitter directions come from an explicitly supplied DeathWard SplitMix64 stream, seed123456; this is not native Isaac RNG replay or distribution acceptance.** The actual Simulation must consume the identical stream state at every comparison, preventing incidental random calls from silently invalidating the fixture. Native third-frame cadence executes; fourth-frame jitter enters after the supplied random direction. Attacks, native actor initialization/morphs/items/statuses/champions and live wall-clock scheduling are excluded.

Each native comparison records the state after AI and base physics for a supplied ordinary update. Source incoming friction is consumed by base physics; stored pre-physics outgoing velocity must not be confused with realized displacement. These fixtures compare realized state. The complete NPC wrapper and live cadence remain outside acceptance.

## Demonstrated differences and private corrections

The old review accumulated time before running Spider/Pooter AI. At the game's60Hz step, its first half of an NPC interval could move using the previous velocity before the new impulse arrived. The private candidate applies the controller at the start, then advances the resulting realized velocity through that interval. Default controllers retain their existing end scheduling. The new opt-in is enabled only in the corrected source-room review and scoped to ordinary85.0/14.0; Fly/Big Spider/other variants are not silently selected.

The previous Pooter edge margin was3 world units on all sides. Original ordinary code uses these fixed thresholds:

| Source condition | Geometric review threshold |
| --- | --- |
| x<80 | x<1 |
| x>540 | x>24 |
| y<230 | z<4.5 |
| y>420 | z>14 |

Those source values are converted using native40-coordinate tiles to world2 tiles, with native top-left60/140. The correction is restricted to the26×14 review room. Other room shapes/generated arenas keep their documented adaptation. The source edge force.06, jitter.6/retention.4, third-frame retention.6, pursuit.7 and cooldown damping.8/.7 are unchanged. Pooter's existing safety cap remains and is not reached by these fixtures.

The legacy comparison reproducibly fails: maximum Spider position error.224508 world units; Pooter position error.319573 and wander-vector error.162816. The corrected60Hz results are approximately.00000668 Spider position and.00003089 Pooter position, with exact recorded wander vectors. At120Hz the position errors stay below.0001 world units. The comparison bounds remain.002 position/.005 velocity and.0001 wander; no force/threshold was tuned to fit them.

## Fixture corrections and regression checks

The first Spider gate fixture omitted construction of its optional controller runtime; this was corrected with explicit initialization before comparisons. Its failed diagnostic is retained. An initial Pooter edge experiment also drove a collision-free native reference outward into DeathWard's physical wall bounds. The resulting clipping was a fixture mismatch. The final right/bottom cases give both sides the same inward initial velocity, preserving edge-force coverage while isolating movement arithmetic. The original CSV/log are retained as a boundary confound. **No collision rule was bypassed in interactive gameplay, and these results do not certify native wall collision.**

The first focused CTest pass had eight passing suites and one failing old Fly/Pooter assertion. That assertion checked whether a player bullet hit dung after15 ticks. An isolated scene with no enemies reproduced health4 at15 ticks and impact/health2 at17 ticks, with the private movement flag both off and on. The test now waits for impact within a bounded60-tick window; its damage/destruction assertions remain. No projectile behavior was changed. The targeted rerun passes. All **nine unique focused suites** are therefore covered and pass: three new motion partitions, Spider family, buzzing flies, status effects, strict Gaper trajectories, Gaper partition stress and source-room review. Initial and final logs preserve that distinction.

Both selected review bodies also pass60-frame rendered launch/capture checks. Actual Game keyboard/native-player checks at30/60/144 render FPS and click arrival pass. Render captures are smoke checks, not user visual acceptance or graphics/performance approval. Full damage/HP pressure acceptance remains held.

## Run and next steps

```sh
# Spider burst/idle candidate
build/deathward_damage_health_review --source-room-review --body 8
# Pooter wandering candidate
build/deathward_damage_health_review --source-room-review --body 6
# Deterministic research/comparisons
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-spider-pooter-movement.py --check
ctest --test-dir build -R '^(spider_pooter_movement(_30hz|_120hz)?|spider_family|buzzing_flies|first_floor_status_effects|gaper_trajectories(_substeps)?|source_room_review)$' --output-on-failure
```

Use1/2 for previous/corrected movement, F8 to reset and Enter after death. Eight-direction firing and dodge remain available. Pooter attacks are still the existing adapted behavior; this checkpoint verifies movement, not its projectile speed/range/cadence.

**Next:** verify enemy projectile timing/speed, beginning with Pooter/Horf, then perform a human pressure review. Still unfinished: full Spider acquisition/RNG/prediction/clamp/status behavior; native Pooter RNG, global-frame/live scheduling and special cases; native terrain/body collision and source-radius policy; champion/variant/lifecycle coverage; human acceptance, production rollout and HP encounter acceptance. Gaper's wider mask/cache/contact/live behavior also remains open. No complete first-floor or actor parity is claimed.
