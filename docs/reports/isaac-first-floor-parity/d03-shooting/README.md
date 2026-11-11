# D03: shooting controls in the main game

Updated 2026-11-11. **The user accepted the scoped main-game D03 delivery and requested a commit plus preset backup. Developer checks pass; full native shooting acceptance remains open.** This delivery extends the existing accepted shooting consumers and the D01/D02 preset system. It does not replace the accepted spatial calibration or enable the private native enemy candidates.

## Accepted preset backup

The exact user export was preserved on 2026-11-11 in [user-preset-2026-11-11.json](user-preset-2026-11-11.json) and a timestamped sibling `backups/` file beside the original export. [Backup manifest](preset-backup.json) records both paths, SHA-256 and byte equality; the source was not modified. This is the user's chosen configuration, separate from the reference defaults: **Tears 1.9272734, Shot Speed 0.9, Range 6.5, Speed 1, room size 110%, minimum/maximum 7/9 half-tiles, route length 26%, zoom 165%**. It does not certify native Isaac parity.

To restore that exact configuration without relying on the external export:

```sh
build/deathward --expedition --seed 1866 --mute --save /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save --balance-preset docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json
```

The developer handoff below records the earlier schema-4 preset (routes 30% and baseline shooting). The backed-up schema-5 preset above records the user's subsequent playtest choices. Human acceptance is scoped to this delivery and chosen configuration; the remaining source-equivalence gaps are unchanged.

## Playable handoff

Use the ordinary main executable and the user's existing map/view export:

