param(
    [string]$SourceDirectory = (Split-Path -Parent $PSScriptRoot),
    [string]$BuildDirectory = (Join-Path $env:LOCALAPPDATA 'DeathWard\build-windows'),
    [string]$OutputDirectory = '',
    [string]$CMake = '',
    [string]$RaylibSourceDirectory = '',
    [ValidateRange(1, 64)][int]$Jobs = 4,
    [switch]$RunTests,
    [switch]$SkipPackage
)
$ErrorActionPreference = 'Stop'
Set-StrictMode -Version Latest

try {
    $SourceDirectory = (Resolve-Path -LiteralPath $SourceDirectory).ProviderPath
    if (!$OutputDirectory) { $OutputDirectory = Join-Path $SourceDirectory 'dist' }
    if (!$CMake) {
        $command = Get-Command cmake.exe -ErrorAction SilentlyContinue
        if ($command) { $CMake = $command.Source }
        elseif (Test-Path "$env:ProgramFiles\CMake\bin\cmake.exe") {
            $CMake = "$env:ProgramFiles\CMake\bin\cmake.exe"
        } else {
            $vswhere = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe"
            if (Test-Path $vswhere) {
                $found = @(& $vswhere -latest -products '*' -find '**\cmake.exe')
                if ($found.Count) { $CMake = $found[0] }
            }
        }
    }
    if (!$CMake -or !(Test-Path -LiteralPath $CMake)) {
        throw 'Install Windows CMake 3.20+ and Visual Studio 2022 with Desktop development with C++.'
    }
    $sourceForBuild = $SourceDirectory
    $cacheDirectory = Join-Path $BuildDirectory 'cmake'
    if ($SourceDirectory.StartsWith('\\')) {
        # MSBuild lowercases tracked dependency paths; WSL's case-sensitive UNC
        # share then forces full rebuilds. Keep a disposable copy on Windows.
        if (![IO.Path]::IsPathRooted($BuildDirectory) -or $BuildDirectory.StartsWith('\\')) {
            throw 'For WSL sources, BuildDirectory must be an absolute local Windows path.'
        }
        $sourceForBuild = Join-Path $BuildDirectory 'source'
        New-Item -ItemType Directory -Force -Path $sourceForBuild | Out-Null
        Copy-Item -LiteralPath (Join-Path $SourceDirectory 'CMakeLists.txt') -Destination $sourceForBuild
        foreach ($folder in @('src', 'tests', 'tools', 'assets')) {
            & robocopy.exe (Join-Path $SourceDirectory $folder) (Join-Path $sourceForBuild $folder) /MIR /XJ /R:2 /W:1 /NFL /NDL /NJH /NJS /NP
            if ($LASTEXITCODE -ge 8) { throw "Could not stage $folder for the Windows build." }
        }
    }
    $configure = @('-S', $sourceForBuild, '-B', $cacheDirectory,
        '-G', 'Visual Studio 17 2022', '-A', 'x64',
        '-DDEATHWARD_PACKAGED_ASSETS=ON', '-DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreaded',
        '-DBUILD_SHARED_LIBS=OFF', "-DBUILD_TESTING=$(@('OFF', 'ON')[[int][bool]$RunTests])")
    if ($RaylibSourceDirectory) {
        $configure += "-DFETCHCONTENT_SOURCE_DIR_RAYLIB=$RaylibSourceDirectory"
    }
    & $CMake @configure
    if ($LASTEXITCODE) { throw "Windows configuration failed ($LASTEXITCODE)." }
    $build = @('--build', $cacheDirectory, '--config', 'Release', '--parallel', "$Jobs")
    if (!$RunTests) { $build += @('--target', 'deathward') }
    & $CMake @build
    if ($LASTEXITCODE) { throw "Windows build failed ($LASTEXITCODE)." }
    if ($RunTests) {
        $ctest = Join-Path (Split-Path -Parent $CMake) 'ctest.exe'
        & $ctest --test-dir $cacheDirectory -C Release --output-on-failure --parallel $Jobs
        if ($LASTEXITCODE) { throw "Windows tests failed ($LASTEXITCODE)." }
    }
    $runtime = Join-Path $cacheDirectory 'Release'
    Write-Host "Windows executable: $runtime\deathward.exe"
    if ($SkipPackage) { exit 0 }

    # CMake stages the runtime assets; do not ship Unity sources or developer saves.
    New-Item -ItemType Directory -Force -Path $OutputDirectory | Out-Null
    $staging = Join-Path $OutputDirectory ('.windows-package-' + [guid]::NewGuid().ToString('N'))
    $bundle = Join-Path $staging 'deathward-windows-x64'
    New-Item -ItemType Directory -Force -Path $bundle | Out-Null
    try {
        Copy-Item -LiteralPath (Join-Path $runtime 'deathward.exe') -Destination $bundle
        Copy-Item -LiteralPath (Join-Path $runtime 'assets') -Destination $bundle -Recurse
        Get-ChildItem -LiteralPath (Join-Path $bundle 'assets') -Recurse -File |
            Where-Object { $_.Name -match '\.(bak|tmp|save)$|^(audio|visual)\.cfg$' } |
            Remove-Item -Force
        $licenseCache = Get-Content -LiteralPath (Join-Path $cacheDirectory 'CMakeCache.txt') |
            Where-Object { $_ -match '^raylib_SOURCE_DIR:STATIC=' } | Select-Object -First 1
        if (!$licenseCache) { throw 'Cannot locate the raylib license in the configured build.' }
        $raylib = ($licenseCache -split '=', 2)[1]
        if (!(Test-Path -LiteralPath (Join-Path $raylib 'LICENSE'))) { $raylib = Split-Path -Parent $raylib }
        Copy-Item -LiteralPath (Join-Path $raylib 'LICENSE') -Destination (Join-Path $bundle 'raylib-LICENSE.txt')
        Copy-Item -LiteralPath (Join-Path $raylib 'src\external\glfw\LICENSE.md') -Destination (Join-Path $bundle 'glfw-LICENSE.txt')
        @'
@echo off
pushd "%~dp0"
deathward.exe --full-experience %*
popd
'@ | Set-Content -LiteralPath (Join-Path $bundle 'Play DeathWard.cmd') -Encoding ASCII
        @'
DeathWard - Windows x64

Extract the whole folder before playing. Double-click Play DeathWard.cmd for
the logos, save slots and train opening. deathward.exe starts directly in town.
Keep assets beside deathward.exe: models include their original textures, and
music, effects, maps, animations and fonts are all included.

Requires 64-bit Windows 10/11 and an OpenGL 3.3-capable graphics driver.
This native build does not need WSL, a browser or a separate C++ runtime install.

Saves and preferences: %LOCALAPPDATA%\DeathWard
Windows saves are separate from Linux/WSL and browser saves.
Editors: deathward.exe --editor or deathward.exe --cinematic
Editors modify this copy of assets; extract into a writable folder.
Other options: deathward.exe --help
'@ | Set-Content -LiteralPath (Join-Path $bundle 'README.txt') -Encoding ASCII
        $archive = Join-Path $staging 'deathward-windows-x64.zip'
        Add-Type -AssemblyName System.IO.Compression, System.IO.Compression.FileSystem
        $zip = [IO.Compression.ZipFile]::Open($archive, [IO.Compression.ZipArchiveMode]::Create)
        try {
            foreach ($file in Get-ChildItem -LiteralPath $bundle -Recurse -File) {
                # PowerShell 5's Compress-Archive can write backslash entries.
                # Use standard ZIP separators for all extractors.
                $name = 'deathward-windows-x64/' + $file.FullName.Substring($bundle.Length + 1).Replace('\', '/')
                [IO.Compression.ZipFileExtensions]::CreateEntryFromFile(
                    $zip, $file.FullName, $name, [IO.Compression.CompressionLevel]::Optimal) | Out-Null
            }
        } finally { $zip.Dispose() }
        $destination = Join-Path $OutputDirectory 'deathward-windows-x64'
        if (Test-Path -LiteralPath $destination) { Remove-Item -LiteralPath $destination -Recurse -Force }
        Move-Item -LiteralPath $bundle -Destination $destination
        Move-Item -LiteralPath $archive -Destination (Join-Path $OutputDirectory 'deathward-windows-x64.zip') -Force
        Write-Host "Windows package: $OutputDirectory\deathward-windows-x64.zip"
    } finally {
        if (Test-Path -LiteralPath $staging) { Remove-Item -LiteralPath $staging -Recurse -Force }
    }
} catch {
    Write-Error $_
    exit 1
}
