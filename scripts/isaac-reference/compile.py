#!/usr/bin/env python3
"""Compile attributed wiki mechanics, local XML facts and implementation coverage.

Wiki-derived text retains its CC BY-SA 4.0 attribution. No game code is generated.
"""
from collections import Counter,defaultdict
from pathlib import Path
import hashlib,html,json,re,sys,unicodedata,urllib.parse
import mwparserfromhell as mw
from mwparserfromhell import nodes as N
import collect as c

DLC={'r':'Repentance','nr':'Before Repentance','r+':'Repentance+', 'nr+':'Before Repentance+',
 'a':'Afterbirth onward','a+':'Afterbirth+ onward','na':'Rebirth only','na+':'Before Afterbirth+',
 'ana+':'Afterbirth only','a+nr':'Afterbirth+ before Repentance','rn':'Repentance','n':'Rebirth'}
DROP={'nav','clear','reflist','references','__toc__','toclimit','ghost','cit','page dlc','header bosses','header pickups',
 'achievement image','image','gallery','transformation table','trinket table','collectible table','entity table','pickup table'}
NAME={'i','item','t','trinket','e','entity','p','pickup','c','character','s','stage','floor','room','m','monster',
      'a','achievement','r','rune','pill','card','ip','item pool','tf','transformation','chal','challenge','wp','wikipedia'}

def plain(value):
    code=value if isinstance(value,mw.wikicode.Wikicode) else mw.parse(str(value))
    out=[]
    for n in code.nodes:
        if isinstance(n,N.Text):out.append(str(n))
        elif isinstance(n,N.Comment):pass
        elif isinstance(n,N.Wikilink):
            target=str(n.title)
            if not target.lower().startswith(('file:','image:','category:')):out.append(plain(n.text or n.title))
        elif isinstance(n,N.ExternalLink):out.append(plain(n.title) if n.title else str(n.url))
        elif isinstance(n,N.Heading):out.append('\n'+plain(n.title)+'\n')
        elif isinstance(n,N.HTMLEntity):out.append(n.normalize())
        elif isinstance(n,N.Tag):
            tag=str(n.tag).lower()
            if tag in ('ref','references','gallery','includeonly','templatestyles'):continue
            if tag in ('br','hr'):out.append('\n')
            elif n.contents is not None:
                body=plain(n.contents)
                if tag in ('td','th'):out.append(' | '+body+' ')
                elif tag in ('tr','table','ul','ol','dl','p','div'):out.append('\n'+body+'\n')
                elif tag=='li':out.append('\n• '+body)
                else:out.append(body)
        elif isinstance(n,N.Template):
            name=str(n.name).strip().lower();params={str(p.name).strip():p.value for p in n.params}
            arg=lambda k,default='':plain(params.get(str(k),default)).strip()
            if name in DROP or name.startswith(('infobox','header','#ev:','nav')):continue
            if name in NAME:out.append(arg(1)+(' / ' if name in ('floor','room') else ''))
            elif name in ('dlc','dlc+'):
                v=arg(1);out.append(' ['+DLC.get(v,'edition '+v)+'] '+arg(2))
            elif name=='dlc-':out.append(' [end edition note] ')
            elif name=='dlc clear':out.append('\n')
            elif name=='dlcalt':
                out.append(' [edition alternatives: '+ '; '.join(('baseline' if k=='1' else DLC.get(k,k))+': '+plain(v).strip() for k,v in params.items())+'] ')
            elif name=='bug':out.append('Bug note: '+' '.join(plain(v) for k,v in params.items() if k.isdigit()))
            elif name=='transformation contribution':out.append('Contributes to the '+arg(1)+' transformation.')
            elif name=='book of virtues synergy':out.append('Book of Virtues interaction: '+arg('description',params.get('1','')))
            elif name=='book of belial synergy':out.append('Book of Belial interaction: '+arg('description',params.get('1','')))
            elif name in ('color','colour'):out.append(arg(2))
            elif name in ('math','nowrap','small','big','note','notes'):out.append(arg(1))
            elif name.startswith(('infobox ','image','sprite','achievement image')):continue
            else:
                vals=[plain(v).strip() for k,v in params.items() if k.isdigit() and str(v).strip()]
                if vals:out.append(' ['+name+': '+'; '.join(vals)+'] ')
        else:out.append(str(n))
    s=''.join(out).replace("'''",'').replace("''",'')
    s=re.sub(r'__[A-Z_]+__','',s)
    s=re.sub(r'[ \t]+',' ',s)
    s=re.sub(r'\n[ \t]+','\n',s)
    s=re.sub(r'(?:\n•\s*){2,}', '\n• ',s)
    return re.sub(r'\n{3,}','\n\n',s).strip()

