# Normal-room geometry and live movement timing

**Selected step1 verified for normal shape1 geometry and ordinary horizontal base-Isaac movement timing.** A fresh read-only capture after the user focused/unpaused Isaac contains eight steady walking segments. Player motion supports about60 invocations per second while the world advances about30. No DeathWard gameplay or calibration was changed by this investigation.

## Verified native dimensions

The installed Repentance1.7.9b executable remains pinned to SHA256 `04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`.

Read-only access to the already running native game observed character0 (Isaac), cached Speed1, room shape1 and a single player entity. The snapshot reads the actual process module base and follows ASLR-adjusted Game/Manager globals separately. The first exploratory check incorrectly treated Game+8 as Manager state; that was corrected before capture. The correct Manager state is2 (gameplay). No writes, input, code injection, process suspension or game/save-file edits were performed.

| Quantity | Verified value |
| --- | --- |
| Whole room grid | **15 columns × 9 rows** |
| Native cell spacing | **40** |
| Grid centre origin | **(40,120)** |
| Interior grid | **13 columns × 7 rows**, excluding the border ring |
| Stored interior top-left | **(60,140)** |
| Stored interior bottom-right | **(580,420)** |
| Interior dimensions | **520 × 280** |
| Interior aspect ratio | **13:7**, approximately1.857:1 |

`live-room-snapshot.json` contains the actual room fields. The native grid-path coordinate arithmetic at7a4687..7a46b5 was executed for all **135** grid positions. Interior-cell centres plus/minus half a native cell exactly reconstruct the observed bounds. The full ordinary room clamp at7cec10 executes against the observed fields in **14** cases with zero and10.5 margins. `geometry-manifest.json`, `native-grid.csv` and `native-clamp.csv` preserve the results. This proves the observed ordinary room geometry and those bounded helper operations; it does not prove all room shapes, the full room generator or player wall/corner collision.

## Concrete DeathWard mismatch

The current private review's logical interior is24×24, a square. Matching its width to native520 would require scale24/520, while matching its height to280 would require24/280. These differ, so **no single isotropic spatial conversion can make that square an equivalent normal Isaac room**. Camera projection does not resolve a logical aspect-ratio mismatch.

DeathWard's existing `FloorTile` is2 (`src/world/Dungeon.hpp`). One possible common geometric anchor for the next selected integration would therefore be one native40-coordinate cell to one existing floor tile, yielding a26×14 ordinary reference interior. This is a derived mapping option, **not an enabled room, player-speed or collider change**. It does not justify assigning native coordinates a guessed metres-per-second value.

The earlier movement review instead anchored its scale to the manually accepted walking pace. That remains an adaptation and cannot establish source room-crossing time. Its native per-invocation player curve remains useful bounded evidence, but the square room and accepted-pace anchor prevent a complete spatial-fidelity claim.

## Active live walking: current result

After the user replied ready, a fresh120-second read-only capture recorded **7,705 samples**, including eight unimpeded horizontal passes at cached Speed1, character0 (Isaac), native time scale1 and friction1. The later idle/paused portion is not treated as active gameplay. See `live-walking.csv`, its metadata, `live-walking-analysis.json` and `live-walking-segments.csv`.

The longest selected steady segment lasted **1.21594 seconds**, moving **322.1349 native coordinates** (about8.05 cells), with79 samples. Fitted values are:

| Observed quantity | Longest steady segment |
| --- | ---: |
| Native cached velocity, mean | 4.412842 coordinates per player invocation |
| Position change fitted against real time | 264.274 coordinates per second |
| Effective motion frequency from position/cached velocity | **59.8875 invocations per second** |
| Outer phase fitted against real time | **59.8385 per second** |
| World counter fitted against real time | **29.9175 per second** |
| Motion invocations per outer phase | **1.00015** |
| Source cells traversed per real second | **6.60685** |

