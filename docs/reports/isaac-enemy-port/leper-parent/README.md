# Leper parent family — Repentance 1.7.9b

This slice adds the four exact parent forms `310.0.0`–`310.0.3` to the existing
Leper Flesh implementation. These remain **in progress**, not fully accepted
ports. The implementation uses the installed native controller and shared damage
helpers, rather than interpreting the wiki's simplified HP-threshold description
as the complete algorithm.

## Source evidence and damage order

The [preceding family investigation](../leper/README.md) preserves the complete
parent controller, Flesh controller, five animation metadata files, installed
entity records and source room presence. Its checkpoint and validation reports
are historical. This slice adds [five bounded source windows](source/manifest.json)
and hashes the shared evidence it relies on. Reproduce the extra evidence with:

```sh
python3 scripts/isaac-reference/analyze-leper-parent-order.py --check
```

The complete NPC damage forwarder calls the base damage queue. Ordinary NPC AI
then runs before the shared entity update subtracts queued damage. Leper predicts
`currentHP - sum(queuedDamage)` and repeatedly compares it with
`(3 - subtype) * maxHP / (4 - subtype)`. Each crossing increments the subtype and
emits a Flesh enemy. **The loop retains the old maxHP.** Only after all crossings
does Morph reload the subtype's maxHP and clamp current HP. Shared friction and
translation run before queued HP subtraction. The damage queue stops at the first
lethal ordinary hit.

Examples below use native HP, starting from intact 60 HP. These are explicit
calculations from the instructions, not measurements from running the original
game:

| Accepted hits in one source frame | New subtype | Remaining HP | Shed pieces |
| --- | ---: | ---: | ---: |
| 14 | 0 | 46 | 0 |
| 15 | 1 | 30 | 1 |
| 20 | 2 | 10 | 2 |
| 10 + 10 | 2 | 10 | 2 |
| 20 + 20 | 3 | -5 before death handling | 3 |

Two 10-HP hits in **different** source frames instead leave subtype two at
20 HP. For the 20+20 same-frame case, the second subtraction is discarded after
the first lethal hit. A successful Gusher morph must not receive that remainder.
DeathWard retains accepted events and their item-chain ownership across split
30/60-Hz frames, room suspension and capacity pressure. Form changes pay no kill
or loot. Execution bypasses ordinary queued damage; debug room clear suppresses
offspring and cancels retained damage.

The split-frame regression initially found early child admission: a 60-Hz half
update could spawn and move Flesh before the corresponding 30-Hz source frame
finished, changing collision-aware placement around the parent. Birth choices
now remain staged until that frame completes. The retained failing log and final
all-four-child position comparison document the correction.

## Movement and mortality

The four forms have native base HP 60/45/30/15, no stage-HP term, and chase forces
`.5/.5/.7/.9`. DeathWard applies its established HP multiplier of 3.2. Only intact
subtype zero is harmless on contact. Earlier forms alternate shared proximity
evasion and pursuit. A far-enough, non-resting form has a one-in-ten source-frame
chance of starting a 90-frame chase. Finishing a chase assigns a 30–89-frame
rest. Positive chase time loses `ceil(2 * queued native damage)` on damage.
The last form pursues regardless of its rest counter. Form changes have a
nine-frame transition with `.8` velocity retention. Chase has the shared ground
pathfinder friction and an additional `.9` retention.

The last form lays small red creep every ten staggered source updates. Its
active lifetime is 30 frames, followed by a 40-frame shrinking fade. DeathWard
uses radius `.4`–`1`, damage `10` before the game-wide multiplier, and the common
creep collision system. Earlier damaged forms produce cosmetic blood only.
Already reserved creep survives a full hazard queue, death and room suspension.

Every ordinary final death emits another independent Flesh enemy. Residual HP
strictly above native `-25` also allows a 50% **same-entity** Gusher morph. That
restores full Gusher HP and assigns a 20–39-frame initial shot timer. The source
headless controller only special-cases state zero; inherited transition state
does not freeze it. DeathWard preserves identity and momentum, uses a scarred
gray body treatment, and does not issue a parent kill for this morph.

Live shedding launches Flesh away from the player with a ±45° spread, native
speed 5–10 and offset 20. Final death uses a random direction and speed 2–4.
The world conversion is speed ×3 and distance ×.1. Offspring remain independent
of parent lifetime and retain room completion while awaiting enemy capacity.
The existing Flesh controller supplies contact consumption and its predictive
death shot. Required terminal offspring are not silently dropped at the ancestry
safety limit.

## Configuration, placement and visuals

`assets/mechanics/leper.mechanics` exposes all four `monster`, `stage_health`,
`leper`, `leper_evade`, `leper_creep` and `encounter` records. Validation requires
all compatible forms, both required child controllers, complete movement/creep
profiles, and exclusive staged-damage ownership. Reload creates a new immutable
mechanics snapshot; active snapshots retain their values.

Each form has a sparse final-band specialist pool entry, capped at one per form
per room. Source Scarred Womb templates support that eligibility; the weight and
cap are DeathWard balancing decisions, not a reproduction of source room odds.
The separate natural Flesh pool remains enabled. Procedural low-poly tissue
lobes disappear as forms advance, with exposed dark wounds, a short transition
shake and a distinct gray Gusher body. No source sprite art is imported.

## Validation and limits

The [native summary](native-summary.json) records build/test results, actual
seeded placement witnesses, starting-kit encounters and artifact hashes.
[Native captures](native/captures.json) and the [visual review](visual-review.json)
separately record the inspected rendering evidence. Source-frame damage batching,
retained offspring, delayed creep, same-entity mortality and immutable external
reload have focused regressions. Shared evasion, headless behavior and floor
generation also have regression coverage.

The conversion retains DeathWard's 3D collision/navigation, Original visual
style and immediate mortality after a completed damage frame; it does not claim
pixel-perfect collision or original death-animation latency. Native champion,
status/control and item-specific interactions, serialized-state parity, broader
human visual/balance review and controlled performance acceptance remain open.
The original Isaac executable was statically analyzed, not executed as an oracle.
WASM builds and checks are skipped under the user's explicit instruction.
