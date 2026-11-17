# Prospector Exchange removal — 2026-11-17

The user accepted D13b and requested its commit (`6062cb35`), then selected removing Prospector Exchange. The removal is implemented and developer-verified; the user acknowledged the result and authorized this checkpoint commit.

Removed: the service identity, generated trader, X minimap marker, two resource-conversion offers and smoke entry. Former slots become quiet empty rooms. The reserved shuffle slot and room-content exclusion preserve other specialists’ seeded sites and source-template candidate ordering. Surgeon, Smuggler and ordinary shops remain. No new tuning setting, preset version or mechanics fingerprint change is needed; existing presets and their application boundaries remain compatible.

Validation:

- Before/after comparison of108actual floors across18expedition seeds:71Exchange rooms become empty;98retained specialist rooms and all other room roles are unchanged. Exact role snapshots and summary are included.
- Existing service transactions, once-only purchases, health previews, floor carry-over and zero-resource reachability pass across98floors through `deathward_expedition_economy_tests --services-only`. A production-configured former Exchange site refuses opening a shop or converting resources and stays outside source-room content selection.
- Actual Game/Renderer shows seed4/displayed room2 with the user's165% preset: no trader, dialog or X marker. Remaining Surgeon/Smuggler mouse and keyboard purchases, pause guards, health previews and legacy boss-reward dismissal pass. Screenshot: `artifacts/removed-exchange.png` in the workspace.
- Duke and Monstro loop regressions pass. The removed `--scene service-exchange` is rejected. Browser smoke references and JS syntax are updated; browser execution was not run.

A freshly linked **pre-removal** full `expedition_economy` suite already failed `all supported items obtainable across pools` with the current catalog. Its old pool assertion remains unchanged; the dedicated service mode does not run it and is not described as a full-economy pass.

Review after restarting the rebuilt game:

```sh
build/deathward --expedition --seed 4 --review-room 2 --mute --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json --save /home/kambo/.local/share/deathward/reviews/removed-exchange/campaign.save
```

The user acknowledged the removal ("ok, cool") and approved committing it. The original user preset is untouched (hash in `verification.json`). Historical study/audit references are preserved as history. Broader native pools and live expedition resume remain outside this change.
