#!/usr/bin/env python3
"""Build an evidence-based enemy port review queue. Never enables runtime content."""
from pathlib import Path
import collections
import csv
import hashlib
import json
import re
import shlex
import xml.etree.ElementTree as ET

ROOT = Path(__file__).resolve().parents[2]
DATA = ROOT / 'docs/research'
LOCAL = ROOT / 'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3'
REFERENCE = DATA / 'isaac-mechanics-reference.json'
BANDS = ['Outer Washes', 'Broken Quarry', 'Abandoned Works', 'Storm Cut']
# DeathWard design proposal, not an assertion that Isaac uses these four groups.
# Alternate-path opening enemies enter the second band pending difficulty review.
STAGE_BAND = {
    'basement': 0, 'cellar': 0, 'burning basement': 0,
    'caves': 1, 'catacombs': 1, 'flooded caves': 1,
    'downpour': 1, 'dross': 1, 'mines': 1, 'ashpit': 1,
    'depths': 2, 'necropolis': 2, 'dank depths': 2,
    'mausoleum': 2, 'gehenna': 2,
    'womb': 3, 'utero': 3, 'scarred womb': 3, 'corpse': 3,
    'sheol': 3, 'cathedral': 3, 'dark room': 3, 'chest': 3,
}
SPECIAL_STAGES = {'blue womb', 'the void', 'home', 'backwards', 'the shop', 'ultra greed'}
NORMAL_STAGES = set(STAGE_BAND) - {'downpour', 'dross', 'mines', 'ashpit', 'mausoleum', 'gehenna', 'corpse'}


def normalize(value):
    return re.sub('[^a-z0-9]', '', value.lower())


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def runtime_monsters():
    result = {}
    for path in sorted((ROOT / 'assets/mechanics').glob('*.mechanics')):
        for line, text in enumerate(path.read_text().splitlines(), 1):
            fields = shlex.split(text, comments=True)
            if fields and fields[0] == 'monster':
                key = '.'.join((fields[1].split('.') + ['0', '0'])[:3])
                result[key] = dict(name=fields[2], behavior=fields[16], natural=bool(int(fields[15])),
                                   hazard=bool(int(fields[14])), source=str(path.relative_to(ROOT)), line=line)
    return result


def runtime_encounters():
    result = collections.defaultdict(list)
    for path in sorted((ROOT / 'assets/mechanics').glob('*.mechanics')):
        for line, text in enumerate(path.read_text().splitlines(), 1):
            f = shlex.split(text, comments=True)
            if f and f[0] == 'encounter' and int(f[6]) > 0:
                key = '.'.join((f[5].split('.') + ['0', '0'])[:3])
                for band in range(int(f[1]), int(f[2]) + 1):
                    result[key].append(dict(band=band, pattern=f[3], role=f[4], weight=int(f[6]),
                        cost=int(f[7]), maximum=int(f[8]), members=int(f[9]) if len(f)>9 else 1,
                        floor_variant=f[10] if len(f)>10 else 'any', source=str(path.relative_to(ROOT)), line=line))
    return result


def runtime_replacements(encounters):
    result = collections.defaultdict(list)
    rules = []
    for path in sorted((ROOT / 'assets/mechanics').glob('*.mechanics')):
        for line, text in enumerate(path.read_text().splitlines(), 1):
            f = shlex.split(text, comments=True)
            if not f or f[0] != 'replace_monster' or int(f[6]) == 0:
                continue
            source_id = '.'.join((f[1].split('.') + ['0', '0'])[:3])
            target_id = '.'.join((f[2].split('.') + ['0', '0'])[:3])
            first, last = int(f[3]), int(f[4])
            route = dict(source_monster=source_id, first_band=first, last_band=last,
                floor_variant=f[5], chance_basis_points=int(f[6]), extra_reserved_threat=int(f[7]),
                phase=int(f[8]) if len(f)>8 else 0, source_pool_present=False,
                source=str(path.relative_to(ROOT)), line=line)
            result[target_id].append(route)
            rules.append((source_id, target_id, route))
    # Explicit phases can replace a target introduced by an earlier pass. A
    # same-phase rule must never make its own target recursively reachable.
    reachable = collections.defaultdict(set)
    for key, pools in encounters.items():
        for pool in pools:
            variants = ('standard', 'scorched', 'flooded') if pool['floor_variant']=='any' else (pool['floor_variant'],)
            reachable[key].update((pool['band'], v) for v in variants)
    for phase in range(4):
        after = collections.defaultdict(set, {key:set(contexts) for key,contexts in reachable.items()})
        for source_id, target_id, route in rules:
            if route['phase'] != phase:
                continue
            contexts = {c for c in reachable[source_id] if route['first_band']<=c[0]<=route['last_band'] and
                (route['floor_variant']=='any' or route['floor_variant']==c[1])}
            route['source_pool_present'] = bool(contexts)
            after[target_id].update(contexts)
            if route['chance_basis_points']==10000:
                after[source_id].difference_update(contexts)
        reachable = after
    return result


