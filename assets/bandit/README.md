# Bandit player asset

The original FBX files in this folder are the supplied character and animation sources. `bandit.glb` is the runtime asset: one mesh, the original embedded 2048 × 2048 texture, a 48-bone skeleton and nine named clips. The source mesh has 1,243 vertices and 2,398 triangles; exporting UV seams and normals can split vertices.

| Source FBX | Exported clip | Game use |
| --- | --- | --- |
| Breathing Idle.fbx | Idle | Standing |
| Walking.fbx | Walk | Slow movement |
| Run Forward.fbx | Run | Normal movement |
| Firing Rifle.fbx | Fire | Attacks; upper-body blend while moving |
| Running Slide.fbx | DodgeSlide | Dodge started while moving |
| Jump Forward.fbx | DodgeForward | Additional imported jump, available for animation tuning |
| Jumping.fbx | DodgeStanding | Dodge started from rest |
| Death.fbx | Death | Natural death |
| Rifle Death.fbx | DeathRifle | Natural death while firing |

The existing revolver is attached to the right hand. Clip names do not change weapon stats or controls. Slide and jump clips fit the existing 0.22-second dodge; death clips fit a two-second presentation before the result screen. The F9 shortcut skips that presentation.

## Rebuild

From the repository root, using Blender 3.6 LTS (verified with 3.6.23):

```sh
blender --background --threads 2 --python scripts/convert_bandit.py
cmake --build build --parallel 4
./build/deathward_player_model_tests
```

The converter selects the Mixamo animation take on the rig and its ancestors, discards unrelated legacy scene tracks, converts centimeters to meters, bakes the skeleton into a clean armature, and removes horizontal root travel while preserving vertical motion. Gameplay remains responsible for movement and collisions. The GLB embeds its texture and animations; no FBX importer or Blender installation is required to run the game.

`bandit.manifest.json` records source hashes, clip lengths, Blender version and the output hash. Regenerate it together with the GLB when replacing a source animation. The runtime loader uses the pinned raylib 5.5 glTF animation sampling interval of 17 ms, then interpolates and blends local bone transforms before skinning.
