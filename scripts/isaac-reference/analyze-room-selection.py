#!/usr/bin/env python3
"""Execute installed 1.7.9b room filter/weighted choice blocks, without running or modifying Isaac.

Synthetic candidate tables/door requests; no claim of native floor generation,
caller difficulty, descriptor seeds, special modes or complete room placement.
"""
import argparse,csv,hashlib,importlib.util,io,json,struct
from pathlib import Path
import capstone,pefile
from unicorn.x86_const import *
ROOT=Path(__file__).resolve().parents[2]
OUT=ROOT/'docs/reports/isaac-first-floor-parity/native-room-selection-placement'
spec=importlib.util.spec_from_file_location('motion',ROOT/'scripts/isaac-reference/analyze-player-motion.py')
motion=importlib.util.module_from_spec(spec);spec.loader.exec_module(motion)
DATA=0x4000000
class NativeSelection(motion.NativeMotion):
    def __init__(self,pe):
        super().__init__(pe);self.u.mem_map(DATA,0x40000)
    def integer(self,a,v):self.u.mem_write(a,struct.pack('<I',v&0xffffffff))
    def record(self,i,r):
        a=DATA+i*0x5c
        for offset,key in [(8,'type'),(12,'variant'),(16,'subtype'),(0x2c,'difficulty'),(0x38,'doors'),(0x48,'shape')]:self.integer(a+offset,r[key])
        self.write_float(a+0x34,r['weight']);return a
    def eligible(self,r,q):
        u=self.u;b=self.ebp;a=self.record(0,r)
        # The original numeric filter, ending before the special G-Fuel seed-effect query.
        for offset,key in [(0x10,'type'),(0x14,'shape'),(0x18,'minVariant'),(0x1c,'maxVariant'),(0x20,'minDifficulty'),(0x24,'maxDifficulty'),(0x2c,'subtype')]:self.integer(b+offset,q[key])
        self.integer(b+0x28,DATA+0x30000);self.integer(DATA+0x30000,q['doors'])
        u.reg_write(UC_X86_REG_ESI,a);u.reg_write(UC_X86_REG_EBP,b);u.reg_write(UC_X86_REG_ECX,0)
        # Both outcomes are forward branches. A rejected row ends at 796b;
        # successful rows stop at 790e before any seed-effect wrapper behavior.
        from unicorn import UC_HOOK_CODE
        def stop(uc,address,size,user):uc.emu_stop()
        hook=u.hook_add(UC_HOOK_CODE,stop,begin=0x7e796b,end=0x7e796b)
        u.emu_start(0x7e78a4,0x7e790e,count=1000);u.hook_del(hook)
        pc=u.reg_read(UC_X86_REG_EIP);assert pc in (0x7e790e,0x7e796b),hex(pc)
        return pc==0x7e790e
    def select(self,rows,seed,doors,reduce):
        u=self.u;b=self.ebp;allptr=DATA+0x18000;exact=DATA+0x20000;mask=DATA+0x30000
        for i,r in enumerate(rows):self.integer(allptr+4*i,self.record(i,r))
        self.integer(mask,doors)
        # Preallocated equivalent std::vector storage: no allocator/selection hooks.
        for off,value in [(-0x60,allptr+4*len(rows)),(-0x50,exact),(-0x54,exact),(-0x4c,exact+4*len(rows)),(-0x58,allptr+4*len(rows)),(-0x3c,allptr),(-0x40,mask),(-0x48,seed)]:self.integer(b+off,value)
        u.mem_write(b-0x31,bytes([reduce]));u.reg_write(UC_X86_REG_EBP,b)
        u.reg_write(UC_X86_REG_EBX,allptr);u.reg_write(UC_X86_REG_EDX,exact+4*len(rows))
        u.reg_write(UC_X86_REG_ESP,b-0x200)
        u.emu_start(0x7e73c8,0x7e767a,count=100000)
        assert u.reg_read(UC_X86_REG_EIP)==0x7e767a
        chosen=u.reg_read(UC_X86_REG_ESI)
        if chosen==0:return -1,0
        index=(chosen-DATA)//0x5c;assert 0<=index<len(rows)
        return index,self.read_float(chosen+0x34)
    def spawn(self,slot,seed):
        u=self.u;b=self.ebp;config=DATA+0x31000;room=DATA+0x32000;spawn=DATA+0x33000;entries=DATA+0x34000
        self.integer(config+0x40,spawn);self.integer(room+0xc,15)
        u.mem_write(spawn,struct.pack('<hhIB3xf',slot['x'],slot['y'],entries,len(slot['choices']),sum(c['weight'] for c in slot['choices'])))
        for i,c in enumerate(slot['choices']):u.mem_write(entries+i*12,struct.pack('<IHHf',c['type'],c['variant'],c['subtype'],c['weight']))
        for offset,value in [(-0x504,config),(-0x5ac,2),(-0x5a8,7),(-0x5a4,7)]:self.integer(b+offset,value)
        u.reg_write(UC_X86_REG_EBP,b);u.reg_write(UC_X86_REG_EDI,room);u.reg_write(UC_X86_REG_EDX,0)
        u.reg_write(UC_X86_REG_ESI,seed);u.reg_write(UC_X86_REG_ESP,b-0x900)
        u.emu_start(0x7b201a,0x7b2093,count=10000)
        assert u.reg_read(UC_X86_REG_EIP)==0x7b2093
        return ((u.reg_read(UC_X86_REG_EAX)-entries)//12,u.reg_read(UC_X86_REG_ESI),struct.unpack('<I',u.mem_read(b-0x4f4,4))[0])

def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--check',action='store_true');args=parser.parse_args()
    raw=motion.EXE.read_bytes();assert hashlib.sha256(raw).hexdigest()==motion.SHA
    pe=pefile.PE(data=raw);native=NativeSelection(pe)
    pool=json.loads((ROOT/'docs/reports/isaac-first-floor-parity/d09a-room-hearts/source-layouts.json').read_text())['templates']
    q=dict(type=1,shape=1,minVariant=0,maxVariant=0xffffffff,minDifficulty=1,maxDifficulty=5,doors=0,subtype=-1)
    filters=[]
    # Includes filter rejections for each field, unsigned variant bounds, exact
    # boundaries, shape wildcard, subtype wildcard and all ordinary door masks.
    base=dict(type=1,variant=100,subtype=0,difficulty=3,shape=1,doors=15,weight=1)
    candidates=[base]+[dict(base,**{key:value}) for key,values in [('type',[0,2]),('variant',[0,0xffffffff]),('subtype',[1]),('difficulty',[0,1,5,6]),('shape',[2,13]),('doors',range(16))] for value in values]
    queries=[dict(q,doors=d) for d in range(16)]+[dict(q,shape=13),dict(q,subtype=1),dict(q,minVariant=100,maxVariant=100),dict(q,minDifficulty=3,maxDifficulty=3)]
    for r in candidates:
        for query in queries:filters.append([*[r[k] for k in ('type','variant','subtype','difficulty','shape','doors')],*[query[k] for k in ('type','shape','minVariant','maxVariant','minDifficulty','maxDifficulty','doors','subtype')],int(native.eligible(r,query))])
    selections=[]
    for doors in range(16):
        rows=[dict(r) for r in pool if native.eligible(r,dict(q,doors=doors))]
        for n in range(64):
            seed=([1,2,0x7fffffff,0x80000000,0xffffffff][n] if n<5 else ((n*2654435761+doors*123457)&0xffffffff) or 1)
            reduce=n>=32
            chosen,weight=native.select(rows,seed,doors,reduce)
            selections.append([doors,n,seed,int(reduce),rows[chosen]['variant'] if chosen>=0 else -1,format(weight,'.9g')])
            if reduce and chosen>=0:rows[chosen]['weight']=weight
    spawns=[]
    for slotIndex,slot in enumerate(s for r in pool for s in r['slots']):
        for n in range(64):
            seed=([1,2,0x7fffffff,0x80000000,0xffffffff][n] if n<5 else ((n*2654435761+slotIndex*123457)&0xffffffff) or 1)
            choice,endpoint,grid=native.spawn(slot,seed)
            spawns.append([slotIndex,seed,choice,endpoint,grid])
    OUT.mkdir(parents=True,exist_ok=True)
    def save(name,data):
        path=OUT/name
        if args.check:assert path.read_bytes()==data,name
        else:path.write_bytes(data)
    def csvout(name,header,rows):
        out=io.StringIO();w=csv.writer(out,lineterminator='\n');w.writerow(header);w.writerows(rows);save(name,out.getvalue().encode())
    csvout('native-filters.csv',['type','variant','subtype','difficulty','shape','doors','queryType','queryShape','minVariant','maxVariant','minDifficulty','maxDifficulty','requiredDoors','querySubtype','eligible'],filters)
    csvout('native-selections.csv',['doors','step','seed','reduce','variant','weightAfter'],selections)
    csvout('native-spawns.csv',['slot','seed','choice','seedAfter','gridIndex'],spawns)
    md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32);windows=[]
    for name,start,end in [('filter',0x7e78a4,0x7e790e),('selection',0x7e73c8,0x7e773a),('door_nonempty',0x6b1490,0x6b14a3),('spawn_step',0x7b201a,0x7b2093),('spawn_choice',0x7e7c20,0x7e7ca3),('spawn_loop',0x7b1fd1,0x7b2120),('spawn_seed',0x7b1849,0x7b187e)]:
        blob=pe.get_data(start-pe.OPTIONAL_HEADER.ImageBase,end-start)
        save(name+'.asm',('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,start))+'\n').encode())
        windows.append(dict(name=name,start=hex(start),end=hex(end),sha256=hashlib.sha256(blob).hexdigest()))
    save('manifest.json',(json.dumps(dict(executable_sha256=motion.SHA,filter_cases=len(filters),selection_cases=len(selections),spawn_cases=len(spawns),windows=windows,method='Original x86/SSE instructions and original door-nonempty/spawn-choice helpers; supplied candidates/requests and preallocated vectors. No instruction patches or selection/RNG hooks.',scope='Numeric filter, ordinary weighted selection, per-slot RNG/choice/grid index; native caller eligibility, full floor generation, G-Fuel/special modes, seeds, spawn-factory mutations and full layout/grid placement remain open.'),indent=2)+'\n').encode())
    print(f'PASS {len(filters)} native filters, {len(selections)} native selections/reduced weights, {len(spawns)} native spawn choices/seeds/grid indices')
if __name__=='__main__':main()
