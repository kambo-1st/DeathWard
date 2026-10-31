import pathlib,subprocess,json
base=pathlib.Path('docs/reports/isaac-enemy-port/spitties').resolve()
results=[]
for name,identity,frames,extra in [('spitty','31.0.0',240,[]),('conjoined','243.0.0',240,[]),('tainted','31.1.0',240,[]),('tainted-death','31.1.0',248,['--enemy-hit','240','10000'])]:
 command=['./build/deathward','--smoke','--mute','--theme','canyon','--style','original','--scene','enemy-'+identity,'--enemy-camera-follow','--frames',str(frames),'--screenshot',str(base/('native-'+name+'-final.png'))]+extra
 with (base/('native-'+name+'-final.txt')).open('w') as f:result=subprocess.run(command,stdout=f,stderr=subprocess.STDOUT)
 results.append(dict(name=name,command=command,exit=result.returncode))
 (base/'native-captures-final.json').write_text(json.dumps(results,indent=2)+'\n')
 if result.returncode:raise SystemExit(result.returncode)
