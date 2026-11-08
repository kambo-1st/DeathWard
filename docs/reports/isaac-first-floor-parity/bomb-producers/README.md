# Mulligan-family source bomb producers

Target: installed Repentance 1.7.9b. Runtime checkpoint: `isaac-baseline-v15`.
Universal dodge, its movement boost and immunity remain enabled. Full parity remains unfinished.

## Verified research

`analyze-bomb-producers.py` executes the original late Mulligoon death branch through its global MT draw and complete Spawn argument construction, stopping before Spawn. Eighteen cases request type 4, variant 3, subtype 0, at the dead NPC position, with zero velocity, the NPC parent and one new InitSeed. Earlier projectile emission is outside this slice.

The resulting child then runs whole original Bomb::Update with the supplied dead 16.1 parent. All 1,083 child states across the eighteen sequences match the C++ kernel. This uses the existing troll-bomb fixture: external audio and blast endpoints are intercepted; actual allocation, recipients and the full NPC controller are not accepted.

Nine separate voluntary Mulligan/Mulligoon and death Mulliboom slices capture BombDamage intent: damage 40, native radius 60, line check 1, source NPC and flags 4. They stop before BombDamage. Numeric instructions use the preserved x86 UCRT identified in `manifest.json`.

## Enabled gameplay

The baseline death adapter now creates an ordinary source troll bomb for Mulligoon instead of the legacy 320-damage bomb. Its native damage is 100, radius 75 and ordinary player damage two half-hearts. The producer identity, position and selected seed survive pending admission and producer-body cleanup. The entire ring/blast/child payload waits when capacity is unavailable; retries preserve the seed and avoid duplicated shots or bombs.

Mulligan-family immediate blasts use source damage 40, native radius 60 and one player half-heart through the existing world adapter. Source attack values are separate mechanics fields; legacy 128/320 damage and the shared regular-enemy HP control are preserved. A .75 HP test gives source Mulligoon 9.75 HP while attack damage remains 40.

A pinned naturally generated baseline Canyon witness, expedition seed 368 / first floor / room 3, reaches this new child path through ordinary damage and death handling. This establishes production reachability for that resident, not native room generation or full enemy acceptance. The screenshot is a separate 40-frame isolated enemy smoke inspection with a scripted normal-damage hit at frame 5 and spectator god mode enabled, not the production witness or a self-damage acceptance check. The ordinary smoke controls can also place player dynamite; the screenshot does not independently label each charge.

## Validation and remaining work

See `validation.json` and the saved build/test/native-check logs for the completed checks. `source_bomb_producers` compares the independent native captures, complete-payload pressure/recovery, source damage, HP separation, invalid schema rejection, legacy isolation and natural production reachability.

Hornfel, FlyBomb and other ordnance producers retain their previous adapters. Complete NPC AI/projectile parity, shared global RNG call order (including projectile draws before the death bomb), native expedition seed mapping, zero InitSeed, complete explosion recipient/flag/knockback/line-check behavior, grid/vertical/contact scheduling, modifiers and save/room persistence remain open. Native captured flags and line-check arguments are research evidence; the DeathWard world blast adapter does not yet prove their full semantics. Source room-reward generation remains disabled. All six broad parity areas remain open; none is fully accepted.
