# PW-T01 — Cancer trinket

Selected 2026-11-16 after scoped Yum Heart acceptance. Main-game implementation and nine focused core suites pass. Actual Game/Renderer collection, drop, rebind, live tuning, Apply, export/load and retry pass. CLI schemas5/37/38/39 also pass; the ordinary main-game review launched successfully and subsequently closed normally. The user accepted the scoped playtest and requested a commit plus PW-C01 continuation; see [acceptance](human-acceptance.json). PW-C01, optional second examples and bulk parity remain unselected.

## Scope

One separate held trinket slot, Cancer `isaac:trinket:39`, distinct from collectible39. Its source contribution is +1 tear/second after the ordinary Tears curve and Sad Onion. The contribution can exceed the ordinary five-tear cap. Unowned/zero-strength effects preserve the baseline; a disabled zero-rate weapon stays disabled. Current firing waits and flying attacks are retained. Player movement, eight-direction controls, universal dodge and active-item settings remain unchanged.

Ordinary opening-floor combat's existing first-clear selector can produce variant350. This delivery resolves that outcome through an explicitly restricted **Cancer-only trinket pool**; it adds no independent reward roll or reroll. The native pool population, depletion across a full expedition, refill, golden/swallowed trinkets and complete source RNG/profile are not reproduced. Source factory execution against a supplied one-entry pool is evidence of Cancer eligibility/selection, not complete pool parity.

Ground actors have installed trinket animation timing (Appear35, Drop26, Collect16 at the explicit30Hz boundary). The original canyon brass double-scroll charm is presentation, not imported Isaac sprite artwork. Collection exchanges the one held slot. A swapped-out item stays at the incoming actor's position; U drops the held trinket onto a physically reachable unblocked location. Contact must be left before recollection, and overlapping actors cannot repeatedly swap within one step. Revisit retains actors and held ownership. Apply explicitly resets floor actors but keeps the held slot and settings. Floor advancement retains the held slot; retry creates a fresh build.

## Live configuration and persistence

Tuning → Shooting → Treasure → Trinkets: Cancer strength0–2x in5% steps, future clear rewards on/off, drop bindingU/Y. These are live, exported, loaded and remembered. Existing pending awards retain their resolved identity. Presets contain configuration, not trinket ownership.

Balance schema39 migrates schemas1–38 via exact additive content hashes. Campaignv9 records the held key separately from permanent collectibles and active charge; versions1–8 have an empty slot. Existing interrupted-expedition recovery is history, **not live save/resume**. PW-C01/D18's full resume question remains open.

## Evidence

`source/manifest.json` pins installed Repentance1.7.9b. Sixty native ordinary Tears/Onion/Cancer arithmetic cases and eight original trinket factory/eligibility cases are captured. `animations/manifest.json` pins installed trinket ANM2 metadata. The arithmetic supplies owned counts/effective multiplier and isolates unrelated contributions. Full cache scheduling, swallowed/golden effects, Mom's Box, complete pickup/drop wrapper, physics and inventory modifiers are not accepted.

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-cancer.py --check
python3 scripts/isaac-reference/extract-trinket-animation.py --check
```

## Developer checks and human review

[Core checks](core-tests.log): nine suites pass, covering Cancer, Yum Heart, Brother Bobby, Cricket, earlier treasure behavior, external mechanics packs, presets, native health and campaign contracts. Cancer covers60 native rate comparisons, appearance gates across30/60/120Hz, independent active/passive ownership, actual primary cadence, emitted attack/wait preservation, drop/recollect/same-kind swap, overlapping-contact gates, room/floor/Apply lifecycle, capacity and invalid-state refusal, source producer bounds and v9/v8 slot persistence. Earlier custom mechanics-pack trinket rules retain their existing behavior; this selected native slot supports Cancer only.

Natural witness: **seed1, displayed room5**, ordinary first-clear variant350/subtype39, pickup seed1416295006 with Luck0. Three dynamic room-size cases deliver exactly one physically reachable pickup; disabled rewards do not reroll, and a pending capacity-delayed birth retains its selected identity across live edits. This is a genuine encounter-clear result; no item is forced into the human review.

[Actual Game/Renderer check](game-input.log) exercises ordinary clear completion, mouse pickup, HUD drop, held/released U, walk-away/recollect, Y rebind, live strength/rewards, real panel export/load, staged Apply, remember, fresh launch and retry. Automated collection setup clears enemies and places the player on valid in-room floor; it does not replace the native award selection. An initial test-only doorway placement belonged to the adjacent room and was corrected without changing gameplay navigation.

[Ground charm](cancer-ground.png), [held HUD](cancer-held.png), [tuning panel](cancer-panel.png) were visually inspected. The [developer preset](cancer-preset.json) deliberately uses105% strength, rewards off and Y; it is for roundtrip testing. The human launch uses the original165% preset with default100% strength, rewards on and U.

[CLI validation](cli-validation.json) passes schemas5/37/38/39 with165% zoom and preserved accepted shooting. The original preset remains SHA256`77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`. [Yum Heart's actual-input regression](active-regression.log) also passes. See [validation summary](validation.json).

The normal interactive review launched successfully and subsequently closed normally; see [launch record](interactive-launch.json). Use this command to reopen it. No god mode, forced item or pre-cleared fight is used.

```sh
build/deathward --expedition --seed 1 --review-room 5 --mute --save /home/kambo/.local/share/deathward/reviews/pw-t01-cancer/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

1. Clear room5 and collect the brass double-scroll charm; inspect **U / DROP CANCER** and the faster firing cadence.
2. Press **U** and fire again; the held effect is removed immediately for subsequent attacks, with the current firing wait preserved.
3. Walk away, return to collect it, then revisit the room. The slot/effect should occur once.

Remaining: full native pool/refill/RNG, drop/collection wrapper/physics, cache scheduling and special-trinket/modifier interactions; full live save/resume. The proposed next delivery after acceptance is **PW-C01**, the four-category combined check. The user selected PW-C01 after accepting this checkpoint. Optional second examples remain unselected.


