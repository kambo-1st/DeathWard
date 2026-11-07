# Archived canyon prototype

The canyon work is paused and incomplete. The runnable authored-wall demo is preserved separately from the latest rejected generalized integration.

Local artifact: `artifacts/canyon-prototype-2026-11-07/`. The accompanying `.tar.zst` archive and SHA-256 checksum preserve the runtime, frozen source/assets/dependency sources, reports, build/launch instructions and known limitations. The artifact directory is ignored by Git; this document, the postmortem and the [committed archive metadata](artifacts/canyon-prototype-2026-11-07/README.md) provide its repository index. The large package and full historical report data remain local and must be retained separately.

Read [the postmortem](canyon_prototype_postmortem.md) for how the work was performed, why delivery failed, the verification scope and the remaining work. The historical [implementation plan](canyon_rock_formations_plan.md) is retained as evidence, not as a declaration of readiness.

After extracting the artifact, read its `README.md`. `./run.sh` starts the interactive authored-wall demo; `./run.sh --check` runs a finite launch check. `./rebuild.sh` rebuilds the packaged Linux executable from the included source snapshot. The exact earlier checkout-bound executable is also retained under `evidence/original-working-demo/`.

Remaining: a seamless accepted generalized terrain join, residual cap/facet visual acceptance, broader neighbouring-wall/world coverage, controlled performance, gameplay/occlusion acceptance and production Old/New modes. Full accepted native generalized assemblies remain zero. Archiving does not resume development.
