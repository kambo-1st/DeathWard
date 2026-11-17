# D13a — Monstro, collectible and descent

Selected by the user on 2026-11-17. Implemented in the main game and developer-verified. The user accepted the scoped interactive review on 2026-11-17 ("nice thx, it works!") and authorized this checkpoint commit. See `human-acceptance.json`; full native parity remains open.

Opening-floor ordinary canyon expeditions select ordinary Monstro20.0.0 as the one supported boss. Installed Basement and Burning Basement pools list Monstro; the complete native selector, first-encounter/history/unlock/replacement and seeded-pool behavior are **not** implemented by this bounded selection. Mine, Classic, tutorial and later floors retain their existing bosses.

The recovered controller uses source hop/spit/large-jump states, event frames and 13 aimed / 18 independently randomized radial projectile payloads. Source HP250/stage0 converts with the same retained ×3.2 unit as player Damage3.5→11.2. Regular enemy HP tuning excludes this boss. Movement and planar shots use the fixed D04–D06 base-player-relative scale; body radius40 uses the accepted Gaper radius.6/source13 ratio. Vertical flight, render geometry, canyon wall collision, RNG stream and live actor scheduling are explicit adaptations. No player speed, firing, dodge or input changes are intended.

A normal kill clears hostile attacks and unlocks one centered solid pedestal containing Breakfast25, replacing the legacy boss menu/money/dynamite payout for this encounter. Installed item XML declares maxhearts2 then hearts4: one red-heart container plus up to two hearts of red healing, capped by the shared health model. It is permanent and does not replace the held active item. An occupied pedestal birth footprint waits until the player leaves. Collection is once-only; the empty base persists. The existing exit and floor transition carry health and owned categories. Reward collection is optional for descent.

TUNING → ENEMIES → MONSTRO exposes health, movement and shot speed in5% steps (10–300%). Health preserves live injury fraction; emitted/queued volleys retain birth speed. Boss-selection changes are staged until Apply map changes. Schema43 exports/loads/remembers settings and migrates the audited old catalogs; existing map/view/player settings are retained.

## Verification

- Application and test targets build. Native48 decision/32 force/24 projectile payload cases and animation metadata checks pass.
- Five focused suites pass: Monstro boss loop, core contracts, preset contracts, Book of Shadows and treasure upgrades. Three generated sizes exercise actual damage death, reward gating, health/active/trinket/familiar ownership, once-only collection, revisit and descent. Attack checks cover13/18-shot emission, airborne contact windows and pending-volley birth settings.
- Actual Game/Renderer `--monstro-only` passes mouse boss tuning, export/load, mouse collectible collection, mouse exit/descent, Apply and retry. UI setup uses developer god mode and a damage event for the kill; it does **not** certify human pressure balance. Direct user review starts with6 half-hearts, no items and god mode off.
- Separate CLI launches with schemas5/42/43 pass. The user's original165% preset SHA256 remains `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`.
- An additional Peep `monster_boss_components` suite passes its ownership/phase/geometry checks but fails its150-second starting-kit bot. The same failure is reproduced with the original `13bd0b4b` mechanics catalog and D13 disabled, using the unchanged Peep branch. This is not a full historical-binary comparison. No Peep behavior or failing assertion was changed; see `peep-legacy-catalog-check.json`. It is not counted among the passing suites.

Initial failures included the old validation prohibition on boss stage-health profiles (now narrowly permits ordinary Monstro), stale schema/hash mutation fixtures (updated), and UI setup/expectations (player height and auto-descent during mouse travel corrected). Final results are in `validation.json`, `focused-tests.log`, `game-input.log` and `cli-validation.json`.

## Human review / next step

From the repository, run this one line:

```sh
build/deathward --expedition --seed 69 --review-room 9 --mute --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json --save /home/kambo/.local/share/deathward/reviews/first-floor-d13a/campaign.save
```

1. Fight Monstro using the existing eight-direction shooting and universal dodge. Check the hop, spit, larger jump and landing volley; judge pressure before changing damage or HP.
2. After defeat, touch the centered Breakfast tin. Starting from full red health, it takes three full red hearts to four. The pedestal pays once and stays solid afterward.
3. Click the NEXT FLOOR exit marker, or approach the exit and press E. Check that the new floor loads and the extra container/owned build remain. You can descend without taking the reward.
4. If you die, Retry returns directly to the same boss encounter with the applied settings. TUNING → ENEMIES → MONSTRO changes boss values; changing the selected boss requires Apply map changes and resets this floor's encounters.

The user has accepted this scoped review and requested its commit. Next proposed: **D13b — ordinary Duke of Flies**, including its summoned flies, the established collectible/descent path, live tuning/export/load and a short main-game review. This proposal is not yet selected; no D13b implementation is included.

Full native boss wrapper/appearance/death scheduling, targeting/grid/RNG, status/item/collider behavior, boss/reward pools and live expedition save/resume remain unfinished. The earlier archived Monstro report is research, not acceptance of this delivery.
