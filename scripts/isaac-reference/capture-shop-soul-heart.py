#!/usr/bin/env python3
"""Execute pinned ordinary-soul-heart shop pricing; reuse recorded basic-shop coordinates."""
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
            sp=n.STACK+0x9000;u.mem_write(sp,struct.pack('<4I',n.STOP,10,3,slot))
            u.reg_write(H.UC_X86_REG_ESP,sp);u.reg_write(H.UC_X86_REG_ECX,f.ROOM);f.run(0x7d0950)
            price=u.reg_read(H.UC_X86_REG_EAX);assert price==5;rows.append([seed,10,3,slot,price])
    # Whole ordinary resolver with supplied category4, empty inventory and room2.
    # Its output pointers are real emulated writable storage; original code executes.
    resolved=[]
    for slot in range(6):
        u.mem_write(f.ROOM+0x1094+slot*2,struct.pack('<h',4))
        variant_out,subtype_out=f.HEAP+0x300000,f.HEAP+0x300004
        sp=n.STACK+0x9000;u.mem_write(sp,struct.pack('<5I',n.STOP,slot,variant_out,subtype_out,12345))
        u.reg_write(H.UC_X86_REG_ESP,sp);u.reg_write(H.UC_X86_REG_ECX,f.ROOM);f.run(0x7d04a0)
        variant,subtype=f.integer(variant_out),f.integer(subtype_out)
        assert (variant,subtype)==(10,3);resolved.append(dict(slot=slot,category=4,variant=variant,subtype=subtype))
    health_spec=importlib.util.spec_from_file_location('health',Path(__file__).with_name('analyze-player-health.py'))
    K=importlib.util.module_from_spec(health_spec);health_spec.loader.exec_module(K)
    health=K.NativeHealth(H.pefile.PE(data=raw));hu=health.u;hn=health.native
    health_rows=[]
    for max_red in (0,6,12,24):
        for bone in (0,1):
            for broken in (0,1,5):
                capacity=24-2*broken-max_red-2*bone
                if capacity<0:continue
                for soul in sorted({0,1,max(0,capacity-1),capacity}):
                    if soul>capacity or max_red+soul+bone==0:continue
                    health.reset()
                    for name,value in dict(max_red=max_red,red=max_red,soul=soul,bone=bone,broken=broken).items():health.write(health.player+K.FIELDS[name],value)
                    # CanPickSoulHeart helper with supplied ordinary empty-inventory state.
                    sp=hn.STACK+0x9000;health.write(sp,hn.STOP);hu.reg_write(H.UC_X86_REG_ESP,sp);hu.reg_write(H.UC_X86_REG_ECX,health.player)
                    health.run(0x786d80,hn.STOP);admitted=hu.reg_read(H.UC_X86_REG_EAX)&255
                    assert admitted==int(soul<capacity)
                    amount=0
                    if admitted:
                        # Original subtype quantity computation and AddSoulHearts call.
                        # Stop before the separate pickup sound/presentation wrapper.
                        pickup=hn.STACK+0x2000;health.write(pickup+0x30,3)
                        hu.reg_write(H.UC_X86_REG_ESI,pickup);hu.reg_write(H.UC_X86_REG_EDI,health.player);hu.reg_write(H.UC_X86_REG_EBP,hn.ebp);hu.reg_write(H.UC_X86_REG_ESP,hn.ebp-0x1000)
                        health.run(0x6bf9e7,0x6bf9fc);amount=struct.unpack('<I',hu.mem_read(hn.ebp-0x80,4))[0]
                        assert amount==2
                    after=health.snapshot();assert after['red']==max_red and after['soul']==min(capacity,soul+amount)
                    health_rows.append([max_red,max_red,soul,bone,broken,admitted,amount,after['soul'],after['red']])
    out=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d12e-shop-soul-heart/source';out.mkdir(parents=True,exist_ok=True)
    def save(name,data):
        p=out/name
        if args.check:assert p.read_bytes()==data,name
        else:p.write_bytes(data)
    text=io.StringIO();writer=csv.writer(text,lineterminator='\n');writer.writerow(['room_seed','variant','subtype','shop_slot','ordinary_price']);writer.writerows(rows)
    save('native-prices.csv',text.getvalue().encode())
    text=io.StringIO();writer=csv.writer(text,lineterminator='\n');writer.writerow(['max_red','red','soul','bone','broken','can_collect','source_amount','soul_after','red_after']);writer.writerows(health_rows)
    save('native-soul-health.csv',text.getvalue().encode())
    record=dict(version=original['version'],executable_sha256=A.M.SHA,room_sha256=original['room_sha256'],layout=original['layout'],price_cases=len(rows),price_function='0x7d0950',scope='Original ordinary soul-heart10.3 pricing with supplied ordinary shop and empty inventory. D12c stock category4 supplies this pickup. Its slot is selected by the existing bounded category schedule, not fixed here. Full native factory/physics and broader shop acceptance remain open.',full_native_acceptance=False)
    save('native-category.json',(json.dumps(resolved,indent=2)+'\n').encode())
    record['health_cases']=len(health_rows);record['health_scope']='Original ordinary admission helper and subtype3 quantity/AddSoulHearts call, supplied health and empty inventory. Stops before sound and presentation; full pickup/contact/payment wrapper is separate.'
    record['category_cases']=len(resolved);record['category_function']='0x7d04a0'
    pe=H.pefile.PE(data=raw);md=H.capstone.Cs(H.capstone.CS_ARCH_X86,H.capstone.CS_MODE_32);windows=[]
    for name,start,end in [('soul-admission',0x786d80,0x786e60),('soul-quantity',0x6bf9e7,0x6bf9fc),('soul-stock',0x7d05ea,0x7d0608)]:
        blob=pe.get_data(start-0x400000,end-start);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,start))+'\n').encode());windows.append(dict(name=name,start=hex(start),end=hex(end),sha256=hashlib.sha256(blob).hexdigest()))
    record['windows']=windows
    save('manifest.json',(json.dumps(record,indent=2)+'\n').encode());print(f'PASS 30 soul-heart prices, six category4 resolver cases and {len(health_rows)} native admission/health cases')
if __name__=='__main__':main()
