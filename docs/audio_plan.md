# Audio implementation plan

Implemented on 2026-09-28. The first pack uses original synthesized effects and soundscapes; recorded effects and a score remain future art work. Runtime controls, WSLg playback, bounded mixing and silent fallback are available. See [the audio pack](../assets/audio/README.md), [player instructions](../README.md#audio) and [verification results](verification.md#first-audio-milestone).

Use the audio module already supplied by pinned raylib 5.5, through a small `AudioSystem` owned by the application. Keep device access and sound assets outside `deathward_core` so simulation tests remain headless and deterministic.

## WSL2 and native Windows

The intended WSL2 path is DeathWard → raylib/miniaudio → WSLg PulseAudio → Windows output. [Microsoft documents WSLg's PulseAudio integration](https://github.com/microsoft/wslg#audio). Native Windows uses miniaudio's Windows backends, headed by WASAPI; [miniaudio documents backend selection and priority](https://miniaud.io/docs/manual/#backends).

Before this milestone, the workspace forced `SUPPORT_MODULE_RAUDIO` off in `CMakeLists.txt`; it is now enabled. Preserve the existing `PULSE_SERVER` environment instead of replacing it or starting another sound server. Provide `libpulse0` as a Linux runtime prerequisite; it is already installed here. An older WSL2 installation without WSLg needs audio-server configuration before this path is available.

A local probe on 2026-09-28 compiled the pinned `raudio.c` separately without changing the game build. It selected **PulseAudio**, initialized stereo output at **44,100 Hz**, played a silent PCM buffer to completion, and closed successfully. The environment provides `PULSE_SERVER=unix:/mnt/wslg/PulseServer`; the socket and client libraries exist. `/dev/snd` is absent, so direct hardware ALSA is not the appropriate default here. Probe source and logs are in `artifacts/audio-probe*`. This verifies the software playback path, not audible speaker output or end-to-end latency.

## First playable milestone

- Revolver report, separate impact sounds for stone and enemies, player hurt, dodge, enemy death, key/power pickup, room clear, and UI confirmation. Preserve the current no-reload gameplay.
- Footsteps tied to actual movement, with gravel, wood and mine-floor variants; pause footsteps while stationary or dodging.
- Quiet looping ambience: wind and occasional wildlife in the canyon, street/wood sounds in Black Creek, foliage/water in Frontier, and creaks/drips in the mine. Crossfade on travel and mission changes.
- Master, effects and ambience volume, mute, and a short test-sound button. Add music as a separate channel once the basic mix feels right.

Use short mono WAV files for positional effects and streamed stereo OGG for long ambience/music. Bundle assets with the executable using the existing asset-copy convention. The first pack uses original synthesized effects, with a few variations per frequently repeated sound; recorded replacements can use the same asset layout.

## Integration

Initialize once at application startup and release all sound/stream resources before closing the device. Pump music streams every application frame, including menus and pause. Reduce ambience on pause and stop combat loops. Do not restart playback or initialize devices from rendering functions.

Emit small audio cues at confirmed gameplay transitions: successful shots, applied damage, final deaths, pickups, door changes and attack windups. Use a bounded presentation queue that survives multiple fixed simulation steps and is consumed once per application frame. Clear old cues on run replacement/travel. Avoid replaying the combat event queue itself: derived shots, chain explosions and damage propagation could otherwise duplicate sounds. Do not consume gameplay random streams when choosing sound variants.

Use a bounded pool of `LoadSoundAlias` voices for overlapping effects. Start with a 32-voice budget, prioritizing player shots, player damage and attack warnings over incidental impacts. Apply per-effect rate limits and distance falloff; pan relative to the camera's right vector so orbiting keeps left/right sound aligned with the screen. Visual enemy occlusion must not mute important attack cues. Basic stereo positioning is sufficient for this milestone; acoustic ray tracing can wait.

Add `--mute` to bypass audio initialization entirely, with scripted rendering and benchmarks silent by default. If initialization fails, continue gameplay silently and record the failure once. Disable miniaudio's null backend for the audio-enabled build so an unavailable output cannot be reported as a working sound device. Log the selected real backend and sample rate without assuming a fixed output rate.

## Acceptance checks

1. WSLg: audible test cue, overlapping shots/impacts, an uninterrupted ambience loop, travel crossfades and clean exit.
2. Native Windows: repeat on WASAPI; this remains untested on the current host.
3. Missing device and `--mute`: gameplay and headless tests continue without hanging or repeated initialization attempts.
4. Pause, death, hub travel and restarting a mission: no stale cues or orphaned loops.
5. Stress encounter: bounded voices, no clipping from stacked impacts, and no material frame-time regression. Verify camera-relative panning after an orbit.

Implement this milestone before adding a full music score or unique sounds for every monster variant.