def boss_pools():
    # The archived file has a malformed final closing tag. Normalize in memory only.
    source = (LOCAL / 'bosspools.xml').read_text()
    if not source.rstrip().endswith('</bosspools>'):
        source = source.rsplit('</pool>', 1)[0] + '</bosspools>'
    pools = collections.defaultdict(list)
    for pool in ET.fromstring(source):
        for boss in pool:
            pools[int(boss.attrib['id'])].append(dict(pool=pool.attrib['name'].lower(),
                                                      weight=float(boss.attrib.get('weight', 1))))
    return pools


def runtime_boss_routes():
    bosses, components = collections.defaultdict(list), collections.defaultdict(list)
    def key(text):
        return '.'.join((text.split('.') + ['0', '0'])[:3])
    for path in sorted((ROOT / 'assets/mechanics').glob('*.mechanics')):
        for line, text in enumerate(path.read_text().splitlines(), 1):
            f = shlex.split(text, comments=True)
            if not f:
                continue
            at = dict(source=str(path.relative_to(ROOT)), line=line)
            if f[0] == 'boss_pool' and int(f[4]) > 0:
                bosses[key(f[2])].append(dict(band=int(f[1]), form=f[3], weight=int(f[4]),
                                             variant=f[5] if len(f)>5 else None, **at))
            elif f[0] == 'component_bounce':
                components[key(f[1])].append(dict(owner=key(f[2]), controller='bounce', **at))
    for routes in components.values():
        for route in routes:
            route['owner_pool_present'] = route['owner'] in bosses
    return bosses, components


def classify_review(record, current, conflict):
    if 'Cut Content' in record['wiki_pages']:
        return 'cut_or_unused_review'
    if record['id'] in (17, 33, 292, 802, 964):
        return 'environment_npc_item_dependency_review'
    if record['group'] == 'boss':
        if record['id'] in range(46, 53) or record['key'] == '81.1.0':
            return 'miniboss_or_component_review'
        return 'boss_encounter_or_component_review'
    if current and not conflict and (not current['natural'] or current['hazard']):
        return 'existing_support_or_hazard_review'
    return 'enemy_or_component_review'


