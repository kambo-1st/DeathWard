# Retired expedition quests and bargain

Requested on 2026-11-17 after scoped acceptance of the Full Fly review: remove Smuggler’s Bargain, the six-miner rescue and the altar subquest.

The bargain no longer generates, displays offers or accepts purchases. Its seeded service slot remains a quiet room; the existing shuffle draw count and Field Surgeon sites are retained. A stale retired service identity cannot open the trade modal or spend resources. The historic enum value and item-pool definitions remain compatible, without providing a new acquisition route for bargain-only items. Already owned items retain their effects.

Miner/altar models, markers, mouse targets, arrival interactions and prompts are removed. The ordinary HUD now shows the expedition floor and guardian objective. Launch descriptions and hub dialogue no longer send the player after the retired objectives. Mine reopening depends on defeating its boss, without a miner-rescue requirement; the altar no longer creates haunting. Stale stranded/haunting flags clear on ordinary campaign resolution. Historical save fields and journal entries remain readable; new summaries do not claim either retired objective.

Room dimensions, corridors, reserved site coordinates and existing source-content exclusions are retained to avoid changing the accepted seeded content layout as part of a quest removal. Controls, balance and preset schema are unchanged; this cleanup does not write the user’s balance/view preset.

Verification passed:

- Main game and affected test targets build. A missing boolean argument in the updated test fixture was corrected before the successful final test build.
- Core contracts: retired locations no longer trigger objectives; new summaries omit their flags; interrupted recovery clears stale quest penalties; boss victory reopens the mine without rescue; campaign history/reload and full expedition progression pass.
- Service contracts:98 generated floors retain resource reachability, only the Field Surgeon generates, former service sites stay quiet, and stale bargain identities expose no offers or purchases.
- Mechanics and companion suites: existing item effects, owned companions, floor carry and historical save-format loading remain valid. Bargain-only items have no replacement natural producer in this cleanup.
- Actual Game/Renderer economy input: quiet former service room, surgeon approach/payment/modal controls and boss reward choice pass. `hud.png` shows the expedition floor/guardian objective without miner/altar tasks. The scripted HUD capture uses default160% zoom; the input check separately loads the archived165% preset.
- Scoped `git diff --check` passes.

Logs are retained in this directory. The user accepted the cleanup and requested a checkpoint commit before a separate pixel-art rendering experiment.

The user accepted this cleanup ("looks good! whats next?").

Unfinished: the next D14a batch remains Round Worm244.0.0/source1.505.0; wider recorded-floor contents and full native actor/selection acceptance remain open.
