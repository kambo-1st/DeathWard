# Town editor

Press **F4 in the hub**, or choose **Town Editor** from its pause screen. You can also open it directly:

```sh
./build/deathward --editor
```

The editor opens the active hub: Black Creek, Western Frontier or Redstone Canyon. Use `./build/deathward --editor --hub frontier` or `./build/deathward --editor --hub redstone` to edit those packs directly. Each has its own scene, mesh library and navigation.

The editor uses the town's original textured meshes. It edits their placements: select, move, rotate, scale, add, duplicate or delete an object. Gameplay is suspended while editing. **Back to town** returns to the game; after a save, the game reloads the edited scene and navigation.

The viewport shares the hub's sunlight, ambient fill and filtered sun shadows. Moving, adding or deleting geometry updates its shadow immediately; orbiting and zooming preserve the scene's original sun direction.

The viewport also previews the game's autumn palette, bloom and color grade. Editor panels and text stay outside the post-processing pass. These effects are runtime rendering choices and do not rewrite textures or the scene catalog when saving.

## Working with objects

Click a visible mesh, or select it in the **Scene** list. Search by asset name or object number, and scroll the list to browse. The **Assets** tab lists reusable models; select one and choose **Add at view center**. Imported placements remain separate mesh instances, as stored in `town.scene`.

Choose **Move**, **Rotate** or **Scale** with the buttons or **1 / 2 / 3**. Drag a colored X, Y or Z handle. Move uses world axes; rotation turns around the chosen axis at the object's pivot. Scale handles resize uniformly. The inspector's numeric position, rotation and scale fields provide precise values and per-axis scaling. Click a field, type its replacement and press Enter; Ctrl+A selects the current text. Imported reflected and sheared matrices are preserved when opening and saving.

Snapping uses 0.5-unit movement, 15-degree rotation and 0.1 scale increments. Hold Shift to bypass it or turn **Snap** off. **Ctrl+D** duplicates, **Delete** removes, and **Ctrl+Z / Ctrl+Y** undo and redo. A complete handle drag is one undo step. History retains up to 80 steps in the current session.

## Animating props

Select an object and open **Animation** in its inspector. Available presets are **Static**, **Spin**, **Sway** and **Tumbleweed**. Black Creek's two original tumbleweeds already use the rolling preset; other props start static. The two original trains use linked route groups, described below.

| Preset | Settings |
| --- | --- |
| Spin | Degrees per second, local X/Y/Z rotation axis and local pivot coordinates |
| Sway | Swing angle, period in seconds, playback speed, local axis and pivot |
| Tumbleweed | Travel speed, small bounce height, gust period and wind seed |

**Play preview** animates the scene; **Pause preview** holds the current pose; **Reset preview** restores the saved placement and enables the placement handles. Camera controls, selection and focus work during preview. Changing a setting resets preview. Duplicate copies the settings and assigns a new object ID, giving a copied tumbleweed its own wind phase. Undo/redo includes animation settings and restores them when undoing deletion.

Saving during preview writes the authored placement and motion settings, never the temporary pose. Preview does not itself mark the scene as changed. Preview uses the current edited navigation; when changes affect it, Play rebuilds a temporary navigation map first. Save rebuilds the persisted map normally.

Spin, Sway and Tumbleweed props are **decorative and do not block the player**. They are excluded from static navigation and the static shadow cache. Tumbleweeds sample ground and clearance, turn at obstacles, roll in proportion to actual travel and make only small bounces. Put them on reachable street ground with room around their scaled bounds.

Settings live in scene format 2 with stable per-object IDs. Format-1 scenes and existing browser editor overrides still load as static scenes; assign presets in the editor to animate those custom layouts. Saving preserves their original matrices and upgrades to the current scene format. No mesh or texture conversion is required when changing presets.

## Trains

Select any part of a train and open **Animation**. Selection outlines the complete vehicle, and **Focus selection** frames that vehicle. The rail centerline appears in teal. **Travel speed**, **Acceleration** and **Station wait / sec** affect all vehicles on the shared loop. Black Creek defaults are 3, 0.8 and 6 respectively. Redstone Canyon has one four-vehicle convoy parked at speed zero beside the sand blockage. Raising its speed reuses the original route; it does not remove the authored sand drifts. A zero station wait lets a moving train continue through the loop boundary without braking; player obstruction still stops it. **Play/Pause/Reset preview** works as it does for props; saving during preview preserves original placements and route settings.

