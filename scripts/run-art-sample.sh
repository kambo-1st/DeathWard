#!/usr/bin/env bash
set -euo pipefail
deathward_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
if [[ "${1:-}" == --help ]]; then
    printf '%s\n' 'Usage: scripts/run-art-sample.sh [--capture]' \
        'Separate art study; the normal game and its saves are untouched.' \
        '1 Original | 2 Shapes | 3 Paint | 4 Combined | Tab Before/after' \
        'Drag to orbit | Wheel to zoom | H Hero | R Reset | Space Animate | W Walk | Esc Exit' \
        '--capture writes comparison images and checks restoration in artifacts/art-sample/.'
    exit 0
fi
cmake -S "$deathward_root" -B "$deathward_root/build" -DDEATHWARD_ART_SAMPLE=ON
cmake --build "$deathward_root/build" --target deathward_art_sample --parallel "${DEATHWARD_BUILD_JOBS:-4}"
cd "$deathward_root"
exec "$deathward_root/build/deathward_art_sample" "$@"
