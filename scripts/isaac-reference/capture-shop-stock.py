#!/usr/bin/env python3
"""Bounded ordinary shop category initialization and Steam Sale price arithmetic."""
import argparse,csv,hashlib,importlib.util,io,json,struct,math,xml.etree.ElementTree as ET
from pathlib import Path
from unicorn import UC_HOOK_CODE
spec=importlib.util.spec_from_file_location('heart',Path(__file__).with_name('capture-shop-heart.py'))
H=importlib.util.module_from_spec(spec);spec.loader.exec_module(H)
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
    A=H.A;raw=A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==A.M.SHA
    pe=H.pefile.PE(data=raw);f=A.NativeAwards(pe,raw);u=f.u;n=f.n
    out=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d12c-shop-stock/source';out.mkdir(parents=True,exist_ok=True)
    def save(name,blob):
        p=out/name
        if args.check:assert p.read_bytes()==blob,name
        else:p.write_bytes(blob)
    def table(name,columns,rows):
        stream=io.StringIO();w=csv.writer(stream,lineterminator='\n');w.writerow(columns);w.writerows(rows);save(name,stream.getvalue().encode())
    descriptor=f.ROOM+0x1000;config=f.ROOM+0x2000
    f.write(f.ROOM+8,2);f.write(f.ROOM+4,descriptor);f.write(descriptor+0x10,config);f.write(config+0x10,0)
    seeds=[1,42,69,0x7fffffff,0xffffffff]+[(i*0x9e3779b9)&0xffffffff for i in range(1,513)]
    rows=[]
    for level in (0,3,4):
        f.write(f.ROOM+0x6f5c,level)
        for seed in seeds:
            u.mem_write(descriptor+0x94,b'\0'*28);f.write(descriptor+0x60,seed)
            sp=n.STACK+0x9000;f.write(sp,n.STOP);u.reg_write(H.UC_X86_REG_ESP,sp);u.reg_write(H.UC_X86_REG_ECX,f.ROOM);f.run(0x7cf800)
            kinds=list(struct.unpack('<8h',u.mem_read(descriptor+0x94,16)))
            index,sale=struct.unpack('<2h',u.mem_read(descriptor+0xac,4))
            assert 8 in kinds[:2] and index==0 and not f.allocations
            rows.append([seed,level,*kinds,sale,f.integer(descriptor+0x60)])
    table('native-stock.csv',['seed','shop_level',*[f'slot{i}' for i in range(8)],'discount_slot','rng_after'],rows)
    # Host the external CRT ceil boundary. Original SSE division and conversion
    # still execute; no installed executable or running process is modified.
    ceil_code=f.HEAP+0x300000;ceil_value=ceil_code+32
    u.mem_write(ceil_code,b'\xdd\x05'+struct.pack('<I',ceil_value)+b'\xc3')
    f.write(0xa0651c,ceil_code)
    def host_ceil(uc,address,size,data):
        sp=uc.reg_read(H.UC_X86_REG_ESP)
        value=struct.unpack('<d',uc.mem_read(sp+4,8))[0]
        uc.mem_write(ceil_value,struct.pack('<d',math.ceil(value)))
    u.hook_add(UC_HOOK_CODE,host_ceil,begin=ceil_code,end=ceil_code)
    base_prices=[]
    # XML64 has no price override: execute the original config default store.
    u.reg_write(H.UC_X86_REG_ECX,f.ITEMS+0x10000+64*0x200)
    n.run(0x6f156b,0x6f1572)
    for seed in (1,42,12345,0x7fffffff,0xffffffff):
        f.write(descriptor+0x58,seed)
        for slot in range(6):
            sp=n.STACK+0x9000;u.mem_write(sp,struct.pack('<4I',n.STOP,100,64,slot))
            u.reg_write(H.UC_X86_REG_ESP,sp);u.reg_write(H.UC_X86_REG_ECX,f.ROOM);f.run(0x7d0950)
            price=u.reg_read(H.UC_X86_REG_EAX);assert price==15;base_prices.append([seed,slot,price])
    table('native-item-prices.csv',['seed','slot','price'],base_prices)
    discounts=[];b=n.ebp
    for price in range(31):
        for copies in (0,1,2,3,8):
            u.reg_write(H.UC_X86_REG_EBP,b);u.reg_write(H.UC_X86_REG_ESP,b-0x1000);u.reg_write(H.UC_X86_REG_EDI,price);f.write(b+0xc,copies)
            n.run(0x7d17cf,0x7d1827)
            discounts.append([price,copies,u.reg_read(H.UC_X86_REG_EDI)])
    table('native-discounts.csv',['base_price','discount_count','price'],discounts)
    source=A.M.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3'
    item=next(e for e in ET.parse(source/'items.xml').getroot() if e.tag=='passive' and e.get('id')=='64')
    pool=next(e for p in ET.parse(source/'itempools.xml').getroot() if p.get('Name')=='shop' for e in p if e.get('Id')=='64')
    assert not item.get('achievement') and pool.get('Weight')=='1'
    md=H.capstone.Cs(H.capstone.CS_ARCH_X86,H.capstone.CS_MODE_32);windows=[]
    for name,start,end in [('stock-init',0x7cf800,0x7d03dc),('stock-dispatch',0x7d03e0,0x7d049c),('stock-resolve',0x7d04a0,0x7d08ee),('stock-shuffle',0x5b6400,0x5b648d),('discount-count',0x7d1751,0x7d1827),('default-item-price',0x6f1564,0x6f1572),('ordinary-price',0x7d0950,0x7d0df4)]:
        blob=pe.get_data(start-0x400000,end-start);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,start))+'\n').encode());windows.append(dict(name=name,start=hex(start),end=hex(end),sha256=hashlib.sha256(blob).hexdigest()))
    manifest=dict(version='Repentance 1.7.9b',executable_sha256=A.M.SHA,stock_cases=len(rows),discount_cases=len(discounts),item_price_cases=len(base_prices),item=dict(item.attrib),shop_pool_entry=dict(pool.attrib),xml_sha256={name:hashlib.sha256((source/name).read_bytes()).hexdigest() for name in ['items.xml','itempools.xml']},windows=windows,scope='Whole ordinary stock initializer and original shuffle/RNG/game queries under supplied normal mode, room type2/config variant0, levels0/3/4 and nonzero descriptor stock seed. Only CRT memory hosting. Discount numeric branch uses a supplied effective Steam Sale/sale count, hosting the external CRT ceil import; full inventory query/cache not accepted. Original config default price store plus whole base-price function verifies the no-price-override XML64 base15. Full shop level/profile selection and collectible pool resolver are not accepted.',full_native_acceptance=False)
    save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode());print(f'PASS {len(rows)} native stock schedules, {len(discounts)} discount arithmetic cases, eligible Steam Sale XML')
if __name__=='__main__':main()
