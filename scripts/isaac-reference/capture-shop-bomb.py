#!/usr/bin/env python3
"""Execute pinned ordinary-bomb shop pricing; reuse recorded basic-shop coordinates."""
import argparse,csv,hashlib,importlib.util,io,json,struct
from pathlib import Path
spec=importlib.util.spec_from_file_location('heart',Path(__file__).with_name('capture-shop-heart.py'))
H=importlib.util.module_from_spec(spec);spec.loader.exec_module(H)
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
    A=H.A;raw=A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==A.M.SHA
    previous=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d12a-shop-heart/source/manifest.json'
    original=json.loads(previous.read_text());assert hashlib.sha256((A.M.ROOT/original['room_file']).read_bytes()).hexdigest()==original['room_sha256']
    assert any(s['x']==5 and s['y']==4 and s['choices']==[dict(type=5,variant=150,subtype=0,weight=1.)] for s in original['layout']['slots'])
    f=A.NativeAwards(H.pefile.PE(data=raw),raw);u=f.u;n=f.n
    f.write(f.ROOM+8,2);f.write(f.ROOM+4,f.ROOM+0x1000)
    rows=[]
    for seed in (1,42,12345,0x7fffffff,0xffffffff):
        f.write(f.ROOM+0x1058,seed)
        for slot in range(6):
            sp=n.STACK+0x9000;u.mem_write(sp,struct.pack('<4I',n.STOP,40,1,slot))
            u.reg_write(H.UC_X86_REG_ESP,sp);u.reg_write(H.UC_X86_REG_ECX,f.ROOM);f.run(0x7d0950)
            price=u.reg_read(H.UC_X86_REG_EAX);assert price==5;rows.append([seed,40,1,slot,price])
    # Whole ordinary resolver with supplied category1, empty inventory and room2.
    # Its output pointers are real emulated writable storage; original code executes.
    resolved=[]
    for slot in range(6):
        u.mem_write(f.ROOM+0x1094+slot*2,struct.pack('<h',1))
        variant_out,subtype_out=f.HEAP+0x300000,f.HEAP+0x300004
        sp=n.STACK+0x9000;u.mem_write(sp,struct.pack('<5I',n.STOP,slot,variant_out,subtype_out,12345))
        u.reg_write(H.UC_X86_REG_ESP,sp);u.reg_write(H.UC_X86_REG_ECX,f.ROOM);f.run(0x7d04a0)
        variant,subtype=f.integer(variant_out),f.integer(subtype_out)
        assert (variant,subtype)==(40,1);resolved.append(dict(slot=slot,category=1,variant=variant,subtype=subtype))
    out=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d12d-shop-dynamite/source';out.mkdir(parents=True,exist_ok=True)
    def save(name,data):
        p=out/name
        if args.check:assert p.read_bytes()==data,name
        else:p.write_bytes(data)
    text=io.StringIO();writer=csv.writer(text,lineterminator='\n');writer.writerow(['room_seed','variant','subtype','shop_slot','ordinary_price']);writer.writerows(rows)
    save('native-prices.csv',text.getvalue().encode())
    record=dict(version=original['version'],executable_sha256=A.M.SHA,room_sha256=original['room_sha256'],layout=original['layout'],price_cases=len(rows),price_function='0x7d0950',scope='Original ordinary pricing with supplied basic-shop descriptor and default empty inventory. Original ordinary bomb40.1 pricing with supplied ordinary shop and empty inventory. D12c stock category1 supplies this pickup. Its slot is selected by the existing bounded category schedule, not fixed here. Full native factory/physics and broader shop acceptance remain open.',full_native_acceptance=False)
    save('native-category.json',(json.dumps(resolved,indent=2)+'\n').encode())
    record['category_cases']=len(resolved);record['category_function']='0x7d04a0'
    save('manifest.json',(json.dumps(record,indent=2)+'\n').encode());print('PASS 30 native ordinary bomb40.1 prices and six category1 resolver cases')
if __name__=='__main__':main()
