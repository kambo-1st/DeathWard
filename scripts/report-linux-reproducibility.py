#!/usr/bin/env python3
"""Render a completed Linux reproducibility audit as an offline HTML report."""
import argparse
import csv
import datetime as dt
import hashlib
from html import escape as esc
import json
from pathlib import Path
import statistics


def code(value):
    return '<code>' + esc(str(value)) + '</code>'


def table(headers, rows):
    return '<div class="table-wrap"><table><thead><tr>' + ''.join('<th>' + h + '</th>' for h in headers) + \
        '</tr></thead><tbody>' + ''.join('<tr>' + ''.join('<td>' + str(c) + '</td>' for c in row) + '</tr>' for row in rows) + \
        '</tbody></table></div>'


def utc(nanoseconds):
    return dt.datetime.fromtimestamp(nanoseconds / 1e9, dt.timezone.utc).isoformat(timespec='milliseconds')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('results', type=Path)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    data = json.loads(args.results.read_text())
    runs, env = data['runs'], data['environment']
    if len(runs) != data['requested_runs'] or 'completed_utc' not in data:
        parser.error('The audit must finish before its report can be produced')
    if not data['source_inputs_unchanged']:
        parser.error('Source inputs changed during the audit')
    first, last = runs[0], runs[-1]
    output = args.output.resolve()
    output.parent.mkdir(parents=True, exist_ok=True)
    summary_file = output.with_suffix('.json')
    csv_file = output.with_suffix('.csv')
    unique = len({r['executable']['sha256'] for r in runs})
    compiled_changed = sorted({name for r in runs for name in r['comparison']['compiled']['changed_content']})
    assets_changed = sorted({name for r in runs for name in r['comparison']['assets']['changed_content']})
    metadata_changed = sorted({name for r in runs for name in r['comparison']['metadata']['changed_content']})
    normalized_equal = all(r['metadata'][name]['path_normalized_sha256'] == first['metadata'][name]['path_normalized_sha256']
                           for r in runs for name in first['metadata'])
    sections_equal = all(not r['comparison']['sections_changed'] for r in runs)
    archive_zero = all(h['timestamp'] in ('', '0') and h['uid'] in ('', '0') and h['gid'] in ('', '0')
                       for r in runs for headers in r['archive_headers'].values() for h in headers)
    raw = args.results.resolve().parent
    binary = (raw / 'run-01/build/deathward').read_bytes()
    embedded_source = (env['source_directory'] + '/assets').encode() in binary
    embedded_audit = str(raw).encode() in binary
    if compiled_changed or assets_changed or not normalized_equal or not sections_equal or not archive_zero or embedded_audit:
        parser.error('Automatic report explanations require identical artifacts, deterministic archives and path-only metadata differences; inspect the raw evidence first')
    if any(name.startswith('.debug') for name in first['sections']):
        parser.error('This report template describes Release without debug sections; inspect this configuration separately')
    completed = dt.datetime.fromisoformat(data['completed_utc'])
    date_label = completed.strftime('%d %B %Y')
    warnings = [[line.replace(str(raw / f'run-{r["run"]:02d}'), '<RUN>')
                 for line in (raw / f'run-{r["run"]:02d}/build.log').read_text().splitlines() if 'warning:' in line]
                for r in runs]
    warning_sets_equal = all(sorted(w) == sorted(warnings[0]) for w in warnings)
    existing = Path(env['source_directory']) / 'build/deathward'
    existing_equal = existing.is_file() and existing.read_bytes() == binary
    timings = [r['seconds']['build'] for r in runs]
    digest = hashlib.sha256(args.results.read_bytes()).hexdigest()
    summary = {key: data[key] for key in ['environment', 'requested_runs', 'completed_utc', 'source_inputs_unchanged',
                                         'all_compiled_identical', 'all_assets_identical']}
    summary.update({'raw_results_sha256': digest, 'raw_evidence_directory': str(raw),
                    'unique_executables': unique, 'changed_compiled_files': compiled_changed,
                    'changed_asset_files': assets_changed, 'changed_metadata_files': metadata_changed,
                    'metadata_identical_after_path_normalization': normalized_equal,
                    'archive_metadata_zeroed': archive_zero, 'existing_linux_executable_identical': existing_equal,
                    'source_asset_path_embedded': embedded_source, 'audit_directory_embedded': embedded_audit,
                    'warning_counts': [len(w) for w in warnings], 'warnings_identical_after_path_normalization': warning_sets_equal,
                    'compiled_manifest': first['compiled'], 'asset_manifest_digest': first['assets_digest'],
                    'executable_sections': first['sections'],
                    'runs': [{key: r[key] for key in ['run', 'started_utc', 'seconds', 'compiled_units', 'archives',
                                                     'executable', 'build_id', 'compiled_digest', 'assets_digest', 'comparison']}
                             for r in runs]})
    summary_file.write_text(json.dumps(summary, indent=2) + '\n')
    with csv_file.open('w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(['run', 'configure_seconds', 'build_seconds', 'executable_bytes', 'sha256', 'build_id',
                         'changed_compiled_files', 'changed_asset_files'])
        for r in runs:
            writer.writerow([r['run'], f'{r["seconds"]["configure"]:.3f}', f'{r["seconds"]["build"]:.3f}',
                             r['executable']['bytes'], r['executable']['sha256'], r['build_id'],
                             len(r['comparison']['compiled']['changed_content']), len(r['comparison']['assets']['changed_content'])])

    # A standalone, vector timing plot is included in the report and saved separately.
    import matplotlib
    matplotlib.use('Agg')
    import matplotlib.pyplot as plt
    plt.rcParams.update({'font.family': 'DejaVu Sans', 'font.size': 10, 'svg.hashsalt': 'deathward-reproducibility'})
    fig, ax = plt.subplots(figsize=(10.4, 3.1))
    fig.patch.set_facecolor('#f5f7fa'); ax.set_facecolor('#f5f7fa')
    xs = list(range(1, len(runs) + 1))
    conf = [r['seconds']['configure'] for r in runs]
    ax.bar(xs, conf, color='#bbc9d5', label='Configure', width=.64)
    ax.bar(xs, timings, bottom=conf, color='#276d66', label='Compile, link and stage', width=.64)
    for x, c, b in zip(xs, conf, timings):
        ax.text(x, c + b + 1, f'{c + b:.1f}', ha='center', fontsize=9, color='#233440')
    ax.set_xticks(xs, [f'{x:02}' for x in xs]); ax.set_xlabel('Independent clean build'); ax.set_ylabel('Seconds')
    ax.set_ylim(0, max(c + b for c, b in zip(conf, timings)) * 1.20)
    ax.spines[['top', 'right', 'bottom', 'left']].set_visible(False)
    ax.tick_params(axis='both', length=0); ax.set_axisbelow(True); ax.grid(axis='y', alpha=.15)
    ax.legend(loc='upper right', frameon=False, fontsize=9, ncol=2)
    fig.tight_layout()
    plot_file = output.with_name(output.stem + '-timings.svg')
    fig.savefig(plot_file, format='svg', metadata={'Date': None}); plt.close(fig)
    chart = plot_file.read_text(); chart = chart[chart.index('<svg'):]

    good = data['all_compiled_identical'] and data['all_assets_identical']
    verdict = 'Ten clean builds. Identical binaries.' if good and len(runs) == 10 else \
              f'{len(runs)} clean builds. ' + ('Identical binaries.' if good else 'Differences found.')
    message = ('Every executable, static library and object file matched run 01 byte for byte. '
               'All staged assets matched by SHA-256. No binary changes were found.' if good else
               'The tables and evidence identify differing files. Further attribution is required before claiming reproducibility.')
    run_table = table(['Run', 'Configure', 'Build', 'Executable SHA-256', 'Changed compiled / assets'], [
        [f'{r["run"]:02}', f'{r["seconds"]["configure"]:.2f} s', f'{r["seconds"]["build"]:.2f} s',
         '<span title="' + r['executable']['sha256'] + '">' + code(r['executable']['sha256'][:16] + '…') + '</span>',
         f'{len(r["comparison"]["compiled"]["changed_content"])} / {len(r["comparison"]["assets"]["changed_content"])}'] for r in runs])
    library_table = table(['Static library', 'Bytes', 'SHA-256 (prefix)', 'Unique hashes'], [
        [code(Path(name).name), f'{info["bytes"]:,}', code(info['sha256'][:16]), len({r['compiled'][name]['sha256'] for r in runs})]
        for name, info in first['compiled'].items() if name.endswith('.a')])
    metadata_table = table(['File', 'Raw content', 'After replacing each run’s path'], [
        [code(name), 'Different' if name in metadata_changed else 'Identical',
         'Identical' if all(r['metadata'][name]['path_normalized_sha256'] == first['metadata'][name]['path_normalized_sha256'] for r in runs) else 'Different']
        for name in first['metadata']])
    section_names = ['.text', '.rodata', '.data', '.symtab', '.strtab', '.note.gnu.build-id', '.comment']
    section_table = table(['Executable section', 'Bytes', 'Result'], [
        [code(name), f'{first["sections"][name]["bytes"]:,}', 'Identical' if all(r['sections'][name] == first['sections'][name] for r in runs) else 'Different']
        for name in section_names])
    timestamp_table = table(['File', 'Run 01 modified (UTC)', f'Run {last["run"]:02} modified (UTC)'], [
        [code(name), utc(first['compiled'][name]['mtime_ns']), utc(last['compiled'][name]['mtime_ns'])]
        for name in ['deathward', 'libdeathward_core.a']])
    steps = [
        'Start from the same tracked game inputs at commit ' + code(env['commit'][:12]) + '. Verify their aggregate content fingerprint before and after the experiment.',
        'Create a new run directory and a previously nonexistent build directory. Freshly extract the raylib archive whose SHA-256 matches CMake’s pinned value.',
        f'Configure Release with the recorded GCC/G++ toolchain, Unix Makefiles, static libraries, sanitizers off and {env["jobs"]} compiler jobs. Disable compiler launchers and ccache.',
        'Build target ' + code('deathward') + ', including its dependencies. Game test executables and the navigation-baking utility are outside this comparison.',
        'Hash the executable, every produced object/library and every staged asset. Compare each compiled file directly against run 01’s bytes; inspect ELF sections, build IDs and archive headers.',
        'Run each executable with ' + code('--help') + ' and retain commands, manifests, logs, symbols and complete build trees.']
    env_table = table(['Setting', 'Recorded value'], [
        ['Source commit', code(env['commit'])], ['C++ compiler', esc(env['tools']['g++']['version'])],
        ['CMake', esc(env['tools']['cmake']['version'])], ['Linker / archiver', esc(env['tools']['ld']['version'])],
        ['Platform', esc(next(line.split('=',1)[1].strip('"') for line in env['os_release'].splitlines() if line.startswith('PRETTY_NAME='))) + ', x86-64, WSL2'], ['Optimization', code('-O3 -DNDEBUG')],
        ['Parallelism', f'{env["jobs"]} compiler jobs per run; runs executed sequentially'],
        ['Source asset mode', code('DEATHWARD_PACKAGED_ASSETS=OFF') + ' (normal Linux development setting)'],
        ['SOURCE_DATE_EPOCH', code(str(env['variables']['SOURCE_DATE_EPOCH'])) + ' — unset'],
        ['Prefix remapping / stripping', 'Neither applied to compared binaries'],
        ['Finished (UTC)', code(data['completed_utc'])]])
    limitation = ('The result establishes repeatability for this source, toolchain, flags and host while changing '
                  'build/dependency extraction directories and compilation time. It does not establish equality across '
                  'different compiler versions, machines, Debug builds or Windows/WASM. The main source checkout path '
                  'was fixed. Its asset path is embedded in the executable, so relocating that checkout is a separate test. '
                  'Shared system libraries and GPU drivers were not rebuilt. This audit checks compiled output, not '
                  'gameplay correctness or runtime performance.')
    explanation = (f'<p>There were <strong>{len(compiled_changed)} changed compiled files</strong>. '
        'The observable changes occurred outside the binary contents:</p>'
        '<h3>Filesystem dates changed</h3><p>Each run created new files. Their modification times differ, '
        'even though their contents and SHA-256 hashes match. A changed date in a file manager does not imply '
        'a changed program.</p>' + timestamp_table +
        '<h3>Build configuration paths changed</h3><p>The CMake cache, Makefile and compilation database record their '
        'run-specific directories. Replacing only each run’s directory prefix makes the four inspected metadata files '
        'identical. The linker command is already identical before normalization.</p>' + metadata_table +
        '<h3>Build timing and log order can vary</h3><p>The measured build phase ranges from '
        f'{min(timings):.2f} to {max(timings):.2f} seconds. Timing differences alone are not binary differences. '
        'This experiment did not isolate the causes of timing variation. OS caches were not flushed, and parallel '
        'compiler scheduling was not controlled, so these measurements are not a cold-cache benchmark.</p>')
    mechanistic = ('<p>The observations are consistent with a deterministic build under the tested conditions:</p><ul>'
        '<li>The source fingerprint remained unchanged, the dependency archive was hash-verified, and the compiler/linker settings stayed fixed.</li>'
        f'<li>All {first["archives"]} archives have zero timestamps and owner/group IDs for their real members. GNU ar’s deterministic mode '
        'removes those varying inputs from archive bytes. <a href="https://sourceware.org/binutils/docs/binutils/ar-cmdline.html">GNU ar documentation</a>.</li>'
        '<li>The executable has no DWARF debug sections, and its bytes contain no audit-directory prefix. The fixed source asset path remains embedded.</li>'
        '<li>The linker command and object/library order are identical. The GNU build ID is also identical; the linker’s default SHA-1 style is content-based. '
        'The full-file SHA-256 and direct byte comparisons provide the stronger file-equality check. '
        '<a href="https://sourceware.org/binutils/docs/ld/Options.html#index-_002d_002dbuild_002did">GNU ld documentation</a>.</li></ul>')
    reproduction = ('python3 scripts/check-linux-reproducibility.py \\\n'
                    '  --runs 10 --jobs 4 \\\n'
                    '  --output artifacts/linux-reproducibility-new-run\n\n'
                    'python3 scripts/report-linux-reproducibility.py \\\n'
                    '  artifacts/linux-reproducibility-new-run/results.json \\\n'
                    '  --output docs/reports/linux-reproducibility-new-run.html')
    style = '''
:root{--ink:#1a2b36;--muted:#536570;--green:#276d66;--line:#dce3e6;--paper:#fff;--soft:#f5f7fa}
*{box-sizing:border-box}body{margin:0;background:#e8edf0;color:var(--ink);font:15px/1.62 system-ui,-apple-system,"Segoe UI",sans-serif}
main{max-width:1100px;margin:34px auto;background:var(--paper);box-shadow:0 16px 65px #16313a16}
header{background:#17323a;color:#fff;padding:48px 56px 38px;border-top:7px solid #d6ad6b}
.eyebrow{font-size:11px;text-transform:uppercase;letter-spacing:2px;color:#b9d0d2;font-weight:650}
h1{font-size:43px;line-height:1.12;letter-spacing:-1.7px;margin:17px 0 19px;max-width:780px}header p{color:#d3e0e2;max-width:820px;font-size:17px}
.status{display:inline-block;background:#2b5558;padding:4px 12px;border-radius:30px;font-size:12px;color:#d6f6ed;margin-bottom:5px}
.toolbar{display:flex;gap:18px;align-items:center;margin-top:22px;font-size:12px}.toolbar a{color:#dcebe9}.toolbar button{background:#fff;color:#17323a;border:0;border-radius:5px;padding:8px 13px;cursor:pointer;font:inherit}
section{padding:30px 56px;border-bottom:1px solid var(--line)}h2{font-size:25px;line-height:1.2;margin:0 0 18px;letter-spacing:-.5px}h3{font-size:17px;margin:25px 0 6px}p{margin:9px 0 15px}a{color:var(--green)}
.metrics{display:grid;grid-template-columns:repeat(4,1fr);gap:14px;margin-bottom:24px}.metric{background:var(--soft);padding:18px;border-radius:7px;border-left:3px solid var(--green)}.metric strong{font-size:31px;line-height:1.15;display:block;letter-spacing:-1px}.metric span{display:block;color:var(--muted);font-size:12px;margin-top:6px}
.callout{padding:17px 20px;background:#edf5f2;border:1px solid #d6e7de;border-radius:5px}.small,.caption{font-size:12px;color:var(--muted)}.caption{margin-top:6px}code,pre{font-family:ui-monospace,SFMono-Regular,Consolas,monospace;font-size:12px}code{overflow-wrap:anywhere}.fingerprint{font-size:13px;display:block;line-height:1.8}
.table-wrap{overflow-x:auto}table{border-collapse:collapse;width:100%;font-size:12px;margin:12px 0 16px}th{text-align:left;text-transform:uppercase;letter-spacing:.6px;font-size:10px;color:var(--muted);background:var(--soft)}th,td{padding:9px 11px;border-bottom:1px solid var(--line);vertical-align:top}tbody tr:nth-child(even){background:#fafcfc}td:first-child{font-weight:550}.chart svg{width:100%;height:auto}.chart{background:var(--soft);border-radius:6px;padding:5px;margin-top:20px}
.two{display:grid;grid-template-columns:1fr 1fr;gap:25px}.two h3{margin-top:0}ul,ol{padding-left:22px}li{margin:8px 0}pre{white-space:pre-wrap;overflow-wrap:anywhere;background:#17323a;color:#deeeeb;border-radius:6px;padding:20px;line-height:1.8}.proof{font-size:12px}footer{padding:22px 56px;color:var(--muted);font-size:11px;display:flex;justify-content:space-between;gap:20px}details>summary{cursor:pointer;font-weight:600;margin:10px 0}
@media(max-width:720px){main{margin:0}header,section{padding:28px 23px}h1{font-size:34px}.metrics{grid-template-columns:repeat(2,1fr)}.two{grid-template-columns:1fr}footer{padding:20px 23px}.toolbar{flex-wrap:wrap}}
@page{size:A4;margin:14mm 13mm}@media print{body{background:#fff;font-size:11px;line-height:1.45}main{max-width:none;margin:0;box-shadow:none}header{padding:22px 25px;print-color-adjust:exact;-webkit-print-color-adjust:exact}h1{font-size:31px;max-width:600px}header p{font-size:12px}.toolbar{display:none}section{padding:20px 10px;break-inside:auto}h2{font-size:20px;break-after:avoid}h3{font-size:13px;break-after:avoid}p,li{orphans:3;widows:3}table{font-size:10px;break-inside:avoid}code,pre{font-size:9px}th{font-size:9px}th,td{padding:6px 7px}.metric{padding:12px;print-color-adjust:exact}.metric strong{font-size:26px}.metric span{font-size:9px}.fingerprint{font-size:10px}.chart{break-inside:avoid}.page{break-before:page}.small,.caption{font-size:10px}footer{font-size:8px;padding:16px 10px}details{display:block}details>*{display:block}.two{gap:15px}a{text-decoration:none}}
'''
    html = ('<!doctype html><html lang="en"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width, initial-scale=1">' + \
        '<title>DeathWard · Linux build reproducibility</title><style>' + style + '</style></head><body><main>' + \
        '<header><div class="eyebrow">DeathWard / Engineering report / ' + date_label + '</div><h1>' + verdict + '</h1>' + \
        '<span class="status">' + ('PASS · Controlled reproducibility check' if good else 'REVIEW · Differences detected') + '</span><p>' + message + '</p>' + \
        '<div class="toolbar"><button onclick="window.print()">Print / Save PDF</button><a href="' + summary_file.name + '">Structured evidence</a><a href="' + csv_file.name + '">Run table CSV</a><a href="#method">Method &amp; limits</a></div></header>' + \
        '<section><div class="metrics">' + ''.join(f'<div class="metric"><strong>{a}</strong><span>{b}</span></div>' for a,b in [
            (f'{len(runs)}/{data["requested_runs"]}', 'clean builds completed'), (str(unique), 'unique executable SHA-256'),
            (str(len(compiled_changed)), 'compiled files changed'), (str(len(assets_changed)), 'asset files changed')]) + '</div>' + \
        '<div class="callout"><strong>Executable fingerprint</strong><code class="fingerprint">' + first['executable']['sha256'] + '</code><div class="small">' + \
        f'{first["executable"]["bytes"]:,} bytes · {first["executable"]["bytes"]/1024**2:.3f} MiB · ELF64 / x86-64<br>GNU build ID: ' + code(first['build_id']) + '</div></div>' + \
        '<p class="small">' + ('The pre-existing <code>build/deathward</code> also matches the clean-build executable byte for byte.' if existing_equal else 'The pre-existing executable does not match or was not available; it is outside the ten-build comparison.') + '</p>' + \
        '<h3>What was compared in every run</h3>' + table(['Artifact category', 'Files per run', 'Comparison', 'Result'], [
            ['Linux executable', 1, 'SHA-256 + direct byte comparison', f'{unique} unique hash'],
            ['Static libraries', first['archives'], 'SHA-256 + direct byte comparison', 'Identical' if not compiled_changed else 'See evidence'],
            ['Compiled object files', first['compiled_units'], 'SHA-256 + direct byte comparison', 'Identical' if not compiled_changed else 'See evidence'],
            ['Staged models, textures, audio, maps and fonts', len(first['assets']), 'SHA-256 by relative path', 'Identical' if not assets_changed else 'See evidence'],
            ['ELF sections', len(first['sections']), 'Contents + section layout', 'Identical' if sections_equal else 'See evidence']]) + \
        f'<p class="caption">{len(first["compiled"])} compiled files and {len(first["assets"])} staged asset files per run. '
        f'Assets total {sum(a["bytes"] for a in first["assets"].values()):,} bytes. The game was not modified.</p></section>' + \
        '<section class="page"><h2>Every run, measured</h2>' + run_table + '<div class="chart">' + chart + '</div>' + \
        f'<p class="caption">Mean build phase: {statistics.mean(timings):.2f} s; median: {statistics.median(timings):.2f} s. '
        'Bars show configure + build only; archive extraction, hashing and analysis are excluded. Timings are observational.</p>' + \
        '<h3>Libraries match as well as the executable</h3>' + library_table + '</section>' + \
        '<section class="page"><h2>What changed, and what it means</h2>' + explanation + \
        '<h3>Why the binaries stayed stable</h3>' + mechanistic +
        f'<p class="small">Build diagnostics: {len(warnings[0])} warning lines in the first build; '
        + ('the same normalized warning set appears in every run. They concern raylib/dependency code and the MAX_MESH_VERTEX_BUFFERS definition. These warnings were recorded, not repaired, in this compilation audit.' if warning_sets_equal else 'diagnostics vary; inspect the retained build logs.') + '</p></section>' + \
        '<section class="page" id="method"><h2>Method &amp; scope</h2><ol>' + ''.join('<li>' + s + '</li>' for s in steps) + '</ol>' + \
        env_table + '<h3>Limits of the conclusion</h3><p>' + limitation + '</p>' + \
        '<div class="callout"><strong>Recommendation</strong><p>No reproducibility repair is needed for the tested Linux Release configuration. '
        'Keep the pinned dependency and record compiler versions for releases. Before promising reproducibility across machines, '
        'test a relocated source checkout, packaged asset mode, compiler versions and archive packaging separately. '
        'GCC provides path remapping for compiler-recorded paths; the explicitly embedded asset-directory string must also be handled. '
        '<a href="https://gcc.gnu.org/onlinedocs/gcc/Overall-Options.html#index-ffile-prefix-map">GCC path-remapping documentation</a>.</p></div></section>' + \
        '<section class="page"><h2>Evidence &amp; reproduction</h2><h3>Selected executable sections</h3>' + section_table + \
        '<p class="small">All section layouts were compared, including the size of the zero-initialized <code>.bss</code> section. '
        'No <code>.debug*</code> sections are present in this Release executable. Raw binaries were compared without stripping or prefix normalization.</p>' + \
        '<h3>Run the experiment again</h3><pre>' + esc(reproduction) + '</pre><p class="small">The runner needs the cached raylib 5.5 source archive '
        '(or <code>--raylib-archive PATH</code>), normal Linux build dependencies and sufficient space for all build trees. '
        'It refuses to overwrite an existing evidence directory. The report renderer additionally uses Matplotlib.</p>' + \
        '<h3>Evidence locations and integrity</h3><p class="proof">Full build trees, logs, manifests, symbols and ELF inspections:<br>' + code(raw) + '</p>' + \
        '<p class="proof">Source-content manifest digest:<br>' + code(env['tracked_source_digest']) + '<br>Verified raylib source archive SHA-256:<br>' + code(env['raylib_sha256']) + \
        '<br>Raw results.json SHA-256:<br>' + code(digest) + '</p>' + \
        '<p class="small">Companion JSON contains the environment, per-run comparisons and compiled-file fingerprints; CSV contains the full executable hashes and timings. '
        'The report works offline. External links point only to the GNU toolchain documentation supporting the explanations.</p></section>' + \
        '<footer><span>DeathWard · Native Linux build audit</span><span>Source ' + env['commit'][:12] + ' · ' + completed.strftime('%d %b %Y') + '</span></footer></main></body></html>')
    output.write_text(html)
    print(output)
    print(summary_file)
    print(csv_file)
    print(plot_file)


if __name__ == '__main__':
    main()
