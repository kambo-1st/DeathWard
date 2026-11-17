#!/usr/bin/env python3
"""Cross-check a captured floor against preserved STB contents and current registries.

Does not resolve random pickup categories, run NPC AI or claim actor acceptance.
"""
import argparse
from collections import Counter
import hashlib
import json
from pathlib import Path
import re
import struct
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / 'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3'
ROLES = {1: 'ordinary', 2: 'shop', 4: 'treasure', 5: 'boss', 7: 'secret',
         8: 'super-secret', 13: 'sacrifice', 29: 'ultra-secret'}
SCOPED = {'10.0.0': 'Existing controller; Frowning-specific production movement/activation acceptance open.',
          '14.0.0': 'Scoped D06 accepted; captured mixed formation is not enabled.',
          '18.0.0': 'Existing Attack Fly; D13b accepted Duke offspring, not full standalone actor/formation acceptance.',
          '67.0.0': 'Scoped D13b accepted; captured initial fly/obstacle arrangement is not enabled.'}


def read_stb(path):
    data = path.read_bytes()
    magic, count = struct.unpack_from('<4sI', data)
    assert magic == b'STB1'
    offset = 8

    def take(fmt):
        nonlocal offset
        value = struct.unpack_from(fmt, data, offset)
        offset += struct.calcsize(fmt)
        return value

    rows = []
    for _ in range(count):
        kind, variant, subtype, difficulty, size = take('<IIIBH')
        name = data[offset:offset + size].decode()
        offset += size
        weight, width, height, shape, doors, slots = take('<fBBBBH')
        allowed = [take('<hh?') for _ in range(doors)]
        entries = []
        for _ in range(slots):
            x, y, n = take('<hhB')
            entries.append(dict(x=x, y=y, choices=[dict(zip(('type', 'variant', 'subtype', 'weight'), take('<HHHf'))) for _ in range(n)]))
        rows.append(dict(type=kind, variant=variant, subtype=subtype, difficulty=difficulty,
                         shape_metadata_only=shape, width_metadata_only=width, height_metadata_only=height,
                         title=name, source_weight=weight, allowed_doors=allowed, slots=entries,
                         source_file=str(path.relative_to(ROOT))))
    assert offset == len(data), path
    return rows, dict(path=str(path.relative_to(ROOT)), sha256=hashlib.sha256(data).hexdigest(), templates=count)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--snapshot', type=Path, required=True)
    parser.add_argument('--output', type=Path, required=True)
    args = parser.parse_args()
    if args.output.exists():
        parser.error('Output must be new')
    capture = json.loads(args.snapshot.read_text())
    assert capture['executable_sha256'] == '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'
    assert (capture['stage'], capture['stage_type'], capture['difficulty']) == (1, 0, 0), 'Normal Basement I required'
    assert any(a['type'] == 1 and a.get('character') == 0 for a in capture['current_room_actors']), 'ordinary Isaac required'
    pool, sources = [], []
    for name in ('00.special rooms.stb', '01.basement.stb', '13.blue womb.stb'):
        rows, manifest = read_stb(SOURCE / 'rooms' / name)
        pool.extend(rows)
        sources.append(manifest)
    registry = {}
    for file in (ROOT / 'assets/mechanics').glob('*.mechanics'):
        for line in file.read_text().splitlines():
            match = re.match(r'monster (\d+\.\d+\.\d+) "([^"]+)"', line)
            if match:
                registry[match[1]] = dict(name=match[2], file=str(file.relative_to(ROOT)))
    names = {}
    for entry in ET.parse(SOURCE / 'entities2.xml').getroot().iter('entity'):
        key = '.'.join(entry.get(k, '0') for k in ('id', 'variant', 'subtype'))
        names.setdefault(key, entry.get('name', key).lstrip('#').replace('_', ' ').title())
    audited, enemies, unresolved = [], Counter(), []
    for room in capture['rooms']:
        config = room['config']
        matches = [r for r in pool if all(r[k] == config[k] for k in ('type', 'variant', 'subtype', 'difficulty', 'shape_metadata_only', 'slots'))]
        assert len(matches) == 1, (room['list_index'], len(matches))
        source = matches[0]
        counts = Counter()
        for slot in config['slots']:
            for entry in slot['choices']:
                identity = '.'.join(str(entry[k]) for k in ('type', 'variant', 'subtype'))
                counts[identity] += 1
                if 10 <= entry['type'] < 1000 and entry['type'] != 17:
                    enemies[identity] += 1
                if entry['type'] == 5 and (entry['variant'] == 150 or entry['subtype'] == 0):
                    unresolved.append(dict(native_list_index=room['list_index'], x=slot['x'], y=slot['y'], template_identity=identity,
                                           reason='Native factory/category/pool result is not established by this unvisited config slot.'))
        audited.append(dict(native_list_index=room['list_index'], native_grid_index=room['grid_index'], dimension=room['dimension'],
                            role=ROLES.get(config['type'], str(config['type'])), template=f"{config['type']}.{config['variant']}.{config['subtype']}",
                            source=source, spawn_seed=room['spawn_seed'], content_counts=dict(sorted(counts.items())),
                            singleton_slots=all(len(s['choices']) == 1 for s in config['slots']), exact_stb_content_match=True))
    actors = [dict(identity=identity, name=names.get(identity, identity), occurrences=count,
                   registry=registry.get(identity), scoped_acceptance=SCOPED.get(identity, 'Not enabled in the current regular-enemy registry; separate actor delivery required.'))
              for identity, count in sorted(enemies.items())]
    result = dict(snapshot=str(args.snapshot), snapshot_sha256=hashlib.sha256(args.snapshot.read_bytes()).hexdigest(),
                  source_files=sources, verified_profile='Repentance1.7.9b / Normal / Basement I / Isaac character0',
                  descriptor_count=len(audited), role_counts=dict(Counter(r['role'] for r in audited)),
                  exact_stb_matches=len(audited), total_spawn_slots=sum(len(r['source']['slots']) for r in audited),
                  rooms=audited, actor_dependencies=actors, unresolved_pickup_slots=unresolved,
                  full_floor_gameplay_accepted=False, source_shapes_and_connections_are_metadata_only=True,
                  limits=['Registry presence is not actor acceptance.', 'Candidate counts are not full live factory/offspring/champion counts.',
                          'No current production complete-room registry entry covers these captured combat templates.',
                          'Room count is descriptor count, not floor-cell area or a procedural-count proof.',
                          'Unvisited item identities, prices, shop unlock level, source starting inventory and rewards remain unverified.'])
    args.output.write_text(json.dumps(result, indent=2) + '\n')
    print(json.dumps(dict(exact_stb_matches=len(audited), spawn_slots=result['total_spawn_slots'], role_counts=result['role_counts'],
                         actor_dependencies=[{'identity': a['identity'], 'name': a['name'], 'registry_present': a['registry'] is not None} for a in actors],
                         unresolved_pickup_slots=len(unresolved))))


if __name__ == '__main__':
    main()
