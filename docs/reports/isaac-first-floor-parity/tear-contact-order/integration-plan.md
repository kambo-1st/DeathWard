# Integrate source contact scheduling and ordering

This is remaining implementation work, not a declaration that the ordinary
projectile area is accepted. Keep the six-area goal intact and retain universal
dodge with speed boost and immunity. Preserve HP, attack values and the shared
regular-health multiplier.

1. **Capture the coupled actor schedule before changing it.** Extend the native
   fixture through primary birth registration, the original entity-manager
   update pass, collision pass, interpolation and the following main update.
   Include an overlapping newborn target and a terrain-only contact. Verify the
   active-list append/collision inclusion against the original spawn/add path.
   Existing captures prove the supplied collision pass, not the entire schedule.
2. **Place primary materialization before the appropriate collision pass.**
   Rework the queue boundary so a newly materialized primary tear can participate
   when required. Preserve its already correct center origin, post-birth offset,
   initial flight invocation and rewind. Avoid moving it or advancing flight
   twice. Verify zero/subtick/large-step behavior rather than inferring phases
   from a presentation timer. Maintain queue limits, attribution and item events.
3. **Run a shared native collision batch at the verified world phase.** Reproduce
   the 80-unit spatial-bucket traversal, actor insertion order and pair
   deduplication. Multiple simultaneous tears and targets must share the batch;
   selecting a target independently per projectile cannot prove global ordering.
   Pin the native/world room-coordinate mapping and retain calibration gaps.
4. **Apply source geometry and eligibility.** Use current-position, strict circle
   overlap for ordinary unit-axis bodies, then source collision-class/dead/flag
   gates. Preserve explicit gaps for non-unit axes, rotations, compound bodies,
   airborne states, friendly actors, special flags and character/item effects.
   A swept segment or globally nearest target does not implement this contract.
5. **Match callback and mutation order.** The tear handler precedes the NPC
   handler. Damage needs its original flags/reference/countdown and immediate
   health/status outcomes before later pairs. Ordinary tear consumption occurs
   even for the captured rejected-damage result. Do not invalidate enemy storage
   during callbacks or lose bounded event/offspring requests. Native HP mutation,
   immunity and lethal effects still require execution beyond the current damage
   boundary. Keep source HP and conversions distinct.
6. **Perform terrain after entity pairs and verify its lifecycle.** A terrain
   contact flag is not itself proof of immediate tear death. Couple the next
   original Tear::Update to the grid contact and capture terminal behavior before
   replacing the current continuous terrain sweep. Verify class-specific grid
   rules, exact boundaries, source floor death, room transitions and special tears.
7. **Turn the counterexamples into acceptance checks.** Compare the coupled
   source schedule and runtime at birth, intermediate and main phases; require
   correct target, damage request/result, lifetime and position. Include all
   recorded permutations/classes/scales and multiple moving actors. Add actual
   gameplay/input checks, retain universal dodge, and run the affected existing
   projectile/enemy/item/health suites. Review live source/gameplay evidence.
   Report scoped research, enabled gameplay and full acceptance separately.

Outside this contact integration, all six broad areas remain open: movement,
projectiles, other heart types, source enemies/bosses, items, and rooms/rewards.
Nine Basement XML boss entries still lack controllers. Production source boss
selection, source-item eligibility/effects and source room/reward generation are
not enabled by this research checkpoint. No overall percentage or ETA is proved.
