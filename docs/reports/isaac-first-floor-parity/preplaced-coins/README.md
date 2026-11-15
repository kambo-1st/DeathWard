# Preplaced ordinary coins — source room 1.30.0

Selected on 2026-11-15 after the accepted source31 chest room, now committed as `3dee8d4f`. **The coin arrangement is enabled, developer-verified and accepted in the scoped human playtest on 2026-11-15 ("yes, nice, it works!").** Committed as `dadbc92b`.

## Short playable check

The main game is running at seed1063, displayed room2, with the unchanged165% user preset, health6 and god mode off. The review starts near the central rock so all four coins are visible. This launch-only approach is physically clear and outside pickup range; ordinary expedition entry is unchanged. Death retry returns here.

```sh
build/deathward --expedition --seed 1063 --review-source-room 30 --mute --save /home/kambo/.local/share/deathward/reviews/preplaced-coins/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

1. Click or walk over the four coins around the rock. They are ready immediately and add **four** to your money in this seed.
2. Movement should route around the solid rock. No dynamite is needed to collect these coins.
3. Leave and return: the collected coins stay gone.

[Room at entry](room.png), [after collection](collected.png), [launch record](interactive-handoff.json).

## Enabled behavior

The pinned Basement record has four ordinary subtype0 coin slots around one central plain rock, with no enemies. Original slot ordinals0/1/3/4 retain the rock ordinal2 in the descriptor spawn sequence. The shared ordinary resolver supplies penny/nickel/dime outcomes using the existing explicit rare-gates-off profile. Source reference data is separate from DeathWard's floor seed/order and canyon spatial adapter. [Complete source record](source-room.json).

The existing native numeric/weighted selector must naturally choose this record in a compatible opening-floor canyon room. Protected key/objective/story sites retain their prior composition without rerolling. Source metadata at an incompatible site cannot masquerade as this complete review. Other coin-bearing templates are not enabled by this delivery.

Coins remain at their source cells, start idle on entry and retain resolved identities through blocked/capacity admission delays. They reuse ordinary collection timing, values and99-cap rules: a coin is refused at99 or above; below99 its whole value is consumed and clipped to99. Collection is once-only, including partial collection followed by leaving/revisiting. This room has no fabricated combat-clear reward or unrelated random coin piles. The central rock remains solid and ordinary navigation respects it.

## Configuration

**TUNING → REWARDS → ROOM LAYOUTS → SOURCE LAYOUTS** includes this arrangement. OFF/SOURCE changes stay pending until **Apply map changes**. Loading a different map mode stages it too. Apply regenerates the current floor, keeps the player/build/wallet/expedition, resets floor actors and avoids putting the player inside the restored rock.

Schema22 (`preplaced-coins-v22`) records the expanded layout policy and migrates schemas1–21. Export/Load/Use next expedition retain the existing controls. **AFTER CLEAR → COINS** remains independent; disabling clear rewards does not remove layout coins. No new tunable or forced appearance frequency is introduced. Accepted movement/shooting/dodge, damage/health, canyon shapes/sizes/connections and original preset bytes remain unchanged.

## Verification and remaining work

Seven focused suites pass, including existing hearts/chests/room coverage and coin rewards. The new actual Simulation checks cover smallest(.75,5–5; seed1322), accepted(1.1,7–9; seed1063) and largest(1.5,10–10; seed1063) dimensions. The smallest witness naturally contains three pennies and a dime; the other two contain four pennies. This is boundary/reference coverage, not an exhaustive random-floor sweep. Denomination/cap fixtures also verify penny/nickel/dime consumers. Deferred positions/identities, idle entry, physical click paths, partial/full revisit, OFF/test/later-floor exclusions and Apply are checked.

The actual Game/Renderer workflow passes mouse toggle/Apply/staged Load, collection around the rock, export/remember/fresh load, revisit and death retry with normal health. Three CLI launches cover schema21 migration, schema22 with clear coins off, and schema22 with source layouts off. The final review approach was rechecked in the actual Simulation and mouse workflow; the165% entry render was visually inspected. [Validation](validation.json), [seven suites](tests.log), [boundary checks](boundary-detail.log), [actual input](input.log), [CLI loads](cli-validation.json).

The accepted delivery was committed as `dadbc92b`; the user subsequently selected D09c ordinary keys under the delivery plan's one-pickup-family rule: natural rewards and compatible source layout placement, once-only collection, existing inventory limits and staged/live preset boundaries. D09c is now in progress; see [ordinary keys](../d09c-keys/README.md). Bomb/dynamite and door-spending rules remain separate later deliveries. Other preplaced coin layouts, special coins, full native seed/factory/physical/profile/modifier/economy equivalence, full expedition gameplay save/restore and prior chest/room gaps remain unfinished. Exact Isaac size/shape/connections remain excluded; automatic bulk parity stays paused.
