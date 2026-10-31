"""Capture the six regular family bodies and their actual seeded rooms once."""
import json
import subprocess
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
OUT = Path(__file__).resolve().parent
names = {'30.0.0':'boil','30.1.0':'gut','30.2.0':'sack','88.0.0':'walking-boil','88.1.0':'walking-gut','88.2.0':'walking-sack'}
cases = [(name, ident, []) for ident,name in names.items()]
for witness in json.loads((OUT/'source-review.json').read_text())['natural_witnesses']:
    cases.append(('natural-'+names[witness['id']],witness['id'],['--resident-seed',str(witness['seed']),'--resident-floor',str(witness['floor'])]))
results=[]
for name,ident,extra in cases:
    image=OUT/f'native-{name}.png'; log=OUT/f'native-{name}.txt'
    assert not image.exists() and not log.exists(), 'Do not overwrite recorded captures'
    args=[str(ROOT/'build/deathward'),'--smoke','--mute','--theme','canyon','--style','original','--scene',('resident-' if extra else 'enemy-')+ident,'--frames','140','--screenshot',str(image),*extra]
    with log.open('w') as stream:
        result=subprocess.run(args,cwd=ROOT,stdout=stream,stderr=subprocess.STDOUT)
    results.append({'name':name,'identity':ident,'command':args,'exit_code':result.returncode,'image':str(image.relative_to(ROOT)),'log':str(log.relative_to(ROOT))})
    (OUT/'native-captures.json').write_text(json.dumps(results,indent=2)+'\n')
    assert result.returncode==0 and image.exists(), name
    print('PASS',name,flush=True)
