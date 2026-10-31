#!/usr/bin/env python3
"""Attach component context, room-library evidence and porting work records."""
import collections, hashlib, importlib, json, math, re, shlex, struct, sys
from pathlib import Path
import collect as c
import mwparserfromhell as mw

LOCAL=c.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3'
PARENT_TYPES={17:'Shopkeeper',33:'Fireplace',35:'Mr. Maw',45:'Mom',51:'Envy',65:'War',66:'Death',
 72:'Fistula',73:'Fistula',75:'Blastocyst',76:'Blastocyst',78:"Mom's Heart",79:'Gemini',
 83:'Headless Horseman',84:'Satan',92:'Heart',98:'Mask of Infamy',102:'??? (Boss)',
 202:'Grimace',216:'Mr. Maw',228:'Homunculus',251:'Begotten',266:'Mama Gurdy',272:'Gabriel',
 273:'The Lamb',274:'Mega Satan',275:'Mega Satan',292:'TNT',294:'Ultra Greed',311:'Mr. Maw',
 405:'Rag Man',408:'Hush',409:'Rag Mega',411:'Big Horn',802:'Blood Puppy',830:'Bony',
 865:'Evis',866:'Dark Esau',885:'Dust',903:'The Visage',904:'The Siren',906:'Hornfel',
 909:'The Scourge',910:'Chimera',911:'Rotgut',912:'Mother',919:'Cut Content',921:'Clutch',
 950:'Dogma',951:'The Beast',960:'Home',963:'Frozen Enemy',965:'Minecart',967:'Hornfel'}
EXACT_CONTEXT={'38.2.0':'Ultra Pride','39.22.0':'Vis','72.1.0':'Teratoma','73.1.0':'Teratoma',
 '79.11.0':'Steven','79.12.0':'Blighted Ovum','951.22.0':'Ultra Pestilence',
 '951.31.0':'Ultra War','951.101.0':'Ultra Famine','951.102.0':'Ultra Pestilence',
 '951.103.0':'Ultra War','951.104.0':'Ultra Death'}
CUT_KEYS={'239.100.0','239.101.0','240.2.0','241.1.0','803.0.0','839.0.0',
          '842.0.0','843.0.0','843.1.0','858.0.0','919.0.0','919.1.0'}
FEATURES={
 'damage-modifiers':r'damage|multiplier', 'fire-rate-and-charge':r'tear delay|fire rate|tears up|charge',
 'projectile-transform':r'tear|projectile|laser|knife|brimstone|sword',
 'child-spawns-and-ownership':r'spawn|summon|familiar|split',
 'grid-and-explosions':r'bomb|explos|rock|obstacle|grid',
 'health-and-defenses':r'heart|health|invincib|armor|shield',
 'status-effects':r'poison|burn|freeze|charm|fear|confus|slow',
 'economy-and-pools':r'coin|shop|price|pool|pedestal|reroll|key',
 'room-floor-run-events':r'room|floor|stage|run|reviv',
 'locomotion-and-navigation':r'walk|mov|chase|teleport|jump|charge|burrow|fly|flies',
 'conditional-vulnerability':r'invulner|invincib|vulnerab|exposed|closed|open',
 'randomness':r'chance|random|luck|probab', 'forms-and-transformations':r'transform|form|phase',
}

def stb_presence():
    """Count room templates containing a spawn, not spawn slots or gameplay odds."""
    output=collections.defaultdict(dict);summaries=[]
    for path in sorted((LOCAL/'rooms').rglob('*.stb')):
        blob=path.read_bytes();offset=0
        def take(fmt):
            nonlocal offset
            val=struct.unpack_from(fmt,blob,offset);offset+=struct.calcsize(fmt);return val
        magic,count=take('<4sI');assert magic==b'STB1'
        per_entity=collections.Counter();positive=collections.Counter()
        for _ in range(count):
            kind,var,sub,difficulty,n=take('<IIIBH');offset+=n
            weight,width,height,shape,doors,stacks=take('<fBBBBH')
            for _ in range(doors):take('<hh?')
            keys=set();positive_keys=set()
            for _ in range(stacks):
                x,y,entries=take('<hhB')
                for _ in range(entries):
                    t,v,s,w=take('<HHHf');key=f'{t}.{v}.{s}';keys.add(key)
                    if weight>0 and w>0:positive_keys.add(key)
            per_entity.update(keys);positive.update(positive_keys)
        assert offset==len(blob),(path,offset,len(blob))
        filename=str(path.relative_to(LOCAL))
        summaries.append({'file':filename,'templates':count,'sha256':hashlib.sha256(blob).hexdigest()})
        for key,n in per_entity.items():output[key][filename]={'templates':n,'positive_weight_templates':positive[key]}
    return output,summaries

