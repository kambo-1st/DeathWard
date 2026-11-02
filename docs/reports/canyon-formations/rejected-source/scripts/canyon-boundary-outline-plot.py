#!/usr/bin/env python3
"""Plot actual collision samples; no game screenshot editing."""
from pathlib import Path
import sys
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
r=Path(sys.argv[1]) if len(sys.argv)>1 else Path(__file__).resolve().parents[1]/'docs/reports/canyon-organic-boundary'
a=np.genfromtxt(r/'floor-grid.csv',delimiter=',',names=True)
x=np.unique(a['x']);z=np.unique(a['z'])
road=np.genfromtxt(r/'road.csv',delimiter=',',names=True)
sockets=np.genfromtxt(r/'sockets.csv',delimiter=',',names=True)
plt.rcParams.update({'font.family':'DejaVu Sans','font.size':14})
fig,axes=plt.subplots(1,2,figsize=(14,7),facecolor='#20272b',constrained_layout=True)
for ax,key,title,color in zip(axes,['classic','organic'],['Previous playable boundary','Organic playable boundary'],['#d3b17d','#80b9a0']):
 ax.set_facecolor('#30383d');grid=a[key].reshape(len(z),len(x))
 ax.imshow(grid,origin='lower',extent=(x[0]-.25,x[-1]+.25,z[0]-.25,z[-1]+.25),cmap=ListedColormap(['#30383d',color]),vmin=0,vmax=1,interpolation='nearest')
 if key=='organic':ax.contour(x,z,a['classic'].reshape(len(z),len(x)),levels=[.5],colors=['#e3cba5'],linewidths=1,linestyles='--')
 if road.size:ax.plot(road['x'],road['z'],color='#ead392',linewidth=2,label='Preserved road')
 if sockets.size:ax.scatter(sockets['x'],sockets['z'],color='#ef92a5',edgecolor='#172023',s=55,label='Preserved sockets',zorder=4)
 ax.set_xlim(x[0]-.25,x[-1]+.25);ax.set_ylim(z[0]-.25,z[-1]+.25)
 ax.set_aspect('equal');ax.set_title(title,color='#f2e5cc',pad=14);ax.tick_params(colors='#c9c5ba');ax.set_xlabel('World X (metres)',color='#c9c5ba');ax.set_ylabel('World Z (metres)',color='#c9c5ba')
 for spine in ax.spines.values():spine.set_color('#718087')
fig.suptitle('Actual traversable floor · seed 1866 collision fixture, room 2\nDark areas are solid terrain or boulders; dashed line is the previous outline.',color='#f2e5cc',fontsize=16)
fig.savefig(r/'floor-outlines.png',dpi=160,facecolor=fig.get_facecolor());plt.close(fig)
print('Saved',r/'floor-outlines.png')
