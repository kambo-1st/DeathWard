# Trite 29.1.0 — installed Repentance 1.7.9b

The earlier [research note](research-progress.md) records the initial questions.
This review resolves the normal movement integration and drives a dedicated
destination-hop controller. The source remains the installed executable, exact
XML/room data and animation metadata; no source artwork is imported.

[Eight preserved native windows](source/manifest.json) pin executable SHA-256
`04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.
`analyze-trite.py --check` verifies their bytes/disassembly, shared dispatch,
numeric constants and event strings. The evidence extractor was extended during
this unfrozen research slice, retaining its existing controller/helper files.

## Identity, selection and timing

Type 29 variant 1 has source HP 10, stage HP 0 and contact damage 1. Its ordinary
habitats include Cellar/Burning Basement, Caves variants and Necropolis; the
[record](record.json) separates stored standard/Greed room-template presence.
Archived [wiki revision 266778](wiki-source.json) describes less frequent,
longer-range jumps. Its replacement probability is not inferred from room counts.

Types 29, 34 and 54 share controller `514450`, but branch conditions distinguish
their variants. Ordinary Trite has an idle threshold of 15 source frames. Each
normal update samples `b=50*U+70*V`, with two independent draws. This is not a
uniform 0–120 roll. Acquisition range is `130+1.3*b`. The range comparison is
strict, and normal selection does not require line of sight.

Inside range, the destination candidate is `target+(target-self)*b/200`. Outside
range, it is a random direction at distance `95+b`. The ordinary target helper
returns the target's position without velocity prediction. The candidate is
clamped with margin 5, checked against grid collision, then snapped to a room
grid cell. Native grid conversion uses spacing 40 and source origins 40/120.

[Installed Trite ANM2](animations/manifest.json) defines a non-looping Hop of
26 frames, Jump event at 4 and Land event at 18, at 30 Hz. Hop selection commits
the destination. Player relocation does not retarget that destination during the
hop. Land triggers sound; it does not itself discard the destination.

## Motion and collision events

The base entity initialization copies base friction into native `+2c4` and sets
entity-time factor `+2f4` to 1. The base movement path `686406` multiplies velocity
by current friction, integrates it using entity time, then resets friction to its
base value. The normal Trite controller multiplies friction by `.7` at its end.
With base friction/time both 1, the ordinary recurrence is:

`v_next = .7 * (v + impulse)`

For distance at least 30 native units, `impulse=.05*delta`, with `delta` first
multiplied by `.1` outside the Jump event interval. Closer than 30, the direction
is normalized; normalization removes that grounded `.1` length factor. At an
exact zero delta the local implementation supplies zero force.

The source event-query helpers use distinct current-event (`+18`) and accumulated
event (`+1c`) masks. Hop motion tests the accumulated Jump event. Thus its
wall-only grid / player-object entity collision interval begins at Jump4 and
continues until the animation finishes, including the frames after Land18.
The local visual descent ends at Land18, while the collision interval ends at
Hop26. It is not a fixed-speed or fixed-duration flight directly to the target.

After animation completion, destination release requires distance below 10, or
a 1-in-10 check when speed is below `.75` or the state counter exceeds 30. The
release update still applies its last steering impulse. The source controller
then resumes its idle counter. No ordinary projectile or death-child branch
applies to Trite.

## DeathWard conversion and geometry policy

- Source distance × `.1`, velocity × `30*.1`; HP × 3.2 gives **32 HP**.
  Hostile contact uses the established base damage 10. Radius `.5` is authored.
  The controller uses the source 30 Hz clock inside the 60 Hz simulation, without
  the generic enemy movement/cooldown multipliers changing these source values.
- [trites.mechanics](../../../../assets/mechanics/trites.mechanics) controls
  frame events, target law, grid spacing, force, friction, stuck-release rules,
  height and contact. Parsing rejects invalid timing, dynamics and conflicting
  controller bindings. Reload creates an independent immutable snapshot.
- Source grid spacing becomes a four-unit destination grid anchored within each
  DeathWard room. Source absolute room coordinates are not copied into world
  coordinates. Radius-aware edge clamping and legal floor checks adapt to rooms
  of different generated sizes and shapes.
- Horizontal travel retains the inertia/destination law. A bounded projection
  of that same steering checks for a legal landing, at selection and again at
  takeoff. It does not substitute a destination-to-destination arc. Invalid
  routes are rejected; later seeded selection can try another destination.
- Jumping uses existing wall/room-boundary flight sweeps over cover and rivers.
  Physical body elevation follows cover support plus an authored 1.6-unit arc
  between Jump and Land. The animation's remaining frames retain its collision
  mode. Grounded movement and landing keep ordinary solid-floor checks.
- Real height drives aiming, projectiles and contact in the 3D game. This differs
  from Isaac's sprite-height presentation on a 2D combat plane. A closing obstacle
  that invalidates a landing restores the last legal ground position; that
  correction does not generate a swept contact attack across its return path.
- Local stun cancels a grounded hop; an airborne actor completes its committed
  motion to safe ground before waiting. Death ends its one room threat, and
  room suspension preserves destination, momentum, animation and position.
  Friendly targeting uses the existing local allied-contact adapter; native
  player-control/charm/status branches are not certified by that adapter.
- Ordinary pool placement is an authored band 0–2 pursuit specialist, weight 2,
  cost 2, cap 2. The native Hopper replacement probability and unlock/context
  conditions are separate unfinished work. Existing spawned Trite children also
  receive the dedicated controller; their parent's spawning rules are unchanged.
- Original-style procedural spider body and real elevation are retained. A small
  preparation ring replaces the inherited ranged-attack warning line.

## Remaining acceptance

Native special-status/champion/control branches, exact native RNG stream order,
half-frame integration, collision/grid behavior under all unusual geometry, and
the Hopper replacement path remain open. 3D navigation and safe-landing behavior
are explicit adaptations. Full mixed-room balance, all-angle combat readability
and controlled Linux/WASM performance require separate acceptance. This slice
must remain in progress even when the normal-controller tests pass.
