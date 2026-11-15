# D10d — shop and treasure-room lock placement

Selected on 2026-11-15: “commit this checkpoint, then implement shop and treasure-room lock placement.” Accepted D10b/D10c were committed first as `bc1651ec`. D10d is enabled and developer-verified. After the optional-shop correction, the user acknowledged the checkpoint and requested its commit on 2026-11-15 ("cool, commit, whats next?"); see [scope of acceptance](../shop-leaf-placement/human-acceptance.json). D10d and that correction are included in this checkpoint. No unrelated bulk parity or item delivery is selected.

## Behavior and application boundary

In ordinary canyon expeditions, both shop and treasure-room entrances are **free on mapped source stage1**. Later ordinary mapped stages require the existing keyed-door payment (default one key). Source stage comes from the existing mechanics mapping, not the expedition floor number. The lock-policy switch itself does not change rooms or geometry. The subsequent selected [optional shop correction](../shop-leaf-placement/README.md) changes shop placement and seeded layouts. Mine, Classic and The Lost Survey retain their previous rules.

TUNING → COMBAT → DOORS adds **ROOM LOCK RULES**: SOURCE STAGE RULES (default) or LEGACY COMPARISON (historical shops free/treasure locked). This is a map setting: edits and preset loads stay pending until **Apply map changes**. Apply regenerates current-floor encounters, pickups and door state while retaining the player/build and expedition identity. A player already inside a special room keeps an exit after testing regeneration. The existing KEYS PER LOCK setting remains live at actual unlocking, including queued approaches; changing it does not generate new locks.

Schema28 exports/loads/remembers the placement setting; schemas1–27 migrate enabled while retaining prior player, combat, dynamite, view and map fields. Invalid presets cannot partly apply. Retry, floor transitions, current-floor regeneration and fresh sessions retain the selected mode. This is configuration persistence, not full gameplay-save continuity.

## Canyon connection adaptations (original D10d checkpoint)

The following transit-shop adaptation describes the original D10d build. The selected [optional shop correction](../shop-leaf-placement/README.md) supersedes multi-connection shops in ordinary canyon generation; historical evidence below remains archived.

DeathWard shops may connect several ordinary rooms. After shop admission, ordinary exits open and stay open on revisit, without another charge. A separate unopened treasure room connected to that shop retains its own lock. This models ordinary unkeyed exits within the retained persistent corridor graph; it does not replace that graph with Isaac's connections.

Existing guaranteed keys retain their count. If a newly locked transit shop would enclose one, generation relocates that key into the unlocked network before source content/terrain are built. It prefers unused ordinary objective sites, then existing protected center/entry anchors when there are fewer open rooms than keys. Anchors remain distinct; no extra key or random draw is added. This is an explicit canyon solvability adaptation, not native key frequency/placement. Custom key costs above one remain testing overrides and can exceed the guaranteed supply.

## Native evidence

[capture-room-lock-policy.py](../../../../scripts/isaac-reference/capture-room-lock-policy.py) executes original instructions from the pinned installed Repentance1.7.9b executable, SHA256 `04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`. The ordinary initialization branch starts at `0x6e194c`; original stage-type, mode and ordinary player-type helpers execute unchanged. Stop hooks mark the lock assignment or unlocked continuation before animation/world callbacks.

864 supplied cases cover source stages1–8, stage types0–5, Normal/Hard, and source/target room types1/2/4. The576 ordinary-family cases verify first-stage free shop/treasure entry, later locks, and ordinary exits. Types4/5 contribute288 contrasting alternate-family cases; those alternate families are not enabled by this delivery. See [manifest](source/manifest.json) and [decision matrix](source/native-locks.csv). This is bounded original-code verification, not live/full factory, generation, collision, animation, profile or item acceptance.

## Developer verification

The focused policy suite compares actual generated locks with the ordinary native matrix, checks48 generated floors against retained geometry/roles/connections/key counts, verifies pre-lock key access and physical pickup routes, exercises9 room-size/corridor-length combinations, and covers a narrow synthetic network requiring a second protected key anchor. It also checks mapped stage versus floor index, paid shop admission, free exits/revisits, an adjacent treasure remaining locked, policy regeneration inside a special room, and excluded Mine/Classic/tutorial modes.

Actual Game/Renderer checks exercise zero-key entry into both first-floor room types, natural later-floor key collection and one-key shop entry, free keyboard return, mouse/keyboard policy edits, staged Apply and load, invalid-load atomicity, export/remember, floor transitions, retry and fresh-session persistence. Unrelated combat is cleared only in the input fixture; the human review launches normal encounters and grants no key. Existing keyed-door spending, preset-contract and generated-dungeon checks are retained. [Final policy checks](final-policy-tests.log), [final main-game input checks](final-input-test.log), [key-spending regression](key-spending-regression.log), [preset/key core checks](core-tests.log) and [generated-dungeon regression](graph-regression.log) pass. Four separate CLI launches load schema5/27/28-source/28-legacy with the expected placement mode, key cost, normal health and165% zoom; see [CLI evidence](cli-validation.json). The [tuning panel](tuning.png) was visually inspected. [Validation manifest](validation.json) records the scope and final hashes. The original user export remains unchanged (SHA256 `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`).

## Human review

```sh
./build/deathward --expedition --seed 99 --review-room 5 --mute --save /home/kambo/.local/share/deathward/reviews/d10d-room-locks/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

The original accepted preset keeps165% zoom and normal six half-hearts. Clear displayed room5, then enter the adjacent P treasure room: no key is required or spent. The first-floor S shop is also free. TUNING → COMBAT → DOORS can stage the historical comparison; Apply explicitly resets the floor. Later-floor paid shop access is developer-tested. This command describes the original D10d layout; use the updated [shop review](../shop-leaf-placement/README.md) for the accepted branch correction.

Remaining: revalidation of older seed-specific review cases; special locks/characters/items, alternate and Greed modes, native floor/room counts and selection/placement/profile rules, full factory/animation/physics equivalence, browser runtime, and gameplay-save continuity. D11's named real treasure upgrade is the next proposed separate delivery. Exact Isaac room size/shape/connections remain excluded.