def normal(s):return re.sub(r'[^a-z0-9]','',unicodedata.normalize('NFKD',s).casefold())
def scalar(s):
    s=s.strip()
    return int(s) if re.fullmatch(r'\d+',s) else None
def url(title,revision=None):
    return 'https://bindingofisaacrebirth.wiki.gg/'+('index.php?oldid='+str(revision) if revision else 'wiki/'+urllib.parse.quote(title.replace(' ','_')))

def load_pages():
    pages={};aliases={};missing=set()
    for path in sorted((c.CACHE/'wiki-api').glob('*.json')):
        if path.name.endswith('.source.json'):continue
        data=json.loads(path.read_text());q=data.get('query',{})
        for row in q.get('normalized',[])+q.get('redirects',[]):aliases[row['from']]=row['to']
        for row in q.get('pages',{}).values():
            if 'revisions' in row:
                rev=row['revisions'][0]
                existing=pages.get(row['title'])
                if existing and existing['revision']>rev['revid']:continue
                pages[row['title']]={'title':row['title'],'pageid':row['pageid'],'revision':rev['revid'],
                   'timestamp':rev['timestamp'],'raw':rev['slots']['main']['*']}
            elif 'missing' in row:missing.add(row['title'])
    return pages,aliases,missing

def parse_article(page):
    code=mw.parse(page['raw']);sections=[{'heading':'Introduction','level':0,'raw':''}]
    boxes=[]
    for node in code.nodes:
        if isinstance(node,N.Heading):sections.append({'heading':plain(node.title),'level':node.level,'raw':''})
        else:
            sections[-1]['raw']+=str(node)
            for t in mw.parse(str(node)).filter_templates():
                name=str(t.name).strip().lower()
                if name.startswith('infobox'):
                    boxes.append({'template':name,'section':len(sections)-1,
                         'fields':{str(p.name).strip().lower():plain(p.value) for p in t.params},
                         'raw_fields':{str(p.name).strip().lower():str(p.value).strip() for p in t.params}})
    for s in sections:s['text']=plain(s['raw'])
    return sections,boxes

def section_range(sections,index):
    if index==0:
        end=next((i for i,s in enumerate(sections) if i>0 and ('variation' in s['heading'].lower() or s['level']==2)),len(sections))
    else:
        level=sections[index]['level'];end=next((i for i in range(index+1,len(sections)) if sections[i]['level']<=level),len(sections))
    return list(range(index,end))

