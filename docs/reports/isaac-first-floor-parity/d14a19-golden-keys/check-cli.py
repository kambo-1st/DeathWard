from pathlib import Path
import subprocess,time,json,hashlib
root=Path.cwd(); report=root/'docs/reports/isaac-first-floor-parity/d14a19-golden-keys'
cases=[('schema61',root/'docs/reports/isaac-first-floor-parity/d14a17-shop-grab-bags/review-preset.json'),('schema62',Path('/home/kambo/.local/share/deathward/reviews/first-floor-d14a18/campaign.save.balance/export.json')),('schema63',report/'review-preset.json'),('custom63',report/'test-custom-preset.json')]
results=[]
for name,preset in cases:
 log=Path('/tmp/deathward-d14a19')/(name+'.log')
 with log.open('w') as f:
  args=[str(root/'build/deathward'),'--expedition','--seed','940','--review-golden-key','--mute','--balance-preset',str(preset),'--save',str(Path('/tmp/deathward-d14a19')/(name+'-cli')/'campaign.save')]
  p=subprocess.Popen(args,stdout=f,stderr=subprocess.STDOUT,start_new_session=True)
  try:
   deadline=time.monotonic()+40
   while time.monotonic()<deadline and p.poll() is None:
    data=log.read_text()
    if 'GRAB_BAG_REVIEW room=7' in data:break
    time.sleep(.25)
   data=log.read_text(); assert 'GRAB_BAG_REVIEW room=7' in data and 'zoom=165' in data and 'god=0' in data,(name,data[-2000:])
   wanted='grab_bag_golden_keys=0' if name=='custom63' else 'grab_bag_golden_keys=1'
   assert wanted in data,(name,'golden key control missing')
   assert 'GOLDEN_KEY_REVIEW room=7 test_lock=7 finite_keys=0 gold=0 god=0' in data
   results.append({'case':name,'preset':str(preset),'sha256':hashlib.sha256(preset.read_bytes()).hexdigest(),'startup':'pass','zoom':165,'god':False,'room':7})
  finally:
   if p.poll() is None:p.terminate()
   try:p.wait(timeout=8)
   except subprocess.TimeoutExpired:p.kill();p.wait()
(report/'cli-loads.json').write_text(json.dumps(results,indent=2)+'\n')
print('PASS four fresh CLI loads:61/62/63/custom63,165% zoom, normal vulnerability')
