#!/usr/bin/env python3
"""Execute pinned explosion CheckLine mode 2 against supplied grid objects.

This verifies obstruction classification, not native grid generation, blast
ray selection, rock drops, destruction callbacks or complete bomb physics.
"""
import argparse, csv, hashlib, importlib.util, io, json, struct
from pathlib import Path
import capstone, pefile
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_EIP, UC_X86_REG_ESP

spec = importlib.util.spec_from_file_location('routing', Path(__file__).with_name('capture-gaper-scheduler-routing.py'))
R = importlib.util.module_from_spec(spec)
spec.loader.exec_module(R)
OUT = R.M.ROOT / 'docs/reports/isaac-first-floor-parity/d10b-rock-demolition/source'

def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--check', action='store_true')
    args = ap.parse_args()
    raw = R.M.EXE.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == R.M.SHA
    pe = pefile.PE(data=raw)
    g = R.Grid(pe, {})
    n, u = g.n, g.n.u
    p, sp = n.PLAYER, n.STACK + 0xd000
    g.word(g.ROOM + 4, g.ROOM + 0x9000)
    rows = []
    for name, kind, collision in [('empty', 0, 0), ('ordinary-rock', 2, 3), ('bomb-rock', 3, 3), ('wall', 15, 4)]:
        for layers in (1, 2):
            for i in range(448):
                g.word(g.ROOM + 0x76c + 4*i, 0)
                g.word(g.ROOM + 0x24 + 4*i, 0)
            for column in range(7, 7 + layers):
                for row in range(1, 8):
                    obj = p + 0x2000 + (row + (column-7)*8)*0x100
                    g.word(g.ROOM + 0x24 + 4*(row*15 + column), obj)
                    g.word(obj + 4, kind)
                    g.word(obj + 0x3c, collision)
            for x,y,tx,ty in [(120,280,520,280),(520,280,120,280),(120,160,520,400),(520,400,120,160)]:
                for address, value in [(p+0x100,x),(p+0x104,y),(p+0x108,tx),(p+0x10c,ty)]:
                    n.write_float(address, value)
                u.mem_write(sp, struct.pack('<8I', n.STOP,p+0x100,p+0x108,2,0,0,0,0))
                u.reg_write(UC_X86_REG_ESP,sp)
                u.reg_write(UC_X86_REG_ECX,g.ROOM)
                u.emu_start(0x7af4b0,n.STOP,count=1000000)
                assert u.reg_read(UC_X86_REG_EIP)==n.STOP
                clear=u.reg_read(UC_X86_REG_EAX)&255
                assert clear==int(kind in (0,2))
                rows.append([name,kind,collision,layers,x,y,tx,ty,clear])
    OUT.mkdir(parents=True,exist_ok=True)
    def save(name,data):
        path=OUT/name
        if args.check: assert path.read_bytes()==data,name
        else: path.write_bytes(data)
    stream=io.StringIO(newline='');w=csv.writer(stream,lineterminator='\n')
    w.writerow(['object','type','collision','layers','from_x','from_y','to_x','to_y','clear']);w.writerows(rows)
    save('native-lines.csv',stream.getvalue().encode())
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
    for name,start,end,executed in [('check-line',0x7af4b0,0x7afa37,True),('explosion-grid-caller',0x6d20d4,0x6d2699,False)]:
        blob=pe.get_data(start-0x400000,end-start)
        save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,start))+'\n').encode())
        windows.append(dict(name=name,start=hex(start),end=hex(end),sha256=hashlib.sha256(blob).hexdigest(),executed=executed))
    save('manifest.json',(json.dumps(dict(executable_sha256=R.M.SHA,cases=len(rows),windows=windows,
        method='Original complete CheckLine mode2, supplied normal grid objects, no patched instructions or calculation hooks.',
        remaining='Native radial sampling and grid destruction/factory/drop/physics wrappers; DW physical radius and terrain are adaptations.',
        full_native_acceptance=False),indent=2)+'\n').encode())
    print(f'PASS {len(rows)} native mode2 lines: ordinary rocks pass; bomb rocks and walls block.')

if __name__=='__main__': main()
