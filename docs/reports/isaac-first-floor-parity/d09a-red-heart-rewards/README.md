# D09a — ordinary red-heart clear rewards in the main game

Selected after the user accepted D08 and said “looks good contoinue”. Full, half and double red hearts now arise from first clears of ordinary opening-floor canyon combat rooms. The existing typed-health consumer supplies healing/refusal. This is a bounded source reward consumer; human acceptance and complete native reward/actor equivalence remain open.

## Short check

```sh
build/deathward --expedition --seed 69 --mute --save /home/kambo/.local/share/deathward/reviews/first-floor-d09a/campaign.save --balance-preset docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json
```

1. Fight the two Gapers in **room 3 beside the entrance**. Its natural, unmodified Luck-0 roll produces a **full red heart** after the last threat dies. No demo-only pickup or forced reward is inserted.
2. At full red health, walk onto the heart: it stays. With missing red health, collect it: it restores up to **one full heart**, capped by existing capacity. A Gaper may leave a successor body before the room clears.
3. Leave and return. An uncollected heart remains; a collected one stays gone. Death retry is available.

The check takes about 1–2 minutes. The interactive launch uses normal damage and active AI. Accepted walking, eight-direction firing, universal dodge, damage/HP, shooting, room dimensions/routes and 165% zoom are retained. The original external preset and its D03 backup remain unchanged.

## Live configuration

**TUNING → REWARDS** supplies:

| Control | Default | Application |
| --- | --- | --- |
| Red-heart clear rewards | Enabled | Future first clears only. Existing pickups, pending selected awards and cleared-room history stay intact. |
| Luck | 0; ±1 steps; editor −3…20 | Future first-clear rolls. The native ordinary selector clamps its Luck input to 0…10. This is not a direct heart-chance multiplier: Luck shifts the whole reward table. |

These settings apply live and export/load/remember together with all existing fields. Schema **11**, contract `d09a-red-hearts-v11`, adds `red_heart_clear_rewards` and `player_luck`; schemas 1–10 migrate to enabled/0. Invalid presets reject before partial publication. Loading reward settings leaves map edits pending until Apply map changes. Retry, new application/expedition and floor travel retain the settings. Actual rewards in this delivery are limited to the opening floor. Map testing regeneration resets floor encounter/reward history, retaining the player/build and selected settings, as previously requested. Configuration persistence remains separate from gameplay saves; this does not add mid-expedition application-resume support.

## Source and integration boundary

[Verified source evidence](source-evidence.json) pins the installed Repentance **1.7.9b** reference. `verify-d09a-reward-evidence.py` checks the preserved native matrices/disassembly against their original hashes and verifies the red quantities. Only the selected pure selector and heart resolver were recovered from the checksum-verified pre-revert archive; the reverted bulk system was not restored.

- All **2,196** captured ordinary award decisions and exact RNG endpoints match the recovered selector. It uses the native 5/9/7 RNG, float conversion, two initial draws, Luck clamp and subsequent family draws. All **1,036** captured heart resolver outputs match, including both represented rare-heart gate inputs.
- Production uses the explicitly recorded **rare-heart gates off** reference inputs. This is a bounded baseline, **not a complete fresh-save/unlocked profile or an import of the user's Isaac unlocks**. Rare hearts, native item/trinket/character/co-op modifiers and full profile acceptance remain open. The source gate values are separate from user Luck/configuration overrides.
- Only source heart subtypes **1 → two red halves**, **2 → one red half**, and **5 → four red halves** are enabled. Other native outcomes are recorded as unsupported; no reroll, substitute heart or unrelated family implementation is introduced. Soul/black/eternal/etc. pickup behavior is not promoted by the ordinary-red-heart selection.
- The source selector consumes an explicit, deterministic **DeathWard room-seed adapter**. It is isolated from combat, discovery order and generic loot streams. The next source RNG draw supplies the pickup seed, matching the ordinary spawn instruction sequence preserved at `7b903a..7b9064`. Full native descriptor/global seed mapping and complete spawn-wrapper execution remain unaccepted; identical DeathWard/Isaac seed strings do not claim identical drops.
- Each first clear stores its resolved identity, seeds, Luck snapshot and pending/delivered state in the owning room. Capacity or blocked placement delays delivery without rerolling. Placement prefers the room center, then reachable legal floor away from gates/cache reservations. It is an explicit canyon placement adapter. Inactive-room pending awards wait for that room; disabling rewards or editing Luck does not cancel or reroll already selected awards.
- Ordinary source hearts reuse the existing world pickup collision/health path. Full red capacity refuses collection; admitted healing clips to available capacity and consumes once. Full/half/double pickups are visually distinguishable. The selected [timing continuation](../d09a-heart-timing/README.md) now supplies ordinary appearance/collection frame gates; vertical/motion physics, full collision/scheduling and modifier acceptance remain unfinished.

