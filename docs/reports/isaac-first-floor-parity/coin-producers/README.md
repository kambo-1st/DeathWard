# Source coin producers and appearance gates

Target: installed Repentance 1.7.9b, ordinary Isaac/Normal. Baseline v11 connects golden-heart and Midas drops to the shared source coin actors. **General native room-clear rewards, ordinary enemy drops and source heart generation are still unfinished.** Universal dodge retains its movement boost and immunity.

## Enabled gameplay

Golden-heart loss now selects 3–8 individual coin requests per burst. The native spawn call requests **subtype 0**, so the provided spawn seed resolves a coin subtype once through the existing source calculator. Midas death requests **explicit penny subtype 1**, with its existing ordinary 1–3 count and once-only/summoned-offspring guards. The two producers retain their different RNG draw roles, velocities, spawn offsets and identities. Golden emission uses a speed factor `.33 + .66 * unitWord` multiplied by its five-unit direction; Midas uses a unit direction multiplied by `3 * unitWord`. The words still come from DeathWard's combat stream; the native global stream and initialization are not accepted.

Requests keep their selected subtype, seed, native velocity and owning room until actor capacity and legal placement are available. They are not stacked into a legacy money pile, discarded or rerolled on retry. A dead Midas owner cannot repay or remove its retained payout. Admission starts the appearance state; waiting requests do not animate or grant money. Existing custom normal-enemy drops and floor money piles retain their older adapter and remain differences.

Born coins use the preserved appearance frame/event metadata and the executed native collision gate. Ordinary `Appear` is 33 frames with DropSound at 23; sticky nickel appearance is 19/9. Golden-penny `Reappear` is 24/16. The collision gate activates at DropSound while a recognized appearance is playing, with animation completion as a fallback. These are source invocation/frame values through the existing 30 Hz adapter, not measured native wall-clock seconds. Placed/inspection pickups can start idle; this is distinct from a newly emitted actor.

Moving coins carry temporary friction: the first base-physics invocation consumes incoming friction 1; subsequent ordinary invocations consume `.965`. Base physics resets friction, then pickup damping prepares the following invocation. Native velocity is converted through the existing `.1` world scale and DeathWard's movement/room solver. Exact native grid/body collision, bounce rules, vertical physics, timing, position searches and seed initialization remain open.

Golden-heart subtype resolution uses explicit `SourcePickupGates` carried across floors. The represented gates default off; this is **not a verified complete fresh-save or unlocked profile**. The optional unlock-profile question remains pending. Source item/trinket/character/co-op overrides and complete eligibility remain unfinished.

## Independent native evidence

`analyze-coin-producers.py` executes original game instructions with the pinned local x86 UCRT numeric exports. [manifest.json](manifest.json) records hashes, boundaries and exclusions.

- [40 appearance collision cases](native-appearance-gates.csv): actual animation-name/playing/event queries and the pickup collision gate, with supplied playing/event state and initial collision class. Sound and Play(Idle) are the only hosted presentation boundaries.
- [451 frame/event states](native-appearance-timelines.csv): original layer frame advance, floor conversion, trigger-mask calculation and collision gate use minimal definitions parsed from the preserved coin ANM2 metadata. C++ compares frame, playing/collision state and accumulated DropSound calls. Render layers and the complete sprite/OS loader are excluded; hosted Play(Idle) resets the minimal idle state.
- [128 emission cases](native-emissions.csv): original unsigned-word conversion, speed, linked precise trigonometry, vector multiplication and spawn-argument construction run with supplied speed/direction words. Spawn coordinates and subtype arguments come from the native instructions. Global RNG calls and room ray queries are not executed by this fixture.

The actor queue integration tests separately check capacity failure/recovery without rerolls or duplicate value, complete eventual collection, Midas once-only payout after owner cleanup, room ownership and randomized golden-heart coin types. Default balance constants and the shared regular-enemy health multiplier are unchanged.

## Correction to the earlier scared-heart fixture

The earlier `native-scared-complete-motion.csv` staged pickup damping before base physics. It matched that synthetic sequence, but **the sequence was not the native update order**. The preserved callsite at `0x6bb276` calls base entity update before pickup damping at `0x6bb472`. The prior 360 states are retained as historical calculation evidence and superseded for runtime acceptance.

The runtime now carries incoming friction and divides steering force by that friction before base physics. [720 correctly ordered native states](../heart-pickups/native-scared-ordered-motion.csv) cover birth friction 1 and ordinary subsequent friction `.965`, with two incoming velocities and supplied predicted targets/ages/seeds. The updated C++ kernel matches velocity, position and next-friction outputs. This corrects the prior first-tick/steering discrepancy; it does not certify complete live scared-heart behavior or world collision.

## Reproduction

```sh
python3 scripts/isaac-reference/extract-coin-animations.py --producer-coins --check
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-coin-producers.py --check
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-heart-pickups.py --check
cmake --build build --target deathward_coin_producer_tests deathward_heart_pickup_tests deathward_source_coin_tests deathward_isaac_baseline_tests deathward -j4
ctest --test-dir build -R '^(source_coin_producers|source_heart_pickups|source_coins|isaac_baseline)$' --output-on-failure
build/deathward --smoke --scene coin-producers --frames 240 --screenshot /tmp/deathward-coin-producers.png --mute
```

The inspection triggers golden-heart loss and an ordinary Midas death through gameplay paths, starts with two available actor slots and releases capacity at frame 60. At this checkpoint it selected six drops and ended with three golden-heart actors, three Midas actors and no pending requests. It preserves player HP 4 after the setup hits and uses inspection god mode afterwards. That is integration/rendering evidence, not a native timing, difficulty or performance acceptance claim.

Unfinished: native global/room RNG and child initialization, exact grid/vertical/body/contact physics and eligibility, complete appearance/scheduler/loader behavior, all modifiers/characters/co-op, every per-actor Midas eligibility/suppression case, complete unlock profiles, active charge slots, troll/giga bombs and other reward families/production rules. All six original parity areas remain open.
