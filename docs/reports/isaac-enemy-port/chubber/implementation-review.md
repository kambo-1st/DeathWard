# Chubber and its returning body: implementation in progress

This batch replaces the old generic `39.2.0` returning-head attack with the
reviewed Chubber body and its required `39.22.0` component. It also adds sparse
ordinary floor placements for the four reviewed Vis-family bodies. Neither
record has passed all six acceptance gates; the full 653-record goal remains
active, with regular enemies first.

## Source and collision findings

The earlier [Vis source review](../vis/source-review.md) and animation manifest
remain frozen. The new [supplemental manifest](source/manifest.json) pins seven
native instruction windows, the installed executable SHA-256, the NPC/tear
virtual-table entries, and the installed tear flag definitions.
`python3 scripts/isaac-reference/analyze-chubber.py --check` checks the export
against the original executable. No Isaac artwork enters the game.

The returning controller at `519980` explicitly clears both HP and maximum HP.
The common damage handler rejects nonpositive maximum HP. The XML's nominal
1000 HP is therefore not an appropriate runtime health pool. Chubber itself has
25 source HP and zero stage HP: the existing 3.2 conversion gives 80 local HP,
correcting its previous generic 112 HP.

The tear collision handler at `64ffb1` checks the piercing flag, then calls
`6846e0`. That helper returns false for type39; the piercing branch exits before
the normal tear-death path at `650076`. The installed enum identifies bit1 as
`TEAR_PIERCING` and bit0 as `TEAR_SPECTRAL`. Consequently, ordinary and spectral
shots are blocked, while piercing shots pass through. The wiki's broad statement
about destroying tears must not be interpreted as overriding this exception.
The separate exceptional death virtual call for tear variant9 appears at
`64de91`; local execution events remove the component without changing its parent.
This is infrastructure for that exception, not a claim that the Chaos Card item
has itself been ported.

## Runtime and external profiles

`assets/mechanics/chubber.mechanics` supplies the body, reciprocal component
ownership, source movement scale, launch speed, horizontal multiplier, turnaround,
return offset, lifetime and contact damage. The loader rejects incomplete or
mixed beam/body payloads, mismatched owners, independent component placement,
and positive-health returning bodies. Zero health remains forbidden for ordinary
monsters. Config reload creates a new immutable content snapshot.

The parent shares the reviewed Vis cardinal wander/acquisition controller:
alignment and range checks staggered every three source frames, heading locked
before windup, Shoot at frame18, and a 69-frame attack animation. Its attack is
admitted as a complete owned spawn, retained at the Shoot event under capacity
pressure. It launches inside the parent without ordinary offspring clearance.

The component stores the original velocity. Outbound velocity follows
`initial * (1 - counter/21)`. Beyond turnaround, it uses the current parent
position, subtracts 20 source units from that vector's length without clamping,
and applies `(-q)/max(43-counter,1)`. Horizontal launch is16×1.4; vertical is16.
With the .1 distance conversion these are67.2 and48 local units/second.
The local integration uses a30Hz controller and continuous motion within each
source frame. It never invokes terrain navigation, so rocks and rivers do not
stop the attack. The source's exact common-physics/controller phase ordering
still needs final comparison; the expression and counter timing alone do not
prove sample-for-sample native trajectory parity.

Collision uses relative swept motion, independently of the final-position
spatial grid. This catches crossing shots that would miss both final body
positions. Active returning bodies are indexed once per projectile update,
avoiding a full enemy scan for each shot. Piercing shots pass without consuming DeathWard's finite piercing
budget; spectral and spent returning shots are still intercepted. Hostile shots
are unaffected. A carried explosive cap retains its physical impact event.
Swept player contact maps source damage2 to local20, then the established combat
multiplier produces25. The player's100 HP and24 damage defaults are unchanged.

