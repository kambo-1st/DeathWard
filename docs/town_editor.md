# Town editor

Press **F4 in the hub**, or choose **Town Editor** from its pause screen. You can also open it directly:

```sh
./build/deathward --editor
```

The editor opens the active hub: Black Creek or Western Frontier. Use `./build/deathward --editor --hub frontier` to edit the second hub directly. Each has its own scene, mesh library and navigation.

The editor uses the town's original textured meshes. It edits their placements: select, move, rotate, scale, add, duplicate or delete an object. Gameplay is suspended while editing. **Back to town** returns to the game; after a save, the game reloads the edited scene and navigation.

## Working with objects

Click a visible mesh, or select it in the **Scene** list. Search by asset name or object number, and scroll the list to browse. The **Assets** tab lists reusable models; select one and choose **Add at view center**. Imported placements remain separate mesh instances, as stored in `town.scene`.

Choose **Move**, **Rotate** or **Scale** with the buttons or **1 / 2 / 3**. Drag a colored X, Y or Z handle. Move uses world axes; rotation turns around the chosen axis at the object's pivot. Scale handles resize uniformly. The inspector's numeric position, rotation and scale fields provide precise values and per-axis scaling. Click a field, type its replacement and press Enter; Ctrl+A selects the current text. Imported reflected and sheared matrices are preserved when opening and saving.

Snapping uses 0.5-unit movement, 15-degree rotation and 0.1 scale increments. Hold Shift to bypass it or turn **Snap** off. **Ctrl+D** duplicates, **Delete** removes, and **Ctrl+Z / Ctrl+Y** undo and redo. A complete handle drag is one undo step. History retains up to 80 steps in the current session.

## Camera and markers

| Control | Action |
| --- | --- |
| Hold middle button and drag | Orbit and tilt |
| Hold right button and drag | Pan |
| Mouse wheel | Zoom |
| WASD | Move the camera across the town |
| Q / E | Lower / raise the camera |
| Shift while moving | Move faster |
| F / Focus selection | Frame the selected object |

**Place Arrival** and **Place Missions** let you choose a street location for each gameplay marker. Saving places the markers on nearby connected walkable ground; it refuses a save if no suitable surface is within eight units. **Grid** toggles the editing grid. **Paths** previews the last saved navigation, which updates after saving.

## Saving and playing

**Save** or **Ctrl+S** validates and saves `town.scene` and rebuilds `town.nav`. It retains the preceding versions as `town.scene.bak` and `town.nav.bak`. Both replacements are staged and validated first; reported replacement failures roll back to the backups. The model library, embedded textures and retained Unity sources are unchanged. **Reload** restores the last saved files. Leaving, reloading or closing the window with unsaved edits offers save/discard/cancel as appropriate.

In a source checkout, the game and editor use `assets/town/` for Black Creek or `assets/frontier/` for Frontier, so edits survive a rebuild. A packaged game without the checkout uses the matching folder beside its executable. To work on a separate copy of a town pack:

```sh
./build/deathward --editor --town /path/to/copied/town
```

That option edits the supplied pack; returning to gameplay uses the game's normal town pack. The direct editor launch uses a temporary campaign and does not resolve an existing player's expedition.

The native navigation rebuild samples the edited **visible geometry**, rather than Unity's original collider components. It keeps the selected hub's original outdoor grid: 0.4-unit cells, surface heights between -5 and 12, obstacle clearance and a 0.6-unit step limit. Black Creek spans X -120 to 120 and Z -90 to 150; Frontier spans X -160 to 170 and Z -120 to 140. Only ground connected to Arrival is playable. This supports rearranging the outdoor town; it does not add building interiors or multiple walkable floors. Check Paths and play the edited streets after substantial changes.

The original import manifest remains an audit of the Unity demo. `scripts/verify_town.py` checks that original conversion and will report scene/navigation hash differences after intentional edits. Reimporting the Unity scene replaces editor changes, so keep the edited files in version control or a separate pack.

## Verification

```sh
./build/deathward_editor_tests
./build/deathward_input_tests
```

Editor tests use an isolated copy of the town. They cover mesh picking, handle dragging, transforms, placement/deletion, undo/redo, exact scene round trips, failed-save preservation, backup files, rebuilt navigation, camera controls and unsaved-close handling.
