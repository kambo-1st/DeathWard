from pathlib import Path
import shlex, subprocess
root=Path.cwd(); build=root/'build'
Path('/tmp/deathward-d14a19').mkdir(exist_ok=True)
vals={l.split(' = ',1)[0]:shlex.split(l.split(' = ',1)[1]) for l in (build/'CMakeFiles/deathward.dir/flags.make').read_text().splitlines() if ' = ' in l}
report=root/'docs/reports/isaac-first-floor-parity/d14a19-golden-keys'; obj=Path('/tmp/deathward-d14a19/game-review.o')
with open('/tmp/deathward-d14a19/game-build.log','w') as log:
 subprocess.run(['/usr/bin/c++',*vals['CXX_DEFINES'],*vals['CXX_INCLUDES'],*vals['CXX_FLAGS'],'-c',str(report/'game-review.cpp'),'-o',str(obj)],stdout=log,stderr=subprocess.STDOUT,check=True)
 args=shlex.split((build/'CMakeFiles/deathward.dir/link.txt').read_text());args[args.index('CMakeFiles/deathward.dir/src/main.cpp.o')]=str(obj);args[args.index('-o')+1]='/tmp/deathward-d14a19/game-review'
 subprocess.run(args,cwd=build,stdout=log,stderr=subprocess.STDOUT,check=True)
with open('/tmp/deathward-d14a19/game-review.log','w') as log:
 subprocess.run(['/tmp/deathward-d14a19/game-review'],stdout=log,stderr=subprocess.STDOUT,check=True)
