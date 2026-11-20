from pathlib import Path
import subprocess,time,json,hashlib
root=Path.cwd(); report=root/'docs/reports/isaac-first-floor-parity/d14a18-bag-bombs'
cases=[('schema60',root/'docs/reports/isaac-first-floor-parity/d14a16-shop-batteries/review-preset.json'),('schema61',Path('/home/kambo/.local/share/deathward/reviews/first-floor-d14a17/campaign.save.balance/export.json')),('schema62',report/'review-preset.json'),('custom62',report/'test-custom-preset.json')]
results=[]
for name,preset in cases:
 log=Path('/tmp/deathward-d14a18')/(name+'.log')
 with log.open('w') as f:
  args=[str(root/'build/deathward'),'--expedition','--seed','338','--review-shop-grab-bag','--mute','--balance-preset',str(preset),'--save',str(Path('/tmp/deathward-d14a18')/(name+'-cli')/'campaign.save')]
  p=subprocess.Popen(args,stdout=f,stderr=subprocess.STDOUT,start_new_session=True)
  try:
   deadline=time.monotonic()+40
   while time.monotonic()<deadline and p.poll() is None:
    data=log.read_text()
    if 'GRAB_BAG_REVIEW room=7' in data:break
    time.sleep(.25)
   data=log.read_text(); assert 'GRAB_BAG_REVIEW room=7' in data and 'zoom=165' in data and 'god=0' in data,(name,data[-2000:])
   wanted='grab_bag_bomb_fuse=1.05 grab_bag_bomb_movement=0.95' if name=='custom62' else 'grab_bag_bomb_fuse=1 grab_bag_bomb_movement=1'
   assert wanted in data,(name,'bomb controls missing')
   results.append({'case':name,'preset':str(preset),'sha256':hashlib.sha256(preset.read_bytes()).hexdigest(),'startup':'pass','zoom':165,'god':False,'room':7})
  finally:
   if p.poll() is None:p.terminate()
   try:p.wait(timeout=8)
   except subprocess.TimeoutExpired:p.kill();p.wait()
(report/'cli-loads.json').write_text(json.dumps(results,indent=2)+'\n')
print('PASS four fresh CLI loads:60/61/62/custom62,165% zoom, normal vulnerability')
