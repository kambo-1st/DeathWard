# Room rewards: native calculations, production generation unfinished

Target: installed Repentance 1.7.9b, ordinary Isaac, Normal, an ordinary room and empty inventory. [SourceRoomRewards.hpp](../../../../src/combat/SourceRoomRewards.hpp) now implements source room-award selection and scoped heart/coin/key/bomb subtype selection. **These calculations are not connected to production room-clear spawning yet.** Existing DeathWard loot generation remains an open difference; no source reward or whole-room acceptance is claimed.

## Verified native execution

The Lua `SpawnClearAward` binding identifies native function `0x7b8b10`. Its ordinary selection call enters `0x7b82b0`; the complete ordinary selector executes in the fixture. The preserved normal-clear and explicit TriggerClear callsites also show the players callback before award spawning, after a guard on descriptor flag bit7; this checkpoint does not assign a complete lifecycle meaning to that bit. This supports the existing rotten-heart room-clear producer's callback relationship, while full callback lifecycle/charge behavior still needs acceptance.

| Independent evidence | Cases | Scope |
| --- | ---: | --- |
| [Room-award selection](native-awards.csv) | 2,196 | Whole native selector with supplied nonzero seed, Luck−3/0/1/5/10/20, and both values of the prevent-none input. C++ matches the selected variant **and exact RNG state afterward**. |
| [Pickup subtype selection](native-pickups.csv) | 4,144 | Whole native resolver `0x6b48b0`, supplied pickup seed and variant10/20/30/40, input subtype0, caller flags1/0, supplied ordinary room/type1. Other game fields use the explicit synthetic fixture defaults. Both settings of the represented achievement gates are captured. |

The samples use varied full-width32-bit seeds plus edge inputs and first-roll values around every native reward-band boundary. Observed results include all ten ordinary award outcomes and all12 heart subtypes, six generated coin subtypes, three generated key subtypes and six generated bomb subtypes. These are observed fixture outcomes, not a claim that every modifier, profile, rare branch or pickup behavior is accepted.

The original RNG, numerical operations, weighted picker, item/trinket queries and resolver branches execute without replacements. Subtype selection uses native dynamic arrays; the fixture hosts CRT `malloc`, `free`, `memcpy`, `memmove` and `memset` with documented memory semantics. The captured matrix actually uses allocation, move and free. Low-memory accesses are rejected except native `FS:[0]` exception bookkeeping. No numeric helper or game query is intercepted. [manifest.json](manifest.json) pins executable/windows, exact gate-byte inputs and import endpoints/counts. The original game installation remains read only.

The gate fixtures are synthetic inputs: ten specific achievement bytes are all disabled or all enabled. **They do not establish a complete fresh-save or fully unlocked profile.** The user's unlock-profile preference remains a separate decision; the formulas retain explicit gate inputs.

## Implemented calculation scope

The room award RNG uses native shifts5/9/7. Its float multiplier is the preserved value below `2^-32`, distinct from the ordinary tear/blue-fly random conversion. Both initial draws occur even at zero Luck; aggregate ordinary Luck is clamped to0–10. The unmodified reward bands and subsequent RNG draws are retained. In particular, the empty-inventory coin band ends at0.45; the0.45–0.50 item-dependent branch falls through to hearts without its modifier. The checks for the battery-trinket opportunity and sack conversion still consume their native draws when the corresponding trinket is absent.

The selector returns these native pickup variants:

| Variant | Family |
| ---: | --- |
| 0 | No award |
| 10 | Heart |
| 20 | Coin |
| 30 | Key |
| 40 | Bomb |
| 50 | Chest |
| 69 | Grab bag |
| 70 | Pill |
| 300 | Card |
| 350 | Trinket |

The separate pickup resolver preserves heart replacement order, achievement gates, coin rarity/overwrite rules, copied-RNG weighted key selection and bomb/troll conversion branches for the scoped ordinary inputs. A key's native weighted entries distinguish the charged-key gate. The C++ result explicitly marks other families unresolved; it does not silently replace them with an ordinary consumable. A selected bomb subtype may be a troll actor rather than collectible ammunition, so family selection alone is insufficient for spawning.

`native_room_awards` compares every captured result. The **17 selected native/baseline/status/boss suites pass** with this new test included. This checkpoint changes calculation code and evidence, not enabled gameplay; the v7 application binary is unchanged. No new render, combat or performance acceptance is implied. Universal dodge remains untouched.

## Required next work

1. Connect native award decisions to a once-only room-clear transaction with the correct room/award seed mapping, spawn RNG draw, placement and persistence. The selector's returned RNG state is not the final state of the complete spawning routine.
2. Complete chest/sack contents, pill/card/trinket selection and interactions, troll/mega/golden bomb actors, golden/charged resources and blended/scared-heart rules. Existing typed-health collection APIs do not supply all these actor contracts.
3. Implement physical pickup birth, animation/delay, motion, collision, collection and refused-pickup rules. Preserve source family/subtype identity through capacity pressure and room transitions.
4. Establish the intended complete unlock profile and native item/trinket/difficulty/special-room modifiers. A toggled byte group does not substitute for a real profile or item implementation.
5. Replace the custom starting-floor coin piles and generic enemy-money drops together with a verified production reward pipeline. Verify special-room/boss/shop/economy rules and matched native floor outcomes.

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-room-awards.py --check
cmake --build build --target deathward_room_award_tests -j4
ctest --test-dir build -R '^native_room_awards$' --output-on-failure
```

All six broad parity areas remain unfinished in the [main progress report](../../../isaac_first_floor_implementation.md). The verified calculation scope must remain distinct from enabled spawning and full acceptance.