def main():
    runtime_bosses, runtime_components = runtime_boss_routes()
    source = json.loads(REFERENCE.read_text())
    current = runtime_monsters()
    encounters = runtime_encounters()
    replacements = runtime_replacements(encounters)
    pools = boss_pools()
    records = [r for r in source['records'] if r.get('group') in ('enemy', 'boss')]
    source_names = {normalize(r['name']): r['key'] for r in records}
    out = []
    for r in sorted(records, key=lambda r: (r['id'], r['variant'], r['subtype'])):
        existing = current.get(r['key'])
        conflict = bool(existing and normalize(existing['name']) not in
                        {normalize(r['name']), normalize(r['display_name'])} and
                        source_names.get(normalize(existing['name'])) not in (None, r['key']))
        alias_review = bool(existing and not conflict and normalize(existing['name']) not in
                            {normalize(r['name']), normalize(r['display_name'])})
        stage_evidence, ignored = [], []
        for filename, presence in sorted(r['room_library_presence'].items()):
            label = re.sub(r'^\d+\.', '', Path(filename).stem)
            reason = None
            if '/greed/' in filename:
                reason = 'Separate Greed-mode evidence; do not merge into standard spawn weights.'
            elif not presence['positive_weight_templates']:
                reason = 'No positive-weight template evidence.'
            elif label in SPECIAL_STAGES:
                reason = 'Special encounter or mode library; requires dedicated encounter rules.'
            elif label not in STAGE_BAND:
                reason = 'Unmapped/special/unused library; needs eligibility review.'
            entry = dict(file=filename, source_stage=label, **presence)
            if reason:
                ignored.append(dict(**entry, reason=reason))
            else:
                stage_evidence.append(dict(**entry, proposed_band=STAGE_BAND[label],
                                          source_path='main' if label in NORMAL_STAGES else 'alternate'))
        boss_id = int(r['xml']['bossID']) if r['xml'].get('bossID') else None
        pool_evidence = [dict(**p, proposed_band=STAGE_BAND.get(p['pool'])) for p in pools.get(boss_id, [])]
        # bossID membership is evidence for a family, not proof this row is its root.
        mapped_pools = [p for p in pool_evidence if p['weight'] > 0 and p['proposed_band'] is not None]
        basis = 'boss_pool_family_review' if mapped_pools else 'positive_room_template_review'
        candidates = sorted({p['proposed_band'] for p in mapped_pools} if mapped_pools else
                            {s['proposed_band'] for s in stage_evidence})
        role = classify_review(r, existing, conflict)
        if role in ('cut_or_unused_review', 'environment_npc_item_dependency_review'):
            proposed = None
            basis = 'classification_before_placement'
        elif candidates:
            proposed = candidates[0]
        else:
            proposed = None
            basis = 'parent_or_scripted_encounter_review_required'
        article_refs = [dict(title=t, url=source['articles'][t]['revision_url'])
                        for t in r['wiki_pages'] if t in source['articles']]
        out.append(dict(
            record_key=r['record_key'], id=r['key'], source_name=r['name'],
            display_name=r['display_name'], source_group=r['group'], boss_pool_id=boss_id,
            source_base_hp=r['xml'].get('baseHP'), source_stage_hp=r['xml'].get('stageHP'),
            current_runtime=existing, identity_conflict=conflict, naming_alias_review=alias_review,
            current_floor_pools=encounters.get(r['key'], []),
            current_replacement_routes=replacements.get(r['key'], []),
            current_boss_pools=runtime_bosses.get(r['key'], []),
            current_component_routes=runtime_components.get(r['key'], []),
            suggested_identity_for_current_name=source_names.get(normalize(existing['name'])) if conflict else None,
            review_role=role, review_approved=False, implementation_status='unverified_existing' if existing else 'not_implemented',
            source_stage_evidence=stage_evidence, separate_mode_or_special_evidence=ignored,
            boss_pool_evidence=pool_evidence, source_band_candidates=candidates,
            proposed_first_band=proposed, proposed_first_band_name=BANDS[proposed] if proposed is not None else None,
            proposal_basis=basis, ordinary_spawn_approved=False,
            has_any_room_templates=bool(r['room_library_presence']), has_article=bool(article_refs),
            wiki_environment_review=[m['fields']['environment'] for m in r['wiki_matches'] if m['fields'].get('environment')],
            article_revisions=article_refs, feature_review_hints=r['feature_triage'],
            feature_note='Keyword triage only. Not an implemented or manually verified capability list.',
            unresolved_native_parameters=list(r['port_contract']['parameters_not_established']),
            required_review=['root/component/hazard/unused classification', 'parent and child dependencies',
                'source-edition behavior contract', 'terrain and arena requirements', 'threat cost and exclusive combinations',
                'visual and damage-window contract', 'source numbers versus DeathWard conversion',
                'stage eligibility and deterministic reachability', 'behavior tests and render capture'],
        ))
    assert len(out) == 653 and len({r['id'] for r in out}) == len(out)
    # Guard the installed identity, including after the original runtime error is fixed.
    # An absent Bloat is honest incomplete work; an eye under its ID is a regression.
    bloat = next(r for r in out if r['id'] == '68.1.0')
    eye = next(r for r in out if r['id'] == '68.10.0')
    assert bloat['source_name'] == 'The Bloat' and eye['source_name'] == 'Peep Eye'
    assert not bloat['current_runtime'] or bloat['current_runtime']['name'] == 'The Bloat'
    assert not eye['current_runtime'] or eye['current_runtime']['name'] == 'Peep Eye'
    selected = set(encounters)
    selected.update(key for key, routes in replacements.items() if any(r['source_pool_present'] for r in routes))
    encounter_source = (ROOT / 'src/combat/FloorEncounters.cpp').read_text()
    for match in re.finditer(r'monsterId\((\d+)(?:,\s*(\d+))?(?:,\s*(\d+))?\)', encounter_source):
        selected.add('.'.join(str(int(n or 0)) for n in match.groups()))
    summary = dict(total_records=len(out), source_groups=dict(collections.Counter(r['source_group'] for r in out)),
        unique_type_ids=len({r['id'].split('.')[0] for r in out}), runtime_definitions=len(current),
        raw_runtime_id_matches=sum(bool(r['current_runtime']) for r in out),
        missing_runtime_ids=sum(not r['current_runtime'] for r in out),
        identity_conflicts=[r['id'] for r in out if r['identity_conflict']],
        naming_alias_reviews=[r['id'] for r in out if r['naming_alias_review']],
        current_progression_selected_ids=sorted(selected, key=lambda s: tuple(map(int, s.split('.')))),
        current_dedicated_boss_ids=sorted(runtime_bosses),
        current_owned_component_ids=sorted(key for key, routes in runtime_components.items()
            if any(route['owner_pool_present'] for route in routes)),
        with_stage_hp=sum(float(r['source_stage_hp'] or 0) != 0 for r in out),
        without_room_templates=sum(not r['has_any_room_templates'] for r in out),
        without_articles=[r['id'] for r in out if not r['has_article']],
        review_roles=dict(collections.Counter(r['review_role'] for r in out)),
        proposed_first_bands=dict(collections.Counter(r['proposed_first_band_name'] or 'review_required' for r in out)),
        accepted_behavior_ports=0, note='Zero verified ports is an audit status, not a claim that existing enemies do nothing.')
    paths = [REFERENCE, LOCAL/'entities2.xml', LOCAL/'bosspools.xml', LOCAL/'stages.xml',
             ROOT/'src/combat/FloorEncounters.cpp', ROOT/'src/world/Expedition.cpp',
             *sorted((ROOT/'assets/mechanics').glob('*.mechanics'))]
    result = dict(schema_version=1, status='analysis_only_not_runtime_content', baseline=source['baseline'],
        wiki_license=source['wiki_license'], wiki_license_url=source['wiki_license_url'],
        wiki_attribution='The Binding of Isaac: Rebirth Wiki contributors; reused environment fields retain revision URLs. Other classifications are authored analysis.',
        method='Exact tuple joins; positive local STB template evidence; bossID joins to local bosspools; explicit DeathWard band proposal. All rows need review.',
        warnings=['A source record is not necessarily a standalone enemy.',
            'STB template counts are not spawn probabilities; special libraries and Greed are kept separate.',
            'Candidate placement is not approval. No item, NPC, body part, unused row or invulnerable hazard is enabled by this file.',
            'bossID is a pool identity, not an entity type, and may be inherited by components.',
            'Missing templates do not imply unused content; absence of an article does not justify exclusion.',
            'Feature tags and environment fields require full article/edition review.',
            'Copying HP or timings does not establish behavior parity.'],
        source_fingerprints={str(p.relative_to(ROOT)): digest(p) for p in paths},
        source_stage_to_proposed_band=STAGE_BAND,
        floor_band_sequences={str(n):[BANDS[min(3, i*4//n)] for i in range(n)] for n in range(4, 9)},
        summary=summary, records=out)
    (DATA/'isaac-enemy-port-plan.json').write_text(json.dumps(result, indent=2, ensure_ascii=False)+'\n')
    columns=['id','source_name','display_name','source_group','current_name','identity_conflict',
        'suggested_identity','review_role','proposed_first_band','proposal_basis','candidate_bands',
        'source_stages','boss_pools','has_article','implementation_status','review_approved','ordinary_spawn_approved']
    with (DATA/'isaac-enemy-port-review.csv').open('w', newline='') as file:
        writer=csv.DictWriter(file, fieldnames=columns);writer.writeheader()
        for r in out:
            writer.writerow(dict(id=r['id'],source_name=r['source_name'],display_name=r['display_name'],
                source_group=r['source_group'],current_name=(r['current_runtime'] or {}).get('name',''),
                identity_conflict=r['identity_conflict'],suggested_identity=r['suggested_identity_for_current_name'] or '',
                review_role=r['review_role'],proposed_first_band=r['proposed_first_band_name'] or 'REVIEW REQUIRED',
                proposal_basis=r['proposal_basis'],candidate_bands=' | '.join(BANDS[b] for b in r['source_band_candidates']),
                source_stages=' | '.join(s['source_stage'] for s in r['source_stage_evidence']),
                boss_pools=' | '.join(p['pool'] for p in r['boss_pool_evidence'] if p['weight']>0),
                has_article=r['has_article'],implementation_status=r['implementation_status'],
                review_approved=False,ordinary_spawn_approved=False))
    print(json.dumps(summary, indent=2))


if __name__ == '__main__':
    main()
