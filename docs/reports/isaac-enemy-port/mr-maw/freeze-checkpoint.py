#!/usr/bin/env python3
"""Freeze this implementation checkpoint once; --check verifies recorded hashes."""
import argparse
from collections import Counter
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
BASE = Path(__file__).resolve().parent
CHECKPOINT = BASE / 'checkpoint.json'
PREVIOUS = ROOT / 'docs/reports/isaac-enemy-port/brain/checkpoint.json'


def digest(path):
    result = hashlib.sha256()
    with path.open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            result.update(block)
    return result.hexdigest()


def read(path):
    return json.loads(path.read_text())


def hashes(paths):
    return {str(path.relative_to(ROOT)): digest(path) for path in sorted(set(paths))}


def verify(data, key):
    for name, expected in data[key].items():
        assert digest(ROOT / name) == expected, f'Changed {key}: {name}'
    return len(data[key])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    if args.check:
        frozen = read(CHECKPOINT)
        counts = {key: verify(frozen, key) for key in
                  ('runtime_sha256', 'build_sha256', 'source_sha256', 'artifacts_sha256')}
        assert digest(PREVIOUS) == frozen['previous_checkpoint_sha256']
        assert frozen['checklist']['complete'] == 0
        assert frozen['native']['passed'] == frozen['native']['registered'] == 88
        assert frozen['browser']['passed'] == 16
        assert frozen['visual']['inspected'] == 25
        print(json.dumps({'result': 'pass', 'verified_files': counts}))
        return

    assert not CHECKPOINT.exists(), 'Refusing to replace a frozen checkpoint'
    previous = read(PREVIOUS)
    preserved = verify(previous, 'artifacts_sha256')
    preserved_source = verify(previous, 'source_sha256')
    checklist = read(ROOT / 'docs/research/isaac-enemy-port-validation.json')
    assert checklist == read(BASE / 'checklist-final.json')
    native = read(BASE / 'native-summary.json')
    browser = read(BASE / 'browser-summary.json')
    visual = read(BASE / 'visual-review.json')
    outcomes = Counter(row['result'] for row in visual['inspected'])
    pools = read(BASE / 'pool-counts.json')
    status = read(ROOT / 'docs/research/isaac-enemy-port-status.json')
    assert status['checkpoint']['mechanics_fingerprint'] == '9dabb84db4838840'
    assert 'fingerprint 9dabb84db4838840' in (BASE / 'config-final.txt').read_text()
    runtime_paths = {ROOT / name for name in previous['runtime_sha256']}
    runtime_paths.update(ROOT / name for name in (
        'src/combat/LinkedHeads.cpp', 'assets/mechanics/linked_heads.mechanics',
        'tests/linked_head_tests.cpp', 'scripts/isaac-reference/analyze-mr-maw.py',
        'scripts/isaac-reference/analyze-baby.py', 'web/linked-head-test.cjs',
        'web/linked-head-resident-test.cjs'))
    build_paths = {ROOT / name for name in previous['build_sha256']}
    build_paths.add(ROOT / 'build/deathward_linked_head_tests')
    source_paths = {ROOT / name for name in previous['source_sha256']}
    for family in (BASE, BASE.parent / 'baby'):
        for directory in ('source', 'animations'):
            source_paths.update(p for p in (family / directory).rglob('*') if p.is_file())
    artifact_paths = {p for p in BASE.rglob('*') if p.is_file()}
    # Baby source work is preserved as preparation, not counted as an implementation.
    artifact_paths.update(p for p in (BASE.parent / 'baby').rglob('*') if p.is_file())
    frozen = {
        'status': 'Mr. Maw implementation checkpoint. Full 653-record goal active; regular enemies first. No complete six-gate ports claimed.',
        'created_utc': datetime.now(timezone.utc).isoformat(),
        'mechanics_fingerprint': '9dabb84db4838840',
        'runtime_definitions': 179, 'item_definitions': 13, 'enemy_bomb_profiles': 6,
        'checklist': checklist,
        'regular_enemy_implementations_in_progress': 95,
        'direct_pool_ids': len(pools['direct_ids']),
        'enabled_pool_ids_including_replacements': len(pools['enabled_ids_including_replacements']),
        'pool_scope': pools['scope'],
        'native': native,
        'browser': browser,
        'visual': {'inspected': len(visual['inspected']), **outcomes, 'full_gate': False},
        'remaining': read(BASE / 'progress.json')['pending'],
        'previous_checkpoint': str(PREVIOUS.relative_to(ROOT)),
        'previous_checkpoint_sha256': digest(PREVIOUS),
        'previous_checkpoint_artifacts_verified_unchanged': preserved,
        'previous_checkpoint_sources_verified_unchanged': preserved_source,
        'installed_executable_sha256': previous['installed_executable_sha256'],
        'installed_executable_hash_scope': 'Pinned by retained source exports; no new executable rehash during metadata freeze.',
        'runtime_sha256': hashes(runtime_paths),
        'build_sha256': hashes(build_paths),
        'source_sha256': hashes(source_paths),
        'artifacts_sha256': hashes(artifact_paths),
    }
    assert frozen['direct_pool_ids'] == 82 and frozen['enabled_pool_ids_including_replacements'] == 86
    assert outcomes == {'accepted_smoke': 17, 'limited': 8}
    CHECKPOINT.write_text(json.dumps(frozen, indent=2, ensure_ascii=False) + '\n')
    print(json.dumps({'result': 'frozen', 'path': str(CHECKPOINT.relative_to(ROOT)),
                      'previous_artifacts_preserved': preserved, 'previous_sources_preserved': preserved_source}))


if __name__ == '__main__':
    main()
