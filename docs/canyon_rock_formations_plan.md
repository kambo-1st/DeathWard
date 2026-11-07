# Canyon rock formations: implementation plan

**Archived and paused (2026-11-07):** the authored-wall demo, frozen source/assets and historical reports are preserved in the [prototype archive](canyon_prototype_archive.md). Read the [postmortem](canyon_prototype_postmortem.md) for the failed delivery and remaining work. The generalized join and production New mode remain unfinished. The implementation record below includes historical and superseded findings.


## Action plan for the remaining work

**Current gate (2026-11-06):** the [active full goal](reports/cliff-formations/goal-status.json) remains unfinished. The [optimization checkpoint](reports/cliff-formations/optimization/index.html) verifies unchanged output on twelve selected sections and a measured construction reduction; rollout acceptance still fails. The [whole-wall structural review](reports/cliff-formations/wall-review/index.html) and its corrections pass geometry/floor/replay checks. The first [12-case seeded matrix](reports/cliff-formations/phase4/index.html) is captured: **12 technically generated cases, 0 unchanged A fallbacks in this matrix, 0 cases accepted for visual rollout**. Phase 4 remains incomplete. Phase 5 acceptance remains incomplete: the first controlled case fails both frame-time and construction targets. Phase 6 production integration has not been reached. The [latest remaining-work checkpoint](reports/cliff-formations/local-finish/index.html) records rear-plane extensions in four cases, checked previous roofs in eight, the expanded boundary inventory and failed controlled performance gates. Localized cap lips/pointed facets, full reference acceptance, boundary-shape coverage and neighbouring-section coordination remain open.

Interactive inspection: `DW_CLIFF_OPTION=formations DW_CLIFF_DETAIL=1 DW_CLIFF_FREEZE_SURROUNDINGS=1 DW_CLIFF_INTERACTIVE=1 ./build/deathward_cliff_alternatives --mute --smoke --theme canyon --style original --scene profile-works`. In this isolated executable, the interactive flag retains deterministic scene setup, then disables scripted input and frame-limit exit before the gameplay loop. Ordinary movement, aiming, combat and pause controls are active. The temporary preview save and inspection god mode come from the scene setup. Production gameplay is unchanged.

**Visual acceptance reopened (2026-11-03):** the user identified a visible notch at the dominant formation/shoulder junction in the orthographic top view. Closed-manifold and sampled top checks did not establish seamless footprint coverage there. The [reported notch was corrected](reports/cliff-formations/join-correction/index.html), and the later [whole-wall review](reports/cliff-formations/wall-review/index.html) corrected further structural issues. Visible cap-height breaks remain; overall visual acceptance is still open. Phase 4 work is an experimental prototype, not an accepted rollout. Earlier connection-assurance claims below are scoped to their measured topology checks, not visual acceptance of every join.

Phases 1–3 are delivered for the selected authored wall: [accepted shapes](reports/cliff-formations/phase1/index.html), [connected plateau with validated joins](reports/cliff-formations/phase2/index.html), and [restrained detail with supported vegetation](reports/cliff-formations/phase3/index.html). Next is Phase 4: seeded composition and plateau continuity across room layouts. General procedural composition, visual acceptance across rooms and production integration remain unfinished. Complete each phase's checks before advancing. A failed visual comparison returns to the relevant geometry task even when automated checks pass.

The subsequent [strict connection audit and closeups](reports/cliff-formations/phase2/connection-audit/index.html) also pass for this wall. Exact emitted coordinates, whole-face solid coverage and triangle intersections are now checked during generation; see the latest assurance entry below for scope and numerical limits.

The user accepted the Phase 1 rock shapes on 2026-11-02 and clarified that they must form the edge of a continuous elevated plateau, as in the supplied reference. This accepts the primary shape direction for the selected wall; it does not accept the current disconnected caps, lowered backing or complete canyon integration. Plateau construction belongs in Phase 2, before detail or seeded rollout.

All phases preserve the playable footprint, authoritative collision, roads, exits, room graph, camera, lighting and material palette. Keep experiments in `deathward_cliff_alternatives` until Phase 6. The diagnosis and historical evidence below remain part of this plan.

### Phase 1 — Refine the primary formations on the existing wall

**Work:** `tools/cliff_experiments/RockFormations.cpp` and its formation descriptors.

- [x] Preserve the current cleaned wall as the next before-image and record its descriptor values.
- [x] Mark remaining problems on a native crop: oversized/uniform caps, repeated shoulder shapes, abrupt ends and any remaining ground-contact seams. Tie each observation to a particular formation or terrain join.
- [x] Vary the primary formations' width, recession, lean, roof slope and upper outline independently. Keep one dominant mass, several supporting masses and smaller connectors; do not make every mass equally prominent.
- [x] Give shoulders different lengths and elevations, with some uninterrupted tall faces. Keep shelves local to their parent formations.
- [x] Adjust end formations to meet the untouched canyon without a sudden height jump or a visible rectangular cut.
- [x] Capture shaded, plain massing and wireframe views using seed 1866, Works room 2, 60 frames and the existing 160% camera. Compare them with the saved references and the cleaned baseline.

**Deliverable:** revised descriptors, a matched before/after sheet, and a short list of remaining visual differences in the report.

**Done when:** the large shapes read as unequal rock masses; caps and shoulders do not repeat the same profile; terraces end locally; end transitions are continuous. The result must work without chips, debris or vegetation concealing its shape. The solid, ray, replay, floor and collision checks must still pass.

### Phase 2 — Finish the rock/body and ground joins

**Depends on:** Phase 1's primary shapes.

- [x] Inventory exposed seams, buried interfaces, coplanar overlaps and disconnected pieces in the selected wall, including both ends and its ground contact.
- [x] Build an elevated rear rock body connecting the accepted front formations into a plateau. Extend solid terrain behind the visible rim instead of leaving separate capped pillars against ground-level backing.
- [x] Connect neighbouring top surfaces into broad, coherent plateau areas. Retain uneven rims and local elevation changes/shoulders; do not recreate continuous terrace rings or a uniform band around the room.
- [x] Make the backing and formations share an exposed boundary at their joins. Remove buried interfaces and weld matching boundary vertices; preserve legitimate recesses and holes.
- [x] Keep the existing protected-floor clipping and buried bases. Correct any remaining floating plates or cracks without moving floor triangles.
- [x] Add focused fixtures for confirmed defects and verify the assembled join, including rays aimed at seams. Closed input rocks alone do not prove the assembled surface is sound.
- [x] Validate plateau-top coverage as well as cliff faces: no unintended gaps between caps, exposed internal walls or thin connecting skins. Capture a matched shaded view showing usable visual depth behind the rim; plateau scenery support is addressed in Phase 3 without expanding the playable floor.
- [x] Check for zero-area faces, duplicate exposed faces and unexpected open edges. Distinguish intentional outer boundaries of the selected patch from cracks inside it.
- [x] Keep the selected rock union below its existing 2,400-triangle prototype limit; record the complete adapted-wall triangle count separately.

**Deliverable:** a connected plateau with the accepted cliff shapes on its exposed edge, a cleaned assembled mesh, top/seam coverage checks and close-up shaded/wireframe captures.

**Done when:** the selected cliff visibly bounds a continuous elevated plateau with connected top surfaces and solid depth behind its rim; no unintended holes, doubled surfaces, floating base plates or abrupt backing cuts remain; protected floor and collision data remain identical. Individual cap validation alone does not satisfy this phase.

### Phase 3 — Add restrained edge and ground detail

**Depends on:** Phases 1–2 passing without added decoration.

- [x] Add a small number of chips or short bevels at selected rims and junctions, leaving the main planes broad and quiet.
- [x] Compose a few partly buried base rocks and buttresses where they support the primary masses. Avoid uniform scatter and repeated base strips.
- [x] Ground existing terrace/base vegetation on the final visible surface; omit unsupported placements. Keep roads, exits and combat space clear, and preserve placement outside the affected wall.
- [x] Capture detail-off and detail-on comparisons so the contribution of detail is visible.
- [x] Recheck support, floor clearance, union coverage and deterministic placement.

**Deliverable:** detailed wall with a comparison showing that detail supports the primary forms.

**Done when:** detail concentrates at edges, joins and the base; vegetation has visible support; broad faces remain readable; no playable clearance is reduced.

### Phase 4 — Turn the authored wall into seeded composition

**Depends on:** a convincing, validated wall from Phases 1–3.

- [x] Extract explicit formation parameters from the authored descriptors: role, width, depth, height, lean, recession and roof profile. Optional shoulder/base counts now vary; the five-primary-role template and neighbouring-section coordination remain limitations.
- [ ] Replace the fixed table with bounded seeded composition. Use wall length, curvature and protected clearances to place dominant masses, supporting masses and connectors.
- [ ] Generate the plateau body and its connected top together with the exposed rim. Coordinate neighbouring sections so separate wall compositions do not leave seams or disconnected plateau islands.
- [x] Separate composition randomness from fine-detail randomness so tuning chips does not rearrange the main masses.
- [ ] Handle straight walls, concave recesses, convex corners, short sections and exit-adjacent sections. Leave unsuitable sections on the existing A path with an explicit fallback reason.
- [x] Remove the hardcoded Works-room selection from the generalized preview path. Keep the original fixed wall available as a regression scene.
- [ ] Record at least 12 exact seed/profile/floor/room cases, covering those boundary shapes across seeds 0, 42, 404 and 1866. Include early and late expedition floors; do not assume all profiles exist on every floor.
- [ ] Check repeatable descriptors, vertices and detail placement; protected floor, collision, roads, exits and room connectivity; bounded mesh counts; and the fallback cases.

**Deliverable:** seeded composition in the debug executable, a reproducible case manifest and a per-case gallery/status table.

**Done when:** all selected cases validate and look coherent, varied and free of repeated terrace rings or identical rock modules. Report synthetic geometry coverage separately from rendered room coverage. Registry availability or successful generation alone is not visual acceptance.

### Phase 5 — Validate visual consistency and performance

**Depends on:** Phase 4's fixed case manifest.

- [x] Capture A and formations for the current twelve-case manifest at matching camera, resolution, simulation frame, lighting and material settings, including shaded and geometry diagnostics. Captures for expanded boundary-shape coverage remain pending.
- [ ] Review silhouettes, primary proportions, local shelves, quiet planes, backing joins and ground contact against the references. Record failures per case and correct them before rollout.
- [ ] Run the relevant geometry, road, floor-progression, rendered-ray and occlusion checks. Preserve explicit failures and fallback coverage in the report.
- [x] Measure the first controlled native case with three alternating trials per mode and 120 warm-up frames excluded; publish raw frame samples, hardware and scoped construction timings. Both provisional targets fail; this does not accept performance across the matrix.
- [ ] Measure repeated construction timings with validation/replay work excluded, and native frame-time distributions after warm-up. Record triangle counts, memory, hardware and settings; do not use the FPS label in one screenshot as performance evidence.
- [ ] Use provisional rollout limits of at most 10% higher native p95 frame time and 25% higher construction time than A on matched cases. Record these as plan targets, not established measurements; optimize or document a revised target before calling a failing comparison accepted.

**Deliverable:** comparison gallery, regression results and measured performance table with remaining defects listed explicitly.

**Done when:** every rollout case meets the visual criteria, preservation checks and recorded performance limits. Any unsupported cases retain a documented A fallback.

### Phase 6 — Integrate and verify the regular game

**Depends on:** Phase 5's validated case set.

- [ ] Move the accepted composition/mesh path into the production terrain implementation while retaining an explicit A rollback option.
- [ ] Enable the new path only for supported sections; preserve the tested fallback behavior elsewhere.
- [ ] Repeat the case manifest and relevant regressions against the regular executable. Confirm that the integration reproduces the accepted debug-preview geometry.
- [ ] Play through representative connected rooms and floor transitions, including returns to Fort Mercy, checking exits, navigation, visibility and scenery support.
- [ ] Update configuration documentation, rollback instructions, the report and this progress record. Remove temporary diagnostic hooks that are no longer needed; preserve reference captures and reproducible validation tools.

**Deliverable:** production integration, rollback instructions and final acceptance report.

**Done when:** the regular game reproduces the accepted appearance and behavior, fallback/rollback works, and all remaining limitations are explicitly documented. Until then, describe the work as a prototype or partial integration.

### Immediate next work package

The original twelve cases now pass technical generation. Continue from the latest dated checkpoint below: finish residual visual defects, correct the rejected straight/targeted boundary cases, coordinate neighbouring plateau interfaces and optimize measured construction cost. Use the persisted inventory and targeted failures to choose the next sections. Broader interactive/occlusion acceptance and Phase 5 performance limits remain prerequisites for Phase 6 production integration.

## Decision and diagnosis

The shaded reference and its wireframe show long triangles as well as broad rock planes. Triangle aspect ratio and literal quads are not the primary explanation for the reference's appearance. Broad planar faces can be triangulated internally without showing diagonal shading.

The current A-derived pass improves surface detail but still starts with a continuous extruded wall. It does not establish convincing primary rock formations. The earlier B/C experiments raised patches from that same wall, so their forms looked like plates rather than substantial three-dimensional rocks.

The next implementation must build complete rock formations first. Surface triangulation is a final representation step, not the art-direction generator.

## Baseline comparison and references

| Feature | Desired reference | Existing wall-based baseline |
|---|---|---|
| Primary rock shapes | Large, uneven sandstone masses with convincing depth | A continuous wall with surface facets added to it |
| Main faces | Broad, relatively quiet planes | Too many visible diagonals, dents and angular patches |
| Terraces | Shelves start, stop and change width locally | Long, continuous horizontal bands |
| Transitions | Small bevels, broken corners and occasional ledges | Sharp joins with similar treatment repeated along the wall |
| Ground contact | Buttresses, partly buried rocks and debris connect the cliff to the floor | More abrupt, consistently defined wall bases |
| Detail placement | Detail concentrates around edges, junctions and the base | Detail spreads across the main faces |

- [Shaded reference](reports/cliff-formations/shaded-reference.png)
- [Supplied wireframe](reports/cliff-formations/wireframe-reference.png)

Tall faces are not inherently wrong. Their width, lean, recession and relation to adjacent masses must vary. The wireframe contains long triangles; replacing them all with small triangles or literal quads is not the goal. Real primary shapes and locally interrupted shelves are the largest remaining differences.

## Visual hierarchy

1. Large, uneven sandstone masses with real depth.
2. Broad, relatively quiet side planes and top surfaces.
3. A few localized chips, fractures, ledges and base rocks.

Do not distribute fine displacement uniformly over the wall. Tall faces are allowed; vary their widths, lean, depth and surrounding formations.

## Required construction

### Complete primary volumes

Compose the selected wall with one dominant formation, several medium formations and smaller connecting outcrops. Every formation must be a thick, closed rock volume with a top, sides and base. Use broad planar faces and irregular convex footprints. Avoid rows of identical modules and displaced front skins.

### Independent formation profiles

Give each formation independent width, height, lean, recession and top shape. Some formations have one uninterrupted face. Others have a secondary shoulder or a short shelf. Establish these profiles explicitly for the first fixed-seed experiment before introducing bounded seeded variation.

### Local terraces

Shelves belong to individual formations and stop at their edges. Do not generate continuous terrace rings around a room. Smaller, offset volumes can establish local shoulders and intermediate levels.

### Continuous body and clean intersections

Interlock volumes with a backing rock body outside the playable space. Remove buried faces and avoid coplanar surface overlaps. Prefer a small exposed union mesh over rendering complete overlapping solids indefinitely. Validate the real volumes and exposed boundary; do not merely change a two-dimensional triangulation.

### Quiet planes and localized transitions

Preserve broad side planes. Small geometric changes belong primarily at rims, adjoining formations, fractures and the base. Use short, varied bevels where useful. Do not displace every interior vertex or add random triangle colors to imitate depth.

### Ground contact

Use a few substantial buttresses and partly buried rocks, followed by smaller debris. Place them to support the larger formations, not as uniform scatter. They must not obstruct the existing playable floor, exits or roads.

## Authorized scope and preserved systems

The user accepted the architectural proposal on 2026-11-02 and requested this plan plus implementation.

The visible upper cliff contours, local visual heights and terrace arrangement may change for the isolated experiment. Freezing those would retain much of the artificial structure.

Preserve the playable footprint, authoritative terrain collision, roads, exit sockets, room graph, camera position/projection/160% zoom, lighting and material palette. Do not change combat, controls, enemy behavior, UI, navigation or room state transitions.

