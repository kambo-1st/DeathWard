# D09c — ordinary keys in the main game

Selected 2026-11-15 after accepted preplaced coins, committed as `dadbc92b`. **Keys are enabled, developer-verified and accepted in the scoped human playtest on 2026-11-15 ("cool, it works!").** This delivery is committed as `b466b5a3`. The automatic bulk parity effort remains paused.

## Playable result

Ordinary opening-floor clear rewards can now produce keys through the existing single native award roll. Chest keys use the same ordinary-key actor; the chest loot table is unchanged. Single keys add1, double/key-ring actors add2, clipped at99; full inventory leaves a pickup available. Collection happens once, with the existing pickup sound. Collected actors never return on revisit.

Complete source **1.214.0** adds18 plain rocks and2 key slots when the existing native selector chooses it in a compatible canyon room. Original source cells and descriptor/slot seeds are preserved, including the rock RNG steps. Both keys remain inside their rock enclosures until ordinary DeathWard dynamite opens access. No forced frequency, relocated keys or unrelated enemies/coins are added to this arrangement. Mandatory legacy key progression is retained.

**TUNING → REWARDS → AFTER CLEAR → KEYS** changes future first-clear admission. Existing actors and pending outcomes stay fixed. **ROOM LAYOUTS → SOURCE/OFF** remains staged until Apply. Schema23 exports/loads/remembers the key switch and migrates1–22 enabled, retaining previous map/view/shooting settings. Apply can regenerate an explored floor and retains player/build/inventory/expedition identity; it moves the player to accessible floor if a restored enclosure would trap them. Retry and later floors retain the selected policy. Configuration persistence is separate from unfinished gameplay save/restore.

## New model

Found the owned Synty Polygon Generic **SM_Gen_Prop_Key_01** under `/mnt/f/UNITY/My project (1)/Assets/Synty/PolygonGeneric`. It now replaces primitive key visuals for ordinary pickups, chest keys and existing mandatory keys.

The164-triangle mesh retains source proportions, UVs and the prefab's `Generic_01_A` albedo. It is centered and normalized to a1-unit long dimension, then uses the ordinary scene mesh lighting/shadow material path in both depth and color passes. Double keys display two copies. Native/web asset manifests include the GLB. [Asset provenance](../../../../assets/pickups/key/manifest.json), [bake script](../../../../scripts/bake_key.py), [room screenshot](room.png), [collected screenshot](collected.png).

## Source evidence and boundaries

Target: preserved installed Repentance1.7.9b. The key resolver's copied-RNG table has weight49 single, weight1 golden, weight1 charged (single when the represented charged gate is off). **All1036 preserved native key choices match**, alongside2196 shared award choices/RNG endpoints and existing heart/coin matrices. The16 preserved admitted single/double collection cases confirm quantity/clamp arithmetic. [Evidence hashes and scope](source-evidence.json).

Golden subtype2 and charged subtype4 remain unsupported outcomes without rerolling. Ordinary1 and double/key-ring3 are the supported actors; the enabled random-key profile does not generate key rings. The earlier collection capture excludes collision eligibility prechecks. Our99-cap refusal, planar proximity and line-of-sight remain explicit adapters, not claimed complete native collision acceptance.

Pinned single/key-ring ANM2 metadata is **Appear33 / Drop25 / Collect12**, reusing the existing active-room30Hz ordinary pickup state machine. Clear/chest births wait; preplaced keys start idle. Inactive rooms and pause freeze the phase. [Animation manifest](animations/manifest.json). No Isaac sprite artwork was imported.

## Verification

Eight focused suites pass across [initial regression results](initial-tests.log) and the [final selected results](selected-tests.log): presets, native reward reference, keys, key layout, chest gameplay/layout and coin gameplay/layout. The initial largest-size fixture used a seed that did not naturally select214; it was replaced with a naturally selected witness, without changing generation to force the room.

The full actual Simulation verifies both enclosed keys, real dynamite breaches, physically clear click routes and once-only collection at the supported smallest size (seed1493,75%,5–5), accepted size (seed285,110%,7–9), and largest size (seed1932,150%,10–10). Capacity deferral, original identities, OFF/test exclusions, Apply, floor policy, timing at30/60/120Hz, caps and unsupported golden outcomes also pass. [Layout details](layout-detail.log), [reward details](reward-detail.log).

Actual Game/Renderer checks pass with normal health: model/shadows, mouse collection/access, keyboard dynamite and reward toggles, staged Apply, export/load/remember, revisit, death retry and fresh-session settings. The reward keyboard-focus list now includes all displayed reward toggles. The automation's second retreat was moved to an interior floor point to avoid selecting the existing adjacent passage; controls are unchanged. [Input check](input.log), [reward panel](rewards-panel.png), [map panel](layouts-panel.png).

Four fresh main-game CLI loads pass: schema5 original preset, schema22, schema23 key rewards off and schema23 room layouts off. All retain165% zoom and normal health. [CLI validation](cli-validation.json). The original user's export remains byte-identical: SHA256 `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`.

## Interactive handoff and next step

The normal game opens directly in **displayed room6, seed285**, beside the first enclosure. Two keys are preplaced,3 dynamite are available, health is6 half-heart units, god mode is off, and the user's165% preset is loaded. Death retry returns here. [Launch record](interactive-handoff.json). The interactive review was relaunched at the user’s request; see the launch record for its PID and log.

```sh
build/deathward --expedition --seed 285 --review-source-room 214 --mute --save /home/kambo/.local/share/deathward/reviews/d09c-keys/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

Human check: inspect the new key's size/readability; press **B** beside an enclosure, retreat within the room, then walk through the breach. The counter increases by1 per key. Leave/revisit and check no duplicates. Review the live KEYS toggle/export/load if desired. The user accepted this scoped playtest. D09c is committed as `b466b5a3`. The user selected corridor decoration and supply-cache removal next; see [cleanup progress](../expedition-presentation-cleanup/README.md). Subsequent proposal, requiring separate selection: **D09d ordinary bomb/dynamite pickups**: natural clear rewards and one compatible complete layout, collection amounts/capacity/timing, revisit persistence and live/export/load settings. Follow with a short main-game check. Fuse/blast/self-damage and keyed-door spending remain separate D10 deliveries; this status question selects no new implementation.

Unfinished: broader key layouts, golden/charged keys, complete native seed/factory/physics/profile/modifier/scheduler equivalence, gameplay save continuity, and earlier chest loot/room gaps. Bomb/dynamite and door-spending changes require separate selection. Isaac size/shape/connections remain excluded; accepted movement, shooting, health/damage and universal dodge remain intact.
