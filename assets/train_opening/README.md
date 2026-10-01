# Westbound cinematic set

A dedicated desert railway, separate from all three playable hubs. The retained
Western train, carriage interiors, tracks, rocks and cacti keep their embedded
source textures. There is no station, fort or town outside the carriage windows.
One convoy follows a long straight foreground rail; the unused return route is
outside the filmed area. The scene has 286 instances, including track sections,
44 sparse desert props and the train parts.

`arrival.cinematic` contains the 82-second opening: camera shots, seated cast,
dialogue, conductor movement, weather, audio, braking and the Redstone destination.
Edit it in **Cinematic Editor → Train opening**. The conversation is subtitled;
the first sound pass uses the original synthesized train/wind/brake clips.

`python3 scripts/create_train_opening.py` rebuilds only this set's geometry,
placements and height map from the retained `assets/town` pack. It deliberately
does not overwrite the authored `.cinematic` file or any existing hub. The height
map supplies cinematic ground sampling; this map is not offered as a playable hub.
To change scenery through the town editor, use:

```sh
./build/deathward --editor --town assets/train_opening
```

Play the complete opening and enter Redstone with `./build/deathward --intro`.
Use `--cinematic --intro` for editing and `--cinematic-at SECONDS` for a chosen frame.
