# Native room selection and placement — first integrated checkpoint

Selected explicitly after the full/half layout-heart delivery. That previous delivery, together with D08 and the D09a clear-reward/timing work, is committed as **b42ef80f**. This continuation is enabled in the main game and developer-verified. On 2026-11-12 the user positively acknowledged the interactive seed56 handoff and requested its commit. That scoped acknowledgment does not establish full native room/placement acceptance.

## What changed in gameplay

**SOURCE LAYOUTS** now filters the retained Basement pool against the canyon room's connected doors, uses the executed native weighted selection rule, favors exact door-mask matches using the native second draw, and reduces the selected template's weight to one tenth (minimum 1e-7) for subsequent eligible rooms in that floor generation. Weights reset with explicit floor regeneration. Empty heart layers remain in the pool; incompatible templates are excluded without rerolling into hearts.

Spawn-stack selection now uses the native 2/7/7 xorshift sequence, native float conversion and cumulative-weight comparison. It advances for **every original source spawn slot**, including omitted enemies/grid obstacles, rather than advancing only for heart slots. The source ordinal and total spawn count are preserved in the generated data. Mixed heart/bomb/sack alternatives retain their original choices; unsupported outcomes are still not substituted. The selected source slot seed is passed to the existing heart subtype adapter; the complete native spawn factory has not been accepted.

This changes which rooms contain hearts for a given DeathWard seed. It does not change the expedition graph, canyon visuals/size, player/enemy pace, shooting, HP, dodge, D08's fixed formation or independent clear rewards. The current floor changes only on its existing regeneration boundary, including **Apply map changes**. OFF and FULL + HALF TEST retain their behavior. No new user tuning parameter was introduced.

Preset **schema14** records the new selection policy. Schemas1–13 still load and migrate, preserving all existing settings and the layout mode. Map changes remain staged; exports and next-expedition defaults include the selected mode. The user's original preset and backup remain byte-identical at SHA256 `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`.

## Short playable check

```sh
build/deathward --expedition --seed 56 --mute --save /home/kambo/.local/share/deathward/reviews/native-room-selection/campaign.save --balance-preset docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json
```

1. Reach **displayed room7**. A full and a half heart are present before clearing it, selected from the heart layer of source template **1.91.0**. This seed/room is verified through the actual Simulation; the main executable's CLI/preset path is smoke-tested.
2. With missing red health, collect one, leave and return. It must remain consumed.
3. In TUNING → REWARDS → ROOM LAYOUTS, OFF stages a change; **Apply map changes** explicitly resets the current floor and removes the layout layer. FULL + HALF TEST remains available for a convenient forced pair.

The source template's enclosing rocks are **not imported yet**. This witness checks the integrated selection and pickup path; it is not an accepted reconstruction of that source room. Old seed33/room6 witness instructions apply to commit b42ef80f, not this selector.

## Evidence and exact boundary

Installed Repentance1.7.9b executable SHA256 `04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`. The pinned Basement STB and generated extraction are recorded in [source-layouts.json](../d09a-room-hearts/source-layouts.json). REPENTOGON's [RoomConfig signatures](https://github.com/TeamREPENTOGON/REPENTOGON/blob/main/libzhl/functions/RoomConfig.zhl) were used to locate functions; the results below come from the installed executable, not inferred documentation or another executable version.

[The fixture](../../../../scripts/isaac-reference/analyze-room-selection.py) executes original x86/SSE instructions in Unicorn2.1.4 with supplied room records, requests and preallocated equivalent vector storage. No selection/RNG helper is replaced or instruction patched. Native numeric filters execute from 0x7e78a4 to their accept/reject endpoints; the ordinary selector runs from 0x7e73c8 through selection and optional reduction, using the native door-nonempty helper. Special wrapper modes and the G-Fuel flag query are outside this fixture. The native Room::Init slot step at 0x7b201a executes its actual weighted-stack helper0x7e7c20 and computes the source grid index. [Manifest and instruction hashes](manifest.json), [numeric filters](native-filters.csv), [weighted selections](native-selections.csv), [spawn decisions](native-spawns.csv).

- **560 numeric-filter cases**: type, shape/wildcard, unsigned variant bounds, inclusive difficulty bounds, subtype/wildcard and all16 ordinary door masks.
- **1,024 selection cases**: native choices and exact weight updates over all16 door requests, signed-conversion boundaries and repeated selections with persistent reduced weights.
- **1,472 spawn cases**: all23 retained heart-containing stacks, mixed alternatives, native RNG endpoints and source grid indices. The native source-loop listing shows one draw per original stack; zero-heart slots are retained through their ordinals/count, not instantiated in DeathWard.

The production C++ consumers match every recorded result. Five focused CTest suites pass (reference, room-heart gameplay, preset contract, D08 and clear-reward regression); an additional gameplay check verifies every selected template allows its actual canyon connections. Actual Game/Renderer checks pass for mouse/keyboard, staging, Apply, export/load/rejection, collection/revisit, floors/retry and fresh-session persistence. Separate main-executable launches verify schema5 and schema13 migration with165% zoom. [Validation](validation.json), [tests](tests.log), [Game/Renderer](input.log), [native reproducibility](native-check.log).

Reproduce the native fixtures with `PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-room-selection.py --check` (pefile, capstone, unicorn2.1.4 required); reproduce extraction with `python3 scripts/isaac-reference/extract-room-heart-layouts.py --check`.

## Unfinished — next selected work

**This is not full native floor selection or physical placement parity.** Remaining inputs/adaptations are explicit:

- The pool is still433 normal positive-weight13×7 Basement templates at difficulty1–5. Native floor caller difficulty/variant/shape/door requests, stage/alternate-floor pools, unlock/special-mode eligibility, generation order and persistent weight lifetime remain unverified. Door masks come from the retained canyon connections; seeds come from a separate DW stream. Native seed-text compatibility is not claimed.
- The heart layer is still separate from the enemies and grid. The uniform dynamic-room cell adapter and nearest-reachable-floor fallback remain. They can erase native access restrictions, such as hearts enclosed by rocks. Native pickup factory mutations, physical displacement/collision, room-entry scheduling and matched live behavior remain unaccepted.

**Next:** import the complete obstacle/access arrangement for one selected heart-bearing source room in the ordinary game, preserving canyon presentation and dynamic sizing, and compare blocked/access-limited placement against Isaac. Then resolve native caller/pool/descriptor generation before expanding coverage. Human review, other heart families/producers and later reward deliveries remain open; coins remain unselected.
