#!/usr/bin/env python3
"""Capture only: runs the separate debug binary; never changes game assets/config."""
from pathlib import Path
import os, subprocess, json, hashlib
root=Path(__file__).resolve().parents[2]
out=root/'docs/reports/cliff-alternatives'
out.mkdir(parents=True,exist_ok=True)
exe=root/'build/deathward_cliff_alternatives'
shared=['--mute','--smoke','--theme','canyon','--style','original','--scene','profile-works','--frames','60']
for mode in ('original','a','b','c'):
    for wire in (False, True):
        name=mode+('-wire' if wire else '')
        env=dict(os.environ,DW_CLIFF_OPTION=mode,DW_CLIFF_FREEZE_SURROUNDINGS="1")
        env.pop('DW_CLIFF_WIRE',None)
        env.pop('DW_CLIFF_BENCH',None)
        if wire: env['DW_CLIFF_WIRE']='1'
        if mode=='original' and not wire: env['DW_CLIFF_BENCH']='1'
        with (out/(name+'.log')).open('w') as log:
            subprocess.run([str(exe),*shared,'--screenshot',str(out/(name+'.png'))],cwd=root,env=env,stdout=log,stderr=subprocess.STDOUT,check=True)
        print('captured',name,flush=True)
production=['src/world/CanyonAppearance.cpp','src/world/CanyonTerrain.cpp','src/world/CliffWallTopology.cpp','src/render/CanyonScene.cpp','src/core/Game.cpp','assets/visual/canyon.cfg']
(out/'capture.json').write_text(json.dumps({'seed':1866,'scene':'profile-works','frames':60,'native_resolution':[1440,900],'game_zoom_percent':160,'options':['original','a','b','c'],'production_hashes':{p:hashlib.sha256((root/p).read_bytes()).hexdigest() for p in production}},indent=2)+'\n')