Use the current upper wall above the player, between the two trail posts, as the first test: seed 1866, Works profile, room 2, fixed 60-frame native capture. No full procedural-world replacement until the primary-form experiment is visually convincing.

## Implementation and validation sequence

1. Persist this plan and preserve the current A comparison as the baseline.
2. Build an isolated debug option with explicit, genuine convex rock volumes. Start with primary masses and local shoulders; no surface-noise pass.
3. Extract the exposed union boundary and adapt only the selected visual cliff region/backing. Prevent new geometry from overlapping the original playable floor.
4. Render the same native scene/camera, plus wireframes and a plain massing view where useful. Compare with both supplied references.
5. Check closed convex solids, outward planes, union clipping, deterministic construction, protected-floor clearance, unchanged collision/room data and bounded polygon counts. Compare union mesh rays against independent convex-volume rays.
6. Report actual strengths and shortcomings. A topology change is not visual acceptance.
7. Only after the primary shapes work: add restrained edge/base detail, then derive bounded seeded formation descriptions suitable for additional rooms.

## Acceptance criteria

- Substantial three-dimensional rock masses, not thin plates or raised wall patches.
- Varied primary widths, heights and recessions.
- Broad quiet planes, including legitimate tall faces.
- Local shelves and shoulders instead of continuous horizontal bands.
- Convincing cliff bases and continuous backing without visible holes.
- Unchanged playable space, connectivity, collisions, camera, lighting and materials.
- Comparable native screenshots showing a meaningful improvement toward the supplied target.
- No automatic adoption merely because the meshes validate or are more complicated.

## Reversibility

Keep the first volume experiment in `deathward_cliff_alternatives`, behind a temporary mode. Do not change the regular executable's generator during this isolated stage. The current A pass remains available, including its `polygon_facets 0` rollback setting.

## Progress and unfinished work

Implemented the first isolated, complete-volume wall in the debug executable:

- Five primary masses (one dominant), three local shoulders and four base rocks.
- Closed convex solids with broad planes; exposed union boundary extraction.
- Explicit protection of the old floor triangles, roads and exits against projected rock overlap.
- Independent union-ray checks, closed-solid checks and identical seeded replay.
- Exact preservation checks for floor vertices and authoritative collision heights.
- Native shaded, polygon-wire and triangle-wire captures at the existing 160% camera.
- The old high terrace band is lowered only in the selected visual test region. Unsupported old plateau plants are suppressed in that diagnostic view.

See the [prototype comparison and current validation](reports/cliff-formations/index.html) and [status data](reports/cliff-formations/status.json).

Still unfinished:

- Phases 1–2 shape, plateau and join work is delivered for the authored wall. Broader visual acceptance remains unfinished; no exact reference match is claimed.
- Phase 3 edge/base detail and scenery support are next. The selected plateau/body join is verified; full-world integration remains Phase 6.
- Fine edge chips, ground-contact debris and grounded terrace vegetation.
- Rendered multi-room/seed validation and a seed-driven formation composition system across rooms/floors. Three synthetic-wall seeds now have geometry coverage only.
- Production rollout: the regular game remains on the current A pass. The new volumes are available only through `DW_CLIFF_OPTION=formations` in `deathward_cliff_alternatives`.

This is a validated blockout and architectural prototype, not a declaration that all procedural canyon cliffs are finished.

## Session recovery — 2026-11-02

Recovered session: `01a0e292-f5a2-7813-9630-d57304e749d3`.

The session reader reports `systemError`; its final attempts failed with `Bad Request`, including an explicit remote-compaction failure. The conversation and local rollout remain readable. This recovery reconstructs the working context here; it does not repair the original thread's compaction state.

### Last request and interruption point

After the first volume prototype was delivered, the user asked: “Hmmmm... Ltes go and BTW there are still some strange small iregulatirs...” and subsequently asked to continue. The assistant committed to inspecting volume joins, backing terrain and cliff bases before extending the formation system.

The last recorded tools read the implementation and viewed `comparison.png`. No geometry cleanup was delivered after that request. Treat the small irregularities as unresolved, with their cause still to be established.

### Recovered workspace and evidence

- Latest commit at recovery: `6d13c1a` (`Restore committed canyon and isolate reversible cliff face detail`). Existing implementation changes and report artifacts remain uncommitted; preserve them.
- The regular executable uses the A-derived facet pass. The complete-volume experiment remains isolated in `deathward_cliff_alternatives` with `DW_CLIFF_OPTION=formations`.
- Main prototype implementation: `tools/cliff_experiments/RockFormations.cpp`, `RockFormations.hpp`, and the formations branch in `CliffExperiments.cpp`.
- Existing visual evidence: `docs/reports/cliff-formations/index.html`, `comparison.png`, `volumes.png`, `wireframe.png`, `triangles.png`, plus the two saved reference images in that directory.
- Recorded prototype validation: 12 closed solids, 1,159 exposed union triangles, 160 independent union rays, 704 protected-floor overlap tests per build, identical deterministic replay, unchanged floor triangles and collision heights. These are prior validation results, not newly executed tests during recovery.
- Recovery checked all six runtime-file SHA-256 values in `docs/reports/cliff-formations/status.json`; all match. This confirms those files still match the recorded checkpoint, not that the prototype is visually accepted.

### Next implementation step and remaining work

1. Inspect the native shaded and wireframe images for the reported small irregularities. Trace visible defects to volume intersections, coplanar fragments, backing transitions or base contact; do not assume a cause from the screenshot alone.
2. Fix the confirmed geometry defects within the isolated wall experiment. Preserve the playable footprint, collision, roads, exits, room graph, camera, lighting and material palette.
3. Rebuild the debug executable and repeat the existing volume, union-ray, floor-clearance, collision and replay checks. Capture the same seed 1866 Works scene, room 2, at 60 frames and 160% zoom; update the comparison and status report with actual results.
4. Refine primary outlines and local shoulders before introducing a broader seeded composition system. Fine detail, grounded vegetation, multiple-seed validation and production rollout remain unfinished.

At recovery, the geometry cleanup requested immediately before the session failure had not yet been implemented or verified. The following entry records the subsequent implementation.

## Geometry cleanup — 2026-11-02

Implemented in the isolated `formations` preview, preserving the previous blockout as `pre-cleanup-*` captures and status data.

### Confirmed causes and corrections

- The retained old wall was lowered to a constant 0.6 m, leaving a raised strip across the bases. It now meets the original 0.12 m floor contour and tapers to sand behind it.
- Old facet vertices protruded beyond the source contour and escaped the original lowering region, leaving spikes. The adapter includes that skin and trims inherited overlap against protected floor triangles instead of moving the floor.
- Beveling every forward-facing rock base produced repeated zigzag joins. Side planes now continue into the ground, with closed bases buried below it.
- Union subtraction partitioned broad exposed faces into unnecessary pieces. Adjacent coplanar pieces now merge only if the resulting boundary is convex and preserves area; real holes, recesses and disconnected regions remain.
- A synthetic seed exposed an open-solid failure: float tolerances classified near-corner intersections as belonging to unrelated bevel planes. Plane intersections and their face membership now use double precision before conversion to render vertices.

### Current verification and visual result

The final native Works capture retains 12 closed convex solids and has 756 union triangles (previously 1,159). Each construction passes 640 independent union rays, 708 floor-overlap checks, and identical replay. Both visual floor triangles and authoritative collision heights remain unchanged. All six recorded production runtime/configuration hashes match the pre-cleanup checkpoint.

Focused regression fixtures pass for interior holes, concave recesses, separated regions, coplanar ownership, repeatability, backing taper, removal of protruding backing over protected floor, and floor/collision preservation. Synthetic walls with seeds 0, 42 and 1866 pass closed-solid construction and 640 rays each. These synthetic checks do not establish visual acceptance across rooms or floors.

The four CTest suites `rock_formations`, `cliff_facet_refinement`, `canyon_visual_geometry` and `canyon_roads` pass. After the final backing changes, the focused `rock_formations` suite and all three native capture modes passed again. Capture settings remain seed 1866, Works room 2, 60 frames and 160% zoom.

The shaded comparison shows a quieter base without the previous raised strip and repeated lower bevel wedges. The broad primary masses remain intact. It is still an authored wall prototype: the large caps, shoulders and transitions into untouched terrain need art refinement, and small ground-contact seams are not claimed to be fully welded or visually accepted.

Updated evidence: [comparison and wireframes](reports/cliff-formations/index.html), [status](reports/cliff-formations/status.json), [focused fixtures](reports/cliff-formations/geometry-tests.log), [regression suites](reports/cliff-formations/regression-tests.log), and [final focused CTest](reports/cliff-formations/cleanup-tests.log).

Reproduce with:

```sh
cmake --build build --target deathward_cliff_alternatives deathward_rock_formations_tests -j4
ctest --test-dir build -R '^rock_formations$' --output-on-failure
python3 tools/cliff_experiments/formations-capture.py
python3 tools/cliff_experiments/formations-report.py
node tools/cliff_experiments/formations-export.cjs
```

The report generator now preserves this plan and its recovery history instead of replacing the progress section.

Remaining: refine top outlines, cap/shoulder shapes and end transitions; finalize backing/body welding; add restrained edge/base detail and grounded vegetation; implement seeded composition and rendered multi-room/seed validation. Production rollout remains pending; the regular game stays on A. Changes are uncommitted.

## Phase 1 shape refinement — 2026-11-02

Delivered the first work package from the action plan. Baseline images, source and dimensions are preserved under `docs/reports/cliff-formations/phase1/before-*`; the current descriptor values are in [descriptors.json](reports/cliff-formations/phase1/descriptors.json).

### Changes and visual assessment

- Six numbered annotations identify the dominant cap, left supporting mass, repeated right shoulders, both end joins and small ground seams on the native before-image. See the [annotated report](reports/cliff-formations/phase1/index.html) and [defect map](reports/cliff-formations/phase1/defects.json).
- Every formation now has independently authored yaw, lean, roof slope, secondary crown slope/position, recession, footprint corner count, side taper and selected rim bevels. The shared random roof/lean rules and near-continuous rim bevel treatment were replaced.
- The dominant formation retains a broad, quiet face with a restrained roof slope. The left supporting mass is narrower and taller, with a different crown cut. Shoulder widths/elevations differ; the left shoulder is broader and lower rather than another tall post.
- Existing base masses are lower and broader so more of the main faces remain uninterrupted. No new chips, debris or vegetation were introduced to conceal the primary forms.
- Wider end formations and reduced setbacks improve the visible transition into the untouched canyon. Final exposed-boundary continuity and body/backing welding are still Phase 2 work; these visual adjustments do not prove those interfaces are welded.
- Matched shaded, polygon-wire, triangle-wire and plain-massing captures use seed 1866, Works room 2, 60 frames, 1440 × 900 and the existing 160% camera. The plain-massing view uses the actual mesh with neutral directional diagnostic shading; normal shaded captures retain the game's lighting/materials. It is not a proposed material change.

The comparison shows a clearer hierarchy and more varied cap/shoulder profiles. The sandstone reference remains the visual specification. This is one composed wall, not full procedural-canyon acceptance or an exact reference-match claim.

### Verification

- Current native wall: 12 closed convex solids, 556 exposed union triangles (cleaned baseline: 756; prototype limit: 2,400), 640 independent union rays and 738 protected-floor overlap tests per construction.
- Vertex replay and authored-profile replay are deterministic. Original floor triangles, authoritative collision heights and all six recorded production runtime/configuration hashes remain unchanged.
- The new slopes exposed a float ray/triangle edge case in an intermediate synthetic wall: both adjacent triangles could miss a ray on their shared bevel edge. The triangle oracle now calculates intersections in double precision from actual render vertices, retaining the 4 mm convex/triangle agreement tolerance. A dedicated shared-bevel-edge fixture passes, as do the existing hole, recess, coplanar ownership, backing and preservation fixtures.
- Seeds 0, 42 and 1866 pass synthetic-wall solid/ray checks. This is geometry coverage only, not multi-room visual acceptance.
- The four regression suites `rock_formations`, `cliff_facet_refinement`, `canyon_visual_geometry` and `canyon_roads` passed during the shape pass. The final authored dimensions and bevel-edge fixture also pass the focused `rock_formations` suite. Native captures repeat solid, ray, replay and floor/collision checks.

Evidence and reproduction commands are in the [Phase 1 report](reports/cliff-formations/phase1/index.html). Its capture/report tools preserve the earlier cleanup report and baseline; the annotations are an overlay on native screenshots, not generated concept art.

Remaining: Phase 2 assembled-boundary validation and final joins; Phase 3 restrained detail/vegetation support; Phase 4 seeded room composition; Phase 5 visual/performance coverage; Phase 6 production integration. The regular game still uses A. Changes are uncommitted.

### User feedback after Phase 1

The user confirmed that the revised shapes resemble the target and reiterated that they must form a plateau, supplying the sandstone reference again. The shape direction is accepted for this wall. The prototype's isolated capped volumes and lowered backing are intermediate construction, not the finished terrain architecture.

Phase 2 now explicitly requires an elevated connected rear body, coherent plateau-top coverage and top/side interface checks. Phase 4 must carry that plateau continuity into seeded composition. Remaining work therefore includes actual plateau construction before production integration; it is not solely a final integration task. No new geometry or plateau validation is claimed by this planning update.

## Phase 2 connected plateau — 2026-11-02

Delivered the plateau/body and join work for the selected wall. The accepted Phase 1 images, descriptors and source are preserved as `phase2/before-*`. See the [matched comparison, body/top diagnostics and validation](reports/cliff-formations/phase2/index.html) and [machine-readable status](reports/cliff-formations/phase2/status.json).

### Implemented

- The 12 accepted front formations connect to 12 closed rear prisms across seven control stations. Shared top edges and restrained rear elevation changes create coherent elevated land behind the rim. All front descriptor records, including clearance shifts, match Phase 1.
- The new 24-solid union is welded into one closed, consistently oriented component. Shared boundary segments are split before triangulation to remove T-junctions; coincident exterior copies consolidate and opposite buried faces cancel.
- The selected old backing is reconstructed as solid terrain rather than folded lowered skins. Buried surfaces are removed in both directions. At the work boundary, positive and negative original surface crossings distinguish actual rock from air beneath old overhangs.
- Original triangles crossing the finite work rectangle are split, with deformation fading to zero at the boundary. A nearest-contour bug beyond segment corners was fixed: true nearest distance now bounds the edit instead of a potentially misleading normal projection. Original outside planes and all floor/collision data are preserved.
- The finite render patch intentionally ends at original terrain/floor interfaces and its buried foundation. Every open perimeter edge must match those actual surfaces or the buried boundary; an inherited hole is not accepted simply because it appeared in the old skin.
- One approximately 0.07935 mm-wide closed numerical slit is repaired with four triangles, only after 12 independent solid-boundary probes confirm the patch. True holes and unsupported repairs remain rejected.

### Verification and scope

- Native seed 1866, Works room 2: 24 closed input solids; **1,606 union triangles** under the 2,400 limit; one component; zero open/nonmanifold edges, duplicate/degenerate faces or winding errors in that union.
- The adapted render patch is counted separately: **9,967 triangles**, zero unexpected boundary edges and zero nonmanifold, duplicate, degenerate or winding errors. Its **261 intentional perimeter edges** are verified against original terrain/floor surfaces (193) or the buried finite-patch foundation (68). This is not a claim that the entire canyon world is a closed manifold.
- Per construction: 640 independent random union rays; 336 top-coverage probes including shared edges; 4,674 near-seam ray probes, with 144 recorded sub-weld/occluded exclusions covered by the complete edge audit; 847 protected-floor overlap tests. The ray-distance tolerance remains 4 mm and the weld tolerance is 80 μm. Native top probes required no neighbourhood guards in the final case.
- Split outside vertices remain within approximately 1.76 μm of their original source planes. Original floor triangles, authoritative collision heights and all six recorded production source/configuration hashes remain unchanged.
- Both new-union vertices and the complete assembled triangle list repeat identically from the same inputs. The native shaded, polygon-wire, triangle-wire, plain-body and orthographic top diagnostics repeat the checks. Normal game camera, lighting and materials are unchanged; neutral shading/top camera are diagnostic modes only.
- Focused fixtures cover T-junction welding, duplicate/internal-face cleanup, actual holes, concave recesses, shared bevel edges, buried/coplanar terrain interfaces, overhang air gaps, the corner-locality regression and floor/collision preservation. Synthetic seeds 0, 42 and 1866 pass solid/top/ray checks; these are not rendered multi-room acceptance.
- The four CTest suites `rock_formations`, `cliff_facet_refinement`, `canyon_visual_geometry` and `canyon_roads` pass. Capture FPS labels and debug construction timings are not controlled performance acceptance.

