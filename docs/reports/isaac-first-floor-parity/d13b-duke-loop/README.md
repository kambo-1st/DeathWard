# D13b — ordinary Duke of Flies

Selected on 2026-11-17 after accepted Monstro commit `3896877b`. Implemented in the main game; developer checks pass. The user accepted the scoped playtest ("nice commit!") and authorized the checkpoint commit. **Scoped human acceptance is recorded; full native acceptance remains open.**

## Play it

```sh
build/deathward --expedition --seed 69 --review-room 9 --mute --balance-preset docs/reports/isaac-first-floor-parity/d13b-duke-loop/duke-preset.json --save /home/kambo/.local/share/deathward/reviews/first-floor-d13b/campaign.save
```

This opens displayed room9 with normal three red hearts, no god mode and the user's165% map/view/shooting settings. Death retry returns to the same encounter. Fight Duke and its flies, clear the remaining flies, collect the centered Breakfast reward, then use the floor exit. Verify readable movement/pressure, fly contact and the reward/exit timing. This is a normal main-game expedition, not a separate prototype.

TUNING → ENEMIES → BOSSES offers **Legacy / Monstro / Duke of Flies**. Selection remains pending until Apply map changes; that regenerates the current floor and keeps the owned build. Existing presets keep their Monstro selection. Duke health, movement and fly speed change live in5% steps; health preserves injury fraction and speed changes preserve the current action phase. Export, Load and Use next expedition include all fields. Schema44 migrates1–43 through audited additive catalog hashes. Loading selection stages it; retry/floor advance carry applied settings. The original user preset is unchanged (SHA256 in `verification.json`).

## Enabled behavior

- Ordinary67.0.0 only: drifting body, native action gates/frames, three linked live Attack Flies, one enlarged unlinked live Attack Fly, cohort detachment/release, six unowned Fly/Attack Fly death offspring.
- Enlarged fly: source1.8×HP and1.25×visual; live offspring expire on contact, death offspring do not inherit that flag. Regular-enemy HP changes use the existing shared calculation for offspring and exclude Duke.
- Native selected births retain identity/seed/payload through capacity or placement delays and parent death. Pending births and live flies prevent premature room clear. After the final threat is cleared, the established single Breakfast25 reward, physical pedestal and floor descent become available. Collection/revisit cannot duplicate the reward; active/passive/familiar/trinket state carries to the next floor.
- Source boss HP110/stage0 is retained separately from the ×3.2 internal unit:352HP. Body35 uses accepted Gaper .6/source13; motion uses the fixed D04 calibration. Existing player balance, eight-direction firing and universal dodge remain intact.

## Evidence

Recovered selectively from the preserved pre-revert archive: `src/combat/Duke.*`, dedicated rendering, the two Duke reference scripts and native test comparisons. No bulk parity restored. Original archive SHA256 `42171909a523f0659e7899e9993ac6183f9fa04c942fd5d6d5c0c51719637be0`.

- Preserved installed1.7.9b ordinary-controller audit:3144states,4345birth intents,304release intents; C++ comparison has zero numeric difference. Native executable/DLL replay and animation metadata checks pass (`native-check.log`, `animation-check.log`; original evidence in `../duke/`). These are bounded actor/kernel checks, not full game acceptance.
- Five focused suites pass: Duke lifecycle/capacity/contact/HP, Monstro regression, core contracts, preset contract and treasure upgrade. Three generated size settings test the complete boss → six remaining flies → reward → collection → revisit → descent path. Shared regularHP.75, injured boss tuning, live fly-speed edits, debug suppression and held live+death births are checked.
- Actual Game/Renderer Duke and Monstro modes pass mouse tuning, export/reload, reward collection, mouse descent, staged selection/Apply and retry. Developer UI tests use god mode/direct damage to exercise lifecycle; they do **not** certify combat pressure. The user launch has neither aid.
- CLI schemas5/43/44 pass, retaining normal health, Speed1 and165% zoom. Old schemas keep Monstro; the new review preset selects Duke. Screenshots show the actual renderer.

## Remaining work and explicit adaptations

The scoped fight/pressure playtest is human-accepted. Full native constructor/appearance/death scheduling, fly actor/factory/global-RNG/cosmetic/status/champion/synergy equivalence, source boss/reward pools and full live expedition resume remain open. Native XML eligibility does not establish full pool-selection probabilities: this delivery uses an explicit supported-boss choice and existing Breakfast-only reward.

Production uses DeathWard RNG, a30Hz controller boundary, accepted spatial calibration, canyon collision/flight altitude and blocked-axis reflection. The parent zero-InitSeed sentinel maps deterministically to1; complete native zero-seed factory resolution remains unaccepted. Retained child birth coordinates can wait for physical admission; broad pathological placement/capacity stress is not full native acceptance. Full room size/shape/connections remain deliberate exceptions.

The separately documented pre-existing Peep150-second combat-bot failure is not counted passing or changed by this delivery; see the D13a report. No further boss or broader parity feature is selected.
