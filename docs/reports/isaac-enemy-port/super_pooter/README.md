# Super Pooter and Pooter item reactions — 2026-10-27

Regular enemies remain the priority. This slice replaces Super Pooter’s generic
controller; further boss/Hornfel work stays deferred. It is a partial port, not
full acceptance of this enemy or the 653-record goal.

## Behavior

| Property | Implemented behavior |
| --- | --- |
| Health | Source 8 HP × DeathWard’s 3.2 conversion = 25.6; formerly 72 |
| Movement | Shared Fly/Pooter buzzing, physical flight over cover, local room boundaries |
| Contact | Harmless; remains a room threat |
| Acquisition | Sight and range 20, staggered every 7 source frames |
| Attack | 14-frame animation, Shoot at frame 6, 35-frame cooldown from acquisition |
| Aim | Current player position at Shoot, including after leaving acquisition range |
| Pair | Forward coefficient .961, side coefficient ±.276; approximately ±16.024° |
| Projectile | Speed 21 before pair transform; base damage 10, 12.5 on impact after the existing hostile multiplier |
| Capacity | Whole pair admitted together; Shoot waits when event/projectile capacity is insufficient |
| Placement | Sparse crossfire specialist across all four bands, cost 3, maximum one per room |

The approximate native pair coefficients are preserved rather than normalized
away. Horizontal speed therefore has a multiplier of approximately .9998485.
Elevated flight shares the physical downward aim between both projectiles.
Original purple low-poly fly geometry, player defaults and expedition structure
are retained.

`buzz_pair ID FORWARD SIDE` and `buzz_suppress ID ITEM_KEY` extend the external
mechanics format. Invalid references/profiles are rejected. Reloaded snapshots
do not alter an expedition already holding an older snapshot.

Skatole suppresses ordinary and Super Pooter attacks while allowing movement and
normal room-clear participation. Suppression pauses the shot delay and its
movement damping; animation recovery continues. A suppressed Shoot is consumed
and is not replayed when the item is removed. This is only an enemy dependency:
**Skatole has no natural reward pool yet**. Its other fly effects, including
Attack Fly conversion, remain unfinished.

## Evidence and validation

The [source review](source-review.json) and [reproducible extraction](../../../../scripts/isaac-reference/analyze-super-pooter.py)
preserve six bounded native disassembly windows, constants, installed XML and
room-library evidence. The animation metadata is retained in [animations/manifest.json](animations/manifest.json):
Attack 14, Shoot 6, 30 FPS. No Isaac sprite artwork is imported. A current wiki
request returned HTTP 403; the existing revision-pinned local research and
installed executable provide this slice’s evidence.

Six [WASM cases](web/results.json) pass: pair, flight over cover, suppression for
both Pooter variants, one death, and an actual seeded resident. No browser or GL
errors were reported. [Native isolated view](native-super.png),
[native seeded room](native-resident.png), [browser cover](web/super-cover.png)
and [browser seeded room](web/natural-super.png) were visually inspected.
Displayed FPS values are not a controlled performance benchmark.

All **65 native suites are covered**: the [full run](native.xml) passed 64,
and the corrected [economy suite rerun](economy-final.xml) passed. Runtime was
unchanged; this is not represented as a second full run. The
[behavior log](behavior-final.txt) records actual Super Pooter witnesses in
bands 0–3: seed1/floor0/room2, seed2/floor2/room2, seed0/floor3/room9 and
seed0/floor5/room2. The [checkpoint](checkpoint.json) freezes source, runtime,
build and evidence hashes. Its mechanics fingerprint is `72c06a2ea58542e1`.
All 3,625 historical artifacts checked remain unchanged.

Early test failures are retained: one expected the
hostile multiplier in stored bullet damage instead of at impact, and another
assumed every expedition has a floor 6. The corrected tests verify an actual
hit and derive valid floors from each seed’s expedition plan. The economy test
now explicitly excludes unfinished Skatole while checking every other
registered item, including namespaced items, remains naturally obtainable.

## Remaining work

Attack Fly and other regular families come next. Tainted Pooter still has its
older partial controller. Full Skatole reactions, native random replacements,
champions, hard-mode speeds, parent-specific and controlled/charmed behavior,
common time-scale/friction integration and exact animation ordering remain
unfinished. Full varied-build balance, occlusion and controlled rendered
Linux/WASM performance gates remain open. No record is certified complete by
this slice.