### Visual assessment and remaining work

The cliff now bounds a connected elevated plateau rather than separate capped masses. The user-accepted front character remains the baseline. Normal captures and diagnostics show the new top/body and its retained-terrain connection; the reference remains the visual target, without an exact-match claim.

Next: Phase 3 restrained edge/base detail and vegetation support on the actual visible surface. Phase 4 seeded composition, Phase 5 broader visual/gameplay/performance validation and Phase 6 regular-game integration remain unfinished. The regular game still uses A. Changes are uncommitted.

## Connection assurance audit — 2026-11-02

The user requires a flawless plateau-to-cliff connection. A stricter audit of the actual emitted mesh found no additional geometry defect in the selected wall. No shape change was needed. See the [audit and four matched shaded/wireframe closeups](reports/cliff-formations/phase2/connection-audit/index.html) and [machine-readable results](reports/cliff-formations/phase2/connection-audit/summary.json).

- Exact-coordinate checks now run during generation without tolerance-welding away small cracks. The closed plateau/cliff core has 803 vertices, 1,606 triangles and zero open/nonmanifold edges, pinched vertex links, duplicate/degenerate faces or winding errors.
- Triangle-pair checks examine 13,292 candidate pairs in the core and 113,384 in the adapted terrain patch: zero self-intersections or coplanar overlaps. Every core triangle also passes whole-face coverage against the source solid union, with zero buried or detached fragments at a 0.1 mm positional margin.
- The assembled patch's 261 exact open perimeter edges match its previously verified intentional boundaries: 193 original terrain/floor interfaces and 68 buried foundation edges. These are outside boundaries of the finite patch, not cracks in the cliff/plateau connection. An independent parse of the exported shared-index OBJ meshes confirms the edge counts.
- Deliberately defective fixtures prove detection of a 10 μm crack hidden by the older weld tolerance, crossing triangles, coplanar overlap, pinched vertices, internal faces and detached faces. Separated parallel surfaces remain accepted. All three synthetic seeds (0, 42, 1866), the native wall and the four regression suites pass.
- Matched left, middle, right and rear closeups were exported and inspected. The checks now reject these defect classes during debug generation. Intersection calculations use double precision with a 10 nm plane tolerance and a 1e-12 m² coplanar-overlap threshold; these numerical checks do not establish an absolute guarantee for untested rooms.

Scope remains the selected native wall (seed 1866, Works room 2), plus synthetic geometry coverage. Remaining: Phase 3 detail and vegetation support; Phase 4 seeded composition and rendered room coverage; Phase 5 broader visual/gameplay/performance validation; Phase 6 production integration. The regular game still uses A. Changes are uncommitted.

## Phase 3 detail and supported vegetation — 2026-11-03

Delivered the requested detail/vegetation pass on the verified wall. See the [matched detail-off/on report](reports/cliff-formations/phase3/index.html), [comparison image](reports/cliff-formations/phase3/comparison.png) and [verification data](reports/cliff-formations/phase3/status.json). Phase 2 source and status are preserved in `phase3/before-*`; fresh detail-off captures reproduce its geometry and temporary scenery suppression.

### Changes

- Two small roof-corner cuts affect the right mass and left shoulder. The accepted primary descriptor dimensions and placement shifts remain unchanged. Main faces stay broad; there is no continuous rim band.
- Two low, partly buried buttresses are unioned into the body. Both pass the protected-floor overlap test and contribute measurable exposed upper area (approximately 0.687 and 1.500 m²). An entirely buried trial placement was detected and repositioned rather than counted as detail.
- Local support is rebuilt from the final emitted upper shell and risers; downward foundation faces are excluded. Original support outside the finite work rectangle is retained. Two existing grass tufts and one small existing rock are reanchored; five unsupported local scenery placements are removed.
- Four fresh grass tufts occupy sparse plateau/shoulder pockets. Shrub/cactus candidates without adequate support remain omitted. All new conservative rotated footprints, including a margin, are checked against protected floor triangles. Existing floor/outside decoration records are preserved.
- Support combines clipped-triangle height ranges with independent visible-mesh rays at no more than 12 cm spacing. Missing mesh cannot fall back to old physical heights. Roots sit 2.5 cm below the sampled lowest surface; maximum accepted height variation is 16 cm (10 cm for cactus candidates), compatible with renderer support checks.
- Detail uses a separate deterministic stream. `DW_CLIFF_DETAIL=0` reproduces the plateau-only preview; the formations preview enables detail by default. The capture tool defaults to detail off to preserve earlier reproduction commands; pass `--detail on` for Phase 3.

### Verification and scope

- Final native wall: 26 closed source solids, **1,804 core triangles** (limit 2,400), one closed component. Zero exact open/nonmanifold edges, pinched vertices, self-intersections, coplanar overlaps, duplicate/degenerate faces or winding errors. Whole-face solid coverage reports no buried/detached fragments.
- The complete adapted patch has **10,565 triangles**, zero unexpected boundaries and zero strict intersection/overlap defects. Its 261 intentional perimeter edges retain the verified 193 terrain/floor and 68 buried-foundation classification.
- Top coverage, targeted seam rays, protected-floor overlap checks and collision preservation pass. Native shaded, polygon-wire, triangle-wire, massing and top views repeat the same mesh and scenery placements. All six recorded production runtime/configuration hashes match Phase 2.
- Detailed synthetic seeds 0, 42 and 1866 pass strict geometry checks. Added fixtures reject stale physical-height support, absent visible mesh and height discontinuities, and verify local reanchoring and outside-placement preservation. All four regression suites pass.
- The native comparison was inspected: the broad faces and plateau silhouette remain readable, with restrained additions at roof corners, the base and a few upper planting pockets. Normal camera, lighting and materials are unchanged. This is one authored wall; capture FPS and debug construction time are not controlled performance acceptance.

Remaining: Phase 4 seeded composition and plateau continuity across room layouts; Phase 5 broader visual/gameplay/performance validation; Phase 6 production integration and rollback verification. The regular game still uses A. Changes are uncommitted.

## User-reported plateau/shoulder notch — 2026-11-03

The user's top-view image rejects the earlier blanket claim of seamless connection. The old core was a closed manifold, but its exterior contour contained a V-shaped notch at the dominant formation/shoulder junction. Rear-body top probes and manifold checks did not cover this footprint defect. This is a correction to the earlier visual assessment, not a failure of the exact-edge audit's narrower measured result.

- Two closed triangular prisms now connect actual roof-edge vertices at their actual heights. Their top surfaces provide a continuous sloped transition across the notch, rather than a disconnected slot or a floating plate. The high formation and lower shoulder retain different elevations; steep faces remain visibly shaded.
- Both connector prisms pass protected-floor clearance. No floor triangle, collision height, accepted primary descriptor or production source/configuration hash changes. Existing detail and supported scenery remain enabled in the preview.
- This is a structural correction, enabled with both detail on and detail off. New detail-off captures therefore include the connector; the preserved pre-correction images remain the historical comparison baseline.
- Generation checks 306 connector-footprint samples, inset by 0.001 of the distance to each triangle centre to avoid exact-corner ray ambiguity. Exact emitted-edge, triangle-intersection and whole-face source-solid audits independently cover the constructed solid surface.
- An independent OBJ check samples 121 points over the reported region (world x 40.66–40.80 m, z −11.07–−10.96 m). The preserved old body has 70 missing hits, 23 hits only below ground, and 28 hits only on low base geometry. The corrected body has zero missing hits; all 121 hit the upper transition at heights 2.382–2.731 m.
- Final corrected native core: 28 source solids, 1,826 triangles, one closed component, zero exact open/nonmanifold edges, vertex pinches, intersections or coplanar overlaps. The adapted patch has 10,619 triangles and retains the verified 261 intentional outer edges. The connector remains below the core's 2,400-triangle limit.
- Native shaded/wire/triangle/massing/top captures and mesh/scenery replay pass. Detailed and plain synthetic seeds 0, 42 and 1866 pass. All four regression suites pass. Before-images and native comparison evidence are preserved in the [junction correction report](reports/cliff-formations/join-correction/index.html) and [status](reports/cliff-formations/join-correction/status.json).

Remaining: further visual review of all other plateau transitions before accepting the whole wall as seamless; Phase 4 seeded composition; Phase 5 broader visual/gameplay/performance validation; Phase 6 production integration. The regular game still uses A. Changes are uncommitted.

## Broader wall review and seeded preview matrix — 2026-11-03

Implemented the next review and prototype work. The [whole-wall report](reports/cliff-formations/wall-review/index.html) contains matched native images, top/wire diagnostics and four side/rear views. The [seeded preview report](reports/cliff-formations/phase4/index.html) records all 12 cases, individual candidate failures, preservation evidence and visual findings. This does not complete Phases 4–6.

### Structural corrections and verification

- Added a sloped roof transition between the left and dominant formations. The two intended transition patches now receive 612 targeted samples, supplementing the original circled-notch regression.
- Replaced the overlapping rear strip construction with one triangulated footprint. Actual rear roof corners join the common elevated body, and station heights sample all five primary caps instead of clamping the result to one nearby descriptor. This corrects artificial low valleys and the end-mass connection found during broader review.
- Protected floor is clipped from candidate body domains before closed solids are created. Sub-weld fragments below 40 μm of projected altitude are omitted; exact emitted topology and the 0.1 mm source-solid boundary audit remain required. Positive-volume construction accepts genuinely small clipped prisms instead of applying the old 0.001 m³ visual-size threshold.
- Added three sampled elevated lanes from each of the five main roofs to common land: 1,935 accepted samples total. Routes may bend through body-triangle centres so intended front recesses are not mistaken for disconnected terrain. These checks establish elevated connectivity; they do not prove every cap edge is smooth or visually accepted.
- Final authored native wall: **25 closed source solids, 1,690 core triangles, 7 rear-body triangles/prisms**, one closed component; zero exact open/nonmanifold edges, pinched vertices, intersections, coplanar overlaps or degenerate faces. Whole-face source coverage has zero buried/detached fragments.
- The adapted patch has **10,111 triangles** with zero unexpected boundaries. Its 261 intentional edges retain their 193 original terrain/floor and 68 buried-foundation classification. Both visible extra buttresses remain in the final wall; buried extras are now omitted rather than counted as detail. Scenery has three reanchored records, five unsupported removals and four new tufts.
- Native shaded, polygon-wire, triangle-wire, massing, top and four orbit diagnostics repeat the same mesh/scenery checks. All four regression suites pass. The six recorded production source/configuration hashes remain unchanged. Visible facet/cap-height changes remain in the diagnostics; no universal seamlessness or exact reference-match claim is made.

### Seeded preview implementation

- Extracted explicit role/profile descriptors and bounded seeded parameter composition into `FormationComposition.cpp`. The authored recipe remains available for regression. Composition randomness is separate from detail randomness. Variable role counts and fully optional shoulders are still unfinished.
- Added world-space contour selection in `FormationSections.cpp`, using bounded 14–30 m sections and at most six spatially distinct candidates. The generalized preview no longer depends on the Works seed or a screen rectangle. Ambiguous, short, folded, obstructed or invalid sections retain A with explicit reasons.
- Added local-coordinate construction for generalized rooms. Exact original faces/placements are restored when unchanged, original floor vertices are checked again in world space, and the translated emitted meshes/source boundary are audited before committing the candidate. Failed attempts operate on copies and leave A untouched.
- Added generated debug-main case setup through `DW_CLIFF_LAYOUT=seeded`, `DW_CLIFF_SEED`, `DW_CLIFF_FLOOR` and `DW_CLIFF_ROOM`. The ordinary executable and its production terrain path are unchanged. `DW_CLIFF_INTERACTIVE=1` continues to hand the prepared scene to ordinary gameplay controls.
- Added a native case-manifest utility and paired A/preview capture tool. The manifest covers seeds 0, 42, 404 and 1866 at early/middle/final expedition floors, recording actual profile bands and room counts. A baseline captures may be reused only when their geometry/scenery hash matches the current baseline; rejected final results must match that hash too. The capture ledger is tied to the binary SHA256.

### Results and the remaining gate

**2/12 cases pass technical generation checks:** seed 0 / floor 5 / room 13 and seed 42 / floor 0 / room 0. Both pass emitted geometry, floor preservation and deterministic geometry/scenery replay. Shaded, wire and top views were inspected. **Neither is accepted for visual rollout:** raised cap outlines/narrow transitions and repetitive role structure remain; the seed-42 selected section also lies mostly outside the normal gameplay camera, so paired inspection framing needs improvement.

**10/12 cases retain byte-identical A geometry/scenery records.** Rejections include protected-floor placement, invalid/steep connector roofs, core topology and assembled boundary failures. The report preserves every candidate rejection rather than treating a fallback as successful formation generation. The current rendered selection covers curved sections; the planned straight/concave/convex/short/exit-adjacent matrix and coordinated neighbouring sections remain incomplete.

Next work: correct the rejected placements and clipping/union joins, replace authored edge hints with geometry-driven transitions, vary role counts, refine cap/backing height breaks, and complete boundary-shape/camera coverage. Then repeat visual acceptance and the Phase 5 controlled construction/frame-time, occlusion and gameplay checks. Phase 6 production integration remains gated. The regular game still uses A. Changes are uncommitted.


## Seeded placement and terrain-join recovery — 2026-11-05

Continued Phase 4 against the same 12 native cases. The [refreshed case gallery](reports/cliff-formations/phase4/index.html) includes matched close-up inspection cameras, so successful sections can be reviewed even when outside the normal gameplay camera. The [prior 2/10 ledger](reports/cliff-formations/phase4/before-reliability/capture-results.json) is preserved.

### Implemented corrections

- Removed buried rock faces beneath the preserved original floor before assembling the terrain surface. These invisible internal faces had produced nonmanifold junctions at floor corners. Original floor faces and collision heights are still restored unchanged.
- Added whole-edge interval proofs for hidden floor/context cuts. The context proof uses actual upward/downward crossings and rejects air beneath overhangs; it does not classify every edge below the highest roof as buried. Fixtures cover fully buried edges, overhang air, projected gaps and missing context.
- Seeded construction tries weld distances of 80, 20, 8 and 2 micrometres, accepting only a mesh that passes the unchanged exact-coordinate topology/intersection checks. Assembled statistics now use that exact audit rather than merging nearby distinct coordinates in the tolerant reporting audit. Source-boundary coverage remains independently checked.
- Added bounded placement fitting: full width, 85% or 70%, with a limited retreat search. Five primary masses remain mandatory. Seeded optional shoulders (1–3) and base roles (1–4) use an independent role-selection stream; obstructed optional roles may be omitted with explicit logs. Primary-profile randomness and authored regression descriptors remain independent.
- Seeded compositions now use the common geometry-driven body without the authored wall's specific connector-edge hints. The authored wall retains its targeted connector regressions. The seeded finite edit margin is 1 metre, with every resulting boundary still requiring proof.
- Captures support bounded parallel jobs, verify the executable hash, and provide paired A/formations inspection views of each successful section. The inspection camera is an explicit diagnostic override; normal gameplay framing is unchanged.

### Results and next steps

The authored wall regression retains **25 solids and 1,690 core triangles**. Removing buried faces reduces its adapted patch from 10,111 to **9,849 triangles**. The 263 remaining intentional edges are proven against terrain/floor context (258) or preserved floor coverage (5); unexpected boundaries and strict mesh defects remain zero. Its 1,935 elevated-route and 612 targeted-join samples remain required.

**5/12 cases pass technical generation checks:** seed 0 / floor 0 / room 0; seed 0 / floor 5 / room 13; seed 42 / floor 0 / room 0; seed 404 / floor 3 / room 2; seed 1866 / floor 3 / room 2. The original two passing cases are retained and three rejected cases recover. Exact mesh, protected floor/collision and deterministic replay checks remain required. **Seven cases retain unchanged A.** Their per-candidate failures are preserved in the gallery and JSON ledger.

