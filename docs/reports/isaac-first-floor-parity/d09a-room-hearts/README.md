# D09a continuation — full and half red hearts in room layouts

**Committed checkpoint: b42ef80f.** The user accepted this scoped delivery. The subsequent [native-selection checkpoint](../native-room-selection-placement/README.md) supersedes this page's sampler, schema13 and seed33 witness; the lifecycle/test-mode evidence below remains historical and valid for the committed implementation.

Selected by the user: “Add hearts (both full and half version) already placed in room layouts.” Implemented in the main game. Developer checks pass. The user positively acknowledged the delivery and requested its commit; full native acceptance remains open.

Placed hearts are generated with the opening floor, start idle/collectible before room clear, restore two/one red half-units, refuse full health and remain consumed across revisits. They are independent of room-clear rewards and their appearance-speed setting.

The default source-layer pool preserves 433 positive-weight, difficulty 1–5, normal 13×7 Basement templates, including zero-heart templates, 23 heart-containing spawn stacks and 28 weighted choices. Mixed non-heart alternatives and unsupported heart outcomes are not converted into selected red hearts. Only resolved full/half types are admitted. The extraction is pinned to installed Repentance 1.7.9b. **This is the heart layer of those templates**, sampled independently per eligible canyon room with DW seeds; it does not reproduce native floor-template selection/eligibility/frequency, source grid obstacles or complete source encounters.

The explicit **FULL + HALF TEST** mode uses the pair coordinates from template 1.215.0 and fixes their types to full/half for inspection. It is a testing override, not source drop odds. Both this mode and source/off controls are staged until **Apply map changes**, exported/loaded/remembered through schema 13, and carried across retry/floors. Applying regenerates current-floor encounters/pickups while retaining player/build/expedition identity. Later floors retain the setting without inserting a Basement layer; tutorial, story/special rooms and the recorded empty-pickup D08 encounter are excluded.

## Playable check

Normal source-layout mode, with a known full/half witness in **displayed room 6**:

```sh
build/deathward --expedition --seed 33 --mute --save /home/kambo/.local/share/deathward/reviews/first-floor-d09a-room-hearts/campaign.save --balance-preset docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json
```

Walk into room 6: both hearts already exist before combat is cleared. They come from the recorded corner slots of template 1.270.0, resolved to full and half by the deterministic source-subtype consumer. At full health, touching them leaves them available. With missing red health, collect them during the encounter: full restores up to two half-units, half restores one. Leaving and revisiting must not duplicate them. Normal damage and active AI are enabled in this handoff; death retry is available.

**TUNING → REWARDS → ROOM LAYOUTS** shows the rooms containing uncollected layout hearts. Choose **OFF**, **SOURCE LAYOUTS** or **FULL + HALF TEST**, then **Apply map changes**. Changes stay pending until Apply, including loaded presets. Apply explicitly resets floor encounters/pickups while retaining the player/build; it can be used after exploration/combat. Existing source clear-reward settings and pending map/view controls remain separate. **EXPORT**, **LOAD PRESET** and **USE NEXT EXPEDITION** include the selected mode. Schema 13 migrates schemas 1–12 to source-layout mode while retaining their previous settings. Configuration persistence does not add mid-expedition application-resume support.

The [test preset](test-preset.json) selects the explicit full/half pair on seed 69, displayed room 6, for a convenient side-by-side check. [Both pickup shapes](full-and-half.png), [controls](panel.png). These screenshots use test-only held enemy AI/god mode for repeatability; neither is used in the interactive handoff.

## Source and implementation boundary

[Extraction manifest and source entries](source-layouts.json) pin the Basement STB hash `524406fcb10c6275995292c0bd024cfc43d3d30c32b233e55d4d514573d963b0`. Reproduce with `python3 scripts/isaac-reference/extract-room-heart-layouts.py --check`. The generated header contains source template weights, heart slots and complete competing choices for those slots. Zero-heart templates stay in the pool. The existing verified ordinary heart resolver handles subtype0 using the recorded rare-heart gates off; this is not a complete imported unlock profile. Explicit half-heart entries retain their subtype. Other resolved heart types remain recorded but unspawned, without reroll or substitution.

A separate DW seeded stream selects each room's heart layer and pickup seeds, without changing encounter/clear-award streams. Native floor selection, difficulty/unlock filters, descriptor RNG and appearance frequencies are not established by preserving this filtered pool. The source's other actors/grid obstacles are not imported; existing canyon encounters/geometry remain. This selected delivery is a source-derived pickup layer, not full template or economy parity.

Source cells map uniformly into each dynamic canyon basin. Placement checks collision, gate/cache/key separation, separation from other hearts and reachability from an interior cell near the room entry. A blocked preferred point uses the nearest reachable legal floor cell. Capacity/placement failure retains the decided identity and retries when the owning room is active. Already admitted/collected slots never regenerate except through the explicitly labelled floor-reset workflow. Already-present idle pickup behavior is an explicit room-entry adapter; full native spawn/scheduler/physical eligibility is still unaccepted.

## Verification

Six focused suites pass: room-heart layouts, preset contract, source combat room, red-heart reward gameplay, reward reference and heart timing reference. The new gameplay suite covers immediate pre-clear full/half collection/refusal, once-only effects, collected/uncollected revisit, unchanged D08 pickup-free formation, same-size mode regeneration and later-floor exclusion. Twelve seed/size cases cover legal placement, gates/cache spacing and separate footprints; capacity and blocked-point cases preserve decided subtypes. A bounded source-pool witness scan through seed37 finds natural full/half outcomes, empty layers and unsupported outcomes. It is a deterministic regression matrix, not a native distribution benchmark. [Gameplay checks](gameplay-tests.log), [reference/preset checks](reference-tests.log), [existing encounter/reward checks](regression-tests.log).

[Actual Game/Renderer checks](input-tests.log) cover mouse/keyboard controls, pending Apply boundaries, export/load/rejection without partial publication, normal combat collection, revisit, floor/retry and fresh-session persistence. Rejected presets deliberately pause gameplay; the test resumes through normal keyboard input before collection. The [existing clear-reward UI regression](clear-reward-ui-regression.log) also passes. Five independent CLI launches verify old schema5/schema12 migration, schema13 pair loading, remembered reload and off mode. The user's accepted preset and backup hashes remain unchanged. [Validation](validation.json).

## Unfinished and next

The user positively acknowledged this delivery and selected native room-selection and placement parity as the next work. Complete native template selection, grid/physical/room-entry lifecycle, other heart outcomes/producers and a matched live encounter remain unfinished. Coins remain unselected. Earlier movement/shooting/HP/dodge/map/view behavior must stay unchanged.
