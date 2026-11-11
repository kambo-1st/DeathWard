#!/usr/bin/env python3
"""Execute Repentance's Spider target-lead arithmetic with supplied target state.

The native target resolver and room clamp are boundaries, not stubbed helpers.
"""
import argparse, csv, hashlib, importlib.util, io, json, struct
from pathlib import Path
import capstone, pefile
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ESP, UC_X86_REG_ECX, UC_X86_REG_EBP
spec = importlib.util.spec_from_file_location('motion', Path(__file__).with_name('analyze-player-motion.py'))
M = importlib.util.module_from_spec(spec)
spec.loader.exec_module(M)
OUT = M.ROOT / 'docs/reports/isaac-first-floor-parity/d05-spider-movement'

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    raw = M.EXE.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == M.SHA
    pe = pefile.PE(data=raw)
    rows = []
    for x, y, vx, vy in [(320,280,0,0),(320,280,4.414238452911377,0),
                         (320,280,-4.414238452911377,0),(320,280,0,4.414238452911377),
                         (320,280,3.121338,3.121338),(550,400,4.414238452911377,2)]:
        n = M.NativeMotion(pe)
        n.u.reg_write(UC_X86_REG_EAX, n.PLAYER)
        n.u.reg_write(UC_X86_REG_EBP, n.ebp)
        n.u.reg_write(UC_X86_REG_ESP, n.STACK + 0x6000)
        for address, value in [(n.PLAYER+0x2b8,vx),(n.PLAYER+0x2bc,vy),
                               (n.ebp-0x38,x),(n.ebp-0x34,y)]:
            n.write_float(address,value)
        # This window dereferences the current game-room pointer, without
        # invoking it; provide mapped storage for that supplied boundary.
        game = 0x4000000
        n.u.mem_map(game,0x200000)
        n.u.mem_write(0xbfd65c,struct.pack('<I',game))
        n.u.reg_write(UC_X86_REG_ECX,game)
        n.run(0x517f60,0x517fb3)
        rows.append([x,y,vx,vy,n.read_float(n.ebp-0x38),n.read_float(n.ebp-0x34)])
    OUT.mkdir(parents=True,exist_ok=True)
    def save(name,data):
        path=OUT/name
        if args.check: assert path.read_bytes()==data,name
        else: path.write_bytes(data)
    stream=io.StringIO(newline=''); writer=csv.writer(stream,lineterminator='\n')
    writer.writerow(['target_x','target_y','player_step_vx','player_step_vy','predicted_x','predicted_y'])
    writer.writerows(rows); save('native-target-lead.csv',stream.getvalue().encode())
    blob=pe.get_data(0x517f60-0x400000,0x517fb3-0x517f60)
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
    save('native-target-lead.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(blob,0x517f60))+'\n').encode())
    report=dict(exe_sha256=M.SHA,window_sha256=hashlib.sha256(blob).hexdigest(),cases=len(rows),
        method='Unmodified native 0x517f60..0x517fb3 instructions; stop before room clamp',
        supplied=['resolved target position and per-player-step velocity','game/room pointer storage'],
        unresolved=['native target acquisition and RNG','room clamp and geometry','status branches and full actor wrapper'])
    save('native-target-lead.json',(json.dumps(report,indent=2)+'\n').encode())
    print(json.dumps(dict(passed=True,check=args.check,cases=len(rows))))
if __name__=='__main__': main()