Verification: the focused geometry/support/composition fixtures and all four regression suites (`rock_formations`, `cliff_facet_refinement`, `canyon_visual_geometry`, `canyon_roads`) pass. The nine authored capture modes repeat the same exact audits. The six recorded production source/configuration hashes remain unchanged.

**Visual acceptance remains 0/12.** Reviewed close-ups show connected elevated land but raised cap outlines, sharp rear height ridges and, in some views, overly long flat rear edges. Technical closure is insufficient evidence of a natural continuous plateau. No claim of universal seamlessness is made.

Remaining work, in order:

1. Correct the seven rejected cases: five end at invalid assembled joins/roof construction and two at protected-floor placement. Preserve strict rejection and unchanged A fallback while fixing the underlying geometry.
2. Refine the cap/backing height transitions and rear silhouette on the five passing sections; repeat shaded/top/wire review against the reference.
3. Complete straight/concave/convex/short/exit-adjacent coverage and coordinate neighbouring sections through shared plateau interfaces. The current rendered selections are curved and still use five primary roles.
4. Complete Phase 5 controlled construction/frame-time measurements, occlusion and interactive gameplay acceptance.
5. Only after those gates pass, perform Phase 6 production integration and rollback verification.

The regular game still uses A. Phases 4–6 remain unfinished; changes are uncommitted.


## Seven-case recovery and verified matrix — 2026-11-05

**Technical checkpoint: 12/12 native rooms generate formations, recovering all seven previously rejected cases and retaining the original five passes.** The [headless audit ledger](reports/cliff-formations/phase4/geometry-audit/results.json), [refreshed gallery](reports/cliff-formations/phase4/index.html) and [prior five-pass baseline](reports/cliff-formations/phase4/before-seven-case-recovery/status.json) preserve the evidence. Visual acceptance remains **0/12** and the regular game still uses A.

### Implemented fixes

- Boundary classification now uses exact emitted float coordinates, matching the strict mesh audit. It no longer merges fine boundary vertices through the older approximate reporting weld. A regression fixture checks that a 10 micrometre emitted crack remains visible to boundary classification.
- Seeded placement follows the local contour segment's facing direction around bends. It no longer derives the whole section's outward direction from its first segment. Placement may retreat at most 4.8 m and uses four bounded width fits (100%, 85%, 70%, 55%); the two smaller fits also reduce depth. Every mandatory primary mass must still clear all protected floor polygons.
- Nearly vertical primary roof-fan triangles receive an upper height envelope with a 1:1 distance bound between backing controls. The existing upward-roof threshold stays required. The accepted authored wall's roof descriptors remain unchanged.
- The terrain-join retry retains very steep upward source caps and constructs the previously missing **old-terrain-minus-new-terrain** transition surfaces at the finite work boundary. Signed source crossings preserve overhang air. These complement the replacement-minus-old faces already supplied by the replacement solids.
- Finite edits try margins of 1, 1.5 and 2 m on independent copies. A difficult source corner can move outside the cut without moving original floor or collision data. Terrain weld distances up to 0.3 mm are construction alternatives; the exact emitted topology/intersection checks still decide acceptance. The core source-boundary audit remains separately checked at its existing 0.1 mm margin.
- Section fitting retains the six original 24 m candidates, then tries up to six each at 18 m and 14 m. Shorter fits recover two rooms whose larger sections remain unsuitable. The search is bounded at eighteen candidates. A section key identifies its contour origin; the successful length is recorded separately.
- Added `deathward_formation_audit` and `formations-audit.py` for headless execution of the same seeded preview, preservation and replay code. Rendered diagnostic views replay the successful candidate directly and must reproduce the normal-view geometry/scenery hash.

### Recovered cases

The numbers below describe the final selected section and finite edit margin. Earlier candidate failures remain recorded; this checkpoint accepts one verified selection per room.

| Previously rejected room | Selected length | Edit margin |
| --- | --- | --- |
| `seed0-floor3-room2` | 14.2609 m | 1 m |
| `seed42-floor3-room2` | 23.9002 m | 1.5 m |
| `seed42-floor6-room13` | 23.4274 m | 1 m |
| `seed404-floor0-room0` | 23.759 m | 1 m |
| `seed404-floor5-room13` | 17.4299 m | 1 m |
| `seed1866-floor0-room0` | 23.8283 m | 1 m |
| `seed1866-floor5-room13` | 23.4734 m | 1 m |

### Verification and remaining work

- The full twelve-case headless audit passes strict core/assembled mesh checks, elevated routes, exact original-floor restoration, unchanged collision heights and deterministic mesh/scenery replay. Native shaded, wire, top and paired inspection captures are tied to the final executable hash; the report verifies headless/rendered geometry/scenery hash agreement for every case.
- All four regression suites pass: `rock_formations`, `cliff_facet_refinement`, `canyon_visual_geometry`, `canyon_roads`. New fixtures verify the missing higher-context closure, preserved overhang air and exact boundary classification. Rejection/unchanged-input fixtures remain in the suite.
- The authored wall retains 25 solids, 1,690 core triangles, 9,849 adapted triangles, 1,935 elevated-route samples and 612 targeted-join samples. Its nine capture modes and the six recorded production source/configuration hashes remain verified.

Next is **visual refinement of cap/backing height transitions and rear silhouettes on the verified cases**. Raised cap outlines, triangular height ridges and long flat rear edges remain visible. Broader straight/concave/convex/short/exit-adjacent coverage, neighbouring-section coordination, controlled construction/p95 performance measurements, interactive gameplay/occlusion acceptance and production integration remain unfinished. This matrix establishes technical generation acceptance for its selected sections; no universal seamlessness or visual rollout acceptance is claimed. Changes remain uncommitted.


## Cap/backing visual refinement — 2026-11-06

Implemented a further visual pass in the isolated seeded preview. The [locked before/after comparisons](reports/cliff-formations/visual-blend/index.html) use identical primary profiles, candidate and camera; the [twelve-case gallery](reports/cliff-formations/phase4/index.html) contains fresh shaded, top, wire and paired inspection captures. The previous twelve-pass checkpoint is preserved in `phase4/before-visual-blend/`. **All twelve remain technical passes; visual rollout acceptance remains 0/12.**

### Changes

- Replaced the seeded backing's global roof fan with a triangulated regional roof: ten controls follow the five primary caps' real rear roof edges, three sample the original visible rear terrain, and one interior control supports broad elevated land. This distributes the height transitions instead of converging on one high apex.
- Constrained backing patches to the primary roof planes wherever they overlap a primary footprint. The backing can no longer poke through the accepted primary roofs. A separate sampled ray check verifies those surfaces against the original source volumes; it supplements all existing strict emitted-mesh checks.
- Constructed clipped roof patches as closed polygonal prisms with explicit winding, edge, plane, volume and protected-floor checks. The existing 40 micrometre fragment construction rule and strict final topology/source-boundary gates remain in force.
- Retained original rear land from six metres behind the section, with a tapered transition before it, so the backing does not expose the former long raised rear slab. Cosmetic non-floor ground at the front join now meets the existing walkable-height plane; this removes tiny crossings caused by the former shallow ramp. Original floor vertices and collision heights remain unchanged.
- The new recipe is the default only for seeded debug previews. `DW_CLIFF_BACKING=legacy` reproduces the former seeded backing for controlled comparisons. The authored wall keeps its existing construction and all nine capture modes.

### Evidence and limits

- Full bounded candidate searches pass for **12/12 rooms**. Native captures replay each successful candidate and match its headless geometry/scenery hash; full search/rejection logs remain separate from the selected-candidate capture logs. Some rooms now select different sections. Only the explicitly locked comparisons, or marked matching-section gallery pairs, establish controlled before/after shape comparisons.
- Each selected section checks 630–690 primary-roof samples. The largest sampled height difference is **0.00000953674 m in local construction coordinates**, below the 0.004 m guard. This is a sampled preservation measurement, not a claim about every world-space join; translated final topology, whole-face source coverage, elevated routes, original-floor/collision restoration and deterministic replay remain independently required.
- All four regression suites pass (`rock_formations`, `cliff_facet_refinement`, `canyon_visual_geometry`, `canyon_roads`). A new roof fixture checks projected area, control heights, upward winding, replay, intersections and invalid collinear input. The authored wall retains 1,690 core / 9,849 adapted triangles, 1,935 route samples and 612 targeted join samples. The six pinned production source/configuration hashes remain unchanged.
- All twelve fresh inspection views were reviewed. The controlled comparison removes the old long rear slab and improves the cap/backing transition, but several cases still show pointed rear facets, narrow transitions or raised cap lips. The pass does **not** finish the natural-plateau/reference acceptance criterion.

### Remaining work

1. Correct the localized pointed rear/end facets and residual cap lips identified in each case's visual notes; repeat matched reference review. Keep this visual gate open until the plateau reads as continuous land throughout the reviewed wall.
2. Expand straight/concave/convex/short/exit-adjacent coverage and coordinate neighbouring sections through shared plateau interfaces.
3. Complete controlled construction and p95 frame-time measurements, occlusion and interactive gameplay acceptance. Screenshot FPS is not performance evidence.
4. Perform production integration and rollback verification only after those gates pass.

Phases 4–6 remain unfinished. The regular game still uses A; the work remains uncommitted.


## Remaining-work continuation: cap extensions, coverage and measured gates — 2026-11-06

The [new checkpoint report](reports/cliff-formations/local-finish/index.html) combines matched visual comparisons, the boundary inventory, targeted coverage failures and controlled native performance results. **The task is not finalized and production integration has not been performed.** The measured performance and visual gates currently fail.

### Implemented and verified

- Extended the selected rear roof plane 0.45 m behind each primary cap before grading toward the rear land. Added two rear terrain stations, bringing the extended recipe to five. This gives the roof a broader transition than controls that sit only inside a cap. The earlier recipe is reproducible with `DW_CLIFF_ROOF_PREVIOUS=1`.
- Tried the extended roof on a copy, with the same source-solid, emitted-float topology, whole-face boundary, route, ray, cap-roof, floor/collision and replay checks. A rejected extension retries the previous checked regional roof on another copy. Rejection of both still leaves A untouched. A lower shared-roof trial was rejected because it disconnected elevated routes; no acceptance limits were relaxed.
- Full searches retain **12/12 technical passes**. Four selected sections use the extension: `seed0-floor0-room0`, `seed404-floor3-room2`, `seed404-floor5-room13`, `seed1866-floor0-room0`. Eight reproduce the previous final geometry/scenery hash exactly. The seed-0 early room selects a different wall; only the three matching-section/profile/camera pairs are presented as controlled comparisons. The prior checkpoint is preserved in `phase4/before-local-finish/`.
- Refreshed all 72 main-matrix capture records. Captures replay the verified section and roof recipe directly; hashes must match the complete headless search. Search/recipe rejection evidence stays in the headless logs. All four regression suites pass, including added equal-distance straight/concave/convex classification fixtures and the existing missing/short-section unchanged-input checks. The six pinned production source/configuration hashes remain unchanged.
- Added a stable, diagnostic curvature classification using equal-distance contour chords; selection ranking and the original coarse shape field remain unchanged. The [inventory](reports/cliff-formations/coverage/inventory.json) contains **2,646 candidates across 147 rooms**, sampled on early/middle/final expedition floors for seeds 0, 42, 404 and 1866. Current matrix sections include concave and convex paths as well as mixed curves; the former generic `curved` label obscured that distinction.
- Ran and captured four additional pinned native boundary cases. **One applied, three retained byte-identical A**. The exit-adjacent case is explicitly within 4 m of a connected passage gate centre in horizontal projection. This is a single sampled layout, not universal exit acceptance. The inventory contains no short sections; short rejection is covered by synthetic fixtures rather than claimed as real-room rollout coverage.

| Target | Pinned section | Current result |
| --- | --- | --- |
| Straight | `seed42-floor3-room3`, candidate 4 | Rejected: exact core connection audit |
| Concave | `seed404-floor5-room10`, candidate 16 | Rejected: assembled join/boundary |
| Convex | `seed42-floor6-room2`, candidate 8 | Rejected: roof cell too steep |
| Exit-adjacent | `seed404-floor3-room10`, candidate 3 | Technical pass; raised cap outline and pointed rear strip remain visually unaccepted |

### Visual acceptance

The fresh extended sections were inspected. The `seed1866-floor0-room0` dominant cap now meets a quieter broad rear plane, and the matched `seed404-floor3-room2` transition is broader. Residual supporting-cap lips, pointed end/rear facets and steep constructed faces remain. `seed404-floor5-room13` still exposes a long triangular rear patch. The eight retained roofs reproduce the previous appearance. **Visual rollout acceptance remains 0/12**; the extra exit-adjacent case is also unaccepted. This continuation improves and measures the prototype; it does not establish a seamless final plateau.

### Controlled performance: both targets fail

See the [raw measurements](reports/cliff-formations/performance/status.json). Tested `seed404-floor3-room2`, candidate 2, on an AMD Ryzen 5 5600X / RTX 4070 Ti SUPER through WSL2's D3D12 renderer. Three sequential alternating A/preview trials per mode use the same binary, camera, settings and 480 deterministic uncapped frames. The first 120 frames are discarded, leaving 360 frame samples per trial. No capture or audit batches overlap these trials.

| Metric | A | Formations | Ratio | Target |
| --- | --- | --- | --- | --- |
| Median of trial p95 frame wall times | 25.9541 ms | 31.4563 ms | 1.212× | ≤1.10× — **fail** |
| Construction comparison | matched A build | A build + selected replacement work | ≥7.419× | ≤1.25× — **fail** |

The selected replacement work alone has a median construction time of about **6.57 seconds**, after the measured major audits are subtracted and replay is excluded. Timed validation covers strict topology, whole-face source boundary and sampled core routes/rays/seams. Required constructive validity and original-floor checks remain in construction time. The ratio is deliberately a **lower bound**: secondary contour-base construction, other dispatch overhead and rejected candidate searches are omitted. The construction target fails even before adding them. Frame wall times include update, draw submission and presentation; these are not GPU timer queries. Peak process RSS includes validation/replay allocations. These measurements establish a failure for this case and environment; they do not accept other cases or deployment hardware.

### Next work, in order

1. Resolve the remaining cap lips, long triangular rear patches and end facets identified in the visual notes. Review plain massing as well as shaded views; do not conceal geometry problems with vegetation. Keep all current preservation/topology gates.
2. Repair the three pinned boundary failures above and coordinate adjacent sections through shared plateau interfaces. Re-run their native hashes/captures and the twelve-case matrix after geometry changes.
3. Profile construction clipping/union/welding and render/update stages, reduce measured cost, then repeat the same sequential benchmark before expanding performance checks to the accepted case set. Keep the 10% p95 / 25% construction limits explicit; a lower-bound failure cannot be counted as acceptance.
4. Complete interactive gameplay/occlusion checks across connected rooms and expedition floor transitions. Existing floor/collision preservation and scripted captures do not constitute this acceptance.
5. Only after the visual, supported-layout and performance gates pass, integrate with an explicit A rollback option and repeat the manifest against the regular executable.

Phases 4–6 remain unfinished. The regular game still uses A. Changes remain uncommitted.


## Active-goal continuation: construction optimization — 2026-11-06

The full objective remains **finish residual cap lips/facets, boundary failures, neighbouring plateau joins, optimization and gameplay/occlusion acceptance, then offer old/new modes**. The [goal ledger](reports/cliff-formations/goal-status.json) tracks each requirement separately; no requirement is redefined around this optimization checkpoint.

Added conservative separating-plane pruning before convex clipping, projected bounds pruning for support/floor queries, reused region descriptors, and a metre-scale weld segment index. The original canonical vertex insertion, point-on-segment predicate, ordering and tolerances remain unchanged. Optional `DW_CLIFF_PROFILE=1` timings locate stage costs; `DW_CLIFF_VERIFY_WELD=1` compares every indexed edge candidate list with a full scan, and `DW_CLIFF_VERIFY_SUPPORT=1` compares the complete support shell with unpruned construction. The profiler showed core construction near 24 ms while terrain joining and support dominated; the work targets those actual costs. System `perf` is unavailable for this WSL kernel, so the scoped native timings provide the evidence instead.

**Verification:** all twelve saved selected sections/roof recipes pass strict audits and replay, match their prior final mesh/scenery hashes, match every unpruned support triangle exactly, and match the full-scan weld candidate lists. All four regression suites pass; a tiled-solid fixture covers metre-bin boundaries and T junctions. This is selected-section verification, not a fresh full candidate search or native capture batch. The regular native preview executable has not yet been rebuilt for these optimizations; previous native reports remain bound to their recorded binary.

