# D09d — ordinary bomb/dynamite pickups

Selected by the user on 2026-11-15 ("ok, lets go!"). Previous cleanup is committed as `bd5e5101`. **D09d is enabled in the main game and developer-verified. The user accepted the scoped playtest on 2026-11-15; the accepted delivery is included in this checkpoint.** Bulk parity remains paused.

## Playable result

Ordinary opening-floor clear rewards can emit the preserved native bomb outcome. Single subtype1 adds1 dynamite; double subtype2 adds2, clamped at99. Full inventory leaves the actor available until spending. Collection pays once, produces the pickup sound, then finishes its animation. Starting supply remains3. Existing fuse/blast/self-damage are retained and remain separate D10 comparison work. After accepting D09d, the user explicitly selected removal of ordinary dynamite throwing. B and the HUD button now place at the feet; the Place/Throw switch, C shortcut and aiming preview are removed. Contact kicking remains. The separate Bomb Grimace supplied-bomb attack is retained; its B/HUD action places the carried bomb. Historical Simulation throw/trajectory helpers remain available for isolated physics fixtures, with no ordinary Game input caller.

The old chest bomb producer now uses this same ordinary actor. Chest loot selection itself is unchanged. Single/double pickups display one/two dynamite sticks with an inactive fuse, through the normal scene primitive color/shadow passes.

The user subsequently selected the same pickup model for placed dynamite, preserving particles. Ordinary deployed charges now share the single-stick geometry and scene color/shadow passes with pickups. Existing fuse glow/four spark strokes follow the new fuse tip with the same timing/color/size/drift. Explosion particle code and manifest, blast timing/damage, audio and collision are unchanged. Boss charges and supplied bombs retain their existing models. Native game/input builds and the actual canyon/mine dynamite and source32 pickup suites pass. [Model/effect verification](shared-dynamite-model/validation.json), [lit stick](shared-dynamite-model/lit-stick.png), [explosion](shared-dynamite-model/explosion.png). The user accepted the shared model and effects on 2026-11-15 ("nice it works"); browser runtime verification remains open.

Complete source **1.32.0** supplies34 plain rocks and3 bomb slots at source cells(5,3)/(6,3)/(7,3), ordinals17/18/19 of37. The existing source selector chooses this arrangement naturally; original descriptor/slot seeds determine subtypes. Original cells remain enclosed until demolition opens access. There are no source enemies or unrelated pickups. Legacy objectives/mandatory key sites retain their composition without rerolling; canyon size/shape/connections are retained. [Source record](source-room.json).

**TUNING → REWARDS → AFTER CLEAR → DYNAMITE** changes future first-clear admission. Existing actors, resolved/deferred rewards and chest contents stay fixed. **ROOM LAYOUTS → SOURCE/OFF** is independent and staged until **Apply map changes**. Schema24 exports/loads/remembers this policy and migrates schemas1–23. Apply regenerates the current floor while retaining player/build/inventory/expedition identity and moves the player out of a restored enclosure. Retry and later floors retain the reward policy. Configuration persistence is separate from unfinished gameplay save/restore.

## Source evidence and limits

Target is installed Repentance1.7.9b. The preserved resolver at6b5caf..6b5d52 uses four successive draws: double chance, gated golden chance, supertroll/golden-troll chance, then troll/golden-troll chance. All1036 native bomb cases match alongside2196 award choices/RNG endpoints and previous heart/coin/key matrices. Eight preserved ordinary no-golden admitted collection cases match actual inventory quantity/clamp behavior. Native AddBombs clamps0..99. [Evidence and hashes](source-evidence.json).

Gameplay retains the represented golden gate off. Only ordinary1/double2 become inventory actors. Golden/troll/supertroll outcomes remain recorded without rerolling or substituting ordinary bombs. Their actors are not implemented by this delivery.

