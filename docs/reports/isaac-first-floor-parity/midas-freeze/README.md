# Midas freeze: native control evidence and enabled integration

Target: installed Repentance 1.7.9b, ordinary Isaac. The original executable is read only and hash checked. [manifest.json](manifest.json) records its hash, native code windows and fixture limits.

[native-midas.csv](native-midas.csv) contains **1,096 native control states across 13 cases**. The C++ [control kernel](../../../../src/combat/MidasFreeze.hpp) matches all recorded flags, Freeze/Midas/cooldown timers, special variant output and color intent. The cases exercise positive/zero/negative requests, active-marker refusal, interaction with ordinary Freeze, cooldown reset by golden-heart depletion, supplied boss metadata, status immunity, death, type245's special variant branch and an ordinary Pooter-shaped body. These are supplied native-layout fixtures, not acceptance of the complete named enemy controllers.

Original `AddMidasFreeze`/`AddFreeze` and their immunity, duration, unlinked propagation and NPC metadata helpers execute. Only the native virtual **SetColor** endpoint is intercepted, with the native five-argument stack cleanup. Timer fixtures execute bounded original expiration/cooldown instructions. No AI, physics, real-time scheduling, linked body, renderer or world spawning is executed by these arithmetic fixtures.

Confirmed scoped rules:

- Midas sets the ordinary Freeze flag and timer **and** a separate Midas marker/timer. It assigns the requested positive duration; it does not apply ordinary Freeze's positive 120-update cap.
- Nonpositive Midas requests, an active Midas timer, an active control cooldown, death and the tested source immunity flag prevent application. An active marker refuses extension.
- Ordinary Freeze can shorten the shared AI-hold timer to 120 while Midas remains active longer. AI hold and the gold/death-payout marker must therefore expire independently.
- Supplied boss metadata starts a 240-update control cooldown. The native golden-heart producer clears that cooldown before attempting Midas, including when Midas then refuses reapplication.
- Type245 has a distinct native variant change; its gameplay morph is still unsupported here.

[native-death-coins.csv](native-death-coins.csv) checks **11 supplied raw RNG values** against the original modulo-helper tail and ordinary-Isaac `+1` block. A marked NPC's ordinary-Isaac payout is **1–3 pennies**. The native death branch excludes a high-word reward-suppression flag; alternate nearest-player health kinds, the global RNG stream, complete death scheduling and spawn physics remain outside these fixtures.

Enabled in the baseline expedition: golden depletion applies Midas within the current eight-world-unit conversion of the source radius80 query; ordinary unlinked NPCs use separate timers, hold AI/pose through the shared Freeze timer, retain the gold marker after an earlier thaw and pay once on death while marked. Gold body/overhead cues distinguish Midas from ordinary frost. The existing summoned-offspring loot restriction also suppresses Midas payout. This Midas checkpoint used `isaac-baseline-v4`; the subsequent blue-fly integration uses v5.

**Integration is partial.** Exact source status-immunity and reward-suppression flag initialization/query selection are not mapped for every actor. The adapter rejects shared formations, linked/owned bodies, rail carriers, special type245 and static/environment hazards pending their contracts. Boss metadata mapping, item duration modifiers, Midas propagation through damage/morphs, per-actor friction, coin RNG/physics and live timing remain open. Passing the common numeric matrix is not full acceptance of every affected enemy. Existing regular enemy HP/source stage values are unchanged; universal dodge boost and immunity remain the explicit user exception.

`isaac_baseline` covers golden-depletion application, active-marker refusal, separate timer expiration, ordinary Freeze interaction, extra death pennies, once-only payout, offspring reward suppression and a Pooter thaw without an ordinary-Freeze profile. The five existing status suites and six baseline/kernel suites pass (**11 suites total**). [hud.png](hud.png) is an eight-frame launch/render check showing two gold actors, the mixed health bar and seven placed pickups, with **inspection god mode**. It is not combat/performance or native live-game acceptance.

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-midas-freeze.py --check
cmake --build build --target deathward_midas_freeze_tests deathward_isaac_baseline_tests deathward -j4
ctest --test-dir build -R '^(native_midas_freeze|isaac_baseline)$' --output-on-failure
./build/deathward --smoke --scene health --frames 8 --screenshot /tmp/deathward-midas.png
```

Ordinary rotten-heart flies and the room-clear producer are now enabled in the separate [blue-fly checkpoint](../blue-fly/README.md). [Refill research](../rotten-heart-flies/README.md) records 104 bounded native cases; full callback and familiar fidelity remain open. All six broad parity areas remain open in the [main progress report](../../../isaac_first_floor_implementation.md).
