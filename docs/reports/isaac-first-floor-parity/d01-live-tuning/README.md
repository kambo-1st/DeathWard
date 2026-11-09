# D01: main-game Speed tuning, presets and retry

Updated 2026-11-09. **Implemented in the main game; developer checks pass; human acceptance pending.** This is configuration infrastructure using the existing accepted walking calibration, not new Isaac movement or first-floor parity acceptance.

## Visible delivery

- The normal expedition HUD has **TUNE SPEED**. Pause also offers **TUNING**. Both open the same panel in the main `deathward` executable, without enabling debug controls.
- Speed changes in 0.10 steps, with an editor range of 0.10–2.00. Changes affect the existing walking consumer on the next simulation step after resuming. Input mapping, immediate stopping, universal dodge, health, shots, enemy HP and room generation retain their previous behavior. The range is an editor constraint, not a newly verified native cap.
- The panel labels **CUSTOM / SPEED** or **REFERENCE / PARTIAL**. It displays current health and actual next-shot damage, including the current base 24 versus source base 3.5 distinction. Firing cadence is derived from the runtime consumer. Range/Shot Speed remain labelled adapted and Luck effects pending. Only Speed is editable/exported in D01; other mechanics extend this contract in their selected deliveries.
- **EXPORT**, **LOAD AND APPLY**, **USE NEXT EXPEDITION**, and **RESET SPEED TO 1.00** work. The file path can be edited, pasted or copied. Applying a preset does not heal, grant/remove items, reset money/keys/rooms or advance combat RNG.
- Enter on death or the death summary retries the same expedition seed directly. Death consequences are resolved once; retry creates a new expedition with normal starting health and the current Speed configuration. It does not rewind the campaign. Tutorial/account/theme/pacing setup is retained within the current session's retry context.
- `--seed NUMBER` provides an explicit repeatable launch seed. `--balance-preset PATH` loads and remembers an exported preset. Normal direct launch remains `--expedition`.

## Preset and persistence contract

Each campaign path has a sibling directory named `<campaign-file>.balance`:

- `export.json`: default human-editable export/load path; an arbitrary chosen JSON path can also be used.
- `next.json`: a resolved snapshot selected by **USE NEXT EXPEDITION**, automatically loaded for future expeditions and application restarts using that campaign.
- `revisions/<revision>.json`: immutable configuration snapshots referenced by the existing checkpoint/history mechanics fingerprint. No campaign save-format migration was introduced.

The version-1 JSON includes resolved Speed and matching custom overrides, source version/executable provenance, retained exceptions, the existing walking calibration, a configuration contract version, DeathWard content version and mechanics fingerprint. It is self-contained for D01's supported Speed parameter. Loading rejects unknown/missing/duplicate fields, unsupported schema/content, inconsistent overrides, changed reference/exception fields, nonfinite/out-of-range values and oversized files. Validated exports use a temporary file and atomic replacement. A bad remembered preset is reported and blocks launch until a valid preset or an explicit reference reset is selected; it never silently launches default settings.

Live edits, exported files and the next-expedition snapshot are distinct. Resetting/applying Speed does not silently overwrite the remembered next preset. **USE NEXT EXPEDITION** is the explicit persistence action. A same-session death retry retains current live Speed, including unsaved changes. Loading configuration does not restore gameplay state; full mid-expedition save/resume remains D18 work.

## Human check

1. Walk, click **TUNE SPEED**, press **−0.10** twice, then **BACK**. Walking should be visibly slower; dodge and firing should feel unchanged.
2. Open tuning, **EXPORT**, then **USE NEXT EXPEDITION**. Close and relaunch using the same campaign path. Tuning should show Speed **0.80** and the remembered next-expedition value.
3. **RESET SPEED TO 1.00** restores the baseline immediately; use **USE NEXT EXPEDITION** to retain that reset. On death, **Enter** retries the same seed without a hub visit.

The tested main-game launch and process details are recorded in `interactive-launch.json` after opening the review. It uses a dedicated review campaign, while the feature is available in ordinary main-game expeditions as well.

## Verification

- Application, input verification, preset and player-Speed targets built successfully without new warnings.
- `balance_preset_contract` and `player_speed_attribute`: 2/2 pass. Preset checks cover exact float/revision round-trips, 19 invalid-input cases and safe export failure. Existing movement checks cover normalized diagonals, immediate stopping, click routes, independent shooting, retained dodge and floor transfer.
- Actual `Game`/`Renderer` input mode `--balance-only` passes: live HUD/pause buttons, modal input capture, measured 0.80 walking ratio, export/load/remember, state preservation, invalid-load isolation, path paste/cancel, immediate and summary death retry, floor transfer and fresh Game construction. A corrupted remembered preset is reported and an explicit reset recovers it.
- Existing `--hud-only`, `--keyboard-only`, and `--arrows-only` modes pass. These include ordinary menu interactions and firing controls.
- Two separate `deathward` executable processes pass: the first loads the exported 0.8 preset by CLI; the second, with no preset argument, restores Speed 0.8 from the same campaign's remembered snapshot. These short scripted launches verify application persistence; the input mode above verifies actual ordinary expedition movement and UI behavior.
- Rendered tuning and death-retry captures were inspected. They are retained as `tuning-custom.png` and `death-retry.png`.
- The first application persistence invocation used an unsupported `--no-audio` flag and exited before launch. It was corrected to the existing `--mute`; both corrected invocations passed. No gameplay or preset failure was concealed by that command correction.

See `validation.json`, retained logs and `speed-080.json`. Developer verification is not the user's acceptance and does not change native-parity counts. **Remaining:** the user's D01 playtest; D02 source-scale walking and later deliveries; exact first-floor eligibility/generation rules, native actor/item acceptance and full first-floor integration. No commit or bulk implementation is included.
