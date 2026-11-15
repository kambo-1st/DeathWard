# Complete four-Gaper room: Basement 1.108.0

The user accepted the previous two-Gaper/seventeen-rock delivery, committed as `afbd2a68`, then selected the next compatible complete room on 2026-11-15. This continuation is enabled in ordinary main-game generation and passes developer checks. The user accepted this scoped main-game playtest on 2026-11-15 ("ok, looks good1"). [Acceptance record](human-acceptance.json).

## Source and gameplay

The pinned Repentance1.7.9b Basement template **1.108.0** has **four ordinary Gapers and nine plain rocks**, no initial pickups and no other actors. Its source difficulty is5, weight1, subtype0 and door mask15. All13 stacks contain one weight-1 choice. Gapers occupy (6,2), (5,3), (7,3), (6,4). [Complete source record](source-room.json).

```text
.............
.....###.....
......G......
....#G#G#....
......G......
.....###.....
.............
```

`G` means ordinary Gaper; `#` means plain rock. The existing native numeric/weighted selector can choose this record from the same433-template pool. Its original descriptor/spawn sequence advances through all13 slots. The complete arrangement now replaces unrelated encounter/cover in a compatible room; no extra initial coins, hearts, champions, cache, river or random cover are added. The existing selected first-clear reward policy remains separate.

A small shared registry now supplies the complete Gaper/rock records4 and108 to obstacle generation, enemy spawning, encounter counts, navigation and review admission. It enables no additional template. The earlier template4 placement and behavior remain covered by their existing tests. Template91 and D08's separate template47 are retained.

The source cells use the accepted uniform canyon adapter. Canyon room outlines, dynamic sizes/ranges and physical connections remain deliberate user exceptions. Legacy objective indices2/3, mandatory-key sites, story/special rooms and injected D08 rooms remain protected. A template108 selection at an incompatible site keeps its metadata without rerolling or pretending to be a complete encounter. Direct review requires the actual complete room.

Gaper movement and HP32 at regular-health1, canonical Damage3.5 →11.2 internal damage, accepted player walking/shooting, universal dodge and eight-direction input are retained. The formation is denser than template4; its higher source difficulty is recorded rather than reducing enemy HP or speed to conceal it. The source-aligned navigation fallback already accepted for template4 also handles108 with full physical clearance checks. No new movement model was introduced.

## Configuration

Use **TUNING → REWARDS → ROOM LAYOUTS → SOURCE LAYOUTS**. OFF/SOURCE/test edits stay pending until **Apply map changes**; Apply works during combat and preserves player/build and expedition identity while rebuilding floor encounters and rewards. The D08 SOURCE COMBAT ROOM switch still controls only template47.

Schema18, contract `d09a-four-gaper-room-v18`, policy `basement-native-descriptor-rooms4-91-108-v6`, exports/loads/remembers this content policy and migrates schemas1–17 with existing settings. No new numerical tunable was added. Live stat edits do not reroll the room. The accepted external preset remains unchanged at SHA256 `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`.

## Verification

- Pinned extraction check passes; both existing complete-record manifests reproduce unchanged. Reproduce with `python3 scripts/isaac-reference/extract-room-heart-layouts.py --check`.
- Seed117 was generated across nine size/range combinations. Five naturally choose complete108; four choose other content and correctly reject direct108 review. A second natural seed793 supplies the absolute minimum size. Six actual arrangements span source-cell sizes1.323–2.911 world units: exact four-actor/nine-rock content, legal placements, unchanged HP, physical paths from/to each actor, cross-room paths and door access pass.
- Actual small-room click movement and all four live Gapers navigating to the player pass at size.75/range5–5. The combat fixture holds actors still only to isolate real projectile obstruction/damage/death/clear behavior. It does not establish full native live combat equivalence. Real dynamite opens cover; destruction/clear/reward state persist on revisit. Apply OFF/ON retains player/build/identity and the selected HP override. [Gameplay log](gameplay.log).
- Eleven unique focused suites pass: the new four-Gaper suite plus10 regression suites covering source4, source91, D08, heart layouts/rewards, source selection, presets, core, rails and destruction. [Regression log](regressions.log), [preset log](presets.log).
- Actual Game/Renderer mouse controls pass for SOURCE/OFF staging, Apply during combat, export/remember/fresh reload and death retry; the accepted source4 UI workflow also passes. [New-room UI](input.log), [source4 regression](source4-ui-regression.log).
- Three separate CLI application launches with schemas5,17 and18 open the natural seed117/room6/template108 with normal HP6, god mode off, accepted Damage and zoom165%. [CLI validation](cli-validation.json), [exported preset](preset-v18.json).

[Room capture](room.png) and [layout controls](layouts.png) show the actual Game/Renderer. Initial-frame FPS overlays are not performance measurements.

## Short human check

```sh
build/deathward --expedition --seed 117 --review-source-room 108 --mute --save /home/kambo/.local/share/deathward/reviews/native-four-gaper-room/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

This opens directly in displayed **room6**, adjacent to the entrance: four Gapers around nine rocks. Selection seed3854136427 produces spawn seed4122658724. Health/damage are normal; death retry returns to this encounter.

1. Move around the rock cluster and fight the four enemies. Shots should stop at rocks; the enemies should navigate around them.
2. Optionally PLACE dynamite beside a rock and retreat; its opening should be usable.
3. Clear the room, leave and return. Enemies stay cleared and demolished rocks stay destroyed.

## Unfinished and next step

The scoped source108 playtest is accepted; the user did not provide an itemized test checklist. Other templates' complete contents, native factory/substitution/physical/drop equivalence, the native floor caller's remaining profile/unlock/fallback/order/RNG details, descriptor consumers beyond pickup spawning and full actor/bomb equivalence remain open. The433-template content subset, protected-room rule and DW seed/geometry/navigation adapters remain explicit deviations. Exact Isaac room size/shape and connections are excluded; coins and unrelated bulk parity remain deferred.

Next proposed: commit this accepted checkpoint, then another compatible complete source arrangement using supported content, with its own bounded check. This delivery is not full first-floor parity and does not resume the paused bulk effort.
