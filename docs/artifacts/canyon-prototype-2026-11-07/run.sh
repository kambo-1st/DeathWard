#!/bin/sh
set -eu
artifact_root=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
exec python3 "$artifact_root/launch.py" "$@"
