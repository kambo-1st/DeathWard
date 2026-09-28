"""Run independent Blender conversions and publish one complete manifest."""
import argparse
import concurrent.futures
import json
from pathlib import Path
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--blender', default='blender')
    p.add_argument('--output', type=Path, default=ROOT / 'assets/animals')
    p.add_argument('--jobs', type=int, default=3)
    args = p.parse_args()
    count = max(1, min(args.jobs, 4))
    output = args.output.resolve()
    logs = ROOT / 'artifacts'
    logs.mkdir(exist_ok=True)

    def worker(index):
        with (logs / f'animals-bake-{index}.log').open('w') as log:
            return subprocess.run([args.blender, '-b', '-t', '2', '--python-exit-code', '1', '--python',
                str(ROOT / 'scripts/bake_animals.py'), '--', str(output / 'animals.source.json'),
                f'--shard={index}/{count}'], stdout=log, stderr=subprocess.STDOUT).returncode

    with concurrent.futures.ThreadPoolExecutor(max_workers=count) as pool:
        results = list(pool.map(worker, range(count)))
    recipe = json.loads((output / 'animals.source.json').read_text())
    merged = dict(format=2, source_sha256=recipe['source_sha256'], animals={}, failures={})
    for index, result in enumerate(results):
        path = output / f'animals.part-{index}.json'
        if not path.exists():
            raise RuntimeError(f'Worker {index} failed before producing a manifest; see its log')
        part = json.loads(path.read_text())
        merged['blender'] = part['blender']
        merged['animals'].update(part['animals'])
        merged['failures'].update(part.get('failures', {}))
        if result and not part.get('failures'):
            raise RuntimeError(f'Worker {index} terminated unexpectedly; see its log')
    expected = {e['id'] for e in recipe['animals']}
    assert expected == set(merged['animals']) | set(merged['failures'])
    (output / 'animals.manifest.json').write_text(json.dumps(merged, indent=2)+'\n')
    for index in range(count):
        (output / f'animals.part-{index}.json').unlink()
    if merged['failures']:
        raise RuntimeError(f'Failed conversions: {merged["failures"]}')
    print(f'Converted all {len(expected)} prefab variants')


if __name__ == '__main__':
    main()
