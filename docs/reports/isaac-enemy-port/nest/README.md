# Nest — installed Repentance 1.7.9b

Nest `205.0.0` is a regular, harmless-contact fleeing spawner. This slice adds a
source-backed implementation and early/middle expedition placement. It is **in
progress**, not fully accepted enemy parity.

## Source evidence

The [native manifest](source/manifest.json) preserves eight executable windows,
their hashes, verified constants, exact XML attributes and room-library counts.
The executable SHA-256 is pinned by `scripts/isaac-reference/analyze-nest.py`.
The [animation manifest](animations/manifest.json) and extracted `.anm2` retain
the highest installed DLC override, its archive checksum and timing metadata;
no Isaac sprite artwork is imported into DeathWard.

The preserved [Mulligan article](../hive/mulligan-wiki.wikitext), revision
[271647](https://bindingofisaacrebirth.wiki.gg/index.php?oldid=271647), independently
describes the Nest's live/death-spider distinction and overkill suppression. An
attempt to reopen this pinned URL on 2026-10-28 failed in the web tool; the cached
revision and installed executable/archives remain available for verification.

## Implemented contract

- Source HP 20, stage growth 0, contact damage 0 become 64 DeathWard HP with the
  existing ×3.2 conversion. Player defaults are unchanged.
- Initialization consumes one 30 Hz source update. Thereafter the shared ground
  evader wanders or flees, checking proximity every 14 staggered updates with
  visible/hidden ranges 250/170 source units and three checks of memory.
- Source path force, friction and wander impulse feed physical canyon navigation.
  HeadAttack coasts instead of continuing active evasion.
- HeadAttack lasts 18 updates and emits a Spider at Shoot frame 4. Nest's timer
  is 75 + 55 + RNG%20: **130–149 source updates**, not Hive's fixed 75. It counts
  down while evading. Out-of-range and blocked-sight retries are 3 and 7 updates.
- The live-spit gate counts the room population, not just owned spiders. At an
  almost-expired timer, a random threshold 4–8 can add 20–69 updates of delay.
- Live Spiders retain full 20.8 HP and their committed stop/burst controller.
  Their birth captures contact expiry, independently of the owner's lifetime.
  Contact deals normal damage when applicable, then expires the child even if
  the player is invulnerable. A full event queue retains that death request.
- Normal death overrides the shared population formula to **one child**. A
  native RNG low bit chooses equally between Big Spider `94.0.0` and Trite
  `29.1.0`. Both have normal health and no live-spit expiry. Big Spider's own two
  ordinary Spider children therefore remain alive after player contact.
- Residual HP ≤−20 source / ≤−64 DeathWard suppresses the death child.
- Live and death births survive local capacity/placement pressure and keep the
  room sealed while pending. Cheats can clear both residents and reservations.
- A sparse pursuit-specialist entry, weight 1/cost 3/cap 1, permits natural Nest
  residents in bands 0–2. These weights are local tuning; source template counts
  establish habitats, not runtime occurrence probabilities.
- Original procedural low-poly rendering adds an uneven hollow head and an
  animated spit opening. Geometry, proportions and palette are DeathWard art,
  not claims of source sprite equivalence.

## Configuration and verification

`assets/mechanics/nest.mechanics` contains the profile, cooldown bonus, live-child
policy, death outcomes, overkill threshold and seeded pool entry. The reusable
`evader_cooldown_bonus` and `evader_child_contact_death` extensions reject invalid
ranges, duplicate declarations and incompatible child controllers. Content
follows the existing immutable snapshot/restart reload policy.

```sh
python3 scripts/isaac-reference/analyze-nest.py --check
python3 scripts/isaac-reference/extract-nest-animations.py --check
ctest --test-dir build -R 'nest_family|hive_evaders|mulligan_family|spider_family' --output-on-failure
```

The [native summary](native-summary.json) records ten passing Linux suites,
656 generated floors, natural residents in all three approved bands and eight
isolated starting-kit encounters. Source/animation verification also passes.
The [visual review](visual-review.json) records eight inspected captures, four
from the final rendering; file/binary hashes and exact commands are retained.
These scoped checks leave the limits below open. **WASM builds and checks are skipped
at the user's explicit request.** Earlier browser results do not certify this
slice.

## Remaining limits

The source evasion helper's grid cache, diagonal bias, initial impulse and exact
search retry distribution remain adapted to the 3D navigation system. Shared
evaders currently integrate movement at the simulation step rate while updating
AI at 30 Hz; full time-partition equivalence is not claimed. Native charm/fear,
shrink, control, champions, mass and full item interactions need further work.
The source signed death-count field at `NPC+bc6` is modeled only in its ordinary
zero-initialized case. The pinned article's Burning Basement Flaming Hopper
replacement bug has not been traced/ported. Appearance/gore/audio details are
adapted. Required child controllers and full mixed-room balance, all-camera
readability and rendering performance still have open acceptance gates.
