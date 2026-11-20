#!/usr/bin/env python3
"""Execute pinned shop coin-donation initialization gates, without a live game.

This is evidence capture, not an enabled DeathWard donation economy. Seed-effect
and mod-policy query results are supplied. Original run flags, custom-run byte,
remaining restrictions, counter digits and removal-state stores execute natively.
"""
import argparse
import csv
import hashlib
import importlib.util
import io
import itertools
import json
import struct
from pathlib import Path
import xml.etree.ElementTree as ET
import capstone
import pefile
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_EBP, UC_X86_REG_ECX, UC_X86_REG_EIP, UC_X86_REG_ESP

spec = importlib.util.spec_from_file_location('awards', Path(__file__).with_name('analyze-room-awards.py'))
A = importlib.util.module_from_spec(spec)
spec.loader.exec_module(A)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    raw = A.M.EXE.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == A.M.SHA
    pe = pefile.PE(data=raw)
    f = A.NativeAwards(pe, raw)
    u, n = f.u, f.n
    u.mem_map(f.MANAGER + 0x100000, 0x200000)
    actor = f.HEAP + 0x10000
    state, calls, digits = {}, [], []
    out = A.M.ROOT / 'docs/reports/isaac-first-floor-parity/d14a13-donation-eligibility/source'
    out.mkdir(parents=True, exist_ok=True)

    def save(name, data):
        path = out / name
        if args.check:
            assert path.read_bytes() == data, name
        else:
            path.write_bytes(data)

    def ret(cleanup=0, value=0):
        sp = u.reg_read(UC_X86_REG_ESP)
        target = f.integer(sp)
        u.reg_write(UC_X86_REG_ESP, sp + 4 + cleanup)
        u.reg_write(UC_X86_REG_EAX, value)
        u.reg_write(UC_X86_REG_EIP, target)

    def host(uc, address, size, data):
        calls.append(address)
        if address == 0x93c4d0:
            ret(value=state['effect'])
        elif address == 0x8b3eb0:
            ret(4, state['mods'])
        elif address == 0x802b70:
            ret(4)  # Room removal queue; original Remove stores still execute.
        elif address == 0x405950:
            sp = uc.reg_read(UC_X86_REG_ESP)
            digits.append([f.integer(sp + 4), f.integer(sp + 8)])
            ret(8)
        elif address in (0x405850, 0x4054f0):
            ret(8)  # Visual animation selection only.
        elif address == 0x6c3d90:
            ret(value=1)  # Cosmetic jam variant; not admission RNG.

    for address in (0x93c4d0, 0x8b3eb0, 0x802b70, 0x405950, 0x405850, 0x4054f0, 0x6c3d90):
        u.hook_add(UC_HOOK_CODE, host, begin=address, end=address)

    # Vtable virtual Init and Remove, and the named Seeds::IsCustomRun binding.
    assert struct.unpack('<I', pe.get_data(0xb46968 - 0x400000, 4))[0] == 0x639180
    assert struct.unpack('<I', pe.get_data(0xb4698c - 0x400000, 4))[0] == 0x6848f0
    assert pe.get_data(0xb54bc0 - 0x400000, 12) == b'IsCustomRun\0'
    assert pe.get_data(0x80997f - 0x400000, 10) == b'\x68' + struct.pack('<I', 0x68f4d0) + b'\x68' + struct.pack('<I', 0xb54bc0)

    rows = []
    for bits in itertools.product((0, 1), repeat=7):
        excluded, jammed, custom, effect, mods, runflag, profile = bits
        for bank in (0, 1, 9, 10, 99, 100, 998, 999, 1000, 1001):
            state.update(effect=effect, mods=mods)
            calls.clear()
            digits.clear()
            f.write(actor, 0xb46964)
            f.write(actor + 0x360, 1)
            f.write(actor + 0x35c, 0)
            u.mem_write(actor + 0x16a, b'\x01\x00')
            f.write(f.GAME + 0x1c3168, (excluded << 17) | (jammed << 18))
            f.write(f.GAME + 0x1c316c, 0)
            u.mem_write(f.GAME + 0x1bb04, bytes([custom]))
            u.mem_write(f.GAME + 0x1c31a0, bytes([runflag]))
            f.write(f.MANAGER + 0x20a9ac, 1)
            f.write(f.MANAGER + 0x20a9b0, 1 + profile)
            f.write(f.MANAGER + 0x31c, bank)
            u.reg_write(UC_X86_REG_EBX, actor)
            u.reg_write(UC_X86_REG_ESP, n.STACK + 0x7000)
            u.reg_write(UC_X86_REG_EBP, n.ebp)
            u.emu_start(0x63937a, 0x639593, count=20000)
            assert u.reg_read(UC_X86_REG_EIP) == 0x639593
            active, removed = u.mem_read(actor + 0x16a, 2)
            phase = f.integer(actor + 0x360)
            expected = int(any((excluded, custom, effect, mods, runflag, profile)))
            assert removed == expected and active == 1 - expected
            assert phase == (3 if jammed else 1)
            assert digits == [[1, (bank // 100) % 10], [2, (bank // 10) % 10], [3, bank % 10]]
            assert (0x802b70 in calls) == bool(removed)
            rows.append([*bits, bank, active, removed, phase, *[d[1] for d in digits],
                         int(0x93c4d0 in calls), int(0x8b3eb0 in calls)])
    buf = io.StringIO()
    writer = csv.writer(buf, lineterminator='\n')
    writer.writerow(['run_flag17', 'run_flag18', 'custom_run', 'blocked_seed_effect_query',
                     'blocked_mod_policy_query', 'run_byte1c31a0', 'profile_vector_nonempty',
                     'bank', 'active', 'removed', 'state', 'hundreds', 'tens', 'ones',
                     'seed_effect_queried', 'mod_policy_queried'])
    writer.writerows(rows)
    save('native-initialization.csv', buf.getvalue().encode())

    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    windows = []
    for name, start, end in [
        ('variant-dispatch', 0x639371, 0x63937a),
        ('coin-donation-initialization', 0x63937a, 0x63946b),
        ('restriction-helper', 0x6d7180, 0x6d71ca),
        ('run-flag-query', 0x41c430, 0x41c475),
        ('remove', 0x6848f0, 0x684948),
        ('factory-init-call', 0x6d0db2, 0x6d0dec),
        ('custom-run-binding', 0x80997f, 0x809989),
        ('custom-run-getter', 0x68f4d0, 0x68f4d3),
        ('overflow-flag-store', 0x63dcba, 0x63dcc9),
        ('jam-flag-store', 0x63dd89, 0x63dda2),
    ]:
        blob = pe.get_data(start - 0x400000, end - start)
        save(name + '.asm', ('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}'.rstrip()
                                      for i in md.disasm(blob, start)) + '\n').encode())
        windows.append(dict(name=name, start=hex(start), end=hex(end), sha256=hashlib.sha256(blob).hexdigest()))
    xml = A.M.ROOT / 'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3/entities2.xml'
    entity = next(e for e in ET.parse(xml).getroot().iter('entity') if e.get('id') == '6' and e.get('variant') == '8')
    manifest = dict(executable_sha256=A.M.SHA, version='Repentance1.7.9b', cases=len(rows),
                    entity=entity.attrib, entity_xml_sha256=hashlib.sha256(xml.read_bytes()).hexdigest(),
                    windows=windows, gameplay_changed=False, historical_capture_gate_inputs_known=False,
                    scope='Original ordinary variant8 initialization, counter display arithmetic, run-state bit queries, restriction helper and entity Remove stores. Seed-effect/mod-policy query results, visual calls, cosmetic RNG and removal-queue endpoint are hosted. No patches to decision instructions. Source initialization/factory entry and named custom-run binding are pinned; complete factory/base init, query internals, donation economy, scheduling and persistent bank are not accepted.',
                    rule='Remove if flag17 or custom run or any supplied restriction. Independently flag18 sets state3 (jammed). Bank value alone does not exclude the actor in this initializer.',
                    source_profile_note='Having a procedural numeric seed is not the same as IsCustomRun. Do not infer the flag from DeathWard --seed or the recorded Isaac seed text.',
                    full_native_acceptance=False)
    save('manifest.json', (json.dumps(manifest, indent=2) + '\n').encode())
    print(f'PASS {len(rows)} native coin-donation initialization/removal/jam/counter cases')


if __name__ == '__main__':
    main()
