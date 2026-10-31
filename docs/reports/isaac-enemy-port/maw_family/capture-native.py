"""Inspect production Original-style family and natural room captures."""
import json, os, subprocess
from pathlib import Path
ROOT=Path(__file__).resolve().parents[4];OUT=Path(__file__).resolve().parent
prefix=os.environ.get('DEATHWARD_CAPTURE_PREFIX','native')
names=['maw','red-maw','psychic-maw']
cases=[(name,i,[]) for i,name in enumerate(names)]
for w in json.loads((OUT/'witnesses.json').read_text()):
 cases.append(('natural-'+names[w['variant']],w['variant'],['--resident-seed',str(w['seed']),'--resident-floor',str(w['floor'])]))
results=[]
for name,v,extra in cases:
 image=OUT/f'{prefix}-{name}.png';log=OUT/f'{prefix}-{name}.txt';assert not image.exists() and not log.exists()
 args=[str(ROOT/'build/deathward'),'--smoke','--mute','--theme','canyon','--style','original','--scene',('resident-' if extra else 'enemy-')+f'26.{v}.0','--frames','100','--screenshot',str(image),*extra]
 with log.open('w') as stream:r=subprocess.run(args,cwd=ROOT,stdout=stream,stderr=subprocess.STDOUT)
 results.append({'name':name,'command':args,'exit_code':r.returncode,'image':str(image.relative_to(ROOT)),'log':str(log.relative_to(ROOT))})
 (OUT/(prefix+'-captures.json')).write_text(json.dumps(results,indent=2)+'\n')
 assert r.returncode==0 and image.exists(),name
 print('PASS',name,flush=True)
