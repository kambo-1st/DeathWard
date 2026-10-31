# Regular enemy port: Tainted Hopper

Tainted Hopper **29.3.0** now has a dedicated four-hop attack sequence instead of
the legacy generic Hop/Ring behavior. Regular enemies and required offspring
remain ahead of further boss implementations.

| Property | Implemented behavior |
| --- | --- |
| Health | Source80 × local3.2 =256; no generic stage-health increase |
| Timing | Source30Hz; idle26, Hop/Hop2 length23, Jump4, Land17 |
| Target | Strict130-native-unit acquisition; zero overshoot bonus; wander95 |
| Sequence | First three landings chain at Jump4 when ground is safe; fourth recovers |
| Rings |4,6,8,12 world-aligned projectiles,30 per cycle |
| Speeds | Native8,10,8,10 → world24,30,24,30 |
| Flight | Native damped descent; physical ground/cover/body collision |
| Contact | Source full-heart contact → local20 before existing enemy multiplier |
| Capacity | Whole rings retained at their landing origins; queue bounded to one cycle |
| Death | One kill/loot; pending rings canceled, emitted shots survive until impact/expiry |
| Placement | Rare band3 pursuit specialist,weight1/cost6/cap1 |
| Visual | Original procedural headless body, visible arms and alternating airborne twist |

**Adaptive armor is still missing.** Source `shieldStrength30` is not equivalent
to extra HP or a flat reduction. This remains an in-progress port, with no claim
of full behavior, balance or performance acceptance.

## Evidence

- A fresh [Linux regression run](native-final.xml) passes **81/81 suites**
  after the final runtime changes. [Checkpoint](checkpoint.json) pins this build,
  fingerprint `d6db0034dfe180f3`, source and validation artifacts. The maintained
  checklist has166 reviewed records,124 in progress and zero fully complete ports.
- [Preserved source preflight](source-review.md), [instruction manifest](source/manifest.json)
  and [animation metadata](animations/manifest.json).
- [Flight and armor review](flight-armor-review.md), with nine additional
  [bounded instruction windows](flight-armor-source/manifest.json). The armor
  findings are research for shared regular-enemy work, not an implemented mechanic.
- [Native behavioral checks](native-flight.txt): exact timings,4/6/8/12 counts,
  speeds, alignment,30Hz flight recurrence, queue pressure, stun, room suspension,
  lethal interruption, contact, source health and immutable configuration snapshots.
- [Production WASM](web-final/results.json): five passing cases cover the isolated
  sequence, physical crate clearance, river crossing, ordinary death and a natural
  late-floor resident. No captured JavaScript or GL errors.
- [Visual review](visual-review.json): nine accepted, individually inspected
  images, three Linux and six WASM. Additional first-ring captures are retained
  with their visibility limitations; none is silently counted as a readable ring.
- [Natural witness](witness.json): Rourke seed22, zero-based floor7, room1.
- [Historical integrity](historical-integrity.json):6,662 previous report files
  preserved byte for byte, including the preceding Eggy checkpoint. The earlier
  Tainted Hopper source-only preflight also remains unchanged.

Preview with `./build/deathward --smoke --theme canyon --style original
--scene enemy-29.3.0 --frames 100000`.

## Adaptations and open work

Source Ascent-only placement is deliberately adapted to a sparse late-expedition
pool. World scale, player damage conversion, actual3D terrain, safe-landing
deferrals, projectile radius/safety lifetime, queue retention and completion
gating are explicit local policies. Native special statuses, champion/control
branches, fear/shrink/charm/familiar interactions and exact RNG ordering remain
open. Friendly shots currently use the existing local player-attack adapter.

The four-shot capture can be difficult to read when its origin overlaps the
stationary player; the natural encounter capture shows the separated cross.
The twelve-shot ring and elevated body are clear in inspected views, but
player/enemy overlap near a canyon wall remains a readability limitation.
Full mixed-room and varied-build balance, every-camera readability and controlled
Linux/WASM performance remain unaccepted. See [implementation scope](implementation-scope.json).

The first flight/armor extraction attempt used a Python environment without
Capstone and failed before extracting files. The retained error log and successful
system-Python extraction/check logs distinguish that tool setup failure from the
validated source windows. No failure artifacts were overwritten.

Next regular work: shared adaptive armor, Leaper variants and improved
normal/Flaming Hopper fidelity. Mine roster, hubs, tutorial,4–8-floor expeditions,
Original style and protagonist defaults are preserved.
