# D11a — The Sad Onion in ordinary treasure rooms

Selected by “ok, continue” after checkpoint `10a1176b`, following the seed-review refresh. Implementation is enabled and developer-verified. Human acceptance remains pending. This delivery covers one eligible source item, not the full treasure pool or D12 shops.

## Behavior and boundaries

Ordinary opening-floor canyon treasure rooms offer a single **The Sad Onion**, source collectible1. Treasure pedestals now sit exactly at the room center on every floor. Walk up to the pedestal edge to collect it once; the old two-choice relic menu is bypassed for this offering. Collected state survives leaving/revisiting. Ownership survives floor descent and the explicit testing regeneration of the current floor. Regeneration resets floor rewards as already labelled by Apply, so a regenerated offering can be collected again; it is not a normal revisit. Retry starts a fresh expedition with no owned upgrade. Other floor/mode offerings and legacy reward pools retain their existing behavior.

The item adds `.7` per copy to the underlying ordinary source tear stat. It does **not** add `.7` shots/second. At the source base, actual rate changes from `30/11 = 2.72727` to about `3.44517` shots/second. The ordinary curve is:

```
delay = max(5, 16 - 6*sqrt(max(0, 1 + 1.3*tear_stat)) - 6*min(tear_stat, 0))
rate = 30 / (delay + 1)
```

DeathWard keeps the accepted editable base rate, inverts that curve to its corresponding tear stat, adds the owned modifier and resolves the effective rate once for future firing intervals. The custom-base inverse is an explicit adaptation. Rates already at/above the ordinary5/s cap remain untouched rather than being reduced; the underlying hidden source stat cannot be reconstructed beyond a saturated cap. Zero copies and zero strength preserve the base exactly. Shot Speed, Range, outgoing Damage, HP, walking, dodge and eight-direction controls are unchanged. Current cooldowns finish normally; flying bullets retain their birth specifications.

The normal scene renders a small faceted onion and stem on the existing pedestal, including the regular lighting/shadow pass. Canyon placement, pedestal contact radius and presentation are adapted; native pickup animation/factory/physics are not claimed.

## Tuning and persistence

**TUNING → SHOOTING → TREASURE** contains the staged offering switch, live strength0–200% in5% steps, source-strength reset, and Apply map changes. Offering changes wait for Apply; owned modifiers respond on the next new firing interval. Export and Use next expedition include both fields. Loading stages the offering while applying strength immediately; an unrelated pending map draft is retained by live edits.

Schema29 migrates1–28 with the selected offering enabled and strength1. Adding the item definition changes the mechanics fingerprint from `2ccd5b1c274a302e` to `57e101e53ba57102`. The loader permits only that exact additive migration for older schemas; unrelated fingerprint mismatches are still rejected. The original accepted165% user export is not rewritten.

## Evidence

- [Native evidence](source/manifest.json): preserved XML eligibility and treasure weight;60 original x86 contribution/ordinary-curve evaluations, with the exact installed1.7.9b executable hash and code windows. `scripts/isaac-reference/capture-sad-onion.py --check` reproduces the recorded bytes and results.
- [Core checks](core-tests.log): all60 native rate cases, inverse checks for uncapped source bases,27 natural room/size/route collection cases, once-only ownership/revisit, floor/regeneration scope, existing-shot/cooldown preservation, actual upgraded emissions and additive preset migration.
- [Preset checks](preset-tests.log): schema round trips, archived migrations, strict invalid input and atomic-write rejection.
- [Focused regressions](regression-tests.log): canonical shooting, ordinary shops, key spending and stage-based locks, plus the new upgrade checks.
- [Actual Game/Renderer input](game-input-tests.log): real mouse contact, once-only item collection, next generated Gaper fight using unchanged per-shot damage, keyboard/live/staged settings, Apply/load/export/remember/retry and fresh application loading pass. The target AI is held stationary in the damage input check; this is not new enemy-AI acceptance. Viewed [pedestal](treasure-pedestal.png), [collection](treasure-collected.png) and [tuning](treasure-panel.png) captures show the normal scene and controls.
- [Three CLI launches](cli-validation.json): original schema5 user export, schema28 source-lock export and schema29 treasure export open displayed room8 at normal health and165% zoom. Only these test processes were stopped after startup verification; no new interactive game was left running. The original export SHA remains `77cc7d6783fb903be3b0aeb88b456c64d6ac1c12b30b09d53ea5d831e1bb40cf`.
- [Catalog and preset regression](content-preset-tests.log) passes, including the new invalid treasure-policy/type/reference/range cases. Together with the focused regression run, seven core suites pass.

The first mouse check caught the legacy arrival interaction stopping short of touch distance; source pedestals now walk to contact. Review automation uses visible waypoints when the accepted zoom puts its target under HUD panels. A temporary test compile error attempted to use a private navigation method; the final test cancels movement through normal keyboard input. Neither issue remains in the verified build.

