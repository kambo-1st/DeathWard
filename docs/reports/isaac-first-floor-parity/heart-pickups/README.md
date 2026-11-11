# Blended and scared heart pickups: implemented adapter, full acceptance open

**Historical pre-revert research.** The selected current producer is [D09a ordinary red-heart clear rewards](../d09a-red-heart-rewards/README.md); other archived implementations below are not thereby restored or enabled.

Target: installed Repentance 1.7.9b, ordinary Isaac, Normal, empty inventory. This checkpoint adds the two missing heart pickup behaviors and an explicit source subtype placement API. **Source random drops and room-clear reward spawning remain disabled.** Universal dodge retains its movement boost and immunity.

## Native evidence

`scripts/isaac-reference/analyze-heart-pickups.py` reads the pinned executable and runs original x86/SSE instructions in the existing synthetic one-player fixture. [manifest.json](manifest.json) pins the executable, XML, instruction windows and scope. No original installation or source XML is modified.

- [78 blended collection states](native-blended.csv): execute `0x6bf6be` through actual `CanPickRedHearts`, `CanPickSoulHearts`, `AddHearts` and `AddSoulHearts` calls. Stop before presentation or the refusal continuation. The matrix covers missing/full red health, soul capacity boundaries, bone containers, black masks, rotten/golden/eternal overlays and broken capacity. C++ compares admission and all ten resulting health fields. Collision prechecks and item modifiers are outside this capture.
- [Four red pickup quantities](native-red-quantities.csv): the original dispatch maps ordinary 1/scared 9 to two red halves, half 2 to one and double 5 to four. These values are checked against the actual source subtype placement API.
- [Twelve player predictions](native-scared-prediction.csv): original instructions calculate `player position + 2 * player velocity - pickup position`, with supplied player/pickup state. World target enumeration is excluded.
- [180 scared-heart drive cases](native-scared-drive.csv): execute native distance gating, local RNG seeding/xorshift, jitter angle, strength, square root and normalization. Inputs include zero/near/boundary/outside distances, creation/global frame differences spanning ten-frame boundaries and unsigned seeds. The capture stops **before imported trigonometry**. C++ compares activation, force, angle and exact local RNG endpoint.
- [Six damping/free-flight cases](native-pickup-damping.csv): execute the ordinary pickup damping and common native physics endpoint with base friction/time scale 1. C++ matches velocity and position endpoints when no new steering force is applied.

- [Historical 360 motion states](native-scared-complete-motion.csv) staged damping before base physics. These are retained as synthetic calculation evidence and superseded for runtime acceptance by the ordered cases below.
- [720 correctly ordered motion states](native-scared-ordered-motion.csv) execute original UCRT steering and incoming-friction division, then base physics, then damping for the next invocation. Incoming friction 1 at birth and .965 subsequently, two velocities and supplied target/age/seed inputs are checked. Native callsite 6bb276 precedes damping 6bb472; the runtime and comparison test now follow that order.

All these are bounded native outputs, not a recording of a complete running game. The existing fixture hosts memory imports only. It does not replace native health queries, mutations, RNG or square root. The earlier pre-trigonometry group still stops at its original boundary. The complete-motion group now executes the linked original local UCRT numeric instructions, with DLL hash/imports/FPU controls in `native_math` metadata. World sounds, animations, target enumeration, collision and the complete live pickup update remain excluded. The fixture does not initialize a full Windows process or establish live loader selection.

## Enabled behavior

Baseline v9 adds `HeartKind::Blended` and `HeartKind::Scared`. A blended pickup has exactly two halves. Each half checks red capacity again; after filling one missing red half, the remaining half can become soul health. At full combined capacity it stays on the floor. At the red/soul limit it can be consumed after admitting only the available red half. This is implemented through the canonical player health fields, preserving bone/black/rotten/eternal/golden state and existing reconciliation.

A scared heart heals two red halves. Its adapter predicts the ordinary player's position two native velocity steps ahead. It applies the native drive only when squared predicted distance is below 2500 (distance 50 in native coordinates). Strength is `3 * distanceSquared / 2500`; the local seed is the creation seed multiplied by the integer age divided by 10, with zero replaced by 1. The native 5/9/7 xorshift yields a direction adjustment in approximately [-90,90) degrees. Native update damping is `.965`. The C++ adapter follows the native float argument → double precise trigonometry → float result contract. Its corrected local motion now matches 720 correctly ordered outputs using the original `_libm_sse2_cos_precise` and `_libm_sse2_sin_precise` exports from the pinned local x86 UCRT. Other math modes/arguments, live loader selection, complete world scheduling/collision and full actor acceptance remain open.

Moving scared hearts use source radius 12 at the current `.1` world conversion, update on the existing 30 Hz adapter, collide through DeathWard's movement solver and remain in their owning room. Inactive-room actors stay still. The default creation seed comes from DeathWard's reward stream; a caller can supply a source seed explicitly. Seed mapping, scheduler, native target candidates and precise grid/body collision remain unaccepted. Static heart contact/placement, collection delays, vertical physics and other existing pickup adapters are not certified by this change.

`spawnSourceHeartPickup` preserves the raw subtype identity and maps all twelve resolved source heart subtypes:

| Subtype | Pickup | Effect quantity |
| --- | --- | --- |
| 1 | Full red | 2 halves |
| 2 | Half red | 1 half |
| 3 | Soul | 2 halves |
| 4 | Eternal | 1 |
| 5 | Double red | 4 halves |
| 6 | Black | 2 halves |
| 7 | Golden | 1 overlay |
| 8 | Half soul | 1 half |
| 9 | Scared | 2 red halves, moving actor |
| 10 | Blended | 2 halves, red first then soul |
| 11 | Bone | 1 container |
| 12 | Rotten | AddRottenHearts(2), one rotten heart |

Unresolved subtype 0 and unknown values are refused, rather than replaced by another heart. The mapping is available for source reward integration; it does not enable natural generation. Existing typed heart APIs and legacy fixtures retain their prior behavior.

## Checks and reproduction

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-heart-pickups.py --check
cmake --build build --target deathward_heart_pickup_tests deathward_isaac_baseline_tests deathward -j4
ctest --test-dir build -R '^(source_heart_pickups|isaac_baseline)$' --output-on-failure
build/deathward --smoke --scene heart-pickups --frames 240 --screenshot /tmp/deathward-heart-pickups.png --mute
```

The world test checks mixed-half consumption/refusal, all twelve source subtype identities, native red quantities, special quantity validation, source update cadence, movement/range, inactive-room persistence, collection and legacy isolation. Existing baseline tests retain dodge activation, boost and immunity. The smoke scene explicitly places all twelve subtypes and enables inspection god mode; it is not a production drop or difficulty demonstration.

Unfinished: native pickup birth/delays, complete collision eligibility and grid/vertical physics, exact native scheduler/scale/global seed streams and live math loader/control-mode acceptance, other scared-heart target candidates, source room/award placement and persistence, complete unlock profiles and item/trinket/character/co-op interactions. The broader movement/projectile/heart/enemy-boss/item/room-reward goal remains open in all six areas.

The [v11 producer report](../coin-producers/README.md) records the ordering correction, shared coin birth/appearance integration and the latest broad verification.
