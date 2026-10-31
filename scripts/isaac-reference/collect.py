#!/usr/bin/env python3
"""Cache attributed Isaac research sources; never modify the Steam installation."""
from pathlib import Path
import argparse, concurrent.futures, hashlib, json, threading, time, urllib.parse, urllib.request

ROOT = Path(__file__).resolve().parents[2]
CACHE = ROOT / 'reference/isaac-mechanics-study'
API = 'https://bindingofisaacrebirth.wiki.gg/api.php'
UA = 'DeathWardResearch/1.0 (personal gameplay mechanics study; cached read-only requests)'
LOCK = threading.Lock()
LAST = 0.0

def fetch(url, path):
    global LAST
    path = Path(path)
    if path.exists(): return path.read_bytes()
    with LOCK:
        delay = .65 - (time.monotonic() - LAST)
        if delay > 0: time.sleep(delay)
        LAST = time.monotonic()
    req = urllib.request.Request(url, headers={'User-Agent': UA})
    with urllib.request.urlopen(req, timeout=60) as response:
        data = response.read()
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(data)
    meta = {'url': url, 'retrieved_utc': time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime()),
            'bytes': len(data), 'sha256': hashlib.sha256(data).hexdigest()}
    path.with_suffix(path.suffix+'.source.json').write_text(json.dumps(meta, indent=2)+'\n')
    return data

def api(params, label=None):
    params = dict(params, format='json')
    url = API+'?'+urllib.parse.urlencode(params)
    key = label or hashlib.sha256(url.encode()).hexdigest()[:24]
    result = json.loads(fetch(url, CACHE/'wiki-api'/f'{key}.json'))
    if 'error' in result: raise ValueError(result['error'])
    return result

def page(title, rendered=False):
    return api({'action':'parse','page':title,'prop':'text|sections|revid' if rendered else 'wikitext|revid'},
               ('html-' if rendered else 'raw-')+hashlib.sha256(title.encode()).hexdigest()[:20])

def pages(titles):
    result = []
    titles = sorted(set(titles))
    for start in range(0,len(titles),30):
        group = titles[start:start+30]
        data = api({'action':'query','prop':'revisions','rvprop':'ids|timestamp|content',
                    'rvslots':'main','redirects':1,'titles':'|'.join(group)})
        result.append(data)
        print(f'Wiki revisions {min(start+30,len(titles))}/{len(titles)}',flush=True)
    return result

def github(repo, ref, path):
    url=f'https://raw.githubusercontent.com/{repo}/{ref}/{urllib.parse.quote(path)}'
    return fetch(url,CACHE/'code'/repo.replace('/','__')/ref/path)

def main():
    p=argparse.ArgumentParser();p.add_argument('--titles',type=Path);p.add_argument('--bootstrap',action='store_true');a=p.parse_args()
    CACHE.mkdir(parents=True,exist_ok=True)
    if a.bootstrap:
        for title in ['Monsters','Bosses','Mini-Boss','Items','Trinkets','Cards and Runes','Pills',
                      'Stage HP','Damage Scaling','Champions','Tears','Damage','Luck','Item Pool',
                      'Transformations','Status Effects','Floor Generation','Bestiary Repentance']:
            try:
                data=page(title)
                print(title,data['parse']['revid'],len(data['parse']['wikitext']['*']),flush=True)
            except Exception as e:print('ERROR',title,str(e),flush=True)
        api({'action':'query','meta':'siteinfo','siprop':'rightsinfo'},'wiki-license')
    if a.titles:
        data=pages(json.loads(a.titles.read_text()))
        (CACHE/'wiki-revisions.json').write_text(json.dumps(data,ensure_ascii=False))

if __name__=='__main__':main()
