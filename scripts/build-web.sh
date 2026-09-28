#!/usr/bin/env bash
set -euo pipefail
deathward_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
if ! command -v emcmake >/dev/null; then
    if [[ -n "${EMSDK:-}" && -f "$EMSDK/emsdk_env.sh" ]]; then
        source "$EMSDK/emsdk_env.sh"
    else
        echo "Activate Emscripten first: source /path/to/emsdk/emsdk_env.sh" >&2
        exit 1
    fi
fi
emcmake cmake -S "$deathward_root" -B "$deathward_root/build-web" -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=OFF "$@"
cmake --build "$deathward_root/build-web" --parallel "${DEATHWARD_BUILD_JOBS:-4}"
python3 - "$deathward_root/build-web" <<'PY'
import gzip, pathlib, sys
root = pathlib.Path(sys.argv[1])
for name in ['index.wasm', 'index.js', 'index.data']:
    file = root / name
    file.with_suffix(file.suffix + '.gz').write_bytes(gzip.compress(file.read_bytes(), compresslevel=6, mtime=0))
print('Browser build ready. Run: python3 scripts/serve-web.py')
PY
