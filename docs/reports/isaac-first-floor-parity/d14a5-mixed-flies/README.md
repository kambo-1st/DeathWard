# D14a.5 — recorded mixed fly room

Selected on 2026-11-18 after accepted D14a.4 commit `7bb4fb44`. **Main-game implementation and developer checks pass. The user acknowledged the wider-pile checkpoint and selected continuation on 2026-11-18. Full native actor acceptance remains open.**

The opening floor can now contain complete recorded Basement **1.414.0**: eight ordinary Pooters14.0.0, twelve ordinary Attack Flies18.0.0 and twenty ordinary poop grids, with no initial pickups. The forty original cells, singleton choices and slot order match the preserved installed STB. Existing Pooter attacks, poop collision/destruction/rewards, player settings, HP/damage, eight-direction controls and universal dodge remain in use.

## Attack Fly movement

Ordinary room Attack Flies now use the fixed accepted D04 base-player scale, `4.8 / (4.414238452911377 × 60)`, instead of the historical `.1` world scale. The preserved source pursuit still halves the second axis, uses deadzone25/gain.08/force cap1.2, refreshes targets every third source update and applies pursuit every second update. Fourth-update jitter and third-update friction remain. The selected controller now applies AI at the beginning of each local 30 Hz interval.

Source HP remains5, stage HP0 and internal conversion×3.2, giving16 internal HP and two ordinary11.2-damage hits. Contact removes one half-heart through the shared hurt path; ordinary contact does not consume the fly. No HP adjustment was used to change pressure.

**TUNING → ENEMIES → FULL FLY → ATTACK FLY** edits movement in5% steps, from10% to200%. The next steering update uses the edit; position, current momentum, cached target and clock are retained. Pooter, Full Fly, Duke children and other summoned flies retain their separate controls/policies. Historical standalone Simulation fixtures remain opt-in.

Schema51 exports, loads and remembers the independent multiplier, migrating schemas1–50 to100%. Retry, Apply map changes and floor transitions retain it. Live edits preserve pending map settings; loading a preset stages its map changes. The user's original export was read only, with SHA256 `22e143a736697ccc780ab31bde3c3a1f7ac0d88392e9bf7aa45055ccd3895604`.

## Canyon placement and scope

Source shape8 and26×14 dimensions describe the content coordinates only. Exact source size, shape and connections remain excluded by user choice.

This record is outside the existing13×7 native-selection pool. A bounded DeathWard allocation considers one remaining compatible ordinary combat room after the existing source704 allocation. Complete source rooms, story/service/shop/treasure roles, objective indices2/3, mandatory-key sites and preplaced pickup layers are preserved. SOURCE ROOM LAYOUTS and PROPS must both be enabled. This is **not native weighted floor allocation or reproduction of the recorded floor seed**.

The complete arrangement is uniformly fitted inside the existing canyon. A final check uses the finished terrain, all actor/prop footprints and doorway landing areas. The content cell can contract in1% steps while retaining at least.95 world spacing for adjacent.45-radius actors. An incompatible candidate is rejected as a whole and generated terrain/content restored. Testing resize remains unrestricted; it can remove this encounter without blocking Apply or truncating its roster.

An initial generated test exposed slot33 touching an irregular cliff. The finished-terrain fit fixes that case; room outlines and corridors were not changed. Expanded grids retain their source28-column indices and original slot seeds, with a separate prop-ID namespace so indices above255 cannot collide with another room. Player navigation uses the fitted content spacing. Enemies remain flyers using the existing canyon flight/height/collision adapter.

## Verification

- [Native capture](source/manifest.json):63 executed ordinary Attack Fly pursuit cases from the pinned installed executable; the existing16-window Attack Fly source extraction also rechecks successfully. [Content verification](content-verification.json) matches all40 STB entries exactly.
- [Runtime core](runtime-core.log):567 actual Simulation comparisons across three update partitions and three movement settings, plus independent control, contact/hurt/dodge, floor retention, migration, round-trip and invalid-value checks. These are bounded supplied-force/cadence checks, not full native AI/RNG/scheduler acceptance.
- [Generated room checks](room-sizes.log):110%/7–9 at seed11,120%/8–9 at seed31,150%/10–10 at seed1. All open in displayed room5 with8 Pooters/12 Attack Flies/20 poop grids. Real player projectiles clear all20 enemies; exposed poop destruction resolves once and persists on revisit. OFF/SOURCE Apply, props OFF and unrestricted75%/5–5 regeneration pass. Automated combat uses test positioning and god mode; it is not human pressure acceptance.
- [Regressions](regressions.log): seven completed CTest suites pass for presets, Pooter, Full Fly, Round Worm, Frowning, Duke and ordinary props. The enclosing CTest process ended with143 before the remaining buzzing suite completed; that suite was rerun separately and [passes](buzzing-flies.log). No complete eight-suite CTest run is claimed.
- [Actual Game/Renderer](game-review.log): normal-health direct entry, mouse navigation/edit/reset/export/load/remember, staged Apply, retry, live movement, clear/revisit and fresh remembered startup pass. [Encounter](encounter.png), [tuning](tuning.png) and [pressure](pressure.png) captures were inspected; displayed FPS is not a benchmark.
- [Four independent CLI launches](cli-verification.json) load schemas5/48/50/51. The current original preset opens source414 at six half-hearts with god mode off; zoom165 and the other existing values remain. The original file hash is unchanged.

