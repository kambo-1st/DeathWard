# Boil family — regular enemies

This checkpoint replaces generic behavior for **Boil 30.0**, **Gut 30.1**,
**Walking Boil 88.0**, **Walking Gut 88.1** and **Walking Sack 88.2**, and extends
the previously reviewed **Sack 30.2**. Subtype is zero for all six. The baseline
is installed Repentance 1.7.9b; these records remain in progress.

The [source review](source-review.json) links nine preserved native code windows,
checked constants, six extracted animation records, installed XML and source
room-library habitats. The [wiki snapshot](wiki-source.json) retains revision
262993, attribution and its CC BY-SA 4.0 license. The source executable, rather
than wiki prose alone, supplies timing, projectile calculations and damage rules.

| Family | Movement and health | Attack |
|---|---|---|
| Boil | Stationary; starts at 7/20 source HP, grows back after damage | Three or four scattered, short-range blood shots |
| Gut | Same growth as Boil | One physical explosive Ipecac lob |
| Sack | Stationary; slower regeneration | Throws a Spider when room population permits |
| Walking Boil | Wanders, starts full-sized, never regenerates | Same blood volley |
| Walking Gut | Wanders without regeneration | Same Ipecac lob |
| Walking Sack | Wanders without regeneration | Throws a Spider from a higher starting point |

All attacks use the 24-frame Shoot animation and its frame-12 event. Stationary
damage interrupts shooting and resets growth. Walking damage does neither.
Sacks check total room population; a rejected stationary Sack shakes, while its
walking variant continues moving. Thrown children remain independent after their
parent dies and participate in room completion. Wet-floor Spider replacements
also apply to these births.

Both source controllers filter hostile/environment explosions, including their
own Gut shots. Player, friendly/familiar and TNT explosions still hurt them.
The implementation reuses the existing damage-provenance system rather than
granting blanket bomb immunity. Only walkers deal contact damage.

`assets/mechanics/boils.mechanics` exposes the cycle, movement, projectile,
explosion and encounter values. The prior `sack` directive remains compatible.
Immutable reloads validate the whole candidate library before replacing a
snapshot. Original-style procedural geometry retains the existing blobs, with
red blood shooters, green explosive shooters, pale Sacks and small walking feet.
Hubs, Mine roster, player defaults, tutorial and expedition structure remain intact.

Source habitats determine eligible local bands. Boil and Walking Boil occupy
bands 1–3, Gut and Walking Gut 1–2, and Sack variants 0–2, with a maximum of one
of each identity per room. Local weights and costs are authored balancing values.
The former Gut band-3 route had no supporting ordinary source habitat and was
removed. Wiki replacement percentages are preserved for later native review;
they are not passed off as verified installed selection rules.

**74 unique native suites pass**, across the full 72-pass run and two corrected
placement fixtures. Expanding the specialist pools changed earlier deterministic
selections. Independent production searches found Drowned Hive at seed109,
floor2, room6; Mulligoon at seed35, floor0, room5; and Mulliboom at seed160,
floor1, room4. The tests retain their earlier candidates and add those examples.
No gameplay weights or replacement rules were changed to satisfy the tests.
The original failures and corrected results remain in this report directory.

Focused native checks cover regenerative recurrence, source events, blood/Gut
flight endpoints against an independent source recurrence, real explosive impacts,
immunity exceptions, retained volleys and impacts, room completion, physical
movement, thrown children, configuration rejection and actual seeded placement.
Expected queue-capacity messages come from deliberately exhausted test queues.

**All 13 production WASM cases pass**, covering six isolated family members,
walking navigation around cover and six actual seeded resident rooms. Browser
telemetry verifies attacks, growth, movement, living offspring, Original style
and no WebGL/runtime errors. It does not certify the entire roster.

The [visual review](visual-review.json) records 24 inspected Linux/WASM images.
All six bodies have visible isolated captures. Two generated-room Walking Boil
frames show only the existing cliff-occlusion outline; one native Walking Gut
frame catches an opaque explosion covering its body. These frames expose real
readability limits and are not counted as body-visibility passes. Broad combat
readability remains open. An interrupted native capture batch retained its ten
completed images and partial log; the last two captures succeeded separately.
Incidental FPS overlays are not controlled performance measurements.

Local 3D navigation, swept collision, height conversion and finite-capacity retry
are documented adaptations. Hard mode/champion/status/control branches, exact
grid/RNG parity, native replacement rates and full readability/balance/performance
acceptance remain open. No definition is certified complete by this report.
