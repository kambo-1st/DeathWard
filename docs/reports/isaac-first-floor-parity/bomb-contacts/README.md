# Ordinary bomb contact: native response connected, full actor acceptance open

Target: installed Repentance 1.7.9b, ordinary Isaac and inventory bomb 4.0.0. This is the `isaac-baseline-v13` checkpoint. Graphics and universal dodge, including its movement boost and immunity, remain accepted exceptions.

## Executed evidence

`scripts/isaac-reference/analyze-bomb-contacts.py` executes the **whole native circular-body dispatcher/response**, with the actual player and bomb vtables and both original collision handlers. Native callback dispatch executes against an explicitly disabled Lua callback registry. Item, flag, mass and grid queries, SSE square root and contact calculations execute unchanged. No gameplay calculation/query is replaced. [manifest.json](manifest.json) pins the executable, XML and instruction windows.

[native-contacts.csv](native-contacts.csv) has **6,552 contacts**: two origins, thirteen relative offsets, seven player velocities, three bomb velocities, three grace counters, two grid-probe configurations and both argument orders. It covers separation, exact touching, deep overlap, nearly coincident centers, fast-separation correction and placement grace. Source XML supplies radii 10/16 and masses 5/6. Both body scales are 1 and collision classes 4; other classes, shapes, items, statuses and special rooms are outside this fixture.

The grid inputs are an empty sample list and one deliberately supplied far-offset sample inside a synthetic solid grid. These execute the real clear/rejected query branches. They **do not establish native actor grid sample positions or production room geometry**. An initial out-of-grid probe was found to be ignored by the native query and was corrected before accepting the fixture; out-of-grid is not assumed to mean blocked.

The original ordinary dispatcher selects the specialized circle solver, not its general capsule/shape solver. For an admitted contact, the bomb handler first adds **0.4 times player velocity**. The shared solver applies mass redistribution, overlap correction and its fast-separation branch. The player's displacement/velocity share receives the native additional factor of 0.5. A rejected player grid probe transfers the displacement share to the bomb. Nearly coincident centers retain the callback velocity change while skipping the normal redistribution.

The bomb starts with placement grace **4**. A positive grace counter blocks physical response and refreshes to 4 on contact. [native-grace-decrement.csv](native-grace-decrement.csv) contains nine executed decrement cases. Once the player stays apart for four actor updates, returning contact can push the bomb. These are update counts; native elapsed time remains unaccepted.

The C++ comparison checks all gates/counters and all eight resulting position/velocity fields per case. **All 52,416 numeric outputs equal the captured native floats; maximum absolute difference is zero** in this matrix. This is numeric equality, not a claim about every bit pattern or every possible input. Nonfinite comparison values fail the test. See [kernel-test.log](kernel-test.log).

## Enabled gameplay

Ordinary baseline inventory bombs now decrement grace and resolve grounded player contacts at the current source actor clock. Separation releases placement grace; returning motion pushes the bomb and preserves its fuse and inventory. The old ballistic kick/lift remains separate for legacy charges. World positions use the existing .1 conversion; player/bomb movement and the rejected-grid input use the current arena adapter. Different Canyon ground surfaces and launched players are excluded from this grounded adapter. Native global update/contact ordering, actual grid/collision sampling and complete vertical behavior remain open.

**All 23 selected suites pass**, including the 6,552 native contacts, bomb lifecycle/queue/stock checks, actual grace release and pushing, 72 free-motion states, retained dodge activation/boost/immunity, source resources/health/rewards, status effects, boss components and legacy contracts. The application builds. [validation.json](validation.json) records the checkpoint and artifacts.

The viewed [65-frame push inspection](push.png), with god mode off, starts by keeping the player apart. Grace reaches zero by frame 12. Grounded pushing moves the bomb **9.03067 world units** by frame 65; native speed is 5.55193, vertical velocity is zero, stock remains 2 after starting with 3, and one bomb remains before detonation. The fuse continues throughout. A separate viewed [120-frame self-blast inspection](after.png) confirms six→four half-hearts, one explosion, stock 2 and no remaining bomb actor. These show the current adapter, not matched native live play.

```sh
build/deathward --smoke --scene bomb-contacts --theme canyon --frames 65 \
  --save /tmp/deathward-bomb-contact-inspection-save.json \
  --screenshot /tmp/deathward-bomb-contact-inspection.png
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-bomb-contacts.py --check
ctest --test-dir build -R '^(native_bomb_contacts|native_player_bombs)$' --output-on-failure
```

## Troll conversion research, not enabled actors

[native-troll-conversion-intents.csv](native-troll-conversion-intents.csv) records **42 bounded native pickup-update outcomes** for seven bomb subtypes and six supplied global MT seeds. Original global MT initialization/next-word code executes. The fixture stops before the Spawn API, so it does not instantiate or remove an actor.

| Pickup subtype | Native spawn intent |
| --- | --- |
| Troll 3 | Bomb entity 4, variant 3, subtype 0 |
| Super troll 5 | Bomb entity 4, variant 4, subtype 0 |
| Golden troll 6 | Bomb entity 4, variant 18, subtype 0 |
| Ordinary 1, double 2, golden resource 4, giga 7 | No conversion in this branch |

The three converted types preserve pickup position, request **zero velocity despite nonzero incoming pickup velocity**, have no parent and consume one new global RNG word for Spawn's seed. They do not reuse the pickup's InitSeed in this branch. Post-spawn removal is preserved in the disassembly; it was not executed by this intent capture. Giga behavior cannot be inferred from its absence in this branch. Full native global seed mapping and troll appearance/update/chasing/repetition/explosion lifecycle still require work. Their resource subtypes remain refused in gameplay until actors are implemented.

**Unfinished:** matched live scheduling/contact order and clock; calibrated source room grid and body samples; other shapes/status/item/character flags; bomb–enemy and bomb–bomb contacts; complete explosion recipients/flags/knockback and room persistence; troll/super/golden troll/giga actor behavior and resource conversion; production source rewards and all six broad parity acceptance areas. No broad area is fully accepted by this checkpoint.
