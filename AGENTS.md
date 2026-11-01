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
- The audited regular-enemy HP control is `regular_health_multiplier` in `assets/mechanics/regular_enemy_health.mechanics`. Its default is `1`; `.75` means 25% less HP. Use the shared calculation for spawning, champions, offspring and HP-dependent lifecycle rules. Keep player defaults (100 HP / 24 damage), attack damage and bosses separate.
- An expedition floor is mapped to a source stage; do not insert the expedition floor number directly into the source Stage HP formula.
- Registry presence or a wiki description match does not constitute full enemy acceptance. Preserve explicit gaps and scope verification by enemy and behavior.
- Whenever stopping work or ending a work turn, state what remains unfinished. Update the relevant persisted progress report when the remaining work changes; distinguish verified research from enabled gameplay and full acceptance.