**Sequential measurement:** three alternating trials per saved/current headless native audit binary, seed 404 / expedition floor 3 / room 2 / candidate 2, with no concurrent build/audit/capture batches. Median replacement construction falls from **5798.75 ms to 3126.86 ms (46.1% less)**, excluding the measured major audits and replay. The final geometry/scenery hash is identical in all six trials. The optimized lower-bound construction ratio versus its matched A build is still **4.90×**, above the 1.25× target. Native frame-time acceptance has not been rerun and remains open. Raw logs, source/binary fingerprints and results are in the [optimization report](reports/cliff-formations/optimization/index.html).

Remaining scope is unchanged: visual defects/acceptance; the three targeted boundary failures; coordinated neighbouring plateau interfaces; further construction and rendering optimization; interactive gameplay/occlusion acceptance; and accepted user-selectable **Old / New** modes with rollback. Next work must advance these requirements, not treat unchanged geometry or faster construction as completion. The goal remains active.


## Active-goal continuation: boundary construction and independent checks — 2026-11-06

The [boundary refinement checkpoint](reports/cliff-formations/boundary-refinement/README.md) records the next construction changes, rejected experiments and fresh evidence. Seeded buttresses now require a positive attachment to their parent. The pinned straight core is connected and closed; its full terrain assembly still rejects. An optional constrained-roof trial retains cap corner anchors, adds a rear midpoint and attempts a concave backing domain. The full trial search passes 12/12 technically, usually by retrying the earlier roof. Its genuinely constrained exit-adjacent roof produces a worse narrow rear blade in native views. It is therefore rejected visually and moved behind `DW_CLIFF_ROOF_CONSTRAINED=1`; the prior extended roof and earlier-roof retry remain the default. The trial can also reject a self-intersecting domain. A successful retry is not acceptance of the new roof. Backing prisms use convex projected footprints and double-precision side planes. All preservation and final strict checks remain in place.

Added an independent rational-arithmetic oracle for emitted float meshes and source half-spaces. Simple contact/intersection and source-band fixtures pass. A preserved rejected boolean specimen has two buried fragments and four detached fragments under the independent check. The optional Manifold backend is a default-OFF build experiment; normal builds neither fetch nor link it. It is not an accepted terrain replacement.

Both native preview and headless audit rebuild successfully. All four regression suites pass, and the six pinned production files are unchanged. The four pinned coverage cases still give **one technical pass and three byte-identical A fallbacks**. Trial full-search results are separate from final-default selected-candidate verification in `boundary-refinement/`. The final default reruns the twelve saved candidates and four pinned coverage cases, with source/binary fingerprints and limited matched captures. The previous twelve-case report and trial captures remain historical evidence for their own binaries.

The trial seed-0 early-room inspection still shows a raised dominant cap, sharp supporting transitions and a pointed rear region. It selects the earlier roof after rejecting the trial outline; the final default reproduces its final geometry/scenery hash. Fresh final-default exit-adjacent views retain the prior rear outline but still show the raised cap and long sharp supporting transition. **Visual acceptance remains 0/12.** No current performance acceptance is inferred from these concurrent audit/capture runs.

Final verification at this checkpoint: **12/12 saved selected candidates** pass strict audits and replay with the final default; this is not a new complete candidate search. The four pinned targeted cases remain **1/4**; all four regression suites pass. Six matched native capture records review one final-default case. The rejected constrained trial remains reproducible only through its explicit debug flag.

Next: construct a simple cap/rear envelope and verify its area/roof coverage; fix the three terrain-boundary failures; coordinate neighbouring plateau interfaces; reduce and remeasure construction/render costs; complete interactive gameplay/occlusion acceptance; then integrate and verify Old / New modes with rollback. Phases 4–6 and the full goal remain unfinished. The regular game still uses A; changes remain uncommitted.


## Active-goal continuation: continuous grading and independent verification — 2026-11-06

The [graded plateau checkpoint](reports/cliff-formations/graded-plateau/README.md) and [matched native comparison](reports/cliff-formations/graded-plateau/index.html) introduce an opt-in roof that merges cap backs into broad land. **This is a design trial with an explicitly revised roof criterion:** original cap volumes stay intact, front roof strips are protected, and rear roofs may be covered by the common land. The default retains complete cap-roof preservation. The trial does not claim to satisfy the earlier full-roof-preservation criterion.

The new grading kernel builds continuous piecewise linear ramps from all crown planes and passes analytical area/height/continuity and multi-facet tests. All four pinned local cores pass strict closure and whole-face source coverage. One final assembly/world replay applies; the other three still retain byte-identical A after assembled-join rejection. In the captured case, 182 protected front-roof samples differ by at most 0.00000190735 m, while 493 rear samples intentionally permit a raise up to 1.90521 m. An independent rational check finds zero conflicts among 13,694 potential triangle pairs and zero buried/detached fragments in that core.

The source-boundary verifier now clips in double precision independently of construction epsilon. The 0.1 mm margin and 1e-12 m² fragment threshold are unchanged. Native and rational checks agree on accepted, rejected and source-band specimens; narrow-gap and 0.11 mm offset fixtures guard the contract. The final default passes all twelve saved candidates and reproduces all twelve previous geometry/scenery hashes. All four regression suites pass; six pinned production files remain unchanged.

**Visual acceptance is still absent.** The central raised-cap outline merges into land, but the finite rear/end footprint now visibly ends as a raised slab against retained terrain. Pointed ramp facets and long straight edges remain. This identifies the next integration task: match a rear/end collar to the actual retained roof, then build common land once per connected plateau region with shared constraints from neighbouring sections. Do not hide the interface with vegetation or count a local core pass as an assembled/world pass.

A conservative grading optimization is also ready to implement: skip a convex cell only when one affine cap bound dominates its current roof everywhere (prove this at every vertex). The maximum of bounds can hide an interior cap even when its values at all polygon corners are high, so that weaker shortcut is invalid. Remove unnecessary partitions before repeating sequential construction/render measurements.

The optional full-roof/boolean experiments remain rejected and disabled by default. More precise adapter source planes did not recover the three joins and were rolled back; unrefined surrounding terrain also remains 1/4. Next work remains the rear/end land interface, coordinated neighbouring plateau regions, the three assembled failures, residual visual facets, controlled performance, interactive gameplay/occlusion acceptance and accepted production **Old / New** modes with rollback. Phases 4–6 and the full goal remain unfinished; the regular game still uses A.


## Active-goal continuation: retained-terrain blend and checked shell extraction — 2026-11-06

The [new checkpoint](reports/cliff-formations/plateau-collar/README.md) implements the rear/end blend and conservative grading pruning proposed above. It remains opt-in under `DW_CLIFF_ROOF_COLLAR=1`, `DW_CLIFF_ROOF_SHELL=1` and `DW_CLIFF_WORLD_GRID=1`, together with the merged-roof trial and required-new-roof flags. The default full-roof criterion and regular gameplay A are unchanged. All twelve saved default candidates pass strict audits/replay and reproduce their previous geometry/scenery hashes; all four regression suites pass and all six production pins remain unchanged.

The new blend limits the graded land against the actual retained roof planes at external rear/end interfaces. Direct body-shell extraction preserves each source roof height, represents step differences with explicit vertical risers, and retains protected-floor holes. Original body prisms remain the whole-face source oracle. Triangle passthrough avoids unnecessary centroid fans. Coplanar interior stars are simplified only through valid disk replacements with identical directed boundaries and checked intersections. Full emitted-mesh/source checks still guard the result. World-grid construction addresses the observed failure where local topology passed but restored world coordinates broke it. Mandatory constructive legality checks count as construction time, including when nested inside validation.

**Trial coverage remains 1/4 final passes.** The failure stages now differ: the straight case rejects an invalid body shell; the convex case exceeds the unchanged triangle budget; the concave case rejects assembled terrain. Do not carry forward the previous checkpoint's four-local-core success claim to this new blend. All three fallbacks retain byte-identical A. The passing exit-adjacent core has 1,910 triangles, with a connected closed surface and zero source-boundary errors. Its final world assembly passes, with 181 intentional boundary edges, unchanged floor/collision and deterministic geometry/scenery replay. The independent rational check tests 19,235 candidate pairs with zero conflicts, buried fragments or detached fragments.

**Visual acceptance remains zero.** The [matched native comparison](reports/cliff-formations/plateau-collar/index.html) contains six records from one room. The rear boundary changes locally, but a large central vertical step, pointed roof facet, steep end transitions, long bands and cap lips remain. A mathematically matched body boundary does not prove the full union of body/caps/retained land forms a seamless plateau. This trial is structurally valid for one room and visually unaccepted; it is not production New mode. Controlled construction comparison and its limits are recorded separately in [the timing ledger](reports/cliff-formations/plateau-collar/construction/construction.json); no native p95 or gameplay acceptance is inferred from these captures.

Next work, with the current preservation and topology gates intact:

1. Diagnose the straight shell before simplification; preserve a rejected specimen and identify the first invalid shared edge or crossing. Reduce convex roof partitions/triangles without increasing the budget. Trace the concave assembled boundary to its retained source faces. Re-run each locked candidate and world replay after a repair.
2. Measure the **full union's** height at each external interface, including original cap volumes. Identify which source surface produces the remaining central step. Extend common land far enough to bury cap-back walls while meeting retained land; a clamp on the body alone cannot guarantee this.
3. Build the roof once per connected plateau region, collecting constraints from every participating wall. Put collars on external region boundaries and verify neighbouring straight/concave/convex/exit sections. Regional ownership and shared constraints are still unimplemented.
4. Refine pointed ramp/end facets and cap lips in neutral and shaded matched views, then broaden visual acceptance beyond this one room. Keep vegetation out of the acceptance argument.
5. Meet controlled construction and native p95 limits, complete interactive gameplay/occlusion across connected rooms and expedition floors, then integrate and verify accepted **Old / New** modes and rollback with the regular executable.

The goal remains active. Phases 4–6, broader acceptance, performance and production integration remain unfinished; changes are uncommitted.

Sequential timing for this checkpoint: three alternating trials per saved/current audit binary reproduce the same trial mesh/scenery hash in all six trials. Faster simplifier legality checks reduce median selected replacement construction from **11,698.7 ms to 9,961.27 ms (14.9%)**, with mandatory constructive checks included. The new blend's lower-bound construction ratio versus matched A is still **13.73×**, above the 1.25× limit. This uses a different case/geometry from the earlier 4.90× specimen and is not a direct regression comparison. No concurrent audit/capture/oracle batches ran during timing. Native p95, broader performance and the complete goal remain unaccepted.


## Active-goal continuation: boundary-derived constraints — 2026-11-06

The [boundary-trace checkpoint](reports/cliff-formations/boundary-trace/README.md) replaces the tile-based collar in an explicit new trial. The previous turn was progress, not completion. The full scope in the goal ledger remains intact.

The new diagnostics refine the cause of the visible rear step. At 128 pre-assembly external-interface samples, positive body-height excess over retained terrain is at most 0.00000429154 m, and no primary cap dominates the sampled edge. The retained roof itself jumps by up to 1.17786 m between adjacent samples. These are sampled construction diagnostics, not proof of the assembled boundary, but they show that treating the whole defect as an unmatched exterior seam is too broad. Projecting whole retained terrain tiles inward also carries their interior steps into the common roof.

Added `plateauBoundaryGrades`: intersect source roof domains with each external edge, include upper-envelope crossings, and extend the selected boundary segments into continuous inward ramps with continuous endpoint bounds. In the verified room, 51 segments replace the interior tile constraints. `DW_CLIFF_ROOF_BOUNDARY_GRADES=1` enables this separately from the earlier collar. Kernel tests preserve flat/sloped boundary height and inward slope while preventing an unrelated interior source step from becoming a vertical roof riser. At genuinely discontinuous source boundaries the body may lie below the higher source roof; wider region selection remains necessary. Do not claim full-union seamlessness from the body field alone.

The new trial passes final local, assembled, world, source-coverage, original-floor/collision and replay checks in one of the four pinned rooms. Its core is 2,014 triangles, under the unchanged 2,400 limit. The other three remain byte-identical A fallbacks. The earlier collar's four outcome/hash records are reproduced separately, as are all twelve saved default geometry/scenery hashes. Four regression suites pass. The regular game still uses A.

The straight shell's nine coplanar bottom overlaps are now preserved and independently confirmed. A near-edge welded point can make a thin split polygon concave and fold its centroid fan. Dominant-plane ear triangulation passes an isolated regression in all three orientations, but broad application fails the targeted rooms later in construction. It is retained only as the default-off `DW_CLIFF_EAR_WELD=1` experiment. It has not repaired the straight case, and no strict check or triangle budget was relaxed.

Fresh matched native views and independent rational checks are recorded in the new checkpoint. They do not establish broad visual, performance, gameplay or production acceptance. Existing controlled construction and p95 evidence remain unaccepted, and no fresh performance claim is made for this changed roof.

Next: use the matched views to separate residual old-terrain steps from body artifacts; choose a connected plateau region whose external boundary avoids bisecting a retained cliff; collect neighbouring sections' front constraints into that region; repair the three locked rejections; refine cap lips and pointed facets; then complete broader visual, controlled performance, gameplay/occlusion and production **Old / New** rollback gates. Phases 4–6 and the full goal remain unfinished.


## Active-goal continuation: connected ownership and regional construction scope — 2026-11-06

The [connected-region checkpoint](reports/cliff-formations/connected-region/README.md) implements source roof connectivity, cap-reach closure, shared footprint construction and a guarded regional roof path. The [interactive map](reports/cliff-formations/connected-region/index.html) shows source planning, not accepted new terrain. The previous goal turn was progress; the full objective remains active.

The planner follows positive-length shared roof edges, including T-junctions. Point contacts and distinct height tiers remain separate. A wall selects complete source components; cap backs can additionally reach complete neighbouring terraces. Canonical source terrain owns that graph independently of the retained A detail surface. Region constraints are restricted to the combined footprint's actual exterior, so an old edge buried by a new cap does not remain an internal collar. The footprint union preserves holes, uses a 1/65,536 m binary grid, follows cap upper rims rather than their wider bases, and cuts protected front-cap strips out of the body domain. Original cap volumes remain intact.

The new roof path samples one shared field, improves interior diagonals before height assignment, and separates point-touching pieces by shared-edge connectivity before attempting individually checked bodies. Full final core/assembly/world/source/floor/replay gates are still required. Intermediate source-domain components are not accepted rendered meshes. The optional Boost polygon backend is isolated behind default-OFF `DEATHWARD_CLIFF_REGION_EXPERIMENT`; runtime `DW_CLIFF_ROOF_REGION=1` remains an unaccepted trial.

**The resulting scope is larger than a wall-local rebuild.** The exit-adjacent wall seeds a 301.1 m² component with 918 source roof faces and 73 neighbouring floor-level cliff edges. Its cap backs reach highland that expands the plan to 19,827.6 m² and 59,924 source faces. The four composed candidates span 19,827.6–69,926.8 m² and 2–5 source components. These are projected source-face sums, not disjoint union areas. The concave candidate includes 187,443 source faces. Complete ownership must not imply rebuilding a whole highland component or raising it to one maximum height whenever a wall changes.

**Regional construction acceptance is 0/4.** All four candidates reject their external footprint and preserve byte-identical A. Earlier analytic partitioning, sampled sliver and point-contact failures remain construction evidence, not visual success. No new regional core has an accepted independent exact oracle or native visual capture. The previous boundary-derived trial's one pass/three fallback outcome hashes are reproduced separately, and all twelve saved default candidates reproduce their previous geometry/scenery hashes. Four regression suites pass; six production pins are unchanged. Normal configuration succeeds with Boost discovery disabled, and the planner source compiles without Boost headers when the experimental macro is absent. These configuration/source checks are not a full macro-OFF executable rebuild.

The next construction task is now explicit:

