# Additional installed-source review

The earlier [source preflight](source-review.md) is preserved unchanged. This
review adds the flight contract and records armor findings without claiming an
armor implementation. [Bounded source windows](flight-armor-source/manifest.json)
pin the installed Repentance 1.7.9b executable.

## Projectile flight

At `515f42`, the landing parameters add −.07 to falling acceleration. The
parameters skip the generic mode adjustment (`6a3059`); initial height remains
−23, falling speed is `(uniform−.5)*.2`, and initial acceleration is zero.
The common ordinary-time update is `speed = .9*speed + .1 + acceleration`,
then `height += speed`. Thus the net acceleration term is .03, not zero.

DeathWard uses the previously reviewed physical-flight adapter: planar distance
×.1 and upward height ×−.05. The external ring configuration therefore sets
height1.15, upward speed−.15..+.15, gravity1.35 and retention.9. Two60Hz steps
match each native30Hz height/velocity endpoint. Planar speeds remain24/30/24/30.
World collision uses actual floor and swept spheres instead of native2D grid
height thresholds. The local six-second safety lifetime and radius.18 are
authored. Already emitted physical shots survive the owner and hold local room
completion until their impacts/expiry; no explosive payload is added.

## Adaptive armor: verified research, runtime still pending

Installed NPC initialization sets shield strength at `+b90` to0 and window size
at `+b94` to120. Configuration fields `+e0/+e4` populate these fields.
The normal NPC update calls `6adfd0`. Unlike later public structure layouts,
this binary does not place shield strength at `+c40`.

The function appends the current pending-damage batch to a rolling history,
including zero-damage frames. Flag0x2000 is excluded. It trims the oldest entry
at the configured window size, then calculates recentDPS as the history sum
divided by its **actual entry count**, multiplied by30. The current hit batch is
included before scaling. Soft cap is the current body's maxHP divided by shield
strength (30 for Tainted Hopper). If recentDPS exceeds this cap, with
`r = cap/recentDPS`, the multiplier is `r + max(.09 − .18*r, 0)`; otherwise1.
Each pending hit is scaled except flags masked by0x40002000, and the batch total
is recomputed. Parent-owner selection exists and needs separate component tests.

The installed [DamageFlag excerpt](flight-armor-source/damage-flags.lua), pinned
by its [provenance](flight-armor-source/damage-flags-source.json), names0x2000
`DAMAGE_INVINCIBLE` and0x40000000 `DAMAGE_IGNORE_ARMOR`. The former bypasses both
history and scaling; the latter still contributes to history but bypasses scaling.
`DAMAGE_FAKE` is a different bit (1<<21); do not confuse it with0x2000. Producers
of IGNORE_ARMOR, especially explosive versus item damage, still need tracing.

The archived wiki also describes initial protection and a large-hit adjustment.
Those claims have not yet been tied to this installed version's call path.
Do not invent them or turn the verified adaptive formula into a flat reduction.
Remaining implementation work: source30Hz damage batching in DeathWard's immediate
event pipeline, bypass flag mapping, initial-protection/version reconciliation,
large-hit behavior, status ordering, suspension and overflow tests. This shared
dependency stays in the **regular-enemy** queue because several Tainted regular
enemies require it. Tainted Hopper is not vulnerability-complete without it.
