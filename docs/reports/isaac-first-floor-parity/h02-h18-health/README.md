# Selected H02–H18: health implementation

The user explicitly selected this range on 2026-11-08. H01 remains six starting red half-heart units. Universal dodge retains its speed boost and immunity. Player attack damage remains 24, regular-enemy HP retains its independent mechanics multiplier, and the bulk parity goal remains paused.

## Enabled gameplay

`hp`/`maxHp` retain their existing API names as red filling/capacity. Soul/black health, slot masks and the other heart counters are separate canonical fields. Every gameplay health operation uses an integer native-unit snapshot and writes its result back; there is no second stored universal health bar.

- H02–H04: separate red filling/capacity, soul health, ordered protective slots and typed pickup mutation. Healing fills red capacity, including red filling inside bone containers; it does not refill soul/black protection.
- H05: black slot depletion queues a 40-base-damage room effect. Pending recipients survive damage-queue pressure and are admitted once. This uses the existing enemy damage dispatcher rather than changing enemy HP or weapon damage.
- H06–H10: eternal halves and pair/floor conversion; empty/filled bone containers and break behavior; rotten red filling with double depletion and room-clear blue-fly refill; golden overlays with 3–8 penny drops and bounded ordinary Midas freeze/death coins; broken hearts reducing the 24-half capacity limit. These are distinct states, not additional interchangeable red HP.
- H11: ordered soul/bone/red depletion, acquisition-order slot masks, eternal shielding and the explicitly measured red-first path. Dodge rejects damage before these mutations or effects.
- H12–H14: existing authored incoming amounts use ten units per half-heart before native integer rounding. An ordinary positive 10-unit hit therefore costs one half-heart, rather than 12.5 old HP. Native rounded-damage counters give ordinary one-second immunity for a half-heart hit and two seconds for a full-heart-or-larger hit. Existing no-contact enemies remain harmless. Six ordinary losses exhaust the starting three red hearts.
- H15: retained universal dodge exception, including movement boost and immunity.
- H16: medicine heals one red heart; surgeon treatment heals up to three, tonic adds/fills one container; current Smuggler offer costs one red/bone container or three soul hearts when there are no such containers. Costs remove capacity without invoking hit damage. Existing authored Judas Bullet capacity changes round down to full containers, keep at least one existing red container, and cannot invent red capacity for a soul-only player. Service descriptions and previews use hearts/containers. Other resource prices remain unchanged.
- H17: death considers red, soul and empty-bone survival. A scoped `isaac:collectible:11` 1up dependency revives ordinary Isaac once in a safe room, filling red capacity or giving half a soul heart when red-free, and consumes its inventory copy. It is available by explicit grant/inspection; it has not been inserted into natural item pools.
- H18: typed health, overlays, broken capacity and inventory carry between floors; an eternal half adds/fills one red container. Other injuries are preserved. Blue flies carry as owned actors and receive fresh entity IDs.

World heart pickups can be placed, collected, retained when unusable, and rendered. The HUD distinguishes protection, bone/rotten/broken health and eternal/golden overlays. `--smoke --scene health --theme canyon --frames 8 --screenshot PATH` inspects the mixed display. This is a rendering fixture with inspection god mode, not a live-game acceptance trial.

## Evidence and limits

The original pinned Repentance 1.7.9b executable is read only. Restored research scripts rerun its bounded health, hurt, Midas, blue-fly and rotten-refill instructions with `--check` against the preserved evidence. `analyze-player-motion.py` is restored as their emulator fixture dependency; no movement/firing implementation is restored.

