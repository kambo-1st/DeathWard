#!/usr/bin/env python3
"""Validate the maintained enemy-port checklist; never infer completed ports.

--init creates pending rows once. --check reads only. --csv exports the current
human-maintained decisions, separately from the regeneratable analysis queue.
"""
import argparse
import collections
import csv
import hashlib
import json
from pathlib import Path
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parents[2]
DATA = ROOT / 'docs/research'
STATUS = DATA / 'isaac-enemy-port-status.json'
REFERENCE = DATA / 'isaac-mechanics-reference.json'
XML = ROOT / 'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3/entities2.xml'
GATES = ('behavior', 'reachability', 'visual_linux', 'visual_wasm', 'balance', 'performance')
DISPOSITIONS = {'pending', 'ordinary', 'boss', 'component', 'hazard', 'environment', 'item_dependency', 'dedicated', 'excluded'}


def require(condition, message):
    if not condition:
        raise ValueError(message)


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def audit_identities(records):
    installed = {}
    for node in ET.parse(XML).getroot():
        a = node.attrib
        if 'id' in a:
            key = '.'.join(a.get(k, '0') for k in ('id', 'variant', 'subtype'))
            require(key not in installed, 'Duplicate installed tuple ' + key)
            installed[key] = a
    for r in records:
        require(installed.get(r['key']) == r['xml'], 'Research XML identity/attributes disagree: ' + r['key'])
    return dict(records=len(records), result='all exact tuples and XML attributes verified',
        source=str(XML.relative_to(ROOT)), sha256=sha(XML), reference_sha256=sha(REFERENCE))


def initialize(source, records):
    require(not STATUS.exists(), 'Refusing to overwrite maintained review decisions')
    audit = audit_identities(records)
    plan = json.loads((DATA / 'isaac-enemy-port-plan.json').read_text())
    current = {r['id']: r['current_runtime'] for r in plan['records']}
    result = dict(schema_version=1, baseline=source['baseline'],
        policy='Maintained review and implementation decisions. Identity verification is not behavioral review. No generic AI or registry presence counts as completion.',
        identity_audit=audit,
        milestones=[dict(number=i, status='in_progress' if i == 1 else 'pending') for i in range(1, 7)],
        records=[dict(id=r['key'], name=r['display_name'], review='pending', disposition='pending',
            evidence=[], parents=[], children=[], contract=None,
            implementation='existing_unverified' if current.get(r['key']) else 'missing',
            runtime=[], placement=[], validation={gate: [] for gate in GATES},
            unresolved=['Review source-edition behavior and eligibility; existing definitions are not parity evidence.'])
            for r in sorted(records, key=lambda r: (r['id'], r['variant'], r['subtype']))])
    STATUS.write_text(json.dumps(result, indent=2, ensure_ascii=False) + '\n')