def main():
    inventory=json.loads((c.CACHE/'inventory.json').read_text())
    pages,aliases,missing=load_pages();articles={};box_index=defaultdict(list);name_index=defaultdict(list)
    interactions=[]
    for title,page in pages.items():
        sections,boxes=parse_article(page)
        article={'title':title,'url':url(title),'revision_url':url(title,page['revision']),'revision':page['revision'],
                 'timestamp':page['timestamp'],'license':'CC BY-SA 4.0','attribution':'The Binding of Isaac: Rebirth Wiki contributors',
                 'sections':[{k:v for k,v in s.items() if k!='raw'} for s in sections],'boxes':boxes}
        articles[title]=article
        entity_family_id=None
        for box_number,b in enumerate(boxes):
            f=b['fields'];ident=scalar(f.get('id',''))
            template=b['template'];group=None
            if 'collectible' in template:group='collectible'
            elif 'trinket' in template:group='trinket'
            elif 'monster' in template or 'boss' in template:
                group='entity'
                if ident is not None:entity_family_id=ident
                else:ident=entity_family_id
            elif 'pill' in template:group='pill'
            elif any(x in template for x in ['card','rune','pickup']):group='card'
            b['group']=group;b['id']=ident;b['name']=f.get('name',title)
            b['variant']=scalar(f.get('variant','0'));b['subtype']=scalar(f.get('subtype','0'))
            b['section_indices']=section_range(sections,b['section'])
            ref={'page':title,'box':box_number,'group':group,'fields':f,'section_indices':b['section_indices'],
                 'name':b['name'],'variant':b['variant'],'subtype':b['subtype'],'id':ident,'template':template}
            name_index[normal(b['name'])].append(ref)
            if group and ident is not None:
                key=f'{ident}.{b["variant"]}.{b["subtype"]}' if group=='entity' else str(ident)
                box_index[(group,key)].append(ref)
        for i,s in enumerate(sections):
            if not any(x in s['heading'].lower() for x in ['synerg','interaction']):continue
            for line in s['raw'].splitlines():
                if not line.startswith('*'):continue
                targets=[]
                for t in mw.parse(line).filter_templates():
                    if str(t.name).strip().lower() in ('i','t') and t.has('1'):
                        targets.append({'kind':'item' if str(t.name).strip().lower()=='i' else 'trinket','name':plain(t.get('1').value)})
                text=plain(line).lstrip('* ').strip()
                if text:interactions.append({'page':title,'section':s['heading'],'text':text,'targets':targets,
                    'depth':len(line)-len(line.lstrip('*')),'evidence':'wiki statement; edition qualifications retained'})
    def resolve_name(name):
        seen=set()
        while name in aliases and name not in seen:seen.add(name);name=aliases[name]
        return name if name in articles else None
    records=[];gaps=[];coverage=Counter();seen_keys=Counter()
    for group,rows in [('item',inventory['items']),('consumable',inventory['consumables']),('entity',inventory['entities'])]:
        for original in rows:
            row=dict(original);kind=row.get('kind');lookup='entity' if group=='entity' else 'trinket' if kind=='trinket' else 'collectible' if group=='item' and kind!='null' else 'pill' if kind=='pilleffect' else 'card' if group=='consumable' else 'internal'
            key=row['key'] if group=='entity' else str(row['id'])
            row['record_key']=lookup+':'+key
            seen_keys[row['record_key']]+=1
            if seen_keys[row['record_key']]>1:
                row['record_key']+=':definition-'+str(seen_keys[row['record_key']])
            exact=box_index.get((lookup,key),[]) if lookup!='internal' else []
            # An ID may have been reused across DLCs (e.g. Tonsil / Broken Glass Cannon).
            current=[r for r in exact if normal(r['name'])==normal(row['name'])]
            if current:exact=current
            # Some wiki boxes omit subtype: keep a variant-level link explicit, never call it an exact match.
            fallback=box_index.get(('entity',f'{row["id"]}.{row["variant"]}.0'),[]) if group=='entity' else []
            named=[r for r in name_index.get(normal(row['name']),[]) if r['group']==lookup]
            candidates=exact or fallback or named
            row['wiki_matches']=candidates
            row['wiki_match_method']='entity/item ID' if exact else 'variant family; subtype not documented' if fallback else 'name only' if named else 'article title only'
            article=resolve_name(row['name'])
            row['wiki_pages']=sorted(set([r['page'] for r in candidates]+([article] if article else [])))
            row['evidence']={'numeric':'installed Repentance 1.7.9b XML','behavior':'current wiki revision; edition notes must be respected',
                'native_ai_timers':'not established by XML or API declarations','implementation':'research only; no behavior ported by this report'}
            if group=='entity':
                hp=float(row['xml'].get('baseHP',0));stage=float(row['xml'].get('stageHP',0))
                row['hp_by_stage']={str(n):round(hp+(min(4,n)+.8*max(0,min(n-5,5)))*stage,4) for n in range(1,14)}
                row['hp_calculation_note']='Standard Stage HP formula applied to local XML, before champion, phase, shared-health, runtime or mod overrides.'
                row['hp_formula_source']='Stage HP'
            bucket=group if group=='entity' else lookup
            coverage[bucket+'_total']+=1
            if row['wiki_pages']:coverage[bucket+'_with_wiki']+=1
            else:gaps.append({'key':row['record_key'],'name':row['name'],'group':row.get('group',lookup)})
            records.append(row)
    result={'schema_version':1,'baseline':'Installed Repentance 1.7.9b','wiki_license':'CC BY-SA 4.0',
       'wiki_license_url':'https://creativecommons.org/licenses/by-sa/4.0/','coverage':dict(coverage),'records':records,
       'articles':articles,'interactions':interactions,'aliases':aliases,'missing_requested_titles':sorted(missing),
       'source_inventory':inventory,'unmatched_records':gaps}
    (c.CACHE/'compiled.json').write_text(json.dumps(result,ensure_ascii=False,separators=(',',':'))+'\n')
    (c.CACHE/'coverage-audit.json').write_text(json.dumps({'coverage':dict(coverage),'unmatched':gaps,'missing_titles':sorted(missing)},ensure_ascii=False,indent=2)+'\n')
    print(json.dumps(dict(coverage),indent=2));print('Articles',len(articles),'interaction statements',len(interactions),'gaps',len(gaps))

if __name__=='__main__':main()