- [Health](../player-health/README.md): 293 transitions, 28 cases; nine health APIs, slot order, capacity, depletion and eternal conversion.
- [Hurt counter](../player-hurt/README.md): 24 rounding/counter cases and 193 decrement states; [update-phase research](../update-phases/README.md) supports 60 player invocations per ordinary simulation second.
- [Midas](../midas-freeze/README.md): 1,096 control states, 13 cases and 11 supplied-RNG death-coin cases.
- [Blue flies](../blue-fly/README.md): 318 motion states, 36 angles, 64 scores, five damage values, 22 special direct-kill branches.
- [Rotten refill](../rotten-heart-flies/README.md): 104 deficit cases.
- 1up behavior is based on the [preserved wiki revision](https://bindingofisaacrebirth.wiki.gg/index.php?oldid=265852), with installed XML establishing collectible identity. Its native death branch has **not** been executed by these health fixtures. Character transformations, revival priority and the wider item catalog are not implemented by registering this one dependency.

Validation is recorded in `validation.json` and the adjacent logs. The independent native-output tests are separate from actual Simulation/Game integration tests.

## Still unfinished

This is scoped enabled gameplay, **not full native health acceptance**. In particular:

1. Full native damage-entry flags/prechecks, source-specific exceptional immunity, champion/hazard/self-damage calibration and health-item modifiers remain unaccepted. The authored ten-to-one adapter is an explicit conversion policy, not proof that every attack matches Isaac.
2. Black-burst special target eligibility and item modifiers; Midas linked/special-body propagation and complete immunity flags; full blue-fly collision/targeting/callback/RNG equivalence and mixed health-effect ordering remain open. Ordinary unlinked paths have bounded evidence; excluded actors are not silently accepted.
3. Native mixed deal prices, pickup-animation survival grace, health item/character exceptions, all other resurrection items and character transformations remain open. Current authored services are adaptations, not a port of native Devil Room generation or its complete item catalog.
4. Heart subtype behavior such as scared-heart motion, native collection timing/physics and natural drop/reward distributions remain open. Placement support is not natural availability. P04/P09 and room/reward differences are still unselected.
5. A live matched native-versus-DeathWard playtest and user visual acceptance remain open. Campaign checkpoints still record expedition summaries; this task does not add resumable mid-expedition save games.

Do not mark these gaps complete solely because the native arithmetic fixtures or the gameplay integration tests pass. Consult the main selection report before implementing any unselected difference.

## Completed validation and baseline comparison

The application and test targets build. Eight focused suites pass: mechanics/content, native health, native hurt counters, native blue fly, native Midas, health gameplay, regular-enemy HP control, and core contracts. Actual Game/input checks pass for starting/reset health, half-heart loss, dodge, keyboard navigation/combat, both shops and specialist trades. Final heart and medicine displays were visually inspected.

The broad run completed 116 suites. After two targeted reruns, **106 pass and 10 fail**. The remaining ten failures also reproduce in an isolated Release build of untouched commit `28023a49dbd8712820ba6953219cfdb7866bdcb6`, using its original source, tests and mechanics. `baseline-tests.log` records that comparison; no user checkout, index or history was changed. The two health-related failures were corrected by migrating the champion damage expectation and teaching the Green Bloat bot to avoid predicted explosive landings. Player/enemy stats were not adjusted to make that bot pass.

| Existing failing suite | Failure reproduced on untouched baseline |
| --- | --- |
| `brain`, `adult_leech`, `knight_lifecycle`, `dip_variants`, `dinga_family`, `membrain_family`, `hardy_family` | Fixed seeded population witnesses no longer contain the required actor. |
| `linked_head` | Replacement HP after splitting does not match the existing assertion. |
| `resident_enemies` | Generic resident cooldown assertion fails on room entry. |
| `rock_spider_family` | Lower airborne projectile hull uses the base position; the existing test expects the rendered height. The diagnostic confirms both tested heights leave HP at 38.4. |

These enemy acceptance issues remain open outside H02–H18. The health implementation does not certify them or change their generation, geometry, lifecycle or balance.

The [mixed health display](health.png), [starting hearts](starting-hearts.png), [half-heart injury](half-heart.png), and [medicine description](shop.png) are inspection artifacts. Numeric/kernel and gameplay verification are in the adjacent logs and `validation.json`.
