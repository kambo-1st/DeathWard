# D14a — recorded first-floor content review

Selected after scoped D13c acceptance, committed as `1003c611`, on 2026-11-17. **The live floor's descriptors and template contents are captured and cross-checked. Treasure is observed as Mom’s Eye55 plus two pennies; shop stock is Mom’s Coin Purse195 for15coins and Temperance card15 for5coins. The boss reward is now observed as Screw255. Other special-room outcomes, D14a gameplay integration and human acceptance remain unfinished.**

The user supplied the paused game with "ready". Read-only capture confirms installed Repentance1.7.9b, Normal difficulty0, stage1/type0 and Isaac character0. The current source log identifies **2FFX 8XJH**, numeric starting seed3466870960 and stage seed1761530316. Its start-room spawn seed3382453641 matches the captured descriptor. Two independent captures preserve identical descriptor/config data at paused world frame82. No input, memory writes or configuration changes were sent to Isaac.

## Observed source content

There are **12 descriptors**: entrance, four ordinary combat rooms, one shop, one treasure room, one boss room, a sacrifice room and three secret-room types. Descriptor count is not floor-cell area or proof of a procedural-count formula. Source shapes and connections remain metadata, as explicitly excluded by the user.

| Role | Native template | Recorded candidate content | DeathWard gap |
| --- | --- | --- | --- |
| Entrance | 1.2.0 | Empty start room | Frozen-floor role mapping not implemented |
| Combat | 1.704.0 | Two Full Flies249.0.0 | D14a.2 now enables Full Fly and the two-enemy arrangement; developer checks pass and scoped human acceptance is recorded |
| Combat | 1.51.0 | Two Frowning Gapers10.0.0, two plain rocks, four poop grids | D14a.4 now enables the distinct Frowning movement/Head consumer and this arrangement; developer checks pass and scoped human acceptance is recorded |
| Combat | 1.505.0 | Two Round Worms244.0.0,36 plain rocks | D14a.3 now enables Round Worm and this arrangement; scoped user acceptance recorded and committed as00313e5b |
| Combat | 1.414.0 | Eight Pooters14.0.0,12 Attack Flies18.0.0,20 poop grids | D14a.5 now enables the complete mixed encounter and ordinary Attack Fly scale/tuning; developer checks pass, human pressure/full native acceptance remain open |
| Boss | 5.2012.13 | Duke67.0.0 plus one initial Attack Fly, four rocks and two poop grids; **observed clear reward: Screw255** | D14a.6 now enables the exact eight-slot starting arrangement with canyon spatial fitting; developer checks pass and scoped human acceptance is recorded; full native acceptance remains open; Screw reward/effect is D14a.1 |
| Treasure | 4.6.0 | **Observed: Mom’s Eye55 and two pennies**, uncollected after the same-seed restart | D14a.7 enables the ordinary backward-shot/Luck effect and recorded arrangement in compatible canyon treasure selections; developer checks pass and scoped human acceptance is recorded; full native acceptance remains open |
| Shop | 2.0.0, source title Shop L1 | **Observed: Mom’s Coin Purse195 for15coins; Temperance card15 for5coins**, still present | Both exact offerings/effects and the complete layout remain unsupported; slot/prop interactions remain open |
| Secret | 7.8.0 | Three unresolved penny subtypes plus props/grids | Hidden access and complete interaction/content support remain open |
| Super-secret | 8.14.20 | Slot entities6.4.0 and6.2.0 | Special interaction support remains open |
| Sacrifice | 13.7.0 | Special grid/prop arrangement | Sacrifice behavior remains open |
| Ultra-secret | 29.1.0 | Random collectible and surrounding grids | Access, resolved item and interaction support remain open |

All **12 template identities and163 placement slots** match the preserved installed STB files exactly, including slot order, coordinates and weighted entries. Every captured slot has one entry; factory/category outcomes can still be unresolved. The original audit identifies seven such pickup slots; the treasure and two shop observations resolve three, leaving four secret/ultra-secret pickup slots outside these observations. Boss clear rewards are separate: the subsequent live boss-room observation identifies Screw255. These are reference candidates, not proof of eventual champions, offspring, item choices or live actors in unvisited rooms. `content-audit.json` preserves full records, file hashes and registry evidence. Registry presence is kept separate from scoped actor acceptance.

## Small reviewable steps

1. **Core reference observations are recorded.** Descriptors/configs/profile, treasure, shop offerings/prices and boss reward are captured. These observations span same-seed restarts; they do not prove an uninterrupted floor playthrough or factory independence from room-entry order. Starting inventory and other special-room outcomes remain unverified. Original snapshots and per-observation context stay separate.
2. **Review the dependency audit above.** Full Fly now has the bounded D14a.2 delivery; Round Worm remains a separate actor delivery; existing Frowning and standalone fly behavior, poop and special-room interactions need review. Do not silently substitute accepted Gapers, Breakfast or existing shop stock for the actual reference contents.
3. **Make one playable content comparison.** Map the verified contents onto DeathWard's retained canyon rooms/corridors. Preserve accepted movement, firing, dodge, damage, dynamic size and165% preset. Any new selection control must use staged Apply and export/load/remember. Actual native graph/room outlines remain excluded.
4. **Human check.** Start at the entrance, visit shop and treasure room, then clear the boss, collect its reward and descend. The handoff must identify what matches, what is adapted and what remains unsupported. A single recorded floor is not acceptance of procedural generation.

