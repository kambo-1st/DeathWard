#!/usr/bin/env python3
"""Capture bounded ordinary-Isaac health operations from pinned native code.

Requires pefile, capstone and unicorn==2.1.4, as for analyze-player-motion.py.
The original executable is read only. World-effect endpoints in the damage
slice are intercepted explicitly; this is NOT full TakeDamage acceptance.
"""
import argparse
import csv
import hashlib
import importlib.util
import io
import json
import struct
from pathlib import Path

import capstone
import pefile
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EBP, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_EDI, UC_X86_REG_EIP, UC_X86_REG_ESP

SPEC = importlib.util.spec_from_file_location('motion', Path(__file__).with_name('analyze-player-motion.py'))
MOTION = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(MOTION)
OUT = MOTION.ROOT / 'docs/reports/isaac-first-floor-parity/player-health'
FIELDS = {'max_red': 0x1290, 'red': 0x1294, 'eternal': 0x1298,
          'soul': 0x129c, 'black_mask': 0x12a0, 'golden': 0x186c,
          'bone': 0x1ca8, 'bone_mask': 0x1cac, 'broken': 0x1cc0, 'rotten': 0x1cc4}
API = {'red': (0x724f00, True), 'max_red': (0x724d50, True),
       'soul': (0x725130, False), 'black': (0x725380, False),
       'eternal': (0x7250a0, False), 'golden': (0x78be00, False),
       'bone': (0x78c870, False), 'rotten': (0x794930, True),
       'broken': (0x794390, False)}
WINDOWS = [('add_max_red', 0x724d50, 0x724f00), ('add_red', 0x724f00, 0x725050),
           ('add_eternal', 0x7250a0, 0x725130), ('add_soul', 0x725130, 0x725380),
           ('add_black', 0x725380, 0x725540), ('black_queries', 0x725540, 0x725600),
           ('add_golden', 0x78be00, 0x78bf20), ('red_rotten_reconcile', 0x78bf20, 0x78c000),
           ('golden_reconcile', 0x78c810, 0x78c870), ('add_bone', 0x78c870, 0x78ca00),
           ('bone_order_reconcile', 0x78cb90, 0x78cc70), ('health_capacity', 0x78cc70, 0x78cea0),
           ('add_broken', 0x794390, 0x794420), ('add_rotten', 0x794930, 0x794ac0),
           ('damage_health_slice', 0x73feb6, 0x74074c),
           ('eternal_floor_conversion', 0x76a71f, 0x76a789),
           ('black_burst_ordinary', 0x5a1841, 0x5a19f1),
           ('golden_burst_world', 0x78c350, 0x78c810),
           ('midas_freeze_entry', 0x685990, 0x685ad3)]


