# PW-F02 — Halo of Flies

Status: selected after accepted Whip Worm commit `fd7b4b58`; main-game implementation and focused native/gameplay checks pass. Halo's actual Game/Renderer review, Brother Bobby/Cricket UI regressions and CLI loading pass. The user accepted the scoped playtest: "ok, cool, it works... Whats next?". Book of Shadows and catalog expansion remain unselected.

## Source evidence

`source/manifest.json` pins the installed Repentance1.7.9b executable and preserved XML. The capture executes nine bounded copy-count cases,36 orbit-angle cases,eight admitted projectile-contact decisions and22 fly-enemy kill admissions. It preserves disassembly and source item/entity/treasure metadata.

- Ordinary Halo10 supplies two Fly Orbital3.33 actors per copy, capped at ten with the supplied zero other-orbital-effect counts.
- Group0 has native orbit radii25/20, speed.045 and angle offset1.5; formation phases are evenly spaced. XML contact radius is6 and ordinary contact damage is0.
- The contact tail removes ordinary hostile projectiles, retains the orbital, and bypasses player-ignoring projectiles. It does not turn the player invulnerable.
- The native special-contact branch kills types13,14(except variant2),18,80,222,256,296,281,868. Halo skips ordinary NPC contact damage and is not consumed by the special kill. Actual gameplay tests exercise ordinary Fly/Pooter kills and unchanged Tainted Pooter/Gaper HP; complete special-family lifecycle equivalence is not certified.

```sh
PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/capture-halo-of-flies.py --check
```

This is bounded evidence, not full actor/cache/factory/scheduler acceptance. Native broadphase, shared orbital groups, other owned-item modifiers, full cache counts and special-projectile death semantics remain open.

## Main-game behavior

The normal treasure pool now contains source-ordered `[1,4,8,10,45]`, each source weight1. Existing canyon seed mixing and a restricted supported pool remain explicit adaptations; this does not implement the full native item-pool/depletion/profile system. Adding Halo changes some historical seed offerings: current standard-size witnesses include Brother Bobby seed4, Cricket seed11, Yum Heart seed2, and Halo seed7 or38; all are displayed treasure room8.

Touch the existing solid, centered pedestal to acquire Halo once. Two distinct winged world models orbit the player. The build inspector names the owned item and copy count. Orbital interception uses relative swept projectile/fly motion and the earliest collision: nearer terrain or player hits still win, friendly bullets pass, and shots through the gaps can hurt the player. Existing projectile death effects remain; this is not protection against beams, explosions or direct contact damage. The existing NPC execution/death path handles eligible fly contact kills.

Native coordinates use the accepted shooting-space conversion `11/260`, separately from source constants and live overrides. Continuous orbital sampling at the Simulation boundary, local phase, isometric physical geometry and NPC contact sweeps are explicit adaptations. Room transfer retains actor identities and resets the collision chord so it cannot sweep across rooms. Copy changes rebuild the evenly spaced formation. Pause freezes motion. Apply and floor advancement retain owned items and configuration, reconstructing orbitals; retry starts unowned. Explicit Apply still resets floor rewards, allowing their ordinary recollection afterward.

## Live configuration and persistence

**TUNING → SHOOTING → TREASURE → FAMILIARS → HALO OF FLIES** exposes independent orbit speed, orbit size and contact size,25–200% in5% steps. Edits apply on the next active simulation step; speed changes preserve the running rotation phase. The existing Brother Bobby tab and all player shooting/movement/dodge settings remain independent.

Treasure pool mode5 is a labelled fixed-Halo testing override and stays pending until Apply map changes. Default mode1 is the ordinary five-item supported pool. Schema41 exports,loads and remembers Halo settings, migrating schemas1–40 through audited additive hashes. The new mechanics fingerprint is `7475c3faee57bd46`. CLI schemas5/40/41 and actual mouse export/reset/load/remember/retry are checked. The original165% preset remains unchanged, SHA256 `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`.

Campaignv10's existing generic collectible record preserves Halo copies in interrupted-expedition history; no save-version bump is needed. This is not live expedition resume, which remains D18 work.

## Verification

`all-tests.log`: ten suites pass — Halo, Brother Bobby, all-category composition, Cancer, Whip Worm, Yum Heart, Cricket, treasure, core contracts and balance presets. `halo-tests.log` adds explicit campaign interruption-history coverage. The Halo suite covers native numeric comparisons, actual acquisition/copy cap/removal, three canyon sizes, pause/room/Apply/floor behavior, live phase continuity, fast hostile/friendly/ignoring shots at30/60/120Hz, earliest wall collision, vulnerable gaps, fly contact kills, no ordinary contact damage, and valid/invalid presets.

`game-input.log` verifies actual main-game mouse acquisition/models/build inspection, the Halo panel, every live control, export/reset/load, staged pool/Apply, retry and next-expedition loading. It also observes the original generated Pooter firing, with direct test positioning inside its already accepted D06 acquisition range. No enemies are injected, no enemy settings are changed, and no immunity is enabled. This test is not a matched live Isaac encounter or acceptance of full corridor navigation.

The UI test caught and fixed the menu guard that initially excluded the new Halo actions. Older fixtures were updated for the added catalog entry, changed natural item seeds and six pool modes; all reruns pass. Historical source captures remain intact.

`cli-validation.json` records real executable launches using schemas5/40/41. Images: [pedestal](halo-pedestal.png), [owned orbitals](halo-owned.png), [build](halo-build.png), [live panel](halo-panel.png), [ordinary Pooter encounter](halo-encounter.png).

## Short human review

From the repository root:

```sh
build/deathward --expedition --seed 38 --review-room 8 --mute --save /home/kambo/.local/share/deathward/reviews/pw-f02-halo-of-flies/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

This opens the naturally generated Halo pedestal directly. There is no forced pickup or pre-granted item. Normal controls, health, accepted165% view and enemy settings are retained.

1. Collect the pedestal item; two flies orbit you.
2. Follow the room's only corridor into displayed room4 and approach the orange Pooter so it fires. Watch the flies block shots that actually touch them; gaps remain vulnerable.
3. Revisit the treasure room after clearing the fight; the item remains owned and the pedestal stays spent. Death retry returns to room8 with a fresh build.

Remaining: checkpoint commit; full native cache/group/factory/scheduler/physical and special-projectile/synergy equivalence; broader catalog and full live expedition resume. Next, commit this accepted checkpoint. Next proposed delivery is PW-A02 Book of Shadows, requiring a separate selection.
