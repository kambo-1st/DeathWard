# S07–S09: revised room-relative projectile review

Status: **revised candidate ready; checks pass; human verdict pending**. The first candidate was rejected for excessive speed, small appearance and excessive reach. Normal expeditions still use their existing projectiles. Earlier native instruction checks established bounded arithmetic, not correct DeathWard world scale. The previous unverified .1 conversion and huge open test field were poor calibration choices.

```sh
./build/deathward_projectile_review
```

The revised candidate is selected on launch. Shoot using the usual arrows (including diagonals) or RMB. **2** selects the revised candidate; **1** retains the old fast bullets for comparison. **T** cycles frozen targets at none / 6 / 9 / 11 / 11.5 units. Targets have 48 HP and die to two normal shots. **F8** resets the room and targets. **F11** follows a shot; existing camera rotation and zoom remain available. The room uses a unique temporary save and actual Game/Simulation/renderer code.

## Revised values and checks

- The visible room is 24×24 world units, within normal Compact first-floor 20–28-unit side dimensions. Both modes use the same room, spawn and view.
- Candidate launch speed is **12 world units/s**, down from 30 in the rejected preview. Native falling arithmetic and movement inheritance remain, with an explicit .04 spatial conversion chosen for this review. It is not a measured live Isaac conversion.
- Path-distance reach is capped at **half the shorter room side minus one unit**: 11 here. Stationary shots in the seeded fixture sample about **10.4 units**; moving/dodging inherited shots also obey the cap.
- Candidate lifetime is bounded at .88 s. Sustained ordinary firing naturally has **at most three live projectiles** at the current unchanged cadence. No renderer-only hiding is used. This bound is a requested adaptation, not claimed native lifetime parity.
- Candidate bullets have **twice the visible radius** (.28 versus .14). Collision radius stays .14 for this stage; native hit geometry remains a separate acceptance task.
- Accepted walking (4.8), immediate stopping, universal dodge (20.4 and immunity), eight-direction mouse/keyboard controls, damage (24), cadence and expedition enemy HP are preserved.

The revised verifier passes all 171 independent native flight rows and birth conversion, 48 stationary Game/input shots in eight directions at 30/60/144 partitions, movement inheritance, near/out-of-range targets, cover, two-hit demo target deaths and dodge. New sustained-fire checks reach a peak of exactly three active projectiles at all three partitions, and inherited shots cannot exceed the room cap. Four focused regression suites plus existing Mine/Canyon arrow and keyboard integration checks pass. Input partitions establish simulation consistency, not rendered performance.

[Current evidence and measurements](room-calibration-revision/validation.json) and [current inspection image](room-calibration-revision/candidate.png) are retained. The image verifies initial room/UI rendering only. Root-level older logs/images describe the rejected first preview; its prior validation is preserved in `room-calibration-revision/previous-validation.json`. The binary and private mechanics snapshot live outside Git; `validation.json` points to the current executable. Visual assets still use this checkout.

Still unfinished: your judgment of the revised feel/reach/visibility, exact live Isaac calibration and production integration; full native actor/birth scheduling, flags/items/children/RNG and hit geometry; later combat balance stages and prior health/enemy acceptance gaps. None of the rejected preview is silently promoted as accepted source parity.
