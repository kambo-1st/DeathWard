# Reversible art-direction sample

This is an isolated asset study, not a new game style or a map update. Normal
gameplay, the editor, the existing visual-style switches and save files do not
load these assets. The sample is excluded from normal native and web packaging.

Run from the repository:

```sh
scripts/run-art-sample.sh
```

Controls: **1** original, **2** silhouettes, **3** painted materials, **4** combined;
**Tab** alternates original and the last custom view. Drag to orbit, wheel to zoom,
**H** to inspect the protagonist, **R** to reset the camera, **Space** to animate,
**W** to preview walking, **Esc** to close. Controls are session-only.

The viewer uses the game's Original sunlight, shadow and post-processing pipeline
for every mode. It does not add another full-screen treatment. Its simple ground
and fixed arrangement deliberately make local mesh and material changes easy to
compare. No original maps are copied into or saved from this tool.

## What changes

| Object | Local shape treatment | Material treatment |
| --- | --- | --- |
| Protagonist | Asymmetric brim, pinched crown, skinned shoulder wrap and hem | Painted indigo, canvas and leather; source face and hands retained |
| Tent | Sagged ridge, uneven sides, entrance valance | Pale canvas and wood |
| Wagon | Lower/listing hoop profile, partial canvas cover, repair boards | Painted canvas, wood and leather; dark iron retained |
| Short fence | Uneven/leaning rails, end post, diagonal brace | Directional painted wood grain |

The original geometry remains underneath the local changes. The protagonist's
rig and nine animation streams are copied byte for byte; added clothing uses the
existing spine joints. This is a visual prototype, not a production cloth system.

## Reproduce and compare

The checked-in derivatives need no asset tools to run. To rebuild only the sample
assets, install Python's `numpy` and `Pillow`, then:

```sh
python3 scripts/create_art_sample.py
scripts/run-art-sample.sh --capture
python3 scripts/art-sample-report.py
```

Open `artifacts/art-sample-comparison.html`. It embeds the actual renderer captures
and has a comparison slider, three cameras and separate shape/material controls.

`manifest.json` records source SHA-256 hashes. The builder asserts that original
character and town/frontier/redstone model, scene and navigation files have not
changed. Capture mode checks exact pixel restoration after switching through the
four modes, and exercises the retained walk animation.

The selected `painted-atlas-v2.png` was created with the built-in imagegen tool.
Its final prompt is in `texture-prompt-v2.txt`. The atlas is embedded in the
derivative GLBs; originals keep their own textures.

## Turn off or remove

Close the separate viewer. There is no gameplay setting to undo and nothing is
written to saves or maps. Pressing **1** also restores the baseline immediately.

To remove its optional build target:

```sh
cmake -S . -B build -DDEATHWARD_ART_SAMPLE=OFF
```

The only integration into the existing project is the gated CMake block. Full
removal consists of removing that block and the sample-only files:
`tools/art_sample.cpp`, `scripts/run-art-sample.sh`, `scripts/create_art_sample.py`,
`scripts/art-sample-report.py`, and `assets/art_sample/`. Generated comparison
files live under the already-ignored `artifacts/` directory. No existing asset
needs to be restored.
