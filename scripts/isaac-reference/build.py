#!/usr/bin/env python3
"""Build the portable HTML, canonical JSON and implementation review queue."""
import csv, hashlib, json
from pathlib import Path
import collect as c
from analysis import CHAPTERS,CODE_REFERENCES

OUT=c.ROOT/'docs/research/isaac-mechanics-reference.json'
REPORT=c.ROOT/'docs/reports/isaac-mechanics-reference-2026-10-25.html'

def main():
    d=json.loads((c.CACHE/'enriched.json').read_text())
    d['analysis']=CHAPTERS;d['code_references']=CODE_REFERENCES
    d['schema_version']=2
    d['interaction_index_scope']='Bullet statements under Synergies or Interactions headings. Other prose, tables and character-specific combinations remain in the complete article dossiers; this index is not exhaustive of every statement.'
    d['artifact_license']='CC BY-SA 4.0 for authored report and wiki-derived descriptions; no relicensing of game code/assets or cached third-party code.'
    OUT.parent.mkdir(parents=True,exist_ok=True);REPORT.parent.mkdir(parents=True,exist_ok=True)
    data=json.dumps(d,ensure_ascii=False,separators=(',',':'))
    OUT.write_text(data+'\n')
    template=(Path(__file__).parent/'report.html').read_text()
    safe=data.replace('<','\\u003c').replace('\u2028','\\u2028').replace('\u2029','\\u2029')
    REPORT.write_text(template.replace('__DATA__',safe))
    backlog=OUT.with_name('isaac-implementation-backlog.csv')
    with backlog.open('w',newline='') as f:
        w=csv.DictWriter(f,fieldnames=['record_key','display_name','local_name','category','match_method','existing_deathward_adaptation','features_to_review','wiki_revisions','status','next_action'])
        w.writeheader()
        for r in d['records']:
            g=r['record_key'].split(':')[0]
            if g not in ('collectible','trinket','card','pill') and r.get('group') not in ('enemy','boss'):continue
            w.writerow({'record_key':r['record_key'],'display_name':r.get('display_name',r['name']),'local_name':r['name'],
                'category':r.get('group',g),'match_method':r['wiki_match_method'],'existing_deathward_adaptation':'yes; unverified parity' if r.get('deathward') else 'no catalog match',
                'features_to_review':' | '.join(r['feature_triage']),
                'wiki_revisions':' | '.join(d['articles'][t]['revision_url'] for t in r['wiki_pages']),
                'status':'research collected; specification review required',
                'next_action':'Select target edition; classify eligibility; resolve numeric unknowns; review full dossier and interactions; write behavior contract and tests.'})
    manifest={'generated':'2026-10-25','files':[{'file':str(p.relative_to(c.ROOT)),'bytes':p.stat().st_size,'sha256':hashlib.sha256(p.read_bytes()).hexdigest()} for p in (OUT,REPORT,backlog)],
        'records':len(d['records']),'articles':len(d['articles']),'interaction_statements':len(d['interactions']),
        'coverage':d['coverage'],'raw_sources':'reference/isaac-mechanics-study (gitignored, preserved locally)',
        'baseline_sources':'reference/isaac-repentance-1.7.9b (gitignored, preserved locally)'}
    OUT.with_name('isaac-mechanics-reference-manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
    print(json.dumps(manifest,indent=2))

if __name__=='__main__':main()
