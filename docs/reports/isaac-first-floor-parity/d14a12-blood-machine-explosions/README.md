# D14a.12 — blood-machine explosion destruction

The user accepted D14a.11 with “it works, next!” on 2026-11-19. That shopkeeper checkpoint is committed as `a09da6e8`. The selected continuation adds explosion destruction to ordinary Temperance blood-donation machines in the main game. The user accepted this scoped playtest with “nice it works, continue!”; see `human-acceptance.json`.

## Enabled behavior

An ordinary dynamite explosion breaks an unbroken blood machine, removes its collision/navigation obstruction and leaves a charred remnant. Ordinary shots do not damage it. Native destruction depends on the explosion flag, not on a positive damage amount or an HP threshold. Already broken machines cannot pay again.

The source selector draws one or two batches. Each batch is either one unresolved heart or one to four unresolved coins; each pickup receives its own recorded RNG draw. Existing ordinary pickup resolution and collection consumers handle those identities. This path does not award Blood Bag or IV Bag. Destroying an active machine cancels its unpaid donation payout; already resolved rewards remain queued.

Blast targets are captured before collateral collision changes. Resolved drops wait for capacity or a reachable location without rerolling. Room departure/revisit retains destruction and pending identities. Testing Apply resets floor actors while preserving pending resolved rewards and configuration; next floors and retry preserve configuration. Retry starts a fresh expedition build.

## Configuration

**TUNING → SHOOTING → PILLS → TEMPERANCE → EXPLOSIONS** exposes independent destruction/drop switches and source rolls / labelled test outcomes (nothing, full red heart, two pennies). Edits apply to future explosions. They neither resurrect machines nor change previously resolved drops.

Schema57 exports, loads and remembers these controls; schemas1–56 migrate to destruction/drops enabled and source rolls. Map edits remain staged until Apply. The user's walking, shooting, damage, dodge, map/routes and zoom165 are preserved. Configuration persistence is distinct from live expedition save/resume.

## Native evidence and limits

`source/manifest.json` pins the installed Repentance1.7.9b executable hash and assembly windows. Reproduce the capture with `scripts/isaac-reference/capture-blood-machine-explosions.py`; its `--check` mode compares the preserved output.

- 90 original damage-gate cases cover six supplied states, five flag masks and three damage amounts, stopping before visual factory calls. Ordinary variant2 requires explosion flag4 and rejects state3; zero damage still destroys it.
- 1,030 original destruction executions verify batch counts, actor variants, output init seeds, order and final RNG against the C++ consumer. The ordinary branch uses shifts4/3/17, with Daemon's Tail absent. Position/factory calls are hosted; their native physics are not reproduced by this capture.
- The accepted donation controller already advances its retained machine RNG using a different adapter. This delivery uses native destruction shifts from that current state and preserves donation behavior. It does **not** claim native seed equivalence after prior DeathWard donations.
- Heart/coin subtype resolution retains the existing rare-gates-off profile. Safe grounded placement, canyon blast geometry, collision, appearance timing and active-room scheduling are explicit adapters. Full damage-wrapper/visual/factory behavior, thrown arrival, Daemon's Tail/profile/unlocks and global RNG remain unaccepted.

## Verification and short human check

`verification.json` records the completed checks. The automated delivery covers native numeric comparisons, real dynamite and ordinary shots, active/idle/already-broken phases, zero-damage explosions, cover, all currently reachable heart subtypes, collection timing/healing, capacity, repeat blasts, revisit and three room sizes. The actual Game/Renderer check exercises input, tuning, export/load/remember, staged Apply and retry. Test outcomes are confined to verification; `review-preset.json` uses source rolls.

The review opens directly in seed68's recorded shop, displayed room7. It supplies **20 test coins and four red half-hearts**, with god mode off. The preset is a migrated copy of the latest D14a.11 export; original presets are not overwritten.

```sh
build/deathward --expedition --seed 68 --review-shop-stock --mute --balance-preset docs/reports/isaac-first-floor-parity/d14a12-blood-machine-explosions/review-preset.json --save /home/kambo/.local/share/deathward/reviews/first-floor-d14a12/campaign.save
```

1. Buy Temperance for five coins and press **F** to create its machine.
2. Place dynamite beside it with **B**, then move away. Touching the machine donates health.
3. Check the destroyed remnant, collect the drops and walk through its former obstruction. Leave and return: it must stay broken without duplicate rewards. Retry after death is available.

## Unfinished / next proposed

Scoped human acceptance is recorded. Full native machine/profile/factory/physics equivalence remains open. The next selected bounded checkpoint is the recorded shop's donation-machine eligibility/factory gate, which is still unresolved because no machine appeared in the preserved live snapshot. Remaining special rooms, complete recorded-floor allocation, missing rare keeper items and live expedition save/resume are also unfinished. Only the recorded shop eligibility/factory continuation is selected; other implementations and bulk parity remain unselected. Pixel/performance work stays deferred.