```sh
build/deathward --expedition --seed 1866 --mute --save /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

Open **TUNING → SHOOTING**. The original schema-4 export still loads: Speed 1, rooms 110%, range 14–18 terrain tiles before scaling, routes 30%, zoom 165%. Missing shooting fields receive the accepted baseline. Loading never rewrites the source export. New exports use schema 5 and work with the same CLI flag. `--balance-preset` remembers the loaded settings before generating an expedition; without that flag, the same save path loads its remembered `next.json`.

Three short checks:

1. Stand and shoot, then walk while shooting. Confirm the accepted base feel and eight firing directions. Increase **Tears** and fire again: shots arrive more often; their launch speed and configured reach stay the same.
2. **Reset shooting base**, increase **Shot Speed**, and shoot again: faster travel with the same configured reach. Reset again and increase **Range**: farther travel at the same launch speed. Walls and targets can end a shot sooner.
3. Choose your settings, **Export**, then **Use next expedition**. Relaunch with that exported file (or the same save path without the preset argument) and check the three values and their effects. Reset restores exactly 30/11 Tears, 1 Shot Speed and 6.5 Range without changing movement, map or view selections.

Tuning pauses the simulation. Close with Escape to observe each change. Death retry uses the active shooting settings. Ordinary floor descent retains them; fresh expeditions use the remembered preset. No separate review executable is required to play this delivery.

## Controls and application boundaries

| Base stat | Accepted default | Button step | Editor bounds | Gameplay effect |
| --- | ---: | ---: | ---: | --- |
| Tears | 30/11 ≈ 2.73 shots/s | 0.10 | 0.10–10.00 | Independent nominal firing rate. |
| Shot Speed | 1.00 | 0.05 | 0.10–3.00 | Independent launch-speed multiplier. |
| Range | 6.50 source-stat tiles | 0.25 | 0.50–20.00 | Independent configured travel budget. |

These bounds are testing limits, not claims about Isaac's stat caps. The panel also shows the next volley rate/count and attack values after current authored upgrades; actual damage is displayed rather than the unused stored source Damage 3.5. Existing modifier composition remains in the shared attack resolver, so changing a base does not multiply an upgrade twice or discard the build.

Edits affect newly constructed attacks. The current firing cooldown completes unchanged; editing Tears repeatedly cannot grant an immediate shot or bank extras. Already emitted projectiles and queued birth specifications retain their birth properties. Subsequent shots resolve the new base plus current upgrades. Existing fractional held-fire carry remains enabled. There is no artificial three-projectile cap.

Shooting changes do not apply or discard pending map edits. Export/remember includes the pending map selection, just as D02 did. Loading applies player/shooting/view settings immediately and stages map differences until **Apply map changes**. Applying the map still performs the previously authorized testing regeneration, including its floor encounter/reward reset; it retains the active player stats/build.

Schema 5 (`d03-shooting-v5`) stores resolved values, explicit overrides, unchanged source provenance, the accepted shooting-calibration identifier and retained control exceptions. Schemas 1–4 migrate with baseline shooting. Invalid values, incompatible content/reference metadata and mismatched overrides reject the entire candidate before a runtime update. Presets remain configuration files, not gameplay save files.

## Comparison and verification

The preserved Repentance 1.7.9b reference supplies the nominal baseline stat values and bounded flight/inheritance arithmetic. The already accepted production conversion remains explicit: Shot Speed 1 launches at 8 DeathWard world units/s; Range 6.5 budgets 11 world units; nominal Tears schedules an interval of 11/30 seconds. Movement, starting health, damage 24, enemy HP, eight-direction controls and universal dodge are unchanged.

The existing flight verifier replays 171 independent preserved native states. Actual Game input checks all eight directions at 30/60/144 input partitions, expiry, near/medium/far targets, intervening walls, dodge and forward/transverse/backward motion inheritance. The inherited factor remains 0.6 with backward projection removed. At accepted walking 4.8, forward inheritance adds 2.88, giving launch 10.88; stationary launch is 8. This is evidence for the bounded arithmetic and existing adapter, not complete native actor/collision equivalence. `shooting-measurements.csv` also contains explicitly labelled historical comparison modes; those rows are not current defaults.

Independent-stat rows report 22 root volleys over the baseline eight-second test and 44 with doubled Tears; raising Shot Speed changes launch 8→12 without changing that count or the 11-unit cap; doubling Range changes the cap to 22 without changing launch or count. Last-observed positions can be up to a sampling step short of expiry; they are not the configured distance itself. Input partitions are simulation consistency checks, not a performance claim.

Four focused CTest suites pass: preset contract, canonical attributes, Speed consumer and canonical shooting integration. The actual Game/Renderer D03 test exercises mouse and keyboard controls, generated canyon shots, independent settings, live cooldown/bullet retention, owned Rail modifiers, invalid-load isolation, pending-map preservation, export/load, floor transfer, death retry and a fresh Game instance. The D01/D02 UI regression passes. The application and all executed targets build successfully.

Separate main-executable processes load the exported custom shooting preset, load its remembered configuration without the CLI preset flag, and load the user's original schema-4 export. Logs verify the same resolved values; the original export's SHA-256 is unchanged. See [validation.json](validation.json), [CLI verification](cli-verification.json), [example preset](custom-shooting.json) and [panel capture](shooting-panel.png).

## Remaining work and next selectable delivery

- The user accepted D03's scoped main-game delivery on 2026-11-11; no further D03 controls review is currently requested.
- Exact shared native room/projectile scale, live firing-counter and emission scheduling, complete ballistic actor/flag/child behavior, height-dependent collision/hit geometry and source item/cache formulas remain open. This is a scoped controls/integration delivery, not completion of the original plan's full 1:1 shooting target.
- Range is independent of dynamic room sizing; resizing does not silently shorten or extend bullets to half of every room. The user's chosen map/view settings remain separate from source-stat values.
- D02 exact spatial/clearance/generator acceptance, coordinated damage/HP, enemy acceptance and complete first-floor rules remain unfinished. The wider bulk effort remains paused.
- Following the accepted shooting review, **D04 — one correctly moving Gaper in an ordinary generated encounter** is the next selectable delivery. D04 is not selected or implemented by this work; retain the enemy-movement-before-HP gate.