The component has no ordinary kill reward, no room-completion weight, no homing
target role and no health bar. Parent death cancels live/pending attacks;
timeout, missing parent, room clearance and room exit clean them up. Room exit
removes transient attacks while preserving the parent's resident state. This
immediate cleanup is a documented DeathWard lifecycle adaptation; exact native
parent-reference invalidation timing remains open. Executing the component never
transforms its parent into a Vis.

## Seeded placement

Source room-library evidence in `isaac-enemy-port-plan.json` supports Chubber in
Catacombs/Mines through Depths/Womb, ordinary Vis/Double Vis in Depths-family and
later libraries, and Scarred Double Vis in Womb-family and later libraries.
Local weights and threat costs are deliberate adaptations, not ratios inferred
from source template counts.

| Body | Bands | Pattern | Weight / cost / maximum |
|---|---|---|---|
| Vis39.0 | 2–3 | Supply guard | 2 / 4 / 1 |
| Double Vis39.1 | 2–3 | Crossfire | 1 / 4 / 1 |
| Chubber39.2 | 1–3 | Charge lane | 1 / 4 / 1 |
| Scarred Double Vis39.3 | 3 | Crossfire | 1 / 5 / 1 |

No family member enters band0. The returning component is parent-only.
`tests/chubber_tests.cpp` discovers actual residents through the production
generator, checks their floor eligibility and footprints, enters those rooms,
and verifies activation of their dedicated runtime. This does not inject enemies.
Initial witnesses, with zero-based floor and room indices:

| Variant | Seed | Floor | Room | Band |
|---|---:|---:|---:|---:|
| Vis | 0 | 4 | 1 | 2 |
| Chubber | 0 | 5 | 7 | 3 |
| Scarred Double Vis | 1 | 6 | 2 | 3 |
| Double Vis | 4 | 5 | 3 | 2 |

## Validation scope and open work

The focused native suite covers source timing, horizontal/vertical launches,
turnaround, moving-parent returns, passage through cover, swept projectile and
player collisions, ordinary immunity, execution, ownership, capacity, room exit,
timeout, malformed external profiles,30/120Hz partitioning, a real starting-kit
fight, and all four generated family routes. The initial broad monster smoke
failed because its fixture tried to spawn the newly owned component without a
parent; the fixture now constructs the valid owner, and the corrected four-suite
run passes. Both receipts are retained.

A later source check exposed an expiry fencepost error in the initial runtime
and its initial timing test. At `519b75`, the native controller compares the
old counter against42, then increments it. Counter42 must survive that update;
the next update removes the component. The corrected native test explicitly
asserts that boundary, and both the dedicated contracts and catalog smoke pass.
Earlier passing receipts are retained as history, not evidence for the corrected
boundary. Further update-order discovery is saved under `discovery/`; the main
AI call precedes common physics, but the immediate newborn update and status
branches still require comparison before claiming exact native phase parity.

Original-style procedural geometry distinguishes the segmented attack from its
parent, whose mouth reveals the emerging body during windup. Initial native
captures at frames68/98 place much of the attack behind the HUD/offscreen;
these are not accepted as clear attack views. The launch capture at frame48 is
readable. Frame120 shows its return heading, with partial HUD overlap. The
screenshots are partial visual evidence, not all-angle acceptance or a performance
benchmark. Eleven scoped native suites pass in this batch. Five isolated
production WASM scenarios and four actual seeded populations also pass, including
real attacks by all four family members. The generated Chubber view clearly
shows its body crossing water among the other residents. Double/Scarred Vis
remain partly concealed by foreground cliffs in the inspected generated views.
The corresponding outlines and some beams are visible, but these views do not
establish full attack-lane readability. Browser and native summaries identify
the exact runs and later rechecks after indexing the moving interceptors and
correcting the expiry boundary.

Remaining work includes exact shared-physics phase order, native walk cell costs
and RNG/view eligibility, charm/status/control interactions, Eraser's run-wide
component suppression and other missing item dependencies, more generated-room
combat/occlusion coverage, mixed-floor balance and controlled Linux/WASM performance.
The existing harmless beam fade adaptation and other Vis-specific questions
remain open in the previous report. All six completion gates remain open.