def validate(source, records, status):
    require(status['schema_version'] == 1 and status['baseline'] == source['baseline'], 'Wrong checklist schema/baseline')
    require(status['identity_audit']['reference_sha256'] == sha(REFERENCE), 'Source changed: review and rerun the identity audit')
    if XML.exists():
        require(sha(XML) == status['identity_audit']['sha256'], 'Installed XML archive fingerprint changed')
    rows = status['records']
    # Preserve historical browser evidence while honoring the user's explicit
    # request to skip WASM. Other acceptance gates cannot be waived here.
    waived = status.get('waived_validation_gates', {})
    require(isinstance(waived, dict) and set(waived) <= {'visual_wasm'}, 'Unsupported validation waiver')
    for gate, decision in waived.items():
        require(decision.get('authority') == 'user' and decision.get('instruction') and decision.get('date'),
                'Validation waiver needs the explicit user instruction and date')
    required_gates = tuple(gate for gate in GATES if gate not in waived)
    ids = {r['key'] for r in records}
    require(len(rows) == len(ids) == 653 and {r['id'] for r in rows} == ids, 'Checklist must account for every exact source tuple once')
    revisions = {a['revision_url'] for a in source['articles'].values()}
    for row in rows:
        key = row['id']
        require(row['review'] in ('pending', 'reviewed'), key + ': invalid review status')
        require(row['disposition'] in DISPOSITIONS, key + ': invalid disposition')
        require(row['implementation'] in ('missing', 'existing_unverified', 'in_progress', 'complete', 'excluded'), key + ': invalid implementation status')
        require(set(row['parents'] + row['children']) <= ids, key + ': unknown dependency tuple')
        for evidence in row['evidence']:
            require(evidence['source'] in revisions or evidence['source'] == status['identity_audit']['source']
                or (ROOT / evidence['source']).is_file(), key + ': unknown evidence source')
            require(evidence.get('supports'), key + ': evidence must say what it establishes')
        if row['review'] == 'reviewed':
            require(row['disposition'] != 'pending' and row['evidence'], key + ': reviewed without classification/evidence')
            if row['disposition'] != 'excluded':
                require(row['contract'] and all(row['contract'].get(k) for k in
                    ('movement', 'targeting', 'attacks', 'vulnerability', 'phases', 'offspring', 'completion', 'adaptations', 'unknowns')),
                    key + ': incomplete reviewed behavior contract')
        if row['disposition'] == 'excluded' or row['implementation'] == 'excluded':
            require(row['review'] == 'reviewed' and row['disposition'] == 'excluded' and row['implementation'] == 'excluded'
                and row.get('exclusion_reason') and row['evidence'], key + ': exclusion requires a reviewed, evidence-backed reason')
        for gate in GATES:
            require(gate in row['validation'], key + ': missing validation gate ' + gate)
            for evidence in row['validation'][gate]:
                require((ROOT / evidence['path']).is_file() and evidence.get('result') in ('pass', 'partial_pass', 'fail')
                    and evidence.get('scope'), key + ': invalid validation evidence')
        if row['implementation'] == 'complete':
            require(row['review'] == 'reviewed' and row['disposition'] != 'excluded' and row['runtime'] and row['placement'], key + ': incomplete implementation/routing')
            require(all(any(e['result']=='pass' for e in row['validation'][gate]) for gate in required_gates),
                    key + ': missing full completion gate; partial smoke checks are insufficient')
            require(not row['unresolved'], key + ': unresolved requirements cannot be complete')
            require(all((ROOT / path).is_file() for path in row['runtime']), key + ': missing implementation file')
            by_id = {r['id']: r for r in rows}
            require(all(by_id[child]['implementation'] == 'complete' for child in row['children']), key + ': unfinished required child')
    return dict(total=len(rows), identity_verified=status['identity_audit']['records'],
        source_archive_available=XML.exists(),
        reviewed=sum(r['review'] == 'reviewed' for r in rows),
        dispositions=dict(collections.Counter(r['disposition'] for r in rows)),
        implementations=dict(collections.Counter(r['implementation'] for r in rows)),
        complete=sum(r['implementation'] == 'complete' for r in rows),
        remaining=sum(r['implementation'] not in ('complete', 'excluded') for r in rows),
        required_validation_gates=required_gates, waived_validation_gates=waived,
        milestones=status['milestones'])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--init', action='store_true')
    parser.add_argument('--check', action='store_true')
    parser.add_argument('--csv', action='store_true')
    parser.add_argument('--audit-identities', action='store_true', help='Recheck local XML, preserving all reviewed decisions')
    args = parser.parse_args()
    source = json.loads(REFERENCE.read_text())
    records = [r for r in source['records'] if r.get('group') in ('enemy', 'boss')]
    if args.init:
        initialize(source, records)
    status = json.loads(STATUS.read_text())
    if args.audit_identities:
        status['identity_audit'] = audit_identities(records)
        validate(source, records, status)
        STATUS.write_text(json.dumps(status, indent=2, ensure_ascii=False) + '\n')
    result = validate(source, records, status)
    if args.csv:
        with (DATA / 'isaac-enemy-port-status.csv').open('w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(['id', 'name', 'review', 'disposition', 'implementation', 'parents', 'children', 'unresolved'])
            for r in status['records']:
                writer.writerow([r['id'], r['name'], r['review'], r['disposition'], r['implementation'],
                    ' | '.join(r['parents']), ' | '.join(r['children']), ' | '.join(r['unresolved'])])
    print(json.dumps(result, indent=2))


if __name__ == '__main__':
    main()