## Reproduce the capture and audit

`scripts/isaac-reference/read-live-floor.ps1` requests only `QUERY_INFORMATION | VM_READ`. It checks the pinned executable SHA256, used-descriptor capacity, current-room membership, unchanged world frame and stable descriptor bytes. It records config spawn candidates and the active room's actor identities. It does not inject code, send input, suspend the process or change game files. Output must be a new file.

```sh
python3 scripts/isaac-reference/capture-live-floor.py --output docs/reports/isaac-first-floor-parity/d14a-floor-content/next-room-observation.json
python3 scripts/isaac-reference/audit-live-floor.py --snapshot docs/reports/isaac-first-floor-parity/d14a-floor-content/source-floor-profile.json --output /tmp/deathward-floor-audit.json
```

Both output filenames must be new. The capture wrapper hosts the C# reader through ordinary PowerShell commands; it does not execute a `.ps1` file or change execution policy. This route completed the live capture successfully. Earlier direct UNC script execution was rejected; that historical preparation result remains in `preparation.json` and is superseded by `capture-verification.json`.

`descriptor-allocation.asm` preserves the pinned native count/stride/config/door stores. Previous seed/slot/geometry evidence is linked in `preparation.json`. `source-floor-20261117-141752.json` is the first immutable capture; `source-floor-profile.json` adds the checked difficulty/stage fields. `source-start-log.txt` preserves the matching current-source-log excerpt.

Unvisited config slots may still contain random categories or subtype0 entries. A descriptor snapshot does not establish the eventual collectible, pickup conversion, champion or factory result. The log's seed text identifies this source expedition; it is not a claim that entering that seed in DeathWard reproduces native generation.

## Unfinished

The user restarted the same source seed and supplied "treasure ready." All12 room identities/spawn seeds match the original capture. `treasure-observation.json`, `treasure-source-log.txt` and `treasure-verification.json` record the live Mom’s Eye55 actor and both pennies; the installed XML identifies it as passive. This is identity/placement observation, not an implemented item effect. The subsequent "shop ready" observation resolves its two slots as Mom’s Coin Purse195/15coins and Temperance card15/5coins at(280,320)/(360,320). `shop-verification.json` links both captures, pinned passive/card definitions and the native signed-price field evidence. The source log records Mom’s Eye being collected between treasure and shop observations; no reset is required or requested. These are observed offerings, not implemented item/card effects. The final "boss reward ready" capture records Screw255 at(320,360), price0, with no boss/fly actors present. The installed XML identifies it as a passive with firedelay/shot-speed cache tags; those tags do not establish numeric effects. A full and a half red heart are also present, but their producers are unverified. `boss-reward-verification.json` preserves this distinction. The latest source log has another same-seed attempt with Mom’s Eye collected and no shop visit; earlier shop observations remain valid observations of that seed under their recorded context, not proof of one uninterrupted playthrough. The complete playable floor, dependency implementations, resolved special-room content and human review remain unfinished. No new boss actor, complete item pool or bulk parity implementation has been enabled. The capture made no gameplay changes; subsequently selected D14a.1 now enables the bounded Screw reward/effects. Full-floor gameplay is still unfinished.

## Next proposed implementation checkpoint

**D14a.1 — Screw255 as the recorded boss reward** was explicitly selected on 2026-11-17, with wider zoom. Implementation and developer checks pass; human review is pending in [the D14a.1 report](../d14a1-screw-reward/README.md). Verify its native Tears/Shot Speed arithmetic and copy/cache behavior, integrate the passive through existing independent consumers, and provide a staged fixed-reward review plus live/export/load controls. The short human check is to defeat the boss, take Screw, then compare firing in the next encounter/floor. Do not replace the established Breakfast default globally without the selected reward-policy change.

After that, deliver Full Fly249 and Round Worm244 individually in their recorded ordinary encounters, then Frowning/mixed-fly/poop arrangements and the remaining recorded treasure/shop dependencies. Card/pill/special-room mechanics remain explicit new work; captured identities do not authorize broad catalog restoration. Full D14a content integration and human acceptance remain unfinished. No additional source play is required for the proposed Screw checkpoint.

D14a.2 update: the user selected smaller batches. Full Fly/source704 is implemented, developer-verified and scoped human-accepted; see [its report](../d14a2-full-fly/README.md). This supersedes the earlier Full Fly registry/dependency gap only. The complete recorded floor, remaining actors/items/special rooms and human full-floor acceptance remain unfinished.

D14a.5 update: complete recorded source414 content and ordinary Attack Fly movement/tuning are enabled in the main game; see [the scoped report](../d14a5-mixed-flies/README.md). Human review and the remaining full-floor work are unfinished.

D14a.6 update: the recorded Duke starting arrangement is enabled and developer-verified; see [its report](../d14a6-duke-room/README.md). The user accepted the scoped handoff on 2026-11-18; complete recorded-floor integration and full native acceptance remain unfinished.

D14a.7 update: Mom’s Eye55 and the two-penny treasure arrangement are enabled and developer-verified; see [its report](../d14a7-moms-eye/README.md). The user accepted the scoped D14a.7 handoff; shop/special-room dependencies and full-floor equivalence remain unfinished. D14a.6 is committed as `5741f7cd`.
