import json,os,subprocess
from pathlib import Path
ROOT=Path(__file__).resolve().parents[4];OUT=Path(__file__).resolve().parent
prefix=os.environ.get('DEATHWARD_CAPTURE_PREFIX','native')
names={(27,0):'host',(27,1):'red-host',(204,0):'mobile-host',(247,0):'flesh-mobile-host',(859,0):'floast'}
cases=[(name,*key,100,[]) for key,name in names.items()]
for key in [(27,0),(204,0),(859,0)]:cases.append((names[key]+'-closed',*key,180,[]))
for w in json.loads((OUT/'witnesses.json').read_text()):cases.append(('natural-'+names[(w['type'],w['variant'])],w['type'],w['variant'],100,['--resident-seed',str(w['seed']),'--resident-floor',str(w['floor'])]))
results=[]
for name,t,v,frames,extra in cases:
 if os.environ.get('DEATHWARD_CAPTURE_ONLY')=='closed' and not name.endswith('-closed'):continue
 image=OUT/f'{prefix}-{name}.png';log=OUT/f'{prefix}-{name}.txt';assert not image.exists() and not log.exists()
 args=[str(ROOT/'build/deathward'),'--smoke','--mute','--theme','canyon','--style','original','--scene',('resident-' if extra else 'enemy-')+f'{t}.{v}.0','--frames',str(frames),'--screenshot',str(image),*extra]
 with log.open('w') as stream:r=subprocess.run(args,cwd=ROOT,stdout=stream,stderr=subprocess.STDOUT)
 results.append({'name':name,'command':args,'exit_code':r.returncode,'image':str(image.relative_to(ROOT)),'log':str(log.relative_to(ROOT))})
 (OUT/(prefix+'-captures.json')).write_text(json.dumps(results,indent=2)+'\n');assert r.returncode==0 and image.exists(),name
 print('PASS',name,flush=True)
