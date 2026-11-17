# D13c — seeded opening boss selection

Selected on 2026-11-17 after Prospector Exchange removal commit `2142ab9c`. Implemented in the main game; build and developer checks pass. The user accepted the scoped playtest ("it works next step1") and requested the next step. This accepted checkpoint is being committed. Full native selection and actor acceptance remain open.

Scope: seeded selection between ordinary Monstro20.0.0 and Duke67.0.0 in the existing opening-floor canyon boss loop. A dedicated DW random stream uses the floor seed and the supported source-ordered XML subset (weights1/1). It does not consume map, encounter, reward or combat RNG. Full native pool probabilities, unlock/history/first-encounter gates, actor equivalence and native global RNG remain unaccepted.

New profiles default to SEEDED. Schemas1–44 keep their previous fixed Monstro/Duke/legacy policy; schema45 exports/loads/remembers the new choice. Fixed choices remain in the same main-game tuning panel. Selection and preset-loaded map changes wait for Apply. Either boss's values can be edited independently without changing the active encounter. The review preset preserves the original165% map/view/shooting settings and enables SEEDED.

Verified policy witnesses: seed0 → Monstro, seed1 → Duke. Same seed survives retry, map resizing and fresh launch. Existing Breakfast reward/descent and later-floor policy are retained. Tutorial, Mine and Classic remain outside this opening-floor policy.

## Short human check

```sh
build/deathward --expedition --seed 0 --review-room 9 --mute --balance-preset docs/reports/isaac-first-floor-parity/d13c-seeded-bosses/seeded-preset.json --save /home/kambo/.local/share/deathward/reviews/first-floor-d13c/campaign.save
```

This enters the main-game boss room with normal three red hearts, no god mode and the accepted165% preset. Seed0 gives Monstro; use `--seed 1` for Duke. Retry returns to the same selected boss. Clear the boss and any remaining flies, collect Breakfast, then descend.

In **TUNING → ENEMIES → BOSSES**, **SEEDED / MONSTRO / DUKE OF FLIES / LEGACY** select the opening encounter policy. Selection takes effect on **Apply map changes**, which regenerates the current floor. Click **MONSTRO VALUES > / DUKE VALUES >** to edit either boss without switching the encounter. Existing health/movement/shot-or-fly controls still apply live. Export includes pending choices; Load stages policy changes; Use next expedition remembers them. Loading the original old preset deliberately restores its fixed Monstro policy; use the new review preset or select SEEDED explicitly to try D13c.

## Verification

- Five focused suites pass: seeded opening choices, Duke loop, Monstro loop, core contracts and preset contract. Actual generated actors, independent RNG streams, run IDs, small/large resize, scope exclusions, fly-clear gating, once-only Breakfast and descent are exercised.
- Three actual Game/Renderer modes pass: seeded selection and both fixed-boss regressions. Mouse tests cover both actors' independent live controls, staged selection/export/load/Apply, resize, retry and remembered settings in a new Game. UI screenshots are `seeded-monstro-settings.png` and `seeded-duke-settings.png`; the displayed tuning actor can differ from the current encounter by design.
- Five separate CLI checks pass: schema5 retains fixed Monstro, schema44 retains fixed Duke, schema45 produces both witnesses and repeats Duke consistently. All retain Speed1,165% zoom,6 red half-heart units and god mode off. See `cli-verification.json` and the corresponding logs.
- The original user preset remains SHA256 `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`. Mechanics fingerprint is unchanged. `verification.json` distinguishes developer validation from scoped human acceptance.

Developer lifecycle/UI tests use god mode and direct damage when exercising reward gates; those tests do not certify combat pressure. The human launch uses normal gameplay.

## Remaining work

D13c is scoped human-accepted and included in this checkpoint. The next selected D14a delivery is a recorded source floor's content allocation reviewed in ordinary canyon gameplay. Full boss/reward pools, native unlock/history/first-encounter/global-RNG rules, full actor equivalence and live expedition resume remain open. Current seeded probabilities are50/50 within the supported two-entry pool, not the full native Basement distribution. No further boss actor or broad parity implementation is selected.
