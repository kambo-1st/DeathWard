# D14a.9 — Temperance and blood donation

Selected by “Nice commit and go!” after scoped D14a.8 acceptance. The accepted Mom’s Coin Purse/pill checkpoint is committed as `340fc763`. This delivery adds Temperance15, an ordinary blood-donation machine, and its two break rewards to the main game. Developer checks pass. The user accepted the scoped main-game handoff on 2026-11-19 (“nice it works, whats next?”); see `human-acceptance.json`. This delivery is committed as `26435e27`.

## Short human check

The review opens directly in **seed6, displayed room7**, with a naturally selected Mom’s Coin Purse195 / Temperance15 pair. The card costs5coins; the purse costs15. The existing shop-review option supplies20test coins and four red half-hearts, with god mode off. It does not grant an item, force the stock or override machine rolls. The isolated schema54 review preset retains the latest user export, including165% zoom,100% room size,7–9 size range,26% routes,Speed1.1 and accepted shooting. Both original exports remain untouched.

1. Walk over **XIV / TEMPERANCE** to buy it. It shares the held pill slot.
2. Press **F** to spawn the machine nearby. **H** drops a held card instead; the existing alternate N/comma binding and HUD buttons also work.
3. Walk or click toward the machine. Each donation costs one red half-heart first. **Step away to stop donating.** A donation can consume the last half-heart. The machine pays after its animation; ordinary outcomes produce one or two coin pickups, or break and drop an item.
4. Blood Bag adds one red-heart container, heals up to five red hearts and adds0.3 Speed. IV Bag uses the existing active-item key (**C** by default), costs one half-heart and pays coins, with a0.5s reuse cooldown and no room-charge requirement. It swaps with the existing active; the outgoing item keeps its charge on the ground.
5. **TUNING → SHOOTING → PILLS → TEMPERANCE** edits the machine. **REWARDS / TESTING** includes an explicitly labelled outcome override for quickly checking either break reward. Set it before donating; a cycle already paid keeps its selected settings. Retry returns to the shop with clean ownership and retained tuning. The shipped review preset uses **SOURCE ROLLS**.

Machine artwork is an original wood/brass donation pump with a red reservoir; the card and bags use original low-poly geometry. Its solid footprint participates in ordinary movement and click navigation. A broken remnant is non-solid.

## Source evidence and precise limits

`source/manifest.json` pins installed **Repentance1.7.9b**, executable SHA256 `04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6`, XML entries and original-code windows. The capture scripts execute original bounded instructions with explicitly supplied state. They do not certify complete live actors.

- Four card cases execute the original Temperance branch and confirm a6.2.0 spawn request. Position/factory calls are hosted. Canyon placement scans safe reachable sites, preserves the card on failure and advances its separate DW seed stream only on successful admission.
- Six ordinary contact cases establish the hurt-counter gate, one-half-heart red-first damage request,30 cooldown argument and Initiate request. The native caller ignores damage denial. DeathWard retains its shared health consumer and existing Book/god protection; universal dodge prevents activation and remains immune. This is not full native damage-flag, special-character, later-stage or invulnerability-scheduler acceptance.
- **1,040 payout cases** verify original source rolls and final RNG state across Blood Bag unlock/IV availability inputs. The ordinary Normal branch consumes the Child’s Heart draw, rolls a1-in15 break, then selects a break reward or `max(1, next % 3)` coin actors. Child’s Heart is absent from the supported catalog, so that eligibility is supplied false. Default Blood Bag eligibility is on; IV availability becomes false after its first machine reward in the expedition. Native profile/achievement/pool depletion is not implemented by those adapters.
- **256 IV draws** verify ordinary coin counts. Its original use branch requests one half-heart; XML records cooldown15/maxcharges0. The explicit30Hz adapter maps that to0.5seconds. Full native active-input, damage flags, character effects and scheduler remain unverified.
- **Five Blood Bag cache cases** verify +0.3 Speed per copy before final caps. XML supplies maxhearts2/hearts10, consumed by the existing half-heart APIs. Speed combines with pill contributions before the retained0.1–2 adapter cap; the editable base and absolute dodge stay intact.
- **Thirty ordinary card prices** verify5coins, and six category6 dispatch slices reach variant300 and the supplied Temperance-only GetCard result. They stop before later subtype wrappers. The existing Steam Sale/sale-slot calculation remains shared. The restricted card pool and stock pair do not certify the complete recorded shop, full native card pool or shop factory.
- ANM2 metadata pins card Appear35/Drop26/Collect16, machine Initiate8, Prize8/eventframe3, and the other machine states. Payment-to-prize uses30world ticks followed by eventframe3; payout is at33/30seconds and ordinary idle resumes at38/30seconds, under the explicit active-room30Hz adapter. Full native animation scheduling remains open.

