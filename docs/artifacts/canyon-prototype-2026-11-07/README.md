# Canyon prototype preservation record

The local package is `artifacts/canyon-prototype-2026-11-07.tar.zst` (1,293,249,421 bytes). It is excluded from Git. Retain that package separately: this commit preserves the code and archive metadata, not the large binary package or full historical report data.

The package contains the portable Linux demo, original working executable, frozen source/assets/dependency sources, all canyon reports and postmortem. Its 11,500 regular files were checked against the archived checksums. The packaged and relocated launch checks passed; file tracing found no access to the original checkout assets.

`run.sh`, `launch.py` and `rebuild.sh` here are reference copies of the package-root scripts; run them from the extracted package, where its runtime, assets and dependency sources are present.

See [the archive guide](../../canyon_prototype_archive.md) and [the postmortem](../../canyon_prototype_postmortem.md). Historical raw diagnostic files referenced by the implementation plan are preserved in the package rather than committed in bulk.

Work remains paused. The authored scene is inspectable; the generalized seamless join, final visual/performance/gameplay acceptance and production Old/New modes remain unfinished.
