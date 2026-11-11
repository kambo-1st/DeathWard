"""Link pinned local x86 UCRT math exports into the isolated native fixture.

Only mapped import pointers are resolved, as by a loader. No instructions are
patched, no DLL initialization/OS process is run and no host math is substituted.
Finite ordinary inputs use the DLL's numeric path, not its OS/error slow paths.
"""
import hashlib
import struct
from pathlib import Path
import pefile
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_FPCW,UC_X86_REG_MXCSR

PATH=Path('/mnt/c/Windows/SysWOW64/ucrtbase.dll')
SHA='e4f8f92eef00ff6a0c6d418af756a59d5a4b818d0d1de0d96cc193b4d6759432'
NAMES=('_libm_sse2_cos_precise','_libm_sse2_sin_precise','_libm_sse2_pow_precise')

class NativeMath:
    def __init__(self,fixture,exe,extra_exports=()):
        data=PATH.read_bytes();assert hashlib.sha256(data).hexdigest()==SHA,'Local x86 UCRT changed'
        dll=pefile.PE(data=data);assert dll.FILE_HEADER.Machine==0x14c
        self.base=dll.OPTIONAL_HEADER.ImageBase;assert self.base==0x10000000
        fixture.u.mem_map(self.base,(dll.OPTIONAL_HEADER.SizeOfImage+4095)&~4095)
        fixture.u.mem_write(self.base,dll.get_memory_mapped_image())
        exports={e.name.decode():self.base+e.address for e in dll.DIRECTORY_ENTRY_EXPORT.symbols if e.name and not e.forwarder}
        names=(*NAMES,*extra_exports)
        self.links={};self.calls={name:0 for name in names};addresses={exports[name]:name for name in names}
        for entry in exe.DIRECTORY_ENTRY_IMPORT:
            for item in entry.imports:
                name=item.name.decode() if item.name else ''
                if name in names:
                    fixture.u.mem_write(item.address,struct.pack('<I',exports[name]))
                    self.links[name]={'contract':entry.dll.decode(),'iat':hex(item.address),'export':hex(exports[name])}
        assert len(self.links)==len(names)
        fixture.u.reg_write(UC_X86_REG_FPCW,0x027f);fixture.u.reg_write(UC_X86_REG_MXCSR,0x1f80)
        def count(uc,address,size,data):self.calls[addresses[address]]+=1
        for address in addresses:fixture.u.hook_add(UC_HOOK_CODE,count,begin=address,end=address)
    def manifest(self):
        return {'path':str(PATH),'sha256':SHA,'image_base':hex(self.base),'links':self.links,'calls':self.calls,
                'x87_control_word':'0x027f','mxcsr':'0x1f80','scope':'Original local x86 UCRT numeric instructions for finite ordinary inputs. Loader-style IAT resolution in emulated memory only; no host math or instruction substitutions. DLL initialization/OS error paths and live process loader selection are not claimed.'}