Ordinary coin subtype selection reuses the enabled rare-gates-off policy. Safe physical placement, contact boxes, projectile passage through low props, separate seed streams, fractional custom break multipliers and original visuals are DeathWard adaptations. Source values remain separate from overrides. **Machine bombing/explosion destruction is not implemented or verified in this bounded donation delivery.** Full machine actor equivalence is not claimed.

## Configuration and lifecycle

Schema54 (`d14a9-temperance-v54`, mechanics fingerprint `6e7b8382ade04b60`) adds `temperance` and migrates schemas1–53 with default Temperance settings, retaining existing values. Invalid/incompatible files are rejected before application.

| Setting | Default / range | Application boundary |
|---|---|---|
| Card price | 5 / 0–30, steps1 | Unsold card; existing discounts apply |
| Donation cost | 1 half-heart / 0–4, steps1 | Next machine/IV payment |
| Machine cycle speed | 1 / .25–4, steps.05 | Next paid cycle |
| Break multiplier | 1 / 0–3, steps.05 | Next paid cycle; source1-in15 at1 |
| Coin payout multiplier | 1 / 0–3, steps.05 | Next cycle/IV use; integer actor counts round |
| Blood Bag Speed strength | 1 / 0–2, steps.05 | Owned copies, live |
| IV cooldown | .5s / .1–3s, steps.05s | Next IV use; current wait retained |
| Outcome | Source rolls / coins / Blood Bag / IV Bag | Last three are labelled testing overrides; next cycle |

Source base health/stat values and ordinary machine defaults are not changed to hide adaptation. Active cycles and emitted pickups retain their selected data. Pausing/inactive rooms stop machine actor phases; revisit keeps the machine state and ground items. IV cooldown advances with active gameplay. Item swaps require leaving contact before recollection.

Apply keeps the held consumable, build, active slot/charge, IV cooldown/availability and tuning. It resets floor machines/ground items like other floor actors. Already resolved queued rewards retain their identities and are remapped to the regenerated room; an unfinished machine animation is a reset floor transient. Descent retains held/build/configuration, leaving ground and pending floor drops behind. Retry creates clean ownership with retained configuration. Map changes remain staged until Apply; live edits do not apply pending map settings.

Campaign format12 records IV Bag’s zero-charge active identity in the existing checkpoint/interrupted-history summary and reads older versions. **This is not live expedition resume.** Ground machines, cards and consumed pills are not a resumable gameplay save; that remains D18.

## Verification

`verification.json` and the adjacent evidence contain:

- Native arithmetic/contact/card/cache/price evidence described above; C++ comparisons against1,301 native payout/IV/Speed rows.
- Real Simulation card/pill swaps, use/drop rearming, denied placement, eight click-approach directions, collider removal, red-first health, hurt/Book/dodge boundaries, lethal donation, exact adapter payout/idle times, live-cycle snapshots, active swaps/cooldown and capacity recovery.
- Naturally generated seed6 shops at75%/fixed5,100%/range7–9 and150%/fixed10 room sizes; five-coin purchase, actual click arrival, Apply and floor transitions.
- Nine focused suites: Temperance, coin purse, preset, treasure, shop stock, shop collectibles, native shop stock, Book of Shadows and heart gameplay. All pass.
- `game-review.cpp`: actual Game/Renderer, mouse purchase/approach, F/H/C, all eight settings, keyboard navigation, export/load/remember, pending Apply, retry, next launch and both reward visuals. Testing branches are confined to the harness; the review preset stays at source rolls.
- Three fresh CLI loads: original schema48 export, latest schema53 export, and current schema54 preset. Source preset hashes are unchanged.

The click test caught the retained0.04world-unit arrival tolerance just outside the original machine contact threshold; the machine-only threshold now accommodates that tolerance without changing movement. The harness also waits for the collectible’s admission delay. New machine collision bodies are appended only by the shared body rebuild, not by statue refresh.

## Unfinished / next proposed

Scoped human handoff acceptance is recorded; D14a.9 is committed as `26435e27`. Full machine explosion destruction, native factory/damage flags/scheduler/physics/unlocks/pools/RNG, special characters/Hard/Greed and unusual synergies remain open. The full pill/card catalogs, full native shop behavior, remaining special rooms/full-floor allocation and live expedition save/resume remain unfinished; pixel/performance work is deferred. D14a.10 now enables the recorded rocks/stock arrangement with an explicit keeper-wagon adapter; its human review is pending.

The user selected the recorded shop continuation with “ok, conitnue”; see [D14a.10](../d14a10-recorded-shop/README.md) for the enabled arrangement and remaining keeper behavior. No unrelated bulk parity is authorized by this report.
