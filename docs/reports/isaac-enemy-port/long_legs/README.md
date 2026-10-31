# Baby/Crazy Long Legs and Sack — regular enemies

This slice covers Baby Long Legs **206.0.0**, Small Baby **206.1.0**,
Crazy Long Legs **207.0.0**, Small Crazy **207.1.0**, and required offspring
Sack **30.2.0** against installed Repentance 1.7.9b. All remain in progress.

The [native evidence](source/manifest.json), [animation metadata](animations/manifest.json),
[XML and habitats](records.json), and [source review](source-review.json) preserve
the reasoning and numeric evidence. The [pinned wiki articles](wiki-source.json)
retain their revision, attribution and CC BY-SA 4.0 license.

Baby flees and pauses for a 45-frame laying animation, producing a Spider at
frame 26. A 1-in-20 roll adds an opposite-moving twin. Laying is gated by total
room population below six, rather than a fixed three-child cap. Small Baby lays
a partly grown Sack and slowing white creep. Both keep their children after dying.

Crazy chases using physical navigation. A direct clear route enables its attack
check. Its 45-frame animation fires at frame 22: eight fixed directions for the
large variant, four diagonals for the small one. The projectiles use the native
falling modifiers translated into physical arcs. The installed controller gives
both variants the same movement force; the small walk animation runs slower.

Sack has no contact damage. It begins at 7 of 20 source HP and grows toward full
health with accelerating regeneration. Taking damage resets that acceleration.
At full size it can shake without attacking or throw a Spider, depending on
room population and RNG. That Spider follows a checked airborne trajectory,
then switches to its normal ground controller. Wet-floor replacements produce
a Strider and use its water-crossing landing rules.

The four parents are sparse seeded specialists, with source habitat differences
mapped onto expedition bands. Sack enters through Small Baby births. Hubs,
Mine enemies, player defaults, Original style and expedition length are preserved.
Attack timing, chances, HP, forces, offspring and regeneration values live in
`assets/mechanics/long_legs.mechanics` and use the existing immutable reload system.

Local canyon pathfinding, physical arcs, retained capacity, procedural silhouettes,
and white-creep radius/lifetime are documented adaptations. Hard mode, champions,
special native status/item branches, exact grid/RNG parity and the full acceptance
gates remain open. The report does not treat these as completed ports.

Validation is recorded in [the checkpoint](checkpoint.json). **73 unique native
suites pass** across the full run and two corrected reachability fixtures.
The initial full run passed 71 suites: adding specialists changed weighted seeded
selections, invalidating old Hive and Mulligan witness samples. Independent
searches found the variants in real generated rooms. The fixtures retain their
earlier samples and add the new witnesses; mechanics and probabilities did not
change. Original failures and search output are preserved.

The [focused behavior output](behavior-final.txt) covers exact animation events,
shot counts/directions, offspring, regeneration, capacity, collision and strict
configuration. [Ten production WASM cases](web/results.json) pass without script
or GL errors, including all four parents in actual seeded rooms. The
[visual review](visual-review.json) records twelve usable Linux/WASM captures.
Earlier isolated captures with an unsettled camera or fleeing enemies outside
the view remain available but do not count as visual approval.

Opening-floor witnesses, using zero-based floor/room indexes:

| Enemy | Seed | Floor | Room |
|---|---:|---:|---:|
| Baby Long Legs | 9 | 0 | 1 |
| Small Baby Long Legs | 1 | 0 | 4 |
| Crazy Long Legs | 3 | 0 | 5 |
| Small Crazy Long Legs | 4 | 0 | 3 |

For example, `build/deathward --mute --smoke --theme canyon --scene resident-206.0.0 --resident-seed 9 --resident-floor 0 --frames 600`
runs the actual Baby room. An isolated `--scene enemy-30.2.0` demonstrates Sack
growth and throwing. The capture/debug options do not alter normal encounter
selection. All five records remain **in progress**. The immutable checkpoint
also verifies that all 5,816 earlier report artifacts were preserved.
