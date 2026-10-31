import datetime,hashlib,json,os,subprocess
from pathlib import Path
root=Path('/home/kambo/workspace/DeathWard')
folder=root/'docs/reports/isaac-enemy-port/headless/validation'
binary=root/'build/deathward_floor_progression_tests'
result={'runner_pid':os.getpid(),'started_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),'binary_sha256':hashlib.sha256(binary.read_bytes()).hexdigest(),'command':[str(binary)],'state':'running'}
path=folder/'floor-direct-result.json'
path.write_text(json.dumps(result,indent=2)+'\n')
with (folder/'floor-direct.log').open('w') as log:
 process=subprocess.Popen([str(binary)],cwd=root,stdout=log,stderr=subprocess.STDOUT)
 result['child_pid']=process.pid;path.write_text(json.dumps(result,indent=2)+'\n')
 result['returncode']=process.wait()
result['state']='finished';result['finished_utc']=datetime.datetime.now(datetime.timezone.utc).isoformat()
path.write_text(json.dumps(result,indent=2)+'\n')
