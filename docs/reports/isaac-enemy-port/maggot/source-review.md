# Ordinary Maggot: installed Repentance 1.7.9b

Scope: **21.0.0**, an ordinary contact enemy. Small Maggot **853.0.0** is a
separate controller and is not changed by this work. The full roster remains
in scope; regular enemies and required offspring take priority over more bosses.

## Evidence and contract

The [source discovery](source-discovery.json) preserves the installed XML,
source room counts and revision-pinned Maggot wiki article. The article is
revision 266753, by The Binding of Isaac: Rebirth Wiki contributors, CC BY-SA
4.0. It describes a blind, aimlessly crawling contact enemy; only the distinct
Small Maggot pursues the player.

[Native source windows](source/manifest.json) and
[animation metadata](animations/manifest.json) are reproduced and verified by
`python3 scripts/isaac-reference/analyze-maggot.py --check`. The executable is
pinned to SHA-256
`04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.
The animation extractor selects the highest available DLC override, checks the
archive hash and entry checksum, and retains metadata without importing art.
Maggot's override comes from `afterbirthp.a`.

| Rule | Installed evidence | DeathWard behavior |
|---|---|---|
| Identity/health | XML type21, variant0, subtype0; HP15, stageHP0 | 48HP using existing x3.2 conversion; corrects generic40 |
| Movement | Shared root `0x51afa0`; type21 selects force.75 at `0x51b733` | Dedicated source-rate cardinal walker, no pursuit |
| Damping | Friction.85; vertical-axis correction.964705825 | Same source30Hz momentum parameters as the shared helper |
| Path choice | `0x7a51e0`, cardinal grid40, draw0..11 cells,10 attempts | Bounded, radius-aware cardinal rays through actual canyon geometry |
| Arrival/stuck | Arrival distance5; speed below.6 for more than10 updates | Same source thresholds, with distance scale.1 |
| Facing/animation | Previous velocity selects axis; horizontal12, vertical24 frames at30Hz | Separate walk clock, reset when axis changes; blind segmented Original-style silhouette |
| Attack | Type21 excluded from charging branch and type31/243 shooting branch | Contact only; no cooldown-driven shots or Spitty payloads |
| Contact/vulnerability | XML collisionDamage1; no family armor or immunity branch | Contact10 before shared1.25 hostile multiplier; ordinary damageable body |
| Death | No type21 child/death-payload branch in shared controller | One normal kill, no offspring or projectile packet |
| Appearance | ANM2 Appear25, no triggers | Preplaced resident lifecycle retained; source spawn-animation immunity/order not certified |

Source ordinary rooms contain Maggots in Caves/Catacombs/Flooded Caves and
Corpse, plus special, Greed and Ascent templates. Their ordinary pools therefore
use **band1 and band3**. The former band2 ordinary route is removed. Template
presence establishes habitat, not probability. Special-mode and parent-produced
routes require separate reviews.

## Reusable implementation and adaptations

`AxisWanderDefinition` and `AxisWanderRuntime` hold shared movement tuning and
state. `faceAxisWander`, `stepAxisWander` and `moveAxisWander` are used by both
Spitty and the new contact-only `CardinalWalkerDefinition`. The extraction of
the helpers preserves Spitty's operation and RNG-call ordering; Spitty still
owns all of its attack timing and payloads. A Maggot never enters that attack
controller.

`assets/mechanics/maggots.mechanics` provides health, movement, animation
lengths, contact damage and stage pools. Incompatible roles, invalid movement
values and duplicate controllers are rejected when a new immutable mechanics
library loads. Active simulations retain their current library.

The physical radius.6, distance conversion.1, health conversion3.2, contact
conversion10, original3D silhouette and source-habitat-to-band mapping are
DeathWard adaptations. Real walls, props, river banks and cliffs constrain the
path. Native grid-cell scoring and exact global RNG/time ordering are not
claimed equivalent. The shared controller reads actual velocity after physical
collision and crowd separation, preserving knockback and collision constraints.

The source has additional charm/fear/confusion/control/champion paths. Full
support for those paths and their item interactions remains open. The source
Appear25 metadata alone does not establish when native collision becomes
active, so an unverified spawn delay is not added to the preplaced residents.
Full-floor/mixed-build balance, all-camera mixed-room readability and controlled
rendered performance still require acceptance evidence. This report does not
declare a complete port.
