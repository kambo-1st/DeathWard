# PW-A01 — Yum Heart

Selected 2026-11-16 after accepted Brother Bobby/Cricket checkpoint `d915e845`. Main-game implementation and developer checks are complete; the user accepted the scoped review and selected PW-T01. See [acceptance](human-acceptance.json). No other category or second example is selected.

## Enabled behavior

The ordinary opening-floor treasure pool now contains Sad Onion1, Cricket’s Head4, Brother Bobby8 and Yum Heart45 with equal supported weights. Natural Yum Heart witness: **seed2, displayed room8**. The prior Bobby witness moves to seed9/room8; Cricket remainsseed4/room8. These are restricted canyon-adapted pools, not complete native treasure selection.

Collect the centered red-heart pedestal to fill one active-item slot with four charges. **C** or the named HUD button uses Yum Heart: the shared red-health consumer requests two half-hearts, then the item discharges. Full red health or no red capacity still spends the charge. Red/bone capacity clamps healing; it does not convert the effect into soul health. Insufficient charge, dead/finished state and gameplay modals reject use. Held input cannot repeatedly activate it. Existing movement, camera keys, eight-direction firing, dodge and placed dynamite remain unchanged.

First hostile-room clears add one charge up to four. Revisit, duplicate clear, debug replay, empty-room entry, pause, loading a preset and Apply do not refill it. The floor-local paid-room ledger survives testing regeneration. Floor transitions retain the slot and its charge; retry begins with a fresh unowned build.

A full-slot pedestal transaction exchanges items and preserves the outgoing item's charge on that same solid pedestal. The player must leave contact before swapping back. Dropped charge survives room visits. Apply deliberately regenerates floor offerings with other pickups while retaining the owned slot/charge; it does not restore prior-floor dropped items.

## Live settings and persistence

**TUNING → SHOOTING → TREASURE → ACTIVES** edits healing in whole half-heart steps (1–6), recharge per eligible clear (0–4) and the dedicated binding (C/X/Z). Healing applies to the next use, recharge to future first clears; neither edit grants charge. Four-charge capacity stays fixed. The source defaults are healing2/recharge1/C. Pool changes, including **TEST: YUM HEART**, remain staged until Apply map changes.

Schema38 exports/loads/remembers these settings and migrates schemas1–37 through audited additive content fingerprints. Charge and ownership never enter the preset. The original165% user preset is unchanged: SHA256`77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`.

Campaignv8 records slot identity and charge in checkpoints/history, validates saved charge/ownership and reads versions1–7 without inventing an active slot. Existing interruption recovery remains a historical summary, **not full live expedition resume**. Full resume remains deferred PW-C01/D18 work.

## Evidence and limits

[source/manifest.json](source/manifest.json) pins Repentance1.7.9b. Reproduce without modifying the installation:

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-yum-heart.py --check
```

- 56 original owner amount/AddHearts cases, including full/no red capacity and bone containers; 53 living-owner cases compared through actual DeathWard use.
- Seven ordinary discharge cases through original SetActiveCharge, bypassing only the SEH prologue; full charge becomes zero independently of red-health amount.
- 15 original clamped primary-charge writes, compared through actual DeathWard encounter completion.
- 24 native room-type/shape award cases: the ordinary normal shape gives one; specified large native shapes give two. DeathWard retains canyon shapes and uses one per first hostile clear, independent of dynamic area. This is an explicit adapter, not source size/shape parity.
- Source item45 XML declares maxcharges4 and treasure weight1. The effect leaves its default discharge result true at full health; the normal caller discharges after the effect.

The full native use/input/animation/pickup factory/co-op/room-clear scheduler, batteries, pocket/extra active slots, modifiers and synergies are not certified. Initial full-charge acquisition, physical pedestal/contact and the testing-regeneration policy are scoped gameplay behavior; complete native pickup-wrapper acceptance remains open.

Eight focused core suites pass, including campaign contracts, native health, presets and earlier treasure/familiar regressions. Three actual Game/Renderer modes exercise Yum Heart, Brother Bobby and Cricket. Yum checks use actual mouse pickup/button, keyboard hold/rebind, encounter completion, second-pedestal swap, live/staged settings, Apply, export/load/remember and retry. CLI schemas5/37/38 load successfully with165% zoom. See [validation](validation.json), [core tests](core-tests.log), [campaign tests](campaign-tests.log), [input checks](game-input.log) and [CLI results](cli-validation.json).

[Pedestal preview](yum-pedestal.png), [used item/HUD](yum-used.png), [tuning panel](yum-panel.png). The exported [developer preset](yum-preset.json) deliberately uses healing3/recharge2/X and fixed Yum Heart; the human launch uses the original preset and source-default active settings.

## Human review

Interactive launch verified with normal health, source-default active settings and165% zoom; see [launch record](interactive-launch.json).

```sh
build/deathward --expedition --seed 2 --review-room 8 --mute --save /home/kambo/.local/share/deathward/reviews/pw-a01-yum-heart/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

1. Walk into the red-heart pedestal; inspect **C / YUM HEART 4/4**.
2. Take a hit in an ordinary encounter, then press **C**. Check the healing and **0/4** charge.
3. Clear four hostile rooms and use it again. For the additional swap check, select **TEST: YUM HEART** under Treasure and Apply while holding it. The regenerated pedestal exchanges the item and preserves the old charge; step away and back to exchange again.

Remaining: native wrapper/synergy/save-resume gaps above. The user explicitly selected **PW-T01 — Cancer** next; PW-C01 and optional second items remain unselected.
