#!/usr/bin/env python3
"""Preserve installed Bouncer animation metadata; never import sprite art."""
import argparse
import hashlib
import importlib.util
import json
import struct
import xml.etree.ElementTree as ET
import zlib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/bouncer/animations'
INSTALL = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth')


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    spec = importlib.util.spec_from_file_location('archive_helpers', ROOT / 'scripts/isaac-reference/extract-hornfel-animations.py')
    helper = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(helper)
    pinned = {r['path']: r for r in json.loads((ROOT / 'reference/isaac-repentance-1.7.9b/manifests/source-manifest.json').read_text())}

    def save(path, data):
        if args.check or path.exists():
            assert path.read_bytes() == data, path
        else:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)

    remaining = {'822.000_bouncer.anm2'}
    files, sources = [], []
    for archive in ['repentance.a', 'afterbirthp.a', 'afterbirth.a', 'animations.a']:
        relative = 'resources/packed/' + archive
        with (INSTALL / relative).open('rb') as stream:
            header = stream.read(14)
            assert header[:8] == b'ARCH000\x02'
            index, count = struct.unpack_from('<IH', header, 8)
            stream.seek(index)
            entries = {entry[:2]: entry for entry in (struct.unpack('<5I', stream.read(20)) for _ in range(count))}
            matches = []
            for name in sorted(remaining):
                for prefix in ['resources-dlc3/gfx/', 'resources-dlc2/gfx/', 'resources-dlc1/gfx/', 'resources/gfx/']:
                    source = prefix + name
                    if helper.namehash(source) in entries:
                        matches.append((name, source, entries[helper.namehash(source)]))
                        break
            if not matches:
                continue
            stream.seek(0)
            hasher = hashlib.sha256()
            for chunk in iter(lambda: stream.read(1024 * 1024), b''):
                hasher.update(chunk)
            digest = hasher.hexdigest()
            if relative in pinned:
                assert digest == pinned[relative]['sha256']
            sources.append({'archive': relative, 'sha256': digest, 'previously_pinned': relative in pinned})
            for name, source, (_, _, position, length, crc) in matches:
                stream.seek(position)
                data = bytearray()
                while True:
                    flags, = struct.unpack('<I', stream.read(4))
                    size = flags & 0x7fffffff
                    assert 0 < size <= 2048 and not (size == 1024 and not flags >> 31)
                    inflater = zlib.decompressobj(-15)
                    data.extend(inflater.decompress(stream.read(size)))
                    assert not inflater.unused_data and not inflater.unconsumed_tail
                    if flags >> 31:
                        break
                assert len(data) == length and helper.checksum(data) == crc
                save(OUT / name, data)
                xml = ET.fromstring(data)
                files.append({'source': source, 'archive': relative, 'path': str((OUT / name).relative_to(ROOT)),
                              'sha256': hashlib.sha256(data).hexdigest(), 'checksum': hex(crc),
                              'info': dict(xml.find('Info').attrib),
                              'events': [dict(e.attrib) for e in xml.findall('./Content/Events/Event')],
                              'animations': [{'attributes': dict(a.attrib), 'triggers': [dict(t.attrib) for t in a.findall('./Triggers/Trigger')]}
                                             for a in xml.findall('./Animations/Animation')]})
                remaining.remove(name)
        if not remaining:
            break
    assert not remaining, remaining
    save(OUT / 'manifest.json', (json.dumps({'baseline': 'Installed Repentance1.7.9b',
         'scope': 'Highest available DLC override before base animation metadata. No sprite artwork imported.',
         'sources': sources, 'files': files}, indent=2) + '\n').encode())
    print(json.dumps({'pass': True, 'animations': len(files), 'check': args.check}))


if __name__ == '__main__':
    main()
