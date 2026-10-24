#!/usr/bin/env python3
"""Summarize locally unpacked Isaac Repentance data without copying room layouts.

Standard library only. Input is read-only; this is not an archive extractor.
STB1 field layout reference:
https://github.com/Basement-Renovator/Basement-Renovator/blob/main/src/roomconvert.py
"""

import argparse
from collections import Counter
import hashlib
import json
import math
from pathlib import Path
import re
import struct
import xml.etree.ElementTree as ET


def histogram(values):
    return {str(k): v for k, v in sorted(Counter(values).items())}


def summarize_stb(path):
    data = path.read_bytes()
    offset = 0

    def take(fmt):
        nonlocal offset
        values = struct.unpack_from(fmt, data, offset)
        offset += struct.calcsize(fmt)
        return values

    magic, count = take('<4sI')
    if magic != b'STB1':
        raise ValueError(f'{path}: expected STB1')
    types, difficulties, shapes, sizes = [], [], [], []
    default_difficulties, weights, stacks = [], [], []
    spawn_rows = 0
    entity_keys = set()
    grid_presence = Counter()
    for _ in range(count):
        kind, variant, subtype, difficulty, name_length = take('<IIIBH')
        if offset + name_length > len(data):
            raise ValueError(f'{path}: truncated room name')
        data[offset:offset + name_length].decode('utf-8')
        offset += name_length
        weight, width, height, shape, doors, stack_count = take('<fBBBBH')
        if not math.isfinite(weight) or weight < 0 or not width or not height:
            raise ValueError(f'{path}: invalid room metadata')
        for _ in range(doors):
            take('<hh?')
        grid_types = set()
        for _ in range(stack_count):
            x, y, entries = take('<hhB')
            for _ in range(entries):
                entity_type, entity_variant, entity_subtype, entity_weight = take('<HHHf')
                if not math.isfinite(entity_weight) or entity_weight < 0:
                    raise ValueError(f'{path}: invalid spawn weight')
                spawn_rows += 1
                entity_keys.add((entity_type, entity_variant, entity_subtype))
                if entity_type >= 1000:
                    grid_types.add(entity_type)
        grid_presence.update(grid_types)
        types.append(kind)
        difficulties.append(difficulty)
        if kind == 1:
            default_difficulties.append(difficulty)
        shapes.append(shape)
        sizes.append(f'{width}x{height}')
        weights.append(weight)
        stacks.append(stack_count)
    if offset != len(data):
        raise ValueError(f'{path}: {len(data) - offset} unparsed trailing bytes')
    return {
        'bytes': len(data), 'sha256': hashlib.sha256(data).hexdigest(),
        'entries': count, 'room_types': histogram(types),
        'difficulties': histogram(difficulties),
        'default_room_difficulties': histogram(default_difficulties),
        'shapes': histogram(shapes), 'stored_sizes': histogram(sizes),
        'zero_weight_entries': sum(w == 0 for w in weights),
        'spawn_rows': spawn_rows, 'distinct_spawn_type_variant_subtype': len(entity_keys),
        'stack_count_range': [min(stacks), max(stacks)] if stacks else [],
        'rooms_with_spawn_type_ge_1000': {str(k): v for k, v in sorted(grid_presence.items())},
        'fully_consumed': True,
    }


