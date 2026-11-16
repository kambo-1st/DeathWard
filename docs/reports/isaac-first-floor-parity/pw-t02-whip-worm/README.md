# PW-T02 — Whip Worm

Selected after accepted PW-C01, committed as `81138b55`. Main-game implementation and developer verification pass. The user accepted the scoped playtest and authorized this checkpoint commit; see [acceptance](human-acceptance.json). Other optional examples and full catalog expansion are unselected.

## Source and effect

Installed Repentance1.7.9b identifies Whip Worm as trinket27 with the Shot Speed cache flag. Original held-slot queries and arithmetic add **0.5 Shot Speed** for an ordinary held copy. Cancer remains a distinct Tears effect. The source ordinary cache does not cap this contribution at2; its global minimum is0.6. Existing DeathWard custom Shot Speed values below that minimum remain explicit testing overrides; this item does not silently clamp the unowned/custom baseline.

`source/manifest.json` pins the executable/XML and disassembly windows. `native-capture.log` records24 native arithmetic cases (including empty/Cancer/Whip slots), three whole ordinary Shot Speed cache cases before the mod callback, and24 original pickup factory cases with supplied fresh eligible pools `[27]`, `[39]`, `[27,39]`. This verifies the ordinary item contribution and bounded selection, not the complete cache scheduler, golden/swallowed/Mom's Box interactions, mod callbacks or complete pickup physics.

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-whip-worm.py --check
```

## Main-game behavior

Whip shares the single held trinket slot with Cancer and never enters permanent collectible inventory. Touching a different trinket swaps the incoming/outgoing identities in place. Leaving contact is required before swapping back. Dropping removes only the held effect; existing passives, active charges, familiar stats, firing waits and emitted bullet specifications remain intact. Whip changes subsequent primary projectile speed and travel time, retaining maximum range, Tears, damage and size.

Ordinary opening-floor first-clear variant350 now resolves against the explicitly restricted fresh two-entry pool `[27,39]`, using the native first-draw operation with the retained DeathWard pickup-seed adapter. The variant's award odds are unchanged. Full native pool population/depletion/refill and expedition RNG streams remain unimplemented. Resolved awards retain their subtype/seed while waiting for placement or capacity, even after live edits.

The world model is an original leather coil with a brass handle; Cancer keeps its brass double-scroll charm. HUD and build display identify the currently held item.

## Configuration and persistence

Tuning → Shooting → Treasure → Trinkets adds Whip strength0–2x in5% steps. It affects the next eligible attack; committed waits and flying projectiles retain their birth values. Cancer strength, reward enable and U/Y binding remain independent. Schema40 exports/loads/remembers both effects and migrates1–39 via audited additive hashes. The original165% preset is unchanged.

Apply regenerates ordinary floor content, removing staged/ground pickups while keeping held ownership and settings. Floor advancement retains the held effect. Retry starts a fresh build with remembered configuration. Campaignv10 records either supported held identity and reads1–9, with Cancer-only validation for the oldv9 slot. This remains interrupted-expedition history, not live save/resume.

## Developer verification

`whip-tests.log` passes24 native cache comparisons, eight native bounded-pair draws, actual primary attack speed/range/cadence, Cancer/Whip swap and removal, other category preservation, committed attack preservation, drop/recollect, floor/Apply, three room sizes, pending identity, schemas5/39→40 and campaignv10 Whip interruption history.

Natural witness: **seed32, displayed room5**, pickup seed3303011089. The ordinary clear produces Whip without forcing the item; Cancer remains seed1/room5. The selected review below stages a pair solely to shorten different-effect swapping.

`core-tests.log` records nine passing regressions and one stale expected catalog-hash assertion in the treasure suite. The audited expected hash was updated for the added Whip definition; that suite then passed in `core-rerun.log`. All ten focused suites now pass. The original fixture failure is retained transparently.

`game-input.log` passes real mouse Cancer→Whip→Cancer→Whip swaps, keyboard firing, drop/recollection, build inspector, live Whip controls, U/Y rebind, panel export/reset/load, Apply, retry and fresh ordinary preset loading. `cancer-regression.log` independently passes the prior natural Cancer award and actual UI workflow. A drop now reserves other trinkets' appearing positions as well as idle positions, avoiding overlapping outgoing/incoming actors before their collection gates open.

`cli-validation.json` verifies actual executable launches with schemas5/39/40 at165% zoom and retained map/route/shooting/category values. `cli-invalid.json` covers missing expedition mode and conflicting review options. No user preset is modified. Visual inspection covers the distinct models, held build and tuning controls; see [pair](whip-pair.png), [held](whip-held.png), [build](whip-build.png), [panel](whip-panel.png).

## Short review

`--expedition --seed 1 --review-trinkets` stages two explicitly labelled test actors in the starting room. Pickups use ordinary contact/swap/drop consumers. No item is granted, no enemies are cleared, and normal health/settings remain. This is not a natural two-pickup seed. The test flag is separate from exported configuration; ordinary launches do not receive the pair. Apply removes the pair and retry recreates it unowned.

Run from the repository root:

```sh
build/deathward --expedition --seed 1 --review-trinkets --mute --save /home/kambo/.local/share/deathward/reviews/pw-t02-whip-worm/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

For the natural reward encounter instead, use `--seed 32 --review-room 5` in place of `--seed 1 --review-trinkets`; clear the encounter normally.

1. Collect Cancer, then Whip Worm; compare cadence and bullet travel. Whip replaces Cancer's Tears effect.
2. Walk away and return to swap back. Each outgoing item remains on the floor.
3. Press **U** to drop the held item and recollect it. **Tab** shows the held name/effect.

Scoped Whip Worm and different-effect swap review is accepted. Remaining: Full native actor/cache/pool/physics equivalence, special trinket interactions and full live expedition resume remain open.

Next proposed: **PW-F02 — Halo of Flies**, orbital formation and enemy-projectile interception. This is not selected yet; Book of Shadows and catalog expansion also remain unselected.
