# Ordinary and Flaming Hopper: installed 1.7.9b review

This slice replaces the earlier fixed-distance, fixed-duration approximation for
**29.0.0 Hopper** and **54.0.0 Flaming Hopper**. It covers ordinary hostile
behavior. Neither exact record is a completed six-gate port.

## Reproducible evidence

`scripts/isaac-reference/analyze-hoppers.py` pins the installed executable SHA-256
`04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`, checks
both dispatch entries, saves three disassembly windows and resolves the highest
installed DLC animation metadata. `--check` re-extracts and compares every byte;
it never rewrites the frozen evidence. The two animation descriptions come from
`afterbirthp.a`, after checking for Repentance overrides. No source artwork is
imported into the runtime.

- [Native manifest](source/manifest.json): both types use dispatch index 16,
  case `0x69a19f`, calling controller `0x514450`. Preserved windows cover that
  controller, the normal target helper and the morph entry point.
- [Animation manifest](animations/manifest.json): ordinary Hop has 26 frames,
  Jump at 4 and Land at 17; Flaming Hop has 26 frames, Jump at 5 and Land at 18.
  Source animation updates run at 30 Hz. The normal file also contains big-jump
  animations, but these two ordinary controller branches do not select them.
- Installed `entities2.xml`: base health 10/20, zero stage health, contact damage
  1, collision radius 13, mass 10; both are non-boss champion-eligible enemies.
- Preserved [Hopper article, revision 267012](https://bindingofisaacrebirth.wiki.gg/index.php?oldid=267012),
  credited to Isaac wiki contributors, CC BY-SA 4.0, provides descriptive
  behavior and fire context. The installed code supplies numeric details.
- [Stage evidence](stage-evidence.json) retains source room-template habitats.
  Positive template counts establish habitat evidence, not spawn probability.

## Source behavior and implementation

| Concern | Installed behavior | DeathWard implementation |
|---|---|---|
| Ordinary timing | Idle threshold zero; one Hop animation, 26 frames | Shared `target_hop`, source-frame accumulator; Jump/Land events at 4/17 |
| Flaming timing | Same duration; events at 5/18 | Separate external profile; no arbitrary shorter arc |
| Ordinary target bonus | Zero | No bonus RNG draws |
| Flaming target bonus | One uniform value times 50 on each normal update, `0x5149a0..0x5149e5` | Same draw cadence for ordinary hostile updates |
| Acquisition | Strict distance less than `130 + 1.3 * bonus` | Source units multiplied by 0.1; 13 units for ordinary, variable for Flaming |
| Pursuit | Target plus `delta * bonus / 200` | Committed snapped destination; moving the player cannot retarget an active hop |
| Flaming prediction | Target velocity times five source frames, `0x515837..0x515880` | Optional `leadFrames` field, 5 for Flaming; world velocity times 5/30 seconds |
| Wandering | Random direction times `95 + bonus` | Source distance conversion, not the old fixed 2/3-unit steps |
| Destination/steering | Grid 40, margin 5, arrival 10, near range 30, force .05, grounded factor .1, retention .7 | Shared destination-hop recurrence in source units |
| Release | After animation, arrival or stochastic stuck release; speed .75, age 30, one-in-ten release | Same ordinary controller predicates |
| Collision | Accumulated Jump changes classes; completed animation restores ground classes | Real elevated body until animation ends; Land is an event within that interval |
| Landing attack | Neither exact ordinary branch emits a landing projectile, creep, fire trail or offspring | Contact-only enemies; no high-leap or landing payload attached |
| Fire transformation | Queued fire damage changes 29.0 into 54.0 and removes that damage entry | Existing typed flame path with in-place identity change and flame immunity |
| Morph health | Stores current/max health before Morph, then multiplies by the new maximum, `0x51468b..0x51471d` | Preserves health fraction; this policy is now source-verified |

The normal target helper is preserved at `0x695a30..0x695c2e`. Special targeting
and player-control branches exist; this review does not certify all of them.
The morph window includes the complete entry point and some following bytes.
Its nested initialization calls have not been exhaustively traced, so continued
animation/momentum across the transformation is explicitly a local policy.

## Necessary 3D adaptations

Health uses the existing conversion of source HP times 3.2: **32/64**. Ordinary
Hopper previously had 48 HP. Player defaults remain 100 HP and 24 damage. Local
contact damage is 10; body radius .6 and apex offsets 1.4/1.8 retain the Original
procedural rendering. These are DeathWard conversions, not native values.

Actual generated geometry replaces Isaac's flat grid. Before takeoff the
controller predicts its stepped trajectory and requires a legal landing. If
snapping puts a legal target inside a non-grid-aligned rock, it tries the legal
unsnapped candidate. Flight clears rocks and deep river water but cannot cross
closed full-height room gates. Dynamically invalidated landings return to the
last legal ground point. Projectile aiming, hits and fire exposure use the
actual elevated body; ordinary hops do not receive Leaper high-jump immunity.

A fire transformation during flight snapshots the original hop profile until
that flight ends, keeping its target, phase and momentum. This prevents a
one-frame shift in collision timing from embedding the transformed body in
terrain. Stun and inactive-room suspension also retain committed flight.
Transformation preserves the entity ID, summoner and team, and grants no kill or
pickup. Burning remains a separate damage channel. The source ratio calculation
is verified; complete fire producers and all status interactions are not.

Both forms keep sparse bands 0–2 pursuit pools. Existing first-band Scorched
replacement of normal Hopper with Flaming Hopper remains 60%, with one extra
reserved threat point. Floor-variant odds, pool weights/caps and threat costs
are authored DeathWard pacing. Natural early-floor witnesses are Rourke seed 0,
floor 0, room 2 (normal) and seed 5, floor 0, room 5 (Flaming).

## Open work

Fear/confusion, player-control and champion branches; native RNG stream parity;
all item and flame producers; complete damage-class/status interaction coverage;
all-camera mixed-room readability; mixed-build/full-floor balance; controlled
rendered performance. Original visual style and existing expedition, tutorial,
Mine and hub structure are retained. This slice improves two already reviewed
regular records; it does not add two new completed enemies.