def pill_rows(pages,plain):
    result={}
    for tag in mw.parse(pages['Pills']['raw']).filter_tags():
        if str(tag.tag)!='tr':continue
        cells=[plain(t.contents) for t in tag.contents.filter_tags(recursive=False) if str(t.tag) in ('td','th')]
        if len(cells)>=6 and re.fullmatch(r'\d+',cells[0].strip()):
            result[int(cells[0])]=dict(zip(['id','name','polarity','class','effect','horse_pill_effect'],cells))
    return result

def main():
    d=json.loads((c.CACHE/'compiled.json').read_text());compiler=importlib.import_module('compile')
    pages,aliases,missing=compiler.load_pages();pills=pill_rows(pages,compiler.plain)
    presence,stbs=stb_presence();articles=d['articles']
    def resolve(title):
        seen=set()
        while title in aliases and title not in seen:seen.add(title);title=aliases[title]
        return title if title in articles else None
    def context(row,title,method):
        title=resolve(title)
        if title:
            row['wiki_pages']=sorted(set(row['wiki_pages']+[title]));row['context_note']=method
            if not row['wiki_matches']:row['wiki_match_method']=method
    dw={}
    mechanics=c.ROOT/'assets/mechanics'
    status='Existing DeathWard adaptation; exact Isaac parity NOT verified; runtime tuning may change these stats.'
    if mechanics.is_dir():
        for path in sorted(mechanics.glob('*.mechanics')):
            for number,line in enumerate(path.read_text().splitlines(),1):
                fields=shlex.split(line,comments=True)
                if fields and fields[0]=='monster':
                    ids=fields[1].split('.');ids+=['0']*(3-len(ids));key='.'.join(ids)
                    dw[key]={'name':fields[2],'motion':fields[3],'attack':fields[4],'shape':fields[5],
                        'catalog_base_hp':float(fields[6]),'behavior':fields[16],
                        'source':str(path.relative_to(c.ROOT)),'line':number,'status':status}
    else: # Also supports reproducing the original analysis against an older checkout.
        source=(c.ROOT/'src/combat/Monsters.cpp').read_text()
        for match in re.finditer(r'\{monsterId\(([^)]+)\),\s*"([^"]+)",\s*M::(\w+),\s*A::(\w+),\s*S::(\w+),\s*([\d.]+)',source):
            ids=[int(n.strip()) for n in match[1].split(',')];ids+= [0]*(3-len(ids));key='.'.join(map(str,ids))
            dw[key]={'name':match[2],'motion':match[3],'attack':match[4],'shape':match[5],'catalog_base_hp':float(match[6]),
                     'source':'src/combat/Monsters.cpp','line':source[:match.start()].count('\n')+1,'status':status}
    if not dw:raise RuntimeError('No DeathWard monster definitions found; update the catalog reader before publishing the audit.')
    for row in d['records']:
        key=row['record_key'];group=key.split(':')[0]
        wiki_name=next((m['name'] for m in row['wiki_matches'] if '[' not in m['name']),None)
        row['display_name']=wiki_name if group=='entity' and wiki_name else row['name']
        if group=='pill':
            context(row,'Pills','Pills effect table, joined by numeric effect ID')
            row['pill_effect']=pills.get(row['id'])
        if group=='entity':
            ident=row['id'];k=row['key'];row['room_library_presence']=presence.get(k,{})
            if k=='25.3.1':
                # Installed #DRAGON_FLY_X / dragonfly2 is the diagonal-fire subtype.
                # The index's generic Dragon Fly label otherwise joins cardinal fire.
                row['display_name']='Dragon Fly X'
                row['wiki_pages']=['Boom Fly']
                row['wiki_matches']=[]
                row['wiki_match_method']='Reviewed XML subtype and Dragon Fly X section'
                row['context_note']='25.3.0 uses cardinal fire lines; 25.3.1 uses diagonal fire lines. Alias resolved against installed XML and pinned article.'
            if ident==33 and row['variant']==11:
                # The title "Coal" redirects to an ITEM. These exact tuples are
                # the hot remnants described in Coal Spider's death behavior.
                row['wiki_pages']=['Rock Spider']
                row['wiki_matches']=[]
                row['wiki_match_method']='Reviewed parent context: Coal Spider remnant, not A Lump of Coal item'
                row['context_note']='Subtype-specific remnant behavior remains unverified; do not infer it from the item article.'
            row['room_library_note']='Presence in stored STB templates, including unused and zero-weight entries; not actual spawn probability. Absence does not mean unused: entities may be spawned by AI/items.'
            if k in CUT_KEYS:context(row,'Cut Content','Wiki documents this as cut/unused content; inclusion in XML does not imply a normal encounter.')
            elif not row['wiki_pages'] and row['group']!='other':
                if k in EXACT_CONTEXT:context(row,EXACT_CONTEXT[k],'Parent encounter context only; component-specific behavior is not established.')
                elif ident in PARENT_TYPES:context(row,PARENT_TYPES[ident],'Parent/family context only; component-specific behavior is not established.')
            if k in dw:row['deathward']=dw[k]
            if row['group'] in ('enemy','boss'):
                row['port_contract']={
                  'classification':'Needs manual eligibility review: standalone creature, boss phase, child, hazard, prop or unused record.',
                  'numeric_policy':'Use local XML as baseline; HP table is derived. Do not interpret mass/friction as measured walking speed.',
                  'state_requirements':['spawn/activation','idle and target acquisition','movement and path selection','attack selection and telegraph','attack emission','recovery','damage/vulnerability','phase transitions','death/children','room-clear participation'],
                  'parameters_not_established':{'walk_speed_world_units_per_second':None,'acceleration':None,'attack_cooldown_seconds':None,'telegraph_seconds':None,'projectile_speed':None,'attack_selection_weights':None,'animation_event_ticks':None},
                  'unknown_parameter_note':'Null means not uniformly extracted into a verified machine-readable field. The linked article may provide individual values; check before measuring.',
                  'required_checks':['fixed seed and RNG calls','line of sight versus alignment','pit/wall/flying navigation','contact and projectile damage','vulnerability during each state','slow/freeze/charm effects','overkill and offspring','phase HP ownership','despawn versus room clear','save/load and re-entry'],
                  'implementation_status':'not ported by this research'}
        if group in ('collectible','trinket','card','pill'):
            row['port_contract']={'implementation_status':'not ported by this research','required_checks':[
                'pickup/use trigger and remove/duplicate behavior','stat changes and recalculation order','charge/cooldown and resource consumption',
                'projectile/damage ownership and proc frequency','room/floor/run duration and save/load','listed positive AND negative interactions',
                'health, character and mode exceptions','random seed stream and pool depletion','visual/audio feedback and bounded child spawning'],
                'unresolved':'No numeric value should be inferred from the item description when it is absent from the selected-version source.'}
        selected=[]
        if group=='entity' and row['id']==33 and row['variant']==11:
            selected.extend(('Rock Spider',i) for i,section in enumerate(articles['Rock Spider']['sections']) if section['heading']=='Coal Spider')
        if group=='entity' and row['key']=='25.3.1':
            selected.extend(('Boom Fly',i) for i,section in enumerate(articles['Boom Fly']['sections']) if section['heading']=='Dragon Fly X')
        for m in row['wiki_matches']:
            for n in m['section_indices']:
                selected.append((m['page'],n))
        if group in ('collectible','trinket','card','pill') or row.get('group')=='boss':
            for title in row['wiki_pages']:
                selected.extend((title,i) for i,s in enumerate(articles[title]['sections']) if not re.search(r'trivia|gallery|footage|achievement|reference',s['heading'],re.I))
        row['behavior_section_refs']=[{'page':t,'section':i} for t,i in dict.fromkeys(selected)]
        text=' '.join(articles[r['page']]['sections'][r['section']]['text'] for r in row['behavior_section_refs'])
        row['feature_triage']=[name for name,pattern in FEATURES.items() if re.search(pattern,text,re.I)]
        row['feature_triage_note']='Keyword-based review hints only, not verified behavior classifications.'
    byname=collections.defaultdict(list)
    for r in d['records']:
        if r['record_key'].split(':')[0] in ('collectible','trinket'):byname[compiler.normal(r['name'])].append(r['record_key'])
    for n,edge in enumerate(d['interactions']):
        edge['id']=f'interaction-{n+1}'
        for target in edge['targets']:
            group='collectible:' if target['kind']=='item' else 'trinket:'
            target['record_keys']=[k for k in byname.get(compiler.normal(target['name']),[]) if k.startswith(group)]
        edge['source_revision']=articles[edge['page']]['revision']
        edge['status']='Documented statement, not a tested pairwise interaction. Nested bullets may depend on parent context; read the article section.'
    coverage=collections.Counter()
    for r in d['records']:
        g=r.get('group',r['record_key'].split(':')[0]);coverage[g+'_total']+=1
        if r['wiki_matches']:coverage[g+'_with_infobox_match']+=1
        if r['wiki_pages']:coverage[g+'_with_article_or_context']+=1
        if r.get('deathward'):coverage[g+'_with_deathward_adaptation']+=1
    d['coverage']=dict(coverage);d['room_libraries']=stbs
    d['unmatched_records']=[{'key':r['record_key'],'name':r['name'],'group':r.get('group',r['record_key'].split(':')[0])} for r in d['records'] if not r['wiki_pages']]
    d['deathward_audit']={'catalog_entries':len(dw),'entries':dw,'exact_parity_verified':0,
      'item_system':('External definitions in assets/mechanics/items.mechanics; composable rules and native hooks, not an implementation of all Isaac collectibles.' if mechanics.is_dir() else '11 Western custom item definitions in src/items/Items.cpp, not an implementation of all Isaac collectibles.'),
      'movement_primitives':13,'attack_primitives':16,
      'warning':('MonsterId now retains type, variant and subtype separately. Definitions and a graph foundation do not establish exact Isaac parity.' if mechanics.is_dir() else 'Composite monsterId packs variant into two decimal digits. New variants >=100 would collide with type digits; migrate to a tuple/struct before importing the full registry.')}
    # Publish factual/derived data and licensed wiki descriptions, not EID descriptions or proprietary assets.
    d.pop('source_inventory',None)
    for a in articles.values():
        for b in a['boxes']:b.pop('raw_fields',None)
    provenance=[]
    for p in sorted(c.CACHE.rglob('*.source.json')):
        if 'venv' in p.parts:continue
        meta=json.loads(p.read_text());meta['cached_file']=str(p.with_name(p.name.removesuffix('.source.json')).relative_to(c.ROOT));provenance.append(meta)
    d['provenance']={'date':'2026-10-25','sources':provenance,'local_xml':[{'file':str(p.relative_to(c.ROOT)),'sha256':hashlib.sha256(p.read_bytes()).hexdigest()} for p in sorted(LOCAL.glob('*.xml'))],
      'wiki_attribution':'The Binding of Isaac: Rebirth Wiki contributors; CC BY-SA 4.0. Article URLs, revision IDs and modification notes accompany this derivative text.',
      'modifications':'Templates converted to readable text; tables flattened; records joined to local XML; derived HP tables, review hints and authored porting analysis added. No guarantee that current wiki behavior exactly matches 1.7.9b.',
      'eid_commit':'8b59d00c6828e333294639ad2b2b6875eae821cb','repentogon_commit':'348e5d0ea277760fc87af420d88e2c7909c9167e',
      'cache_policy':'Raw snapshots and extraction inputs retained locally under reference/ (gitignored); derived report, data and generation scripts are versionable. Back up reference/ separately when moving machines.'}
    (c.CACHE/'enriched.json').write_text(json.dumps(d,ensure_ascii=False,separators=(',',':'))+'\n')
    print(json.dumps(d['coverage'],indent=2));print('pill table rows',len(pills),'room libraries',len(stbs),'DeathWard entries',len(dw))
    print('Unlinked NPC records',[(r['key'],r['name']) for r in d['unmatched_records'] if r['group'] in ('enemy','boss')])

if __name__=='__main__':main()
