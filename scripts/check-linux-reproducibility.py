#!/usr/bin/env python3
"""Build Linux Release repeatedly in empty directories and retain comparison evidence."""
import argparse
import datetime as dt
import filecmp
import hashlib
import json
import os
from pathlib import Path
import re
import shlex
import shutil
import struct
import subprocess
import tarfile
import time


def sha(path):
    h = hashlib.sha256()
    with path.open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            h.update(block)
    return h.hexdigest()


def capture(args, cwd=None):
    return subprocess.check_output(args, cwd=cwd, text=True).strip()


def write_json(path, data):
    path.write_text(json.dumps(data, indent=2) + '\n')


def inventory(root, paths):
    return {str(p.relative_to(root)): {
        'sha256': sha(p), 'bytes': p.stat().st_size,
        'mtime_ns': p.stat().st_mtime_ns, 'mode': oct(p.stat().st_mode & 0o777),
    } for p in sorted(paths)}


def content_digest(records):
    content = {name: {'sha256': info['sha256'], 'bytes': info['bytes']}
               for name, info in sorted(records.items())}
    return hashlib.sha256(json.dumps(content, sort_keys=True, separators=(',', ':')).encode()).hexdigest()


def elf_sections(path):
    data = path.read_bytes()
    if data[:6] != b'\x7fELF\x02\x01':
        raise ValueError('Expected a little-endian ELF64 executable')
    offset = struct.unpack_from('<Q', data, 40)[0]
    stride, count, names_index = struct.unpack_from('<HHH', data, 58)
    headers = [struct.unpack_from('<IIQQQQIIQQ', data, offset + n * stride) for n in range(count)]
    names_header = headers[names_index]
    names = data[names_header[4]:names_header[4] + names_header[5]]
    result = {}
    for header in headers[1:]:
        name = names[header[0]:].split(b'\0', 1)[0].decode()
        result[name] = {'type': header[1], 'flags': header[2], 'offset': header[4], 'bytes': header[5],
                        'sha256': None if header[1] == 8 else
                        hashlib.sha256(data[header[4]:header[4] + header[5]]).hexdigest()}
    return result


def archive_headers(path):
    data = path.read_bytes()
    if not data.startswith(b'!<arch>\n'):
        raise ValueError(f'Expected a regular ar archive: {path}')
    result, offset = [], 8
    while offset < len(data):
        header = data[offset:offset + 60]
        if len(header) != 60 or header[-2:] != b'`\n':
            raise ValueError(f'Invalid ar member: {path}')
        size = int(header[48:58])
        result.append({'name': header[:16].decode().strip(), 'timestamp': header[16:28].decode().strip(),
                       'uid': header[28:34].decode().strip(), 'gid': header[34:40].decode().strip(),
                       'mode': header[40:48].decode().strip(), 'bytes': size})
        offset += 60 + size + size % 2
    return result


def differences(baseline, current):
    all_names = sorted(baseline.keys() | current.keys())
    changed = [name for name in all_names if name not in baseline or name not in current or
               baseline[name]['sha256'] != current[name]['sha256']]
    return {'files': len(current), 'changed_content': changed,
            'changed_mtime': [name for name in all_names if name in baseline and name in current and
                              baseline[name]['mtime_ns'] != current[name]['mtime_ns']]}


