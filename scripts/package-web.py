#!/usr/bin/env python3
"""Package an existing browser build for any static HTTP(S) directory."""
import argparse
import hashlib
import json
from pathlib import Path
import re
import shutil
import tempfile
import zipfile


UPLOAD_GUIDE = """DeathWard - static website package

Upload/extract all files beside this README into the desired public directory.
index.html must sit directly in that directory (not inside another folder).

The SAME files work at either address, without editing or rebuilding:
  https://kambo.us/deathward/  -> the website's public deathward directory
  https://deathward.kambo.us/ -> the subdomain's document root

The subdomain must first point to your host and have its document root/HTTPS set
up there. No Node.js, Python, PHP, database or application server is needed on
the host. Open the URL, wait for loading, then click Enter Black Creek.

Server settings:
  - Serve index.html as the directory index.
  - Redirect directory URLs without a trailing slash to the slash version.
  - Serve .wasm as application/wasm, .js as text/javascript (or
    application/javascript), and .data as application/octet-stream.
  - Serve real files directly. Do not rewrite missing .wasm/.data/.js requests
    to another site's index.html or a login page.
  - Revalidate index.html on each visit (Cache-Control: no-cache recommended).
    The versioned deathward.* files can be cached for a year with immutable.
  - Enable HTTP gzip/Brotli compression for .data/.wasm/.js if available.
    ZIP compression is for upload; the extracted files are ordinary files.

Deploy updates by uploading the new versioned assets first and index.html last.
Keep old versioned assets until users have refreshed any cached old index.html.
manifest.json records each runtime file's SHA-256 and uncompressed byte size.

This package contains the game, both hubs, missions, textures, effects and music.
A desktop browser with WebGL 2, keyboard and mouse is required. No cross-origin
isolation headers are needed. Browser saves belong to the site's origin;
kambo.us and deathward.kambo.us have separate saves. Saves are not uploaded.
"""


def digest(data):
    return hashlib.sha256(data).hexdigest()


def package(build, output):
    inputs = {name: (build / name).read_bytes()
              for name in ("index.html", "index.js", "index.wasm", "index.data")}
    if any(not data for data in inputs.values()):
        raise ValueError("The browser build contains an empty runtime file")
    if not inputs["index.wasm"].startswith(b"\0asm"):
        raise ValueError("index.wasm is not a WebAssembly binary")
    names = {name: f"deathward.{digest(inputs[name])[:20]}.{name.split('.')[-1]}"
             for name in ("index.js", "index.wasm", "index.data")}
    # Emscripten consults locateFile for both its early asset download and WASM.
    # Resolve against the hosting document, never a domain or root-relative path.
    mapping = json.dumps({name: names[name] for name in ("index.wasm", "index.data")},
                         separators=(",", ":"))
    loader = ("<script>Module.locateFile=(function(){const base=new URL('.',document.baseURI);"
              f"const files={mapping};return file=>new URL(files[file]||file,base).href;"
              "})();</script>\n"
              f'<script async src="./{names["index.js"]}"></script>')
    html, replacements = re.subn(
        r'<script\b[^>]*\bsrc\s*=\s*(?:"index\.js"|\'index\.js\'|index\.js)(?=[\s>])[^>]*>\s*</script>',
        lambda _: loader, inputs["index.html"].decode("utf-8"))
    if replacements != 1:
        raise ValueError("Expected exactly one Emscripten index.js script in index.html; rebuild first")
    files = {names[name]: inputs[name] for name in names}
    files["index.html"] = html.encode("utf-8")
    manifest = {"format": 1, "files": {
        name: {"bytes": len(data), "sha256": digest(data)}
        for name, data in sorted(files.items())}}
    files["manifest.json"] = (json.dumps(manifest, indent=2) + "\n").encode("utf-8")
    files["README.txt"] = UPLOAD_GUIDE.encode("utf-8")
    output.mkdir(parents=True, exist_ok=True)
    # Only replace this script's generated bundle; leave other dist files alone.
    with tempfile.TemporaryDirectory(prefix=".deathward-package-", dir=output) as temp:
        staging = Path(temp)
        site = staging / "deathward-web"
        site.mkdir()
        archive = staging / "deathward-web.zip"
        with zipfile.ZipFile(archive, "w", compression=zipfile.ZIP_DEFLATED, compresslevel=6) as bundle:
            for name, data in sorted(files.items()):
                (site / name).write_bytes(data)
                entry = zipfile.ZipInfo(name, date_time=(2020, 1, 1, 0, 0, 0))
                entry.external_attr = 0o100644 << 16
                entry.compress_type = zipfile.ZIP_DEFLATED
                bundle.writestr(entry, data, compresslevel=6)
        destination = output / "deathward-web"
        if destination.exists():
            shutil.rmtree(destination)
        site.rename(destination)
        archive.replace(output / "deathward-web.zip")
    archive = output / "deathward-web.zip"
    print(f"Upload package: {archive} ({archive.stat().st_size / 1024**2:.1f} MiB)")
    print(f"Unpacked site: {output / 'deathward-web'}")
    print("Upload its contents to either a domain root or a subdirectory.")


if __name__ == "__main__":
    root = Path(__file__).resolve().parents[1]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--build-dir", type=Path, default=root / "build-web")
    parser.add_argument("--output", type=Path, default=root / "dist")
    args = parser.parse_args()
    try:
        package(args.build_dir.resolve(), args.output.resolve())
    except (OSError, ValueError) as error:
        parser.exit(1, f"Packaging failed: {error}\nBuild first with scripts/build-web.sh\n")
