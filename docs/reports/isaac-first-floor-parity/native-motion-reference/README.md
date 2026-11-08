# Executed native movement reference and private player adapter

The ordinary player movement recurrence is implemented in `src/combat/reference/NativeMotion.hpp` and enabled explicitly in the private review through `Simulation::nativePlayerMovement`. Normal expeditions retain the accepted responsive movement. No HP, attack, default pace or source enemy force has been retuned.

## What is sourced and checked

The capture reads the installed Repentance 1.7.9b executable, SHA256 `04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`. It executes original x86/SSE instructions with original square-root/vector helpers. No native helper is stubbed and no instructions or installed files are patched. Actor state, inputs, NPC destinations and path outcomes are supplied fixture boundaries.

The baseline Speed write at **0x722b66** stores float **1.0** to `Player+0x14ac`. The capture executes this original write and records its value. This verifies that baseline initialization instruction, not the entire character/item cache recomputation.

**1,840 executed bounded states in ten sequences** check native position, realized velocity, outgoing velocity and current friction. Player cases cover press/release, diagonals, reversal, turning, analog input and Speed .8/2. Gaper cases cover supplied long moving paths followed by arrival and blockage. Spider has a supplied target/idle sequence: its selection, counter and RNG behavior are not executed or accepted by that fixture.

Native base physics consumes current friction and moves incoming velocity before steering prepares the next invocation. Outgoing NPC velocity must not be mistaken for realized displacement: Gaper steering divides its impulse by current friction, which the next physics invocation consumes. The reference retains both quantities explicitly. At Speed1 the bounded player settles at approximately **4.41423845 native coordinates per invocation**; ordinary/awakened Gaper long-path realized steps settle at approximately **3.32/4.8 native coordinates per NPC invocation**. These are per-invocation measurements, not a claim of live wall-clock speed.

**2,760 actual Simulation states** match all seven player sequences at two explicit spatial transforms. This verifies native acceleration, coasting, turns, positions and next-step velocities through the real player update. The native recurrence has no accepted-pace constant. The private adapter feeds realized arena movement back into steering; native collider equivalence is not established by these open-space tests. Universal dodge retains its absolute boost, immunity logic and reset behavior; it remains a deliberate DeathWard feature. Eight-direction firing is preserved.

Six focused CTest suites pass (`tests.log`). The actual Game keyboard path matches the reference at 30/60/144 render FPS (`game-input.csv`). At 144 FPS the held-input interval delivered 89 fixed ticks instead of 90; expected distances use the actual invocation count. This verifies per-invocation behavior through Game input, not equal live elapsed-time scheduling. The source curve includes stopping inertia; normal gameplay still stops immediately by the earlier accepted choice.

## Interactive review and spatial limitation

Run:

```sh
build/deathward_damage_health_review --native-player-reference --body 2
```

**3** toggles native/responsive player curves. **1/2** compare previous/corrected enemy conversion, **[ / ]** selects an enemy, **T** switches single enemy/encounter, **F8** restarts and **Enter** restarts after death. HP/damage remain current production values in both movement modes. See `launch.json` for the copied executable; it retains development asset dependencies on this checkout.

**The review's coordinate scale is still anchored to the previously accepted player pace.** The new native player recurrence is independently checked in native coordinates, but this display is not an independently verified source room-crossing speed. The room shape, player/enemy colliders and NPC projectiles remain adapted. Do not ask the user to infer native base speed by selecting arbitrary sliders, and do not label this window a complete 1:1 Isaac port. `review.png` was captured and inspected.

Reproduce the original-code evidence with:

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-motion-reference.py --check
ctest --test-dir build -R '^(native_motion_reference|native_player_adapter)$' --output-on-failure
build/deathward_damage_health_review --native-player-reference --verify --measurements /tmp/native-game-input.csv
```

Requires the pinned installed executable, pefile, capstone and Unicorn2.1.4. No live Isaac process is started by the capture.

Still unfinished: complete Player/NPC branch reachability and initialization, independent live scheduling/elapsed-time capture, source room and collider geometry, full NPC integration/steering ordering in DeathWard, native Spider/Pooter target and pause sequences, enemy projectiles and wider roster coverage. Production rollout and live HP acceptance remain on hold. This checkpoint proves bounded native arithmetic and an opt-in ordinary-player adapter; it does not certify complete enemy AI or a full 1:1 expedition.

## Subsequent live timing verification

[The room/timing follow-up](../room-scale-timing/README.md) now independently verifies the normal520×280 room interior and ordinary horizontal base-Isaac motion at approximately60 player steps versus30 world updates per second. That supersedes the earlier open ordinary horizontal timing gate within the recorded live scope. The review spatial scale itself has not been replaced; full actor reachability, collision/stopping and other states remain unaccepted.