def main():
    root = Path(__file__).resolve().parents[1]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--runs', type=int, default=10)
    parser.add_argument('--jobs', type=int, default=4)
    parser.add_argument('--output', type=Path, required=True, help='New directory; existing results are never erased')
    parser.add_argument('--raylib-archive', type=Path, default=root / 'build/_deps/raylib-subbuild/raylib-populate-prefix/src/5.5.tar.gz')
    args = parser.parse_args()
    if args.runs < 2 or args.jobs < 1:
        parser.error('Use at least two runs and one compiler job')
    output = args.output.resolve()
    if output.exists():
        parser.error('Output directory already exists; choose a fresh evidence directory')
    archive = args.raylib_archive.resolve()
    expected = re.search(r'URL_HASH SHA256=([a-f0-9]{64})', (root / 'CMakeLists.txt').read_text()).group(1)
    if sha(archive) != expected:
        parser.error('raylib source archive does not match the hash pinned in CMakeLists.txt')
    output.mkdir(parents=True)
    source_names = capture(['git', 'ls-files', '-z', '--', 'CMakeLists.txt', 'src', 'assets'], root).split('\0')
    source_inputs = inventory(root, [root / name for name in source_names if name])
    write_json(output / 'source-inputs.json', source_inputs)
    env = os.environ.copy()
    env['CCACHE_DISABLE'] = '1'
    environment = {
        'commit': capture(['git', 'rev-parse', 'HEAD'], root),
        'tracked_source_digest': content_digest(source_inputs), 'source_directory': str(root),
        'raylib_archive': str(archive), 'raylib_sha256': expected,
        'uname': capture(['uname', '-a']), 'os_release': Path('/etc/os-release').read_text(),
        'cpu_count': os.cpu_count(), 'jobs': args.jobs,
        'variables': {key: env.get(key) for key in ['LANG', 'LC_ALL', 'TZ', 'CFLAGS', 'CXXFLAGS', 'CPPFLAGS',
                                                 'LDFLAGS', 'SOURCE_DATE_EPOCH', 'CCACHE_DISABLE']},
        'tools': {name: {'path': shutil.which(name), 'sha256': sha(Path(shutil.which(name)).resolve()),
                         'version': capture([name, '--version']).splitlines()[0]}
                  for name in ['cmake', 'gcc', 'g++', 'ld', 'ar', 'ranlib', 'make']},
    }
    write_json(output / 'environment.json', environment)
    summary = {'environment': environment, 'requested_runs': args.runs, 'runs': []}
    baseline = None
    for number in range(1, args.runs + 1):
        run = output / f'run-{number:02d}'
        build = run / 'build'
        run.mkdir()
        assert not build.exists()
        started = dt.datetime.now(dt.timezone.utc).isoformat()
        print(f'[{number}/{args.runs}] Fresh configure and complete Release build', flush=True)
        # Only verified source is reused. Every dependency object/library is compiled anew.
        with tarfile.open(archive) as tar:
            source = run / 'dependency-source'
            source.mkdir()
            for member in tar.getmembers():
                target = (source / member.name).resolve()
                if not target.is_relative_to(source.resolve()) or member.issym() or member.islnk():
                    raise ValueError('Unexpected path or link in the pinned raylib archive')
            tar.extractall(source)
        raylib = source / 'raylib-5.5'
        configure = ['cmake', '-S', str(root), '-B', str(build), '-G', 'Unix Makefiles',
                     '-DCMAKE_BUILD_TYPE=Release', '-DBUILD_TESTING=OFF', '-DBUILD_SHARED_LIBS=OFF',
                     '-DDEATHWARD_PACKAGED_ASSETS=OFF', '-DDEATHWARD_SANITIZERS=OFF',
                     '-DCMAKE_C_COMPILER=/usr/bin/gcc', '-DCMAKE_CXX_COMPILER=/usr/bin/g++',
                     '-DCMAKE_C_COMPILER_LAUNCHER=', '-DCMAKE_CXX_COMPILER_LAUNCHER=',
                     '-DCMAKE_EXPORT_COMPILE_COMMANDS=ON', f'-DFETCHCONTENT_SOURCE_DIR_RAYLIB={raylib}']
        compile_command = ['cmake', '--build', str(build), '--target', 'deathward', '--parallel', str(args.jobs)]
        times = {}
        for phase, command in [('configure', configure), ('build', compile_command)]:
            start = time.perf_counter()
            with (run / f'{phase}.log').open('w') as log:
                subprocess.run(command, stdout=log, stderr=subprocess.STDOUT, env=env, check=True)
            times[phase] = time.perf_counter() - start
        commands = json.loads((build / 'compile_commands.json').read_text())
        objects = []
        for command in commands:
            words = shlex.split(command['command'])
            path = (Path(command['directory']) / words[words.index('-o') + 1]).resolve()
            if path.exists():
                objects.append(path)
        libraries = sorted(build.rglob('*.a'))
        compiled = inventory(build, [build / 'deathward', *libraries, *objects])
        assets = inventory(build, [p for p in (build / 'assets').rglob('*') if p.is_file()])
        metadata_names = ['CMakeCache.txt', 'Makefile', 'compile_commands.json', 'CMakeFiles/deathward.dir/link.txt']
        metadata = inventory(build, [build / name for name in metadata_names])
        for name in metadata_names:
            # Source and build path are the only intended configuration differences.
            normalized = (build / name).read_text().replace(str(run), '<RUN>')
            metadata[name]['path_normalized_sha256'] = hashlib.sha256(normalized.encode()).hexdigest()
        notes = capture(['readelf', '-n', str(build / 'deathward')])
        (run / 'elf-notes.txt').write_text(notes + '\n')
        (run / 'elf-layout.txt').write_text(capture(['readelf', '-h', '-l', '-S', '--wide', str(build / 'deathward')]) + '\n')
        (run / 'dynamic-dependencies.txt').write_text(capture(['readelf', '-d', str(build / 'deathward')]) + '\n')
        (run / 'help.txt').write_text(capture([str(build / 'deathward'), '--help']) + '\n')
        (run / 'symbols.txt').write_text(capture(['nm', '-n', '-S', str(build / 'deathward')]) + '\n')
        result = {'run': number, 'started_utc': started, 'seconds': times,
                  'configure_command': configure, 'build_command': compile_command,
                  'compiled_units': len(objects), 'archives': len(libraries),
                  'executable': compiled['deathward'],
                  'build_id': re.search(r'Build ID: ([a-f0-9]+)', notes).group(1),
                  'sections': elf_sections(build / 'deathward'),
                  'compiled': compiled, 'assets': assets, 'metadata': metadata,
                  'compiled_digest': content_digest(compiled), 'assets_digest': content_digest(assets),
                  'archive_headers': {str(p.relative_to(build)): archive_headers(p) for p in libraries}}
        if baseline is None:
            baseline = result
        result['comparison'] = {kind: differences(baseline[kind], result[kind]) for kind in ['compiled', 'assets', 'metadata']}
        result['comparison']['sections_changed'] = [name for name in baseline['sections'].keys() | result['sections'].keys()
                                                   if baseline['sections'].get(name) != result['sections'].get(name)]
        verified = 0
        for name, info in compiled.items():
            if name in baseline['compiled'] and baseline['compiled'][name]['sha256'] == info['sha256']:
                if not filecmp.cmp(output / 'run-01/build' / name, build / name, shallow=False):
                    raise AssertionError(f'Byte comparison disagrees with SHA-256: {name}')
                verified += 1
        result['comparison']['compiled_byte_comparisons_equal'] = verified
        write_json(run / 'manifest.json', result)
        summary['runs'].append(result)
        write_json(output / 'results.json', summary)
        changed = len(result['comparison']['compiled']['changed_content'])
        print(f'[{number}/{args.runs}] {times["build"]:.1f}s build; {len(objects)} objects; '
              f'exe {compiled["deathward"]["sha256"]}; {changed} compiled files differ from run 1', flush=True)
    source_after = inventory(root, [root / name for name in source_names if name])
    summary['source_inputs_unchanged'] = content_digest(source_after) == environment['tracked_source_digest']
    summary['completed_utc'] = dt.datetime.now(dt.timezone.utc).isoformat()
    summary['all_compiled_identical'] = all(not r['comparison']['compiled']['changed_content'] for r in summary['runs'])
    summary['all_assets_identical'] = all(not r['comparison']['assets']['changed_content'] for r in summary['runs'])
    write_json(output / 'results.json', summary)
    if not summary['source_inputs_unchanged']:
        raise RuntimeError('Source inputs changed during the experiment; results are not controlled')
    print(f'Complete: {output / "results.json"}', flush=True)


if __name__ == '__main__':
    main()
