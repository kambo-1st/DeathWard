# Canyon prototype postmortem

Status: stopped at the user's request, incomplete. This is an account of failed delivery, not a claim that the work is nearly finished.

## What was requested and what was delivered

The requested result was the approved low-poly rock formations forming a continuous elevated plateau, followed by detail/vegetation, reliable seeded placement, neighbouring terrain joins, performance and gameplay/occlusion acceptance, and production Old/New selection.

An earlier authored-wall prototype is runnable and interactive. Component geometry checks, several small assembled controls and some scenery checks pass. The separate C++ asset browser is also usable. The complete generalized canyon join was not delivered: the latest full native cases still reject and preserve A through fallback. No production New mode was accepted. Cap/facet visual review, broader coverage, performance and gameplay/occlusion acceptance remain incomplete.

The goal tracker last inspected recorded 4,275,262 tokens and 78,027 seconds (about 21.7 hours). These are tracker totals, not proof of equivalent productive development time. The amount of effort did not justify the delivered canyon result.

## How I worked

I extended the isolated C++ formation experiment, generated seeded cases, and repeatedly used geometry probes and audits to investigate failures. The work accumulated source-plane reconstruction, cap-domain selection, snap rounding, Boolean union, source restoration, terrain cropping and welding experiments. I checked topology, source coverage, cap heights, floor preservation and repeatability, and kept the production path on A when candidates failed.

I often compiled changed files and linked them against previously built experiment objects to shorten iteration. Late in the work I added frozen join/adapter inputs, standalone replay, a fresh build of the active optional targets, independent projection witnesses and an interactive original/rejected-model comparison.

## Why delivery failed

1. **I did not establish an end-to-end integration method early.** I refined components before proving that a complete cliff, plateau, neighbouring terrain and floor could be constructed and rendered together. The user had explicitly identified this dependency.
2. **I used the wrong abstractions without validating them first.** Reconstructing old rendered terrain as downward prisms from upward faces is not automatically equivalent to its visible surface. Cropping against a projected footprint and joining independently rounded pieces creates additional interface problems. A good isolated solid did not prove a good terrain join.
3. **I treated measurements as progress toward acceptance too readily.** Closed component meshes, ray samples and source checks were useful diagnostics. They did not establish a seamless complete wall. Some earlier assurances were broader than the evidence justified.
4. **I kept iterating on symptoms.** Many numerical and ownership variants were tried while the construction strategy itself remained unaccepted. Some were subsequently removed. I should have set a short evaluation limit and replaced the approach much sooner when full-wall acceptance stayed at zero.
5. **I introduced avoidable projection errors.** The first joint Boolean trial extruded raw `Project()` contours even though the library documents that they can self-intersect. Positive-fill normalization corrected that. Decimal clipping also perturbed binary-float border coordinates; a later binary-scaled normalization preserved the input coordinates. These corrections did not solve the full join.
6. **I scoped the audits poorly at first.** The old selected rendered surface already has open boundaries and intersection/vertex-link defects in the captured baseline. Reconstructed closed operands also include buried foundations and artificial edit curtains. I did not distinguish inherited source defects, newly introduced visible defects and intentionally hidden geometry early enough. This does not excuse new gaps or justify accepting the failed candidate.
7. **My iteration setup became difficult to trust and review.** Private object-file combinations and many flags made provenance harder to follow. A clean optional build was eventually completed, but the frozen full-adapter replay and faithful capture of geometry-affecting flags should have existed at the beginning. The reports grew to about 4.2 GB without a corresponding accepted feature.
8. **I communicated too optimistically and continued too long.** I should have led with zero accepted complete assemblies, shown the current rendered failure sooner, and been explicit that the integration strategy was failing. Repeated plans and component statistics were not a substitute for the requested result.

These were failures in my engineering process and judgment. There is no demonstrated fundamental obstacle to making a seamless plateau/cliff connection, and the user's manually constructed result is evidence against that explanation. The evidence does not establish one final root cause that, once fixed, will complete this implementation.

## Evidence at the stop point

- The earlier authored demo launches with ordinary gameplay input enabled. Its launch log records assembled geometry/scenery replay checks passing for that selected scene. This is narrower than general integration acceptance.
- The checked exit core reached 2,134 triangles and passed its component checks. Its full native integration still falls back.
- Normalizing the captured silhouette reduces 39 raw contours to three filled-domain boundaries. An independent integer-predicate audit passes 10,138 projection witnesses, with boundary rounding bounded below two picometres. This proves only those projection witnesses.
- Fresh optional replay/audit/test targets build and the optional kernel suite passes. Full rectangular and whole-source integration trials still fail their unchanged visible-assembly gates.
- The captured original selected surface has 65 intersection pairs and 13 invalid vertex links; adding nearby context gives 111 intersection pairs and 73 invalid links. Its open boundaries are also recorded. These are scoped baseline diagnostics, not blanket acceptance exceptions.
- The original/rejected-candidate GLBs are explicitly labelled inspection artifacts. They are not production game assets.

See `docs/reports/cliff-formations/joint-stage-diagnosis/`, `docs/reports/cliff-formations/source-restore/`, the persisted goal status and the historical implementation plan for raw evidence. Earlier dated claims in the historical plan must be read with their stated scope and later corrections.

## If this is resumed

Start from the archived working authored demo and the full frozen adapter fixture. Reproduce the failure with a fresh build, define the exact ownership of the shared visible border, and measure the source baseline before changing geometry. Establish one complete rendered join before additional polish or optimization. Preserve the approved artistic direction and protected gameplay floor; do not conceal failures by weakening final acceptance.

Keep component verification, visible join acceptance and production readiness separate. Set a short evaluation checkpoint for any replacement construction method. Broaden seeded coverage and performance/gameplay checks only after the complete wall works. This is a proposed restart discipline, not an implementation or a completion estimate.
