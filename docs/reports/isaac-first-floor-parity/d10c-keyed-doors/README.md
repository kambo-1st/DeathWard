# D10c — ordinary keyed-door spending

The user selected keyed-door spending after D10b and accepted the D10b playtest on 2026-11-15 (“it works move to a next thing”). D10c is enabled, developer-verified and scoped human-accepted on 2026-11-15 (“looks good!”); see [acceptance](human-acceptance.json). D10b and D10c are included in this accepted checkpoint. Bulk parity remains paused.

## Delivered behavior

Ordinary locked passages already required one key. This delivery hardens that interaction: a successful unlock spends the configured cost exactly once, opens the passage collision and starts the crossing. The opened collision and complete route are prepared before payment. An unusable exit, wrong room/side, sealed combat passage, insufficient inventory, invalid target, inactive player or open reward/shop menu cannot spend keys or partially unlock the passage. Previously opened doors stay free in either direction, including after a cost change or room revisit.

TUNING → COMBAT → DOORS edits **KEYS PER LOCK** in whole-key steps from 0 to 5. The source default remains 1; other values are explicit testing overrides. Changes apply at actual successful unlocking, including an approach already in progress. Reset restores 1 without closing opened doors. Schema27 exports/loads/remembers the setting; schemas1–26 migrate to 1 while preserving prior controls. Invalid loads are rejected before any application. Pending map edits remain staged until Apply; map regeneration, floor changes, retry and a fresh application retain the selected cost. Gameplay save continuity is a separate unfinished feature.

Existing canyon geometry/connections, lock placement, keys, accepted player/shooting/enemy/balance settings, dynamite and particles are retained. This is spending on existing locks, not source-equivalent floor lock placement: ordinary shops remain governed by the current generator, and the source first-floor treasure-room exception is not implemented here.

## Source evidence

The local installed Repentance1.7.9b executable has SHA256 `04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.

[capture-keyed-door-spending.py](../../../../scripts/isaac-reference/capture-keyed-door-spending.py) executes the complete original ordinary key-spend helper at `0x726070–0x726181`, with empty inventory, golden flag off and original bookkeeping helpers. Eight cases cover −1/0/1/2/3/5/98/99 keys: positive counts spend one; nonpositive counts fail unchanged. The bounded ordinary door admission branch at `0x6e112e` executes the same helper, stopping at its success/rejection boundary before animation/world callbacks. Twenty-four cases cover locked, already opened and incompatible supplied states. The full caller context is preserved as static evidence.

[Manifest](source/manifest.json), [key spending](source/native-spend.csv), [door admission](source/native-doors.csv). These are bounded original-code observations, not full native factory, collision, animation, profile, generation or item acceptance. DeathWard keeps its explicit canyon approach/path checks and interaction controls. Free/custom costs do not claim native parity.

## Verification and review

Core checks cover the cost/inventory matrix, unchanged state after rejection, open-door revisit, generated canyon size/route combinations, live edits during queued approaches, schema migrations/rejections and existing dungeon/dynamite behavior. See [core checks](core-tests.log), [accepted room-range checks](accepted-range-test.log) and [regressions](regression-tests.log). Two actual Game/Renderer modes pass: `--keyed-doors-only` covers natural key mouse collection/unlock, keyboard return, mouse/keyboard tuning, invalid-load atomicity, reset/export/load/remember, staged map Apply, floors, retry and fresh-session loading; `--dynamite-balance-only` covers the adjacent dynamite panel and retained charge snapshots. The input fixture clears combat only to isolate interaction checks; the human review keeps normal combat. [Door input](input-test.log), [dynamite regression](dynamite-input-regression.log). The [DOORS panel](tuning.png) was visually inspected. Separate schema5/26/27 CLI launches pass with zoom165 and expected key costs1/1/3; see [CLI evidence](cli-validation.json). The [custom test preset](custom-test-preset.json) deliberately costs3 keys and stages room scale1.11; it is not the baseline human review preset. The original user preset remains byte-identical (SHA256 `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`).

The review witness uses seed99, displayed room5, with the original accepted preset (room scale1.1, range7–9, corridor scale.26, zoom165). It naturally contains three enemies, an ordinary key and a locked passage. No key is granted and combat remains enabled. Clear the room, collect its key, click the lock (or approach it and press E), then leave and return. Expect inventory1→0 once and free subsequent crossings.

```sh
./build/deathward --expedition --seed 99 --review-room 5 --mute --save /home/kambo/.local/share/deathward/reviews/d10c-keyed-doors/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

Remaining: source floor-specific lock placement/free first-floor treasure/shop policy; golden/double/coin/special locks and item overrides; full native animation/factory/physics/profile/generation equivalence; browser runtime and gameplay-save continuity. D11's named treasure upgrade remains a future separately selected delivery.
