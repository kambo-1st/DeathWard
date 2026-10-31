# Regular enemy port: Trite

Trite **29.1.0** now uses a dedicated destination-hop controller instead of the
generic Hopper behavior. It appears in ordinary seeded pursuit encounters in
progression bands 0–2. Regular enemies and required offspring remain the priority.

| Property | Implemented behavior |
| --- | --- |
| Health | 10 source HP × 3.2 = 32 local HP |
| Selection | Two independent movement-bonus draws; nearby target overshoot or distant wandering |
| Timing | 15-frame idle threshold; 26-frame Hop; Jump at 4, Land at 18, at source 30 Hz |
| Movement | Committed destination, source force and friction recurrence, grid snapping |
| Collision | Real elevation over cover/water; room walls still block; legal landing required |
| Attack | Contact only; no invented shots or ordinary death children |
| Placement | Band 0–2 pursuit specialist, weight 2 / cost 2 / cap 2 |

The Land event ends the visual descent, but the source's accumulated Jump event
keeps its collision mode until the Hop animation finishes. This distinction is
covered by the tests. Values are external in
[trites.mechanics](../../../../assets/mechanics/trites.mechanics), including
timing, force, friction, destination rules and the authored 3D height.

## Evidence and limits

- [Source review](source-review.md), [eight instruction windows](source/manifest.json)
  and [installed animation metadata](animations/manifest.json) distinguish
  measured source rules from DeathWard adaptations.
- [Native targeted test](native-targeted.txt) checks timing, numeric motion,
  target commitment, cover/water/walls, stun, room re-entry, contact, death,
  configuration reload, a default-kit kill and seeded placement.
- The full [Linux run](native.xml) initially passed **77/79 suites**. Both
  remaining placement suites pass after the witness-search corrections below:
  [Mulligan](mulligan-corrected.xml), [Hive](hive-final.xml). Together these cover
  **79 distinct passing suites**; this is not described as a fresh 79/79 full run.
- Four [production WASM cases](web-final/results.json) pass: isolated cycle,
  cover, river and natural resident. No captured browser or GL errors occur.
- [Visual review](visual-review.json) records eleven individually inspected
  accepted images, five Linux and six WASM. A startup-camera capture is explicitly
  rejected. Static captures do not certify all-angle combat readability.
- [Natural witness](witness.json): Rourke seed 0, zero-based floor 1, room 2.
  Preview: `./build/deathward --smoke --theme canyon --style original
  --scene enemy-29.1.0 --frames 100000`.
- [Historical integrity](historical-integrity.json) pins 6,481 earlier report
  files unchanged. [Checkpoint](checkpoint.json) freezes this slice's hashes.

## Retained failures and corrections

Adding a weighted specialist changes seeded choices. The old five-seed Mulligan
witness list no longer found Mulligoon; a bounded sequential search still requires
all three variants and finds it at seed 114, floor 0, room 2. Hive's previous
seed list similarly missed the Flooded replacement; the new witness is seed 261,
floor 2, room 4. Its search now covers a bounded range and uses the production
floor configuration to skip dry floors
only after normal Hive has been witnessed. Spawn odds, habitat constraints,
room caps and all required assertions remain unchanged.

An intermediate [Hive correction](hive-corrected.xml) failed because its search
filter read the unconfigured plan's default variant. The final filter calls
`configureFloor` with the same floor seed as the production simulation. This
was a test-only correction; no runtime floor-generation rules changed.

The native ground image at frame 20 was obscured by the settling camera.
It is retained as rejected evidence; later Linux and WASM captures show the
grounded actor. Capture FPS under concurrent build/test load is not a controlled
performance measurement.

## Remaining

Native special-status/champion/control branches, exact RNG/update ordering,
native room-grid parity and the Hopper replacement probability/unlock path are
unfinished. Real 3D elevation, safe landing and local stun/friendly handling are
explicit adaptations. Full mixed-room balance, combat readability and controlled
Linux/WASM performance remain open.

The maintained total is **122 in-progress records and zero fully certified
complete ports**. The full goal stays active. Eggy with its required Swarm
offspring, Tainted Hopper and Leapers remain in the regular-enemy queue.
