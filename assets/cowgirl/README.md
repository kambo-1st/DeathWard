# Cowgirl

The supplied FBXs contain the same Western cowgirl: 1,049 source vertices, 2,024 triangles, a 48-bone skeleton and an embedded 2048×2048 color texture. The runtime model is `cowgirl.glb`.

| Runtime clip | Source file | Duration |
| --- | --- | ---: |
| Idle | Idle.fbx | 16.63 s |
| Idle2 | Idle (1).fbx | 1.97 s |
| Walk | Walking (1).fbx | 0.97 s |

All three clips and the original embedded texture are retained. Animated ancestors and centimeter units are baked into a meter-scale, Y-up skeleton. Horizontal root travel is removed so navigation controls position. Runtime blends locomotion with idle poses and alternates between the two idle clips at route stops. Instances share a model but have independent animation clocks. The model uses the same lighting, shadows and post processing as town scenery and animals.

Black Creek includes `cowgirl-street-walk`, an ambient character who follows four stops around the starting street. She walks at 1.2 m/s and waits two seconds at each stop. Characters do not block or fight the player. Pause, mission selection and expeditions suspend their simulation. Frontier starts without characters, but the editor can place them there too.

Open **F4 → People** to place characters and edit their routes. Placements, speed, pause, scale, facing, route mode and stops are stored in `town.scene` format 4. See [the town editor guide](../../docs/town_editor.md#characters-and-walking-routes).

Rebuild with Blender 3.6 LTS, verified with 3.6.23:

```sh
blender --background --python-exit-code 1 --python scripts/convert_cowgirl.py
python3 scripts/verify_cowgirl.py
cmake --build build --parallel 1
./build/deathward_character_tests
./build/deathward_character_model_tests
./build/deathward_editor_tests
```

The manifest records source hashes, clip frame counts/durations and the generated GLB hash. The audit checks the source/output hashes, embedded texture, UVs, skin weights, joint indices and all clip durations. Source FBXs remain in this folder; native and browser distributions include only the GLB. Use the supplied character under its existing asset license.
