# ROUGHSHOD — editable cart-story artwork with textured sand

**Revision 8:** corrects the floating cargo. Previously, grounding used the corners of rotated bounding boxes and three inside sacks had guessed support heights. Those corners do not lie on the cloth mesh, leaving visible gaps above the sand. The eight sacks now settle against their actual support surfaces: two on the crate's tilted interior floor, one on the lower sacks, and five on the sand. The spill immediately outside the opening moves slightly forward to clear the crate lip. Cloth/sand contact uses a small 0.004–0.006 scene-unit embed to avoid visible gaps. Sand texture, wheel tracks and the surrounding composition are retained.

Revision 7 added fine sand grain, uneven dry-color patches, smaller scuffs and shallow relief. All material controls remain editable.

The paired carriage wheel tracks retain the actual source wheel spacing and curve across the open sand with soft edges and a gradual fade.

The preserved cart story shows a stopped merchant cart with a dropped wooden supply crate: the opening faces the viewer, some cloth cargo remains inside and an irregular trail of sacks spills onto the sand. A small lantern crate sits beside the spill; the barrel, second lantern and intact supplies sit behind it. Extra local clutter is hidden to keep those relationships visible.

The restored cowboy, gun pose, title/font, camera, landscape geometry and original lighting remain. There is no enemy or Spider in the active scene. The scene is assembled from existing game assets; the fallen crate is an explicitly edited copy of the game's wooden crate, with its front planks opened and an editable thickness modifier for the interior. Original game asset files are unchanged.

## Files

- **`roughshod-banner.png`** — current 2560 × 1440 master, Cycles, 64 samples.
- **`cart-story-detail.png`** — close-up rendered from the same banner camera, for inspecting the cart and cargo relationship.
- **`roughshod-banner.blend`** — editable scene with packed textures and font.
- **`thumbnail-320x180.png`** — thumbnail of the current composition.
- `hand-detail.png` — restored revision-2 grip detail; the hand/weapon pose is retained.
- `scene.json` — preserved-scene reference, cart/cargo transforms, wheel-track controls, sand-grain/patch/relief controls and output settings.
- `build_scene.py`, `story.py`, `cargo_contacts.py`, `wheel_tracks.py`, `ground_noise.py` — restore the original composition and assemble the cart story, wheel ruts and textured sand.
- `cargo-contacts.json` — per-sack support and measured contact after placement, rechecked from the saved scene.
- `ground-noise.json` — editable sand texture settings and material-layering record.
- `wheel-tracks.json` — source wheel bounds, spacing and editable path/material configuration.
- `render_master.py`, `capture_cart.py`, `capture_preview.py`, `capture_thumbnail.py`, `capture_hand.py` — render the saved composition and detail views.
- `restoration-check.json` — records the local objects changed or hidden relative to revision 2.
- `source-assets.json`, `verification.json`, `artifact-hashes.json` — provenance, saved-scene checks and hashes.
- `history/v2/roughshod-banner.blend` and its `source-assets.json` — versioned rebuild dependencies. Other earlier handoffs remain in the local ignored history archive; the rejected Spider version is only in that archive. Duplicate preview scenes and render logs also remain local.

This is promotional artwork, not a screenshot of an expedition floor. No game code, balance or presets are changed. There is no generated bitmap, painted backdrop or AI-created model in the scene.

## Edit in Blender

Open `roughshod-banner.blend` in Blender 3.6 or later.

- **Title:** edit `ROUGHSHOD · EDIT THIS TEXT` in collection 05. Its linked shadow updates with it. The packed font is the game's `DeathWardDisplay-Regular.otf`, SHA256 `8a959b9e8bbaed9dbd02e3dc284389c303ae6ee358b0a5d9102b270a75be8ae9`.
- **Cart:** move/scale `WAGON · placement control` to adjust the entire original merchant cart.
- **Story cluster:** `STORY · tipped crate and cargo` groups the fallen crate and eight individually editable sacks. Change each object's transform to adjust the spill. Rebuilding settles the actual sack meshes onto the crate deck, lower sacks or sand using `cargo_contacts.py`; support heights are no longer guessed. The crate retains the source wooden frame, planks and UV atlas; its front-panel removal is confined to its private mesh copy. `EDITABLE · wooden wall thickness` controls its interior thickness. The unchanged source crate remains in hidden collection 00.
- **Wheel tracks:** collection 07 contains `WHEEL TRACKS · path control`, parented to the wagon. Moving the wagon moves the tracks with it. The material `SAND · original atlas + carriage wheel tracks` on the original floor has a labelled control frame for spacing, width, bend, fading and shallow relief. Its original base atlas and UVs remain.
- **Ground texture:** the same floor material contains `SAND GRAIN · editable controls`. Adjust fine grain scale/strength, dry patches, scuffs and shallow bump there. Grain uses fixed world coordinates, so moving the cart moves its tracks across the sand rather than dragging the grain pattern. It feeds the existing wheel-rut color/normal layer. Rebuild settings are in `scene.json` → `ground_noise`.
- **Supporting props:** barrel, lanterns, intact crate, cactus and skull remain separate named source objects in collection 02. Superseded local clutter is hidden rather than deleted.
- **Character:** collection 03 retains the original 48-bone rig, imported clips and revision-2 hand/weapon pose. The still composition uses frame 28.
- **View and light:** collection 04 contains the original camera and lights. Collection 01 contains the canyon; collection 00 keeps source meshes.
- Press **F12** to render. Hide collection 05 for an image without the title.