Together with the independently executed native recurrence, this supports the ordinary **60Hz player / 30Hz world** timing basis in the captured session. This conclusion uses actual position change and elapsed timestamps; it is not inferred solely from the outer phase counter. The eight individual short/long estimates range57.76–60.33 motion invocations per second, with median59.72. Short intervals, discrete updates, sampling and delivered frame timing cause variation; no claim of exact60.000Hz wall-clock delivery is made. The full capture rate is roughly64 samples per second.

At fitted steady speed, `520 / 264.274` is approximately **1.97 seconds per complete logical room width**. That is a **derived steady point-traversal equivalent**, not a measured trip from rest between collision walls. Acceleration, player radius and wall/door clearance must be treated separately. Actual input-release timestamps were not logged, so the recording does not certify live stopping distance. Vertical live walking and other room shapes are not directly sampled here.

The earlier accepted walking pace and square review geometry are therefore not the authority for source speed. This investigation supplies an independent native geometric/timing reference for the next spatial integration. No speed selector or subjective retuning was required.

## Earlier paused captures: retained negative evidence

`read-live-motion.ps1` opens the existing native process with `VM_READ|QUERY_INFORMATION` only. It verifies the executable hash and records a monotonic high-resolution Stopwatch timestamp, actual Manager phase, Game frame counter, source position/velocity/friction/time scale and cached Speed. Reads crossing a phase/frame boundary are excluded from stable-segment analysis. The Windows sleep resolution produced roughly64 samples per second in the first capture; no higher sample rate is claimed.

The first120-second capture has7,721 rows. The outer phase advanced at approximately **60.09 phases per real second**, but Game frame count stayed519 and position stayed approximately(569.5522,308.1885). It contains **zero active walking segments**. Therefore it verifies an advancing outer loop with frozen gameplay, **not effective player movement frequency or room-crossing time**. See `live-paused-analysis.json`. The initial requested user action to start a new game was superseded: the existing room/character are suitable; only focus/unpause and walking are needed.

The subsequent300-second bounded capture also remained at Game frame519 with no movement (19,269 samples, approximately60.14 outer phases per second). Both recording processes finished. See `live-followup-paused-analysis.json`. Neither capture establishes active player timing. An active sample requires focus/unpause and walking in the existing suitable game; no new game is needed. Until that sample exists, do not multiply a cached velocity by60 and call it a measured wall-clock speed.

`analyze-live-motion.py` fits unimpeded steady position against actual timestamps and reports the ratio of displacement rate to native cached velocity. This can discriminate30 versus60 effective motion invocations without assuming that the outer loop is the player clock. Seven analysis tests pass, including paused/idle rejection, wall rejection, phase-crossing rejection, rejection of motion without Game-frame progression and discrimination of known30/60 synthetic controls. Those controls test the analyzer; they are not native observations. Exact input-release timestamps are not recorded, so this capture does not accept live stopping behavior.

## Reproduction and next gate

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-room-geometry.py --check
python3 -m unittest discover -s tests/isaac_reference -p 'test_live_motion_analysis.py' -v
python3 scripts/isaac-reference/analyze-live-motion.py CAPTURE.csv --output ANALYSIS.json
```

The PowerShell reader must run on Windows while the pinned game is already open. Use a new output file and a bounded duration. For a valid active sample, focus/unpause the existing empty room as base Isaac at Speed1, walk left/right and release a few times. The reader sends no controls. No new expedition or save reset is required.

Still unfinished: measured full wall-to-wall/from-rest trips, native player collision clearance and exact live release-to-stop behavior; direct vertical live motion and other room shapes. Applying a shared conversion to the review is the subsequent integration step, not part of this geometry investigation. Full NPC phase/AI behavior, enemy projectiles, production rollout and damage/HP acceptance remain open.

## Subsequent private integration

[The geometric room review](../source-room-review/README.md) now applies one source tile per existing floor tile in a13×7 interior. It uses the native player curve and selected NPC conversion, with native traces and live pace checks. This does not complete collider/NPC/projectile acceptance or enable production rollout.
