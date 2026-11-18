# D14a.3 — ordinary Round Worm and recorded room505

Status, 2026-11-17: selected after the user returned to finishing the game. Main-game implementation, build and focused developer checks pass. The user accepted the scoped playtest on 2026-11-18 ("D14a.3 was alright, lets move out!"); see `human-acceptance.json`. The accepted preceding checkpoint is `1ff5dde5`.

## Bounded source evidence

Installed Repentance1.7.9b ordinary244.0.0 has10 base HP,0 stage HP,13 collision radius and100 collision mass. The retained shared HP unit gives32 internal HP, three accepted11.2-damage hits. No Tube Worm/Tainted variant is enabled.

`source/manifest.json` pins the installed executable, XML identity and controller windows. The capture executes68 native cases:24 shot velocities,5 ten-player-step predictions,32 strict relocation-range/parity gates and7 supplied animation-end transitions. The highest matching archive supplies DigIn17 and DigOut61, with PreShoot30/Shoot38. Ordinary DigOut fires one aimed mode0 shot at native speed10 when line of sight permits it; it does not use Lump's three-shot volley.

Hidden relocation samples60–310 native units around the room centre, requires100 < player distance <1000, and an even random result. DeathWard uses its seeded combat RNG, retained canyon floor/collider checks and physical occupancy rejection. Relocation coordinates use the room's source-cell scale (`sourceHeartCellSize / 40`), independently of the fixed movement/projectile scale. This fixes the reproduced large-room case where a distant entrance kept worms outside the native1000-unit admission gate. Three room-size configurations verify continued emergence, valid placement and normal projectile kills. Native free-grid search, RNG consumption, complete factory/animation scheduling, statuses/champions and full live actor equivalence remain unverified.

## Main-game scope

- Dedicated stationary surfaced / hidden relocation / emergence / single-shot controller.
- Source room1.505.0: two ordinary Round Worms and36 plain rocks, no initial pickups. It is admitted through the existing native-filtered13×7 selection pool when naturally selected in a compatible ordinary canyon room. Source door metadata does not replace canyon connections or outlines.
- Buried actors are intangible; surfaced contact uses one half-heart and shared hurt/dodge immunity. Shared outgoing damage and regular-enemy HP controls remain intact.
- TUNING → ENEMIES → FULL FLY → ROUND WORM has independent cycle and shot-speed controls in5% steps. Cycle edits apply at the next phase; shot-speed edits apply at the next emergence. Active and capacity-delayed shots retain their selected settings. Source30Hz timing and fixed accepted-player-relative space conversion are explicit production adapters.
- Schema49 exports/loads/remembers both values, with migrations from schemas1–48. Map settings remain staged until Apply; regeneration, retries and floor transitions retain tuning. The user's current schema48 preset must remain unchanged.

## Verification and remaining work

- Main-game build passes.
- Native capture/replay:68 original-code cases; C++ matches61 numeric shot/lead/relocation cases. The7 supplied native animation-end cases are preserved as source evidence; complete native scheduling is not claimed.
- Runtime tests pass: DigIn17, Shoot38, DigOut61, 30/60/120Hz partitions, hidden immunity, one-half-heart contact, retained universal dodge, three-hit HP, stationary surfaced bodies, and once-only capacity-delayed shots.
- Seed445/displayed room2 passes at size75% /5–5 half-tiles,110% /7–9 and150% /10–10: exact2-worm/36-rock contents, actual floor/cover clearance after relocation, successful real-player-projectile kills, room clear, revisit and SOURCE OFF/ON map regeneration.
- Actual Game/Renderer mouse checks pass for page access, independent live controls, export/load/reset/remember, Apply, death retry, aimed shots, clear/revisit and a fresh launch. `game-review.cpp` preserves the harness; screenshots show the surfaced model and tuning panel.
- Normal CLI direct-entry loads pass for schemas5,48 and49. The user's current schema48 file remains SHA256 `22e143a736697ccc780ab31bde3c3a1f7ac0d88392e9bf7aa45055ccd3895604` (including Speed1.1, Shot Speed1.05, zoom165 and route length26%). No original-preset rewrite.
- Focused regressions cover Full Fly, room props, source room coverage, preset validation, Whip Worm and treasure upgrades. `final-tests.log` records the aggregate result.

Interactive review command:

```sh
build/deathward --expedition --seed 445 --review-source-room 505 --mute --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json --save /home/kambo/.local/share/deathward/reviews/first-floor-d14a3/campaign.save
```

Starts at normal health, with two worms and the user's current view/balance. Retry returns to the same room. Check the burrow/emerge/shot cycle, kill both and leave through the released passage. Scoped human acceptance is recorded; full native actor acceptance remains open.

After this scoped delivery: recorded Frowning Gaper/poop arrangement, mixed Pooter/Attack Fly arrangement, the exact Duke-room contents, Mom's Eye treasure, Mom's Coin Purse/Temperance shop dependencies, unresolved special-room pickups, complete recorded-floor allocation and human acceptance. Broader native actor/selection/factory/physics equivalence and later gameplay-save/resume remain open. Canyon size/shape/connections, eight-direction controls and universal dodge remain deliberate exceptions.
