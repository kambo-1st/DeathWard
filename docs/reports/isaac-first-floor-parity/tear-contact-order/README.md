# Ordinary tear contact and ordering — native research

**Research is verified; this collision ordering is not enabled in gameplay.**
The application remains at `3801552ba3f01ba9-isaac-baseline-v23`. Universal dodge,
including speed boost and immunity, remains the accepted exception. All six broad
parity areas remain unfinished.

## What executes

`analyze-tear-contact-order.py` pins the installed Repentance 1.7.9b executable,
XML and local x86 UCRT/VCRUNTIME. The executable SHA256 is
`04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.
Original instructions execute the collision-manager pass at `0x414f80`, its
spatial insertion/pair methods, circle geometry and collision-class gate, ordinary
tear handler `0x64dcd0`, NPC handler `0x6a3970`, ordinary zero-flag tear death
routine `0x650dd0`, and terrain collision method `0x682280`.

The actual source constructor argument block at `0x412a42` and complete spatial
constructor initialize each of eight grids. They have width 1200, height 720,
step 80, 15 columns, nine rows and 135 buckets. These are source constants, not
assumed dimensions chosen to make competing targets share a bucket. The complete
manager performs original pair deduplication. The source caller's gate at
`0x414724` invokes that pass for input 0 and skips it for input 1.

There are **2,016 cases**: three tear scales, fourteen scenarios, six actor-list
permutations, optional terrain, both caller inputs and two supplied damage-return
values. The captures contain 5,040 event observations: 480 tear-handler entries,
480 damage requests, 480 ordinary death-routine entries, 576 NPC-handler entries
and 3,024 terrain-method entries. Both complete capture generation and `--check`
regeneration pass.

For the recorded ordinary cases:

- Circle contact uses current planar positions and a strict summed-radius test.
  At tear radius 7 and target radius 10, distance 17 is excluded; 16.99 is admitted.
- Collision classes 0, 1 and 3 reject the supplied tear/NPC pair. Classes 2 and 4
  admit it. This does not accept every flag/friendly/character combination.
- Target selection depends on bucket traversal and insertion order. For the
  `opposite_cells` case at scale 1, the left target wins all six permutations.
  The `farther_first` input layout selects npc1 in all six permutations. A global
  nearest-target rule or an unconditional first-storage rule is insufficient.
- Each damage request precedes terrain collision. The ordinary request is 3.5
  damage, flags 0 and countdown 30. The tear handler runs first; the second NPC
  handler still runs after the tear is consumed. Subsequent pairs cannot damage
  another target with that consumed ordinary tear.
- The original caller consumes all 480 tears that issue a request, including
  cases where the supplied damage result rejects it. The fixture does not set
  the tear's dead flag on behalf of the collision routine.
- Caller input 1 produces no collision events in all 1,008 corresponding probes.
  This verifies that bounded caller gate, not a complete Game/Room scheduler.

## External boundaries and limits

NPC `TakeDamage` at `0x6ac370` records the amount, flags, source reference and
countdown, then returns a supplied boolean without changing HP. **Native damage
application, actual NPC death and damage callbacks are not accepted.** Both NPCs
retain the supplied HP of 10. Their entity/config constructor state, positions,
collision classes and ordinary flags are supplied; full NPC/player/tear creation,
XML loading and AI updates are not executed. The optional room-grid body is also
supplied. The player list is empty for manager traversal; the tear retains a
supplied player owner with empty inventory/callback registries.

The complete ordinary zero-flag tear death routine executes. Special tear flags
and their world effects remain unaccepted. Original UCRT numerical exports and
VCRUNTIME RTTI execute; CRT allocation/memory operations use the existing fixture
boundaries. The profiling `timeGetTime` boundary returns zero. Missing imports
point to unmapped addresses, so an unconfigured call faults instead of executing
an import-name RVA as instructions. No collision instructions are patched or
replaced by host geometry calculations.

The supplied actor population and caller input do not prove live birth timing,
room transitions, global RNG order, spatial conversion or production eligibility.
Whole manager execution is stronger than a pure-circle description; it still
does not establish full gameplay parity.

## Current runtime differences

`deathward_contact_order_probe` builds and runs against this capture. It reports
**six first-step differences in ten supplied circle scenarios** for v23. The
first-step shots retain the correct center birth and one initialized flight state,
but have no damage at that check. The supplied native main collision pass can
already issue damage for overlapping targets. Current shots hit during a later
simulation step. The production code queues shots in `updatePlayer`, runs
`updateProjectiles`, then materializes those shots during the final event drain.

This diagnostic compares fixture outcomes, not a full matched native gameplay
recording. Its DeathWard targets are stationary Gunman bodies with radius 1 and
HP 10, representing the supplied native radius-10 circles after conversion.
Body separation, scheduling and coordinate calibration are not isolated. The
output records subsequent intermediate/main-step HP for follow-up investigation;
it must not be read as acceptance of all those timestamps. The diagnostic exits
successfully when the comparison runs, including when mismatches remain. It is
intentionally not registered as a passing parity test in CTest.

The [integration plan](integration-plan.md) preserves the full required work.
Source/evidence/probe/application hashes and exact verification are recorded in
`validation.json`. The earlier v23 application/22-suite/desktop results remain
historical validation of that unchanged runtime; they do not accept these gaps.

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-tear-contact-order.py --check
cmake --build build --target deathward_contact_order_probe --parallel 4
build/deathward_contact_order_probe docs/reports/isaac-first-floor-parity/tear-contact-order/native-manager.csv
```
