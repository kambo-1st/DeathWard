# D14a.18 — armed bomb outcomes from ordinary shop grab bags

Selected after the accepted D14a.17 checkpoint `1e3933d1`. Enabled and scoped human-accepted on2026-11-20 (“itasawesome commit and continue”). The user requested this checkpoint and selected golden-key bag outcomes next. Full native acceptance remains open.

Ordinary bags retain their source contents selection and subtype odds. Bomb pickup subtype3 becomes Troll actor4.3; subtype5 becomes Megatroll actor4.4. They are lit hazards, not inventory ammunition. The existing shop payment and per-content delivery flags prevent repeat payment or duplicate hazards. Capacity delays keep the original request; inactive rooms pause admitted hazards; Apply resets floor actors while retaining configuration.

## Source and adaptation boundary

The preserved installed Repentance1.7.9b whole-Bomb::Update capture contains48 ordinary/Super cases with2,568 pre-explosion states. The new bounded controller compares position, velocity, friction and countdown exactly against those states. It retains45+one4/3/17 RNG word modulo30 fuse counts, explosion on the invocation after zero, grounded.95 damping/additional.5 below squared speed1, and Megatroll five-step player prediction,1.5 acceleration inside270source coordinates,.8 damping and initial friction. Original conversion-intent capture independently identifies3→3 and5→4. See [source evidence](source-evidence.json). These are reused primary captures, not a new native live-process experiment.

The bag's stored content seed is explicitly used as the actor seed. Native conversion instead draws a fresh global MT word; complete global RNG order/mapping is not ported. Zero seeds remain refused. Source motion uses the fixed D04 accepted base-player conversion, independent of current player Speed and room size. Blast damage100 converts to320 internal units; radius75 uses the retained D10 distance adapter; player damage is two half-hearts with ordinary dodge immunity. Existing enemy-bomb explosion admission/recipient/demolition paths are reused. Other enemy-bomb producers and player inventory bomb tuning are unchanged.

Canyon body/terrain collision, constrained placement, grounded contact pushes, world clock integration and explosion recipients remain adaptations. The visual uses existing lit enemy-bomb geometry: dark ordinary Troll and rust-red Megatroll. Full native appearance/removal playback, physical mass/grid/contact ordering, vertical behavior, all item/status/character modifiers and full native actor acceptance remain unfinished.

## Live configuration

Tuning → Rewards → Shop → Grab Bags adds **Lit bomb fuse** (25–400%) and **Megatroll movement** (10–200%) in5% steps. Both snapshot at hazard admission; existing lit bombs retain their fuse, motion and position. They do not change contents odds or current payment state. Export/load/remember uses schema62; schemas1–61 migrate to100% with existing settings retained. Pending map edits remain staged until Apply.

## Human check

Natural **seed338 / displayed room7** contains a Megatroll; seed227 contains an ordinary Troll. Both use the existing direct shop review and20 labelled test coins, with god mode off and the accepted165% preset. The bag can also contain ordinary dynamite; only that collectible increases inventory.

```sh
build/deathward --expedition --seed 338 --review-shop-grab-bag --mute --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d14a18/campaign.save.balance/export.json --save /home/kambo/.local/share/deathward/reviews/first-floor-d14a18/campaign.save
```

Replace338 with227 for the stationary Troll witness.  Buy the bag, step away from the lit hazard, and observe a single explosion. A Megatroll should pursue you; the ordinary type should stay in place unless pushed. Inventory dynamite must not increase from these rare outcomes. Retry and Apply are available for repeating the check.

## Verification

- Build and five focused suites pass: bag bombs, shop grab bags, batteries, preset contract and existing enemy bomb payloads. See [tests.log](tests.log).
- The new delivery suite covers all48 native cases, both rare outcomes at75%/100%/150% room size, payment/capacity/identity, inactive rooms/revisit, Apply, two-half-heart blast/dodge, deferred queue admission and30/60/120Hz actual Simulation with moving-player prediction.
- Actual Game/Renderer checks cover mouse access to both new controls, normal walk-to-purchase from naturally selected stock, real fuse/explosion/damage, immutable lit settings, export/load/remember with pending map edits, Apply, retry and fresh startup. Screenshots inspected. The Reset button was moved clear of the preset path field.
- Four fresh CLI loads cover schemas60/61/62/custom62, preserving165% zoom and normal vulnerability. The original user's schema61 export remains unchanged.
- The inactive-room fixture initially left the player physically inside the shop and therefore travelled back automatically; moving it to the other room corrected the fixture. The preset rejection fixture was updated to schema62/future63. These were test corrections, not changes to room travel or preset strictness.

## Unfinished / next proposal

Native contact/physics/seed/scheduler/modifier/complete actor equivalence; golden key outcomes and full card pool; remaining milestone items, special rooms and full-floor allocation/acceptance; live expedition save/resume. The user selected golden key outcomes from bags as the next small delivery. No automatic bulk parity work is resumed; pixel/performance work remains deferred.
