# D14a.2 — Full Fly in the recorded two-enemy encounter

The user selected completing D14a in smaller batches. This batch implements Full Fly249.0.0 and the recorded Basement1.704.0 encounter in the main game. Round Worm, the other recorded encounters, treasure/shop dependencies and special rooms are subsequent batches, not silently included here.

## Source and adaptation boundaries

`source/room.json` preserves the installed13×14 record with two Full Flies at(6,5)/(6,8), difficulty5 and weight1. The retained canyon spatial adapter fits these relative centres to the available room; source outlines, door positions and connections are excluded by the user. The existing13×7 selection pool does not contain this shape5 template. A bounded separate allocation therefore chooses an available ordinary room, preserving already complete source rooms, objectives, keys and special roles. This is explicitly a fixed recorded-content layer, not proof of native floor selection probabilities. It requires SOURCE ROOM LAYOUTS; OFF/test-heart modes omit it. Layout edits remain staged until Apply map changes.

Full Fly uses source base HP10/stage HP0 and the shared×3.2 internal unit, giving32 HP and three accepted baseline11.2-damage hits. It belongs to the audited regular-health multiplier. Incoming contact remains one half-heart through ordinary immunity/dodge rules. Existing player movement, shooting, damage, universal dodge and map/view settings remain unchanged.

The shared fly controller now has Full Fly's original diagonal pursuit transform and doubled force, third/fourth-frame buzz behavior and decaying collision recoil. Movement uses the existing D04 fixed player-relative spatial scale. Canyon flight collision supplies the rejected movement vector for recoil and the existing DW RNG supplies draws; these do not establish native collision-normal/global-RNG equivalence. The Skatole pursuit/contact exception is retained without introducing an item producer. The model uses the existing canyon fly artwork with a swollen crimson abdomen.

Death emits six mode9 shots, source speed8 and evenly spaced angles, using the existing ordinary enemy-shot height lifetime. A burst selects its speed once at death; pending and already emitted shots retain it. Capacity-delayed emissions survive actor cleanup without duplicate payout. Debug removal suppresses the burst. The ordinary room-clear path keeps the death projectiles active; leaving the room retains the existing transition cleanup policy.

## Configuration

TUNING → ENEMIES → FULL FLY exposes movement and death-shot speed independently,10–200% in5% steps. Movement applies on the next steering update without discarding momentum. Shot speed applies at the next death. Schema48 exports/loads/remembers both settings and migrates the exact audited earlier catalogs/presets. Current-floor regeneration, retry and floor transition preserve these settings. Preset persistence is not full expedition save/resume.

## Verification and remaining work

The main-game build and four focused suites pass: Full Fly delivery, existing buzzing flies, ordinary room props and the preset contract. The preset contract's invalid-version/duplicate-key fixtures now target schema48. `capture-full-fly.py` and the C++ test agree on70 original pursuit cases, six recoil cases and six radial velocities. Ordinary live simulation checks cover deterministic motion, flight bounds, half-heart contact, three-hit health, exactly six death shots, capacity delay, birth-speed retention, debug removal and projectile expiry.

Twelve generated seed/size cases were examined: eight contain an eligible allocated source704 encounter; the other four have no available compatible site and are not force-filled. All eight witnesses have exactly two flies at the adapted recorded centres, no unrelated destructibles, complete bursts/clear and no respawn on revisit. SOURCE OFF omits the encounter.

The actual Game/Renderer check passes direct entry, mouse tuning/export/load/reset/remember, Apply, retry, burst/clear/revisit and a fresh Game launch. The original preset gives seed1/displayed room5, normal six-half-heart health and165% zoom. Automated death verification uses direct developer damage and god mode to accelerate the check; the interactive handoff does not. Screenshots are `encounter.png`, `death-bursts.png` and `tuning.png`. The tuned screenshot deliberately shows95% movement/105% shot speed; those are not the interactive launch defaults.

Two separate normal main-executable CLI launches confirm schema5 baseline migration and schema48 custom reload, each with the target room, normal health and original zoom. `--smoke` cannot be combined with direct source-room review, so these checks use ordinary launches and terminate only their own test processes after load. The user's original preset remains byte-identical. See `verification.json`, `cli-verification.json` and the saved logs. The user accepted the scoped encounter on 2026-11-17 ("ok, looks good") before requesting the unrelated quest cleanup; see `human-acceptance.json`.

## Interactive review

```sh
build/deathward --expedition --seed 1 --review-source-room 704 --mute --balance-preset /home/kambo/.local/share/deathward/reviews/first-floor-d02/campaign.save.balance/export.json --save /home/kambo/.local/share/deathward/reviews/first-floor-d14a2/campaign.save
```

1. Enter the open floor and evade the two crimson flies. They pursue diagonally with buzzing drift; walking, firing and dodge retain the accepted settings.
2. Shoot each fly. At the accepted unupgraded Damage3.5 setting it takes three ordinary hits; each death releases six bullets. Avoid the burst.
3. Leave and revisit after clearing, or use Retry after death. Cleared flies stay cleared; retry returns to this encounter with normal starting health.

Full Fly tuning is available through the pause menu: Tuning → Enemies → Full Fly. SOURCE ROOM LAYOUTS controls the recorded-room layer through staged Apply.

Unfinished: full native target acquisition, AI/base scheduling, global RNG/constructor/collision/status/champion behavior; source704 native procedural allocation; full D14a contents and live expedition resume. The next small content batch is Round Worm244.0.0 in recorded room1.505.0.
