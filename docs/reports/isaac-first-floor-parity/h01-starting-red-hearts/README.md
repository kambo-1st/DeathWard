# H01 — three starting red hearts

**Implemented: H01 only.** The bulk parity goal stays paused. No other difference
was selected or implemented by this change.

Fresh players start with current, maximum and base red health of **6 half-heart
units**, shown as **three full red hearts**. The pinned Repentance 1.7.9b
`resources-dlc3/players.xml` entry `id=0`, `name=#ISAAC_NAME` has `hp=6`.
This is a starting-state requirement; it does not establish a full typed-heart
model or complete source damage/healing semantics.

The HUD displays red-heart icons and a whole-heart count. At five half-heart
units it shows two full hearts and one half heart. Existing custom/debug health
capacities above twelve hearts use a compact numeric meter. Health tuning accepts
one half-heart or more so ordinary game launch cannot clamp the new default to
the previous minimum of 25. Debug health buttons change capacity by one full
heart (two units); restoring defaults returns to six units. Existing floor
transfer retains injured health instead of refilling it.

Universal dodge's movement boost and immunity are preserved. Player attack damage
remains 24, starting dynamite remains three, and the regular-enemy health control
and all mechanic files are unchanged. No source weapon, enemy, item, pickup,
room or reward implementation was restored from the archived bulk attempt.

## Verified behavior

- Fresh Mine and Canyon expeditions and The Lost Survey start at 6/6 health.
- The actual Game launch and restore-default paths retain 6/6 current/maximum
  health and base health 6; the debug increase uses two health units.
- An existing damage-unit fixture reduces health to five after dodge ends.
- Actual keyboard dodge blocks an immediately active hostile hazard and moves
  faster than ordinary movement. The lower starting health does not remove
  dodge's boost, immunity or cooldown.
- An injured player retains 5/6 health across a floor transfer; a fresh expedition
  starts at 6/6 again.
- The starting and injured HUD captures were viewed:
  [three full red hearts](starting-hearts.png),
  [two full hearts and one half heart](half-heart.png).

Seven related suites pass across the recorded checks: `core_contracts`,
`regular_health_balance`, `player_dynamite`, `mission_shop`, `expedition`,
`expedition_destruction` and `expedition_economy`. The actual Game/input checks
`--starting-hearts-only` and `--keyboard-only` also pass. Selected application/test
targets build successfully. This is not a claim that every repository suite or
all parity rules were tested.

Existing bomb, shop, bargain and control fixtures that require their former
numeric health budgets now explicitly request 100 health; they no longer assume
that value is the default. Initial test failures and final passing results are
retained separately. The default-health and actual-launch tests assert six units.
No production damage or pricing values were changed to make those tests pass.

## Remaining limitations — other differences are not selected

Enemy contact/projectile damage, self-damage, medicine, health-item floors and
bargain costs retain their authored numeric amounts. **An existing hostile attack
can exceed all six starting units and kill in one hit.** Existing medicine may
refill the entire smaller capacity; authored health floors can also increase
capacity unexpectedly at this scale. Those are pending damage/healing/item
conversion differences, not accepted Isaac-equivalent survivability.

Other heart families, damage-loss order, invulnerability timing, upgrades/deals,
revival, source pickup generation and the complete typed-heart model remain
unfinished. H01 does not authorize implementing them. Wait for the user's next
individual difference selection.

## Reproduce

```sh
cmake --build build --target deathward deathward_tests deathward_input_tests deathward_regular_health_tests deathward_dynamite_tests deathward_shop_tests deathward_expedition_tests deathward_destruction_tests deathward_expedition_economy_tests --parallel 4
ctest --test-dir build -R '^(core_contracts|regular_health_balance|player_dynamite|mission_shop|expedition|expedition_destruction|expedition_economy)$' --output-on-failure
build/deathward_input_tests --starting-hearts-only
build/deathward_input_tests --keyboard-only
```

`validation.json` pins the source, selected XML, application/test binaries,
verification logs and viewed images. Historical rollback/native-parity records
remain historical; their hashes are not rewritten to imply H01 existed then.
