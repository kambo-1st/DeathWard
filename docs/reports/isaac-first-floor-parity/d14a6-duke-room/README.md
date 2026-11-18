# D14a.6 — recorded Duke starting arrangement

Selected on 2026-11-18 after the user acknowledged the wider-pile checkpoint and requested continuation. D14a.5 is committed as `598cbc77`. **Main-game integration and developer checks pass. The user accepted the scoped handoff on 2026-11-18 ("lookss awesome! Whats next?"). Full native acceptance remains open.**

The opening-floor Duke choice now uses recorded boss **5.2012.13** when SOURCE LAYOUTS and source FIRE / POOP layouts are enabled and the full arrangement fits: Duke67.0.0, one initial ordinary Attack Fly18.0.0, four plain rocks and two poop grids. All eight original cells, singleton entries and slot order match the preserved installed Repentance1.7.9b STB and the recorded source floor. The initial fly is independent of Duke's summoned cohorts and participates in the ordinary room-clear gate.

Existing Duke/Attack Fly controllers, source HP and internal conversions, damage, player movement, shooting, eight-direction controls and universal dodge remain. The accepted wider poop bounds and small remnants are retained. This delivery changes the initial arrangement; it does not certify full native actor or factory equivalence.

## Configuration and placement

The existing SOURCE LAYOUTS, FIRE / POOP source selection and fixed/seeded boss selection control this arrangement. Their edits remain staged until **Apply map changes**. Switching to Monstro, legacy/test props, OFF/test layouts, or another floor excludes the recorded arrangement. An incompatible canyon omits the complete arrangement and keeps its existing Duke arena; resizing is never blocked. No new tunable or preset field is introduced: schema51 retains export/load/remember and migration. Existing live Duke health/movement/offspring speed and independent ordinary Attack Fly movement still apply through their established consumers.

Source13×7 dimensions, shape1 and door positions describe only content coordinates. A uniform content fit checks finished canyon terrain, prop footprints, actor clearance, doorway landings, floor exit and central reward space. Room outlines and connections stay DeathWard's. The fit now processes both source414 and the boss candidate; failure of one does not skip checking the other. A rejected candidate restores ordinary procedural terrain. Duke gets a conservative2-unit fit margin around its retained1.615-unit body.

Boss content uses an independent DeathWard allocation seed and the existing descriptor/slot seed adapter for prop drops. This is fixed recorded content for a supported boss choice, **not native weighted boss-room selection or reproduction of source seed2FFX8XJH**. Native actor initialization RNG, full pickup factory, native physical dimensions and complete source floor allocation remain unverified.

Boss rewards keep the user's existing Breakfast/Screw setting; the arrangement does not change it globally. The separate review preset selects fixed Duke and Screw255, preserving the user's other resolved settings including165% zoom. The original export stays untouched.

## Developer verification

- `content-verification.json` compares all eight entries with preserved `00.special rooms.stb`, SHA256 `a8f7bd23a0362703ffe6ad4a6b80756a2894b01ba710266cc80f1d40e93eb432`. `source-room.json` preserves the original captured identity/context.
- `runtime-tests-final.log`: seed11 at75%/5–5,110%/7–9 and150%/10–10; exact actor/prop cells and counts, terrain/route checks, independent initial fly, retained HP352/16, real projectile kill of the last fly, six existing Duke death offspring, sealed reward/exit while the initial fly survives, real-shot poop destruction, once-only Screw, revisit and descent. Boss/offspring removal uses developer damage events; this is not a human pressure verdict.
- SOURCE/OFF/test/Monstro boundaries and unrestricted Apply preserve health/tuning and safe player placement. Later floors omit the record.
- `regressions.log`: seven suites pass (two mixed-fly sizes, ordinary props, Screw, seeded bosses, Duke and Monstro). The older bare-Duke test now explicitly disables source props; the seeded-boss test clears the new initial fly before expecting its reward. The new test separately asserts that leaving it alive keeps the gate locked.
- `game-review-final.log`: actual Game/Renderer normal-health direct entry, six props, retained165% view/player settings, mouse live Duke HP with injury/phase preservation, export/load/remember, staged OFF/SOURCE Apply, retry and fresh startup pass. `encounter.png` and `tuning.png` were visually inspected. The final review approach keeps the boss visible without changing ordinary room entry.
- `cli-verification.json`: separate schema48 original-preset migration and schema51 fixed-Duke/Screw direct launch pass. The original user export is unchanged (SHA256 `22e143a736697ccc780ab31bde3c3a1f7ac0d88392e9bf7aa45055ccd3895604`).
- Build and `git diff --check` pass. Displayed capture FPS is not a performance benchmark.

## Human check

The main-game review uses seed11, displayed room9, normal six-half-heart health and165% zoom. `--review-source-room 2012` opens near the generated boss on a clear, reachable approach; ordinary entrance behavior is unchanged.

```sh
build/deathward --expedition --seed 11 --review-source-room 2012 --mute --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d14a6/campaign.save.balance/export.json --save /home/kambo/.local/share/deathward/reviews/first-floor-d14a6/campaign.save
```

1. Move around Duke, the initial fly and the four rocks/two wide poop piles.
2. Defeat Duke and all remaining flies; shoot a pile to check collision/destruction.
3. Take Screw and descend. Retry returns to this same encounter if you die.

## Unfinished and next proposal

Full native actor/RNG/scheduler/factory/physics equivalence; native full-floor allocation; the recorded treasure/shop/special rooms; full expedition save/resume. Pixel/performance work stays deferred.

Next, checkpoint this accepted delivery. The proposed **D14a.7** is recorded treasure4.6.0 with Mom's Eye55 and two pennies, including verified Mom's Eye firing/Luck behavior while retaining eight-direction controls and live/export/load settings. That item delivery is not started or selected by this handoff.

## Human acceptance, 2026-11-18

The user accepted the scoped handoff with “lookss awesome! Whats next?” See `human-acceptance.json`. This is not a claim of full native equivalence or that every checklist action was reported complete. D14a.6 remains uncommitted; the next-step question does not select D14a.7 or request a commit.
