# Ordinary Isaac health: scoped native evidence

Target: installed Repentance **1.7.9b**, ordinary Isaac, empty inventory. The executable SHA-256 and all code-window hashes are in [manifest.json](manifest.json). The installation is read only.

[native-health.csv](native-health.csv) records **293 transitions across 28 cases**: nine native health-add APIs, mixed acquisition order, removal/capacity boundaries, depleted soul/black/bone slots, rotten health, golden effect intents, eternal conversion/last-life shielding and new-floor conversion, and an explicit red-first flag. The independent C++ [health kernel](../../../../src/combat/PlayerHealth.hpp) matches every recorded health field and effect intent. **Typed health is connected to gameplay**, with remaining fidelity gaps below. None of the six additional families has full acceptance.

The addition calls execute original instructions and native health, inventory and capacity helpers. Their fixture constructs a type-0 actor with six red half hearts; empty collectible/trinket/effect storage; an empty native modifier tree; zero game modifiers; disabled achievements; zero-filled item metadata for empty-inventory queries; and an actor absent from HUD registration. This is a synthetic state, not a live-game capture.

The damage fixture executes **0x73feb6–0x74074c** of `TakeDamage`, supplying an integer half-heart amount, default low flags or `0x20`, the actor pointer and zero-initialized surrounding locals. The initial damage checks/conversion, other incoming flags and prior calculations, hit cooldown, deal-chance callbacks, death/revival and later item callbacks are outside its scope. Dead fixtures receive no subsequent damage. Four explicit endpoints are intercepted:

- The black-heart active-item/sound block records a `black_burst` intent. It does not execute enemy damage or establish its magnitude.
- The bone-break particle/TLS-RNG/sound block records a visual intent.
- The golden burst function records its count and returns with native stack cleanup. It does not execute coin spawning, physics or downstream world feedback.
- The health-conversion animation function records its animation ID and returns with native stack cleanup. Sprite playback is omitted.

Consequently these traces establish **the bounded operations under the declared fixture and endpoint substitutions**, not full native damage behavior. In particular, counts/order observed around golden effects must not be promoted to complete gameplay behavior without checking the omitted world routine and its feedback. No instruction bytes are patched; endpoint interception remains a deliberate limitation.

The three floor cases execute 0x76a71f–0x76a789. Ordinary eternal conversion clears the eternal counter, plays animation 13, adds two maximum red halves and heals two red halves, subject to native limits. This is the health portion, not an execution of the complete native floor transition.

Separate **static native disassembly** establishes the empty-inventory black burst base damage of **40**, and golden coin count **RNG modulo 6 + 3** per burst. Golden depletion also queries native radius 80 and passes 180 frames to the distinct Midas routine; its complete actor eligibility, duration modifiers and linked/special propagation still need implementation/validation. The [Midas follow-up](../midas-freeze/README.md) now enables ordinary unlinked NPC control and death coins, with separate numeric and integration evidence. The manifest distinguishes these inspected effect bodies from the executed arithmetic fixtures.

Red health includes red filling inside bone containers. Black slot bits count soul slots; bone slot bits count the ordered mixture of soul and bone slots. Flattening these into one protective counter loses damage order. Raw removal APIs can produce surprising internal results (the extreme rotten-removal case ends with a negative rotten counter); the kernel preserves the observed API operation, and this does not authorize invalid pickup/cost requests in gameplay.

Reproduce using the same `pefile`, `capstone` and `unicorn==2.1.4` dependencies as the movement capture:

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-player-health.py --check
cmake -S . -B build
cmake --build build --target deathward_player_health_tests -j4
ctest --test-dir build -R '^native_player_health$' --output-on-failure
./build/deathward --smoke --scene health --frames 8 --screenshot /tmp/deathward-health.png
```

The temporary dependency directory is an example, not a bundled dependency. Omit `--check` only to intentionally regenerate the evidence; the executable hash must match first. The C++ test reads independent native outputs rather than calculating its expectations from the port.

Enabled integration: canonical player health feeds transient kernel snapshots; damage follows ordered bone/soul/red slots; empty bones sustain life; black bursts queue ordinary damage; golden overlays produce penny-count bursts; eternal floor conversion runs during floor travel; broken capacity reconciles health. Seven world pickup families can be placed, collected and rendered, with distinct defaults for bone/eternal/golden counts. A full or invalid pickup is retained/rejected. The generator does **not** yet select these from native drop/reward tables.

[hud.png](hud.png) shows all displayed families and seven placed world pickups. The eight-frame smoke uses inspection god mode. It proves rendering/launch only, not combat, native performance or live-game equivalence. Integration tests separately cover ordered depletion, forty-damage bursts, empty-bone death, broken capacity, pickup consumption, eternal floor transfer and retained dodge immunity. Native fixtures separately establish the bounded arithmetic scope.

Still required: full damage-entry calibration/flags, black target eligibility and item/trinket modifiers, complete Midas eligibility, linked/special actors and damage/morph propagation; native gold/pickup physics and RNG, source drop/reward generation, collection timing/subtypes, complete rotten-heart blue-fly fidelity and callback triggers, health upgrades/costs, all reachable item interactions, live-game comparison and acceptance. Universal dodge, including its boost and immunity, remains the user's explicit exception.

The historical Midas follow-up uses mechanics version `isaac-baseline-v4` and passes 11 suites. Its validation and screenshot are stored separately; this directory's earlier v3 screenshot/validation remain historical evidence. Rotten-heart refill now has [104 scoped native cases](../rotten-heart-flies/README.md), and an enabled [ordinary actor in the v5 checkpoint](../blue-fly/README.md), which passes 12 selected suites. Full familiar acceptance remains open.