1. Preserve global floor/plateau ownership, but assign deterministic bounded construction chunks aligned to canonical terrain. Compute a conservative influence halo for relevant neighbouring caps, rather than using isolated 14–24 m windows or rebuilding an entire component.
2. Evaluate one shared height definition at common world-grid edge vertices on both sides of each chunk. Collect participating wall/front constraints, retain baseline heights outside local edit influence, and remove internal chunk walls. The current component-wide maximum land target is a rejected prototype, not the final field.
3. Diagnose and repair external footprint topology under that representation, including point pinches and holes. Verify combined chunks across room boundaries and height tiers with all strict source/floor/manifold/world/replay guards intact. Keep the original three pinned failures explicit until they actually pass.
4. Refine residual cap lips, pointed facets and long bands, obtain broader matched native visual acceptance, then meet construction/p95 limits and interactive gameplay/occlusion acceptance across connected rooms and expedition floors.
5. Integrate and verify accepted production **Old / New** modes and rollback only after those gates pass.

Phases 4–6 and the full goal remain unfinished. The regular game still uses A; changes are uncommitted. Current concurrent audit timings establish no performance acceptance.

## Active-goal continuation: shared local chunks — 2026-11-07

The [shared-chunks checkpoint](reports/cliff-formations/shared-chunks/README.md) implements a bounded local construction kernel under the existing experimental region flag. This is progress, not completion of the cap/facet refinement or the full goal.

One world-space 1 m grid supplies deterministic 16 m chunks, including negative coordinates. Common nodes share the same height deformation; changing chunk size does not change the synthetic roof geometry. The field retains source heights outside compact support, uses local cap/terrain targets rather than a whole-component maximum, and excludes protected front-cap strips. Six-metre node support has a conservative piecewise-linear support of `6 + sqrt(2)` metres. The exit case bins 1,211 nearby source faces from a 59,924-face ownership plan. This reduction in construction scope is not a measured performance improvement. Other walls' caps are not yet collected through a shared registry.

Synthetic tests pass for identical shared-node heights, chunk-size invariance, retained sloping border heights, distant-highland independence, protected cutouts and closed shells where adjacent roof tiers exchange height along an edge. The new edge split remains opt-in and keeps the existing weld radius. The general ear-weld experiment remains off; chunk-only planar triangulation does not waive any final guard.

**Native chunk acceptance is 0/4.** All four locked candidates now reach local roof construction but reject a nonmanifold projected edge. The exit witness contains a one-quantum strip with three incident faces. Local welding and a shared-edge crossing split do not fix the entire partition. A further overlay/union trial increased geometry and still rejected a four-owner edge; that trial was removed. Every rejected candidate preserves byte-identical A. The original three boundary failures remain unresolved, and no accepted new chunk core exists for visual or independent exact acceptance. The 2,400-triangle, source-coverage, original-floor, topology and replay gates remain unchanged.

Current regression ledgers, test logs and source/binary fingerprints are persisted in the checkpoint. The native preview builds, but chunk-mode rejection displays A; this is not an accepted New mode. No controlled construction or native p95 acceptance measurement was run. The regular gameplay path and six pinned production files remain unchanged.

Next: construct a consistent projected arrangement across source faces and grid cuts; resolve thin overlaps and point pinches; collect all participating neighbouring-wall constraints; verify combined bodies across room boundaries and height tiers. Then refine residual cap lips, pointed rear facets and long bands in accepted native meshes, obtain broader visual acceptance, meet controlled performance limits, complete interactive gameplay/occlusion across expedition floors and integrate production Old / New selection with rollback. Phases 4–6 and all six goal requirements remain unfinished; the goal remains active.

## Active-goal continuation: continuous chunk field — 2026-11-07

The [continuous-chunks checkpoint](reports/cliff-formations/continuous-chunks/README.md) changes the roof construction after the previous turn's thin-strip failure. This is concrete progress, not completion of the full goal.

A vertical slab partition resolves the small saved overlap witness, but the native exit trial expands to 373,348 projected triangles and still has point-contact defects after extrusion. It is rejected as the current construction path and remains off under a diagnostic flag. Synthetic crossing-chain and hole tests pass; these do not establish native partition acceptance.

The current chunk field instead unions source/cap footprints before assigning one affine field per grid triangle. Shared node samples interpolate the upper retained roof and blend to the local cap/terrain target. A new source-tier test verifies a single height at the shared seam. The original cap volumes and protected front strips remain. Unlike the previous additive per-source field, this interpolated baseline can differ from irregular retained source faces between samples; exact exterior matching remains unproven and must be checked against actual source breakpoints. The unchanged linear-border test is not broad native seam acceptance.

**The exit case passes all six individually closed plateau bodies and their constructed-prism coverage checks.** Its roof cells fall from 6,676 to 3,304. The largest simplified body still has 10,242 triangles, so geometry reduction and the unchanged 2,400-triangle final core budget remain substantial work. This field change is not a like-for-like performance measurement. The chunk-only simplifier now uses its largest incident triangle as a stable plane reference while retaining the same planarity tolerance and mandatory replacement checks.

**Final native chunk acceptance remains 0/4.** The straight shell rejects six crossings; concave and convex reject four and two nonmanifold edges respectively. The exit gets through body construction but rejects the combined cap/body core with seven open edges, fifteen nonmanifold edges, twenty-three vertex-link failures, fourteen crossings and eight overlaps. The persisted emitted-float core and independent rational check confirm all twenty-two reported crossing/overlap pairs; they are rejection evidence, not a complete acceptance oracle. Every rejected case retains byte-identical A. The original three boundary failures remain unresolved.

The report preserves default/previous-boundary replay ledgers, regression tests, source/binary fingerprints and six unchanged production pins. The optional native preview builds, but rejected chunk trials display A. No new visual, controlled construction/native p95, gameplay/occlusion or production Old / New acceptance is claimed.

Next: repair the emitted body point contacts and straight-shell crossings; fix the combined cap/body junction and constrain outer transitions to actual retained source breakpoints; reduce geometry without raising the budget; collect neighbouring-wall constraints and verify combined cross-room construction. Then refine cap lips, pointed rear facets and long bands, broaden matched visual acceptance, meet performance limits, complete interactive gameplay/occlusion across expedition floors and integrate accepted production Old / New selection with rollback. Phases 4–6 and all six goal requirements remain unfinished. The goal remains active; changes are uncommitted.

## Active-goal continuation: shared footprint and finite links — 2026-11-07

The [finite-links checkpoint](reports/cliff-formations/finite-links/README.md) advances body construction from one passing case to three. The previous turn was progress; the full objective remains active.

The field now clips one common nearby source/cap footprint to the world grid. A projected vertex-fan detector identifies point-only contacts before extrusion. At two convex-case contacts it adds deliberate terrain links of 4 cm radius (8 cm across), followed by the existing protected cuts. These are local shape changes requiring visual acceptance, not an increased numerical weld tolerance. A one-quantum bridge passed the small synthetic test but was insufficient on the native render grid and was superseded.

The chunk path also stops deleting positive cells solely for the old minimum-area/40-micrometre-width heuristic. Deleting a thin finite connection could recreate a pinched solid. This changes construction filtering; it does not waive convexity, positive-volume, protected-floor, final exact topology/source coverage or the 2,400-triangle core budget. The ordinary path retains its previous filtering. Tests verify finite link width, valid connected footprint topology, locality and an empty later protected cutout.

**All individual bodies pass in three of four native cases:** nine straight, ten convex and six exit-adjacent pieces. The concave shell has no remaining nonmanifold edges or vertex-link failures, but still rejects ten crossings and two overlaps. Its persisted emitted-float witness and independent rational check confirm all twelve reported conflict pairs. A sample has boundary vertices one binary quantum apart whose adjoining triangles cross; shared clipping/partition coordinates remain a concrete next target.

**Final chunk assembly acceptance remains 0/4.** The three cases that pass body construction reject combined cap/body cores with topology/intersection defects; straight and convex also retain multiple components. All four fall back to byte-identical A. The exit's largest body drops from 10,242 to 7,486 triangles, but this is not controlled performance evidence and still exceeds the unchanged final budget. The largest straight and convex bodies are 15,838 and 12,772 triangles. Original boundary failures, retained irregular-boundary agreement and neighbouring-wall coordination remain unresolved.

All twelve saved default geometry/scenery hashes and all four previous boundary outcomes/hashes reproduce; four regression suites pass. The native preview builds and six production pins remain unchanged. This provides neither fresh broad candidate coverage nor accepted visual, controlled performance, gameplay/occlusion or production Old / New modes.

Next: repair the concave partition intersections and the three combined cap/body cores; constrain transitions to actual retained source breakpoints; reduce geometry; coordinate all participating neighbouring walls and verify combined cross-room bodies. Then refine remaining cap lips/facets and long bands, review the finite links in matched native views, meet construction/p95 limits, verify interactive gameplay/occlusion across expedition floors and integrate accepted production Old / New selection with rollback. Phases 4–6 and all six goal requirements remain unfinished. Changes are uncommitted.

## Active-goal continuation: contour field and checked bodies — 2026-11-07

The [contour-field checkpoint](reports/cliff-formations/contour-field/README.md) advances all four locked cases through individual body construction: **29 closed, source-checked bodies**, including the previously failing concave body. Contour triangulation with exact collinear cleanup avoids artificial decomposition cuts; cap-boundary controls and conforming roof refinement remain experimental. The source baseline between irregular retained-terrain breakpoints is still unverified.

The optional solid union now consumes the checked body meshes while retaining original cap/prism half-spaces as its independent oracle. A bounded, opt-in float repair changes one shared exit vertex by 0.238 micrometres. It preserves topology and reduces crossings, without changing audit tolerances. The roof-coverage probe also caps its existing inward step so it cannot overshoot a tiny source triangle's centre; the height and coverage requirements remain unchanged.

**The exit final core passes:** one closed component, 1,790 triangles under the unchanged 2,400 limit, no strict topology/intersection/overlap defects, no native source-boundary fragments, 21,868 coverage rays, and front-cap preservation within 0.0000038147 m. An independent rational check confirms zero conflicts across all 18,607 candidate triangle pairs and zero buried/detached fragments against the complete original half-space source boundary. These results apply to the core only.

**Final assembly acceptance remains 0/4.** The exit reaches the retained-terrain join and rejects unverified boundaries/nonmanifold edges. Straight and convex retain four and two components respectively; concave retains seven crossings and two components after the optional repair. Those three also exceed the core budget. All four rejected trials keep exactly their original A geometry/scenery hashes. The original boundary failures and complete neighbouring-wall joins remain unresolved.

A uniform body inset worsened the exit core and was removed. A direct Boolean union with retained terrain prisms also failed topology and source coverage and was removed. Their diagnostic logs are preserved; neither is an accepted fallback. The next construction must share seam vertices and actual retained source-plane heights, rather than independently interpolating both sides or widening weld tolerances.

The checkpoint records optional kernel tests, four passing regression suites, current replay ledgers, executable/source fingerprints and six unchanged production pins. The macro-off native preview builds. No new visual, controlled performance, gameplay/occlusion or production Old / New acceptance is claimed. Geometry reduction does not supersede the earlier failed performance acceptance.

Next: construct a conforming retained-terrain seam with actual source breakpoints; resolve disconnected ownership and remaining concave intersections; meet the other three core budgets; coordinate neighbouring-wall caps and verify cross-room/world/floor/replay. Then refine and visually accept cap lips, pointed rear facets, long rear edges and finite links, broaden seeded coverage, meet construction/native p95 targets, verify interactive gameplay/occlusion across expedition floors and integrate accepted Old / New modes with rollback. Phases 4–6 and all six goal requirements remain unfinished. Changes are uncommitted; the goal remains active.

## Active-goal continuation: retained-source seam witness — 2026-11-07

The [retained-seam checkpoint](reports/cliff-formations/precise-join/README.md) identifies a concrete shape defect behind the remaining assembly failures. The previous turn was progress, and the complete objective remains active.

An actual local-source fixture preserves 1,211 owned original roof faces, five cap domains and nineteen cutouts. An independent exact-rational oracle checks boundary midpoints outside both active direct/nodal deformation and local contact controls. **32 of 39 eligible midpoint samples differ from the owned original source by more than 0.1 mm; the worst drop is 2.473959949 m.** A narrow source roof strip falls between grid nodes, and the 0.12 m fallback at an outside node pulls the generated roof down. This is a source-baseline error, not a small weld gap. The samples prove failure; they are not a complete edge/world acceptance check.

More accurate source planes and extended-precision clipping do not solve this native join. Their first assemblies have substantially more boundary/topology defects than the existing path. Their emitted meshes and bounded source context are saved, and independent rational checks confirm the reported conflict pairs checked. Those diagnostic processes were deliberately terminated after their captured rejected assemblies; exhaustive retries and final exit fallbacks are not claimed for those variants. The separate existing-arithmetic exit baseline completes with the unchanged A hash, and its verified core is identical to the previous checkpoint.

A new optional clipping primitive passes tests for distinct roof layers one float step apart, genuine coincident ownership, plane-order invariance and an analytic clipped corner. Existing protected-floor/synthetic-wall checks pass with it selected. This is kernel research, not an accepted native seam. Diagnostic arithmetic flags are sampled once per join operation. Production geometry and all final acceptance tolerances remain unchanged.

Current verification reproduces twelve default geometry/scenery hashes and all four previous boundary outcomes/hashes. Four regression suites pass; the macro-off native preview builds; all six production pins remain unchanged. The earlier 29 body passes and one exit-core pass remain verified, while **full assembly acceptance remains 0/4**. No new visual, controlled performance, gameplay/occlusion or production Old / New acceptance is claimed.

Next implementation: preserve actual source planes and breakpoints in each projected grid-cell partition, and interpolate only deformation over those source planes. Preserve those constraints through triangulation/refinement and share the actual intersections with retained terrain. A nearest-face extension, raising only the saved samples, or wider welds would not prove a seamless retained boundary. Then repair the other core failures/budgets, coordinate neighbouring-wall constraints and pass full cross-room/world/floor/replay checks. Visual cap/facet/edge refinement, broad coverage, controlled construction/p95, interactive gameplay/occlusion across expedition floors and accepted production Old / New selection with rollback all remain open. Phases 4–6 and all six goal requirements remain unfinished; changes are uncommitted.

## Active-goal continuation: preserved source-plane samples — 2026-11-07

The [source-planes checkpoint](reports/cliff-formations/source-planes/README.md) implements the source-plane field and a shared labelled projected ownership arrangement. All **39 saved cold boundary midpoints now match** the original source within 0.2 micrometres, with no missing roof. The old field still reproduces 32 failures and its 2.474 m worst drop. Matching those samples does not prove complete seam acceptance.

All four locked source-plane trials pass projected edge/intersection/overlap checks and primitive validation. However, point contacts remain and **0/4 pass 3D body or final assembly validation**. All four preserve their original A geometry/scenery hash. This replacement's body results must not be combined with the previous continuous field's 29 accepted individual bodies and verified exit core.

The saved exit shell has twenty exact nonmanifold edges, all vertical and within approximately 8 micrometres of original source-triangle boundaries. Three lie inside original protected cutouts. A new independent diagnostic records exact projected membership and approximate boundary distances. This points toward constructing shared source/grid intersections once; it does not justify broad bridges or filling protected floor. A uniform footprint-expansion trial completes all four cases but fails coverage/partition guards and remains a rejected default-off diagnostic. An independent rational check classifies the exit's 57 reported crossing pairs as disjoint; complete intersection acceptance is not established and the native guard remains unchanged.

Next: eliminate independently rounded source/grid strips while preserving original cutouts, prove bounded active deformation and cap-boundary conformity, then pass complete 3D bodies and retained-terrain joins. Resolve the other core failures and unchanged triangle budgets, coordinate neighbouring walls and verify full cross-room/world/floor/replay. Residual cap lips, pointed facets, long rear edges, visual acceptance, broader coverage, controlled construction/native p95, interactive gameplay/occlusion across expedition floors and production Old / New modes with rollback remain unfinished. Phases 4–6 and all six goal requirements remain incomplete; the regular game remains A and changes are uncommitted.

## Active-goal continuation: shared-cut topology isolated — 2026-11-07

The [shared-cuts checkpoint](reports/cliff-formations/shared-cuts/README.md) tests original source domains and grid triangles as conjunctive labels in one arrangement, avoiding separately clipped cell outlines. The synthetic ownership/cutout tests pass, but **all four native trials still reject** with unchanged A. This candidate increases point contacts and geometry and is not promoted. It preserves the same 39 cold midpoint heights within 0.3 micrometres; previous source-plane outcomes and roof-cell fixtures reproduce exactly.

The exit arrangement has 32 point contacts. Three match exact positions in the uncut source footprint. Of the other 29, **28 lie strictly inside both uncut source triangles and active-grid triangles**, verified independently with rational membership. They are introduced inside the intended footprint, not at its outer active boundary. The remaining contact needs further classification. This establishes that a single rounded integer ownership scan does not itself preserve topology; the existing positive-area per-region triangulation checks are insufficient as a whole-footprint invariant.

