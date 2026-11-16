# PW-C01 — combined category check

Selected after accepted PW-T01; active/trinket checkpoint committed as `27d7691c`. Main-game implementation and developer verification pass. Scoped human review is accepted; the user authorized committing this checkpoint and selected PW-T02 Whip Worm next. No second item examples or catalog expansion are selected.

## Review setup

`--expedition --review-powerups` uses the normal main-game renderer, generation, pickup consumers and combat. It explicitly labels **test offerings**, because ordinary opening floors currently have only one supported treasure collectible. No natural all-item seed is claimed. One centered solid pedestal offers Sad Onion1, Cricket4, Bobby8 and Yum Heart45 in sequence; step away before collecting each next offering. Cancer is a labelled preplaced test actor using its ordinary pickup path. No items are pre-granted. Encounter and boss travel buttons shorten setup, without healing, resetting charge, killing enemies or changing damage/HP/speed. They are available only after the offerings and when the current room is clear.

Existing source values, accepted165% preset and live settings remain. Review selection is a launch/test aid, not exported balance data. Presets continue to contain configuration only. Apply regenerates normal floor content, ends the staged review offerings and retains owned build/slots; retry with the review launch aid starts unowned with the staged offerings again. Floor advancement preserves owned state and review travel but creates no additional review offerings.

## Save audit

The real campaign path is `Game::checkpoint → configuredSummary → CampaignStore::checkpoint`. It stores summary inventory, active identity/charge and held trinket. `Game` construction calls `CampaignStore::recover`, which resolves pending records as an interrupted expedition; it does not reconstruct a live Simulation.

A summary omits player injury/position, consumed pickup actors and their phase, per-room encounter/reward state, dropped active charges, the paid-clear ledger, RNG streams, current timers and live familiar/projectile state. Recovering only the newly added slots would duplicate rewards and lose injuries/charges/room progress. There is no sufficient small slot-only fix. **Full live save/resume remains D18 work and is not claimed by PW-C01**; configuration reload and interruption history will be verified separately.

## Verification

- `combined-tests.log`: actual Simulation pickup consumers, both attack sources, Cricket/Onion/Cancer composition, real ordinary combat clear and once-only Yum recharge, drop/recollection, floor transition and Apply; three dynamic room sizes and ordinary-mode isolation pass.
- `core-tests.log`: eight focused suites pass (combined categories, Cancer, Yum Heart, Bobby, Cricket, treasure upgrade, preset contract and core contracts).
- Boss completion in the transition fixture is controlled with `clearRoomDebug`; the actual floor transition and category reconstruction follow normally. This is not a boss-balance acceptance test. The ordinary encounter is cleared through actual attacks.
- The Game/Renderer fixture temporarily sets health to four half-hearts before using Yum Heart to verify healing; the interactive launch starts at the accepted six half-hearts. Neither launch mode nor travel grants health, ammunition or charge.
- `game-input.log`: actual Game/Renderer mouse acquisition of all offerings, real combined combat, C/U controls, drop/recollection, pause, live configuration/export/load, floor transition, Apply and fresh-build retry pass. Recovery from a real copied checkpoint preserves item/slot state in interrupted history, resolves once and creates no live Simulation. Ordinary preset loading grants no items and enables no review fixture.
- `cli-validation.json`: the actual main executable loads the unchanged original schema5 preset and the exported schema39 preset, retaining map/route/zoom, player and category settings; both start unowned at six half-hearts without god mode. CLI loading remembers staged map configuration for generation.
- `cli-invalid.json`: missing expedition mode and conflicting review options reject before launch.
- Visual checks: the review panel shrinks during combat; fight travel uses clear interior floor rather than a camera-obscured canyon entry lip. Setup, build, combat and next-floor captures are preserved below. Existing game visuals and geometry are unchanged.

## Human review

Launch from the repository root:

```sh
build/deathward --expedition --seed 1 --review-powerups --mute --save /home/kambo/.local/share/deathward/reviews/pw-c01-category-check/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

1. Collect all four pedestal offerings, stepping away between each, and the Cancer charm beside it. **Tab** lists the owned build.
2. Choose **NEXT ENCOUNTER**. Fire with Bobby; use **C** for Yum Heart and **U** to drop Cancer. Walk away and return to collect it again. A first hostile-room clear adds one active charge.
3. Optionally choose **BOSS / THEN FLOOR EXIT**, defeat the boss and use the floor exit. The four-category build continues onto the next floor. Retry starts a fresh unowned review with the same settings.

Apply map changes ends the test offerings/travel and resets floor content while keeping the owned build. It is not a gameplay-save reload. The original user preset is preserved byte-for-byte.

The scoped combined human playtest is accepted; see [acceptance](human-acceptance.json). Remaining: Full native actor/cache/pool/physics parity and complete gameplay resume remain open. PW-T02 Whip Worm is selected next; other optional examples and catalog expansion remain unselected.

## Captures

[Setup](categories-setup.png), [owned build](categories-build.png), [combined combat](categories-combat.png), [next floor](categories-next-floor.png).
