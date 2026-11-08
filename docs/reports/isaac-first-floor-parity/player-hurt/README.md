# Ordinary player hurt immunity

Target: installed Repentance 1.7.9b, ordinary Isaac with empty inventory. **This is bounded native counter evidence, not full TakeDamage or wall-clock acceptance.** The executable is read only, pinned by SHA-256 in [manifest.json](manifest.json).

The native block at `0x73d701–0x73d719` rounds the supplied float by adding `0.5` and truncating to an integer, retaining both the original rounded amount and the amount later modified for health loss. At `0x740cfe–0x740d4b`, ordinary post-health processing sets the counter at player offset `0x1308` to `60 * min(originalRoundedDamage, 2)`. The real native integer-min helper executes. It is the original rounded amount, rather than actual red halves lost to a rotten heart or damage clipped by a bone container, that supplies this ordinary counter.

[native-counter.csv](native-counter.csv) contains **24 executed rounding/counter cases**, including boundaries around 0.5 and 1.5. [native-tick.csv](native-tick.csv) contains **193 executed decrement states**: the block at `0x74ff9e–0x74ffaf` decrements a positive counter once per invocation, leaving zero and negative values unchanged. No executed instructions or helper calls are replaced. The guard and early override windows are disassembled for follow-up; they are **not executed or accepted** by this fixture.

Historical v6 integration: the ordinary incoming-damage adapter now uses this damage-derived counter rather than the previous fixed 0.45-second duration. At that checkpoint's provisional 30 Hz adaptation, 60/120 counter units correspond to 2/4 simulation seconds. **That conversion remains conditional on scheduler calibration; these captures do not measure live callback frequency or certify native seconds.** The player timer remains represented in simulation seconds, with a small float-boundary tolerance. Legacy expeditions retain their previous 0.45 seconds. Universal dodge still blocks damage and health effects before this path, preserving both its boost and immunity.

Current correction in `isaac-baseline-v18`: [executed phase evidence](../update-phases/README.md) locates the extra player call either in the alternate phase or, with interpolation disabled, inside the main entity manager. The runtime now converts 60/120 player counter units at 60 Hz to 1/2 simulation seconds. Sustained-contact boundary tests pass, and 590 coupled original physics/motion/counter states match world integration. Full TakeDamage/Player-update branch coverage and live elapsed-time capture remain open. Universal dodge boost/immunity and the legacy 0.45-second hurt window are retained.

The incoming amount is still produced by the provisional DeathWard-authored-damage conversion (`max(1, round(authoredDamage/10))` for positive attacks). This change does not certify its source-specific amounts, flags, champions, self damage or hazards. Damage-entry items, reduction rules, exceptional counter overrides, death/revival and global collision ordering remain open.

`native_player_hurt` compares all 24 counter cases and 193 tick states against the C++ helpers. `isaac_baseline` additionally checks sustained creep contact through the current adapter's expiry boundary, the cap for larger hits, original-damage preservation through rotten double-red depletion, retained legacy duration and retained dodge. See `integration-tests.log` for the completed selected suite results and `validation.json` for input hashes.

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-player-hurt.py --check
cmake --build build --target deathward_player_hurt_tests deathward_isaac_baseline_tests deathward -j4
ctest --test-dir build -R '^(native_player_hurt|isaac_baseline)$' --output-on-failure
```

Still unfinished: native live scheduler/unit calibration; all damage-entry flags and source-specific payloads; item/status/special-state invulnerability and counter overrides; complete damage reduction, costs and revival interactions; the other outstanding requirements in the [main report](../../../isaac_first_floor_implementation.md). All six broad parity areas remain open.
