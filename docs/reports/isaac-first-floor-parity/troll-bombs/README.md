# Troll actors and corrected grounded bomb motion

Target: installed Repentance 1.7.9b, ordinary Isaac, no items/statuses/mod callbacks. This is the `isaac-baseline-v14` checkpoint. Graphics and universal dodge (including movement boost and immunity) remain accepted exceptions. **Full actor and broad parity acceptance remain open.**

## Native execution and correction

`scripts/isaac-reference/analyze-troll-bombs.py` executes the original **whole Bomb::Update**, its base physics, actual one-player target selection and native sprite selection/restart/frame/event code. Animation metadata comes from the highest installed DLC overrides, with archive hashes/checksums; no sprite artwork or render layers are imported. Original local x86 UCRT `floor`, `nextafterf`, sine and cosine exports execute in the emulator. [manifest.json](manifest.json) identifies the executable, DLL, metadata, instruction windows and exact fixture limits.

Only the external Audio::Play and Game::BombExplosionEffects endpoints are intercepted. They record requests; explosions leave the supplied target health/world unchanged so later updates can be measured. **Explosion recipient work does not execute in this fixture.** Steering, RNG, damping, fuse, animation, post-explosion reset and removal decisions inside Bomb::Update remain native. Configuration/active flags are explicit fixture inputs; this is not an entire constructor, game process, grid or live-clock capture.

[native-updates.csv](native-updates.csv) contains **11,184 update states across 96 cases**, for ordinary 0, troll 3, super troll 4 and golden troll 18. Four InitSeeds and six velocity/target configurations cover damping thresholds, super range/prediction, appearance, ordinary removal and repeated golden explosions. [native-blast-requests.csv](native-blast-requests.csv) records 162 blast requests; [native-sound-requests.csv](native-sound-requests.csv) records 156 sound requests. All recorded C++ fields match; maximum numeric motion difference is **zero** in this matrix. This does not prove all inputs, modifiers or external effects.

**Correction to v12/v13 world movement:** the earlier 72-state free-motion fixture executed base physics alone. Whole Bomb::Update subsequently multiplies grounded velocity by **0.95**, then by **0.5 again if squared damped speed is below 1**. Movement happens before this damping; countdown and super steering happen afterward. The old bounded capture is still valid for base physics, but did not prove complete bomb flight. The ordinary player-bomb adapter now applies the missing damping, and [288 whole-update grounded states](native-grounded-motion.csv) replace its earlier base-only world-motion comparison. The v13 contact arithmetic remains independently valid; its reported world push/coasting behavior was incomplete without this damping.

## Measured actor behavior

- Ordinary troll initialization uses 45 + one entity RNG word modulo 30 countdown units. Entity initialization copies the supplied InitSeed and sets shifts 4/3/17. The countdown runs through the 35-frame Appear animation; its landing sound occurs at frame 25. Pulse frames then follow the current fuse. Zero is an explosion entry on the next update, as for ordinary inventory bombs.
- Super troll uses the same fuse/animation and damping. After movement/countdown it predicts the selected player's position using five velocity units, accelerates toward it by 1.5 within squared range 72,900, then multiplies velocity by .8. Before age 20, it also prepares .8 friction for the next base-physics invocation. Actual native target selection executes with one supplied player; complete co-op/eligibility enumeration is outside the capture.
- Golden troll reactivates after each explosion. It draws a new entity RNG countdown of 60–89, restarts Appear at frame 8 and draws speed in [5,10) plus a hashed random direction. The direction helper applies shifts 3/1/14 to its supplied word before native trig; it does not consume another entity RNG word. Three stored RNG advances occur per reset. The recorded 90-count repeat timer is decremented afterward. Grounded damping applies to subsequent movement. Native repeated state continues through 300 updates per golden case.
- Standard and super actors enter their five-frame Explode animation and then call native Remove. Ordinary variant 0 has a one-frame Explode animation. These post-blast states are part of the native comparison; the world adapter uses its existing explosion visual and removes single-use hazards after blast admission.

