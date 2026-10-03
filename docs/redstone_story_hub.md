# Fort Mercy: the stranded-train story hub

The current story replaces the earlier wife/spiritualist/abandoned-baby outline.
The physical hub keeps its existing Redstone asset directory, map, scene IDs and
`--hub redstone` / `?hub=redstone` launch options. Its displayed story name is
**Fort Mercy**. No map placements or user-authored scenes are rewritten.

Implemented: train opening, arrival conversations, overnight rest, the single-floor
survey tutorial, Eleanor's readable letter, persistent recovery and the commander's
return conversation, and Rourke's first testimony run with a persistent field
journal and Eleanor's response. Eleanor's, Mercer's and Cole's expeditions and
the final departure remain planned.

## Arrival quest prototype

1. **Sunset:** ask the conductor about departure. He expects the next morning if
   the wind drops and directs the player to the passenger tent.
2. **Rest:** sleep in the tent; morning sunlight replaces the sunset.
3. **Morning:** the line is still closed. The conductor points to the commander.
4. **Commission:** recover Silas Bell's missing survey records to help the railroad
   inspect the route ahead. Eleanor is Bell's daughter and is already back at the
   fort. This is not a search for the commander's daughter.
5. **The Lost Survey:** one generated canyon floor with five connected rooms: a
   quiet entrance, two basic enemies, a quiet bend, three basic enemies, and the
   peaceful survey camp. Room sizes, bends, obstacles and terrain follow the seed.
   The normal canyon creatures are retained for this tutorial; their story role
   remains a separate design question. There are no locks, shops or boss encounters.
6. **Documents:** click the leather case, or approach and choose Recover records.
   It contains the survey sheets and an undated letter signed Eleanor. Reading
   pauses gameplay. Close the letter and use the return lantern; there is no next
   floor. Clearing enemies or using a victory cheat does not recover documents.
7. **Report:** return to the commander, who accepts the records and distinguishes
   Eleanor's written claim from an established explanation of Bell's death. He
   mentions the detained guide Caleb Rourke. Completing this conversation closes
   the tutorial and points to Rourke in the holding yard. The letter remains
   readable from the quest panel.

The letter asks why the northern cutting differs from the route Bell showed
Mercer and objects to Bell calling Eleanor's questions weakness. This is a new
introductory clue, not proof of corruption, guilt or the sequence at the creek.

Click gold markers or Current objective to walk to conversations. WASD or a new
movement click cancels the approach. Enter/Space advances dialogue; Escape or
Not yet leaves the conversation unfinished. During letter reading these keys
close the letter and cannot move/fire or open the editor. Tutorial hints introduce
walking, shooting, cover, dodging and document interaction without requiring a
particular input method or forcing players to perform artificial checklist tasks.

Quest flags remain under `redstone.*`. Old `redstone.daughter_missing` progress
is accepted as the new survey commission, retaining completed arrival dialogue.
Campaign format 5 stores floor progress and evidence provenance alongside the
recovered-document bit; formats 1–4 remain readable. Document pickup requests an immediate checkpoint. The copied
information survives death, retreat or interrupted-session recovery and points
back to the commander. Without the documents, the trail remains retryable.
Legacy pending Before First Light runs recover without mine-related consequences.
Story returns never rescue miners, destroy the altar, change mine prosperity or
award the unrelated boss outcome. Ordinary missions retain their own rules and
15-room layouts.

The conductor follows `quest-conductor` if authored in the editor; otherwise he
appears beside the train. Sleep uses `story-settler-tent-0:*`, the commander uses
`story-commander`, and departure uses the map's mission point. Moving these in the
editor moves their quest targets. The story cast still uses provisional models;
legacy witness IDs and placements are retained. Their displayed names now identify
Eleanor, Rourke, Mercer and Cole. Rourke's and Eleanor's current conversations use
`story-outlaw` and `story-wife`; moving those residents moves their quest targets.
Final costumes and later conversations remain future work.

Fresh playtest:

```sh
./build/deathward --hub redstone --save /tmp/deathward-survey-demo.save
```

Use `--full-experience` for the logo/save-slot/opening flow. A completed existing
arrival save continues at its current objective. The browser uses the same logic
and its existing persistent save slots. Native CPU verification is
`deathward_arrival_quest_tests`; explicit graphics/input verification is
`deathward_arrival_input_tests`, with `web/arrival-test.cjs` for the browser.

## Full expeditions and the first account

Every non-tutorial expedition now has **4–8 floors selected by the run seed**.
Each floor retains the existing **15-room** generator: branching paths, combat
seals, Isaac monsters in canyons, quiet rooms, one shop, keys and 1–2 power rooms.
Ordinary mine missions use the same floor progression with their Western roster.
The tutorial remains the sole one-floor/five-room exception.

Clear the final room and use its lantern to continue to the next floor. The last
floor's lantern returns to the hub. Health, damage, loaded revolver round, powers,
keys, money, dynamite and run statistics carry forward. There is no free heal.
Layouts, enemy groups, shops, ground loot and power choices are generated afresh
from each floor's derived seed; old projectiles and hazards are discarded.

