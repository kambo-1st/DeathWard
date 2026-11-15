# Four additional complete source arrangements

The user requested committing the accepted source108 room, adding source109, then focusing on broader room coverage and coins on 2026-11-15. Source108 is committed as `b8c3c4f7`. This selected continuation adds four compatible complete arrangements to ordinary opening-floor canyon generation. Developer checks pass. On 2026-11-15 the user accepted the enemies in the launched source109 encounter ("enemies looks good!"). [Acceptance record](human-acceptance.json). The other added layouts, unconfirmed room interactions and coins still need human review.

| Source record | Ordinary Gapers | Plain rocks | Source difficulty | Direct review seed with the accepted preset | Displayed room |
| --- | ---: | ---: | ---: | ---: | ---: |
| 1.109.0 | 5 | 8 | 5 | 2942 | 7 |
| 1.547.0 | 2 | 39 | 1 | 860 | 5 |
| 1.548.0 | 1 | 52 | 1 | 6 | 7 |
| 1.550.0 | 2 | 33 | 1 | 2704 | 5 |

The extractor verifies complete singleton spawn stacks against the pinned Repentance1.7.9b Basement STB. Per-room `source-room.json` files preserve cells, original weights, metadata and provenance. The existing selector/descriptor sequence chooses the record; there is no forced room insertion or replacement enemy. The bounded registry now contains six Gaper/plain-rock arrangements (4,108,109,547,548,550). Source91's rock/heart arrangement and D08's separate47 formation remain.

Canyon size/shape and connections remain explicit exceptions. Existing objective indices2/3, key sites, story/special rooms and D08's injected room retain their protections; unsupported placements are not rerolled into a supported record. Gaper AI, HP, accepted walking/shooting, eight-direction controls and universal dodge are unchanged. The existing source-cell navigation fallback handles the new content without a new speed or collider adaptation.

## Verification and configuration

Twelve naturally generated cases cover every added record at minimum (.75/range5–5), accepted (1.1/range7–9) and maximum (1.5/range10–10) sizes. Exact rosters/rocks, safe source positions, full-radius paths to each actor, passage access and cross-room travel pass. At minimum size, actual Gaper movement reaches the entrance; the controlled routing check retires each arrival so crowd blocking does not masquerade as a path failure. That check does not certify simultaneous native crowd behavior. A real-projectile source109 fixture holds actors still for aiming and verifies obstruction, damage/death, clear seals, ordinary dynamite, revisit and Apply. [Gameplay evidence](gameplay.log).

Fourteen focused suites pass across this delivery and [D09b](../d09b-coins/README.md): the new room and coin suites, prior complete rooms, heart layouts/rewards/reference, native room selection, presets, core, destruction and rails. Actual Game/Renderer/mouse SOURCE/OFF/Apply, export/remember/reload and retry pass for source109. [UI evidence](input.log), [regressions](regressions.log).

Schema19 retains the staged SOURCE LAYOUTS boundary and migrates schemas1–18. The user's original165% preset remains unchanged. [Current export](preset-v19.json). No new room control is required: SOURCE LAYOUTS includes these supported records, and Apply still regenerates during combat while retaining player/build/expedition identity. The independent coin policy is documented in D09b.

## Short review

```sh
build/deathward --expedition --seed 2942 --review-source-room 109 --mute --save /home/kambo/.local/share/deathward/reviews/native-room-coverage/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

This opens directly in room7 with normal health/damage and five Gapers around eight rocks. Death retry returns here. The first-clear result for this seed is an unsupported bomb outcome, so this encounter is not the coin witness. For the other layouts, substitute their source variant and seed from the table.

1. Move/shoot around the rocks and finish the five enemies.
2. Optionally open a rock with dynamite, then leave/revisit after clearing.

The [room capture](room.png) is actual gameplay; its initial-frame FPS overlay is not a performance measurement.

## Unfinished

Source109 enemy feedback is accepted. Human review of the other added layouts and unconfirmed room interactions, most of the433-template pool's complete contents, mixed enemy/obstacle/pickup arrangements, native factory/substitution/unlock/selection-order rules and full physical/actor/drop equivalence remain unfinished. Complete content coverage is six Gaper/rock records plus the separately scoped91 and47 arrangements, not a complete first-floor pool. Size/shape/connections remain excluded. Next is the ordinary coin review, with the other added layouts still available for review; subsequent room work should cover a different supported content family. Unrelated bulk parity remains paused.