[native-spawn-rng.csv](native-spawn-rng.csv) separately executes original global MT initialization and **4,200 words**, spanning the 624-word twist boundary for six seeds. `std::mt19937` matches all words. This proves the represented generator arithmetic, **not the expedition seed mapping or complete shared global RNG call order**.

## Enabled gameplay

`spawnSourceResource(40, subtype, position)` now converts **3→troll 3**, **5→super 4** and **6→golden troll 18**, following the [42 native conversion intents](../bomb-contacts/native-troll-conversion-intents.csv). It selects a new spawn seed from the MT adapter, preserves position and starts with zero velocity. These are actors, never collectible ammunition. The ordinary/double/golden inventory bomb resources remain separate. Direct `spawnSourceTrollBomb` is also available for inspection with an explicit nonzero InitSeed.

Typed pending requests retain variant, room, position and selected seed under hazard-capacity pressure. Admission retries do not draw another seed. The MT adapter is seeded from the low 32 bits of the expedition seed and carried across floors; this mapping is an explicit adaptation. Other source producers have not all migrated to that shared generator. A zero drawn InitSeed is retained unresolved rather than silently remapped or rerolled; the native zero-seed protocol still requires research. Neither pending actors nor this RNG state have complete save/resume acceptance.

All three actors use their measured update controller at the existing 30 Hz/.1 world conversion. The arena supplies movement, room containment, grounded contact and blocked-component handling; **native grid samples, bounce response, vertical eligibility and scheduling are not accepted**. Source ordinary player contact uses the previously verified circular-body kernel. Standard/super explosions are single-use; golden explosions continue until room exit/cleanup. Room clear preserves active troll hazards. Each timed explosion starts a separate damage-event root, avoiding lifetime chain-budget exhaustion for a persistent golden actor. Queue pressure pauses the logical actor until its one pending blast is admitted, preserving RNG and preventing catch-up explosions.

Blast requests use damage 100, native base radius 75 and the current 7.5 world conversion, with two incoming player half-hearts through the existing damage adapter. Enemy/familiar recipient rules and flags still need full native verification. Existing enemy/boss ordnance producers continue to use their current adapters; **general production source room rewards/layout spawning remain disabled**. Lost Survey, Mine/Classic legacy launches and their ballistic dynamite behavior remain separate. Starting player/balance defaults and the regular-enemy HP multiplier are unchanged.

## Verification and remaining work

**All 24 selected suites pass**, including 11,184 whole-update states, 4,200 MT words, 288 corrected world-motion states, resource conversion/stock, super chasing, golden repetition, actual room-clear preservation, actor-capacity recovery, blast-queue recovery without rerolls/catch-up, independent repeat roots under a one-event chain budget, retained dodge and legacy isolation. The native capture and five animation metadata files regenerate with `--check`.

Viewed inspections use god mode **off**. At [frame 70](before.png), all three types are active, each has emitted one landing event, health is six half-hearts and ammunition stays 3. At [frame 360](after.png), the standard and super actors are gone, golden has produced two explosions and remains active, health is four half-hearts, ammunition remains 3 and no spawn/blast request is pending. See [validation.json](validation.json) and the render logs. This is functional/render evidence for the current adapter, not a native side-by-side playtest or performance acceptance.

```sh
build/deathward --smoke --scene troll-bombs --theme canyon --frames 360 \
  --save /tmp/deathward-troll-inspection-save.json \
  --screenshot /tmp/deathward-troll-inspection.png
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-troll-bombs.py --check
python3 scripts/isaac-reference/extract-coin-animations.py --bombs --check
ctest --test-dir build -R '^(native_troll_bombs|native_player_bombs|source_resources)$' --output-on-failure
```

**Still unfinished:** native live update/contact ordering and time; room/grid/body sampling and bounce/vertical behavior; complete explosion recipients/knockback/flags, characters/items/co-op and linked actors; enemy/boss ordnance producer integration; hot/giga and other special bomb forms; global seed/call-order/zero-seed protocol, room persistence and save/resume; charged keys/active slots, remaining source reward families/layouts/production; and the original movement, projectile, heart, enemy/boss, item and room/reward acceptance requirements. **0 of the six broad areas are fully accepted.**
