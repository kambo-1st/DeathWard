#!/usr/bin/env python3
"""Bounded native room-caller and descriptor evidence from installed 1.7.9b.

Supplied Normal/Hard, stage, resolved curse mask and room slots. Executes original
instructions; does not run the floor graph, unlock profile or spawn factory.
"""
import argparse, csv, hashlib, importlib.util, io, json, struct
from pathlib import Path
import capstone, pefile
from unicorn.x86_const import *

ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-first-floor-parity/native-room-eligibility'
spec = importlib.util.spec_from_file_location('motion', ROOT / 'scripts/isaac-reference/analyze-player-motion.py')
motion = importlib.util.module_from_spec(spec)
spec.loader.exec_module(motion)
DATA = 0x4000000
LEVEL, RNG, SLOT, PTR = DATA + 0x250000, DATA + 0x290000, DATA + 0x290100, DATA + 0x290200

class Native(motion.NativeMotion):
    def __init__(self, pe):
        super().__init__(pe)
        self.u.mem_map(DATA, 0x300000)
        self.integer(0xbfd65c, DATA)
    def integer(self, a, v): self.u.mem_write(a, struct.pack('<I', v & 0xffffffff))
    def read(self, a): return struct.unpack('<I', self.u.mem_read(a, 4))[0]
    def registers(self):
        self.u.reg_write(UC_X86_REG_EBP, self.ebp)
        self.u.reg_write(UC_X86_REG_ESP, self.ebp - 0x1000)
        self.u.reg_write(UC_X86_REG_EDI, LEVEL)
    def difficulty(self, stage, hard, curse):
        self.registers()
        self.integer(LEVEL, stage)
        self.integer(self.ebp - 0x3fc, hard)
        self.u.reg_write(UC_X86_REG_EAX, curse)
        self.run(0x70e7a7, 0x70e85a)
        return self.read(self.ebp - 0x3fc), self.read(self.ebp - 0x410)
    def stage_pool(self, stage, kind):
        self.registers()
        sp = self.ebp - 0x1000
        self.integer(sp, self.STOP); self.integer(sp + 4, 0)  # ordinary mode
        self.u.reg_write(UC_X86_REG_ECX, stage)
        self.u.reg_write(UC_X86_REG_EDX, kind)
        self.run(0x7e79c0, self.STOP)
        return self.u.reg_read(UC_X86_REG_EAX)
    def query(self, seed, doors, minimum=1, maximum=5):
        self.registers()
        self.integer(LEVEL, 1); self.integer(LEVEL + 0x18160, 84)
        self.integer(PTR, SLOT)
        for off, v in [(8, 1), (12, 1), (0x18, 1), (0x1c, doors), (0x40, 0)]: self.integer(SLOT + off, v)
        for off, v in enumerate([seed, 1, 5, 16]): self.integer(RNG + off * 4, v)
        for off, v in [(-0x14c, maximum), (-0x10c, 1), (-0xe0, DATA + 0x1879c)]: self.integer(self.ebp + off, v)
        self.u.reg_write(UC_X86_REG_EBX, RNG)
        self.u.reg_write(UC_X86_REG_ESI, PTR)
        self.u.reg_write(UC_X86_REG_ECX, minimum)
        self.run(0x70a5c5, 0x70a6ee)
        sp = self.u.reg_read(UC_X86_REG_ESP)
        args = [self.read(sp + 4*i) for i in range(12)]
        args[9] = self.read(args[9])  # replace address with actual door mask
        return args
    def descriptor(self, seed):
        self.registers()
        self.integer(LEVEL + 0x1815c, 0)
        self.integer(self.ebp + 0x10, seed)
        self.u.reg_write(UC_X86_REG_EAX, 0)
        # Includes the actual place_room seed setup and complete InitSeeds call.
        self.run(0x7066d9, 0x70670d)
        return [self.read(LEVEL + 0x14 + off) for off in (0x58, 0x5c, 0x60, 0x64)]

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true'); args = parser.parse_args()
    raw = motion.EXE.read_bytes(); assert hashlib.sha256(raw).hexdigest() == motion.SHA
    pe = pefile.PE(data=raw); native = Native(pe)
    difficulties = [[s, h, c, *native.difficulty(s, h, c)] for s in (1, 2, 3, 8, 9) for h in (0, 1) for c in (0, 2)]
    pools = [[s, k, native.stage_pool(s, k)] for s in (1, 2) for k in range(6)]
    queries = []; descriptors = []
    for n in range(64):
        seed = [1, 2, 0x7fffffff, 0x80000000, 0xffffffff][n] if n < 5 else ((n*2654435761) & 0xffffffff) or 1
        for doors in range(16): queries.append([seed, doors, *native.query(seed, doors)])
        descriptors.append([seed, *native.descriptor(seed)])
    assert difficulties[0][-2:] == [1, 5] and pools[0][-1] == 1
    assert all(r[3:11] == [1, 1, 1, 1, 0, 0xffffffff, 1, 5] and r[12:] == [0, 0xffffffff] for r in queries)
    OUT.mkdir(parents=True, exist_ok=True)
    def save(name, value):
        path = OUT / name
        if args.check: assert path.read_bytes() == value, name
        else: path.write_bytes(value)
    def csvout(name, header, rows):
        out = io.StringIO(); w = csv.writer(out, lineterminator='\n'); w.writerow(header); w.writerows(rows)
        save(name, out.getvalue().encode())
    csvout('native-difficulty.csv', ['stage','hard','resolvedCurseMask','minimum','maximum'], difficulties)
    csvout('native-pools.csv', ['stage','stageType','pool'], pools)
    csvout('native-queries.csv', ['rngInput','doors','selectionSeed','reduce','pool','type','shape','minVariant','maxVariant','minDifficulty','maxDifficulty','requiredDoors','subtype','mode'], queries)
    csvout('native-descriptors.csv', ['selectionSeed','decoration','spawn','award','bossDeath'], descriptors)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32); windows = []
    for name, start, end in [('difficulty',0x70e775,0x70e85a),('stage-pool',0x7e79c0,0x7e7a8e),('ordinary-query',0x70a5c5,0x70a70e),('placement-seeds',0x7066d9,0x70670d),('descriptor-seeds',0x705d10,0x705e23),('floor-call',0x70ef92,0x70efb6)]:
        blob = pe.get_data(start-0x400000, end-start)
        save(name+'.asm', ('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip() for i in md.disasm(blob,start))+'\n').encode())
        windows.append(dict(name=name,start=hex(start),end=hex(end),sha256=hashlib.sha256(blob).hexdigest()))
    manifest = dict(executable_sha256=motion.SHA, difficulty_cases=len(difficulties), pool_cases=len(pools), query_cases=len(queries), descriptor_cases=len(descriptors), windows=windows,
        finding='Ordinary non-XL Normal Basement I: pool1, type1, subtype0, difficulty1..5, variants0..UINT_MAX, reduceWeight=true. Shape/doors supplied by the retained canyon adapter. Descriptor seeds derive from the selection seed with native2/7/9; spawn is the second advance.',
        scope='Original instructions with supplied stage, difficulty, resolved curse mask, slot and RNG. No live/full floor generator, unlock profile, special modes, graph ordering or Isaac seed-string compatibility accepted. Only the spawn seed consumer is enabled by this delivery; native decoration, award and boss-death consumers remain separate.')
    save('manifest.json', (json.dumps(manifest, indent=2)+'\n').encode())
    print(f'PASS {len(difficulties)} difficulty, {len(pools)} stage-pool, {len(queries)} ordinary caller, {len(descriptors)} descriptor cases')

if __name__ == '__main__': main()
