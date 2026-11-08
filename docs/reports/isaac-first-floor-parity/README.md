# First-floor differences audit evidence

Read [the differences report](../../isaac_first_floor_differences.md) first. This directory records an initial comparison, not native gameplay acceptance. No balance changes were made.

Run from the repository root, with the preserved `reference/isaac-repentance-1.7.9b` payload present. That licensed local reference is intentionally excluded from Git. A configured Linux `build/` with Raylib is required for the runtime probe:

```sh
cmake --build build --target deathward_core -j2
/usr/bin/c++ -O2 -std=c++20 -I src -I build/_deps/raylib-src/src tools/isaac_first_floor_probe.cpp build/libdeathward_core.a build/_deps/raylib-build/raylib/libraylib.a -lpthread -lm -ldl -lGL -o /tmp/deathward-first-floor-probe
/tmp/deathward-first-floor-probe > docs/reports/isaac-first-floor-parity/deathward-runtime.tsv
python3 scripts/isaac-reference/audit-first-floor-parity.py > docs/reports/isaac-first-floor-parity/generation-summary.json
```

The probe exports the active registry and default build, three first-floor profile samples and a 241-step held-fire fixture at 60 Hz. It writes no campaign save. It does not run or modify the original Isaac installation. Rebuilding after gameplay changes deliberately produces a different snapshot; retain the report's commit and input hashes when interpreting these results.

- `deathward-runtime.tsv`: raw probe output; descriptive registry speeds/cooldowns are not measured native AI.
- `snapshot.json`: resolved defaults, inventories, opening encounter candidates and the narrow firing observation.
- `enemy-comparison.csv`: chapter-library candidates joined to opening DeathWard encounter candidates. This is a superset, not a certified Basement-I spawn list. Same-type/variant numeric subtype fallbacks are labeled explicitly.
- `enemy-gaps.json`: existing acceptance-ledger entries for comparison candidates; implementation presence is not acceptance.
- `room-library-inventory.json`: completely parsed chapter libraries, including floor-II and conditionally available content. Row frequencies are not spawn probabilities.
- `source-boss-pools.json`, `boss-comparison.csv`: XML membership/weights and per-entity health, not proven floor-I selection probabilities or total segmented encounter HP.
- `input-hashes.json`: exact local inputs, including the probe and generator. The source XML closing-tag repair is in memory only.
- `validation.json`: integrity and consistency checks for this captured audit. Passing these checks establishes reproducibility/data consistency, not 1:1 mechanics.

Still unfinished: matched installed-game measurements, exact first-floor/unlock eligibility, gameplay implementation and complete nonvisual acceptance. Existing partial enemy research remains separately scoped in `docs/research/isaac-enemy-port-status.json`.
