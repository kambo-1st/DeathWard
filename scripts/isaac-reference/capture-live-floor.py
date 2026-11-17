#!/usr/bin/env python3
"""Capture a paused installed first floor through the read-only C# reader.

Uses ordinary PowerShell commands to host the reader. Does not execute a .ps1
file, change execution policy, write process memory or send game input.
"""
import argparse
import base64
import json
from pathlib import Path
import subprocess

ROOT = Path(__file__).resolve().parents[2]
SHA = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    output = args.output.resolve()
    if output.exists() or not output.parent.is_dir():
        parser.error('Output must be a new file in an existing directory')
    script = (ROOT / 'scripts/isaac-reference/read-live-floor.ps1').read_text()
    source = script.split("@'", 1)[1].split("'@", 1)[0]
    windows_path = subprocess.check_output(['wslpath', '-w', str(output)], text=True).strip()
    quoted = windows_path.replace("'", "''")
    command = "$ErrorActionPreference='Stop'; $ProgressPreference='SilentlyContinue'; Add-Type -TypeDefinition @'\n" + source + "\n'@\n"
    command += "$p=@(Get-Process isaac-ng -ErrorAction Stop); if($p.Count -ne 1){throw 'Expected one Isaac process'}; $p=$p[0]; "
    command += "$expected='" + SHA + "'; if((Get-FileHash -LiteralPath $p.Path -Algorithm SHA256).Hash.ToLowerInvariant() -ne $expected){throw 'Pinned executable mismatch'}; "
    command += "$c=[DeathWardLiveFloor]::Capture($p.Id,$p.MainModule.BaseAddress.ToInt64()); $c['executable_sha256']=$expected; "
    command += "$out='" + quoted + "'; if(Test-Path -LiteralPath $out){throw 'Output exists'}; "
    command += "[IO.File]::WriteAllText($out,($c|ConvertTo-Json -Depth 16),(New-Object Text.UTF8Encoding($false)))"
    encoded = base64.b64encode(command.encode('utf-16le')).decode()
    result = subprocess.run(['powershell.exe', '-NoProfile', '-NonInteractive', '-EncodedCommand', encoded], capture_output=True, text=True)
    if result.returncode:
        raise SystemExit(result.stdout + result.stderr)
    capture = json.loads(output.read_text())
    print(json.dumps({'output': str(output), 'stage': capture['stage'], 'stage_type': capture['stage_type'],
                      'difficulty': capture['difficulty'], 'descriptors': capture['descriptor_count'],
                      'current_list_index': capture['current_list_index']}))


if __name__ == '__main__':
    main()
