# Canonical attributes — step 2: Speed movement consumer

**Implemented and checked: Speed drives ordinary walking in the game.** Speed 1 preserves the previously accepted walking pace. Stopping remains immediate; universal dodge and eight-direction firing are retained. This is the user-selected movement step, not authorization to wire the other stat consumers.

## Implementation

`Player` stores the six scalar source attributes as `SourcePlayerStats`. Typed health remains in the existing authoritative player fields. `sourceAttributes()` returns a combined snapshot that reads live typed health, avoiding a second mutable health bar. Only Speed has a gameplay consumer at this step. Other scalar defaults remain source-domain values; for example canonical Damage 3.5 is not yet a replacement for the existing 24-damage attack.

`WalkingPace` is an explicit accepted-feel calibration. Its proportional mapping anchors Speed 1 to the accepted walking pace. This is not a native acceleration/cache/cap formula port, and it does not select an unverified global native tile/coordinate/clock conversion. `Player::walkingSpeed()` derives ordinary walking speed; the previous separately stored world-speed field is removed.

Keyboard and click-to-walk both consume the derived Speed. Zero Speed preserves a click route without movement or division by zero; the route resumes when Speed becomes positive. Diagonal normalization, stopping and reversal are unchanged. The existing ordinary slow ratio follows Speed as well, preventing a slow effect from speeding up a low-Speed player; the default slow pace remains unchanged. Source-specific slow rules (S14) remain unported.

Universal dodge retains its existing absolute boost, immunity, duration and distance independently of Speed, including the pre-existing final-tick slow exception. Physical player velocity still reflects movement for existing prediction/inheritance consumers; that is not a change to base Shot Speed. Floor transfer copies the source scalar state. Save formats, authored item rules, UI and campaign behavior are not changed; no new stat-upgrade/persistence system is claimed.

The historical movement A/B tool now selects its old physical comparison paces through Speed calibration. The projectile review uses canonical base Speed and keeps the selected Faster review checkpoint separate from normal-expedition integration.

## Verification

The application and all executed targets rebuild. Five focused suites pass: `player_attributes_contract`, `player_speed_attribute`, `core_contracts`, `heart_gameplay`, `regular_health_balance`.

New actual Simulation checks cover straight/diagonal Speed values zero, half, base, one-and-a-half and double; normal and slowed walking; immediate stop/reversal; zero-Speed click pause/resume and destination arrival; dodge boost/distance/duration/immunity at every Speed; independence from Shot Speed/Tears/Range/Damage/Luck; unchanged existing projectile damage/speed/cadence; a live health snapshot without duplicate authority; and Speed carry-over between floors.

Actual Game movement input checks pass at 30/60/144 input partitions, including the default pace, keyboard/click walking, no diagonal boost, stopping, dodge and retained firing. The projectile review verifier passes its native-row, firing, inheritance, same-reach/cadence, cover, target and dodge regressions. Separate Mine/Canyon arrow and keyboard integration tests pass. These timing partitions are not rendering performance claims. No broad enemy acceptance is inferred from these focused checks.

## Still unfinished

Step 3 must wire Tears, Shot Speed and Range independently and retire the temporary review travel-time/cadence coupling, followed by a human shooting check before production projectile integration. Damage and enemy HP/DPS reconciliation, Luck consumers, source cache/upgrade/cap formulas and later persistence/HUD wiring remain unselected work. Exact live native movement/acceleration, spatial/clock calibration, source slow rules and earlier health/enemy/actor/hit-geometry acceptance gaps remain. The accepted Faster review choice, universal dodge and eight-direction controls stay recorded.
