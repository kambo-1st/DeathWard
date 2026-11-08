# Baseline implementation checks

Read [implementation progress](../../../isaac_first_floor_implementation.md) for enabled scope and unfinished work. The parent directory retains the pre-change audit.

- `deathward-runtime.tsv`: the content/simulation probe with `--isaac-baseline` after rebuilding; HP and attack units differ intentionally from the parent audit.
- `tests.log`: focused CTest results. These are DeathWard regression checks, not native-game acceptance.
- `validation.json`: captured implementation observations and remaining gaps.
- `hud.png`: one-frame graphical smoke capture, with inspection god mode. It verifies the heart HUD only, not combat or balance.

Do not run the historical CSV generator over this TSV: its original hit-count columns are explicitly based on the old 24-damage audit. Regenerate a new comparison schema when updating numerical analysis.
