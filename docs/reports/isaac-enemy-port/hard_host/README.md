# Regular enemy port: Hard Host

Hard Host **27.3.0** now uses its armored slam and physical rock-wave attack,
replacing its generic bullet attack. This is a partial normal-state port, with
remaining parity and acceptance work recorded below. Regular enemies and their
required offspring remain the priority over additional bosses.

| Property | Implemented behavior |
| --- | --- |
| Health | 15 source HP × 3.2 = 48 local HP |
| Armor | Closed except between source animation frames 10 and 54; shared Host hit-delay and Burning exception |
| Attack | Slam at Close54; no regular bullet volley; animation ends at frame 71 |
| Rock wave | Starts 2 units forward; steps 3 units every two source frames; gradually wanders after frame 6 |
| Nearby player | Strict 12-unit range; physical hop and outward impulse, then landing |
| Crush pulse | 32 NPC damage / 10 base player damage; distinct from fire and bomb damage |
| Terrain | Breaks eligible cracks, dung and cache entrances; can trigger powder barrels; stops at collision or pits |
| Placement | Ordinary specialist in progression band 1, cap one; Mines/Ashpit analogue |

Band 1 is a progression category, not necessarily the second floor. This does
not change the Mine roster, tutorial, hubs, expedition length or player defaults.
The external values are in [hosts.mechanics](../../../../assets/mechanics/hosts.mechanics).
The new `host_slam` row is validated and supports immutable configuration reload.

The original stone cap, exposed stem and small traveling rock crests use the
existing Original rendering style. No source artwork was imported. The hop uses
actual player height while horizontal navigation stays grounded, so it does not
grant a route over walls or pits. Emitted waves survive owner death and room
clear; leaving the room clears them. Capacity pressure retains a whole pending
slam or pulse, including its RNG state.

## Evidence

- [Source review](source-review.md) and [six native instruction windows](source/manifest.json)
  pin the installed Repentance 1.7.9b executable, effect dispatch, damage helper
  and player-launch method. The latter establishes a hop, not just flat knockback.
- [Targeted native test](native-targeted.txt) covers armor/events, live aim,
  damage, deterministic stepping, terrain, hop recurrence/landing, lifecycle,
  capacity limits, external configuration and natural placement.
- **77 unique native suites pass**, combining the [full run](native.xml) with
  the [corrected Crackle placement test](crackle-corrected.xml).
- **Three production WASM cases pass**: nearby, distant and naturally generated
  Hard Host. [Browser results](web-final/results.json) contain sampled states,
  captures and zero page/GL errors. The natural case also emitted a wave and
  launched the player during observation.
- [Eleven inspected images](visual-review.json): four Linux and seven WASM.
  Static appearance is checked; full combat readability and performance are not
  certified from screenshots or their FPS counters.
- [Natural witness](witness.json): Rourke account, seed 1, zero-based floor 2,
  room 3. For an interactive isolated preview: `./build/deathward --smoke
  --theme canyon --style original --scene enemy-27.3.0 --frames 100000`.
- [Historical integrity](historical-integrity.json) pins 6,347 earlier report
  files. They remain unchanged; [checkpoint.json](checkpoint.json) freezes this
  slice's final runtime, build, source and evidence hashes.

## Corrections retained in the evidence

The initial pit test modified visible floor strips while leaving the collision
grid intact. Its corrected fixture sets the collision grid; the test now passes.
The initial WASM build failed because new probe object literals contained commas
outside parentheses in `EM_ASM`. Parenthesizing those literals fixes compilation;
the subsequent production build and all browser cases pass. Compressed assets
were refreshed and verified by decompression.

The full native run passed 76/77 suites. Adding a specialist changes seeded pool
draws: Crackle was absent from the previous 30-seed witness window. Its bounded
search now permits 256 seeds and finds **seed 61, floor 1, room 4**, with the
expected 128 HP and Standard band-1 placement. The corrected suite passes; no
Crackle runtime behavior or pool weight was changed. Original failure logs are
preserved.

## Remaining

Native special statuses, champions/control branches, item transformations and
all grid/NPC immunity exceptions are not fully reproduced. Exact source RNG
ordering, age-zero generator ordering, crush mass/knockback physics and player
friction/control exceptions remain open. Local swept terrain tracing, resource
gate protection, normal movement during the hop and seeded per-wave RNG are
explicit adaptations. Placement weights are authored, not native probabilities.

Full balance, combat readability and controlled Linux/WASM performance acceptance
remain open. This raises the maintained total to **120 in-progress records**, with
**zero fully certified complete ports**. Mushroom and the remaining regular
roster follow; the full goal remains active.
