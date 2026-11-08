# DeathWard project terminology

- Call the randomized gameplay portion an **expedition**, or an **expedition into the Badlands**, in player-facing text, documentation and discussions.
- An expedition is the entire run. It contains **floors**, and each floor contains connected **rooms**. Do not use these terms interchangeably.
- Standard expeditions have 4–8 seeded floors, growing from 9 to 15 rooms per floor (Classic comparison preset: 15 throughout). The tutorial expedition, **The Lost Survey**, is the exception: one floor with five rooms.
- **Fort Mercy** is the story hub the player returns to between expeditions.
- Expeditions deliberately follow The Binding of Isaac's room-based roguelike structure. Story rooms are woven into the appropriate floors; they do not replace the multi-floor structure with a short linear story level.
- Existing internal names such as `MissionTheme` may remain. The terminology decision alone does not require renaming code APIs or save fields.

## Enemy fidelity and balance

- Target installed **The Binding of Isaac: Repentance 1.7.9b**. Resolve numeric wiki conflicts against its preserved XML; use measured native behavior for AI conflicts. XML attributes alone do not prove AI behavior.
- Keep source base HP and stage HP separate from DeathWard conversions and adaptation factors. Preserve the current starting balance until a requested playtest adjustment; document deviations rather than changing source values to hide them.
- The audited regular-enemy HP control is `regular_health_multiplier` in `assets/mechanics/regular_enemy_health.mechanics`. Its default is `1`; `.75` means 25% less HP. Use the shared calculation for spawning, champions, offspring and HP-dependent lifecycle rules. The selected H01 starting default is 6 red half-heart units / 24 damage; keep attack damage and bosses separate. H02–H18 are now selected, including incoming damage and healing conversion.
- An expedition floor is mapped to a source stage; do not insert the expedition floor number directly into the source Stage HP formula.
- Registry presence or a wiki description match does not constitute full enemy acceptance. Preserve explicit gaps and scope verification by enemy and behavior.
- Whenever stopping work or ending a work turn, state what remains unfinished. Update the relevant persisted progress report when the remaining work changes; distinguish verified research from enabled gameplay and full acceptance.

## Manual difference selection for Isaac comparisons

- The bulk Isaac parity implementation was reverted at the user's request. The automatic parity goal is paused.
- Consult `docs/isaac_first_floor_implementation.md` for the current state, difference selection register, historical research and recovery archive.
- Implement comparison differences only after the user explicitly selects them (a named range is a valid selection). An archived plan, historical checklist or earlier broad parity objective does not authorize automatic implementation or resuming the bulk effort.
- H01 is implemented. The user has now explicitly selected H02–H18; implement that range and preserve universal dodge, including its speed boost and immunity. S04 walking pace is also explicitly selected: the user preferred option 2 (4.8 world units/s), then requested continuation to integrate it. Preserve immediate stopping, absolute universal dodge speed/immunity and firing controls. Exact native speed parity remains unverified; S07–S09 and the ordinary S02 rate consumer are selected; the accepted independent shooting base is integrated. Full native acceptance is still open. Other differences remain unselected.

## Combat controls retained by user request

- Preserve the current eight-direction firing mechanism and existing mouse/keyboard controls for isometric gameplay. This is an explicit exception to Isaac's firing-direction comparison (S06), alongside universal dodge.
- Do not replace firing with Isaac's four-direction restriction or change aim/input mapping as part of damage, enemy HP, fire-rate, range, movement or hitbox calibration. Those balance changes require their own manual selection and must retain the existing controls.

## Canonical attributes scope

- The user selected steps 1 and 2: the seven-attribute data/adapter model and its Speed movement consumer. Canonical Speed now drives ordinary walking through an explicit accepted-feel calibration; base pace, stopping and dodge are preserved. Runtime health remains in existing player fields; combined source attributes are a transient snapshot. Speed is enabled in ordinary gameplay. The user subsequently selected Tears, Shot Speed and Range wiring: the user accepted the base comparison and authorized continuation. Their independent consumers are now enabled in normal expeditions and the tutorial. Exact native counter/actor/cache/calibration acceptance remains open. The temporary cadence/travel coupling and artificial three-shot expectation are removed; increased stats may produce more simultaneous shots. Preserve the Faster review choice and eight-direction controls. Do not treat this work as authorization for bulk stat, damage/HP, item or save changes.
