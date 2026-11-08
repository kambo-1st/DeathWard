# Native blast recipients and impulse

Target: installed Repentance 1.7.9b. Runtime checkpoint `isaac-baseline-v16`.
Graphics and universal dodge (movement boost and immunity) remain accepted departures. **Full blast and six-area parity remain unfinished.**

## Independent evidence

`analyze-blast-recipients.py` executes the original post-tree circle filter at 415960 and the ordinary BombDamage recipient path starting at 6d1833. A single supplied broadphase candidate is filtered with the original code. Recipient processing stops before the virtual TakeDamage call, or after rejecting the recipient. Actual player/NPC/bomb vtables and the preserved x86 VCRUNTIME `__RTDynamicCast` execute. No geometry, type-check, mass, impulse, RNG or math calculation is replaced. The executable, DLL and source XML hashes are pinned in `manifest.json`; the DLL is read locally, not redistributed. This is isolated IAT resolution, not proof of the live process loader or OS initialization.

The 658 cases produce 437 damage intents and execute 398 runtime type checks. They cover exact/near/diagonal circle boundaries, center overlap, player/NPC bodies, nine masses (including 0/20/20.001/1000), three incoming velocities, collision/dead/query exclusions, no-knockback flags, damage thresholds and three damage-flag combinations. Eighteen cases supply an empty-flag player, bomb or NPC source; the others use a null source. All C++ eligibility, damage-intent and impulse comparisons pass, with **zero maximum velocity difference**.

The source filter uses strict planar `(blastRadius + bodyRadius)^2 > distanceSquared`. Ordinary knockback retains half the old velocity and adds the outward direction times `min(reach-distance,15)`. The executed branch halves this force for every mass above 20; later apparent mass tiers are unreachable under that earlier branch. Players additionally cap resulting speed at 10; mass 1000 and the captured source/type/flag exclusions suppress their impulse. Coincident centers retain velocity. Mass zero/dead/noncolliding/query-excluded candidates are rejected by the native recipient path. The fixture preserves those findings without claiming all runtime state mappings.

## Enabled adapter

Source player bombs, source troll bombs and source Mulligan-family blasts opt into the new world adapter. Twelve basic enemy forms use installed XML radius/mass metadata from `source_blast_bodies.mechanics`: 10.0/10.1, 11.0/11.1, 12.0, 13.0, 14.0, 16.0/16.1/16.2, 18.0 and 85.0. These source blast bodies are separate from authored general collision/render hulls and HP. Existing represented collision-size scaling is carried into the blast body; native champion/dynamic-size acceptance is still open.

For these bodies, native planar blast membership replaces the former authored 3D reach, and the native impulse replaces the former tuned hit-response impulse for this blast only. It runs before queued health damage and preserves the separate vertical world velocity; the later damage event skips the second authored recoil. Player blast membership uses native radius 10 and changes native motion velocity before health damage. Existing world cover still gates exposure. Universal dodge continues to protect health and retain its movement boost. Legacy blasts and actors outside the reviewed metadata retain their previous adapters.

World regressions exercise strict boundaries, single impulse, existing cover, legacy isolation and dodge. Additional checks use actual placed player bombs, actual source troll actors and normal-damage Mulliboom deaths: they damage real Horf recipients in the newly corrected outer radius. This is stronger than constructing only a flagged test event, but does not establish full native production room/actor acceptance.

## Remaining work

Native broadphase tree construction/enumeration and line checks, special source/item/tear flags, every represented collision class/mass/no-knockback state, other enemy body metadata and dynamic forms, source NPC AI motion after the initial impulse, grid/vertical/contact/update ordering, knockback against props and other entity families, actual native TakeDamage and all modifiers remain open. The world impulse uses the current .1 scale / 30 Hz adapter; live elapsed time and geometry are not accepted. Existing terrain destruction, pickups, flags, room travel and persistent actor cleanup still use DeathWard adapters. Production source rewards, broader enemies/bosses/items and all six broad parity areas remain open.

See `validation.json`, saved native check/build/test logs and the graphical inspection for the final checkpoint evidence. The 360-frame inspection uses god mode off and no movement input: room 0 becomes room 2, health six becomes four half-hearts, ammunition remains three and no source bombs remain after room exit. This does not establish full native travel/persistence acceptance. An inspection that changes room must not be compared with the old same-room golden-bomb count: room exit invokes the existing room-owned actor cleanup policy.
