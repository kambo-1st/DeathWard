# Baby family implementation progress

The dedicated controller now covers normal Baby, Angelic Baby, its small
offspring and Wrinkly Baby. Their health, source movement, firing events,
teleport windows and Wrinkly's committed dash replace the old generic behavior.
The original visual style and default100HP/24damage player are preserved.

The [source review](source-review.md), [native source manifest](source/manifest.json)
and [implementation review](implementation-review.md) distinguish measured
values, DeathWard conversions and remaining fidelity work. The existing source
files remain unchanged from the preceding frozen Mr. Maw checkpoint.

[Focused checks](native-lifecycle.txt) cover health, movement, projectile spread
and inherited velocity, teleport destination/collision rules, attack interruption,
Wrinkly's dash and recovery, atomic capacity handling, external configuration and
the actual Holy Mulligan child route. Four isolated fights clear with actual
movement/fire input and unchanged starting equipment. A later
[focused run](native-cadence-final.txt) adds room suspension/current global-frame
acquisition and player interception of a dash. All these checks pass.

[Passing evidence covers all89 native suites](native-summary.json). The initial
broad run passed88; its only failure was Brain's old fixed room after pool
expansion. The [actual generator search](brain-witnesses.jsonl) found its new
room, and the corrected test passes without changing its behavior assertions.

[Five unmodified seeded populations](native-residents.txt) activate for360 frames,
covering both Baby bands, Angelic and Wrinkly, with two interior rivers. The
[final Wrinkly rerun](native-wrinkly-resident-final.txt) passes after player-contact
handling changed. A further [source-driven eligibility correction](native-target-eligibility.txt)
removes the invented Wrinkly sight gate and tests acquisition behind solid cover.
The [final actual resident](native-wrinkly-target-final.txt) also passes. Native
and production WASM builds pass, with [final served hashes](served-build-final.json).

All [11 final browser cases pass](browser-summary.json): six isolated behavior/terrain
cases plus five generated populations. The initial headless run was confirmed to
use SwiftShader and stopped; windowed Chromium uses the RTX4070TiSUPER through
WSL D3D12. A first GPU run exposed the Wrinkly bug; its failure is preserved.
The final run includes the correction. This is not a controlled performance result.

Twenty-six native/browser images were [directly inspected](visual-review.json).
Separated single/triple shots and teleport phases are visible. Several captures
retain explicit foreground-terrain or camera/HUD limits. A final native Wrinkly
view using the normal player-follow camera shows both actors clearly; it does
not certify dash-motion readability. Full visual acceptance remains open.
Captured startup FPS under concurrent work is not a controlled performance test.

This is partial implementation/validation, not full acceptance. Exact native
status/control/champion behavior, recent-damage decay, RNG/grid equivalence,
hard-mode integration, full visual readability, mixed-floor balance and controlled
Linux/WASM performance remain open. The full653-record objective stays active;
regular enemies and required offspring remain the priority.

The next regular family has a [preserved Vis source review](../vis/source-review.md).
The [checkpoint](checkpoint.json) freezes evidence and build/source hashes; current
[progress](implementation-progress.json) keeps the full goal and remaining work explicit.
