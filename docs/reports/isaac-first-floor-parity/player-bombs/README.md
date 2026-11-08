# Ordinary inventory bombs: enabled baseline adapter, full actor acceptance open

Target: installed Repentance 1.7.9b, ordinary Isaac, empty inventory. Graphics and universal dodge (movement boost and immunity) remain accepted exceptions. This checkpoint is `isaac-baseline-v12`.

## Executed research

`scripts/isaac-reference/analyze-player-bombs.py` pins the executable hash and executes its original bounded instructions in Unicorn. There are no replacement calculation, RNG or math hooks. [manifest.json](manifest.json) records the exact scope, instruction windows and source XML fingerprint.

- **48 initializations:** eight bomb variants and six nonzero InitSeeds. Actual `Entity::Init` copies InitSeed into the entity RNG and initializes shifts **4/3/17**. Bomb initialization supplies ordinary countdown 45, damage 100 and radius multiplier 1. Troll variants 3/4/8/18 consume one RNG word and add its unsigned remainder modulo 30. Variant 15 supplies 94/20; variants 17/20 supply 87/300. Special variants are research, not enabled gameplay actors.
- **82 countdown cases:** absent modifiers, a positive countdown decrements; entry with zero or less proceeds to the explosion path. Ordinary 1→0 does not itself enter that path. The later global collectible-63 branch and remote/freeze conditions are outside this capture.
- **Six inherited velocities and 72 free-motion states:** ordinary inventory placement takes **0.1 times the player's current velocity**. Original base physics then moves the body with friction 1 and timeScale 1. XML independently supplies collision radius 16, mass 6 and friction 1. Unobstructed C++ world motion is compared at the current .1 scale.
- **Placement cooldown:** the ordinary inventory path sets counter 30. It spawns entity type 4 and decrements ordinary bomb stock unless the golden/other override is active. `inventory_placement.asm` preserves the caller. This is separate from `Player.FireBomb`, whose weapon-bomb defaults must not be substituted for inventory placement.
- **12 base-radius cases:** damage ≤140 selects radius 75, 140<damage<175 selects 90, and damage ≥175 selects 105. `radius_application.asm` preserves subsequent radius-multiplier application and the BombDamage call. Special bomb flags can change this path and remain outside the adapter.
- **21 incoming-player amount cases:** for admitted positive damage, the final player branch selects two half-hearts for blast damage ≥85, otherwise one; damage flag `0x10000000` selects one. Earlier eligibility/flag changes, character/item overrides and actual native TakeDamage are not established by this slice. The zero input row describes this slice only; the caller excludes nonpositive blasts.

The initializer capture does not execute the entire constructor, configuration loading or visual setup. Supplied InitSeed mapping is verified locally; native global spawn RNG selection is not. These findings are not a whole native actor trace or a measurement of elapsed native seconds.

## Enabled gameplay

Standard Canyon expeditions using the Isaac baseline now place ordinary inventory bombs at the player's position. Aiming no longer creates the custom ballistic throw, and the throw/place toggle is hidden for this baseline. Both placement entry points use the same actor. Legacy dynamite, supplied bombs, hostile custom bombs and universal dodge retain their separate behavior.

The actor uses countdown 45 and enters its blast on source invocation 46. At the existing 30 Hz adapter this is 92 fixed simulation ticks; the 30-count placement cooldown is 60 fixed ticks. These are **adapter timings**, not accepted native wall-clock durations. Blast damage is 100 and world radius is 7.5 at the current .1 scale. Player self-damage is two half-hearts, passed as 20 units through the existing ten-units-per-half incoming adapter. Ordinary native velocity inheritance replaces the aimed arc. The arena supplies planar grid movement; the old scripted kick/lift is excluded for these source actors.

A ready bomb is retained when explosion admission fails because the event queue is full. It emits one blast after queue capacity returns. Chain/depth limits retain their existing safeguards. Gold-bomb inventory admission and stock preservation still apply. The baseline's ordinary adapter does not apply the custom Braid bomb transformation; complete source item modifiers remain unfinished.

## Validation and remaining work

`native_player_bombs` compares all recorded numerical outputs and the 72 world free-motion states. Integration checks cover stock, cooldown boundaries, the 46th invocation, self-damage exactly once, queue recovery, retained dodge activation/boost/immunity and legacy isolation. **All 22 selected suites pass**; see [validation.json](validation.json) and [selected-tests.log](selected-tests.log).

Two graphical inspections were viewed. [Before detonation](before.png) at frame 75 retains six half-hearts and one bomb actor. [After detonation](after.png) at frame 120 has four half-hearts, zero bomb actors and stock 2 after starting with 3. God mode is disabled. The custom Canyon room/visuals and existing unrelated coin piles are not source layout/reward acceptance.

Reproduce the after inspection with a separate campaign file:

```sh
build/deathward --smoke --scene player-bombs --theme canyon --frames 120 \
  --save /tmp/deathward-player-bombs-inspection-save.json \
  --screenshot /tmp/deathward-player-bombs-inspection.png
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-player-bombs.py --check
ctest --test-dir build -R '^native_player_bombs$' --output-on-failure
```

**Unfinished:** native scheduler/live timing, full entity-contact pushing and collision impulses, calibrated grid/recipient sizes and 2D/vertical eligibility, complete explosion damage flags and knockback, callbacks/familiars/items/characters, remote/freeze/appearance lifecycle, room travel/persistence, troll/super/golden troll/giga actors and conversion from resource pickups, and production source reward generation. Troll pickup subtypes are still refused rather than turned into ammunition. The ordinary bomb is enabled within this scope; **full bomb acceptance and all six broad parity areas remain open**.