Next implementation: build and verify a topology-preserving shared arrangement, including full projected footprint coverage and vertex-fan validity. Evaluate conforming snap rounding against the saved native source/grid/partition fixtures; it remains unimplemented. Address the three source-footprint pinches separately without filling protected floor, then verify 3D bodies, actual source constraints, cap-boundary conformity, retained-terrain assembly and floor/replay. Original boundary/core failures, triangle budgets, neighbouring walls, residual visual refinement, broader coverage, controlled performance, interactive gameplay/occlusion across expedition floors and accepted production Old / New modes with rollback all remain unfinished. All six goal requirements and phases 4–6 remain incomplete; the regular game remains A and changes are uncommitted.

## Active-goal continuation: snap rounding and exact contacts — 2026-11-07

The [snap-round checkpoint](reports/cliff-formations/snap-round/README.md) implements a common hot-pixel arrangement with integer intersection/membership predicates and an explicit proper-crossing guard. Real intersections exactly on pixel corners are shared by both edges. The final locked cases need one routing pass each; the bounded multi-pass fallback still rejects unresolved crossings.

Projected point contacts fall from 54/48/17/32 to **5/3/5/2**. Both remaining exit contacts match the uncut source footprint; none of its previously proved interior contacts remain. An independent rational check of the exit's initial 42,876-triangle shell finds **zero conflicts across all 566,814 bounding-box candidate pairs**. The previous 27 native reports were twenty legitimate shared vertices and seven disjoint pairs.

An optional exact integer contact predicate now checks every conservative candidate pair and is shared by full and local replacement validation. It retains legitimate common vertices/edges and detects all positive coplanar overlaps, including below the old area cutoff. Subnormal separation, genuine crossing, tiny-overlap and full/local simplifier tests pass. This is a predicate correction, not a larger acceptance tolerance; default gameplay remains unchanged.

The snap/source field recovers **six individually closed, constructed-prism-checked exit bodies**. The combined core still rejects one nonmanifold edge and has 8,550 triangles, above the unchanged 2,400 limit. Straight and concave still reject two nonmanifold shell edges each; convex rejects an unrepresentable roof-crossing split. All four complete trials keep byte-identical A. The earlier continuous field's 29 body passes and verified exit core are separate historical results, not acceptance of this source-preserving replacement.

A further height defect is now measured: at the core's cutout-adjacent pinch, original roof height is about 4.052 m, the local land-height reference is 4.343 m, and the additive field reaches 6.324 m. A source-aware node-blend trial removes that saved upward overshoot but rejects all four bodies, with many new height-junction defects on three cases. An exact counterexample proves separate nodal interpolation can disagree by 0.125 m along a shared non-grid source edge. That trial remains rejected and default-off. Both trials preserve the same 39 saved cold source samples within 0.3 micrometres; this is not complete original-source acceptance.

The latest normal audit/tests/native preview build; four regression suites pass. Twelve default and four earlier boundary outcomes/hashes reproduce, as do all four earlier shared-cut outcomes and byte-identical roof-cell fixtures. Six production pins remain unchanged. No new visual, controlled performance, gameplay/occlusion or production Old / New acceptance is claimed.

Next implementation: evaluate deformation at actual shared source/grid intersection vertices, retaining source/target/floor break lines and grid identity through grouping. Construct deformed planes from precise sampled heights and preserve original cold affine planes. Verify the analytic continuity counterexample and native fans, then resolve protected-cutout/source pinches and the convex crossing without relaxing guards. Pass complete original-source/cap/core/retained-terrain/floor/world/replay checks and unchanged budgets, coordinate neighbouring walls, then finish visual cap/facet/edge refinement, broad coverage, controlled performance, interactive gameplay/occlusion across expedition floors and accepted production Old / New selection with rollback. All six goal requirements and phases 4–6 remain incomplete; the regular game remains A and changes are uncommitted.

## Active-goal continuation: shared vertex blend and tighter output processing — 2026-11-07

The [vertex-blend checkpoint](reports/cliff-formations/vertex-blend/README.md) evaluates deformation at actual shared source/grid vertices and retains grid identity through ownership grouping. Original cold affine planes survive. Shared active-height corrections remove extreme skinny-triangle gradients within incident vertex bounds while keeping cold/full-target anchors fixed. The existing slope and acceptance guards remain unchanged. Explicit source/target/floor crossover break lines, interior envelope bounds and exact cap-boundary conformity remain unfinished.

A one-quantum protected-cutout clearance and finite source links/cuts recover **all 29 individual constructed-prism bodies** across the four locked cases (9/4/10/6). These are checks against the new nominal constructed prisms, not complete original-source/world/floor acceptance, and must not be combined with the separate historical continuous-field result. All 39 saved cold boundary midpoint witnesses still match within 0.2 micrometres.

The source-boundary validator now retains every positive intermediate piece and compares the **total uncovered area of each original mesh face** against the unchanged 1e-12 square metre threshold. Two saved fixtures prove both the previous false rejection of covered partitioned geometry and false acceptance of fragmented gaps; native and independent rational results agree. One saved concave rejection was false; five saved exit faces genuinely violated the existing source half-space contract. Historical rational source-boundary results used the old per-piece area policy and need rechecking under the corrected policy before being relied upon; historical intersection results are separate.

At the default 8-micrometre Boolean simplification setting the exit core is topologically valid but has genuine detached source fragments. Captured checked-body meshes and nominal source planes reproduce its face coordinates/order exactly without world generation. **Reducing construction simplification tolerance to 1 micrometre fixes the exit's native topology and source-boundary checks.** The native result exactly matches replay: one closed component, zero strict intersection/overlap/topology defects, zero buried/detached fragments at the unchanged 0.1 mm positional margin. Raw float Boolean output remains invalid, so skipping output processing is rejected.

**The exit still fails the unchanged budget: 13,200 triangles against a strict limit below 2,400.** It does not reach subsequent full coverage, retained-terrain assembly or world/floor/replay acceptance. At the tighter setting straight still has four components; convex now has zero crossings but retains two components; concave retains four crossings, one degenerate triangle and two components. All 29 individual bodies pass again. All four complete candidates still preserve original A; no full assembly or new visual acceptance is claimed.

The normal audit/tests/native preview build; four regression suites pass. Twelve default outcomes/hashes, four previous boundary outcomes/hashes and four previous shared-cut outcomes/hashes and byte-identical roof fixtures reproduce. Six production pins remain unchanged. The Boolean backend and new blend remain optional experiments; regular gameplay stays A.

Next: repair remaining disconnected/intersecting cores, construct explicit cap/source/target/floor constraints, and reduce the active field before extraction to meet the unchanged budget. Then verify full retained-terrain, protected-floor, neighbouring-wall and cross-room/world/replay acceptance; refine and visually accept cap lips, pointed rear facets, rear edges and finite links; broaden coverage; meet controlled construction/native p95 targets; verify interactive gameplay/occlusion across expedition floors; and integrate accepted production Old / New modes with rollback. All six goal requirements and phases 4–6 remain unfinished; changes are uncommitted and the goal remains active.

## Active-goal continuation: affine crossovers and exact disjoint-pair pruning — 2026-11-07

The [affine-envelope checkpoint](reports/cliff-formations/affine-envelope/README.md) implements an optional piecewise-affine source-to-target band with explicit max/min crossover arrangements. A shared global band preserves the ideal cold/full-target endpoints and source/target bounds. The routed realization still needs numerical, complete cap/floor and interior-envelope acceptance. It avoids interpolating a quadratic blend across skinny triangles.

The first native trial failed all four cases. Exact integer separating-axis pruning then removes height constraints only between proved disjoint convex domains; genuine overlaps and nonconvex/unproved pairs remain checked. This reduces unnecessary routing and recovers **all 29 individual constructed-prism body passes**. No acceptance guard or budget changes.

The exit core now has **6,324 triangles, down from 13,200**, with one closed component, zero native strict topology/intersection/overlap defects, and zero native buried/detached source fragments at the unchanged 0.1 mm half-space margin. The maximum nominal constructed roof slope drops from approximately 84.23 degrees to 60.90 degrees; this is not rendered-facet or visual acceptance. All 39 saved cold boundary midpoint witnesses still match within 0.2 micrometres. An independent exact clipping oracle finds no positive overlap between any emitted new roof cell and any original saved convex protected cutout in all four cases. That scope excludes cap bodies and assembled terrain; full protected-floor acceptance remains unfinished.

**The new field is not promoted.** Straight and convex introduce four and three combined crossings relative to the previous tighter vertex field's zero; concave retains four crossings, one degenerate face and two components. Independent rational checks confirm every reported crossing pair. Straight retains four components and convex two. All four complete trials preserve original A. The exit still exceeds the unchanged strict triangle budget below 2,400 and does not reach subsequent full coverage/terrain/world gates. Full assemblies accepted: zero.

An independent diagnosis of previous vertex-field islands finds both originally disconnected local source pieces and source-window-created isolation. Fifteen rational checks of saved approximate closest-gap samples show that some shortest links cross protected front-wall floor cutouts and others leave the original sampled source roof. This excludes cap membership and does not rule out alternate routes. It establishes that indiscriminate bridges or post-union deletion cannot serve as a fix; source ownership and retained context must be handled explicitly.

Four normal regression suites and optional kernel tests pass. Twelve default outcomes/hashes reproduce. All four previous tighter vertex outcomes/hashes and byte-identical chunk/core fixtures reproduce. The normal native preview builds and six production pins remain unchanged. Neither concurrent research runs nor geometric reductions establish controlled performance acceptance.

Next: repair combined Boolean/float crossings and the concave near-degenerate geometry; identify unchanged source pieces that should remain in the original backing, with explicit ownership, preserved-source and shared-closure proofs before reducing the changed domain. Meet the unchanged core budget and complete cap, retained-terrain, protected-floor, neighbouring-wall and cross-room/world/replay verification. Then finish visual acceptance of lips/facets/edges/links, broader coverage, controlled construction/native p95, interactive gameplay/occlusion across expedition floors and accepted production Old / New modes with rollback. All six goal requirements and phases 4–6 remain incomplete. Changes are uncommitted and the goal remains active.

## Active-goal continuation: source-checked short-edge cleanup — 2026-11-07

The [short-edge cleanup checkpoint](reports/cliff-formations/vertex-repair/README.md) fixes the three combined-core crossing failures and the concave degenerate face. The optional construction collapses short manifold edges to a shared float midpoint or endpoint, moving each original vertex at most once and no more than 20 micrometres. It must remove exactly two incident triangles, preserve retained-face orientation and closedness, maintain component count, improve defect counts, pass changed-face source checks, and agree with whole strict validation. Source, floor, weld and budget acceptance thresholds remain unchanged. No failed individual/column-move or repeated-round processing branches remain in the active routine.

All four native cases retain **29 individually checked constructed-prism input bodies**. Combined cores have no crossing, overlap, degenerate, open/nonmanifold, vertex-link, duplicate or winding defects, but their component counts remain **4/2/2/1**. Independent rational all-pairs checks confirm zero conflicts across **422,333 candidate pairs** in the three repaired cores. Independent edit reconstruction exactly reproduces each entire repaired mesh with one two-triangle collapse, bounded at approximately 10.80 / 0.83 / 3.81 micrometres. All 9/6/5 edited faces pass independent nominal-source half-space checks. Exact projected subtraction finds no newly covered positive area inside any saved original protected convex cutout. These checks do not establish full original-world/cap/floor or assembled-terrain acceptance.

A deeper convex source defect is now verified: **six buried-source fragment reports across five faces**, independently confirmed. Local rational witnesses place bad simplified-output face centroids inside a checked input body's solid interior. Raw Boolean output has no native source fragments but invalid topology; a 0.1-micrometre simplification trial removes the source fragments but leaves two crossings; preserving original face metadata also fails. None is an accepted alternative. The source loss is isolated to output processing, without claiming one particular internal library operation is responsible.

Repaired straight/concave/convex cores contain **12,362 / 9,044 / 12,970 triangles** and remain disconnected. Exit is unchanged at **6,324 triangles**, native closed/source-valid but still above the unchanged strict budget below 2,400. All four complete trials preserve original A. Zero full assemblies or new visual acceptances are claimed; subsequent complete cap, terrain, protected-floor/world/replay and gameplay gates remain unpassed.

The cleaned final routine exactly reproduces all four frozen repaired replay meshes; three also match native final core arrays, while exit applies its unchanged 6,336-to-6,324 core simplifier. Four normal regression suites, final negative-control assertions and optional/full-mode kernel tests pass. Twelve default outcomes/hashes reproduce. Disabling cleanup reproduces all four previous affine chunk/core fixtures byte for byte. The normal native preview builds; six production pins remain unchanged. Controlled construction/native p95 acceptance is still missing.

Next: prevent the convex output-processing source loss and repair source/retained-context connectivity. Evaluate shared cap/body intersection construction; do not bypass guards, use invalid raw output, delete isolated components or bridge protected floor. Keep unchanged source in the backing only with explicit ownership and independently checked shared closure, then meet the unchanged geometry budget and full cap/source/terrain/floor/neighbouring-wall/cross-room/world/replay gates. Residual cap lips/facets/edges/links, visual acceptance, broader coverage, controlled performance, interactive gameplay/occlusion across expedition floors and accepted production Old / New selection with rollback all remain unfinished. All six goal requirements and phases 4–6 stay incomplete; changes are uncommitted and the goal remains active.

## Active-goal continuation: source-checked Boolean output — 2026-11-07

The [source-processing checkpoint](reports/cliff-formations/source-stages/README.md) identifies the first observed convex source loss at the tolerance increase, which itself invokes library topology simplification; the next explicit simplification expands the buried reports from two to six. All staged checks inspect emitted floats. The stage-6 control exactly reproduces the previous pipeline, so this is a controlled operation-sequence diagnosis rather than an assertion about one internal algorithm.

A new opt-in processor verifies each complete emitted candidate against strict surface checks and the unchanged constructed-source contract. Failed candidates are rebuilt from the same original solids at one-quarter the requested simplification tolerance, bounded at four attempts; failure still falls back to A. Exact contacts are required, raw output cannot bypass processing, and input/backend exceptions propagate. Acceptance margins, source area policy, floor/weld guards, component requirement and budget are unchanged. All retries and required validation are included in profiling.

The completed locked native matrix retains **29 checked input bodies** and has zero native crossing/overlap/degenerate/open/nonmanifold/link/duplicate/winding defects and zero processor source fragments in all four cases. Three retain their previous output at the original 1-micrometre request. Convex rejects its invalid first output and succeeds at 0.25 micrometres. The new convex surface has zero independent rational conflicts across **188,365 pairs**; together with unchanged straight/concave surfaces, 446,814 candidate pairs are independently clear. Four selected corrected faces pass rational source checks. At two formerly failing positions, exact vertical sections restore the input body's roof, correcting a measured drop of approximately 1.11721 m. This is not a complete independent original-world source proof.

**Full assemblies accepted remain zero.** Components stay **4/2/2/1**. Straight/concave/exit stay at 12,362 / 9,044 / 6,324 triangles, while the source-correct convex grows to **15,182**. All exceed the unchanged strict core budget below 2,400 and complete candidates preserve original A hashes. Subsequent complete cap/source/terrain/floor/world/replay and gameplay gates remain unpassed. The retry path is experimental and has no controlled performance acceptance.

Four regression suites and optional/default-mode kernel tests pass, including valid-source and exhausted-retry invalid-source controls. Twelve default outcomes/hashes reproduce. All four input roof fixtures remain byte-identical; retained outputs and the separately verified convex correction reproduce exactly. The normal audit/tests/native preview build, six production pins remain unchanged, and regular gameplay stays A.

Next: repair source ownership and retained-context connectivity without deleting disconnected pieces or bridging protected floor. Preserve unchanged source in the backing only with explicit ownership and independently verified shared closure, reduce changed geometry below budget, and finish all original cap/source/terrain/floor/neighbouring-wall/cross-room/world/replay gates. Residual lips/facets/edges/links, visual acceptance, broad coverage, controlled construction/native p95 including retry costs, interactive gameplay/occlusion across expedition floors and accepted production Old / New selection with rollback remain unfinished. All six goal requirements and phases 4–6 stay incomplete; changes are uncommitted and the goal remains active.