Special rooms, bosses, story sites, tutorial, trap/plate-only rooms, Classic/Mine and later floors are outside this producer. Existing custom coin piles and generic enemy coin drops remain until the separate coin delivery; existing boss/power/shop rewards remain separate. No prior ordinary room-clear heart policy existed to replace. This delivery does **not** establish full first-floor economy parity.

## Verification

- [Gameplay checks](gameplay-tests.log): full/half/double natural seeded outcomes and exact quantities, full-health refusal, clipped healing, collected/uncollected revisit behavior, capacity recovery, committed roll retention across live edits, inactive-room ownership, blocked-center fallback, unsupported soul result, Luck consumption and later-floor exclusion.
- The D08 real Simulation door/projectile/clear/leave/revisit check now also verifies the uncollected full heart persists exactly once.
- [Actual Game/Renderer check](input-tests.log): generated two-Gaper encounter cleared by mouse primary fire, natural heart production/refusal/healing, reward mouse/keyboard controls, pending map boundaries, export/load/invalid isolation, map reset, floor travel, death retry and fresh-session loading. Test-only god mode, held AI and aligned firing points are used for deterministic verification; they are not used in the interactive handoff. [Natural heart](natural-heart.png), [controls](panel.png), [test preset](preset.json).
- [Final validation](validation.json) records six focused suites, prior UI regressions, CLI reload cases and source/preset hashes. Source/native coverage is limited to the described matrices and adapters.

## Remaining and next

The user positively acknowledged the producer and selected ordinary red-heart spawn/collection timing before coins. That [continuation](../d09a-heart-timing/README.md) is now enabled and developer-verified; its human review and full native lifecycle acceptance remain open. Placement/collision and a matched native encounter check are next proposals. Coins and other outcomes/producers remain unselected.

## Heart-spawning parity review before coins

The user positively acknowledged D09a and asked what remains before coins. This was initially a gap review. The subsequent “ok, lets go!” selected its first slice, ordinary red-heart spawn/collection timing; no other gap was selected. Coins remain unselected.

| Remaining work | Current implementation / acceptance boundary |
| --- | --- |
| Spawn and collection lifecycle | Appearance/collection gates and frame durations now enabled through the bounded timing continuation. Complete native factory/scheduler/physical and room-transition behavior remain open. |
| Placement and clearance | DW room center / nearest reachable cell; native placement search and grid/body clearance remain unverified in production. |
| Complete heart outcomes | Only full/half/double red hearts are produced. A selected soul/black/eternal/blended/etc. heart outcome currently produces no pickup. Typed-health support alone does not enable its producer or actor behavior. |
| Profile and modifiers | Recorded rare-heart gates off and ordinary Normal/no reward modifiers. A declared actual unlock profile and relevant item/trinket/character/difficulty conditions remain needed for broader parity. |
| Other eligible first-floor sources | Ordinary combat first-clear rewards and the subsequently selected full/half room-layout heart layer are connected. Other authored outcomes and eligible destructible/container/enemy/item sources require their own verified producer rules. Later floors/co-op/other characters are additional scope, not prerequisites for the bounded ordinary-Isaac/Normal first-floor target. |
| End-to-end native comparison | Selector/resolver calculations match captured native cases; complete source spawning, physical collection and room lifecycle have not been compared in a matched live encounter. DW room seeds remain adapted; identical Isaac seed replay is a separate requirement from matching rules/distributions. |

