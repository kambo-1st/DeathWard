# Eggy 29.2.0 — normal hostile source contract

This is a partial regular-enemy implementation. The accompanying checkpoint
records validation; it does not certify full Isaac parity.

Installed Repentance 1.7.9b uses the shared Hopper controller at `514450`.
[Preserved instruction windows](source/manifest.json) and
[animation metadata](animations/manifest.json) establish the following branch
rules; Trite's review explains the common destination/friction law.

- Source HP is **20 + 2 × stage multiplier**, contact 1, radius 13. Eggy has an
  eight-frame idle threshold, zero movement bonus and acquisition range
  `130 × .7 = 91`. Wandering distance is 95; near destinations are the target
  position before clamping/grid snapping, with no Trite overshoot bonus.
- Hop is 26 frames, Jump4 and Land17. The ordinary inertia/ground factor and
  accumulated-Jump collision interval are shared with Trite.
- On the current Land event (`4060f0` wraps current-event query `405e90`), a
  1-in-3 draw returns to idle with counter9999. The next selection starts its
  Hop at frame4 (`515c00`), skipping preparation. It is not a random self-kill.
- Land also creates effect1000.25, white creep, at visual scale .8 with both
  timeout fields150 frames. The common effect's exact radius/slow rule and
  grid marker900 semantics are not inferred from this call alone.
- A pending-death flag transitions Eggy into state5, plays **Die**, saves its
  position, sets HP .1 and an invulnerable/death-processing flag. It remains
  present until the animation ends. The exact generic flag lifecycle is not
  independently certified here; local death deferral is an integration policy.
- Die lasts **70 frames**. Jump7 resets the release counter; Land52 is metadata
  and does not terminate the body. Entity collision class is zero in state5.
- The release counter increments at the Jump event update. Releases occur when
  `(n<=14 && n%3==2) || (n<=31 && n%6==1) || (n<=60 && n%15==0)`.
  Thus the normal zero-status branch has **14 children**, at counters
  `2,5,7,8,11,13,14,15,19,25,30,31,45,60`. With Jump7 counting as n1 these are
  animation frames8,11,13,14,17,19,20,21,25,31,36,37,51,66.
- Each release creates **884.0.0 Swarm Spider**, with independently random
  one-native-unit position scatter and launch direction. Hop kind weights are
  short/medium/long **3:2:1**. Speeds are 5–6, 8–10 and 10–13 native units.
  Child animations start at frames4/5/6 respectively, already after Jump;
  state6 and both velocity/launch storage are set. This is not a normal idle
  Swarm selecting its own first direction toward the player.
- A nonzero signed word at native+bc6 can suppress releases probabilistically.
  Its status identity remains unresolved; do not describe it as room crowding
  or reproduce it from the current local enemy count.

The archived [Hopper wiki revision267012](wiki-source.json) describes Eggy's
white creep, Swarm release and lingering body. Installed ordinary room templates
place it mostly in Necropolis/Utero, with sparse Catacombs/Corpse presence.
The Ascent entry is distinct from ordinary templates. The local intended direct
pool is bands1–3, sparse specialist, max1 per room; weights are authored.

Implementation must retain required births under local capacity/placement limits,
preserve release state across room suspension and prevent early room completion.
It must remove the old instantaneous five-child fallback for configured Eggy.
Children must use the existing dedicated Swarm controller and retain their first
hop metadata even if their parent has disappeared before they can be placed.

Implemented DeathWard adaptations: source HP×3.2; source distance×.1 and velocity×3;
the existing physical target-hop controller for 3D cover/water; a pale slow-only
patch with five-second life and authored radius; safe grounded restoration if a
death occurs over impassable geometry; deferred single kill/loot at Die completion.
An immediate re-hop can be suppressed when its local3D landing point is unsafe.
Exact native RNG, special statuses/champions, Bursting Sack and all six acceptance
gates remain open. No completed-port claim follows from this review.

## Local integration and navigation

The external `eggies.mechanics` record supplies timing, creep, release counters,
child selection weights and first-hop advancement. Children use the existing
dedicated Swarm Spider controller, including source HP. Capacity-delayed births
retain their launch metadata after the parent disappears. The native test caps
the room at one actor, waits through the entire death animation, then restores
capacity and requires all fourteen births. Room suspension freezes the husk and
resumes it without a duplicated release or kill. This covers ordinary generation
zero Eggies; the shared generation-depth limit above four is still an integration
limit, not an extracted native rule.

White creep uses the local Tar slow adapter: radius1.28, duration5 seconds,
movement3.2 versus normal6, with .3 seconds of residual slow. The radius and
strength are authored; only the native effect identity, scale and150-frame
timeout were measured here. The hostile path is tested. Friendly/charm behavior,
including the shared Tar adapter's treatment of `harmsPlayer`, is not certified.

A production WASM resident exposed a real grid mismatch: in seed8/floor4/room10,
the legal player target `(111.197,.214081)` snapped into a rock at `(112,2)`.
With zero random overshoot, Eggy rejected every hop. The target-hop adapter now
uses the radius-clamped, unsnapped candidate when the snapped cell is blocked;
the existing trajectory prediction, water/ground and supply-cache checks still
apply. This is a local arbitrary-geometry correction, not a claim that Isaac
uses this fallback. A native regression reproduces those exact positions; the
browser must show both physical hops and creep in the original generated room.
Trite's native behavior suite also passes with the shared correction.

The dying body no longer draws a health bar: HP.1 is retained to manage its death
sequence, not to present an unkillable combat target. Shots and companions ignore
the harmless husk. Its one kill and loot event occur at Die70; the pending body
and mandatory offspring prevent premature room completion.