Highest installed animation overrides are **Appear35 / Drop25 / Collect16(single),13(double)**. [Pinned metadata](animations/manifest.json); no Isaac artwork is imported. Collection gates and cleanup use an active-room30Hz adapter. Native collision eligibility prechecks, pushing, factory/scheduler/profile/unlocks/modifiers and complete seed/physical equivalence remain unaccepted. DW planar proximity/line-of-sight, source-cell-to-canyon placement, current dynamite mechanics and starting3 remain explicit adaptations.

## Verification

Eleven focused suites pass across [initial selected checks](initial-tests.log), [six regression suites](regression-tests.log) and [final selected checks](selected-tests.log): native reward reference, bomb gameplay/layout, presets, chest gameplay/layout, key gameplay/layout, coin gameplay/layout and retained player dynamite. The initial build had a generated symbol naming mismatch; it was corrected in the extractor. The first preset negative fixture still named the prior layout policy; it was updated and the full preset suite passed.

Natural source32 witnesses cover the smallest size (seed1027,75%,5–5), accepted size (seed129,110%,7–9) and largest size (seed1027,150%,10–10). All retain exact source slots/rocks, sealed access, free door routes, real two-charge breaches, physically clear click paths, collection/revisit persistence, staged OFF/SOURCE Apply and rescue from reclosed pockets. Deferred capacity retains the same seed/subtype/location. Ordinary reward timing passes at30/60/120Hz; full99 refusal/recovery, inactive/pause, future-clear policy and source-scope exclusions pass.

[Actual Game/Renderer input](input.log) passes with normal health: mouse access, keyboard charges and safe retreat, source pickup rendering/shadows, live mouse/keyboard toggle, staged Apply, export/load/remember, once-only collection, revisit, death retry and fresh-session settings. The test spent2 charges, collected3 singles, ended with4 dynamite and retained6 half-heart health. A stale intermediate input executable first failed launch; after rebuilding, a distant collection click hit the Pause HUD at165% zoom. The final check uses visible mouse waypoints back to the breach before clicking inside it; controls/gameplay were not changed to accommodate that test. [Room](room.png), [collected](collected.png), [rewards panel](rewards-panel.png).

Four separate main-game CLI launches pass: original schema5 preset, schema23 with keys off, schema24 dynamite rewards off, and schema24 layouts off. All retain165% zoom and normal6-half-heart health. [CLI results](cli-validation.json). The original export remains byte-identical: SHA256 `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`.

## Interactive handoff

Open directly in **displayed room2, seed129**, beside the source32 rock enclosure, with the user's165% preset,3 dynamite,6 half-heart health and no god mode. Death retry returns here. [Launch record](interactive-handoff.json).

```sh
build/deathward --expedition --seed 129 --review-source-room 32 --mute --save /home/kambo/.local/share/deathward/reviews/d09d-bombs/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

Human check: press **B** at the starting rock edge, then retreat before the blast. Move into the breach and repeat. Walk back toward the opening, collect the three sticks and revisit. With exactly two charges spent, DYNAMITE should finish at4. Check the live DYNAMITE toggle/export/load if desired.

[Scoped human acceptance](human-acceptance.json) records the user’s “ok, looks good” and requested placement-only followup. The followup is implemented and developer-verified: native game/input builds and seven checks pass (dynamite physics; actual Game/Renderer placement, keyboard, arrows, HUD, supplied bombs and D09d pickups). The HUD check confirms the old mode-button area accepts world input. Canyon/mine placement, kicking, pause, refill and arrow-fire separation pass. Source32 still spends2 charges, collects3 sticks and finishes with4 dynamite at normal health. [Results and limits](placement-only/validation.json), [placement-only HUD](placement-only/hud.png). The first test build had a duplicate local variable; a subsequent HUD assertion needed one simulation tick after button release. Both fixture issues were corrected without changing gameplay timing. The user accepted the simplified controls with the shared-model followup on 2026-11-15; browser runtime verification remains open.

Unfinished: browser runtime verification, special bombs and wider layouts, complete native factory/physics/profile/modifier/seed/scheduler equivalence and gameplay save continuity. The user requested committing this accepted checkpoint and selected D10a fuse/blast/self-damage next. D10a implementation is separate from this pickup/control/model checkpoint; no other parity family is selected.
