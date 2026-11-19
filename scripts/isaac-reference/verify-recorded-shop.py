#!/usr/bin/env python3
"""Verify the recorded shop STB and observed offerings, without touching the game."""
from pathlib import Path
import importlib.util,json,hashlib,csv,io
spec=importlib.util.spec_from_file_location('audit',Path(__file__).with_name('audit-live-floor.py'))
A=importlib.util.module_from_spec(spec);spec.loader.exec_module(A)
rows,source=A.read_stb(A.SOURCE/'rooms/00.special rooms.stb')
assert source['sha256']=='a8f7bd23a0362703ffe6ad4a6b80756a2894b01ba710266cc80f1d40e93eb432'
room=next(r for r in rows if (r['type'],r['variant'],r['subtype'])==(2,0,0))
assert len(room['slots'])==8
root=A.ROOT/'docs/reports/isaac-first-floor-parity';capture=json.loads((root/'d14a-floor-content/shop-prices-observation.json').read_text())
live=capture['current_room_actors'];keeper=[a for a in live if a['type']==17];pickups=[a for a in live if a['type']==5]
assert len(keeper)==1 and (keeper[0]['variant'],keeper[0]['subtype'],keeper[0]['x'],keeper[0]['y'])==(1,4,320,200)
assert [(a['variant'],a['subtype'],a['x'],a['y'],a['price']) for a in pickups]==[(100,195,280,320,15),(300,15,360,320,5)]
assert not [a for a in live if (a['type'],a['variant'])==(6,8)]
assert room['slots'][3]['choices']==[dict(type=17,variant=1,subtype=0,weight=.5),dict(type=17,variant=0,subtype=0,weight=.5)]
assert sum(s['choices'][0]['type']==1000 for s in room['slots'])==4
out=root/'d14a10-recorded-shop';out.mkdir(exist_ok=True)
buf=io.StringIO();w=csv.writer(buf,lineterminator='\n');w.writerow(['ordinal','x','y','type','variant','subtype','choice_weight','choice_count'])
for n,s in enumerate(room['slots']):
 c=s['choices'][0];w.writerow([n,s['x'],s['y'],c['type'],c['variant'],c['subtype'],c['weight'],len(s['choices'])])
(out/'source-slots.csv').write_text(buf.getvalue())
(out/'content-verification.json').write_text(json.dumps(dict(template='2.0.0',source=source,room=room,live_capture='d14a-floor-content/shop-prices-observation.json',live_capture_sha256=hashlib.sha256((root/'d14a-floor-content/shop-prices-observation.json').read_bytes()).hexdigest(),observed_keeper=keeper,observed_stock=pickups,donation_machine_observed=False,donation_gate_verified=False,actor_list_scope='Pinned reader enumerates all entries of room+0x125c/count+0x1264 without identity filtering; absence is specific to this recorded snapshot, not proof of a general factory/unlock rule.',keeper_adapter='Retained merchant wagon occupies the source keeper role. Native keeper destruction/drop behavior remains unsupported.',native_floor_selection_claimed=False),indent=2)+'\n')
print('PASS eight STB stacks/four rocks, weighted keeper choices and live17.1.4, Purse195/15coins, Temperance15/5coins; no6.8 in recorded actor list')
