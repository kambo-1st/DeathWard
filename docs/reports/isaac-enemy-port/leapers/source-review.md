# Leaper34.0.0 and Sticky Leaper34.1.0

This review targets the installed Repentance1.7.9b executable and its matching
archives. The executable SHA256 is
`04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.
[Native windows and constants](source/manifest.json) and
[extracted animation metadata](animations/manifest.json) are reproducible with
`python3 scripts/isaac-reference/analyze-leapers.py --check`.
The extraction stores metadata and disassembly, without importing source artwork
into DeathWard. Previous report artifacts are pinned in historical-integrity.json.

The locally preserved [Hopper article, revision267012](https://bindingofisaacrebirth.wiki.gg/index.php?oldid=267012)
describes ordinary hopping, occasional high leaps, a normal four-way landing
shot, and Sticky's slowing black creep and scattered six-shot landing.
This is paraphrased from the Binding of Isaac wiki contributors under
[CC BY-SA4.0](https://creativecommons.org/licenses/by-sa/4.0/); the complete pinned
article remains in docs/research/isaac-mechanics-reference.json, articles.Hopper.
The newer article is corroboration, not a substitute for the installed baseline.

## Verified normal-hostile contract

Both exact tuples dispatch to0x514450. XML gives HP25/28, stageHP0,
contact1, mass10, collision radius13 and no boss classification. DeathWard's
existing HP conversion gives80/89.6, correcting Sticky's legacy96.

OrdinaryHop has26 frames, Jump4 and Land17. Its native destination controller
uses range130, wander95, grid40, arrival10, near threshold30, far force.05,
ground factor.1 and post-retention.7. Leapers have no random range bonus or
initial idle threshold. Ordinary hops do **not** fire a generic Cross/Burst.
Sticky's currentLand event creates black creep, native effect1000.26,
scale1.5 and timeout300 frames (0x515d70..0x515dd9).

At destination release, the type34 branch0x516375 selects a big jump with
RNG remainder0 modulo7. It snapshots the current target and, if the target grid
is blocked, asks for a legal nearby position within120 native units. Selection
does not add the ordinary130-unit acquisition limit. The source also checks
special-status flags0x1000a00 and has a separate controlled-actor path; these
remain outside the reviewed ordinary-hostile path.

BigJumpUp12 triggers Jump5. Once Jump has occurred, source collision classes
become0 and progress increases.02 per30Hz update. The position advances toward
the committed destination by the remaining delta times that progress.
BigJumpDown40 continues this motion until Land22, restoring collision classes
4/5. CurrentLand releases its payload once; the remaining animation recovers.
There are29 interpolation updates (7 during Up,22 during Down), with final
progress.58. A player's subsequent movement does not retarget the leap.

Normal landing calls FireProjectiles mode6 at0x5155e9, producing a world-cardinal
cross. Source speed9 is selected for normal play; hard mode uses12. The local
default is27; source hard speed36 is documented but is not tied to DeathWard's
unrelated progression/aggression settings. Default projectile height-23,
falling speed[-.1,.1], retention.9 and base acceleration.1 become height1.15,
upward velocity[-.15,.15], retention.9 and gravity4.5.

Sticky landing creates black creep scale2, timeout300, then calls
FireBossProjectiles(6,zero,10) at0x515569 with scale.7 and custom color. The
preserved helper0x6a3420 chooses independent random directions when target is
zero; planar speed7 becomes21. Falling speed is -5-24U, becoming upward
velocity7.5..43.5. Acceleration1.32 plus the integrator's base.1 gives local
gravity63.9, retention.9. Radius uses local base.22 times
(.9+.4*bit+.05U)*.7, retaining the two size groups. Coloring a shot does not
give it native impact-creep behavior: these remain ordinary physical bullets.

Neither tuple has required offspring or a special death sequence. Already
released projectiles and creep survive the owner; un-emitted landing packets
are cancelled on death. DeathWard retains its existing hostile-projectile
completion rule after the ordinary body dies.

## Explicit DeathWard adaptations and unresolved scope

- External leapers.mechanics contains all new phase/flight/creep parameters.
  The shared target_hop controller keeps native30Hz decisions and existing
  metres conversion. High-leap height6 and the 3D arc are local presentation.
- Flight respects actual room boundaries/closed gates and clears rocks/water.
  Blocked target correction uses a bounded half-metre radial search within12m,
  rather than reproducing Isaac's fixed grid helper. Newly blocked ground falls
  back to the last legal position. High-leap preparation stops residual local
  momentum; native render/movement-scale damping is not claimed as exact3D parity.
- A ground landing marker is a local readability aid. Procedural bodies retain
  Original style, with muted red normal skin and dark Sticky skin; the dark
  bullet tint is locally chosen, not a sampled sprite/material color.
- Ordinary physical projectile collision and aim assistance exclude the high
  airborne interval. Direct scripted damage/explosions retain existing rules;
  no claim is made that the source is immune to every damage kind while airborne.
- Creep is non-damaging Tar with locally selected radii1.5/2, native10-second
  lifetime and the existing local slow/residual duration. The source's exact
  effect26 world footprint and slow factor still need measurement. Tar now
  honors its existing harmsPlayer field, including friendly patches.
- Whole landing packets wait for sufficient projectile/event/hazard capacity.
  One pending landing pauses further takeoffs. Native has different capacity
  constraints. Local stun cancels preparation or lets an airborne body finish
  a safe landing, delaying its attack until recovery. Inactive rooms freeze
  state; re-entry resumes it. These are explicit engine integrations.
- Fear/shrink/control branches, all item/status interactions, native hard mode,
  all camera views, mixed-build balance and controlled rendered performance
  remain open. These are **in-progress ports**, not completed six-gate records.

## Stage placement

The preserved room library has positive normal Leaper templates in Caves3,
Catacombs2,FloodedCaves3,Depths45,Necropolis21,DankDepths40. Sticky has61 in
DankDepths. Separate Ascent/Greed records do not determine ordinary weights.
Normal Leapers therefore use sparse band1 pursuit and band2 pursuit/crossfire;
Sticky uses sparse band2 crossfire. Band2 has no separate DankDepths/flooded
floor variant, so that finer habitat remains an explicit local approximation.
No first-floor/tutorial or late-band route is added. Weights, budgets and actor
caps are authored DeathWard pacing, not native template probabilities.
