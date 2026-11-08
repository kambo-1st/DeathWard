# Canonical attributes — step 3: independent shooting consumers

**Implemented in the gated review path; tests pass; human shooting verdict pending.** The normal expedition shooting path is unchanged until this new comparison is accepted. Canonical Speed remains enabled in normal walking.

```sh
./build/deathward_projectile_review
```

## Human review

- **1 Base build:** base Tears, Shot Speed and Range; selected projectile feel retained.
- **2 Quicker firing:** only Tears increases. Rhythm changes; reach and projectile speed stay the same.
- **3 Faster travel:** only Shot Speed increases. Shots arrive sooner; rhythm and reach stay the same.
- **4 Longer reach:** only Range increases. Shots travel farther; rhythm and launch speed stay the same.

Each selection resets the same room, spawn and camera. The review camera is zoomed out using the existing camera controls so the across-room lane is visible; controls and picking share that camera. Fire along the guide using normal arrows/RMB. **T** cycles a stationary close/middle/near-limit/far target. The far target lies beyond base reach and can be reached by the longer-Range preset. **F8** resets, **F11** follows a shot. All targets take two ordinary hits and remain explicitly frozen. A gold ring shows base reach from the starting position. No numerical speed metrics are shown.

Start with the base build and judge its firing rhythm and travel feel. Then change one preset at a time and confirm the named difference. Universal dodge, accepted walking, larger bullet presentation and eight-direction mouse/keyboard firing are retained. The demo uses a unique temporary campaign.

## Consumers and evidence

`ShootingCalibration` resolves the three source scalar attributes independently. Tears supplies the nominal interval with held-fire fractional carry in the fixed-step producer. Idle time cannot bank shots. This is not a restored or fully accepted native weapon-counter implementation. Shot Speed supplies the launch multiplier, and Range supplies tile-based reach through `AttributeSpace`. No firing interval depends on range/travel time. No reach depends on room size, three-shot occupancy or a fixed short lifetime. A zero Tears/Shot Speed/Range disables ordinary emission without division by zero.

Base Shot Speed 1 retains the previously selected Faster projectile feel. Base Range 6.5 maps to the accepted standard-room reach; this is a fixed tile conversion, not a per-room clamp. Larger Range can exceed the original half-room baseline. These explicit spatial/launch adaptations are not live native velocity equivalence. Native-shaped falling presentation is normalized over the trip; full native actor/grid/height/item behavior remains separate acceptance work. Existing DW modifier ratios are retained in the review, but native item/cache composition is not implemented or accepted here.

The earlier travel-time/cadence coupling and separately mutable review launch-speed field are removed. With the documented base Tears and selected travel/reach, the base stream peaks at **four** ordinary bullets, rather than the earlier artificial three-bullet requirement. This is shown for review, without hiding shots or lowering Tears. Changing Shot Speed or Range may change simultaneous occupancy while preserving the firing rhythm. Higher Tears may legitimately increase it too.

Actual Game checks compare all four presets at 30/60/144 input partitions. In the controlled eight-second samples the base emits 22 shots; increased Tears emits 44; increased Shot Speed and Range each still emit 22. Range measurements remain unchanged when only Tears/Shot Speed changes; the longer-Range preset doubles configured reach without a room cap. Additional actual Game cases cover six flight-speed settings without changing Tears, all eight firing directions, independent native flight rows, inheritance, same-reach traversal, stationary targets, cover, two-hit deaths, zero-stat disabling, idle no-burst behavior and dodge. Terminal position samples allow fixed-tick observation tolerance because cleanup can remove a projectile within an update.

Five focused suites pass (`player_attributes_contract`, `player_speed_attribute`, `core_contracts`, `heart_gameplay`, `regular_health_balance`), as do the actual Game movement verifier, Mine/Canyon arrow and keyboard integration checks. The application rebuilds. Input partitions establish simulation consistency, not rendering performance. [Measurements](measurements.csv), logs, [initial UI inspection](review.png) and hashes are retained. The inspection image does not prove human acceptance. A preserved executable/private mechanics snapshot is outside Git; visual assets still use the checkout.

Still unfinished: human shooting verdict and normal-expedition integration; complete native counter/emission/birth/room/floor scheduling (especially extreme rates), coordinate/clock/live calibration, full actor/item/flags/height/hit geometry; source damage/enemy HP/DPS reconciliation, Luck and upgrade/cache/cap formulas; prior health/enemy acceptance gaps. Attack damage and expedition enemy HP were not changed, and authored stat composition is not claimed as a native port. The automatic bulk goal stays paused.

## Subsequent human acceptance and integration

The user accepted the base build and authorized continuation. [Normal-expedition integration](../canonical-shooting-production-integration/README.md) is complete and checked. Statements above about pending review/integration describe the preserved demo checkpoint; exact native fidelity and later stat/health/enemy acceptance gaps remain open.
