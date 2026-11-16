#!/usr/bin/env python3
"""Bounded two-entry shop choice and original BOGO Bombs pickup resolution."""
import argparse,csv,hashlib,importlib.util,io,json,struct,xml.etree.ElementTree as ET
from unicorn import UC_HOOK_CODE
from pathlib import Path
spec=importlib.util.spec_from_file_location('heart',Path(__file__).with_name('capture-shop-heart.py'))
H=importlib.util.module_from_spec(spec);spec.loader.exec_module(H)
def main():
    ap=argparse.ArgumentParser();ap.add_argument('--check',action='store_true');args=ap.parse_args()
    A=H.A;raw=A.M.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==A.M.SHA
    pe=H.pefile.PE(data=raw);f=A.NativeAwards(pe,raw);u=f.u;n=f.n
    out=A.M.ROOT/'docs/reports/isaac-first-floor-parity/d12f-shop-collectibles/source'
    if not args.check:out.mkdir(parents=True,exist_ok=True)
    def save(name,blob):
        if args.check:assert (out/name).read_bytes()==blob,name
        else:(out/name).write_bytes(blob)
    def table(name,columns,rows):
        s=io.StringIO();w=csv.writer(s,lineterminator='\n');w.writerow(columns);w.writerows(rows);save(name,s.getvalue().encode())
    # Supplied two-entry eligible pool. Run native RNG and cumulative-weight
    # comparison, stopping BEFORE config eligibility/history/depletion checks.
    poolbase=f.HEAP+0x300000;pool=poolbase+4+0x34;entries=poolbase+0x1000
    u.mem_write(pool,struct.pack('<fII',2.,entries,entries+48))
    for index,item in enumerate((64,250)):u.mem_write(entries+index*24,struct.pack('<IfffII',item,1.,1.,.1,1,0))
    rows=[]
    seeds=[1,42,0x7fffffff,0x80000000,0xffffffff]+[(i*0x9e3779b9)&0xffffffff for i in range(1,513)]
    def undo(word,shift,left=False):
        value=word
        for _ in range(32):value=(word^((value<<shift) if left else (value>>shift)))&0xffffffff
        return value
    for word in (0x7fffffbf,0x7fffffc0,0x7fffffff,0x80000000,0xffffff7f,0xffffff80,0xffffffff):
        seeds.append(undo(undo(undo(word,6),11,True),1))
    for seed in seeds:
        b=n.ebp;u.reg_write(H.UC_X86_REG_EBP,b);u.reg_write(H.UC_X86_REG_ESP,b-0x1000)
        u.reg_write(H.UC_X86_REG_EDI,poolbase);u.reg_write(H.UC_X86_REG_ESI,1)
        u.mem_write(b-0xa4,struct.pack('<4I',seed,1,11,6));f.write(b-0x74,0)
        n.run(0x7015e9,0x70160f);after=f.integer(b-0xa4)
        sp=n.STACK+0x9000;u.mem_write(sp,struct.pack('<3I',n.STOP,pool,0));u.reg_write(H.UC_X86_REG_ESP,sp)
        u.reg_write(H.UC_X86_REG_ECX,poolbase)
        hook=u.hook_add(UC_HOOK_CODE,lambda uc,a,size,data:uc.emu_stop(),begin=0x700ce1,end=0x700ce1)
        u.emu_start(0x700c60,n.STOP,count=10000);u.hook_del(hook)
        pc=u.reg_read(H.UC_X86_REG_EIP);assert pc in (0x700ce1,n.STOP)
        chosen=f.integer(u.reg_read(H.UC_X86_REG_ESI)) if pc==0x700ce1 else 0
        assert chosen in (0,64,250);rows.append([seed,after,chosen])
    table('native-choice.csv',['seed','rng_after','collectible'],rows)
    effects=[]
    for copies in (0,1,2,5):
        f.write(f.ITEMS+0xf1000+250*4,copies)
        for variant in (10,20,30,40):
            for subtype in (1,2,3,4,5,6,7):
                vp=n.STACK+0x600;st=vp+4;sp=n.STACK+0x9000
                f.write(vp,variant);f.write(st,subtype)
                u.mem_write(sp,struct.pack('<4I',n.STOP,st,1,0))
                u.reg_write(H.UC_X86_REG_ESP,sp);u.reg_write(H.UC_X86_REG_ECX,12345);u.reg_write(H.UC_X86_REG_EDX,vp)
                f.run(0x6b48b0)
                result=f.integer(st);assert result==(2 if copies and variant==40 and subtype==1 else subtype)
                effects.append([copies,variant,subtype,f.integer(vp),result])
    table('native-bogo.csv',['copies','variant','subtype','result_variant','result_subtype'],effects)
    f.write(f.ITEMS+0xf1000+250*4,0);f.write(f.ROOM+8,2);f.write(f.ROOM+4,f.ROOM+0x1000)
    prices=[]
    for item in (64,250):
        u.reg_write(H.UC_X86_REG_ECX,f.ITEMS+0x10000+item*0x200);n.run(0x6f156b,0x6f1572)
        for seed in (1,42,12345,0x7fffffff,0xffffffff):
            f.write(f.ROOM+0x1058,seed)
            for slot in range(6):
                sp=n.STACK+0x9000;u.mem_write(sp,struct.pack('<4I',n.STOP,100,item,slot))
                u.reg_write(H.UC_X86_REG_ESP,sp);u.reg_write(H.UC_X86_REG_ECX,f.ROOM);f.run(0x7d0950)
                price=u.reg_read(H.UC_X86_REG_EAX);assert price==15;prices.append([item,seed,slot,price])
    table('native-prices.csv',['collectible','seed','slot','price'],prices)
    bomb_prices=[]
    for subtype in (1,2):
        for slot in range(6):
            sp=n.STACK+0x9000;u.mem_write(sp,struct.pack('<4I',n.STOP,40,subtype,slot))
            u.reg_write(H.UC_X86_REG_ESP,sp);u.reg_write(H.UC_X86_REG_ECX,f.ROOM);f.run(0x7d0950)
            price=u.reg_read(H.UC_X86_REG_EAX);assert price==5;bomb_prices.append([subtype,slot,price])
    table('native-bomb-prices.csv',['subtype','slot','price'],bomb_prices)
    source=A.M.ROOT/'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3'
    items=ET.parse(source/'items.xml').getroot();shop=next(p for p in ET.parse(source/'itempools.xml').getroot() if p.get('Name')=='shop')
    records=[]
    for id in ('64','250'):
        item=next(x for x in items if x.tag=='passive' and x.get('id')==id);entry=next(x for x in shop if x.get('Id')==id)
        assert not item.get('achievement') and not item.get('shopprice') and entry.get('Weight')=='1'
        records.append(dict(item=dict(item.attrib),shop_entry=dict(entry.attrib)))
    md=H.capstone.Cs(H.capstone.CS_ARCH_X86,H.capstone.CS_MODE_32);windows=[]
    for name,a,b in [('choice-rng',0x7015e9,0x701614),('rng-float',0x7a7db0,0x7a7e1d),('weighted-scan',0x700c60,0x700e55),('bogo-gate',0x6b57da,0x6b58a1)]:
        blob=pe.get_data(a-0x400000,b-a);save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,a))+'\n').encode());windows.append(dict(name=name,start=hex(a),end=hex(b),sha256=hashlib.sha256(blob).hexdigest()))
    manifest=dict(version='Repentance 1.7.9b',executable_sha256=A.M.SHA,items=records,choice_cases=len(rows),bogo_cases=len(effects),price_cases=len(prices),windows=windows,xml_sha256={name:hashlib.sha256((source/name).read_bytes()).hexdigest() for name in ('items.xml','itempools.xml')},scope='Original RNG/weighted scan under supplied two eligible equal-weight entries; stops before eligibility/history/depletion. Whole pickup resolver with real inventory query and supplied explicit subtype, ordinary player, no Humbling Bundle or mode overrides. Original default store and ordinary prices. Canyon item seed, restricted pool and lazy room admission are adaptations. Full item pool, modifiers, existing-actor lifecycle and native actor acceptance remain open.',full_native_acceptance=False)
    coefficient=pe.get_data(0xb6a198-0x400000,4);assert coefficient==bytes.fromhex('feff7f2f')
    manifest['rng_coefficient']={'address':'0xb6a198','float_bits':'0x2f7ffffe'}
    manifest['bomb_price_cases']=len(bomb_prices)
    save('manifest.json',(json.dumps(manifest,indent=2)+'\n').encode());print(f'PASS {len(rows)} choices, {len(effects)} BOGO cases, {len(prices)} collectible / {len(bomb_prices)} bomb prices')
if __name__=='__main__':main()
