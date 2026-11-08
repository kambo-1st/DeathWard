# Rotten-heart blue-fly refill: research only

This directory scopes **refill arithmetic**, independently of the enabled [blue-fly actor](../blue-fly/README.md). The installed 1.7.9b executable is hash checked and read only. [manifest.json](manifest.json) scopes the capture; [native-refill.csv](native-refill.csv) contains **104 executed native arithmetic cases**. Neither capture alone nor the enabled integration establishes full familiar acceptance.

The native block at 0x76e60c computes a positive deficit from `2 * rottenHeartCount - alreadyOwnedBlueFlies`. It requests that deficit from `AddBlueFlies`; it leaves existing excess flies alone. Upstream code enumerates familiar type3/variant43 and counts those whose player pointer matches the current player. Thus blindly adding twice the rotten count on every invocation would be incorrect.

The fixture supplies the owned-fly count in ESI and uses valid 24-half red capacity. It executes the original deficit branch and argument assembly, then stops **before** `AddBlueFlies`/world spawning. Entity enumeration, familiar creation, orbit/target/contact behavior, damage/removal and live timing are not exercised. The preserved `AddBlueFlies` disassembly also shows a trinket94 query that doubles the request when owned; no item modifier is enabled by this research.

The block belongs to native function0x76e140, called through the players callback0x91aa70 and another player path. The complete trigger/room-charge semantics still need confirmation. Neither function addresses nor an arithmetic trace alone prove every event on which refill occurs.

The ordinary actor and DeathWard room-clear producer are now integrated. Separate native captures/checks cover motion, orbit-angle arithmetic, target scores, initialization damage and special contact branches. Integration fixtures cover stock/excess, contact consumption, direct Kill, queue pressure, actual clear refill and floor carry-over. These are distinct evidence scopes; source pickup/drop selection is still absent.

Next: confirm every native refill callback trigger and exact ordering; complete actor target eligibility/lifecycle/subtypes, imported orbit math and item/cache modifiers; compare native room/floor persistence, live scheduling/collision and RNG. This remains part of the original health/items/room-rules objective.

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-rotten-heart-flies.py --check
```