After the tutorial report, speak to **Caleb Rourke**, then use the badlands trail
to follow his account. The HUD names him throughout the expedition. Four authored
sites are inserted within the ordinary networks:

| Site | Floor placement | Role |
| --- | --- | --- |
| Survey Camp | First | Route sketch and survey equipment; establishes a stop, not a motive. |
| Split Rock | About one third through | A matching landmark; no recovered payroll money. |
| Old Railway Cutting | About two thirds through | A firing position his duel account omits; timing remains uncertain. |
| Dry Creek | Final floor, final room | Bell's revolver has one discharged chamber despite Rourke's repeated-fire claim. |

The first three occupy seeded ordinary rooms and preserve their encounters.
The last occupies the final combat room. Floors between these beats remain full
combat floors. Story dressing checks flat terrain, roads, rivers and approach
clearance; carts and rocks have collision. Rooms keep their generated shape.
These are inspectable sites with written accounts, **not animated duel scenes**.

`?` marks the required site on the current floor map. Clear its encounter, then
click the evidence or choose **Examine site** nearby. The field journal separates
**Witness claim**, **Recovered observation** and **Open question**, with the account,
floor and floor seed attached. Reading freezes gameplay. **Journal** or **J**
reopens it; arrows and Previous/Next change entries. A story floor's exit waits
until its site is examined, so no required clue is lost by advancing.

The completed run unlocks Eleanor's response at her shelter. She disputes the
treasure story and says her father was alive when she returned. This is another
claim, not a verdict. Her expedition is the next development slice. Cole's future
unheroic version must retain the same explicit attribution.

Evidence inspection and floor transitions checkpoint immediately. Saved records
validate their witness, site, floor and derived seed. Retreat, death and interruption
preserve inspected observations in history and the journal, but do not complete
Rourke's run. Retrying starts a new complete expedition; old journal entries do
not bypass its required inspections. As before, closing/reopening a pending run
returns to the fort using the checkpoint; exact mid-floor simulation resume is
not implemented. Historical runs retain all their records; the journal displays
the latest observation for each site/account pair.

Verification: `deathward_expedition_tests` checks plans, full room networks,
story-site access, carry-over, completion, interrupted evidence, witness routes
and save migration. `deathward_arrival_input_tests` exercises the full tutorial,
Rourke launch, floor transitions, mouse inspection/journal and Eleanor return.

## Physical hub

The [placement review](redstone_placement_review.md) records the original audit
and the accepted corrections. The kitchen and market now sit beside the road,
the holding fence has continuous runs and one guarded entrance, the prospectors
use a level pull-off, and the command desk and personal belongings have shelter.
The sand blockage remains as requested.

The road is now a 3.8-metre wagon track with a low crown and a narrower fort
approach. Hitching rails, water and feed occupy the western frontage; cart
repairs and timber occupy the eastern side. A bench and notice board serve
people waiting at the gate. Small worn paths and irregular dry scrub connect
these spaces while leaving the wagon route and court entrances clear.
The fort floor ends inside the walls, with a narrow graded bank joining the
canyon. The footpaths follow that ground continuously, rather than cutting
through the former raised apron.
Their dirt palette matches the main road, with muted tonal variation and faint
worn tracks instead of a single flat color.
At the gate junction, unequal sweeping wagon turns form a broad Y-shaped worn
area. Soft margins blend into the main road and sand, with several curved wheel
ruts converging toward the fort.
The same feathered soil, varied wear and rounded bends now extend along the
main road, through the fort and into the hitching and repair paths. These roads
follow the ground; the raised rectangular road pieces are retained only as
editor catalog assets for older saved layouts. Solid sand ground bridges the
gap beside the Badlands sign and joins the barricade's bank to the wagon road.

## Current story

The protagonist travels west to meet a wealthy family known mostly through letters,
photographs and stories from the East. Fort Mercy was supposed to be a brief water
and coal stop. A wall of sand cuts visibility, stops western telegraph reports and
fills railway cuttings. A maintenance crew confirms the danger; the engineer
refuses to continue. Nobody knows whether the delay will last one night or four.

The old military fort has outlived much of its original purpose. Railroad work has
brought a temporary settlement of tents, shacks and wagons: soldiers, settlers,
prospectors, merchants, workers and drifters. The camp must remain a functioning
place whose ordinary pressures continue around the investigation.

Three days earlier, surveyor **Silas Bell**, his daughter **Eleanor Bell**, guide
and outlaw **Caleb Rourke**, and **Lieutenant Nathaniel Mercer** entered the badlands.
Bell died in a dry creek. Rourke returned first and was arrested; Mercer returned
hours later; Eleanor was found the following morning walking toward the railroad.
**Elias Cole**, a local scout, claims to have discovered Bell's body.

The tutorial recovers records and Eleanor's letter. It precedes the four accounts;
it is not a fifth reconstruction or a murder-solving mission.

