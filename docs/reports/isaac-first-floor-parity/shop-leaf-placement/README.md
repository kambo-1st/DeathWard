# Optional shop branch correction

Selected on 2026-11-15 after the user identified that shops could connect multiple rooms: “ok, lets fix this”. This is a focused correction to ordinary canyon expedition generation, following D10d; it does not select broader native floor generation or items. Implementation is enabled and developer-verified. On 2026-11-15 the user acknowledged this scoped checkpoint and requested its commit ("cool, commit, whats next?"). This records acceptance of the delivered scope, not a separate observed playtest or full native acceptance; see [acceptance](human-acceptance.json). This change and D10d are included in this checkpoint.

## Behavior

Each ordinary canyon floor reserves one shop with exactly one passage to an ordinary room. The shop is placed after the ordinary network, shortcuts, boss and treasure branches, and cannot become their parent. Removing the shop leaves every other room connected to the entrance. Entrance and protected objective identities2/3, total room count, and treasure-room count remain intact. Shop sites are reserved before guaranteed keys and quiet/story/service roles are allocated.

This intentionally changes seeded shop placement and may change the generated layout/content for a previously recorded seed. Canyon outlines, wide physical corridors, size/range/route-length controls and combat/view settings retain their existing algorithms and values. Mine, Classic and tutorial generation retain their historical behavior. This is not a reproduction of Isaac’s complete floor generator, room counts or selection rules.

The correction is a generation invariant, independent of D10d’s SOURCE/LEGACY lock policy. Both modes get optional shops in ordinary canyon expeditions. No new tunable or schema is introduced: schema28 settings and old preset loading remain. A newly generated floor, retry or existing **Apply map changes** uses the corrected graph; an already-running old binary does not change. Apply still resets current-floor encounters/rewards while preserving player/build and expedition identity.

## Verification

- [Build](build.log): native game, policy, key-spending, preset, generated-dungeon and input targets pass.
- [Policy checks](policy-tests.log): 7,168 graph cases (1,024 seeds × all room counts9–15), deterministic cells/links, unique adjacent edges, exactly one shop entrance, boss/treasure leaves, all other rooms reachable with the shop removed.48 actual generated floors preserve ordinary/boss access under source locks; zero guaranteed-key relocations are needed. Nine size/route combinations verify physically traversable shop passages and reachable keys. The retained576 ordinary native lock decisions and exclusion/Apply/revisit cases pass.
- [Focused regressions](regression-tests.log): keyed-door spending, preset contract and generated dungeons pass.
- [Actual Game/Renderer](input-tests.log): first-floor free shop/treasure entry, later-floor natural-key shop entry, free keyboard return, staged mouse/keyboard Apply, strict preset load/export/remember, floor/retry/fresh-session checks pass. Shop degree is checked again after generation, Apply, floor change, retry and fresh launch. [Separate key-spending input regression](key-input-tests.log) passes.
- [Three CLI launches](cli-validation.json): accepted schema5 and schema28 SOURCE/LEGACY presets open directly in displayed shop room7 at normal health and165% zoom. Original user export SHA256 remains `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`.
- [Inspected main-game screenshot](main-game.png): retained canyon style and the S shop branch on the minimap.

The first physical-path fixture changed a lock flag without rebuilding collision. It was corrected to perform the corresponding collision rebuild; the production entry/return checks passed. A later verification invocation ended with SIGTERM and was rerun to completion. No additional production navigation change was required. These are focused checks, not a full-suite/native acceptance claim.

## Human check

```sh
./build/deathward --expedition --seed 99 --review-room 7 --mute --save /home/kambo/.local/share/deathward/reviews/shop-leaf-placement/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

This opens directly in the first-floor shop. Check that S has one corridor on the minimap; leave and return without spending a key. Continue through ordinary rooms without needing to use the shop as a passage. The command was startup-verified with temporary saves; no new interactive window was left running by this correction.

## Remaining

Older seed-specific room review fixtures and handoffs need revalidation after this structural correction. Broader source floor counts, room eligibility/selection/profile, special locks/items, full native factory/animation/physics, browser runtime and gameplay-save continuity remain open. Bulk parity remains paused. Next proposed: refresh affected review cases, then D11a’s named treasure upgrade. The commit request does not select either implementation.