A preliminary budget prefilter finds original-source plane matches in 2,607–4,973 body prisms per locked case, approximately 58–71% of summed projected prism area. This is an opportunity estimate only: exact original-domain coverage, upper ownership and shared closure must be proved before reusing or omitting any reconstructed source geometry. The diagnostic changes no geometry.

## Active-goal continuation: narrower retained-source band rejected — 2026-11-07

The [retained-band trial](reports/cliff-formations/retained-band/README.md) excludes artificial cap-fill baselines from the global affine contrast bound; genuine source roofs still determine cold preservation, and excluded cold cells are rejected. This experiment is optional, defaults off, removes no source geometry and changes no acceptance threshold.

The locked four-case matrix is complete. It does **not** fix connectivity: concave retains two components at 9,044 triangles, convex retains two at 14,864, and exit retains one at 6,220. Exit saves only 104 triangles and remains over the strict budget below 2,400. Straight introduces an invalid shell; an independent exact incidence witness confirms four faces sharing one vertical edge. An independent rational footprint oracle also finds a positive exit protected-cutout intersection of approximately 4.56e-11 m². The trial is rejected for promotion; all four complete candidates preserve A. No full assembly or visual acceptance is claimed.

All 39 saved cold boundary midpoint witnesses remain within 0.2 µm; this sampled result does not excuse either exact failure. Normal builds and four regression suites pass, as does the optional full-mode kernel suite. The previous source-checked mode remains the baseline; disabled-trial controls and final provenance are recorded in the trial report.

Next: repair original-source ownership and retained-context connectivity, preserve protected exclusions and vertex-link topology after final arrangement routing, and reduce changed geometry below budget. Full cap/source/terrain/floor/neighbouring-wall/world/replay gates, cap lip/facet/edge visual acceptance, broad coverage, controlled performance, interactive gameplay/occlusion across expedition floors and accepted production Old / New selection remain unfinished. All six goal requirements and phases 4–6 stay incomplete; regular gameplay remains A and changes are uncommitted.

## Active-goal continuation: exact source ownership and guarded reuse preconditions — 2026-11-07

The [source-reuse checkpoint](reports/cliff-formations/source-reuse/README.md) replaces the earlier numerical opportunity estimate with exact projected domain/owner checks across all four frozen fixtures. Of 16,618 plane matches, 1,995 fail complete original-domain coverage within the 0.1 mm vertical band or have a strictly higher original owner. Eight real rejection centroids pass direct rational inequality checks, alongside six synthetic controls. No geometry is removed or reused yet.

Exact saved-grid edge splitting identifies 309 proposed reuse/changed interfaces with nominal roof-height gaps above the existing 20 µm weld distance. A monotonic guard keeps 247 additional transition cells reconstructed, leaving 4,181 / 3,719 / 4,101 / 2,375 candidates in straight/concave/convex/exit. Their shared-edge nominal height gaps are within 20 µm. This is a necessary precheck, not original-backing weld, closed vertex-link, cap/foundation or full assembly acceptance. The original-domain band and nominal interface check do not together prove the final source seam.

Actual baseline geometry and triangle counts are unchanged; regular gameplay remains A, full assemblies accepted remain zero, and all six goal requirements remain incomplete. Next: retain original source-domain identity, generate only changed geometry plus explicit transition joins, construct both sides of each original-source cut from one shared intersection and float conversion, then pass the complete retained-world/cap/floor/connectivity/coverage/replay gates and unchanged budget. Visual lips/facets/edges, neighbouring-wall coordination, broad coverage, controlled performance, interactive gameplay/occlusion across expedition floors and accepted production Old / New modes remain unfinished.

## Active-goal continuation: runtime source-reuse construction — 2026-11-07

The [runtime reuse experiment](reports/cliff-formations/native-reuse/README.md) implements exact source-domain/owner selection, shared-edge guards, footprint point-link guards and larger emitted-height vertex-fan guards. Full roof fields remain available to existing callers; the optional formation constructor consumes the mask. Across the four locked inputs, 14,196 cells stay assigned to original backing and 7,053 remain reconstructed. Every claimed eligible input cell passes an independent rational source check, and every final mask passes its stated interface/fan prechecks. Four reconstructed roof subsets have no positive overlap with the original saved protected cutouts. These are intermediate checks, not complete assembly acceptance.

The source-preserving adapter path is implemented and analytically checked, but remains unreached by the final native fixtures through complete acceptance. Initial source filtering creates nonmanifold shells; additional transition and height-link guards recover closed source-checked cores in completed cases. Those cores still fragment and increase triangle counts: straight 14,670 / 62 components, concave 10,748 / 58 (also missing an elevated route), exit 7,038 / 19. All four final trials reject. Convex exhausts four Boolean output retries; its last candidate has 16,800 triangles, 55 components, 11 crossings and one degenerate face. The final regression/control completion state is authoritative in the linked status report. No acceptance guard or strict budget below 2,400 is relaxed, and completed candidates preserve A.

Optional kernel tests and four normal regression suites pass. Final normal audit/tests/preview binaries match the tested build byte for byte. All six goal requirements remain incomplete; production stays A. Next construction must coordinate changed geometry with retained backing before exposing/extracting their shared interfaces. Then prove full original cap/source/backing/floor/neighbour/world/replay and connectivity requirements, meet the budget, finish lip/facet/edge visuals, broad coverage, controlled performance, interactive gameplay/occlusion across expedition floors and accepted production Old / New modes.

## Active-goal continuation: coordinated source-edge simplification — 2026-11-07

The [shared-source-edge checkpoint](reports/cliff-formations/shared-source-edges/README.md) keeps the complete constructed field and simplifies both owners of a shared original-source interface together. Exact directed-edge cancellation and contour tracing replace the rejected integer-union prototype. Exterior/hole boundaries stay fixed; original source-edge proximity and switched roof heights are bounded by 20 µm. No component is deleted after extraction and acceptance guards remain unchanged.

All four final native cores pass strict surface and constructed-source checks, including convex's existing retry. Separate whole-core checks against the pre-simplification nominal source unions also pass. Independent rational field overlays check 46,085 positive overlap parts with complete bidirectional coverage and maximum roof change approximately 19.7544 µm. Independent all-pairs checks find no conflicts across 455,629 candidate pairs. Original protected roof cutouts remain clear in all four field sets; all 39 saved far boundary midpoint witnesses still match within 0.2 µm. These are not full original-world or assembled-seam acceptance.

Core triangles drop from **12,362 / 9,044 / 15,182 / 6,324 to 9,916 / 7,258 / 11,128 / 5,136**, about 22.1% overall. Components stay 4/2/2/1. **All four complete candidates still reject**, preserve A, and exceed the strict budget below 2,400. A source-checked replay at 4 µm reaches 4,234 triangles in the exit and passes its separate original-reference check; it is still over budget and is not a completed terrain/world trial. More aggressive smaller replay outputs are rejected for real source errors.

Four disabled-mode native controls preserve exact source/chunk/core geometry and outcomes/hashes. Normal builds, four regression suites and the optional full-mode kernel suite pass; final normal binaries match the tested build. The twelve-case default comparison from the previous checkpoint is resolved: it had compared automatic versus pinned attempt selection, and matching-input old/new controls agree. Audit result files now pin the manifest and effective input cases.

Next: classify primary-cliff versus changed/unchanged source components before reconstructing the coherent active domain with retained backing. Avoid independent removal of scattered unchanged cells. Reduce remaining roof/exterior complexity while preserving original source/cap/floor and shared closure, then finish full terrain/neighbour/world/replay and connectivity gates. Visual lip/facet/edge acceptance, broad coverage, controlled performance, interactive gameplay/occlusion across expedition floors and accepted production Old / New selection remain open. All six requirements and phases 4–6 remain incomplete; production stays A and changes are uncommitted.

## Active-goal continuation: detached-component provenance — 2026-11-07

The shared-source-edge report now includes exact primary interior-witness classification and checked pre-union body comparisons. In all four locked cases, interior witnesses for every primary solid, including the five main cliffs, lie uniquely inside the largest emitted component. This does not establish entire primary-volume containment or a seamless assembled plateau.

There are five detached pieces across the three disconnected cases: straight has 28 / 12 / 12 triangles, concave 70, and convex 96. Three pieces—the two 12-triangle straight pieces and the 96-triangle convex piece—match separate pre-union checked constructed bodies exactly, including oriented triangle multiplicities and coordinates. Their disconnection therefore predates final Boolean output processing. All 29 pre-union body meshes are individually edge-connected. Neither fact proves that a constructed body is unchanged original terrain or may safely be omitted.

The other two pieces have the same bounds as separate 48- and 76-triangle checked bodies. Exact bidirectional coplanar surface subtraction **rejects equivalence**: the straight comparison leaves 12 emitted / 29 input faces partly uncovered, and concave leaves 2 / 6. Bounding boxes alone are not ownership evidence. Exact clipping finds no satellite boundary patch strictly inside a nominal primary in any of the five pieces; this boundary test alone is not a full-volume disjointness proof. Eight analytic controls cover triangulation changes, orientation, missing area and interior/tangent/disjoint clipping. Geometry and production behavior are unchanged by these diagnostics.

Next: resolve the two non-equivalent source correspondences and establish original-terrain/cap ownership of all five pieces. Only then construct a coherent retained-backing domain with proved shared closure; do not delete final union components or bridge protected floor. Budget reduction, full cap/source/terrain/floor/neighbour/world/replay verification, visual lips/facets/edges, broader coverage, controlled performance, interactive gameplay/occlusion across expedition floors and accepted production Old / New modes remain unfinished. All six requirements remain incomplete, full accepted assemblies remain zero, and production remains A. A dependable completion estimate is still unavailable while the construction strategy remains unaccepted.

## Active-goal continuation: whole cap-connected construction domains — 2026-11-07

The [cap-domain checkpoint](reports/cliff-formations/cap-connected-domain/README.md) recovers **one connected core in all four locked native cases**, with zero native strict and constructed-source defects. Core triangles decrease from 9,916 / 7,258 / 11,128 / 5,136 to **9,354 / 6,958 / 9,582 / 4,622**. All four still exceed the unchanged strict budget below 2,400 and preserve original A. Full accepted native assemblies remain zero.

Exact footprint subtraction assigns the five satellite candidate input bodies to complete groups of 22 nominal cells, with no partial cells, uncovered candidate body footprint or positive-area cap overlap. Only one group passes unchanged-source coverage/upper ownership at 20 µm. Three groups are about 0.74–1.87 m above overlapping saved original roofs; another has matching height but a small uncovered footprint. The sampled source roofs are not the entire original world. These pieces must not all be labelled unchanged source. The two prior emitted/input surface equivalence checks remain rejected; the new proof concerns nominal footprint ownership.

The new default-off selector limits the proposed edit to **whole footprint components with positive-area cap contact**, before constructing any solids. It retains all cells within those components, including unchanged transition cells. Other complete components are assigned to original terrain, which the adapter preserves outside the selected construction columns. This intentionally restores original terrain in unattached regions, instead of claiming its raised proposals were unchanged. No extracted union component is deleted. Exit retains two cap-connected input regions; selection is not a largest-component shortcut.

An independent exact grid-edge sweep and rational cap clipping reproduce all four input selections. Actual output cells exactly match the selected inputs; 282 of 11,071 proposed cells are assigned to original backing. Primary/detail planes and selected body planes remain identical to their previous inputs. Independent rational all-pairs audits find zero conflicts across **418,806 candidate pairs** on the final cores. Native final whole-core constructed-source checks also pass. These are not complete original-world or assembled-join proofs.

The real adapter passes a synthetic assembled control preserving adjacent original roof height at 3 m, replacement height at 4 m, protected floor and physical heights. Full native adapter/shared-closure validation remains unreached because of the earlier budget rejection. Four normal regression suites, final optional kernel tests, normal audit/tests/native preview builds and four byte-identical disabled-mode controls pass. Six production pins remain unchanged. Controlled performance acceptance is still missing.

Next: reduce remaining roof/exterior complexity below budget while preserving cap controls, cold terrain and protected exclusions. Then complete full native retained-original/shared-closure, cap/source/terrain/floor/neighbouring-wall/world/replay acceptance. Residual cap lips/facets/rear edges and visual acceptance, broader coverage, controlled performance, interactive gameplay/occlusion across connected rooms and expedition floors, and accepted production Old / New selection with rollback remain unfinished. All six requirements and phases 4–6 stay incomplete; production remains A and changes are uncommitted.

## Current delivery checkpoint — canyon join remains unfinished

The [source-restoration report](reports/cliff-formations/source-restore/README.md) records the first native exit core below budget: **2,134 triangles**, with complete core source/topology checks, 640 union rays, 72,128 top-coverage rays, 182 cap samples, 5,637 seam rays and 26,215 floor tests passing. Restoring three unchanged original source solids repairs the source loss introduced by coarse processing. Independent rational checks confirm zero conflicts across 21,648 pairs on the actual native mesh.

**This is not a delivered canyon feature.** The complete candidate still rejects at the retained-terrain join. Full accepted assemblies remain zero; no New production mode or accepted interactive New wall is available. The time spent on local experiments has not produced the required end-to-end result.

The crop now uses the actual checked replacement mesh's shadow, and complete canonical source ownership reuses original source borders. This corrects a verified mismatch between the earlier prism shadow and the rendered mesh. Controls preserve real holes and independent ownership audits pass. The native join still encounters an unrepresentable retained fragment. Fixed crop padding and bounded fragment-drop experiments did not solve it and their runtime paths are removed. Final acceptance thresholds remain unchanged.

The next work must build retained terrain and replacement through **one common cut-vertex interface**, with a frozen adapter fixture to avoid regenerating the whole floor for each edit. Verify a complete wall in the interactive renderer before broadening coverage. A passing component check is not delivery acceptance.

Other open work remains: the early-target convex roof crossing, straight/concave core budgets, cap lips/facets/rear edges and visual review, complete neighbouring-wall/world/replay checks, controlled construction/rendering performance, gameplay/occlusion across connected rooms and expedition floors, and accepted production Old / New modes. A source-valid 2,366-triangle baseline control fails a native inverse ray by about 4.2 cm and remains rejected. All six requirements and phases 4–6 remain incomplete; production stays A.

Separately, the requested [asset browser](asset_browser.md) is implemented as its own C++ executable and launched. Its inventory matches all 4,156 asset files; model/image/font/audio-waveform/text/metadata/binary previews are verified. This separate deliverable does not establish canyon completion.


## Shared-construction checkpoint — full native join still rejected

The [joint terrain join report](reports/cliff-formations/joint-terrain-join/README.md) captures the original adapter operands before cropping: 1,972 original cap prisms and the actual 2,134-triangle checked exit core. A standalone C++ replay now tests this join without regenerating the floor. The default-off implementation subtracts the replacement silhouette from the original cap solid, unions the actual replacement, then converts the combined result to float; it rejects any strict emitted-mesh defect.

Small overlap/shared-border/one-float-sliver controls pass. The optional kernel adapter control preserves old roof height, replacement height, original floor and physical heights. Four normal regression suites also pass. **The full native fixture still fails**: direct float conversion reports 14,758 defects; global 8 micrometre simplification and float reimport still reports 1,259. These rejected trials do not establish a seamless wall or source fidelity. The first shadow built from separate triangle columns was stopped for excessive construction cost; the silhouette replay completes quickly enough to iterate directly.

Next: resolve the frozen full-wall render-precision topology, keeping the final strict guard. Then run complete adapter/source/floor checks and inspect an actual rendered wall. All earlier visual, broader coverage, performance, gameplay/occlusion and production Old/New acceptance items remain unfinished. Production remains A; full accepted native assemblies remain zero.


## Work stopped at the user’s request

Status: **paused; incomplete**. Further canyon work was cancelled. No complete native join was accepted and no production New mode is available. The rectangular and whole-source integration trials both preserve original A through fallback. Fresh optional builds/kernel tests pass, and the binary silhouette projection passes 10,138 independent integer witnesses; these checks do not establish a seamless assembled wall.

The [last checkpoint](reports/cliff-formations/joint-stage-diagnosis/status.json) preserves the full adapter fixtures, failed native/replay results and original/rejected-candidate GLB inspection models. All six goal requirements remain unfinished. The experimental Boolean CMake option was restored to OFF; source files and reports remain uncommitted. The separate asset browser remains a completed, independently buildable deliverable.
