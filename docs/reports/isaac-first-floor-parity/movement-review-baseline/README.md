# Movement baseline: human checkpoint 0

Status: **human accepted the responsive comparison baseline, then requested slower walking**. This is the current DeathWard movement, not an Isaac movement replacement. No inertia/glide was added and no S gameplay difference is enabled.

Run from the repository root:

```sh
./build/deathward_movement_review
```

The preserved executable is `/home/kambo/.local/share/deathward/reviews/movement-baseline-20261108T145628Z/deathward_movement_review`. It uses a private mechanics snapshot beside the binary. Its hash is in `validation.json`; rebuilding the development executable does not overwrite it. It still uses visual assets from this checkout. No binary was added to Git.

- **WASD / left click:** existing walking controls.
- **Arrows, including diagonals / right mouse:** existing firing controls. No direction quantization or input mapping was changed.
- **Space:** existing universal dodge. **H:** ordinary controls help.
- **F8:** reset position, camera and sample to the baseline starting state.
- **F11:** pinned camera / ordinary following camera. Q/R, middle drag and zoom remain available. Keep the same view for a fair comparison; reset restores the default 160% zoom.
- **F7:** arm a two-simulation-second travel sample, starting when movement begins. The result includes any pauses in movement, dodge or wall contact during that sample.

Try straight walking, diagonals, stopping/reversing, click-to-walk, dodge and firing while moving. Report whether the current baseline feels reasonable, too fast or too slow. This is a reference check, not approval of any candidate: there is no different candidate yet.

## Checks completed

The harness uses the existing `Game::update`, `Simulation` and renderer; it supplies a fixed empty review room and observes movement. The normal expedition executable, production source, controls, health and balance are unchanged. It opens a unique temporary save, never the ordinary campaign. Returning to the hub ends the review. No enemy, upgrade or god-mode modifier is present.

Actual Game input checks pass at 30/60/144 input-update partitions: straight and diagonal walking measure 6 world units per simulation second, with no diagonal boost. The 144 partition sample ends one fixed tick short of two seconds; actual simulation elapsed time is recorded instead of concealing that boundary. These are controlled timing checks, not a claim of rendering performance at those rates. Current stopping is immediate after release.

Existing dodge measures 20.4 world units/s: 14 boosted 60 Hz ticks, 4.76 units. Configured duration remains 0.22 s; the discrete effective duration is approximately 0.2333 s. This records the existing behavior without changing it. All eight arrow firing combinations pass, and the existing Mine/Canyon arrow, camera, strafing, short-tap and mouse-fallback checks also pass.

The native motion verifier was re-executed: all 590 bounded per-invocation states match the preserved fixture. It retains velocity after release in that code path, but does **not** establish live stopping distance, noticeable sliding, a complete player frame or a trustworthy source-to-world speed conversion. Therefore S05 is verification-first; do not add a glide effect based on this trace alone.

[Inspection image](baseline.png), measurements and logs are adjacent. The image proves rendering only; human acceptance remains pending. A later scale/frame/movement change must reopen this checkpoint.

Still unfinished: human baseline acceptance; matched live-reference movement/stopping calibration; the first explicitly selected candidate and A/B check; all subsequent stat/combat stages and the existing health/enemy acceptance gaps.

## Subsequent human feedback

The user reported that the baseline feels good but Isaac base movement is slower. This accepts the responsive reference, not native speed parity. The [S04 walking A/B candidate](../movement-review-s04-walking/README.md) now provides a 20% slower review-only option; its human acceptance and live native calibration remain pending. The historical checks and frozen executable above remain baseline evidence.