Locomotives, tenders, coaches and freight wagons follow the original rail curves as separate linked vehicles. The sixteen separate locomotive wheels turn with distance traveled. Wheels and linkage geometry already combined into coach/tender/freight body meshes remain rigid. Trains are solid: game movement and mouse paths avoid their current hulls, and trains stop for the player. Pause and missions freeze the hub simulation.

Bound parts cannot be moved, rotated, scaled or duplicated independently. **Delete** removes the selected vehicle and all its parts; **Undo** restores its bindings. **Detach vehicle** releases that entire vehicle at its original placement, making its parts static and editable again. Route point editing and attaching additional vehicles are not yet exposed; keep the authored rails clear of new buildings. The train route and bindings use scene format 3, while older scene formats remain compatible.

## Characters and walking routes

The **People** tab places textured, animated residents in any hub. **Add cowgirl** creates the default model; the inspector's **Model: Cowgirl / Model: Bandit** button switches between the two supplied characters. Position, route and other settings are retained, and model changes support undo/redo. Black Creek includes a four-stop cowgirl demo near the starting street. Redstone has fifteen provisional story residents, including stationary witnesses and walking passengers, settlers and railroad workers.

1. Choose **Add cowgirl**, then click walkable ground for her starting point.
2. Choose **Add route stops** and click each destination in order. Press **Escape** when finished.
3. Select a numbered stop in the list or click its marker. **Move stop** lets you reposition it with another ground click; **Remove stop** deletes it. Scroll the list for longer routes, or choose **Clear route** to leave a stationary character.
4. Set **Speed**, **Pause**, **Size** and **Facing**. **Loop** returns from the final stop to the start; **Back and forth** reverses through the stops. The starting point is also a stop. Pause applies there and at every destination; speed zero holds the character still.
5. Use **Play preview**, **Pause preview** and **Reset preview** to review the route. **Focus** frames the selected cowgirl. Save, then choose **Back to town** to see her follow it in the game.

The route line follows navigable streets around buildings. Invalid connections appear red. Unreachable destinations are rejected when adding stops; saving also checks the route against navigation rebuilt from edited scenery. A moving train can temporarily block a route; the character waits and retries. Characters follow terrain, turn toward their movement, blend the walking animation with idle poses, and use both supplied idle clips during stops. The preview shares the game's sunlight, shadows and post processing.

Click a cowgirl in the viewport while the People tab is active to select her. Moving her starting point leaves existing route stops in place. **Duplicate**, **Delete**, **Undo** and **Redo** include the character and route. Duplicates get separate IDs; place the copy on clear ground. Changing settings resets preview. Saving during playback records authored positions and stops, never the preview's temporary pose. A town supports up to 64 characters with 128 additional stops each.

Character records were introduced in `town.scene` format 4 and remain in format 5 alongside animal placements; formats 1–4 still load. Characters are separate from static mesh instances and navigation blockers. They are ambient residents, with no combat or dialogue behavior. Their gameplay simulation stops during pause, mission selection and expeditions. Editor preview runs separately from the suspended game.

## Animals

The **Animals** tab supports all 98 textured, animated variants in any hub. **In town** lists the existing residents, including Black Creek's horse, cow, cat and two hens. Click one in the list or viewport to edit it. **Species** provides a searchable, scrollable catalog; choose a variant, click **Add animal**, then click clear ground for its home. Escape ends placement.

**Place home** moves the selected animal with another ground click. **Change species** opens the catalog and **Apply species** replaces its model while retaining its home and settings. The inspector edits **Size** (0.25–3), **Roaming radius** (0–20 metres), **Facing** and **Roaming seed**. Radius zero keeps the animal stationary while its idle/eating animation plays. The home marker and ring show the authored center and roaming area. The whole animal footprint needs clear ground, with space from other homes and the mission board; large species may need a more open area or smaller scale.

**Play preview**, **Pause preview** and **Reset preview** use the same textured models, animations, lighting and ground-following roaming as gameplay. The preview has its own clock and respects scenery, other residents and the moving trains. Changing settings resets preview. **Focus**, **Duplicate**, **Delete**, **Undo** and **Redo** include animals; duplicates receive separate IDs and seeds and must be placed on clear ground before saving. Up to 64 animals can be placed in each hub.

