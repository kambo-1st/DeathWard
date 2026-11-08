#!/usr/bin/env python3
"""Capture native rotten-heart refill arithmetic; blue-fly AI is not ported."""
import argparse
import csv
import hashlib
import importlib.util
import io
import json
import struct
from pathlib import Path
import capstone
import pefile
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EBP,UC_X86_REG_EDI,UC_X86_REG_ESI,UC_X86_REG_ESP,UC_X86_REG_EIP

SPEC=importlib.util.spec_from_file_location('health',Path(__file__).with_name('analyze-player-health.py'))
HEALTH=importlib.util.module_from_spec(SPEC);SPEC.loader.exec_module(HEALTH)
OUT=HEALTH.MOTION.ROOT/'docs/reports/isaac-first-floor-parity/rotten-heart-flies'


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--check',action='store_true');args=parser.parse_args()
    raw=HEALTH.MOTION.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==HEALTH.MOTION.SHA
    pe=pefile.PE(data=raw);native=HEALTH.NativeHealth(pe);u=native.u;n=native.native
    OUT.mkdir(parents=True,exist_ok=True)
    def save(name,data):
        path=OUT/name
        if args.check:assert path.read_bytes()==data,name
        else:path.write_bytes(data)
    intents=[]
    def endpoint(uc,address,size,data):
        if address==0x76e626:
            sp=uc.reg_read(UC_X86_REG_ESP)
            intents.append(struct.unpack('<I',uc.mem_read(sp,4))[0])
            uc.emu_stop()  # Before AddBlueFlies/world spawning.
    u.hook_add(UC_HOOK_CODE,endpoint)
    rows=[]
    for rotten in range(13):
        for owned in [0,1,2,3,4,12,24,50]:
            native.reset();intents.clear()
            for offset,value in [(0x1290,24),(0x1294,24),(0x1cc4,rotten)]:native.write(native.player+offset,value)
            u.reg_write(UC_X86_REG_EBP,n.ebp);u.reg_write(UC_X86_REG_EDI,native.player)
            u.reg_write(UC_X86_REG_ESI,owned);u.reg_write(UC_X86_REG_ESP,n.STACK+0x9000)
            u.emu_start(0x76e60c,0x76e62b,count=1000)
            at=u.reg_read(UC_X86_REG_EIP)
            assert at in (0x76e626,0x76e62b),hex(at)
            assert len(intents)<=1
            rows.append([rotten,owned,intents[0] if intents else 0])
    stream=io.StringIO(newline='');writer=csv.writer(stream,lineterminator='\n')
    writer.writerow(['rotten_hearts','owned_blue_flies','native_add_blue_flies_request']);writer.writerows(rows)
    save('native-refill.csv',stream.getvalue().encode())
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
    for name,start,end in [('owned_query_and_refill',0x76e5b2,0x76e62b),('add_blue_flies',0x725cc0,0x725da0),
                           ('player_callback_entry',0x76e140,0x76e19a),('players_callback',0x91aa70,0x91ab5e)]:
        blob=pe.get_data(start-pe.OPTIONAL_HEADER.ImageBase,end-start)
        listing=''.join(f'{i.address:08x} {i.mnemonic} {i.op_str}\n' for i in md.disasm(blob,start)).encode()
        save(name+'.asm',listing);windows.append({'name':name,'start':hex(start),'end_exclusive':hex(end),'raw_sha256':hashlib.sha256(blob).hexdigest(),'listing_sha256':hashlib.sha256(listing).hexdigest()})
    manifest={'version':'Repentance 1.7.9b','exe_sha256':HEALTH.MOTION.SHA,'native_cases':len(rows),
              'executed_scope':'0x76e60c-0x76e626/0x76e62b, positive-deficit branch and AddBlueFlies argument assembly; stop before the call.',
              'fixture':'Ordinary player, valid 24-half red capacity; supplied count of already owned blue flies in ESI. World entity enumeration and the AddBlueFlies call are not executed.',
              'static_findings':['Upstream query requests familiar type3/variant43 and counts only those whose player pointer matches the current player.',
                                 'Only a positive 2*rotten - owned deficit requests new flies. Existing excess flies are not removed by this block.',
                                 'AddBlueFlies queries trinket94; a positive count doubles requested quantity before spawning familiar3.43. The native family update/attack and room callback trigger are not established by these arithmetic traces.'],
              'capture_claims_runtime_acceptance':False,'full_acceptance':False,
              'next_work':['confirm all refill callback triggers','verify the integrated actor against whole native initialization/orbit/target/contact/removal behavior','native inventory/room/floor persistence comparison','native item/trinket modifiers','source RNG, collision and live scheduling acceptance'],
              'windows':windows}
    save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode())
    print(f'{"Checked" if args.check else "Captured"} {len(rows)} native rotten-heart refill cases; full actor acceptance is outside this capture.')


if __name__=='__main__':main()
