import json,os,subprocess
from pathlib import Path
ROOT=Path(__file__).resolve().parents[4];OUT=Path(__file__).resolve().parent
prefix=os.environ.get('DEATHWARD_CAPTURE_PREFIX','native')
w=json.loads((OUT/'witness.json').read_text())
cases=[('closed',100,[]),('burst',266,[]),('exposed',280,[]),
 ('resident',100,['--resident-seed',str(w['seed']),'--resident-floor',str(w['floor'])])]
rows=[]
for name,frames,extra in cases:
 image=OUT/f'{prefix}-{name}.png';log=OUT/f'{prefix}-{name}.txt';assert not image.exists() and not log.exists()
 args=[str(ROOT/'build/deathward'),'--smoke','--mute','--theme','canyon','--style','original','--scene',('resident-' if extra else 'enemy-')+'300.0.0','--frames',str(frames),'--screenshot',str(image),*extra]
 with log.open('w') as stream:r=subprocess.run(args,cwd=ROOT,stdout=stream,stderr=subprocess.STDOUT)
 rows.append(dict(name=name,command=args,exit_code=r.returncode,image=str(image.relative_to(ROOT)),log=str(log.relative_to(ROOT))))
 (OUT/f'{prefix}-captures.json').write_text(json.dumps(rows,indent=2)+'\n')
 assert r.returncode==0 and image.exists(),name
 print('PASS',name,flush=True)