Selected first slice: **ordinary red-heart spawn/collection timing**, implemented in the [continuation](../d09a-heart-timing/README.md). Next proposed: placement/collision and a matched native encounter check. Then expand the selected heart outcomes and eligible first-floor producers. Do not treat this recommendation as authorization to implement all gaps.

### Clarification: hearts already present on room entry

The user asked specifically about hearts placed in rooms before combat. At that checkpoint these were **not implemented** in normal generation: `RedHeartRewards.cpp` was then the sole production caller of `spawnHeartPickup`, and it pays eligible first clears. Shop/service healing is direct health restoration, not a placed heart actor.

A read-only parse of the pinned installed Basement STB confirms authored heart entries: normal template `1.86.0` has type5/variant 10/subtype0 at cell(6,3); `1.91.0` has subtype0 entries at(5,3) and(7,3). These establish source template placements, not their live selection frequency or unlock/eligibility. Subtype0 still requires source resolution; it does not guarantee a full red heart. The current selected D08 template `1.47.0` contains no pickups.

Proposed separate delivery: source room-template heart placements and verified subtype/eligibility rules, adapted to dynamic canyon geometry, visible on first entry and persistent without duplication on revisit. Initial placement must use its appropriate lifecycle rather than automatically replaying the room-clear birth animation. Any new overrides need the existing live/export/load workflow. This question alone does not authorize implementing that delivery. Full template selection/distribution, supported outcomes and physical placement remain unfinished.

### Recheck: are room-clear hearts an Isaac rule?

**Yes.** Hearts are an ordinary chance-based room-clear reward in the targeted installed Repentance 1.7.9b. They are separate from pickups authored into room layouts. The natural-clear callsite invokes `SpawnClearAward` at `7ae398`; its ordinary selector is `7b82b0`. The prior explanation should not be read as saying room-clear hearts are a DeathWard invention or that all clears should award one.

For ordinary Isaac, Normal mode, Luck 0 and no reward-modifying inventory, the initial selector bands are: nothing 22%; card/pill/trinket 8%; coin 15%; heart 15%; key 20%; bomb 15%; chest 5%. These are **initial bands**, before later replacements and subtype resolution, not final observed full-red-heart rates. The native selected fixture includes the later sack conversion. The [public rules reference](https://bindingofisaacrebirth.wiki.gg/wiki/Room_Clear_Awards) corroborates the heart band; its historical pseudocode is not substituted for the pinned native code when versions differ.

A fresh read-only isolated execution of the installed executable matched all 2,196 preserved selector cases, including exact RNG endpoints; 357 selected variant 10 in this boundary-biased matrix. That count is not a drop-frequency estimate. The current C++ reference check also passes all 2,196 selector cases and 1,036 heart-subtype cases. [Recheck record](room-clear-rule-recheck.json).

Seed 69/displayed room 3 is a deterministic natural full-heart witness. Repeating that same expedition seed repeats its reward; the production path does not unconditionally grant a heart after each clear. Actual native room-seed mapping remains adapted. DeathWard currently realizes only the selected full/half/double-red results; other source reward families and heart types still produce no source reward actor. Existing custom coin drops are a separate unfinished policy. Thus the **room-clear-heart mechanism is valid**, while complete reward availability/economy remains incomplete.

No gameplay settings or logic changed during this rule recheck. Remaining work includes preplaced room hearts, other eligible heart producers/outcomes, full reward families/modifiers and native placement/lifecycle/seed acceptance. The proposed next source-placement delivery still requires selection.

### Selected follow-up: preplaced full and half hearts

The user subsequently selected and enabled full/half hearts already in room layouts. See the [current layout-heart delivery](../d09a-room-hearts/README.md). It adds a separate source-derived pickup layer and staged schema13 configuration without changing clear rewards. Earlier statements above that preplaced hearts were missing describe the previous checkpoint. Human and full native template/seed/grid/physical lifecycle acceptance remain open; other outcomes/producers and coins remain unselected.
