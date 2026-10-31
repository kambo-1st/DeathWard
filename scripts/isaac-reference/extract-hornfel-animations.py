#!/usr/bin/env python3
"""Preserve Hornfel's animation/event metadata, without importing sprite art.

Uses the already documented ARCH000/2 extraction method and validates both the
installed archive SHA-256 and each extracted entry's length/checksum.
"""
import hashlib
import json
import struct
import xml.etree.ElementTree as ET
import zlib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
INSTALL = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth')
REFERENCE = ROOT / 'reference/isaac-repentance-1.7.9b'
OUT = ROOT / 'docs/reports/isaac-enemy-port/hornfel/animations'
NAMES = ['resources-dlc3/gfx/' + name for name in [
    '906.000_hornfel.anm2', '965.000_minecart.anm2', '965.001_hornfel minecart.anm2',
    'grid/door_10_bossroomdoor_rails.anm2', 'grid/grid_rail.anm2']]


def namehash(name):
    a, b = 5381, 0x5bb2220e
    for c in name.lower().encode():
        a = (a * 33 + c) & 0xffffffff
        b = ((b ^ c) * 0x1000193) & 0xffffffff
    return a, b


def checksum(data):
    value, buf = 0xababeb98, bytearray(512)
    for start in range(0, len(data), 512):
        chunk = data[start:start + 512]
        buf[:len(chunk)] = chunk
        for offset in range(0, len(chunk), 4):
            value = ((value >> 1) + (value << 31) + struct.unpack_from('<I', buf, offset)[0]) & 0xffffffff
    return value


def main():
    archive = 'resources/packed/repentance.a'
    expected = next(r for r in json.loads((REFERENCE / 'manifests/source-manifest.json').read_text()) if r['path'] == archive)
    hasher = hashlib.sha256()
    with (INSTALL / archive).open('rb') as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b''):
            hasher.update(chunk)
        assert hasher.hexdigest() == expected['sha256'], 'Archive differs from preserved baseline'
        stream.seek(0)
        header = stream.read(14)
        assert header[:8] == b'ARCH000\x02'
        index, count = struct.unpack_from('<IH', header, 8)
        assert index + count * 20 == expected['bytes']
        stream.seek(index)
        entries = [struct.unpack('<5I', stream.read(20)) for _ in range(count)]
        wanted = {namehash(name): name for name in NAMES}
        records = []
        OUT.mkdir(parents=True, exist_ok=True)
        for a, b, position, length, crc in entries:
            name = wanted.get((a, b))
            if name is None:
                continue
            stream.seek(position)
            data = bytearray()
            while True:
                flags, = struct.unpack('<I', stream.read(4))
                size = flags & 0x7fffffff
                assert 0 < size <= 2048 and not (size == 1024 and not flags >> 31), 'Unsupported archive block'
                inflater = zlib.decompressobj(-15)
                data.extend(inflater.decompress(stream.read(size)))
                assert not inflater.unused_data and not inflater.unconsumed_tail
                if flags >> 31:
                    break
            assert len(data) == length and checksum(data) == crc, name
            xml = ET.fromstring(data)
            path = OUT / Path(name).name
            path.write_bytes(data)
            records.append({'source_path': name, 'bytes': length, 'checksum': hex(crc),
                            'sha256': hashlib.sha256(data).hexdigest(), 'artifact': str(path.relative_to(ROOT)),
                            'info': dict(xml.find('Info').attrib),
                            'events': [dict(e.attrib) for e in xml.findall('./Content/Events/Event')],
                            'animations': [{'attributes': dict(animation.attrib),
                                            'triggers': [dict(t.attrib) for t in animation.findall('./Triggers/Trigger')]}
                                           for animation in xml.findall('./Animations/Animation')]})
    assert {r['source_path'] for r in records} == set(NAMES), 'Requested animation metadata missing from archive'
    (OUT / 'manifest.json').write_text(json.dumps({'baseline': 'Repentance 1.7.9b', 'archive': archive,
        'archive_sha256': expected['sha256'], 'files': records,
        'scope': 'Source animation/event metadata only. Sprite artwork is not extracted or imported into DeathWard.'}, indent=2) + '\n')
    print('Preserved', len(records), 'checksum-verified animation metadata files')


if __name__ == '__main__':
    main()
