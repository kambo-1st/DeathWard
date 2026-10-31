# Tainted Pooter: regular-enemy implementation slice

Tainted Pooter (`14.2.0`) now uses the shared buzzing controller and its own
four-shot attack, replacing the generic chase/spread placeholder. Physical
impacts create two smaller shots travelling backward. This is a partial port:
its dedicated Ascent-equivalent encounter and broader acceptance gates remain
unfinished. It has **not** been added to ordinary expedition floor pools.

## Source and behavior

The [source review](source-review.json) records installed Repentance 1.7.9b
executable evidence, the extracted XML and animation metadata, pinned wiki
revision 266767, and the API name for projectile flag `BACKSPLIT`. The
[extractor/checker](../../../../scripts/isaac-reference/analyze-tainted-pooter.py)
verifies the executable hash before reading the same disassembly windows.
No Isaac sprite artwork was imported.

| Property | Installed evidence | DeathWard implementation |
|---|---|---|
| Health/contact | 75 HP, zero touch damage | 240 HP using the established ×3.2 conversion; harmless touch |
| Movement | Shared Fly/Pooter buzzing and cooldown friction | Shared 30 Hz controller with physical flight |
| Acquisition | Check every 7 source frames, range 200, sight required | Same cadence, local range 20 |
| Attack | Delay 63 from acquisition; Attack 14; Shoot event 6 | Configurable timing; current target sampled at Shoot |
| Four-shot volley | Mode 4, spread 1.2, scale 1.4 | Four unnormalized velocity vectors; root radius .308 |
| Inner pair | Forward .99, side ±.139 × 1.2 | (.99, ±.1668) × local base speed 21 |
| Outer pair | Forward .914, side ±.407 × 1.2; both ×.9 | (.8226, ±.43956) × 21; slower outer shots |
| Terminal impact | Two backward children at ±24°, source speed/offset 10 | Speed 30, offset 1, radius .22; no recursive splitting |
| Player hit | Native collision sets the same dead-processing flag | Splits on player impact as well as solid scenery |
| Skatole | Shared type-14 suppression branch | Stops shooting, keeps buzzing; item remains unpooled |
| Placement | Ascent-only | Dedicated route pending; ordinary pools unchanged |

The earlier split implementation emitted forward children on any termination,
including timeout. Splitting now requires an actual terminal collision. A live
bounce, timeout or explicit cancellation does not trigger it. Released shots
retain their source identity after the owner dies.

The reusable external `buzz_volley` row supplies forward/side coefficients;
`buzz_back_split` supplies root radius, backward angle, child speed, damage,
radius, offset and lifetime. Invalid combinations are rejected. Existing
simulations and already-emitted projectiles retain immutable configuration
snapshots when files are reloaded.

Four roots and each two-child split must fit as a whole. A saturated impact
retains one stationary carrier and retries when capacity returns. Its damage
is not repeated. Child spawn offsets are clipped against intervening scenery.
These are explicit bounded-runtime and physical-3D adaptations.

## Validation

All **66 native CTest suites pass** in the [final run](native.xml).
The [focused behavior log](behavior-final.txt) covers timing, the real volley,
owner death, physical impacts, capacity retry, thin-wall clipping and immutable
reloads; [shared buzzing regressions](buzz-regression.txt) also pass.
The timing test exposed a float residual that delayed reacquisition by one
seven-frame interval; this was fixed before the final builds. The old monster
fixture was corrected to reject splitting on safety timeout.

All **five WASM cases pass** with no browser/GL errors in the
[final browser report](web/results.json). They use production mechanics and
cover volley coefficients, physical size/pitch, backward splitting, cover,
river, Skatole and death. The initial seven-second river observation ended too
soon; the extended observation saw the slow actor return to land at frame 475.
The [initial evidence](web-initial-run.txt) is retained. No runtime change was
needed for that observation-window correction.

[Linux volley](native-volley.png), [Linux scene after cover crossing](native-cover.png),
[browser volley](web/tainted-volley.png) and [browser river flight](browser-river.png)
were inspected. Displayed FPS is not a controlled benchmark.
The [checkpoint](checkpoint.json) freezes the exact runtime, build and evidence
hashes. All 5,238 previously recorded report artifacts checked remain unchanged.

## Remaining work

Native projectile height/falling curves are **not** reproduced yet. Roots use
DeathWard's physical aim, and children travel horizontally at impact elevation.
The extracted native falling-speed/acceleration parameters are preserved for
follow-up. Five-second lifetime is a local safety cap, not a claimed Isaac timer.

Natural Ascent-equivalent reachability, full status/control and Skatole behavior,
exact animation/integration parity, wider build/encounter balance, all-angle
readability and controlled rendered performance remain open. This slice does
not certify a completed enemy. Regular enemies and their required dependencies
remain the priority; further boss/Hornfel work stays deferred.