The earlier `runtime-room.log` also preserves the successful110% case and a failed assumption that the same seed would select414 at120%; the final size checks use actual compatible witnesses. The medium test originally targeted a corner pile screened by neighbouring source piles. Its corrected check fires at an exposed pile and retains the source access arrangement.

## Human check

```sh
build/deathward --expedition --seed 11 --review-source-room 414 --mute --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d14a5/campaign.save.balance/export.json --save /home/kambo/.local/share/deathward/reviews/first-floor-d14a5/campaign.save
```

The review export path above starts as a byte-for-byte copy of the unchanged original D02 export. Starts in displayed room5 with the original165% zoom and normal health. Move into the room, compare the pursuing Attack Flies with the wandering/shooting Pooters, shoot poop, and clear the encounter. Retry returns directly here. The Attack Fly percentage can be changed independently in TUNING; Export and Use next expedition keep edits in this review's separate directory.

## Unfinished

Human movement/pressure/placement acceptance; full native target acquisition, RNG order, global scheduling, animation/status/item wrappers, physical geometry and lifecycle equivalence; native full-floor allocation and descriptor consumers; the exact recorded Duke starting arrangement, remaining recorded treasure/shop/special-room dependencies, complete-floor review and gameplay save/resume. Pixel/performance work stays deferred. After this scoped playtest is accepted, commit it and propose the recorded Duke room's initial Attack Fly, four rocks and two poop grids as the next small delivery. Do not start that delivery automatically.

## Wider poop — requested follow-up, 2026-11-18

The user requested much wider piles. Fixed ordinary-pile width/depth now uses105% of the original authored footprint instead of70%, a50% increase in the presentation factor. Height stays105% (1.155 for these source piles). Rendering and collision share the widened bounds; the accepted small destroyed crumbs retain their previous footprint. Legacy placement checks now use the final bounds, and source414 fits reserve the widened footprint's half-diagonal. This is a fixed presentation adjustment; source hit counters, drops, controls, balance, map dimensions and preset schema are unchanged.

Five existing geometry/prop suites pass, including the mixed encounter at all three sizes and the previous Frowning room. The actual Game/Renderer opens seed11/displayed room5 with20 actors/20 piles, normal health and zoom165. The measured pile width is1.04526 and height1.155. Finished-terrain fitting contracts the source cell slightly (1.02168 →.995483), so the actual width in this room increases approximately46%, while the presentation factor increases50%. See [the new capture](wider-poop/encounter.png), [geometry checks](wider-poop/geometry-checks.log) and [render check](wider-poop/game-review.log). Legacy fly/dung regression completion is recorded in `wider-poop/verification.json`.

Human acceptance of the wider presentation and mixed-room pressure remains open; the broader unfinished work above is unchanged.

## Second width increase — requested follow-up, 2026-11-18

The user requested even wider piles. The intact width/depth factor increases another25%, from1.05 to1.3125, while height remains1.05 and the small destroyed crumbs retain their previous scale. At seed11/displayed room5, actual measured width grows from1.04526 to1.28938 (23.35% after finished-terrain fitting); height remains1.155. This is approximately80% wider than the original D14a.5 handoff. Rendering and collision still share the same bounds.

Source prop-room flyers now use the established flight admission and flight-height path, so nearby wider piles do not incorrectly reject actors that fly above them. Grounded actors retain ground collision checks. No enemy motion/HP, player controls, source slot identities, map dimensions or preset schema changed.

Four geometry/prop CTest cases pass: source414 at all three sizes and ordinary props. The original Frowning fixture expected a destroyed pile's centre to become player-accessible even while its wider neighbour still overlapped that position. Diagnostics confirmed successful destruction/reward, clear terrain and one intact neighbouring pile. The corrected fixture shoots that neighbouring pile too and verifies access; all three Frowning size cases pass. The legacy fly/dung suite and actual Game/Renderer capture pass. See [verification](wider-poop-2/verification.json), [capture](wider-poop-2/encounter.png) and [Frowning access checks](wider-poop-2/frowning-final.log).

Human width/pressure acceptance is still pending. The next step remains this playtest, then committing the accepted D14a.5 checkpoint; remaining recorded-floor dependencies and full native equivalence are unfinished.

## Scoped acknowledgment and continuation, 2026-11-18

The user replied “ok, contnnue in your next tyhings” after the second width follow-up. This acknowledges the checkpoint and selects the next bounded recorded Duke arrangement, D14a.6. No separate detailed mixed-room pressure verdict or full native acceptance is inferred. See `human-acceptance.json`. The remaining actor/floor/item/save gaps above stay open.
