# Basement boss inventory

Target: preserved installed Repentance 1.7.9b XML. This inventories the eleven entries of the Basement pool; it does not establish the complete eligible first-floor denominator, native gates or selection behavior.

Pool boss IDs and entity identities are different namespaces. Multi-body XML HP is per entity; encounter totals remain unverified.

| Pool ID | Boss | Source weight | XML bodies (base HP / stage HP) | Dedicated controller declaration |
| --- | --- | --- | --- | --- |
| 1 | Monstro | 1 | 20.0.0 (250 / 0) | boss_monstro |
| 17 | Gemini | 1 | 79.0.0 (140 / 0), 79.10.0 (140 / 0) | Missing |
| 2 | Larry Jr. | 1 | 19.0.0 (22 / 0) | Missing |
| 44 | Dingle | 1 | 261.0.0 (300 / 0) | Missing |
| 64 | Dangle | 0.25 | 261.1.0 (375 / 0) | Missing |
| 56 | Gurglings | 1 | 237.1.0 (60 / 0) | Missing |
| 65 | Turdling | 0.25 | 237.2.0 (50 / 0) | Missing |
| 20 | Steven | 0.25 | 79.1.0 (140 / 0), 79.11.0 (140 / 0) | Missing |
| 13 | Duke of Flies | 1 | 67.0.0 (110 / 0) | boss_duke |
| 60 | Little Horn | 1 | 404.0.0 (200 / 0) | Missing |
| 84 | Baby Plum | 1 | 908.0.0 (234 / 0) | Missing |

Two entries now have dedicated controllers available through spawning/inspection: Monstro and ordinary Duke. **Neither has full actor acceptance. Nine pool entries still lack dedicated controllers.** No Monstro-only or two-boss subset has replaced the required source pool in production.

The preserved full bosspools.xml has a later mismatched tag under strict ElementTree parsing. The audit extracts the intact, exact Basement fragment and never repairs reference data. Live parser/loading behavior remains unverified. Portrait achievement fields are metadata, not evidence that the native selector uses those exact gates. Unlocks, first encounters, boss history, champions/alternate forms, replacements outside the pool, RNG selection and room-layout multiplicity remain open.

Production Canyon boss selection and existing boss rewards remain DeathWard adapters. See the [main progress report](../../../isaac_first_floor_implementation.md). All six broad parity areas remain unfinished.
