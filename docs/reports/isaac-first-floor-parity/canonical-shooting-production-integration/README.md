# Accepted shooting: normal-expedition integration

**Base build accepted by the user and integrated. Focused checks pass. Exact Isaac equivalence remains unverified.** Normal expeditions and The Lost Survey now use the independently wired Tears, Shot Speed and Range consumers by default. Canonical Speed remains enabled. Damage, enemy HP, health, universal dodge and eight-direction controls are preserved.

Run directly into an expedition:

```sh
./build/deathward --expedition
```

For an isolated campaign, add `--save /tmp/deathward-canonical-shooting-playtest.save`. The ordinary command uses the normal campaign.

## What changed

`Simulation::canonicalShooting` defaults to true. `PlayerShooting.hpp` names the explicit accepted calibration: base Shot Speed retains the chosen Faster feel, and base Range retains the accepted standard-room reach. The nominal Tears producer uses its own rate with held-fire fractional interval carry. Shot Speed cannot change firing intervals or configured reach; Range cannot change firing intervals or launch speed. There is no artificial three-shot cap. Physical inheritance remains an additional movement effect, rather than a change to the base Shot Speed stat. Full native counter, launch, actor and coordinate equivalence are not inferred from the accepted feel.

Primary weapon construction is shared through `primaryPlayerAttack`; shotless Ghost effects repeat that current weapon specification. Existing authored DW damage, projectile-count, cadence and velocity modifier ratios are retained as adaptations. The generic explicit-Event projectile builder remains separate for raw/supplied projectile specifications. Normal and explicit historical comparison modes persist across floor transfers.

Returning projectiles get time for their return leg, and the outward Range check cannot kill a returning leg. Split descendants share their parent's remaining outward distance and account for their birth offset instead of receiving a fresh full range. Their remaining lifetime is also retained. These are production compatibility checks, not complete native child/flag behavior acceptance.

Scatter retains its authored distance budget (14 at the base Range stat), scaled by Range independently of Shot Speed. This custom distance now exceeds the ordinary accepted base reach (11); it is an explicit retained authored-weapon exception, not a claim of Isaac item balance or a silently retuned item. Native item/cache formulas and broader custom-weapon balance remain separate work.

## Verification

The application and executed targets rebuild. Eight focused suites pass: `player_attributes_contract`, `player_speed_attribute`, `canonical_shooting_integration`, `core_contracts`, `heart_gameplay`, `regular_health_balance`, `item_builds`, `expedition`.

New production-default checks cover Mine/Canyon and tutorial starts; the accepted ordinary launch/range/rate and unchanged health/damage; independent stat effects on emitted shots; split range inheritance; return-leg completion/catch; Scatter range independence; 66 authored weapon pair birth/lifecycle cases; floor mode/stat carry-over; and shotless Ghost specification inheritance. The final targeted check adds explicit historical-mode preservation between floors.

The earlier `item_builds` fixture explicitly selects historical authored units, preserving its old exact-value contracts. It is supplemented by the new canonical default tests and 66-pair lifecycle checks, rather than treated as proof of new production behavior. The core cylinder test's minimum shot count is adjusted for the intentionally changed source-rate cadence; the new production suite independently checks actual emission counts.

Actual Game shooting and movement verifiers pass, including all eight directions, 30/60/144 input partitions, independent canonical stats, native flight arithmetic rows, no idle burst, zero-stat disabling, cover/target cases, dodge, and normal default activation. Mine/Canyon arrow and broader keyboard integration checks pass. Input partitions are simulation consistency checks, not rendering performance claims. No broad enemy/full native item acceptance is claimed.

## Still unfinished

Measured live Isaac firing/travel/tile-scale equivalence; complete native counter, birth/emission/transition scheduling, actor/flags/item/height/hit geometry and source cache/modifier formulas; coordinated Damage/enemy HP/hits-to-kill/DPS reconciliation; Luck consumers and previous health/enemy acceptance gaps. Canonical Damage and Luck values are stored but are not their gameplay consumers: ordinary attack damage remains 24 while the stored source Damage baseline is 3.5. Source base/stage HP and the regular-health multiplier were not changed. The automatic bulk goal remains paused; later features still require individual selection.
