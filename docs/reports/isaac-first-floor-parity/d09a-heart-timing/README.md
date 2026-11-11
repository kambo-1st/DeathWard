# D09a continuation — ordinary red-heart birth and collection timing

The user selected this first slice after the heart-spawning gap review. Full, half and double red hearts now use the bounded source appearance/collection timing in the **main game**. Placement/collision redesign, other heart outcomes/producers and coins are not selected by this continuation. Human review and full native lifecycle acceptance remain open.

## Playable check

From the repository root:

```sh
build/deathward --expedition --seed 69 --mute --save /home/kambo/.local/share/deathward/reviews/first-floor-d09a-timing/campaign.save --balance-preset docs/reports/isaac-first-floor-parity/d03-shooting/user-preset-2026-11-11.json
```

This retains the accepted 165% zoom, walking, shooting and map settings. Normal damage and enemy AI are active. Retry remains available after death.

1. Clear the adjacent two-Gaper encounter, displayed room 3. At base Luck 0 this seeded first clear produces a full red heart.
2. Watch it settle before it can be picked up. At the default appearance speed the game opens the gate after 25 source-frame steps, about 0.83 seconds through the explicit 30 Hz adapter. This is not an independently measured native factory-to-contact wall-clock result.
3. At full health the heart remains. With missing red health, touching the ready heart heals up to one full heart immediately and plays a brief collection effect. It cannot heal twice. Leave and return: it remains collected.
4. **TUNING → REWARDS → APPEAR SPEED** edits future heart births in 0.05 steps. Existing actors retain their birth speed. Export, load and **USE NEXT EXPEDITION** include the value; older presets migrate to 1x. A remembered custom value applies on a later launch without a CLI override. The command above explicitly reloads the accepted preset and therefore selects the 1x baseline.

No pickup redesign or forced demonstration reward is used. The producer's seed and eligibility are the existing D09a rules. Main-game screenshot/test fixtures use held AI/god mode only to verify repeatable input; those are absent from the interactive handoff.

## Source evidence and boundaries

- The three installed full/half/double-heart ANM2 files all specify **Appear 33 frames**, **DropSound at frame 25**, **Collect 12 frames**, and metadata FPS 30. [Extraction manifest](animations/manifest.json) pins archive paths and hashes. No sprite artwork is imported.
- Native `Pickup::Init` includes the `Appear` call and collision class zero at `6b7bf2..6b7c11`; the initial touch counter is zero at `6b706a`. [Appearance callsite](pickup_initial_appearance.asm), [counter](pickup_initial_counter.asm). The entire factory/room-clear wrapper is not executed by this capture.
- [40 native gate cases](native-appearance-gates.csv) execute the installed name/playing/event queries and collision gate. A recognized appearance opens collision on DropSound, with completed-animation fallback. Existing collision eligibility is retained.
- [2,115 native appearance states](native-appearance-timelines.csv) execute original layer frame advance, original linked UCRT floor, event-mask generation and the pickup gate using the installed red-heart metadata. Speeds .25, .5, 1, 1.05 and 4 cover baseline and custom playback, including fractional event crossing. Speeds other than 1 are explicitly test overrides, not a source balance claim.
- [48 native collection states](native-collection-timelines.csv) execute the original nonlooping Collect frame progression and consumed-actor cleanup decision. Consumed state is supplied; execution stops at the virtual Remove endpoint. [Collection tail](pickup_collection_tail.asm) separately records disabling collision, playing Collect and setting the consumed flag.
- The fixture hosts only sound/Play(Idle) presentation and the Remove endpoint. Initial animation/consumed state and update invocations are supplied. Native physical/health contact prechecks, complete factory, scheduler/room persistence and live OS loader are outside this capture. [Capture manifest](manifest.json) records exact scope and hashes.

Reproduce the capture with `PYTHONPATH=/tmp/deathward-native-emulator python3 scripts/isaac-reference/analyze-red-heart-timing.py --check`; the environment needs pefile, capstone and Unicorn 2.1.4. `python3 scripts/isaac-reference/extract-red-heart-animations.py --check` verifies the local animation extraction. Neither command modifies the installed game.

## Enabled behavior

`RedHeartTiming` advances in active-room 30 Hz steps, retaining fractional elapsed time across game updates. The default appearance opens collection at frame 25 and settles to Idle at frame 33. Accepted collection changes health once, disables further admission and removes the presentation after 12 steps. Canyon descent/fade visuals are an explicit art adaptation.

Birth starts when a pending award actually obtains a legal actor slot, after that update's aging/collection pass. Capacity/placement waiting does not pre-age the actor. Paused gameplay and inactive rooms do not advance these actors; re-entry resumes the stored phase. A consumed actor can finish its remaining effect on revisit without paying again. Directly placed legacy typed-health pickups retain their prior idle behavior; only selected ordinary red-heart clear rewards start this appearance lifecycle.

The new `red_heart_appearance_speed` configuration is bounded to .25–4, defaults to 1 and is snapshotted at actor admission. It changes only appearance, not healing quantities, reward rolls or the 12-frame collection effect. Schema **12** records immutable reference timing separately from overrides and migrates schemas 1–11. Loading rejects invalid/incompatible settings atomically, stages map edits and applies appearance configuration to future births. Map regeneration, floor descent, retry and fresh launches retain the configured value.

## Verification

Seven focused suites pass: native heart timing, reward reference, reward gameplay, source combat room, preset contract, typed-heart gameplay and native player health. Runtime cases include natural full/half/double outcomes, exact admission/removal boundaries at 30/60/120 Hz, full-health refusal, clipped/once-only healing, retained birth speed, pause/inactive/revisit behavior and deferred-capacity birth. See [gameplay checks](gameplay-tests.log), [reference/preset checks](reference-tests.log) and [health/timing checks](health-tests.log).

Actual Game/Renderer mouse/keyboard checks cover a naturally cleared encounter, the appearance edit/reset, paused timing, collection, retained pending map edits, export/load, invalid isolation, floor/retry and fresh-session configuration. See [input check](input-tests.log), [controls](panel.png) and [birth](birth.png). Four separate CLI launches verify schema-5 migration, schema-11 migration, custom schema-12 loading and remembered reload. The accepted preset's hash is unchanged. [Validation](validation.json).

## Unfinished and next

**Human timing acceptance is pending.** Full native factory/scheduler/physical collision and room-transition timing, placement/grid/vertical physics, unlock/modifier profiles, other heart outcomes/producers and matched live encounter acceptance remain open. The existing source-to-canyon spatial and room-seed adapters remain explicit. No HP, damage, walking, shooting, dodge, reward-odds or enemy behavior changes are part of this slice.

Next proposed selectable slice after this check: **heart placement and collision**, followed by the matched native encounter check. Coins and broader heart work remain unselected. D08/D09a and this timing continuation remain uncommitted; the latest committed delivery is D07 `56743a72`.
