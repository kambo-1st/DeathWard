import pathlib,subprocess,json
base=pathlib.Path('docs/reports/isaac-enemy-port/brain').resolve()
results=[]
for name,frames,extra in [('open',42,[]),('cover',180,['--enemy-terrain','cover']),('river',100,['--enemy-terrain','river']),('death',188,['--enemy-hit','180','10000']),('expired',520,['--enemy-hit','180','10000'])]:
 command=['./build/deathward','--smoke','--mute','--theme','canyon','--style','original','--scene','enemy-32.0.0','--enemy-camera-follow','--frames',str(frames),'--screenshot',str(base/('native-final-'+name+'.png'))]+extra
 with (base/('native-final-'+name+'.txt')).open('w') as f:r=subprocess.run(command,stdout=f,stderr=subprocess.STDOUT)
 results.append(dict(name=name,command=command,exit=r.returncode));(base/'native-captures-final.json').write_text(json.dumps(results,indent=2)+'\n')
 if r.returncode:raise SystemExit(r.returncode)
