"""Build the dedicated train prologue set from retained Western meshes/textures.
No existing hub is modified. Runtime/editor use the checked-in assets/train_opening.
"""
from pathlib import Path
import json, math, struct
import numpy as np
from create_redstone import Pack, Library
from redstone_ground import add_surface
from town_train_motion import train_lines

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'assets/train_opening'

def build():
    source, library = Pack('town'), Library()
    placements=[]
    def place(asset, matrix, name):
        key=library.asset(source,asset)
        placements.append(dict(asset=key,transform=np.asarray(matrix).flatten().tolist(),object=name))
    # Remap the existing straight section into a desert set: +X is train travel.
    conversion=np.diag([-1.,1.,-1.,1.]);conversion[:3,3]=[.48,0,18]
    groups=[];members={}
    for g in source.manifest['train_motion']['groups']:
        if g['offset']<300:continue
        prefix=g['id'][8:]
        offset=g['offset']-376.5976389814609+200
        groups.append(dict(id=g['id'],path='opening-rail',offset=offset,wheelbase=g['wheelbase']))
        for p in source.groups[prefix]:
            name='opening-'+p['object'];place(p['asset'],conversion@np.array(p['transform']).reshape(4,4),name)
            members[name]=source.manifest['train_motion']['members'][p['object']]
    # Only the long, straight foreground is filmed; the return loop is well outside the set.
    points=[]
    for a,b in [((-200,0),(800,0)),((800,0),(800,250)),((800,250),(-200,250)),((-200,250),(-200,0))]:
        count=math.ceil(math.dist(a,b)/10)
        points += [[a[0]+(b[0]-a[0])*n/count,0,a[1]+(b[1]-a[1])*n/count] for n in range(count)]
    route=dict(id='opening-rail',speed=0,acceleration=2,dwell=0,points=points)
    # Authored, subtly varied desert terrain: no town, fort or station in the shot.
    seed=np.random.default_rng(186601)
    base=library.asset(source,'part_0000')
    material=len(library.gltf['materials'])
    library.gltf['materials'].append(dict(name='Opening desert sand',pbrMetallicRoughness=dict(baseColorFactor=[.72,.53,.31,1],roughnessFactor=1,metallicFactor=0)))
    vertices=[];colors=[]
    def height(x,z):return max(0,(abs(z)-9)/80)*(.8+.45*math.sin(x*.017+z*.06))
    for x in range(-220,841,12):
        for z in range(-180,181,12):
            for dx,dz in [(0,0),(0,12),(12,12),(0,0),(12,12),(12,0)]:
                xx,zz=x+dx,z+dz;vertices.append([xx,height(xx,zz)-.05,zz,0,1,0,0,0])
                tone=.97+.035*math.sin(xx*.17+zz*.31)+.02*math.sin(xx*.43-zz*.23)
                tone=min(1,tone);colors.append([tone,tone,tone,1])
    op={};asset=add_surface(library,'opening_desert',base,vertices,material,op,colors,origin=[0,0,0])
    placements.append(dict(asset=asset,transform=np.eye(4).flatten().tolist(),object='opening-desert'))
    # Track parts retain their encoded source textures and exact 10 m rail spacing.
    for x in range(-200,811,10):
        m=np.array([[0,0,1,x],[0,1,0,0],[-1,0,0,0],[0,0,0,1]],float)
        for part in ['part_0109','part_0110']:place(part,m,f'rail-{x}-{part}')
    for n in range(44):
        x=float(seed.uniform(-90,520));z=float(seed.choice([-1,1])*seed.uniform(14,85))
        part=str(seed.choice(['part_0004','part_0012','part_0026','part_0044','part_0056']))
        angle=float(seed.uniform(0,math.tau));scale=float(seed.uniform(.75,1.4));c,s=math.cos(angle)*scale,math.sin(angle)*scale
        m=np.array([[c,0,s,x],[0,scale,0,height(x,z)],[-s,0,c,z],[0,0,0,1]])
        place(part,m,f'desert-prop-{n}')
    OUT.mkdir(parents=True,exist_ok=True);library.write(OUT/'town.glb')
    indices={name:n for n,name in enumerate(library.assets)}
    lines=['DEATHWARD_TOWN 5']
    for name,a in library.assets.items():
        lines.append('asset '+' '.join(map(str,[name,a['first_mesh'],a['mesh_count'],a['unlit'],*a['bounds'][0],*a['bounds'][1]])))
    for p in placements:lines.append('instance '+' '.join(map(str,[indices[p['asset']],p['object'],*p['transform']])))
    lines+=train_lines([route],groups,members)
    lines += [line for line in (source.directory/'town.scene').read_text().splitlines() if line.startswith('light 1 ')]
    (OUT/'town.scene').write_text('\n'.join(lines)+'\n')
    (OUT/'town.labels').write_text(''.join(f'{k} {a["label"]}\n' for k,a in library.assets.items()))
    width,depth=1100,400
    heights=np.array([height(-220+x,-180+z) for z in range(depth) for x in range(width)],dtype='<f4')
    (OUT/'town.nav').write_bytes(b'DWTNAV03'+struct.pack('<II9f',width,depth,-220,-180,1,0,0,8,20,0,8)+heights.tobytes())
    (OUT/'town.manifest.json').write_text(json.dumps(dict(title='Westbound',purpose='Dedicated cinematic desert set',assets=library.assets,placements=placements,train_motion=dict(paths=[route],groups=groups,members=members)),indent=2)+'\n')
    print('Created',len(placements),'objects with original Western textures in',OUT)
if __name__=='__main__':build()
