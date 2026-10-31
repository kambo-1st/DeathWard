import os,subprocess,time,urllib.request
from pathlib import Path
ROOT=Path(__file__).resolve().parents[4];OUT=Path(__file__).resolve().parent
prefix=os.environ.get('DEATHWARD_TRITE_RUN','final')
with (OUT/f'http-{prefix}.txt').open('x') as log:
 server=subprocess.Popen(['python3','-m','http.server','8099','--bind','127.0.0.1','--directory','build-web'],cwd=ROOT,stdout=log,stderr=subprocess.STDOUT)
 try:
  for _ in range(50):
   try:urllib.request.urlopen('http://127.0.0.1:8099/',timeout=1);break
   except OSError:time.sleep(.1)
  assert server.poll() is None
  env=os.environ|{'NODE_PATH':'/tmp/deathward-web-tools/node_modules','DEATHWARD_BROWSER':'/home/kambo/.cache/ms-playwright/chromium-1194/chrome-linux/chrome','DEATHWARD_WEB_URL':'http://127.0.0.1:8099/','DEATHWARD_TRITE_OUTPUT':str(OUT/f'web-{prefix}'),'DEATHWARD_TRITE_WITNESS':str(OUT/'witness.json')}
  result=subprocess.run(['node','web/trite-test.cjs'],cwd=ROOT,env=env)
 finally:server.terminate();server.wait()
raise SystemExit(result.returncode)
