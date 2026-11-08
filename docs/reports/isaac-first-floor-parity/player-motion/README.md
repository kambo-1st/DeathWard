# Installed 1.7.9b ordinary player motion

The source executable SHA-256 is pinned in `manifest.json`. The generator reads the installation and maps its original PE code into Unicorn 2.1.4, with separate synthetic player/stack memory. It does not launch or modify the game, patch instructions or replace helpers with mocks. Native square root, vector normalization and empty item queries execute unchanged.

Reproduction from the repository root (Python dependencies may be installed in a dedicated environment):

```sh
python3 -m pip install --target /tmp/deathward-native-emulator unicorn==2.1.4
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-player-motion.py --check
```

`pefile` and `capstone` are also required, as in the existing native evidence scripts. Emulator API usage follows the [official Unicorn tutorial](https://www.unicorn-engine.org/docs/tutorial.html).

The 590 trace rows cover seven sequences: starting/stopping, normalized diagonals, reversal, cornering, analog input and speed-stat values 0.8 and 2.0. The separately recorded inheritance examples include forward, transverse and opposing movement. The C++ checks compare against the executed x86 output, not a second handwritten version of the formula.

Ordinary motion first scales normalized input by `0.25 * Speed + 0.75`. Its perpendicular velocity component has a separate damping step. Acceleration depends on the existing component along the input; final retention is `sqrt(0.775)`. Releasing input therefore retains stopping inertia. Tear inheritance uses 1.2 times the previous invocation's velocity and removes only the component opposing the shot.

Scope: ordinary grounded, no-items/no-status/no-ice physics **per native invocation**. Earlier control and character branches, presentation-facing angles, later item actions, collision, scheduler cadence and room scale are outside these traces. No full-game wall-clock or geometry parity is certified.

The earlier 30 Hz player adapter is superseded in `isaac-baseline-v18`. [Update-phase evidence](../update-phases/README.md) establishes the ordinary extra player update in both interpolation modes and adds 590 coupled bounded physics/motion/counter states. Runtime player movement now advances at 60 Hz, moving incoming velocity before steering prepares the next update; all 590 positions/velocities and hurt counters pass the world integration comparison. The .1 spatial conversion, full Player-update branches, collision and matched live timing remain unaccepted. NPC/tear/bomb clocks stay 30 Hz, with inherited/target velocity converted to their own units. Universal dodge keeps its 3.4 boost multiplier and immunity.
