# D14a.16 — ordinary shop batteries and active-item recharge

Selected by the user's “ok, lets go!” after accepting D14a.15; the accepted milestone/shop-upgrade checkpoint is committed as `a96ef565`. This delivery enables ordinary batteries in main-game shop stock. The user accepted the scoped playtest (“nice it works, continue”) and selected supported shop trinkets next.

## Enabled behavior

Source-selected shop category5 now creates the ordinary battery5.90.1 in both compatible basic two-position shops and upgraded shops. There is no new category roll: previously unsupported battery outcomes now produce their actor. The remaining unsupported trinket category stays omitted. Retained canyon geometry, shop level, donation progress, player controls and accepted combat/map/view settings remain intact.

The ordinary reference price is5 coins, using the existing random-sale/Steam Sale rules. A touch purchase adds6 charges capped at the held active item's capacity. It pays only if charge increases: no active item, a fully charged item or IV Bag leaves both money and battery unchanged. Existing Yum Heart capacity4 and Book of Shadows capacity3 are retained. Charge can be used immediately with the existing active-item key. Purchase and charge happen once; sold stock stays sold on room revisit. Death/retry starts a new expedition with the applied configuration; this is not live expedition save/resume.

The original editable battery mesh is `assets/pickups/battery/battery.blend`; `scripts/bake_battery.py` reproduces its GLB. It uses ordinary scene lighting/depth/shadow passes and native/web asset packaging. No Isaac sprite artwork is imported. Presentation is a small brass/olive cell with a plus marking.

## Source evidence and limits

`capture-shop-battery.py --check` runs original instructions from the pinned installed Repentance1.7.9b executable:

- 11 ordinary collection cases through `0x6c0cfe` and the original AddActiveCharge routine cover absent active, IV Bag, and all charge states of Yum Heart/Book of Shadows.
- 136 supplied capacity/amount cases verify the actual clamped charge write and returned gain, including capacities1/2/3/4/6/12. Other item capacities are numeric research, not newly implemented actives.
- 30 ordinary prices and6 stock-category resolutions verify5 coins and variant90/subtype1.

The harness skips charge HUD/audio after the actual charge write and stops at success/rejection before achievement/collection visuals. It does not replace the numeric recharge calculation. The inventory and player/slot state are supplied; this does not certify full native contact, shop-payment ordering, factory, seed/profile, item modifiers or scheduler behavior. The Battery passive/extra charge storage, alternate active slots, timed capacities and special active interactions remain outside this delivery.

`extract-battery-animation.py --check` preserves the highest installed animation metadata: Appear36, Drop26, Collect15. Gameplay uses the established active-room30Hz adapter. Preplaced shop batteries start idle; collected effects no longer accept contact. Model size/contact distance and fixed ground placement remain canyon adaptations. Other battery subtypes/producers are not enabled.

## Live controls and persistence

**TUNING → REWARDS → SHOP → BATTERIES** edits collection enabled, charges1–12 and base price0–30 in single-unit steps. These apply to future purchases, including existing unsold actors. They do not change charge already awarded, sold state, or the current floor layout. Stock layout/level remains governed by the existing staged Apply controls.

Preset schema60 exports/loads/remembers all three fields. Schemas1–59 migrate enabled/6charges/5coins and retain their existing settings. Loading still stages map changes. Apply, death/retry and floor transitions preserve battery configuration; testing Apply resets floor stock while retaining active charge and build. Invalid values are rejected before applying/writing them. The original schema59 user preset is byte-for-byte unchanged; `review-preset.json` is its migrated baseline, retaining165% zoom, Speed1.1, range7–9 and routes.26.

## Checks and human handoff

Build and11 focused CTest suites pass. Developer evidence is in `verification.json`, `tests.log`, `game-review.log`, `cli-checks.json`, the source CSVs and screenshots. Coverage includes the183 native cases,30/60/120Hz timing, naturally selected basic shops at75%/100%/150% room sizes, upgraded stock, actual purchase/Steam Sale, no-active/full/IVBag/insufficient-funds gates, live settings, collection cleanup, revisit, map Apply, descent, schema59 migration and18 custom schema60 roundtrips.

The actual Game/Renderer check uses the C key for Yum Heart, normal movement into the battery, ordinary charge/payment, mouse tuning, export/load/remember, pending map changes, Apply, revisit, retry and fresh-process loading. Four separate CLI loads cover schemas58/59/60 and a custom schema60 export. Two historical test fixtures were corrected: the version7 save fixture now removes the schema13/14 donation fields while respecting multiline quoted context; the seed69 stock witness now expects its supported battery rather than the old fixed fallback, after actor admission.

Interactive command/isolated save are recorded in `interactive-latest.json`. The review opens seed15/displayed room7 with a naturally selected battery/BOGO pair. Only review resources are supplied: a labelled full Yum Heart,20coins and four red half-heart units, god mode off. The baseline battery costs5.

1. Touch the battery with full active charge: no purchase.
2. Move away, press **C** to use Yum Heart, then walk into the battery.
3. Check5 coins are spent and Yum Heart returns to4/4; pressC again to verify reuse.
4. Leave/revisit: the battery stays sold. Retry starts a fresh review shop.

Unfinished: full trinket/card/pill/collectible stock coverage and native item-pool depletion/profile behavior; donation-unlocked item effects; special battery subtypes, non-shop producers, extra/alternate charge slots and battery modifiers; full native factory/contact/physics/scheduler equivalence; remaining special rooms/full-floor allocation and live expedition save/resume. Pixel/performance work remains deferred. Next selected small delivery: shop trinket stock with the already supported trinket effects, retaining explicit pool coverage. Bulk parity stays paused.