class NativeHealth:
    """Synthetic empty-inventory Isaac; native routines operate on native layout."""
    GAME = 0x4000000
    MANAGER = 0x5000000
    ITEMS = 0x6000000

    def __init__(self, pe):
        self.native = MOTION.NativeMotion(pe)
        self.u = self.native.u
        self.player = self.native.PLAYER
        self.effects = []
        for address, size in [(self.GAME, 0x400000), (self.MANAGER, 0x100000), (self.ITEMS, 0x100000)]:
            self.u.mem_map(address, size)
        self.write(0xbfd65c, self.GAME)
        self.write(0xbfd680, self.MANAGER)
        # Native achievement-disabled guard avoids backend/logging work.
        self.u.mem_write(self.MANAGER + 0x15, b'\x01')
        self.write(self.MANAGER + 0x29e84, self.ITEMS)
        self.write(self.MANAGER + 0x29e88, self.ITEMS + 1024 * 4)
        for index in range(1024):
            self.write(self.ITEMS + index * 4, self.ITEMS + 0x10000 + index * 0x200)
        # Real empty tree layout for native game-modifier lookups.
        sentinel = self.ITEMS + 0xf0000
        for offset in (0, 4, 8):
            self.write(sentinel + offset, sentinel)
        self.u.mem_write(sentinel + 0xc, b'\x01\x01')
        self.write(self.GAME + 0x1bb58, sentinel)
        self.u.hook_add(UC_HOOK_CODE, self.effect_boundary)
        self.reset()

    def write(self, address, value):
        self.u.mem_write(address, struct.pack('<I', value & 0xffffffff))

    def reset(self):
        self.native.reset()
        self.write(self.player + 0x28, 1)
        self.write(self.player + 0x15f0, self.ITEMS + 0xf1000)
        self.write(self.player + 0x1670, self.ITEMS + 0xf3000)
        self.write(self.player + FIELDS['max_red'], 6)
        self.write(self.player + FIELDS['red'], 6)
        self.effects.clear()

    def snapshot(self):
        return {name: struct.unpack('<i', self.u.mem_read(self.player + offset, 4))[0]
                for name, offset in FIELDS.items()}

    def effect_boundary(self, uc, address, size, data):
        if address == 0x740084:
            self.effects.append('black_burst')
            uc.reg_write(UC_X86_REG_EIP, 0x7400b7)
        elif address == 0x74022f:
            self.effects.append('bone_break_visuals')
            uc.reg_write(UC_X86_REG_EIP, 0x7402be)
        elif address == 0x78c350:
            sp = uc.reg_read(UC_X86_REG_ESP)
            ret, count = struct.unpack('<II', uc.mem_read(sp, 8))
            self.effects.append('golden_burst:' + str(count))
            uc.reg_write(UC_X86_REG_ESP, sp + 8)
            uc.reg_write(UC_X86_REG_EIP, ret)
        elif address == 0x90dd70:
            sp = uc.reg_read(UC_X86_REG_ESP)
            ret, animation, _, _ = struct.unpack('<4I', uc.mem_read(sp, 16))
            self.effects.append('health_animation:' + str(animation))
            uc.reg_write(UC_X86_REG_ESP, sp + 16)
            uc.reg_write(UC_X86_REG_EIP, ret)

    def add(self, kind, amount):
        self.effects.clear()
        function, has_ignore = API[kind]
        args = [amount, 0] if has_ignore else [amount]
        sp = self.native.STACK + 0x9000
        values = [self.native.STOP] + [value & 0xffffffff for value in args]
        self.u.mem_write(sp, struct.pack('<' + 'I' * len(values), *values))
        self.u.reg_write(UC_X86_REG_ESP, sp)
        self.u.reg_write(UC_X86_REG_ECX, self.player)
        self.run(function, self.native.STOP)

    def damage(self, amount, red_first=False):
        self.effects.clear()
        b = self.native.ebp
        self.u.mem_write(b - 0x1000, bytes(0x1100))
        self.write(b - 0x138, self.player)
        self.write(b - 0x100, amount)
        self.write(b - 0x104, 0x20 if red_first else 0)
        self.u.reg_write(UC_X86_REG_EDI, self.player)
        self.u.reg_write(UC_X86_REG_EBP, b)
        self.u.reg_write(UC_X86_REG_ESP, b - 0x1000)
        self.run(0x73feb6, 0x74074c)

    def new_floor(self):
        self.effects.clear()
        self.u.reg_write(UC_X86_REG_EBX, self.player)
        self.u.reg_write(UC_X86_REG_ESP, self.native.STACK + 0x9000)
        self.run(0x76a71f, 0x76a789)

    def run(self, start, end):
        try:
            self.u.emu_start(start, end, count=200000)
        except Exception as error:
            address = self.u.reg_read(UC_X86_REG_EIP)
            raise RuntimeError(f'native call {start:#x} faulted at {address:#x}; state={self.snapshot()}') from error
        actual = self.u.reg_read(UC_X86_REG_EIP)
        if actual != end:
            raise RuntimeError(f'native execution stopped at {actual:#x}; expected {end:#x}')


