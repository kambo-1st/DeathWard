import pathlib,subprocess,json
base=pathlib.Path('docs/reports/isaac-enemy-port/maggot').resolve()
results=[]
for name,frames,extra in [('open',100,[]),('cover',180,['--enemy-terrain','cover']),('river',100,['--enemy-terrain','river']),('death',188,['--enemy-hit','180','10000'])]:
 command=['./build/deathward','--smoke','--mute','--theme','canyon','--style','original','--scene','enemy-21.0.0','--enemy-camera-follow','--frames',str(frames),'--screenshot',str(base/('native-'+name+'.png'))]+extra
 with (base/('native-'+name+'.txt')).open('w') as f:r=subprocess.run(command,stdout=f,stderr=subprocess.STDOUT)
 results.append(dict(name=name,command=command,exit=r.returncode));(base/'native-captures.json').write_text(json.dumps(results,indent=2)+'\n')
 if r.returncode:raise SystemExit(r.returncode)
