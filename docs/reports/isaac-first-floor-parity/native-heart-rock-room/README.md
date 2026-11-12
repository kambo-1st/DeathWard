# Source heart room 1.91.0 — rocks and pickup access

Selected after the user accepted and committed the native selector/slot-sequence checkpoint (`ca239ff9`). Implemented in the main game; developer checks pass. The user positively acknowledged the interactive delivery on 2026-11-12 and requested its commit. This scoped acknowledgment does not establish complete native physical/floor-generation acceptance.

## Playable result

The source room's **19 rocks and two heart slots now form one arrangement**. Both pickups start inside sealed pockets. Ordinary shots and walking cannot open the rocks; normal inventory dynamite opens a path, after which the hearts can be collected. Destroyed rocks and consumed hearts stay changed on revisit.

The complete source record has no enemies, so this room is an empty obstacle room. It does not acquire unrelated generated enemies, outcrops, supply caches, initial coins or a fake combat-clear reward. The canyon basin, surrounding cliffs, controls and accepted player/combat settings remain. Rivers avoid this selected source room. Mandatory DeathWard keys, if assigned to this room, use an accessible position outside its optional pockets; that is an explicit progression adapter.

Contents are selected before terrain/encounter generation. The source record's rocks and hearts share the existing uniform dynamic cell transform. Rock collision and visible breakables use the same bounds. Hearts retain their exact source slots here; the previous nearest-reachable-floor fallback is bypassed for this template. Capacity/collision delays retain that position and identity. Other templates still use the previously documented heart-layer adapter.

**Apply map changes** remains unrestricted after exploration/combat. It regenerates the current floor, restores the rocks/pickups and preserves player/build/expedition identity. It places the retained player outside a reclosed pocket. Debug room travel also enters safely. OFF removes this arrangement; FULL + HALF TEST retains its existing unobstructed pair. No new tunable was added. Schema15 identifies the new content policy and migrates schemas1–14, preserving existing choices and accepted settings. Old presets are not overwritten.

## Human check

```sh
build/deathward --expedition --seed 56 --mute --save /home/kambo/.local/share/deathward/reviews/native-heart-rock-room/campaign.save --balance-preset docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json
```

1. The expedition starts at room1. Reach **room7**, marked **E** on the minimap because it has no enemies (above room2 on this seed). See both hearts enclosed by cracked rocks, with no enemies in that room. Shooting or walking should not let you collect through the rocks.
2. Stand beside an enclosing rock, use **PLACE** dynamite and retreat. After the blast, walk through the opening; collect the heart if red health is missing. The other pocket has its own approach.
3. Leave and return. Demolished rocks and collected hearts must stay gone.

[Closed arrangement](closed.png), [opened by the normal PLACE action](opened.png). Captures use the actual Game/Renderer with the accepted165% zoom; only the automated capture player's damage immunity is enabled so it can remain beside the blast. The interactive command uses ordinary damage and AI, without cheats.

## Source and checks

[Complete source extraction](source-room.json) pins the installed Repentance1.7.9b Basement STB SHA256 `524406fcb10c6275995292c0bd024cfc43d3d30c32b233e55d4d514573d963b0`. All21 source slots are preserved:19 entries1000.0.0 and two random-heart entries5.10.0 at(5,3)/(7,3), no NPC entries. The generated rock coordinates are validated by `python3 scripts/isaac-reference/extract-room-heart-layouts.py --check`. The already verified native selector and per-slot RNG choose template91 naturally for seed56/room7; the existing heart resolver yields half/full. No guaranteed-room override or new source random stream was added.

[Gameplay tests](tests.log) cover nine combinations of size.75/1.1/1.5 and room half-tile ranges5–5/7–9/10–10: all19 rocks, both exact pickup positions, sealed pockets, ordinary-shot resistance, real inventory spending, movement/path/collection after demolition, unobstructed door routes, no extra room coins/enemies/reward, revisit and regeneration. Regeneration from a position that would be re-enclosed relocates the player safely. The forced-pair mode remains unchanged.

[Seven focused suites](regressions.log) pass: new rock-room gameplay, existing heart layouts, native selection reference, preset contract, D08 encounter, red-heart clear rewards and expedition destruction. [Actual Game/Renderer checks](input.log) cover the normal PLACE action, both healing amounts, revisit and staged OFF/Apply. [Existing layout UI checks](layout-ui-regression.log) cover mouse/keyboard, export/load/rejection, floor/retry and fresh-session persistence. Separate main-executable launches verify [schema5](cli-v5.log) and [schema14](cli-v14.log) migration; schema15 round trips are tested in the preset suite. The accepted preset and backup remain SHA256 `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`.

## Unfinished and next

This verifies the source content arrangement and its DeathWard access behavior, **not full native grid/physics parity**. Dynamic canyon cell scale, player footprint and existing dynamite radius/fuse/blast shielding are retained adapters. Native runtime special-rock substitutions and ordinary rock drops remain unimplemented; these source props deliberately do not add the unrelated DeathWard rock-coin payout. Pickups keep the existing preplaced-idle lifecycle and source-subtype adapter; full native factory/scheduling/displacement acceptance remains open.

On 2026-11-12 the user explicitly excluded Isaac's room **size/shape** and **connections**. The retained canyon geometry, dynamic sizing and physical corridors are deliberate exceptions, not unfinished parity requirements. Source content, access restrictions and room-selection rules remain in scope.

Next is the selected native first-floor ordinary-room eligibility work: establish the actual caller pool/difficulty and descriptor-seed rules, interpreting source shape/door inputs as compatibility metadata for the retained canyon layout. Integrate those rules and expand complete contents beyond template91. Future review launches should open directly at the relevant room; the current command still starts at the entrance, which caused confusion during this handoff. Other room layers still lack their full source obstacles/actors. Coins, other reward families and bulk parity remain unselected.

## Subsequent checkpoint

The [ordinary caller/descriptor delivery](../native-room-eligibility/README.md) verifies the scoped Normal Basement I inputs and corrects pickup seed derivation. Use its seed934/direct-entry command for current builds; the seed56 full/half witness above describes the preceding schema15 checkpoint. Wider complete contents and native acceptance remain open.
