#!/usr/bin/env python3
"""Check source joins and derived facts; this does not test Isaac gameplay."""
import collections,csv,hashlib,json,re,shlex
import collect as c

def main():
    path=c.ROOT/'docs/research/isaac-mechanics-reference.json';d=json.loads(path.read_text())
    rows=d['records'];by={r['record_key']:r for r in rows};checks=[]
    def check(label,condition):
        assert condition,label
        checks.append(label)
    check('All 2,443 local definition rows retained',len(rows)==2443)
    check('Unique typed record keys, including duplicate internal ID',len(by)==len(rows))
    for group,count in [('collectible',721),('trinket',188),('card',98),('pill',50),('internal',49),('entity',1337)]:
        check(f'{group}: {count} rows',sum(r['record_key'].startswith(group+':') for r in rows)==count)
    check('Effects are not classified as NPC bosses',all(r['id']<1000 for r in rows if r.get('group')=='boss'))
    check('Null item rows do not inherit collectible metadata',all(not r['metadata'] for r in rows if r['record_key'].startswith('internal:')))
    check('All 50 pill IDs joined to the effect table',all(r.get('pill_effect',{}).get('id')==str(r['id']) for r in rows if r['record_key'].startswith('pill:')))
    check('Bombs Are Key retains normal and horse-pill rules','50%' in by['pill:3']['pill_effect']['horse_pill_effect'])
    check('Historical ID 474 resolves to Broken Glass Cannon',all(m['name']=='Broken Glass Cannon' for m in by['collectible:474']['wiki_matches']))
    check('Drowned Hive inherits family ID 22, not Mulligan ID 16',by['entity:22.1.0']['wiki_matches'][0]['id']==22)
    check('Internal XML name witness is displayed as Mother',by['entity:912.0.0']['display_name']=='Mother')
    check('Coal remnant tuples do not inherit the A Lump of Coal item article',all(
        by[f'entity:33.11.{subtype}']['wiki_pages']==['Rock Spider'] and
        by[f'entity:33.11.{subtype}']['behavior_section_refs'] for subtype in range(4)))
    dragon=by['entity:25.3.1']
    check('Dragon Fly X alias selects the diagonal-fire subtype section',dragon['display_name']=='Dragon Fly X'
        and dragon['xml']['name']=='#DRAGON_FLY_X' and dragon['behavior_section_refs']
        and all(d['articles'][s['page']]['sections'][s['section']]['heading']=='Dragon Fly X'
                for s in dragon['behavior_section_refs']))
    dip=by['entity:217.0.0']['hp_by_stage']
    check('Dip Stage HP worked examples',dip['1']==4 and dip['8']==9.4 and dip['12']==11)
    check('Stage IV/V plateau and X+ cap',all(r['hp_by_stage']['4']==r['hp_by_stage']['5'] and r['hp_by_stage']['10']==r['hp_by_stage']['13'] for r in rows if 'hp_by_stage' in r))
    check('All behavior section pointers are valid',all(x['page'] in d['articles'] and 0<=x['section']<len(d['articles'][x['page']]['sections']) for r in rows for x in r['behavior_section_refs']))
    check('All article links resolve',all(t in d['articles'] for r in rows for t in r['wiki_pages']))
    check('Each wiki article retains revision attribution',all(a.get('revision') and a.get('revision_url') and a.get('license')=='CC BY-SA 4.0' for a in d['articles'].values()))
    check('Interaction source revisions match',all(d['articles'][x['page']]['revision']==x['source_revision'] for x in d['interactions']))
    check('Interaction typed ID links resolve',all(k in by for x in d['interactions'] for t in x['targets'] for k in t['record_keys']))
    check('All 53 STB libraries accounted for',len(d['room_libraries'])==53)
    runtime=set()
    for file in (c.ROOT/'assets/mechanics').glob('*.mechanics'):
        for line in file.read_text().splitlines():
            fields=shlex.split(line,comments=True)
            if fields and fields[0]=='monster':
                runtime.add('.'.join(str(int(x)) for x in (fields[1].split('.')+['0','0'])[:3]))
    check('Every current runtime adaptation audited by exact tuple',bool(runtime) and
        set(d['deathward_audit']['entries'])==runtime and d['deathward_audit']['catalog_entries']==len(runtime))
    check('Packed-ID collision demonstrated',912*10000+100*100==913*10000 and 'entity:912.100.0' in by)
    check('Native AI timing unknowns not invented',all(all(v is None for v in r['port_contract']['parameters_not_established'].values()) for r in rows if r.get('group') in ('enemy','boss')))
    for entry in d['provenance']['local_xml']:
        check('XML hash '+entry['file'],hashlib.sha256((c.ROOT/entry['file']).read_bytes()).hexdigest()==entry['sha256'])
    for entry in d['provenance']['sources']:
        check('Cached source hash '+entry['cached_file'],hashlib.sha256((c.ROOT/entry['cached_file']).read_bytes()).hexdigest()==entry['sha256'])
    manifest=json.loads(path.with_name('isaac-mechanics-reference-manifest.json').read_text())
    for entry in manifest['files']:
        check('Artifact hash '+entry['file'],hashlib.sha256((c.ROOT/entry['file']).read_bytes()).hexdigest()==entry['sha256'])
    with path.with_name('isaac-implementation-backlog.csv').open() as f:backlog=list(csv.DictReader(f))
    check('All 1,710 relevant definitions in implementation review queue',len(backlog)==1710 and len({r['record_key'] for r in backlog})==1710)
    missing=[]
    for chapter in d['analysis']:
        for title in chapter['sources']:
            seen=set();name=title
            while name in d['aliases'] and name not in seen:seen.add(name);name=d['aliases'][name]
            if name not in d['articles']:missing.append(title)
    check('All authored source dossier links collected',not missing)
    report={'status':'passed','checks':len(checks),'scope':'Data integrity and derived facts only; no new Isaac gameplay measurements.',
       'assertions':checks,'records':len(rows),'wiki_articles':len(d['articles']),
       'npc_rows_with_context':sum(bool(r['wiki_pages']) for r in rows if r.get('group') in ('enemy','boss')),
       'unlinked_npcs':[r for r in d['unmatched_records'] if r['group'] in ('enemy','boss')]}
    (c.ROOT/'docs/research/isaac-mechanics-validation.json').write_text(json.dumps(report,indent=2)+'\n')
    print(f'PASS: {len(checks)} data/source integrity assertions; {len(rows)} definitions; {len(backlog)} implementation-review rows.')

if __name__=='__main__':main()