def analyze(root):
    inputs, normalizations = {}, []

    def xml(name):
        data = (root / name).read_bytes()
        inputs[name] = {'bytes': len(data), 'sha256': hashlib.sha256(data).hexdigest()}
        try:
            return ET.fromstring(data)
        except ET.ParseError:
            # The installed v1.7.9b file has a mismatched final root closing tag.
            # Repair only the in-memory parsing input, and only this exact shape.
            if name == 'bosspools.xml' and data.lstrip().startswith(b'<bosspools>'):
                fixed, changed = re.subn(rb'</pool>(\s*)$', rb'</bosspools>\1', data)
                if changed == 1:
                    parsed = ET.fromstring(fixed)
                    normalizations.append('bosspools.xml: final </pool> parsed as </bosspools>; input unchanged')
                    return parsed
            raise

    items = xml('items.xml')
    metadata = xml('items_metadata.xml')
    pools = xml('itempools.xml')
    stages = xml('stages.xml')
    bosses = xml('bosspools.xml')
    entities = xml('entities2.xml')
    collectibles = [e for e in items if e.tag in ('passive', 'active', 'familiar')]
    item_by_id = {int(e.attrib['id']): e for e in collectibles}
    item_pools = {}
    for pool in pools:
        rows = list(pool)
        ids = [int(e.attrib['Id']) for e in rows]
        item_pools[pool.attrib['Name']] = {
            'rows': len(rows), 'distinct_ids': len(set(ids)),
            'weight_histogram': histogram(float(e.attrib['Weight']) for e in rows),
            'decrease_by_histogram': histogram(float(e.attrib['DecreaseBy']) for e in rows),
            'remove_on_histogram': histogram(float(e.attrib['RemoveOn']) for e in rows),
            'ids_without_collectible_definition': sorted(set(ids) - item_by_id.keys()),
        }
    boss_pools = {}
    for pool in bosses:
        boss_pools[pool.attrib['name']] = {
            'rows': len(pool), 'attributes': dict(pool.attrib),
            'boss_ids': [int(e.attrib['id']) for e in pool],
            'weight_histogram': histogram(float(e.attrib['weight']) for e in pool),
        }
    room_files = {
        str(p.relative_to(root)): summarize_stb(p)
        for p in sorted((root / 'rooms').rglob('*.stb'))
    }
    if not room_files:
        raise ValueError('No rooms/*.stb files found')
    selected_ids = (2, 3, 52, 68, 69, 104, 114, 118, 149, 153, 169, 182,
                    224, 229, 233, 256, 373, 395, 453, 533, 617, 646, 678, 706)
    return {
        'schema_version': 1,
        'scope': 'Unpacked resources-dlc3; definition entries, not obtainable content or gameplay frequencies',
        'inputs': inputs, 'parsing_normalizations': normalizations,
        'items': {
            'rows_by_tag': histogram(e.tag for e in items),
            'collectible_rows': len(collectibles),
            'distinct_collectible_ids': len(item_by_id),
            'metadata_rows_by_tag': histogram(e.tag for e in metadata),
            'collectible_quality_histogram': histogram(e.attrib.get('quality', 'missing') for e in metadata if e.tag == 'item'),
            'selected_cache_flags': {str(i): item_by_id[i].attrib.get('cache', '') for i in selected_ids if i in item_by_id},
        },
        'item_pools': item_pools,
        'stages': [dict(e.attrib) for e in stages],
        'boss_pools': boss_pools,
        'entities': {
            'rows': len(entities),
            'boss_flagged_rows': sum(e.attrib.get('boss') == '1' for e in entities),
            'distinct_type_ids': len({e.attrib['id'] for e in entities}),
            'rows_with_nonzero_stage_hp': sum(float(e.attrib.get('stageHP', '0')) != 0 for e in entities),
        },
        'rooms': {
            'files': len(room_files),
            'normal_files': sum('/greed/' not in p for p in room_files),
            'greed_files': sum('/greed/' in p for p in room_files),
            'stored_entries': sum(v['entries'] for v in room_files.values()),
            'normal_stored_entries': sum(v['entries'] for p, v in room_files.items() if '/greed/' not in p),
            'greed_stored_entries': sum(v['entries'] for p, v in room_files.items() if '/greed/' in p),
            'by_file': room_files,
        },
    }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--resources', type=Path, required=True, help='Unpacked resources-dlc3 directory')
    parser.add_argument('--output', type=Path, required=True, help='Destination for aggregate JSON')
    args = parser.parse_args()
    root = args.resources.resolve()
    output = args.output.resolve()
    if output == root or root in output.parents:
        parser.error('Output must be outside the input resources directory')
    result = analyze(root)
    output.parent.mkdir(parents=True, exist_ok=True)
    output.write_text(json.dumps(result, indent=2, ensure_ascii=False) + '\n', encoding='utf-8')
    print(f"{result['items']['collectible_rows']} collectible rows; {len(result['item_pools'])} item pools; "
          f"{len(result['boss_pools'])} boss pools; {result['rooms']['stored_entries']} room entries "
          f"in {result['rooms']['files']} fully parsed STB1 files")


if __name__ == '__main__':
    main()