The packed `.blend` renders without the repository. Rebuilding uses `history/v2/roughshod-banner.blend` as the stable scene snapshot and imports individual sacks from `assets/town/town.glb`. Keep that snapshot and repository asset available for rebuilding. The original `hero`/lighting fields in `scene.json` document the preserved composition; this scoped builder applies wagon, `cart_focus`, `cart_story`, `wheel_tracks`, `ground_noise` and output settings. Supporting layout positions are in `story.py`.

Manual Blender edits and rebuilding are separate workflows: save a separate `.blend` for manual revisions because rebuilding replaces the master with the script/configuration settings.

## Rebuild and detail render

From the repository root:

```sh
/tmp/deathward-blender/blender --background --threads 12 --python docs/artifacts/roughshod-steam-banner-2026-11-19/build_scene.py
```

The executable path is the temporary local Blender 3.6.23 installation; substitute another installation if needed. Add `-- --preview` for separate 1280 × 720 drafts, or `-- --save-only` to assemble/save without rendering. To render an already edited master, open the `.blend` and press F12, or load it with Blender and run `render_master.py`.

```sh
/tmp/deathward-blender/blender --background --threads 12 docs/artifacts/roughshod-steam-banner-2026-11-19/roughshod-banner.blend --python docs/artifacts/roughshod-steam-banner-2026-11-19/capture_cart.py
```

## Source assets

| Element | Repository source |
| --- | --- |
| Cowboy, costume, rig and clips | `assets/bandit/bandit.glb` |
| Canyon, sand, cacti, fence, crates, barrels, grouped sacks, lanterns and skull | `assets/western/western.glb` |
| Ground grain | Editable procedural color, matte roughness and shallow normal relief on the original sand material; original atlas/UVs retained |
| Wheel tracks | Procedural color/normal treatment on the original Western sand floor, aligned from the shop-cart GLB wheel bounds; no added mesh or image |
| Fallen wooden crate | Edited private copy of Western `crate`; front opened, original frame/UVs retained, inward thickness modifier |
| Individual spilled cloth sacks | `assets/town/town.glb`, node `part_0271`, original `SM_Prop_Sack_03` |
| Fort Mercy merchant cart | `assets/props/shop-cart/shop-cart.glb` |
| Detailed source revolver | `assets/town/source/Models/SM_Wep_Revolver_01.fbx` |
| Revolver atlas | `assets/town/source/Textures/PolygonWestern_Texture_01_A.png` |
| Game display font | `assets/ui/deathward-display/DeathWardDisplay-Regular.otf` |

The detailed revolver is a repository source asset; the gameplay actor uses a simpler drawn weapon. The scene arrangement is not a claim of exact gameplay scale. `OFL.txt` accompanies the font. `source-assets.json` records the crate adaptation separately from the unchanged source-file hashes.

## Verification and remaining work

The restoration check bounds changes to the cart's local props and records the added crate/cargo. Saved-scene checks cover the packed game font, editable linked title/shadow, original rig, source hashes, absence of Spider geometry, the copied crate's modifier and resource portability. Each sack's actual saved mesh is also checked against the crate floor, lower cargo or sand. The full banner, cart detail and 320 × 180 thumbnail are inspected separately.

**Revision 8 accepted by the user**, who requested its commit before a separate contrast/color experiment; see `human-acceptance.json`. Revision 7's ground texture was also positively acknowledged. The cart story, character, title and wheel tracks are retained. Steam-specific store/library crops remain; the landscape master is not a complete Steam upload package. The separate D14a.11 gameplay delivery remains outside this artwork change and awaits its own playtest acceptance.
