import json,subprocess
from pathlib import Path
ROOT=Path(__file__).resolve().parents[4];OUT=Path(__file__).resolve().parent
results=json.loads((OUT/'native-captures.json').read_text())
assert len(results)==10
for name,ident,seed,floor in [('natural-walking-boil-retry','88.0.0',2,5),('natural-sack','30.2.0',8,3)]:
 image=OUT/f'native-{name}.png';log=OUT/f'native-{name}.txt'
 assert not image.exists() and not log.exists()
 args=[str(ROOT/'build/deathward'),'--smoke','--mute','--theme','canyon','--style','original','--scene','resident-'+ident,'--resident-seed',str(seed),'--resident-floor',str(floor),'--frames','140','--screenshot',str(image)]
 with log.open('w') as stream: result=subprocess.run(args,cwd=ROOT,stdout=stream,stderr=subprocess.STDOUT)
 results.append({'name':name,'identity':ident,'command':args,'exit_code':result.returncode,'image':str(image.relative_to(ROOT)),'log':str(log.relative_to(ROOT))})
 (OUT/'native-captures.json').write_text(json.dumps(results,indent=2)+'\n')
 assert result.returncode==0 and image.exists(),name
 print('PASS',name,flush=True)
