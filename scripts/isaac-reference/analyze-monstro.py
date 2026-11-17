#!/usr/bin/env python3
"""Pin ordinary Monstro dispatch/AI and execute bounded native decisions/forces.

No game code is modified. Supplied RNG words and targets are explicit inputs;
this does not execute whole world/animation callbacks or establish acceptance.
"""
import argparse
import csv
import hashlib
import importlib.util
import io
import json
import struct
from pathlib import Path
import xml.etree.ElementTree as ET

import capstone
import pefile
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDI, UC_X86_REG_ESI, UC_X86_REG_EBP, UC_X86_REG_ESP

SPEC = importlib.util.spec_from_file_location('motion', Path(__file__).with_name('analyze-player-motion.py'))
M = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(M)
OUT = M.ROOT / 'docs/reports/isaac-first-floor-parity/monstro'
XML = M.ROOT / 'reference/isaac-repentance-1.7.9b/extracted/repentance/resources-dlc3/entities2.xml'
WINDOWS = [('ordinary_and_shared_ai', 0x45bec0, 0x45dd3b),
           ('boss_projectile_constructor', 0x6a3420, 0x6a3963),
           ('projectile_params_constructor', 0x430d70, 0x430ed4),
           ('target_position', 0x695a30, 0x695e30),
           ('normalize_vector', 0x962560, 0x9625b0),
           ('ordinary_physics', 0x686406, 0x686497),
           ('collision_property_binding', 0x80548c, 0x8054aa),
           ('entity_collision_getter', 0x412230, 0x412237),
           ('entity_collision_setter', 0x4273c0, 0x4273d0),
           ('grid_collision_getter', 0x432f40, 0x432f47),
           ('grid_collision_setter', 0x43dcc0, 0x43dcd0)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    raw = M.EXE.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == M.SHA
    pe = pefile.PE(data=raw)
    read = lambda address, size: pe.get_data(address-pe.OPTIONAL_HEADER.ImageBase, size)
    OUT.mkdir(parents=True, exist_ok=True)

    def save(name, blob):
        path = OUT / name
        if args.check:
            assert path.read_bytes() == blob, name
        else:
            path.write_bytes(blob)

    def table(name, fields, rows):
        buf = io.StringIO(newline='')
        w = csv.writer(buf, lineterminator='\n')
        w.writerow(fields)
        w.writerows(rows)
        save(name, buf.getvalue().encode())

    index = read(0x69abc0+20-10, 1)[0]
    case = struct.unpack('<I', read(0x69a7f8+4*index, 4))[0]
    assert index == 8 and case == 0x6997a8
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    dispatch = list(md.disasm(read(case, 12), case))
    assert any(i.mnemonic == 'call' and i.op_str == '0x45bec0' for i in dispatch)
    assert read(0xb51a84, 21) == b'EntityCollisionClass\0'
    assert read(0xb519c0, 19) == b'GridCollisionClass\0'
    assert read(0x412230, 7) == bytes.fromhex('8b8180010000c3')
    assert read(0x432f40, 7) == bytes.fromhex('8b817c010000c3')
    save('dispatch.asm', ('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in dispatch)+'\n').encode())
    windows = []
    for name, start, end in WINDOWS:
        blob = read(start, end-start)
        save(name+'.asm', ('\n'.join(f'{i.address:08x} {i.mnemonic} {i.op_str}' for i in md.disasm(blob, start))+'\n').encode())
        windows.append({'name': name, 'start': hex(start), 'end_exclusive': hex(end), 'raw_sha256': hashlib.sha256(blob).hexdigest(), 'scope': 'bounded linear disassembly; helper windows may end before their full function'})

    n = M.NativeMotion(pe)
    u, p, b = n.u, n.PLAYER, n.ebp

    def write(address, value):
        u.mem_write(address, struct.pack('<I', value & 0xffffffff))

    def setup():
        n.reset()
        u.mem_write(b-0x1000, bytes(0x1100))
        u.reg_write(UC_X86_REG_EDI, p)
        u.reg_write(UC_X86_REG_EBP, b)
        u.reg_write(UC_X86_REG_ESP, b-0x1000)
        write(p+0x28, 20)
        write(b-0x1a4, -1)

    decisions = []
    words = [0, 1, 2, 3, 4, 5, 17, 29, 30, 31, 1234567, 0x7fffffff, 0x80000000, 0xfffffffd, 0xfffffffe, 0xffffffff]
    for subtype in (0, 1, 2):
        for word in words:
            setup()
            write(p+0x30, subtype)
            u.reg_write(UC_X86_REG_EAX, word)
            # The RNG call is before this entry. Execute real modulo/dispatch.
            n.run(0x45c870, 0x45c84b)
            action = struct.unpack('<i', u.mem_read(p+0xb14, 4))[0]
            decisions.append([subtype, word, action])
    table('native-decisions.csv', ['subtype', 'supplied_rng_word', 'action'], decisions)

    forces = []
    for mode in ('small_hop', 'large_jump'):
        for dx, dz in [(0, 0), (.001, 0), (10, 0), (0, -10), (30, 40), (-40, 30), (200, 100), (-200, -100)]:
            for vx, vz in [(0, 0), (2, -1)]:
                setup()
                n.write_float(p+0x294, 0)
                n.write_float(p+0x298, 0)
                n.write_float(p+0x28c, dx)
                n.write_float(p+0x290, dz)
                n.write_float(p+0x2b8, vx)
                n.write_float(p+0x2bc, vz)
                n.write_float(p+0x2c4, 1)
                n.write_float(p+0x2f4, 1)
                # Native common controller entry damps its temporary friction.
                n.run(0x45bf03, 0x45bf2a)
                if mode == 'small_hop':
                    n.run(0x45d015, 0x45d1f0)
                else:
                    u.reg_write(UC_X86_REG_ESI, p+0x28c)
                    n.run(0x45d625, 0x45d6f9)
                forces.append([mode, dx, dz, vx, vz,
                               n.read_float(p+0x2b8), n.read_float(p+0x2bc), n.read_float(p+0x2c4)])
    table('native-forces.csv', ['mode', 'target_dx', 'target_dz', 'velocity_x', 'velocity_z', 'next_velocity_x', 'next_velocity_z', 'temporary_friction'], forces)
    payloads = []
    for trajectory in (0, 10):
        for word in (0, 1, 1234567, 0x7fffffff, 0x80000000, 0xffffffff):
            for bit in (0, 1):
                setup()
                sp=b-0x1000
                params=n.STACK+0x700
                n.write_float(b+0x10, trajectory)
                write(b+0x14, params)
                n.write_float(params+0x14, 1)
                n.write_float(sp+0x18, 1)
                n.run(0x6a3466, 0x6a3494)
                acceleration=n.read_float(sp+0x24)
                u.reg_write(UC_X86_REG_EAX, word)
                n.run(0x6a36cf, 0x6a3718)
                falling=n.read_float(p+0x364)
                u.reg_write(UC_X86_REG_ESI, bit)
                u.reg_write(UC_X86_REG_EAX, word)
                n.run(0x6a3727, 0x6a3794)
                payloads.append([trajectory, word, bit, word, falling, acceleration, n.read_float(p+0x370)])
    table('native-projectile-payload.csv', ['trajectory', 'fall_word', 'size_bit', 'size_jitter_word', 'falling_speed', 'falling_acceleration', 'size'], payloads)
    entity = next(e for e in ET.parse(XML).getroot() if e.get('id') == '20' and e.get('variant') == '0')
    assert entity.get('baseHP') == '250' and entity.get('stageHP') == '0'
    manifest = {'baseline': 'Installed Repentance 1.7.9b', 'executable_sha256': M.SHA,
                'dispatch': {'type': 20, 'index': index, 'case': hex(case), 'controller': '0x45bec0'},
                'source_entity_xml': {'path': str(XML.relative_to(M.ROOT)), 'sha256': hashlib.sha256(XML.read_bytes()).hexdigest(), 'attributes': dict(entity.attrib)},
                'decision_cases': len(decisions), 'force_cases': len(forces), 'projectile_payload_cases': len(payloads), 'windows': windows,
                'collision_properties': {'entity': {'offset': '0x180', 'getter': '0x412230', 'setter': '0x4273c0', 'name': '0xb51a84'}, 'grid': {'offset': '0x17c', 'getter': '0x432f40', 'setter': '0x43dcc0', 'name': '0xb519c0'}, 'scope': 'Pinned property-registration and getter/setter disassembly identify fields, not complete collision handling.'},
                'executed_scope': 'Supplied RNG words after the native call; original modulo/subtype remapping. Native ordinary-controller common friction prefix followed by bounded small-hop or large-jump force update with supplied target/vector/timeScale1. Original sqrt and vector-normalization helpers execute; no helper/interception substitutions.',
                'capture_claims_runtime_acceptance': False, 'full_actor_accepted': False,
                'remaining': ['complete native state/animation callback ordering', 'room grid target selection and collision-class mapping', 'boss projectile birth/physics and global RNG stream', 'champion variants and all nonordinary branches', 'live timing and spatial calibration', 'damage/status/death and room-clear contracts', 'Basement pool unlock/exclusion/selection conditions and production integration']}
    save('manifest.json', (json.dumps(manifest, indent=2)+'\n').encode())
    print(f'Monstro native kernels: {len(decisions)} decisions, {len(forces)} forces, {len(payloads)} projectile payloads; full actor acceptance remains open.')


if __name__ == '__main__':
    main()
