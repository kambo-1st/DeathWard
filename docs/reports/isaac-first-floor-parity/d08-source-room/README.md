# D08 — a recorded combat formation in the main expedition

Selected by “nice its good, commit and hurtrpy up for a next item”. D07 was committed as **56743a72**. D08 now integrates one recorded Basement formation into the opening floor of ordinary canyon expeditions. The user accepted the scoped encounter playtest ("looks good contoinue"); this is not complete source geometry or floor-generation parity.

## Short playtest

```sh
build/deathward --expedition --seed 69 --mute --save /home/kambo/.local/share/deathward/reviews/first-floor-d08/campaign.save --balance-preset docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json
```

Enter **room 3, next to the entrance**. There are two ordinary Gapers and no added cover. Fight, leave and return: combat doors should seal, reopen after the last threat dies, and stay open on revisit without respawning enemies. Existing key locks on special-room connections remain independent. Gapers may produce their existing successor bodies. This takes about 1–2 minutes; no measurements are requested.

The main executable keeps the accepted 165% zoom, 110% rooms, 7–9 half-tile range, 26% routes, Speed 1 / 4.8 walking, Tears 1.9272734, Shot Speed 0.9, Range 6.5, Damage 3.5 and regular HP 100%. Eight-direction firing and universal dodge remain. Death retry works. The original user export and D03 backup are unchanged.

**TUNING → MAP / MOVEMENT / VIEW → SOURCE COMBAT ROOM** enables/disables the formation. The nearby label identifies its active room number. The change stays pending until **APPLY MAP CHANGES**, which regenerates the current floor while preserving the player/build and expedition identity, resetting floor encounters/rewards/transients. Testing regeneration remains available after combat/exploration. Export stores pending settings; load stages this map field; **USE NEXT EXPEDITION** remembers it. Schema **10**, contract `d08-source-room-v10`, adds boolean `source_combat_room`; schemas 1–9 migrate with the selected delivery enabled while preserving prior settings. Current-floor generation, retries and future expeditions respect the switch. Later floors retain the setting but do not insert this opening-floor template.

## Exact source evidence and explicit adaptations

[Source record](source-template.json) is reproduced by `python3 scripts/isaac-reference/capture-d08-source-room.py`. The script verifies the preserved Repentance 1.7.9b Basement STB hash, parses all 1,181 templates and consumes all 553,404 bytes before checking the selected record.

| Property | Recorded value | Enabled gameplay |
| --- | --- | --- |
| Identity | Normal room `1.47.0`, index 47 | One deterministic eligible opening-floor combat room |
| Eligibility evidence | Standard shape 1; difficulty 1; weight 1 in Basement library | Earliest combat site without story/key/shop/service role; ties by room index |
| Interior | 13×7 source cells | Existing irregular canyon basin retained; source formation uniformly embedded within it |
| Enemy stacks | `10.1.0` at `(5,3)` and `(7,3)`, each weight 1 | Exactly two ordinary Gapers; no extra specialists, statues, random placement or champions |
| Cover/hazards/pickups | No extra spawn stacks | No random outcrops, breakables, dung, cache, preplaced coins/key sites or river through this room |
| Door slots | North/south/east/west enabled | Existing graph supplies connected door slots; combat seals and existing key locks retain their separate rules |

The spatial adapter uses `cell = min(0.86 × room width / 13, 0.86 × room depth / 7)` and offsets `(−cell,0)` and `(+cell,0)` from the room center. It preserves formation proportions as the user changes room size; **it is not literal native room dimensions or proven equivalent pressure**. Source values stay recorded separately. Existing Gaper behavior, HP units and morph dependencies are reused. No unsupported actor is substituted.

The guaranteed one-room selection, omitted random champions, retained canyon boundaries/doors/scale, native RNG gaps and existing post-kill/clear rewards are explicit adaptations. Room-library presence plus positive weight/difficulty is bounded eligibility evidence, not proof of native floor selection probabilities, unlock filters or an independently captured live source seed. Native floor generation and complete encounter-pressure acceptance remain open. D09 reward rules have not been implemented. Disabling the switch restores prior generation, including the historical D06/D07 seed-69 Pooter encounter; their archived screenshots and acceptance remain historical evidence.

## Verification

- 28 generation cases: 19 seeds plus nine minimum/maximum/scale combinations, including 75%, 101% and 150% size and 25%/200% routes. Exact roster, mapped positions, dry legal spawns, empty cover/pickups, connected door approaches and original HP units pass.
- Real Simulation movement crosses the door; combat seals; ordinary projectiles finish bodies/successors; clearing reopens combat seals; leaving/revisiting produces no respawn, extra clear count or duplicate reward. Test-only god mode and held AI make this deterministic; the interactive handoff uses normal damage and active AI.
- Same-size switch changes regenerate correctly; wounded player/build/expedition identity, accepted tuning and live HP scale survive. Disabled generation and later-floor scope pass.
- Actual Game/Renderer mouse and keyboard controls, deferred Apply, export/load, invalid-preset isolation, death retry and remembered fresh-session loading pass. [Panel](panel.png), [preset fixture](preset.json), [UI log](input-tests.log).
- Final build, regression and CLI checks are recorded in [validation](validation.json). These are scoped developer checks, not a human/native-pressure verdict.

## Unfinished / next

**Human D08 scoped review is accepted.** Full native geometry, pressure, actor/RNG/status/lifecycle, floor selection, champions and reward equivalence remain open. The user selected **D09a: ordinary heart pickups and room-clear reward eligibility**; see [current D09a handoff](../d09a-red-heart-rewards/README.md). Later content remains unselected; the bulk parity goal remains paused.
