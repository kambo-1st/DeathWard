004f6fd2 push 1
004f6fd4 push 0xb41e78
004f6fd9 lea ecx, [edi + 0x3c]
004f6fdc call 0x405bb0
004f6fe1 test al, al
004f6fe3 je 0x4f6ffc
004f6fe5 cmp dword ptr [edi + 0x90], 0
004f6fec je 0x4f6ffc
004f6fee lea ecx, [edi + 0x8c]
004f6ff4 xorps xmm1, xmm1
004f6ff7 call 0x403c00