| Account | Claimed events and presentation | Evidence and unresolved questions |
| --- | --- | --- |
| Caleb Rourke | Bell's survey conceals a search for a lost army payroll cache. Rourke demands a share, but Bell draws first. They fight a magnificent duel; Mercer flees and Eleanor vanishes. The creek is a broad arena. | Firing positions are omitted. Bell's recovered revolver has only one discharged chamber despite Rourke describing repeated fire. Reloading or later handling must remain possible explanations; this discrepancy challenges his account without proving the killer. |
| Eleanor Bell | Bell discovers Rourke's work guiding prospectors and claim jumpers through railroad land. Rourke attacks; Mercer intervenes. Eleanor runs, returns to her wounded father, and faces his contempt. She raises his revolver and remembers nothing more. The route emphasizes flight and a cramped creek behind a homestead. | A bullet from Bell's revolver struck rock high above the body site. Tracks suggest somebody returned. These observations cannot by themselves establish who fired the fatal shot or exactly when the tracks were made. |
| Nathaniel Mercer | He fights an unstable Rourke, orders Eleanor back, pursues the outlaw and searches until dark. The landscape is orderly and his decisions initially seem reasonable. | Earlier evidence places him near the creek later than claimed. At the railway cutting, evidence reveals Bell buying route-adjacent land through intermediaries and offering Mercer money. Mercer says he refused. Their omitted argument does not settle the murder. |
| Elias Cole | He followed the party and watched fragments from a distance. The conflict was frightened, clumsy and intermittent: missed shots, falls, hesitation, departures and returns. He eventually found Bell dead and says he never saw the killing. Familiar places lose their heroic scale. | Bell's silver compass and its cut strap expose Cole's theft and false arrival time. His admission compromises this account too; it does not authenticate everything else he says. |

## Contract for testimony expeditions

- Every reconstruction names its source on entry and in the HUD, including
  **Elias Cole's account**. Evidence and journals keep source and revision attached.
- Cole's smaller, unheroic landscape is his presentation. No camera, final label,
  achievement, narrator or hidden truth meter identifies it as the correct version.
- The split rock, abandoned homestead, old railway cutting and dry creek remain
  recognizable anchors. Seeds vary the playable routes between them; each account
  changes scale, emphasis, encounters and approaches under authored constraints.
- An expedition is a playable interpretation, not literal proof that terrain has
  changed. The presentation must not silently introduce an objective flashback.
- Clues are placed on reachable routes. Each important clue supports or questions
  specific claims. Separate an observation, its provenance and its interpretation.
- Save the seed, account, revision and evidence history needed to reproduce a trip.
  Avoid one interchangeable encounter set with different dialogue pasted over it.
- Combat and the current creature roster need deliberate art/story treatment before
  the testimony journeys are authored. Existing gameplay alone does not decide it.

Some facts become defensible: Bell's corruption, the confrontation, Mercer's
knowledge, Eleanor's fear and anger, multiple shots, departures and returns, and
Bell's death. They never combine into a certified complete sequence or a compulsory
culprit selection. Cole's account receives the same scrutiny as the others.

## Compass continuity — still to author

The supplied outline has the player discover the compass, later shows it on
Cole's belt, and finally leaves its disappearance unexplained. Preserve that
intent, but make custody explicit when implementing the scenes. Options are to
find the cut strap and confront Cole while he still has the compass, or to author
an explicit transfer after recovery. Neither option is implemented or treated as
an accepted story revision yet.

## Ending

The wind weakens. Crews report the drifts manageable and expect morning departure.
Rourke maintains his duel story; Eleanor cannot resolve her memory gap; Mercer
insists he fulfilled his duty; Cole admits theft but stands by the rest. The murder
remains unresolved.

A settler family has lost possessions, a horse and its overturned wagon. Army,
railroad and neighbors find reasons somebody else should help. Cole brings his own
worn but usable wagon and begins moving the family's belongings despite a taunt
about his conscience. The compass is no longer on his belt. The game never explains
whether he sold it for supplies, returned it, discarded it or hid it.

Morning: the line clears and the train leaves. From the carriage the protagonist
sees Rourke under guard, Mercer outside the command building, Eleanor waiting for
transport east and Cole helping the family harness his horse. None resembles the
person presented in their own account. The fort returns to ordinary concerns;
Bell's death will remain an argument after the passenger is gone. The protagonist
leaves with many facts that no longer form a single story.

## Next implementation slices

1. Playtest Rourke's 4–8-floor run for combat pacing and reward balance; refine
   site dressing and add authored reconstruction scenes within its story rooms.
2. Eleanor and Mercer: authored variations around shared anchors, evidence
   provenance, revised conversations and save migration.
3. Cole: his explicitly attributed reconstruction, theft confrontation and the
   unresolved compass custody detail.
4. Ending: camp assistance, weakening storm, track clearance, train departure and
   final views of the four witnesses. Test multiple evidence histories.
