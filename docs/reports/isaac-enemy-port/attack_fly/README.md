# Attack Fly — 2026-10-27

Regular enemies remain the priority. This slice replaces the ordinary Attack
Fly's generic chase and adds its required Skatole and live-Hive reactions.
Further boss work remains deferred. This is a partial port, with no newly
certified complete records.

## Behavior

| Property | Implemented behavior |
| --- | --- |
| Health | Installed 5 HP × 3.2 = 16, previously 32 |
| Pursuit | Cached target every 3 source frames; directional force every 2 |
| Direction | Halve the second planar axis before measuring distance and normalizing |
| Force | Native deadzone 25, gain .08, cap 1.2; world scale .1 |
| Buzz | Shared fourth-frame jitter, third-frame wander/friction and local room-edge forces |
| Contact | Base damage 10, 12.5 after the existing hostile multiplier; ordinary fly survives |
| Skatole | Transform into Fly 13 in place; clamp current HP to max 9.6 without healing |
| Live Hive child | Additional .9 pursuit friction; expires on player contact, including invulnerable contact |
| Hive death child | Ordinary persistent Attack Fly, without the live-summon expiry flag |
| Placement | Pursuit specialist in bands 0–3; weight 2, cost 1, maximum 3 per room |

The native directional asymmetry matters near the player: the effective
deadzone along the second axis is twice as large. The previous constant-speed
chase did not preserve this behavior. Motion retains DeathWard's physical
flight over interior rocks and deep water, with enclosing cliffs, gates and
active-room limits. Swept contact includes vertical separation.

Skatole reads current inventory state. Conversion keeps actor ID, summoner,
generation and momentum, gives no kill reward, and preserves room-clear
participation. Removing the item does not reverse an already completed morph.
Item possession also prevents damaging contact before the next local morph
tick. A damaged fly stays damaged: 1 HP becomes 1 HP, not 9.6.

Live Hive summons latch their contact policy when spawned. It survives parent
removal and conversion to a harmless Fly. A transformed live summon therefore
expires harmlessly on contact. Contact expiry uses DeathWard's existing bounded
execution-damage queue; queue pressure retains a spent actor without allowing
it to resume movement, then resolves one death when capacity returns. Summoned
generations cannot drop money. This uses local kill/threat accounting and does
not imply native reward-system parity.

## Configuration and source

The [external profile](../../../../assets/mechanics/buzz_flies.mechanics) adds:

```text
buzz_chase 18.0.0 3 2 .5 25 .08 1.2 10
buzz_item_morph 18.0.0 isaac:collectible:9 13.0.0
buzz_contact_summon 18.0.0 22.0.0 .9
```

Invalid values, missing references and incompatible morph targets are rejected.
Reloads produce immutable snapshots; an existing expedition keeps its content
snapshot. Skatole remains outside natural item pools until its other required
fly reactions are implemented.

The [source review](source-review.json), [native manifest](source/manifest.json)
and [reproducible extractor](../../../../scripts/isaac-reference/analyze-attack-fly.py)
retain installed 1.7.9b evidence: movement constants, target cadence, morph HP
clamping, live Hive flag assignment and player-collision death. The installed
NPC vtable resolves the collision and Kill methods independently of newer API
layouts. Source animation metadata is preserved in
[animations/manifest.json](animations/manifest.json): Fly 4-frame loop, Die 11,
Appear 13, at 30 FPS. No Isaac artwork is imported.

The radius changes from .38 to .45, matching the existing ordinary Fly and
allowing an in-place morph without enlarging into scenery. Original low-poly
artwork remains. The local fixed clock, source-to-world conversions, speed cap,
room boundaries, physical elevation and bounded event queue are explicit
adaptations. The new Fly controller starts on the next local update after
conversion; native update ordering is not certified.

## Validation

All **65 native CTest suites are covered**: the [full run](native.xml) passed 63,
and both corrected [fixture suites](fixtures-final.xml) passed on rerun. One
fixture expected quarter-health children from the old 32 HP definition; it now
checks 4 HP from the corrected 16 HP. Formation reachability now samples 32 seeds
and verifies complete four-member groups instead of relying on one seed's old
weighted selection. Runtime was unchanged; no second full run is claimed.
The [focused behavior log](behavior-final.txt) covers the new controller and
shared Fly/Pooter regressions, including actual contact damage, HP-preserving
conversion, real Hive spawn paths, capacity pressure and source-axis asymmetry.
Existing [physical flight tests](flight-initial.txt) also pass without changing
their cover, river, gate or elevated-combat expectations.

All **seven browser cases pass** with no browser/GL errors in the
[final WASM report](web/results.json): pursuit, crate crossing, river crossing,
healthy and damaged Skatole transformations, one death, and a real generated
resident. [Linux cover scene](native-cover.png),
[Linux generated room](native-resident.png), [browser crate crossing](web/attack-cover.png)
and [browser generated room](web/natural-attack.png) were inspected.
Displayed FPS values are not a controlled performance benchmark.

Natural witnesses span all four bands: seed0/floor0/room2,
seed20/floor2/room2, seed7/floor3/room3 and seed1/floor6/room9. The first is also
verified in WASM. The [checkpoint](checkpoint.json) freezes runtime, source,
build and evidence hashes at mechanics fingerprint `bef0b7c155852203`.
All 5,180 previously recorded artifacts checked remain unchanged.

## Remaining work

Continue the unfinished regular fly variants, including Tainted Pooter, and
then the remaining regular roster. Hive and Moter parent behavior is not
completed by this child-controller change. Duke/Husk tethered children,
large-child health/scale and edge exceptions, Gurdy's current-HP reduction,
and Eternal Fly-derived special cases remain pending. Their retained source
preflight is research only.

Full Skatole effects, controlled/charmed/status behavior, knockback, exact
native integration/time scaling and animation ordering remain unverified.
Broader build balance, all-angle occlusion and controlled rendered Linux/WASM
performance gates remain open. All 653 records and all six acceptance gates
remain part of the active goal.
