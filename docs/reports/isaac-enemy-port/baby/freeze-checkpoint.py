#!/usr/bin/env python3
"""Freeze the Baby evidence once; --check verifies its immutable snapshot."""
import argparse
from collections import Counter
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[4]
BASE = Path(__file__).resolve().parent
PREVIOUS = BASE.parent / 'mr-maw/checkpoint.json'
CHECKPOINT = BASE / 'checkpoint.json'


def read(path):
    return json.loads(path.read_text())


def digest(path):
    h = hashlib.sha256()
    with path.open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            h.update(block)
    return h.hexdigest()


def hashes(paths):
    return {str(p.relative_to(ROOT)): digest(p) for p in sorted(set(paths))}


def verify(mapping):
    for name, expected in mapping.items():
        assert digest(ROOT / name) == expected, name
    return len(mapping)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    if args.check:
        frozen = read(CHECKPOINT)
        counts = {key: verify(frozen[key]) for key in
                  ('runtime_sha256', 'build_sha256', 'source_sha256', 'artifacts_sha256')}
        assert digest(PREVIOUS) == frozen['previous_checkpoint_sha256']
        assert frozen['checklist']['complete'] == 0
        assert frozen['native']['passed'] == frozen['native']['registered'] == 89
        assert frozen['browser']['final_build_passed'] == 11
        print(json.dumps({'result': 'pass', 'verified_files': counts}))
        return

    assert not CHECKPOINT.exists(), 'Refusing to overwrite frozen evidence'
    previous = read(PREVIOUS)
    preserved = verify(previous['artifacts_sha256'])
    preserved_source = verify(previous['source_sha256'])
    checklist = read(ROOT / 'docs/research/isaac-enemy-port-validation.json')
    assert checklist == read(BASE / 'checklist-final.json')
    assert checklist['reviewed'] == 187 and checklist['implementations']['in_progress'] == 140
    native = read(BASE / 'native-summary.json')
    browser = read(BASE / 'browser-summary.json')
    visual = read(BASE / 'visual-review.json')
    outcomes = Counter(x['result'] for x in visual['inspected'])
    pools = read(BASE / 'pool-counts.json')
    assert len(pools['direct_ids']) == 85 and len(pools['enabled_ids_including_replacements']) == 89
    assert len(visual['inspected']) == 26
    assert browser['final_build_passed'] == 11 and not browser['headless']
    assert 'fingerprint c0d4e092a3ac08b4' in (BASE / 'config-final.txt').read_text()
    assert not read(BASE / 'implementation-progress.json')['live_jobs']

    runtime = {ROOT / name for name in previous['runtime_sha256']}
    runtime.update(ROOT / name for name in (
        'src/combat/Babies.cpp', 'assets/mechanics/babies.mechanics',
        'tests/baby_tests.cpp', 'web/baby-test.cjs', 'scripts/isaac-reference/analyze-vis.py'))
    build = {ROOT / name for name in previous['build_sha256']}
    build.add(ROOT / 'build/deathward_baby_tests')
    source = {ROOT / name for name in previous['source_sha256']}
    artifacts = set()
    for family in (BASE, BASE.parent / 'vis'):
        artifacts.update(p for p in family.rglob('*') if p.is_file())
        for folder in ('source', 'animations'):
            source.update(p for p in (family / folder).rglob('*') if p.is_file())

    data = {
        'status': 'Baby implementation checkpoint; Vis source review prepared. Full653-record goal active, regular enemies first. No complete six-gate ports.',
        'created_utc': datetime.now(timezone.utc).isoformat(),
        'mechanics_fingerprint': 'c0d4e092a3ac08b4',
        'runtime_definitions': 179, 'item_definitions': 13, 'enemy_bomb_profiles': 6,
        'checklist': checklist, 'regular_enemy_implementations_in_progress': 98,
        'direct_pool_ids': 85, 'enabled_pool_ids_including_replacements': 89,
        'pool_scope': pools['scope'], 'native': native, 'browser': browser,
        'visual': {'inspected': len(visual['inspected']), **outcomes, 'full_gate': False},
        'remaining': read(BASE / 'implementation-progress.json')['pending'],
        'previous_checkpoint': str(PREVIOUS.relative_to(ROOT)),
        'previous_checkpoint_sha256': digest(PREVIOUS),
        'previous_checkpoint_artifacts_verified_unchanged': preserved,
        'previous_checkpoint_sources_verified_unchanged': preserved_source,
        'installed_executable_sha256': previous['installed_executable_sha256'],
        'installed_executable_hash_scope': 'Rehashed by Vis export/check and supplementary Baby target-eligibility extraction.',
        'runtime_sha256': hashes(runtime), 'build_sha256': hashes(build),
        'source_sha256': hashes(source), 'artifacts_sha256': hashes(artifacts),
    }
    CHECKPOINT.write_text(json.dumps(data, indent=2, ensure_ascii=False) + '\n')
    print(json.dumps({'result': 'frozen', 'path': str(CHECKPOINT.relative_to(ROOT)),
                      'previous_artifacts_preserved': preserved, 'previous_sources_preserved': preserved_source}))


if __name__ == '__main__':
    main()
