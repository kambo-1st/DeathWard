# D14a.1 — Screw boss reward and wider zoom

Selected by the user on 2026-11-17 after the recorded D14a boss reward. Implemented in the main game and developer-verified. Seven focused core suites,258 original-code arithmetic cases, the actual Game/Renderer lifecycle check and two CLI preset versions pass. The user accepted the scoped Screw/wider-zoom playtest on 2026-11-17 ("ok, its greeate!"). This is scoped gameplay acceptance, not full native equivalence.

## Playable scope

Opening-floor source boss pedestals can offer Breakfast25 or Screw255. **TUNING → ENEMIES → BOSSES → REWARD** stages that choice until **Apply map changes**. This testing action regenerates the current floor, retaining the player/build and expedition identity while resetting floor encounters and rewards. Existing/new defaults remain Breakfast; the dedicated Screw review preset selects Screw. This is a bounded fixed choice, not the complete native boss reward pool.

Screw is a permanent, stackable passive collectible. It does not occupy or replace the usable active item. It increases the underlying ordinary Tears contribution by0.5 per copy and Shot Speed by0.2 per copy at reference strength. Sad Onion and Screw contributions combine before a single ordinary tear curve; Cancer applies afterward. Whip Worm adds after Screw's Shot Speed contribution. The existing editable Tears baseline uses the documented inverse adapter; the accepted base is not silently replaced. Disabled fire/custom rates at or above the ordinary cap retain their prior behavior. Range, damage, health, walking and controls are unaffected.

The two effect strengths are independent live0–200% controls in5% steps. Edits affect new shots; the current firing wait and emitted projectile specifications remain unchanged. Schema46 exports, loads and remembers both strengths and the staged reward choice. Schemas1–45 retain Breakfast and default Screw strengths, their previous boss selector and all existing settings. Only exact additive mechanics-catalog fingerprints migrate.

Manual wheel/Page Up/Page Down zoom and the saved default now share **25–500%** bounds. Default edits remain immediate and support export/load/remember; manual zoom remains temporary. The user's original165% preset is preserved.

The centered physical pedestal uses the existing collection, collision, once-only/revisit and descent paths. Screw has an original small steel screw model on that pedestal. This delivery does not replace room geometry, controls, enemy behavior or accepted balance.

## Native evidence

`scripts/isaac-reference/capture-screw.py` executes the preserved Repentance1.7.9b binary under the existing bounded emulator; it does not modify the running source game. Executable SHA256 is `04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.

- 240 tear cases execute the original owned-item query/contribution and ordinary curve, with supplied base tear stat and Sad Onion contributions. The source Screw block sums applicable counts and multiplies by0.5. Other item counts in that block are explicitly zero.
- 18 shot cases execute the ordinary source cache block with real Screw count and optional Whip Worm. Its neutral cached-effect multiplier is explicitly1. The bounded ordinary block adds0.2 per copy; Whip adds0.5.
- The preserved XML lists Screw in the boss pool with weight1 and no item achievement gate. The live D14a capture independently observes Screw255 on the defeated Duke's pedestal. Neither fact verifies the complete native pool selection wrapper/RNG.

`source/manifest.json` preserves byte-window and XML hashes, fixture conditions and limits. CSVs contain all outputs; assembly retains the relevant original instructions. `PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-screw.py --check` passes258 comparisons.

## Human check

From the repository root:

```sh
build/deathward --expedition --seed 1 --review-room 9 --mute --balance-preset docs/reports/isaac-first-floor-parity/d14a1-screw-reward/screw-preset.json --save /home/kambo/.local/share/deathward/reviews/first-floor-d14a1/campaign.save
```

This enters the generated Duke room directly with normal starting health, no granted items and the original165% view/map/shooting preset. Defeat Duke and the remaining flies, collect the steel screw from the center pedestal, then fire and descend. The firing rate and bullet speed increase; the maximum shot distance stays unchanged. On death, retry returns to the same encounter. Use the wheel or Page Up/Page Down to check the wider camera limits. To retain a chosen view, use the existing default-zoom control and export/remember it.

The review preset enables the existing seeded two-boss policy and fixes the reward to Screw at100% effect strength. It does not reproduce the complete recorded source floor or its original seed. The user's original preset remains unchanged: SHA256 `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`.

## Developer verification

- Seven focused core suites pass: Screw reward, balance presets, treasure upgrade, Whip Worm, Monstro loop, Duke loop and seeded boss selection. Evidence: `screw-core.log`, `regression-tests.log` and the successful `catalog-regressions-final.log` rerun. The first regression run exposed stale expected catalog hashes in treasure/Whip tests; their exact audited expectations are updated to `859917e69e266ce4`.
- `game-ui-final.log` records actual generated Duke defeat/remaining-fly gate, mouse Screw collection, mouse descent, permanent ownership, independent live strengths, staged reward selection and Apply, export/load/remember, retry and fresh Game construction. Developer damage events/god mode accelerate this automated lifecycle test; the human launch has neither. The wheel test required two events to traverse the full25–500% span because each individual event is intentionally capped at20 wheel steps; the existing wheel-input cap is preserved.
- `cli-verification.json` records independent schema5 and46 CLI startups: legacy Breakfast and selected Screw respectively, both with original165% zoom and normal6-half-heart/no-god starting state. Only the spawned verification processes were terminated after successful startup.
- `screw-tuning.png`, `screw-zoom25.png`, `screw-reward.png` and `screw-collected.png` were visually inspected. Existing warning diagnostics in unrelated files are retained; no performance/native full-actor claim is made.

## Unfinished

Complete native cache/callback/synergy/pool behavior, full D14a recorded room contents and gameplay-save continuity remain open. Full Fly249, Round Worm244, the remaining recorded encounter/obstacle dependencies, Mom's Eye55, Mom's Coin Purse195, Temperance15 and special-room mechanics are separate deliveries. The recorded floor has not been reproduced in full. Exact source room shapes and connections remain deliberate exceptions.

Next proposed checkpoint: commit the accepted Screw/zoom work, then D14a.2 Full Fly249.0.0 in recorded ordinary template1.704.0 (two Full Flies), with native behavior verification, main-game placement, live/export/load controls and a short direct encounter review. That implementation is not selected by the user's request for next steps. Round Worm244 follows as a separate proposed delivery.
