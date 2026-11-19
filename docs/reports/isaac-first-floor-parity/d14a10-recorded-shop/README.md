# D14a.10 — recorded shop arrangement

Selected by “ok, conitnue” after scoped D14a.9 acceptance. The accepted Temperance/donation checkpoint is committed as `26435e27`. This delivery puts the recorded shop's four rocks and Purse/Temperance offerings into the main game, retaining the existing merchant wagon and canyon geometry. Developer checks pass; the user accepted the scoped handoff on 2026-11-19 ("it its works focus on next"). This delivery's commit is authorized; see `human-acceptance.json`. Native keeper behavior is still missing, so this is not full shop parity.

## Playable check

The review opens directly in **seed 6, displayed room 7**, with four rocks around the merchant wagon, Mom's Coin Purse for **15 coins** and Temperance for **5 coins**. Those offerings are selected by the ordinary restricted stock pool. The review supplies **20 test coins and four red half-hearts**, with god mode off. It neither grants the items nor forces their selection. The separate schema-55 preset retains the latest user export: 165% zoom, 100% room size, 7–9 size range, 26% routes, Speed 1.1 and accepted shooting. Original exports are unchanged.

```sh
build/deathward --expedition --seed 6 --review-shop-stock --mute --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d14a10/campaign.save.balance/export.json --save /home/kambo/.local/share/deathward/reviews/first-floor-d14a10/campaign.save
```

Use `--review-source-room 2000000` **instead of** `--review-shop-stock` to enter the generated arrangement at normal starting health without test coins. Review-room CLI options are mutually exclusive.

1. Walk to each offering and buy it. Purse produces four pills; Temperance occupies the shared held pill/card slot. The two purchases spend exactly 20 coins at the baseline prices.
2. Use Temperance with **F** to spawn the blood machine. Place dynamite beside a rock and move away; the rock and its collision disappear.
3. Leave and return. Purchases stay sold, demolished rocks remain gone and the blood machine remains. Death retry starts a fresh review with the labelled test funds.

Screenshots: [shop](shop.png), [Purse pills](pills.png), [spawned blood machine](machine.png), [tuning](tuning.png). The developer harness uses actual mouse purchase input and F use; it positions the player for some prop/pill checks and invokes tuning actions through Game. It is not a human verdict.

## Source evidence and explicit adaptations

`scripts/isaac-reference/verify-recorded-shop.py` reads the pinned Repentance 1.7.9b STB and the preserved live shop capture. [content-verification.json](content-verification.json) records hashes, source metadata and observed actors; [source-slots.csv](source-slots.csv) records original stack order.

Template **2.0.0, Shop L1**, contains eight stacks: a donation-machine slot; rocks at (1,1), (5,1), (7,1), (11,1); a weighted keeper stack at (6,1); and generic shop offerings at (5,4), (7,4). The keeper stack has two alternatives, each weight .5. The live capture resolves the keeper to 17.1.4 and the offerings to Purse195/15 coins and Temperance15/5 coins.

The captured actor list contains **no donation machine 6.8**. Its reader enumerates the room actor array without identity filtering. This establishes absence in that snapshot only; the underlying factory/unlock gate is unverified. The delivery preserves that observed absence. It does not add the donation system or infer that every such shop omits it.

The existing Fort Mercy merchant wagon occupies the keeper's visual and physical role. **Native keeper bombing, destruction and drops are unsupported.** This retained presentation is an explicit adaptation, not an accepted native keeper implementation.

Source cell (6,1) is anchored to the wagon center. Other cells scale with the dynamic canyon room; the two adjacent rocks move outward as needed to clear the wagon's wider footprint. Rock half-width is .42 of the adapted cell. A bounded fit reduces cell spacing in 1% steps, stopping below 1.05 world units, and checks the four solid rocks, doorway clearance and both stock routes. A failed fit declines the arrangement and restores ordinary terrain; it does not claim a partial room as complete. Source room outlines, size and connections remain excluded from parity by user instruction.

The arrangement is enabled only in compatible opening-floor canyon shops when SOURCE layouts, source props and varied shop stock are enabled, and the ordinary stock selection yields Purse then Temperance without a sale on either slot. Other stock pairs retain their existing composition. No selection reroll is added. The retained fixed-Purse test mode can also qualify and remains a testing override. The DW selection seed and restricted pools are not the captured native floor's RNG or eligibility policy.

All eight source stack ordinals are retained when deriving rock and card spawn seeds, including the omitted machine and adapted keeper slots. This is bounded descriptor/slot sequencing, not complete native factory scheduling. Plain rocks use the existing dynamite destruction path and do not pay the legacy custom coin reward. Existing Purse pill seeds and machine placement remain their documented adapters.

## Configuration and lifecycle

No new tunable is introduced. Existing **TUNING → REWARDS → ROOM LAYOUTS**, props and shop-stock settings control generation and remain pending until **Apply map changes**. Existing shop/card price and item-effect controls keep their live boundaries. Apply is allowed after exploration: it regenerates floor encounters, props and stock while retaining the player build, injury and expedition identity, with a reachable player position. Revisit preserves purchase/demolition state; retry starts fresh. The arrangement is opening-floor-only; owned items and configuration carry through descent.

Schema **55**, contract `d14a10-recorded-shop-v55`, updates the recorded stock policy and migrates schemas 1–54 without new resolved fields. Mechanics fingerprint remains `6e7b8382ade04b60`. Export, load and remember retain user settings and staged map choices. This is configuration persistence; full live expedition save/resume is still D18 work.

## Verification

- Source verification: eight STB stacks, four rocks, weighted keeper metadata and observed keeper/offerings/prices; donation-gate uncertainty is retained.
- Actual Simulation: three room sizes, reachable purchases, pill/card use, dynamite collision removal, sold/destroyed state on revisit, Apply, descent and configuration exclusions.
- Minimum-size coverage: all **23** matching shop selections among the first **1,024** seeds admitted the arrangement and passed placement/access checks. This is bounded coverage, not proof of a native distribution or every seed.
- **Ten focused suites pass.** Nine completed through CTest. The original aggregate invocation ended with exit 143 before the remaining `source_shop_stock` result; the complete shop-stock executable then passed separately with exit 0. See [regressions.log](regressions.log), [shop-stock.log](shop-stock.log) and [verification.json](verification.json).
- Actual Game/Renderer: mouse purchases, F pill/card use, demolition/revisit, staged SOURCE/OFF, schema-55 export/load/remember, Apply, retry and fresh launch pass. See [game-review.cpp](game-review.cpp) and [game.log](game.log).
- Three fresh main-game CLI loads pass: original schema 48, latest schema 54 and current schema 55; all retain zoom 165. Source export hashes remain unchanged. Two additional normal CLI launches verify the mutually exclusive stock and source-room review modes separately; both reached the correct room before intentional test termination. See [cli-verification.json](cli-verification.json) and [review-cli-verification.json](review-cli-verification.json).

## Unfinished and next proposed

Scoped human acceptance is recorded; the D14a.10 checkpoint commit is authorized. Native keeper destruction/drops, donation-machine factory/unlock rules, blood-machine explosion destruction, full shop pools/RNG/factory/physics, remaining special rooms, complete recorded-floor allocation and live expedition save/resume remain unfinished. Pixel/performance work remains deferred.

Next proposed after the human check: commit this arrangement, then implement the keeper's destruction/drop interaction with verified source rules while retaining the chosen canyon presentation. The user selected that bounded continuation on 2026-11-19. This does not resume bulk parity.
