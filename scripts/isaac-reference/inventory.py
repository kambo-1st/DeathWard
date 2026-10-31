#!/usr/bin/env python3
"""Build a complete local-data inventory and a wiki revision collection list."""
from pathlib import Path
import json,re,sys,xml.etree.ElementTree as ET
from collections import Counter
import mwparserfromhell as mw
import collect as c

LOCAL=c.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3'

def category(name):
    rows=[]; continuation={}
    while True:
        d=c.api(dict(action='query',list='categorymembers',cmtitle='Category:'+name,cmlimit=500,**continuation))
        rows+=d['query']['categorymembers']
        if 'continue' not in d:break
        continuation=d['continue']
    return [r['title'] for r in rows if r['ns']==0 and not re.search(r'/[a-z-]{2,5}$',r['title'])]

def title_guess(attributes):
    name=attributes.get('name','')
    if name.startswith('#'):
        path=Path(attributes.get('anm2path','')).stem
        stripped=re.sub(r'^\d+[. _\d-]*','',path)
        if stripped and not stripped.isnumeric():return stripped
        return name[1:].replace('_',' ').title()
    return name

def main():
    names={}
    namefile=next((c.CACHE/'code/wofsauge__External-Item-Descriptions').glob('*/descriptions/names/en_us.lua'))
    for prefix,num,name in re.findall(r'\[(C_ID|T_ID|Pill_ID|Card_ID)\s*\.\.\s*(\d+)\]\s*=\s*"((?:[^"\\]|\\.)*)"',namefile.read_text()):
        names[(prefix,int(num))]=name.replace('\\"','"')
    metadata={(r.tag,int(r.get('id'))):dict(r.attrib) for r in ET.parse(LOCAL/'items_metadata.xml').getroot()}
    pools={}
    for pool in ET.parse(LOCAL/'itempools.xml').getroot():
        for row in pool:
            pools.setdefault(int(row.get('Id')),[]).append({'pool':pool.get('Name'),**row.attrib})
    inventory={'items':[],'consumables':[],'entities':[],'categories':{},'mechanics':[]}
    for row in ET.parse(LOCAL/'items.xml').getroot():
        if 'id' not in row.attrib:continue
        ident=int(row.get('id'));prefix='T_ID' if row.tag=='trinket' else 'C_ID'
        display=names.get((prefix,ident),title_guess(row.attrib)) if row.tag!='null' else title_guess(row.attrib)
        inventory['items'].append({'kind':row.tag,'id':ident,'name':display,'xml':dict(row.attrib),
          'metadata':metadata.get(('trinket' if row.tag=='trinket' else 'item',ident),{}) if row.tag!='null' else {},
          'pools':pools.get(ident,[]) if row.tag in ('active','passive','familiar') else [],
          'source_file':'items.xml'})
    for row in ET.parse(LOCAL/'pocketitems.xml').getroot():
        ident=int(row.get('id'));prefix='Pill_ID' if row.tag=='pilleffect' else 'Card_ID'
        inventory['consumables'].append({'kind':row.tag,'id':ident,'name':names.get((prefix,ident),title_guess(row.attrib)),
                                        'xml':dict(row.attrib),'source_file':'pocketitems.xml'})
    for row in ET.parse(LOCAL/'entities2.xml').getroot():
        ident=int(row.get('id','0'));variant=int(row.get('variant','0'));subtype=int(row.get('subtype','0'))
        inventory['entities'].append({'key':f'{ident}.{variant}.{subtype}','id':ident,'variant':variant,'subtype':subtype,
            'name':title_guess(row.attrib),'xml':dict(row.attrib),'source_file':'entities2.xml',
            'group':('boss' if row.get('boss')=='1' else 'enemy') if 10<=ident<1000 else 'other'})
    for cat in ['Collectibles','Trinkets','Monsters','Bosses','Mini-bosses','Transformations']:
        inventory['categories'][cat]=category(cat)
        print(cat,len(inventory['categories'][cat]),flush=True)
    mechanics=['Monsters','Bosses','Items','Trinkets','Cards and Runes','Pills','Stage HP','Damage Scaling',
      'Champions','Tears','Damage','Luck','Item Pool','Item Quality','Item Tags','Transformations','Status Effects',
      'Floor Generation','Bestiary Repentance','Speed','Range','Shot Speed','Tear Delay','Tear Effects','Health',
      'Greed Mode','Hard Mode','Special Item','Golden Trinket','Isaac','Item Synergies','Item Interactions',
      'Invincibility','Bombs','Creep','Chapters','Entities','Characters']
    inventory['mechanics']=mechanics
    titles=set(mechanics)
    for group in inventory['categories'].values():titles.update(group)
    for group in ('items','consumables'):
        titles.update(r['name'] for r in inventory[group] if r['kind']!='null' and r['name'] and not r['name'].startswith('#'))
    titles.update(r['name'] for r in inventory['entities'] if r['group']!='other' and r['name'])
    for title in ['Monsters','Cards and Runes']:
        code=mw.parse(c.page(title)['parse']['wikitext']['*'])
        for t in code.filter_templates():
            if str(t.name).strip().lower() in ['entity table','pickup table'] and t.has('1'):
                titles.update(s.strip() for s in str(t.get('1').value).split(',') if s.strip())
    (c.CACHE/'inventory.json').write_text(json.dumps(inventory,ensure_ascii=False,indent=2)+'\n')
    (c.CACHE/'wiki-titles.json').write_text(json.dumps(sorted(titles),ensure_ascii=False,indent=2)+'\n')
    print('Inventory', {k:len(inventory[k]) for k in ['items','consumables','entities']},'wiki titles',len(titles),flush=True)

if __name__=='__main__':main()