## Center placement correction

The user requested that the pedestal always be in the middle and clear of other objects. Every generated treasure room now sets its pedestal to the exact room center after seeded placement, retaining the original random draw sequence. Before terrain baking, only outcrops intruding into the treasure center clearance are filtered. Existing center reservations exclude decoration, while ordinary pickup placement keeps its distance from the centered objective. The smallest-room check exposed an irregular rock edge too close to a diagonal approach; the explicit outcrop clearance resolves it. No new tuning field or preset migration is needed for this placement rule.

Direct treasure review/debug entry uses a clear position three units from the center, keeping the item visible and avoiding automatic collection or doorway click targets. Normal passage entry is unchanged. The final checks cover27 opening-floor size/route configurations and nine valid later-floor configurations, with centered coordinates, flat/physically clear approach samples, separated coins/keys and retained collection/cadence/persistence behavior. [Core verification](centered-pedestal-tests.log), [actual mouse/keyboard main-game verification](centered-pedestal-input.log), and [inspected centered pedestal](centered-treasure-pedestal.png). An initial later-floor fixture requested a floor outside one seeded expedition's range; the final test uses that expedition's actual final floor.

The correction is rebuilt; an already-running older game process retains its previous layout until relaunched. Human acceptance of the centered placement is pending. The current pedestal mesh remains the existing simple stone geometry. [Existing model candidates and rendered previews](pedestal-assets/README.md) include the low Frontier tree stump, the town church podium and the small flat-top table. No dedicated stone pedestal was found, and the user explicitly chose to keep the current stone model.

## Solid pedestal correction

The user selected “keep current, it should have a collision”. The existing eight-sided stone model, dimensions and material are retained. Treasure-room bases now have a shared octagonal ground footprint used by movement and navigation. Swept checks prevent walking and universal dodge from passing through; character clearance conservatively expands the base prism, rather than the tapered top. Like chests, this low prop does not become projectile cover. This correction covers persistent treasure-room bases, not transient boss reward props.

Clicking the pedestal chooses a reachable edge by actual route length. The source item collects once at that edge; legacy offerings still open their menu at interaction range. Empty bases remain solid after collection and revisit, and regenerated floors retain collision with safe player placement. Geometry is derived from the current room, so it cannot be cleared by the statue/chest movement-body refresh. There is no new tunable or preset change.

[Collision core checks](collision-core-tests.log) pass: 16 directions of actual walking, dodge and click routing; edge collection, solid empty-base revisit, safe Apply and the legacy menu. The existing27 opening-floor and nine later-floor placement configurations and item/cadence/persistence checks also pass. [Four focused regression suites](collision-regressions.log) pass (treasure, chest gameplay, preplaced chests and ordinary shops). [Actual Game/Renderer mouse/tuning/persistence check](collision-game-input.log) passes with the original165% preset; [the inspected collected state](collision-treasure-collected.png) shows the player beside the unchanged solid base. The application is rebuilt. An already-running older process needs relaunching; human collision/placement acceptance remains pending. Full native pickup physics is still unverified.

## Human check

The user subsequently requested “run it”. The interactive main game was launched with the command below; startup confirmed room8, normal health6 and zoom165. See [launch record](interactive-launch.json). Human acceptance remains pending.

```sh
./build/deathward --expedition --seed 69 --review-room 8 --mute --save /home/kambo/.local/share/deathward/reviews/d11a-treasure-upgrade/campaign.save --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json
```

This opens directly in the treasure room at normal health using the accepted map, movement, shooting and165% view. The review starts beside the centered pedestal; click it or walk up to its edge to collect the onion. It disappears, “THE SAD ONION / TEARS UP” appears and firing becomes faster. Leave, fight, and return: the item must stay collected. **TUNING → SHOOTING** shows the unchanged base Tears and effective next-volley rate; **TREASURE** exposes owned count and live strength. Check strength0% then100%, export/reload if desired. Human acceptance is still pending.

## Still unfinished

Human review, full native inventory/cache order and item synergies, complete treasure eligibility/pool exhaustion/RNG, pedestal choice/replacement rules beyond this one ordinary offering, D6/active items, native pickup lifecycle/physics/animation, browser runtime and gameplay-save continuity remain open. The entry in the native treasure XML verifies eligibility; choosing the one implemented item in every scoped treasure room is a bounded content override, not native pool-selection parity. D12 stock/prices/purchases are not started. Bulk parity remains paused.

## Checkpoint and selected continuation

The user authorized this checkpoint and D12a on2026-11-15 (“ok, lets go!”), following the proposed commit and first source shop/red-heart purchase. The seed refresh, D11a, centered placement and retained-model collision are included in this checkpoint. This acknowledgment does not establish a separate observed new playtest or full native acceptance. [Authorization record](checkpoint-authorization.json). D12a is the next selected delivery.
