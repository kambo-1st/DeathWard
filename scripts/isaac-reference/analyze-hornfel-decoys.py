#!/usr/bin/env python3
"""Read-only verification of preserved Hornfel decoy native evidence.

Requires pefile/capstone and the installed baseline. Never regenerates or
replaces captured artifacts. Older damage/vtable evidence stays in its report.
"""
import argparse, hashlib, json, struct
from pathlib import Path
import capstone
import pefile
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-enemy-port/hornfel_decoys'
EXE=Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
def main():
 p=argparse.ArgumentParser(description=__doc__);p.add_argument('--check',action='store_true');p.parse_args()
 manifest=json.loads((OUT/'native/manifest.json').read_text());data=EXE.read_bytes()
 assert hashlib.sha256(data).hexdigest()==manifest['exe_sha256']
 pe=pefile.PE(data=data);base=pe.OPTIONAL_HEADER.ImageBase;decoder=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
 for w in manifest['windows']:
  start,end=int(w['start'],16),int(w['end_exclusive'],16);raw=pe.get_data(start-base,end-start)
  assert hashlib.sha256(raw).hexdigest()==w['raw_sha256'],w['path']
  expected=[f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in decoder.disasm(raw,start)]
  actual=[line.rstrip() for line in (ROOT/w['path']).read_text().splitlines() if not line.startswith(';')]
  assert actual==expected,w['path']
 for name,a in manifest['room_count_api'].items():
  at=int(a['name'],16);function=int(a['function'],16)
  assert pe.get_data(at-base,len(name)+1)==name.encode()+b'\0'
  assert data.count(b'\x68'+struct.pack('<I',function)+b'\x68'+struct.pack('<I',at))==1
 assert struct.unpack('<f',pe.get_data(0xb6ad0c-base,4))[0]==3600
 assert pe.get_data(0x8604e9-base,5)==bytes.fromhex('8b01ff6020')
 for name,a in manifest['properties'].items():
  at=int(a['name'],16);getter=int(a['getter'],16);setter=int(a['setter'],16)
  assert pe.get_data(at-base,len(name)+1)==name.encode()+b'\0'
  assert data.count(b'\x68'+struct.pack('<I',setter)+b'\x68'+struct.pack('<I',getter)+b'\x68'+struct.pack('<I',at))==1
 print('PASS:',len(manifest['windows']),'preserved decoy windows; room counts, HP/Parent properties, entry distance and damage virtual slot')
if __name__=='__main__':main()
