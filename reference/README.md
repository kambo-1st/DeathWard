# Preserved Isaac research files

The expanded [mechanics reference](../docs/reports/isaac-mechanics-reference-2026-10-25.html)
adds a searchable catalog, detailed behavior/effect dossiers, item interaction
index and implementation plan. Its [JSON dataset](../docs/research/isaac-mechanics-reference.json)
and [CSV review queue](../docs/research/isaac-implementation-backlog.csv) are
versionable. It is research for the next implementation step, not a claim that
all mechanics have been ported.

New revision-pinned wiki API responses, SHA-256 provenance sidecars, EID naming
sources and a pinned REPENTOGON source snapshot are preserved in
`reference/isaac-mechanics-study/`. That directory is gitignored and must be
included separately in backups. The original game installation is unchanged.
The public source snapshot is mod/API code, not the complete original Isaac
source. Current wiki/Repentance+ statements remain distinguished from the local
Repentance 1.7.9b numeric baseline.

To rebuild the expanded report from the preserved inputs:

```sh
python3 -m venv reference/isaac-mechanics-study/venv
reference/isaac-mechanics-study/venv/bin/pip install -r scripts/isaac-reference/requirements.txt
reference/isaac-mechanics-study/venv/bin/python scripts/isaac-reference/compile.py
reference/isaac-mechanics-study/venv/bin/python scripts/isaac-reference/enrich.py
reference/isaac-mechanics-study/venv/bin/python scripts/isaac-reference/build.py
reference/isaac-mechanics-study/venv/bin/python scripts/isaac-reference/validate.py
```

The collector and inventory builder are in `scripts/isaac-reference/`. Existing
cached responses remain pinned; the rebuild above does not need network access
once the Python dependency is installed. The generated validation records check
data joins and hashes, not empirical gameplay parity.

The [expedition study](../docs/isaac_expedition_study.md) and its
[offline HTML edition](../docs/reports/isaac-expedition-study-2026-10-24.html)
are the lasting report. The local source data used by that study is preserved at:

```text
reference/isaac-repentance-1.7.9b/
```

Saved on 2026-10-24: **181 extracted files plus 12 supporting files**, totaling
**37,812,076 bytes** before the inventory. All 193 payload files were copied
without modification and checked against their source SHA-256 hashes.

## Directory contents

| Location under the reference directory | Contents |
| --- | --- |
| `extracted/repentance/resources-dlc3/` | Latest analyzed layer: items, item metadata, item pools, stage definitions, boss pools, entity definitions and binary room libraries |
| `extracted/afterbirthp/resources/` | Earlier Afterbirth+ layer, retained separately for comparisons |
| `extracted/afterbirth/resources/` | Earlier Afterbirth layer, retained separately for comparisons |
| `loose/resources/scripts/` | Installed `enums.lua` and `main.lua` support files |
| `native-analysis/` | Three targeted disassembly captures, string cross-references, PE headers and executable strings |
| `manifests/` | Original installation fingerprints and the 181-file extraction manifest with lengths, archive checksums and SHA-256 hashes |
| `method/` | Exact original extraction-script snapshot and the shipped extractor's filename list |
| `inventory.json` | Relative path, byte length and SHA-256 for every preserved payload file |

The original extraction script is an archival snapshot with the original
machine-specific paths. It is not a general extractor CLI. No extraction is
needed to use these preserved files. The disassembly captures include adjacent
instructions or partial functions; the report identifies what was actually
reconstructed. They are not the complete game source.

## Repeat the analysis

Run from the DeathWard repository root:

```sh
python3 scripts/analyze-isaac-data.py \
  --resources reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3 \
  --output /tmp/isaac-local-data-summary.json

cmp docs/research/isaac-local-data-summary.json /tmp/isaac-local-data-summary.json
```

The analyzer only reads the preserved inputs. Its in-memory correction for the
malformed closing tag in `bosspools.xml` leaves the original file intact.

## Verify the preserved files

This standard-library check reads the payload and writes nothing:

```sh
python3 - <<'PY'
from pathlib import Path
import hashlib
import json

root = Path('reference/isaac-repentance-1.7.9b')
inventory = json.loads((root / 'inventory.json').read_text())
for entry in inventory['files']:
    data = (root / entry['path']).read_bytes()
    if len(data) != entry['bytes'] or hashlib.sha256(data).hexdigest() != entry['sha256']:
        raise SystemExit('Integrity mismatch: ' + entry['path'])
print('Verified', len(inventory['files']), 'preserved files')
PY
```

## Storage and moving the study

This is a normal project directory, independent of `/tmp`, `build/`, `dist/`
and the installed game's directory. It survives normal WSL restarts and build
cleanup. Its contents are local research inputs: `.gitignore` excludes
`reference/isaac-repentance-1.7.9b/`, and the game does not load or package them.
Copy this entire directory separately when backing up the study or moving it
to another checkout; a Git clone alone contains the report and aggregate
evidence, not the extracted game files.
