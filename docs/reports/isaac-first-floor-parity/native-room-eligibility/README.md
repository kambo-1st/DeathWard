# Ordinary room eligibility and descriptor seeds

Selected continuation after the source91 rock-room delivery (`37e4c4c2`) and the user's 2026-11-12 room-scope decision. DeathWard's canyon room size/shape and physical corridors remain deliberate exceptions. This checkpoint targets ordinary non-XL Normal Basement I content selection, not the entire native floor generator.

## Source findings

The original native difficulty branch confirms **1–5** for that profile. The previous range was correct; it is now backed by executed caller evidence. The native stage mapper chooses Basement pool1. The ordinary room caller requests type1, subtype0, variants0..UINT_MAX, the requested shape/door mask and weight reduction. DeathWard keeps its shape1 content subset and derives compatible door masks from its existing canyon connections. This does not resize rooms or alter their connections.

Native `Level::place_room` passes the room-selection seed into `RoomDescriptor::InitSeeds`. The descriptor uses shift triplet2/7/9: decoration is its first advance, spawn the second and award the third. The main game previously took a second independent DeathWard draw for the spawn seed. It now uses the native derivation from the selection seed, followed by the already implemented per-source-slot2/7/7 sequence. Heart subtype resolution therefore changes for some existing DeathWard seeds. Unsupported outcomes remain unsupported; they are not rerolled into red hearts. Only the spawn consumer changes: clear rewards and decoration/boss-death consumers are separate work.

The preserved executable SHA256 is `04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`. [Native manifest](manifest.json), [caller cases](native-queries.csv), [descriptor cases](native-descriptors.csv), [difficulty cases](native-difficulty.csv), [stage-pool cases](native-pools.csv). Reproduce with:

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-room-eligibility.py --check
```

These execute original x86/SSE instructions in an isolated emulator with supplied stage/difficulty/resolved curse mask/slots/RNG state. The placement window executes the complete native InitSeeds function. There are20 difficulty cases,12 stage-pool cases,1024 ordinary caller cases and64 descriptor cases. No instructions, RNG or selector results are patched. Source signatures from [REPENTOGON RoomDescriptor](https://github.com/TeamREPENTOGON/REPENTOGON/blob/main/libzhl/functions/RoomDescriptor.zhl) and [Level](https://github.com/TeamREPENTOGON/REPENTOGON/blob/main/libzhl/functions/Level.zhl) were used as locators; the pinned executable supplies the behavior.

## Main-game delivery and persistence

`SOURCE LAYOUTS` uses the explicit ordinary query and native-derived spawn seed during generation. Existing live controls, pending map edits and Apply behavior remain. Loading/remembering an older preset migrates it to schema16, retaining map/view/player/enemy/combat choices. The new content policy is `basement-native-descriptor-rock-room91-v4`; the preset also records the user's canyon-geometry and canyon-connections exceptions. Invalid or incompatible presets still reject atomically. Existing generated rooms are not rerolled by live stat edits; explicit floor regeneration/new expeditions use this policy. No new balance tunable was introduced.

`--expedition --review-source-room N` starts directly at an existing generated source template's entrance. It uses ordinary room admission, with normal HP, inventory, enemies and damage. It neither forces a template into the floor nor heals/clears the room. Missing templates reject a new launch with a clear error. Death retry returns to that source room when present; if the user has disabled it through map settings, retry starts at the entrance with a notice. The launch aid is session configuration, not an exported balance parameter.

The resize checks reproduced a navigation defect at seed934, size.75 and range5–5: demolition opened a physically clear path, but coarse navigation nodes could not anchor the destination. Ground navigation now accepts a clear segment between two valid endpoints before requiring those anchors. Closed rocks still block movement; blocked-click relocation retains its existing path.

Nine focused suites pass, including core contracts, authored rails, source-room generation, heart rewards/layouts, preset compatibility and destruction. An additional real click-to-move check passes in all nine size/range combinations after demolition. Actual Game/Renderer checks pass for direct launch, normal starting HP/inventory/damage, PLACE, both pickups, revisit, staged OFF/Apply, death retry, missing-template rejection and fresh preset reload. Existing mouse/keyboard tuning, export/load/rejection and floor/retry checks also pass. Four separate real CLI launches verify schema5/15/16 presets and direct source91/source47 entry; five invalid CLI requests reject before opening the game. [Validation](validation.json), [regressions](regressions.log), [click navigation](click-navigation.log), [Game/Renderer](input.log), [tuning UI](layout-ui-regression.log), [CLI](cli-validation.json).

## Human check

```sh
build/deathward --expedition --seed 934 --review-source-room 91 --mute --save /home/kambo/.local/share/deathward/reviews/native-room-eligibility/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

This opens directly in generated room4 (source91), with a half heart in the left pocket and a full heart in the right. The selection seed is1277566494 and the native-derived spawn seed is2844051982. The old seed56 witness now resolves an unsupported soul-heart outcome and one half heart; that outcome is retained without substituting a red heart.

1. Walk to the rock pockets. Shooting and movement must not let you collect through intact rocks.
2. Use **PLACE** beside a rock, retreat, then click through the opening. A heart heals only when health is missing.
3. Leave/revisit, or use death retry if needed. Changed room state persists on revisit; retry reconstructs the same floor and opens directly in the room.

[Closed](closed.png) and [opened](opened.png) captures use the actual Game/Renderer. Automated capture enables damage immunity only to stand beside the blast; the interactive launch uses normal health/damage. DeathWard's existing legacy objective prop is visible outside the source arrangement in this witness; it is retained, not part of the native template. The accepted external preset and D03 backup remain SHA256 `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`.

## Remaining work

The433-template shape1 subset, initial DeathWard selection-seed adapter, canyon generation order and weight lifetime remain documented adaptations. Full native floor caller behavior (including fallback/retry, special seeds, unlocks, XL/other modes), descriptor consumers beyond pickup spawning, pickup factory/scheduling and full floor distributions are unaccepted. Other source templates still lack their complete enemy/obstacle/pickup arrangement. Existing DeathWard legacy objective props also remain outside the imported arrangement; complete source contents do not yet replace the entire room. Source91 retains DeathWard dynamite and collision adaptations. Exact source size/shape and physical connections are excluded by the user. Coins and unrelated bulk parity remain deferred.

Next: expand complete source contents together, starting with a compatible ordinary template and a direct main-game review; continue unresolved native selection dependencies where required by that template. The user accepted this scoped playtest on 2026-11-12 ("looks goo, commit and contionue"), requested its commit and selected the next complete-room continuation. [Acceptance record](human-acceptance.json). Broader native acceptance remains open.