Save includes animal definitions in `town.scene` format 5 and checks their homes against freshly rebuilt navigation. Saving during preview retains the authored homes, not temporary roaming positions. Deleting every animal remains an empty population on reload. The five original Black Creek placements are preserved; Frontier starts empty. Older game scenes use the legacy `town.animals` definitions until their first editor save. Browser persistence includes the same records.

Animals remain ambient residents. Flying and aquatic models can be placed and animated, but their movement currently follows ground navigation; flight and water habitats are not implemented.

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

Navigation includes reachable building interiors and checks standing headroom beneath roofs and beams. Door leaves open automatically as the player approaches; walls, posts, furniture and low ceilings retain collision. Imported building labels identify the hollow architecture and hinged door/window pieces, including copies placed in the editor. Keep those asset labels when preparing a custom pack. An explicitly assigned animation takes precedence over automatic door movement. Saving records the original door poses, not temporary open positions.

In gameplay, entering a building cuts away its roof and upper walls so the original interior stays visible. Leaving restores the exterior. The editor keeps complete meshes visible for placement; test entry and cutaways with **Back to town**. Older navigation is rebuilt once at startup without replacing the saved scene.

**Save** or **Ctrl+S** validates and saves `town.scene` and rebuilds `town.nav`. It retains the preceding versions as `town.scene.bak` and `town.nav.bak`. Both replacements are staged and validated first; reported replacement failures roll back to the backups. The model library, embedded textures and retained Unity sources are unchanged. **Reload** restores the last saved files. Leaving, reloading or closing the window with unsaved edits offers save/discard/cancel as appropriate.

In a source checkout, the game and editor use `assets/town/` for Black Creek, `assets/frontier/` for Frontier or `assets/redstone/` for Redstone Canyon, so edits survive a rebuild. A packaged game without the checkout uses the matching folder beside its executable. To work on a separate copy of a town pack:

```sh
./build/deathward --editor --town /path/to/copied/town
```

That option edits the supplied pack; returning to gameplay uses the game's normal town pack. The direct editor launch uses a temporary campaign and does not resolve an existing player's expedition.

The navigation rebuild samples the edited **visible geometry** with 0.2-unit cells, surface heights between -5 and 12, 1.9 units of standing headroom and a 0.6-unit step limit. Black Creek spans X -120 to 120 and Z -90 to 150; Frontier spans X -160 to 170 and Z -120 to 140. Only surfaces connected to Arrival are playable. Building floors and roofs are separate slabs rather than a solid column. Navigation still stores one traversable height per X/Z cell, so overlapping upstairs/downstairs routes are not fully supported. Check Paths and play the edited entrances after substantial changes.

Black Creek includes an added `station-entrance-steps` placement made from the original textured stair asset, connecting the raised platform to the street. It can be edited like any other static prop. After a fresh Unity import, `python3 scripts/add_station_steps.py` restores this placement and rebuilds navigation.

The original import manifest remains an audit of the Unity demo. `scripts/verify_town.py` checks that original conversion and will report scene/navigation hash differences after intentional edits. Reimporting the Unity scene replaces editor changes, so keep the edited files in version control or a separate pack.

## Verification

```sh
./build/deathward_editor_tests
./build/deathward_input_tests
```

Editor tests use an isolated copy of the town. They cover mesh picking, handle dragging, transforms, placement/deletion, undo/redo, exact scene round trips, failed-save preservation, backup files, rebuilt navigation, camera controls and unsaved-close handling.

## Attached fire effects

Search **CampFire** in the Assets tab to place a stone-ring fireplace. Campfire
props carry the PolygonParticleFX fire automatically, including flames, embers,
smoke and warm light. **Play preview**, **Pause preview** and **Reset preview**
control the effect clock. Moving, rotating, scaling, duplicating or deleting the
prop also changes its attached effect; normal save/reload and undo apply.
Black Creek includes a demo near the starting point at `(-2, .06, 0)`.
Effects use the shared [particle library](../assets/particles/README.md); individual
emitter settings are currently edited in its data files, without a particle panel.

Locomotive steam is attached to `SM_Veh_Train_01_Alt_Smokestack`. Train preview
keeps emitted puffs behind a moving locomotive. Moving, scaling, duplicating and
deleting a stack automatically updates its emitter; preview reset clears trails.
The imported train groups and routes still control the vehicle itself.