def cases():
    yield 'mixed_order', [('soul', 2), ('black', 2), ('bone', 1), ('red', 2),
                           ('rotten', 2), ('golden', 2), ('eternal', 1)] + [('damage', n) for n in [1, 2, 1, 1, 1, 2, 1, 2, 1, 1]]
    for kind in API:
        yield 'add_remove_' + kind, [(kind, n) for n in [1, 1, 2, 3, 0, -1, -2, 4, 24, -3, -24]]
    for protective in ['soul', 'black', 'bone']:
        for amount in [1, 2]:
            setup = [(protective, 3), ('red', 6), ('golden', 3)]
            yield f'deplete_{protective}_{amount}', setup + [('damage', amount)] * 12
    for order in [('bone', 'black', 'soul'), ('soul', 'bone', 'black'), ('black', 'soul', 'bone')]:
        yield 'order_' + '_'.join(order), [(kind, 2) for kind in order] + [('red', 4)] + [('damage', 1)] * 12
    yield 'broken_capacity', [('soul', 12), ('bone', 2), ('red', 4), ('golden', 8)] + [('broken', 1)] * 12
    yield 'rotten_red', [('red', -5), ('rotten', 1), ('rotten', 2), ('red', -1), ('red', -2), ('rotten', -1), ('rotten', -2)]
    yield 'rotten_damage', [('rotten', 4), ('golden', 3)] + [('damage', 1)] * 6
    yield 'eternal_last_life', [('red', -5), ('eternal', 1), ('damage', 1), ('damage', 1)]
    yield 'eternal_conversion_at_limit', [('max_red', 18), ('eternal', 1), ('eternal', 1)]
    yield 'red_first', [('black', 4), ('bone', 2), ('red', 4), ('eternal', 1), ('rotten', 2)] + [('red_first_damage', 1)] * 10
    yield 'eternal_floor_transition', [('red', -3), ('eternal', 1), ('floor', 0), ('floor', 0)]
    yield 'eternal_floor_at_limit', [('max_red', 18), ('soul', 2), ('eternal', 1), ('floor', 0)]
    yield 'eternal_floor_displaces_soul', [('soul', 18), ('eternal', 1), ('floor', 0)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--check', action='store_true')
    args = parser.parse_args()
    raw = MOTION.EXE.read_bytes()
    assert hashlib.sha256(raw).hexdigest() == MOTION.SHA
    pe = pefile.PE(data=raw)
    native = NativeHealth(pe)
    OUT.mkdir(parents=True, exist_ok=True)

    def save(name, data):
        path = OUT / name
        if args.check:
            assert path.read_bytes() == data, name
        else:
            path.write_bytes(data)

    rows = []
    for case, operations in cases():
        native.reset()
        for step, (operation, amount) in enumerate(operations):
            if operation in ('damage', 'red_first_damage'):
                state = native.snapshot()
                if state['red'] + state['soul'] + state['bone'] == 0:
                    break  # Death/revival pipeline is outside the captured slice.
                native.damage(amount, operation == 'red_first_damage')
            elif operation == 'floor':
                native.new_floor()
            else:
                try:
                    native.add(operation, amount)
                except Exception as error:
                    raise RuntimeError(f'{case} step {step}: {operation}({amount})') from error
            rows.append([case, step, operation, amount, *native.snapshot().values(), '|'.join(native.effects)])
    stream = io.StringIO(newline='')
    writer = csv.writer(stream, lineterminator='\n')
    writer.writerow(['case', 'step', 'operation', 'amount', *FIELDS, 'effect_intents'])
    writer.writerows(rows)
    save('native-health.csv', stream.getvalue().encode())
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    windows = []
    for name, start, end in WINDOWS:
        blob = pe.get_data(start - pe.OPTIONAL_HEADER.ImageBase, end - start)
        listing = ''.join(f'{i.address:08x} {i.mnemonic} {i.op_str}\n' for i in md.disasm(blob, start)).encode()
        save(name + '.asm', listing)
        windows.append({'name': name, 'start': hex(start), 'end_exclusive': hex(end),
                        'raw_sha256': hashlib.sha256(blob).hexdigest(), 'listing_sha256': hashlib.sha256(listing).hexdigest()})
    manifest = {'version': 'Repentance 1.7.9b', 'exe_sha256': MOTION.SHA,
                'emulator': 'Unicorn 2.1.4', 'rows': len(rows), 'cases': len({row[0] for row in rows}),
                'scope': 'Ordinary Isaac with empty inventory: nine health-add APIs, bounded health-mutation slice of TakeDamage and ordinary eternal floor conversion. These captures establish scoped arithmetic, not full native gameplay acceptance. DW integration is documented separately.',
                'fixture': 'Type 0 Isaac, six red halves initially, empty collectibles/trinkets/effects/modifier tree, zero game modifiers, disabled achievements, unregistered HUD actor; zero-filled item metadata for empty-inventory queries.',
                'interceptions': [
                    '0x740084 -> 0x7400b7: record black-heart UseActiveItem(35) intent; skip world damage and sound.',
                    '0x74022f -> 0x7402be: record bone-break visual intent; skip particles/TLS RNG/sound.',
                    '0x78c350: record golden burst count, return with native callee stack cleanup; skip coin/world spawning.',
                    '0x90dd70: record health animation ID and return with native stack cleanup; skip sprite playback.'],
                'damage_entry': '0x73feb6, integer half-heart amount local, default flags or low flag 0x20; source prechecks/float conversion and prior local calculations are outside this fixture.',
                'damage_exit': '0x74074c, before death/revival and remaining callbacks.',
                'floor_scope': '0x76a71f-0x76a789: ordinary eternal conversion only; not whole native floor transition.',
                'static_effect_findings': {
                    'black_base_damage': '0x5a189c-0x5a18ac: 40 * (1 + collectible 262 count + trinket 48 count); empty inventory = 40. Target filtering and payload are disassembled, not executed here.',
                    'golden_coins': '0x78c606-0x78c617: native RNG uint modulo 6 + 3 per burst (3-8). Spawn physics and global RNG stream remain unverified.',
                    'golden_status': '0x78c6e7 loads query radius 80; 0x78c75a supplies 180 to 0x685990. Distinct Midas freeze, not ordinary freeze; eligibility/duration adjustments remain open.'},
                'unverified': ['whole TakeDamage flags and preconditions', 'hit cooldown', 'effect payloads and RNG',
                               'golden coin counts/physics', 'black burst enemy damage', 'world pickups',
                               'complete floor-transition effects', 'items/other characters', 'live game captures'],
                'windows': windows}
    save('manifest.json', (json.dumps(manifest, indent=2) + '\n').encode())
    print(f'{"Checked" if args.check else "Captured"} {len(rows)} native health transitions across {manifest["cases"]} cases; full gameplay acceptance remains open.')


if __name__ == '__main__':
    main()
