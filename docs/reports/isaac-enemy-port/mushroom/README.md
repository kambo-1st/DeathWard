# Regular enemy port: Mushroom

Mushroom **300.0.0** now has its own stationary hide/reveal cycle and four-shot
cross attack. It can appear in ordinary Caves-equivalent rooms. This is a partial
normal-hostile port; regular enemies and their required offspring remain the
priority over more bosses.

| Property | Implemented behavior |
| --- | --- |
| Health | 23 source HP × 3.2 = 73.6 local HP |
| Closed | Takes 25% incoming damage, including burning and explosions |
| Timing | Initial Hide 6 frames; blocked for 30 × a random integer 1–5; Reveal 6 frames |
| Attack | Shoot event at Reveal frame 3; four cardinal or diagonal shots, chosen per burst |
| Shots | Speed 21 local units/second; base damage 10; physical terrain collision |
| Exposed | 30 × a random integer 1–3 frames, then Hide 6 frames; full damage throughout retraction |
| Movement | Anchored to its starting position; contact damage remains active while closed |
| Placement | Progression band 1 specialist, weight 2 / cost 3 / cap 1 |

Animation timing uses the source's 30 Hz clock. Band 1 is a progression category,
not necessarily the second floor. Values live in
[mushrooms.mechanics](../../../../assets/mechanics/mushrooms.mechanics), with
validation and immutable reload. Source replacement/unlock rules are still open;
the direct weighted entry is an explicit DeathWard placement adaptation.

The Original-style body uses a low spotted cap that rises to expose a pale stem.
Its reveal supplies the warning for a fixed-axis burst. The inherited aimed
warning ray was removed because it indicated an attack direction the enemy does
not use. No source artwork is imported.

## Evidence

- [Source review](source-review.md), [record](record.json),
  [four native instruction windows](source/manifest.json), and
  [installed animation metadata](animations/manifest.json) pin the 1.7.9b basis.
- [Targeted test](native-targeted.txt) covers phase timing, damage resistance,
  both cross patterns, exact converted speed, contact, terrain, anchoring,
  death/stun/re-entry, queue pressure, configuration and natural placement.
- The final [Linux regression run](native-final.xml) passes **78/78 suites**.
- The final [production WASM run](web-placement/results.json) passes **three
  cases**: isolated cycle, a hit against closed armor, and a natural resident.
  No captured browser or GL errors occur.
- [Visual review](visual-review.json) records eleven individually inspected
  images: four Linux and seven WASM. These establish static appearance and
  visible attacks, not full combat readability or performance acceptance.
- [Natural witness](witness.json): Rourke seed 1, zero-based floor 2, room 5.
  Isolated preview: `./build/deathward --smoke --theme canyon --style original
  --scene enemy-300.0.0 --frames 100000`.
- [Historical integrity](historical-integrity.json) pins 6,401 preceding report
  files, preserved unchanged. [Checkpoint](checkpoint.json) freezes the final
  source, runtime, build and evidence hashes.

## Retained failures and corrections

The initial [full regression run](native.xml) passed 77/78 suites. The existing
`expedition_pacing` test found a real Classic-preset placement bug: seed 0,
Canyon room 1 placed a solid Grimace over the room center. Removing its movement
body in the [diagnostic](pacing-diagnostic.txt) isolated the cause.

The progression spawner already checked connectivity around solid statues.
The generic Classic/debug placement path now makes the same check: reserve the
actual footprint temporarily, then require entry, center, objective and door
routes to remain accessible. The original pacing test is unchanged and passes
in the final full run. This is a runtime correction, not a relaxed test.

The initial browser run also passed behavior checks but displayed the misleading
aimed ray. Its captures remain in `web-final/` as superseded evidence. The final
`web-placement/` run follows both rendering and placement fixes. The first Linux
burst capture at frame 259 was too early to show the shots; the accepted final
capture uses frame 266. Initial images and their command manifests are retained.

## Remaining

Petrification and its resistance exception, champion/control branches, exact
native RNG and damage-event ordering, projectile vertical physics, and the
Host/Red Host replacement unlock/probability are not fully reproduced. Collision
radius, combat-plane lifetime, local stun handling and seeded pool weights are
documented adaptations. Full balance, all-angle combat readability and controlled
Linux/WASM performance acceptance remain open.

The maintained total is **121 in-progress records and zero fully certified
complete ports**. The full goal stays active. Hopper variants and Leapers are
next in the regular-enemy queue.
