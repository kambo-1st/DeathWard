# Ordinary fireplaces and poop

Selected by the user on 2026-11-17 before the proposed Full Fly/Round Worm work. This delivery extends the existing ordinary fireplace and dung actors into complete opening-floor source arrangements and adds their ordinary destruction rewards. It preserves canyon room geometry, corridors, player movement, eight-direction firing, universal dodge and accepted combat values.

## Source evidence

Target: installed Repentance 1.7.9b, executable SHA256 `04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`. `source/manifest.json` records the exact bounded native routines and comparison inputs. Reproduce with:

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-room-props.py --check
```

`source/native-drops.csv` records 512 fireplace and 512 poop cases from original executable code, with supplied nonzero drop RNG states and ordinary Normal/no held modifier gates. Fire uses shifts 1/11/6: 25% any pickup, then 25% heart versus 75% coin. Poop uses 1/5/16: 10% any pickup, consumes the disabled trinket-gate draw, then the same heart/coin split. The final word feeds the existing ordinary subtype factory. These probabilities do not describe modified or special props.

Existing ordinary durability is retained: fire starts at five hit-count HP, ordinary damage queues loss 1 plus a 1/3 bonus (base 2 above ten source damage), extinguishing below 1.5; explosion extinguishes. Poop has four steps, losing 1 plus two independent 1/3 bonuses per ordinary hit; explosion destroys it. Native disassembly is preserved alongside the drop fixtures. These counters are separate from regular enemy HP conversion. Fire contact defaults to one half-heart through the existing hurt/dodge/protection path. Poop is harmless and solid until destroyed.

`source/rooms.json` preserves three complete Basement records and STB hash: 1.26.0 (two poops), 1.52.0 (two poops/one ordinary Pooter), 1.633.0 (seven ordinary fires/eight plain rocks/two ordinary Gapers). Original spawn ordinal and source cells are retained. The existing canyon cell/descriptor adapter places them without imposing source outlines or corridor geometry. Protected objective/key/story/service roles retain their compositions. Test record 1000000 is explicitly authored for review: two fires/three poops/no hostile actors; it is not a native template.

## Enabled behavior and tuning

- **TUNING → REWARDS → ROOM LAYOUTS → FIRE / POOP** exposes LEGACY, SOURCE ROOMS and TEST BOTH. Layout changes are pending until **Apply map changes**, which regenerates the current floor and retains player/build/expedition identity. SOURCE requires the existing SOURCE LAYOUTS policy. LEGACY retains older room generation, including existing random dung dressing.
- Fire contact edits use half-heart steps (0–3 hearts), immediately for the next eligible contact. Destruction rewards ON/OFF affects future destructions. Resolved drops keep their identity and appearance settings through capacity/placement delay and revisits; every prop pays at most once. Ground flooding extinguishes without a destruction drop; mounted fires retain their previous rules.
- Schema47 exports/loads/remembers all three settings; schemas1–46 migrate to ordinary defaults while retaining their accepted map/view/shooting/item settings. Loaded map choices stay staged. Retry, new floors and next expeditions retain configuration. Configuration persistence is not live gameplay save/resume.
- Uses Black Creek’s original stone-ring campfire (`SM_Env_CampFire_01`, town asset `part_0362`) and its shared flame/ember/smoke attachments, plus the existing staged poop model. Extinguished fire retains the unlit hearth; destroyed poop opens its former solid footprint. Environmental fire does not count as an enemy or prevent room clear.

## Verification status

Source regeneration and the C++ selector match all1,024 native ordinary-drop cases. The focused prop suite passes real projectile destruction, half-heart contact and dodge, once-only rewards, capacity deferral, OFF behavior, revisit persistence, map regeneration and schemas5/46/47. The source witnesses are seed150/room6 for26, seed1015/room5 for52 and seed523/room5 for633. Nine minimum/accepted/maximum-size configurations construct successfully; seven retain the target record, while two correctly change selection with canyon door compatibility. Three test-layout size configurations retain their exact two-fire/three-poop contents. This is bounded coverage, not exhaustive seed acceptance.

Actual Game/Renderer mouse checks pass panel navigation, live edits, staged Apply, export/load, remembered next expedition and retry; screenshots are `room.png` and `tuning.png`. Preset and Screw regressions pass; existing environment and Fly/Pooter/dung suites pass. Final combined results are in `tests.log`. The original user export remains byte-identical (SHA256 `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`). Human review remains pending.

The saved review uses ordinary half-heart contact and enabled destruction rewards; the tuning screenshot shows deliberate test edits (one heart/drops off). Those screenshot settings are not the launch defaults.

## Interactive launch

```sh
build/deathward --expedition --seed 69 --review-source-room 1000000 --mute --balance-preset docs/reports/isaac-first-floor-parity/ordinary-room-props/review-preset.json --save /home/kambo/.local/share/deathward/reviews/first-floor-room-props/campaign.save
```

Opens directly near the centre of displayed room6, with normal six-half-heart health and no god mode. `interactive-launch.json` records the process/command, and `interactive.log` records CLI preset/review admission. The artificial template is explicitly labelled FIRE / POOP TEST in the game. The original user preset is not replaced.

## Human check

1. Walk into a fire: lose half a heart. Dodge through it: dodge immunity remains. Shoot it until it goes out, then walk across the unlit hearth safely.
2. Walk against a poop pile: it blocks movement without hurting you. Shoot it apart or place dynamite beside it; the space becomes passable. Drops are probabilistic, so an individual prop need not yield anything.
3. Revisit the room; destroyed props and collected rewards must stay spent. In tuning, change layout and press Apply; it should reset the floor for another test without restarting the application.

Unfinished: human visual/play acceptance, additional source layouts and colored/special fire/poop variants, item/trinket-modified destruction rewards, exact native actor/grid RNG initialization and physics/scheduler equivalence, complete D14a recorded-floor content and live gameplay resume. Full Fly/Round Worm remain proposed, not part of this selection. Next: accept or adjust this bounded prop delivery before resuming those dependencies.


## Town fireplace reuse — requested correction

The user rejected the procedural fireplace presentation and explicitly requested the town’s existing model and particles. `scripts/extract_campfire.py` extracts the unchanged630-triangle Black Creek mesh, original UVs/material/atlas into `assets/props/campfire/campfire.glb`; `--check` reproduces it byte-for-byte. No town placements or source asset bytes are changed. Its uniform render scale fits the already existing fire radius.

The town and expedition now call the same attachment sampler using the existing `SM_Env_CampFire_01` entries in `assets/particles/town.attachments`: three flame layers, ember, smoke and warm flickering light. Rendering uses the same simulation clock/culling limits and mission mesh/shadow/material passes. Extinguished fires retain the hearth and stop all attached emitters/lights; revisits cannot reignite them. Fire damage, hit counters, rewards, collision/controls and configuration are unchanged. Mounted rail fire remains on its earlier rendering path.

The main-game Game/Renderer check passes imported-model admission, visible flames/smoke/two lights, paused effects and extinguish/revisit behavior. The shared town render suite passes its pixel animation/depth/pause checks, editor transforms/copies, train trails and dust; ordinary-prop and environment gameplay suites pass. The separate existing `particle_emission` suite fails at its mine-obstacle bullet-impact fixture before explosion checks; its earlier source curve/prewarm tests pass. This rendering correction changes no core simulation or particle-library code, and that unrelated fixture is not counted passing. See the dedicated town-fireplace logs. Human acceptance and browser runtime verification remain open.

`town-fireplace-lit.png` and `town-fireplace-extinguished.png` show the updated main-game view. `interactive-town-fireplace-launch.json` records the restarted review using the same seed, settings and direct room entry.


## Poop remains — requested visual correction

The user clarified that the unwanted seven-point dirt foundation was the destroyed poop remnant, not the fireplace. The destroyed-pile render now uses five small, low, unevenly sized crumbs with visible floor between them; the continuous heptagonal slab is removed. Intact piles, collision/destruction/rewards and the accepted town fireplace were unchanged at this checkpoint. Main-game build and a temporary renderer capture of three piles destroyed by the existing explosion path pass; see `poop-remains-crumbs.png`. The user acknowledged this presentation ("nice") and requested slightly smaller piles next. Broader gaps above are unchanged.

## Smaller poop piles — requested adjustment

Ordinary piles now use 70% of their original width/depth and 105% of their original height, with the same bounds driving rendering and collision. The user selected 50% more height relative to the accepted short version (70% × 1.50 = 105%), superseding the insufficiently visible 25% increase. This fixed canyon presentation adjustment applies to source-layout and legacy-generated dung. Source placement centres, floor contact, hit counters and drop rules remain unchanged; the small remnant crumbs retain the accepted smaller footprint. Fireplaces are unchanged. The original authored mechanics values and preset schema remain intact. Verification results are recorded in `verification.json`; the user accepted the taller proportions. The earlier `poop-smaller.png` capture shows the superseded uniform 85% size.


### Height visibility audit

The user reported that the first height change was not visible. A temporary actual Game/Renderer comparison keeps the room, camera, zoom, clock and intact health identical and changes only the pile height. Generated bounds confirmed 0.77 → 0.9625 world units (+25%), retaining width 1.83379. At 1440×900 and 165% zoom the tip moved only about six screen pixels; the screenshots confirm a subtle silhouette change. See the historical `poop-height-before.png`, `poop-height-current.png` and `poop-height-audit.log`. The user subsequently selected +50% from the short version: current full height is 1.155 world units. The user subsequently accepted this taller appearance.

The selected +50% build and ordinary prop suite pass. A fresh actual Game/Renderer comparison confirms unchanged width and full heights 0.77 → 1.155, with about twelve screen pixels of tip movement at the same 1440×900/165% view. See `poop-height-50-before.png`, `poop-height-50-current.png` and `poop-height-50-audit.log`. The user accepted these proportions ("ok, nice now") and selected the separate [heart/dynamite HUD adjustment](../../expedition-heart-dynamite-hud/README.md). Broader prop/parity gaps above remain open.


## Wider piles requested during D14a.5, 2026-11-18

The later user request supersedes the70% intact footprint above: ordinary piles now use105% authored width/depth, retaining105% height and the earlier small destroyed crumbs. Rendering and collision use the same wider bounds, including legacy placement reservations and the source414 terrain-fit check. See [the D14a.5 follow-up](../d14a5-mixed-flies/README.md#wider-poop--requested-follow-up-2026-11-18). Developer geometry and render checks pass; human acceptance of this new width is pending.

The subsequent second width request increases the intact footprint to131.25% of authored size, retaining105% height and the small remnants. See [the second D14a.5 width adjustment](../d14a5-mixed-flies/README.md#second-width-increase--requested-follow-up-2026-11-18). Human acceptance remains pending.
