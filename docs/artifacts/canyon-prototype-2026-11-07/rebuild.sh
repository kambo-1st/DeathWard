#!/bin/sh
set -eu
artifact_root=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
cmake -S "$artifact_root/source" -B "$artifact_root/rebuild" \
  -DCMAKE_BUILD_TYPE=Release \
  -DDEATHWARD_PACKAGED_ASSETS=ON \
  -DDEATHWARD_CLIFF_REGION_EXPERIMENT=ON \
  -DDEATHWARD_CLIFF_BOOLEAN_EXPERIMENT=OFF \
  -DFETCHCONTENT_SOURCE_DIR_RAYLIB="$artifact_root/dependency-sources/raylib" \
  -DFETCHCONTENT_SOURCE_DIR_MANIFOLD="$artifact_root/dependency-sources/manifold" \
  -DFETCHCONTENT_SOURCE_DIR_CLIPPER2="$artifact_root/dependency-sources/clipper2"
cmake --build "$artifact_root/rebuild" --target deathward_cliff_alternatives \
  -j "${DEATHWARD_ARCHIVE_JOBS:-2}"
cp "$artifact_root/rebuild/deathward_cliff_alternatives" "$artifact_root/runtime/deathward_cliff_alternatives"
