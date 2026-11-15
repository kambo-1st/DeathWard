# D10b — ordinary rock demolition

Selected on 2026-11-15 after accepted D10a commit `de8ea28c`. The user also selected keyed-door spending afterward. D10b is enabled, developer-verified and scoped human-accepted (2026-11-15: “it works move to a next thing”). See [acceptance](human-acceptance.json). The already selected D10c keyed-door spending is now enabled/developer-verified and scoped human-accepted. Bulk parity remains paused.

## Delivered interaction

Ordinary placed inventory dynamite lets its blast reach other nearby ordinary rocks behind the first rock. Each affected plain rock breaks once, clears its movement/projectile collision, shows stone debris, and remains destroyed on room revisit. Ordinary bullets still cannot break it. Structural walls, terrain, closed doors and other prop types retain their shielding. Enemy/player blast recipients keep their existing rules; this is a destructible-only delivery. Source-layout rocks keep their no-custom-coin policy; native ordinary rock drops remain unfinished.

TUNING → COMBAT → DYNAMITE adds **ROCK SHIELDING**. Default OFF uses the selected ordinary-rock rule; ON is the explicit historical shielding test override. It snapshots on charge placement, so changing it cannot alter already-lit charges. Schema26 exports/loads/remembers it and migrates schemas1–25 with OFF while preserving their other fields. Existing fuse, damage, size, self-damage, Braid, placement/kicking, particles, walking, shooting, dodge and map/view settings retain their contracts. No native room dimensions or connection geometry are imposed.

## Source evidence and limits

`capture-ordinary-rock-blast.py` executes the pinned installed 1.7.9b complete CheckLine mode2, with supplied normal room grid objects and original instructions.32 cases cover one/two obstruction layers, both directions and diagonals. Ordinary rock type2/collision3 passes; bomb-rock type3 and wall type15/collision4 block. The unchanged explosion caller is preserved as static evidence that it uses mode2 before grid destruction. No helpers replace calculations. See [source manifest](source/manifest.json) and [native line matrix](source/native-lines.csv).

DeathWard retains its physical blast sphere/nearest-box-distance, canyon terrain, other props and the D10a spatial calibration. Native angular ray sampling, native object construction/destruction/drop callbacks, pits/bridges, special rocks and full collision/physics are not implemented or accepted by this scoped rule. The synthetic native line fixture does not prove those broader behaviors.

## Developer verification

Three focused suites passed: `inventory_bomb_tuning`, `balance_preset_contract`, and `expedition_destruction`. The final strengthened debris assertion also passed. They cover32 native line comparisons, actual bullets and charges, both vector orders, near/far rocks, wall/other-prop protection, exact one-debris-burst per destroyed rock, live snapshot isolation, collision removal, room revisit, legacy destruction and strict schema migration/rejection. [Core results](core-tests.log), [debris assertion](debris-test.log).

Two actual Game/Renderer modes passed: `--dynamite-balance-only` exercises the new mouse toggle and existing keyboard controls, birth snapshots, Reset, rejected loads, staged map Apply, export/load/remember, floor change, retry and fresh-session persistence. `--bombs-only` walks the naturally generated enclosure, places dynamite and retreats with normal six half-hearts, collects once and revisits/retries. The accepted map/view now needs **one charge** to open the source32 breach, versus two under historical shielding; starting3 minus1 plus3 collected ends at5. [Tuning input](tuning-input.log), [room input](room-input.log), [opened enclosure](opened-collected.png). The [tuning panel](tuning.png) was visually inspected.

Separate schema25 and schema26 CLI launches passed with zoom165, normal health and the expected shielding values. [CLI evidence](cli-validation.json). The [custom test preset](custom-test-preset.json) deliberately enables historical shielding and zero self-damage; it is not the reference review preset. The user's original schema5 export remains byte-identical (SHA256 `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`).

## Review

Use the generated source32 enclosure, seed129, displayed room2. With normal six half-hearts and three charges, approach the rock enclosure, press B, retreat, then walk through the breach to collect the enclosed dynamite. Leave/revisit and confirm the breach stays open. Compare ROCK SHIELDING ON/OFF using Apply map changes to reset the floor, then check export/load. The accepted user preset retains165% zoom.

```sh
./build/deathward --expedition --seed 129 --review-source-room 32 --mute --save /home/kambo/.local/share/deathward/reviews/d10b-rock-demolition/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

Remaining: the already selected D10c keyed-door spending. Full native blast radial sampling/grid/drop/physics/item/profile equivalence, browser runtime and gameplay-save continuity remain open.
