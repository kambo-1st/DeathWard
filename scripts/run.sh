#!/usr/bin/env bash
set -euo pipefail
deathward_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
cmake -S "$deathward_root" -B "$deathward_root/build" -DCMAKE_BUILD_TYPE=Release
cmake --build "$deathward_root/build" --parallel "${DEATHWARD_BUILD_JOBS:-4}"
exec "$deathward_root/build/deathward" "$@"
