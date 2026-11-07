#!/usr/bin/env python3
"""Compare native whole-face coverage with independent rational clipping."""
from pathlib import Path
import argparse
import hashlib
import json
import re
import subprocess
import sys
import tempfile

root=Path(__file__).resolve().parents[2]
parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('probes',nargs='+',type=Path)
parser.add_argument('--binary',type=Path,default=root/'build/deathward_formation_audit')
parser.add_argument('--output-dir',type=Path,required=True)
options=parser.parse_args()
options.output_dir.mkdir(parents=True,exist_ok=True)
sha=lambda p:hashlib.sha256(p.read_bytes()).hexdigest()
fingerprint=sha(options.binary)
rows=[]
for probe in options.probes:
    source=json.loads(probe.read_text())
    label=probe.stem+'-'+sha(probe)[:8]
    with tempfile.NamedTemporaryFile(mode='w',suffix='.boundary') as stream:
        stream.write(str(len(source['faces']))+'\n')
        for face in source['faces']:
            for point in face:stream.write(' '.join(map(repr,point))+'\n')
        stream.write(str(len(source['volumes']))+'\n')
        for volume in source['volumes']:
            stream.write(str(len(volume))+'\n')
            for plane in volume:stream.write(' '.join(map(repr,plane))+'\n')
        stream.flush()
        native=subprocess.run([str(options.binary.resolve()),'--boundary-probe',stream.name],capture_output=True,text=True)
    assert native.returncode in (0,2),native.stderr
    match=re.search(r'SOURCE_BOUNDARY triangles=(\d+) buried=(\d+) detached=(\d+)',native.stdout)
    assert match,native.stdout
    report=options.output_dir/(label+'-exact.json')
    rational=subprocess.run([sys.executable,str(root/'tools/cliff_experiments/formations-exact-intersections.py'),str(probe),
                             '--source-boundary','--output',str(report)],capture_output=True,text=True,check=True)
    (options.output_dir/(label+'.log')).write_text(native.stdout+rational.stdout+rational.stderr)
    exact=json.loads(report.read_text())['exact_source_boundary']
    counts=dict(triangles=int(match[1]),buried=int(match[2]),detached=int(match[3]))
    expected=dict(triangles=len(source['faces']),buried=len(exact['buried']),detached=exact['detached_fragments'])
    assert counts==expected,(str(probe),counts,expected)
    rows.append(dict(probe=str(probe),probe_sha256=sha(probe),native=counts,exact=expected,match=True,exact_report=report.name))
    print(probe.name,counts,'exact rational agreement PASS',flush=True)
assert sha(options.binary)==fingerprint,'Audit binary changed during comparison'
(options.output_dir/'results.json').write_text(json.dumps(dict(audit_binary_sha256=fingerprint,cases=rows,
    scope='Whole-face source coverage only, with the unchanged 0.1 mm margin and 1e-12 square-metre fragment threshold. Does not establish mesh topology, visual or gameplay acceptance.'),indent=2)+'\n')
