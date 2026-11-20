# D14a.13 — recorded shop coin-donation eligibility

**Continuation selected:** the user acknowledged this checkpoint and selected the proposed playable coin economy. D14a.14 now enables that bounded main-game feature; see [its report](../d14a14-coin-donation/README.md). The historical capture context/full factory gaps below remain open.

The user accepted D14a.12 with “nice it works, continue!” and selected its checkpoint plus the recorded shop's donation-machine eligibility/factory investigation. D14a.12 is committed as `2e2f7e17`.

**The ordinary coin-machine initializer's gates are now verified. This checkpoint changes the source capture tooling and reports; it adds no gameplay actor or tuning setting.** The historical reason for the recorded machine's absence is still unknown because that capture omitted the relevant run-context fields. Full factory and coin-donation gameplay are not accepted.

## Verified result

The shop template's first slot is **Donation Machine6.8**, which accepts coins. It is separate from **Blood Donation Machine6.2**, created by the already enabled Temperance card. The source shop2.0.0 snapshot contains no6.8 actor.

The installed Repentance1.7.9b initializer behaves as follows:

| Input | Native result |
| --- | --- |
| Ordinary context, no exclusion or jam flags | Machine remains active in state1 |
| `Seeds::IsCustomRun` byte set | Machine is removed |
| Run-state flag17 set | Machine is removed |
| Seed-effect query, mod-policy query, run restriction byte, or profile restriction reports blocked | Machine is removed |
| Run-state flag18 set, otherwise eligible | Machine remains present in state3, jammed |
| Bank counter alone, including999 or1000 | Does not exclude the machine in this initializer |

The jam-state assignment also executes after a removal request when both inputs are set; removal still wins for actor presence. A jammed actor is not equivalent to an omitted actor. The native bank display shows the final three decimal digits.

**A numeric procedural seed does not establish `IsCustomRun`.** DeathWard's `--seed` and the recorded Isaac seed text must not automatically disable donation machines. The preserved log's `[New, 2]` value is not treated as proof of custom-run context. User recollection of manually entering the seed would provide context, but would not recover every native flag at the time of the old observation.

## Evidence and reproducibility

`scripts/isaac-reference/capture-donation-eligibility.py` executes the original variant8 initialization instructions, run-state bit queries, restriction helper and native Remove state stores against the pinned executable. There are **1,280 cases**: all128 combinations of seven gate inputs, each with ten bank values. Counter digits, active/removed flags, jam state and query calls are recorded in `source/native-initialization.csv`. `--check` reproduces the saved output exactly.

`source/manifest.json` pins executable/XML hashes and assembly windows. The actual vtable Init/Remove addresses and the named `Seeds::IsCustomRun` binding are checked. The generic factory-to-Init call is preserved as assembly evidence; the complete allocation/base-init/factory wrapper is not executed by this test.

Seed-effect and mod-policy query results are supplied inputs. Their complete internals are not claimed verified. Animation calls, cosmetic jam RNG and the room removal-queue endpoint are hosted. The numeric gate decisions and actor-state stores execute original instructions. A raw run byte and profile-vector restriction retain offset-based names until their complete semantics are established; they are not relabelled as guessed achievements or unlocks.

Reproduce with a Python environment containing pefile, capstone and unicorn:

```sh
python scripts/isaac-reference/capture-donation-eligibility.py --check
```

## Read-only capture improvement

`read-live-floor.ps1` now emits capture schema2 with `donation_context`: the actual custom-run flag, run flags17/18, the additional run/profile restriction fields and bank total. It verifies those fields stayed stable during capture. Seed-effect/mod-policy query results remain explicitly uncaptured. Existing descriptors, actor enumeration and consumers remain compatible; old snapshots are immutable.

PowerShell-hosted C# compilation passes. The updated reader has **not** been verified against a live Isaac instance: none was running during this checkpoint. It uses the same read-only process access and pinned executable validation as before. No process writes, injected calls, input or source-game file changes are used.

When a paused first-floor source game is available, capture to a new file:

```sh
python scripts/isaac-reference/capture-live-floor.py --output /tmp/isaac-donation-context.json
```

A new capture describes that new moment. It cannot retrospectively prove every gate input for the old shop snapshot. The outstanding user question asks whether seed2FFX8XJH was entered manually or began as a random expedition.

## Gameplay state and next proposed delivery

DeathWard retains the accepted recorded shop, including the observed absence of a coin donation machine and the correct original spawn-slot seed sequencing. This remains an observed-content policy, **not general native shop eligibility parity**. The supported Temperance/blood-machine mechanic, accepted controls/balance, user presets and schema57 are unchanged. There is no new human playtest for this research checkpoint.

The next proposed playable delivery is an ordinary coin donation machine for eligible expeditions: persistent bank ownership, coin admission, jam/revisit rules, destruction/withdrawal policy and live/export/load testing boundaries need explicit design and source verification together. A schema or a decorative machine alone would not complete that feature. This proposal is not automatically selected by the gate investigation.

Unfinished: historical source context, full factory/query/profile acceptance, the coin-donation economy and persistence, remaining special rooms, complete recorded-floor allocation, missing rare keeper items and live expedition save/resume. Pixel/performance work remains deferred; bulk parity stays paused.
