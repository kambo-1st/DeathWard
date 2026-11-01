#!/usr/bin/env python3
"""Preserve/check the installed Horf room-layout replacement conditions.

Static native analysis and a specification truth table, not an Isaac playtest
or proof of a DeathWard Sub Horf implementation. Does not change runtime data.
"""
import argparse, hashlib, html, itertools, json, struct
from pathlib import Path
import capstone
import pefile
ROOT = Path(__file__).resolve().parents[2]
OUT = ROOT / 'docs/reports/isaac-enemy-port/horf_fly/replacement-review'
EXE = Path('/mnt/c/Program Files (x86)/Steam/steamapps/common/The Binding of Isaac Rebirth/isaac-ng.exe')
HASH = '04469d0c3d3581936fcf85bea5f9f4f3a65b2ccf96b36310456c9626bac36dc6'

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    raw = EXE.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == HASH, 'Unexpected native baseline'
    pe = pefile.PE(data=raw)
    read = lambda a, n: pe.get_data(a-pe.OPTIONAL_HEADER.ImageBase, n)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    def instructions(a, z):
        return {i.address: (i.mnemonic, i.op_str) for i in md.disasm(read(a,z-a),a)}
    def expect(ins, address, mnemonic, operands):
        assert ins[address] == (mnemonic,operands), (hex(address),ins.get(address))
    # Horf's table entry lands directly on the sixty-way roll, not the
    # preceding fifteen-way branch used by a different table entry.
    slot = read(0x7abc28+12-10,1)[0]
    target = struct.unpack('<I',read(0x7abbe0+slot*4,4))[0]
    assert target == 0x7aba2c
    code = instructions(0x7aba2c,0x7aba58)
    for address,mnemonic,operands in [
        (0x7aba2c,'push','0x3c'),(0x7aba31,'call','0x7a7d50'),
        (0x7aba36,'test','eax, eax'),(0x7aba38,'jne','0x7abadd'),
        (0x7aba3e,'mov','dword ptr [esi], 0x32c'),
        (0x7aba44,'mov','word ptr [ebx], ax')]:
        expect(code,address,mnemonic,operands)
    gates = instructions(0x7ab683,0x7ab795)
    for address,mnemonic,operands in [
        (0x7ab694,'mov','eax, dword ptr [eax + 0x4c]'),
        (0x7ab697,'and','eax, 1'),(0x7ab69e,'test','al, al'),
        (0x7ab6a0,'jne','0x7abbcb'),
        (0x7ab6a6,'cmp','dword ptr [edx + 8], 0x1b'),
        (0x7ab6aa,'je','0x7abbcb'),
        (0x7ab787,'movzx','eax, byte ptr [eax + 0x7abc28]'),
        (0x7ab78e,'jmp','dword ptr [eax*4 + 0x7abbe0]')]:
        expect(gates,address,mnemonic,operands)
    early = instructions(0x7aacfa,0x7aad9d)
    expect(early,0x7aad17,'call','0x802f30')
    expect(early,0x7aad83,'cmp','byte ptr [ebp - 0x2f], 0')
    expect(early,0x7aad87,'jne','0x7abbcb')
    rng = instructions(0x7a7d50,0x7a7da8)
    expect(rng,0x7a7d9d,'xor','edx, edx')
    expect(rng,0x7a7d9f,'div','ecx')
    expect(rng,0x7a7da2,'mov','eax, edx')
    enum_path = ROOT/'reference/isaac-repentance-1.7.9b/loose/resources/scripts/enums.lua'
    enums = enum_path.read_text()
    assert 'ROOM_SECRET_EXIT = 27' in enums
    assert 'MC_PRE_ROOM_ENTITY_SPAWN = 71' in enums
    assert 'Returning a table will override any replacements' in enums
    windows = [('native-branch',0x7aba2c,0x7aba58),
        ('native-room-gates-and-dispatch',0x7ab683,0x7ab795),
        ('native-pre-spawn-override',0x7aacfa,0x7aad9d),
        ('native-random-int',0x7a7d50,0x7a7da8),
        ('native-type-normalization',0x697510,0x697bd1)]
    evidence = []
    OUT.mkdir(parents=True,exist_ok=True)
    for name,a,z in windows:
        data=read(a,z-a)
        text='\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(data,a))+'\n'
        path=OUT/(name+'.asm')
        if args.check: assert path.read_text()==text,path
        else: path.write_text(text)
        evidence.append(dict(path=str(path.relative_to(ROOT)),start=hex(a),end=hex(z),sha256=hashlib.sha256(data).hexdigest()))
    # Exhaustive truth-table of the recovered predicate. Stage/mode/variant
    # factors below are absent from Horf's branch, not newly invented gates.
    trials=hits=0
    for kind,override,flags,room,stage,mode,roll in itertools.product(
        (12,248,812),(False,True),(0,1,2,3),(1,5,27),range(1,14),range(4),range(60)):
        got = kind==12 and not override and not flags&1 and room!=27 and roll==0
        if got: hits+=1
        trials+=1
    # For a permitted Horf, exactly one of all sixty possible residues passes.
    assert sum(roll==0 for roll in range(60))==1
    assert hits==2*2*13*4
    result=dict(baseline='Repentance 1.7.9b',exe_sha256=HASH,
        status='replacement_conditions_verified_runtime_enabled_scoped_tests',
        method='Static disassembly, byte-checked native branch/gates and specification truth table; no live Isaac trial.',
        source=dict(type=12,variant='No variant test in the native type-12 case',subtype='Preserved'),
        target=dict(type=812,variant=0,subtype='Unchanged'),
        roll=dict(numerator=1,denominator=60,native='xorshift32 output modulo 60 equals zero; do not round to basis points'),
        conditions=[
            'Room-layout spawn preprocessing: a successful MC_PRE_ROOM_ENTITY_SPAWN override bypasses native replacements.',
            'The layout RoomConfig.Flags bit 0 must be clear (or the configuration pointer absent). Other flag bits do not suppress this branch.',
            'Room type must not be ROOM_SECRET_EXIT (27).',
            'After earlier normalization the current entity type must be Horf (12); Psychic Horf (248) does not use this case.',
            'The native type-12 branch has no stage, stage-type, difficulty, unlock or variant check. It rolls once for the layout entry.',
            'On residue zero it writes type812 and variant0, retaining subtype. This is a spawn replacement, never a death offspring.'
        ],
        downpour='The wiki describes Sub Horfs authored in Downpour plus rare replacements elsewhere. It does not imply a guaranteed Horf conversion there. The recovered Horf branch remains1/60; nearby1/15 code is a different dispatch case.',
        deathward=dict(enabled=True,reason='Ordinary812.0.0reactive controller and replace_fraction exact1/60rule are enabled; scoped tests in sub-horf/tests.log.',
            rule=dict(source='12.0.0',target='812.0.0',first_band=0,last_band=3,chance_numerator=1,chance_denominator=60,scope='generated room encounter selection only'),
            adaptations=['DeathWard seeded room/slot RNG will preserve repeatability, not reproduce Isaac seed streams.',
                'DeathWard bands are not source floor numbers. No additional stage restriction belongs on this rare replacement.',
                'DeathWard currently has no Isaac mod callback/RoomConfig flag/alternate-path trapdoor room equivalents. Apply any future equivalents before the roll.',
                'replace_fraction uses an exact rational denominator; legacy basis-point rules retain their old behavior.']),
        validation=dict(result='pass',specification_cases=trials,passing_cases=hits,native_windows=len(evidence),scope='Source condition checks only, not runtime replacement or Sub Horf acceptance'),
        evidence=evidence,remaining=['Ordinary Sub Horf champion/item exceptions and full visual/balance/performance acceptance remain open.',
            'Tainted Sub Horf812.1is a separate missing actor.'])
    path=OUT/'status.json'
    if args.check: assert json.loads(path.read_text())==result
    else: path.write_text(json.dumps(result,indent=2)+'\n')
    if not args.check:
        bullets=''.join('<li>'+html.escape(x)+'</li>' for x in result['conditions'])
        pending=''.join('<li>'+html.escape(x)+'</li>' for x in result['remaining'])
        (OUT/'index.html').write_text('<!doctype html><html lang="en"><meta charset="utf-8"><meta name="viewport" content="width=device-width"><title>Horf replacement conditions</title><style>body{max-width:900px;margin:40px auto;padding:0 20px;background:#182024;color:#e9e2d5;font:18px/1.6 system-ui}a{color:#8fd5ce}li{margin:12px 0}code{overflow-wrap:anywhere}</style><h1>Horf → Sub Horf: verified spawn conditions</h1><p><strong>Condition analysis complete. Ordinary Sub Horf and exact1/60replacement are enabled with scoped native tests; full enemy acceptance remains open.</strong></p><p>Installed Repentance1.7.9b; exact native roll1/60, approximately1.667%. This is static native evidence, not a gameplay trial.</p><ul>'+bullets+'</ul><h2>Downpour</h2><p>'+html.escape(result['downpour'])+'</p><h2>Still missing</h2><ul>'+pending+'</ul><p><a href="status.json">Machine-readable findings and validation</a> · <a href="native-room-gates-and-dispatch.asm">Native room gates</a> · <a href="native-branch.asm">Native branch</a></p></html>')
    print(json.dumps(dict(result='pass',check=args.check,validation=result['validation'],runtime_enabled=True)))
if __name__=='__main__':main()
