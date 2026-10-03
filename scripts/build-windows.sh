#!/usr/bin/env bash
set -euo pipefail
deathward_root="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
if ! command -v powershell.exe >/dev/null || ! command -v wslpath >/dev/null; then
    echo 'Run this script in WSL with Windows interop enabled, or run scripts/build-windows.ps1 in Windows PowerShell.' >&2
    exit 1
fi
exec powershell.exe -NoProfile -NonInteractive -ExecutionPolicy Bypass \
    -File "$(wslpath -w "$deathward_root/scripts/build-windows.ps1")" "$@"
