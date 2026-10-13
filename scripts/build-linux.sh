#!/usr/bin/env bash
set -euo pipefail
deathward_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
deathward_build_dir="$deathward_root/build"
deathward_config=Release
deathward_jobs="${DEATHWARD_BUILD_JOBS:-4}"

usage() {
    cat <<'USAGE'
Usage: scripts/build-linux.sh [options]

Build the native Linux game and stage its runtime assets without launching it.
Works on Linux and WSL2. Requires CMake 3.20+, a C++20 compiler, and the
OpenGL/X11 development libraries listed in README.md. The first build downloads
the pinned raylib source; later builds reuse the CMake cache.

Options:
  --build-dir DIR   Build directory (default: build, relative to the repository)
  --config TYPE     Release, Debug, RelWithDebInfo, or MinSizeRel (default: Release)
  --jobs N          Parallel build jobs (default: DEATHWARD_BUILD_JOBS or 4)
  -h, --help        Show this help
USAGE
}

die() { printf 'Error: %s\n' "$*" >&2; exit 1; }

while (($#)); do
    case "$1" in
        --build-dir|--config|--jobs)
            [[ $# -ge 2 && -n "$2" && "$2" != --* ]] || die "$1 needs a value."
            case "$1" in
                --build-dir) deathward_build_dir="$2" ;;
                --config) deathward_config="$2" ;;
                --jobs) deathward_jobs="$2" ;;
            esac
            shift 2
            ;;
        -h|--help) usage; exit 0 ;;
        *) die "Unknown option: $1. Use --help for usage." ;;
    esac
done

[[ $(uname -s) == Linux ]] || die "Use this script on Linux or WSL2. For Windows, use scripts/build-windows.sh."
command -v cmake >/dev/null || die "CMake is missing. Install the Linux build dependencies listed in README.md."
[[ "$deathward_jobs" =~ ^[1-9][0-9]*$ ]] || die "Build jobs must be a positive integer."
case "$deathward_config" in
    Release|Debug|RelWithDebInfo|MinSizeRel) ;;
    *) die "Unknown build configuration: $deathward_config." ;;
esac
if [[ "$deathward_build_dir" != /* ]]; then
    deathward_build_dir="$deathward_root/$deathward_build_dir"
fi

cmake -S "$deathward_root" -B "$deathward_build_dir" -DCMAKE_BUILD_TYPE="$deathward_config"
cmake --build "$deathward_build_dir" --config "$deathward_config" \
    --target deathward --parallel "$deathward_jobs"

# Multi-configuration generators put the executable in a configuration folder.
deathward_runtime="$deathward_build_dir"
if grep -q '^CMAKE_CONFIGURATION_TYPES:' "$deathward_build_dir/CMakeCache.txt"; then
    deathward_runtime="$deathward_build_dir/$deathward_config"
fi
printf '\nLinux build ready: %s/deathward\n' "$deathward_runtime"
printf 'Runtime assets: %s/assets\n' "$deathward_runtime"
