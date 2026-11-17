# PW-A02 — Book of Shadows / one active slot

Selected on 2026-11-17 after scoped Halo acceptance. Halo is committed as `5945b526`. Book is implemented, developer-verified and scoped human-accepted. The user accepted the playtest and requested its checkpoint commit: “ok, cool, commit... Then Whats next (discuss)”. See [human acceptance](human-acceptance.json); no next delivery is selected.

The player holds one usable active item. Collecting Book58 replaces Yum45 and leaves the outgoing item on the same solid, centered pedestal with its charge intact. Leaving contact rearms pickup; swapping back restores that item's charge. Passive collectibles and familiars remain owned for the expedition. Trinkets retain their separate held-slot rules.

## Source and scope

The installed Repentance1.7.9b XML supplies Book58, three charges, cooldown300 and treasure weight1. [The native capture](source/manifest.json) executes the ordinary temporary-effect constructor/add, all300 update ticks and effect-vector removal, effect-presence queries, additive repeat use, and12 primary recharge cases. The generic use caller and damage-protection branch are disassembled; full wrappers are not executed. The fixture supplies item definitions/player/vector state, emulates CRT memmove and intercepts costume removal. Reproduce with:

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-book-of-shadows.py --check
```

DeathWard adapts300 effect ticks to10 seconds of active gameplay at30Hz. Duration is independent of the held slot, dodge and hurt immunity. Reuse adds its snapshotted duration; swapping, pauses, tuning and configuration loads do not restart it. Room transfers, testing regeneration and floor transfers retain its remaining duration; this is an explicit DeathWard lifecycle policy, not verified native transition equivalence. Ordinary damage including enemy contact/projectiles and placed dynamite uses the shared protection gate. Unimplemented native special damage bypass flags, battery/pocket/co-op/synergy behavior and full scheduling/physics remain outside this delivery.

## Configuration and state

- TUNING → SHOOTING → TREASURE → ACTIVES → BOOK OF SHADOWS: duration1–30seconds in0.5s steps; recharge0–3 in whole charges. Duration applies at next activation, recharge at future first hostile-room clears. The use binding remains shared C/X/Z.
- Three charges per use; default+1 per eligible first clear. Existing clear ledger prevents re-awards on revisit/debug replay/Apply. Preset operations never refill charge or extend current protection.
- Schema42, contract `pw-a02-book-of-shadows-v42`, migrates schemas1–41 through audited additive catalog fingerprints; full pending map/view/player/shooting settings remain intact. The original165% preset is unchanged.
- Ordinary restricted treasure mode1 selects source-ordered `[1,4,8,10,45,58]`; mode6 is an explicit fixed-Book test setting staged until Apply. The expanded pool changes deterministic item outcomes for existing seeds. Full native pools/depletion/caller RNG are not claimed.
- Campaignv11 records Book identity/charge in the existing interrupted-expedition history format. This is not a live Simulation resume: active timers and world-pedestal state are not restored after application restart. Full live resume remains D18 work.
- `--review-actives` stages two clearly labelled test offerings on a real main-game treasure pedestal: first Yum, then Book. Start unowned at normal health; no forced charge grants after collection and no cleared enemies. Retry recreates the review; Apply regenerates floor content and ends its staged sequence while retaining the held build.

## Verification

- Build and11 focused suites pass: Book, Yum, Halo, Bobby, Cancer, Whip, combined categories, Cricket, treasure, core contracts and balance presets. Covers different-active swaps, passive/familiar ownership, first-clear charges/caps, room/floor/Apply/retry boundaries, interruption history, input rearming, damage admission, actual projectile/blast protection and expiry at30/60/120Hz.
- Actual Game/Renderer Book pickup/swap-back, key use, pause/expiry, shared rebind, live controls, export/reset/load, encounter shortcut, first-clear charging, Apply and retry pass. The clear-charge check explicitly removes enemies through a developer fixture before ordinary Game completion; it does not certify manual combat feel. Yum/Halo/Bobby/Cricket interface regressions pass. Halo uses fixed mode5 on its old seed38/Pooter route because the expanded pool changes that seed's item; natural Halo is now seed9/room8.
- Separate application processes load schemas5/41/42, preserving165% zoom. Duration9.5/recharge2 roundtrip reaches the actual main-game consumer. Invalid configuration is rejected; the user's original preset hash is unchanged.
- Ordinary six-item pool: source-recorded Book58 appears naturally at **seed5, displayed room8**. The labelled swap review below uses staged offerings for reliable access to both items.

See [validation](validation.json), [focused tests](focused-tests.log), [Book interface log](ui-book-of-shadows.log), [CLI checks](cli-validation.json), [pedestal](book-pedestal.png), [protection HUD](book-protected.png) and [live controls](book-panel.png).

## Short human review

```sh
build/deathward --expedition --seed 1 --review-actives --mute --save /home/kambo/.local/share/deathward/reviews/pw-a02-book-of-shadows/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

1. Touch the heart pedestal to take Yum. Step away and touch it again to take Book. Yum remains on the pedestal.
2. Step away and return to swap back, then repeat to reclaim Book. Each item keeps its own charge; only the held item appears in the active slot.
3. Choose **NEXT ENCOUNTER**, press **C**, and observe the protection rings/countdown. Protection ends after10seconds; combat clears recharge the held item. Universal dodge still works independently.

The encounter button moves to an ordinary uncleared room without healing or refilling charge. The review starts with normal health and no owned items. Source/native acceptance is distinct from this human check.

## Remaining work

The scoped main-game review is accepted and included in this checkpoint. Full native wrappers, scheduler/transitions, special damage flags, synergies and pools/physics are not accepted. Broader item catalog and full live expedition resume remain deferred.
