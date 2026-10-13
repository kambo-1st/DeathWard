#!/usr/bin/env bash
set -euo pipefail
deathward_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
"$deathward_root/scripts/build-linux.sh"
deathward_runtime="$deathward_root/build"
if grep -q '^CMAKE_CONFIGURATION_TYPES:' "$deathward_runtime/CMakeCache.txt"; then
    deathward_runtime="$deathward_runtime/Release"
fi
exec "$deathward_runtime/deathward" "$@"
